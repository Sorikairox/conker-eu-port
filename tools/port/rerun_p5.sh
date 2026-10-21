#!/bin/bash
# P5: re-run convert.py (no m2c generation, existing drafts) on the DIFFER/UNSURE/HANG functions of
# earlier tags with the fixed difftest.  usage: tools/port/rerun_p5.sh TAG...  (list in port_work/r5_TAG.txt)
R=${CONKER_ROOT:-$HOME/conker}; cd $R
for T in "$@"; do
  mkdir -p port_work/r5_$T; ln -sfn ../$T/gen port_work/r5_$T/gen
  CONVERT_BUDGET=${CONVERT_BUDGET:-120} python3 tools/port/convert.py --tag r5_$T --no-gen -l port_work/r5_$T.txt > port_work/r5_$T.log 2>&1
  tail -1 port_work/r5_$T.log
done
