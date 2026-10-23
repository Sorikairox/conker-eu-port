#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A5860[];
void func_150D71A8(f32 *arg0, f32 *arg1);
void func_150D6898(s32 arg0, u8 arg1, s32 arg2);
void func_150D6944(s32 arg0, u8 arg1, s32 arg2);
void func_150D6B00(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void func_150D6BB4(u8 arg0, u8 arg1, s32 arg2);
#endif
// hoisted forward declaration(s) for func_150D6898
#ifdef NON_MATCHING
s32 func_15154728(s32, f32, f32, f32, f32, s32, s32); /* P95: f32 parameter */
#else
s32 func_15154728(s32, f32, s32, f32, f32, s32, s32);
#endif


void func_150D5950(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_15149130(300, -1, 0x38, -1, 0, 0x28, 0xC, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void func_1514373C(f32, f32, f32 *, f32 *);
s32 func_1515C668(u8 *, u8 **);

void func_150D59D8(u8 *arg0) {
    struct {
        u8 * u84;
        u8 pad88[0x8];
        f32 u90;
        f32 u94;
        s32 u98;
        s32 u9C;
        s16 uA0;
        s16 uA2;
        s32 uA4;
        s32 uA8;
        s8 uAC;
        s8 uAD;
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s8 uB4;
        s8 uB5;
        s16 uB6;
        s16 uB8;
        s16 uBA;
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
        f32 uE4;
        f32 uE8;
        f32 uEC;
        s32 uF0;
        s32 uF4;
        s8 uF8;
        s8 uF9;
        s8 uFA;
        s8 uFB;
        s8 uFC;
        s8 uFD;
        s8 uFE;
    } sp;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f24;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f6;
    f32 var_f12;
    f32 var_f12_2;
    f32 var_f14;
    f32 var_f2;
    s32 temp_s0;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_s1;
    u8 *temp_s2;

    temp_s2 = (*(u8 **)((u8 *)arg0 + 0x28));
    temp_s1 = arg0 + 0x28;
    if (((*(s32 *)((u8 *)temp_s2 + 0)) == 0) || ((*(u8 *)((u8 *)temp_s1 + 4)) != (*(u8 *)((u8 *)temp_s2 + 0x3B)))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    if (((*(f32 *)((u8 *)temp_s2 + 0x28)) < 8.0f) && (((*(s32 *)((u8 *)temp_s2 + 0x184)) & 0x1F) == 0xE)) {
        (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) + ((3.0000002f + (func_150ADA68() * 1.0f)) * D_800BE9A4));
        if ((*(f32 *)((u8 *)temp_s1 + 8)) > 1.0f) {
            if (func_1515C668(temp_s2, &sp.u84) == 0) {
                sp.u84 = ((u8 *)&D_800A5860);
            }
            func_1514373C((*(f32 *)((u8 *)temp_s2 + 0x40)) * 0.017453292f, 1.0f, &sp.u90, &sp.u94); /* P95: was 0x3F800000 as an int */
            sp.uB5 = 0x28;
            sp.uAD = 0xFF;
            sp.uA0 = 0x2203;
            sp.u98 = 0x200005;
            sp.uAC = 0xFF;
            sp.uAE = 0xFF;
            sp.uAF = 0xFF;
            sp.uB0 = 0xFF;
            sp.uB1 = 0xFF;
            sp.uB2 = 0xFF;
            sp.u9C = 0;
            sp.uA4 = 0;
            sp.uA8 = 0;
            sp.uB4 = 0xFF;
            sp.uB6 = 5;
            sp.uB8 = 0x33;
            sp.uBA = 1;
            sp.uF0 = 0x84C207;
            sp.uF8 = 6;
            sp.uF9 = 8;
            sp.uFA = -1;
            sp.uFB = -1;
            sp.uFC = -1;
            sp.uFD = 0;
            sp.uF4 = 0;
            sp.uFE = 0xFF;
            sp.uBC = 1.0f;
            sp.uD4 = 0.0f;
            sp.uD8 = 0.0f;
            sp.uDC = 0.0f;
            temp_f24 = -sp.u90;
            do {
                temp_s0 = func_150ADA20() & 1;
                temp_f20 = func_150ADA68();
                temp_f0 = func_150ADA68();
                if (temp_s0 != 0) {
                    var_f14 = 35.0f;
                } else {
                    var_f14 = -35.0f;
                }
                temp_f2 = sp.u90 * 180.0f;
                temp_f12 = sp.u94 * 180.0f;
                sp.uC8 = (((*(f32 *)((u8 *)temp_s2 + 0x14)) + (sp.u94 * var_f14)) - (temp_f2 * 0.5f)) + (temp_f2 * temp_f20);
                sp.uCC = (*(f32 *)((u8 *)temp_s2 + 0x180));
                sp.uD0 = (((*(f32 *)((u8 *)temp_s2 + 0x1C)) + (temp_f24 * var_f14)) - (temp_f12 * 0.5f)) + (temp_f12 * temp_f20);
                if (temp_s0 != 0) {
                    var_f2 = (temp_f0 * 2.907f) + 6.0000005f;
                    var_f12 = var_f2;
                } else {
                    var_f2 = (temp_f0 * 2.907f) + 6.0000005f;
                    var_f12 = -var_f2;
                }
                sp.uE0 = (var_f12 * sp.u94) - ((*(f32 *)((u8 *)sp.u84 + 0)) * 0.564f);
                sp.uE4 = 3.1560001f * var_f2;
                if (temp_s0 != 0) {
                    var_f12_2 = var_f2;
                } else {
                    var_f12_2 = -var_f2;
                }
                sp.uE8 = (var_f12_2 * temp_f24) - ((*(f32 *)((u8 *)sp.u84 + 8)) * 0.564f);
                sp.uA2 = (func_150ADA20() % 10U) + 0x1F;
                sp.uB3 = (func_150ADA20() % 76U) + 0xB4;
                temp_f2_2 = (func_150ADA68() * 364.0f) + 111.0f;
                sp.uC0 = temp_f2_2;
                sp.uC4 = temp_f2_2;
                temp_f6 = func_150ADA68() * 0.157f;
                sp.uF0 &= ~0xC0;
                sp.uEC = temp_f6 + -2.111f;
                var_s0 = 0;
                if (func_150ADA20() & 1) {
                    var_s0 = 0x80;
                }
                if (func_150ADA20() & 1) {
                    var_v0 = 0x40;
                } else {
                    var_v0 = 0;
                }
                sp.uF0 |= var_v0 | var_s0;
                func_151307F0(&sp.u98, 1, 0, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s1 + 8)) > 1.0f);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D59D8.s")
#endif
void func_150D5E7C(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x28;
    if (arg2 == 0 || arg2 == 0x2F || arg2 == 3) {
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

void func_150D5F3C(struct260 *arg0) {
    func_1514933C(arg0);
}

void func_150D5F5C(struct260 *arg0) {
    func_15149368(arg0);
}

#ifdef NON_MATCHING
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, s16 *, f32 *, f32 *, f32 *, f32 *, s32, s32 *, f32);
s32 func_15132FBC(void *, s32, s32, s32, s32, s32);
s32 func_15134070(struct127 *);
void func_15143874(s16, f32, f32 *, f32 *);
f32 func_15144A74(f32 *, f32 *);
s32 func_15144E80(s16 *, f32 *, f32 *, f32 *);
s32 func_15145128(f32 *, f32 *, s32 *, s32 *);
s32 func_15146078(f32 *, f32 *, f32 *);
void func_151C0910(s16 *, f32 *, s32, s32);
void func_151C0B54(f32 *, s32, s32);
void func_151C0BA0(f32 *, s32, s32);
extern s32 D_800A0E00[3];   /* sprites of the first burst */
extern s32 D_800A42F4[];    /* per type: entry count of the D_80089DC0 list */
extern s32 *D_80089DC0[];   /* per type: sprite list (entries 2.. are used) */

/* P67: particle request passed to func_15132FBC (0x7C bytes). */
typedef struct {
    /* 0x00 */ f32 scale[4];     /* 1, 1, xz_scale, y_scale */
    /* 0x10 */ f32 rot[3];       /* random degrees */
    /* 0x1C */ f32 one[3];
    /* 0x28 */ f32 pos[3];
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 spinX;
    /* 0x44 */ f32 spinY;
    /* 0x48 */ f32 spinZ;
    /* 0x4C */ f32 gravity;
    /* 0x50 */ s32 flags;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 sprite;
    /* 0x58 */ u8  u58;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8  alpha;
    /* 0x61 */ u8  u61;
    /* 0x62 */ u8  u62[6];
    /* 0x68 */ u8  u68;
    /* 0x69 */ u8  pad69;
    /* 0x6A */ u8  u6A;
    /* 0x6C */ struct127 *owner;
    /* 0x70 */ u8  ownerId;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x78 */ s32 u78;
} DebrisParticle;

/* P67: debris burst of a destroyed object: sounds, two particle bursts thrown out along the surface it hit (ray cast
 * along its last movement) or straight up, then the dust / scorch effects. arg1 / arg2 are passed through. */
void func_150D5F7C(struct127 *arg0, s32 arg1, s32 arg2) {
    DebrisParticle p;
    f32 pos[3];          /* sp1B4: centre, 50 above the object */
    f32 dir[3];          /* sp1A8: last movement (normalised) */
    f32 hit[3];          /* sp19C */
    s16 tri[9];          /* sp188: the hit triangle */
    f32 axisA[3];        /* sp15C */
    f32 axisB[3];        /* sp150 */
    f32 normal[3];       /* sp168 */
    f32 t;
    s32 surface;
    s32 type;
    s32 tmp0, tmp1;
    s32 moved;
    s32 useDefault;
    u8 hitWall = 0;
    u8 id = arg1 & 0xFF;
    s32 *s;
    s32 i;

    pos[0] = arg0->x_position;
    pos[1] = arg0->y_position + 50.0f;
    pos[2] = arg0->z_position;
    dir[0] = arg0->x_position - arg0->old_x_position;
    dir[1] = arg0->y_position - arg0->old_y_position;
    dir[2] = arg0->z_position - arg0->old_z_position;
    type = func_15134070(arg0);
    if (type == 0x63) {
        return;
    }
    if ((arg0->unk184 & 0x1F) == 0xE) {
        func_10010630(0x434, arg0, 0x7D00, 0x2BC, 0x7D0);
    } else {
        func_10010630(0x4C8, arg0, -0x7D00, 0x2BC, 0x7D0);
    }
    func_10010630((func_150ADA20() & 1) + 0x2B6, arg0, 0x7D00, 0x3E8, 0xBB8);
    func_10010630((func_150ADA20() & 3) + 0x2B1, arg0, 0x7D00, 0x2BC, 0x7D0);
    func_151C0B54(pos, id, arg2);
    func_151C0BA0(pos, id, arg2);
    func_15145A50(arg0);
    if (arg0->unk1D4 == NULL || (arg0->unk74 & 0xF) == 0xF) {
        return;
    }

    /* the surface it was moving into: basis (axisA, axisB, normal) of the hit triangle, facing back */
    moved = func_15145128(dir, dir, &tmp0, &tmp1) != 0;
    if (moved && func_150ACEA0(arg0->old_x_position, arg0->old_y_position, arg0->old_z_position, dir[0], dir[1], dir[2],
                               0, tri, &hit[0], &hit[1], &hit[2], &t, 0, &surface, 0.0f) != 0 && t < 397.0f) {
        hitWall = 1;
    }
    useDefault = 1;
    if (hitWall) {
        useDefault = 0;
        if (func_15144E80(tri, axisA, axisB, normal) != 0) {
            s32 a, b;

            func_15145128(axisA, axisA, &a, &b);
            func_15145128(axisB, axisB, &a, &b);
            func_15145128(normal, normal, &a, &b);
            if (func_15144A74(normal, dir) > 0.0f) {
                normal[0] = -normal[0];
                normal[1] = -normal[1];
                normal[2] = -normal[2];
            }
        } else {
            useDefault = 1;
        }
    }
    if (useDefault) {
        if (moved) {
            normal[0] = -dir[0];
            normal[1] = -dir[1];
            normal[2] = -dir[2];
            func_15146078(normal, axisA, axisB);
        } else {
            normal[0] = 0.0f; normal[1] = 1.0f; normal[2] = 0.0f;
            axisA[0] = 1.0f;  axisA[1] = 0.0f;  axisA[2] = 0.0f;
            axisB[0] = 0.0f;  axisB[1] = 0.0f;  axisB[2] = 1.0f;
        }
    }

    p.scale[0] = 1.0f;
    p.scale[1] = 1.0f;
    normal[0] *= 1000.0f;
    normal[1] *= 1000.0f;
    normal[2] *= 1000.0f;
    p.scale[2] = arg0->xz_scale;
    p.one[0] = 1.0f;
    p.one[1] = 1.0f;
    p.one[2] = 1.0f;
    p.scale[3] = arg0->y_scale;
    p.pos[0] = pos[0];
    p.pos[1] = pos[1];
    p.pos[2] = pos[2];
    p.flags = 0x21E8;
    p.u58 = 0;
    p.u5C = 0;
    p.alpha = 0xFF;
    p.u61 = 8;
    p.u62[0] = 0;
    p.u62[1] = 0;
    p.u62[2] = 0;
    p.u62[3] = 0;
    p.u62[4] = 0;
    p.u62[5] = 0;
    p.u68 = 2;
    p.u6A = 1;
    p.owner = arg0;
    p.u78 = 0;
    p.spinY = 0.0f;
    p.ownerId = arg0->unique_id;
    p.u72 = 0xC;
    p.u74 = 0x15;

    /* burst 1: one particle per D_800A0E00 sprite, thrown in a random direction around the normal */
    for (i = 0; i < 3; i++) {
        f32 speed = func_150ADA68() * 0.0132f + 0.0298f;
        s32 ang = func_150ADA20();
        f32 c, d;

        func_15143874(ang & 0xFF, func_150ADA68() * 759.0f, &c, &d);
        p.vel[0] = (axisA[0] * c + axisB[0] * d + normal[0]) * speed;
        p.vel[1] = (axisA[1] * c + axisB[1] * d + normal[1]) * speed;
        p.vel[2] = (axisA[2] * c + axisB[2] * d + normal[2]) * speed;
        p.rot[0] = func_150ADA68() * 360.0f;
        p.rot[1] = func_150ADA68() * 360.0f;
        p.rot[2] = func_150ADA68() * 360.0f;
        p.spinX = func_150ADA68() * 38.444f + -19.222f;
        p.spinZ = func_150ADA68() * 38.444f + -19.222f;
        p.gravity = func_150ADA68() * 0.648f + -1.3970001f;
        p.life = (u32)func_150ADA20() % 21 + 30;
        p.sprite = D_800A0E00[i];
        func_15132FBC(&p, 0, 0, 0, id, arg2);
    }

    /* burst 2: the type's own sprites, entries 2 .. count - 1 */
    p.u72 = 0xC;
    p.u74 = 0x15;
    for (i = 2; i < D_800A42F4[type]; i++) {
        f32 speed = func_150ADA68() * 0.02f + 0.0052f;
        s32 ang = func_150ADA20();
        f32 c, d;

        func_15143874(ang & 0xFF, func_150ADA68() * 723.0f, &c, &d);
        p.vel[0] = (axisA[0] * c + axisB[0] * d + normal[0]) * speed;
        p.vel[1] = (axisA[1] * c + axisB[1] * d + normal[1]) * speed;
        p.vel[2] = (axisA[2] * c + axisB[2] * d + normal[2]) * speed;
        p.rot[0] = func_150ADA68() * 360.0f;
        p.rot[1] = func_150ADA68() * 360.0f;
        p.rot[2] = func_150ADA68() * 360.0f;
        p.spinX = func_150ADA68() * 40.45f + -20.225f;
        p.spinZ = func_150ADA68() * 40.45f + -20.225f;
        p.gravity = func_150ADA68() * 0.62600005f + -1.0890001f;
        p.life = (u32)func_150ADA20() % 41 + 40;
        p.sprite = D_80089DC0[type][i];
        func_15132FBC(&p, 0, 0, 0, id, arg2);
    }

    if (arg0->camera != NULL && D_80082FA0 <= 0) {
        func_150D6BB4(arg0->camera->unk23D, id, arg2);
    }
    if (hitWall && arg0->camera != NULL) {
        if ((surface & 0x1F) == 0xE) {
            func_150D6B00((s32)tri, (s32)hit, id, arg2);
        } else {
            func_151C0910(tri, hit, id, arg2);
        }
    }
    func_150D6944((s32)pos, id, arg2);
    func_150D6898((s32)pos, id, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D5F7C.s")
#endif
void func_150D6898(s32 arg0, u8 arg1, s32 arg2) {
    f32 temp_f12;
    f32 sp28;
    f32 temp_f14;
    f32 var_f18;
    u32 temp_t7;
    sp28 = func_150ADA68();
    temp_t7 = (func_150ADA20() % 56U) + 0xC8;
    temp_f14 = sp28 * 4.0f;
    temp_f12 = temp_f14 + 15.0f;
    var_f18 = (f32) temp_t7;
#ifdef NON_MATCHING
    func_15154728(arg0, temp_f12, 1.37457f, var_f18, 0.0f, arg1, arg2); /* P95: float literal (asm passes the bits 0x3FAFF1E9) */
#else
    func_15154728(arg0, temp_f12, 0x3FAFF1E9, var_f18, 0.0f, arg1, arg2);
#endif
}

s32 func_15154DF4(s32, f32, f32, f32, u8, s32);
extern f32 D_800A0E80;
extern f32 D_800A0E84;

void func_150D6944(s32 arg0, u8 arg1, s32 arg2) {
    s32 pad;
    f32 sp28;
    f32 sp24;

    sp24 = func_150ADA68();
    sp28 = func_150ADA68();
    func_15154DF4(arg0, (sp24 * 3.0f) + 8.0f, (sp28 * D_800A0E80) + D_800A0E84, (func_150ADA68() * 50.0f) + 100.0f, (s32) arg1, arg2);
}

#ifdef NON_MATCHING
extern f32 D_800A0E88;
extern f32 D_800A0E8C;
extern f32 D_800A0E90;
extern f32 D_800A0E94;
extern f32 D_800A0E98;
void func_150D69F8(u8 *arg0, f32 *arg1) {
    (*(s32 *)((u8 *)arg0 + 0)) = 6;
    (*(s32 *)((u8 *)arg0 + 4)) = 3;
    *arg1 = D_800A0E88;
    (*(f32 *)((u8 *)arg0 + 0x14)) = D_800A0E8C;
    (*(s32 *)((u8 *)arg0 + 0x2C)) = 4;
    (*(s32 *)((u8 *)arg0 + 0x30)) = 3;
    (*(f32 *)((u8 *)arg0 + 0x18)) = D_800A0E90;
    (*(f32 *)((u8 *)arg0 + 0x1C)) = 150.0f;
    (*(f32 *)((u8 *)arg0 + 0x20)) = 105.0f;
    (*(f32 *)((u8 *)arg0 + 0x24)) = 396.0f;
    (*(f32 *)((u8 *)arg0 + 0x28)) = 612.0f;
    (*(f32 *)((u8 *)arg0 + 0x34)) = 25.0f;
    (*(f32 *)((u8 *)arg0 + 0x38)) = D_800A0E94;
    (*(f32 *)((u8 *)arg0 + 0x3C)) = -2.0f;
    (*(s16 *)((u8 *)arg0 + 0x44)) = 0x14;
    (*(s16 *)((u8 *)arg0 + 0x46)) = 0x1E;
    (*(s16 *)((u8 *)arg0 + 0x48)) = 0x64;
    (*(s16 *)((u8 *)arg0 + 0x4A)) = 0x64;
    (*(s16 *)((u8 *)arg0 + 0x4C)) = 0xC;
    (*(s16 *)((u8 *)arg0 + 0x4E)) = 0x14;
    (*(f32 *)((u8 *)arg0 + 0x40)) = D_800A0E98;
    if ((D_80082FA0 >= 2) || (D_8008FD8C >= 8)) {
    s32 pad;
        (*(s8 *)((u8 *)arg0 + 0x50)) = -1;
        return;
    }
    (*(s8 *)((u8 *)arg0 + 0x50)) = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D69F8.s")
#endif
s32 func_151A6308(f32, s32, s32, s32, s16, u8, u8, u8, s32);

void func_150D6B00(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 pad;
    u32 sp38;
    f32 sp34;

    sp34 = func_150ADA68();
    sp38 = func_150ADA20();
    func_151A6308((sp34 * 100.0f) + 150.0f, ((sp38 % 71U) + 0x82) & 0xFF, arg0, arg1, (func_150ADA20() % 31U) + 0x32, 0, 1, (s32) arg2, arg3);
}

s32 func_15182BE0(u8, u8, u8, s32, s16, u8, u8, s32); 

void func_150D6BB4(u8 arg0, u8 arg1, s32 arg2) {
    s32 pad;
    u32 sp28;

    sp28 = func_150ADA20();
    func_15182BE0(0xFF, 0xFF, 0xFF, ((sp28 % 56U) + 0xC8) & 0xFF, (func_150ADA20() % 6U) + 0x19, (s32) arg0, (s32) arg1, arg2);
}

#ifdef NON_MATCHING
void func_15143794(s16, s16, f32, void *);

void func_150D6C40(f32 *arg0, s32 arg1, s32 arg2) {
    struct {
        f32 * u48;
        u8 u4C;
        u8 pad4D[0x3];
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        s32 u64;
        s32 u68;
        s16 u6C;
        s16 u6E;
        s32 u70;
        s32 u74;
        s8 u78;
        s8 u79;
        s8 u7A;
        s8 u7B;
        s8 u7C;
        s8 u7D;
        s8 u7E;
        s8 u7F;
        s8 u80;
        s8 u81;
        s16 u82;
        s16 u84;
        s16 u86;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        u8 pad98[0x8];
        s32 uA0;
        u8 padA4[0x8];
        s32 uAC;
        u8 padB0[0x8];
        f32 uB8;
        s32 uBC;
        s32 uC0;
        s8 uC4;
        s8 uC5;
        s8 uC6;
        s8 uC7;
        s8 uC8;
        s8 uC9;
        s8 uCA;
        u8 padCB[0xD];
        f32 * uD8;
        u8 uDC;
        u8 padDD[0x3];
        f32 uE0;
        s32 uE4;
        s32 uE8;
        s16 uEC;
        s16 uEE;
        s32 uF0;
        s32 uF4;
        s8 uF8;
        s8 uF9;
        s8 uFA;
        s8 uFB;
        s8 uFC;
        s8 uFD;
        s8 uFE;
        s8 uFF;
        s8 u100;
        s8 u101;
        s16 u102;
        s16 u104;
        s16 u106;
        f32 u108;
        f32 u10C;
        f32 u110;
        f32 u114;
        u8 pad118[0x8];
        f32 u120;
        f32 u124;
        f32 u128;
        s32 u12C;
        u8 pad130[0x8];
        f32 u138;
        s32 u13C;
        s32 u140;
        s8 u144;
        s8 u145;
        s8 u146;
        s8 u147;
        s8 u148;
        s8 u149;
        s8 u14A;
    } sp;
    f32 temp_f12;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f2_2;
    s16 temp_t1;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    u32 temp_hi;
    u8 *temp_s2;

    temp_s3 = arg1 & 0xFF;
    temp_hi = func_150ADA20() % 11U;
    sp.uD8 = arg0;
    sp.u101 = 0x6C;
    sp.uDC = (*(u8 *)((u8 *)arg0 + 0x3B));
    var_s2 = temp_hi + 0xF;
    sp.uEC = 0x5103;
    sp.uE4 = 0x200005;
    sp.uE8 = 0;
    sp.uF0 = 0;
    sp.uF4 = 0;
    sp.uFC = 0x14;
    sp.uFD = 0x14;
    sp.uFE = 0x14;
    sp.uFB = 0xFF;
    sp.uF8 = 0x4B;
    sp.uF9 = 0x4B;
    sp.uFA = 0x4B;
    sp.u100 = 0xFF;
    sp.uE0 = 0.871118f;
    func_150D71A8(arg0, &sp.u114);
    sp.u102 = 0xF;
    sp.u104 = 0x11;
    sp.u13C = 0x84DE01;
    sp.u144 = 8;
    sp.u145 = 6;
    sp.u146 = 0x1E;
    sp.u147 = -1;
    sp.u148 = -1;
    sp.u149 = 8;
    sp.u140 = 0;
    sp.u14A = 0xFF;
    sp.u120 = 0.0f;
    sp.u124 = 0.0f;
    sp.u128 = 0.0f;
    sp.u108 = 1.062733f;
    do {
        sp.uFF = (func_150ADA20() % 156U) + 0x64;
        temp_t1 = (func_150ADA20() % 14U) + 8;
        sp.u106 = temp_t1;
        sp.uEE = temp_t1;
        temp_f2 = (func_150ADA68() * 207.0f) + 238.0f;
        sp.u10C = temp_f2;
        sp.u110 = temp_f2;
        temp_s1 = func_150ADA20();
        temp_s0 = func_150ADA20();
        func_15143794((s16) (temp_s1 & 0xFF), (s16) (((u32) temp_s0 % 36U) - 0x19), (func_150ADA68() * 30.0f) + 25.0f, &sp.u12C);
        temp_f16 = func_150ADA68() * 0.0f;
        sp.u13C &= ~0xC0;
        sp.u138 = temp_f16;
        var_s1 = 0;
        if (func_150ADA20() & 1) {
            var_s1 = 0x80;
        }
        if (func_150ADA20() & 1) {
            var_s0 = 0x40;
        } else {
            var_s0 = 0;
        }
        sp.u13C |= var_s0 | var_s1;
        temp_v0 = func_151307F0(&sp.uE4, 1, 0, 0xC, temp_s3, arg2);
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0xA8, &sp.uD8, 0xC);
        }
        var_s2 -= 1;
    } while (var_s2 > 0);
    sp.u48 = arg0;
    sp.u4C = (*(u8 *)((u8 *)arg0 + 0x3B));
    sp.u50 = 0.0f;
    sp.u58 = 2392.16f;
    temp_f12 = (func_150ADA68() * 3.0f) + 9.0f;
    sp.u54 = temp_f12;
    temp_f2_2 = (func_150ADA68() * 80.0f) + 100.0f;
    sp.u60 = temp_f2_2 / (temp_f12 * temp_f12);
    sp.u7F = (s8) (u32) temp_f2_2;
    sp.u81 = 0x79;
    sp.u6C = 0x4403;
    sp.u64 = 0x200005;
    sp.u68 = 0;
    sp.u70 = 0;
    sp.u74 = 0;
    sp.u7C = 0xFF;
    sp.u7D = 0xFF;
    sp.u7E = 0xDF;
    sp.u7B = 0xFF;
    sp.u78 = 0xFF;
    sp.u79 = 0xFF;
    sp.u7A = 0xFF;
    sp.u80 = 0xFF;
    sp.u5C = temp_f2_2;
    func_150D71A8(arg0, &sp.u94);
    temp_s2 = ((u8 *)&D_800A5860);
    (*(s32 *)((u8 *)(&sp.uA0) + 0)) = (s32) (*(s32 *)((u8 *)temp_s2 + 0));
    (*(s32 *)((u8 *)(&sp.uA0) + 4)) = (s32) (*(s32 *)((u8 *)temp_s2 + 4));
    (*(s32 *)((u8 *)(&sp.uA0) + 8)) = (s32) (*(s32 *)((u8 *)temp_s2 + 8));
    sp.u82 = 1;
    sp.u84 = 0xFF;
    sp.u86 = 1;
    sp.u88 = 1.0f;
    var_s1_2 = 0;
    if (func_150ADA20() & 1) {
        var_s1_2 = 0x40;
    }
    if (func_150ADA20() & 1) {
        var_s0_2 = 0x80;
    } else {
        var_s0_2 = 0;
    }
    sp.uBC = var_s0_2 | 0x4C000 | var_s1_2;
    sp.uC4 = 6;
    sp.uC5 = 6;
    sp.uC6 = 0x1F;
    sp.uC7 = -1;
    sp.uC8 = -1;
    sp.uC9 = 9;
    sp.uC0 = 0;
    sp.uCA = 0xFF;
    (*(s32 *)((u8 *)(&sp.uAC) + 0)) = (s32) (*(s32 *)((u8 *)temp_s2 + 0));
    (*(s32 *)((u8 *)(&sp.uAC) + 4)) = (s32) (*(s32 *)((u8 *)temp_s2 + 4));
    (*(s32 *)((u8 *)(&sp.uAC) + 8)) = (s32) (*(s32 *)((u8 *)temp_s2 + 8));
    sp.u6E = 0x12C;
    sp.u90 = 0.0f;
    sp.u8C = 0.0f;
    sp.uB8 = 0.0f;
    temp_v0_2 = func_151307F0(&sp.u64, 1, 0, 0x1C, temp_s3, arg2);
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0xA8, &sp.u48, 0x1C);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D6C40.s")
#endif
void func_150D71A8(f32 *arg0, f32 *arg1) {
    arg1[0] = arg0[5];
    arg1[1] = arg0[6] + 60.0f;
    arg1[2] = arg0[7];
}

#ifdef NON_MATCHING
void func_15131EC8(f32 *, f32);

/* P67: update of a debris piece that follows its owner (obj +0xA8 = owner record, +0xAC = the owner's unique_id when
 * spawned). Returns 0 when the owner is gone or reused; else follows it (func_150D71A8 into obj +0x40), adds gravity
 * (obj +0x64) to the velocity (obj +0x58), lets func_15131EC8 adjust it and moves obj +0x4C by the average of the
 * old and new velocity over the frame (D_800BE9A4; D_800BEDC8 scales the change). Returns 1. */
s32 func_150D71D4(u8 *arg0, s32 arg1) {
    struct127 *owner = *(struct127 **)(arg0 + 0xA8);
    f32 *pos = (f32 *)(arg0 + 0x4C);
    f32 *vel = (f32 *)(arg0 + 0x58);
    f32 old[3];

    if (owner->interaction_state == 0 || arg0[0xAC] != owner->unique_id) {
        return 0;
    }
    func_150D71A8((f32 *)owner, (f32 *)(arg0 + 0x40));
    old[0] = vel[0];
    old[1] = vel[1];
    old[2] = vel[2];
    vel[1] += *(f32 *)(arg0 + 0x64) * D_800BE9A4;
    func_15131EC8(vel, *(f32 *)(arg0 + 0xB0));
    pos[0] += old[0] * D_800BE9A4 + (vel[0] - old[0]) * D_800BEDC8 * D_800BE9A4 * D_800BE9A4 * 0.5f;
    pos[1] += old[1] * D_800BE9A4 + (vel[1] - old[1]) * D_800BEDC8 * D_800BE9A4 * D_800BE9A4 * 0.5f;
    pos[2] += old[2] * D_800BE9A4 + (vel[2] - old[2]) * D_800BEDC8 * D_800BE9A4 * D_800BE9A4 * 0.5f;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D71D4.s")
#endif
void func_150D7370(struct102 *arg0, u8 *arg1, u8 arg2) {
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
        if (arg2 == 0) {
            s32 t = *(s32 *)arg1;
            if (t == *(s32 *)v || v[4] == arg1[4]) {
                func_1516972C(arg0);
            }
        }
    }
}

#ifdef NON_MATCHING
s32 func_150D741C(u8 *arg0, s32 arg1) {
    u8 *sp18;
    f32 *temp_a3;
    f32 temp_f12;
    f32 temp_f2;
    s32 var_v0;
    u8 *temp_v0;

    temp_a3 = (*(f32 **)((u8 *)arg0 + 0xA8));
    temp_v0 = arg0 + 0xA8;
    if (((*(s32 *)((u8 *)temp_a3 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_a3 + 0x3B)))) {
        return 0;
    }
    sp18 = temp_v0;
    func_150D71A8(temp_a3, arg0 + 0x40);
    temp_f2 = sqrtf((*(f32 *)((u8 *)temp_v0 + 8))) * (*(f32 *)((u8 *)temp_v0 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = temp_f2;
    (*(f32 *)((u8 *)arg0 + 0x38)) = temp_f2;
    temp_f12 = (*(f32 *)((u8 *)temp_v0 + 8));
    (*(s8 *)((u8 *)arg0 + 0x2B)) = (s8) (u32) ((*(f32 *)((u8 *)temp_v0 + 0x14)) - ((*(f32 *)((u8 *)temp_v0 + 0x18)) * temp_f12 * temp_f12));
    (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 8)) + D_800BE9A4);
    var_v0 = 1;
    if ((*(f32 *)((u8 *)temp_v0 + 0xC)) < (*(f32 *)((u8 *)temp_v0 + 8))) {
        var_v0 = 0;
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D741C.s")
#endif
void func_150D7578(struct102 *arg0, u8 *arg1, u8 arg2) {
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
        if (arg2 == 0) {
            s32 t = *(s32 *)arg1;
            if (t == *(s32 *)v || v[4] == arg1[4]) {
                func_1516972C(arg0);
            }
        }
    }
}
