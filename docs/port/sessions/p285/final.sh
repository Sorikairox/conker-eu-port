#!/bin/bash
# P285: sequential final checks, logs in docs/port/sessions/p285/
cd ~/conker-wt/pe && eval "$(tools/eu_port/wt.sh env pe)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH DIFFTEST_SLOTS=1
D=docs/port/sessions/p285
MUT=1 tools/port/reverify.sh func_10001550 > $D/rv_func_10001550.log 2>&1; echo 1550 done
MUT=1 tools/port/reverify.sh func_16001044 > $D/rv2_func_16001044.log 2>&1; echo 1044 done
tools/port/reverify.sh func_150AA950 func_150AA9B0 func_150AAB58 func_150AC824 > $D/rv_d5e90.log 2>&1; echo d5e90 done
tools/eu_port/verify_all.sh > $D/verify_all.log 2>&1; echo "verify_all rc $?"
docker exec -w /conker $CONKERDEV make -C conker VERSION=eu NON_MATCHING=1 -j4 > $D/nm_build.log 2>&1; echo "nm rc $?"
python3 tools/eu_port/protocheck.py > $D/protocheck.log 2>&1; echo "protocheck rc $?"
bash tools/port/difftest/selftest.sh > $D/selftest.log 2>&1; echo "selftest rc $?"; tail -1 $D/selftest.log
