#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P241: readable C for func_151008C0 (game_eu_12E0D0, 73 insns). */
// sky_segments_flicker: level update handler (D_8008D0A4 entry 10, `void (s32)`; does nothing for a non-zero
// argument): advances the sky animation frame D_800DD835 and toggles each of the 5 sky segment variants
// D_800BE500[i] with chance 35 / 1000 (70 / 1000 while it is on). A segment that turns on gets command 0x18 for
// its id (D_80088F60 = 9..13, light_ctrl_broadcast), one that turns off gets 0x1C then 0x17. func_150ADA20 is the random
// number generator.
typedef struct {
    u8 id[5];
} SkyIds_151008C0;
extern SkyIds_151008C0 D_80088F60;
extern u8 D_800DD835;
void light_ctrl_broadcast(u8, u8, s32);
void func_151008C0(s32 arg0) {
    SkyIds_151008C0 ids = D_80088F60;
    s32 i;
    u32 chance;

    if (arg0 != 0) {
        return;
    }
    D_800DD835++;
    for (i = 0; i < 5; i++) {
        chance = (D_800BE500[i] != 0) ? 70 : 35;
        if ((u32) func_150ADA20() % 1000 < chance) {
            D_800BE500[i] ^= 1;
            if (D_800BE500[i] != 0) {
                light_ctrl_broadcast(ids.id[i], 0x18, 0);
            } else {
                light_ctrl_broadcast(ids.id[i], 0x1C, 0);
                light_ctrl_broadcast(ids.id[i], 0x17, 0);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E0D0/func_151008C0.s")
#endif

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
