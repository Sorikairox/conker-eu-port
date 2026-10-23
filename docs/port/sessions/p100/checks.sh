#!/bin/bash
# P100: p98 copy. P98: NM build + protocheck + progress_nm, then quick (or full with FULL=1) verify_all; output to port_work/p100/checks_$1.log
cd /Users/sorikairo/conker-wt/port
eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
log=port_work/p100/checks_$1.log
{ docs/port/sessions/p100/nmcheck.sh
  if [ -n "$FULL" ]; then tools/eu_port/verify_all.sh; else tools/eu_port/verify_all.sh --quick; fi
  echo "verify rc=$?"; echo CHECKS-DONE; } > $log 2>&1
