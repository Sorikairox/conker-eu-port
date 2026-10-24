#!/bin/bash
# P180: random-trial difftest of the func_1500BEC0 unit drafts (plain and ROMDATA). usage: rand_all.sh [TRIALS]
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p180
for k in AD84 AF08 B1F4 B3B0 B714 B8F4 BAB8 BC7C BEC0 BE0C; do
  f=func_1500$k; [ $k = BE0C ] && f=func_1517BE0C
  for rd in 0 1; do
    echo "$k rd$rd: $(DIFFTEST_ROMDATA=$rd DIFFTEST_TMP=build/difftest_p180_$k tools/port/difftest.sh $f $D/${k}_cand.c --trials ${1:-100} 2>&1 | grep -E '^(EQUIV|DIFFER|UNSURE|ERROR|CERR)' | cut -c1-300)"
  done
done
