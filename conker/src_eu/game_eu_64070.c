#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64070/func_15036860.s")

#ifdef NON_MATCHING
u8 * func_15031C4C(u8 *arg0, s32 arg1, s32 arg2);
s32 func_15036860(s32, struct254 **, u8 *, s32);
u8 * func_1515EAB4(u8 *, s32, u8, u8, u8 *);
extern s32 D_800846E0;
extern s32 D_8009076C;

u8 *func_15036BB4(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *sp78;
    struct222 **sp3C;
    u8 *sp38;
    s32 temp_t2;
    s32 temp_v0_4;
    struct127 *temp_s0;
    struct222 **temp_t0;
    struct255 *temp_v0_5;
    u8 *temp_a2;
    u8 temp_v0_2;
    u8 *temp_v0;
    u8 *temp_v0_3;
    u8 *temp_v0_6;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *var_s1;

    temp_s0 = &D_800CC2D0[arg1];
    temp_v0_2 = temp_s0->unk31C->unk75;
    if ((temp_v0_2 != 2) && (temp_v0_2 != 0x13)) {
        return arg0;
    }
    temp_v0_3 = func_15031C4C((u8 *) temp_s0, 8, 0);   /* the callee never reads a3 */
    sp78 = temp_v0_3;
    if (temp_v0_3 == NULL) {
        return arg0;
    }
    if (arg1 > 0) {
        return arg0;
    }
    temp_v1 = (*(u8 **)((u8 *)((temp_v0_3 + (D_800BE9C0 * 4))) + 0x28));
    temp_t0 = &(&D_800C3FC0)[arg1];
    temp_v0_4 = 1 * 0x10;
    (*(u8 *)((u8 *)(*temp_t0) + 0xC)) = (u8) (*(u8 *)((u8 *)temp_v1 + 0x30C));
    temp_v1_2 = temp_v1 + 0x300;
    (*(u8 *)((u8 *)(*temp_t0) + 0xD)) = (u8) (*(u8 *)((u8 *)temp_v1 + 0x30D));
    (*(u8 *)((u8 *)(*temp_t0) + 0xE)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xE));
    (*(u8 *)((u8 *)((*temp_t0 + temp_v0_4)) + 0xC)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xC));
    (*(u8 *)((u8 *)((*temp_t0 + temp_v0_4)) + 0xD)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xD));
    (*(u8 *)((u8 *)((*temp_t0 + temp_v0_4)) + 0xE)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xE));
    (*(u8 *)((u8 *)((*temp_t0 + temp_v0_4)) + 0x1C)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xC));
    (*(u8 *)((u8 *)((*temp_t0 + temp_v0_4)) + 0x1D)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xD));
    (*(u8 *)((u8 *)((*temp_t0 + temp_v0_4)) + 0x1E)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xE));
    (*(u8 *)((u8 *)((*temp_t0 + temp_v0_4)) + 0x2C)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xC));
    (*(u8 *)((u8 *)((*temp_t0 + temp_v0_4)) + 0x2D)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xD));
    (*(u8 *)((u8 *)((*temp_t0 + temp_v0_4)) + 0x2E)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xE));
    (*(u8 *)((u8 *)((*temp_t0 + temp_v0_4)) + 0x3C)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xC));
    (*(u8 *)((u8 *)((*temp_t0 + temp_v0_4)) + 0x3D)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xD));
    (*(u8 *)((u8 *)((*temp_t0 + temp_v0_4)) + 0x3E)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xE));
    temp_v0_5 = temp_s0->unk1D4;
    if (temp_v0_5 == NULL) {
        return arg0;
    }
    temp_a2 = &temp_v0_5->pad0[0x100];
    sp38 = temp_a2;
    sp3C = temp_t0;
    func_15036860(arg1, &temp_v0_5->unk240, temp_a2, arg1);
    (*(s32 *)((u8 *)arg0 + 0)) = 0xDE000000;
    (*(s32 **)((u8 *)arg0 + 4)) = &D_800846E0;
    temp_v0_6 = func_1515EAB4(arg0 + 8, (*(s32 *)((u8 *)((temp_s0 + (arg2 * 4))) + 0x304)), temp_s0->unk301, temp_s0->unk302, temp_s0->unk314 + (D_800BE9C0 * 8));
    temp_t2 = temp_s0->unk66 & 0xC;
    if (temp_t2 == 0xC) {
        (*(s32 *)((u8 *)temp_v0_6 + 0)) = 0xD9FDFFFF;
        var_s1 = temp_v0_6 + 8;
        (*(s32 *)((u8 *)temp_v0_6 + 4)) = 0;
    } else if ((temp_t2 != 8) && (var_s1 = temp_v0_6 + 8, (((*(u8 *)((u8 *)sp78 + 4)) & 1) == 0))) {
        (*(s32 *)((u8 *)temp_v0_6 + 0)) = 0xD9FDFFFF;
        (*(s32 *)((u8 *)temp_v0_6 + 4)) = 0;
    } else {
        var_s1 = temp_v0_6 + 8;
        if (D_800DCD7C != 0) {
            (*(s32 *)((u8 *)temp_v0_6 + 4)) = 0x20000;
            (*(s32 *)((u8 *)temp_v0_6 + 0)) = 0xD9FFFFFF;
            var_s1 = temp_v0_6 + 8;
        } else {
            (*(s32 *)((u8 *)temp_v0_6 + 0)) = 0xD9FDFFFF;
            (*(s32 *)((u8 *)temp_v0_6 + 4)) = 0;
        }
    }
    sp3C = temp_t0;
    temp_v0 = func_15095380(var_s1, &D_8009076C, 0, 0, 0, 0, 0, 2, 3);
    (*(u8 **)((u8 *)temp_v0 + 4)) = D_80089810;
    (*(s32 *)((u8 *)temp_v0 + 0)) = 0xDA380003;
    (*(s32 *)((u8 *)temp_v0 + 8)) = 0x01001002;
    (*(struct222 **)((u8 *)temp_v0 + 0xC)) = (struct222 *) *temp_t0;
    (*(s32 *)((u8 *)temp_v0 + 0x10)) = 0xDA380003;
    (*(u8 **)((u8 *)temp_v0 + 0x14)) = sp38;
    (*(s32 *)((u8 *)temp_v0 + 0x18)) = 0x0100400A;
    (*(struct222 **)((u8 *)temp_v0 + 0x1C)) = (struct222 *) (*temp_t0 + 0x10);
    (*(s32 *)((u8 *)temp_v0 + 0x20)) = 0x05000204;
    (*(s32 *)((u8 *)temp_v0 + 0x24)) = 0;
    (*(s32 *)((u8 *)temp_v0 + 0x28)) = 0x05000608;
    (*(s32 *)((u8 *)temp_v0 + 0x2C)) = 0;
    return temp_v0 + 0x30;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64070/func_15036BB4.s")
#endif