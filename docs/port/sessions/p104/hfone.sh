#!/bin/bash
# P104: one hfrun.sh job: hfone.sh FUNC (env HFD = candidate dir, HFO = log)
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
r=$(DIFFTEST_TMP=build/difftest_p104hf_$1 tools/port/difftest.sh $1 $HFD/$1.c --trials ${TR:-100} --seed 1 2>&1 | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR|CERR)" | head -1 | cut -c1-300)
echo "$1	$r" >> $HFO
