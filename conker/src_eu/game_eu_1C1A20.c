#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15195564(struct127 *obj, struct127 *target, u8 attached);

s32 func_1518D1C0(u8 *, s16, s32, u8, u8, s32, char *);
s32 func_1504715C(s32 *, struct127 *);
void func_15194210(u8 *obj, u8 alt, u8 view, s32 group);


#ifdef NON_MATCHING
// hit_impact_effect: P256: the impact effect at the last hit point D_800CC2C0/C4/C8 (written by the hit tests in
// game_83300) for the struck object `obj`, chosen by its kind byte obj +0x04 (the material of the thing that was
// hit). func_1504715C gives the object's matrix (9 words) on the stack first. Fire-like kinds spawn embers
// (func_151C384C(pos, view, group)); the others pick a spark style (0 / 1 / 2 / 5 / 6) and spawn it with
// func_151DC484 (`alt` != 0) or func_151DC260 (pos, matrix, style, view, group); unknown kinds spawn nothing.
// Callers func_151942B0 (alt 0, reached from the Baddie hit handler func_15074FD4) / func_15194858 (alt 1).
// The N64 code also XORs the code words func_150A16A4..func_150A2280 and on a mismatch (anti-tamper) scribbles
// osGetCount() & 0x3FFFF7 into a random 0x20-byte record of D_80043ED0; the port has no MIPS code there, so the
// NON_MATCHING build skips the check (as func_15046F70, func_150AEB9C).
void func_151DC260(void *pos, void *mtx, u8 style, u8 view, s32 group);
void func_15194210(u8 *obj, u8 alt, u8 view, s32 group) {
    s32 mtx[9];
    f32 pos[3];
    u8 style;

    func_1504715C(mtx, (struct127 *) obj);
    pos[0] = D_800CC2C0;
    pos[1] = D_800CC2C4;
    pos[2] = D_800CC2C8;
    switch (obj[4]) {
    case 0x06: case 0x09: case 0x0C: case 0x0F: case 0x10: case 0x12: case 0x17: case 0x1B: case 0x1E: case 0x28:
    case 0x29: case 0x2A: case 0x2B: case 0x2C: case 0x2D: case 0x2E: case 0x30: case 0x34: case 0x38: case 0x3A:
    case 0x41: case 0x42: case 0x46: case 0x47: case 0x49: case 0x4A: case 0x4B: case 0x4C: case 0x4D: case 0x4E:
    case 0x4F: case 0x51: case 0x52: case 0x55: case 0x56: case 0x5D: case 0x60: case 0x61: case 0x62: case 0x63:
    case 0x66: case 0x67: case 0x6F: case 0x70: case 0x73: case 0x77: case 0x7B: case 0x7D: case 0x7E: case 0x7F:
    case 0x82: case 0x83: case 0x84: case 0x89: case 0x8C: case 0x8E: case 0x8F: case 0x91: case 0x94: case 0x9E:
    case 0xA1: case 0xA6: case 0xAB: case 0xAC: case 0xB2: case 0xB4: case 0xB7: case 0xB8: case 0xB9:
        func_151C384C(pos, view, group);
        return;
    case 0x05: case 0x07: case 0x13: case 0x20: case 0x23: case 0x44: case 0x5A: case 0x5C: case 0x5E: case 0x5F:
    case 0x6D: case 0x74: case 0x75: case 0x78: case 0x7A: case 0x8A: case 0x8D: case 0xAD: case 0xAE: case 0xAF:
    case 0xB1:
        style = 1;
        break;
    case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x08: case 0x0A: case 0x11: case 0x14: case 0x16:
    case 0x1A: case 0x21: case 0x22: case 0x26: case 0x27: case 0x31: case 0x36: case 0x3B: case 0x3E: case 0x50:
    case 0x53: case 0x54: case 0x58: case 0x5B: case 0x64: case 0x69: case 0x6B: case 0x71: case 0x72: case 0x76:
    case 0x79: case 0x80: case 0x86: case 0x87: case 0x88: case 0x90: case 0x96: case 0x97: case 0x98: case 0x9A:
    case 0x9B: case 0x9C: case 0x9D: case 0x9F: case 0xA0: case 0xA2: case 0xA4: case 0xA5: case 0xA7: case 0xB0:
    case 0xB3: case 0xB5: case 0xB6:
        style = 0;
        break;
    case 0x25: case 0x92: case 0x95:
        style = 2;
        break;
    case 0x3F:
        style = 6;
        break;
    case 0x93:
        style = 5;
        break;
    default:
        return;
    }
    if (alt) {
        func_151DC484(pos, mtx, style, view, group);
    } else {
        func_151DC260(pos, mtx, style, view, group);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15194210.s")
#endif

void func_151942B0(s32 arg0, s32 arg1, s32 arg2) {
    func_15194210((u8 *) arg1, 0, 0xFF, 1);
}

void func_15194858(s32 arg0, s32 arg1, s32 arg2) {
    func_15194210((u8 *) arg1, 1, 0xFF, 1);
}


void func_15194890(s32 arg0, u8 *arg1, s32 arg2) {

    switch ((*(u8 *)((u8 *)arg1 + 4))) {
    s32 pad;
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        func_1518D1C0(arg1, 0xA, 0, 1, 0xFF, 1, "effects_impact_lavaboulder");
        break;
    }
}

void func_15194904(s32 arg0, u8 *arg1, s32 arg2) {

    switch ((*(u8 *)((u8 *)arg1 + 4))) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        func_1518D1C0(arg1, 0xC, 0, 1, 0xFF, 1, "effects_impact_fireimp");
        break;
    }
}

s32 func_1504715C(s32 *, struct127 *);
void func_151AED60(u8 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_15194978(struct127 *arg0, struct127 *arg1) {
    struct_eu_15154488 sp4C;
    s32 sp28[9];

    switch (((u8 *) arg1)[4]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        func_151AED60((u8 *) arg1, 0.6f, 0x5A, 0xFF, 1);
        func_1504715C(sp28, arg1);
        sp4C.unk8.unk0 = *(f32 *)((u8 *) arg1 + 0x14);
        sp4C.unk8.unk4 = *(f32 *)((u8 *) arg1 + 0x18) + 50.0f;
        sp4C.unk8.unk8 = *(f32 *)((u8 *) arg1 + 0x1C);
        sp4C.unk14 = 6.0f;
        sp4C.unk18 = 3.0f;
        sp4C.unk1C = 0.21f;
        sp4C.unk20 = 0.406f;
        sp4C.unk24 = 13.0f;
        sp4C.unk28 = 8.0f;
        sp4C.unk2C = 0xC;
        sp4C.unk2E = 5;
        sp4C.unk2 = 0xFF;
        sp4C.unk4 = -0x3F;
        sp4C.unk0 = 0;
        sp4C.unk6 = 0x23;
        sp4C.unk30 = 3;
        sp4C.unk32 = 2;
        sp4C.unk34 = 0x1E;
        sp4C.unk36 = 0x1E;
        sp4C.unk38 = 0x64;
        sp4C.unk3A = 0x64;
        sp4C.unk44 = 0x10;
        sp4C.unk46 = 0xF;
        sp4C.unk48 = 0;
        sp4C.unk3C = 0;
        sp4C.unk40 = 0.3f;
        func_15154488(&sp4C, &sp4C.unk8, (s32) sp28, 0xFF, 1);
        break;
    }
}

void func_15194AF8(struct127 *arg0, struct127 *arg1, s32 arg2) {
    func_150C7520(arg0, 500, 0xFF, 1);
    func_15194978(arg0, arg1);
}

#ifdef NON_MATCHING
// hit_debris_burst: P256: the debris burst when `obj` is hit by `attacker`: unless obj's class (func_15134070) is
// 0x63 or its class mode D_800A43C6[class * 16] is 2, one func_15154488 burst 270 above obj's position (heading
// (attacker yaw +0x7A >> 8) - 0x80, single = mode == 1, obj's matrix from func_1504715C), then func_151B5280(obj,
// 0xFF, 1). The y offset is added in double as in the asm (D_800A8680 = 270.0).
s32 func_15134070(s32);
u8 *func_151B5280(u8 *, u8, s32);
extern u8 D_800A43C6[];
void func_15194B3C(u8 *attacker, u8 *obj, s32 arg2) {
    s32 mtx[9];
    struct_eu_15154488 s;
    s16 yaw;
    struct17 pos;
    s32 class;
    u8 mode;

    yaw = (*(u16 *)(attacker + 0x7A) >> 8) - 0x40;
    pos.unk0 = *(f32 *)(obj + 0x14);
    pos.unk4 = *(f32 *)(obj + 0x18) + 270.0;
    pos.unk8 = *(f32 *)(obj + 0x1C);
    func_1504715C(mtx, (struct127 *) obj);
    class = func_15134070((s32) obj);
    if (class == 0x63) {
        return;
    }
    mode = D_800A43C6[class * 16];
    if (mode == 2) {
        return;
    }
    s.unk8 = pos;
    s.unk14 = 6.7f;
    s.unk18 = 2.33f;
    s.unk1C = 0.68f;
    s.unk20 = 0.0f;
    s.unk24 = 4.4f;
    s.unk28 = 5.3f;
    s.unk2C = 0xF;
    s.unk2E = 0xC;
    s.unk0 = yaw - 0x40;
    s.unk2 = 0x80;
    s.unk4 = -0xA0;
    s.unk6 = 0x20;
    s.unk30 = 3;
    s.unk32 = 1;
    s.unk34 = 0x1F;
    s.unk36 = 0x13;
    s.unk38 = 0x9B;
    s.unk3A = 0x64;
    s.unk44 = 0x10;
    s.unk46 = 0xF;
    s.unk48 = 0;
    s.unk40 = 0.5f;
    s.unk3C = (mode == 1) ? 1 : 0;
    func_15154488(&s, &s.unk8, (s32) mtx, 0xFF, 1);
    func_151B5280(obj, 0xFF, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15194B3C.s")
#endif

s32 func_151AF820(u8 *, u8, s32);
s32 func_151B01B8(s32, u8 *);
s32 func_151B09BC(s32, u8 *, s16, u8, s32);

void func_15194794(s32 arg0, u8 *arg1, s32 arg2) {

    func_151B01B8(arg0, arg1);
    func_151B09BC(arg0, arg1, 0x3E8, 0xFF, 0);
    switch ((*(u8 *)((u8 *)arg1 + 4))) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        func_151AF820(arg1, 0xFF, 1);
        break;
    }
}

void func_15194D80(s32 arg0, u8 *arg1, s32 arg2) {
    struct17 pos;
    struct_eu_15154488 sp50;
    s32 sp2C[9];
    structEU_151D8E18 sp24;

    switch (arg1[4]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 0x53:
        pos.unk0 = *(f32 *)(arg1 + 0x14);
        pos.unk4 = *(f32 *)(arg1 + 0x18) + 95.0f;
        pos.unk8 = *(f32 *)(arg1 + 0x1C);
    block_boundary: // fakematch: bare label = basic-block boundary (IDO_SHAPES s66 recipe 1), keeps addiu a0 in the jal slot
        func_1504715C(sp2C, (struct127 *) arg1);
        sp50.unk8 = pos;
        sp50.unk14 = 10.0f;
        sp50.unk18 = 5.0f;
        sp50.unk1C = 0.675f;
        sp50.unk20 = 0.231f;
        sp50.unk24 = 5.0f;
        sp50.unk28 = 25.1f;
        sp50.unk2C = 0xF;
        sp50.unk2E = 0xA;
        sp50.unk2 = 0xFF;
        sp50.unk4 = -0x3F;
        sp50.unk0 = 0;
        sp50.unk6 = 0x39;
        sp50.unk30 = 3;
        sp50.unk32 = 2;
        sp50.unk34 = 0x46;
        sp50.unk36 = 0x16;
        sp50.unk38 = 0x9B;
        sp50.unk3A = 0x64;
        sp50.unk44 = 0x10;
        sp50.unk46 = 0xF;
        sp50.unk48 = 0;
        sp50.unk3C = 0;
        sp50.unk40 = 0.5f;
        func_15154488(&sp50, &sp50.unk8, (s32) sp2C, 0xFF, 1);
        sp24.unk0 = 1;
        sp24.unk2 = (func_150ADA20() % 11U) + 20;
        sp24.unk4 = 8;
        sp24.unk6 = -1;
        sp24.unk5 = 1;
        func_151D8E18(&sp24, 0, 0xFF, 0);
        break;
    }
}

void func_15194F50(s32 arg0, s32 arg1, s32 arg2) {
}

void func_15194F64(s32 arg0, u8 *arg1, s32 arg2) {
    if ((D_80090130 == 1) && (arg1[0x127] == 0) && (D_800E9D00 & 8) && (*(u16 *)(*(u8 **)(arg1 + 0x31C) + 0x1A0) == 0)) {
        func_151046F0(arg0, (s32)arg1, arg2);
        *(s16 *)(*(u8 **)(arg1 + 0x31C) + 0x1A0) = 0x3E8;
    }
}

void func_15194FD8(s32 arg0, s32 arg1, s32 arg2) {
    func_1507DE4C(arg1);
    func_15138BC0(arg1, 0xFF, 1);
    func_15194F64(0, arg0, arg1);
}

s32 func_15195024(s32 arg0) {
    s32 r = *(u8 *)(arg0 + 4);
    s32 a;

    *(s32 *)(arg0 + 0x9C) |= 0xFFFE;
    a = -1;
    switch (r) {
    case 0x75:
        a = 0x73;
        break;
    case 0x80:
        a = 0x72;
        break;
    }
    if (a != -1) {
        r = func_15083568((struct127 *)arg0, a, 1.0f, 0);
    }
    // fakematch: no return statement, the result is left in v0 (IDO_SHAPES 3.9)
}

s32 func_15134070(s32);
s32 func_15136C3C(s32, u8, u8, u8, u8, u8, u8, s32);
s32 func_15138120(struct127 *, s32, u8);
s32 func_15195024(s32);

void func_1519508C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_15134070(arg0);
    if (temp_v0 != 0x63) {
        func_15138120(arg0, temp_v0, 0);
    }
    func_15136C3C(arg0, 1, 1, 1, 1, 1, 0xFF, 1);
    func_15195024(arg0);
}

void func_15195104(s32 arg0, u8 *arg1, s32 arg2) {
    if (arg1[4] == 0x53) {
        func_151942B0(arg0, arg1, arg2);
    } else {
        func_1519508C(arg1);
        func_15194F64(1, arg0, arg1);
    }
}

#ifdef NON_MATCHING
s32 func_1507CD64(struct127 *, s32);
void func_15063F14(struct127 *, s32);

// obj_hit_retire: per-kind reaction of object `obj` (kind obj[4]): most enemy / prop kinds (0..4, 0x11, 0x14, 0x3B and
// a set of kinds from 0x58 on) are switched off (func_15136C3C), released (func_15145A50), sent to state 6
// (func_1507CD64) and lose their attached model (func_15063F14) when its +0x19B is set; kind 0x16 is switched off and
// released, then like kind 0x7C hands back its rider: player obj[0x65] (1-based) gets +0x232 = 10, +0x218 = 0 and
// obj[0x65] is cleared. Other kinds: nothing.
void func_15195160(s32 arg0, u8 *obj, s8 *arg2) {
    u8 *p;
    u8 *model;

    switch (obj[4]) {
        case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x11: case 0x14: case 0x3B:
        case 0x58: case 0x5A: case 0x5B: case 0x5F: case 0x74: case 0x75: case 0x7A: case 0x80:
        case 0x87: case 0x88: case 0x90: case 0x96: case 0x98: case 0x9C: case 0x9D: case 0x9F:
        case 0xA0: case 0xB0: case 0xB1: case 0xB2: case 0xB4:
            func_15136C3C((s32) obj, 1, 1, 1, 1, 0, 0xFF, 1);
            func_15145A50((struct127 *) obj);
            func_1507CD64((struct127 *) obj, 6);
            model = *(u8 **) (obj + 0x31C);
            if (model != NULL && model[0x19B] != 0) {
                func_15063F14((struct127 *) obj, 0);
            }
            break;
        case 0x16:
            func_15136C3C((s32) obj, 1, 1, 1, 1, 0, 0xFF, 1);
            func_15145A50((struct127 *) obj);
            /* fallthrough */
        case 0x7C:
            if (obj[0x65] != 0) {
                p = (u8 *) &D_800CC2D0[obj[0x65] - 1];
                p[0x232] = 10;
                *(s32 *) (p + 0x218) = 0;
                obj[0x65] = 0;
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195160.s")
#endif

void func_151952F0(s32 arg0, s32 arg1, s32 arg2) {
    func_15195564((struct127 *)arg0, (struct127 *)arg1, 0);
}

void func_15195314(s32 arg0, s32 arg1, s32 arg2) {
    func_15195564((struct127 *)arg0, (struct127 *)arg1, 1);
}

s32 func_1514B8D4(s32, s32 *, u8, s32);

void func_15195338(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp2C[9];

    if (D_800BE616 != 0) {
        func_15195314(arg0, arg1, arg2);
    } else {
        func_1518D1C0((u8 *)arg1, 0xB, 0, 1, 0xFF, 1, "effects_impact_lava");
    }
    func_1504715C(sp2C, arg1);
    func_1514B8D4(arg1 + 0x14, sp2C, 0xFF, 1);
}

void func_151953C4(s32 arg0, u8 *arg1, s32 arg2) {
    u8 v = arg1[4];

    if ((v == 0x3E) || (v == 0xA6)) {
        func_150B0B90(arg1, arg0, 0xFF, 1);
    }
}

s32 func_15182BE0(u8, u8, u8, u8, s16, u8, u8, s32);
#ifdef NON_MATCHING
void func_15195160(s32, u8 *, s8 *); // P200: the asm returns no value; the only caller ignores it
#else
s32 func_15195160(s32, u8 *, s8 *);
#endif

void func_15195418(s32 arg0, u8 *arg1, s32 arg2) {
    s8 sp37;
    s32 pad;
    volatile s32 sp2C;

    sp37 = 0;
    if ((*(u8 **)((u8 *)arg1 + 0x318)) != NULL) {
        sp2C = func_150ADA20();
        func_15182BE0(0xFF, 0xFF, 0xFF, 0xFF, (func_150ADA20() % 11U) + 0x23, (s32) (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg1 + 0x318))) + 0x23D)), 0xFF, 1);
    }
    func_15195160(arg0, arg1, &sp37);
}

s32 func_1507CD64(struct127 *, s32);
#ifdef NON_MATCHING
void func_151C0648(f32 *, struct127 *, s32, s32, s32);
#else
s32 func_151C0648(f32 *, struct127 *, s32, s32, s32);
#endif
void func_151954B8(s32 arg0, struct127 *arg1, s32 arg2) {
    f32 sp34[3];

    sp34[0] = arg1->x_position;
    sp34[1] = arg1->y_position + 50.0f;
    sp34[2] = arg1->z_position;
    func_151C0648(sp34, arg1, 1, 0xFF, 1);
    func_15136C3C(arg1, 0, 0, 1, 0, 0, 0xFF, 1);
    func_15145A50(arg1);
    func_1507CD64(arg1, 6);
}

#ifdef NON_MATCHING
void func_15190A88(u8 *arg0);
s32 func_1518FA8C(s32 arg0, u8 arg1, s16 arg2, s8 arg3, s8 arg4, s8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9);
s32 memcpy(s32, s32, s32);

// character_hit_react: resets `target`'s reaction state (func_15190A88) and, for the character kinds listed in the
// switch, starts reaction animation 0 (func_1518FA8C): with D_800BE616 clear a plain one (0x12C, all channels -1);
// otherwise 0xFA, and when `attached` is set also binds it (0, 0, flags 1 / 0xC) and copies the record {0x7D, 5,
// source} to it at +0x90 (source = `obj`, or for a player (+4 == 0xFF) the object in its +0x124 slot) and marks the
// target's +0x31C block (+0x1AC = 1).
void func_15195564(struct127 *obj, struct127 *target, u8 attached) {
    s32 rec[3];
    s32 r;

    func_15190A88((u8 *)target);
    switch (target->id) {
        case 0x00:
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x11:
        case 0x14:
        case 0x16:
        case 0x3B:
        case 0x50:
        case 0x53:
        case 0x58:
        case 0x5A:
        case 0x5F:
        case 0x70:
        case 0x74:
        case 0x75:
        case 0x7A:
        case 0x80:
        case 0x87:
        case 0x88:
        case 0x90:
        case 0x96:
        case 0x98:
        case 0x99:
        case 0x9C:
        case 0x9D:
        case 0x9F:
        case 0xA0:
        case 0xB0:
        case 0xB1:
        case 0xB2:
        case 0xB4:
            break;
        default:
            return;
    }
    if (D_800BE616 == 0) {
        func_1518FA8C((s32)target, 0, 0x12C, -1, -1, 8, 0, 0, 0xFF, 1);
        return;
    }
    rec[0] = 0x7D;
    rec[1] = 5;
    if (obj->id == 0xFF && obj->unk124 != 0) {
        rec[2] = (s32)&D_800CC2D0[obj->unk124 - 1];
    } else {
        rec[2] = (s32)obj;
    }
    r = func_1518FA8C((s32)target, 0, 0xFA, attached ? 0 : -1, attached ? 0 : -1, 8, attached ? 1 : 0,
                      attached ? 0xC : 0, 0xFF, 1);
    if (r != 0 && attached) {
        memcpy(r + 0x90, (s32)rec, 0xC);
        if (target->unk31C != NULL) {
            ((u8 *)target->unk31C)[0x1AC] = 1;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195564.s")
#endif

#ifdef NON_MATCHING
void * func_1505ED34(void);
s32 func_15083D54(struct127 *, u16, s32, f32);
void func_150D15F4(u8 *, s32);

void func_15195750(struct127 *arg0) {
    f32 temp_f8;
    f32 var_f16;
    f32 var_f18;
    f32 var_f4;
    f32 var_f8;
    struct127 *temp_v0;
    u16 temp_t2;
    u32 temp_hi;
    u32 temp_hi_2;
    u32 temp_hi_3;

    arg0->health = 0;
    func_1507CD64(arg0, 5);
    func_15195024((s32) arg0);
    arg0->interaction_state = 0x28;
    arg0->xz_velocity = -3.0f;
    arg0->unkBC = -10.0f - (f32) (func_150ADA20() % 5U);
    temp_f8 = (f32) (func_150ADA20() % 10U);
    arg0->y_velocity = 0.0f;
    arg0->gravity = 0.0f;
    arg0->unk148 = temp_f8 - 5.0f;
    temp_v0 = func_1505ED34();
    temp_v0->interaction_state = 0x28;
    temp_v0->immune = 0xFF;
    temp_v0->stunned = 0xFF;
    temp_v0->id = arg0->id;
    temp_v0->x_position = arg0->x_position;
    temp_v0->y_position = arg0->y_position;
    temp_v0->z_position = arg0->z_position;
    temp_v0->unk40 = arg0->unk40;
    temp_v0->unk76 = arg0->unk76;
    temp_v0->unk7A = arg0->unk7A;
    temp_v0->unkB8 = arg0->unkB8;
    temp_v0->xz_scale = arg0->xz_scale;
    temp_v0->xz_velocity = 10.0f;
    temp_v0->y_scale = arg0->y_scale;
    temp_hi = func_150ADA20() % 5U;
    var_f8 = (f32) temp_hi;
    if ((s32) temp_hi < 0) {
        var_f8 += 4294967296.0f;
    }
    temp_v0->unkBC = var_f8 + 10.0f;
    temp_hi_2 = func_150ADA20() % 10U;
    var_f16 = (f32) temp_hi_2;
    if ((s32) temp_hi_2 < 0) {
        var_f16 += 4294967296.0f;
    }
    temp_v0->unk148 = var_f16 - 5.0f;
    temp_v0->unk68 = arg0->unk68;
    temp_v0->unk69 = arg0->unk69;
    temp_v0->unk6A = arg0->unk6A;
    temp_v0->unk6B = arg0->unk6B;
    (*(u8 *)((u8 *)temp_v0 + 0x6C)) = (u8) (*(u8 *)((u8 *)arg0 + 0x6C));
    (*(u8 *)((u8 *)temp_v0 + 0x6D)) = (u8) (*(u8 *)((u8 *)arg0 + 0x6D));
    temp_hi_3 = func_150ADA20() % 10922U;
    var_f4 = (f32) temp_hi_3;
    if ((s32) temp_hi_3 < 0) {
        var_f4 += 4294967296.0f;
    }
    temp_t2 = temp_v0->unk76;
    var_f18 = (f32) temp_t2;
    if ((s32) temp_t2 < 0) {
        var_f18 += 4294967296.0f;
    }
    temp_v0->unk76 = (u16) (u32) (var_f18 + (var_f4 - 5461.3335f));
    temp_v0->unk40 = (f32) (arg0->unk76 + 0x4000) * 0.005493164f;
    temp_v0->unk9C |= 0x0FFF0000;
    temp_v0->unkF8 = arg0->unkF8;
    func_15083D54(temp_v0, arg0->unk84.uh, 0, arg0->animation_speed);
    func_150D15F4(arg0, 0);
    func_150D15F4(temp_v0, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195750.s")
#endif
void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3);
void func_15137610(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, s32 arg4, s32 arg5);
void func_15195A98(u8 *arg0, u8 *arg1, s32 arg2) {
    f32 angle;
    f32 a[3];
    f32 b[3];
    f32 dir[3];
    f32 x;
    f32 z;

    if (arg0 != NULL) {
        angle = *(f32 *)(arg0 + 0x40) - 90.0f;
    } else if (arg1 != NULL) {
        angle = *(f32 *)(arg1 + 0x40) - 90.0f;
    } else {
        angle = func_150ADA68() * 360.0f;
    }
    func_1514373C(angle * 0.017453292f, 1.0f, &dir[0], &dir[2]);
    dir[1] = 0.0f;
    x = dir[0] * 20.0f;
    a[0] = *(f32 *)(arg1 + 0x14) + x;
    a[1] = *(f32 *)(arg1 + 0x18) + 50.0f;
    z = dir[2] * 20.0f;
    a[2] = *(f32 *)(arg1 + 0x1C) + z;
    b[0] = *(f32 *)(arg1 + 0x14) - x;
    b[1] = *(f32 *)(arg1 + 0x18) + 50.0f;
    b[2] = *(f32 *)(arg1 + 0x1C) - z;
    func_15137610(arg1, a, b, dir, 0xFF, 1);
}

void func_15195BC0(s32 arg0, s32 arg1, s32 arg2) {
    func_151B01B8(arg0, arg1);
    func_151B09BC(arg0, arg1, 1000, 0xFF, 0);
}

s32 func_1507CD64(struct127 *, s32);

void func_15195C08(u8 *arg0, struct127 *arg1, s32 arg2) {
    if ((arg1->health == 0) && (arg1->unk127 != 0xFF)) {
        func_15136C3C((s32) arg1, 1, 1, 1, 1, 0, 0xFF, 1);
        func_15145A50(arg1);
        func_1507CD64(arg1, 6);
    }
    if ((*(u8 *)((u8 *)arg0 + 4)) == 0x47) {
        (*(s8 *)((u8 *)arg0 + 0x1CA)) = 0;
    }
}

void func_15195CA8(s32 arg0, s32 arg1, s32 arg2) {
    structEU_151D8E18 sp18;

    sp18.unk0 = 1;
    sp18.unk2 = (func_150ADA20() % 11U) + 20;
    sp18.unk4 = 8;
    sp18.unk6 = -1;
    sp18.unk5 = 1;
    func_151D8E18(&sp18, 0, 0xFF, 0);
}
