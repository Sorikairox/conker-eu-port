#!/bin/bash
# P316 (from P315): post-merge checks: verify_all + NM build + protocheck + implicit_scan (all TUs) + selftest + progress_nm.
cd ~/conker-wt/portb && eval "$(tools/eu_port/wt.sh env portb)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH DIFFTEST_SLOTS=1
D=docs/port/sessions/p316
tools/eu_port/verify_all.sh > $D/verify_all.log 2>&1; echo "verify_all rc $?"; tail -2 $D/verify_all.log
docker exec -w /conker $CONKERDEV make -C conker VERSION=eu NON_MATCHING=1 -j4 > $D/nm_build.log 2>&1; echo "nm rc $?"; tail -2 $D/nm_build.log
python3 tools/eu_port/protocheck.py > $D/protocheck.log 2>&1; echo "protocheck rc $?"; tail -1 $D/protocheck.log
python3 tools/port/implicit_scan.py > $D/implicit.log 2>&1; echo "implicit rc $?"; tail -3 $D/implicit.log
tools/port/difftest/selftest.sh > $D/selftest.log 2>&1; echo "selftest rc $?"; tail -2 $D/selftest.log
python3 tools/port/progress_nm.py 2>&1 | grep "^total"
