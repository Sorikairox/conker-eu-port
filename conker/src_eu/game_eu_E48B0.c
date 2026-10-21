#include <ultra64.h>
#include "functions.h"
#include "variables.h"

u8 *func_15169ED8(void *);

void func_150B7B9C(s32, s32);


void func_150B7C88(void);
void func_150B7B6C(void);
void func_150B7B3C(void);
void func_150B7A40(void);
void func_150B7964(void);
s32 func_150B7170(void);
s32 func_150B7214(void);
s32 func_150B7258(void);
s32 func_150B7DFC(void);

void func_150B70A0(s32 arg0) {
    switch (D_800D9CB0) {
    case 1:
        func_150B7170();
        return;
    case 2:
        func_150B7214();
        return;
    case 4:
        func_150B7258();
        return;
    case 5:
        func_150B7964();
        return;
    case 6:
        func_150B7A40();
        return;
    case 7:
        func_150B7B3C();
        return;
    case 8:
        func_150B7C88();
        return;
    case 9:
        func_150B7B6C();
        return;
    case 10:
        func_150B7DFC();
        /* fallthrough */
    default:
        return;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7170.s")

#ifdef NON_MATCHING
extern s32 D_800D9CC4;

s32 func_150B7214(void) {
    s32 *var_v1;
    s32 temp_v0;

    var_v1 = D_800D9CB8;
    do {
        temp_v0 = var_v1[5];
        var_v1 = (s32 *)((u8 *)var_v1 + (4));
        if (temp_v0 != 0) {
            (*(s32 *)((u8 *)temp_v0 + 0x20)) = 1;
        }
    } while (var_v1 != &D_800D9CC4);
    D_800D9CB0 = 3;
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7214.s")
#endif
s32 func_150B7258(void) {
    struct102 **p;

    if (*(struct102 **)&D_800D9CB4 != NULL) {
        func_1516972C(*(struct102 **)&D_800D9CB4);
        *(struct102 **)&D_800D9CB4 = NULL;
    }
    p = (struct102 **)D_800D9CB8; do { // fakematch: same-line `do` sets the s0/s1 addiu order
        if (*p != NULL) {
            func_1516972C(*p);
            *p = NULL;
        }
        p++;
    } while (p != (struct102 **)D_800D9CE0);
    D_800D9CB0 = 3;
}

void func_150B72DC(u8 *arg0) {
    *(s16 *)(arg0 + 0x34) += D_800BE9E4 * 0x30;
    if (*(s16 *)(arg0 + 0x34) > 0x800) {
        *(s16 *)(arg0 + 0x34) = -0xC00;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B731C.s")

#ifdef NON_MATCHING
void func_150B757C(u8 *arg0) {
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x18));
    if (temp_v0 == 0x1E) {
        var_v1 = (*(u8 *)((u8 *)arg0 + 0x45)) + (D_800BE9E4 * 8);
        if (var_v1 >= 0x100) {
            var_v1 = 0;
        }
        (*(u8 *)((u8 *)arg0 + 0x45)) = (u8) var_v1;
    }
    var_v0 = temp_v0 + (D_800BE9E4 * 2);
    if (var_v0 >= 0x1F) {
        var_v0 = 0x1E;
    }
    (*(s32 *)((u8 *)arg0 + 0x18)) = var_v0;
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (((s32) (var_v0 * -0x54) / 30) + 0xE6);
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (((s32) (var_v0 * -0x32) / 30) + 0xAA);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B757C.s")
#endif
void func_150B7688(u8 *arg0) {
    if (*(s16 *)(arg0 + 0x38) != 0x1000) {
        *(s16 *)(arg0 + 0x38) += D_800BE9E4 << 8;
        if (*(s16 *)(arg0 + 0x38) > 0x1000) {
            *(s16 *)(arg0 + 0x38) = 0x1000;
        }
    } else if (*(s16 *)(arg0 + 0x3A) != 0x1000) {
        *(s16 *)(arg0 + 0x3A) += D_800BE9E4 << 8;
        if (*(s16 *)(arg0 + 0x3A) > 0x1000) {
            *(s16 *)(arg0 + 0x3A) = 0x1000;
        }
    }
}

#ifdef NON_MATCHING
s32 func_15169E70(s32 **, s32);
extern s32 D_80091CD4;
extern s32 D_800BEA58;

void func_150B7700(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s8 sp7D;
    s8 sp7B;
    s8 sp7A;
    s8 sp79;
    s8 sp78;
    s8 sp77;
    s8 sp76;
    s8 sp75;
    s8 sp74;
    s16 sp72;
    s16 sp70;
    s16 sp6E;
    s16 sp6C;
    s16 sp6A;
    s16 sp68;
    f32 sp64;
    f32 sp60;
    s16 sp5C;
    s16 sp5A;
    s16 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 *sp44;
    s32 sp34;
    s32 sp30;
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 var_s1;

    temp_v1 = arg0 << 0x10;
    temp_t0 = arg1 & 0xFFFF;
    sp6E = 0x1000;
    sp44 = &D_80091CD4;
    sp4C = temp_v1 | temp_t0;
    sp6C = 0x1000;
    sp50 = arg2;
    sp58 = (s16) arg2;
    sp5C = 0;
    sp68 = 0;
    sp6A = 0;
    sp70 = 0x10;
    sp72 = 0x10;
    sp74 = 7;
    sp75 = 2;
    sp76 = 0xFF;
    sp77 = 0;
    sp78 = 0;
    sp79 = 0xFF;
    sp7A = 7;
    sp7B = 0x11;
    if (arg0 < ((s32) D_800BEA58 >> 1)) {
        var_s1 = D_800BEA58 - arg0;
    } else {
        var_s1 = arg0;
    }
    temp_v0 = arg1 - var_s1;
    sp54 = temp_v1 | (temp_v0 & 0xFFFF);
    sp7D = 0;
    sp5A = 0;
    sp60 = (f32) arg0;
    sp34 = temp_v1;
    sp30 = temp_t0;
    sp64 = (f32) temp_v0;
    func_15169E70(&sp44, arg3);
    temp_v0_2 = arg1 + var_s1;
    sp54 = sp34 | (temp_v0_2 & 0xFFFF);
    sp7D = 8;
    sp64 = (f32) temp_v0_2;
    func_15169E70(&sp44, arg3);
    temp_v0_3 = arg0 - var_s1;
    sp60 = (f32) temp_v0_3;
    sp54 = (temp_v0_3 << 0x10) | sp30;
    sp7D = 4;
    sp5A = 0x100;
    sp64 = (f32) arg1;
    func_15169E70(&sp44, arg3);
    temp_v0_4 = arg0 + var_s1;
    sp54 = (temp_v0_4 << 0x10) | sp30;
    sp7D = 0;
    sp60 = (f32) temp_v0_4;
    func_15169E70(&sp44, arg3);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7700.s")
#endif
#ifdef NON_MATCHING
void func_150B78D0(u8 *arg0) {
    s16 temp_v0;
    s16 temp_v1;
    s32 temp_lo;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x18));
    temp_lo = (s32) ((*(s16 *)((u8 *)arg0 + 0x24)) << 0x10) / (s32) (*(s32 *)((u8 *)arg0 + 0x1C));
    temp_v1 = (*(s16 *)((u8 *)arg0 + 0x1A));
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (((s32) (((*(s16 *)((u8 *)arg0 + 0x20)) - temp_v0) * temp_lo) >> 0x10) + temp_v0);
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (((s32) (((*(s16 *)((u8 *)arg0 + 0x22)) - temp_v1) * temp_lo) >> 0x10) + temp_v1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B78D0.s")
#endif
extern s32 D_80091C8C;

void func_150B7964(void) {
    struct {
        s32 *unk0;
        u8 pad4[0x14 - 4];
        s16 unk14;
        s16 unk16;
        s16 unk18;
        u8 pad1A[2];
        f32 unk1C;
        f32 unk20;
        s16 unk24;
        s16 unk26;
        s16 unk28;
        s16 unk2A;
        s16 unk2C;
        s16 unk2E;
        s8 unk30;
        s8 unk31;
        u8 unk32;
        s8 unk33;
        s8 unk34;
        u8 unk35;
        s8 unk36;
        s8 unk37;
        s8 unk38;
        s8 unk39;
    } sp;

    sp.unk31 = 1;
    sp.unk2C = 0x58;
    sp.unk1C = 60.0f;
    sp.unk20 = 60.0f;
    sp.unk14 = 0;
    sp.unk16 = 0;
    sp.unk18 = 0;
    sp.unk2E = 0x58;
    sp.unk30 = 6;
    sp.unk0 = &D_80091C8C;
    sp.unk32 = 0xFF;
    sp.unk33 = 0;
    sp.unk34 = 0;
    sp.unk35 = 0xFF;
    sp.unk24 = 0;
    sp.unk26 = 0;
    sp.unk39 = 0;
    sp.unk36 = 7;
    sp.unk37 = 0x15;
    sp.unk38 = 1;
    sp.unk28 = 0x51;
    sp.unk2A = 0x51;
    if (*(struct102 **)D_800D9CB8 != NULL) {
        func_1516972C(*(struct102 **)D_800D9CB8);
    }
    *D_800D9CB8 = (s32)func_15169ED8(&sp);
    D_800D9CB0 = 3;
}

extern s32 D_80091C8C;

void func_150B7A40(void) {
    struct {
        s32 *unk0;
        u8 pad4[0x14 - 4];
        s16 unk14;
        s16 unk16;
        s16 unk18;
        u8 pad1A[2];
        f32 unk1C;
        f32 unk20;
        s16 unk24;
        s16 unk26;
        s16 unk28;
        s16 unk2A;
        s16 unk2C;
        s16 unk2E;
        s8 unk30;
        s8 unk31;
        u8 unk32;
        s8 unk33;
        s8 unk34;
        u8 unk35;
        s8 unk36;
        s8 unk37;
        s8 unk38;
        s8 unk39;
    } sp;

    if (*(struct102 **)D_800D9CB8 != NULL) {
        func_1516972C(*(struct102 **)D_800D9CB8);
        *D_800D9CB8 = 0;
    }
    sp.unk18 = 0x4D;
    sp.unk31 = 0xF;
    sp.unk14 = 0;
    sp.unk16 = 0;
    sp.unk2C = 0x58;
    sp.unk2E = 0x58;
    sp.unk30 = 0;
    sp.unk0 = &D_80091C8C;
    sp.unk24 = 0;
    sp.unk26 = 0;
    sp.unk32 = 0xFF;
    sp.unk33 = 0;
    sp.unk34 = 0;
    sp.unk35 = 0xFF;
    sp.unk36 = 7;
    sp.unk37 = 0x11;
    sp.unk38 = 1;
    sp.unk39 = 0;
    sp.unk28 = 0x1000;
    sp.unk2A = 0x1000;
    sp.unk1C = 60.0f;
    sp.unk20 = 60.0f;
    if (((struct102 **)D_800D9CB8)[3] != NULL) {
        func_1516972C(((struct102 **)D_800D9CB8)[3]);
    }
    D_800D9CB8[3] = (s32)func_15169ED8(&sp);
    D_800D9CB0 = 3;
}

void func_150B7B3C(void) {
    func_150B7B9C(0x3C, 1);
    D_800D9CB0 = 3;
}

void func_150B7B6C(void) {
    func_150B7B9C(0xE6, 2);
    D_800D9CB0 = 3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7B9C.s")

extern s32 D_80091C98;
extern s32 D_80091CA4;
extern s32 D_80091CB0;

void func_150B7C88(void) {
    struct {
        s32 *unk0;
        s32 *unk4;
        u8 pad8[0x14 - 8];
        s16 unk14;
        s16 unk16;
        s16 unk18;
        u8 pad1A[2];
        f32 unk1C;
        f32 unk20;
        s16 unk24;
        s16 unk26;
        s16 unk28;
        s16 unk2A;
        s16 unk2C;
        s16 unk2E;
        s8 unk30;
        s8 unk31;
        u8 unk32;
        s8 unk33;
        s8 unk34;
        u8 unk35;
        s8 unk36;
        s8 unk37;
        s8 unk38;
        s8 unk39;
    } sp;

    if (((struct102 **)D_800D9CB8)[1] != NULL) {
        func_1516972C(((struct102 **)D_800D9CB8)[1]);
        D_800D9CB8[1] = 0;
    }
    sp.unk1C = 60.0f;
    sp.unk20 = 170.0f;
    sp.unk2C = 0x40;
    sp.unk2E = 0x40;
    sp.unk30 = 4;
    sp.unk0 = &D_80091CA4;
    sp.unk4 = &D_80091CB0;
    sp.unk14 = 0;
    sp.unk16 = 0;
    sp.unk18 = 0;
    sp.unk31 = 0;
    sp.unk24 = -0x800;
    sp.unk26 = 9;
    sp.unk32 = 0xFF;
    sp.unk33 = 0;
    sp.unk34 = 0;
    sp.unk35 = 0xFF;
    sp.unk36 = 0xD;
    sp.unk37 = 0x12;
    sp.unk38 = 2;
    sp.unk39 = 3;
    sp.unk28 = 0x1000;
    sp.unk2A = 0x1000;
    if (((struct102 **)D_800D9CB8)[4] != NULL) {
        func_1516972C(((struct102 **)D_800D9CB8)[4]);
    }
    D_800D9CB8[4] = (s32)func_15169ED8(&sp);
    sp.unk24 = 0;
    sp.unk26 = 0;
    sp.unk2C = 0x58;
    sp.unk2E = 0x40;
    sp.unk30 = 0;
    sp.unk36 = 7;
    sp.unk37 = 0x11;
    sp.unk0 = &D_80091C98;
    sp.unk38 = 1;
    if (((struct102 **)D_800D9CB8)[8] != NULL) {
        func_1516972C(((struct102 **)D_800D9CB8)[8]);
    }
    D_800D9CB8[8] = (s32)func_15169ED8(&sp);
    D_800D9CB0 = 3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7DFC.s")
