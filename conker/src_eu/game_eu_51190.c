#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15023980(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15023988.s")

#ifdef NON_MATCHING
extern s32 D_800C3AA8;
extern s32 D_eu_800C3A60;

s32 func_15023C60(u32 arg0, s32 arg1, s32 arg2, u8 **arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    s16 var_v1;
    s32 var_a1;
    u16 temp_t0;
    u8 var_v0;
    u8 *temp_v0;
    u8 *var_a0;

    temp_v0 = *(((s32 *)((u8 *)&D_800C3AA8 + ((argA * 0x78) + (arg2 * 4)))));
    if (temp_v0 != NULL) {
        var_a0 = temp_v0 + 0x20;
        temp_t0 = D_800C39F8[argA][arg2];
        var_a1 = var_a0 - temp_v0;
        var_v1 = (*(s16 *)((u8 *)temp_v0 + 2));
        if ((u32) (var_a1 >> 3) < temp_t0) {
loop_3:
            var_v0 = (*(u8 *)((u8 *)var_a0 + 1));
            if ((var_v0 == 0) && ((*(s8 *)((u8 *)var_a0 + 0)) == 0)) {
                var_v1 = (*(s16 *)((u8 *)var_a0 + 2));
                goto block_37;
            }
            if ((arg0 < (u32) var_a0) && (arg1 == (*(s8 *)((u8 *)var_a0 + 0))) && ((arg4 == 0) || ((arg4 == 1) && (arg5 == (*(s16 *)((u8 *)var_a0 + 2))))) && ((arg6 == 0) || ((arg6 == 1) && (arg7 == (*(s8 *)((u8 *)var_a0 + 4))))) && ((arg8 == 0) || ((arg8 == 1) && (arg9 == (*(s8 *)((u8 *)var_a0 + 5)))))) {
                *arg3 = var_a0;
                return (s32) (var_v1 * 0x32) / 60;
            }
            if (var_v0 == 0) {
loop_19:
                if ((*(s8 *)((u8 *)var_a0 + 0)) == 0) {
                    var_v1 = (*(s16 *)((u8 *)var_a0 + 2));
                    goto block_36;
                }
                var_a1 += 8;
                var_a0 += 8;
                if ((u32) (var_a1 >> 3) >= temp_t0) {
                    var_v0 = (*(u8 *)((u8 *)var_a0 + 1));
                    goto block_36;
                }
                if ((arg0 < (u32) var_a0) && (arg1 == (*(s8 *)((u8 *)var_a0 + 0))) && ((arg4 == 0) || ((arg4 == 1) && (arg5 == (*(s16 *)((u8 *)var_a0 + 2))))) && ((arg6 == 0) || ((arg6 == 1) && (arg7 == (*(s8 *)((u8 *)var_a0 + 4))))) && ((arg8 == 0) || ((arg8 == 1) && (arg9 == (*(s8 *)((u8 *)var_a0 + 5)))))) {
                    *arg3 = var_a0;
                    return (s32) (var_v1 * 0x32) / 60;
                }
                var_v0 = (*(u8 *)((u8 *)var_a0 + 1));
                if (var_v0 != 0) {
                    goto block_36;
                }
                goto loop_19;
            }
block_36:
            var_v1 += var_v0;
block_37:
            var_a1 += 8;
            var_a0 += 8;
            if ((u32) (var_a1 >> 3) >= temp_t0) {
                goto block_38;
            }
            goto loop_3;
        }
    }
block_38:
    *arg3 = NULL;
    return *(s32 *)((u8 *)&D_eu_800C3A60 + (argA * 4));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15023C60.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15023EC4.s")

s32 func_1502AB94(s32, u8, u16, s32, s32);

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u16 unkA;
} struct_150243AC; // size 0xC

extern struct_150243AC *D_800C4170;

void func_150243AC(s32 arg0, s32 arg1) {
    s32 i;
    struct_150243AC *temp_v0;

    for (i = 0; i < arg0; i++) {
        temp_v0 = (struct_150243AC *)((u8 *)D_800C4170 + i * 0xC);
        func_1502AB94(temp_v0->unk0, temp_v0->unk8, temp_v0->unkA, temp_v0->unk4 >> 8, arg1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15024438.s")

#ifdef NON_MATCHING
s32 func_15024438(struct_150243AC *, s32 *, u8 *, s32, s32, s32, s32);
extern s32 D_800C39D0;
extern s32 D_800C39D8;
extern s32 D_800C39E0;
extern s32 D_800C3A68;
extern s32 D_800C3AA8;
extern u8 D_800C40AC;
extern u16 D_800C40BA;
extern s32 D_eu_800C3A60;

void func_1502457C(s32 arg0, s32 arg1) {
    struct {
        s32 u80;
    } sp;
    s32 sp7C;
    s32 sp78;
    u8 *sp74;
    s16 var_s1;
    s32 temp_a0;
    s32 temp_t5;
    s32 temp_v1;
    s32 var_s7;
    s32 var_v0;
    s32 var_v1;
    u16 **temp_s4;
    u16 var_a0;
    u8 *temp_t2;
    u8 temp_v0;
    u8 var_a3;
    u8 var_v0_2;
    u8 **var_s6;
    u8 *temp_a1;
    u8 *var_s0;

    if ((D_800C40AC != 2) && ((&D_800C35EA)[arg1] == 1) && (D_800C40BA != 0)) {
        D_800C3638 = 0;
        sp.u80 = 0;
        temp_t2 = &D_800C3A5A[arg1];
        sp74 = temp_t2;
        var_a3 = *temp_t2;
        var_s7 = 0;
        if ((s32) var_a3 > 0) {
            var_s6 = (arg1 * 0x78) + &D_800C3AA8;
            do {
                temp_a1 = *var_s6;
                temp_t5 = arg1 * 4;
                if (temp_a1 != NULL) {
                    temp_a0 = *(&D_800C39D8 + temp_t5);
                    temp_v1 = *(&D_800C39D0 + temp_t5);
                    var_s0 = temp_a1 + 0x20;
                    if (temp_a0 != temp_v1) {
                        temp_s4 = &D_800C39F8[arg1];
                        var_s1 = (*(s16 *)((u8 *)temp_a1 + 2));
                        sp78 = (s32) (temp_a0 * 0x3C) / 50;
                        if (temp_v1 >= *(&D_eu_800C3A60 + temp_t5)) {
                            sp7C = D_800C3A68;
                        } else {
                            sp7C = (s32) (temp_v1 * 0x3C) / 50;
                        }
                        var_a0 = (*temp_s4)[var_s7];
                        var_v1 = var_s0 - temp_a1;
                        var_v0 = var_v1 >> 3;
                        if ((u32) var_v0 < var_a0) {
loop_11:
                            if (((*(u8 *)((u8 *)var_s0 + 1)) == 0) && ((*(s8 *)((u8 *)var_s0 + 0)) == 0)) {
                                var_s1 = (*(s16 *)((u8 *)var_s0 + 2));
                                goto block_35;
                            }
                            if ((sp7C >= var_s1) && (sp78 < var_s1) && ((u32) var_v0 < var_a0)) {
loop_17:
                                if (((arg0 == 0) && ((*(s8 *)((u8 *)var_s0 + 0)) != 0x11)) || ((arg0 == 1) && ((*(s8 *)((u8 *)var_s0 + 0)) == 0x11))) {
                                    func_15024438(D_800C4170, &sp.u80, var_s0, var_s7, var_v0, (s32) ((var_s1 << 8) * 0x32) / 60, arg1);
                                }
                                temp_v0 = (*(u8 *)((u8 *)var_s0 + 1));
                                if ((temp_v0 == 0) && ((temp_v0 != 0) || ((*(s8 *)((u8 *)var_s0 + 0)) != 0))) {
                                    var_s0 += 8;
                                    var_v0 = (s32) (var_s0 - *var_s6) >> 3;
                                    if ((u32) var_v0 < (u16) (*temp_s4)[var_s7]) {
                                        goto loop_17;
                                    }
                                }
                            }
                            if (sp7C < var_s1) {
                                var_a3 = *sp74;
                            } else {
                                var_v0_2 = (*(u8 *)((u8 *)var_s0 + 1));
                                var_a0 = (*temp_s4)[var_s7];
                                var_v1 = var_s0 - *var_s6;
                                if (var_v0_2 == 0) {
loop_29:
                                    if ((*(s8 *)((u8 *)var_s0 + 0)) == 0) {
                                        var_s1 = (*(s16 *)((u8 *)var_s0 + 2));
                                    } else {
                                        var_v1 += 8;
                                        var_s0 += 8;
                                        if ((u32) (var_v1 >> 3) >= var_a0) {
                                            var_v0_2 = (*(u8 *)((u8 *)var_s0 + 1));
                                        } else {
                                            var_v0_2 = (*(u8 *)((u8 *)var_s0 + 1));
                                            if (var_v0_2 == 0) {
                                                goto loop_29;
                                            }
                                        }
                                    }
                                }
                                var_s1 += var_v0_2;
block_35:
                                var_v1 += 8;
                                var_v0 = var_v1 >> 3;
                                var_s0 += 8;
                                if ((u32) var_v0 >= var_a0) {
                                    var_a3 = *sp74;
                                } else {
                                    goto loop_11;
                                }
                            }
                        }
                    }
                }
                var_s7 += 1;
                var_s6 += 4;
            } while (var_s7 < (s32) var_a3);
        }
        func_150243AC(sp.u80, arg1);
        D_800C3638 = 1;
        if (arg0 == 0) {
            *(&D_800C39E0 + arg1) = 1;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_1502457C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15024910.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_150268BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15029EA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_1502AB94.s")
