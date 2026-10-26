#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A4EA8[];

typedef struct {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ s32 unk38[1];
} struct_eu_1DFE20_c;

typedef struct {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ struct_eu_1DFE20_c *unk178;
    /* 0x17C */ u8 unk17C;
} struct_eu_1DFE20_d;

typedef struct {
    /* 0x00 */ u8 pad0[0x44];
    /* 0x44 */ s32 unk44;
} struct_eu_1DFE20_b;

typedef struct {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ struct_eu_1DFE20_b *unk4C;
} struct_eu_1DFE20;


/* was func_151B2610 */
void cord_rig_spawn(u8 *arg0) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        struct127 *unk8;
        u8 unkC;
        u8 unkD;
        f32 unk10[3];
        s32 unk1C;
    } tmp;

    if (arg0 != NULL) {
        tmp.unk0 = arg0;
        tmp.unk4 = arg0[0x3B];
        tmp.unk8 = obj_find_by_setup_id(1);
        tmp.unkC = 1;
        tmp.unkD = 0;
        bzero(tmp.unk10, 0xC);
        tmp.unk1C = 0;
        temp_v0 = effect_node_create_nodraw(300, -1, 0x16, 0, 0x12, 0x20, 0xFF, 1);
        if (temp_v0 != NULL) {
            memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x20);
        }
    }
}

typedef struct {
    u8 *a;
    u8 a4;
    u8 pad5[3];
    u8 *c;
    u8 cC;
    u8 d;
} Link26B0;
s32 cord_rig_get_state(u8 *arg0);
void cord_rig_free_ropes(u8 *);
void cord_rig_spawn_three_ropes(u8 *);
void cord_rig_spawn_twin_ropes(u8 *);

/* was func_151B26B0 */
void cord_rig_update(u8 *arg0) {
    Link26B0 *s;
    u8 *a;
    u8 *c;
    u8 old;

    a = *(u8 **)(arg0 + 0x28);
    c = *(u8 **)(arg0 + 0x30);
    s = (Link26B0 *)(arg0 + 0x28);
    if (*(s32 *)a == 0 || a[4] == 0xFF || s->a4 != a[0x3B] || *(s32 *)c == 0 || c[4] == 0xFF || s->cC != c[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    old = s->d;
    s->d = cord_rig_get_state(arg0);
    if (s->d != old) {
        cord_rig_free_ropes(arg0);
        if (s->d == 1) {
            cord_rig_spawn_three_ropes(arg0);
        }
        if (s->d == 2 || s->d == 0) {
            cord_rig_spawn_twin_ropes(arg0);
        }
    }
}

void cord_rig_free_ropes(u8 *);

/* was func_151B27BC */
void cord_rig_free_ropes_wrap(s32 arg0) {
    cord_rig_free_ropes(arg0);
}

/* was func_151B27DC */
void cord_rig_free_ropes(u8 *arg0) {
    u8 *base = arg0 + 0x28;
    u8 i;

    for (i = 0; i < 3; i++) {
        struct102 *p = ((struct102 **)(base + 0x10))[i];

        if (p != NULL) {
            node_destroy(p);
        }
    }
    if (*(struct102 **)(base + 0x1C) != NULL) {
        node_destroy(*(struct102 **)(base + 0x1C));
    }
}

/* was func_151B284C */
void cord_rig_retire(void *arg0) {
    cord_rig_free_ropes_wrap(arg0);
    effect_node_retire(arg0);
}

/* was func_151B2878 */
void cord_rig_delete(void *arg0) {
    cord_rig_free_ropes_wrap(arg0);
    effect_node_free(arg0);
}

/* was func_151B28A4 */
s32 cord_rig_get_state(u8 *arg0) {
    struct127 *temp_v0 = *(struct127 **)(arg0 + 0x28);
    s32 ret = 2;
    u8 *temp_v1 = *(u8 **)(arg0 + 0x30);

    if (((temp_v0 - D_800CC2D0) + 1 == temp_v1[0x65]) && (*(s32 *)(temp_v1 + 0x5C) == 1)) {
        return 1;
    }
    return ret;
}

extern s32 D_800AA700;
extern s32 D_800AA70C;
extern s32 D_800AA718;
extern s32 D_800AA724;
extern s32 D_800AA730;

u8 *cord_spawn(void *, f32, s32, u8, s32); /* P95 */
/* was func_151B28F8 */
void cord_rig_spawn_three_ropes(u8 *arg0) {
    struct {
        u8 * u34;
        u8 u38;
        s8 u39;
        u8 pad3A[0x2];
        s32 u3C;
        u8 pad40[0x8];
        u8 * u48;
        u8 u4C;
        s8 u4D;
        u8 pad4E[0x2];
        s32 u50;
        u8 pad54[0x8];
        u8 * u5C;
        s8 u60;
        u8 pad61[0x3];
        s8 u64;
        u8 pad65[0x1];
        s16 u66;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        s8 u80;
        s8 u81;
        s8 u82;
        u8 pad83[0x1];
        f32 u84;
        s8 u88;
        u8 pad89[0x3];
        f32 u8C;
        f32 u90;
        f32 u94;
        s8 u98;
    } sp;
    s32 *temp_t8;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_s0 = (*(u8 **)((u8 *)arg0 + 0x30));
    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x28));
    sp.u60 = 2;
    sp.u5C = arg0;
    sp.u34 = temp_s0;
    sp.u39 = 5;
    sp.u38 = (*(u8 *)((u8 *)temp_s0 + 0x3B));
    (*(s32 *)((u8 *)(&sp.u3C) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800AA730) + 0));
    (*(s32 *)((u8 *)(&sp.u3C) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800AA730) + 4));
    (*(s32 *)((u8 *)(&sp.u3C) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800AA730) + 8));
    sp.u48 = temp_s0;
    temp_t8 = "A@";
    sp.u4D = 0xA;
    sp.u4C = (*(u8 *)((u8 *)temp_s0 + 0x3B));
    (*(s32 *)((u8 *)(&sp.u50) + 0)) = (s32) (*(s32 *)((u8 *)temp_t8 + 0));
    (*(s32 *)((u8 *)(&sp.u50) + 4)) = (s32) (*(s32 *)((u8 *)temp_t8 + 4));
    (*(s32 *)((u8 *)(&sp.u50) + 8)) = (s32) (*(s32 *)((u8 *)temp_t8 + 8));
    sp.u98 = 0;
    sp.u64 = 0;
    sp.u66 = 0x3E8;
    sp.u68 = (*(f32 *)((u8 *)temp_s0 + 0x14));
    sp.u6C = (*(f32 *)((u8 *)temp_s0 + 0x18));
    sp.u70 = (*(f32 *)((u8 *)temp_s0 + 0x1C));
    sp.u74 = (*(f32 *)((u8 *)temp_s0 + 0x14));
    sp.u78 = (*(f32 *)((u8 *)temp_s0 + 0x18));
    sp.u80 = 1;
    sp.u81 = 1;
    sp.u82 = 0;
    sp.u88 = 3;
    sp.u84 = 5.0f;
    sp.u8C = 80.0f;
    sp.u90 = -0.02f;
    sp.u94 = 0.70000005f;
    sp.u7C = (*(f32 *)((u8 *)temp_s0 + 0x1C));
    temp_v0 = cord_spawn(&sp.u64, 0.0015f, 0x30, 0xFF, 0); /* P95: was 0x3AC49BA6 as an int */
    (*(s32 *)((u8 *)(&arg0[0x28]) + 0x18)) = temp_v0;
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x150, &sp.u34, 0x30);
    }
    sp.u60 = 1;
    sp.u34 = temp_s1;
    sp.u39 = 5;
    sp.u38 = (*(u8 *)((u8 *)temp_s1 + 0x3B));
    (*(s32 *)((u8 *)(&sp.u3C) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800AA700) + 0));
    (*(s32 *)((u8 *)(&sp.u3C) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800AA700) + 4));
    (*(s32 *)((u8 *)(&sp.u3C) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800AA700) + 8));
    sp.u48 = temp_s0;
    sp.u4D = 5;
    sp.u4C = (*(u8 *)((u8 *)temp_s0 + 0x3B));
    (*(s32 *)((u8 *)(&sp.u50) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800AA718) + 0));
    (*(s32 *)((u8 *)(&sp.u50) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800AA718) + 4));
    (*(s32 *)((u8 *)(&sp.u50) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800AA718) + 8));
    sp.u68 = (*(f32 *)((u8 *)temp_s1 + 0x14));
    sp.u6C = (*(f32 *)((u8 *)temp_s1 + 0x18));
    sp.u70 = (*(f32 *)((u8 *)temp_s1 + 0x1C));
    sp.u74 = (*(f32 *)((u8 *)temp_s0 + 0x14));
    sp.u78 = (*(f32 *)((u8 *)temp_s0 + 0x18));
    sp.u82 = 0;
    sp.u8C = 170.0f;
    sp.u7C = (*(f32 *)((u8 *)temp_s0 + 0x1C));
    temp_v0_2 = cord_spawn(&sp.u64, 0.0015f, 0x30, 0xFF, 0); /* P95: was 0x3AC49BA6 as an int */
    (*(s32 *)((u8 *)(&arg0[0x28]) + 0x14)) = temp_v0_2;
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0x150, &sp.u34, 0x30);
    }
    sp.u60 = 0;
    sp.u34 = temp_s1;
    sp.u39 = 5;
    sp.u38 = (*(u8 *)((u8 *)temp_s1 + 0x3B));
    (*(s32 *)((u8 *)(&sp.u3C) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800AA70C) + 0));
    (*(s32 *)((u8 *)(&sp.u3C) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800AA70C) + 4));
    (*(s32 *)((u8 *)(&sp.u3C) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800AA70C) + 8));
    sp.u48 = temp_s0;
    sp.u4D = 0xA;
    sp.u4C = (*(u8 *)((u8 *)temp_s0 + 0x3B));
    (*(s32 *)((u8 *)(&sp.u50) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800AA724) + 0));
    (*(s32 *)((u8 *)(&sp.u50) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800AA724) + 4));
    (*(s32 *)((u8 *)(&sp.u50) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800AA724) + 8));
    sp.u68 = (*(f32 *)((u8 *)temp_s1 + 0x14));
    sp.u6C = (*(f32 *)((u8 *)temp_s1 + 0x18));
    sp.u70 = (*(f32 *)((u8 *)temp_s1 + 0x1C));
    sp.u74 = (*(f32 *)((u8 *)temp_s0 + 0x14));
    sp.u78 = (*(f32 *)((u8 *)temp_s0 + 0x18));
    sp.u82 = 0;
    sp.u7C = (*(f32 *)((u8 *)temp_s0 + 0x1C));
    temp_v0_3 = cord_spawn(&sp.u64, 0.0015f, 0x30, 0xFF, 0); /* P95: was 0x3AC49BA6 as an int */
    (*(s32 *)((u8 *)(&arg0[0x28]) + 0x10)) = temp_v0_3;
    if (temp_v0_3 != 0) {
        memcpy(temp_v0_3 + 0x150, &sp.u34, 0x30);
    }
}
/* a light attachment: owner, its room byte, a mode and an offset from the owner */
typedef struct {
    u8 *owner;
    u8 room;
    u8 mode;
    u8 pad6[2];
    f32 offset[3];
} Attach2C40;

/* the 0x30-byte record copied to each cord_spawn light (+0x150) */
typedef struct {
    Attach2C40 a;   /* 0x00 */
    Attach2C40 b;   /* 0x14 */
    u8 *obj;        /* 0x28 */
    u8 first;       /* 0x2C */
    u8 pad2D[3];
} Light2C40;

/* the 0x28-byte record copied to the effect_node_create object (+0x28) */
typedef struct {
    u8 *owner;      /* 0x00 */
    u8 room;        /* 0x04 */
    u8 mode;        /* 0x05 */
    u8 pad6[2];
    f32 left[3];    /* 0x08 */
    f32 right[3];   /* 0x14 */
    f32 u20;        /* 0x20 */
    u8 *obj;        /* 0x24 */
} Beam2C40;

/* cord_spawn's light template */
typedef struct {
    u8 u0;          /* 0x00 */
    s16 u2;         /* 0x02 */
    f32 pos[3];     /* 0x04 */
    f32 pos2[3];    /* 0x10 */
    u8 u1C[3];      /* 0x1C */
    f32 u20;        /* 0x20 */
    u8 u24;         /* 0x24 */
    f32 u28;        /* 0x28 */
    f32 u2C;        /* 0x2C */
    f32 u30;        /* 0x30 */
    u8 u34;         /* 0x34 */
} LightTmpl2C40;

typedef struct {
    f32 v[3];
} Vec3f2C40;
/* D_800AA700 (77, 20, 67) / D_800AA70C (-77, 20, 67): declared s32 above */
extern f32 D_800AA748[3]; /* (27, 42, 0) */
extern f32 D_800AA754[3]; /* (-27, 42, 0) */

// twin_lights_spawn: obj +0x28 holds the owner. Spawns two lights (cord_spawn: template at the owner position,
// rate 0.0015) whose records attach them to the owner at (+-77, 20, 67) (mode 5) and (+-27, 42, 0) (mode 2), the
// first one flagged; stores them at obj +0x3C / +0x38. Then a type 0x13 object (effect_node_create) for the beam between
// (27, 42, 0) and (-27, 42, 0), stored at obj +0x44.
/* was func_151B2C40 */
void cord_rig_spawn_twin_ropes(u8 *obj) {
    Beam2C40 beam;
    Light2C40 rec;
    LightTmpl2C40 t;
    u8 *owner = *(u8 **) (obj + 0x28);
    u8 *o;
    struct260 *b;

    rec.obj = obj;
    rec.first = 1;
    rec.a.owner = owner;
    rec.a.mode = 5;
    rec.a.room = owner[0x3B];
    *(Vec3f2C40 *) rec.a.offset = *(Vec3f2C40 *) &D_800AA700;
    rec.b.owner = owner;
    rec.b.mode = 2;
    rec.b.room = owner[0x3B];
    *(Vec3f2C40 *) rec.b.offset = *(Vec3f2C40 *) D_800AA748;
    t.u34 = 0;
    t.u0 = 0;
    t.u2 = 100;
    t.pos[0] = *(f32 *) (owner + 0x14);
    t.pos[1] = *(f32 *) (owner + 0x18);
    t.pos[2] = *(f32 *) (owner + 0x1C);
    t.pos2[0] = *(f32 *) (owner + 0x14);
    t.pos2[1] = *(f32 *) (owner + 0x18);
    t.pos2[2] = *(f32 *) (owner + 0x1C);
    t.u1C[0] = 1;
    t.u1C[1] = 1;
    t.u1C[2] = 1;
    t.u24 = 3;
    t.u20 = 5.0f;
    t.u28 = 180.0f;
    t.u2C = -0.01185f;  /* D_800AA768 */
    t.u30 = 0.713000059f; /* D_800AA76C */
    o = cord_spawn(&t, 0.0015f, 0x30, 0xFF, 0);
    *(u8 **) (obj + 0x3C) = o;
    if (o != NULL) {
        memcpy(o + 0x150, &rec, 0x30);
    }
    rec.first = 0;
    *(Vec3f2C40 *) rec.a.offset = *(Vec3f2C40 *) &D_800AA70C;
    *(Vec3f2C40 *) rec.b.offset = *(Vec3f2C40 *) D_800AA754;
    t.u1C[2] = 1;
    o = cord_spawn(&t, 0.0015f, 0x30, 0xFF, 0);
    *(u8 **) (obj + 0x38) = o;
    if (o != NULL) {
        memcpy(o + 0x150, &rec, 0x30);
    }
    beam.owner = owner;
    beam.room = owner[0x3B];
    beam.mode = 2;
    *(Vec3f2C40 *) beam.left = *(Vec3f2C40 *) D_800AA748;
    *(Vec3f2C40 *) beam.right = *(Vec3f2C40 *) D_800AA754;
    beam.u20 = 5.0f;
    beam.obj = obj;
    b = effect_node_create(0x12C, -1, -1, 0, 0, 0x13, (struct37 *) 0x28, 0xFF, 1);
    *(struct260 **) (obj + 0x44) = b;
    if (b != NULL) {
        memcpy((u8 *) b + 0x28, &beam, 0x28);
    }
}

/* was func_151B2F00 */
void cord_rig_rope_unlink(struct_eu_1DFE20_d *arg0) {
    struct_eu_1DFE20_c *temp_v0 = arg0->unk178;

    if (temp_v0 != NULL) {
        temp_v0->unk38[arg0->unk17C] = 0;
    }
}

s32 gfx_set_combine_mode(s32, s32, s8 *);
s32 gfx_geometry_mode_cached(u8 *, s32, s32);
s32 gfx_env_color_cached(s32, s32, s32, s32, s32, s8 *);
s32 gfx_prim_color_cached(s32, s32, s32, s32, s32, s32, s32, s8 *);
s32 gfx_load_texture_cached(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
u8 *gfx_other_mode_cached(s32, s32, s32, s8 *);
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
extern s32 D_80091198;
extern s32 D_800D30BC;

/* was func_151B2F24 */
u8 *cord_plank_draw(u8 *arg0, u8 *arg1, s16 arg2) {
    struct {
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        u8 pad90[0x18];
        f32 * uA8;
        s16 * uAC;
        u8 padB0[0x2];
        s8 uB2;
        u8 uB3;
    } sp;
    u8 *sp64;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    s32 *temp_v1;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f6;
    f32 temp_f8;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    s16 *temp_t3;
    s16 *temp_t3_2;
    s16 *temp_t3_3;
    u8 *temp_a2;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s1;
    u8 *temp_s1_2;
    u8 *temp_v0;
    u8 *var_s0;

    var_s0 = arg0;
    sp.uB3 = 0;
    temp_s1 = arg1 + 0x28;
    if ((*(*(s32 **)((u8 *)arg1 + 0x28)) == 0) || ((*(u8 *)((u8 *)temp_s1 + 4)) != (*(u8 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0))) + 0x3B)))) {
        sp.uB3 = 1;
    }
    temp_s1_2 = arg1 + 0x28;
    if ((sp.uB3 == 0) && ((*(s32 *)((u8 *)((*(u8 **)((u8 *)temp_s1_2 + 0))) + 0x1D4)) != 0)) {
        vtx_slot_buffer_get(arg1 + 0x14, arg2, 0x40, &sp.uAC, 0);
        if (sp.uAC == NULL) {
            return var_s0;
        }
        temp_a2 = (*(s32 *)((u8 *)((*(u8 **)((u8 *)temp_s1_2 + 0))) + 0x1D4)) + ((*(u8 *)((u8 *)temp_s1_2 + 5)) << 6);
        sp64 = temp_a2;
        mtx_transform_point_or_origin(temp_s1_2 + 8, &sp.u80, temp_a2);
        mtx_transform_point_or_origin(temp_s1_2 + 0x14, &sp.u74, sp64);
        sp.uB2 = 1;
        sp.uA8 = &D_800DBFF0[arg2].unk2F8;
        temp_v1 = ((u8 *)&D_800A4EA8);
        temp_v0 = gfx_other_mode_cached(gfx_set_combine_mode(gfx_prim_color_cached(gfx_env_color_cached(gfx_load_texture_cached(gfx_geometry_mode_cached(var_s0, 0x200005, 0x60600), &D_80091198, 0, 0, 0, 0, 0x36, 0, 0, &sp.uB2, 3), 0xFF, 0xFF, 0xFF, 0xFF, &sp.uB2), 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, &sp.uB2), 0x2B, &sp.uB2), D_800D30BC | 0x80000 | 0x2CA0, (*(s32 *)((u8 *)temp_v1 + 0x2C)) | (*(s32 *)((u8 *)temp_v1 + 0x28)), &sp.uB2);
        temp_f0 = sp.u74 - sp.u80;
        temp_f14 = ((temp_f0 * 0.5f) + sp.u80) - (*(f32 *)((u8 *)sp.uA8 + 0));
        temp_f2 = sp.u78 - sp.u84;
        temp_f16 = ((temp_f2 * 0.5f) + sp.u84) - (*(f32 *)((u8 *)sp.uA8 + 4));
        temp_f12 = sp.u7C - sp.u88;
        temp_f18 = ((temp_f12 * 0.5f) + sp.u88) - (*(f32 *)((u8 *)sp.uA8 + 8));
        temp_f8 = (temp_f2 * temp_f18) - (temp_f16 * temp_f12);
        sp4C = temp_f8;
        temp_f6 = (temp_f12 * temp_f14) - (temp_f18 * temp_f0);
        sp48 = temp_f6;
        temp_f10 = (temp_f0 * temp_f16) - (temp_f14 * temp_f2);
        sp44 = temp_f10;
        sp40 = (temp_f8 * temp_f8) + (temp_f6 * temp_f6) + (temp_f10 * temp_f10);
        sp.u8C = sp40;
        if (sp40 == 0.0f) {
            var_f12 = 0.0f;
            var_f14 = 0.0f;
            var_f16 = 0.0f;
        } else {
            temp_f2_2 = (*(f32 *)((u8 *)temp_s1_2 + 0x20)) / sqrtf(sp.u8C);
            var_f12 = sp4C * temp_f2_2;
            var_f14 = sp48 * temp_f2_2;
            var_f16 = sp44 * temp_f2_2;
        }
        (*(s16 *)((u8 *)sp.uAC + 0)) = (s16) (s32) (sp.u74 + var_f12);
        (*(s16 *)((u8 *)sp.uAC + 2)) = (s16) (s32) (sp.u78 + var_f14);
        (*(s16 *)((u8 *)sp.uAC + 4)) = (s16) (s32) (sp.u7C + var_f16);
        (*(s16 *)((u8 *)sp.uAC + 8)) = 0;
        (*(s16 *)((u8 *)sp.uAC + 0xA)) = 0;
        temp_t3 = (s16 *) ((u8 *) sp.uAC + 0x10);  /* P270: byte offset (was s16 stride) */
        sp.uAC = temp_t3;
        *temp_t3 = (s16) (s32) (sp.u74 - var_f12);
        (*(s16 *)((u8 *)sp.uAC + 2)) = (s16) (s32) (sp.u78 - var_f14);
        (*(s16 *)((u8 *)sp.uAC + 4)) = (s16) (s32) (sp.u7C - var_f16);
        (*(s16 *)((u8 *)sp.uAC + 8)) = 0x3C0;
        (*(s16 *)((u8 *)sp.uAC + 0xA)) = 0;
        temp_t3_2 = (s16 *) ((u8 *) sp.uAC + 0x10);  /* P270: byte offset (was s16 stride) */
        sp.uAC = temp_t3_2;
        *temp_t3_2 = (s16) (s32) (sp.u80 - var_f12);
        (*(s16 *)((u8 *)sp.uAC + 2)) = (s16) (s32) (sp.u84 - var_f14);
        (*(s16 *)((u8 *)sp.uAC + 4)) = (s16) (s32) (sp.u88 - var_f16);
        (*(s16 *)((u8 *)sp.uAC + 8)) = 0x3C0;
        (*(s16 *)((u8 *)sp.uAC + 0xA)) = 0x3C0;
        temp_t3_3 = (s16 *) ((u8 *) sp.uAC + 0x10);  /* P270: byte offset (was s16 stride) */
        sp.uAC = temp_t3_3;
        *temp_t3_3 = (s16) (s32) (sp.u80 + var_f12);
        (*(s16 *)((u8 *)sp.uAC + 2)) = (s16) (s32) (sp.u84 + var_f14);
        (*(s16 *)((u8 *)sp.uAC + 4)) = (s16) (s32) (sp.u88 + var_f16);
        (*(s16 *)((u8 *)sp.uAC + 8)) = 0;
        (*(s16 *)((u8 *)sp.uAC + 0xA)) = 0x3C0;
        sp.uAC = (s16 *) ((u8 *) sp.uAC + 0x10);  /* P270: byte offset (was s16 stride) */
        (*(s32 *)((u8 *)temp_v0 + 0)) = 0x01004008;
        temp_s0 = temp_v0 + 8;
        (*(s16 **)((u8 *)temp_v0 + 4)) = (s16 *) ((s16 *) ((u8 *) sp.uAC - 0x40));  /* P270: byte offset (was s16 stride) */
        temp_s0_2 = temp_s0 + 8;
        (*(s32 *)((u8 *)temp_s0 + 0)) = 0x05000204;
        (*(s32 *)((u8 *)temp_s0 + 4)) = 0;
        (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0x05000406;
        (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0;
        var_s0 = temp_s0_2 + 8;
        goto block_11;
    }
block_11:
    if (sp.uB3 != 0) {
        (*(s16 *)((u8 *)arg1 + 0xE)) = -1;
    }
    return var_s0;
}
/* was func_151B3474 */
void cord_plank_handle_link_msg(s32 arg0, s32 arg1, u8 arg2) {
    node_handle_link_message(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

/* was func_151B34B4 */
void cord_rig_on_obj_replaced(u8 *arg0, s32 *arg1, u8 arg2)
{
  u8 *v = arg0 + 0x28;
  s32 a;
  s32 b;
  s32 c;
  if (arg2 == 0x2D) {
    a = arg1[0];
    c = *(s32 *)v;
    if (a == c) {
      *(s32 *)v = arg1[1];
      v[4] = ((u8 *)arg1)[9];
    } else if ((b = arg1[1]) == c) {
      *(s32 *)v = a;
      v[4] = ((u8 *)arg1)[8];
    }
    b = arg1[1];
    a = arg1[0];
    c = *(s32 *)(v + 8);
    if (a == c) {
      *(s32 *)(v + 8) = b;
      v[0xC] = ((u8 *)arg1)[9];
      return;
    }
    if (b == c) {
      
      *(s32 *)(v + 8) = a;
      v[0xC] = ((u8 *)arg1)[8];
    }
  }
}

s32 cord_end_get_bone_pos(void *arg0, void *arg1, s32 arg2, u8 arg3);

/* P274: s32 (D_8008FE90 entry; cord_end_get_obj_pos and the C dispatchers test the result: the asm passes on
   cord_end_get_bone_pos's v0) */
/* was func_151B3550 */
s32 cord_end_handler_bone(u8 *arg0, s32 arg1, u8 arg2) {
    return cord_end_get_bone_pos(arg0, arg0 + 0x150, arg1, arg2);
}

/* was func_151B3580 */
void cord_plank_unlink(struct_eu_1DFE20 *arg0) {
    struct_eu_1DFE20_b *temp_v0 = arg0->unk4C;
    if (temp_v0 != NULL) {
        temp_v0->unk44 = 0;
    }
}

/* was func_151B3598 */
void cord_plank_retire(void *arg0) {
    cord_plank_unlink(arg0);
    effect_node_retire(arg0);
}

/* was func_151B35C4 */
void cord_plank_delete(void *arg0) {
    cord_plank_unlink(arg0);
    effect_node_free(arg0);
}

/* was func_151B35F0 */
void cord_handle_link_msg(s32 arg0, s32 arg1, u8 arg2) {
    s32 pad;
    s32 temp_a2;

    temp_a2 = arg0 + 0x150;
    node_handle_link_message(arg1, arg2, temp_a2, arg0 + 0x154, arg0);
    node_handle_link_message(arg1, arg2, temp_a2 + 0x14, temp_a2 + 0x18, arg0);
}
