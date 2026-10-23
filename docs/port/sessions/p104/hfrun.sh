#!/bin/bash
# P104: re-run difftest (100 random trials, seed 1, P100 FP-argument harness) on every NM block listed by hdrfloat.py.
# usage: hfrun.sh LIST.tsv CANDDIR OUT.log [P]   (P parallel jobs, default 3; xargs -P, no shell &)
cd /Users/sorikairo/conker-wt/port
export HFD=$2 HFO=$3; : > $HFO
cut -f1 $1 | xargs -P ${4:-3} -n 1 docs/port/sessions/p104/hfone.sh
echo HF-DONE >> $HFO
