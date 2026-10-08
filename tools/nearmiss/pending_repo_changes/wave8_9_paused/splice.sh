# usage: splice.sh <workdir>  -- copy every <TU>.c deliverable into conker/src (handles debugger.c nested), print diffstat
R='/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp'
W="$1"
for f in "$W"/*.c; do
  b=$(basename "$f" .c)
  case "$b" in debugger|debugger_dbg) dst="$R/conker/src/debugger/debugger.c";; *) dst="$R/conker/src/$b.c";; esac
  [ -f "$dst" ] || { echo "SKIP $b (no repo TU)"; continue; }
  sed -i 's/\r$//' "$f"
  cp "$f" "$dst"; echo "spliced $b -> $(grep -c GLOBAL_ASM "$dst") pragmas left"
done
