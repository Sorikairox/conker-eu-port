#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A5860[];
#endif
// hoisted forward declaration(s) for func_150D6898
s32 func_15154728(s32, f32, s32, f32, f32, s32, s32);


void func_150D5950(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_15149130(300, -1, 0x38, -1, 0, 0x28, 0xC, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void func_1514373C(f32, f32, f32 *, f32 *);
s32 func_1515C668(u8 *, u8 **);

void func_150D59D8(u8 *arg0) {
    struct {
        u8 * u84;
        u8 pad88[0x8];
        f32 u90;
        f32 u94;
        s32 u98;
        s32 u9C;
        s16 uA0;
        s16 uA2;
        s32 uA4;
        s32 uA8;
        s8 uAC;
        s8 uAD;
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s8 uB4;
        s8 uB5;
        s16 uB6;
        s16 uB8;
        s16 uBA;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        s32 uF0;
        s32 uF4;
        s8 uF8;
        s8 uF9;
        s8 uFA;
        s8 uFB;
        s8 uFC;
        s8 uFD;
        s8 uFE;
    } sp;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f24;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f6;
    f32 var_f12;
    f32 var_f12_2;
    f32 var_f14;
    f32 var_f2;
    s32 temp_s0;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_s1;
    u8 *temp_s2;

    temp_s2 = (*(u8 **)((u8 *)arg0 + 0x28));
    temp_s1 = arg0 + 0x28;
    if (((*(s32 *)((u8 *)temp_s2 + 0)) == 0) || ((*(u8 *)((u8 *)temp_s1 + 4)) != (*(u8 *)((u8 *)temp_s2 + 0x3B)))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    if (((*(f32 *)((u8 *)temp_s2 + 0x28)) < 8.0f) && (((*(s32 *)((u8 *)temp_s2 + 0x184)) & 0x1F) == 0xE)) {
        (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) + ((3.0000002f + (func_150ADA68() * 1.0f)) * D_800BE9A4));
        if ((*(f32 *)((u8 *)temp_s1 + 8)) > 1.0f) {
            if (func_1515C668(temp_s2, &sp.u84) == 0) {
                sp.u84 = ((u8 *)&D_800A5860);
            }
            func_1514373C((*(f32 *)((u8 *)temp_s2 + 0x40)) * 0.017453292f, 0x3F800000, &sp.u90, &sp.u94);
            sp.uB5 = 0x28;
            sp.uAD = 0xFF;
            sp.uA0 = 0x2203;
            sp.u98 = 0x200005;
            sp.uAC = 0xFF;
            sp.uAE = 0xFF;
            sp.uAF = 0xFF;
            sp.uB0 = 0xFF;
            sp.uB1 = 0xFF;
            sp.uB2 = 0xFF;
            sp.u9C = 0;
            sp.uA4 = 0;
            sp.uA8 = 0;
            sp.uB4 = 0xFF;
            sp.uB6 = 5;
            sp.uB8 = 0x33;
            sp.uBA = 1;
            sp.uF0 = 0x84C207;
            sp.uF8 = 6;
            sp.uF9 = 8;
            sp.uFA = -1;
            sp.uFB = -1;
            sp.uFC = -1;
            sp.uFD = 0;
            sp.uF4 = 0;
            sp.uFE = 0xFF;
            sp.uBC = 1.0f;
            sp.uD4 = 0.0f;
            sp.uD8 = 0.0f;
            sp.uDC = 0.0f;
            temp_f24 = -sp.u90;
            do {
                temp_s0 = func_150ADA20() & 1;
                temp_f20 = func_150ADA68();
                temp_f0 = func_150ADA68();
                if (temp_s0 != 0) {
                    var_f14 = 35.0f;
                } else {
                    var_f14 = -35.0f;
                }
                temp_f2 = sp.u90 * 180.0f;
                temp_f12 = sp.u94 * 180.0f;
                sp.uC8 = (((*(f32 *)((u8 *)temp_s2 + 0x14)) + (sp.u94 * var_f14)) - (temp_f2 * 0.5f)) + (temp_f2 * temp_f20);
                sp.uCC = (*(f32 *)((u8 *)temp_s2 + 0x180));
                sp.uD0 = (((*(f32 *)((u8 *)temp_s2 + 0x1C)) + (temp_f24 * var_f14)) - (temp_f12 * 0.5f)) + (temp_f12 * temp_f20);
                if (temp_s0 != 0) {
                    var_f2 = (temp_f0 * 2.907f) + 6.0000005f;
                    var_f12 = var_f2;
                } else {
                    var_f2 = (temp_f0 * 2.907f) + 6.0000005f;
                    var_f12 = -var_f2;
                }
                sp.uE0 = (var_f12 * sp.u94) - ((*(f32 *)((u8 *)sp.u84 + 0)) * 0.564f);
                sp.uE4 = 3.1560001f * var_f2;
                if (temp_s0 != 0) {
                    var_f12_2 = var_f2;
                } else {
                    var_f12_2 = -var_f2;
                }
                sp.uE8 = (var_f12_2 * temp_f24) - ((*(f32 *)((u8 *)sp.u84 + 8)) * 0.564f);
                sp.uA2 = (func_150ADA20() % 10U) + 0x1F;
                sp.uB3 = (func_150ADA20() % 76U) + 0xB4;
                temp_f2_2 = (func_150ADA68() * 364.0f) + 111.0f;
                sp.uC0 = temp_f2_2;
                sp.uC4 = temp_f2_2;
                temp_f6 = func_150ADA68() * 0.157f;
                sp.uF0 &= ~0xC0;
                sp.uEC = temp_f6 + -2.111f;
                var_s0 = 0;
                if (func_150ADA20() & 1) {
                    var_s0 = 0x80;
                }
                if (func_150ADA20() & 1) {
                    var_v0 = 0x40;
                } else {
                    var_v0 = 0;
                }
                sp.uF0 |= var_v0 | var_s0;
                func_151307F0(&sp.u98, 1, 0, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s1 + 8)) > 1.0f);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D59D8.s")
#endif
void func_150D5E7C(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x28;
    if (arg2 == 0 || arg2 == 0x2F || arg2 == 3) {
        s32 t = *(s32 *)arg1;
        if (t == *(s32 *)v || v[4] == arg1[4]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
            *(s32 *)v = *(s32 *)arg1;
            v[4] = arg1[8];
        }
    }
}

void func_150D5F3C(struct260 *arg0) {
    func_1514933C(arg0);
}

void func_150D5F5C(struct260 *arg0) {
    func_15149368(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D5F7C.s")

void func_150D6898(s32 arg0, u8 arg1, s32 arg2) {
    f32 temp_f12;
    f32 sp28;
    f32 temp_f14;
    f32 var_f18;
    u32 temp_t7;
    sp28 = func_150ADA68();
    temp_t7 = (func_150ADA20() % 56U) + 0xC8;
    temp_f14 = sp28 * 4.0f;
    temp_f12 = temp_f14 + 15.0f;
    var_f18 = (f32) temp_t7;
    func_15154728(arg0, temp_f12, 0x3FAFF1E9, var_f18, 0.0f, arg1, arg2);
}

s32 func_15154DF4(s32, f32, f32, f32, u8, s32);
extern f32 D_800A0E80;
extern f32 D_800A0E84;

void func_150D6944(s32 arg0, u8 arg1, s32 arg2) {
    s32 pad;
    f32 sp28;
    f32 sp24;

    sp24 = func_150ADA68();
    sp28 = func_150ADA68();
    func_15154DF4(arg0, (sp24 * 3.0f) + 8.0f, (sp28 * D_800A0E80) + D_800A0E84, (func_150ADA68() * 50.0f) + 100.0f, (s32) arg1, arg2);
}

#ifdef NON_MATCHING
extern f32 D_800A0E88;
extern f32 D_800A0E8C;
extern f32 D_800A0E90;
extern f32 D_800A0E94;
extern f32 D_800A0E98;
void func_150D69F8(u8 *arg0, f32 *arg1) {
    (*(s32 *)((u8 *)arg0 + 0)) = 6;
    (*(s32 *)((u8 *)arg0 + 4)) = 3;
    *arg1 = D_800A0E88;
    (*(f32 *)((u8 *)arg0 + 0x14)) = D_800A0E8C;
    (*(s32 *)((u8 *)arg0 + 0x2C)) = 4;
    (*(s32 *)((u8 *)arg0 + 0x30)) = 3;
    (*(f32 *)((u8 *)arg0 + 0x18)) = D_800A0E90;
    (*(f32 *)((u8 *)arg0 + 0x1C)) = 150.0f;
    (*(f32 *)((u8 *)arg0 + 0x20)) = 105.0f;
    (*(f32 *)((u8 *)arg0 + 0x24)) = 396.0f;
    (*(f32 *)((u8 *)arg0 + 0x28)) = 612.0f;
    (*(f32 *)((u8 *)arg0 + 0x34)) = 25.0f;
    (*(f32 *)((u8 *)arg0 + 0x38)) = D_800A0E94;
    (*(f32 *)((u8 *)arg0 + 0x3C)) = -2.0f;
    (*(s16 *)((u8 *)arg0 + 0x44)) = 0x14;
    (*(s16 *)((u8 *)arg0 + 0x46)) = 0x1E;
    (*(s16 *)((u8 *)arg0 + 0x48)) = 0x64;
    (*(s16 *)((u8 *)arg0 + 0x4A)) = 0x64;
    (*(s16 *)((u8 *)arg0 + 0x4C)) = 0xC;
    (*(s16 *)((u8 *)arg0 + 0x4E)) = 0x14;
    (*(f32 *)((u8 *)arg0 + 0x40)) = D_800A0E98;
    if ((D_80082FA0 >= 2) || (D_8008FD8C >= 8)) {
    s32 pad;
        (*(s8 *)((u8 *)arg0 + 0x50)) = -1;
        return;
    }
    (*(s8 *)((u8 *)arg0 + 0x50)) = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D69F8.s")
#endif
s32 func_151A6308(f32, s32, s32, s32, s16, u8, u8, u8, s32);

void func_150D6B00(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 pad;
    u32 sp38;
    f32 sp34;

    sp34 = func_150ADA68();
    sp38 = func_150ADA20();
    func_151A6308((sp34 * 100.0f) + 150.0f, ((sp38 % 71U) + 0x82) & 0xFF, arg0, arg1, (func_150ADA20() % 31U) + 0x32, 0, 1, (s32) arg2, arg3);
}

s32 func_15182BE0(u8, u8, u8, s32, s16, u8, u8, s32); 

void func_150D6BB4(u8 arg0, u8 arg1, s32 arg2) {
    s32 pad;
    u32 sp28;

    sp28 = func_150ADA20();
    func_15182BE0(0xFF, 0xFF, 0xFF, ((sp28 % 56U) + 0xC8) & 0xFF, (func_150ADA20() % 6U) + 0x19, (s32) arg0, (s32) arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D6C40.s")

void func_150D71A8(f32 *arg0, f32 *arg1) {
    arg1[0] = arg0[5];
    arg1[1] = arg0[6] + 60.0f;
    arg1[2] = arg0[7];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D71D4.s")

void func_150D7370(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0xA8;
    if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else {
            if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
                *(s32 *)v = *(s32 *)arg1;
                v[4] = arg1[8];
            }
            goto end; // fakematch: permuter artifact (no-op jump keeps this arm's exit)
end:        ;
        }
    } else {
        if (arg1) { // fakematch: permuter artifact (empty if)
        }
        if (arg2 == 0) {
            s32 t = *(s32 *)arg1;
            if (t == *(s32 *)v || v[4] == arg1[4]) {
                func_1516972C(arg0);
            }
        }
    }
}

#ifdef NON_MATCHING
s32 func_150D741C(u8 *arg0, s32 arg1) {
    u8 *sp18;
    f32 *temp_a3;
    f32 temp_f12;
    f32 temp_f2;
    s32 var_v0;
    u8 *temp_v0;

    temp_a3 = (*(f32 **)((u8 *)arg0 + 0xA8));
    temp_v0 = arg0 + 0xA8;
    if (((*(s32 *)((u8 *)temp_a3 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_a3 + 0x3B)))) {
        return 0;
    }
    sp18 = temp_v0;
    func_150D71A8(temp_a3, arg0 + 0x40);
    temp_f2 = sqrtf((*(f32 *)((u8 *)temp_v0 + 8))) * (*(f32 *)((u8 *)temp_v0 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = temp_f2;
    (*(f32 *)((u8 *)arg0 + 0x38)) = temp_f2;
    temp_f12 = (*(f32 *)((u8 *)temp_v0 + 8));
    (*(s8 *)((u8 *)arg0 + 0x2B)) = (s8) (u32) ((*(f32 *)((u8 *)temp_v0 + 0x14)) - ((*(f32 *)((u8 *)temp_v0 + 0x18)) * temp_f12 * temp_f12));
    (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 8)) + D_800BE9A4);
    var_v0 = 1;
    if ((*(f32 *)((u8 *)temp_v0 + 0xC)) < (*(f32 *)((u8 *)temp_v0 + 8))) {
        var_v0 = 0;
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D741C.s")
#endif
void func_150D7578(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0xA8;
    if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else {
            if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
                *(s32 *)v = *(s32 *)arg1;
                v[4] = arg1[8];
            }
            goto end; // fakematch: permuter artifact (no-op jump keeps this arm's exit)
end:        ;
        }
    } else {
        if (arg1) { // fakematch: permuter artifact (empty if)
        }
        if (arg2 == 0) {
            s32 t = *(s32 *)arg1;
            if (t == *(s32 *)v || v[4] == arg1[4]) {
                func_1516972C(arg0);
            }
        }
    }
}
