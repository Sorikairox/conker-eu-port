#!/bin/bash
_top=$(git rev-parse --show-toplevel 2>/dev/null); if [ -n "$_top" ] && [ "$_top" != "${CONKER_ROOT:-$HOME/conker}" ]; then echo "refusing: cwd repo $_top != CONKER_ROOT ${CONKER_ROOT:-$HOME/conker} (run: eval \"\$(tools/eu_port/wt.sh env <name>)\")" >&2; exit 3; fi
# usage: mydis.sh <func>  : disassemble column 2 ("mine") of tools/decomp-permuter/repair/<func>.diff
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
f=$1; d=${CONKER_ROOT:-$HOME/conker}/tools/decomp-permuter/repair/$f.diff
sed -E "s/^\*\*/  /" $d | awk "{print \$2}" | python3 -c "
import sys,struct
b=b''.join(struct.pack('>I',int(l,16)) for l in sys.stdin if l.strip())
open('/dev/stdout.bin','wb') if False else None
sys.stdout.buffer.write(b)" > ${CONKER_ROOT:-$HOME/conker}/conker/build/mine_$f.bin
docker exec ${CONKERDEV:-conkerdev} mips-linux-gnu-objdump -D -b binary -mmips:isa32 -EB /conker/conker/build/mine_$f.bin | tail -n +8
