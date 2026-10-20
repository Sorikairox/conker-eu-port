#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_15149AC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_15149DA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A004.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514AA5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514AB04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514AC10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514B0CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514B30C.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514B5A4.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514BE54.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514C50C.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514CBE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514CDC8.s")
