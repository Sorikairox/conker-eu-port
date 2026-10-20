#!/bin/bash
# s101: unmatched (GLOBAL_ASM) lo-slice callers of the given callees: "insns callee file func"
# usage: spcallers.sh [lo|hi] callee...
cd "${CONKER_ROOT:-$HOME/conker}/conker"
sl=$1; shift
for c in "$@"; do
  grep -l "jal *$c\b" asm/nonmatchings/game*/*.s 2>/dev/null | while read f; do
    stem=$(basename $(dirname $f)); fn=$(basename $f .s)
    hex=$(echo $stem | grep -oE '[0-9A-F]+$'); v=$((16#$hex))
    if [ "$sl" = lo ] && [ $v -ge $((0x130000)) ]; then continue; fi
    if [ "$sl" = hi ] && [ $v -lt $((0x130000)) ]; then continue; fi
    grep -q "GLOBAL_ASM(.*/$fn.s" src_eu/$stem.c src_eu/game/done/$stem.c 2>/dev/null || continue
    n=$(grep -cE '^\s*/\* [0-9A-F]+ ' $f)
    echo "$n $c $stem $fn"
  done
done | sort -n
