#!/bin/bash
# P59 generic knob runner. usage: knobs.sh FUNC cand.c setups.txt [names...]
# P60: as p59/knobs.sh plus a 6th field DIFFTEST_OUTA (stack out-params). setups: name ! ARG ! POKE ! RET ! RETF ! OUTA  (fields may be empty; # comments)
# Env: TR (trials, 16), SEED (1), SEEDS (list, overrides SEED). Prints one line per setup and seed.
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
F=$1; C=$2; S=$3; shift 3
grep -vE '^\s*(#|$)' "$S" | while IFS='!' read -r n a p r rf ow; do
  n=$(echo $n); [ $# -gt 0 ] && ! [[ " $* " == *" $n "* ]] && continue
  for sd in ${SEEDS:-${SEED:-1}}; do
    out=$(DIFFTEST_TMP=build/difftest_p60_$F DIFFTEST_EXACT='*' DIFFTEST_ARG="$(echo $a)" DIFFTEST_POKE="$(echo $p)" \
      DIFFTEST_RET="$(echo $r)" DIFFTEST_RETF="$(echo $rf)" DIFFTEST_OUTA="$(echo $ow)" tools/port/difftest.sh $F $C --trials ${TR:-16} --seed $sd 2>&1 \
      | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR)" | cut -c1-200)
    echo "$n/s$sd: $out"
  done
done
