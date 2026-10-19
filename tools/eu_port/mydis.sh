#!/bin/bash
# usage: mydis.sh <func>  : disassemble column 2 ("mine") of tools/decomp-permuter/repair/<func>.diff
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
f=$1; d=${CONKER_ROOT:-$HOME/conker}/tools/decomp-permuter/repair/$f.diff
sed -E "s/^\*\*/  /" $d | awk "{print \$2}" | python3 -c "
import sys,struct
b=b''.join(struct.pack('>I',int(l,16)) for l in sys.stdin if l.strip())
open('/dev/stdout.bin','wb') if False else None
sys.stdout.buffer.write(b)" > ${CONKER_ROOT:-$HOME/conker}/conker/build/mine_$f.bin
docker exec ${CONKERDEV:-conkerdev} mips-linux-gnu-objdump -D -b binary -mmips:isa32 -EB /conker/conker/build/mine_$f.bin | tail -n +8
