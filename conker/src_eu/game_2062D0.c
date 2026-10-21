#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 memcpy(s32, s32, s32);
extern u8 D_800AB7C8[];
s32 func_151DAB58(u8, f32, u8, f32 *, s32, s32, s32);
void func_151D9FC0(u8 arg0, f32 arg1, u8 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);
u8 func_151D9534(u8 *arg0, u8 *arg1);
#endif


u8 func_151D8E20(void) {
    if ((D_800BE9F0 == 0) && (func_150A29C8(0, 0x1C) == 0)) {
        return 10;
    }
    return D_800E0A10;
}

u8 func_151D8E6C(void) {
    u8 tmp[3] = D_800AB340;
    return tmp[(func_150ADA20() % 3U)];
}

u8 func_151D8EB0(void) {
    return 117;
}

u8 func_151D8EBC(void) {
    return 29;
}

u8 func_151D8EC8(void) {
    s32 tmp;

    if (func_150ADA20() & 1) {
        tmp = 17;
    } else {
        tmp = 147;
    }
    return tmp;
}

u8 func_151D8EFC(void) {
    s32 tmp;

    if (func_150ADA20() & 1) {
        tmp = 90;
    } else {
        tmp = 91;
    }
    return tmp;
}

u8 func_151D8F30(void) {
    u8 tmp[5] = D_800AB344;
    return tmp[func_150ADA20() % 5U];
}

u8 func_151D8F7C(void) {
    s32 tmp;

    if ((func_150ADA20() & 1) != 0) {
        tmp = 102;
    } else {
        tmp = 103;
    }
    return tmp;
}

u8 func_151D8FB0(void) {
    return 149;
}

u8 func_151D8FBC(void) {
    return 159;
}

u8 func_151D8FC8(void) {
    return 179;
}

u8 func_151D8FD4(void) {
    return 117;
}

u8 func_151D8FE0(void) {
    u8 tmp[4] = D_800AB34C;
    return tmp[func_150ADA20() & 3];
}

// big struct definition
// void func_151D9014(void *arg0, f32 *arg1, u8 arg2, f32 arg3, s16 arg4, u8 arg5, f32 arg6, u8 arg7, f32 arg8, f32 arg9, u8 argA, s32 argB, u8 argC, u8 argD, u8 argE, s32 argF);
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9014.s")

s32 func_151D93F4(void *arg0, void *arg1) {
    s32 res;

    if (func_151D9450(arg0, arg1) != 0) {
        if (func_151D9534(arg0, arg1) != 0) {
            res = 1;
        } else {
            res = 0;
        }
    } else {
        res = 0;
    }
    return res;
}

s32 func_151D9450(struct_eu_2062D0_d *arg0, s32 arg1) {
    struct_eu_2062D0_d_sub *sub = &arg0->unkA8;

    if (arg0->unkC1 & 1) {
        return 1;
    }
    sub->unk4 += sub->unk6 * D_800BE9E4;
    sub->unk5 += sub->unk7 * D_800BE9E4;
    arg0->unk38 = func_151423D8(sub->unk4 - 0x40) * sub->unk8 + sub->unk0;
    arg0->unk3C = func_151423D8(sub->unk5 - 0x40) * sub->unkC + sub->unk0;
    return 1;
}
#ifdef NON_MATCHING
s32 func_15046F70(f32 *, s32, f32, u8 *);
s32 func_1514672C(f32 *);

u8 func_151D9534(u8 *arg0, u8 *arg1) {
    struct {
        f32 u50;
        f32 u54;
        f32 u58;
        u8 pad5C[0x3];
        u8 u5F;
    } sp;
    f32 sp48;
    f32 temp_f0;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;

    sp.u5F = 1;
    if ((*(f32 *)((u8 *)arg0 + 0x44)) < (*(f32 *)((u8 *)arg1 + 4))) {
        sp.u50 = (*(f32 *)((u8 *)arg0 + 0x40));
        sp.u54 = (*(f32 *)((u8 *)arg1 + 4));
        sp.u58 = (*(f32 *)((u8 *)arg0 + 0x48));
        if (func_1514672C(&sp.u50) == 0) {
            return 0U;
        }
        if (func_15046F70(&sp.u50, 0, (*(f32 *)((u8 *)arg0 + 0x44)), arg0 + 0x80) != 0) {
            sp.u54 = (*(f32 *)((u8 *)arg0 + 0x80)) + 2.0f;
            if ((*(u8 *)((u8 *)arg0 + 0xC1)) & 2) {
                (*(f32 *)((u8 *)arg0 + 0x58)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x58)) * 0.39900002f);
                (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) (((*(f32 *)((u8 *)arg0 + 0x3C)) * 0.060000002f) + sp.u54);
                (*(f32 *)((u8 *)arg0 + 0x5C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x5C)) * -0.39900002f);
                (*(f32 *)((u8 *)arg0 + 0x60)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x60)) * 0.39900002f);
                if (fabsf((*(f32 *)((u8 *)arg0 + 0x5C))) < 0.326f) {
                    (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
                    (*(s32 *)((u8 *)arg0 + 0x68)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x68)) & ~6);
                    (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
                    (*(f32 *)((u8 *)arg0 + 0x60)) = 0.0f;
                    (*(f32 *)((u8 *)arg0 + 0x64)) = 0.0f;
                }
            } else {
                sp.u5F = 0;
                temp_v0 = arg0 + 0xA8;
                temp_f0 = ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x3C))) * 0.5f;
                if ((*(u8 *)((u8 *)arg0 + 0x9D)) == 3) {
                    func_151D9FC0((*(u8 *)((u8 *)temp_v0 + 0x18)), (*(f32 *)((u8 *)temp_v0 + 0x14)) * temp_f0, (*(u8 *)((u8 *)arg0 + 0x2B)), (s32) (arg0 + 0x84), (s32) &sp.u50, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                } else {
                    sp48 = temp_f0;
                    if (func_150ADA20() & 1) {
                        temp_v0_2 = arg0 + 0xA8;
                        func_151D9B8C((*(u8 *)((u8 *)temp_v0_2 + 0x18)), temp_f0 * 0.09f * (*(f32 *)((u8 *)temp_v0_2 + 0x10)), (*(u8 *)((u8 *)arg0 + 0x2B)), (s32) (arg0 + 0x84), (struct17 *) &sp.u50, 0x64, 0U, 1U, 0U, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                    } else {
                        temp_v0_3 = arg0 + 0xA8;
                        func_151DAB58((*(u8 *)((u8 *)temp_v0_3 + 0x18)), temp_f0 * 0.025f * (*(f32 *)((u8 *)temp_v0_3 + 0x10)), (*(u8 *)((u8 *)arg0 + 0x2B)), &sp.u50, 1, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                    }
                }
            }
        }
        goto block_12;
    }
block_12:
    return sp.u5F;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9534.s")
#endif
u8 func_151D97A8(void) {
    s32 tmp[7] = D_800AB350;
    return tmp[func_150ADA20() % 7U];
}

u8 func_151D9820(void) {
    s32 tmp[3] = D_800AB36C;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D9878(void) {
    s32 tmp[3] = D_800AB378;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D98D0(void) {
    s32 tmp[2] = D_800AB384;
    return tmp[func_150ADA20() & 1];
}

u8 func_151D9918(void) {
    s32 tmp[2] = D_800AB38C;
    return tmp[func_150ADA20() & 1];
}

u8 func_151D9960(void) {
    s32 tmp[5] = D_800AB394;
    return tmp[func_150ADA20() % 5U];
}

u8 func_151D99C8(void) {
    s32 tmp[3] = D_800AB3A8;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D9A20(void) {
    s32 tmp[2] = D_800AB3B4;
    return tmp[func_150ADA20() & 1];
}

u8 func_151D9A68(void) {
    s32 tmp[3] = D_800AB3BC;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D9AC0(void) {
    s32 tmp[1] = D_800AB3C8;
    return tmp[0];
}

u8 func_151D9ADC(void) {
    s32 tmp[3] = D_800AB3CC;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D9B34(void) {
    s32 tmp[4] = D_800AB3D8;
    return tmp[func_150ADA20() & 3];
}

#ifdef NON_MATCHING
f32 func_15144A74(s32 *, s32 *);
s32 func_15144E80(s32, s32 *, s32 *, s32 *);
s32 func_15145128(s32 *, s32 *, s32, s32);
extern s32 D_800900A4;
extern s32 D_800AB710;

s32 func_151D9B8C(u8 arg0, f32 arg1, u8 arg2, s32 arg3, struct17 *arg4, s16 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, s32 argA) {
    struct {
        s16 u60;
        u8 pad62[0x2];
        f32 u64;
        s32 u68;
        u8 pad6C[0x8];
        u8 u74;
        u8 u75;
        u8 u76;
        u8 pad77[0x5];
        s32 u7C;
        u8 pad80[0x8];
        s32 u88;
        u8 pad8C[0x8];
        s32 u94;
        u8 pad98[0x8];
        s32 uA0;
        u8 padA4[0xC];
        s32 uB0;
        s16 uB4;
        s8 uB6;
        s8 uB7;
        s32 uB8;
        s32 uBC;
        u8 uC0;
        s8 uC1;
        s8 uC2;
        s8 uC3;
        s8 uC4;
        s8 uC5;
        s8 uC6;
        s8 uC7;
        s32 uC8;
        s32 uCC;
        s8 uD0;
        u8 padD1[0x1];
        s16 uD2;
        s16 uD4;
    } sp;
    s32 sp50;
    s32 sp4C;
    s32 *temp_t5;
    s32 temp_t1;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    struct210 *var_v0;
    struct210 *var_v1_4;

    sp.uD2 = 0x20;
    sp.uD4 = 7;
    sp.uB6 = (*(s32 (**)())((u8 *)&D_800900A4 + (arg0 * 4)))();
    if (arg5 == -1) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    if (*(&D_800AB710 + arg0) != 0) {
        var_v0_2 = 0x20000;
    } else {
        var_v0_2 = 0;
    }
    sp.uB0 = var_v0_2 | var_v1 | 0xF700;
    if (arg5 == -1) {
        sp.uB4 = 0x12C;
    } else {
        sp.uB4 = arg5;
    }
    sp.uB8 = 0;
    sp.uBC = 0;
    sp.uC1 = 0xFF;
    sp.uC4 = 0;
    sp.uC3 = 0;
    sp.uC2 = 0;
    sp.uC5 = 0xFF;
    sp.uC0 = arg2;
    if (arg6 != 0) {
        var_v1_2 = 2;
    } else {
        var_v1_2 = 3;
    }
    var_v0_3 = 0x22;
    if (arg7 != 0) {
        var_v0_3 = 0x3B;
    }
    sp.uC8 = (var_v0_3 << 0x10) + var_v1_2;
    sp.uB7 = 0;
    sp.uC6 = 0;
    sp.uC7 = 7;
    sp.uD0 = 0xFF;
    sp.uCC = 0;
    sp4C = func_150ADA20();
    sp50 = func_150ADA20();
    temp_t1 = func_150ADA20();
    if (arg7 != 0) {
        var_v1_3 = 3;
    } else {
        var_v1_3 = 0;
    }
    if (arg7 != 0) {
        var_v0_4 = 0xFF;
    } else {
        var_v0_4 = 0;
    }
    var_v0 = func_1513C650((s32) &sp.uB0, 0U, 0U, arg3, arg4->unk0, arg4->unk4, arg4->unk8, arg1, arg1, (u8) (sp4C & 0xFF), (u8) (((temp_t1 & 1) * 2) + (sp50 & 1)), var_v1_3, var_v0_4, 0, (u8) (s32) arg9, argA);
    if ((var_v0 != NULL) && (arg8 != 0)) {
        var_v0 = func_15144E80(arg3, &sp.uA0, &sp.u94, &sp.u88);
        if (var_v0 != NULL) {
            temp_t5 = ((u8 *)&D_800AB7C8);
            (*(s32 *)((u8 *)(&sp.u7C) + 0)) = (s32) (*(s32 *)((u8 *)temp_t5 + 0));
            (*(s32 *)((u8 *)(&sp.u7C) + 4)) = (s32) (*(s32 *)((u8 *)temp_t5 + 4));
            (*(s32 *)((u8 *)(&sp.u7C) + 8)) = (s32) (*(s32 *)((u8 *)temp_t5 + 8));
            func_15145128(&sp.u88, &sp.u88, 0, 0);
            var_v0 = (struct210 *) arg5;
            if (func_15144A74(&sp.u88, &sp.u7C) < -0.5f) {
                sp.u60 = 0;
                var_v1_4 = var_v0;
                sp.u64 = arg1 * 4.5f;
                (*(f32 *)((u8 *)(&sp.u68) + 0)) = (f32) arg4->unk0;
                (*(f32 *)((u8 *)(&sp.u68) + 4)) = (f32) arg4->unk4;
                (*(f32 *)((u8 *)(&sp.u68) + 8)) = (f32) arg4->unk8;
                sp.u74 = arg2;
                sp.u75 = arg7;
                sp.u76 = arg0;
                if (var_v0 == (struct210 *)-1) {
                    var_v1_4 = (struct210 *)0x12C;
                }
                if (var_v0 == (struct210 *)-1) {
                    var_v0_5 = 0;
                } else {
                    var_v0_5 = 1;
                }
                var_v0 = func_15149130((s16) var_v1_4, -1, 0x4A, -1, (u8) var_v0_5, 0U, (struct37 *)0x18, (u8) (s32) arg9, argA);
                if (var_v0 != NULL) {
                    var_v0 = memcpy(&var_v0->pad20[8], &sp.u60, 0x18);
                }
            }
        }
    }
    return (s32) var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9B8C.s")
#endif
void func_151D9EB0(struct_eu_2062D0_e *arg0) {
    struct_eu_2062D0_e_sub *sub = &arg0->unk28;

    sub->unk0 -= D_800BE9E4;
    if (sub->unk0 < 0) {
        func_151D9014(sub->unk8, (f32 *)D_800A5860, sub->unk16, func_150ADA68() * D_800AB844 + D_800AB848, (u32)func_150ADA20() % 41 + 0x23, sub->unk14, sub->unk4, 0, 1.0f, 1.0f, sub->unk15, 0, 1, 0, arg0->unkC, arg0->unk1);
        sub->unk0 = (u32)func_150ADA20() % 111 + 30;
    }
}

void func_151D9FC0(u8 arg0, f32 arg1, u8 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    func_151DBCBC(arg0, arg1 * 0.5f, arg2, arg3, arg4, arg5, arg6);
    if ((arg0 != 5) && (arg0 != 2)) {
        func_151DA08C(arg0, arg1 * D_800AB46C, 1.0099999904632568f, arg2, 100, arg3, arg4, arg5, arg6);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA08C.s")
#ifdef NON_MATCHING
s32 func_151DB5D0(u8 arg0, u8 *arg1, u8 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s16 arg7, u8 arg8, s16 arg9, s16 argA, u8 argB, u8 argC, s32 argD);

s32 func_151DA368(u8 *arg0) {
    struct {
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
    } sp;
    f32 sp98;
    f32 sp94;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f2;
    s16 temp_s0;
    s16 temp_s0_2;
    u8 temp_a0;
    u8 *temp_s2;

    temp_a0 = (*(u8 *)((u8 *)arg0 + 0x128)) + ((*(s8 *)((u8 *)arg0 + 0x12A)) * D_800BE9E4);
    (*(u8 *)((u8 *)arg0 + 0x128)) = temp_a0;
    (*(u8 *)((u8 *)arg0 + 0x129)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x129)) + ((*(s8 *)((u8 *)arg0 + 0x12B)) * D_800BE9E4));
    temp_s2 = arg0 + 0x128;
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((func_151423D8((temp_a0 - 0x40) & 0xFF) * (*(f32 *)((u8 *)temp_s2 + 4))) + (*(f32 *)((u8 *)temp_s2 + 0x10)));
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((func_151423D8(((*(u8 *)((u8 *)temp_s2 + 1)) - 0x40) & 0xFF) * (*(f32 *)((u8 *)temp_s2 + 8))) + (*(f32 *)((u8 *)temp_s2 + 0x10)));
    (*(f32 *)((u8 *)temp_s2 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 0xC)) + ((0.15f + (func_150ADA68() * 0.1f)) * D_800BE9A4));
    temp_f2 = ((*(f32 *)((u8 *)arg0 + 0x2C)) + (*(f32 *)((u8 *)arg0 + 0x30))) * 0.5f;
    if ((*(f32 *)((u8 *)temp_s2 + 0xC)) > 1.0f) {
        sp98 = temp_f2 * 500.0f;
        sp94 = temp_f2 * 471.0f;
        do {
            temp_s0 = func_150ADA20() & 0xFF;
            temp_f20 = func_150ADA68() * sp98;
            temp_f22 = func_151423D8((temp_s0 - 0x40) & 0xFF);
            sp.uC4 = (*(f32 *)((u8 *)arg0 + 0x34)) + (func_151423D8(temp_s0 & 0xFF) * temp_f20);
            sp.uC8 = (*(f32 *)((u8 *)arg0 + 0x38)) + -3.5f;
            sp.uCC = (*(f32 *)((u8 *)arg0 + 0x3C)) + (temp_f22 * temp_f20);
            sp.uB8 = 0.0f;
            sp.uBC = 0.0f;
            sp.uC0 = 0.0f;
            temp_s0_2 = (func_150ADA20() % 51U) + 0x96;
            temp_f20_2 = func_150ADA68();
            func_151DB5D0((*(u8 *)((u8 *)temp_s2 + 0x18)), &sp.uC4, &sp.uB8, sp94, ((temp_f20_2 * 154.0f) + 10106.0f) * 0.0001f, 1.0f, ((func_150ADA68() * 25.0f) + -50.0f) * 0.001f, (s32) temp_s0_2, 0x9B, (s32) temp_s0_2, 0xFF / temp_s0_2, 1, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            (*(f32 *)((u8 *)temp_s2 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 0xC)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s2 + 0xC)) > 1.0f);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA368.s")
#endif
// TODO when we know what arg0 is...
s32 func_151DA6A8(struct_eu_2062D0 *arg0) {
    s32 i;
    struct_eu_2062D0_sub *p;

    if (arg0->unk58 & 1) {
        p = &arg0->unk128;
        i = D_800BE9E4;
        while (i--) {
            p->unk10 *= p->unk14;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA6F8.s")
typedef struct { f32 x, y, z; s32 a, b; } Node14;
extern f32 D_800AB87C;
s32 func_151DAB58(u8, f32, u8, f32 *, s32, s32, s32);
s32 func_151DA938(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5)
{
  u8 *tbl;
  u8 *obj;
  f32 pos[3];
  u8 *p;
  s32 pad;
  pad = 0x48; // fakematch: keeps obj + 0x48 in v0 (permuter)
  tbl = *((u8 **) (arg0 + 0x94));
  obj = *((u8 **) (arg0 + 0x98));
  pos[0] = ((Node14 *) tbl)[*((s8 *) (arg0 + 0x2D))].x;
  pos[1] = arg4 + 2.0f;
  pos[2] = ((Node14 *) tbl)[*((s8 *) (arg0 + 0x2D))].z;
  if (func_150ADA20() & 1)
  {
    p = obj + pad;
    func_151D9B8C(*((u8 *) (p + 8)), (*((f32 *) p)) * ((*((f32 *) (obj + 0))) * 3.0f), *((u8 *) (obj + 0x1B)), arg5, (struct17 *) pos, 0x64, 0, 1, 0, *((u8 *) (arg0 + 0xC)), *((u8 *) (arg0 + 1)));
  }
  else
  {
    p = obj + pad;
    func_151DAB58(*((u8 *) (p + 8)), (*((f32 *) p)) * ((*((f32 *) (obj + 0))) * D_800AB87C), *((u8 *) (obj + 0x1B)), pos, 1, *((u8 *) (arg0 + 0xC)), *((u8 *) (arg0 + 1)));
  }
  *((s8 *) (obj + 0x20)) = 4;
  return 1;
}
s32 func_151DAA88(struct_eu_2062D0_c *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    struct_eu_2062D0_c_sub *sub = arg0->unk98;
    struct_eu_2062D0_pt *pts = arg0->unk94;
    struct17 sp34;

    sp34.unk0 = pts[arg0->unk2D].unk0;
    sp34.unk4 = arg4;
    sp34.unk8 = pts[arg0->unk2D].unk8;
    func_151D9FC0(sub->unk50, sub->unk0 * 11.0f * sub->unk4C, sub->unk1B, arg5, &sp34, arg0->unkC, arg0->unk1);
    sub->unk20 = 4;
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DAB58.s")
s32 func_151DADA0(struct_eu_2062D0_b *arg0) {
    struct_eu_2062D0_b_sub *sub = &arg0->unk110;
    f32 f0;

    sub->unk0 += sub->unk1 * D_800BE9E4;
    f0 = func_151423D8(sub->unk0 - 0x40);
    arg0->unk4C = sub->unk4 * f0 + 1.0f;
    arg0->unk50 = D_800AB890 - sub->unk8 * f0;
    return 1;
}
#ifdef NON_MATCHING
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, s32, s32);
extern s32 D_800DD608;
extern s32 D_800DD618;

u8 *func_151DAE28(u8 *arg0, s16 arg1) {
    struct {
        u8 u37;
        u8 pad38[0x10];
        u8 * u48;
        u8 * u4C;
    } sp;
    u8 *sp30;
    s32 sp2C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    s32 temp_a1;
    s32 temp_f16;
    s32 temp_f16_2;
    s32 temp_f16_3;
    s32 temp_f6;
    s32 temp_f6_2;
    s32 temp_f8;
    s32 temp_t0;
    u8 *temp_v0;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u4C, &sp.u37);
    sp.u48 = sp.u4C;
    if (sp.u4C != NULL) {
        if (sp.u37 != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp2C = temp_a1;
            sp30 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_t0 = arg1 * 4;
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C)) * (*(f32 *)((u8 *)arg0 + 0x4C));
        (*(s16 *)((u8 *)sp.u4C + 6)) = 0;
        (*(s16 *)((u8 *)sp.u4C + 0x16)) = 0;
        temp_f2 = *(&D_800DD608 + temp_t0) * temp_f0;
        (*(s16 *)((u8 *)sp.u4C + 0x26)) = 0;
        temp_f12 = *(&D_800DD618 + temp_t0) * temp_f0;
        (*(s16 *)((u8 *)sp.u4C + 0x36)) = 0;
        temp_f8 = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12);
        (*(s16 *)((u8 *)sp.u4C + 0x30)) = (s16) temp_f8;
        (*(s16 *)((u8 *)sp.u4C + 0)) = (s16) temp_f8;
        temp_f16 = (s32) (*(f32 *)((u8 *)arg0 + 0x38));
        (*(s16 *)((u8 *)sp.u4C + 0x12)) = (s16) temp_f16;
        (*(s16 *)((u8 *)sp.u4C + 2)) = (s16) temp_f16;
        temp_f6 = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f2);
        (*(s16 *)((u8 *)sp.u4C + 0x34)) = (s16) temp_f6;
        (*(s16 *)((u8 *)sp.u4C + 4)) = (s16) temp_f6;
        temp_f16_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12);
        (*(s16 *)((u8 *)sp.u4C + 0x20)) = (s16) temp_f16_2;
        (*(s16 *)((u8 *)sp.u4C + 0x10)) = (s16) temp_f16_2;
        temp_f6_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x30)) * (*(f32 *)((u8 *)arg0 + 0x50))));
        (*(s16 *)((u8 *)sp.u4C + 0x32)) = (s16) temp_f6_2;
        (*(s16 *)((u8 *)sp.u4C + 0x22)) = (s16) temp_f6_2;
        temp_f16_3 = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f2);
        (*(s16 *)((u8 *)sp.u4C + 0x24)) = (s16) temp_f16_3;
        (*(s16 *)((u8 *)sp.u4C + 0x14)) = (s16) temp_f16_3;
        return sp.u48;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DAE28.s")
#endif
void func_151DB004(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = 0;
    arg0->unk16 = 0;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = 0;
    arg0->unk1A = 0;
}

void func_151DB068(struct218 *arg0) {
    arg0->unk14 = arg0->unk15 = (func_150ADA20() % 0x38U) + 100;
    arg0->unk16 = 0;
    arg0->unk18 = arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB0CC(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk16 = 0;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB15C(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk16 = 0;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB1EC(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk16 = 0;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB27C(struct218 *arg0) {
    arg0->unk14 = 0xFF;
    arg0->unk15 = 0xFF;
    arg0->unk16 = 0xFF;
    arg0->unk18 = 0xB4;
    arg0->unk19 = 0xC8;
    arg0->unk1A = 0xC8;
}

void func_151DB2A8(struct218 *arg0) {
    arg0->unk14 = 0;
    arg0->unk15 = 200;
    arg0->unk16 = 0;
    arg0->unk18 = 0;
    arg0->unk19 = 200;
    arg0->unk1A = 0;
}

void func_151DB2CC(struct218 *arg0) {
    arg0->unk14 = 0;
    arg0->unk15 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk16 = 0;
    arg0->unk18 = 0;
    arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB330(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x15U) + 95;
    arg0->unk15 = (func_150ADA20() % 0x15U) + 95;
    arg0->unk16 = (func_150ADA20() % 0xBU) + 45;
    arg0->unk18 = (func_150ADA20() & 0xF) + 58;
    arg0->unk19 = (func_150ADA20() & 0xF) + 60;
    arg0->unk1A = (func_150ADA20() % 0xBU) + 25;
}

void func_151DB3D8(struct218 *arg0) {
    arg0->unk14 = 0;
    arg0->unk15 = arg0->unk16 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk18 = 0;
    arg0->unk19 = arg0->unk1A = (func_150ADA20() % 0x2EU) + 180;
}

void func_151DB43C(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = 0;
    arg0->unk16 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = 0;
    arg0->unk1A = (func_150ADA20() % 0x2EU) + 180;
}

void func_151DB4CC(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 56U) + 200;
    arg0->unk15 = (func_150ADA20() % 56U) + 200;
    arg0->unk16 = (func_150ADA20() % 56U) + 200;
    arg0->unk18 = (func_150ADA20() % 56U) + 200;
    arg0->unk19 = (func_150ADA20() % 56U) + 200;
    arg0->unk1A = (func_150ADA20() % 56U) + 200;
}

#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
extern s32 D_800900D8;

s32 func_151DB5D0(u8 arg0, u8 *arg1, u8 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s16 arg7, u8 arg8, s16 arg9, s16 argA, u8 argB, u8 argC, s32 argD) {
    struct {
        s8 u30;
        u8 pad31[0x3];
        f32 u34;
        s8 u38;
        s8 u39;
        s8 u3A;
        s8 u3B;
        s8 u3C;
        s8 u3D;
        u8 pad3E[0x2];
        f32 u40;
        f32 u44;
        f32 u48;
        s32 u4C;
        s32 u50;
        s32 u54;
        s16 u58;
        s16 u5A;
        s32 u5C;
        s32 u60;
        u8 pad64[0x3];
        s8 u67;
        u8 pad68[0x3];
        u8 u6B;
        s8 u6C;
        s8 u6D;
        s16 u6E;
        s16 u70;
        s16 u72;
        f32 u74;
        f32 u78;
        f32 u7C;
        s32 u80;
        u8 pad84[0x8];
        s32 u8C;
        u8 pad90[0x8];
        s32 u98;
        u8 pad9C[0x8];
        f32 uA4;
        s32 uA8;
        s32 uAC;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        u8 padB7[0x1];
        s16 uB8;
        u8 padBA[0x2];
        f32 uBC;
    } sp;
    s32 sp20;
    s32 temp_v0;
    s32 var_t0;
    s32 var_t1;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    u8 *temp_t5;
    u8 *temp_t8;

    if (argB != 0) {
        var_v1_2 = 1;
    } else {
        var_v1_2 = 0;
    }
    if (arg5 == 1.0f) {
        var_v0 = 0;
    } else {
        var_v0 = 2;
    }
    sp.u30 = var_v0 | var_v1_2;
    sp.u34 = arg5;
    sp.u38 = 0;
    sp.u39 = 0;
    sp.u3A = 0;
    if (argB != 0) {
        sp.u3B = (func_150ADA20() % 7U) - 3;
        sp.u3C = (func_150ADA20() % 7U) - 3;
        sp.u3D = (func_150ADA20() % 7U) - 3;
        sp.u40 = ((func_150ADA68() * 0.05f) + 0.05f) * arg3;
        sp.u44 = ((func_150ADA68() * 0.03f) + 0.03f) * arg3;
        sp.u48 = ((func_150ADA68() * 0.05f) + 0.05f) * arg3;
    } else {
        temp_t8 = ((u8 *)&D_800A5860);
        sp.u3B = 0;
        sp.u3C = 0;
        sp.u3D = 0;
        (*(f32 *)((u8 *)(&sp.u40) + 0)) = (*(f32 *)((u8 *)temp_t8 + 0));
        (*(s32 *)((u8 *)(&sp.u40) + 4)) = (s32) (*(s32 *)((u8 *)temp_t8 + 4));
        (*(s32 *)((u8 *)(&sp.u40) + 8)) = (s32) (*(s32 *)((u8 *)temp_t8 + 8));
    }
    (*(s32 (**)())((u8 *)&D_800900D8 + (arg0 * 4)))(&sp.u50);
    sp.u6D = 0x6C;
    sp.u58 = 0x5103;
    sp.u50 = 0x200005;
    sp.u54 = 0x9F0600;
    if (arg7 == -1) {
        sp.u5A = 0x12C;
    } else {
        sp.u5A = arg7;
    }
    sp.u5C = 0;
    sp.u60 = 0;
    sp.u67 = 0xFF;
    sp.u6C = 0xFF;
    sp.u7C = arg3;
    sp.u78 = arg3;
    sp.u6B = arg8;
    temp_t5 = ((u8 *)&D_800A5860);
    (*(s32 *)((u8 *)(&sp.u80) + 0)) = (s32) (*(s32 *)((u8 *)arg1 + 0));
    (*(s32 *)((u8 *)(&sp.u80) + 4)) = (s32) (*(s32 *)((u8 *)arg1 + 4));
    (*(s32 *)((u8 *)(&sp.u80) + 8)) = (s32) (*(s32 *)((u8 *)arg1 + 8));
    (*(f32 *)((u8 *)(&sp.u8C) + 0)) = (f32) (*(f32 *)((u8 *)temp_t5 + 0));
    (*(s32 *)((u8 *)(&sp.u8C) + 4)) = (s32) (*(s32 *)((u8 *)temp_t5 + 4));
    (*(s32 *)((u8 *)(&sp.u8C) + 8)) = (s32) (*(s32 *)((u8 *)temp_t5 + 8));
    (*(s32 *)((u8 *)(&sp.u98) + 0)) = (s32) (*(s32 *)((u8 *)arg2 + 0));
    (*(s32 *)((u8 *)(&sp.u98) + 4)) = (s32) (*(s32 *)((u8 *)arg2 + 4));
    (*(s32 *)((u8 *)(&sp.u98) + 8)) = (s32) (*(s32 *)((u8 *)arg2 + 8));
    sp.uA4 = arg6;
    sp.u6E = arg9;
    sp.u70 = argA;
    if (arg7 == -1) {
        sp.u72 = 1;
    } else {
        sp.u72 = arg7;
    }
    sp.u74 = arg4;
    var_t1 = 0;
    if (func_150ADA20() & 1) {
        var_t1 = 0x80;
    }
    sp20 = var_t1;
    if (func_150ADA20() & 1) {
        var_t0 = 0x40;
    } else {
        var_t0 = 0;
    }
    if (arg7 == -1) {
        var_v1_3 = 0;
    } else {
        var_v1_3 = 1;
    }
    if (argB != 0) {
        var_v0_2 = 0x1000;
    } else {
        var_v0_2 = 0;
    }
    sp.uA8 = var_v0_2 | var_v1_3 | 6 | var_t0 | var_t1 | 0xCE00 | 0x40000 | 0x800000;
    sp.uB0 = 8;
    sp.uB1 = 6;
    sp.uB2 = 5;
    sp.uB3 = -1;
    sp.uB4 = -1;
    sp.uB5 = 0;
    sp.uAC = 0;
    sp.uB6 = 0xFF;
    sp.uB8 = 0x3E8;
    sp.uBC = 1000.0f;
    temp_v0 = func_151307F0(&sp.u50, 1, 0, 0x1C, (s32) argC, argD);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        sp.u4C = temp_v0;
        memcpy(temp_v0 + 0xA8, &sp.u30, 0x1C);
        var_v1 = sp.u4C;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DB5D0.s")
#endif
typedef struct { u8 fl; u8 pad1[3]; s32 unk4; u8 a[3]; u8 d[3]; u8 padE[2]; f32 s[3]; } S97C;
s32 func_15131E88(u8 *, s32);
s32 func_151DB97C(u8 *arg0, s32 arg1) {
    S97C *p;
    f32 z;
    f32 y;
    f32 x;
    p = (S97C *)(arg0 + 0xA8);
    if (p->fl & 2) {
        func_15131E88(arg0 + 0x58, *(s32 *)(arg0 + 0xAC));
    }
    if (p->fl & 1) {
        p->a[0] += p->d[0] * D_800BE9E4;
        p->a[1] += p->d[1] * D_800BE9E4;
        p->a[2] += p->d[2] * D_800BE9E4;
        x = func_151423D8(p->a[0] - 0x40);
        y = func_151423D8(p->a[1] - 0x40);
        z = func_151423D8(p->a[2] - 0x40);
        *(f32 *)(arg0 + 0x4C) = p->s[0] * x;
        *(f32 *)(arg0 + 0x50) = p->s[1] * y;
        *(f32 *)(arg0 + 0x54) = p->s[2] * z;
    }
    return 1;
}

extern f32 D_800AB8A0;
extern f32 D_800AB8A4;
extern f32 D_800AB8A8;
extern f32 D_800AB8AC;

void func_151DBAA8(struct17 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct_eu_15154488 s;

    s.unk8 = *arg0;
    s.unk14 = 5.5f;
    s.unk18 = D_800AB8A0;
    s.unk1C = D_800AB8A4;
    s.unk20 = D_800AB8A8;
    s.unk24 = 10.0f;
    s.unk28 = D_800AB8AC;
    s.unk2C = arg1;
    s.unk2E = 0;
    s.unk2 = 0xFF;
    s.unk4 = -0x40;
    s.unk6 = 0x2E;
    s.unk0 = 0;
    s.unk30 = 3;
    s.unk32 = 2;
    s.unk34 = 0x1E;
    s.unk36 = 0x1E;
    s.unk38 = 0x9B;
    s.unk3A = 0x64;
    s.unk44 = 0x10;
    s.unk46 = 0xF;
    s.unk40 = 0.5f;
    s.unk48 = 0;
    s.unk3C = arg2;
    func_15154488(&s, &s.unk8, 0, arg3, arg4);
}

void func_151DBBD4(struct17 *arg0, s32 arg1, u8 *arg2, u8 arg3, s32 arg4) {
    struct17 tmp;
    struct217 tmp2;

    tmp.unk0 = arg0->unk0;
    tmp.unk4 = arg0->unk4 + 5.0f;
    tmp.unk8 = arg0->unk8;

    tmp2.unkF = *arg2;
    tmp2.unk0 = func_150ADA68();
    tmp2.unk4 = func_150ADA20();

    func_151D9B8C(tmp2.unkF, (tmp2.unk0 * 25.0f) + 10.0f, ((tmp2.unk4 % 0x38U) + 200), arg1 + 4, &tmp, (func_150ADA20() % 0x97U) + 150, 0, 1, 0, arg3, arg4);
}

#ifdef NON_MATCHING
extern s32 D_800AB7F4;

void func_151DBCBC(u8 arg0, f32 arg1, s16 arg2, s32 arg3, void * arg4_p, u8 arg5, s32 arg6) {
    u8 * arg4 = (u8 *) arg4_p;
    struct {
        s32 u50;
        s16 u54;
        s8 u56;
        s8 u57;
        s32 u58;
        s32 u5C;
        s8 u60;
        s8 u61;
        u8 u62;
        u8 u63;
        u8 u64;
        s8 u65;
        s8 u66;
        s8 u67;
        s32 u68;
        s32 u6C;
        s8 u70;
        u8 pad71[0x1];
        s16 u72;
        s16 u74;
    } sp;
    s32 sp48;
    s32 sp44;
    u8 *temp_v0;

    temp_v0 = ((arg0 & 0xFF) * 3) + &D_800AB7F4;
    sp.u5C = 0x8000;
    sp.u56 = 0x38;
    sp.u50 = 0x67B02;
    sp.u54 = 0x12C;
    sp.u58 = 0;
    sp.u60 = (s8) arg2;
    sp.u61 = 0xFF;
    sp.u65 = 0xFF;
    sp.u68 = 0x440001;
    sp.u57 = 0;
    sp.u66 = 0;
    sp.u67 = 6;
    sp.u72 = 1;
    sp.u74 = 0xFF;
    sp.u70 = 0xFF;
    sp.u6C = 0;
    sp.u62 = (*(u8 *)((u8 *)temp_v0 + 0));
    sp.u63 = (*(u8 *)((u8 *)temp_v0 + 1));
    sp.u64 = (*(u8 *)((u8 *)temp_v0 + 2));
    if (arg3 != 0) {
        sp44 = func_150ADA20();
        sp48 = func_150ADA20();
        func_1513C73C((s32) &sp.u50, 0U, 0U, arg3, (*(f32 *)((u8 *)arg4 + 0)), (*(f32 *)((u8 *)arg4 + 4)), (*(f32 *)((u8 *)arg4 + 8)), arg1, arg1, (u8) (sp44 & 0xFF), (u8) (((func_150ADA20() & 1) * 2) + (sp48 & 1)), 0, (u8) (s32) arg5, arg6);
        return;
    }
    func_1513C5B0((s32) &sp.u50, 0, 0U, 0U, (*(f32 *)((u8 *)arg4 + 0)), (*(f32 *)((u8 *)arg4 + 4)), (*(f32 *)((u8 *)arg4 + 8)), arg1, arg1, 0U, 0U, 0, (u8) (s32) arg5, arg6);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBCBC.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800AB7F4;

void func_151DBE80(s32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, s32 arg5, u8 arg6, u8 arg7, u8 arg8, s32 arg9) {
    struct {
        s8 u58;
        s8 u59;
        s16 u5A;
        s16 u5C;
        u8 pad5E[0x2];
        s32 u60;
        s32 u64;
        u8 u68;
        u8 u69;
        u8 u6A;
        s8 u6B;
        f32 u6C;
        f32 u70;
        s32 u74;
        u8 pad78[0x8];
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        s32 u98;
        u8 u9C;
        s8 u9D;
        s8 u9E;
        s8 u9F;
        s32 uA0;
        s8 uA4;
        u8 padA5[0x3];
        s32 uA8;
        s16 uAC;
        s16 uAE;
    } sp;
    s32 sp50;
    s32 sp4C;
    s32 var_v1;
    u8 *temp_v0;

    sp.u58 = 0x38;
    if (arg7 != 0) {
        var_v1 = 2;
    } else {
        var_v1 = 1;
    }
    temp_v0 = ((arg0 & 0xFF) * 3) + &D_800AB7F4;
    sp.u5A = var_v1 + 0x440000;
    sp.u5C = arg3;
    sp.u60 = 0;
    sp.u64 = 0x4000;
    sp.u6B = 0xFF;
    sp.u68 = (*(u8 *)((u8 *)temp_v0 + 0));
    sp.u6C = 1.0f;
    sp.u70 = 1.0f;
    sp.u69 = (*(u8 *)((u8 *)temp_v0 + 1));
    sp.u6A = (*(u8 *)((u8 *)temp_v0 + 2));
    (*(s32 *)((u8 *)(&sp.u74) + 0)) = (s32) (*(s32 *)((u8 *)arg4 + 0));
    (*(s32 *)((u8 *)(&sp.u74) + 4)) = (s32) (*(s32 *)((u8 *)arg4 + 4));
    (*(s32 *)((u8 *)(&sp.u74) + 8)) = (s32) (*(s32 *)((u8 *)arg4 + 8));
    sp.u8C = arg2;
    sp.u98 = 0x466C0001;
    sp.u9D = 0xFF;
    sp.u59 = 0;
    sp.u9E = 0;
    sp.u9F = 6;
    sp.uA0 = 0;
    sp.uA4 = 0xFF;
    sp.uA8 = 0;
    sp.uAC = 1;
    sp.uAE = 0xFF;
    sp.u90 = 1.0f;
    sp.u94 = 1.0f;
    sp.u80 = 0.0f;
    sp.u84 = 0.0f;
    sp.u88 = 0.0f;
    sp.u9C = arg6;
    sp4C = func_150ADA20();
    sp50 = func_150ADA20();
    func_1513D668((s32) &sp.u58, 0, 0xBU, 0x11U, 0U, (u8) ((sp50 & 1) + (sp4C & 1)), (s16) (func_150ADA20() & 0xFF), arg1, arg1, 0, arg5, 0U, 0, (u8) (s32) arg8, arg9);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBE80.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DC034.s")
extern f32 D_800AB8B0;
extern f32 D_800AB8B4;
extern f32 D_800AB8B8;
extern f32 D_800AB8BC;
extern f32 D_800AB8C0;

typedef struct {
    s16 u0[4];
    struct17 pos;
    s16 u14;
    s16 u16;
    f32 u18;
    f32 u1C;
    s16 u20;
    s16 u22;
    f32 u24;
    f32 u28;
    u8 u2C;
    u8 u2D;
    f32 u30;
    f32 u34;
    u8 u38;
    u8 u39;
    f32 u3C;
    u8 u40;
    f32 u44;
} S06E8;

s32 func_151506E8(S06E8 *, struct17 *, s32, u8, s32);

void func_151DC260(struct17 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct_eu_15154488 s;
    S06E8 t;

    s.unk8 = *arg0;
    s.unk14 = 3.0f;
    s.unk18 = 4.0f;
    s.unk1C = D_800AB8B0;
    s.unk20 = D_800AB8B4;
    s.unk24 = 12.0f;
    s.unk28 = 11.0f;
    s.unk2C = 10;
    s.unk2E = 10;
    s.unk2 = 0xFF;
    s.unk4 = -0x40;
    s.unk6 = 0x28;
    s.unk0 = 0;
    s.unk30 = 3;
    s.unk32 = 1;
    s.unk34 = 0x3C;
    s.unk36 = 0x28;
    s.unk38 = 0x64;
    s.unk3A = 0x64;
    s.unk44 = 0x10;
    s.unk46 = 0xF;
    s.unk40 = 1.0f;
    s.unk48 = 0;
    s.unk3C = arg2;
    func_15154488(&s, &s.unk8, arg1, arg3, arg4);
    {
    struct17 *p = &t.pos;
    *p = *arg0;
    t.u18 = 6.0f;
    t.u1C = 8.0f;
    t.u14 = 0xC;
    t.u16 = 6;
    t.u0[0] = 0;
    t.u0[1] = 0xFF;
    t.u0[2] = -0x40;
    t.u24 = D_800AB8B8;
    t.u0[3] = 0x24;
    t.u20 = 0x23;
    t.u22 = 0xF;
    t.u28 = D_800AB8BC;
    t.u2C = 0x9B;
    t.u2D = 0x64;
    t.u38 = 1;
    t.u30 = 123.0f;
    t.u39 = arg2;
    t.u34 = 134.0f;
    t.u40 = 1;
    t.u3C = D_800AB8C0;
    t.u44 = 0.0f;
    func_151506E8(&t, p, arg1, arg3, arg4);
    }
}
extern f32 D_800AB8C4;
extern f32 D_800AB8C8;
extern f32 D_800AB8CC;
extern f32 D_800AB8D0;
extern f32 D_800AB8D4;



void func_151DC484(void *arg0, void *arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct_eu_15154488 s;
    S06E8 t;

    s.unk8 = *(struct17 *)arg0;
    s.unk0 = 0;
    s.unk14 = 3.0f;
    s.unk18 = 2.0f;
    s.unk1C = D_800AB8C4;
    s.unk20 = D_800AB8C8;
    s.unk24 = 8.0f;
    s.unk28 = 5.0f;
    s.unk2C = 8;
    s.unk2E = 6;
    s.unk2 = 0xFF;
    s.unk4 = -0x40;
    s.unk6 = 0x28;
    s.unk30 = 3;
    s.unk32 = 0;
    s.unk34 = 0x3C;
    s.unk36 = 0x28;
    s.unk38 = 0x64;
    s.unk3A = 0x64;
    s.unk44 = 0x10;
    s.unk46 = 0xF;
    s.unk40 = 1.0f;
    s.unk48 = 0;
    s.unk3C = arg2;
    func_15154488(&s, &s.unk8, (s32)arg1, arg3, arg4);
    {
    struct17 *p = &t.pos;
    *p = *(struct17 *)arg0;
    t.u18 = 7.0f;
    t.u1C = 3.0f;
    t.u24 = D_800AB8CC;
    t.u28 = D_800AB8D0;
    t.u14 = 0xC;
    t.u16 = 6;
    t.u0[0] = 0;
    t.u0[1] = 0xFF;
    t.u0[2] = -0x40;
    t.u0[3] = 0x1A;
    t.u20 = 0x23;
    t.u22 = 0xF;
    t.u2C = 0x9B;
    t.u2D = 0x64;
    t.u30 = 59.0f;
    t.u34 = 59.0f;
    t.u38 = 1;
    t.u39 = arg2;
    t.u3C = D_800AB8D4;
    t.u40 = 1;
    t.u44 = 0.0f;
    func_151506E8(&t, p, (s32)arg1, arg3, arg4);
    }
}

// typedef struct {
//     s16 unk10; // sp24
//     s16 unk12; // sp26
//     s16 unk14;
//     s16 unk16; // sp2A
//     s32 unk18[3];
//     s16 unk24; // sp38;
//     s16 unk26; // sp3A
//     f32 unk28; // sp3C
//     f32 unk2C; // sp40
//     s16 unk30; // sp44
//     s16 unk32; // sp46
//     f32 unk34; // sp48;
//     f32 unk38; // sp4C;
//     s8  unk3C; // sp50;
//     s8  unk3D; // sp51;
//     u8  unk3E[2]; //
//     f32 unk40; // sp54
//     f32 unk44; // sp58
//     s8  unk48; // sp5C
//     u8  unk49; // sp5D
//     u8  unk4A[2];
//     f32 unk4C; // sp60
//     s8  unk50; // sp64
//     u8  pad51[3];
//     f32 unk54; // sp68
// } struct217;
//
// typedef struct {
//     s16 unk58; // sp6C
//     s16 unk5A; // sp6E
//     s16 unk5C; // sp70
//     s16 unk5E; // sp72
//     s32 unk60[3]; // sp74
//     f32 unk6C; // sp80
//     f32 unk70; // sp84
//     f32 unk74; // sp88
//     f32 unk78; // sp8C
//     f32 unk7C; // sp90
//     f32 unk80; // sp94
//     s16 unk84; // sp98
//     s16 unk86; // sp9A
//     s16 unk88; // sp9C
//     s16 unk8A; // sp9E
//     s16 unk8C; // spA0
//     s16 unk8E; // spA2
//     s16 unk90; // spA4
//     s16 unk92; // spA6
//     u8  unk94; // spA8;
//     u8  pad95[3];
//     f32 unk98; // spAC;
//     s16 unk9C; // spB0
//     s16 unk9E; // spB2
//     s32 unkA0; // spB4
// } struct218;
//
// void func_151DC484(struct00 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
//     struct218 tmp2;
//     struct217 tmp;
//
//     tmp2.unk60[0] = arg0->unk0; // sp74.unk0 = (s32) arg0->unk0;
//     tmp2.unk60[1] = arg0->unk4; // sp74.unk4 = (s32) arg0->unk4;
//     tmp2.unk60[2] = arg0->unk8; // sp74.unk8 = (s32) arg0->unk8;
//
//     tmp2.unk5A = 0xFF;   // sp6E = 0xFF;
//     tmp2.unk5C = -0x40;  // sp70 = -0x40;
//     tmp2.unk84 = 8;      // sp98 = 8;
//     tmp2.unk86 = 6;      // sp9A = 6;
//     tmp2.unk58 = 0;      // sp6C = 0;
//     tmp2.unk88 = 3;      // sp9C = 3;
//     tmp2.unk8A = 0;      // sp9E = 0;
//     tmp2.unk5E = 0x28;   // sp72 = 0x28;
//     tmp2.unk8C = 0x3C;   // spA0 = 0x3C;
//     tmp2.unk8E = 0x28;   // spA2 = 0x28;
//
//     tmp2.unk6C = 3.0f;   // sp80 = 3.0f;
//     tmp2.unk90 = 100;     // spA4 = 0x64;
//     tmp2.unk92 = 100;     // spA6 = 0x64;
//     tmp2.unk9C = 16;      // spB0 = 0x10;
//     tmp2.unk9E = 15;      // spB2 = 0xF;
//     tmp2.unk70 = 2.0f;       // sp84 = 2.0f;
//     tmp2.unk74 = D_800AB4E4; // sp88 = D_800AB4E4;
//     tmp2.unk78 = D_800AB4E8; // sp8C = D_800AB4E8;
//     tmp2.unk7C = 8.0f;       // sp90 = 8.0f;
//     tmp2.unk80 = 5.0f;       // sp94 = 5.0f;
//     tmp2.unk98 = 1.0f;       // spAC = 1.0f; 0x3f80
//     tmp2.unk94 = arg2;       // spA8 = arg2;
//     tmp2.unkA0 = 0;      // spB4 = 0;
//
//     // func_15153F18(&sp6C, &sp74, arg1, arg3, arg4);
//     func_15153F18(&tmp2, &tmp2, arg1, arg3, arg4);
//
//     tmp.unk18[0] = arg0->unk0; // sp2C.unk0 = (s32) arg0->unk0;
//     tmp.unk18[1] = arg0->unk4; // sp2C.unk4 = (s32) arg0->unk4;
//     tmp.unk18[2] = arg0->unk8; // sp2C.unk8 = (s32) arg0->unk8;
//
//     tmp.unk24 = 0xC; // sp38 = 0xC;
//     tmp.unk12 = 0xFF;   // sp26 = 0xFF;
//     tmp.unk26 = 6;      // sp3A = 6;
//     tmp.unk10 = 0;      // sp24 = 0;
//     tmp.unk14 = -0x40;  // sp28 = -0x40;
//     tmp.unk16 = 0x1A;   // sp2A = 0x1A;
//     tmp.unk30 = 0x23;   // sp44 = 0x23;
//     tmp.unk32 = 0xF;    // sp46 = 0xF;
//     tmp.unk3C = 0x9B;   // sp50 = 0x9B;
//     tmp.unk3D = 0x64;   // sp51 = 0x64;
//     tmp.unk40 = 59.0f;  // sp54 = 59.0f;
//     tmp.unk44 = 59.0f;  // sp58 = 59.0f;
//     tmp.unk48 = 1;      // sp5C = 1;
//     tmp.unk50 = 1;      // sp64 = 1;
//     tmp.unk54 = 0.0f;   // sp68 = 0.0f;
//     tmp.unk28 = 7.0f;   // sp3C = 7.0f;
//     tmp.unk2C = 3.0f;   // sp40 = 3.0f;
//     tmp.unk34 = D_800AB4EC; // sp48 = D_800AB4EC;
//     tmp.unk38 = D_800AB4F0; // sp4C = D_800AB4F0;
//     tmp.unk49 = arg2;       // sp5D = arg2;
//     tmp.unk4C = D_800AB4F4; // sp60 = D_800AB4F4;
//     // func_15150178(&sp24, &sp2C, arg1, arg3, arg4);
//     func_15150178(&tmp, &tmp.unk18, arg1, arg3, arg4);
// }
