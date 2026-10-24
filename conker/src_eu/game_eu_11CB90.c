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
u8 *func_150EF500(struct127 *, u8, s32, s32);
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

#ifdef NON_MATCHING
/* P181 */
void *func_1513D2F0(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB);
u8 *func_151A7F00(u8 *arg0, s32 arg1, u8 arg2, s32 arg3);
u8 *func_150F0448(u8 *obj, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7);
struct225 *func_150F0718(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6);
extern u8 D_800A5860[];
extern s32 D_800A4AA0;

// fire_effect_start: P181: starts the burning effect on object `arg0` (side `arg1` < 2, else nothing): an effect
// record (func_1513D2F0, handlers D_800A4AA0, 0x44 extra bytes at +0x110 holding obj, its index obj +0x3B, the
// effect object func_15083E90(18), kind 18, `arg1`, two random angles 0..2pi), two flame sprites
// (func_151A7F00 with the 0x50-byte flame definition; their +0x60 blocks get obj / index / effect / sprite number)
// stored at +0x12C / +0x130, a light (func_15149130, its +0x28 gets effect / 0.0) at +0x134, a smoke emitter
// (func_150F0448, colour (255, 217, 160)) at +0x138 and func_150F0718(70, 255, 130, 0) at +0x13C; all owned by
// arg2 / arg3. Returns the effect (NULL when none). Bytes +0x1C..+0x2F of the extra block are not set by the
// asm (uninitialised stack copied).
u8 *func_150EF500(struct127 *arg0, u8 arg1, s32 arg2, s32 arg3) {
    u8 *obj = (u8 *)arg0;
    struct {
        u8 *obj;       /* +0x00 */
        u8 index;      /* +0x04 */
        u8 *effObj;    /* +0x08 */
        u8 kind;       /* +0x0C */
        u8 side;       /* +0x0D */
        f32 angA;      /* +0x10 */
        f32 angB;      /* +0x14 */
        u8 u18;        /* +0x18 */
        u8 u19[0x17];
        s32 color[3];  /* +0x30: D_800A5860 */
        f32 u3C;       /* +0x3C */
        f32 u40;       /* +0x40 */
    } pay;
    struct {
        u8 u00;
        u8 u01;
        s16 flags;     /* +0x02 */
        s16 life;      /* +0x04 */
        s32 u08;
        s32 u0C;
        u8 color[4];   /* +0x10 */
        f32 size;      /* +0x14 */
        f32 u18;
        s32 color1[3]; /* +0x1C: D_800A5860 */
        s32 color2[3]; /* +0x28: D_800A5860 */
        f32 u34[3];
        s32 u40;
        u8 u44[4];
        s32 u48;
        u8 u4C;
        s32 u50;
        s16 u54;
        s16 u56;
    } def;
    struct {
        u8 *obj;
        u8 index;
        u8 *eff;
        u8 i;
    } spay;
    struct {
        s16 u00;
        s16 u02;
        f32 u04;
        f32 u08;
        u8 u0C;
        f32 u10;
        u8 color[4];   /* +0x14 */
        f32 u18;
        u8 u1C;
        s8 u1D;
        f32 u20[10];
        f32 u48;
        u8 u4C;
    } flame;
    struct {
        u8 *eff;
        f32 u4;
    } lpay;
    u8 *e;
    u8 *s;
    u8 **slots;

    if (obj == NULL) {
        return NULL;
    }
    if (arg1 >= 2) {
        return NULL;
    }
    pay.angA = func_150ADA68() * 6.2831855f;
    pay.angB = func_150ADA68() * 6.2831855f;
    pay.obj = obj;
    pay.index = obj[0x3B];
    pay.effObj = (u8 *)func_15083E90(18);
    pay.kind = 18;
    pay.side = arg1;
    pay.color[0] = ((s32 *)D_800A5860)[0];
    pay.color[1] = ((s32 *)D_800A5860)[1];
    pay.color[2] = ((s32 *)D_800A5860)[2];
    pay.u18 = 0;
    def.u00 = 0x94;
    def.u01 = 7;
    def.flags = 0x2203;
    def.life = 300;
    def.u08 = 0;
    def.u0C = 0;
    def.color[0] = 0xFF;
    def.color[1] = 0xFF;
    def.color[2] = 0xFF;
    def.color[3] = 0xFF;
    pay.u40 = 1.0f;
    def.u18 = 1.0f;
    pay.u3C = 0.0f;
    def.u34[0] = 0.0f;
    def.u34[1] = 0.0f;
    def.u34[2] = 0.0f;
    def.size = 100.0f;
    def.color1[0] = ((s32 *)D_800A5860)[0];
    def.color1[1] = ((s32 *)D_800A5860)[1];
    def.color1[2] = ((s32 *)D_800A5860)[2];
    def.color2[0] = ((s32 *)D_800A5860)[0];
    def.color2[1] = ((s32 *)D_800A5860)[1];
    def.color2[2] = ((s32 *)D_800A5860)[2];
    def.u40 = 0x046C0008;
    def.u44[0] = 0xFF;
    def.u44[1] = 0xFF;
    def.u44[2] = 0;
    def.u44[3] = 7;
    def.u48 = 0;
    def.u4C = 0xFF;
    def.u50 = 0;
    def.u54 = 1;
    def.u56 = 0xFF;
    e = func_1513D2F0(&def, (s32)&D_800A4AA0, 29, 0, 0, 28, 0, 0, 0, 0x44, arg2, arg3);
    if (e == NULL) {
        return e;
    }
    memcpy(e + 0x110, &pay, 0x44);
    flame.u00 = 300;
    flame.u02 = 9;
    flame.u04 = 1.0f;
    flame.u08 = 1.0f;
    flame.u0C = 0;
    flame.color[0] = 0xFF;
    flame.color[1] = 0xDC;
    flame.color[2] = 0xA0;
    flame.color[3] = 0xC8;
    flame.u1C = 0;
    flame.u1D = -1;
    flame.u20[0] = 0.0f;
    flame.u20[1] = 0.0f;
    flame.u20[2] = 0.0f;
    flame.u20[3] = 0.0f;
    flame.u20[4] = 0.0f;
    flame.u20[5] = 0.0f;
    flame.u20[6] = 0.0f;
    flame.u20[7] = 0.0f;
    flame.u20[8] = 0.0f;
    flame.u20[9] = 0.0f;
    flame.u48 = 1.0f;
    spay.obj = obj;
    flame.u10 = 0.95f;
    flame.u18 = 40.0f;
    spay.eff = e;
    flame.u4C = 1;
    spay.i = 0;
    spay.index = obj[0x3B];
    slots = (u8 **)(e + 0x110 + 0x1C);
    do {
        slots[spay.i] = func_151A7F00((u8 *)&flame, 16, arg2, arg3);
        s = slots[spay.i];
        if (s != NULL) {
            memcpy(*(u8 **)(s + 0x60), &spay, 16);
        }
        spay.i++;
    } while (spay.i < 2);
    lpay.eff = e;
    lpay.u4 = 0.0f;
    s = (u8 *)func_15149130(300, -1, 34, -1, 0, 32, (struct37 *)8, arg2, arg3);
    *(u8 **)(e + 0x110 + 0x24) = s;
    if (s != NULL) {
        memcpy(s + 0x28, &lpay, 8);
    }
    *(u8 **)(e + 0x110 + 0x28) = func_150F0448(obj, arg1, 255, 217, 160, (s32)e, arg2, arg3);
    *(u8 **)(e + 0x110 + 0x2C) = (u8 *)func_150F0718(70, 255, 130, 0, (s32)e, arg2, arg3);
    return e;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EF500.s")
#endif

#ifdef NON_MATCHING
/* P146 */
s32 func_15081A90(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
void func_1502ED88(u8 *, s32, s32, s32, s32, s32, s32);
s32 func_1505D024(struct127 *, s32, u16, s32);
// tether_beam_update: update handler (D_8008A058 slot 29) of a beam from a bone of a source object (+0x110, id
// +0x114; gone when +0x3B differs, +0 is clear or +4 is 0xFF) to a target object (+0x118, id +0x11C). Ends (0)
// when either object is gone or the source's +0x94 flags hit the beam kind's mask D_800A1A0C[+0x11D]. The start
// is the kind's bone point (D_800A19C0 / bone D_800A1A08) of the source skeleton, the end the target position;
// +0x140 / +0x14C / +0x150 get the normalised direction, its length and the second func_15145128 output, and bit 0
// of +0x128 says whether that worked. Width (+0x2C) and alpha (+0x5C) pulse with two phases (+0x120, +0x124). A
// valid beam moves its sound / light (+0x13C) to the start and is ray cast (func_15081A90, bounds only, filter 4);
// an object hit gets tinted and animation 0xA0038 with the source's slot. Otherwise the light is hidden.
s32 func_150EF90C(u8 *fx) {
    u8 *st = fx + 0x110;
    u8 *src = *(u8 **)(fx + 0x110);
    u8 *dst = *(u8 **)(fx + 0x118);
    u8 *bones;
    u8 *p;
    s16 *pos;
    s32 kind;
    s32 hit[0x19];

    if (fx[0x114] != src[0x3B] || *(s32 *)src == 0 || src[4] == 0xFF) {
        return 0;
    }
    if (st[0xC] != dst[0x3B] || *(s32 *)dst == 0) {
        return 0;
    }
    if (D_800A1A0C[st[0xD]] & *(s32 *)(src + 0x94)) {
        return 0;
    }
    st[0x18] &= ~1;
    bones = *(u8 **)(src + 0x1D4);
    if (bones != NULL) {
        kind = st[0xD];
        func_15143134(&D_800A19C0[kind], fx + 0x34, bones + (D_800A1A08[kind] << 6));
        *(f32 *)(fx + 0x40) = *(f32 *)(dst + 0x14);
        *(f32 *)(fx + 0x44) = *(f32 *)(dst + 0x18);
        *(f32 *)(fx + 0x48) = *(f32 *)(dst + 0x1C);
        *(f32 *)(st + 0x30) = *(f32 *)(fx + 0x40) - *(f32 *)(fx + 0x34);
        *(f32 *)(st + 0x34) = *(f32 *)(fx + 0x44) - *(f32 *)(fx + 0x38);
        *(f32 *)(st + 0x38) = *(f32 *)(fx + 0x48) - *(f32 *)(fx + 0x3C);
        if (func_15145128((f32 *)(st + 0x30), (f32 *)(st + 0x30), (f32 *)(st + 0x3C), (f32 *)(st + 0x40)) != 0) {
            st[0x18] |= 1;
        }
    }
    *(f32 *)(st + 0x10) += 0.16000001f * D_800BE9A4;
    *(f32 *)(st + 0x10) = func_15144B68(*(f32 *)(st + 0x10));
    *(f32 *)(fx + 0x2C) = sinf(*(f32 *)(st + 0x10)) * 5.0f + 16.0f;
    *(f32 *)(st + 0x14) += 0.16000001f * D_800BE9A4;
    *(f32 *)(st + 0x14) = func_15144B68(*(f32 *)(st + 0x14));
    fx[0x5C] = (u32)(sinf(*(f32 *)(st + 0x14)) * 25.0f + 230.0f);
    if (st[0x18] & 1) {
        p = *(u8 **)(st + 0x2C);
        if (p != NULL) {
            (*(u8 **)(p + 0x14))[9] = 0;
            pos = (s16 *)(*(u8 **)(*(u8 **)(st + 0x2C) + 0x14) + 0xE);
            pos[0] = *(f32 *)(fx + 0x34);
            pos[1] = *(f32 *)(fx + 0x38);
            pos[2] = *(f32 *)(fx + 0x3C);
        }
        func_15081A90((struct127 *)src, *(f32 *)(fx + 0x34), *(f32 *)(fx + 0x38), *(f32 *)(fx + 0x3C),
                      *(f32 *)(st + 0x30), *(f32 *)(st + 0x34), *(f32 *)(st + 0x38), (u8 *)hit, *(f32 *)(st + 0x3C), 1,
                      0, 1, 4, 0, 0);
        if (((u8 *)hit)[0x59] >= 2) {
            func_1502ED88(*(u8 **)hit, 0xFF, 0, 0, 0x90, 0, 1);
            func_1505D024(*(struct127 **)hit, 0xA0038, 0, (s32)(src - (u8 *)D_800CC2D0) / 0x32C);
        }
    } else {
        p = *(u8 **)(st + 0x2C);
        if (p != NULL) {
            (*(u8 **)(p + 0x14))[9] = 1;
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EF90C.s")
#endif

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

#ifdef NON_MATCHING
extern f32 D_800A19F0[][3];      /* bone-local points per kind (D_800A19C0 + 0x30) */

/* rider_anchor_update: follows the mount ((+0x60)->+8): when its flag +0x128 bit 0 is set and its skeleton
 * (+0x110)->+0x1D4 exists, copies its six words +0x34..+0x48 to +0x30..+0x44 and +0x14C / +0x150 to +0x54 / +0x58,
 * transforms the point D_800A19F0[k] (k = mount +0x11D) by bone D_800A1A08[k] (func_15143134) into +0x48, makes it
 * relative to +0x30 and sets flag 2 of +0x1C; otherwise clears flag 2. Always returns 1. */
s32 func_150EFFCC(u8 *o) {
    u8 *m = *(u8 **) (*(u8 **) (o + 0x60) + 8);
    u8 *sk;
    u8 k;

    if (m[0x128] & 1) {
        sk = *(u8 **) (m + 0x110);
        if (*(u8 **) (sk + 0x1D4) != NULL) {
            k = m[0x11D];
            *(s32 *) (o + 0x30) = *(s32 *) (m + 0x34);
            *(s32 *) (o + 0x34) = *(s32 *) (m + 0x38);
            *(s32 *) (o + 0x38) = *(s32 *) (m + 0x3C);
            *(s32 *) (o + 0x3C) = *(s32 *) (m + 0x40);
            *(s32 *) (o + 0x40) = *(s32 *) (m + 0x44);
            *(s32 *) (o + 0x44) = *(s32 *) (m + 0x48);
            *(f32 *) (o + 0x54) = *(f32 *) (m + 0x14C);
            *(f32 *) (o + 0x58) = *(f32 *) (m + 0x150);
            func_15143134(D_800A19F0[k], o + 0x48, *(u8 **) (sk + 0x1D4) + (D_800A1A08[k] << 6));
            *(f32 *) (o + 0x48) -= *(f32 *) (o + 0x30);
            *(f32 *) (o + 0x4C) -= *(f32 *) (o + 0x34);
            *(f32 *) (o + 0x50) -= *(f32 *) (o + 0x38);
            o[0x1C] |= 2;
            return 1;
        }
    }
    o[0x1C] &= ~2;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EFFCC.s")
#endif

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
#ifdef NON_MATCHING
/* P181 */
u8 *func_151407D0(void *emit, s32 emitSize, void *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8,
                  s32 arg9);
extern u8 (*D_800900A0)(void); /* kind-0 particle texture picker (func_151D8FE0 in ROM) */

// smoke_emitter_spawn: P181: starts a 30-tick particle emitter (func_151407D0, 0x6C-byte emitter block, owner
// arg6 / arg7) of texture D_800900A0() (life 300, flags 0x2203, kind 3), colour (r, g, b) = (arg2, arg3, arg4)
// alpha 0xFF, size 100 x 100, emit flags 0xCD2002; emitter ranges 160 / 80, rates 0.5, 1, fade 0.7, 1e-6,
// slots -1. The emitter's extra bytes (+0x170) keep obj, its index obj +0x3B, `arg1` and `arg5`. Returns the
// emitter (NULL when none).
u8 *func_150F0448(u8 *obj, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7) {
    struct {
        u8 *obj;
        u8 index;
        u8 arg1;
        s32 arg5;
    } pay;
    struct {
        u8 texture;    /* +0x00 */
        u8 kind;       /* +0x01 */
        s16 flags;     /* +0x02 */
        s16 life;      /* +0x04 */
        s32 u08;
        s32 u0C;
        u8 color[4];   /* +0x10 */
        f32 sizeX;     /* +0x14 */
        f32 sizeY;     /* +0x18 */
        f32 u1C[6];    /* +0x1C */
        f32 u34[3];    /* +0x34 */
        s32 emitFlags; /* +0x40 */
        u8 u44[4];     /* +0x44 */
        s32 u48;
    } spawn;
    struct {
        f32 range[4];  /* +0x00 */
        f32 u10;
        f32 u14;
        f32 u18;
        f32 u1C;
        f32 u20;
        s32 slots[8];  /* +0x24 */
        s32 u44;
        f32 u48;
        s16 u4C[4];
        u8 u54[6];
    } emit;
    u8 *e;

    pay.obj = obj;
    pay.index = obj[0x3B];
    pay.arg1 = arg1;
    pay.arg5 = arg5;
    spawn.texture = D_800900A0();
    spawn.color[3] = 0xFF;
    spawn.emitFlags = 0xCD2002;
    spawn.kind = 3;
    spawn.flags = 0x2203;
    spawn.life = 300;
    spawn.color[0] = arg2;
    spawn.u44[0] = 0xFF;
    spawn.u44[3] = 6;
    emit.slots[6] = -1;
    emit.slots[3] = -1;
    emit.slots[0] = -1;
    emit.slots[4] = -1;
    emit.slots[1] = -1;
    spawn.color[1] = arg3;
    spawn.color[2] = arg4;
    spawn.u08 = 0;
    spawn.u0C = 0;
    spawn.u44[1] = 0xFF;
    spawn.u44[2] = 0;
    spawn.u48 = 0;
    emit.slots[7] = -1;
    emit.slots[2] = -1;
    emit.slots[5] = -1;
    emit.u44 = 0;
    emit.u4C[0] = 0;
    emit.u4C[1] = 0;
    emit.u4C[2] = 0;
    emit.u4C[3] = 0;
    emit.u54[0] = 0xFF;
    emit.u54[1] = 0xFF;
    emit.u54[2] = 0xFF;
    emit.u54[3] = 0xFF;
    emit.u54[4] = 10;
    emit.u54[5] = 0xFF;
    spawn.u34[0] = 1.0f;
    spawn.u34[1] = 1.0f;
    spawn.u34[2] = 1.0f;
    emit.u18 = 1.0f;
    emit.u48 = 1.0f;
    spawn.sizeY = 100.0f;
    spawn.sizeX = 100.0f;
    emit.range[1] = 160.0f;
    emit.range[0] = 160.0f;
    emit.range[3] = 80.0f;
    emit.range[2] = 80.0f;
    spawn.u1C[0] = 0.0f;
    spawn.u1C[1] = 0.0f;
    spawn.u1C[2] = 0.0f;
    spawn.u1C[3] = 0.0f;
    spawn.u1C[4] = 0.0f;
    spawn.u1C[5] = 0.0f;
    emit.u10 = 0.5f;
    emit.u14 = 0.5f;
    emit.u1C = 0.7f;
    emit.u20 = 1e-06f;
    e = func_151407D0(&emit, 0x6C, &spawn, 30, 0, 0, 0, -1, arg6, arg7);
    if (e != NULL) {
        memcpy(e + 0x170, &pay, 12);
    }
    return e;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0448.s")
#endif

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
    temp_v0 = arg1 + (u8 *)&D_800A1A40;
    sp.uBC = temp_t0 + (u8 *)&D_800A1A10;
    sp.uC0 = temp_t0 + (u8 *)&D_800A1A28;
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
    func_151030B8(arg0, *sp84, temp_v0_2 + (u8 *)&D_800A1A10, temp_v0_2 + (u8 *)&D_800A1A28, &sp.u98, ((u32) sp88 % 3U) + 8, 0xFF, (func_150ADA68() * 2000.0f) + 2000.0f, &sp.uD0, 0xFF, 0, -1, (s32) arg2, arg3);
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
#ifdef NON_MATCHING
s32 func_151530A8(s32 *, u8, s32); /* P164: 3 arguments (asm 151530A8 never reads a3) */
#else
s32 func_151530A8(s32 *, s32, s32, u8 *);
#endif

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
#ifdef NON_MATCHING
    func_151530A8(&sp.u1C, 0xFF, 1);
#else
    func_151530A8(&sp.u1C, 0xFF, 1, arg0);
#endif
}

#ifdef NON_MATCHING
/* P159 */
s32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
extern u8 D_800A5860[];
// object_glow_spawn: spawns effect 0x2B (func_151307F0, 0x14 extra bytes at +0xA8) at obj's position: size 250,
// the colour of D_800A5860, life 300, random flip flags 0x40 / 0x80; the extra bytes keep obj, its index (+0x3B)
// and three random angles 0..2pi.
void func_150F0BEC(u8 *obj) {
    struct {
        /* extra data copied to the effect +0xA8 (0x14 bytes) */
        u8 *obj;
        u8 index;
        u8 pad5[3];
        f32 angle[3];
        /* spawn block for func_151307F0 (0x70 bytes) */
        s32 u0;
        s32 u4;
        s16 u8_;
        s16 life;
        s32 uC;
        s32 u10;
        u8 u14[9];
        u8 type;
        s16 u1E;
        s16 u20;
        s16 u22;
        f32 u24;
        f32 size[2];
        f32 pos[3];
        s32 color1[3];
        s32 color2[3];
        f32 u54;
        s32 flags;
        s32 u5C;
        u8 u60[7];
        u8 pad67;
        s16 u68;
        u8 pad6A[2];
        f32 u6C;
    } sp;
    s32 flipX;
    s32 flipY;
    s32 p;
    f32 r;

    sp.u0 = 0x200005;
    sp.u4 = 0x70600;
    sp.u8_ = 0x4403;
    sp.life = 300;
    sp.uC = 0;
    sp.u10 = 0;
    sp.u14[0] = 0xFF;
    sp.u14[1] = 0xFF;
    sp.u14[2] = 0xFF;
    sp.u14[3] = 0xFF;
    sp.u14[4] = 0xFF;
    sp.u14[5] = 0xD9;
    sp.u14[6] = 0xA0;
    sp.u14[7] = 0xFF;
    sp.u14[8] = 0xFF;
    sp.type = 0x2B;
    sp.size[1] = 250.0f;
    sp.size[0] = 250.0f;
    sp.pos[0] = *(f32 *)(obj + 0x14);
    sp.pos[1] = *(f32 *)(obj + 0x18);
    sp.pos[2] = *(f32 *)(obj + 0x1C);
    sp.color1[0] = ((s32 *)D_800A5860)[0];
    sp.color1[1] = ((s32 *)D_800A5860)[1];
    sp.color1[2] = ((s32 *)D_800A5860)[2];
    sp.color2[0] = ((s32 *)D_800A5860)[0];
    sp.color2[1] = ((s32 *)D_800A5860)[1];
    sp.color2[2] = ((s32 *)D_800A5860)[2];
    sp.u1E = 1;
    sp.u20 = 0xFF;
    sp.u22 = 1;
    sp.u54 = 0.0f;
    sp.u24 = 1.0f;
    flipX = (func_150ADA20() & 1) ? 0x40 : 0;
    flipY = (func_150ADA20() & 1) ? 0x80 : 0;
    sp.flags = flipY | flipX | 0xC000 | 0x40000;
    sp.u60[0] = 6;
    sp.u60[1] = 6;
    sp.u60[2] = 0x25;
    sp.u60[3] = 0xFF;
    sp.u60[4] = 0xFF;
    sp.u60[5] = 0xA;
    sp.u5C = 0;
    sp.u60[6] = 0xFF;
    sp.u68 = 0;
    sp.u6C = 10000.0f;
    sp.obj = obj;
    sp.index = obj[0x3B];
    r = func_150ADA68();
    sp.angle[0] = (r + r) * 3.1415927f;
    r = func_150ADA68();
    sp.angle[1] = (r + r) * 3.1415927f;
    r = func_150ADA68();
    sp.angle[2] = (r + r) * 3.1415927f;
    p = func_151307F0((s32)&sp.u0, 1, 0, 0x14, 0xFF, 1);
    if (p != 0) {
        memcpy((u8 *)p + 0xA8, &sp.obj, 0x14);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0BEC.s")
#endif

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
#ifdef NON_MATCHING
void func_15149514(s32, u8, s32, s32, s32);
// fx_hit_handler: P237. Hit handler of an effect (sibling of func_150F1C04; record at +0x28 = target id, +0x2C =
// target slot byte). Event 0x43: when the hitter `other` is the target (same id, or same byte +4 as +0x2C) the effect
// ends (func_1516972C). Any other event is passed on to func_15149514(other, event, &id, &slot, obj).
void func_150F1B78(u8 *obj, s32 *other, u8 event) {
    u8 *p = obj + 0x28;

    if (event == 0x43) {
        if (other[0] == *(s32 *) p || p[4] == ((u8 *) other)[4]) {
            func_1516972C((struct102 *) obj);
        }
        return;
    }
    func_15149514((s32) other, event, (s32) p, (s32) (p + 4), (s32) obj);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F1B78.s")
#endif

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

#ifdef NON_MATCHING
extern u8 D_800A1A5C[];    /* [2 variant][4 slot][2 side] f32[3] points */
extern u8 D_800A1B1C[];    /* same layout, second point set */
extern u8 D_800A1BDC[];    /* [2 variant][2 side] bone index */
extern u8 D_800A1BE0[];    /* [2 side] obj + 0x94 flag mask (variant 0) */

// limb_burst_spawn: for side (0 / 1) and slot (0..3) of obj, takes the attachment point of the obj's variant
// (1 when obj[4] == 0x23, else 0 unless the side's flag D_800A1BE0 is set in obj + 0x94: then nothing), moves it to
// world space by the bone matrix, and spawns a flash there (func_151602C0) plus a spray (func_151030B8) along the
// second point set
void func_150F1C5C(u8 *obj, u8 side, u8 slot, u8 flag, s32 arg4) {
    u8 variant;
    u8 *points;
    u8 *bone;
    f32 *src;
    f32 *dst;
    f32 world[3];
    s32 pos[3];
    struct {
        u8 u0;
        s8 u1;
        s16 life;
        u8 u4;
    } flash;
    f32 speed[2];
    s32 r;

    if (obj == NULL || slot >= 4 || side >= 2) {
        return;
    }
    if (obj[4] == 0x23) {
        variant = 1;
    } else {
        if (D_800A1BE0[side] & *(s32 *)(obj + 0x94)) {
            return;
        }
        variant = 0;
    }
    if (*(void **)(obj + 0x1D4) == NULL) {
        return;
    }
    points = D_800A1A5C + variant * 0x60 + slot * 0x18;
    bone = &D_800A1BDC[variant * 2 + side];
    src = (f32 *)(points + side * 0xC);
    dst = world;
    func_15145EA4(&src, &dst, *(u8 **)(obj + 0x1D4) + (*bone << 6), 1);
    flash.u0 = 3;
    flash.u1 = -1;
    flash.life = (u32)func_150ADA20() % 5 + 4;
    flash.u4 = 0;
    pos[0] = world[0];
    pos[1] = world[1];
    pos[2] = world[2];
    func_151602C0((Header *)&flash, (Header2 *)pos, (u32)func_150ADA20() % 51 + 0x50, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                  flag, arg4);
    speed[1] = (func_150ADA68() * 701.0f + 1925.0f) * 0.001f;
    speed[0] = (func_150ADA68() * 1155.0f + 1526.0f) * 0.1f;
    r = func_150ADA20();
    func_150ADA20();
    func_151030B8(obj, *bone, points + side * 0xC,
                  D_800A1B1C + variant * 0x60 + slot * 0x18 + side * 0xC, speed, (u32)r % 6 + 8, 0xFF,
                  func_150ADA68() * 1877.0f + 2414.0f, world, 0xFF, 0, -1, flag, arg4);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F1C5C.s")
#endif
