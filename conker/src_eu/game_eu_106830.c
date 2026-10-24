#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150D9020(f32 *arg0, f32 *arg1) {
    arg1[0] = arg0[5];
    arg1[1] = arg0[6] + 20.0f;
    arg1[2] = arg0[7];
}

void func_150D904C(s32 arg0, s32 arg1) {
    f32 sp34[3];
    f32 sp28[3];

    func_15145740(arg0, (s32)sp34, (s32)sp28, arg1, D_800BE616 ? D_800A0F10 : D_800A0F14);
}

#ifdef NON_MATCHING
extern f32 D_800A0F18;
int func_151EFDD0(void);
void func_1000D96C(s32 arg0, s32 arg1, s32 arg2);

// obj_spawn_effect50_with_sound: for an object with a character record (+0x31C), starts a sound 0x1B6 / 0x1B7
// (random, func_10010F88; 1500 or, outside level 0x34, 5000 frames) and an effect record of kind 0x50
// (func_15147FF0, 300 frames) at the object's position + 20 in y (func_150D9020); its 0x50-byte data (rec + 0x98)
// holds the object, its id, the position (twice), the aim of func_150D904C, the sound handle and a flag byte (bit 0
// cleared when the character record's +0x84 is set). In level 10 a func_1000D96C(10, 0x37, 0) cue comes first.
void func_150D9098(u8 *obj) {
    struct {
        u8 *obj;        // 0x00 (sp58)
        u8 id;          // 0x04
        f32 pos0[3];    // 0x08
        f32 pos1[3];    // 0x14
        f32 aim[3];     // 0x20
        f32 u2C;        // 0x2C
        s16 sound;      // 0x30
        f32 u34;        // 0x34
        f32 u38;        // 0x38
        f32 u3C;        // 0x3C
        f32 u40;        // 0x40
        f32 u44;        // 0x44
        f32 u48;        // 0x48
        u8 flags;       // 0x4C
        u8 u4D;         // 0x4D
    } data;
    struct {
        f32 pos[3];     // 0x00 (spAC)
        s16 time;       // 0x0C
        s16 u0E;        // 0x0E
        s32 u10;        // 0x10
        u8 u14;         // 0x14
        u8 u15;         // 0x15
        s32 u18;        // 0x18
    } spec;
    u8 *rec;

    if (*(u8 **) (obj + 0x31C) == NULL) {
        return;
    }
    if (D_800BE9F0 == 10) {
        func_1000D96C(10, 0x37, 0);
    }
    func_150D9020((f32 *) obj, spec.pos);
    data.flags = 1;
    data.u4D = 0;
    data.obj = obj;
    data.id = obj[0x3B];
    data.pos0[0] = spec.pos[0];
    data.pos0[1] = spec.pos[1];
    data.pos0[2] = spec.pos[2];
    data.pos1[0] = spec.pos[0];
    data.pos1[1] = spec.pos[1];
    data.pos1[2] = spec.pos[2];
    func_150D904C((s32) obj, (s32) data.aim);
    data.u3C = D_800A0F18;
    if (D_800BE9F0 == 0x34) {
        data.sound = func_10010F88(0x1B6 + func_151EFDD0() % 2, 0x7FFF, 0, 0, 0, 0, 0, 0, 500, 1500);
    } else {
        data.sound = func_10010F88(0x1B6 + func_151EFDD0() % 2, 0x7FFF, 0, 0, 0, 0, 0, 0, 500, 5000);
    }
    data.u34 = 0.0f;
    data.u2C = 0.0f;
    data.u40 = 0.0f;
    data.u44 = 0.0f;
    data.u48 = 0.0f;
    data.u38 = -16384.0f;
    if (*(u8 **) (obj + 0x31C) != NULL && (*(u8 **) (obj + 0x31C))[0x84] != 0) {
        data.flags &= ~1;
    }
    spec.u15 = 0x32;
    spec.time = 0x12C;
    spec.u0E = 0x36;
    spec.u10 = 2;
    spec.u14 = 5;
    spec.u18 = 0;
    rec = func_15147FF0(&spec, 0x50, 0x24, 0xE, 1, 0x11, 3, 0xFF, 0, 0xFF, 1);
    if (rec != NULL) {
        memcpy(*(u8 **) (rec + 0x98), &data, 0x50);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D9098.s")
#endif

extern f32 D_800A0F1C;
extern f32 D_800A0F20;

void func_150D9304(f32 *arg0, f32 *arg1, f32 arg2) {
    vertex sp4 = *(vertex *)arg1;

    arg1[1] += D_800A0F1C * arg2;
    arg0[0] += sp4.x * arg2;
    arg0[1] += sp4.y * arg2 + D_800A0F20 * arg2 * arg2;
    arg0[2] += sp4.z * arg2;
}

void func_150D939C(u8 *arg0) {
    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= ~2;
    *(u16 *)(arg0 + 0x1E) |= 8;
    *(u16 *)(arg0 + 0x1E) |= 1;
    *(u16 *)(arg0 + 0x1C) = 0x28;
}

#ifdef NON_MATCHING
// path_points_catch_up: P250. Handler (s32 (u8 *), function table at ELF file offset 0x24A5D8, next to
// func_150D952C) of an object that walks a ring of 0x24-byte points (+0x94; +0x25 = point count, +0x2E = last
// processed point, +0x2D = current point, +0x2C = state). Returns 0 at once when the state is < 2 and flag 8 of +0x1E
// is set. Otherwise every point from the last processed one back to the current one (walking backwards around the
// ring) gets func_150D9304(point, point + 0xC, D_800BE9A4); +0x54..0x5C becomes the current point's position (zero
// in state <= 0). The timer +0x4D of the record at +0x98 advances by D_800BE9E4; past 50 it restarts and the
// record's owner (+0) part +0x31C gets its counter +0x1AA bumped. Returns 1.
s32 func_150D93CC(u8 *p) {
    u8 *pts = *(u8 **) (p + 0x94);
    u8 *rec = *(u8 **) (p + 0x98);
    s32 i;

    if (*(s8 *) (p + 0x2C) < 2 && (*(u16 *) (p + 0x1E) & 8)) {
        return 0;
    }
    i = *(s8 *) (p + 0x2E);
    if (i != *(s8 *) (p + 0x2D)) {
        do {
            i--;
            if (i < 0) {
                i = p[0x25] - 1;
            }
            func_150D9304((f32 *) (pts + i * 0x24), (f32 *) (pts + i * 0x24 + 0xC), D_800BE9A4);
        } while (i != *(s8 *) (p + 0x2D));
    }
    if (*(s8 *) (p + 0x2C) > 0) {
        s32 *pos = (s32 *) (pts + *(s8 *) (p + 0x2D) * 0x24);   /* copied as words, like the asm */

        *(s32 *) (p + 0x54) = pos[0];
        *(s32 *) (p + 0x58) = pos[1];
        *(s32 *) (p + 0x5C) = pos[2];
    } else {
        *(f32 *) (p + 0x54) = 0.0f;
        *(f32 *) (p + 0x58) = 0.0f;
        *(f32 *) (p + 0x5C) = 0.0f;
    }
    *(s8 *) (rec + 0x4D) += D_800BE9E4;
    if (*(s8 *) (rec + 0x4D) >= 0x33) {
        u8 *owner = *(u8 **) rec;
        u8 *part;

        if (owner != NULL && (part = *(u8 **) (owner + 0x31C)) != NULL) {
            *(s16 *) (part + 0x1AA) += 1;
        }
        *(s8 *) (rec + 0x4D) = 0;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D93CC.s")
#endif

#ifdef NON_MATCHING
extern f32 D_800A0F24;
extern f32 D_800A0F28;
extern f32 D_800A0F2C;
extern f32 D_800A0F34;
s32 func_150D952C(u8 *arg0) {
    struct {
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        u8 padD0[0x8];
        f32 uD8;
        f32 uDC;
        u8 padE0[0xC];
        f32 uEC;
        f32 uF0;
        f32 uF4;
        f32 uF8;
        f32 uFC;
        f32 u100;
    } sp;
    u8 *sp88;
    u8 *sp84;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp60;
    f32 *temp_a0;
    f32 *temp_s2;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f8;
    f32 var_f0;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    f32 var_f20;
    f32 var_f2;
    s32 temp_s5;
    s8 temp_v1_2;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s5 = (*(s32 *)((u8 *)arg0 + 0x94));
    temp_s2 = (*(f32 **)((u8 *)temp_s1 + 0));
    if (((*(u8 *)((u8 *)((*(u8 **)((u8 *)temp_s2 + 0x31C))) + 0x78)) != 3) || ((s32) (*(u8 *)((u8 *)temp_s2 + 0x1CA)) <= 0)) {
        func_150D939C(arg0);
    }
    if (((*(s32 *)((u8 *)temp_s2 + 0)) == 0) || ((*(u8 *)((u8 *)temp_s1 + 4)) != (*(u8 *)((u8 *)temp_s2 + 0x3B)))) {
        return 0;
    }
    func_150D9020(temp_s2, &sp.uF8);
    func_150D904C((s32) temp_s2, (s32) &sp.uEC);
    temp_v1 = temp_s1 + 0x20;
    (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) (*(f32 *)((u8 *)(&sp.uF8) + 0));
    (*(s32 *)((u8 *)arg0 + 0x14)) = (s32) (*(s32 *)((u8 *)(&sp.uF8) + 4));
    (*(s32 *)((u8 *)arg0 + 0x18)) = (s32) (*(s32 *)((u8 *)(&sp.uF8) + 8));
    if ((*(u8 *)((u8 *)temp_s1 + 0x4C)) & 1) {
        if ((*(u16 *)((u8 *)((*(u8 **)((u8 *)temp_s2 + 0x31C))) + 0x8A)) & 0x2000) {
            var_f0 = D_800A0F24;
            (*(f32 *)((u8 *)temp_s1 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) + (D_800A0F28 * D_800BE9A4));
            if ((*(f32 *)((u8 *)temp_s1 + 0x3C)) > D_800A0F24) {
                goto block_11;
            }
        } else {
            var_f0 = D_800A0F2C;
            (*(f32 *)((u8 *)temp_s1 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) - (D_800A0F28 * D_800BE9A4));
            if ((*(f32 *)((u8 *)temp_s1 + 0x3C)) < D_800A0F2C) {
block_11:
                (*(f32 *)((u8 *)temp_s1 + 0x3C)) = var_f0;
            }
        }
    }
    temp_v0 = temp_s1 + 0x14;
    (*(f32 *)((u8 *)temp_s1 + 0x34)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x34)) + (D_800A0F34 * D_800BE9A4));
    temp_f2 = (*(f32 *)((u8 *)temp_s1 + 0x34));
    if (temp_f2 > 1.0f) {
        (*(f32 *)((u8 *)(&sp.uB8) + 0)) = (*(f32 *)((u8 *)temp_v0 + 0));
        var_f20 = (*(f32 *)((u8 *)temp_s1 + 0x2C)) + D_800BE9A4;
        (*(s32 *)((u8 *)(&sp.uB8) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0 + 4));
        temp_f0 = 1.0f / temp_f2;
        (*(s32 *)((u8 *)(&sp.uB8) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0 + 8));
        (*(f32 *)((u8 *)(&sp.uAC) + 0)) = (*(f32 *)((u8 *)temp_v1 + 0));
        (*(s32 *)((u8 *)(&sp.uAC) + 4)) = (s32) (*(s32 *)((u8 *)temp_v1 + 4));
        (*(s32 *)((u8 *)(&sp.uAC) + 8)) = (s32) (*(s32 *)((u8 *)temp_v1 + 8));
        var_f16 = var_f20 * temp_f0;
        temp_f4 = sp.u100 - (*(f32 *)((u8 *)temp_s1 + 0x1C));
        temp_f26 = (sp.uF8 - (*(f32 *)((u8 *)temp_s1 + 0x14))) * temp_f0;
        sp.uD8 = temp_f4;
        temp_f28 = (sp.uFC - (*(f32 *)((u8 *)temp_s1 + 0x18))) * temp_f0;
        temp_f6 = sp.uEC - (*(f32 *)((u8 *)temp_s1 + 0x20));
        sp.uC4 = temp_f6;
        sp60 = temp_f4;
        temp_f8 = sp.uF0 - (*(f32 *)((u8 *)temp_s1 + 0x24));
        sp.uC8 = temp_f8;
        sp84 = temp_v1;
        sp88 = temp_v0;
        temp_f10 = sp.uF4 - (*(f32 *)((u8 *)temp_s1 + 0x28));
        sp.uCC = temp_f10;
        var_f2 = temp_f6 * temp_f0;
        var_f12 = temp_f8 * temp_f0;
        var_f14 = temp_f10 * temp_f0;
        do {
            temp_a0 = ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24) + temp_s5;
            (*(f32 *)((u8 *)temp_a0 + 0)) = (*(f32 *)((u8 *)(&sp.uB8) + 0));
            (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uB8) + 4));
            (*(s32 *)((u8 *)temp_a0 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uB8) + 8));
            (*(f32 *)((u8 *)temp_a0 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) * sp.uAC);
            (*(f32 *)((u8 *)temp_a0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) * sp.uB0);
            (*(f32 *)((u8 *)temp_a0 + 0x18)) = 0.0f;
            (*(s8 *)((u8 *)temp_a0 + 0x1C)) = 0xFF;
            (*(f32 *)((u8 *)temp_a0 + 0x20)) = 0.0f;
            (*(f32 *)((u8 *)temp_a0 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) * sp.uB4);
            sp.uDC = var_f16;
            sp70 = var_f14;
            sp74 = var_f12;
            sp78 = var_f2;
            func_150D9304(temp_a0, ((f32 *)((u8 *)temp_a0 + 0xC)), var_f20);
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
            var_f20 -= var_f16;
            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
            }
            temp_v1_2 = (*(s8 *)((u8 *)arg0 + 0x2D));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
            if (temp_v1_2 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v1_2 + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
            }
            sp.uB8 += temp_f26;
            sp.uBC += temp_f28;
            sp.uC0 += temp_f4 * temp_f0;
            sp.uAC += var_f2;
            sp.uB0 += var_f12;
            sp.uB4 += var_f14;
            (*(f32 *)((u8 *)temp_s1 + 0x34)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x34)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0x34)) > 1.0f);
        (*(f32 *)((u8 *)sp88 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.uB8) + 0));
        (*(s32 *)((u8 *)sp88 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uB8) + 4));
        (*(s32 *)((u8 *)sp88 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uB8) + 8));
        (*(f32 *)((u8 *)sp84 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.uAC) + 0));
        (*(s32 *)((u8 *)sp84 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uAC) + 4));
        (*(s32 *)((u8 *)sp84 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uAC) + 8));
        (*(f32 *)((u8 *)temp_s1 + 0x2C)) = var_f20;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D952C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D99AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150DA1FC.s")

void func_150DAA04(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    u16 temp_a1 = *(u16 *)(temp_v0 + 0x30);

    if (temp_a1 != 0) {
        func_100111C8(temp_a1);
    }
}

void func_150DAA34(s32 arg0) {
    func_150DAA04(arg0);
    func_15147E64(arg0);
}

void func_150DAA60(s32 arg0) {
    func_150DAA04(arg0);
    func_15147E98(arg0);
}

void func_150DAA8C(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = *(u8 **)((u8 *)arg0 + 0x98);
    if (arg2 == 0x44) {
        if ((u16)(*(s32 *)v == *(s32 *)arg1 || v[4] == arg1[4])) { // fakematch: permuter artifact (u16 cast of the condition)
            *(f32 *)(v + 0x3C) = *(f32 *)(arg1 + 8);
dummy_label: ; // fakematch: permuter artifact (unused label)
        }
    } else if (arg2 == 0) {
        s32 t = *(s32 *)arg1;
        if (t == *(s32 *)v || arg1[4] == v[4]) {
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

void func_150DAB6C(u8 *arg0, f32 arg1) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = arg1;
    func_151482D4(&tmp, 0x44);
}

s32 func_15131D98(s32, s32, u8 *, s32);
#ifdef NON_MATCHING
void func_15131EC8(s32, f32, u8 *); /* P95: f32 (float bits were passed as an int) */
#else
void func_15131EC8(s32, s32, u8 *);
#endif

s32 func_150DABA8(s32 arg0, s32 arg1) {
    u8 *sp20;
    u8 *temp_a2;

    temp_a2 = arg0 + 0xA8;
    sp20 = temp_a2;
    func_15131D98(arg0, arg0 + 0xAC, temp_a2, arg0 + 0xAA);
#ifdef NON_MATCHING
    func_15131EC8(arg0 + 0x58, (*(f32 *)((u8 *)temp_a2 + 0xC)), temp_a2); /* P95: f32 (float bits were passed as an int) */
#else
    func_15131EC8(arg0 + 0x58, (*(s32 *)((u8 *)temp_a2 + 0xC)), temp_a2);
#endif
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150DABFC.s")
