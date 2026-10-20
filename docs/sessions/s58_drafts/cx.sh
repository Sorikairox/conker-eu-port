#!/bin/bash
# cx.sh file.c [grep]: compile a standalone test file with the game flags, print sp ops per function
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
f=$(basename $1 .c)
docker exec -w /conker/conker/build_port/s58/x conkerdev sh -c "/opt/ido5.3/cc -c -32 -G 0 -Xfullwarn -signed -non_shared -Wab,-r4300_mul -woff 649,838 -O2 -g3 -mips2 -o32 -o $f.o $f.c 2>&1 | grep -v warning | head -5; mips-linux-gnu-objdump -d --no-show-raw-insn $f.o" | grep -E '^[0-9a-f]+ <|sp\)|sp,sp|addiu.*sp,' | sed -E 's/^ +[0-9a-f]+:\s+//'
