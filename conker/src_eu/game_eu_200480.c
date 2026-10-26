#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_151D2C70 */
void scroll_banner_spawn(s16 arg0) {
    u8 *temp_v0;

    temp_v0 = node_alloc(0x3C, 1, 0x18, 0, 0xFFU, 1U);
    (*(s16 *)((u8 *)temp_v0 + 0x14)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x12)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0xE)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x16)) = 1;
    (*(s16 *)((u8 *)temp_v0 + 0x10)) = arg0;
}

/* was func_151D2CC8 */
void scroll_banner_stop(s16 arg0) {
    u8 *var_v0;

    for (var_v0 = D_800DD510; var_v0 != NULL; var_v0 = *(u8 **)(var_v0 + 8)) {
        if (arg0 == *(s16 *)(var_v0 + 0x10)) {
            *(s8 *)(var_v0 + 0x16) = -2;
        }
    }
}

typedef struct {
    u8 pad0[0xE];
    s16 xE;
    s16 x10;
    s16 x12;
    s16 x14;
    s8 x16;
} Obj2D0C;

/* was func_151D2D0C */
void scroll_banner_update(Obj2D0C *arg0) {
    arg0->xE += D_800BE9E4 * arg0->x16;
    if (arg0->x16 > 0 && arg0->xE >= 0xED) {
        arg0->x14 = (0x128 - arg0->xE) << 2;
        if (arg0->x14 < 0) {
            arg0->x14 = 0;
        }
    } else {
        arg0->x14 = arg0->xE * 2;
    }
    if (arg0->x14 >= 0x80) {
        arg0->x14 = 0x80;
    }
    arg0->x12++;
    if (arg0->x12 >= 0x100) {
        arg0->x12 -= 0x100;
    }
    if (arg0->xE >= 0x12D || arg0->xE < 0) {
        node_destroy((struct102 *)arg0);
    }
}

#ifdef NON_MATCHING
s32 texture_cache_lookup(s32 *, s32, s32, s32);
extern s32 D_A4A;

/* was func_151D2DE0 */
u8 *scroll_banner_draw(u8 *arg0, u8 *arg1, s16 arg2) {
    s32 temp_v0;
    u8 *temp_s0;
    u8 *temp_s0_10;
    u8 *temp_s0_11;
    u8 *temp_s0_12;
    u8 *temp_s0_13;
    u8 *temp_s0_14;
    u8 *temp_s0_15;
    u8 *temp_s0_16;
    u8 *temp_s0_17;
    u8 *temp_s0_18;
    u8 *temp_s0_19;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *temp_s0_7;
    u8 *temp_s0_8;
    u8 *temp_s0_9;
    u8 *var_s0;

    var_s0 = arg0;
    if ((arg2 != (*(s16 *)((u8 *)arg1 + 0x10))) || ((*(s16 *)((u8 *)arg1 + 0x14)) == 0)) {

    } else {
        (*(s32 *)((u8 *)var_s0 + 4)) = -1;
        temp_s0 = var_s0 + 8;
        (*(s32 *)((u8 *)var_s0 + 0)) = 0xD7000002;
        (*(s32 *)((u8 *)temp_s0 + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)temp_s0 + 4)) = 0;
        temp_s0_2 = temp_s0 + 8;
        (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0xFC12D225;
        (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0xFFA7FFFF;
        temp_s0_3 = temp_s0_2 + 8;
        (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0xEF002C3F;
        (*(s32 *)((u8 *)temp_s0_3 + 4)) = 0x504244;
        temp_s0_4 = temp_s0_3 + 8;
        temp_v0 = texture_cache_lookup(&D_A4A, 0, 3, 0);
        (*(s32 *)((u8 *)temp_s0_4 + 0)) = 0xFD700000;
        (*(s32 *)((u8 *)temp_s0_4 + 4)) = temp_v0;
        temp_s0_5 = temp_s0_4 + 8;
        (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xF5700000;
        (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0x07018060;
        temp_s0_6 = temp_s0_5 + 8;
        (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xE6000000;
        (*(s32 *)((u8 *)temp_s0_6 + 4)) = 0;
        temp_s0_7 = temp_s0_6 + 8;
        (*(s32 *)((u8 *)temp_s0_7 + 0)) = 0xF3000000;
        (*(s32 *)((u8 *)temp_s0_7 + 4)) = 0x077FF000;
        temp_s0_8 = temp_s0_7 + 8;
        (*(s32 *)((u8 *)temp_s0_8 + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)temp_s0_8 + 4)) = 0;
        temp_s0_9 = temp_s0_8 + 8;
        (*(s32 *)((u8 *)temp_s0_9 + 0)) = 0xF5681000;
        (*(s32 *)((u8 *)temp_s0_9 + 4)) = 0x18060;
        temp_s0_10 = temp_s0_9 + 8;
        (*(s32 *)((u8 *)temp_s0_10 + 0)) = 0xF2000000;
        (*(s32 *)((u8 *)temp_s0_10 + 4)) = 0xFC0FC;
        temp_s0_11 = temp_s0_10 + 8;
        (*(s32 *)((u8 *)temp_s0_11 + 0)) = 0xFB000000;
        temp_s0_12 = temp_s0_11 + 8;
        (*(s32 *)((u8 *)temp_s0_11 + 4)) = (s32) (((*(s16 *)((u8 *)arg1 + 0x14)) & 0xFF) | 0xFF0000);
        (*(s32 *)((u8 *)temp_s0_12 + 0)) = 0xE45003C0;
        (*(s32 *)((u8 *)temp_s0_12 + 4)) = 0;
        temp_s0_13 = temp_s0_12 + 8;
        (*(s32 *)((u8 *)temp_s0_13 + 0)) = 0xE1000000;
        temp_s0_14 = temp_s0_13 + 8;
        (*(s32 *)((u8 *)temp_s0_13 + 4)) = (s32) (((*(s16 *)((u8 *)arg1 + 0x12)) << 0x13) | 0x400);
        (*(s32 *)((u8 *)temp_s0_14 + 4)) = 0x04000400;
        (*(s32 *)((u8 *)temp_s0_14 + 0)) = 0xF1000000;
        temp_s0_15 = temp_s0_14 + 8;
        (*(s32 *)((u8 *)temp_s0_15 + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)temp_s0_15 + 4)) = 0;
        temp_s0_16 = temp_s0_15 + 8;
        (*(s32 *)((u8 *)temp_s0_16 + 0)) = 0xFB000000;
        temp_s0_17 = temp_s0_16 + 8;
        (*(s32 *)((u8 *)temp_s0_16 + 4)) = (s32) ((((s16) (*(s16 *)((u8 *)arg1 + 0x14)) >> 1) & 0xFF) | 0xFF000000);
        (*(s32 *)((u8 *)temp_s0_17 + 0)) = 0xE45003C0;
        (*(s32 *)((u8 *)temp_s0_17 + 4)) = 0;
        temp_s0_18 = temp_s0_17 + 8;
        (*(s32 *)((u8 *)temp_s0_18 + 0)) = 0xE1000000;
        temp_s0_19 = temp_s0_18 + 8;
        (*(s32 *)((u8 *)temp_s0_18 + 4)) = (s32) ((*(s16 *)((u8 *)arg1 + 0x12)) << 0x13);
        (*(s32 *)((u8 *)temp_s0_19 + 4)) = 0x02000200;
        var_s0 = temp_s0_19 + 8;
        (*(s32 *)((u8 *)temp_s0_19 + 0)) = 0xF1000000;
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_200480/scroll_banner_draw.s")
#endif