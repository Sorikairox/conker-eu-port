#!/bin/bash
# P291: sequential MUT=1 reverify of the listed functions, one log per function in docs/port/sessions/p291/
cd ~/conker-wt/pe && eval "$(tools/eu_port/wt.sh env pe)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH DIFFTEST_SLOTS=1
for f in "$@"; do MUT=1 tools/port/reverify.sh $f > docs/port/sessions/p291/rv_$f.log 2>&1; echo "$f done"; done
