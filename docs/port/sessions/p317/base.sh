#!/bin/bash
# P317: difftest a function's NM block with HEAD's source (baseline) vs the working tree. usage: base.sh FUNC FILE.c [knobs...]
cd ~/conker-wt/portb && eval "$(tools/eu_port/wt.sh env portb)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
F=$1; S=$2; shift 2; W=port_work/p317; mkdir -p $W
cp conker/src_eu/$S $W/$S.cur && git show HEAD:conker/src_eu/$S > conker/src_eu/$S
python3 tools/port/nmblock.py $F $W/${F}_base.c > /dev/null; cp $W/$S.cur conker/src_eu/$S
python3 tools/port/nmblock.py $F $W/${F}_cur.c > /dev/null
for v in base cur; do
  echo "$F $v: $(env "$@" DIFFTEST_TMP=build/difftest_p317b_${F}_$v tools/port/difftest.sh $F $W/${F}_$v.c --trials ${NR:-100} --seed 1 2>&1 | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR)" | head -1 | cut -c1-220)"
done
