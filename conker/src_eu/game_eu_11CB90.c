#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8  pad0[0x8];
    s32 *unk8;
    u8  unkC;
} struct_eu_11CB90_60;

typedef struct {
    u8  pad0[0x12C];
    s32 unk12C[1];
} struct_eu_11CB90_elem;

void func_150F0820(void *arg0);
void func_150F0898(void *arg0);
void func_150F0900(void *arg0);
void func_150F0968(void *arg0);
void func_151617C4(void *arg0);
void func_151617E4(void *arg0);


extern u8 D_800A1A0C[];
extern u8 D_800A1A08[];
extern struct17 D_800A19C0[];
void func_150EF500(struct127 *, u8, s32, s32);
void func_150F0FA4(u8 *);

void func_150EEE00(struct127 *arg0, u8 arg1) {
    struct17 pos;
    Header header;
    Header2 header2;

    if (D_800A1A0C[arg1] & arg0->unk94) {
        return;
    }
    func_150EF500(arg0, arg1, 0xFF, 1);
    if (arg0->unk1D4 == NULL) {
        return;
    }
    func_15143134(&D_800A19C0[arg1], &pos, (u8 *)(0, arg0->unk1D4) + (D_800A1A08[arg1] << 6)); // fakematch: comma from the permuter (register choice)
    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (u32)func_150ADA20() % 3 + 4;
    header.unk4 = 0;
    header2.unk0 = pos.unk0;
    header2.unk4 = pos.unk4;
    header2.unk8 = pos.unk8;
    func_151602C0(&header, &header2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
    func_150F0FA4((u8 *)&pos);
}

void func_150EEF40(u8 *arg0, u8 arg1) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk5 = arg1;
    func_151403A8(&tmp, 0x43);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EF500.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EF90C.s")

s32 func_150EFD04(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0[4] == 0x28) {
        return 1;
    }
    return 0;
}

void func_150EFD30(u8 *arg0) {
    u8 **q = &arg0; // fakematch: forces the arg0 home-slot reload
    s32 var_s0;
    struct102 *temp_a0;
    struct102 *temp_a0_2;
    struct102 *temp_a0_3;
    struct102 *temp_a0_4;
    u8 *temp_s3;
    u8 *var_s1;

    var_s0 = 0;
    temp_s3 = *q + 0x110;
    var_s1 = temp_s3;
    do {
        temp_a0 = (*(struct102 **)((u8 *)var_s1 + 0x1C));
        if (temp_a0 != NULL) {
            func_1516972C(temp_a0);
        }
        var_s0 += 4;
        var_s1 += 4;
    } while (var_s0 != 8);
    temp_a0_2 = (*(struct102 **)((u8 *)temp_s3 + 0x24));
    if (temp_a0_2 != NULL) {
        func_1516972C(temp_a0_2);
    }
    temp_a0_3 = (*(struct102 **)((u8 *)temp_s3 + 0x28));
    if (temp_a0_3 != NULL) {
        func_1516972C(temp_a0_3);
    }
    temp_a0_4 = (*(struct102 **)((u8 *)temp_s3 + 0x2C));
    if (temp_a0_4 != NULL) {
        func_1516972C(temp_a0_4);
    }
    func_1513CA6C(*q);
}

void func_150EFDE0(u8 *arg0) {
    u8 **q = &arg0; // fakematch: forces the arg0 home-slot reload
    s32 var_s0;
    struct102 *temp_a0;
    struct102 *temp_a0_2;
    struct102 *temp_a0_3;
    struct102 *temp_a0_4;
    u8 *temp_s3;
    u8 *var_s1;

    var_s0 = 0;
    temp_s3 = *q + 0x110;
    var_s1 = temp_s3;
    do {
        temp_a0 = (*(struct102 **)((u8 *)var_s1 + 0x1C));
        if (temp_a0 != NULL) {
            func_1516979C(temp_a0);
        }
        var_s0 += 4;
        var_s1 += 4;
    } while (var_s0 != 8);
    temp_a0_2 = (*(struct102 **)((u8 *)temp_s3 + 0x24));
    if (temp_a0_2 != NULL) {
        func_1516979C(temp_a0_2);
    }
    temp_a0_3 = (*(struct102 **)((u8 *)temp_s3 + 0x28));
    if (temp_a0_3 != NULL) {
        func_1516979C(temp_a0_3);
    }
    temp_a0_4 = (*(struct102 **)((u8 *)temp_s3 + 0x2C));
    if (temp_a0_4 != NULL) {
        func_1516979C(temp_a0_4);
    }
    func_1513CAA0(*q);
}

void func_150EFE90(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x110;
    if (arg2 == 0) {
        s32 x = *(s32 *)v; s32 y = *(s32 *)arg1; s32 p = v[4]; s32 q = arg1[4];
        if (x == y || q == p) {
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
        if (*(s32 *)arg1 == *(s32 *)(v + 8)) {
            *(s32 *)(v + 8) = *(s32 *)(arg1 + 4);
            v[0xC] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)(v + 8)) {
            *(s32 *)(v + 8) = *(s32 *)arg1;
            v[0xC] = arg1[8];
        }
        goto end; end: ; // fakematch: no-op label ends the 0x2D arm like the ref (b to the epilogue not delay-filled)
    } else if (arg2 == 0x43) {
        if (*(s32 *)arg1 == *(s32 *)v || arg1[4] == v[4]) {
            if (arg1[5] == v[0xD]) {
                func_1516972C(arg0);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EFFCC.s")

#ifdef NON_MATCHING
void func_15143794(s16, s16, f32, void *);
s32 func_1515C2F0(s32 *, s32, f32 *, s32, s32, s32);

void func_150F0100(u8 *arg0) {
    struct {
        f32 u8C;
        s32 u90;
        u8 pad94[0x8];
        f32 u9C;
        s8 uA0;
        s8 uA1;
        s8 uA2;
        s8 uA3;
        s8 uA4;
        s8 uA5;
        s8 uA6;
        s8 uA7;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        s8 uAD;
        u8 padAE[0x2];
        s32 uB0;
        s32 uB4;
        s16 uB8;
        s16 uBA;
        s16 uBC;
        s8 uBE;
        u8 padBF[0x1];
        f32 uC0;
        s8 uC4;
        s8 uC5;
        u8 padC6[0x2];
        s32 uC8;
        u8 padCC[0x8];
        s16 uD4;
        s16 uD6;
        s32 uD8;
        u8 padDC[0x1];
        s8 uDD;
    } sp;
    s32 temp_s1;
    s32 temp_s2;
    u8 *temp_s0;
    u8 *temp_v0;

    temp_s0 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s0 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 4)) + ((364.0f + (func_150ADA68() * 300.0f)) * 0.001f));
    if ((*(f32 *)((u8 *)temp_s0 + 4)) > 1.0f) {
        temp_v0 = (*(u8 **)((u8 *)temp_s0 + 0));
        if ((*(u8 *)((u8 *)temp_v0 + 0x128)) & 1) {
            (*(s32 *)((u8 *)(&sp.uC8) + 0)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0x40));
            (*(s32 *)((u8 *)(&sp.uC8) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0x44));
            (*(s32 *)((u8 *)(&sp.uC8) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0x48));
            sp.uD8 = 0xA;
            sp.uA0 = 4;
            sp.uD6 = 5;
            sp.uA1 = 2;
            sp.uA2 = 3;
            sp.uA3 = 0x9D;
            sp.uA4 = 0x72;
            sp.uA5 = 0x2E;
            sp.uA7 = 0;
            sp.uA8 = 0;
            sp.uA9 = 0;
            sp.uAA = 0;
            sp.uAB = 0xFF;
            sp.uAC = 3;
            sp.uAD = 0x24;
            sp.uB0 = 0x200005;
            sp.uB4 = 0x60600;
            sp.uB8 = 0xC;
            sp.uBA = 0x15;
            sp.uBC = 1;
            sp.uBE = 0;
            sp.uC0 = 1.0f;
            sp.uC4 = -1;
            sp.uC5 = 0;
            do {
                sp.uDD = (func_150ADA20() % 3U) + 3;
                sp.uD4 = (func_150ADA20() & 0xF) + 0x28;
                sp.u8C = (func_150ADA68() * 10.0f) + 22.0f;
                temp_s1 = func_150ADA20();
                temp_s2 = func_150ADA20();
                func_15143794((s16) (temp_s1 & 0xFF), (s16) (((u32) temp_s2 % 31U) - 0x37), (func_150ADA68() * 15.0f) + 25.0f, &sp.u90);
                sp.u9C = ((func_150ADA68() * 740.0f) + -1761.0f) * 0.001f;
                sp.uA6 = (func_150ADA20() % 101U) + 0x9B;
                func_1515C2F0(&sp.uC8, 0, &sp.u8C, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                (*(f32 *)((u8 *)temp_s0 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 4)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s0 + 4)) > 1.0f);
            return;
        }
        do {
            (*(f32 *)((u8 *)temp_s0 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 4)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 4)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0100.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0448.s")

#ifdef NON_MATCHING
s32 func_150F066C(u8 *arg0) {
    s32 temp_t4;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x178));
    if ((*(u8 *)((u8 *)temp_v0 + 0x128)) & 1) {
        temp_v1 = temp_v0 + 0x110;
        (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x34));
        (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x38));
        (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x3C));
        (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x34)) + ((*(f32 *)((u8 *)temp_v1 + 0x30)) * 500.0f));
        (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x38)) + ((*(f32 *)((u8 *)temp_v1 + 0x34)) * 500.0f));
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x58)) | 6);
        (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x3C)) + ((*(f32 *)((u8 *)temp_v1 + 0x38)) * 500.0f));
    } else {
        temp_t4 = (*(s32 *)((u8 *)arg0 + 0x58)) & ~4;
        (*(s32 *)((u8 *)arg0 + 0x58)) = temp_t4;
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) (temp_t4 & ~2);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F066C.s")
#endif
struct225 *func_150F0718(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6) {
    struct225 *r;
    s8 sp4C[8];
    s32 sp40[3];
    s32 sp3C;
    struct225 *sp54;

    sp3C = arg4;
    sp4C[0] = 2;
    sp4C[1] = -1;
    *(s16 *)(sp4C + 2) = 0x12C;
    sp4C[4] = 0x21;
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    r = func_151602C0(sp4C, sp40, arg0, arg1, arg2, arg3, 0xFF, 0, 4, arg5, arg6);
    if (r != NULL) {
        memcpy((u8 *)r + 0x18, &sp3C, 4);
        sp54 = r;
        r = sp54;
    }
    return r;
}

void func_150F07E0(void *arg0) {
    func_150F0820(arg0);
}

void func_150F0800(void *arg0) {
    func_150F0820(arg0);
}

void func_150F0820(void *arg0) {
    struct_eu_11CB90_60 *temp_v0 = *(struct_eu_11CB90_60 **)((u8 *)arg0 + 0x60);
    s32 *temp_v1 = temp_v0->unk8;
    ((struct_eu_11CB90_elem *)temp_v1)->unk12C[temp_v0->unkC] = 0;
}

void func_150F0840(void *arg0) {
    func_150F0898(arg0);
    func_1514933C(arg0);
}

void func_150F086C(void *arg0) {
    func_150F0898(arg0);
    func_15149368(arg0);
}

void func_150F0898(void *arg0) {
    u8 *temp_v0 = *(u8 **)((u8 *)arg0 + 0x28);
    *(s32 *)(temp_v0 + 0x134) = 0;
}

void func_150F08A8(void *arg0) {
    func_150F0900(arg0);
    func_151411A4(arg0);
}

void func_150F08D4(void *arg0) {
    func_150F0900(arg0);
    func_151411C4(arg0);
}

void func_150F0900(void *arg0) {
    u8 *temp_v0 = *(u8 **)((u8 *)arg0 + 0x178);
    *(s32 *)(temp_v0 + 0x138) = 0;
}

void func_150F0910(void *arg0) {
    func_150F0968(arg0);
    func_151617C4(arg0);
}

void func_150F093C(void *arg0) {
    func_150F0968(arg0);
    func_151617E4(arg0);
}

void func_150F0968(void *arg0) {
    u8 *temp_v0 = *(u8 **)((u8 *)arg0 + 0x18);
    *(s32 *)(temp_v0 + 0x13C) = 0;
}

#ifdef NON_MATCHING
s32 func_151030B8(u8 *, u8, u8 *, u8 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
void func_15145EA4(f32 **, f32 **, void *, s32);
s32 func_151C284C(f32 *, f32 *, s32, s32, s32, s32, f32, f32, f32, f32, f32, s32, u8 *, s32, s32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32);
extern s32 D_800A1A10;
extern s32 D_800A1A28;
extern s32 D_800A1A40;

s32 func_150F03F8(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    struct {
        f32 u98;
        f32 u9C;
        s32 uA0;
        s32 uA4;
        s32 uA8;
        s8 uAC;
        s8 uAD;
        s16 uAE;
        s8 uB0;
        u8 padB1[0x3];
        f32 * uB4;
        f32 * uB8;
        u8 * uBC;
        u8 * uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        s32 uDC;
    } sp;
    s32 sp94;
    f32 sp90;
    f32 sp8C;
    s32 sp88;
    u8 *sp84;
    s32 temp_t0;
    s32 temp_v0_2;
    u8 *temp_v0;

    if (arg0 == NULL) {
        return 0;
    }
    if ((s32) arg1 >= 2) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x1D4)) == 0) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x2EC)) < 0x5A) {
        return 0;
    }
    temp_t0 = arg1 * 0xC;
    temp_v0 = arg1 + &D_800A1A40;
    sp.uBC = temp_t0 + &D_800A1A10;
    sp.uC0 = temp_t0 + &D_800A1A28;
    sp.uB4 = &sp.uD0;
    sp.uB8 = &sp.uC4;
    sp84 = temp_v0;
    func_15145EA4(&sp.uBC, &sp.uB4, (*temp_v0 << 6) + (*(s32 *)((u8 *)arg0 + 0x1D4)), 2);
    sp.uC4 -= sp.uD0;
    sp.uC8 -= sp.uD4;
    sp.uCC -= sp.uD8;
    sp8C = func_150ADA68();
    sp90 = func_150ADA68();
    func_150ADA20();
    sp.uDC = func_151C284C(&sp.uD0, &sp.uC4, 0, 0, 0, 0, 150.0f, 0.006666667f, (sp8C * 19.0f) + 38.0f, (sp90 * 363.0f) + 149.0f, 50.0f, 0xFF, arg0, 1, 1, 0, 8, 0, 1, 0, 0xA0038, 0.0f, 0xFF, -1, 0, (s32) arg2, arg3);
    sp.uAC = 3;
    sp.uAD = -1;
    sp.uAE = (func_150ADA20() % 5U) + 4;
    sp.uB0 = 0;
    sp.uA0 = (s32) sp.uD0;
    sp.uA4 = (s32) sp.uD4;
    sp.uA8 = (s32) sp.uD8;
    func_151602C0((Header *) &sp.uAC, (Header2 *) &sp.uA0, (func_150ADA20() % 51U) + 0x50, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, (u8) (s32) arg2, arg3);
    sp.u9C = ((func_150ADA68() * 1906.0f) + 969.0f) * 0.001f;
    sp.u98 = ((func_150ADA68() * 911.0f) + 628.0f) * 0.1f;
    sp88 = func_150ADA20();
    sp94 = func_150ADA20();
    temp_v0_2 = arg1 * 0xC;
    func_151030B8(arg0, *sp84, temp_v0_2 + &D_800A1A10, temp_v0_2 + &D_800A1A28, &sp.u98, ((u32) sp88 % 3U) + 8, 0xFF, (func_150ADA68() * 2000.0f) + 2000.0f, &sp.uD0, 0xFF, 0, -1, (s32) arg2, arg3);
    return sp.uDC;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F03F8.s")
#endif
void func_150F0D64(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = *(u8 **)((u8 *)arg0 + 0x60);
    s32 a;
    if (arg2 == 0) {
        s32 t = *(s32 *)arg1;
        if (t == *(s32 *)v || v[4] == arg1[4]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        ; // fakematch: permuter artifact (empty statement)
        a = *(s32 *)arg1;
        if (a == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
            *(s32 *)v = a;
            v[4] = arg1[8];
        }
    }
}

void func_150F0E0C(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x170;
    if (arg2 == 0) {
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

s32 func_15160A58(s32, u8, s32 *, u8, s16, s32, s32, s32, s32, s32, s32, s8, s32, u8, u8, s32);
extern s32 D_800A1A44;
extern s32 D_800A1A50;

void func_150F0EB8(s32 arg0) {
    func_15160A58(arg0, 0x25, &D_800A1A44, 2, 0x12C, 4, 0, 0xFF, 0, 0xFF, 0, -1, 0, 0, 0xFF, 1);
    func_15160A58(arg0, 2, &D_800A1A50, 2, 0x12C, 0xD, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, 0xFF, 1);
}

typedef struct { s32 x, y, z; } V3i;
s32 func_151530A8(s32 *, s32, s32, u8 *);

void func_150F0FA4(u8 *arg0) {

    struct {
        s32 u1C;
        s32 u20;
        V3i u24;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s32 u50;
        s32 u54;
        s16 u58;
        s16 u5A;
        s16 u5C;
        u8 u5E;
        u8 u5F;
        u8 u60;
        u8 u61;
        u8 u62;
        u8 u63;
        u8 u64;
        u8 u65;
        u8 u66;
        u8 u67;
        u8 u68;
        u8 u69;
        u8 u6A;
        u8 u6B;
        u8 u6C;
        u8 u6D;
        u8 u6E;
        u8 u6F;
        u8 u70;
        u8 u71;
        u8 u72;
        u8 u73;
        u8 u74;
        u8 pad75[0x3];
        s32 u78;
        s32 u7C;
        s16 u80;
        s16 u82;
        s16 u84;
        s8 u86;
        u8 pad87[0x1];
        f32 u88;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
    } sp;

    sp.u1C = 9;
    sp.u20 = 6;
    sp.u24 = *(V3i *) arg0;
    sp.u30 = 14.88f;
    sp.u34 = 14.88f;
    sp.u38 = -1.353f;
    sp.u3C = 0.71800005f;
    sp.u40 = 39.0f;
    sp.u44 = 35.0f;
    sp.u48 = 0;
    sp.u4A = 0xFF;
    sp.u4C = -0x1F;
    sp.u4E = 0x50;
    sp.u50 = 3;
    sp.u54 = 4;
    sp.u58 = 0x14;
    sp.u5A = 0x1E;
    sp.u5C = 1;
    sp.u5E = 4;
    sp.u5F = 2;
    sp.u60 = 3;
    sp.u61 = 0xFF;
    sp.u62 = 0xFF;
    sp.u63 = 0xFF;
    sp.u64 = 0xFF;
    sp.u65 = 0;
    sp.u66 = 0;
    sp.u67 = 0;
    sp.u68 = 0;
    sp.u69 = 0xFF;
    sp.u6A = 0xFF;
    sp.u6B = 0xFF;
    sp.u6C = 0xFF;
    sp.u6D = 0;
    sp.u6E = 0;
    sp.u6F = 0;
    sp.u70 = 0;
    sp.u71 = 0xFF;
    sp.u72 = 0;
    sp.u73 = 3;
    sp.u74 = 0x24;
    sp.u78 = 0x200005;
    sp.u7C = 0x60600;
    sp.u80 = 8;
    sp.u82 = 0x1F;
    sp.u84 = 1;
    sp.u86 = 0;
    sp.u88 = 1.0f;
    sp.u8C = -1;
    sp.u8D = 0;
    sp.u8E = -1;
    sp.u8F = -1;
    func_151530A8(&sp.u1C, 0xFF, 1, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0BEC.s")

s32 func_150F13C8(u8 *arg0, s32 arg1)
{
  u8 *temp_s0;
  s32 pad;
  u8 *temp_v0;
  temp_v0 = *((u8 **) (((u8 *) arg0) + 0xA8));
  if ((*((u8 *) (((u8 *) arg0) + 0xAC))) != (*((u8 *) (((u8 *) temp_v0) + 0x3B))))
  {
    return 0;
  }
  *((f32 *) (((u8 *) arg0) + 0x40)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 0x14)));
  temp_s0 = arg0 + 0xA8;
  *((f32 *) (((u8 *) arg0) + 0x44)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 0x18)));
  if (arg0 && arg0)
  {
  }
  *((f32 *) (((u8 *) arg0) + 0x48)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 0x1C)));
  *((f32 *) (((u8 *) temp_s0) + 8)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 8))) + (0.263f * D_800BE9A4));
  *((f32 *) (((u8 *) temp_s0) + 0xC)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 0xC))) + (0.303f * D_800BE9A4));
  *((f32 *) (((u8 *) temp_s0) + 0x10)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 0x10))) + (0.25f * D_800BE9A4));
  *((f32 *) (((u8 *) temp_s0) + 8)) = func_15144B68(*((f32 *) (((u8 *) temp_s0) + 8)));
  *((f32 *) (((u8 *) temp_s0) + 0xC)) = func_15144B68(*((f32 *) (((u8 *) temp_s0) + 0xC)));
  *((f32 *) (((u8 *) temp_s0) + 0x10)) = func_15144B68(*((f32 *) (((u8 *) temp_s0) + 0x10)));
  *((f32 *) (((u8 *) arg0) + 0x38)) = (f32) ((sinf(*((f32 *) (((u8 *) temp_s0) + 8))) * 243.0f) + 780.0f);
  *((f32 *) (((u8 *) arg0) + 0x3C)) = (f32) ((sinf(*((f32 *) (((u8 *) temp_s0) + 0xC))) * 243.0f) + 780.0f);
  *((s8 *) (((u8 *) arg0) + 0x2B)) = (s8) ((u32) ((sinf(*((f32 *) (((u8 *) temp_s0) + 0x10))) * 50.0f) + 200.0f));
  return 1;
}

void func_150F15A0(struct102 *arg0, u8 *arg1, u8 arg2) {
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
        if (arg2 == 0 || arg2 == 0x43) {
            s32 t = *(s32 *)arg1;
            if (t == *(s32 *)v || v[4] == arg1[4]) {
                func_1516972C(arg0);
            }
        }
    }
}

void func_150F10D4(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    tmp.unkC = *(f32 *)(arg0 + 0x14);
    tmp.unk10 = *(f32 *)(arg0 + 0x18);
    tmp.unk14 = *(f32 *)(arg0 + 0x1C);
    temp_v0 = func_15149130(300, -1, 0x4C, -1, 0, 0x3A, 0x18, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x18);
    }
}

#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);

void func_150F16F0(u8 *arg0) {
    struct {
        s8 u98;
        s8 u99;
        s8 u9A;
        s8 u9B;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        s32 uA8;
        s32 uAC;
        s16 uB0;
        s16 uB2;
        s32 uB4;
        s32 uB8;
        s8 uBC;
        s8 uBD;
        s8 uBE;
        s8 uBF;
        s8 uC0;
        s8 uC1;
        s8 uC2;
        s8 uC3;
        s8 uC4;
        s8 uC5;
        s16 uC6;
        s16 uC8;
        s16 uCA;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        f32 uF8;
        f32 uFC;
        s32 u100;
        u8 pad104[0x4];
        s8 u108;
        s8 u109;
        s8 u10A;
        s8 u10B;
        s8 u10C;
        s8 u10D;
        u8 pad10E[0x16];
        f32 u124;
        f32 u128;
        f32 u12C;
    } sp;
    f32 temp_f0;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_s1;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x28));
    (*(f32 *)((u8 *)(&sp.u124) + 0)) = (*(f32 *)((u8 *)arg0 + 0x34));
    temp_s1 = arg0 + 0x28;
    (*(s32 *)((u8 *)(&sp.u124) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x38));
    (*(s32 *)((u8 *)(&sp.u124) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x3C));
    if (((*(s32 *)((u8 *)temp_v0 + 0)) == 0) || ((*(u8 *)((u8 *)temp_s1 + 4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B)))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x14));
    (*(f32 *)((u8 *)temp_s1 + 0x10)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x18));
    (*(f32 *)((u8 *)temp_s1 + 0x14)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x1C));
    temp_f24 = (*(f32 *)((u8 *)temp_s1 + 0xC)) - sp.u124;
    temp_f26 = (*(f32 *)((u8 *)temp_s1 + 0x10)) - sp.u128;
    temp_f28 = (*(f32 *)((u8 *)temp_s1 + 0x14)) - sp.u12C;
    (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) + ((0.109000005f + (func_150ADA68() * 0.284f)) * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s1 + 8)) > 1.0f) {
        sp.uC5 = 0x6C;
        sp.uB0 = 0x5103;
        sp.uA8 = 0x200005;
        sp.uC6 = 0x23;
        sp.uC8 = 7;
        sp.u100 = 0x90DE07;
        sp.u108 = 8;
        sp.u109 = 6;
        sp.u10A = 0x20;
        sp.u10B = -1;
        sp.uAC = 0;
        sp.uB4 = 0;
        sp.uB8 = 0;
        sp.u10C = -1;
        sp.u10D = 0;
        sp.uCA = 0x23;
        sp.uBC = 0xDD;
        sp.uBD = 0xD3;
        sp.uBE = 0xCD;
        sp.uBF = 0xFF;
        sp.uC0 = 0x57;
        sp.uC1 = 0x55;
        sp.uC2 = 0x5A;
        sp.uC4 = 0xFF;
        sp.uE4 = 0.0f;
        sp.uE8 = 0.0f;
        sp.uEC = 0.0f;
        sp.uA4 = 0.986372f;
        sp.uCC = 1.029834f;
        do {
            temp_f0 = func_150ADA68();
            sp.uD8 = (temp_f24 * temp_f0) + sp.u124;
            sp.uDC = (temp_f26 * temp_f0) + sp.u128;
            sp.uE0 = (temp_f28 * temp_f0) + sp.u12C;
            sp.uF0 = temp_f24 * D_800BEDC8 * 0.333f;
            sp.uF4 = temp_f26 * D_800BEDC8 * 0.333f;
            sp.uF8 = temp_f28 * D_800BEDC8 * 0.333f;
            sp.u98 = func_150ADA20();
            sp.u99 = func_150ADA20();
            sp.u9A = (func_150ADA20() % 5U) + 4;
            sp.u9B = (func_150ADA20() % 5U) + 4;
            sp.u9C = func_150ADA68() * 39.0f;
            sp.uA0 = func_150ADA68() * 39.0f;
            temp_f16 = func_150ADA68() * 0.514f;
            sp.u100 &= ~0xC0;
            sp.uFC = temp_f16 + 0.656f;
            var_s0 = 0;
            if (func_150ADA20() & 1) {
                var_s0 = 0x80;
            }
            if (func_150ADA20() & 1) {
                var_v0 = 0x40;
            } else {
                var_v0 = 0;
            }
            sp.u100 |= var_v0 | var_s0;
            sp.uC3 = (func_150ADA20() % 71U) + 0x50;
            sp.uB2 = (func_150ADA20() % 31U) + 0x3C;
            temp_f16_2 = (func_150ADA68() * 514.0f) + 404.0f;
            sp.uD4 = temp_f16_2;
            sp.uD0 = temp_f16_2;
            temp_v0_2 = func_151307F0(&sp.uA8, 1, 0, 0x10, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0_2 != 0) {
                memcpy(temp_v0_2 + 0xA8, &sp.u98, 0x10);
            }
            (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 8)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F16F0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F1B78.s")

void func_150F1C04(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *p = arg0 + 0x18;
    s32 id;
    if (arg2 == 0x43) {
        id = arg1[0];
        if (id == *(s32 *)p || p[4] == ((u8 *)arg1)[4]) {
            func_1516972C(arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F1C5C.s")
