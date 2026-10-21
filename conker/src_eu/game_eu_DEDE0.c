#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150B15D0(struct127 *arg0) {
    s32 pad;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 temp_f0;
    f32 temp_f16;
    f32 temp_f0_2;
    f32 temp_f2;
    u16 temp_v1;

    arg0->unk174 = arg0->x_position;
    arg0->unk178 = arg0->z_position;
    arg0->immune = 0x64;
    arg0->unk40 = (f32) (s16) (arg0->unk7A + 0x4000) * 0.005493164f;
    if (func_1505A6F8(D_800CC2D0, arg0) < 1100.0f) {
        temp_f0 = func_1505A6F8(arg0, D_800CC2D0);
        temp_f16 = temp_f0;
        temp_f2 = arg0->y_position - D_800CC2D0->y_position;
        if (temp_f2 < 0.0f) {
            temp_f2 = 1000.0f;
        } else {
            temp_f2 = 1050.0f - (temp_f2 * 0.7f);
        }
        if ((temp_f0 < temp_f2) && (D_800CC2D0->in_water == 1)) {
            
            temp_f0_2 = 1100.0f - temp_f16;
            temp_v1 = func_1505A630(arg0->unk174 - D_800CC2D0->x_position, D_800CC2D0->z_position - arg0->unk178, 0);
            if (temp_f0_2 > 850.0f) {
                temp_f2 = (temp_f0_2 - 820.0f) * 0.09f;
                *D_800CC2E8 = D_800CC2D0->y_position - *D_800D1550 * (0, temp_f2);
            }
            func_1505A184(temp_v1 - 0x3000, (temp_f0_2 * 0.045f) + 5.0f, 0.0f, &sp50, &sp4C, &sp48);
            D_800CC2D0->unk164 = sp50;
            D_800CC2D0->unk168 = sp4C;
        }
    }
    func_1505E650(arg0, 0U, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}

#ifdef NON_MATCHING
extern f32 D_8009FC8C;
extern f32 D_8009FC90;
s32 func_15021834(struct127 *, s32, s32);
s32 func_15056B08(struct127 *);

void func_150B17DC(struct127 *arg0) {
    f32 var_f2;
    f32 var_f0;
    f32 temp_f2;
    f32 temp_f12;
    f32 temp_f0;
    s16 sp34;

    arg0->unk80 = 0xA;
    sp34 = arg0->unk76;
    temp_f0 = (f32) (*(s16 *)((u8 *)(D_800D2104[arg0->unk13F]) + 2));
    func_15058EA4(arg0, temp_f0, 1.0f, temp_f0, D_8009FC8C, 12.0f, -16.0f);
    func_15056B08(arg0);
    var_f2 = 6.0f;
    temp_f12 = arg0->unkC4;
    var_f0 = ((f32) (s16) ((sp34 - arg0->unk76) * 6) * 0.00390625f) - temp_f12;
    if (var_f0 > 6.0f) {
        goto block_3;
    }
    var_f2 = -6.0f;
    if (var_f0 < -6.0f) {
block_3:
        var_f0 = var_f2;
    }
    temp_f2 = arg0->unk148;
    arg0->unk148 = temp_f2 + ((var_f0 - temp_f2) * D_8009FC90);
    arg0->unkC4 = temp_f12 + arg0->unk148;
    arg0->unk40 = (f32) (s16) (arg0->unk7A + 0x4000) * 0.005493164f;
    func_15059140(arg0);
    if (func_150535F4(arg0) == 0) {
        func_15021834(arg0, 0, -1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DEDE0/func_150B17DC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DEDE0/func_150B1964.s")

#ifdef NON_MATCHING
s32 func_15056B08(struct127 *);
s32 func_1505A770(struct127 *);
u8 *func_1505EEB0(s32, s32 *);

void func_150B1CBC(struct127 *arg0) {
    struct {
        f32 u2C;
        f32 u30;
        f32 u34;
        u8 pad38[0x4];
        s32 u3C;
    } sp;
    f32 var_f12;
    u16 temp_v0;
    u8 temp_t9;
    u8 *temp_s0;

    temp_s0 = func_1505EEB0(0xA, &sp.u3C);
    func_15056B08(arg0);
    if (arg0->unk1E5 == 2) {
        arg0->x_position = (*(f32 *)((u8 *)temp_s0 + 0x14));
        arg0->z_position = (*(f32 *)((u8 *)temp_s0 + 0x1C));
        arg0->y_velocity = 0.0f;
        arg0->y_position = (*(f32 *)((u8 *)temp_s0 + 0x18)) + ((f32) ((s32) arg0->unk21C / 5) + 160.0f);
        arg0->unk7E = 0;
        arg0->gravity = -0.35f;
    } else {
        temp_t9 = arg0->unk7E;
        var_f12 = (f32) temp_t9;
        if ((s32) temp_t9 < 0) {
            var_f12 += 4294967296.0f;
        }
        (*(f32 *)((u8 *)temp_s0 + 0xB8)) = (f32) (func_150AD78C(var_f12 * 0.2f) * 6.0f);
        func_1505A770(arg0);
        (*(f32 *)((u8 *)temp_s0 + 0x18)) = (f32) (arg0->y_position - 170.0f);
        (*(s8 *)((u8 *)temp_s0 + 0x13C)) = (s8) (D_800C3E78 + 0x64);
        func_1505A184((*(u16 *)((u8 *)temp_s0 + 0x7A)), (*(f32 *)((u8 *)temp_s0 + 0xB8)) * -7.0f, 0.0f, &sp.u34, &sp.u30, &sp.u2C);
        (*(f32 *)((u8 *)temp_s0 + 0x14)) = (f32) (arg0->x_position + sp.u34);
        (*(f32 *)((u8 *)temp_s0 + 0x1C)) = (f32) (arg0->z_position + sp.u30);
        (*(u16 *)((u8 *)temp_s0 + 0x7A)) = (u16) ((*(u16 *)((u8 *)temp_s0 + 0x7A)) + (D_800BE9A0 << 8));
        arg0->unk7E += D_800BE9A0;
        (*(s8 *)((u8 *)temp_s0 + 0xAD)) = 0;
        (*(f32 *)((u8 *)temp_s0 + 0x3C)) = 0.0f;
        (*(f32 *)((u8 *)temp_s0 + 0x16C)) = 0.0f;
        (*(f32 *)((u8 *)temp_s0 + 0x170)) = 0.0f;
    }
    temp_v0 = func_1505A630(D_800CC2D0->x_position - arg0->x_position, arg0->z_position - D_800CC2D0->z_position, 0);
    arg0->unk7A = temp_v0;
    arg0->unk40 = (f32) (s16) (temp_v0 + 0x4000) * 0.005493164f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DEDE0/func_150B1CBC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DEDE0/func_150B1EC0.s")
