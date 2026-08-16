#!/usr/bin/env bash
# Measure two claimed IDO frame levers at OUR flags (-O2 -g3), outside conker/src.
#   L1: `void f(void)` uses 4 MORE bytes of stack than `void f()`
#   L2: calling a function returning a value costs stack even if the result is ignored
# Sweeps the number of live locals 0..8 so 8-byte frame ALIGNMENT cannot mask a 4-byte delta.
set -uo pipefail
cd "/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp/conker" || exit 1
CC="../ido/ido5.3_recomp/cc"
CROSS=mips-linux-gnu-
W=$HOME/framelever2; rm -rf "$W"; mkdir -p "$W"
CFLAGS="-G 0 -Xfullwarn -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul -D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI_2 -D_MIPS_SZLONG=32 -woff 649,838"
MIPSBIT="-mips2 -o32"

frame() {
  local src="$1"
  local opt="$2"
  local tag="$3"
  local obj="$W/$tag.o"
  rm -f "$obj"
  $CC -c -32 $CFLAGS $opt $MIPSBIT -o "$obj" "$src" > "$W/$tag.log" 2>&1
  if [ ! -f "$obj" ]; then echo "FAIL"; return; fi
  local n
  n=$(${CROSS}objdump -d "$obj" 2>/dev/null | grep -m1 -oE 'addiu[[:space:]]+sp,sp,-[0-9]+' | grep -oE '[0-9]+$')
  [ -n "$n" ] && echo "$n" || echo "leaf"
}

# Build a probe with N locals that are all live across a call, forcing real frame pressure.
gen() {  # $1=N locals  $2=proto spelling for the callee  $3=outfile
  local n=$1 proto=$2 out=$3 i
  { echo "extern void sink${proto};"
    echo "extern int  src(int);"
    echo "int probe(int a) {"
    for i in $(seq 1 "$n"); do echo "    int v$i;"; done
    for i in $(seq 1 "$n"); do echo "    v$i = src(a + $i);"; done
    echo "    sink();"
    echo -n "    return a"
    for i in $(seq 1 "$n"); do echo -n " + v$i"; done
    echo ";"
    echo "}"
  } > "$out"
}

echo "######## L1: callee declared (void) vs () -- sweep locals 0..8, OPT = -O2 -g3 ########"
printf "  %-8s %-10s %-10s %s\n" N "(void)" "()" delta
for n in 0 1 2 3 4 5 6 7 8; do
  gen "$n" "(void)" "$W/a.c"; gen "$n" "()" "$W/b.c"
  x=$(frame "$W/a.c" "-O2 -g3" "a$n"); y=$(frame "$W/b.c" "-O2 -g3" "b$n")
  d="?"; case "$x$y" in *FAIL*|*leaf*) d="-";; *) d=$((x - y));; esac
  printf "  %-8s %-10s %-10s %s\n" "$n" "$x" "$y" "$d"
done

echo
echo "######## L1b: the DEFINED function itself, probe(void) vs probe() ########"
for n in 0 2 4 6; do
  { echo "extern int src(int);"; echo "int probe(void) {"
    for i in $(seq 1 "$n"); do echo "    int v$i;"; done
    for i in $(seq 1 "$n"); do echo "    v$i = src($i);"; done
    echo -n "    return 0"; for i in $(seq 1 "$n"); do echo -n " + v$i"; done; echo ";"; echo "}"
  } > "$W/c.c"
  sed 's/int probe(void)/int probe()/' "$W/c.c" > "$W/d.c"
  x=$(frame "$W/c.c" "-O2 -g3" "c$n"); y=$(frame "$W/d.c" "-O2 -g3" "d$n")
  d="?"; case "$x$y" in *FAIL*|*leaf*) d="-";; *) d=$((x - y));; esac
  printf "  N=%-4s (void)=%-8s ()=%-8s delta=%s\n" "$n" "$x" "$y" "$d"
done

echo
echo "######## L2: ignored int return vs void callee vs captured, locals 0..6 ########"
printf "  %-6s %-12s %-12s %-12s\n" N ignored voidcallee captured
for n in 0 1 2 3 4 5 6; do
  pre=""; ret="    return a"
  for i in $(seq 1 "$n"); do pre="$pre    int v$i;\n"; done
  body=""; for i in $(seq 1 "$n"); do body="$body    v$i = src(a + $i);\n"; done
  for i in $(seq 1 "$n"); do ret="$ret + v$i"; done
  { echo "extern int src(int);"; echo "extern int getval(int);"; echo "int probe(int a) {"
    printf "$pre"; printf "$body"; echo "    getval(a);"; echo "$ret;"; echo "}"; } > "$W/e.c"
  { echo "extern int src(int);"; echo "extern void doval(int);"; echo "int probe(int a) {"
    printf "$pre"; printf "$body"; echo "    doval(a);"; echo "$ret;"; echo "}"; } > "$W/f.c"
  { echo "extern int src(int);"; echo "extern int getval(int);"; echo "int probe(int a) {"
    printf "$pre"; echo "    int q;"; printf "$body"; echo "    q = getval(a);"; echo "$ret + q;"; echo "}"; } > "$W/g.c"
  x=$(frame "$W/e.c" "-O2 -g3" "e$n"); y=$(frame "$W/f.c" "-O2 -g3" "f$n"); z=$(frame "$W/g.c" "-O2 -g3" "g$n")
  printf "  %-6s %-12s %-12s %-12s\n" "$n" "$x" "$y" "$z"
done

echo
echo "VERDICT KEY:"
echo "  L1  TRUE only if some N shows (void) - () == +4.  All zeros => FALSE at -O2 -g3."
echo "  L2  TRUE only if 'ignored' > 'voidcallee' at some N."
