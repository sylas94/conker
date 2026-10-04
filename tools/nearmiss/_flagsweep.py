#!/usr/bin/env python3
"""Score every parked near-miss at the tree default AND at alternative OPT_FLAGS.

WHY
    func_150AD900/func_150AD930 sat at 21 and 41 with the wrong instruction COUNT for months.
    At plain -O2, with no -g3, both became length-exact and fell to 10 and 9. The reason is
    that -g3 stops IDO scheduling the final instruction into the `jr $ra` delay slot, so a
    function whose golden form fills that slot can never match at the tree default no matter
    how the C is spelled.

    This is not exotic: conker/Makefile already carries ~20 `OPT_FLAGS := -g` overrides for
    init_* TUs and an explicit note that libultra "was shipped compiled without debug info".
    Rare evidently built different translation units with different flags, so any park whose
    residue includes a length difference or a stray nop is worth one cheap re-measurement
    before another hour goes into re-spelling its C.

WHAT A HIT MEANS
    A better score at different flags is a claim about the TU's BUILD, not about the C. Acting
    on it means adding

        $(BUILD_DIR)/$(SRC_DIR)/<tu>.c.o: OPT_FLAGS := <flags>

    to conker/Makefile, which changes how EVERY function in that TU is compiled. If any
    sibling already matches at the default, that override will break it -- so gate on the full
    ROM sha1, never on the one function's score.

USAGE
    python3 tools/nearmiss/_flagsweep.py [--limit N]
"""
import io
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, "tools"))
import fastscore  # noqa: E402
sys.path.insert(0, HERE)
import _splice  # noqa: E402

ALTS = [["-O2"], ["-O1"], ["-g"], ["-O1", "-g3"]]


def main(argv):
    limit = int(argv[argv.index("--limit") + 1]) if "--limit" in argv else None
    idx = {}
    for root, _d, files in os.walk(os.path.join(REPO, "conker", "src")):
        for f in files:
            if f.endswith(".c"):
                t = io.open(os.path.join(root, f), encoding="utf-8", errors="replace").read()
                for m in re.finditer(r'GLOBAL_ASM\("asm/nonmatchings/([^/]+)/(\w+)\.s"\)', t):
                    idx[m.group(2)] = m.group(1)

    hits, done = [], 0
    for pf in sorted(f for f in os.listdir(HERE) if re.match(r"^func_[0-9A-Fa-f]+\.c$", f)):
        func = pf[:-2]
        if func not in idx:
            continue
        if limit is not None and done >= limit:
            break
        tu = idx[func]
        try:
            src = _splice.splice(tu, func, os.path.join(HERE, pf))
            sc = fastscore.Scorer(tu, func,
                                  workdir=os.path.expanduser("~/.conker_fsw/%s.%s" % (tu, func)))
        except SystemExit:
            continue
        except Exception:
            continue
        default_opt = list(sc.opt)
        base, binfo, _ = sc.score(src)
        if base is None or base >= 10 ** 6:
            continue                      # cannot build at all; not this tool's problem
        done += 1
        best, bestopt, bestinfo = base, default_opt, binfo
        for alt in ALTS:
            if alt == default_opt:
                continue
            sc.opt = list(alt)
            m, i, _ = sc.score(src)
            if m is not None and m < best:
                best, bestopt, bestinfo = m, alt, i
        sc.opt = default_opt
        if best < base:
            hits.append((base - best, base, best, tu, func, " ".join(bestopt), str(bestinfo)))
            print("HIT  %-14s %-16s %s -> %s at %-10s %s"
                  % (tu, func, base, best, " ".join(bestopt), bestinfo))
            sys.stdout.flush()

    hits.sort(reverse=True)
    print("\n=== %d parks improve at non-default flags, by gain ===" % len(hits))
    for gain, base, best, tu, func, opt, info in hits:
        print("  -%-5s %-6s -> %-6s %-14s %-16s %-10s %s" % (gain, base, best, tu, func, opt, info))
    print("\nA hit is a claim about the TU's BUILD. Adding an OPT_FLAGS override recompiles")
    print("EVERY function in that TU -- gate on the ROM sha1, not on the one score.")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
