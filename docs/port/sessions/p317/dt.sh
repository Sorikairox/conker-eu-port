#!/bin/bash
# P317: random difftest of FUNC's current NM C (nmblock) vs its asm. usage: dt.sh FUNC [K=V knobs...]  (NR trials, default 100)
cd ~/conker-wt/portb && eval "$(tools/eu_port/wt.sh env portb)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
F=$1; shift; W=port_work/p317; mkdir -p $W
python3 tools/port/nmblock.py $F $W/$F.c > /dev/null || { echo "$F: no C"; exit 1; }
env "$@" DIFFTEST_TMP=build/difftest_p317_${F}_$$ tools/port/difftest.sh $F $W/$F.c --trials ${NR:-100} --seed 1 2>&1 | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR)|knob|unread" | head -3 | cut -c1-300
