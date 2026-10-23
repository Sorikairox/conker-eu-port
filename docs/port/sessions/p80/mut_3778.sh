#!/bin/bash
# P80: func_15013778 mutants on s3778.txt (ARGMEM: the 0x34-byte block passed to memcpy)
D=/Users/sorikairo/conker-wt/port/docs/port/sessions/p80
DIFFTEST_ARGMEM="10023360=1:52" MTAG=_w $D/mutfast.sh func_15013778 port_work/p80/3778.c $D/s3778.txt \
 's/if (r == 0) {/if (r == 1) {/' 's/blk.size = (f32) r + (f32) r;/blk.size = (f32) r;/' 's/inv = 1.0f \/ blk.size;/inv = 2.0f \/ blk.size;/' \
 's/blk.height = rec\[3\];/blk.height = rec[2];/' 's/blk.k1 = D_800969F0;/blk.k1 = D_800969F4;/' 's/blk.dir\[1\] \*= inv;//' \
 's/0, 0x17, (struct37/0, 0x18, (struct37/' 's/rec\[1\] + r, rec\[2\]/rec[1] - r, rec[2]/' 's/r \* 2, r \/ 2/r * 2, r \/ 4/' \
 's/0x2EE0/0x2EE1/' 's/NULL, 0, 8, 0);/NULL, 0, 9, 0);/' 's/blk.zero = 0.0f;/blk.zero = 1.0f;/' 's/0.0f, blk.size, 0.0f, \&blk/blk.size, 0.0f, 0.0f, \&blk/' \
 's/\*(f32 \*) (rec + 6), \*(f32 \*) (rec + 8), 0.0f);/*(f32 *) (rec + 8), *(f32 *) (rec + 6), 0.0f);/' 's/    r = rec\[4\];//' > $D/mut_3778.log 2>&1
echo DONE >> $D/mut_3778.log
