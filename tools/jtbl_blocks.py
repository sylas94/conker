#!/usr/bin/env python3
"""Which jump-table rodata blocks can actually be migrated, and what each one costs.

WHY THIS EXISTS
    Migrating a jtbl out of asm/data/<OFF>.rodata.s and into a compiled TU is a one-line
    conker.us.yaml change, but it only LINKS if that TU re-emits the whole block, in order,
    from its own C.  So the real question is never "does this block hold a jump table" but
    "is every symbol in this block owned by functions I am about to decompile".

    The project note previously recorded 5 migratable blocks, from a single-symbol test.
    That test is too strict: a 26-symbol block is fine if all 26 belong to the one TU.
    Applying the ownership test instead finds 14.  It is also not too loose -- it rejects
    blocks a foreign-reference check would wave through, because an UNREFERENCED symbol in
    the block still has to be emitted by somebody, and nobody emits it.

A BLOCK IS CHEAP ONLY IF ALL FOUR HOLD
    1. every symbol is referenced by exactly one TU,
    2. no already-decompiled C file references it (that TU's C would have to emit it, and
       it does not -- its literals are already fixed),
    3. no symbol is referenced by nothing at all (nobody would emit it),
    4. every referencing function is still a #pragma GLOBAL_ASM (a function already
       decompiled cannot be made to re-emit the symbol).

    Rule 4 is the one that bites late: decompiling ONE function of a shared block silently
    disqualifies the block for all the others.  Migrate a block's functions together.

USAGE
    python3 tools/jtbl_blocks.py            # cheap blocks, smallest total bytes first
    python3 tools/jtbl_blocks.py --all      # every jtbl block with the reason it is blocked
"""

import collections
import glob
import io
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CONKER = os.path.join(REPO, "conker")

GLABEL = re.compile(r"^glabel\s+(\S+)", re.M)
RELOC = re.compile(r"%(?:hi|lo)\((\w+)\)")
CSYM = re.compile(r"\b(D_[0-9A-Fa-f]{6,}|jtbl_[0-9A-Fa-f]+)\b")
INSN = re.compile(r"/\*\s*\S+\s+\S+\s+[0-9A-Fa-f]{8}\s*\*/")


def rel(p):
    return os.path.relpath(p, CONKER).replace("\\", "/")


def load():
    """-> (blocks, refs, c_refs, sizes) for every jtbl-bearing rodata block."""
    blocks = {}
    for f in glob.glob(os.path.join(CONKER, "asm/data/*.rodata.s")):
        syms = GLABEL.findall(io.open(f, encoding="utf-8", errors="replace").read())
        if any(s.startswith("jtbl_") for s in syms):
            blocks[os.path.basename(f).split(".")[0]] = syms

    refs = collections.defaultdict(set)
    sizes = {}
    for f in glob.glob(os.path.join(CONKER, "asm/nonmatchings/**/*.s"), recursive=True):
        tu = os.path.basename(os.path.dirname(f))
        fn = os.path.basename(f)[:-2]
        txt = io.open(f, encoding="utf-8", errors="replace").read()
        sizes[fn] = len(INSN.findall(txt)) * 4
        for s in set(RELOC.findall(txt)):
            refs[s].add((tu, fn))

    c_refs = collections.defaultdict(set)
    for f in glob.glob(os.path.join(CONKER, "src/**/*.c"), recursive=True):
        txt = io.open(f, encoding="utf-8", errors="replace").read()
        for s in set(CSYM.findall(txt)):
            c_refs[s].add(os.path.basename(f)[:-2])

    return blocks, refs, c_refs, sizes


def classify(blocks, refs, c_refs, sizes):
    rows = []
    for blk, syms in sorted(blocks.items()):
        owners, funcs, unref, foreign = set(), set(), [], set()
        for s in syms:
            hits = refs.get(s, set())
            for tu, fn in hits:
                owners.add(tu)
                funcs.add(fn)
            foreign |= c_refs.get(s, set())
            if not hits and not c_refs.get(s):
                unref.append(s)
        gone = sorted(f for f in funcs if f not in sizes)
        reason = None
        if len(owners) > 1:
            reason = "shared by %d TUs" % len(owners)
        elif foreign:
            reason = "live C references it (%s)" % ", ".join(sorted(foreign)[:2])
        elif unref:
            reason = "%d symbol(s) referenced by nothing" % len(unref)
        elif gone:
            reason = "already decompiled: %s" % ", ".join(gone[:2])
        elif not owners:
            reason = "no references found at all"
        rows.append(dict(blk=blk, tu=sorted(owners)[0] if owners else "?",
                         syms=len(syms), funcs=sorted(funcs),
                         bytes=sum(sizes.get(f, 0) for f in funcs), reason=reason))
    return rows


def main(argv):
    show_all = "--all" in argv
    rows = classify(*load())
    cheap = [r for r in rows if r["reason"] is None]
    cheap.sort(key=lambda r: r["bytes"])

    print("jtbl rodata blocks: %d    migratable: %d    blocked: %d"
          % (len(rows), len(cheap), len(rows) - len(cheap)))
    print()
    print("%-8s %-15s %5s %6s %9s  %s"
          % ("block", "TU", "syms", "funcs", "bytes", "functions to decompile together"))
    print("-" * 110)
    for r in cheap:
        print("%-8s %-15s %5d %6d %9d  %s"
              % (r["blk"], r["tu"], r["syms"], len(r["funcs"]), r["bytes"],
                 " ".join(r["funcs"])))
    print()
    print("total bytes behind the migratable set: %d" % sum(r["bytes"] for r in cheap))

    if show_all:
        print()
        print("BLOCKED blocks and why:")
        why = collections.Counter()
        for r in rows:
            if r["reason"]:
                why[r["reason"].split(" (")[0].split(":")[0]] += 1
                print("  %-8s %-15s %s" % (r["blk"], r["tu"], r["reason"]))
        print()
        for k, v in why.most_common():
            print("  %-40s %d" % (k, v))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
