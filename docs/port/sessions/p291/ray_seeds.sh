#!/bin/bash
# P291: walls harness --only ray, 300 trials per seed (args: seeds); NM build must be current
cd ~/conker-wt/pe && eval "$(tools/eu_port/wt.sh env pe)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
for s in "$@"; do NOBUILD=1 HLOG=docs/port/sessions/p291/ray_s$s.log tools/port/nmharness.sh tools/port/difftest/nmasm_walls.py 300 $s --only ray; tail -1 docs/port/sessions/p291/ray_s$s.log; done
