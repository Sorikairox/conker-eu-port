#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15017790(void) {
    func_1509C120();
    bzero(D_800D2E4C, 0x1B);
    bzero(&D_800D2E50, 0x10);
    bzero(&D_800D2E60, 9);
    bzero(&D_800D2E70, 0xCC);
    D_800D2E44 = (u8)0;
}

void func_150177F8(void) {
    func_1509BA04(1);
    bzero(&D_800D2F48, 0xC);
    func_150A00F0();
    D_800D2DB0 = D_800968C0;
    D_800D2E41 = 0xA;
    D_800D2E42 = 6;
    D_800D3858 = 0;
    D_800D2E44 = 0;
}

void func_15017868(void) {
    u16 *temp_v0;
    s32 i;

    for (i = 0; i < D_800D2F3C; i++) {
        temp_v0 = func_1509B704((s16)D_800D2F40[i]);
        if ((temp_v0 != 0) && ((temp_v0[0] & 0x1000) != 0)) {
            temp_v0[1] = D_800BE9F0;
        }

    }
    func_1509BA04(0);
    func_1509B4A0(*(((s16*)&D_800BE9F0)+1), 1); // er?
}

#ifdef NON_MATCHING
u8 **allocate_memory(s32, s32, s32, s32);
s32 func_15017B20(u8 *, u32);
extern s32 D_800D34F0;
extern s32 D_800D3510;
extern u8 **D_800D3690;
extern s32 D_800D3694;

void func_15017930(s32 arg0) {
    s32 temp_t9;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    u32 temp_lo;
    u32 temp_v0;
    u32 var_a3;
    u32 var_a3_2;
    u8 **temp_v0_3;
    u8 **var_a0_2;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 temp_v0_2;
    u8 temp_v0_4;

    temp_v0 = func_1502B7F0((s32 *) &D_800D34B8, 3, 0xC, arg0, 5);
    temp_lo = temp_v0 / 52U;
    D_800D3094 = (s32) temp_v0;
    D_800D3094 = (s32) temp_lo;
    func_15017B20(D_800D34B8, temp_lo);
    D_800D3694 = 0;
    D_800D3690 = NULL;
    var_a3 = 0;
    if (D_800D3094 != 0) {
        var_a1 = 0;
        do {
            var_a3 += 1;
            temp_v1 = &D_800D34B8[var_a1];
            temp_t9 = (s32) (*(u8 *)((u8 *)temp_v1 + 0x15)) >> 2;
            var_a0 = temp_t9;
            if (temp_t9 == 1) {
                temp_v0_2 = (*(u8 *)((u8 *)temp_v1 + 0x17));
                if (temp_v0_2 != 2) {
                    if (temp_v0_2 != 0) {
                        if (temp_v0_2 == 6) {
                            goto block_6;
                        }
                    } else {
                        goto block_6;
                    }
                } else {
block_6:
                    D_800D3694 += 1;
                    var_a0 = (s32) (*(u8 *)((u8 *)temp_v1 + 0x15)) >> 2;
                }
            }
            if (var_a0 != 2) {
                if (var_a0 == 7) {
                    goto block_9;
                }
            } else {
block_9:
                (*(s32 *)((u8 *)temp_v1 + 0x20)) = 0;
            }
            var_a1 += 0x34;
        } while (var_a3 < (u32) D_800D3094);
    }
    if (D_800D3694 != 0) {
        temp_v0_3 = allocate_memory(D_800D3694 * 4, 1, 0, 0);
        D_800D3690 = temp_v0_3;
        if (temp_v0_3 != NULL) {
            var_a0_2 = temp_v0_3;
            var_a3_2 = 0;
            var_a1_2 = 0;
            if (D_800D3094 != 0) {
                do {
                    var_a3_2 += 1;
                    temp_v1_2 = &D_800D34B8[var_a1_2];
                    if (((s32) (*(u8 *)((u8 *)temp_v1_2 + 0x15)) >> 2) == 1) {
                        temp_v0_4 = (*(u8 *)((u8 *)temp_v1_2 + 0x17));
                        if (temp_v0_4 != 2) {
                            if (temp_v0_4 != 0) {
                                if (temp_v0_4 == 6) {
                                    goto block_18;
                                }
                            } else {
                                goto block_18;
                            }
                        } else {
block_18:
                            *var_a0_2 = &D_800D34B8[var_a1_2];
                            var_a0_2 = (u8 * *)((u8 *)var_a0_2 + (4));
                        }
                    }
                    var_a1_2 += 0x34;
                } while (var_a3_2 < (u32) D_800D3094);
            }
        }
    }
    bzero(&D_800D3510, 0x180);
    bzero(&D_800D34F0, 0x20);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_44C40/func_15017930.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_44C40/func_15017B20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_44C40/func_15017FA4.s")
