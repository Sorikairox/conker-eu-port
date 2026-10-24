#!/bin/bash
# P196: random 100 + setups + mutants for one function. usage: full.sh FUNC (files p207/FUNC_cand.c, FUNC_setups.txt, FUNC_muts.txt)
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
F=$1; D=docs/port/sessions/p207; C=$D/${F}_cand.c; S=$D/${F}_setups.txt; M=$D/${F}_muts.txt
echo "== random"; DIFFTEST_TMP=build/difftest_p207r_$F tools/port/difftest.sh func_$F $C --trials 100 --seed 1 2>&1 | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR)|POKE unread|never called" | cut -c1-300
[ -f $S ] && { echo "== setups"; TR=${TR:-4} $D/knobs.sh func_$F $C $S | awk '{print}' | grep -v ": EQUIV" ; echo "setups non-EQUIV above; total $(grep -cvE '^\s*(#|$)' $S)"; }
[ -f $M ] && [ -z "$NOMUT" ] && { echo "== mutants"; TR=${TR:-4} $D/mut.sh func_$F $C $S $M; }
echo DONE
