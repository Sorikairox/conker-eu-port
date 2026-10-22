#!/bin/bash
# P80: func_150322B8 over s22b8_full.txt in 4 parallel chunks (own DIFFTEST_TMP each, KTAG), log p80/knobs_22b8_full.log
D=/Users/sorikairo/conker-wt/port/docs/port/sessions/p80; cd $D
for c in 0 1 2 3; do
  awk -v c=$c 'NF && $0 !~ /^#/ && (NR % 4) == c' s22b8_full.txt > ../../../../port_work/p80/full_$c.txt
  KTAG=_c$c TR=${TR:-4} ./knobs.sh func_150322B8 port_work/p80/22b8.c port_work/p80/full_$c.txt > ../../../../port_work/p80/full_$c.log 2>&1 &
done
wait
cat ../../../../port_work/p80/full_?.log | sort > knobs_22b8_full.log
echo DONE; awk '{print $2}' knobs_22b8_full.log | sort | uniq -c
