#!/bin/bash
# P294: walls harness, args: tag trials seeds... -- extra args (e.g. --only ab6d0); logs walls_<tag>_s<seed>.log
cd ~/conker-wt/pe && eval "$(tools/eu_port/wt.sh env pe)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
tag=$1; n=$2; shift 2; seeds=(); while [ $# -gt 0 ] && [ "$1" != "--" ]; do seeds+=($1); shift; done; shift
for s in "${seeds[@]}"; do NOBUILD=1 HLOG=docs/port/sessions/p294/walls_${tag}_s$s.log tools/port/nmharness.sh tools/port/difftest/nmasm_walls.py $n $s "$@"; echo "s$s: $(tail -1 docs/port/sessions/p294/walls_${tag}_s$s.log)"; grep -m3 DIFF docs/port/sessions/p294/walls_${tag}_s$s.log; done
