#!/usr/bin/env python3
"""opt_screen.py -- screen golden .s files for the IDO OPTIMISATION LEVEL they were built at.

WHY THIS EXISTS
---------------
conker/Makefile carries a per-object OPT_FLAGS override block.  A handful of TUs shipped as
unoptimised `-g` output rather than the project default `-O2 -g3`.  A -g function is close to a
literal transcription of its C, so it is by far the cheapest thing in the backlog -- but until
now nothing screened for it, so -g targets sat in the queue indistinguishable from hard -O2 ones.
func_100210C0 (init_210C0, 1072 B) was closed last wave by ONE Makefile line after somebody
noticed by eye that its golden was -g.  This tool finds the rest by machine.

THE TELLS (all measurable from the golden .s alone, NO BUILD REQUIRED)
---------------------------------------------------------------------
At -g IDO does no register allocation: every local lives in a stack slot, is reloaded from that
slot at every single reference, and is stored back after every single assignment.  It also does
no instruction scheduling, so branch/jal delay slots are almost always `nop`, and incoming
arguments are homed into the caller's argument save area in the prologue.

  RELOAD   distinct $sp offsets that are LOADED two or more times, per 100 instructions.
           This is the strongest single feature: an -O2 function keeps a local in a register.
  DELAY    fraction of jal/branch delay slots left as `nop`.  -O2 fills them.
  ARGHOME  incoming a0..a3 stored to $sp in the prologue (before the first branch).
  SREGS    how many callee-saved $s registers the function touches.  Weak on its own (see the
           calibration table) because plenty of small -O2 leaves need none.

CALIBRATION (run --calibrate to reproduce; numbers from 2026-08-15)
------------------------------------------------------------------
Positives  = 80 functions in 19 TUs the Makefile already compiles at -g.
Negatives  = 610 functions in 163 default-flag TUs that are ALREADY DECOMPILED, i.e. proven
             byte-identical at -O2 -g3, so their golden really is -O2 output.
             (Both sets are read live from the tree, so the counts creep up as work lands.
             Re-run --calibrate rather than trusting the table below to the unit.)

  per-function rule                        TP  FN  FP   TN   TPR%   FPR%
  reload >= 8                              69  11  30  580   86.2    4.9
  delay_nop >= 40                          75   5 193  417   93.8   31.6
  no $s register used                      68  12 415  195   85.0   68.0
  reload>=8 AND delay_nop>=40  [SHIPPED]   66  14   3  607   82.5    0.5

  per-TU rule (instruction-weighted)  reload>=8 AND delay_nop>=45:
      TPR = 94.7% (18/19 known -g TUs)      FPR = 0.0% (0/163 known -O2 TUs)

All 3 per-function false positives are 20-23 instruction leaves; all 14 false negatives are
small functions with no multiply-referenced local, where -g and -O2 legitimately coincide.
That is why the TU-level verdict is the one to act on: OPT_FLAGS is a PER-OBJECT setting.

RESULT OF THE FIRST RUN OVER THE WHOLE BACKLOG (2026-08-15) -- A NEGATIVE
------------------------------------------------------------------------
1727 live pragmas, 1698 of them non-handwritten, across 374 TUs.  10 TUs pass the TU-level -g
screen and NINE OF THEM ARE ALREADY DECLARED -g IN THE MAKEFILE.  The tenth is pfschecker2,
which already carries an -O1 override.  Laid out by address, the -g block is CONTIGUOUS from
init_128D0 (0x128D0) to init_22460 (0x22460) with no gaps left -- the bracketed-TU hole that
func_100210C0 fell into has been filled and there is not another one.
**So there is no undiscovered -g TU. The remaining value is the 37 functions still stubbed
INSIDE the already-declared -g TUs**, which the size-first picker has never prioritised; they
are the cheapest functions on the board and need no Makefile change at all.

A TU that already has ONE matched function has SETTLED flags: that function was byte-verified
at the TU's current OPT_FLAGS, and OPT_FLAGS is per object, so the flags cannot be changed
without breaking it.  --population uses this to separate "still arguable" from "decided".

USAGE
-----
  python3 tools/opt_screen.py --calibrate      # true/false positive rate on known -g / known -O2
  python3 tools/opt_screen.py --population     # per-TU verdict over every live GLOBAL_ASM pragma
  python3 tools/opt_screen.py --tu game_221290 # per-function detail for one TU
  python3 tools/opt_screen.py --dump out.tsv   # every function, every feature

Run from anywhere; paths are resolved relative to this file.
"""
import os, re, sys, glob, argparse
from collections import defaultdict

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
CONKER = os.path.join(ROOT, "conker")
SRC = os.path.join(CONKER, "src")
NM = os.path.join(CONKER, "asm", "nonmatchings")
MAKEFILE = os.path.join(CONKER, "Makefile")

# ---------------------------------------------------------------- asm parsing
INSN_RE = re.compile(r'^\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s*\*/\s+(\S+)\s*(.*)$')
LABEL_RE = re.compile(r'^\s*(\.?L?[A-Za-z_.$][\w.$]*):\s*$')

LOADS = {"lw", "lh", "lhu", "lb", "lbu", "lwc1", "ldc1", "ld", "lwu", "lwl", "lwr"}
STORES = {"sw", "sh", "sb", "swc1", "sdc1", "sd", "swl", "swr"}
BRANCHES_RE = re.compile(r'^(b|beq|bne|blez|bgtz|bltz|bgez|beqz|bnez|bgezal|bltzal|j|jal|jr|jalr|bc1t|bc1f|beql|bnel|blezl|bgtzl|bltzl|bgezl)$')
CALLS_RE = re.compile(r'^(jal|jalr)$')
SP_OFF_RE = re.compile(r'(-?0x[0-9A-Fa-f]+|-?\d+)\(\$sp\)')
TEMPS = re.compile(r'\$(t[0-9]|s[0-7]|v[01]|a[0-3])\b')


def parse(text):
    """-> list of (mnemonic, operands, is_delay_slot)"""
    ins = []
    for ln in text.split("\n"):
        m = INSN_RE.match(ln)
        if m:
            ins.append([m.group(1), m.group(2).strip(), False])
    for i in range(len(ins) - 1):
        if BRANCHES_RE.match(ins[i][0]):
            ins[i + 1][2] = True
    return ins


def features(text):
    ins = parse(text)
    n = len(ins)
    if n == 0:
        return None
    f = {"nins": n}

    # ---- RELOAD: sp offsets loaded 2+ times
    loadcnt = defaultdict(int)
    sp_loads = 0
    for mn, ops, _ in ins:
        if mn in LOADS:
            m = SP_OFF_RE.search(ops)
            if m:
                loadcnt[m.group(1)] += 1
                sp_loads += 1
    redundant = sum(c - 1 for c in loadcnt.values() if c >= 2)
    f["sp_loads"] = sp_loads
    f["reload_slots"] = sum(1 for c in loadcnt.values() if c >= 2)
    f["reload"] = 100.0 * redundant / n

    # ---- DELAY: nop-filled delay slots
    slots = [i for i in ins if i[2]]
    f["ndelay"] = len(slots)
    f["delay_nop"] = (100.0 * sum(1 for i in slots if i[0] == "nop") / len(slots)) if slots else 0.0
    calls = [i for i, (mn, _, _) in enumerate(ins) if CALLS_RE.match(mn)]
    call_nops = sum(1 for i in calls if i + 1 < n and ins[i + 1][0] == "nop")
    f["ncall"] = len(calls)
    f["call_nop"] = (100.0 * call_nops / len(calls)) if calls else 0.0

    # ---- ARGHOME: a0..a3 stored to sp before the first branch
    homed = set()
    for mn, ops, _ in ins:
        if BRANCHES_RE.match(mn):
            break
        if mn == "sw" or mn == "swc1":
            m = re.match(r'\$(a[0-3]|f1[24])\s*,\s*(-?0x[0-9A-Fa-f]+|-?\d+)\(\$sp\)', ops)
            if m:
                homed.add(m.group(1))
    f["arghome"] = len(homed)

    # ---- CALLEESAVE: at -g every local lives on the stack, so IDO never needs an $s
    # register to carry a value across a call -- the prologue saves $ra and nothing else.
    # At -O2 locals live in $s0..$s7 and are saved.  This is the cleanest single tell.
    sregs = set(re.findall(r'\$(s[0-7])\b', text))
    f["sregs"] = len(sregs)
    f["uses_s"] = 1 if sregs else 0

    # ---- raw counters so a TU-level (weighted) verdict can be recomputed
    f["_redundant"] = redundant
    f["_delayslots"] = len(slots)
    f["_delaynops"] = sum(1 for i in slots if i[0] == "nop")
    return f


# ---- calibrated thresholds; see --calibrate output in the tool's header comment.
G_RELOAD = 8.0      # redundant $sp reloads per 100 instructions
G_DELAY = 40.0      # % of delay slots left as nop


def is_g(f):
    """Function-level verdict.  Two features must agree: no register allocation (RELOAD)
    AND no instruction scheduling (DELAY).  Either alone has ~5%/20% false-positive rates."""
    return f["reload"] >= G_RELOAD and f["delay_nop"] >= G_DELAY

# ---------------------------------------------------------------- repo model
def tu_of_sfile(path):
    return os.path.basename(os.path.dirname(path))


def src_for_tu():
    """tu name -> src path relative to conker/ (e.g. src/libultra/audio/init_15550.c)"""
    out = {}
    for c in glob.glob(os.path.join(SRC, "**", "*.c"), recursive=True):
        out.setdefault(os.path.basename(c)[:-2], os.path.relpath(c, CONKER).replace("\\", "/"))
    return out


def stubbed_funcs():
    """func name -> tu, for every LIVE #pragma GLOBAL_ASM."""
    out = {}
    for c in glob.glob(os.path.join(SRC, "**", "*.c"), recursive=True):
        try:
            txt = open(c, errors="ignore").read()
        except OSError:
            continue
        for m in re.finditer(r'^\s*#pragma\s+GLOBAL_ASM\("([^"]+)"\)', txt, re.M):
            p = m.group(1)
            out[os.path.basename(p)[:-2]] = os.path.basename(os.path.dirname(p))
    return out


def makefile_overrides():
    """src-relative object stem -> OPT_FLAGS, from the Makefile override block."""
    exact, wild = {}, []
    for ln in open(MAKEFILE, errors="ignore"):
        m = re.match(r'^\$\(BUILD_DIR\)/\$\(SRC_DIR\)/(\S+)\.o:\s*OPT_FLAGS\s*:=\s*(.+?)\s*$', ln)
        if not m:
            continue
        pat, flags = m.group(1), m.group(2)
        if "%" in pat:
            wild.append((pat.replace("%", ""), flags))
        else:
            exact["src/" + pat] = flags
    return exact, wild


def flags_for(srcpath, exact, wild):
    if srcpath in exact:
        return exact[srcpath]
    for prefix, flags in wild:
        if srcpath.startswith("src/" + prefix):
            return flags
    return "-O2 -g3"


def load_all():
    """-> list of dicts, one per golden .s under asm/nonmatchings"""
    srcmap = src_for_tu()
    stub = stubbed_funcs()
    exact, wild = makefile_overrides()
    rows = []
    for dirpath, _, files in os.walk(NM):
        for fn in files:
            if not fn.endswith(".s"):
                continue
            p = os.path.join(dirpath, fn)
            tu = tu_of_sfile(p)
            func = fn[:-2]
            try:
                txt = open(p, errors="ignore").read()
            except OSError:
                continue
            f = features(txt)
            if f is None:
                continue
            sp = srcmap.get(tu)
            f.update(func=func, tu=tu, src=sp,
                     flags=(flags_for(sp, exact, wild) if sp else "?"),
                     stubbed=(stub.get(func) is not None),
                     handwritten=("Handwritten function" in txt or "handwritten instruction" in txt))
            rows.append(f)
    return rows


# ---------------------------------------------------------------- commands
def tu_agg(fs):
    """TU-level (instruction-weighted) features.  OPT_FLAGS is a PER-OBJECT setting, so this,
    not the per-function verdict, is the number that decides whether to add a Makefile line."""
    nins = sum(r["nins"] for r in fs)
    ds = sum(r["_delayslots"] for r in fs)
    return {
        "nfunc": len(fs), "nins": nins,
        "reload": 100.0 * sum(r["_redundant"] for r in fs) / nins if nins else 0.0,
        "delay_nop": 100.0 * sum(r["_delaynops"] for r in fs) / ds if ds else 0.0,
        "sfrac": 100.0 * sum(1 for r in fs if r["uses_s"]) / len(fs),
        "gfrac": 100.0 * sum(1 for r in fs if is_g(r)) / len(fs),
    }


def cmd_calibrate(rows):
    pos = [r for r in rows if r["flags"] == "-g" and not r["handwritten"]]
    neg = [r for r in rows if r["flags"].startswith("-O2") and not r["handwritten"] and not r["stubbed"]]
    print("=" * 78)
    print("CALIBRATION SET")
    print("  known -g   (Makefile OPT_FLAGS := -g)            : %d functions in %d TUs"
          % (len(pos), len({r['tu'] for r in pos})))
    print("  known -O2  (default flags AND already decompiled): %d functions in %d TUs"
          % (len(neg), len({r['tu'] for r in neg})))
    print("  (the -O2 set is restricted to ALREADY-MATCHED functions: those are PROVEN to")
    print("   compile byte-identically at -O2 -g3, so their golden really is -O2 output.)")
    print()
    print("FEATURE SEPARATION")
    print("  %-10s %-4s %9s %9s %9s %9s" % ("feature", "set", "median", "mean", "min", "max"))
    for k in ("reload", "delay_nop", "arghome", "sregs", "nins"):
        for name, s in (("-g", pos), ("-O2", neg)):
            v = sorted(x[k] for x in s)
            print("  %-10s %-4s %9.2f %9.2f %9.2f %9.2f"
                  % (k, name, v[len(v) // 2], sum(v) / len(v), v[0], v[-1]))
    print()

    def rate(pred):
        tp = sum(1 for r in pos if pred(r)); fp = sum(1 for r in neg if pred(r))
        return tp, len(pos) - tp, fp, len(neg) - fp

    print("PER-FUNCTION RULES")
    print("  %-40s %5s %5s %5s %5s %7s %7s" % ("rule", "TP", "FN", "FP", "TN", "TPR%", "FPR%"))
    for label, pred in [
        ("reload >= 8", lambda r: r["reload"] >= 8),
        ("delay_nop >= 40", lambda r: r["delay_nop"] >= 40),
        ("no $s register used", lambda r: not r["uses_s"]),
        ("reload>=8 AND delay_nop>=40  [SHIPPED]", is_g),
        ("reload>=8 AND delay>=40 AND no-$s", lambda r: is_g(r) and not r["uses_s"]),
    ]:
        tp, fn_, fp, tn = rate(pred)
        print("  %-40s %5d %5d %5d %5d %7.1f %7.1f"
              % (label, tp, fn_, fp, tn, 100.0 * tp / len(pos), 100.0 * fp / len(neg)))
    print()
    print("  FALSE POSITIVES of the shipped rule (matched -O2 functions it calls -g):")
    fps = sorted((r for r in neg if is_g(r)), key=lambda r: -r["reload"])
    for r in fps:
        print("    %-20s %-16s reload=%6.2f delay_nop=%5.1f nins=%4d"
              % (r["func"], r["tu"], r["reload"], r["delay_nop"], r["nins"]))
    print("  FALSE NEGATIVES of the shipped rule (known -g functions it calls -O2):")
    fns = sorted((r for r in pos if not is_g(r)), key=lambda r: r["nins"])
    for r in fns:
        print("    %-20s %-16s reload=%6.2f delay_nop=%5.1f nins=%4d"
              % (r["func"], r["tu"], r["reload"], r["delay_nop"], r["nins"]))
    print()

    # ------------------------------------------------------------- TU level
    print("=" * 78)
    print("PER-TU VERDICT (the unit that actually matters -- OPT_FLAGS is per object)")
    bytu = defaultdict(list)
    for r in rows:
        if not r["handwritten"]:
            bytu[r["tu"]].append(r)
    gtus = sorted({r["tu"] for r in pos})
    otus = sorted({r["tu"] for r in neg})
    print("\n  KNOWN -g TUs (%d):" % len(gtus))
    print("  %-24s %5s %6s %8s %9s %7s %7s" % ("TU", "func", "insn", "reload", "delay_nop", "%no-$s", "%g-func"))
    for tu in gtus:
        a = tu_agg(bytu[tu])
        print("  %-24s %5d %6d %8.2f %9.1f %7.1f %7.1f"
              % (tu, a["nfunc"], a["nins"], a["reload"], a["delay_nop"], 100 - a["sfrac"], a["gfrac"]))
    print("\n  KNOWN -O2 TUs -- worst 20 by TU-level reload (out of %d):" % len(otus))
    aggs = sorted(((tu_agg([r for r in bytu[tu] if not r["stubbed"]]), tu) for tu in otus),
                  key=lambda t: -t[0]["reload"])
    print("  %-24s %5s %6s %8s %9s %7s %7s" % ("TU", "func", "insn", "reload", "delay_nop", "%no-$s", "%g-func"))
    for a, tu in aggs[:20]:
        print("  %-24s %5d %6d %8.2f %9.1f %7.1f %7.1f"
              % (tu, a["nfunc"], a["nins"], a["reload"], a["delay_nop"], 100 - a["sfrac"], a["gfrac"]))
    print()
    tp = sum(1 for tu in gtus if tu_agg(bytu[tu])["reload"] >= TU_RELOAD
             and tu_agg(bytu[tu])["delay_nop"] >= TU_DELAY)
    fp = sum(1 for a, tu in aggs if a["reload"] >= TU_RELOAD and a["delay_nop"] >= TU_DELAY)
    print("  TU RULE  reload>=%.0f AND delay_nop>=%.0f :  TPR=%.1f%% (%d/%d)   FPR=%.1f%% (%d/%d)"
          % (TU_RELOAD, TU_DELAY, 100.0 * tp / len(gtus), tp, len(gtus),
             100.0 * fp / len(otus), fp, len(otus)))


TU_RELOAD = 8.0
TU_DELAY = 45.0


def cmd_population(rows, show_all=False):
    stub = [r for r in rows if r["stubbed"] and not r["handwritten"]]
    hw = [r for r in rows if r["stubbed"] and r["handwritten"]]
    print("live GLOBAL_ASM pragmas with a golden .s: %d  (+%d handwritten, excluded)"
          % (len(stub), len(hw)))
    tot_g = sum(1 for r in stub if is_g(r))
    print("stubbed functions passing the PER-FUNCTION -g screen: %d (%.1f%%)"
          % (tot_g, 100.0 * tot_g / len(stub)))
    print()

    allbytu = defaultdict(list)
    for r in rows:
        if not r["handwritten"]:
            allbytu[r["tu"]].append(r)

    # A TU that already has a MATCHED function is SETTLED: that function was byte-verified at
    # the TU's current OPT_FLAGS, and OPT_FLAGS is per object, so its flags cannot be changed.
    # Only 100%-stubbed TUs are candidates for a new override line.
    out = []
    for tu, fs in allbytu.items():
        sf = [r for r in fs if r["stubbed"]]
        if not sf:
            continue
        a = tu_agg(fs)
        matched = len(fs) - len(sf)
        settled = matched > 0
        out.append((a["reload"], a, tu, fs[0]["flags"], fs[0]["src"], len(sf), matched, settled))
    out.sort(key=lambda t: -t[0])

    open_tus = [t for t in out if not t[7]]
    hits = [t for t in out if t[1]["reload"] >= TU_RELOAD and t[1]["delay_nop"] >= TU_DELAY]
    open_hits = [t for t in hits if not t[7]]
    print("TUs with live pragmas: %d   (%d already have >=1 matched function => flags SETTLED,"
          % (len(out), len(out) - len(open_tus)))
    print("                        %d are 100%% stubbed => an OPT_FLAGS line is still possible)"
          % len(open_tus))
    print("TUs passing the TU-level -g screen (reload>=%.0f AND delay_nop>=%.0f): %d"
          % (TU_RELOAD, TU_DELAY, len(hits)))
    print("  ... of which are NOT already declared -g in the Makefile: %d"
          % sum(1 for t in hits if t[3] != "-g"))
    print()
    print("%-28s %-8s %5s %5s %8s %9s %6s  %s"
          % ("TU", "FLAGS", "stub", "done", "reload", "delay_nop", "verdict", "SRC"))
    for rl, a, tu, flags, src, nstub, nmatch, settled in out:
        v = "-g" if (a["reload"] >= TU_RELOAD and a["delay_nop"] >= TU_DELAY) else "-O2"
        if not show_all and v != "-g":
            continue
        print("%-28s %-8s %5d %5d %8.2f %9.1f %6s  %s"
              % (tu, flags, nstub, nmatch, a["reload"], a["delay_nop"], v, src))
    print()
    print("ACTIONABLE (screen says -g, Makefile does not, TU is 100%% stubbed):")
    act = [t for t in open_hits if t[3] != "-g"]
    if not act:
        print("  NONE.")
    for rl, a, tu, flags, src, nstub, nmatch, settled in act:
        print("  %-28s %-8s stub=%d reload=%.2f delay_nop=%.1f  %s"
              % (tu, flags, nstub, a["reload"], a["delay_nop"], src))
    print()
    print("NEAR MISSES (one of the two TU features passes; inspect by hand):")
    for rl, a, tu, flags, src, nstub, nmatch, settled in out:
        if settled or flags == "-g":
            continue
        one = (a["reload"] >= TU_RELOAD) != (a["delay_nop"] >= TU_DELAY)
        if one:
            print("  %-28s %-8s stub=%d reload=%6.2f delay_nop=%5.1f  %s"
                  % (tu, flags, nstub, a["reload"], a["delay_nop"], src))


def cmd_tu(rows, tu):
    fs = [r for r in rows if r["tu"] == tu]
    fs.sort(key=lambda r: -r["reload"])
    print("%-20s %6s %5s %6s %6s %4s %4s %s"
          % ("FUNC", "reload", "nins", "dlynop", "clnop", "argh", "stub", "verdict"))
    for r in fs:
        print("%-20s %6.2f %5d %6.1f %6.1f %4d %4s %s"
              % (r["func"], r["reload"], r["nins"], r["delay_nop"], r["call_nop"],
                 r["arghome"], "Y" if r["stubbed"] else ".",
                 "-g" if is_g(r) else "-O2"))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--calibrate", action="store_true")
    ap.add_argument("--population", action="store_true")
    ap.add_argument("--all", action="store_true", help="with --population, show every TU")
    ap.add_argument("--tu")
    ap.add_argument("--dump")
    a = ap.parse_args()
    rows = load_all()
    if a.calibrate:
        cmd_calibrate(rows)
    if a.population:
        cmd_population(rows, a.all)
    if a.tu:
        cmd_tu(rows, a.tu)
    if a.dump:
        keys = ["func", "tu", "src", "flags", "stubbed", "handwritten", "nins", "reload",
                "reload_slots", "sp_loads", "delay_nop", "call_nop", "ncall", "arghome"]
        with open(a.dump, "w") as fh:
            fh.write("\t".join(keys) + "\n")
            for r in sorted(rows, key=lambda r: -r["reload"]):
                fh.write("\t".join(str(r.get(k, "")) for k in keys) + "\n")
        print("wrote", a.dump, len(rows), "rows")
    if not (a.calibrate or a.population or a.tu or a.dump):
        ap.print_help()


if __name__ == "__main__":
    main()
