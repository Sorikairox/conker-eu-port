#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1513F680(u8 *, u8, u8, u8, u8);
s32 func_15149AC0(f32 *, s32, s32, s32, s32, s32);
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_15149AC0.s")

#ifdef NON_MATCHING
s32 func_15149DA8(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    s32 temp_v0;
    s32 temp_v1;
    u8 *temp_s0;
    u8 *temp_s0_2;

    (*(s16 *)((u8 *)arg0 + 0x11C)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x11C)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)arg0 + 0x11C)) < 0) {
        temp_s0 = arg0 + 0x110;
        (*(s16 *)((u8 *)temp_s0 + 0xC)) = (s16) (func_150ADA20() % (u32) (*(s16 *)((u8 *)temp_s0 + 0xE)));
        temp_f2 = (*(f32 *)((u8 *)temp_s0 + 4));
        (*(f32 *)((u8 *)temp_s0 + 8)) = (f32) ((func_150ADA68() * ((*(f32 *)((u8 *)temp_s0 + 0)) - temp_f2)) + temp_f2);
    }
    temp_s0_2 = arg0 + 0x110;
    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (temp_f0 + (((*(f32 *)((u8 *)temp_s0_2 + 8)) - temp_f0) * (*(f32 *)((u8 *)temp_s0_2 + 0x10))));
    (*(s16 *)((u8 *)temp_s0_2 + 0x24)) = (s16) ((*(s16 *)((u8 *)temp_s0_2 + 0x24)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)temp_s0_2 + 0x24)) < 0) {
        (*(s16 *)((u8 *)temp_s0_2 + 0x24)) = (s16) (func_150ADA20() % (u32) (*(s16 *)((u8 *)temp_s0_2 + 0x26)));
        if (func_150ADA20() & 3) {
            temp_f2_2 = (*(f32 *)((u8 *)temp_s0_2 + 0x18));
            (*(f32 *)((u8 *)temp_s0_2 + 0x20)) = (f32) ((func_150ADA68() * ((*(f32 *)((u8 *)temp_s0_2 + 0x14)) - temp_f2_2)) + temp_f2_2);
        } else {
            temp_f2_3 = (*(f32 *)((u8 *)temp_s0_2 + 0x14));
            (*(f32 *)((u8 *)temp_s0_2 + 0x20)) = (f32) ((func_150ADA68() * ((*(f32 *)((u8 *)temp_s0_2 + 0x1C)) - temp_f2_3)) + temp_f2_3);
        }
    }
    temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x30));
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (temp_f0_2 + (((*(f32 *)((u8 *)temp_s0_2 + 0x20)) - temp_f0_2) * (*(f32 *)((u8 *)temp_s0_2 + 0x28))));
    (*(s16 *)((u8 *)temp_s0_2 + 0x38)) = (s16) ((*(s16 *)((u8 *)temp_s0_2 + 0x38)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)temp_s0_2 + 0x38)) < 0) {
        (*(s16 *)((u8 *)temp_s0_2 + 0x38)) = (s16) (func_150ADA20() % (u32) (*(s16 *)((u8 *)temp_s0_2 + 0x3A)));
        temp_v1 = (*(s32 *)((u8 *)temp_s0_2 + 0x30));
        (*(s32 *)((u8 *)temp_s0_2 + 0x34)) = (s32) ((func_150ADA20() % (u32) (((*(s32 *)((u8 *)temp_s0_2 + 0x2C)) - temp_v1) + 1)) + temp_v1);
    }
    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x24));
    (*(s32 *)((u8 *)arg0 + 0x24)) = (s32) (temp_v0 + (s32) (((f32) (*(s32 *)((u8 *)temp_s0_2 + 0x34)) - (f32) temp_v0) * (*(f32 *)((u8 *)temp_s0_2 + 0x3C))));
    if ((*(s16 *)((u8 *)arg0 + 0x1C)) < 5) {
        func_1513F680(arg0, (*(u8 *)((u8 *)arg0 + 0x70)), (*(u8 *)((u8 *)temp_s0_2 + 0x48)), (*(u8 *)((u8 *)arg0 + 0x72)), (u8) (s32) (*(u8 *)((u8 *)arg0 + 0x73)));
        (*(s16 *)((u8 *)arg0 + 0x1C)) = 0x12C;
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x58)) & ~1);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_15149DA8.s")
#endif
#ifdef NON_MATCHING
s32 func_1514A004(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    s32 var_v1;
    u8 temp_t8;
    u8 var_v0;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_v0 = (*(u8 *)((u8 *)arg0 + 0x74));
    var_v1 = 1;
    if (!(var_v0 & 2)) {
        temp_v0 = arg0 + 0x110;
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
        (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (temp_f0 + (((*(f32 *)((u8 *)temp_v0 + 8)) - temp_f0) * (*(f32 *)((u8 *)temp_v0 + 0x44))));
        if (((*(f32 *)((u8 *)temp_v0 + 8)) * 0.95f) < (*(f32 *)((u8 *)arg0 + 0x2C))) {
            temp_t8 = (*(u8 *)((u8 *)arg0 + 0x74)) | 2;
            (*(u8 *)((u8 *)arg0 + 0x74)) = temp_t8;
            var_v0 = temp_t8 & 0xFF;
        } else {
            var_v1 = 0;
            var_v0 = (*(u8 *)((u8 *)arg0 + 0x74));
        }
    }
    temp_v0_2 = arg0 + 0x110;
    if (!(var_v0 & 8)) {
        temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x30));
        (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (temp_f0_2 + (((*(f32 *)((u8 *)temp_v0_2 + 0x20)) - temp_f0_2) * (*(f32 *)((u8 *)temp_v0_2 + 0x44))));
        if (((*(f32 *)((u8 *)temp_v0_2 + 0x20)) * 0.95f) < (*(f32 *)((u8 *)arg0 + 0x30))) {
            (*(u8 *)((u8 *)arg0 + 0x74)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x74)) | 8);
        } else {
            var_v1 = 0;
        }
    }
    if (var_v1 != 0) {
        func_1513F680(arg0, (*(u8 *)((u8 *)arg0 + 0x70)), 0xDU, (*(u8 *)((u8 *)arg0 + 0x72)), (u8) (s32) (*(u8 *)((u8 *)arg0 + 0x73)));
    }
    if ((*(s16 *)((u8 *)arg0 + 0x1C)) < 5) {
        func_1513F680(arg0, (*(u8 *)((u8 *)arg0 + 0x70)), (*(u8 *)((u8 *)arg0 + 0x158)), (*(u8 *)((u8 *)arg0 + 0x72)), (u8) (s32) (*(u8 *)((u8 *)arg0 + 0x73)));
        (*(s16 *)((u8 *)arg0 + 0x1C)) = 0x64;
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x58)) & ~1);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A004.s")
#endif
s32 func_1514A164(u8 *arg0) {
    *(f32 *)(arg0 + 0x2C) -= *(f32 *)(arg0 + 0x2C) * *(f32 *)(arg0 + 0x150);
    *(f32 *)(arg0 + 0x30) -= *(f32 *)(arg0 + 0x30) * *(f32 *)(arg0 + 0x150);
    if (*(f32 *)(arg0 + 0x2C) < 2.0f || *(f32 *)(arg0 + 0x30) < 2.0f) {
        return 0;
    }
    return 1;
}

s32 func_1514A1C8(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x150));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x30));
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (temp_f0 - (temp_f0 * temp_f2));
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (temp_f12 - (temp_f12 * temp_f2));
    (*(f32 *)((u8 *)arg0 + 0x50)) += ((*(f32 *)((u8 *)arg0 + 0x4C)) * D_800BE9A4);
    (*(f32 *)((u8 *)arg0 + 0x38)) += ((*(f32 *)((u8 *)arg0 + 0x50)) * D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x15C)) < (*(f32 *)((u8 *)arg0 + 0x38))) {
        return 0;
    }
    if (((*(f32 *)((u8 *)arg0 + 0x2C)) < 4.0f) || ((*(f32 *)((u8 *)arg0 + 0x30)) < 4.0f)) {
        return 0;
    }
    return 1;
}

s32 func_151D6310(s32, s16, s32, u8 **, u8 *);
extern f32 D_800DD608[];
extern f32 D_800DD618[];

u8 *func_1514A288(u8 *arg0, s16 arg1) {
    u8 *sp44;
    u8 *sp40;
    f32 temp_f12;
    f32 temp_f2;
    u8 sp37;

    func_151D6310((s32)(arg0 + 0x100), arg1, 0x40, &sp44, &sp37);
    sp40 = sp44;
    if (sp44 != NULL) {
        if (sp37 != 0) {
            memcpy(((u8 **)(arg0 + 0x100))[arg1], arg0 + 0xC0, 0x40);
            memcpy(((u8 **)(arg0 + 0x100))[arg1] + 0x40, arg0 + 0xC0, 0x40);
        }
    } else {
        return NULL;
    }
    temp_f2 = *(f32 *)(arg0 + 0x2C) * D_800DD608[arg1];
    temp_f12 = *(f32 *)(arg0 + 0x2C) * D_800DD618[arg1];
    *(s16 *)(sp44 + 0) = *(s16 *)(sp44 + 0x30) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12);
    *(s16 *)(sp44 + 2) = *(s16 *)(sp44 + 0x12) = (s32) (*(f32 *)((u8 *)arg0 + 0x38));
    *(s16 *)(sp44 + 4) = *(s16 *)(sp44 + 0x34) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f2);
    *(s16 *)(sp44 + 0x10) = *(s16 *)(sp44 + 0x20) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12);
    *(s16 *)(sp44 + 0x22) = *(s16 *)(sp44 + 0x32) = (s32) ((*(f32 *)((u8 *)arg0 + 0x30)) + (*(f32 *)((u8 *)arg0 + 0x38)));
    *(s16 *)(sp44 + 0x14) = *(s16 *)(sp44 + 0x24) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f2);
    return sp40;
}

typedef struct { f32 x, y, z; } V3A434;
typedef struct {
    V3A434 pos;
    u8 unkC[0xA];
    s16 h16;
    s16 h18;
    s16 h1A;
    s16 h1C;
    s16 h1E;
    s16 h20;
    s16 h22;
    s16 h24;
    s16 h26;
    u8 c0[3];
    u8 c1[3];
    u8 b2E;
    u8 b2F;
    u8 b30;
    u8 b31;
} SpawnA434;
void func_151429E0(u8, u8 *, u8 *, u8 *);
void func_1518CFF0(SpawnA434 *, s32);
s32 func_1514A434(u8 *arg0) {
    SpawnA434 s;

    s.pos = *(V3A434 *)(arg0 + 0x34);
    s.h16 = 0;
    s.h18 = 0;
    s.h1A = s.h1C = func_150ADA20() % 6U + 8;
    s.h1E = 0;
    s.h20 = 0;
    s.h22 = func_150ADA20() % 201U + 100;
    s.h24 = func_150ADA20() % 5U + 3;
    s.h26 = 600;
    func_151429E0(3, &s.c0[0], &s.c0[1], &s.c0[2]);
    func_151429E0(4, &s.c1[0], &s.c1[1], &s.c1[2]);
    s.b2E = 0xFF;
    s.b2F = func_150ADA20() % 65U + 0x5C;
    s.b30 = func_150ADA20() % 3U + 1;
    s.b31 = 0;
    func_1518CFF0(&s, 1);
    return 0;
}

s32 func_151D6310(s32, s16, s32, u8 **, u8 *);
extern f32 D_800DD608[];
extern f32 D_800DD618[];

u8 *func_1514A540(u8 *arg0, s16 arg1) {
    u8 *sp44;
    u8 *sp40;
    f32 temp_f12;
    f32 temp_f2;
    u8 sp37;

    func_151D6310((s32)(arg0 + 0x100), arg1, 0x40, &sp44, &sp37);
    sp40 = sp44;
    if (sp44 != NULL) {
        if (sp37 != 0) {
            memcpy(((u8 **)(arg0 + 0x100))[arg1], arg0 + 0xC0, 0x40);
            memcpy(((u8 **)(arg0 + 0x100))[arg1] + 0x40, arg0 + 0xC0, 0x40);
        }
    } else {
        return NULL;
    }
    temp_f2 = *(f32 *)(arg0 + 0x2C) * D_800DD608[arg1];
    temp_f12 = *(f32 *)(arg0 + 0x2C) * D_800DD618[arg1];
    *(s16 *)(sp44 + 6) = 0;
    *(s16 *)(sp44 + 0x16) = 0;
    *(s16 *)(sp44 + 0x26) = 0;
    *(s16 *)(sp44 + 0x36) = 0;
    *(s16 *)(sp44 + 0) = *(s16 *)(sp44 + 0x30) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12);
    *(s16 *)(sp44 + 2) = *(s16 *)(sp44 + 0x12) = (s32) (*(f32 *)((u8 *)arg0 + 0x38));
    *(s16 *)(sp44 + 4) = *(s16 *)(sp44 + 0x34) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f2);
    *(s16 *)(sp44 + 0x10) = *(s16 *)(sp44 + 0x20) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12);
    *(s16 *)(sp44 + 0x22) = *(s16 *)(sp44 + 0x32) = (s32) ((*(f32 *)((u8 *)arg0 + 0x30)) + (*(f32 *)((u8 *)arg0 + 0x38)));
    *(s16 *)(sp44 + 0x14) = *(s16 *)(sp44 + 0x24) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f2);
    return sp40;
}

s32 func_1514A70C(u8 *arg0) {
    u8 *p;

    p = arg0 + 0x110;
    *(s16 *)(arg0 + 0x12E) -= D_800BE9E4;
    if (*(s16 *)(arg0 + 0x12E) < 0) {
        *(s16 *)(p + 0x1E) = func_150ADA20() % 6U;
        if (func_150ADA20() & 3) {
            *(f32 *)(p + 0x18) = *(f32 *)(p + 0x10) + ((*(f32 *)(p + 0xC) - *(f32 *)(p + 0x10)) * func_150ADA68());
        } else {
            *(f32 *)(p + 0x18) = *(f32 *)(p + 0xC) + ((*(f32 *)(p + 0x14) - *(f32 *)(p + 0xC)) * func_150ADA68());
        }
    }
    *(f32 *)(arg0 + 0x30) += (*(f32 *)(p + 0x18) - *(f32 *)(arg0 + 0x30)) * 0.359f;
    *(s16 *)(p + 0x1C) -= D_800BE9E4;
    if (*(s16 *)(p + 0x1C) < 0) {
        *(s16 *)(p + 0x1C) = func_150ADA20() % 17U;
        *(f32 *)(p + 8) = *(f32 *)(p + 4) + ((*(f32 *)(p + 0) - *(f32 *)(p + 4)) * func_150ADA68());
    }
    *(f32 *)(arg0 + 0x2C) += (*(f32 *)(p + 8) - *(f32 *)(arg0 + 0x2C)) * 0.186f;
    *(s16 *)(p + 0x44) -= D_800BE9E4;
    if (*(s16 *)(p + 0x44) < 0) {
        *(s16 *)(p + 0x44) = func_150ADA20() % 15U;
        *(f32 *)(p + 0x40) = *(f32 *)(p + 0x3C) + ((*(f32 *)(p + 0x38) - *(f32 *)(p + 0x3C)) * func_150ADA68());
    }
    *(s32 *)(arg0 + 0x24) += (s32)((*(f32 *)(p + 0x40) - (f32)*(s32 *)(arg0 + 0x24)) * 0.231f);
    return 1;
}

void func_1513F680(u8 *, u8, u8, u8, u8);
s32 func_1514A8F0(u8 *arg0) {
    u8 *p;
    s32 done;

    p = arg0 + 0x110;
    done = 1;
    if (!(arg0[0x74] & 2)) {
        *(f32 *)(arg0 + 0x2C) += (*(f32 *)(p + 8) - *(f32 *)(arg0 + 0x2C)) * 0.7f;
        if (*(f32 *)(p + 8) * 0.95f < *(f32 *)(arg0 + 0x2C)) {
            arg0[0x74] |= 2;
        } else {
            done = 0;
        }
    }
    if (!(arg0[0x74] & 8)) {
        *(f32 *)(arg0 + 0x30) += (*(f32 *)(p + 0x18) - *(f32 *)(arg0 + 0x30)) * 0.7f;
        if (*(f32 *)(p + 0x18) * 0.95f < *(f32 *)(arg0 + 0x30)) {
            arg0[0x74] |= 8;
        } else {
            done = 0;
        }
    }
    if (done) {
        func_1513F680(arg0, arg0[0x70], 4, arg0[0x72], arg0[0x73]);
    }
    return 1;
}

typedef struct {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[0xE];
    f32 unk2C;
    f32 unk30;
    u8 pad34[0x28];
    u8 unk5C;
    u8 pad5D[0xE7];
    f32 unk144;
    u8 pad148[0xE];
    s16 unk156;
    s16 unk158;
} struct_1514AA08;

s32 func_1514AA08(struct_1514AA08 *arg0) {
    arg0->unk30 -= arg0->unk30 * arg0->unk144;
    arg0->unk2C -= arg0->unk2C * arg0->unk144;
    if (arg0->unk1C < arg0->unk156) {
        arg0->unk5C = arg0->unk1C * arg0->unk158;
    }
    return 1;
}

#ifdef NON_MATCHING
s32 func_1514AA5C(u8 *arg0) {
    f32 temp_f0;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x140));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (*(f32 *)((u8 *)arg0 + 0x34));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) (*(f32 *)((u8 *)arg0 + 0x38));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C));
    (*(f32 *)((u8 *)arg0 + 0x130)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x130)) * temp_f0);
    (*(f32 *)((u8 *)arg0 + 0x138)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x138)) * temp_f0);
    (*(f32 *)((u8 *)arg0 + 0x134)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x134)) + ((*(f32 *)((u8 *)arg0 + 0x13C)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((*(f32 *)((u8 *)arg0 + 0x130)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x134)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((*(f32 *)((u8 *)arg0 + 0x138)) * D_800BE9A4));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514AA5C.s")
#endif
#ifdef NON_MATCHING
s32 func_1514AB04(u8 *arg0) {
    f32 sp4;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f6;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x140));
    (*(f32 *)((u8 *)arg0 + 0x130)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x130)) * temp_f0);
    (*(f32 *)((u8 *)arg0 + 0x134)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x134)) + ((*(f32 *)((u8 *)arg0 + 0x13C)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x138)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x138)) * temp_f0);
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x130)) * D_800BE9A4;
    temp_f14 = (*(f32 *)((u8 *)arg0 + 0x134)) * D_800BE9A4;
    temp_f16 = (*(f32 *)((u8 *)arg0 + 0x138)) * D_800BE9A4;
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12);
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f14);
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f16);
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40)) + temp_f12);
    temp_f6 = (*(f32 *)((u8 *)arg0 + 0x54));
    temp_f18 = (*(f32 *)((u8 *)arg0 + 0x34));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) + temp_f14);
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x48)) + temp_f16);
    sp4 = temp_f6;
    temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x38));
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x3C));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (temp_f18 + (((*(f32 *)((u8 *)arg0 + 0x40)) - temp_f18) * sp4));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) (temp_f0_2 + (((*(f32 *)((u8 *)arg0 + 0x44)) - temp_f0_2) * temp_f6));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) (temp_f2 + (((*(f32 *)((u8 *)arg0 + 0x48)) - temp_f2) * sp4));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514AB04.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514AC10.s")

#ifdef NON_MATCHING
void func_1514B0CC(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, s16 arg9, s16 argA, u8 argB) {
    struct {
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        s16 uB2;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        u8 uB7;
        s32 uB8;
        s8 uBC;
        u8 padBD[0x3];
        f32 uC0;
        u8 padC4[0x4];
        f32 uC8;
        f32 uCC;
    } sp;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f2;
    s16 var_s1;
    s32 temp_v0;

    var_s1 = arg4;
    if (var_s1 > 0) {
        sp.uAA = 0x1A4D;
        sp.uA8 = 0x6231;
        sp.uAE = 0;
        sp.uAF = 0;
        sp.uB0 = 0;
        sp.uB1 = 0xFF;
        sp.uB2 = 1;
        sp.uB4 = 0xFF;
        sp.uB5 = 0xFF;
        sp.uB8 = 0;
        sp.uB6 = 0;
        sp.uBC = 0xF;
        sp.u8C = arg1;
        sp.uC8 = 0.045f;
        sp.uB7 = argB;
        sp.uC0 = 0.0f;
        sp.uCC = 0.7f;
        do {
            temp_v0 = func_150ADA20();
            temp_f24 = func_151423D8((temp_v0 - 0x40) & 0xFF);
            temp_f26 = func_151423D8(temp_v0 & 0xFF & 0xFF);
            temp_f20 = func_150ADA68() * arg3;
            temp_f22 = (func_150ADA68() * arg6) + arg5;
            temp_f0 = func_150ADA68();
            sp.u88 = (temp_f20 * temp_f24) + arg0;
            sp.u90 = (temp_f20 * temp_f26) + arg2;
            sp.u94 = 22.6f * temp_f22;
            sp.u9C = 13.786f * temp_f22;
            temp_f2 = (temp_f0 * arg8) + arg7;
            sp.u98 = 57.969f * temp_f2;
            sp.uA0 = 42.714f * temp_f2;
            sp.uA4 = 118.763f * temp_f2;
            sp.uAC = (func_150ADA20() % (u32) (argA + 1)) + arg9;
            func_15149AC0(&sp.u88, 0xA, 0, 0, 0xFF, 1);
            var_s1 -= 1;
        } while (var_s1 != 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514B0CC.s")
#endif
s32 func_15149AC0(f32 *, s32, s32, s32, s32, s32);
extern f32 D_800A5BAC;
extern f32 D_800A5BB0;
extern f32 D_800A5BB4;
extern f32 D_800A5BB8;
extern f32 D_800A5BBC;
extern f32 D_800A5BC0;
extern f32 D_800A5BC4;
extern f32 D_800A5BC8;
extern f32 D_800A5BCC;
extern f32 D_800A5BD0;
extern f32 D_800A5BD4;
extern f32 D_800A5BD8;
extern f32 D_800A5BDC;
extern f32 D_800A5BE0;
extern f32 D_800A5BE4;

void func_1514B30C(f32 *arg0, u8 arg1, s32 arg2) {
    struct {
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s16 u50;
        s16 u52;
        s16 u54;
        u8 u56;
        u8 u57;
        u8 u58;
        u8 u59;
        s16 u5A;
        u8 u5C;
        u8 u5D;
        u8 u5E;
        u8 u5F;
        s32 u60;
        u8 u64;
        u8 pad65[3];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
    } sp;
    f32 a;
    f32 b;
    s32 pad[2]; // fakematch: frame

    do { sp.u50 = 0x6231; sp.u52 = 0x1A4D; } while (0); // fakematch: block boundary flips the two sh stores (permuter)
    *(V3A434 *)&sp.u30 = *(V3A434 *)arg0;
    sp.u56 = 0;
    sp.u57 = 0;
    sp.u58 = 0;
    sp.u59 = 0xFF;
    sp.u5D = 0xFF;
    sp.u5E = 0;
    sp.u5F = 1;
    sp.u60 = 0;
    sp.u5A = 1;
    sp.u64 = 0x1C;
    sp.u6C = 0.0f;
    sp.u70 = D_800A5BAC;
    sp.u74 = D_800A5BB0;
    a = (func_150ADA68() * D_800A5BB4 + D_800A5BB8) * D_800A5BBC;
    b = func_150ADA68();
    sp.u3C = D_800A5BC0 * a;
    sp.u44 = D_800A5BC4 * a;
    b = (b * D_800A5BC8 + D_800A5BCC) * D_800A5BD0;
    sp.u40 = D_800A5BD4 * b;
    sp.u48 = D_800A5BD8 * b;
    sp.u4C = D_800A5BDC * b;
    sp.u54 = func_150ADA20() % 17U + 16;
    sp.u68 = (func_150ADA68() * D_800A5BE0 + 50.0f) * D_800A5BE4;
    sp.u5C = func_150ADA20() % 156U + 100;
    func_15149AC0(&sp.u30, 0xA, 0, 0, arg1, arg2);
}

s32 func_1514B4E4(struct_eu_EF410_b *arg0) {
    arg0->unk2C -= arg0->unk2C * arg0->unk150;
    arg0->unk30 -= arg0->unk30 * arg0->unk150;
    arg0->unk38 += arg0->unk50 * D_800BE9A4 + 0.5f * arg0->unk4C * D_800BE9A4 * D_800BE9A4;
    arg0->unk50 += arg0->unk4C * D_800BE9A4;
    if (arg0->unk2C < 10.0f || arg0->unk30 < 10.0f) {
        return 0;
    }
    return 1;
}

#ifdef NON_MATCHING
void func_15143874(s16, f32, f32 *, f32 *);

void func_1514B5A4(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        s16 uA4;
        s16 uA6;
        s16 uA8;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        s8 uAD;
        s16 uAE;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s32 uB4;
        s8 uB8;
        u8 padB9[0x3];
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
    } sp;
    f32 temp_f16;
    f32 temp_f20;
    f32 temp_f2;
    f32 var_f24;
    s32 temp_s0;

    var_f24 = ((func_150ADA68() * 20.0f) + 29.0f) * 0.0001f * 5541.7695f;
    if (var_f24 > 1.0f) {
        sp.uA4 = 0x6231;
        sp.uA6 = 0x1A4D;
        sp.uAA = 0;
        sp.uAB = 0;
        sp.uAC = 0;
        sp.uAD = 0xFF;
        sp.uB1 = 0xFF;
        sp.uB2 = 0;
        sp.uB3 = 1;
        sp.uB4 = 0;
        sp.uAE = 1;
        sp.uB8 = 0x1C;
        sp.u88 = (*(f32 *)((u8 *)arg0 + 4));
        sp.uC0 = 0.0f;
        do {
            temp_s0 = func_150ADA20();
            func_15143874((s16) (temp_s0 & 0xFF), func_150ADA68() * 42.0f, &sp.u84, &sp.u8C);
            sp.u84 += (*(f32 *)((u8 *)arg0 + 0));
            sp.u8C += (*(f32 *)((u8 *)arg0 + 8));
            sp.uC4 = ((func_150ADA68() * 16.0f) + 29.0f) * 0.001f;
            sp.uC8 = ((func_150ADA68() * 600.0f) + 400.0f) * 0.001f;
            temp_f20 = ((func_150ADA68() * 1205.0f) + 304.0f) * 0.001f;
            temp_f16 = func_150ADA68() * 1006.0f;
            sp.u90 = 22.6f * temp_f20;
            sp.u98 = 13.786f * temp_f20;
            temp_f2 = (temp_f16 + 504.0f) * 0.001f;
            sp.u94 = 57.969f * temp_f2;
            sp.u9C = 42.714f * temp_f2;
            sp.uA0 = 118.763f * temp_f2;
            sp.uA8 = (func_150ADA20() % 31U) + 0x14;
            sp.uBC = func_150ADA68() * 497.0f * 0.001f;
            sp.uB0 = (func_150ADA20() % 156U) + 0x64;
            func_15149AC0(&sp.u84, 0xA, 0, 0, arg1 & 0xFF, arg2);
            var_f24 -= 1.0f;
        } while (var_f24 > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514B5A4.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514B8D4.s")

s32 func_1514BDB4(u8 *arg0) {
    u8 *temp_v0;
    s16 temp_v1;
    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(s16 *)(arg0 + 0x1C);
    if (temp_v1 < 16) {
        if ((temp_v1 << 4) < temp_v0[0x1B]) {
            temp_v0[0x1B] = temp_v1 << 4;
        }
    }
    return 1;
}

s32 func_1514BDEC(f32 *arg0) {
    f32 temp_f0 = arg0[0x4C / 4] * D_800BE9A4;
    arg0[0x2C / 4] += temp_f0;
    arg0[0x30 / 4] += temp_f0;
    return 1;
}

s32 func_1514BE20(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    if (temp_v0 < 16) {
        if ((temp_v0 << 4) < arg0[0x5C]) {
            arg0[0x5C] = temp_v0 << 4;
        }
    }
    return 1;
}

#ifdef NON_MATCHING
u8 *func_1514BE54(u8 *arg0, u8 *arg1, s16 arg2, u8 arg3, u8 *arg4, f32 arg5, f32 arg6, f32 arg7, u8 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s16 argD, s16 argE, s32 argF, u8 arg10, s32 arg11) {
    struct {
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        s32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        s8 u9C;
        s8 u9D;
        s16 u9E;
        s16 uA0;
        u8 padA2[0x2];
        s32 uA4;
        s32 uA8;
        s8 uAC;
        s8 uAD;
        s8 uAE;
        s8 uAF;
        f32 uB0;
        f32 uB4;
        s32 uB8;
        u8 padBC[0x8];
        s32 uC4;
        f32 uC8;
        s32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        s32 uDC;
        u8 uE0;
        s8 uE1;
        s8 uE2;
        s8 uE3;
        s32 uE4;
        u8 padE8[0x8];
        s16 uF0;
        s16 uF2;
        u8 * uF4;
    } sp;
    s32 var_a0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1_2;
    u8 *temp_v0;
    u8 *var_v1;

    if (arg4 != NULL) {
        (*(s32 *)((u8 *)(&sp.u84) + 0)) = (*(s32 *)((u8 *)arg4 + 0));
        (*(s32 *)((u8 *)(&sp.u84) + 4)) = (s32) (*(s32 *)((u8 *)arg4 + 4));
        (*(s32 *)((u8 *)(&sp.u84) + 8)) = (s32) (*(s32 *)((u8 *)arg4 + 8));
    } else {
        sp.u84 = 0;
        sp.u88 = 0.0f;
        sp.u8C = 0.0f;
    }
    sp.u90 = arg5;
    sp.u68 = 0.0f;
    sp.u6C = 0.0f;
    sp.u7C = 0.0f;
    sp.uA8 = 0x3E3F;
    sp.u80 = 15935.0f;
    sp.u78 = 15935.0f;
    sp.u70 = 6733.0f;
    sp.u94 = arg6;
    sp.u98 = arg7;
    sp.u74 = 18404.0f;
    sp.u4C = (*(f32 *)((u8 *)arg1 + 0)) * 15.045272f;
    sp.u54 = (*(f32 *)((u8 *)arg1 + 0)) * 5.8676558f;
    sp.uB0 = 0.0f;
    sp.u5C = (*(f32 *)((u8 *)arg1 + 0)) * 12.111444f;
    sp.u50 = (*(f32 *)((u8 *)arg1 + 4)) * 0.396174f;
    sp.u58 = (*(f32 *)((u8 *)arg1 + 4)) * 0.1042563f;
    sp.u64 = (*(f32 *)((u8 *)arg1 + 4)) * 0.5197371f;
    sp.uB4 = 0.0f;
    sp.u9D = 0;
    sp.u9E = 0x2203;
    sp.u9C = (s8) argB;
    sp.u60 = (*(f32 *)((u8 *)arg1 + 4)) * 0.34404588f;
    if (arg2 == -1) {
        sp.uA0 = 0x12C;
    } else {
        sp.uA0 = arg2;
    }
    sp.uA4 = 0;
    sp.uAC = 0xFF;
    sp.uAD = 0xFF;
    sp.uAE = 0xFF;
    sp.uAF = 0xFF;
    var_v1_2 = 0;
    (*(s32 *)((u8 *)(&sp.uB8) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(f32 *)((u8 *)(&sp.uB8) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.uB8) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.uC4 = (*(s32 *)((u8 *)arg0 + 0));
    sp.uC8 = (*(f32 *)((u8 *)arg0 + 4)) + 100.0f;
    sp.uD0 = 1.0f;
    sp.uD4 = 1.0f;
    sp.uD8 = 1.0f;
    sp.uCC = (*(s32 *)((u8 *)arg0 + 8));
    if (argC & 1) {
        var_v1_2 = 0x800000;
    }
    if (arg2 == -1) {
        var_a0 = 0;
    } else {
        var_a0 = 1;
    }
    var_v0 = 0;
    if (argC & 2) {
        var_v0 = 0x02000000;
    }
    sp.uDC = var_v0 | var_a0 | 0x40000 | 0x80000 | 0x200000 | 0x400000 | var_v1_2 | 0x40000000;
    sp.uE1 = 0xFF;
    sp.uE2 = 0;
    sp.uE3 = 7;
    sp.uE4 = 0;
    sp.uE0 = arg3;
    sp.uF0 = argD;
    sp.uF2 = argE;
    if (func_150ADA20() & 1) {
        var_v0_2 = 1;
    } else {
        var_v0_2 = 0;
    }
    temp_v0 = func_1513D2F0(&sp.u9C, (s32) ((u8 *)&D_800A4AA0), arg8, arg9, (u8) (s32) argA, 0x1CU, (u8) (var_v0_2 | 2), 0, 0, argF + 0x50, (u8) (s32) arg10, arg11);
    var_v1 = temp_v0;
    if (temp_v0 != NULL) {
        sp.uF4 = temp_v0;
        memcpy(temp_v0 + 0x110, &sp.u4C, 0x50);
        var_v1 = sp.uF4;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514BE54.s")
#endif
s32 func_1514C178(u8 *arg0, u8 *arg1) {

    (*(f32 *)((u8 *)arg1 + 0x1C)) = (f32) ((*(f32 *)((u8 *)arg1 + 0x1C)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg1 + 0x1C)) < 0.0f) {
        (*(f32 *)((u8 *)arg1 + 0x1C)) = (f32) (func_150ADA68() * 4.0f);
        (*(f32 *)((u8 *)arg1 + 0x10)) = (f32) ((*(f32 *)((u8 *)arg1 + 0)) + ((*(f32 *)((u8 *)arg1 + 8)) * func_150ADA68()));
    }
    (*(f32 *)((u8 *)arg0 + 0x2C)) += ((*(f32 *)((u8 *)arg1 + 0x10)) - (*(f32 *)((u8 *)arg0 + 0x2C))) * 0.35f;
    (*(f32 *)((u8 *)arg1 + 0x20)) = (f32) ((*(f32 *)((u8 *)arg1 + 0x20)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg1 + 0x20)) < 0.0f) {
        (*(f32 *)((u8 *)arg1 + 0x20)) = (f32) (func_150ADA68() * 9.0f);
        if (func_150ADA20() & 1) {
            (*(f32 *)((u8 *)arg1 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg1 + 4)) + ((*(f32 *)((u8 *)arg1 + 0xC)) * func_150ADA68()));
        } else {
            (*(f32 *)((u8 *)arg1 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg1 + 4)) + ((*(f32 *)((u8 *)arg1 + 0x18)) * func_150ADA68()));
        }
    }
    (*(f32 *)((u8 *)arg0 + 0x30)) += ((*(f32 *)((u8 *)arg1 + 0x14)) - (*(f32 *)((u8 *)arg0 + 0x30))) * 0.4f;
    (*(f32 *)((u8 *)arg1 + 0x30)) = (f32) ((*(f32 *)((u8 *)arg1 + 0x30)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg1 + 0x30)) < 0.0f) {
        (*(f32 *)((u8 *)arg1 + 0x30)) = (f32) (func_150ADA68() * 7.0f);
        (*(f32 *)((u8 *)arg1 + 0x2C)) = (f32) ((*(f32 *)((u8 *)arg1 + 0x24)) + ((*(f32 *)((u8 *)arg1 + 0x28)) * func_150ADA68()));
    }
    (*(f32 *)((u8 *)arg1 + 0x34)) += ((*(f32 *)((u8 *)arg1 + 0x2C)) - (*(f32 *)((u8 *)arg1 + 0x34))) * 0.4f;
    (*(s32 *)((u8 *)arg0 + 0x24)) = (s32) (*(f32 *)((u8 *)arg1 + 0x34));
    return 1;
}

void func_1514C370(u8 *arg0) {
    func_1514C178(arg0, arg0 + 0x110);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514C390.s")

void func_1514C4C0(f32 *arg0) {
    arg0[0x40 / 4] = arg0[0x34 / 4];
    arg0[0x44 / 4] = arg0[0x38 / 4] + 100.0f;
    arg0[0x48 / 4] = arg0[0x3C / 4];
}

void func_1514C4EC(u8 *arg0) {
    func_1514C178(arg0, arg0 + 0x110);
}

#ifdef NON_MATCHING
void func_1514C50C(u8 *arg0) {
    struct {
        f32 u20;
        f32 u24;
        f32 u28;
        u8 pad2C[0x4];
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f16;
    f32 var_f18;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_v1;
    s32 var_v1_2;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;

    (*(f32 *)((u8 *)(&sp.u20) + 0)) = (*(f32 *)((u8 *)arg0 + 0x148));
    (*(s32 *)((u8 *)(&sp.u20) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x14C));
    (*(s32 *)((u8 *)(&sp.u20) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x150));
    var_v1 = D_800BE9E4;
    if (var_v1 != 0) {
        temp_a2 = -(var_v1 & 3);
        temp_a1 = temp_a2 + var_v1;
        if (temp_a2 != 0) {
            temp_v0 = arg0 + 0x110;
            temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0x48));
            var_v1 -= 1;
            var_f18 = (*(f32 *)((u8 *)temp_v0 + 0x38)) * temp_f0;
            if (temp_a1 != var_v1) {
                do {
                    (*(f32 *)((u8 *)temp_v0 + 0x38)) = var_f18;
                    var_v1 -= 1;
                    var_f18 = (*(f32 *)((u8 *)temp_v0 + 0x38)) * temp_f0;
                    (*(f32 *)((u8 *)temp_v0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x3C)) * temp_f0);
                    (*(f32 *)((u8 *)temp_v0 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x40)) * temp_f0);
                } while (temp_a1 != var_v1);
            }
            (*(f32 *)((u8 *)temp_v0 + 0x38)) = var_f18;
            (*(f32 *)((u8 *)temp_v0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x3C)) * temp_f0);
            (*(f32 *)((u8 *)temp_v0 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x40)) * temp_f0);
            if (var_v1 != 0) {
                goto block_5;
            }
        } else {
block_5:
            temp_v0_2 = arg0 + 0x110;
            temp_f0_2 = (*(f32 *)((u8 *)temp_v0_2 + 0x48));
            var_v1_2 = var_v1 - 4;
            var_f16 = (*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2;
            if (var_v1_2 != 0) {
                do {
                    (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = var_f16;
                    var_v1_2 -= 4;
                    (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
                    var_f16 = (*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2;
                    (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
                } while (var_v1_2 != 0);
            }
            (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = var_f16;
            (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0_2);
        }
    }
    temp_v0_3 = arg0 + 0x110;
    (*(f32 *)((u8 *)temp_v0_3 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_3 + 0x3C)) + ((*(f32 *)((u8 *)temp_v0_3 + 0x44)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((sp.u20 + (0.5f * (((*(f32 *)((u8 *)temp_v0_3 + 0x38)) - sp.u20) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((sp.u24 + (0.5f * (((*(f32 *)((u8 *)temp_v0_3 + 0x3C)) - sp.u24) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((sp.u28 + (0.5f * (((*(f32 *)((u8 *)temp_v0_3 + 0x40)) - sp.u28) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514C50C.s")
#endif
s32 func_1514C7C8(void *arg0) {
    func_1514C50C(arg0);
    func_1514C390(arg0);
    return 1;
}

s32 func_1514C7F8(void *arg0) {
    func_1514C50C(arg0);
    func_1514C4C0(arg0);
    return 1;
}

s32 func_1514C828(u8 *arg0) {
    arg0[0x72] = 0;
    arg0[0x71] = 0x24;
    *(s16 *)(arg0 + 0x1C) = *(s16 *)(arg0 + 0x164);
    *(s32 *)(arg0 + 0x58) |= 0x08000000;
    *(f32 *)(arg0 + 0x154) = *(f32 *)(arg0 + 0x160);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514C860.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514C9E0.s")

#ifdef NON_MATCHING
extern s32 D_8008ADA0;

void func_1514CBE8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9, s32 argA, u8 argB) {
    f32 temp_f20;
    f32 temp_f2;
    s16 var_s1;
    s16 var_v0;
    s16 var_v1;
    s32 (*temp_v0)(s32, s16, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, f32, s32, s32);
    s32 temp_a0;
    s32 temp_s0;

    if (arg5 < arg4) {
        var_v0 = (arg4 - arg5) + 1;
        var_v1 = arg5;
    } else {
        var_v0 = (arg5 - arg4) + 1;
        var_v1 = arg4;
    }
    var_s1 = 0;
    if (arg6 > 0) {
loop_5:
        temp_a0 = (func_150ADA20() % (u32) var_v0) + var_v1;
        temp_s0 = temp_a0 & 0xFF;
        temp_f20 = func_151423D8((temp_a0 - 0x40) & 0xFF);
        temp_v0 = *(((s32 *)((u8 *)&D_8008ADA0 + (arg7 * 4))));
        temp_f2 = (arg3 * func_151423D8(temp_s0 & 0xFF)) + arg2;
        if (temp_v0 != NULL) {
            if (temp_v0(2, var_s1, (arg3 * temp_f20) + arg0, arg1, temp_f2, arg0, arg1, arg2, temp_s0, (s32) arg4, arg3, arg8, arg9, argA, (s32) argB) != 0) {
                goto block_9;
            }
            return;
        }
block_9:
        var_s1 += 1;
        if (var_s1 >= arg6) {

        } else {
            goto loop_5;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514CBE8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514CDC8.s")
