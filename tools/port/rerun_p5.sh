#!/bin/bash
# P5: re-run convert.py (no m2c generation, existing drafts) on the DIFFER/UNSURE/HANG functions of
# earlier tags with the fixed difftest.  usage: tools/port/rerun_p5.sh TAG...  (list in port_work/r5_TAG.txt;
# RERUN_PREFIX=r7 uses port_work/r7_TAG.txt and tag r7_TAG instead)
. "$(dirname "${BASH_SOURCE[0]}")/portguard.sh"  # wrong-checkout guard (P7)
R=${CONKER_ROOT:-$HOME/conker}; cd $R
X=${RERUN_PREFIX:-r5}
for T in "$@"; do
  mkdir -p port_work/${X}_$T; ln -sfn ../$T/gen port_work/${X}_$T/gen
  CONVERT_BUDGET=${CONVERT_BUDGET:-120} python3 tools/port/convert.py --tag ${X}_$T --no-gen -l port_work/${X}_$T.txt > port_work/${X}_$T.log 2>&1
  tail -1 port_work/${X}_$T.log
done
