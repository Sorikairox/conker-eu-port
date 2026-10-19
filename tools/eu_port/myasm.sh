#!/bin/bash
# usage: myasm.sh <func> <draft.c>  -> prints the assembly of your draft (objdump, no raw words); screens it too
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
R=${CONKER_ROOT:-$HOME/conker}; f=$1
T=ma_$f
SCREEN_KEEP=1 TRYDIR=$T $R/tools/eu_port/m2c/try $f $2 | head -${MAXERR:-4}
docker exec -w /conker/conker ${CONKERDEV:-conkerdev} sh -c "mips-linux-gnu-objdump -dr --no-show-raw-insn build/$T/$f.o | sed -n '/^[0-9a-f]* <$f>/,\$p'" | cut -c1-70
