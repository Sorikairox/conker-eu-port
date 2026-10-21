#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 (*D_800D3040)[4];
s32 func_15094DAC(s32, u8 **);
void func_15094CD0(s32 arg0, u8 *arg1) {
    u8 *sp50[16];
    u8 *v;
    u8 *p;
    s32 i;
    func_15094DAC(arg0, sp50);
    for (i = 0; i < 16; i++) {
        p = sp50[i];
        if (p != NULL) {
            v = arg1 + i * 0xC;
            func_150A7E40(D_800D3040, (f32) *(s16 *)(p + 0), (f32) *(s16 *)(p + 2), (f32) *(s16 *)(p + 4), (f32 *)v, (f32 *)(v + 4), (f32 *)(v + 8));
        }
    }
}

#ifdef NON_MATCHING
s32 func_15094DAC(s32 arg0, u8 **arg1) {
    s32 *temp_v0;
    s16 temp_a2;
    s16 temp_v1_2;
    s16 var_a3_2;
    s32 temp_t1;
    s32 temp_t6;
    s32 var_a3;
    u8 **var_a0;
    u8 **var_a0_2;
    u8 **var_a0_3;
    u8 **var_a0_4;
    u8 **var_a0_5;
    u8 *var_v0;
    u8 temp_v1;
    u8 *temp_v0_2;

    temp_v1 = (*(u8 *)((u8 *)arg0 + 1));
    var_v0 = (*(u8 **)((u8 *)arg0 + 4));
    var_a3 = 0;
    temp_a2 = temp_v1 & 0xF;
    temp_v1_2 = ((s32) temp_v1 >> 4) + 1;
    if (temp_a2 > 0) {
        temp_t1 = temp_a2 & 3;
        if (temp_t1 != 0) {
            var_a0 = &arg1[0];
            do {
                var_a3 += 1;
                *var_a0 = NULL;
                var_a0 = (u8 * *)((u8 *)var_a0 + (4));
            } while (temp_t1 != var_a3);
            if (var_a3 != temp_a2) {
                goto block_5;
            }
        } else {
block_5:
            var_a0_2 = &arg1[var_a3];
            do {
                var_a0_2 = (u8 * *)((u8 *)var_a0_2 + (0x10));
                (*(s32 *)((u8 *)var_a0_2 + -0xC)) = 0;
                (*(s32 *)((u8 *)var_a0_2 + -8)) = 0;
                (*(s32 *)((u8 *)var_a0_2 + -4)) = 0;
                (*(s32 *)((u8 *)var_a0_2 + -0x10)) = 0;
            } while (var_a0_2 != &arg1[temp_a2]);
        }
    }
    var_a3_2 = temp_a2;
    if (temp_a2 < temp_v1_2) {
        temp_t6 = (temp_v1_2 - temp_a2) & 3;
        if (temp_t6 != 0) {
            var_a0_3 = &arg1[temp_a2];
            do {
                *var_a0_3 = var_v0;
                var_a3_2 += 1;
                var_v0 += 0x10;
                var_a0_3 = (u8 * *)((u8 *)var_a0_3 + (4));
            } while ((temp_t6 + temp_a2) != var_a3_2);
            if (var_a3_2 != temp_v1_2) {
                goto block_12;
            }
        } else {
block_12:
            var_a0_4 = &arg1[var_a3_2];
            do {
                (*(u8 **)((u8 *)var_a0_4 + 0)) = var_v0;
                (*(u8 **)((u8 *)var_a0_4 + 4)) = (u8 *) (var_v0 + 0x10);
                temp_v0 = &(*(s32 *)((u8 *)(&var_v0[0x10]) + 0x10));
                (*(s32 **)((u8 *)var_a0_4 + 8)) = temp_v0;
                temp_v0_2 = ((s32 *)((u8 *)temp_v0 + 0x10));
                (*(u8 **)((u8 *)var_a0_4 + 0xC)) = temp_v0_2;
                var_a3_2 += 4;
                var_v0 = temp_v0_2 + 0x10;
                var_a0_4 = (u8 * *)((u8 *)var_a0_4 + (0x10));
            } while (var_a3_2 != temp_v1_2);
        }
    }
    if (var_a3_2 < 0x10) {
        var_a0_5 = &arg1[var_a3_2];
        do {
            var_a3_2 += 1;
            var_a0_5 = (u8 * *)((u8 *)var_a0_5 + (4));
            (*(s32 *)((u8 *)var_a0_5 + -4)) = 0;
        } while (var_a3_2 < 0x10);
    }
    return (s32) var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C24E0/func_15094DAC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C24E0/func_15094EC8.s")

extern Mtx *D_800DC6D0[];
extern f32 D_800D30C8[][4][4];
void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

void func_150952B0(s32 arg0) {
    f32 a[4][4];
    f32 b[4][4];

    guMtxL2F(a, &D_800DC6D0[D_800BE9C0][arg0]);
    guMtxL2F(b, &((Mtx *)((u8 *)&((struct_eu_BE628 *)D_800BE628)[arg0] + 0x100))[D_800BE9C0]);
    func_150A7A48(a, b, D_800D30C8[arg0]);
}
