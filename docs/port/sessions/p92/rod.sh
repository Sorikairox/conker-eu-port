#!/bin/bash
# P92: print words of the default EU ELF at ADDR (hex, n words) as hex + f32. usage: rod.sh 80096D84 [n]
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
a=$((16#$1)); n=${2:-1}
docker exec $CONKERDEV mips-linux-gnu-objdump -s --start-address=$a --stop-address=$((a+4*n)) /conker/conker/build/conker.eu.elf | grep -E '^ [0-9a-f]{8} ' | python3 -c '
import sys,struct
for l in sys.stdin:
  p=l.split(); a=int(p[0],16)
  for i,w in enumerate(p[1:5]):
    if len(w)==8: print("%08X %s %g"%(a+4*i,w,struct.unpack(">f",bytes.fromhex(w))[0]))'
