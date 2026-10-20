#!/bin/bash
# s121: screen a reference decomp (Rare or libultra) against the unmatched Conker functions.
# usage: rarescreen.sh <name> <srcroot> <slice: init|lo|hi|all> [thr=0.6] [-- extra cc flags...]
#   Compiles every .c under <srcroot> with refcc.sh at -O1, -O2 and -g (OPTS overrides, e.g. OPTS="-O1 -O2 -O3 -g"; -O3 works since s132) (with -Dstatic= so that
#   static functions get their own symbols; IDO emits none for statics), into
#   build_port/rare/<name>_O{1,2,3}/, then runs srcmatch.py on each objdir (opcode similarity,
#   size ratio 0.8-1.25) and writes the merged ranking (best ratio per Conker function) to
#   build_port/rare/<name>.<slice>.txt:  ratio conker_func insns opt:obj:reffunc refinsns file
# Undefined identifiers are only auto-#defined when they look like constants (UCRE), which
# keeps refcc.sh from defining `i` or `type`. Objects are reused when present (delete the dir to redo).
# Example: tools/eu_port/rarescreen.sh dkr tools/dkr init 0.6 -- -I include/libc -I libultra -D_FINALROM -DF3DDKR_GBI
R=${CONKER_ROOT:-$HOME/conker}; cd $R
name=$1; src=$2; sl=$3; thr=${4:-0.6}; shift 4 2>/dev/null; [ "$1" = "--" ] && shift; extra="$*"
mkdir -p build_port/rare
out=build_port/rare/$name.$sl.txt; : > $out.tmp
for O in ${OPTS:--O1 -O2 -g}; do
  d=build_port/rare/${name}_${O#-}
  if [ ! -d $d ] || [ -z "$(ls $d 2>/dev/null)" ]; then
    OPT=$O UCRE='^[A-Z_][A-Z0-9_]*$' tools/eu_port/refcc.sh $src $d 4 $extra -Dstatic= 2>&1 | tail -1 | sed "s/^/$O /"
  fi
  python3 tools/eu_port/srcmatch.py $d --slice $sl --thr $thr | sed "s/^\([0-9.]*\) \([^ ]*\) \([^ ]*\) /\1 \2 \3 ${O#-}:/" >> $out.tmp
done
sort -k1,1nr $out.tmp | awk '!seen[$2]++' > $out; rm -f $out.tmp
echo "$(wc -l < $out | tr -d ' ') functions >= $thr -> $out"; head -15 $out
