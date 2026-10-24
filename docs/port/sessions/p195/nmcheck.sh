#!/bin/bash
# NM build (container) + protocheck + progress_nm, compact output
cd /Users/sorikairo/conker-wt/port
eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
docker exec -w /conker $CONKERDEV make -C conker VERSION=eu NON_MATCHING=1 -j4 > port_work/p195/nm_build.log 2>&1; rc=$?
echo "NM build rc=$rc"; grep -iE "error|undefined reference" port_work/p195/nm_build.log | head -15
python3 tools/port/protocheck.py 2>&1 | tail -4
python3 tools/port/progress_nm.py 2>&1 | tail -6
