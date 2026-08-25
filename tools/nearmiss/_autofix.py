#!/usr/bin/env python3
"""Repair the SPLICE of parks that no longer compile, and report what they actually score.

WHY
    Half the parked near-misses (99 of 207) cannot be built. Grouped by real compiler message,
    76 of those are a single mechanical cause: the park carries a declaration or a whole
    sibling definition that its TU has since gained, so splicing produces a duplicate. Those
    parks are not wrong about the function -- they are stale about their surroundings, and
    their scores have been invisible the whole time.

WHAT IT DOES
    Splice, compile, read the first error, delete exactly the offending construct, repeat.
    A `redeclaration` loses the one declaration statement; a `redefinition` loses the whole
    duplicate function body (brace-matched). It stops as soon as the file compiles.

    It edits the SPLICED TEXT, never the park. The parks stay as written -- they are the
    record of how each function was reasoned about, and rewriting them to make a compiler
    happy would destroy that. What this produces is a measurement.

CAUTION -- READ THIS BEFORE BELIEVING ANY SCORE THIS PRODUCES
    A deleted declaration is not always a harmless duplicate. Several parks deliberately
    SHADOW a wrong declaration in variables.h, using a #define / #undef pair, because the
    header is inaccurate about the symbol's type. func_15010880 is the worked example:
    variables.h says `struct178 D_800D3098[73]`, the symbol actually holds a POINTER, and the
    park re-declares it `extern struct178 *D_800D3098;` on purpose. Deleting that shadow turns
    `&D_800D3098[72]` from a pointer load into an address computation -- a different program.
    It scored 16 that way against the park's honest 210, so the repair looked like a large win
    and was really a semantic change.

    Therefore: this tool reports exactly what it deleted for every park, and a score whose
    deletion list contains anything other than a plain duplicate must be re-derived by hand
    before it is believed. Declaration ORDER is not free under IDO either, so even a genuine
    duplicate removal only says the park is worth re-opening -- never that it is correct.

USAGE
    python3 tools/nearmiss/_autofix.py [--only func_X] [--out repaired.tsv]
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

MAXPASS = 60


def drop_declaration(lines, n):
    """Remove the declaration statement containing 1-based line n.

    A reported "redeclaration" can point at a DEFINITION line. Walking forward to the first
    `;` then swallows the whole function body and leaves a fragment behind, which the compiler
    reports as "Empty declaration specifiers" -- an error that looks nothing like the one that
    caused it. Decide which construct this is the same way the permuter harness has to:
    whichever of `{` or `;` appears first.
    """
    i = n - 1
    if i < 0 or i >= len(lines):
        return None
    rest = "\n".join(lines[i:])
    brace, semi = rest.find("{"), rest.find(";")
    if brace != -1 and (semi == -1 or brace < semi):
        return drop_definition(lines, n)
    j = i
    while j < len(lines) and ";" not in lines[j]:
        j += 1
    if j >= len(lines):
        return None
    return lines[:i] + lines[j + 1:]


def drop_definition(lines, n):
    """Remove the whole brace-matched function definition containing 1-based line n."""
    i = n - 1
    # Back up to the start of this definition: the nearest line at column 0 that opens a
    # declarator. Scanning past that would delete a preceding, innocent function.
    while i > 0 and not re.match(r"^\S.*\(", lines[i]):
        i -= 1
    text = "\n".join(lines)
    start = sum(len(l) + 1 for l in lines[:i])
    b = text.find("{", start)
    if b == -1:
        return None
    depth = 0
    for k in range(b, len(text)):
        if text[k] == "{":
            depth += 1
        elif text[k] == "}":
            depth -= 1
            if depth == 0:
                head = text[:start]
                tail = text[k + 1:]
                return (head + tail).split("\n")
    return None


def suspicious(text, n):
    """Is the declaration at 1-based line n a DELIBERATE shadow rather than a duplicate?

    A park that works around a wrong variables.h declaration brackets its own with
    #define / #undef. Deleting that is a semantic change, not a cleanup, so it has to be
    surfaced rather than counted as a repair.
    """
    lines = text.split("\n")
    lo, hi = max(0, n - 12), min(len(lines), n + 3)
    window = "\n".join(lines[lo:hi])
    return "#undef" in window or "#define" in window


def repair(tu, func, park_path):
    text = _splice.splice(tu, func, park_path)
    sc = fastscore.Scorer(tu, func, workdir=os.path.expanduser("~/.conker_fix/%s.%s" % (tu, func)))
    removed = []
    for _ in range(MAXPASS):
        mism, info, _rows = sc.score(text)
        if mism is not None and mism < 10 ** 6:
            return mism, info, text, None, removed
        s = str(info)
        m = re.search(r"line (\d+): (redeclaration|redefinition) of '([^']*)'", s)
        if not m:
            return None, s, text, "unhandled: " + s[:70], removed
        n, kind, ident = int(m.group(1)), m.group(2), m.group(3)
        removed.append(ident + ("!" if suspicious(text, n) else ""))
        if ident == func:
            # NOT a stale duplicate. The park's definition disagrees with the prototype the
            # tree already has for this very function -- i.e. a HEADER BUG, the same class as
            # func_150408CC (declared void, actually returns s32; fixing it was byte-neutral
            # and ROM-gated). Deleting either side would hide it, so report and stop.
            return None, s, text, "PROTOTYPE MISMATCH on %s -- reconcile functions.h" % func, removed
        lines = text.split("\n")
        new = drop_declaration(lines, n) if kind == "redeclaration" else drop_definition(lines, n)
        if new is None:
            return None, s, text, "could not remove %s at line %d" % (kind, n), removed
        text = "\n".join(new)
    return None, "gave up after %d passes" % MAXPASS, text, "too many duplicates", removed


def main(argv):
    only = argv[argv.index("--only") + 1] if "--only" in argv else None
    out = argv[argv.index("--out") + 1] if "--out" in argv else None
    emit = argv[argv.index("--emit") + 1] if "--emit" in argv else None
    idx = {}
    for root, _d, files in os.walk(os.path.join(REPO, "conker", "src")):
        for f in files:
            if f.endswith(".c"):
                p = os.path.join(root, f)
                t = io.open(p, encoding="utf-8", errors="replace").read()
                for m in re.finditer(r'GLOBAL_ASM\("asm/nonmatchings/([^/]+)/(\w+)\.s"\)', t):
                    idx[m.group(2)] = m.group(1)
    results = []
    protos = []
    for pf in sorted(f for f in os.listdir(HERE) if re.match(r"^func_[0-9A-Fa-f]+\.c$", f)):
        func = pf[:-2]
        if func not in idx or (only and func != only):
            continue
        tu = idx[func]
        try:
            mism, info, _text, err, removed = repair(tu, func, os.path.join(HERE, pf))
            if emit and mism is not None:
                io.open(os.path.join(emit, func + ".c"), "w", encoding="utf-8",
                        newline="\n").write(_text)
        except Exception as e:
            mism, info, err, removed = None, str(e)[:70], "exception", []
        if mism is None:
            if err and err.startswith("PROTOTYPE MISMATCH"):
                protos.append((tu, func))
                print("%-8s %-14s %-16s %s" % ("PROTO", tu, func, err))
                sys.stdout.flush()
            continue
        risky = any(r.endswith("!") for r in removed)
        note = ""
        if removed:
            note = ("  *** SEMANTIC RISK -- deleted a deliberate shadow: %s ***"
                    if risky else "  deleted: %s") % ",".join(removed)
        results.append((mism, tu, func, str(info) + note))
        print("%-8s %-14s %-16s %s" % (mism, tu, func, info))
        sys.stdout.flush()
    results.sort()
    if out:
        io.open(out, "w", encoding="utf-8", newline="\n").write(
            "score\ttu\tfunc\tinfo\n" + "".join("%s\t%s\t%s\t%s\n" % r for r in results))
    print("\n=== REPAIRED, ranked (top 25) ===")
    for r in results[:25]:
        print("%-8s %-14s %-16s %s" % r)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
