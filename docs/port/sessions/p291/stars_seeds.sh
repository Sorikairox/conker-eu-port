#!/bin/bash
# P291: star field harness, 300 trials x seeds 1-3 (NM build already current)
cd ~/conker-wt/pe && eval "$(tools/eu_port/wt.sh env pe)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
for s in 1 2 3; do NOBUILD=1 HLOG=docs/port/sessions/p291/stars_s$s.log tools/port/nmharness.sh tools/port/difftest/nmasm_stars.py 300 $s; done
