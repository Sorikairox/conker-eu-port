#!/bin/bash
# P291: ray body survivors with the grid trees, then ray seeds 2-5
cd ~/conker-wt/pe && eval "$(tools/eu_port/wt.sh env pe)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
D=docs/port/sessions/p291
tools/port/nmharness_mut.sh conker/src_eu/nm_asm/D5E90.c $D/ray_body_surv.txt tools/port/difftest/nmasm_walls.py 300 1 --only ray > $D/hmut_raybody2.log 2>&1; tail -1 $D/hmut_raybody2.log
$D/ray_seeds.sh 2 3 4 5
