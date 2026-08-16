#!/usr/bin/env python3
"""relcheck.py -- NON-CIRCULAR byte proof for one function, independent of expected/.

WHY THIS EXISTS
    Some TUs have no original object in conker/expected/, so one has to be SEEDED -- generated
    from our own source.  Verifying against a seeded golden is partly CIRCULAR: it proves we
    reproduce ourselves.  The ROM gate is the real authority, but it is a whole-ROM, minutes-long
    check that says nothing about which function was wrong when it fails.

    This closes the gap at the function level.  fastscore proves our instruction words equal the
    ROM disassembly with every relocated field MASKED; the mask is the hole, because a relocation
    could point anywhere.  Here every relocation in our REAL object is resolved against the
    project's own address map -- splat's `glabel <name>` plus vaddr comments across conker/asm,
    together with undefined_*_auto.txt and symbol_addrs.us.txt -- and the composed field is
    compared with what the ROM actually encodes.

    NOTHING HERE READS expected/.  The verdict cannot inherit an error from a seeded object.

WHAT IT CHECKS
    * instruction count equals golden's
    * every UNRELOCATED word is byte-equal to the ROM
    * every R_MIPS_26 target composes to the ROM's encoded target
    * every HI16/LO16 pair composes (with the +0x8000 carry) to the ROM's encoded halves
    * no HI16 is left unpaired, and no relocation type goes unhandled

    Any symbol whose address is unknown is a FAILURE, not a skip -- an unresolvable name is
    exactly the case where a wrong reference would hide.  This is the fail-closed rule that
    tools/verify_match.sh follows: no-evidence is never a pass.

ALWAYS NEGATIVE-CONTROL IT.  Point it at a knowingly-wrong build and confirm it FAILS with the
expected row count before you trust a PASS.  A checker that has only ever passed proves nothing;
this project has had three separate tools whose failure state produced a plausible number.

USAGE
    tools/relcheck.py <object> <func> [golden.s]
        <object>    e.g. conker/build/src/libultra/audio/game_21FC90.c.o
        <func>      e.g. func_151F2E88
        golden.s    optional; by default it is located under conker/asm/nonmatchings/**/<func>.s
"""
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
CONKER = os.path.join(REPO, "conker")
OBJDUMP = "mips-linux-gnu-objdump"


def find_golden(func):
    for root, _dirs, files in os.walk(os.path.join(CONKER, "asm", "nonmatchings")):
        if func + ".s" in files:
            return os.path.join(root, func + ".s")
    raise SystemExit("could not locate golden .s for %s under asm/nonmatchings" % func)


def load_symbols():
    syms = {}
    for f in ["undefined_syms_auto.txt", "undefined_funcs_auto.txt", "symbol_addrs.us.txt",
              "undefined_syms.us.txt", "undefined_funcs.us.txt"]:
        try:
            txt = open(os.path.join(CONKER, f)).read()
        except IOError:
            continue
        for name, val in re.findall(r"^\s*([A-Za-z_.][\w.]*)\s*=\s*(0x[0-9A-Fa-f]+)", txt, re.M):
            syms.setdefault(name, int(val, 16))

    # splat's disassembly is the project's authoritative address map for everything else
    glabel = re.compile(r"^\s*glabel\s+(\S+)\s*$")
    vaddr = re.compile(r"/\* \w+ ([0-9A-Fa-f]{8})(?: [0-9A-Fa-f]{2,8})? \*/")
    for root, _dirs, files in os.walk(os.path.join(CONKER, "asm")):
        for fn in files:
            if not fn.endswith(".s"):
                continue
            pending = []
            for line in open(os.path.join(root, fn)):
                g = glabel.match(line)
                if g:
                    pending.append(g.group(1))
                    continue
                v = vaddr.search(line)
                if v and pending:
                    a = int(v.group(1), 16)
                    for nm in pending:
                        syms.setdefault(nm, a)
                    pending = []
    return syms


def main():
    if len(sys.argv) < 3:
        raise SystemExit(__doc__)
    obj, func = sys.argv[1], sys.argv[2]
    golden = sys.argv[3] if len(sys.argv) > 3 else find_golden(func)

    syms = load_symbols()
    gtxt = open(golden).read()
    gold = [int(x, 16) for x in re.findall(r"/\* \w+ \w+ ([0-9A-F]{8}) \*/", gtxt)]
    if not gold:
        raise SystemExit("no instruction words parsed out of %s" % golden)

    # -z IS LOAD-BEARING: without it objdump ELIDES runs of zero words as "...", so any function
    # containing a zero-filled block comes out SHORT and this reports a bogus length mismatch.
    # Caught on func_1001ED6C, whose migrated .rodata jump table sits in such a run.
    # The trailing sentinel handles the other end: the LAST function in .text has no blank line.
    dis = subprocess.check_output([OBJDUMP, "-dzr", obj]).decode() + "\n\n"
    m = re.search(r"^([0-9a-f]+) <%s>:\n(.*?)\n\n" % re.escape(func), dis, re.S | re.M)
    if not m:
        raise SystemExit("FAIL -- %s not found in %s (still a #pragma?)" % (func, obj))

    words, addrs, rel = [], [], {}
    for line in m.group(2).splitlines():
        mm = re.match(r"^\s*([0-9a-f]+):\t([0-9a-f]{8})", line)
        if mm:
            addrs.append(int(mm.group(1), 16))
            words.append(int(mm.group(2), 16))
            continue
        mr = re.match(r"^\s*([0-9a-f]+):\s+(R_MIPS_\w+)\s+(\S+)", line)
        if mr:
            rel[int(mr.group(1), 16)] = (mr.group(2), mr.group(3))

    # TRAILING ALIGNMENT PADDING, handled explicitly rather than tolerated.
    # splat's golden .s covers the symbol as the ORIGINAL object sized it, which for the last
    # function in a section includes the nops that pad .text to a 16-byte boundary.  Our symbol
    # stops at the code.  Trimming is only legitimate when EVERY extra word is a real nop -- if
    # any of them is an instruction, that is a genuine length mismatch and must fail.
    trimmed = 0
    if len(gold) > len(words):
        extra = gold[len(words):]
        if all(w == 0 for w in extra):
            trimmed = len(extra)
            gold = gold[:len(words)]
        else:
            raise SystemExit(
                "FAIL -- golden is %d words longer and %d of them are NOT nops (real mismatch)"
                % (len(extra), sum(1 for w in extra if w != 0)))

    if len(words) != len(gold):
        raise SystemExit("FAIL -- LENGTH MISMATCH ours=%d gold=%d" % (len(words), len(gold)))

    bad, checked, plain, pending_hi = [], 0, 0, {}
    for i, a in enumerate(addrs):
        if a not in rel:
            if words[i] != gold[i]:
                bad.append((i, a, "PLAIN word differs", words[i], gold[i]))
            plain += 1
            continue
        typ, name = rel[a]
        if name not in syms:
            # project convention: a C-defined function is named for its own vaddr
            mn = re.match(r"^func_([0-9A-F]{8})$", name)
            if mn:
                syms[name] = int(mn.group(1), 16)
        if name not in syms:
            bad.append((i, a, "symbol %s has NO KNOWN ADDRESS (fail closed)" % name,
                        words[i], gold[i]))
            continue
        sym = syms[name]
        mask = 0x03FFFFFF if typ == "R_MIPS_26" else 0xFFFF
        if (words[i] & ~mask) != (gold[i] & ~mask):
            bad.append((i, a, "opcode/register bits differ", words[i], gold[i]))
        if typ == "R_MIPS_26":
            target = sym + ((words[i] & 0x03FFFFFF) << 2)
            checked += 1
            if ((target >> 2) & 0x03FFFFFF) != (gold[i] & 0x03FFFFFF):
                bad.append((i, a, "jal %s -> %08x" % (name, target),
                            (target >> 2) & 0x03FFFFFF, gold[i] & 0x03FFFFFF))
        elif typ == "R_MIPS_HI16":
            pending_hi.setdefault(name, []).append((i, words[i] & 0xFFFF))
        elif typ == "R_MIPS_LO16":
            lo = words[i] & 0xFFFF
            addend_lo = lo - 0x10000 if lo & 0x8000 else lo
            value = sym + addend_lo
            checked += 1
            if (value & 0xFFFF) != (gold[i] & 0xFFFF):
                bad.append((i, a, "lo16 %s value=%08x" % (name, value),
                            value & 0xFFFF, gold[i] & 0xFFFF))
            for (hi_i, hi_imm) in pending_hi.pop(name, []):
                v = sym + (hi_imm << 16) + addend_lo
                checked += 1
                if (((v + 0x8000) >> 16) & 0xFFFF) != (gold[hi_i] & 0xFFFF):
                    bad.append((hi_i, addrs[hi_i], "hi16 %s value=%08x" % (name, v),
                                ((v + 0x8000) >> 16) & 0xFFFF, gold[hi_i] & 0xFFFF))
        else:
            bad.append((i, a, "UNHANDLED reloc %s (fail closed)" % typ, words[i], gold[i]))

    leftover = sum(len(v) for v in pending_hi.values())
    print("golden:                   %s" % os.path.relpath(golden, REPO))
    print("instructions:             %d (golden %d)" % (len(words), len(gold)))
    if trimmed:
        print("trailing alignment nops:  %d trimmed from golden (all verified 00000000)" % trimmed)
    print("unrelocated words equal:  %d" % plain)
    print("relocated fields checked: %d" % checked)
    print("unpaired HI16 left over:  %d" % leftover)
    if leftover:
        bad.append((-1, 0, "unpaired HI16 relocations remain", 0, 0))
    if bad:
        print("FAIL -- %d problem(s):" % len(bad))
        for i, a, why, w, g in bad[:30]:
            print("  idx%-4d %04x  %-46s ours=%08x gold=%08x" % (i, a, why, w, g))
        sys.exit(1)
    print("PASS -- every instruction, including every relocated field, resolves to the ROM's bytes")


if __name__ == "__main__":
    main()
