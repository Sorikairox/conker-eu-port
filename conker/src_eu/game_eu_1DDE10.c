#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15143874(s16, f32, f32 *, f32 *);
#endif


void func_15143794(s16, s16, f32, void *);
s32 func_151DA6F8(f32 *, f32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);

s32 func_151B0600(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s16 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    f32 v[3];
    f32 sp68[3];
    f32 r;

    v[0] = arg2;
    v[1] = arg3;
    v[2] = arg4;
    r = func_150ADA68();
    func_15143794(arg9, arg8, (r * 5.3f) + 4.4f, sp68);
    func_151DA6F8(v, sp68, (func_150ADA68() * (f32)0) + 0.68f, (func_150ADA20() % 20U) + 0x1F, (func_150ADA20() % 101U) + 0x9B, (func_150ADA68() * 2.33f) + 6.7f, (func_150ADA20() & 1) + 3, 1, 1.0f, 1.0f, 0, 0, 0, 0x10, 0xF, 0, argE, 1); // fakematch: (f32)0 keeps the rand * 0 multiply (0.0f folds it)
    return 1;
}

#ifdef NON_MATCHING
/* P153 */
void func_1504715C(void *, u8 *);
s32 func_15134070(struct127 *);
extern f32 D_800AA500[3]; /* (0, -12, 96): offset of the effect from the model node */

// object_hit_flash_spawn: P153: spawns the hit flash (func_15154488 parameter block) on obj's model node
// (obj +0x1D4, +0x180) for the target's class: 4 without a target or for target types 0x53 / 0xA5, else
// func_15134070(target); nothing for class 0x63, a class mode (D_800A43B8[class] byte 0xE) of 2, obj without a
// model, or obj +0x74 low nibble 0xF. Angle: (u8) ((+0x7A >> 8) + 0x40) - 0x68; +0x3C set for class mode 1.
// The asm leaves v0 unset; the callers (func_15194794, game_981E0) declare an int result and ignore it: 0 here.
s32 func_151B01B8(u8 *obj, u8 *target) {
    struct_eu_15154488 p;
    s32 basis[10];
    u8 *cls;
    s32 class;
    u8 yaw;

    if (obj == NULL || *(s32 *) (obj + 0x1D4) == 0 || (obj[0x74] & 0xF) == 0xF) {
        return 0;
    }
    func_1504715C(basis, obj);
    class = 4;
    if (target != NULL) {
        if (target[4] == 0x53 || target[4] == 0xA5) {
            class = 4;
        } else {
            class = func_15134070((struct127 *) target);
        }
    }
    if (class == 0x63) {
        return 0;
    }
    cls = D_800A43B8[class];
    if (cls[0xE] == 2) {
        return 0;
    }
    yaw = (*(u16 *) (obj + 0x7A) >> 8) + 0x40;
    func_15143134(D_800AA500, &p.unk8, *(u8 **) (obj + 0x1D4) + 0x180);
    p.unk0 = yaw - 0x68;
    p.unk14 = 7.22f;
    p.unk2C = 0xA;
    p.unk2E = 0x14;
    p.unk2 = 0xD0;
    p.unk4 = -0x1B;
    p.unk6 = 0x36;
    p.unk30 = 3;
    p.unk32 = 2;
    p.unk34 = 0x1E;
    p.unk36 = 0x28;
    p.unk38 = 0x9B;
    p.unk3A = 0x64;
    p.unk18 = 3.04f;
    p.unk1C = 0.81000006f;
    p.unk20 = 0.40500003f;
    p.unk24 = 6.0f;
    p.unk28 = 13.900001f;
    p.unk40 = 0.5f;
    if (cls[0xE] == 1) {
        p.unk3C = 1;
    } else {
        p.unk3C = 0;
    }
    p.unk44 = 0x10;
    p.unk46 = 0xF;
    p.unk48 = 0;
    func_15154488(&p, &p.unk8, (s32) basis, 0xFF, 1);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B01B8.s")
#endif

#ifdef NON_MATCHING
s32 func_15046C6C(f32 *, s32, f32, f32 *);
s32 func_15046F70(f32 *, s32, f32, f32 *);
void func_1504715C(void *, u8 *);
s32 func_15136698(f32, f32, s32, s32, s32, s32 *, f32 *, s32, s32, s32, s32);
void func_151DAB58(u8, f32, u8, f32 *, u8, u8, s32);

void func_151B03B8(struct127 *arg0, s32 arg1, s32 arg2) {
    struct {
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        s32 u9C;
        u8 padA0[0x10];
        s32 uB0;
        s8 uB4;
        u8 uB5;
        u8 padB6[0x2];
        s32 uB8;
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
        s32 uE4;
        u8 padE8[0x10];
        s32 uF8;
        s8 uFC;
        u8 uFD;
        u8 padFE[0x2];
        s32 u100;
        u8 pad104[0x4];
        s32 u108;
        u8 pad10C[0x20];
        s16 u12C;
        s16 u12E;
        s16 u130;
        s16 u132;
        f32 u134;
        f32 u138;
        f32 u13C;
        f32 u140;
        f32 u144;
        f32 u148;
        f32 u14C;
        f32 u150;
        f32 u154;
        s16 u158;
        s16 u15A;
        s16 u15C;
        s16 u15E;
        s16 u160;
        s16 u162;
        s16 u164;
        s16 u166;
        s8 u168;
        u8 pad169[0x3];
        f32 u16C;
        s16 u170;
        s16 u172;
        s32 u174;
    } sp;
    f32 temp_f10;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f22;
    f32 temp_f4;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s4;
    s32 var_s1;
    u32 temp_hi;

    temp_s4 = arg1 & 0xFF;
    if (arg0 != NULL) {
        func_1504715C(&sp.u108, arg0);
        sp.u134 = arg0->x_position;
        sp.u138 = arg0->y_position;
        sp.u13C = arg0->z_position;
        sp.u140 = 5.08f;
        sp.u158 = 0xA;
        sp.u12E = 0xFF;
        sp.u130 = -0x3F;
        sp.u15A = 0;
        sp.u12C = 0;
        sp.u132 = 0x2D;
        sp.u15C = 3;
        sp.u15E = 2;
        sp.u160 = 0x28;
        sp.u162 = 0x14;
        sp.u164 = 0x9B;
        sp.u166 = 0x64;
        sp.u168 = 0;
        sp.u170 = 0x10;
        sp.u172 = 0xF;
        sp.u174 = 0;
        sp.u144 = 3.02f;
        sp.u148 = 0.80700004f;
        sp.u14C = 0.70100003f;
        sp.u150 = 18.0f;
        sp.u154 = 11.8f;
        sp.u16C = 0.5f;
        func_15154488((struct_eu_15154488 *) &sp.u12C, (struct17 *) &sp.u134, (s32) &sp.u108, 0xFFU, 1);
        temp_hi = func_150ADA20() % 6U;
        sp.uF8 = 0;
        sp.uFC = 0;
        sp.uFD = 0;
        sp.u100 = 0;
        sp.uE0 = -10000.0f;
        var_s1 = temp_hi + 0xC;
        sp.uD8 = arg0->y_position + 100.0f;
        if (var_s1 != 0) {
loop_3:
            temp_s0 = func_150ADA20();
            func_15143874((s16) (temp_s0 & 0xFF), (func_150ADA68() * 100.0f) + 110.0f, &sp.uC8, &sp.uD0);
            temp_f4 = sp.uC8 + arg0->x_position;
            sp.uC8 = temp_f4;
            sp.uD4 = temp_f4;
            temp_f10 = sp.uD0 + arg0->z_position;
            sp.uD0 = temp_f10;
            sp.uDC = temp_f10;
            if ((func_15046F70(&sp.uD4, 0, arg0->y_position - 500.0f, &sp.uE0) != 0) && (sp.uFD != 3)) {
                sp.uCC = sp.uE0 + 10.0f;
                if (func_150ADA20() & 1) {
                    temp_f20 = func_150ADA68();
                    func_151D9B8C(0U, (temp_f20 * 4.5f) + 15.0f, (u32) ((func_150ADA68() * 100.0f) + 155.0f) & 0xFF, (s32) &sp.uE4, (struct17 *) &sp.uC8, 0x64, 0U, 1U, 0U, (u8) temp_s4, arg2);
                } else {
                    temp_f20_2 = func_150ADA68();
                    func_151DAB58(0, (temp_f20_2 * 5.9f) + 6.1f, (u32) ((func_150ADA68() * 100.0f) + 155.0f) & 0xFF, &sp.uC8, 1, temp_s4, arg2);
                }
                var_s1 -= 1;
                if (var_s1 == 0) {
                    goto block_9;
                }
                goto loop_3;
            }
        } else {
block_9:
            sp.uBC = arg0->x_position;
            sp.uC0 = arg0->y_position;
            sp.uB8 = 0;
            sp.uB5 = 0;
            sp.uB4 = 0;
            sp.uB0 = 0;
            sp.u98 = -10000.0f;
            sp.uC4 = arg0->z_position;
            sp.u8C = sp.uBC;
            sp.u90 = sp.uC0 + 100.0f;
            sp.u94 = sp.uC4;
            if ((func_15046C6C(&sp.u8C, 0, sp.uC0 - 500.0f, &sp.u98) != 0) && (sp.uB5 != 3)) {
                sp.uC0 = sp.u98 + 10.0f;
                temp_f20_3 = func_150ADA68();
                temp_f22 = func_150ADA68();
                temp_s0_2 = func_150ADA20();
                temp_s1 = func_150ADA20();
                func_15136698(((temp_f20_3 * 40.0f) + 120.0f) * 0.001f, ((temp_f22 * 123.0f) + 123.0f) * 0.00001f, (((u32) temp_s0_2 % 101U) + 0x9B) & 0xFF, (((u32) temp_s1 % 101U) + 0x64) & 0xFF, (func_150ADA20() % 56U) + 0x46, &sp.u9C, &sp.uBC, 0, 1, temp_s4, arg2);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B03B8.s")
#endif
#ifdef NON_MATCHING
/* P150 */
s32 memcpy(s32, f32 *, s32);
s32 func_15134070(struct127 *);
extern u8 D_800A43C6[];
// object_link_effect_spawn: spawns a type 0x13 effect tied to obj (func_151491F4, 0x98-byte state copied to +0x28)
// for the target's class: 4 without a target or for target types 0x53 / 0xA5, else func_15134070(target);
// class 0x63 or a class mode (D_800A43C6[class * 16]) of 2 spawns nothing. The state is {obj, obj[0x3B], zeros,
// 0.0f, mode == 1}. life = span, or 300 (not fixed) when span is -1. Returns the effect or 0. The type 0x13
// effects of obj are first cleared through func_151494E0({obj, obj[0x3B]}, 0x13).
s32 func_151B09BC(u8 *obj, u8 *target, s16 span, u8 arg3, s32 arg4) {
    struct {
        u8 *obj;
        u8 id;
    } key;
    struct {
        /* 0x00 */ u8 *obj;
        /* 0x04 */ u8 id;
        /* 0x08 */ s32 zero[0x22];
        /* 0x90 */ f32 f90;
        /* 0x94 */ u8 single;
    } state;
    u8 *part;
    s32 class;
    s32 mode;
    s32 life;
    s32 fixed;
    s32 i;

    if (obj == NULL) {
        return 0;
    }
    if (target == NULL || target[4] == 0x53 || target[4] == 0xA5) {
        class = 4;
    } else {
        class = func_15134070((struct127 *)target);
    }
    if (class == 0x63) {
        return 0;
    }
    mode = D_800A43C6[class * 16];
    if (mode == 2) {
        return 0;
    }
    state.single = (mode == 1) ? 1 : 0;
    key.obj = obj;
    key.id = obj[0x3B];
    func_151494E0((s32)&key, 0x13);
    if (span == -1) {
        fixed = 0;
        life = 300;
    } else {
        life = span;
        fixed = 1;
    }
    state.obj = obj;
    state.id = obj[0x3B];
    for (i = 0; i < 0x22; i++) {
        state.zero[i] = 0;
    }
    state.f90 = 0.0f;
    part = (u8 *)func_151491F4(life, -1, 0x13, fixed, 0xF, 0x98, arg3, arg4);
    if (part != NULL) {
        memcpy((s32)(part + 0x28), (f32 *)&state, 0x98);
    }
    return (s32)part;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B09BC.s")
#endif

#ifdef NON_MATCHING
void func_1513F680(u8 *, u8, u8, u8, u8);
void func_151B1EC8(u8 *arg0);

/* bone-attached point: bone index (64-byte matrices at the character's +0x1D4) and offset */
typedef struct {
    /* 0x00 */ u8 bone;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ f32 ofs[3];
} BonePt1138;
extern BonePt1138 D_800AA50C[]; /* 11 points */
extern BonePt1138 D_800AA5BC[]; /* the same for character kind 0x36 */
extern u8 D_800AB6F0[];

typedef struct SparkSlot1138 {
    /* 0x00 */ u8 *rec;    /* the spark (func_1513D524 record) */
    /* 0x04 */ s32 timer;  /* frames until it is let go */
    /* 0x08 */ struct SparkSlot1138 *next;
} SparkSlot1138;

/* the spark set at +0x28 of the object */
typedef struct {
    /* 0x00 */ u8 *target;  /* character */
    /* 0x04 */ u8 targetId; /* its id byte (+0x3B) */
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ s32 count;   /* attached sparks */
    /* 0x0C */ SparkSlot1138 slots[11];
    /* 0x90 */ f32 accum;
    /* 0x94 */ u8 kind;
} SparkSet1138;

/* func_1513D524's template */
typedef struct {
    /* 0x00 */ u8 sprite;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ s16 flags;
    /* 0x04 */ s16 life;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ s32 u8w;
    /* 0x0C */ s32 uC;
    /* 0x10 */ u8 colour[4];
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 pos[3];
    /* 0x28 */ s32 prev[3]; /* f32, copied as words */
    /* 0x34 */ f32 scale[3];
    /* 0x40 */ s32 u40;
    /* 0x44 */ u8 u44;
    /* 0x45 */ u8 u45;
    /* 0x46 */ u8 pad46[2];
} Spr1138;

/* the spark's motion block (record +0x110) */
typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ f32 spin;
    /* 0x10 */ u8 u10;
    /* 0x11 */ u8 u11;
    /* 0x12 */ u8 u12;
    /* 0x13 */ u8 u13;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ u8 u24;
    /* 0x25 */ u8 kind;
    /* 0x26 */ u8 pad26[2];
} SparkMotion1138;

// character_sparks_update: keeps up to 11 sparks attached to bone points (D_800AA50C, D_800AA5BC for character kind
// 0x36) of the target character. Each frame every attached spark is moved to its point (old position kept at
// +0x40) and its timer counts down by D_800BE9E4; at < 0 it is let go (velocity (pos - old) * D_800BEDC8 in x / z,
// func_1513F680(rec, 0x10, 0x1B, 0, 0x10), flag 1 at +0x58). New sparks (sprite D_800AB6F0[kind], life 52..102,
// timer 20..50) are spawned with func_1513D524 at random free points while accum (+ random 0..0.307 *
// D_800BE9A4 per frame) is above 1. Without a skeleton (+0x1D4) or with (+0x74 & 0xF) == 0xF all sparks are
// released (func_151B1EC8); when the target is gone or changed the object is ended (+0xE = -1).
void func_151B1138(u8 *obj) {
    SparkSet1138 *s = (SparkSet1138 *) (obj + 0x28);
    Spr1138 t;
    SparkMotion1138 m;
    SparkSlot1138 *slot;
    SparkSlot1138 *free;
    SparkSlot1138 *last;
    BonePt1138 *pt;
    u8 *tgt;
    u8 *rec;
    s32 nfree;
    s32 isFree;
    s32 i;
    u32 k;
    u8 kill = 0;

    if (*(s32 *) s->target == 0 || s->targetId != s->target[0x3B]) {
        kill = 1;
    }
    if (!kill) {
        tgt = s->target;
        if (*(s32 *) (tgt + 0x1D4) == 0 || (tgt[0x74] & 0xF) == 0xF) {
            if (s->count != 0) {
                func_151B1EC8(obj);
            }
        } else {
            free = NULL;
            last = NULL;
            nfree = 0;
            for (i = 0; i < 11; i++) {
                slot = &s->slots[i];
                isFree = 1;
                if (slot->rec != NULL) {
                    rec = slot->rec;
                    ((s32 *) (rec + 0x40))[0] = ((s32 *) (rec + 0x34))[0];
                    ((s32 *) (rec + 0x40))[1] = ((s32 *) (rec + 0x34))[1];
                    ((s32 *) (rec + 0x40))[2] = ((s32 *) (rec + 0x34))[2];
                    tgt = s->target;
                    pt = (tgt[4] == 0x36) ? &D_800AA5BC[i] : &D_800AA50C[i];
                    func_15143134(pt->ofs, slot->rec + 0x34, (void *) (pt->bone * 64 + *(s32 *) (tgt + 0x1D4)));
                    slot->timer -= D_800BE9E4;
                    if (slot->timer < 0) {
                        rec = slot->rec;
                        *(f32 *) (rec + 0x114) = 0.0f;
                        *(f32 *) (rec + 0x110) = (*(f32 *) (rec + 0x34) - *(f32 *) (rec + 0x40)) * D_800BEDC8;
                        *(f32 *) (rec + 0x118) = (*(f32 *) (rec + 0x3C) - *(f32 *) (rec + 0x48)) * D_800BEDC8;
                        func_1513F680(slot->rec, 0x10, 0x1B, 0, 0x10);
                        *(s32 *) (slot->rec + 0x58) |= 1;
                        slot->rec = NULL;
                        s->count--;
                    } else {
                        isFree = 0;
                    }
                }
                if (isFree) {
                    if (last == NULL) {
                        last = slot;
                    }
                    slot->next = free;
                    free = slot;
                    nfree++;
                }
            }
            if (nfree != 0) {
                s->accum = s->accum + func_150ADA68() * 307.0f * 0.001f * D_800BE9A4;
                if (1.0f < s->accum) {
                    last->next = free; /* the free list becomes a ring */
                    t.sprite = D_800AB6F0[s->kind];
                    t.flags = 0x1001;
                    t.life = (u32) func_150ADA20() % 51 + 52;
                    t.u8w = 0;
                    t.uC = 0;
                    t.colour[0] = 0;
                    t.colour[1] = 0;
                    t.colour[2] = 0;
                    t.colour[3] = 0xFF;
                    t.u40 = 0;
                    t.scale[0] = 1.0f;
                    t.scale[1] = 1.0f;
                    t.scale[2] = 1.0f;
                    m.u10 = 0;
                    m.u11 = 0;
                    *(f32 *) &t.prev[0] = 0.0f;
                    *(f32 *) &t.prev[1] = 0.0f;
                    *(f32 *) &t.prev[2] = 0.0f;
                    m.kind = s->kind;
                    m.u24 = func_150ADA20() & 1;
                    m.u14 = 5.0f;
                    m.u18 = 25.0f;
                    m.u1C = 2.0f;
                    t.u14 = 0.0f;
                    t.u18 = 0.0f;
                    m.u20 = 8.0f;
                    do {
                        for (k = (u32) func_150ADA20() % (u32) nfree; k != 0; k--) {
                            last = free;
                            free = free->next;
                        }
                        pt = &D_800AA50C[free - s->slots];
                        t.u45 = (u32) func_150ADA20() % 101 + 100;
                        t.u44 = (u32) func_150ADA20() % 101 + 155;
                        m.u12 = (u32) func_150ADA20() % 5 + 4;
                        m.u13 = (u32) func_150ADA20() % 5 + 4;
                        m.spin = (func_150ADA68() * 506.0f + -703.0f) * 0.001f;
                        func_15143134(pt->ofs, t.pos, (void *) (pt->bone * 64 + *(s32 *) (s->target + 0x1D4)));
                        t.prev[0] = *(s32 *) &t.pos[0];
                        t.prev[1] = *(s32 *) &t.pos[1];
                        t.prev[2] = *(s32 *) &t.pos[2];
                        func_150ADA20(); /* RNG advance, result unused */
                        free->rec = (u8 *) func_1513D524((s32) &t, 0x11, 0, 0, 0x10, 2, 0x28, obj[0xC], obj[1]);
                        if (free->rec != NULL) {
                            memcpy(free->rec + 0x110, &m, 0x28);
                            free->timer = (u32) func_150ADA20() % 31 + 20;
                            free = free->next;
                            nfree--;
                            last->next = free;
                            s->count++;
                        }
                        s->accum -= 1.0f;
                    } while (1.0f < s->accum && nfree != 0);
                }
            }
        }
    }
    if (kill) {
        *(s16 *) (obj + 0xE) = -1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B1138.s")
#endif

#ifdef NON_MATCHING
/* P143 */
extern f32 D_800AA6D0;
extern f32 D_800AA6D4;
extern f32 D_800AA6D8;
// debris_fall_update: update handler (D_8008A058 slot 16) of a falling debris sprite. Motion block at +0x110:
// velocity x/y/z, gravity +0x11C; x / z speeds are multiplied by 0.25 * dt each frame, y gains gravity * dt; the
// position +0x34 moves by the mean speed, the trail point +0x40 moves with it and then eases back towards the
// position (factor D_800AA6D0). With floor check (+0x134) a floor probe (func_15046F70, from the previous height
// minus the half height +0x30) that hits ends the sprite (0) and spawns a splash at the floor + 5: either
// func_151D9B8C (scale D_800AA6D4) or the ring func_151DAB58 (scale D_800AA6D8), of type +0x135, sized by the mean
// of +0x124 + +0x12C / 2 and +0x128 + +0x130 / 2. Returns 1 while it keeps falling.
s32 func_151B173C(u8 *fx) {
    f32 *mv = (f32 *)(fx + 0x110);
    f32 probe[3];
    f32 hit[3];
    f32 y0, vx0, vz0, vy, dvy;
    f32 dx, dy, dz;
    f32 x, y, z;
    f32 size;
    s8 ret;

    y0 = *(f32 *)(fx + 0x38);
    vx0 = mv[0];
    vz0 = mv[2];
    ret = 1;
    mv[0] = vx0 * (0.25f * D_800BE9A4);
    mv[2] = vz0 * (0.25f * D_800BE9A4);
    dx = (mv[0] + vx0) * 0.5f * D_800BE9A4;
    vy = mv[1];
    dvy = mv[3] * D_800BE9A4;
    dy = vy * D_800BE9A4 + dvy * D_800BE9A4 * 0.5f;
    dz = (mv[2] + vz0) * 0.5f * D_800BE9A4;
    mv[1] = vy + dvy;
    *(f32 *)(fx + 0x38) = y0 + dy;
    *(f32 *)(fx + 0x34) += dx;
    *(f32 *)(fx + 0x3C) += dz;
    *(f32 *)(fx + 0x40) += dx;
    *(f32 *)(fx + 0x44) += dy;
    *(f32 *)(fx + 0x48) += dz;
    x = *(f32 *)(fx + 0x34);
    y = *(f32 *)(fx + 0x38);
    z = *(f32 *)(fx + 0x3C);
    *(f32 *)(fx + 0x40) = x + (*(f32 *)(fx + 0x40) - x) * D_800AA6D0;
    *(f32 *)(fx + 0x44) = y + (*(f32 *)(fx + 0x44) - y) * D_800AA6D0;
    *(f32 *)(fx + 0x48) = z + (*(f32 *)(fx + 0x48) - z) * D_800AA6D0;
    if (fx[0x134] != 0) {
        probe[0] = x;
        probe[1] = y0 - *(f32 *)(fx + 0x30);
        probe[2] = *(f32 *)(fx + 0x3C);
        if (func_15046F70(probe, 0, *(f32 *)(fx + 0x38) - *(f32 *)(fx + 0x30), (f32 *)(fx + 0x78)) != 0) {
            hit[0] = probe[0];
            hit[1] = *(f32 *)(fx + 0x78) + 5.0f;
            hit[2] = probe[2];
            size = ((mv[5] + mv[7] * 0.5f) + (mv[6] + mv[8] * 0.5f)) * 0.5f;
            if (func_150ADA20() & 1) {
                func_151D9B8C(fx[0x135], size * D_800AA6D4, fx[0x5C], (s32)(fx + 0x7C), (struct17 *)hit, 100, 0, 1, 0,
                              fx[0xC], fx[1]);
            } else {
                func_151DAB58(fx[0x135], size * D_800AA6D8, fx[0x5C], hit, 1, fx[0xC], fx[1]);
            }
            ret = 0;
        }
    }
    return ret;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B173C.s")
#endif

s32 func_151B1A28(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    s32 temp_v1;

    if (temp_v0 < 32) {
        temp_v1 = temp_v0 << 3;
        if (temp_v1 < arg0[0x5C]) {
            arg0[0x5C] = temp_v1;
        }
    }
    return 1;
}

#ifdef NON_MATCHING
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, f32 *, s32);
extern s32 D_800DD608;
extern s32 D_800DD618;

u8 *func_151B1A5C(u8 *arg0, s16 arg1) {
    struct {
        u8 u3B;
        f32 u3C;
        u8 pad40[0x10];
        f32 u50;
        f32 u54;
        u8 pad58[0x4];
        f32 u5C;
        u8 * u60;
        u8 * u64;
    } sp;
    u8 *sp34;
    f32 *sp30;
    f32 *sp2C;
    f32 *temp_a0;
    f32 *temp_a1;
    f32 *temp_v1;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    s32 temp_t0;
    u8 *temp_v0;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u64, &sp.u3B);
    sp.u60 = sp.u64;
    if (sp.u64 != NULL) {
        if (sp.u3B != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp30 = temp_a1;
            sp34 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_t0 = arg1 * 4;
        temp_v1 = temp_t0 + &D_800DD618;
        temp_a0 = temp_t0 + &D_800DD608;
        var_f16 = -1.0f;
        var_f14 = ((*temp_v1 * ((*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x34)))) - (*temp_a0 * ((*(f32 *)((u8 *)arg0 + 0x48)) - (*(f32 *)((u8 *)arg0 + 0x3C))))) * D_800BEDC8;
        if (var_f14 < 0.0f) {
            var_f16 = 1.0f;
            var_f14 = -var_f14;
        }
        var_f12 = sqrtf(var_f14) * 0.25f;
        if (var_f12 > 1.5707964f) {
            var_f12 = 1.5707964f;
        }
        temp_f12 = var_f12 * var_f16;
        sp30 = temp_v1;
        sp2C = temp_a0;
        sp.u3C = temp_f12;
        sp.u5C = sinf(temp_f12);
        temp_f0 = cosf(temp_f12);
        temp_f12_2 = (*(f32 *)((u8 *)arg0 + 0x2C));
        temp_f14 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_f2 = temp_f12_2 * temp_f0;
        temp_f18 = temp_f12_2 * sp.u5C;
        temp_f16 = -temp_f2;
        sp.u54 = temp_f14 * temp_f0;
        sp.u50 = temp_f14 * sp.u5C;
        (*(s16 *)((u8 *)sp.u64 + 0)) = (s16) (s32) ((*temp_v1 * temp_f16) + (*(f32 *)((u8 *)arg0 + 0x34)));
        (*(s16 *)((u8 *)sp.u64 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (*temp_a0 * temp_f16));
        (*(s16 *)((u8 *)sp.u64 + 6)) = 0;
        (*(s16 *)((u8 *)sp.u64 + 0x10)) = (s16) (s32) ((*temp_v1 * temp_f2) + (*(f32 *)((u8 *)arg0 + 0x34)));
        (*(s16 *)((u8 *)sp.u64 + 0x12)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 0x14)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (*temp_a0 * temp_f2));
        (*(s16 *)((u8 *)sp.u64 + 0x16)) = 0;
        temp_f0_2 = temp_f2 - sp.u50;
        (*(s16 *)((u8 *)sp.u64 + 0x20)) = (s16) (s32) ((*temp_v1 * temp_f0_2) + (*(f32 *)((u8 *)arg0 + 0x34)));
        (*(s16 *)((u8 *)sp.u64 + 0x22)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) - temp_f18) - sp.u54);
        (*(s16 *)((u8 *)sp.u64 + 0x24)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (*temp_a0 * temp_f0_2));
        (*(s16 *)((u8 *)sp.u64 + 0x26)) = 0;
        temp_f0_3 = -(temp_f2 + sp.u50);
        (*(s16 *)((u8 *)sp.u64 + 0x30)) = (s16) (s32) ((*temp_v1 * temp_f0_3) + (*(f32 *)((u8 *)arg0 + 0x34)));
        (*(s16 *)((u8 *)sp.u64 + 0x32)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f18) - sp.u54);
        (*(s16 *)((u8 *)sp.u64 + 0x34)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (*temp_a0 * temp_f0_3));
        (*(s16 *)((u8 *)sp.u64 + 0x36)) = 0;
        return sp.u60;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B1A5C.s")
#endif
s32 func_151B1DD8(u8 *arg0) {
    s32 pad;
    u8 *p;
    f32 s;
    f32 c;

    arg0[0x120] += (s8)arg0[0x122] * D_800BE9E4;
    arg0[0x121] += (s8)arg0[0x123] * D_800BE9E4;
    p = arg0 + 0x110;
    s = func_151423D8((u8)(arg0[0x120] - 0x40));
    c = func_151423D8((u8)(p[0x11] - 0x40));
    *(f32 *)(arg0 + 0x2C) += ((*(f32 *)(p + 0x14) + (*(f32 *)(p + 0x1C) * s)) - *(f32 *)(arg0 + 0x2C)) * 0.5f;
    *(f32 *)(arg0 + 0x30) += ((*(f32 *)(p + 0x18) + (*(f32 *)(p + 0x20) * c)) - *(f32 *)(arg0 + 0x30)) * 0.5f;
    return 1;
}

#ifdef NON_MATCHING
void func_151B1EC8(u8 *arg0) {
    s32 var_s3;
    u8 *var_s0;
    u8 *var_s2;

    var_s2 = arg0 + 0x28;
    (*(s32 *)((u8 *)arg0 + 0x30)) = 0;
    var_s0 = var_s2 + 0xC;
    var_s3 = 0;
    (*(f32 *)((u8 *)arg0 + 0xB8)) = 0.0f;
    do {
        if ((*(s32 *)((u8 *)var_s2 + 0xC)) != 0) {
            func_1516972C((*(struct102 **)((u8 *)var_s0 + 0)));
        }
        (*(struct102 **)((u8 *)var_s0 + 0)) = NULL;
        (*(s32 *)((u8 *)var_s0 + 4)) = 0;
        (*(s32 *)((u8 *)var_s0 + 8)) = 0;
        var_s3 += 0xC;
        var_s2 += 0xC;
        var_s0 += 0xC;
    } while (var_s3 != 0x84);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B1EC8.s")
#endif
void func_151B1F54(struct102 *arg0, u8 *arg1, u8 arg2) {
    s32 cur;
    u8 *temp_v0;
    cur = *(s32 *)((u8 *)arg0 + 0x28);
    if ((arg2 == 0) || (arg2 == 0x13)) {
        if (cur == (*(s32 *)((u8 *)arg1 + 0)) || ((*(u8 *)((u8 *)arg0 + 0x2C)) == (*(u8 *)((u8 *)arg1 + 4)))) {
            func_1516972C(arg0);
        }
    } else {
        temp_v0 = (u8 *)arg0 + 0x28;
        if (arg2 == 0x2D) {
            if (*(s32 *)(arg1 + 0) == *(s32 *)(temp_v0 + 0)) {
                *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
                *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
                return;
            }
            if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
                *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 0);
                *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
            }
        }
    }
}

void func_151B2008(void *arg0) {
    func_151B1EC8(arg0);
    func_1514933C(arg0);
}

void func_151B2034(void *arg0) {
    func_151B1EC8(arg0);
    func_15149368(arg0);
}

void func_151B2060(u8 *arg0) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;

    if (arg0 == NULL) {
        return;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_151491F4(0x3C, -1, 0x15, 1, 0x11, 0xC, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

extern f32 D_800BE9A4;
typedef struct { f32 x, y, z; } V3_20E4;
extern V3_20E4 D_8008FE70, D_8008FE7C;
void func_15143874(s16, f32, f32 *, f32 *);
s32 func_151308E4(void *, s32, s32, u8, s32);
void func_15143794(s16, s16, f32, void *);
void func_151B20E4(u8 *arg0) {
    u8 *p;
    V3_20E4 *q;
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64[3];
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0x8];
    } sp;
    s32 obj;
    f32 scale;
    V3_20E4 b;
    V3_20E4 a;

    p = arg0 + 0x28;
    *(f32 *)(p + 8) += (697.0f + func_150ADA68() * 342.0f) * 0.001f * D_800BE9A4;
    if (*(f32 *)(p + 8) > 1.0f) {
        if (*(s32 *)(*(u8 **)p + 0x1D4) != 0) {
            V3_20E4 c = D_8008FE70;
            func_15143134(&c, &b, *(s32 *)(*(u8 **)p + 0x1D4) + 0x800);
            {
                V3_20E4 d = D_8008FE7C;
                func_15143134(&d, &a, *(s32 *)(*(u8 **)p + 0x1D4) + 0x640);
            }
            sp.u51 = 0x29;
            sp.u3C = 0xE03;
            sp.u34 = 0x200005;
            sp.u4C = 0xB0;
            sp.u4D = 0xA0;
            sp.u4E = 0x2A;
            sp.u48 = 0x40;
            sp.u49 = 0xB;
            sp.u4A = 0x6A;
            sp.u38 = 0;
            sp.u40 = 0;
            sp.u44 = 0;
            sp.u4B = 0xFF;
            sp.u50 = 0xFF;
            sp.u94 = 3;
            sp.u95 = 3;
            sp.u88 = 0.0f;
            sp.u8C = 0xE05;
            sp.u96 = 0xA;
            sp.u97 = -1;
            sp.u52 = 0x1E;
            sp.u54 = 8;
            sp.u56 = 0x32;
            sp.u58 = 1.02700007f;
            scale = 0.924f;
            do {
                s32 base;
                s16 ang;

                sp.u3E = (func_150ADA20() % 41U) + 0x1E;
                sp.u4F = (func_150ADA20() % 156U) + 0x64;
                sp.u5C = sp.u60 = (func_150ADA68() * 104.0f) + 199.0f;
                if (func_150ADA20() & 1) {
                    q = &b;
                } else {
                    q = &a;
                }
                base = ((*(u16 *)(*(u8 **)p + 0x7A) >> 8) + 0x40) & 0xFF;
                ang = ((func_150ADA20() % 100U) + base) - 0x31;
                func_15143874(ang, 36.0f, &sp.u64[0], &sp.u64[2]);
                sp.u64[1] = 0.0f;
                sp.u64[0] += q->x;
                sp.u64[1] = q->y;
                sp.u64[2] += q->z;
                func_15143874(ang, ((func_150ADA68() * 1497.0f) + 995.0f) * 0.01f, &sp.u7C[0], &sp.u7C[2]);
                sp.u7C[1] = 0.0f;
                if (!p && !p && !p) { // fakematch: basic-block boundary (remote permuter)
                }
                sp.u8C &= ~0xC0;
                if (func_150ADA20() & 1) {
                    sp.u8C |= 0x40;
                }
                if (func_150ADA20() & 1) {
                    sp.u8C |= 0x80;
                }
                obj = func_151308E4(&sp, 1, 4, arg0[0xC], arg0[1]);
                if (obj != 0) {
                    memcpy(obj + 0xA8, &scale, 4);
                }
                *(f32 *)(p + 8) -= 1.0f;
            } while (*(f32 *)(p + 8) > 1.0f);
            return;
        }
        while (*(f32 *)(p + 8) > 1.0f) {
            *(f32 *)(p + 8) -= 1.0f;
        }
    }
}

void func_151B255C(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    s32 temp_v1;
    temp_v0 = (u8 *)arg0 + 0x28;
    if (arg2 == 0x2D) {
        if (*(s32 *)(arg1 + 0) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 0);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
        goto dummy_label; dummy_label: ; // fakematch: b + target-copied lw ra
    } else if (arg2 == 0) {
        temp_v1 = *(s32 *)(arg1 + 0);
        if (temp_v1 == *(s32 *)(temp_v0 + 0) || *(u8 *)(temp_v0 + 4) == *(u8 *)(arg1 + 4)) {
            func_1516972C(arg0);
        }
    }
}
