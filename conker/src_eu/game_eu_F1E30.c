#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* damage_smoke_spawn records (stack images; pad bytes stay unset like the asm's) */
typedef struct {
    u8 *obj;        /* 0x00 */
    u8 room;        /* 0x04 obj +0x3B */
    u8 pad5[3];
    f32 u8;         /* 0x08 */
    void *glow;     /* 0x0C particle_spawn_ex result */
    f32 u10;        /* 0x10 */
    s16 u14;        /* 0x14 -1, 0x54 for a type 0x34 owner */
    u8 u16;         /* 0x16 */
    u8 pad17;
    s32 u18;        /* 0x18 */
} Link4620;         /* 0x1C, copied to the new object +0x28 */

typedef struct {
    u8 u0;          /* 0x00 */
    u8 u1;          /* 0x01 */
    u8 u2;          /* 0x02 5..10 */
    u8 u3;          /* 0x03 5..10 */
    f32 radius;     /* 0x04 700 */
    f32 u8;         /* 0x08 */
    f32 uC;         /* 0x0C */
} Tail4620;         /* 0x10, copied to the glow +0xA8 */

typedef struct {
    s32 u0;         /* 0x00 0x200005 */
    s32 u4;         /* 0x04 */
    s16 u8;         /* 0x08 0x2203 */
    s16 uA;         /* 0x0A 0x12C */
    s32 uC;         /* 0x0C */
    s32 u10;        /* 0x10 */
    u8 rgba[4];     /* 0x14 */
    u8 rgba2[4];    /* 0x18 */
    u8 u1C;         /* 0x1C */
    u8 colour;      /* 0x1D D_800A0710[rand & 3] */
    s16 u1E;        /* 0x1E */
    s16 u20;        /* 0x20 */
    s16 u22;        /* 0x22 */
    f32 u24;        /* 0x24 */
    f32 u28;        /* 0x28 */
    f32 u2C;        /* 0x2C */
    f32 pos[3];     /* 0x30 D_800A5860 */
    f32 pos2[3];    /* 0x3C */
    f32 pos3[3];    /* 0x48 */
    f32 u54;        /* 0x54 */
    s32 flags;      /* 0x58 */
    s32 u5C;        /* 0x5C */
    u8 u60;         /* 0x60 */
    u8 u61;         /* 0x61 */
    u8 u62;         /* 0x62 */
    s8 u63;         /* 0x63 */
    s8 u64;         /* 0x64 */
    u8 u65;         /* 0x65 */
    u8 u66;         /* 0x66 */
    u8 pad67;
    s16 u68;        /* 0x68 */
    u8 pad6A[2];
    f32 u6C;        /* 0x6C D_800A0784 */
} Glow4620;         /* particle_spawn_ex request */

typedef struct {
    f32 v[3];
} Vec4620;

extern u32 D_800A0710[4];
s32 memcpy(void *, void *, s32);
s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);

// object_glow_spawn: spawns a type `kind` object (0x12C when kind is -1; effect_node_create) linked to obj (record at +0x28:
// obj, room, the glow at +0xC; field +0x14 = 0x54 / +0x16 = 1 for a type 0x34 owner, else -1 / 0), then a glow
// (particle_spawn_ex type 1, radius 700, a random colour of D_800A0710, random flag bits 0x40 / 0x80) whose +0xA8 tail
// gets two random bytes, two counts 5..10 and two scales (0.2 + [0, 0.25)) * 700.
/* was func_150C4620 */
void damage_smoke_spawn(u8 *obj, s16 kind, u8 flag, s32 arg3) {
    Link4620 link;
    Tail4620 tail;
    Glow4620 g;
    u8 *rec;
    Link4620 *l;
    u8 *e;
    s32 lo;
    s32 hi;

    link.obj = obj;
    link.u8 = 0.0f;
    link.glow = NULL;
    link.u10 = 0.0f;
    link.u14 = -1;
    link.u16 = 0;
    link.u18 = 0;
    link.room = obj[0x3B];
    if (obj[4] == 0x34) {
        link.u14 = 0x54;
        link.u16 = 1;
    }
    rec = (u8 *) effect_node_create(kind == -1 ? 0x12C : kind, -1, 0x53, -1, kind != -1, 0x40, (struct37 *) 0x1C, flag, arg3);
    if (rec == NULL) {
        return;
    }
    l = (Link4620 *) (rec + 0x28);
    memcpy(l, &link, 0x1C);
    tail.u0 = random_int();
    tail.u1 = random_int();
    g.u2C = 700.0f;
    g.u28 = 700.0f;
    tail.radius = 700.0f;
    tail.u2 = (u32) random_int() % 6 + 5;
    tail.u3 = (u32) random_int() % 6 + 5;
    tail.u8 = (random_float() * 0.25f + 0.2f) * tail.radius;   /* D_800A077C */
    tail.uC = (random_float() * 0.25f + 0.2f) * tail.radius;   /* D_800A0780 */
    g.colour = D_800A0710[random_int() & 3];
    g.u8 = 0x2203;
    g.u0 = 0x200005;
    g.u4 = 0;
    g.uC = 0;
    g.u10 = 0;
    g.rgba[0] = 0;
    g.rgba[1] = 0;
    g.rgba[2] = 0;
    g.rgba[3] = 0xFF;
    g.rgba2[0] = 0;
    g.rgba2[1] = 0;
    g.rgba2[2] = 0;
    g.rgba2[3] = 0xFF;
    g.u1C = 0xFF;
    *(Vec4620 *) g.pos = *(Vec4620 *) D_800A5860;
    *(Vec4620 *) g.pos2 = *(Vec4620 *) D_800A5860;
    *(Vec4620 *) g.pos3 = *(Vec4620 *) D_800A5860;
    g.u22 = 1;
    g.u54 = 0.0f;
    g.u24 = 1.0f;
    lo = (random_int() & 1) ? 0x40 : 0;
    hi = (random_int() & 1) ? 0x80 : 0;
    g.flags = hi | lo | 0xC000;
    g.uA = 0x12C;
    g.u6C = 10000.0f;   /* D_800A0784 */
    g.u1E = 1;
    g.u20 = 0xFF;
    g.u60 = 6;
    g.u61 = 8;
    g.u64 = -1;
    g.u62 = 0x26;
    g.u63 = -1;
    g.u65 = 0;
    g.u5C = 0;
    g.u66 = 0xFF;
    g.u68 = 0;
    e = (u8 *) particle_spawn_ex((s32) &g, 1, 0, 0x10, flag, arg3);
    l->glow = e;
    if (e != NULL) {
        memcpy(e + 0xA8, &tail, 0x10);
    }
}

void hitinfo_from_obj_floor(f32 *, u8 *);
u8 *attachment_find_by_slot(u8 *arg0, s32 arg1, s32 arg2);
s32 model_node_points_to_world(u8 *, u8 *, s32, f32 **, f32 **, s32);
void fire_embers_spawn_b(u8 *arg0, u8 arg1, s32 arg2);
s32 motion_track_get_delta(u8 *, f32 **);
void vec3_from_angles_byte(s16, s16, f32, f32 *);

extern f32 D_800A0720[3][3];    /* offsets by health third */
extern u8 D_800A0744[3];        /* bone index by health third */
extern f32 D_800A0748[4][3];    /* offsets by quarter */
extern u8 D_800A0778[4];        /* attachment point by quarter */

/* rodata copies (NM link drops the asm rodata) */
static const f32 D_800A0788_c[1] = { 0.33333334f };  /* 0x3EAAAAAB */
static const f32 D_800A078C_c[1] = { 0.12900001f };  /* 0x3E041894 */
static const f32 D_800A0790_c[1] = { 0.117000006f }; /* 0x3DEF9DB3 */
static const f32 D_800A0794_c[1] = { 0.13000001f };  /* 0x3E051EB9 */
static const f32 D_800A0798_c[1] = { 0.2f };         /* 0x3E4CCCCD */
static const f32 D_800A079C_c[1] = { 0.6f };         /* 0x3F19999A */
static const f32 D_800A07A0_c[1] = { 2.5970001f };   /* 0x40263540 */
static const f32 D_800A07A4_c[1] = { 4.8700004f };   /* 0x409BD70B */
static const f32 D_800A07A8_c[1] = { 0.25800002f };  /* 0x3E841894 */
static const f32 D_800A07AC_c[1] = { -0.60800004f }; /* 0xBF1BA5E4 */
static const f32 D_800A07B0_c[1] = { 0.70000005f };  /* 0x3F333334 */

/* +0x28 record of the effect object (written by damage_smoke_spawn) */
typedef struct {
    u8 *obj;        /* 0x00 owner */
    u8 room;        /* 0x04 owner +0x3B at spawn */
    u8 pad5[3];
    f32 smoke;      /* 0x08 smoke puff accumulator */
    u8 *glow;       /* 0x0C */
    f32 sparks;     /* 0x10 spark accumulator */
    s16 point;      /* 0x14 attachment point id */
    u8 mode;        /* 0x16 bit 0: attachment-point mode, bit 1: off */
    u8 pad17;
    s32 sound;      /* 0x18 */
} Smoke49A4;

typedef struct {
    f32 v[3];
} Vec49A4;

// damage_smoke_update: handler 21 of D_8008A980 (`void (u8 *)`). Ends the effect (+0xE = -1) when the owner is gone
// or changed room; with the owner switched off (+0x1D4 == 0 or mode bit 1) it only sets the glow's +0x74 to 3.
// Otherwise starts the 0x96 loop sound once, places the emitter on the owner (mode bit 0: attachment point
// attachment_find_by_slot / model_node_points_to_world by the +0x2DC * +0x2D8 quarter, fallback owner + (0, 800, 0); else bone
// D_800A0744[third] of +0x1D4 by the +0x2E4 / +0x2E8 third), moves the glow there, then emits smoke puffs
// (fire_embers_spawn_b, (0.129 + 0.117 * random) * D_800BE9A4 per frame, skipped in mode 2 when trigger_test_player says no) and
// sparks (impact_dust_cloud_spawn, (0.13 + 0.2 * random) * D_800BE9A4 per frame, blown against the owner's motion_track_get_delta vector).
/* was func_150C49A4 */
void damage_smoke_update(u8 *self) {
    f32 basis[12];
    f32 off[3];
    f32 pos[3];
    f32 vel[3];
    f32 *offp;
    f32 *posp;
    f32 *up;
    Smoke49A4 *rec;
    u8 *obj;
    u8 *glow;
    s32 i;
    s32 enabled;
    f32 t;
    f32 f;
    f32 a;
    f32 b;
    f32 c;
    s32 r1;
    s32 r2;

    rec = (Smoke49A4 *) (self + 0x28);
    obj = rec->obj;
    if (*(s32 *) obj == 0 || rec->room != obj[0x3B]) {
        *(s16 *) (self + 0xE) = -1;
        return;
    }
    if (*(s32 *) (obj + 0x1D4) == 0 || (rec->mode & 2)) {
        if (rec->glow != NULL) {
            rec->glow[0x74] = 3;
        }
        return;
    }
    hitinfo_from_obj_floor(basis, obj);
    if (rec->sound == 0) {
        rec->sound = actor_sound_play(0x96, (struct127 *) obj, 0x36B0, 0x190, 0x4268);
    }
    if (rec->mode & 1) {
        u8 *pt = attachment_find_by_slot(obj, rec->point, 0);

        if (pt == NULL) {
            return;
        }
        t = (*(s32 *) (obj + 0x2EC) != 0) ? *(f32 *) (obj + 0x2DC) * *(f32 *) (obj + 0x2D8) : 0.0f;
        i = (s32) (t * 4.0f);
        if (i >= 4) {
            i = 3;
        }
        f = (t - (f32) i * 0.25f) * 4.0f;
        off[0] = D_800A0748[i][0] * f;
        off[1] = D_800A0748[i][1] * f;
        off[2] = D_800A0748[i][2] * f;
        offp = off;
        posp = pos;
        if (model_node_points_to_world(obj, pt, D_800A0778[i], &offp, &posp, 1) == 0) {
            pos[0] = *(f32 *) (obj + 0x14);
            pos[1] = *(f32 *) (obj + 0x18) + 800.0f;
            pos[2] = *(f32 *) (obj + 0x1C);
        }
    } else {
        t = (*(s32 *) (obj + 0x2E8) != 0) ? (f32) *(s32 *) (obj + 0x2E4) / (f32) *(s32 *) (obj + 0x2E8) : 1.0f;
        i = (s32) (t * 3.0f);
        if (i >= 3) {
            i = 2;
        }
        f = (t - (f32) i * D_800A0788_c[0]) * 3.0f;
        off[0] = D_800A0720[i][0] * f;
        off[1] = D_800A0720[i][1] * f;
        off[2] = D_800A0720[i][2] * f;
        mtx_transform_point_or_origin(off, pos, *(u8 **) (obj + 0x1D4) + (D_800A0744[i] << 6));
    }
    glow = rec->glow;
    if (glow != NULL) {
        glow[0x74] = 0xFF;
        *(Vec49A4 *) (rec->glow + 0x40) = *(Vec49A4 *) pos;
    }

    enabled = TRUE;
    if (g_level_id == 2 && trigger_test_player(((u8 *) obj - (u8 *) g_objects) / 0x32C, 0x4065) == 0) {
        enabled = FALSE;
    }
    if (enabled) {
        rec->smoke += (D_800A078C_c[0] + random_float() * D_800A0790_c[0]) * D_800BE9A4;
        while (1.0f < rec->smoke) {
            fire_embers_spawn_b((u8 *) pos, self[0xC], self[1]);
            rec->smoke -= 1.0f;
        }
    }

    rec->sparks += (D_800A0794_c[0] + random_float() * D_800A0798_c[0]) * D_800BE9A4;
    if (!(1.0f < rec->sparks)) {
        return;
    }
    if (motion_track_get_delta(obj, &up) == 0) {
        up = (f32 *) D_800A5860;
    }
    do {
        r1 = random_int();
        r2 = random_int();
        f = random_float();
        vec3_from_angles_byte((s16) (r1 & 0xFF), (s16) ((u32) r2 % 25 - 0x40), f * D_800A07A0_c[0] + D_800A07A4_c[0], vel);
        vel[0] -= up[0] * D_800A079C_c[0];
        vel[2] -= up[2] * D_800A079C_c[0];
        a = random_float();
        r1 = random_int();
        r2 = random_int();
        b = random_float();
        c = random_float();
        impact_dust_cloud_spawn(pos, vel, 0xC, a * D_800A07A8_c[0] + D_800A07AC_c[0], (u32) r1 % 41 + 0x3C, (u32) r2 % 56 + 0xC8,
                      b * 160.0f + 121.0f, c < D_800A07B0_c[0], 1.0f, 1.0f, 0, (s32) basis, 1, 1,
                      self[0xC], self[1]);
        rec->sparks -= 1.0f;
    } while (1.0f < rec->sparks);
}

/* was func_150C4FD8 */
void damage_smoke_destroy_glow(u8 *arg0) { u8 *p = arg0; if (*(s32 *)(p + 0x34) != 0) { node_destroy(*(struct102 **)(p + 0x34)); } }

/* was func_150C5008 */
void damage_smoke_retire(struct260 *arg0) {
    damage_smoke_destroy_glow(arg0);
    effect_node_retire(arg0);
}

/* was func_150C5034 */
void damage_smoke_free(struct260 *arg0) {
    damage_smoke_destroy_glow(arg0);
    effect_node_free(arg0);
}

/* was func_150C5060 */
void damage_smoke_on_message(u8 *arg0, s32 arg1, u8 arg2) {
    u8 **q = &arg0; // fakematch: address-taken arg0 forces the home-slot reload (shape C)
    u8 *p;
    if (arg2 == 0x55) {
        p = *q + 0x28; p[0x16] = p[0x16] & 0xFFFD;
    } else if (arg2 == 0x56) {
        p = *q + 0x28; p[0x16] = p[0x16] | 2;
    } else {
        p = *q + 0x28;
        effect_node_link_message(arg1, arg2, (s32)p, (s32)(p + 4), (s32)*q);
    }
}
