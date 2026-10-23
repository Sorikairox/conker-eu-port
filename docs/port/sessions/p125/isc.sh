#!/bin/bash
# isc.sh FUNC... : C (body exists in src_eu/src) or ASM (only GLOBAL_ASM) per function, with file
cd /Users/sorikairo/conker-wt/portb
for f in "$@"; do
  b=$(grep -lE "^[A-Za-z][^;]*\b$f\s*\([^;]*$" conker/src_eu/*.c conker/src/*.c 2>/dev/null | head -1)
  a=$(grep -l "/$f.s\")" conker/src_eu/*.c 2>/dev/null | head -1)
  if [ -n "$b" ]; then echo "$f C ${b##*/}"; elif [ -n "$a" ]; then echo "$f ASM ${a##*/}"; else echo "$f ? (lib/asm)"; fi
done
