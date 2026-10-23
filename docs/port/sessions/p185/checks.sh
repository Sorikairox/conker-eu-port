#!/bin/bash
# P105: post-merge checks. Usage: docs/port/sessions/p185/checks.sh TAG
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
T=${1:-x}; L=port_work/p185
tools/eu_port/verify_all.sh > $L/verify_$T.log 2>&1; echo "verify rc=$?"; head -3 $L/verify_$T.log
docker exec conkerdev-web bash -c 'cd /conker && make -C conker VERSION=eu NON_MATCHING=1 -j4' > $L/nm_build_$T.log 2>&1
echo "nm rc=$?"; grep -E "error|undefined reference" $L/nm_build_$T.log | head -5
python3 tools/port/protocheck.py > $L/protocheck_$T.log 2>&1; echo "protocheck rc=$?"; tail -2 $L/protocheck_$T.log
python3 docs/port/sessions/p110/floatint_scan.py > $L/floatint_$T.log 2>&1; echo "floatint rc=$?"; tail -3 $L/floatint_$T.log
python3 tools/port/arity_scan.py > $L/arity_$T.log 2>&1; echo "arity rc=$?"; tail -2 $L/arity_$T.log
python3 port/tools/m2c_sanity.py > $L/m2c_$T.log 2>&1; echo "m2c_sanity rc=$?"; tail -2 $L/m2c_$T.log
