#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15024438(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
#endif


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

#ifdef NON_MATCHING
extern u16 D_800C40BA;

void func_15024438(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 *var_v0_2;
    s32 temp_a0;
    s32 temp_at;
    s32 temp_s0;
    s32 var_a0;
    s32 var_a2;
    u8 *temp_v0;
    u8 *var_v0;
    u8 *var_v1;

    temp_s0 = *arg1;
    var_a2 = temp_s0;
    if (temp_s0 >= (s32) D_800C40BA) {
        func_150243AC(temp_s0, arg6);
        *arg1 = 0;
        return;
    }
    var_a0 = 0;
    if (temp_s0 > 0) {
        var_v0 = arg0;
loop_4:
        if ((*(s32 *)((u8 *)var_v0 + 4)) >= arg5) {
            var_a2 = var_a0;
        } else {
            var_a0 += 1;
            var_v0 += 0xC;
            if (var_a0 < temp_s0) {
                goto loop_4;
            }
        }
    }
    temp_a0 = temp_s0 - 1;
    if (temp_a0 >= var_a2) {
        var_v0_2 = arg0 + (temp_a0 * 0xC);
        var_v1 = ((s32 *)((u8 *)var_v0_2 + 0xC));
        do {
            temp_at = *var_v0_2;
            var_v1 -= 0xC;
            var_v0_2 = (s32 *)((u8 *)var_v0_2 - (0xC));
            (*(s32 *)((u8 *)var_v1 + 0xC)) = temp_at;
            (*(s32 *)((u8 *)var_v1 + 0x10)) = (s32) (*(s32 *)((u8 *)var_v0_2 + 0x10));
            (*(s32 *)((u8 *)var_v1 + 0x14)) = (s32) (*(s32 *)((u8 *)var_v0_2 + 0x14));
        } while ((u32) var_v1 >= (u32) ((var_a2 * 0xC) + arg0 + 0xC));
    }
    temp_v0 = arg0 + (var_a2 * 0xC);
    (*(s32 *)((u8 *)temp_v0 + 0)) = arg2;
    (*(s8 *)((u8 *)temp_v0 + 8)) = (s8) arg3;
    (*(s32 *)((u8 *)temp_v0 + 4)) = arg5;
    (*(s16 *)((u8 *)temp_v0 + 0xA)) = (s16) arg4;
    *arg1 += 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15024438.s")
#endif
#ifdef NON_MATCHING
void func_15024438(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
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

#ifdef NON_MATCHING
/* one 8-byte entry of a player's D_800C3A10 table: what entry arg1 refers to */
typedef struct {
    u16 kind;   /* 2: object func_15083E90(id), 3: func_151149AC(id), else none */
    u8  id;
    u8  pad3[5];
} struct_1502AB94_ref;

extern struct_1502AB94_ref *D_800C3A10[];   /* per player */
u8 *func_151149AC(u8);
s32 func_15024910(s32, u8, u16, s32, s32, struct127 *, u8 *, u8 *, s32);
s32 func_150268BC(s32, u8, u16, s32, s32, struct127 *, u8 *, u8 *, s32);
s32 func_15029EA8(s32, u8, u16, s32, s32, struct127 *, u8 *, u8 *, s32, s32);

/* Runs entry arg1 of player `player` through the three handlers in turn; the first non-zero result is returned.
 * The entry may refer to an object (kind 2: its data at +0x14 replaces the player's D_800C3958 record) or to a
 * func_151149AC record (kind 3); a missing reference returns 0. When D_800C3C88 == 2 the middle handler is skipped
 * and the last one gets 1 instead of 0. */
s32 func_1502AB94(s32 arg0, u8 arg1, u16 arg2, s32 arg3, s32 player) {
    struct127 *obj;
    u8 *rec;
    u8 *data;
    s32 flag;
    s32 ret;
    struct_1502AB94_ref *ref;

    obj = NULL;
    rec = NULL;
    data = NULL;
    flag = (&D_800C3A08)[player];
    ref = &D_800C3A10[player][arg1];
    if (ref->kind == 2) {
        obj = func_15083E90(ref->id);
        if (obj == NULL) {
            return 0;
        }
        data = (u8 *) obj + 0x14;
    } else if (ref->kind == 3) {
        rec = func_151149AC(ref->id);
        if (rec == NULL) {
            return 0;
        }
    }
    if (data == NULL) {
        data = (u8 *) ((&D_800C3958)[player] + arg1);
    }
    if (D_800C3C88 != 2) {
        ret = func_15024910(arg0, arg1, arg2, arg3, player, obj, rec, data, flag);
        if (ret != 0) {
            return ret;
        }
        ret = func_150268BC(arg0, arg1, arg2, arg3, player, obj, rec, data, flag);
        if (ret != 0) {
            return ret;
        }
        return func_15029EA8(arg0, arg1, arg2, arg3, player, obj, rec, data, flag, 0);
    }
    ret = func_15024910(arg0, arg1, arg2, arg3, player, obj, rec, data, flag);
    if (ret != 0) {
        return ret;
    }
    return func_15029EA8(arg0, arg1, arg2, arg3, player, obj, rec, data, flag, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_1502AB94.s")
#endif
