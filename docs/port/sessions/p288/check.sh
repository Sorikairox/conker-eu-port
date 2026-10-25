#!/bin/bash
# P288: verify_all + NM build + protocheck (sequential), logs in docs/port/sessions/p288/
cd ~/conker-wt/pe && eval "$(tools/eu_port/wt.sh env pe)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH DIFFTEST_SLOTS=1
D=docs/port/sessions/p288
tools/eu_port/verify_all.sh > $D/verify_all.log 2>&1; echo "verify_all rc $?"
docker exec -w /conker $CONKERDEV make -C conker VERSION=eu NON_MATCHING=1 -j4 > $D/nm_build.log 2>&1; echo "nm rc $?"
python3 tools/eu_port/protocheck.py > $D/protocheck.log 2>&1; echo "protocheck rc $?"
