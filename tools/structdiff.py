#!/usr/bin/env python3
"""Split a near-miss into STRUCTURAL rows and REGISTER-PERMUTATION rows.

WHY THIS EXISTS
    `mism` conflates two completely different situations. A candidate whose control flow,
    immediates and stack offsets are all correct but whose register allocation is permuted
    scores WORSE than one that is structurally wrong -- a permutation touches every
    instruction naming the register, while a wrong branch touches one. Ranking variants by
    `mism` at the endgame therefore climbs the wrong hill, and an automated search that
    optimises `mism` will do the same, confidently.

    This answers the question `mism` cannot: "is what remains a real defect, or is my
    function already correct and merely coloured differently?"

IT ALIGNS THE TWO STREAMS FIRST
    A candidate one instruction short makes every later row differ index-to-index, which
    naively reads as hundreds of structural defects when the real fault is one missing
    instruction. The first version of this tool did exactly that: it reported 75 "structural"
    rows for a function whose streams were merely shifted by one. Alignment is not a
    refinement here, it is the difference between a useful answer and a confident wrong one.

WHAT IT REPORTS
    * INSERT/DELETE blocks -- the stream shapes diverge. A real defect; fix first.
    * IMMEDIATE/OFFSET rows -- same opcode, different constant or stack offset. Real, EXCEPT
      that %hi/%lo and jal targets are unresolved in a .o, so some are relocation noise.
    * REGISTER-ONLY rows -- every field identical except which registers are named. This is
      allocator output, not a source defect.
    * the permutation implied by those rows, and whether it is one consistent renaming.

    No structural rows + a consistent permutation means the source is very likely already
    right and the residue is a register-allocation tie -- the class 43k permuter iterations
    failed to move. Stop spelling; change what the allocator ranks.

USAGE
    python3 tools/structdiff.py <tu> <func> <candidate.c>
"""

import collections
import difflib
import io
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fastscore  # noqa: E402

REG = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
       "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
       "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
       "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"]

# Opcodes whose low 16 bits are an immediate/offset, not a register field.
I_TYPE = (set(range(0x08, 0x10)) |
          {0x01, 0x04, 0x05, 0x06, 0x07, 0x0F, 0x14, 0x15, 0x16, 0x17,
           0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x28, 0x29, 0x2A, 0x2B, 0x2E,
           0x31, 0x35, 0x39, 0x3D})


def decode(w):
    return dict(op=w >> 26, rs=(w >> 21) & 31, rt=(w >> 16) & 31, rd=(w >> 11) & 31,
                sa=(w >> 6) & 31, fn=w & 0x3F, imm=w & 0xFFFF)


def shape(d):
    """Everything except which registers are used."""
    if d["op"] in I_TYPE:
        return (d["op"], d["imm"])
    if d["op"] == 0:
        return (d["op"], d["fn"], d["sa"])
    return (d["op"], d["imm"], d["fn"], d["sa"])


def regfields(d):
    """The register slots this instruction actually names."""
    if d["op"] in I_TYPE:
        return [d["rs"], d["rt"]]
    if d["op"] == 0:
        return [d["rs"], d["rt"], d["rd"]]
    if d["op"] == 0x11:                        # COP1: rt is the GPR, the rest are FPRs
        return [d["rt"]]
    return [d["rs"], d["rt"], d["rd"]]


RELOC_MASK = {"R_MIPS_26": 0x03FFFFFF, "R_MIPS_HI16": 0xFFFF,
              "R_MIPS_LO16": 0xFFFF, "R_MIPS_GPREL16": 0xFFFF}


def reloc_offsets(ob, func):
    """Byte offsets within <func> that carry a relocation, and the field to blank.

    Our object has %hi/%lo and jal targets UNRESOLVED (zero); golden's words come from the
    ROM and are resolved. Comparing them raw manufactures dozens of phantom "immediate"
    differences. fastscore masks these; this tool has to as well or one whole category of
    its output is noise.
    """
    out = {}
    try:
        rel = subprocess.check_output([fastscore.OBJDUMP, "-r", ob]).decode()
    except Exception:
        return out
    sect = None
    for line in rel.splitlines():
        m = re.match(r"^RELOCATION RECORDS FOR \[(.*)\]", line)
        if m:
            sect = m.group(1)
            continue
        if sect != ".text":
            continue
        m = re.match(r"^([0-9a-f]+)\s+(\S+)\s", line)
        if m and m.group(2) in RELOC_MASK:
            out[int(m.group(1), 16)] = RELOC_MASK[m.group(2)]
    return out


def streams(tu, func, cand):
    """Full instruction words for (ours, golden) -- not just the mismatching rows."""
    sc = fastscore.Scorer(tu, func)
    ob, err = sc._compile(io.open(cand, encoding="utf-8", errors="replace").read(), "sd")
    if err:
        return None, None, err
    dis = subprocess.check_output([fastscore.OBJDUMP, "-dz", ob]).decode()
    ours, addrs, on, base = [], [], False, None
    for line in dis.splitlines():
        m0 = re.match(r"^([0-9a-f]+) <%s>:" % re.escape(func), line)
        if m0:
            on, base = True, int(m0.group(1), 16)
            continue
        if on:
            if re.match(r"^[0-9a-f]+ <", line):
                break
            m = re.match(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})", line)
            if m:
                addrs.append(int(m.group(1), 16))
                ours.append(int(m.group(2), 16))
    gsrc = os.path.join(fastscore.CONKER, "asm/nonmatchings", tu, func + ".s")
    gold = []
    for line in io.open(gsrc, encoding="utf-8", errors="replace"):
        m = re.match(r"^\s*/\*\s*\S+\s+\S+\s+([0-9A-Fa-f]{8})\s*\*/", line)
        if m:
            gold.append(int(m.group(1), 16))
    # Blank every relocated field in BOTH streams so relocation noise cannot masquerade
    # as an immediate/offset defect.
    rl = reloc_offsets(ob, func)
    for i, a in enumerate(addrs):
        mask = rl.get(a)
        if mask is not None:
            ours[i] &= ~mask
            if i < len(gold):
                gold[i] &= ~mask
    return ours, gold, None


def main(argv):
    if len(argv) < 3:
        print(__doc__.strip().split("USAGE")[-1].strip())
        return 2
    tu, func, cand = argv[0], argv[1], argv[2]
    ours, gold, err = streams(tu, func, cand)
    if err:
        print("could not compile: %s" % err)
        return 1

    # Align on the OPCODE only (plus the function code for R-type).
    #
    # Do NOT put `fn` in the key unconditionally: for an I-type instruction `fn` is the low
    # six bits of the IMMEDIATE, so `addiu sp,-168` and `addiu sp,-0xB8` get different keys
    # and refuse to align. That bug fragmented exact-length functions into ~20 bogus
    # "length-changing blocks" and made three near-misses look structurally broken when they
    # were not. The key must ignore immediates and registers entirely.
    def key(w):
        d = decode(w)
        return (d["op"], d["fn"]) if d["op"] == 0 else (d["op"],)

    ko = [key(w) for w in ours]
    kg = [key(w) for w in gold]
    sm = difflib.SequenceMatcher(a=ko, b=kg, autojunk=False)

    blocks, opcode_rows, imm_rows, register = [], [], [], []
    pairs = collections.Counter()
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != "equal":
            # An equal-length "replace" is not an insert/delete -- it is N positions where the
            # OPCODE differs. Reporting those as length changes overstates the damage badly.
            if tag == "replace" and (i2 - i1) == (j2 - j1):
                for i, j in zip(range(i1, i2), range(j1, j2)):
                    opcode_rows.append((i, j, ours[i], gold[j]))
            else:
                blocks.append((tag, i1, i2, j1, j2))
            continue
        for i, j in zip(range(i1, i2), range(j1, j2)):
            if ours[i] == gold[j]:
                continue
            do, dg = decode(ours[i]), decode(gold[j])
            if shape(do) != shape(dg):
                imm_rows.append((i, j, ours[i], gold[j]))
                continue
            moved = [(a, b) for a, b in zip(regfields(do), regfields(dg)) if a != b]
            if moved:
                register.append((i, j, moved))
                for a, b in moved:
                    pairs[(a, b)] += 1
            else:
                imm_rows.append((i, j, ours[i], gold[j]))

    print("%s / %s   ours=%d gold=%d words" % (tu, func, len(ours), len(gold)))
    print("LENGTH-CHANGING blocks %d   OPCODE rows %d   IMMEDIATE/OFFSET rows %d   "
          "REGISTER-ONLY rows %d"
          % (len(blocks), len(opcode_rows), len(imm_rows), len(register)))
    print()

    if blocks:
        print("INSERT/DELETE -- a real structural defect, fix before anything else:")
        for tag, i1, i2, j1, j2 in blocks[:12]:
            print("    %-8s ours[%d:%d] (%d words)  vs  gold[%d:%d] (%d words)"
                  % (tag, i1, i2, i2 - i1, j1, j2, j2 - j1))
        print()

    if opcode_rows:
        print("OPCODE rows -- same position, DIFFERENT instruction. Real defects; these are")
        print("where the two versions genuinely do different work (e.g. a register move where")
        print("golden stores to the stack):")
        for i, j, a, b in opcode_rows[:12]:
            print("    ours[%-4d]=%08x   gold[%-4d]=%08x" % (i, a, j, b))
        if len(opcode_rows) > 12:
            print("    ... %d more" % (len(opcode_rows) - 12))
        print()

    if imm_rows:
        print("IMMEDIATE / OFFSET rows (%hi/%lo and jal targets are unresolved in a .o, so")
        print("some of these are relocation noise rather than defects):")
        for i, j, a, b in imm_rows[:12]:
            print("    ours[%-4d]=%08x   gold[%-4d]=%08x" % (i, a, j, b))
        if len(imm_rows) > 12:
            print("    ... %d more" % (len(imm_rows) - 12))
        print()

    if register:
        src = collections.defaultdict(collections.Counter)
        for (a, b), n in pairs.items():
            src[a][b] += n
        consistent = all(len(v) == 1 for v in src.values())
        print("REGISTER permutation implied by the register-only rows:")
        for a in sorted(src):
            print("    %-4s -> %s" % (REG[a], ", ".join("%s x%d" % (REG[b], n)
                                                        for b, n in src[a].most_common())))
        print()
        print("    permutation is %s" % ("CONSISTENT (one global renaming)" if consistent
                                         else "INCONSISTENT (more than one target per source)"))
        if consistent and not blocks and not imm_rows and not opcode_rows:
            print()
            print("    *** NO STRUCTURAL ROWS. The source is very likely already correct and")
            print("        the residue is a register-allocation tie. More spellings will not")
            print("        move it -- change what the allocator RANKS (live-range count,")
            print("        first-reference order, how many invariants are simultaneously live).")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
