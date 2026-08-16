#!/usr/bin/env python3
"""Un-stubbed expansion: flip pure-asm game segments to `c` so the matching
pipeline can see their ~3458 functions. MECHANICAL + ROM-sha1-gated, so it can
never corrupt the matching baseline.

WHY IT'S SAFE
-------------
1. splat only CREATES a .c if it doesn't exist (c.py:226), so converting a new
   segment never clobbers an already-matched file.
2. A freshly-converted segment is all GLOBAL_ASM stubs => byte-identical to the
   original ROM. So after convert+extract+build the inner sha1 (842e3d34…) and
   outer sha1 (4cbadd3c…) MUST still match. We gate on that: any conversion that
   breaks the sha1 (mis-associated rodata, jump tables, alignment) is reverted.
3. Stubbing a jtbl function is fine — the jtbl problem only bites when you MATCH
   it (C emits a local table). Stubs keep the asm inline, so they link + match.

FLOW (run from ~/conker; NOT while the orchestrator is building — it does full
builds + git):
    stub_expand.py expand <N>
      pick N unnamed `[0xNNN, asm]` game subsegments (smallest spans first),
      flip each to `[0xNNN, c, game_NNN]`, `make -C conker extract`, full build,
      verify both sha1s. On success: commit yaml + new stub src/game_NNN.c.
      On failure: bisect (revert half, re-verify) to find the breaker(s), leave
      those as `asm` (logged for rodata/jtbl follow-up), keep the good ones.

VALIDATION NOTE: run the FIRST expansion with N=1 and a clean git tree so the
auto-revert path is proven before batching. select_chunk.py picks up the new
game_NNN stubs automatically after you regenerate /tmp/game_ranked2.txt.
"""
import json, os, re, subprocess, sys

REPO = os.path.expanduser("~/conker")
INNER = os.path.join(REPO, "conker")
YAML = os.path.join(INNER, "conker.us.yaml")
INNER_SHA = "842e3d348e3c8ae0039e2ab367ad492f9b5266d8"
OUTER_SHA = "4cbadd3c4e0729dec46af64ad018050eada4f47a"
ASM_LINE = re.compile(r"^(\s+- \[)(0x[0-9A-Fa-f]+)(, asm\])\s*$")

def sh(cmd, cwd=REPO):
    return subprocess.run(cmd, shell=True, cwd=cwd, capture_output=True, text=True)

def find_convertible():
    """Unnamed `[0xNNN, asm]` lines (offset, line-index, span-to-next-segment)."""
    lines = open(YAML).read().splitlines()
    segs = []
    for i, ln in enumerate(lines):
        m = ASM_LINE.match(ln)
        if m:
            segs.append((int(m.group(2), 16), i))
    # span = distance to the next subsegment offset (proxy for # of functions)
    out = []
    offs = sorted(o for o, _ in segs)
    nxt = {offs[k]: offs[k + 1] for k in range(len(offs) - 1)}
    for off, i in segs:
        span = nxt.get(off, off + 0x1000) - off
        out.append({"off": off, "line": i, "span": span})
    return lines, out

def convert(lines, picks):
    """Return new yaml text with each pick flipped asm -> c, named game_<hexoff>."""
    out = list(lines)
    for p in picks:
        name = f"game_{p['off']:X}"
        out[p["line"]] = f"      - [0x{p['off']:X}, c, {name}]"
    return "\n".join(out) + "\n"

def rom_ok():
    sh("make -C conker extract", cwd=REPO)
    r = sh(". .venv/bin/activate && make -C conker && make -C conker replace && make -j", cwd=REPO)
    inner = sh(f"sha1sum {INNER}/build/conker.us.bin").stdout.split()
    outer = sh(f"sha1sum {REPO}/build/conker.us.z64").stdout.split()
    return bool(inner) and inner[0] == INNER_SHA and bool(outer) and outer[0] == OUTER_SHA

def try_batch(orig_lines, picks):
    """Convert `picks`, extract+build, gate on sha1. Returns the subset that
    builds clean (recursively bisecting on failure)."""
    if not picks:
        return []
    open(YAML, "w").write(convert(orig_lines, picks))
    if rom_ok():
        return picks
    # restore + bisect
    open(YAML, "w").write("\n".join(orig_lines) + "\n")
    sh("make -C conker extract", cwd=REPO)
    if len(picks) == 1:
        print(f"  REJECT game_{picks[0]['off']:X} (rodata/jtbl/align — needs manual segment work)")
        return []
    mid = len(picks) // 2
    good = try_batch(orig_lines, picks[:mid])
    # re-read lines after the first half committed its changes
    cur = open(YAML).read().splitlines()
    good += try_batch(cur, picks[mid:])
    return good

def expand(n):
    lines, conv = find_convertible()
    conv.sort(key=lambda s: s["span"])           # smallest segments first
    picks = conv[:n]
    print(f"converting {len(picks)} segments: {[hex(p['off']) for p in picks]}")
    good = try_batch(lines, picks)
    if good:
        # refresh expected/ so object-diff (iter_match) works for the new stub
        # files — the current build objects ARE the correct target bytes.
        #
        # MIRROR, don't merge. `cp -r` can add and overwrite but never removes, so any
        # object that moves (e.g. src/init_1CBF0.c -> src/libultra/audio/init_1CBF0.c) or
        # stops being generated (a TU that becomes fully live C emits no asm-processor
        # intermediate) leaves a permanent orphan in expected/. Those orphans made
        # objsame/iter_match report DIFF on six files that had not changed at all, which
        # is indistinguishable from genuinely losing a match.
        #
        # RE-VERIFY IMMEDIATELY BEFORE MIRRORING. This overwrites the golden reference
        # with whatever is currently built, so running it over a broken tree would make
        # expected/ adopt the broken bytes — and every later objsame would report a
        # false SAME, silently, forever. try_batch() gates on the sha1s, but it also
        # bisects and reverts, so the tree state at THIS point is not necessarily the
        # state that was verified. Check the artefacts on disk right now instead of
        # trusting that history.
        inner = sh(f"sha1sum {INNER}/build/conker.us.bin").stdout.split()
        outer = sh(f"sha1sum {REPO}/build/conker.us.z64").stdout.split()
        if not (inner and inner[0] == INNER_SHA and outer and outer[0] == OUTER_SHA):
            print("REFUSING to refresh expected/: current build is not byte-perfect "
                  f"(inner={inner[0] if inner else '?'}, outer={outer[0] if outer else '?'}). "
                  "expected/ left untouched.")
            return
        sh("rsync -a --delete conker/build/src/ conker/expected/build/src/")
        files = " ".join(f"conker/src/game_{p['off']:X}.c" for p in good)
        sh(f"git add conker/conker.us.yaml {files}", cwd=REPO)
        msg = f"yaml: stub {len(good)} game segments (asm->c) for matching\\n\\nROM sha1 unchanged (all GLOBAL_ASM stubs)."
        sh(f'git commit -q -m "{msg}\\n\\nCo-Authored-By: Claude Opus 4.8 (1M context) <noreply@anthropic.com>"', cwd=REPO)
        print(f"COMMITTED {len(good)} new stub segments — now in the matchable pool")
    else:
        print("no segments converted cleanly")

if __name__ == "__main__":
    if len(sys.argv) >= 3 and sys.argv[1] == "expand":
        expand(int(sys.argv[2]))
    else:
        print(__doc__)
