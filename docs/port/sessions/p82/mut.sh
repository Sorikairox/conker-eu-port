#!/bin/bash
# P68 mutants. usage: mut.sh FUNC draft.c setups.txt muts.txt
# P82: sed errors print SED ERROR; a setup giving neither EQUIV nor DIFFER (CERR, UNSURE) prints INVALID, not SURVIVED.
# P77: NORAND=1 skips the random phase (for functions whose random trials DIFFER already, e.g. func_150954E4: table index out of range).
# P73: the random phase runs without DIFFTEST_ARGMEM (out-of-range stack reads of random inputs differ between frame layouts); setups keep it.
# muts.txt lines: sed-expression % setup names (space separated; empty = all setups).
# P68: each mutant first runs 100 random trials (seed 1), then its setups one by one, and stops at the first
# DIFFER (p67/mut.sh ran every setup of every mutant). Env TR = trials per setup (default 8).
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
F=$1; D=$2; S=$3; M=port_work/p82_mut_$F.c
# P77 guard: a random phase only means something when the unmutated draft is EQUIV on it (else every mutant is "killed by random").
if [ -z "$NORAND" ] && ! env -u DIFFTEST_ARGMEM DIFFTEST_TMP=build/difftest_p73m_$F tools/port/difftest.sh $F $D --trials 100 --seed 1 2>&1 | grep -q "^EQUIV"; then
  echo "NOTE: draft not EQUIV on random trials: random phase off"; NORAND=1
fi
grep -vE '^\s*(#|$)' "$4" | while IFS='%' read -r e n; do
  e=$(echo "$e" | sed 's/ *$//'); sed "$e" $D > $M 2>/dev/null || { echo "SED ERROR [$e]"; continue; }; cmp -s $D $M && { echo "NOT APPLIED: $e"; continue; }
  k=""
  if [ -z "$NORAND" ] && env -u DIFFTEST_ARGMEM DIFFTEST_TMP=build/difftest_p73m_$F tools/port/difftest.sh $F $M --trials 100 --seed 1 2>&1 | grep -q "^DIFFER"; then k=random; fi
  if [ -z "$k" ]; then
    names=$(echo $n); [ -z "$names" ] && names=$(grep -vE '^\s*(#|$)' $S | awk '{print $1}')
    for s in $names; do
      o=$(KTMP=build/difftest_p73m_$F TR=${TR:-8} docs/port/sessions/p73/knobs.sh $F $M $S $s)
      if echo "$o" | grep -q DIFFER; then k=$s; break; fi
      # P82: a setup that is neither EQUIV nor DIFFER (CERR, UNSURE, crash) is not a survival
      echo "$o" | grep -q EQUIV || { k="NOTHING: $s gave '$(echo $o | cut -c1-80)'"; break; }
    done
  fi
  case "$k" in NOTHING*) echo "INVALID ($k) [$e]";; "") echo "SURVIVED [$e]";; *) echo "KILLED by $k [$e]";; esac
done
