#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#ifdef NON_MATCHING
/* P124: the 0x3C-byte effect template func_15169ED8 / func_15169E70 copy into a new effect record (+0x10);
 * same layout as S59A0 in game_eu_1231B0.c. */
typedef struct {
    void *u0;
    s32 u4;
    s32 u8;
    s32 uC;
    s32 u10;
    s16 u14;
    s16 u16;
    s16 u18;
    s16 pad1A;
    f32 u1C;
    f32 u20;
    s16 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s16 u2E;
    u8 u30; /* effect type: index into D_8008CDC0 (record +0x40) */
    u8 u31;
    u8 u32;
    u8 u33;
    u8 u34;
    u8 u35;
    u8 u36;
    u8 u37;
    u8 u38;
    u8 u39;
    u8 pad3A[2];
} EffectTemplateE48B0;
#endif
u8 *func_15169ED8(void *);

void func_150B7B9C(s32, s32);


void func_150B7C88(void);
void func_150B7B6C(void);
void func_150B7B3C(void);
void func_150B7A40(void);
void func_150B7964(void);
void func_150B7170(void);   /* P182: no result (asm v0 = a stale address) */
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

#ifdef NON_MATCHING
extern s32 D_800BEE08;
void *func_151A5580(s32, s32, s32, s32, s32, s32, u8, s32);
#endif

#ifdef NON_MATCHING
// hud_box_reset: removes the old box object D_800D9CB4 (func_1516972C), creates a new one (func_151A5580(0, 0, 0xFF,
// 0, 0, D_800BEE08, 0, 0)), sets state D_800D9CB0 = 3 and clears the 10 words D_800D9CB8.
void func_150B7170(void) {
    s32 i;

    if (D_800D9CB4 != 0) {
        func_1516972C((struct102 *) D_800D9CB4);
    }
    D_800D9CB4 = (s32) func_151A5580(0, 0, 0xFF, 0, 0, D_800BEE08, 0, 0);
    D_800D9CB0 = 3;
    for (i = 0; i < 10; i++) {
        D_800D9CB8[i] = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7170.s")
#endif

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

#ifdef NON_MATCHING
extern s32 D_80091CC8;

void func_150B731C(u8 *arg0) {
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f0;
    s32 temp_t6;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    if (((*(s32 *)((u8 *)arg0 + 0x20)) != 0) && ((*(s32 *)((u8 *)arg0 + 0x18)) == (*(s16 *)((u8 *)arg0 + 0x26)))) {
        temp_v0 = (*(s32 *)((u8 *)arg0 + 0x1C));
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_f12 = (f32) temp_v0;
        if (temp_f2 < temp_f12) {
            var_f0 = -(temp_f2 - temp_f12);
        } else {
            var_f0 = temp_f2 - temp_f12;
        }
        if ((f32) (D_800BE9E4 * 3) < var_f0) {
            goto block_6;
        }
        (*(f32 *)((u8 *)arg0 + 0x30)) = temp_f12;
        if (temp_v0 == 0xAA) {
            var_v1 = (*(u8 *)((u8 *)arg0 + 0x45)) + (D_800BE9E4 * 8);
            if (var_v1 >= 0x100) {
                var_v1 = 0;
                temp_t6 = (*(s32 *)((u8 *)arg0 + 0x20)) + 1;
                (*(s32 *)((u8 *)arg0 + 0x20)) = temp_t6;
                if (temp_t6 == 3) {
                    (*(s32 **)((u8 *)arg0 + 0x10)) = &D_80091CC8;
                    (*(s8 *)((u8 *)arg0 + 0x40)) = 8;
                    (*(u8 *)((u8 *)arg0 + 0x45)) = 0xFFU;
                    (*(s16 *)((u8 *)arg0 + 0x3C)) = 0x80;
                    (*(s16 *)((u8 *)arg0 + 0x3E)) = 0x10;
                    (*(s16 *)((u8 *)arg0 + 0x26)) = 0;
                    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
                    return;
                }
            }
            (*(u8 *)((u8 *)arg0 + 0x45)) = (u8) var_v1;
            return;
        }
        temp_f2_2 = (*(f32 *)((u8 *)arg0 + 0x30));
        if (temp_f2_2 < 170.0f) {
            var_v0 = (s32) -(temp_f2_2 - 170.0f);
        } else {
            var_v0 = (s32) (temp_f2_2 - 170.0f);
        }
        var_v1_2 = 0xFF - (var_v0 * 9);
        if (var_v1_2 < 0) {
            var_v1_2 = 0;
        }
        (*(u8 *)((u8 *)arg0 + 0x45)) = (u8) var_v1_2;
        return;
    }
block_6:
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x30)) - (f32) (D_800BE9E4 * 3));
    if ((*(f32 *)((u8 *)arg0 + 0x30)) <= 140.0f) {
        (*(s16 *)((u8 *)arg0 + 0x26)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x26)) + 0x100);
        if ((*(s16 *)((u8 *)arg0 + 0x26)) >= ((*(u8 *)((u8 *)arg0 + 0x41)) << 8)) {
            (*(s16 *)((u8 *)arg0 + 0x26)) = 0;
        }
        (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (200.0f - (140.0f - (*(f32 *)((u8 *)arg0 + 0x30))));
    }
    if ((*(f32 *)((u8 *)arg0 + 0x30)) < 170.0f) {
        var_v0_2 = (s32) -((*(f32 *)((u8 *)arg0 + 0x30)) - 170.0f);
    } else {
        var_v0_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x30)) - 170.0f);
    }
    var_v1_3 = 0xFF - (var_v0_2 * 8);
    if (var_v1_3 < 0) {
        var_v1_3 = 0;
    }
    (*(u8 *)((u8 *)arg0 + 0x45)) = (u8) var_v1_3;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B731C.s")
#endif
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
u8 *func_15169E70(void *, s32);
extern s32 D_80091CD4;
extern s32 D_800BEA58;

// effect_spawn_cross: spawns four type-7 effects (template D_80091CD4, priority arg3) around (arg0, arg1): above and
// below (arg1 -/+ d, flag byte 0 / 8) and left and right (arg0 -/+ d, flag 4 / 0, u16 0x100), where d is the
// distance of arg0 to the nearer screen edge (D_800BEA58 = screen width). arg2 goes to words 0xC and +0x14.
void func_150B7700(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    EffectTemplateE48B0 t;
    s32 d;
    s32 v;

    t.u2A = 0x1000;
    t.u0 = &D_80091CD4;
    t.u8 = (arg0 << 16) | (arg1 & 0xFFFF);
    t.u28 = 0x1000;
    t.uC = arg2;
    t.u14 = arg2;
    t.u18 = 0;
    t.u24 = 0;
    t.u26 = 0;
    t.u2C = 0x10;
    t.u2E = 0x10;
    t.u30 = 7;
    t.u31 = 2;
    t.u32 = 0xFF;
    t.u33 = 0;
    t.u34 = 0;
    t.u35 = 0xFF;
    t.u36 = 7;
    t.u37 = 0x11;
    if (arg0 < (D_800BEA58 >> 1)) {
        d = D_800BEA58 - arg0;
    } else {
        d = arg0;
    }
    v = arg1 - d;
    t.u10 = (arg0 << 16) | (v & 0xFFFF);
    t.u39 = 0;
    t.u16 = 0;
    t.u1C = arg0;
    t.u20 = v;
    func_15169E70(&t, arg3);
    v = arg1 + d;
    t.u10 = (arg0 << 16) | (v & 0xFFFF);
    t.u39 = 8;
    t.u20 = v;
    func_15169E70(&t, arg3);
    v = arg0 - d;
    t.u1C = v;
    t.u10 = (v << 16) | (arg1 & 0xFFFF);
    t.u39 = 4;
    t.u16 = 0x100;
    t.u20 = arg1;
    func_15169E70(&t, arg3);
    v = arg0 + d;
    t.u10 = (v << 16) | (arg1 & 0xFFFF);
    t.u39 = 0;
    t.u1C = v;
    func_15169E70(&t, arg3);
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

#ifdef NON_MATCHING
extern s32 D_80091C98;

// hud_counter_box_open: replaces HUD box slot `slot` of D_800D9CB8 (the old one is removed with func_1516972C) by a
// new type-6 box effect (func_15169ED8) using the D_80091C98 graphics, `width` wide and 170 high (0x51 / 0x51
// offsets, 0x58 / 0x40 size, colour 0xFF / 0 / 0 / 0xFF, flags 7 / 0x15 / 1).
void func_150B7B9C(s32 width, s32 slot) {
    EffectTemplateE48B0 sp;
    s32 *box;

    sp.u30 = 6;
    sp.u2E = 0x40;
    box = &D_800D9CB8[slot];
    sp.u31 = 1;
    sp.u2C = 0x58;
    sp.u1C = width;
    sp.u14 = 0;
    sp.u16 = 0;
    sp.u18 = 0;
    sp.u0 = &D_80091C98;
    sp.u32 = 0xFF;
    sp.u33 = 0;
    sp.u34 = 0;
    sp.u35 = 0xFF;
    sp.u24 = 0;
    sp.u26 = 0;
    sp.u39 = 0;
    sp.u36 = 7;
    sp.u37 = 0x15;
    sp.u38 = 1;
    sp.u28 = 0x51;
    sp.u2A = 0x51;
    sp.u20 = 170.0f;
    if (*box != 0) {
        func_1516972C((struct102 *)*box);
    }
    *box = (s32)func_15169ED8(&sp);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7B9C.s")
#endif

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

#ifdef NON_MATCHING
u8 *func_15169ED8(void *);
extern s32 D_80091CBC;
extern s32 D_80091C98;

// hud_bars_create: (re)creates the effect records D_800D9CB8[5..7] (three type-5 bars from template D_80091CBC at
// y 150 / 170 / 190, alpha 0x80 / 0xFF / 0x80) and [9] (a type-0 effect from D_80091C98 at 230, 170); frees [2]
// first. Returns the last record; sets D_800D9CB0 = 3. The free before [6] / [7] passes D_800D9CB8[5] (as the asm:
// the original source frees the wrong slot there).
s32 func_150B7DFC(void) {
    EffectTemplateE48B0 t;

    if (D_800D9CB8[2] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[2]);
        D_800D9CB8[2] = 0;
    }
    t.u31 = 3;
    t.u2C = 0x40;
    t.u2E = 0x10;
    t.u30 = 5;
    t.u24 = 0;
    t.u26 = 0;
    t.u14 = 0;
    t.u16 = 0;
    t.u18 = 0;
    t.u0 = &D_80091CBC;
    t.u4 = 0;
    t.u8 = 0;
    t.u10 = 0;
    t.u32 = 0xFF;
    t.u33 = 0;
    t.u34 = 0;
    t.u35 = 0x80;
    t.u36 = 7;
    t.u37 = 0x11;
    t.u38 = 1;
    t.u39 = 0;
    t.u28 = 0x1000;
    t.u2A = 0x1000;
    t.u20 = 150.0f;
    t.u1C = 230.0f;
    t.uC = (s32) t.u20;
    if (D_800D9CB8[5] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[5]);
    }
    D_800D9CB8[5] = (s32) func_15169ED8(&t);
    t.u16 = 0x100;
    t.u8 = 0x100;
    t.u35 = 0xFF;
    t.u20 = 170.0f;
    t.uC = (s32) t.u20;
    if (D_800D9CB8[6] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[5]);
    }
    D_800D9CB8[6] = (s32) func_15169ED8(&t);
    t.u16 = 0x200;
    t.u8 = 0x200;
    t.u35 = 0x80;
    t.u20 = 190.0f;
    t.uC = (s32) t.u20;
    if (D_800D9CB8[7] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[5]);
    }
    D_800D9CB8[7] = (s32) func_15169ED8(&t);
    t.u14 = 0;
    t.u16 = 0;
    t.u18 = 0;
    t.u31 = 0;
    t.u2C = 0x58;
    t.u2E = 0x40;
    t.u35 = 0xFF;
    t.u30 = 0;
    t.u0 = &D_80091C98;
    t.u1C = 230.0f;
    t.u20 = 170.0f;
    if (D_800D9CB8[9] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[9]);
    }
    D_800D9CB8[9] = (s32) func_15169ED8(&t);
    D_800D9CB0 = 3;
    return D_800D9CB8[9];
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7DFC.s")
#endif