#!/usr/bin/env python3
"""Sweep sub-word LOCAL widths across every parked near-miss.

WHY
    On func_15040A78 a single declaration -- `u8 op` instead of `s32 op` -- was worth 41
    points, three instructions of length, and 8 bytes of frame. The mechanism is general and
    has nothing to do with that function: IDO gives a sub-word scalar local a MEMORY HOME,
    so it cannot win a callee-saved register and has to be stored and reloaded around every
    call. That changes register allocation, frame size and delay-slot filling together, which
    is why it shows up as a large score swing rather than one or two rows.

    A decompiler writes `u8` whenever the golden code loads with `lbu`, because the LOAD
    width is visible and the VARIABLE width is not. That guess is wrong whenever the original
    assigned a byte into an int -- which is the common C idiom for exactly this code. So the
    same misreading is expected to be spread across the whole backlog, not confined to one
    function.

WHAT IT DOES
    For every park that still has a GLOBAL_ASM pragma, score the parked C, then score it again
    with every sub-word scalar local promoted to s32, and report where that helps. Pointers,
    arrays and struct members are left alone -- only plain scalar locals are touched, because
    only they are the decompiler's free guess.

USAGE
    python3 tools/nearmiss/_widths.py [--only <func>] [--limit N]
"""
import io
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, "tools"))
import fastscore  # noqa: E402

# A plain scalar local: leading indent, sub-word type, one name, semicolon. No `*`, no `[`.
DECL = re.compile(r"^([ \t]+)(u8|s8|u16|s16)([ \t]+)([A-Za-z_]\w*)\s*;\s*$", re.M)

_pragma_index = None


def tu_for(func):
    """Which TU still carries this function's GLOBAL_ASM pragma."""
    global _pragma_index
    if _pragma_index is None:
        _pragma_index = {}
        for root, _d, files in os.walk(os.path.join(REPO, "conker", "src")):
            for f in files:
                if not f.endswith(".c"):
                    continue
                path = os.path.join(root, f)
                try:
                    txt = io.open(path, encoding="utf-8", errors="replace").read()
                except OSError:
                    continue
                for m in re.finditer(r'GLOBAL_ASM\("asm/nonmatchings/([^/]+)/(\w+)\.s"\)', txt):
                    _pragma_index[m.group(2)] = (m.group(1), path)
    return _pragma_index.get(func)


def main(argv):
    only = None
    limit = None
    if "--only" in argv:
        only = argv[argv.index("--only") + 1]
    if "--limit" in argv:
        limit = int(argv[argv.index("--limit") + 1])

    parks = sorted(f for f in os.listdir(HERE)
                   if re.match(r"^func_[0-9A-Fa-f]+\.c$", f))
    if only:
        parks = [p for p in parks if p.startswith(only)]

    done = 0
    for pf in parks:
        if limit is not None and done >= limit:
            break
        func = pf[:-2]
        hit = tu_for(func)
        if hit is None:
            continue                       # already decompiled, or no pragma
        tu, tupath = hit
        park = io.open(os.path.join(HERE, pf), encoding="utf-8", errors="replace").read()
        names = [m.group(4) for m in DECL.finditer(park)]
        if not names:
            continue
        src = io.open(tupath, encoding="utf-8", errors="replace").read()
        pragma = '#pragma GLOBAL_ASM("asm/nonmatchings/%s/%s.s")' % (tu, func)
        if pragma not in src:
            continue
        try:
            sc = fastscore.Scorer(tu, func,
                                  workdir=os.path.expanduser("~/.conker_widths/%s.%s" % (tu, func)))
        except Exception as e:
            print("%-16s SKIP (%s)" % (func, str(e)[:40]))
            continue
        base, binfo, _ = sc.score(src.replace(pragma, park))
        if base is None or base < 0:
            print("%-16s SKIP (base did not compile)" % func)
            continue
        promoted = DECL.sub(lambda m: "%ss32%s%s;" % (m.group(1), m.group(3), m.group(4)), park)
        alt, ainfo, _ = sc.score(src.replace(pragma, promoted))
        done += 1
        flag = ""
        if alt is not None and alt >= 0 and alt < base:
            flag = "  *** BETTER by %d ***" % (base - alt)
        print("%-16s %-12s base=%-6s %-22s all-s32=%-6s %-22s%s"
              % (func, tu, base, binfo, alt, ainfo, flag))
        sys.stdout.flush()
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
