#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} struct_eu_158110;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512A390.s")

#ifdef NON_MATCHING
extern s16 D_80089930[4][4];      /* default viewport rects (x, y, w, h?) for slots 0..3 */
extern s16 D_800DC630[4][4][4];   /* per player count: the viewport rects */
extern u8 D_800DC4F0[];

/* Camera tables reset: copy the 4 default viewport rects into each of the 4 per-player-count tables, halving the
 * first two halfwords in split screen (1..3 extra players) and scaling them by 0.75 on levels 0x1B / 0x1E; clear D_800DC4F0. */
void func_1512B168(void) {
    u8 i, j;
    s16 *r;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            r = D_800DC630[i][j];
            r[0] = D_80089930[j][0];
            r[1] = D_80089930[j][1];
            r[2] = D_80089930[j][2];
            r[3] = D_80089930[j][3];
            if (D_80082FA0 > 0 && D_80082FA0 < 4) {
                r[0] = (s32)(r[0] * 0.5f);
                r[1] = (s32)(r[1] * 0.5f);
            }
            if (D_800BE9F0 == 0x1B || D_800BE9F0 == 0x1E) {
                r[0] = (s32)(r[0] * 0.75f);
                r[1] = (s32)(r[1] * 0.75f);
            }
        }
    }
    bzero(D_800DC4F0, 0x130);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B168.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B2C4.s")

s32 func_1512B2C4();

void func_1512B670(u8 *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x2C));
    if ((temp_v0 & ~0x100) && (D_800BEAC0 == 0) && (D_800C3671 == 0)) {
        if (temp_v0 != 0x40) {
            temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x84));
            if ((temp_v0_2 & 8) && !(temp_v0_2 & 0x200) && ((*(u8 *)((u8 *)arg0 + 0x23C)) == 0)) {
                temp_v0_3 = (*(s32 *)((u8 *)arg0 + 0x5F0));
                if (!(temp_v0_3 & 0x80) && !(temp_v0_3 & 0x40)) {
                    func_1512B2C4();
                    return;
                }
            }
        }
        (*(s16 *)((u8 *)arg0 + 0x5F8)) = 1;
        (*(s16 *)((u8 *)arg0 + 0x5FC)) = 2;
        (*(s16 *)((u8 *)arg0 + 0x5FE)) = 0x32;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B728.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512BAAC.s")

void func_1512BB6C(struct_eu_158110 *arg0, s32 arg1, s32 arg2) {
    arg0->unk2 = arg0->unk1;
    if (arg0->unk4 < arg1) {
        arg0->unk1 = 0;
    } else {
        arg0->unk1 = 1;
    }
    arg0->unk8 = arg2;
    arg0->unk4 = arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512BBA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512BCA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C080.s")

void func_15123A54(u8 *);
s32 func_1512C6C0(u8 *);

void func_1512C5D8(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    f32 var_f14;
    s32 temp_v0;

    if ((*(f32 *)((u8 *)arg0 + 0x390)) < 180.0f) {
        var_f14 = 2.0f;
    } else {
        var_f14 = -2.0f;
    }
    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x2C));
    if ((temp_v0 != 0x80) && (temp_v0 != 0x40)) {
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x2F8)) - (*(f32 *)((u8 *)arg0 + 0x2BC));
        temp_f12 = (*(f32 *)((u8 *)arg0 + 0x300)) - (*(f32 *)((u8 *)arg0 + 0x2C4));
        temp_f0 = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
        (*(f32 *)((u8 *)arg0 + 0x370)) = temp_f0;
        if (temp_f0 < 42.0f) {
            (*(f32 *)((u8 *)arg0 + 0x384)) = (*(f32 *)((u8 *)arg0 + 0x37C)) - 45.0f * var_f14;
            (*(f32 *)((u8 *)arg0 + 0x5CC)) = 0.0f;
            func_15123A54(arg0);
            (*(s32 *)((u8 *)arg0 + 0x240)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x240)) | 2);
        }
    }
    func_1512C6C0(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C6C0.s")

void func_1512C770(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C77C.s")

s32 func_1512C9EC(s32 arg0) {
    return 1;
}
