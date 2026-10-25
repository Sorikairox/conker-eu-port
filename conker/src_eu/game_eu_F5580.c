#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15116A8C(s32, s32, s32, f32);
void func_150C7D70(s32 arg0) {
    if (!((*(u8 *)((u8 *)D_800D2E4C + 0xA)) & 8)) {
        if (!(D_800DBEF4->pad70[3] & 4)) {
            func_15116A8C(arg0, 1, 0x353, 1000.0f);
            return;
        }
        func_15116A8C(arg0, 1, 0x43, 400.0f);
    }
}

void func_1511563C(u8 *);
void func_150C7DE0(u8 *arg0) {
    u8 *p;
    if (!(arg0[0x73] & 4)) {
        p = (u8 *)D_800DBEF4;
        p += 0x1E1;  // fakematch: keeps the dead addiu (p += K+1; p--;)
        p--;  // fakematch: pairs with p += K+1
        *(s32 *)(arg0 + 0x3C) = -(*(s32 *)(p + 0x3C) & 0xFFFF0000) & 0xFFFF0000;
        func_1511563C(arg0);
    }
}

void func_150C7E30(u8 *arg0) {
    u8 *p;
    p = (u8 *)D_800DBEF4;
    p += 0x1E1;  // fakematch: keeps the dead addiu (p += K+1; p--;)
    p--;  // fakematch: pairs with p += K+1
    *(s32 *)(arg0 + 0x3C) = *(s32 *)(p + 0x3C) & 0xFFFF0000;
    func_1511563C(arg0);
}

#ifdef NON_MATCHING
void func_15116690(u8 *obj);
// obj_shade_from_level: P237. Object callback (same family as func_150C7DE0 / func_150C7E30): runs func_15116690(obj),
// then, unless the object's +0x73 bit 2 is set, gives its model record (+0x7C, when there is one) the shade byte
// +0x13 = the level block's (D_800DBEF4) s16 +0x21C / 16.
void func_150C7E68(u8 *obj) {
    u8 *rec;

    func_15116690(obj);
    if (!(obj[0x73] & 4)) {
        rec = *(u8 **) (obj + 0x7C);
        if (rec != NULL) {
            rec[0x13] = *(s16 *) ((u8 *) D_800DBEF4 + 0x21C) >> 4;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F5580/func_150C7E68.s")
#endif

#ifdef NON_MATCHING
void func_1000D96C(s32, s32, s32);
void func_1000DE1C(s32, s32);
f32 func_150489B0(s32);
void func_1517A550(s32, s16, s32, s16, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_80088B94;

void func_150C7EBC(s32 arg0) {
    u8 sp4B;
    s32 sp44;                                       /* compiler-managed */
    f32 temp_f18;
    f32 temp_f2;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s1_3;
    s32 var_a1;
    struct108 *temp_v0;
    u32 temp_s1_2;
    u8 temp_v0_2;

    sp44 = arg0 * 0x9A0;
    temp_v0 = &D_800DBFF0[arg0];
    var_a1 = (s32) temp_v0->unk2FC;
    temp_s0 = (s32) temp_v0->unk2F8 + 0x972;
    temp_s1 = (s32) temp_v0->unk300 - 0x6EF;
    if (((var_a1 - 0x9C4) >= -0xC7) && (((temp_s0 * temp_s0) + (temp_s1 * temp_s1)) < 0x15F900)) {
        if (D_80088B94 == 0) {
            func_1000D96C(0x5F, 0xF, 6);
            func_1000DE1C(0x10, 4);
            D_80088B94 = 1;
            var_a1 = (s32) (*(f32 *)((u8 *)((D_800DBFF0 + sp44)) + 0x2FC));
        }
    } else if (D_80088B94 != 0) {
        func_1000D96C(0xF, 0x5F, 4);
        func_1000D96C(0x10, 0, 3);
        D_80088B94 = 0;
        var_a1 = (s32) (*(f32 *)((u8 *)((D_800DBFF0 + sp44)) + 0x2FC));
    }
    if (((var_a1 - 0x62F) < 0) && (((temp_s0 * temp_s0) + (temp_s1 * temp_s1)) < 0xC5C10) && ((u32) (func_150ADA20() & 0xFFFF) < 0x2000U)) {
        temp_s1_2 = func_150ADA20() % 900U;
        temp_v0_2 = func_150ADA20();
        sp4B = temp_v0_2;
        temp_f2 = (f32) temp_s1_2;
        temp_f18 = func_150489B0(temp_v0_2 & 0xFF) * temp_f2;
        sp44 = temp_f2;
        temp_s1_3 = (s32) ((func_15048A40(sp4B) * temp_f2) + 1775.0f);
        func_1517A550((s32) ((f32) ((func_150ADA20() & 0xFFFF) * 2) * 0.000015258789f) & 0xFF, (s16) (s32) (temp_f18 + -2418.0f), 0x62F, (s16) temp_s1_3, 7, 0x4B0, 0x25, 0xA, 0x1E, 3, 8);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F5580/func_150C7EBC.s")
#endif
#ifdef NON_MATCHING
u8 *func_151149AC(u8 id); /* P119: one argument (world_record_find reads only the id) */

void func_150C8190(u8 *arg0) {
    s32 *sp18;
    s32 *temp_a1_2;
    s32 temp_t0;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    s8 *temp_a1;

    var_v1 = (*(s32 *)((u8 *)arg0 + 0x7C));
    if (var_v1 == 0) {
        temp_a1 = (*(s8 **)((u8 *)arg0 + 0x1C));
        var_v0 = 0;
        if (*temp_a1 != -0xE) {
            do {
                var_v0 += 1;
            } while (*((var_v0 * 8) + temp_a1) != -0xE);
        }
        (*(s32 *)((u8 *)arg0 + 0x7C)) = var_v0;
        var_v1 = var_v0;
    }
    temp_a1_2 = (*(s8 **)((u8 *)arg0 + 0x1C)) + (var_v1 * 8);
    sp18 = temp_a1_2;
    var_v1_2 = -0x29D - (*(s16 *)((u8 *)(func_151149AC((*(s32 *)((u8 *)arg0 + 0x3C)) & 0xFF)) + 0x12));
    if ((*(s32 *)((u8 *)arg0 + 0x3C)) & 0x8000) {
        var_v1_2 = 0x344 - var_v1_2;
    }
    if (var_v1_2 < 0) {
        do {
            var_v1_2 += 0x400;
        } while (var_v1_2 < 0);
    }
    if (var_v1_2 >= 0x400) {
        do {
            var_v1_2 -= 0x400;
        } while (var_v1_2 >= 0x400);
    }
    temp_t0 = *temp_a1_2 & ~0xFFF;
    *temp_a1_2 = temp_t0;
    *temp_a1_2 = temp_t0 | var_v1_2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F5580/func_150C8190.s")
#endif
void func_150C827C(u8 *arg0) {
    struct127 *temp_v0;

    temp_v0 = func_15083E90(0xC);
    (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) (s32) (temp_v0->x_position - 30.0f);
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) (temp_v0->y_position + 50.0f);
    (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) (s32) (temp_v0->z_position + 30.0f);
}
