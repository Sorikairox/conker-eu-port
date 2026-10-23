#!/bin/bash
# P71 mutant runner (p71/knobs.sh: 8 setup fields). usage: mut.sh FUNC base.c setups.txt 'sed-expr' ['sed-expr' ...]
# Each sed expression makes one mutant of base.c (must change it); prints KILLED (any setup DIFFER) or LIVE.
cd /Users/sorikairo/conker-wt/port
F=$1; B=$2; S=$3; shift 3; i=0
for e in "$@"; do
  i=$((i+1)); m=port_work/p71/mut_${F}_$i.c
  sed -e "$e" "$B" > $m
  if cmp -s "$B" "$m"; then echo "m$i NOCHANGE: $e"; continue; fi
  r=$(TR=${TR:-4} bash docs/port/sessions/p71/knobs.sh $F $m $S | awk '{print $2}' | sort | uniq -c | tr '\n' ' ')
  case "$r" in *DIFFER*) echo "m$i KILLED ($r): $e";; *) echo "m$i LIVE ($r): $e";; esac
done
