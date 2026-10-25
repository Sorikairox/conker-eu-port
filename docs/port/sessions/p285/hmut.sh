#!/bin/bash
# P285: nmharness_mut.sh on D5E90.c with the unit mode: hmut.sh MUTFILE HELPERS TRIALS LOG
cd ~/conker-wt/pe && eval "$(tools/eu_port/wt.sh env pe)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
tools/port/nmharness_mut.sh conker/src_eu/nm_asm/D5E90.c $1 tools/port/difftest/nmasm_walls.py $3 1 --unit $2 > $4 2>&1
tail -1 $4
