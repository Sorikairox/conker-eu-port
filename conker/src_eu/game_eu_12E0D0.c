#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E0D0/func_151008C0.s")

#ifdef NON_MATCHING
extern s32 D_800906D4[]; /* asset ids: 3 animated frames, then the 5 segment textures' variants */
extern u8 D_800DD835;
s32 func_1510D66C(s32, s32 *, s32, s32);

// sky_segments_set: points RSP segments 2 / 3 at two consecutive frames of a 3-frame animation (D_800DD835 / 4)
// and segments 4..8 at the assets picked by D_800BE500[0..4] (func_1510D66C, mode 3). Returns the advanced DL.
Gfx *func_151009E4(Gfx *gdl) {
    s32 size;
    s32 addr;
    s32 frame;
    s32 seg;
    s32 i;

    frame = D_800DD835 >> 2;
    addr = func_1510D66C(D_800906D4[frame % 3], &size, 3, 0);
    gdl->words.w0 = 0xDB060008;
    gdl->words.w1 = addr;
    gdl++;
    addr = func_1510D66C(D_800906D4[(frame + 1) % 3], &size, 3, 0);
    gdl->words.w0 = 0xDB06000C;
    gdl->words.w1 = addr;
    gdl++;
    for (i = 0, seg = 0x10; seg != 0x24; i++, seg += 4) {
        addr = func_1510D66C(D_800906D4[3 + D_800BE500[i]], &size, 3, 0);
        gdl->words.w0 = 0xDB060000 | (seg & 0xFFFF);
        gdl->words.w1 = addr;
        gdl++;
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E0D0/func_151009E4.s")
#endif
