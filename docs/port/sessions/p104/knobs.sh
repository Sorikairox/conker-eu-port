#!/bin/bash
# P104: p100 copy. P93: p90 copy (p104 temp dir, 400-char lines for the POKE notes). P90: p89 copy (p90 paths). P86: p85 copy. P85: p80/knobs.sh (KTMP overrides the temp dir). P80: p76/knobs.sh for the port worktree. P59 generic knob runner. usage: knobs.sh FUNC cand.c setups.txt [names...]
# P67: as p64/knobs.sh plus an 8th field DIFFTEST_OUTB (bytes). P64: as p60/knobs.sh plus a 7th field DIFFTEST_OUTW (per-call words; N >= 4 = stack arg since P64). Env DIFFTEST_ARGMEM passes through.
# setups: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW  (fields may be empty; # comments)
# Env: TR (trials, 16), SEED (1), SEEDS (list, overrides SEED). Prints one line per setup and seed.
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
F=$1; C=$2; S=$3; shift 3
grep -vE '^\s*(#|$)' "$S" | while IFS='!' read -r n a p r rf ow ww wb; do
  n=$(echo $n); [ $# -gt 0 ] && ! [[ " $* " == *" $n "* ]] && continue
  for sd in ${SEEDS:-${SEED:-1}}; do
    out=$(DIFFTEST_TMP=${KTMP:-build/difftest_p104_$F${KTAG:-}} DIFFTEST_EXACT='*' DIFFTEST_ARG="$(echo $a)" DIFFTEST_POKE="$(echo $p)" \
      DIFFTEST_RET="$(echo $r)" DIFFTEST_RETF="$(echo $rf)" DIFFTEST_OUTA="$(echo $ow)" DIFFTEST_OUTW="$(echo $ww)" DIFFTEST_OUTB="$(echo $wb)" tools/port/difftest.sh $F $C --trials ${TR:-16} --seed $sd 2>&1 \
      | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR)" | cut -c1-400)
    echo "$n/s$sd: $out"
  done
done
