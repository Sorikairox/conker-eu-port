#!/bin/bash
# P324 (copy of p322/check.sh): post-merge checks for port-web: verify_all + NM build + protocheck + implicit_scan +
# selftest + romabs_check + arity_scan + census summary. Run after a clean port/web/run.sh build.
cd ~/conker-wt/web && eval "$(tools/eu_port/wt.sh env web)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH DIFFTEST_SLOTS=1
D=port_work/p324; mkdir -p $D
tools/eu_port/verify_all.sh > $D/verify_all.log 2>&1; echo "verify_all rc $?"; tail -2 $D/verify_all.log
docker exec -w /conker $CONKERDEV make -C conker VERSION=eu NON_MATCHING=1 -j4 > $D/nm_build.log 2>&1; echo "nm rc $?"; tail -2 $D/nm_build.log
python3 tools/eu_port/protocheck.py > $D/protocheck.log 2>&1; echo "protocheck rc $?"; tail -1 $D/protocheck.log
python3 tools/port/implicit_scan.py > $D/implicit.log 2>&1; echo "implicit rc $?"; tail -3 $D/implicit.log
python3 port/tools/romabs_check.py > $D/romabs.log 2>&1; echo "romabs rc $?"; tail -2 $D/romabs.log
python3 tools/port/arity_scan.py > $D/arity.log 2>&1; echo "arity rc $?"; tail -3 $D/arity.log
tools/port/difftest/selftest.sh > $D/selftest.log 2>&1; echo "selftest rc $?"; tail -2 $D/selftest.log
