#!/bin/bash
# P76: func_15037CCC mutants on s7ccc.txt (mutfast.sh, stops at the first DIFFER)
D=/Users/sorikairo/conker-wt/port/docs/port/sessions/p76
$D/mutfast.sh func_15037CCC port_work/p76/7ccc.c $D/s7ccc.txt \
 's/(ext + 0x2C) == 0x100/(ext + 0x2C) == 0x101/' \
 's/out\[1\] = \*(f32 \*) (ext + 0x744)/out[1] = *(f32 *) (ext + 0x748)/' \
 's/if (id == 0 \&\& /if (id == 1 \&\& /' \
 's/other\[5\] == 5/other[5] == 4/' \
 's/best != 1.6e9f/best != 1.0e9f/' \
 's/D_80084790 >= D_800C6A74/D_80084790 > D_800C6A74/' \
 's/sx < lp->xMax/sx <= lp->xMax/' \
 's/lp->y + 50.0f/lp->y + 40.0f/' \
 's/d2 < (f32) lp->range2/d2 < (f32) (s32) lp->range2/' \
 's/idx == 25 || idx == 72/idx == 25 || idx == 71/' \
 's/d2 < 250000.0f/d2 < 25000.0f/' \
 's/found = 3;/found = 1;/' \
 's/objRet - 1);/objRet);/' \
 's/ \&\& D_800C6A70\[bestPoint\].anim != 0//' \
 's/lp->unk6 == 0/(lp->unk6 \& 1) == 0/' \
 's/pt\[0\] = \*(f32 \*) (node + 0x98)/pt[0] = *(f32 *) (node + 0x9C)/' \
 's/dx = (f32) sx - lp->x;/dx = *(f32 *) (self + 0x14) - lp->x;/' \
 's/(node + 0x66) != 0/(node + 0x64) != 0/' \
 's/            D_80084790 = bestPoint;//' \
 's/if (func_15037B70(id, (u8 \*) out) != 0)/if (func_15037B70(id, (u8 *) out) == 2)/'
