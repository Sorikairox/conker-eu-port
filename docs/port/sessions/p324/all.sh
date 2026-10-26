#!/bin/bash
# P324: checks + census + build in one go (sequential: verify_all regenerates asm/). Output: compact rc lines.
cd ~/conker-wt/web && eval "$(tools/eu_port/wt.sh env web)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
docs/port/sessions/p324/check.sh
port/web/run.sh census > port_work/p324/census.log 2>&1; echo "census rc $?"; tail -3 port_work/p324/census.log
port/web/run.sh build > port_work/p324/build.log 2>&1; echo "build rc $?"; tail -3 port_work/p324/build.log
