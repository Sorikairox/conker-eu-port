#!/bin/bash
# P56: wall engine / ray cast harness runs (synthetic seeds + real levels); output in port_work/p56/runs.log
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
H="python3 ../tools/port/difftest/nmasm_walls.py"
for s in 11 12 13; do for k in ab6d0 ac8c4 ray; do echo "seed $s $k: $(docker exec -w /conker/conker $CONKERDEV sh -c "$H 400 $s --only $k 2>&1 | tail -1")"; done; done
for L in 0x21 0x1 0x5 0xB; do echo "level $L:"; docker exec -w /conker/conker $CONKERDEV sh -c "$H 300 7 --level $L 2>&1 | tail -4"; done
