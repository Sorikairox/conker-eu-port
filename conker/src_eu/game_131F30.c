#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void fx_sparks_emit(u8 *arg0);
void func_1000FD38(s32, s32, s32);
#endif


#ifdef NON_MATCHING
// prop_owner_effects_clear: P256: for the prop `obj` (a 0xA0-byte record of D_800DBEF4), finds its owner, the first
// live object (interaction_state != 0) of D_800CC2D0[0..24] whose bit is set in the prop's mask D_800DC3C4[index],
// or NULL, then clears effects keyed on it (func_151494E0): kinds 0xF9 / 0xF8 / 0xF7 (obj +0x72) clear the type
// 0x35 effects of {9, part list, owner} with the 9-entry part lists D_800A2750 / D_800A275C / D_800A2768 (copied to
// the stack), kind 0xF6 the type 0x38 effects of {owner}; other kinds do nothing.
typedef struct {
    u8 b[9];
} PartList9;
extern PartList9 D_800A2750;
extern PartList9 D_800A275C;
extern PartList9 D_800A2768;
extern s32 *D_800DC3C4;
/* was func_15104A80 */
void prop_owner_effects_clear(u8 *obj) {
    struct {
        s32 count;
        u8 *parts;
        struct127 *owner;
    } key;
    struct {
        struct127 *owner;
    } key38;
    PartList9 parts;
    struct127 *owner;
    struct127 *p;
    s32 mask;
    s32 i;

    owner = NULL;
    mask = D_800DC3C4[(struct131 *) obj - D_800DBEF4];
    if (mask != 0) {
        p = D_800CC2D0;
        for (i = 0; i < 25 && owner == NULL; i++, p++) {
            if (p->interaction_state != 0 && (mask & (1 << i))) {
                owner = p;
            }
        }
    }
    switch (obj[0x72]) {
    case 0xF9:
    case 0xF8:
    case 0xF7:
        key.owner = owner;
        if (obj[0x72] == 0xF9) {
            parts = D_800A2750;
        } else if (obj[0x72] == 0xF8) {
            parts = D_800A275C;
        } else if (obj[0x72] == 0xF7) {
            parts = D_800A2768;
        }
        key.count = 9;
        key.parts = parts.b;
        func_151494E0((s32) &key, 0x35);
        break;
    case 0xF6:
        key38.owner = owner;
        func_151494E0((s32) &key38, 0x38);
        break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/prop_owner_effects_clear.s")
#endif

#ifdef NON_MATCHING
s32 func_15046F70(f32 *, s32, f32, u8 *);
s32 bolt_arc_spawn(s16 *, s32, u8, u8);
void func_15143874(s16, f32, f32 *, f32 *);
s32 func_151464B8(s32);

/* was func_15104C44 */
void fx_ground_arcs_update(u8 *arg0) {
    struct {
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        s16 u8C;
        s8 u8E;
        u8 pad8F[0x1];
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        s8 uC0;
        u8 padC1[0x3];
        s32 uC4;
        f32 uC8;
        f32 uCC;
        s16 uD0;
        s16 uD2;
        s8 uD4;
        s8 uD5;
        s8 uD6;
        s8 uD7;
        s8 uD8;
    } sp;
    u8 *sp60;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    u8 *temp_s1;

    temp_s1 = arg0 + 0x28;
    if ((*(s16 *)((u8 *)arg0 + 0x30)) >= 0) {
        (*(s16 *)((u8 *)temp_s1 + 8)) = (s16) ((*(s16 *)((u8 *)temp_s1 + 8)) - D_800BE9E4);
        if ((*(s16 *)((u8 *)temp_s1 + 8)) < 0) {
            func_1000FD38(func_1000EF40, (*(s32 *)((u8 *)temp_s1 + 0)), 0);
        }
        if (func_151464B8((*(s32 *)((u8 *)temp_s1 + 0x44))) == 0) {
            (*(f32 *)((u8 *)temp_s1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 4)) + ((0.19700001f + (random_float() * 0.3f)) * D_800BE9A4));
            if ((*(f32 *)((u8 *)temp_s1 + 4)) > 1.0f) {
                sp.u8E = 1;
                sp.uC0 = -1;
                sp.u84 = (*(f32 *)((u8 *)temp_s1 + 0x10)) + (*(f32 *)((u8 *)temp_s1 + 0x1C));
                sp.uD0 = 3;
                sp.uD2 = 4;
                sp.uD8 = 0;
                sp.uCC = 45.0f;
                sp.uC8 = 25.0f;
                sp.u90 = (*(f32 *)((u8 *)temp_s1 + 0xC));
                sp.u94 = (*(f32 *)((u8 *)temp_s1 + 0x10)) + (*(f32 *)((u8 *)temp_s1 + 0x1C));
                sp.u98 = (*(f32 *)((u8 *)temp_s1 + 0x14));
                sp.uD4 = 0x61;
                sp.uD5 = 0xF2;
                sp.uD6 = 0xFF;
                sp60 = temp_s1 + 0x20;
                sp.uA0 = ((*(f32 *)((u8 *)temp_s1 + 0x10)) + (*(f32 *)((u8 *)temp_s1 + 0x1C))) - 180.0f;
                do {
                    temp_s0 = random_int();
                    func_15143874((s16) (temp_s0 & 0xFF), ((random_float() * 0.5f) + 0.5f) * (*(f32 *)((u8 *)temp_s1 + 0x18)), &sp.u80, &sp.u88);
                    sp.u80 += (*(f32 *)((u8 *)temp_s1 + 0xC));
                    sp.u88 += (*(f32 *)((u8 *)temp_s1 + 0x14));
                    if (func_15046F70(&sp.u80, 0, (*(f32 *)((u8 *)temp_s1 + 0x10)), sp60) != 0) {
                        temp_s0_2 = random_int();
                        func_15143874((s16) (temp_s0_2 & 0xFF), random_float() * 220.0f, &sp.u78, &sp.u7C);
                        temp_s0_3 = random_int();
                        func_15143874((s16) (temp_s0_3 & 0xFF), random_float() * 220.0f, &sp.u70, &sp.u74);
                        sp.u9C = (*(f32 *)((u8 *)temp_s1 + 0xC)) + sp.u78;
                        sp.uB4 = sp.u80;
                        sp.uA4 = (*(f32 *)((u8 *)temp_s1 + 0x14)) + sp.u7C;
                        sp.uB8 = (*(f32 *)((u8 *)temp_s1 + 0x20));
                        sp.uA8 = sp.u80 + sp.u70;
                        sp.uBC = sp.u88;
                        sp.uB0 = sp.u88 + sp.u74;
                        sp.uAC = sp.uB8 + 180.0f;
                        sp.u8C = (random_int() % 13U) + 8;
                        sp.uD7 = (random_int() % 156U) + 0x64;
                        sp.uC4 = (random_int() % 3U) + 5;
                        bolt_arc_spawn(&sp.u8C, 0, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
                    }
                    (*(f32 *)((u8 *)temp_s1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 4)) - 1.0f);
                } while ((*(f32 *)((u8 *)temp_s1 + 4)) > 1.0f);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/fx_ground_arcs_update.s")
#endif
#ifdef NON_MATCHING
void func_1000FD38(s32, s32, s32);

/* was func_15104FF8 */
void fx_ground_arcs_on_msg(s32 arg0, s32 arg1, s32 arg2) {
    u8 *sp40;
    s32 (*sp3C)(struct57 *, struct57 *, s32 *, s32, s32, s32, u16 *);
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v1;

    temp_v1 = arg0 + 0x28;
    if ((arg2 & 0xFF) == 0x38) {
        temp_v0 = (*(u8 **)((u8 *)temp_v1 + 0));
        if ((*(u8 *)((u8 *)temp_v0 + 0x14)) == 1) {
            (*(s16 *)((u8 *)temp_v1 + 8)) = 0xFA;
            sp3C = func_1000EF40;
            sp40 = temp_v1;
            func_1000FD38(func_1000EF40, temp_v0, 0);
            temp_v0_2 = (*(u8 **)((u8 *)temp_v1 + 0));
            func_1000FA64(0x236U, (*(s16 *)((u8 *)temp_v0_2 + 0)), (*(s16 *)((u8 *)temp_v0_2 + 2)), (*(s16 *)((u8 *)temp_v0_2 + 4)), 0x4000, 0x5DCU, 0x3E8, (s32) sp3C, temp_v0_2, 0, 8, 0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/fx_ground_arcs_on_msg.s")
#endif
#ifdef NON_MATCHING
s32 bolt_spawn(f32 *, f32 *, s32, f32 *, f32, s32, s32, s32);
s32 func_151464B8(s32);

/* was func_151050B0 */
void fx_quad_bolts_update(u8 *arg0) {
    struct {
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        s16 uB0;
        s16 uB2;
        s16 uB4;
        s16 uB6;
        s16 uB8;
        u8 padBA[0x2];
        s32 uBC;
        s32 uC0;
        s8 uC4;
        s8 uC5;
        s8 uC6;
        s8 uC7;
        s8 uC8;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f6;
    f32 var_f4;
    s32 temp_s0;
    s32 temp_v1;
    s32 var_s1;
    u32 temp_v0;
    u8 *temp_s2;
    u8 *temp_v0_2;
    u8 *temp_v0_3;

    temp_s2 = arg0 + 0x28;
    if ((*(s16 *)((u8 *)arg0 + 0x2C)) < 0) {
        (*(s8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x28))) + 0x14)) = 1;
        return;
    }
    (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_s2 + 0))) + 0x14)) = 0;
    (*(s16 *)((u8 *)temp_s2 + 4)) = (s16) ((*(s16 *)((u8 *)temp_s2 + 4)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)temp_s2 + 4)) < 0) {
        func_151494E0(0, 0x39U);
        func_151494E0(0, 0x4BU);
    }
    if (func_151464B8((*(s32 *)((u8 *)temp_s2 + 0x6C))) == 0) {
        (*(f32 *)((u8 *)temp_s2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 8)) + ((0.040000003f + (random_float() * 0.07f)) * D_800BE9A4));
        if ((*(f32 *)((u8 *)temp_s2 + 8)) > 1.0f) {
            sp.uB0 = 0x64;
            sp.uB2 = 0;
            sp.uB4 = 0xA;
            sp.uB6 = 1;
            sp.uB8 = 0xA;
            sp.uBC = 4;
            sp.uC0 = 2;
            sp.uC4 = 0x7E;
            sp.uC5 = 0xF9;
            sp.uC6 = 0xFF;
            sp.uC7 = 0x37;
            sp.uC8 = 0xC8;
            sp.u9C = 10.0f;
            sp.uA0 = 15.0f;
            sp.uA4 = 20.0f;
            sp.uA8 = 44.0f;
            sp.uAC = 37.0f;
            do {
                temp_s0 = (u32) (random_float() * 3.0f) & 0xFF;
                var_f4 = (f32) temp_s0;
                temp_f6 = (random_float() * 2.0f) + 1.0f;
                if (temp_s0 < 0) {
                    var_f4 += 4294967296.0f;
                }
                temp_v0 = (u32) (temp_f6 + var_f4);
                temp_v1 = temp_v0 & 0xFF;
                var_s1 = temp_v0 & 0xFF;
                if (temp_v1 >= 4) {
                    var_s1 = (temp_v1 - 4) & 0xFF;
                }
                temp_f0 = random_float();
                temp_v0_2 = temp_s2 + (temp_s0 * 0xC);
                sp.u90 = ((*(f32 *)((u8 *)temp_v0_2 + 0x3C)) * temp_f0) + (*(f32 *)((u8 *)temp_v0_2 + 0xC));
                sp.u94 = ((*(f32 *)((u8 *)temp_v0_2 + 0x40)) * temp_f0) + (*(f32 *)((u8 *)temp_v0_2 + 0x10));
                sp.u98 = ((*(f32 *)((u8 *)temp_v0_2 + 0x44)) * temp_f0) + (*(f32 *)((u8 *)temp_v0_2 + 0x14));
                temp_f0_2 = random_float();
                temp_v0_3 = temp_s2 + (var_s1 * 0xC);
                sp.u84 = ((*(f32 *)((u8 *)temp_v0_3 + 0x3C)) * temp_f0_2) + (*(f32 *)((u8 *)temp_v0_3 + 0xC));
                sp.u88 = ((*(f32 *)((u8 *)temp_v0_3 + 0x40)) * temp_f0_2) + (*(f32 *)((u8 *)temp_v0_3 + 0x10));
                sp.u8C = ((*(f32 *)((u8 *)temp_v0_3 + 0x44)) * temp_f0_2) + (*(f32 *)((u8 *)temp_v0_3 + 0x14));
                bolt_spawn(&sp.u90, &sp.u84, 3, &sp.u9C, 0.32500002f, 2, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                (*(f32 *)((u8 *)temp_s2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 8)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s2 + 8)) > 1.0f);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/fx_quad_bolts_update.s")
#endif
/* was func_1510550C */
void fx_free_on_msg_4b(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4B) {
        node_destroy(arg0);
    }
}

/* was func_15105548 */
void fx_quad_bolts_on_msg(struct207 *arg0, s32 *arg1, u8 arg2) {
    struct206 *temp_v0 = &arg0->unk28;
    if ((arg2 == 0x38) && (temp_v0->unk0->unk14 == 1)) {
        temp_v0->unk70 = *arg1;
        temp_v0->unk4 = 250;
    }
}

#ifdef NON_MATCHING
typedef struct { s16 v[9]; } HitSurface558C; /* 0x12-byte surface record (func_150ACEA0) */
void func_151C384C(void *, u8, s32);
void func_151522DC(void *, s32 *, f32 *, s32, u8, s32);
struct210 *cam_sprite_puff_spawn(f32, u8, s32, u8 *, s16, u8, u8, s32, u8, s32);

// impact_debris_burst: hit effect of object p (state at p + 0x110 = s: impact point s+0x30, normal s+0x60, surface
// record s+0x6C, flags s+0x88). Always throws debris with cam_sprite_puff_spawn (speed 15..40, 200..255, 50..130); on
// surface type 9 (flags & 0x1F) it adds embers (func_151C384C) with chance 0.4 and stops. Otherwise embers with
// chance 0.1, and with chance 0.4 an animated impact flash (func_151522DC, one keyframe {0x85, 0.1}) at the point
// facing back along the normal.
/* was func_1510558C */
void impact_debris_burst(u8 *p) {
    struct {
        s32 u0;
        s32 u4;
        f32 pos[3];
        f32 dir[3];
        HitSurface558C hit;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        s16 u48;
        s16 u4A;
        f32 u4C;
        f32 u50;
        f32 u54;
    } flash;
    s32 frames[1];
    f32 scales[1];
    f32 r;
    s32 a;
    u8 *s;
    f32 *pos;
    HitSurface558C *hit;

    r = random_float();
    a = random_int();
    s = p + 0x110;
    hit = (HitSurface558C *) (s + 0x6C);
    pos = (f32 *) (s + 0x30);
    cam_sprite_puff_spawn(r * 25.0f + 15.0f, (u32) a % 56 + 200, (s32) hit, (u8 *) pos, (u32) random_int() % 81 + 50, 1, 1,
                  *(s32 *) (s + 0x88), p[0xC], p[1]);
    if ((*(s32 *) (s + 0x88) & 0x1F) == 9) {
        if (random_float() < 0.4f) {
            func_151C384C(pos, p[0xC], p[1]);
        }
        return;
    }
    if (random_float() < 0.1f) {
        func_151C384C(pos, p[0xC], p[1]);
    }
    if (random_float() < 0.4f) {
        frames[0] = 0x85;
        scales[0] = 0.1f;
        flash.u0 = 1;
        flash.u4 = 3;
        flash.pos[0] = pos[0];
        flash.pos[1] = pos[1];
        flash.pos[2] = pos[2];
        flash.dir[0] = -*(f32 *) (s + 0x60);
        flash.dir[1] = -*(f32 *) (s + 0x64);
        flash.dir[2] = -*(f32 *) (s + 0x68);
        flash.hit = *hit;
        flash.u34 = 614.0f;
        flash.u38 = 0.009000001f;
        flash.u48 = 0xF;
        flash.u4A = 0xF;
        flash.u3C = 0.010000001f;
        flash.u40 = -0.90400004f;
        flash.u44 = 0.395f;
        flash.u4C = 0.060000002f;
        flash.u50 = 0.142f;
        flash.u54 = 25.777f;
        func_151522DC(&flash, frames, scales, 1, p[0xC], p[1]);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/impact_debris_burst.s")
#endif

/* was func_15105848 */
void fx_sparks_on_msg(struct207 *arg0, s32 arg1, u8 arg2) {
    struct206 *temp_v0;

    if (arg2 == 0x38) {
        temp_v0 = &arg0->unk28;
        fx_sparks_emit(arg0);
        temp_v0->unkC |= 1;
    } else {
        temp_v0 = &arg0->unk28;
        if (arg2 == 0x39) {
            temp_v0->unkC &= 0xFFFE;
        }
    }
}

#ifdef NON_MATCHING
s32 func_151432BC(u8 *, s32 *, s32 *, s32 *, s32 *);
void func_15143794(s16, s16, f32, void *);
s32 func_151464B8(s32);
s32 streak_spawn(s32 *, s32, f32 *, s32, s32, s32);

/* was func_151058B4 */
void fx_sparks_emit(u8 *arg0) {
    struct {
        s32 u88;
        s32 u8C;
        f32 u90;
        s32 u94;
        u8 pad98[0x8];
        f32 uA0;
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
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        u8 padB2[0x2];
        s32 uB4;
        s32 uB8;
        s16 uBC;
        s16 uBE;
        s16 uC0;
        s8 uC2;
        u8 padC3[0x1];
        f32 uC4;
        s8 uC8;
        s8 uC9;
        u8 padCA[0x2];
        s32 uCC;
        f32 uD0;
        s32 uD4;
        s16 uD8;
        s16 uDA;
        s32 uDC;
        s8 uE0;
        s8 uE1;
    } sp;
    f32 var_f20;
    s32 temp_s0;
    s32 temp_s1;
    u8 *temp_s4;

    if (func_151464B8((*(s32 *)((u8 *)arg0 + 0x30))) == 0) {
        temp_s4 = arg0 + 0x28;
        var_f20 = ((random_float() * 0.0013f) + 0.0018999999f) * (*(f32 *)((u8 *)temp_s4 + 4));
        if (var_f20 > 1.0f) {
            sp.uDA = 0x15;
            sp.uDC = 0xA;
            sp.uA7 = 0x61;
            sp.uA8 = 0xF2;
            sp.uE0 = -1;
            sp.uA4 = 4;
            sp.uA5 = 2;
            sp.uA6 = 3;
            sp.uA9 = 0xFF;
            sp.uAB = 0xFF;
            sp.uAC = 0xFF;
            sp.uAD = 0xFF;
            sp.uAE = 0xFF;
            sp.uAF = 0xFF;
            sp.uB0 = 3;
            sp.uB1 = 0x24;
            sp.uB4 = 0x200005;
            sp.uB8 = 0x60600;
            sp.uBC = 0x14;
            sp.uBE = 0xC;
            sp.uC0 = 1;
            sp.uC2 = 0;
            sp.uC4 = 1.0f;
            sp.uC8 = -1;
            sp.uC9 = 0;
            sp.uD0 = (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s4 + 0))) + 2));
            do {
                sp.uAA = (random_int() % 101U) + 0x9B;
                sp.uE1 = (random_int() & 3) + 3;
                func_151432BC((*(u8 **)((u8 *)temp_s4 + 0)), &sp.uCC, &sp.uD4, &sp.u8C, &sp.u88);
                sp.uD8 = (random_int() % 31U) + 0x1E;
                sp.u90 = (random_float() * 10.13f) + 7.3999996f;
                temp_s0 = random_int();
                temp_s1 = random_int();
                func_15143794((s16) (temp_s0 & 0xFF), (s16) (((u32) temp_s1 % 22U) - 0x36), (random_float() * 20.0f) + 30.0f, &sp.u94);
                sp.uA0 = (random_float() * 1.4860001f) + -3.048f;
                streak_spawn(&sp.uCC, 0, &sp.u90, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                var_f20 -= 1.0f;
            } while (var_f20 > 1.0f);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/fx_sparks_emit.s")
#endif
// void fx_sparks_emit(void *arg0) {
//     s8 spE1;
//     s8 spE0;
//     ?32 spDC;
//     s16 spDA;
//     s16 spD8;
//     ? spD4;
//     f32 spD0;
//     ? spCC;
//     s8 spC9;
//     s8 spC8;
//     f32 spC4;
//     s8 spC2;
//     s16 spC0;
//     s16 spBE;
//     s16 spBC;
//     ?32 spB8;
//     ?32 spB4;
//     s8 spB1;
//     s8 spB0;
//     s8 spAF;
//     s8 spAE;
//     s8 spAD;
//     s8 spAC;
//     s8 spAB;
//     s8 spAA;
//     s8 spA9;
//     s8 spA8;
//     s8 spA7;
//     s8 spA6;
//     s8 spA5;
//     s8 spA4;
//     f32 spA0;
//     ? sp94;
//     f32 sp90;
//     ? sp8C;
//     ? sp88;
//     f32 temp_f20;
//     f32 temp_f20_2;
//     f32 temp_f24;
//     f32 temp_f26;
//     s32 temp_s0;
//     u32 temp_s1;
//     void *temp_s4;
//     f32 phi_f20;
//
//     if (func_151464B8(arg0->unk30) == 0) {
//         temp_s4 = arg0 + 0x28;
//         temp_f20 = ((random_float() * *(void *)0x800A23EC) + *(void *)0x800A23F0) * temp_s4->unk4;
//         if (temp_f20 > 1.0f) {
//             spDA = 0x15;
//             spDC = 0xA;
//             spA7 = 0x61;
//             spA8 = 0xF2;
//             spE0 = -1;
//             spA4 = 4;
//             spA5 = 2;
//             spA6 = 3;
//             spA9 = 0xFF;
//             spAB = 0xFF;
//             spAC = 0xFF;
//             spAD = 0xFF;
//             spAE = 0xFF;
//             spAF = 0xFF;
//             spB0 = 3;
//             spB1 = 0x24;
//             spB4 = 0x200005;
//             spB8 = 0x60600;
//             spBC = 0x14;
//             spBE = 0xC;
//             spC0 = 1;
//             spC2 = 0;
//             spC4 = 1.0f;
//             spC8 = -1;
//             spC9 = 0;
//             temp_f26 = *(void *)0x800A23F4;
//             temp_f24 = *(void *)0x800A23F8;
//             spD0 = (f32) temp_s4->unk0->unk2;
//             phi_f20 = temp_f20;
// loop_3:
//             spAA = (random_int() % 0x65U) + 0x9B;
//             spE1 = (random_int() & 3) + 3;
//             func_151432BC(temp_s4->unk0, &spCC, &spD4, &sp8C, &sp88);
//             spD8 = (random_int() % 0x1FU) + 0x1E;
//             sp90 = (random_float() * temp_f24) + temp_f26;
//             temp_s0 = random_int();
//             temp_s1 = random_int();
//             func_15143794((s16) (temp_s0 & 0xFF), (s16) ((temp_s1 % 0x16U) - 0x36), (random_float() * 20.0f) + 30.0f, &sp94);
//             spA0 = (random_float() * *(void *)0x800A23FC) + *(void *)0x800A2400;
//             streak_spawn(&spCC, 0, &sp90, 0, (?32) arg0->unkC, (?32) arg0->unk1);
//             temp_f20_2 = phi_f20 - 1.0f;
//             phi_f20 = temp_f20_2;
//             if (temp_f20_2 > 1.0f) {
//                 goto loop_3;
//             }
//         }
//     }
// }

/* was func_15105BC8 */
void fx_shake_if_active(struct204 *arg0) {
    if ((arg0->unk34 & 1) != 0) {
        func_1508B20C(arg0->unk28->unk0, arg0->unk28->unk2, arg0->unk28->unk4, 500.0f);
    }
}

/* was func_15105C24 */
struct_eu_node *scene_node_find_type2e(s32 arg0) {
    u8 i;
    u8 j;
    struct_eu_node *p;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (p = D_800DD280[j][(&D_800A5770)[i]]; p != NULL; p = p->next) {
                if ((*(u8 *)((u8 *)p + 0x13) == 0x2E) && (arg0 == *(s32 *)((u8 *)p + 0x28))) {
                    return p;
                }
            next: ; // fakematch: label at the end of the inner loop body moves the j/i increments into the exit block
            }
        }
    }
    return NULL;
}
// void *scene_node_find_type2e(s32 arg0) {
//     s32 temp_t4;
//     s32 temp_t5;
//     void *temp_a0;
//     void *temp_a0_2;
//     s32 phi_v1;
//     s32 phi_v0;
//     void *phi_a0;
//
//     phi_v0 = 0;
// loop_1:
//     phi_v1 = 0;
// loop_2:
//     temp_a0 = *((((((phi_v1 * 4) - phi_v1) * 4) + phi_v1) << 5) + 0x800DCE50 + (((phi_v0 * 4) + 0x800A0000)->unk5770 * 4));
//     phi_a0 = temp_a0;
//     if (temp_a0 != 0) {
// loop_3:
//         if ((phi_a0->unk13 == 0x2E) && (arg0 == phi_a0->unk28)) {
//             return phi_a0;
//         }
//         temp_a0_2 = phi_a0->unk8;
//         phi_a0 = temp_a0_2;
//         if (temp_a0_2 != 0) {
//             goto loop_3;
//         }
//     }
//     temp_t4 = (phi_v1 + 1) & 0xFF;
//     phi_v1 = temp_t4;
//     if (temp_t4 < 2) {
//         goto loop_2;
//     }
//     temp_t5 = (phi_v0 + 1) & 0xFF;
//     phi_v0 = temp_t5;
//     if (temp_t5 < 2) {
//         goto loop_1;
//     }
//     return NULL;
// }
