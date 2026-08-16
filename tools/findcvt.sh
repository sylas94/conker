#!/bin/bash
# findcvt.sh -- find ROM functions with a BARE cvt.w.s (no cfc1/ctc1 FPU-control fixup within
# +/-5 instructions, i.e. NOT the float->unsigned conversion sequence) and say whether the
# function is already decompiled to live C.
set -u
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO/conker" || exit 1

grep -rhoE 'GLOBAL_ASM\("[^"]*/([A-Za-z_][A-Za-z0-9_]*)\.s"\)' src/ --include=*.c \
  | sed -E 's|.*/([A-Za-z0-9_]+)\.s"\)|\1|' | sort -u > /tmp/fc_pragma.txt

# sliding window of 11 lines; flag a cvt.w.s whose window has no cfc1/ctc1
awk '
  function flush(  i) { for (i=1;i<=n;i++) delete buf[i]; n=0 }
  /^glabel/ { fn=$2 }
  { line[NR%11] = $0; fnat[NR%11] = fn }
  /cvt\.w\.s/ { hits[NR] = fn }
  END { }
  { }
' asm/*.s >/dev/null 2>&1

for f in asm/*.s; do
  awk -v FILE="$f" '
    /^glabel/ { fn=$2 }
    { L[NR]=$0; F[NR]=fn }
    /cvt\.w\.s/ { c[NR]=1 }
    END {
      for (i in c) {
        bare=1
        for (j=i-5; j<=i+5; j++) if (j in L && L[j] ~ /cfc1|ctc1/) bare=0
        if (bare) print F[i], FILE, i
      }
    }
  ' "$f"
done | sort -u > /tmp/fc_bare.txt

echo "functions with a BARE cvt.w.s: $(awk '{print $1}' /tmp/fc_bare.txt | sort -u | wc -l)"
echo
echo "=== BARE cvt.w.s, and whether decompiled ==="
awk '{print $1, $2, $3}' /tmp/fc_bare.txt | sort -u | while read -r fn file ln; do
    if grep -qx "$fn" /tmp/fc_pragma.txt; then
        st="PRAGMA (not decompiled)"
    else
        src=$(grep -rlE "^[A-Za-z_].*[ *]$fn[[:space:]]*\(" src/ --include=*.c 2>/dev/null | head -1)
        st="LIVE C -> ${src:-<no C definition found>}"
    fi
    printf '%-18s %-22s line %-6s %s\n' "$fn" "$file" "$ln" "$st"
done
