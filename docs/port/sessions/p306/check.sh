#!/bin/bash
# P306 (from P291): verify_all + NM build + protocheck + implicit_scan + selftest + progress_nm (sequential), logs here.
cd ~/conker-wt/pe && eval "$(tools/eu_port/wt.sh env pe)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH DIFFTEST_SLOTS=1
D=docs/port/sessions/p306
tools/eu_port/verify_all.sh > $D/verify_all.log 2>&1; echo "verify_all rc $?"
docker exec -w /conker $CONKERDEV make -C conker VERSION=eu NON_MATCHING=1 -j4 > $D/nm_build.log 2>&1; echo "nm rc $?"
python3 tools/eu_port/protocheck.py > $D/protocheck.log 2>&1; echo "protocheck rc $?"
python3 tools/port/implicit_scan.py conker/src_eu/game_eu_20B730.c conker/src_eu/game_eu_129650.c > $D/implicit.log 2>&1; echo "implicit rc $?"; tail -3 $D/implicit.log
tools/port/difftest/selftest.sh > $D/selftest.log 2>&1; echo "selftest rc $?"; tail -2 $D/selftest.log
python3 tools/port/progress_nm.py 2>&1 | grep "^total"
