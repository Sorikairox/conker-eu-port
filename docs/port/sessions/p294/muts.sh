#!/bin/bash
# P294: harness mutants of D5E90.c (args: mutfile log trials -- harness args), sequential
cd ~/conker-wt/pe && eval "$(tools/eu_port/wt.sh env pe)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
mf=$1 log=$2 n=$3; shift 4
tools/port/nmharness_mut.sh conker/src_eu/nm_asm/D5E90.c $mf tools/port/difftest/nmasm_walls.py $n 1 "$@" > $log 2>&1; tail -1 $log
