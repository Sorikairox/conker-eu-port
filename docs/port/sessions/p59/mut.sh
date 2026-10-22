#!/bin/bash
# P59 mutants. usage: mut.sh FUNC draft.c setups.txt muts.txt
# muts.txt lines: sed-expression % setup names (space separated). A mutant is killed when any setup DIFFERs.
cd "$(dirname "$0")/../../../.."; F=$1; D=$2; S=$3; M=port_work/p59/mut_$F.c
grep -vE '^\s*(#|$)' "$4" | while IFS='%' read -r e n; do
  e=$(echo "$e" | sed 's/ *$//'); sed "$e" $D > $M; cmp -s $D $M && { echo "NOT APPLIED: $e"; continue; }
  r=$(docs/port/sessions/p59/knobs.sh $F $M $S $n | grep -c DIFFER)
  echo "$([ $r -gt 0 ] && echo KILLED || echo SURVIVED) [$e] ($n): $r DIFFER"
done
