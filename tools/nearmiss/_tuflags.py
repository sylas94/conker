#!/usr/bin/env python3
"""Find TUs where a per-TU OPT_FLAGS override is RISK-FREE, and sweep them for a flag that
zeroes every function at once.

WHY THIS SHAPE
    Changing `$(BUILD_DIR)/$(SRC_DIR)/<tu>.c.o: OPT_FLAGS` recompiles EVERY function in that
    TU. If a sibling already matches at the tree default, the override breaks it -- so most
    TUs cannot be swept this way without a full ROM gate per attempt.

    But a TU in which every remaining function is still a `#pragma GLOBAL_ASM` has NOTHING to
    break: a pragma'd function is spliced from golden asm and is unaffected by OPT_FLAGS. Such
    a TU can be re-flagged freely, and if some flag set matches all of its functions at once,
    the whole TU ships in one step.

    That is exactly what game_21D420 was -- libultra sprintf plus its proout helper, two
    pragmas, both scoring 17 and 16 at the tree default and BOTH ZERO at plain -O2. Its park
    had recorded the required override and it had simply never been applied.

WHAT IT REPORTS
    For each all-pragma TU whose functions all have parked C, the score of every function at
    every usable flag set, and the flag set with the best total.

    Only -O2 -g3, -O2, -O1, -g and -O0 are usable in this tree; -g0/-g1/-g2/-O3/-O1 -g3 fail
    before producing an object, so they are not swept and must never be reported as "worse".

USAGE
    python3 tools/nearmiss/_tuflags.py [--limit N]
"""
import io
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, "tools"))
import fastscore  # noqa: E402

OPTS = [["-O2", "-g3"], ["-O2"], ["-O1"], ["-g"], ["-O0"]]
PRAGMA = re.compile(r'#pragma GLOBAL_ASM\("asm/nonmatchings/([^/]+)/(\w+)\.s"\)')
# A definition at column 0 that is not a pragma line: rough, but enough to tell "all pragmas"
# from "has live C".
DEFN = re.compile(r"^[A-Za-z_][\w \*]*\b\w+\s*\([^;]*\)\s*\{", re.M)


def main(argv):
    limit = int(argv[argv.index("--limit") + 1]) if "--limit" in argv else None
    cands = []
    for root, _d, files in os.walk(os.path.join(REPO, "conker", "src")):
        for f in sorted(files):
            if not f.endswith(".c"):
                continue
            path = os.path.join(root, f)
            txt = io.open(path, encoding="utf-8", errors="replace").read()
            funcs = [m.group(2) for m in PRAGMA.finditer(txt)]
            if not funcs:
                continue
            if DEFN.search(txt):
                continue                       # has live C -- an override could break it
            tu = f[:-2]
            parks = [fn for fn in funcs
                     if os.path.exists(os.path.join(HERE, fn + ".c"))]
            if parks and len(parks) == len(funcs):
                cands.append((tu, funcs))

    print("all-pragma TUs with a park for EVERY function: %d\n" % len(cands))
    wins = []
    for i, (tu, funcs) in enumerate(cands):
        if limit is not None and i >= limit:
            break
        # every park in the TU is a candidate whole-TU source; use the first that builds
        best = None
        for src_fn in funcs:
            park = io.open(os.path.join(HERE, src_fn + ".c"), encoding="utf-8",
                           errors="replace").read()
            if "#include" not in park:
                continue
            src = park[park.index("#include"):]
            totals = []
            for opt in OPTS:
                tot, detail, ok = 0, [], True
                for fn in funcs:
                    try:
                        sc = fastscore.Scorer(tu, fn, workdir=os.path.expanduser(
                            "~/.conker_tuf/%s.%s" % (tu, fn)))
                    except SystemExit:
                        ok = False
                        break
                    sc.opt = list(opt)
                    m, info, _ = sc.score(src)
                    if m is None or m >= 10 ** 6:
                        ok = False
                        break
                    tot += m
                    detail.append("%s=%s" % (fn, m))
                if ok:
                    totals.append((tot, " ".join(opt), detail))
            if totals:
                totals.sort()
                best = (src_fn, totals)
                break
        if not best:
            continue
        src_fn, totals = best
        tot, opt, detail = totals[0]
        dflt = [t for t in totals if t[1] == "-O2 -g3"]
        dtot = dflt[0][0] if dflt else None
        flag = ""
        if tot == 0:
            flag = "   *** WHOLE TU MATCHES at %s ***" % opt
        elif dtot is not None and tot < dtot:
            flag = "   (better than default %s)" % dtot
        print("%-16s best=%-6s at %-8s  %s%s" % (tu, tot, opt, " ".join(detail), flag))
        sys.stdout.flush()
        if tot == 0 or (dtot is not None and tot < dtot):
            wins.append((tot, tu, opt, detail, dtot))

    print("\n=== ACTIONABLE ===")
    for tot, tu, opt, detail, dtot in sorted(wins):
        print("  %-16s %s -> %s at %-8s  %s" % (tu, dtot, tot, opt, " ".join(detail)))
    print("\nGate every override on the full ROM sha1 before believing it.")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
