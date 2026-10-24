#!/bin/bash
# P207: for each FUNC: C under NM (file:line of the definition) or asm (file). run from conker/.
for f in "$@"; do
  d=$(grep -nE "^[a-zA-Z_].*[ *]$f\(.*\)[[:space:]]*\{?[[:space:]]*$" src_eu/*.c | grep -v ';' | head -1 | cut -c1-90)
  a=$(find asm/nonmatchings -name "$f.s" | head -1)
  echo "$f | ${d:-none} | ${a:+asm $(grep -c '/\*' $a)}"
done
