#!/bin/bash
# P54: nmasm_floorsets.py synthetic seeds + real levels (after both builds). Output: port_work/p54/floorruns.log
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
H="python3 ../tools/port/difftest/nmasm_floorsets.py"
{
for s in 3 4; do echo "synth seed $s: $(docker exec -w /conker/conker $CONKERDEV $H 1500 $s 2>&1 | tail -1)"; done
for L in ${LEVELS:-0x21 0x1 0x5 0xB}; do echo "level $L: $(docker exec -w /conker/conker $CONKERDEV $H 300 1 --level $L 2>&1 | grep -v '^  (' | tr '\n' ' ')"; done
} > port_work/p54/floorruns.log 2>&1
