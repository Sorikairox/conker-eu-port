#!/bin/bash
# P59 generic knob runner. usage: knobs.sh FUNC cand.c setups.txt [names...]
# setups.txt lines: name ! DIFFTEST_ARG ! DIFFTEST_POKE ! DIFFTEST_RET ! DIFFTEST_RETF   (fields may be empty; # comments)
# Env: TR (trials, 16), SEED (1), SEEDS (list, overrides SEED). Prints one line per setup and seed.
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
F=$1; C=$2; S=$3; shift 3
grep -vE '^\s*(#|$)' "$S" | while IFS='!' read -r n a p r rf; do
  n=$(echo $n); [ $# -gt 0 ] && ! [[ " $* " == *" $n "* ]] && continue
  for sd in ${SEEDS:-${SEED:-1}}; do
    out=$(DIFFTEST_TMP=build/difftest_p62_$F DIFFTEST_EXACT='*' DIFFTEST_ARG="$(echo $a)" DIFFTEST_POKE="$(echo $p)" \
      DIFFTEST_RET="$(echo $r)" DIFFTEST_RETF="$(echo $rf)" tools/port/difftest.sh $F $C --trials ${TR:-16} --seed $sd 2>&1 \
      | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR)" | cut -c1-200)
    echo "$n/s$sd: $out"
  done
done
