#!/usr/bin/env bash
#
# permuter_tu.sh -- TU-AWARE decomp-permuter harness for the Conker decomp.
#
# WHY THIS EXISTS
# ---------------
# decomp-permuter compiles an isolated single-function source.c.  That is wrong for
# this project for two independent reasons:
#
#   1. src/ast_util.py:extract_fn() DEMOTES every function definition in base.c that
#      is not the target down to a bare prototype.  So even if you hand it the whole
#      translation unit, the permuter compiles the target ALONE.
#   2. IDO 5.3 -O2 -g3 codegen for a function is translation-unit dependent (the repo
#      has an on-record case of a source that compiled to golden bytes in isolation
#      and scored 560 inside its real 40-function TU).
#
# This harness keeps base.c single-function (so the randomizer works normally) but
# makes compile.sh SPLICE the candidate back into the real TU and compile the WHOLE
# file with the repo's exact flags + asm-processor, in a private per-worker temp dir.
# The object it emits is therefore identical to what `make build/src/<tu>.c.o` emits,
# and the score it reports is the real one.
#
# USAGE
# -----
#   ./permuter_tu.sh setup <tu> <func> <full-tu-candidate.c> [dir]
#       <tu>    e.g. game_1A89B0        (i.e. src/<tu>.c)
#       <func>  e.g. func_1517BBAC
#       <full-tu-candidate.c>  a COMPLETE copy of src/<tu>.c in which <func> is live C
#                              (its #pragma GLOBAL_ASM removed).  This is normally your
#                              current near-miss.  It is never written into the repo.
#       [dir]   permuter directory to create (default: permuter_tu/<func>)
#
#   ./permuter_tu.sh selftest <dir>
#       MANDATORY before trusting any run.  Proves:
#         (a) head+region+tail reassembles the input TU byte-for-byte;
#         (b) compile.sh's object has .text for <func> BYTE-IDENTICAL to the object the
#             repo Makefile produces from the same C  (this is what makes the score real);
#         (c) positive control: base.c scores what the harness claims;
#         (d) negative control: a trivially perturbed base.c scores strictly WORSE;
#         (e) TU-context control: the same function compiled in ISOLATION and its
#             bytes compared, to show whether TU context actually matters here.
#
#   ./permuter_tu.sh run <dir> [-j N] [extra permuter args]
#       Runs decomp-permuter with --stack-diffs (MANDATORY: without it the scorer
#       rewrites every sp-relative offset to "addr(sp)" and normalises `addiu sp,sp,N`,
#       so frame-size bugs -- the usual last blocker -- become invisible and it reports
#       0 for sources asm-differ scores in the hundreds).
#
#   ./permuter_tu.sh extract <dir> <output-dir-or-source.c>
#       Prints the candidate's function text (everything after the splice marker), i.e.
#       what you paste over the #pragma GLOBAL_ASM in the repo file.
#
#   ./permuter_tu.sh chain <dir> <output-dir>
#       Promote an output to the new base and clear old outputs, to break a plateau.
#
# HARD RULE: a permuter score of 0 is a CANDIDATE, never a match.  Re-score it with
#   cd conker && python3 ../tools/asm-differ/diff.py -o <func> -R
# with the #pragma GLOBAL_ASM actually removed, then gate on the full ROM sha1.
#
set -uo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"     # .../conker
ROOT="$(cd "$HERE/.." && pwd)"                            # repo root
PERMUTER="${PERMUTER_DIR:-$ROOT/tools/decomp-permuter}"
if [ ! -f "$PERMUTER/permuter.py" ]; then
  # fall back to the scratchpad clone used during development
  for cand in "$ROOT"/../*/decomp-permuter /mnt/c/Users/*/AppData/Local/Temp/claude/*/*/scratchpad/decomp-permuter; do
    [ -f "$cand/permuter.py" ] && PERMUTER="$cand" && break
  done
fi

CC="$ROOT/ido/ido5.3_recomp/cc"
AP="$ROOT/tools/asm-processor"
MIPSBIT="-mips2 -o32"
CFLAGS="-G 0 -Xfullwarn -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul"
CFLAGS="$CFLAGS -D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI_2 -D_MIPS_SZLONG=32 -woff 649,838"
INC="-I . -I include -I include/2.0L -I include/2.0L/PR -I include/libc -I src/libultra/os -I src/libultra/audio -I src/libultra/io"
ASFLAGS="-EB -mtune=vr4300 -march=vr4300 -mabi=32 -I include"
MARKER="PERMUTER_SPLICE_MARKER"

die() { echo "permuter_tu: $*" >&2; exit 1; }

# OPT_FLAGS for a TU, honouring the Makefile's per-file overrides.
opt_flags_for() {
  local tu="$1" f
  f=$(grep -oP "^\\\$\(BUILD_DIR\)/\\\$\(SRC_DIR\)/${tu}\.c\.o:\s*OPT_FLAGS\s*:=\s*\K.*" "$HERE/Makefile" 2>/dev/null | tail -1)
  echo "${f:--O2 -g3}"
}

# ---------------------------------------------------------------- setup
cmd_setup() {
  local tu="$1" func="$2" cand="$3" dir="${4:-$HERE/permuter_tu/$2}"
  [ -f "$cand" ] || die "candidate TU not found: $cand"
  [ -f "$HERE/src/$tu.c" ] || die "no such TU: src/$tu.c"
  [ -f "$HERE/expected/build/src/$tu.c.o" ] || die "no golden object expected/build/src/$tu.c.o"
  local opt; opt="$(opt_flags_for "$tu")"

  mkdir -p "$dir" || die "mkdir $dir"
  dir="$(cd "$dir" && pwd)"
  cp "$cand" "$dir/input_tu.c"

  # --- split the candidate TU into head / <func> definition / tail -----------
  python3 - "$dir/input_tu.c" "$func" "$dir" <<'PY' || die "could not locate $func in $cand"
import re, sys
src, func, out = sys.argv[1:4]
lines = open(src, encoding="utf-8", errors="replace").read().split("\n")
start = None
pat = re.compile(r"^[A-Za-z_].*\b" + re.escape(func) + r"\s*\(")
for i, ln in enumerate(lines):
    if pat.match(ln) and not ln.rstrip().endswith(";"):
        start = i
        break
if start is None:
    sys.exit(1)
# brace-match from the first '{' at/after the signature
depth = 0; seen = False; end = None
for j in range(start, len(lines)):
    for ch in lines[j]:
        if ch == "{":
            depth += 1; seen = True
        elif ch == "}":
            depth -= 1
    if seen and depth == 0:
        end = j
        break
if end is None:
    sys.exit(1)
open(out + "/tu_head.c", "w", encoding="utf-8").write("\n".join(lines[:start]) + "\n")
open(out + "/region.c",  "w", encoding="utf-8").write("\n".join(lines[start:end+1]) + "\n")
open(out + "/tu_tail.c", "w", encoding="utf-8").write("\n".join(lines[end+1:]))
print(f"  region = lines {start+1}..{end+1} ({end-start+1} lines)")
PY

  # --- base.c ---------------------------------------------------------------
  # ONE cpp pass over head+region, so that (i) the prelude pycparser needs is exactly
  # the real headers plus the TU's own file-local decls, and (ii) the region handed to
  # the randomizer is fully macro-expanded.  Anything else risks the randomizer seeing
  # a file-local macro as an undeclared identifier and mangling it.
  { cat "$dir/tu_head.c"
    echo
    echo "int ${MARKER}_BEGIN;"
    echo
    cat "$dir/region.c"
  } > "$dir/.pp_in.c"
  ( cd "$HERE" && cpp -P -nostdinc -D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI_2 \
        -D_MIPS_SZLONG=32 -I . -I include -I include/2.0L -I include/2.0L/PR -I include/libc \
        "$dir/.pp_in.c" > "$dir/.pp_out.c" ) || die "cpp of tu_head+region failed"
  grep -q "${MARKER}_BEGIN" "$dir/.pp_out.c" || die "splice marker lost in cpp output"
  awk -v m="${MARKER}_BEGIN" '$0 ~ m {exit} {print}' "$dir/.pp_out.c" > "$dir/prelude.h"
  awk -v m="${MARKER}_BEGIN" 'p{print} $0 ~ m {p=1}' "$dir/.pp_out.c" > "$dir/region_pp.c"
  { cat "$dir/prelude.h"
    echo
    echo "extern int $MARKER;"
    echo
    cat "$dir/region_pp.c"
  } > "$dir/base.c"
  rm -f "$dir/.pp_in.c" "$dir/.pp_out.c"

  # --- compile.sh: splice + WHOLE-TU compile with the repo's exact pipeline ---
  cat > "$dir/compile.sh" <<EOF
#!/usr/bin/env bash
# generated by permuter_tu.sh -- compiles the candidate INSIDE the real TU
set -e
IN="\$1"; OUT="\$3"
D="$dir"
W=\$(mktemp -d "\${TMPDIR:-/tmp}/permtu.XXXXXXXX")
trap 'rm -rf "\$W"' EXIT
awk 'p{print} /$MARKER/{p=1}' "\$IN" > "\$W/region.c"
cat "\$D/tu_head.c" "\$W/region.c" "\$D/tu_tail.c" > "\$W/tu.c"
cd "$HERE"
python3 "$AP/asm_processor.py" $opt "\$W/tu.c" > "\$W/tu.i.c"
"$CC" -c -32 $CFLAGS $INC $opt $MIPSBIT -o "\$OUT" "\$W/tu.i.c"
python3 "$AP/asm_processor.py" $opt "\$W/tu.c" --post-process "\$OUT" \\
    --assembler "mips-linux-gnu-as $ASFLAGS" --asm-prelude "$AP/prelude.inc"
EOF
  chmod +x "$dir/compile.sh"

  # --- objdump wrapper: score ONLY the target function ----------------------
  cat > "$dir/objdump_fn.sh" <<EOF
#!/usr/bin/env bash
# generated by permuter_tu.sh -- restricts the scorer to $func's own instructions,
# so the other (GLOBAL_ASM, byte-identical) functions in the TU cannot mask or dilute it.
mips-linux-gnu-objdump -drz -m mips:4300 "\$1" | awk -v fn="$func" '
  /^[0-9a-f]+ <.*>:\$/ { p = (\$0 ~ ("<" fn ">:")) }
  p
'
EOF
  chmod +x "$dir/objdump_fn.sh"

  cp "$HERE/expected/build/src/$tu.c.o" "$dir/target.o"
  echo "$func" > "$dir/function.txt"
  cat > "$dir/settings.toml" <<EOF
compiler_type = "ido"
func_name = "$func"
objdump_command = "$dir/objdump_fn.sh"
EOF
  cat > "$dir/harness.env" <<EOF
TU="$tu"
FUNC="$func"
OPT="$opt"
EOF
  echo "permuter_tu: created $dir  (TU=$tu FUNC=$func OPT_FLAGS='$opt')"
  echo "permuter_tu: NEXT -> ./permuter_tu.sh selftest \"$dir\""
}

# ---------------------------------------------------------------- selftest
cmd_selftest() {
  local dir; dir="$(cd "$1" && pwd)" || die "no such dir $1"
  . "$dir/harness.env"
  local rc=0

  echo "=== (a) reassembly identity ==="
  cat "$dir/tu_head.c" "$dir/region.c" "$dir/tu_tail.c" > "$dir/.reassembled.c"
  if cmp -s "$dir/.reassembled.c" "$dir/input_tu.c"; then
    echo "    PASS: head+region+tail == input TU"
  else
    echo "    FAIL: reassembly differs from input TU"; diff "$dir/input_tu.c" "$dir/.reassembled.c" | head -10; rc=1
  fi

  echo "=== (b) harness object vs repo-Makefile object (byte compare of $FUNC) ==="
  # harness path
  "$dir/compile.sh" "$dir/base.c" -o "$dir/.harness.o" || { echo "    FAIL: compile.sh errored"; rc=1; }
  # reference path: the real Makefile pipeline, in a scratch dir, on the SAME source
  local W; W=$(mktemp -d "${TMPDIR:-/tmp}/permtu_ref.XXXXXX")
  mkdir -p "$W/build/src"
  cp "$dir/input_tu.c" "$W/$TU.c"
  ( cd "$HERE" && python3 "$AP/asm_processor.py" $OPT "$W/$TU.c" > "$W/build/src/$TU.c" \
      && "$CC" -c -32 $CFLAGS $INC $OPT $MIPSBIT -o "$W/ref.o" "$W/build/src/$TU.c" \
      && python3 "$AP/asm_processor.py" $OPT "$W/$TU.c" --post-process "$W/ref.o" \
           --assembler "mips-linux-gnu-as $ASFLAGS" --asm-prelude "$AP/prelude.inc" ) \
      || { echo "    FAIL: reference compile errored"; rc=1; }
  local h r
  h=$("$dir/objdump_fn.sh" "$dir/.harness.o" | sha1sum | cut -d' ' -f1)
  r=$("$dir/objdump_fn.sh" "$W/ref.o"        | sha1sum | cut -d' ' -f1)
  echo "    harness   $FUNC disasm sha1 = $h"
  echo "    makefile  $FUNC disasm sha1 = $r"
  if [ "$h" = "$r" ] && [ -n "$h" ]; then echo "    PASS: identical codegen"; else echo "    FAIL"; rc=1; fi

  echo "=== (b2) pycparser round-trip: what the permuter ACTUALLY compiles ==="
  # The permuter never compiles base.c verbatim -- it preprocesses it, parses it with
  # pycparser and REGENERATES the C from the AST.  If that round trip is not codegen-
  # neutral, every score the harness reports is measured on the wrong source.
  PERMUTER="$PERMUTER" python3 - "$dir/base.c" "$FUNC" "$dir/.roundtrip.c" <<'PY'
import os, sys
sys.path.insert(0, os.environ["PERMUTER"])
from src.preprocess import preprocess
from src import ast_util
base, fn, out = sys.argv[1:4]
source = preprocess(base)
ast = ast_util.parse_c(source)
orig_fn, idx = ast_util.extract_fn(ast, fn)
ast_util.normalize_ast(orig_fn, ast)
open(out, "w", encoding="utf-8").write(ast_util.to_c(ast))
print("    round-trip source written")
PY
  if [ -s "$dir/.roundtrip.c" ]; then
    "$dir/compile.sh" "$dir/.roundtrip.c" -o "$dir/.roundtrip.o" 2>&1 | head -5
    local rt; rt=$("$dir/objdump_fn.sh" "$dir/.roundtrip.o" 2>/dev/null | sha1sum | cut -d' ' -f1)
    echo "    roundtrip $FUNC disasm sha1 = $rt"
    if [ "$rt" = "$r" ] && [ -n "$rt" ]; then
      echo "    PASS: pycparser round trip is codegen-neutral"
    else
      echo "    FAIL: round trip changes codegen -- scores would be measured on the wrong source"; rc=1
    fi
  else
    echo "    FAIL: could not produce a round-trip source (pycparser parse error?)"; rc=1
  fi

  echo "=== (c) positive control: score of the unmodified base ==="
  local base_score
  base_score=$(python3 "$PERMUTER/permuter.py" "$dir" --stack-diffs --debug 2>&1 \
               | grep -oP "base score = \K[0-9]+" | head -1)
  echo "    base score = ${base_score:-<none>}"
  [ -n "$base_score" ] || { echo "    FAIL: no base score"; rc=1; }

  echo "=== (d) negative control: perturbed base must score WORSE ==="
  local B; B=$(mktemp -d "${TMPDIR:-/tmp}/permtu_neg.XXXXXX")
  cp -r "$dir"/* "$B/" 2>/dev/null
  # flip a constant that is certain to be in the function body
  python3 - "$B/base.c" "$MARKER" <<'PY'
import sys, re
p, marker = sys.argv[1], sys.argv[2]
t = open(p, encoding="utf-8", errors="replace").read()
i = t.index(marker)
head, body = t[:i], t[i:]
# perturb the first small decimal constant in the body
body2, n = re.subn(r"(?<![\w.])0x44(?![\w])", "0x48", body, count=1)
if n == 0:
    body2, n = re.subn(r"(?<![\w.])1(?![\w.])", "2", body, count=1)
open(p, "w", encoding="utf-8").write(head + body2)
print("    perturbations applied:", n)
PY
  sed -i "s#$dir#$B#g" "$B/compile.sh" "$B/settings.toml"
  local neg_score
  neg_score=$(python3 "$PERMUTER/permuter.py" "$B" --stack-diffs --debug 2>&1 \
              | grep -oP "base score = \K[0-9]+" | head -1)
  echo "    perturbed score = ${neg_score:-<none>}   (baseline ${base_score:-?})"
  if [ -n "$neg_score" ] && [ -n "$base_score" ] && [ "$neg_score" -gt "$base_score" ]; then
    echo "    PASS: perturbation is not free"
  else
    echo "    FAIL: perturbation was free -- the harness is not scoring what you think"; rc=1
  fi
  rm -rf "$B"

  echo "=== (e) TU-context control: what a PLAIN (non-TU) permuter would compile ==="
  # .roundtrip.c is exactly what stock decomp-permuter hands its compiler: the context
  # decls with every other function body demoted to a prototype, plus the target.
  # Compiling it standalone is the setup this harness exists to replace.
  local I; I=$(mktemp -d "${TMPDIR:-/tmp}/permtu_iso.XXXXXX")
  grep -v '^#pragma GLOBAL_ASM' "$dir/.roundtrip.c" > "$I/iso.c" 2>/dev/null
  ( cd "$HERE" && "$CC" -c -32 $CFLAGS $INC $OPT $MIPSBIT -o "$I/iso.o" "$I/iso.c" ) >"$I/err" 2>&1
  if [ -s "$I/iso.o" ]; then
    local iso; iso=$("$dir/objdump_fn.sh" "$I/iso.o" | sha1sum | cut -d' ' -f1)
    echo "    isolated  $FUNC disasm sha1 = $iso"
    if [ "$iso" = "$h" ]; then
      echo "    RESULT: isolation agrees for this TU -- context happens not to matter here."
    else
      echo "    RESULT: isolation DIFFERS from the in-TU build."
      echo "            A plain single-function permuter would optimise the wrong bytes;"
      echo "            this harness is load-bearing."
    fi
  else
    echo "    (isolated compile failed -- see below; treat as 'cannot compile standalone')"
    head -4 "$I/err"
  fi
  rm -rf "$I" "$W"

  echo
  [ $rc -eq 0 ] && echo "SELFTEST: PASS" || echo "SELFTEST: FAIL"
  return $rc
}

# ---------------------------------------------------------------- run
cmd_run() {
  local dir; dir="$(cd "$1" && pwd)"; shift
  # --stack-diffs is not optional here: without it the scorer normalises frame size away.
  exec python3 "$PERMUTER/permuter.py" "$dir" --stack-diffs "$@"
}

# ---------------------------------------------------------------- extract
cmd_extract() {
  local src="$2"
  [ -d "$src" ] && src="$src/source.c"
  awk "p{print} /$MARKER/{p=1}" "$src"
}

# ---------------------------------------------------------------- chain
cmd_chain() {
  local dir; dir="$(cd "$1" && pwd)"; local out="$2"
  [ -d "$out" ] && out="$out/source.c"
  [ -f "$out" ] || die "no such output source: $out"
  cp "$dir/base.c" "$dir/base.c.prev"
  cp "$out" "$dir/base.c"
  rm -rf "$dir"/output-*
  echo "permuter_tu: base.c replaced from $out; previous kept as base.c.prev; outputs cleared"
}

case "${1:-}" in
  setup)    shift; cmd_setup "$@" ;;
  selftest) shift; cmd_selftest "$@" ;;
  run)      shift; cmd_run "$@" ;;
  extract)  shift; cmd_extract "x" "$@" ;;
  chain)    shift; cmd_chain "$@" ;;
  *) sed -n '2,60p' "${BASH_SOURCE[0]}"; exit 1 ;;
esac
