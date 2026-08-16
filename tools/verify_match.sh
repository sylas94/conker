#!/bin/bash
# verify_match.sh -- FAIL-CLOSED verification that a decompiled function is a real match.
#
# WHY THIS EXISTS
#   Every wave used to hand-roll its own comparison. That is how measurement trap #7 got in:
#   a section compare whose two extractions BOTH failed printed "IDENTICAL (0 bytes)", because
#   the failure state collapsed into the success state. A verification routine that can report
#   success without having read anything is a false-positive generator, and it is worse than no
#   verification at all -- it is the one piece of the pipeline whose job is to be trustworthy.
#
# THE INVARIANT, and it is the whole design:
#       read A  -> MUST succeed
#       read B  -> MUST succeed
#       compare -> only now is a verdict meaningful
#   Any read failure is a VERIFICATION FAILURE, never an empty or absent comparison. Every check
#   below is three-state: PASS / FAIL / NO-EVIDENCE, and NO-EVIDENCE is a failure, not a shrug.
#   This script exits non-zero unless every single check actually ran and actually passed.
#
# WHAT IT DOES NOT DO
#   It does not judge whether the SOURCE is honest. A score of 0 is necessary, not sufficient.
#   No tool can tell you that a construct is a forcer -- read the diff yourself, and see the
#   fake-match policy in tools/ido_cookbook.md.
#
# USAGE
#   tools/verify_match.sh <tu> <func>        e.g. tools/verify_match.sh game_100810 func_150D5124
#
set -u

REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CONKER="$REPO/conker"
TU="${1:-}"
FUNC="${2:-}"

if [ -z "$TU" ] || [ -z "$FUNC" ]; then
    echo "usage: $0 <tu> <func>" >&2
    exit 2
fi

cd "$CONKER" || { echo "FATAL: cannot cd to $CONKER" >&2; exit 2; }

SRC="src/$TU.c"
OBJ="build/src/$TU.c.o"
GOLD="expected/build/src/$TU.c.o"
DIFFER="../tools/asm-differ/diff.py"

FAILED=0
note()  { printf '  %-9s %s\n' "$1" "$2"; }
pass()  { note "PASS" "$1"; }
fail()  { note "FAIL" "$1"; FAILED=1; }
noev()  { note "NO-EVID" "$1 -- treated as FAILURE (fail closed)"; FAILED=1; }

echo "=== verify_match: $FUNC in $TU ==="

# ---------------------------------------------------------------- 0. inputs must exist
[ -f "$SRC" ]  || { fail "source $SRC missing"; echo "ABORT"; exit 1; }
if [ ! -f "$GOLD" ]; then
    fail "golden object $GOLD missing -- cannot verify anything against nothing"
    echo "ABORT"; exit 1
fi
pass "source and golden object both present"

# ---------------------------------------------------------------- 1. pragma gone, definition live
# NOTE: no `|| echo 0` here. `grep -c` already PRINTS 0 when it matches nothing, and also exits
# non-zero -- so a `|| echo 0` fallback appends a SECOND zero, giving "0\n0", which then blows up
# every numeric test and silently reports PASS for a function that does not exist. Found by the
# negative control, which is the entire reason this script has one.
n_pragma=$(grep -c "GLOBAL_ASM.*\"[^\"]*/$FUNC\.s\"" "$SRC" 2>/dev/null | head -1)
n_def=$(grep -cE "^[A-Za-z_].*[ *]$FUNC[[:space:]]*\(" "$SRC" 2>/dev/null | head -1)
n_pragma=${n_pragma:-0}; n_def=${n_def:-0}
if [ "$n_pragma" -ne 0 ]; then fail "#pragma GLOBAL_ASM for $FUNC is STILL PRESENT ($n_pragma)"
elif [ "$n_def" -eq 0 ]; then fail "no live definition of $FUNC found in $SRC"
else pass "pragma gone; $n_def declaration/definition line(s) live"; fi

# ---------------------------------------------------------------- 2. forced rebuild (never score stale)
rm -f "$OBJ" "build/src/$TU.c"
if ! make "$OBJ" >/tmp/vm_build.log 2>&1; then
    fail "BUILD FAILED -- see /tmp/vm_build.log"; tail -15 /tmp/vm_build.log; echo "ABORT"; exit 1
fi
[ -f "$OBJ" ] || { fail "make returned 0 but produced NO object (the quoted -o trap)"; exit 1; }
pass "forced rebuild produced a fresh object"

# ---------------------------------------------------------------- 3. the symbol must EXIST in both
# Distinguishing "symbol absent" from "could not read the object" is the whole point here.
read_sym() {  # $1=object -> "value size" or empty
    readelf -sW "$1" 2>/dev/null | awk -v f="$FUNC" '$4=="FUNC" && $8==f {print $2, $3; exit}'
}
ours_sym=$(read_sym "$OBJ")
gold_sym=$(read_sym "$GOLD")
if [ -z "$ours_sym" ]; then fail "symbol $FUNC not found in OUR object (still a pragma? wrong name?)"
elif [ -z "$gold_sym" ]; then fail "symbol $FUNC not found in the GOLDEN object"
else
    ours_size=${ours_sym#* }; gold_size=${gold_sym#* }
    if [ "$ours_size" = "$gold_size" ]; then pass "symbol size $ours_size both sides"
    else note "WARN" "st_size ours=$ours_size golden=$gold_size (benign IFF .text compares identical below -- trailing alignment padding; symtab is stripped at link)"; fi
fi

# ---------------------------------------------------------------- 4. score, with AND without -R
score_of() {
    local out
    out=$(python3 "$DIFFER" -o "$FUNC" $1 --max-lines 4096 2>&1) || { echo "ERR"; return; }
    echo "$out" | grep -oE 'CURRENT \([0-9]+\)|score = [0-9]+' | grep -oE '[0-9]+' | head -1
}
s_R=$(score_of "-R"); s_n=$(score_of "")
if [ "$s_R" = "ERR" ] || [ -z "$s_R" ]; then noev "asm-differ produced no score WITH -R"
elif [ "$s_R" != "0" ];              then fail "score WITH -R is $s_R (not 0)"
else pass "score with -R = 0"; fi
if [ "$s_n" = "ERR" ] || [ -z "$s_n" ]; then noev "asm-differ produced no score WITHOUT -R"
elif [ "$s_n" != "0" ];              then fail "score WITHOUT -R is $s_n (not 0)"
else pass "score without -R = 0"; fi

# ---------------------------------------------------------------- 5. EVERY sibling still 0
syms=$(readelf -sW "$OBJ" 2>/dev/null | awk '$4=="FUNC" && $7!="UND" && $8!="" {print $8}' | sort -u)
if [ -z "$syms" ]; then noev "could not enumerate FUNC symbols in $OBJ"
else
    nsym=0; nbad=0
    for f in $syms; do
        nsym=$((nsym+1))
        s=$(python3 "$DIFFER" -o "$f" -R --max-lines 4096 2>&1 | grep -oE 'CURRENT \([0-9]+\)|score = [0-9]+' | grep -oE '[0-9]+' | head -1)
        if [ -z "$s" ]; then echo "      NO-EVID $f"; nbad=$((nbad+1))
        elif [ "$s" != "0" ]; then echo "      NONZERO $f -> $s"; nbad=$((nbad+1)); fi
    done
    if [ "$nbad" -eq 0 ]; then pass "all $nsym FUNC symbols in the TU score 0"
    else fail "$nbad of $nsym symbols are nonzero or unmeasurable"; fi
fi

# ------------------------------------------------- 5b. .text SECTION SIZE (ROM layout, not content)
# A function can score 0 and still break the ROM. If the TU's .text ends up SHORTER than the
# original, everything the linker places AFTER it moves. Measured case: func_10022460 scored 0
# with a .text of 0x250 against expected 0x290, and conker.ld places bzero.s.o immediately after
# it with SUBALIGN(16) and no ALIGN -- so bzero would have shifted from 0x226F0 to 0x226B0.
# That match was correctly REVERTED. This check is cheap, unambiguous, and independent of the
# content compare below, which only reports "differs" without saying the layout moved.
# NOTE the sed: readelf prints the section index as "[ 4]" (TWO awk fields) but "[12]" (ONE),
# so column positions shift with the index. Strip the bracket prefix before parsing.
sechdr() { readelf -SW "$1" 2>/dev/null | sed -E 's/^ *\[ *[0-9]+\] *//' | awk '$1==".text"{print $5; exit}'; }
ours_tsz=$(sechdr "$OBJ")
gold_tsz=$(sechdr "$GOLD")
if [ -z "$ours_tsz" ] || [ -z "$gold_tsz" ]; then
    noev "could not read .text section size from one or both objects"
elif [ "$ours_tsz" = "$gold_tsz" ]; then
    pass ".text SECTION SIZE 0x$ours_tsz both sides"
else
    fail ".text SECTION SIZE ours=0x$ours_tsz golden=0x$gold_tsz -- everything the linker places AFTER this TU would MOVE"
fi

# ---------------------------------------------------------------- 6. section bytes, FAIL CLOSED
# readelf -x is used deliberately: host objcopy silently emits NOTHING on these MIPS objects,
# which is exactly the failure that used to masquerade as "IDENTICAL (0 bytes)".
for sec in .text .rodata .data; do
    a_out=$(readelf -x "$sec" "$OBJ"  2>/dev/null); a_rc=$?
    b_out=$(readelf -x "$sec" "$GOLD" 2>/dev/null); b_rc=$?
    a_has=$([ $a_rc -eq 0 ] && [ -n "$a_out" ] && echo 1 || echo 0)
    b_has=$([ $b_rc -eq 0 ] && [ -n "$b_out" ] && echo 1 || echo 0)
    if [ "$a_has" = "0" ] && [ "$b_has" = "0" ]; then
        note "SKIP" "$sec absent in BOTH objects (legitimately empty section)"
    elif [ "$a_has" != "$b_has" ]; then
        # A MIGRATED TU legitimately grows a .rodata that its expected/ object predates.
        # conker.us.yaml is the authority on whether this TU owns a migrated rodata block; if it
        # does, and the asymmetry is exactly "ours has it, golden does not", then expected/ is
        # STALE rather than the build being wrong.  Report NO-EVIDENCE with the fix, not a FAIL
        # that reads like a byte defect -- but never PASS, because a stale golden proves nothing.
        # (Verified 2026-08-15: init_1E530 expected/=none built=48 B, while init_2E50 -- whose
        # expected/ was reseeded after its migration -- is 32 B on both sides.)
        if [ "$sec" = ".rodata" ] && [ "$a_has" = "1" ] && [ "$b_has" = "0" ] \
           && grep -qE "^\s*-\s*\[0x[0-9A-Fa-f]+,\s*\.rodata,\s*$TU\s*\]" "$CONKER/conker.us.yaml"; then
            noev ".rodata present only in OUR object, and $TU OWNS A MIGRATED RODATA BLOCK in conker.us.yaml -- expected/ predates that migration and must be reseeded (after the ROM gate passes) before this check can mean anything"
        else
            fail "$sec present on one side only (ours=$a_has golden=$b_has)"
        fi
    elif [ "$a_out" = "$b_out" ]; then
        pass "$sec IDENTICAL ($(printf '%s' "$a_out" | wc -l) dump lines)"
    else
        fail "$sec DIFFERS"
        diff <(printf '%s' "$a_out") <(printf '%s' "$b_out") | head -8
        # THE RELOCATION-NAMING FLOOR produces a .text diff that is NOT a defect: we emit
        # %lo(SYM+N) with the addend in the field against the base symbol, while a golden built
        # from #pragma GLOBAL_ASM emits %lo(SYM_plus_N) with a zero field against a name splat
        # minted at that offset.  Both link to the same address.  Do NOT silently pass that --
        # attach the evidence and let the human (and the ROM gate) decide.
        if [ "$sec" = ".text" ]; then
            echo "      -- is this the relocation-naming floor? --"
            readelf -rW "$OBJ"  2>/dev/null | awk '/R_MIPS/{print $1, $3}' | sort > /tmp/vm_r_ours
            readelf -rW "$GOLD" 2>/dev/null | awk '/R_MIPS/{print $1, $3}' | sort > /tmp/vm_r_gold
            n_ours=$(wc -l < /tmp/vm_r_ours)
            if [ "$n_ours" -eq 0 ]; then
                echo "      NO-EVIDENCE: readelf returned no relocations (wrong toolchain? run under WSL)"
            elif cmp -s /tmp/vm_r_ours /tmp/vm_r_gold; then
                echo "      relocation offsets+types are IDENTICAL ($n_ours) -- only symbol NAMES differ."
                echo "      Names only in golden (splat-minted interior labels):"
                readelf -rW "$OBJ"  2>/dev/null | awk '/R_MIPS/{print $5}' | sort -u > /tmp/vm_s_ours
                readelf -rW "$GOLD" 2>/dev/null | awk '/R_MIPS/{print $5}' | sort -u > /tmp/vm_s_gold
                comm -13 /tmp/vm_s_ours /tmp/vm_s_gold | sed 's/^/        /' | head -8
                echo "      CONSISTENT WITH THE RELOCATION-NAMING FLOOR, BUT NOT PROOF."
                echo "      Confirm with:  tools/relcheck.py $OBJ <func>   (non-circular)"
                echo "      and the full ROM gate, which is the only authority on linked bytes."
            else
                echo "      relocation offsets/types ALSO differ -- this is a REAL defect, not naming:"
                diff /tmp/vm_r_ours /tmp/vm_r_gold | head -6 | sed 's/^/        /'
            fi
        fi
    fi
done

# ---------------------------------------------------------------- 7. banned constructs, DIFF ONLY
cd "$REPO" || exit 1
d=$(git diff HEAD -- "conker/$SRC" | grep '^+' | grep -v '^+++')
if [ -z "$d" ]; then
    note "SKIP" "no diff vs HEAD for $SRC (already committed?) -- audit the source by hand"
else
    hits=$(printf '%s\n' "$d" | grep -nE 'volatile|while[[:space:]]*\([[:space:]]*0[[:space:]]*\)|\(void\)[[:space:]]*0|&[[:space:]]*0xFFFFFFFF' )
    selfa=$(printf '%s\n' "$d" | grep -nE '^\+[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*=[[:space:]]*\1[[:space:]]*;')
    if [ -z "$hits" ] && [ -z "$selfa" ]; then pass "no banned constructs in the diff"
    else fail "banned constructs in the diff:"; printf '%s\n%s\n' "$hits" "$selfa" | sed '/^$/d' | head -10; fi
fi

echo
if [ "$FAILED" -eq 0 ]; then
    echo "RESULT: ALL CHECKS RAN AND PASSED."
    echo "        Score 0 is NECESSARY, NOT SUFFICIENT -- now read the diff and judge the SOURCE."
    echo "        The ROM gate (scratchpad/gate_full.sh) remains the final authority."
    exit 0
else
    echo "RESULT: VERIFICATION FAILED (a check failed, or could not be run at all)."
    exit 1
fi
