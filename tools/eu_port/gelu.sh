#!/bin/bash
# compile every GoldenEye src/libultrare/**/*.c (US) into build_port/s119/gelu/<dir>_<name>.o (run in conkerdev at /conker)
G=tools/goldeneye; O=build_port/s119/gelu; mkdir -p $O
for f in $(find $G/src/libultrare -name '*.c'); do
  d=$(basename $(dirname $f)); n=$(basename $f .c); opt=-O1
  case $d in audio|gu|libc) opt=-O3;; esac
  case $n in vimgr|pimgr) opt=-O2;; esac
  cpp -P -undef -nostdinc -D_LANGUAGE_C -D__sgi -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32 -D_FINALROM -DTARGET_N64 -DVERSION_US -I $G -I $G/include -I $G/include/PR -I $G/src/libultrare -I $G/src/libultra -I $G/src $f > $O/${d}_$n.c 2>/dev/null
  /opt/ido5.3/cc -c -32 -G 0 -non_shared -Wab,-r4300_mul -woff 819,820,852,821,838,649 $opt -mips2 -o $O/${d}_$n.o $O/${d}_$n.c >/dev/null 2>&1 || echo "FAIL $d/$n"
done
