#!/bin/bash
# P126: frame-1985 trap check: sequential events-on node boots (one at a time), 55 s each, summary per run.  trap6.sh N
cd /Users/sorikairo/conker-wt/web || exit 1
for i in $(seq 1 ${1:-5}); do
  PORT_P103BOOT=1 PORT_P88SCENE=8 PORT_HEAPWATCH=1 PORT_P78NULL=1 docs/port/sessions/p126/nb.sh trap$i 55
  python3 docs/port/sessions/p126/sum.py port_work/p126/trap$i.log | head -1
done
echo ALLDONE
