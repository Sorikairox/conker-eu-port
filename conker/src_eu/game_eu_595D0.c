#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 func_1506196C(struct127 *, s32);
void func_1502E228(s32 arg0, s32 arg1);
void func_1502C8F8(s32 arg0);
void func_1502FED8(struct127 *arg0);
void func_1502E7B4(s32 arg0);
void func_1503A37C(struct127 *arg0);
void func_150348D4(s32 arg0);
void func_1503AB20(struct127 *arg0);
void func_1503E238(s32 arg0);
void func_1502F1E4(s32 arg0);
void func_1502F554(s32 arg0);
void func_1502EDEC(struct127 *arg0);
void func_150A4FE4(struct127 *arg0);
void func_1517B270(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_800C6A8F[];
#endif

typedef struct {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ u8 unkA4;
    /* 0xA5 */ u8 unkA5;
    /* 0xA6 */ u8 unkA6;
    /* 0xA7 */ u8 unkA7;
} struct_eu_595D0;


#ifdef NON_MATCHING
u8 * func_1502C6F8(u8 *, s32, s16);
u8 * func_1502CC64(u8 *, s32, s16, s32, s32);
u8 * func_15036BB4(u8 *, s32, s16);
extern s32 D_800844F0;
extern s32 D_80084520;

Gfx *func_1502BDC0(Gfx *gdl, s32 arg1, s16 arg2) {
    u8 *arg0 = (u8 *) gdl;
    s32 var_s1;
    struct127 *var_s0;
    u8 temp_v0;
    u8 *temp_v0_2;
    u8 *var_s2;
    u8 *var_v0;
    u8 *var_v0_2;

    (*(s32 *)((u8 *)arg0 + 0)) = 0xDE000000;
    (*(s32 **)((u8 *)arg0 + 4)) = &D_800844F0;
    var_s2 = arg0 + 8;
    var_s0 = D_800CC2D0;
    var_s1 = 0;
    do {
        D_8003C8E0 = (var_s1 & 0xFFFFFF) | 0x01000000;
        if (var_s0->interaction_state != 0) {
            temp_v0 = var_s0->unk5;
            if ((temp_v0 != 3) && (temp_v0 != 5)) {
                if (temp_v0 == 2) {
                    if (arg1 != 2) {

                    } else {
                        goto block_8;
                    }
                } else if (var_s0->id != 0xFF) {
block_8:
                    if (arg1 == 6) {
                        if (temp_v0 != 7) {

                        } else {
                            goto block_27;
                        }
                    } else if (arg1 == 0) {
                        if (!(((u32) var_s0->unk184 >> 9) & 1)) {

                        } else {
                            goto block_27;
                        }
                    } else if (arg1 == 1) {
                        if ((temp_v0 != 7) && (temp_v0 != 1)) {
                            if ((temp_v0 == 0) && (func_1506196C(var_s0, arg2) < 0xFF)) {

                            } else {
                                goto block_27;
                            }
                        }
                    } else if ((arg1 != 2) || (temp_v0 == 2) || ((temp_v0 != 7) && ((temp_v0 == 0) || (temp_v0 == 1)) && ((temp_v0 != 0) || (func_1506196C(var_s0, arg2) != 0xFF)))) {
block_27:
                        if (var_s0->unk5 == 2) {
                            var_v0 = func_1502C6F8(var_s2, var_s1, arg2);
                            goto block_31;
                        }
                        temp_v0_2 = func_1502CC64(var_s2, var_s1, arg2, arg1, 0);
                        var_s2 = temp_v0_2;
                        if (var_s1 == 0) {
                            var_v0 = func_15036BB4(temp_v0_2, var_s1, arg2);
block_31:
                            var_s2 = var_v0;
                        }
                    }
                }
            }
        }
        var_s1 += 1;
        var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
    } while (var_s1 != 0x19);
    D_8003C8E0 = 0x01FFFFFF;
    if (arg1 == 1) {
        var_v0_2 = func_150310F8(var_s2, arg2, 0);
        goto block_39;
    }
    if (arg1 == 2) {
        var_v0_2 = func_150310F8(var_s2, arg2, 1);
        goto block_39;
    }
    if (arg1 == 6) {
    s32 pad;
        var_v0_2 = func_150310F8(var_s2, arg2, 2);
block_39:
        var_s2 = var_v0_2;
    }
    (*(s32 *)((u8 *)var_s2 + 0)) = 0xDE000000;
    (*(s32 **)((u8 *)var_s2 + 4)) = &D_80084520;
    D_8003C8E0 = 0;
    return (Gfx *) (var_s2 + 8);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502BDC0.s")
#endif
#ifdef NON_MATCHING
/* P41: per-object update of object arg1 (record arg0): clears +0x1D4 (the shadow / model pointer), type +5 == 5 →
 * func_1502E228(arg1, 1) only; type +4 == 0xFF or +5 == 3: nothing; +5 == 2: func_1502C8F8. Otherwise the model setup
 * (func_1502E7B4, func_1502E228(arg1, 0) which sets +0x1D4, func_1503A37C), +0x1FC = 2 without a model, and the
 * per-frame callees (D_800C6A8F[arg1 * 16], +0x0, +0xA4, +0xF8 & 0x4000, +0x260). */
void func_1502C074(struct127 *arg0, s32 arg1) {
    u8 *obj = (u8 *)arg0;
    s32 t = obj[5];

    *(s32 *)(obj + 0x1D4) = 0;
    if (t == 5) {
        func_1502E228(arg1, 1);
        return;
    }
    if (obj[4] == 0xFF || t == 3) {
        return;
    }
    if (t == 2) {
        func_1502C8F8(arg1);
        return;
    }
    if (obj[0x1C9] != 0) {
        func_1502FED8(arg0);
    }
    func_1502E7B4(arg1);
    func_1502E228(arg1, 0);
    func_1503A37C(arg0);
    if (*(s32 *)(obj + 0x1D4) == 0) {
        obj[0x1FC] = 2;
    } else {
        func_150348D4(arg1);
        func_1503AB20(arg0);
    }
    if (D_800C6A8F[arg1 * 16] != 0) {
        func_1503E238(arg1);
    }
    if (*(s32 *)obj == 0) {
        return;
    }
    func_1502F1E4(arg1);
    func_1502F554(arg1);
    if (obj[0xA4] != 0) {
        func_1502EDEC(arg0);
    }
    if (*(s32 *)(obj + 0xF8) & 0x4000) {
        func_150A4FE4(arg0);
    }
    if (*(s32 *)(obj + 0x260) != 0) {
        func_1517B270(obj[0x134], obj[0x135], arg1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C074.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C1D4.s")

#ifdef NON_MATCHING
s32 func_15022A8C(struct127 *);
s32 func_1506196C(struct127 *, s32);
struct102 *func_1510DEF0(s32, struct127 *, s32, s32, s32);
extern u8 D_800C3A7A;

void func_1502C494(void) {
    s32 var_a2;
    s32 var_s0;
    s32 var_s2;
    s32 var_v0;
    struct127 *var_s1;
    u8 *temp_a0;

    var_s1 = D_800CC2D0;
    do {
        if (var_s1->interaction_state != 0) {
            var_s2 = 0;
            if ((var_s1->unk5 != 3) && (var_s1->id != 0xFF) && (var_s1->unk123 == 0) && ((var_s1->unk66 & 0x10) != 0x10) && (var_s1->unk160 != 0) && (var_s1->unk65 == 0) && ((D_800C3638 == 0) || (D_800C3A7A != 0) || (func_15022A8C(var_s1) != 0)) && ((var_s1->unk88 == 0) || (var_s1->unkCC >= -0x96))) {
                var_s0 = 0;
                if (D_80082FA0 >= 0) {
                    do {
                        if (func_1506196C(var_s1, var_s0) != 0) {
                            var_s2 = 1;
                        }
                        var_s0 += 1;
                    } while (D_80082FA0 >= var_s0);
                }
            }
            if (var_s2 != 0) {
                if (var_s1->unk2D4 == NULL) {
                    var_a2 = 0;
                    var_v0 = 0;
                    if (var_s1->id == 0x4D) {
                        var_a2 = 2;
                        var_v0 = 1;
                    }
                    var_s1->unk2D4 = func_1510DEF0(0, var_s1, var_a2, 0, var_v0);
                }
            } else {
                temp_a0 = var_s1->unk2D4;
                if (temp_a0 != NULL) {
                    func_1516972C((struct102 *) temp_a0);
                    var_s1->unk2D4 = NULL;
                }
            }
        }
        var_s1 = (struct127 *)((u8 *)var_s1 + (0x32C));
    } while ((s32)var_s1 != (s32)&D_800D121C);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C494.s")
#endif
void func_1502C380(void) {
    D_800C42AC = D_800C42A8 = (&D_800C3E80)[D_800BE9C0];
    D_800C429A = 0;
}

s32 func_1502C6AC(s32 arg0) {
    s32 temp_v1 = (&D_800CC826)[arg0 * 0x32C];

    if (temp_v1 >= 0x46) {
        temp_v1 = 0xB;
    }
    return temp_v1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C6F8.s")

extern u8 *D_8008CDEC[];

void func_1502C8F8(s32 arg0) {
    s32 lim;
    s16 a;
    s16 b;

    if (D_800BEAC0 == 0) {
        a = *(s16 *)((u8 *)&D_800CC2D0[arg0] + 0x60);
        b = *(s16 *)((u8 *)&D_800CC2D0[arg0] + 0x62);
        if (D_800CC2D0[arg0].unk7 != 0) {
            lim = D_8008CDEC[func_1502C6AC(arg0)][4] << 8;
            a = a + b;
            if (a >= lim) {
                a = a - lim;
            } else if (a < 0) {
                a = a + lim;
            }
            *(s16 *)((u8 *)&D_800CC2D0[arg0] + 0x60) = a;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C9D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502CC64.s")

s32 func_1502EF24(u8 *, s32 *, s32 *, s32 *, s32 *);

void func_1502CF24(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *argA, s32 *argB, s32 *argC, s32 *argD) {
    s32 temp_a2;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_a2 = arg1 * 3;
    temp_v0 = temp_a2 + D_800D9F88;
    *arg4 = (s32) (*(u8 *)((u8 *)temp_v0 + 0));
    temp_v1 = temp_a2 + D_800D9F98;
    *arg5 = (s32) (*(u8 *)((u8 *)temp_v0 + 1));
    *arg6 = (s32) (*(u8 *)((u8 *)temp_v0 + 2));
    *arg7 = (s32) (*(u8 *)((u8 *)temp_v1 + 0));
    *arg8 = (s32) (*(u8 *)((u8 *)temp_v1 + 1));
    *arg9 = (s32) (*(u8 *)((u8 *)temp_v1 + 2));
    *argA = 0;
    *argB = 0;
    *argC = 0;
    *argD = (*(s32 *)((u8 *)arg3 + 0xC));
    if ((*(u8 *)((u8 *)arg0 + 0xA4)) != 0) {
        func_1502EF24(arg0, argA, argB, argC, argD);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502CFEC.s")

#ifdef NON_MATCHING
void func_1502D83C(s32 arg0, u8 *arg1) {
    s32 temp_t1;
    struct127 *temp_v0;

    temp_v0 = &D_800CC2D0[arg0];
    if ((temp_v0->unk66 & 0xC) == 4) {
        (*(s32 *)((u8 *)arg1 + 0)) = (s32) ((s32) (temp_v0->unk1DD + temp_v0->unk1E0) / 2);
        (*(s32 *)((u8 *)arg1 + 4)) = (s32) ((s32) (temp_v0->unk1DE + temp_v0->unk1E1) / 2);
        temp_t1 = (s32) (temp_v0->unk1DF + temp_v0->unk1E2) / 2;
        (*(s32 *)((u8 *)arg1 + 8)) = temp_t1;
        (*(s32 *)((u8 *)arg1 + 0)) = (s32) (0xFF - (*(s32 *)((u8 *)arg1 + 0)));
        (*(s32 *)((u8 *)arg1 + 4)) = (s32) (0xFF - (*(s32 *)((u8 *)arg1 + 4)));
        (*(s32 *)((u8 *)arg1 + 8)) = (s32) (0xFF - temp_t1);
        return;
    }
    (*(s32 *)((u8 *)arg1 + 8)) = 0xFF;
    (*(s32 *)((u8 *)arg1 + 4)) = 0xFF;
    (*(s32 *)((u8 *)arg1 + 0)) = 0xFF;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502D83C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502D920.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502DB14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502DE10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502DE74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502E228.s")

void func_1502E764(void) {
    if ((u16)D_800C429A != 0) {
        func_150A9E64((&D_800C3E80)[D_800BE9C0], (u16)D_800C429A);
    }
    D_800C42B0 = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502E7B4.s")

void func_1502ECEC(s32 arg0, s32 arg1) {
}

void func_1502ECFC(struct_eu_595D0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    arg0->unkA4 = 4;
    arg0->unkA5 = 0;
    arg0->unkA6 = arg5;
    arg0->unkA0 = (arg4 << 24) | (arg1 << 16) | (arg2 << 8) | arg3;
    arg0->unkA7 = 0xFF;
}

void func_1502ED40(struct_eu_595D0 *arg0) {
    arg0->unkA4 = 5;
}

void func_1502ED50(struct_eu_595D0 *arg0, s32 arg1) {
    arg0->unkA4 = 2;
    arg0->unkA5 = 0xFF;
    arg0->unkA6 = arg1;
}

void func_1502ED6C(struct_eu_595D0 *arg0, s32 arg1) {
    arg0->unkA4 = 3;
    arg0->unkA5 = 0xFF;
    arg0->unkA6 = arg1;
}

void func_1502ED88(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u8 temp_v0;

    temp_v0 = (*(u8 *)((u8 *)arg0 + 0xA4));
    if ((temp_v0 != 6) && (temp_v0 != 7)) {
        if (arg5 != 0) {
            (*(u8 *)((u8 *)arg0 + 0xA5)) = 0xFF;
        } else {
            (*(s8 *)((u8 *)arg0 + 0xA5)) = 0;
        }
        (*(s32 *)((u8 *)arg0 + 0xA0)) = (s32) ((arg4 << 0x18) | (arg1 << 0x10) | (arg2 << 8) | arg3);
        (*(s8 *)((u8 *)arg0 + 0xA6)) = (s8) arg6;
    }
    (*(u8 *)((u8 *)arg0 + 0xA4)) = 6U;
}

#ifdef NON_MATCHING
void func_1502EDEC(struct127 *arg0) {
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_t1;
    u8 temp_t6;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;

    temp_t6 = arg0->unkA4;
    switch (temp_t6) {
    case 2:
    case 3:
        temp_v1 = arg0->unkA5;
        temp_lo = arg0->unkA6 * D_800BE9E4;
        if (temp_lo < (s32) temp_v1) {
            arg0->unkA5 = temp_v1 - temp_lo;
            return;
        }
        arg0->unkA5 = 0;
        return;
    case 5:
        temp_v1_2 = arg0->unkA7;
        temp_t1 = D_800BE9E4 * 0xA;
        if (temp_t1 < (s32) temp_v1_2) {
            arg0->unkA7 = temp_v1_2 - temp_t1;
        } else {
            arg0->unkA4 = 0;
        }
        /* fallthrough */
    case 4:
        arg0->unkA5 += arg0->unkA6 * D_800BE9E4;
        return;
    case 6:
        temp_v1_3 = arg0->unkA5;
        temp_lo_2 = arg0->unkA6 * D_800BE9E4;
        if ((s32) temp_v1_3 < (0xFF - temp_lo_2)) {
            arg0->unkA5 = temp_v1_3 + temp_lo_2;
        } else {
            arg0->unkA5 = 0xFF;
        }
        arg0->unkA4 = 7;
        return;
    case 7:
        temp_v1_4 = arg0->unkA5;
        temp_lo_3 = arg0->unkA6 * D_800BE9E4;
        if (temp_lo_3 < (s32) temp_v1_4) {
            arg0->unkA5 = temp_v1_4 - temp_lo_3;
            return;
        }
        arg0->unkA4 = 0;
    default:
        return;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502EDEC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502EF24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F17C.s")

#ifdef NON_MATCHING
s32 func_1502F17C(s32, s32);
s32 func_1507E7A0(struct127 *);

void func_1502F1E4(s32 arg0) {
    s32 temp_v1;
    s32 var_s1;
    struct127 *var_s0;
    u8 temp_v0;
    u8 temp_v0_2;

    var_s0 = &D_800CC2D0[arg0];
    var_s1 = 0;
    do {
        if ((s32) (*(u8 *)((u8 *)var_s0 + 0x6C)) < 0xA) {
            temp_v1 = func_1502F17C(arg0, var_s1) & 0xFF;
            if (temp_v1 == 0) {
                temp_v0 = (*(u8 *)((u8 *)var_s0 + 0x6C));
                if ((s32) temp_v0 > 0) {
                    (*(u8 *)((u8 *)var_s0 + 0x6C)) = (u8) (temp_v0 - 1);
                }
            } else if (temp_v1 == 1) {
                temp_v0_2 = (*(u8 *)((u8 *)var_s0 + 0x6C));
                if ((s32) temp_v0_2 < 2) {
                    (*(u8 *)((u8 *)var_s0 + 0x6C)) = (u8) (temp_v0_2 + 1);
                }
            } else {
                (*(u8 *)((u8 *)var_s0 + 0x6C)) = 1U;
            }
        }
        var_s1 += 1;
        var_s0 = (struct127 *)((u8 *)var_s0 + (1));
    } while (var_s1 != 2);
    func_1507E7A0(&D_800CC2D0[arg0]);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F1E4.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F30C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F554.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F6B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F780.s")

u8 *allocate_memory(s32, s32, s32, s32);
void func_1502FC38(u8 *arg0) {
    s32 temp_v1;
    u8 *temp_v0;
    if ((*(s32 *)(arg0 + 0xF8) & 0x4000) && *(s32 *)(arg0 + 0x264) != 0 && *(s32 *)(arg0 + 0x1D4) != 0) {
        temp_v1 = arg0[4];
        if (*(s32 *)(arg0 + 0x1D8) == 0) {
            temp_v0 = allocate_memory(D_800C52F0[temp_v1] << 6, 1, 1, 2);
            *(u8 **)(arg0 + 0x1D8) = temp_v0;
            if (temp_v0 == NULL) {
                return;
            }
        }
        bcopy(*(u8 **)(arg0 + 0x1D4), *(u8 **)(arg0 + 0x1D8), D_800C52F0[temp_v1] << 6);
    }
}

#ifdef NON_MATCHING
void * func_150C3160(void *, void *);
extern s32 D_800C5758;

u8 *func_1502FCEC(u8 *arg0, s32 arg1) {
    s32 *temp_t4;
    s32 var_a0;
    s32 var_v1;
    struct127 *temp_a2;
    struct127 *var_a1;
    u8 temp_v0;
    u8 *temp_v0_2;
    u8 *var_s0;

    var_s0 = arg0;
    temp_a2 = &D_800CC2D0[arg1];
    temp_v0 = temp_a2->id;
    if ((temp_v0 == 0x89) || (temp_v0 == 0xBA)) {
        return func_150C3160(var_s0, temp_a2);
    }
    if (temp_v0 == 0) {
        var_v1 = 0xE;
    } else {
        var_v1 = 7;
        if (temp_v0 == 0x96) {

        } else {
            var_v1 = 4;
            if (temp_v0 == 0x28) {

            } else if ((temp_v0 == 1) || (temp_v0 == 2) || (temp_v0 == 3) || (var_v1 = 0, (temp_v0 == 4))) {
                var_v1 = 5;
            }
        }
    }
    temp_t4 = ((s32 *)((u8 *)&D_800C5758 + (temp_v0 * 4)));
    var_a0 = 0;
    if (*temp_t4 != 0) {
        var_a1 = &D_800CC2D0[arg1];
        do {
            temp_v0_2 = *temp_t4 + (var_v1 * 0xC);
            (*(s32 *)((u8 *)var_s0 + 0)) = (s32) ((((var_a1->unk27A + 2) & 0xFFFF & 0xFFF) << 0xC) | 0xF2000000 | ((var_a1->unk27E + 2) & 0xFFFF & 0xFFF));
            (*(s32 *)((u8 *)var_s0 + 4)) = (s32) ((((5 - var_a0) & 7) << 0x18) | (((((*(u16 *)((u8 *)temp_v0_2 + 8)) * 4) - 2) & 0xFFFF & 0xFFF) << 0xC) | ((((*(u16 *)((u8 *)temp_v0_2 + 0xA)) * 4) - 2) & 0xFFFF & 0xFFF));
            var_s0 += 8;
            var_a0 += 1;
            var_a1 = (struct127 *)((u8 *)var_a1 + (2));
        } while (var_a0 != 2);
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502FCEC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502FED8.s")

void func_15030060(u8 *arg0)
{
  u8 idx = arg0[4];
  u8 *p;
  u8 *s;
  u8 a2;
  s32 v;
  if ((D_80038080 == 0) && (D_800BE9F0 == 0x1D))
  {
    ((u8 *) D_800D2040)[idx] = 2;
    return;
  }
  p = &((u8 *) D_800D2040)[idx];
  if ((*p) != 0xFF)
  {
    s = *((u8 **) (arg0 + 0x144));
    if (s != 0)
    {
      ;
      if (s[0x2E] != 0xFF)
      {
        if (s[0x2E] != 0)
        {
          ;
          if ((*p) < (s[0x2E] * 30))
          {
            *p = s[0x2E] * 30;
          }
        }
        else
        {
          goto set3;
        }
      }
    }
    else
    {
      set3:
      *p = 3;

    }
    if (arg0)
    {
    }
  }
}
