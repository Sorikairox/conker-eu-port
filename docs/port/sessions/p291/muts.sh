#!/bin/bash
# P291: harness mutant runs (sequential): stars, func_150AD844 (P288 mutants, new ray inputs), ray cast body
cd ~/conker-wt/pe && eval "$(tools/eu_port/wt.sh env pe)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
D=docs/port/sessions/p291
tools/port/nmharness_mut.sh conker/src_eu/game_eu_129250.c $D/stars_hmuts.txt tools/port/difftest/nmasm_stars.py 40 1 > $D/hmut_stars.log 2>&1; tail -1 $D/hmut_stars.log
tools/port/nmharness_mut.sh conker/src_eu/nm_asm/D5E90.c docs/port/sessions/p288/ray_ad844_hmuts.txt tools/port/difftest/nmasm_walls.py 300 1 --only ray > $D/hmut_ad844.log 2>&1; tail -1 $D/hmut_ad844.log
tools/port/nmharness_mut.sh conker/src_eu/nm_asm/D5E90.c $D/ray_body_hmuts.txt tools/port/difftest/nmasm_walls.py 300 1 --only ray > $D/hmut_raybody.log 2>&1; tail -1 $D/hmut_raybody.log
