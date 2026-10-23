#!/bin/bash
# P166: disassemble EU functions from the matching ELF. usage: dis.sh func_X... (symbol names as in the map)
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
for f in "$@"; do docker exec $CONKERDEV sh -c "mips-linux-gnu-objdump -d --no-show-raw-insn --disassemble=$f /conker/conker/build/conker.eu.elf" | grep -E '^ *[0-9a-f]+:' | sed 's/^ *//' ; done
