#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for model_drip_drop_all
void model_drip_drop_all(u8 *arg0);

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} struct_eu_vec3;

typedef struct {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ struct_eu_vec3 unk34;
} struct_eu_1BAAA0_c;

typedef struct {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ struct_eu_1BAAA0_c *unk2C;
} struct_eu_1BAAA0_d;

typedef struct {
    /* 0x000 */ u8 pad0[0x1C];
    /* 0x01C */ s16 unk1C;
    /* 0x01E */ u8 pad1E[0xE];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[0x28];
    /* 0x05C */ u8 unk5C;
    /* 0x05D */ u8 pad5D[0x2C];
    /* 0x089 */ s8 unk89;
    /* 0x08A */ u8 pad8A[0x9A];
    /* 0x124 */ s16 unk124;
    /* 0x126 */ s16 unk126;
    /* 0x128 */ u8 pad128[0x2C];
    /* 0x154 */ f32 unk154;
    /* 0x158 */ s16 unk158;
    /* 0x15A */ s16 unk15A;
} struct_eu_1BAAA0_e;

typedef struct {
    u8 unk0[4];
} struct_eu_bytes4b;

extern struct_eu_bytes4b D_800A78B4;

typedef struct {
    /* 0x00 */ u8 pad0[0x84];
    /* 0x84 */ s32 unk84;
} struct_eu_1BAAA0_b;

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[0x24];
    /* 0x40 */ struct_eu_1BAAA0_b *unk40;
} struct_eu_1BAAA0;

/* was func_15190DB0 */
void model_drip_retire(void *arg0) {
    model_drip_drop_all(arg0);
    node_retire(arg0);
}

/* was func_15190DDC */
void model_drip_unlink_free(void *arg0) {
    model_drip_drop_all(arg0);
    node_unlink_free(arg0);
}

/* P188: moved up from model_drip_drop_all (also used by the NON_MATCHING model_drip_update) */
typedef struct { s16 base; s16 range; u8 pad4[0x10]; } Rng14;
extern Rng14 D_800AA120[];

/* P188 */
/* P188: the 3-argument prototype (functions.h) again here, so that difftest takes its arity from it: the asm leaves
 * cfg->points in a3 at the call, mtx_transform_point_or_origin (matching C, 3 parameters) never reads a3 */
void mtx_transform_point_or_origin(void *arg0, void *arg1, void *arg2);
void effect3d_set_handlers(u8 *, s32, s32, s32, s32);
s32 memcpy(s32, f32 *, s32);
void hitinfo_from_obj_floor(void *, u8 *);
extern f32 D_800A83F4;
extern u8 D_800AB6F0[];
extern u8 D_800AB7E4[];

typedef struct DripSlot {
    u8 *obj;               /* the falling drop object, NULL when free */
    s32 timer;             /* frames until it is released */
    struct DripSlot *next; /* free list (circular while spawning) */
} DripSlot;

typedef struct {
    u8 kind;     /* +0x00 drop type (D_800AA120 entry) */
    u8 pad1[3];
    s32 count;   /* +0x04 number of drip points / slots */
    u8 *points;  /* +0x08 0x10 bytes per point, +0xC = owner matrix index */
    f32 rate;    /* +0x0C drops per second */
    s32 max;     /* +0x10 most drops alive at once */
    s16 base;    /* +0x14 hang time base */
    s16 range;   /* +0x16 hang time random range */
} DripCfg;
extern DripCfg D_8008FE10[];

/* drip_emitter_update: P186: update handler (g_node_type_table entry +0) of a drip emitter e (rain drops hanging off an
 * owner model e +0x10, config D_8008FE10[e[0x1A]], slots e +0x24, live count e +0x20, accumulator f32 e +0x1C).
 * Kills itself (node_destroy) when its timer s16 e +0x16 runs out (flag e[0x18] & 1), the owner is gone or has
 * another id (e[0x14] vs owner[0x3B]), or the owner has no matrices (+0x1D4; then it first starts the ending
 * effect effect_node_create_nodraw with e +0x10..+0x1B copied to its +0x28). Hanging drops follow their point on the owner
 * (mtx_transform_point_or_origin with the owner matrix), and once their timer is over they fall (velocity from the last move *
 * D_800BEDC8, effect3d_set_handlers, life from D_800AA120). The accumulator gains rate * dt; for every whole unit a free slot
 * is picked at random and, when the point is below the owner's +0x118 height limit, a drop object is created
 * (effect3d_spawn_default with a 0x60-byte motion block at +0x110) and given a hang time. */
/* was func_15190E08 */
void model_drip_update(u8 *e) {
    struct {
        f32 vel[3];     /* +0x00 */
        f32 gravity;    /* +0x0C -1 */
        f32 f10;        /* +0x10 D_800A83F4 */
        s16 s14, s16;   /* +0x14 15, 17 */
        f32 f18;        /* +0x18 0 */
        f32 f1C;        /* +0x1C D_800A83F4 */
        u8 kind;        /* +0x20 */
        u8 b21, b22, b23, b24;
        u8 pad25[3];
        s32 rng[4];     /* +0x28 D_800AA120[kind] +4..+0x13 (+0x2C, +0x34 read as f32) */
        u8 owner[0x24]; /* +0x38 hitinfo_from_obj_floor */
        u8 b5C;         /* +0x5C e[0x2C] */
        u8 pad5D[3];
    } blk;
    struct {
        u8 type;        /* +0x00 */
        u8 pad1;
        s16 flags;      /* +0x02 0x1001 */
        s16 life;       /* +0x04 300 */
        u8 pad6[2];
        s32 w8, wC;
        u8 b10, b11, b12, b13;
        f32 f14, f18;
        f32 pos[3];     /* +0x1C */
        f32 pos2[3];    /* +0x28 */
        f32 scale[3];   /* +0x34 */
        s32 w40;
        u8 b44, b45;
    } spawn;
    u8 kill = 0;
    u8 *owner;
    DripCfg *cfg;
    DripSlot *slot, *slots, *head, *tail;
    s32 i, n, k, live, idx;
    u8 *obj;
    Rng14 *r;
    s32 *src;
    u8 *drop;

    if (e[0x18] & 1) {
        *(s16 *) (e + 0x16) -= D_800BE9E4;
        if (*(s16 *) (e + 0x16) < 0) {
            kill = 1;
        }
    }
    if (!kill) {
        owner = *(u8 **) (e + 0x10);
        if (*(s32 *) owner == 0 || e[0x14] != owner[0x3B]) {
            kill = 1;
        }
    }
    if (!kill) {
        owner = *(u8 **) (e + 0x10);
        if (*(u8 **) (owner + 0x1D4) == NULL) {
            kill = 1;
            drop = (e[0x18] & 1) ? (u8 *) effect_node_create_nodraw(*(s16 *) (e + 0x16), -1, 13, 1, 8, 12, 255, 0)
                                 : (u8 *) effect_node_create_nodraw(300, -1, 13, 0, 8, 12, 255, 0);
            if (drop != NULL) {
                memcpy((s32) (drop + 0x28), (f32 *) (e + 0x10), 12);
            }
        } else {
            cfg = &D_8008FE10[e[0x1A]];
            head = NULL;
            tail = NULL;
            n = 0;
            slots = *(DripSlot **) (e + 0x24);
            for (i = 0, slot = slots; i < cfg->count; i++, slot++) {
                live = 1;
                if (slot->obj != NULL) {
                    obj = slot->obj;
                    *(f32 *) (obj + 0x40) = *(f32 *) (obj + 0x34);
                    *(f32 *) (obj + 0x44) = *(f32 *) (obj + 0x38);
                    *(f32 *) (obj + 0x48) = *(f32 *) (obj + 0x3C);
                    mtx_transform_point_or_origin(cfg->points + i * 0x10, obj + 0x34,
                                  *(u8 **) (*(u8 **) (e + 0x10) + 0x1D4) + cfg->points[i * 0x10 + 0xC] * 0x40);
                    slot->timer -= D_800BE9E4;
                    if (slot->timer < 0) {
                        obj = slot->obj;
                        *(f32 *) (obj + 0x114) = 0.0f;
                        *(f32 *) (obj + 0x110) = (*(f32 *) (obj + 0x34) - *(f32 *) (obj + 0x40)) * D_800BEDC8;
                        *(f32 *) (obj + 0x118) = (*(f32 *) (obj + 0x3C) - *(f32 *) (obj + 0x48)) * D_800BEDC8;
                        r = &D_800AA120[obj[0x130]];
                        effect3d_set_handlers(obj, 13, 18, 0, 13);
                        *(s16 *) (obj + 0x1C) = (u32) random_int() % (u32) (r->range + 1) + r->base;
                        *(s32 *) (obj + 0x58) |= 1;
                        slot->obj = NULL;
                        *(s32 *) (e + 0x20) -= 1;
                    } else {
                        live = 0;
                    }
                }
                if (live) {
                    /* free slot: push it on the free list */
                    n++;
                    if (tail == NULL) {
                        tail = slot;
                    }
                    slot->next = head;
                    head = slot;
                }
            }
            if (n != 0) {
                *(f32 *) (e + 0x1C) += cfg->rate * D_800BE9A4;
                if (1.0f < *(f32 *) (e + 0x1C)) {
                    tail->next = head; /* circular */
                    blk.vel[0] = 0.0f;
                    blk.vel[1] = 0.0f;
                    blk.vel[2] = 0.0f;
                    blk.f10 = D_800A83F4;
                    blk.s14 = 15;
                    blk.s16 = 17;
                    blk.f18 = 0.0f;
                    blk.f1C = D_800A83F4;
                    blk.gravity = -1.0f;
                    blk.kind = cfg->kind;
                    r = &D_800AA120[cfg->kind];
                    hitinfo_from_obj_floor(blk.owner, *(u8 **) (e + 0x10));
                    blk.b5C = e[0x2C];
                    spawn.type = D_800AB6F0[e[0x2C]];
                    spawn.flags = 0x1001;
                    spawn.life = 300;
                    spawn.w8 = 0;
                    spawn.wC = 0;
                    spawn.b10 = 0;
                    spawn.b11 = 0;
                    spawn.b12 = 0;
                    spawn.b13 = 255;
                    spawn.scale[0] = 1.0f;
                    spawn.scale[1] = 1.0f;
                    spawn.scale[2] = 1.0f;
                    spawn.w40 = 0;
                    spawn.b45 = 255;
                    blk.b21 = 0;
                    blk.b22 = 0;
                    src = (s32 *) ((u8 *) r + 4);
                    do {
                        /* pick a random free slot */
                        k = (u32) random_int() % (u32) n;
                        while (k-- != 0) {
                            tail = head;
                            head = head->next;
                        }
                        idx = head - slots;
                        spawn.b44 = (u32) random_int() % 101 + 100;
                        spawn.f14 = 0.0f;
                        spawn.f18 = 0.0f;
                        blk.rng[0] = src[0];
                        blk.rng[1] = src[1];
                        blk.rng[2] = src[2];
                        blk.rng[3] = src[3];
                        blk.b23 = (u32) random_int() % 5 + 4;
                        blk.b24 = (u32) random_int() % 5 + 4;
                        mtx_transform_point_or_origin(cfg->points + idx * 0x10, spawn.pos,
                                      *(u8 **) (*(u8 **) (e + 0x10) + 0x1D4) + cfg->points[idx * 0x10 + 0xC] * 0x40);
                        spawn.pos2[0] = spawn.pos[0];
                        spawn.pos2[1] = spawn.pos[1];
                        spawn.pos2[2] = spawn.pos[2];
                        if (*(f32 *) (*(u8 **) (e + 0x10) + 0x118) <
                            spawn.pos[1] - *(f32 *) &blk.rng[1] - *(f32 *) &blk.rng[3]) {
                            random_int();
                            drop = (u8 *) effect3d_spawn_default((s32) &spawn, 12, 0, 0, 13, D_800AB7E4[e[0x2C]] ? 0 : 2, 96, 255, 0);
                            head->obj = drop;
                            if (drop != NULL) {
                                memcpy((s32) (drop + 0x110), (f32 *) &blk, 0x60);
                                head->timer = (u32) random_int() % (u32) (cfg->range + 1) + cfg->base;
                                n--;
                                head = head->next;
                                tail->next = head;
                                *(s32 *) (e + 0x20) += 1;
                            }
                        }
                        *(f32 *) (e + 0x1C) -= 1.0f;
                    } while (1.0f < *(f32 *) (e + 0x1C) && n != 0 && *(s32 *) (e + 0x20) < cfg->max);
                }
            }
        }
    }
    if (kill) {
        node_destroy((struct102 *) e);
    }
}

/* was func_1519150C */
s32 drop_wobble_update(u8 *arg0) {
    s32 pad;
    u8 *p;
    f32 s;
    f32 c;

    arg0[0x131] += (s8)arg0[0x133] * D_800BE9E4;
    arg0[0x132] += (s8)arg0[0x134] * D_800BE9E4;
    p = arg0 + 0x110;
    s = angle_byte_cos((u8)(arg0[0x131] - 0x40));
    c = angle_byte_cos((u8)(p[0x22] - 0x40));
    *(f32 *)(arg0 + 0x2C) += ((*(f32 *)(p + 0x28) + (*(f32 *)(p + 0x30) * s)) - *(f32 *)(arg0 + 0x2C)) * 0.5f;
    *(f32 *)(arg0 + 0x30) += ((*(f32 *)(p + 0x2C) + (*(f32 *)(p + 0x34) * c)) - *(f32 *)(arg0 + 0x30)) * 0.5f;
    return 1;
}

void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, f32 *, s32);
extern s32 D_800DD608;
extern s32 D_800DD618;

/* was func_151915FC */
u8 *drop_quad_velocity_build(u8 *arg0, s16 arg1) {
    struct {
        u8 u37;
        f32 u38;
        u8 pad3C[0x10];
        f32 u4C;
        f32 u50;
        u8 pad54[0x4];
        f32 u58;
        u8 pad5C[0x4];
        u8 * u60;
        u8 * u64;
    } sp;
    u8 *sp30;
    f32 *sp2C;
    f32 *sp28;
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
    f32 var_f2;
    s32 temp_t0;
    u8 *temp_v0;

    vtx_slot_buffer_get(arg0 + 0x100, arg1, 0x40, &sp.u64, &sp.u37);
    sp.u60 = sp.u64;
    if (sp.u64 != NULL) {
        if (sp.u37 != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp2C = temp_a1;
            sp30 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_t0 = arg1 * 4;
        temp_v1 = temp_t0 + &D_800DD618;
        temp_a0 = temp_t0 + &D_800DD608;
        var_f14 = -1.0f;
        var_f2 = ((*temp_v1 * ((*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x34)))) - (*temp_a0 * ((*(f32 *)((u8 *)arg0 + 0x48)) - (*(f32 *)((u8 *)arg0 + 0x3C))))) * D_800BEDC8;
        if (var_f2 < 0.0f) {
            var_f14 = 1.0f;
            var_f2 = -var_f2;
        }
        var_f12 = sqrtf(var_f2) * (*(f32 *)((u8 *)arg0 + 0x12C));
        if (var_f12 > 1.5707964f) {
            var_f12 = 1.5707964f;
        }
        temp_f12 = var_f12 * var_f14;
        sp2C = temp_v1;
        sp28 = temp_a0;
        sp.u38 = temp_f12;
        sp.u58 = sinf(temp_f12);
        temp_f0 = cosf(temp_f12);
        temp_f12_2 = (*(f32 *)((u8 *)arg0 + 0x2C));
        temp_f14 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_f2 = temp_f12_2 * temp_f0;
        temp_f18 = temp_f12_2 * sp.u58;
        temp_f16 = -temp_f2;
        sp.u50 = temp_f14 * temp_f0;
        sp.u4C = temp_f14 * sp.u58;
        (*(s16 *)((u8 *)sp.u64 + 0)) = (s16) (s32) ((*temp_v1 * temp_f16) + (*(f32 *)((u8 *)arg0 + 0x34)));
        (*(s16 *)((u8 *)sp.u64 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (*temp_a0 * temp_f16));
        (*(s16 *)((u8 *)sp.u64 + 6)) = 0;
        (*(s16 *)((u8 *)sp.u64 + 0x10)) = (s16) (s32) ((*temp_v1 * temp_f2) + (*(f32 *)((u8 *)arg0 + 0x34)));
        (*(s16 *)((u8 *)sp.u64 + 0x12)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 0x14)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (*temp_a0 * temp_f2));
        (*(s16 *)((u8 *)sp.u64 + 0x16)) = 0;
        temp_f0_2 = temp_f2 - sp.u4C;
        (*(s16 *)((u8 *)sp.u64 + 0x20)) = (s16) (s32) ((*temp_v1 * temp_f0_2) + (*(f32 *)((u8 *)arg0 + 0x34)));
        (*(s16 *)((u8 *)sp.u64 + 0x22)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) - temp_f18) - sp.u50);
        (*(s16 *)((u8 *)sp.u64 + 0x24)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (*temp_a0 * temp_f0_2));
        (*(s16 *)((u8 *)sp.u64 + 0x26)) = 0;
        temp_f0_3 = -(temp_f2 + sp.u4C);
        (*(s16 *)((u8 *)sp.u64 + 0x30)) = (s16) (s32) ((*temp_v1 * temp_f0_3) + (*(f32 *)((u8 *)arg0 + 0x34)));
        (*(s16 *)((u8 *)sp.u64 + 0x32)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f18) - sp.u50);
        (*(s16 *)((u8 *)sp.u64 + 0x34)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (*temp_a0 * temp_f0_3));
        (*(s16 *)((u8 *)sp.u64 + 0x36)) = 0;
        return sp.u60;
    }
    return NULL;
}
void effect3d_set_handlers(u8 *, s32, s32, s32, s32);
/* was func_15191970 */
void model_drip_drop_all(u8 *arg0) {
    s32 i;
    u8 **p;
    u8 *q;
    Rng14 *r;

    *(f32 *)(arg0 + 0x1C) = 0.0f;
    *(s32 *)(arg0 + 0x20) = 0;
    p = *(u8 ***)(arg0 + 0x24);
    for (i = 0; i != 0x3C; i++, p += 3) {
        if (*p != NULL) {
            q = *p + 0x110;
            *(f32 *)(q + 0) = 0.0f;
            *(f32 *)(q + 4) = 0.0f;
            *(f32 *)(q + 8) = 0.0f;
            r = &D_800AA120[*(u8 *)(q + 0x20)];
            effect3d_set_handlers(*p, 0xD, 0x12, 0, 0xD);
            *(s16 *)(*p + 0x1C) = random_int() % (u32)(r->range + 1) + r->base;
            *(s32 *)(*p + 0x58) |= 1;
        }
    }
    bzero(*(u8 ***)(arg0 + 0x24), 0x2D0);
}

/* P143 */
s32 pos_in_world_bounds(u8 *);
s32 collision_floor_probe(f32 *, s32, f32, f32 *);
void impact_splash_ring_spawn(u8, f32, u8, f32 *, u8, u8, s32);
void impact_dust_particle_spawn(u8, f32, s16, s32, void *, u8, s32);
extern f32 D_800A83FC;
extern f32 D_800A8400;
// drop_fall_update: update handler (g_effect3d_update_fns slot 13) of a falling drop / debris sprite. Motion block at +0x110:
// velocity x/y/z, gravity +0x11C, drag +0x120 (x / z speeds times drag * dt each frame), trail easing +0x128 (the
// trail point +0x40 follows the position +0x34). Ends (0) when pos_in_world_bounds rejects the new position (out of the
// level); a floor probe (collision_floor_probe, floor y to +0x148) that hits also ends it and spawns a splash at the floor,
// sized by width +0x2C * height +0x30: kind +0x165 == 3 -> impact_dust_particle_spawn (0.25), else randomly impact_debris_spawn
// (D_800A83FC, life 80..120) or the ring impact_splash_ring_spawn (D_800A8400), of type +0x16C, owner data +0x14C.
/* was func_15191A90 */
s32 drop_fall_update(u8 *fx) {
    f32 *mv = (f32 *)(fx + 0x110);
    f32 probe[3];
    f32 y0, vx0, vz0, vy, dvy;
    f32 dx, dy, dz;
    f32 x, y, z;
    s8 ret;

    y0 = *(f32 *)(fx + 0x38);
    vx0 = mv[0];
    vz0 = mv[2];
    ret = 1;
    mv[0] = vx0 * (mv[4] * D_800BE9A4);
    mv[2] = vz0 * (mv[4] * D_800BE9A4);
    dx = (mv[0] + vx0) * 0.5f * D_800BE9A4;
    vy = mv[1];
    dvy = mv[3] * D_800BE9A4;
    dy = vy * D_800BE9A4 + dvy * D_800BE9A4 * 0.5f;
    dz = (mv[2] + vz0) * 0.5f * D_800BE9A4;
    mv[1] = vy + dvy;
    *(f32 *)(fx + 0x34) += dx;
    *(f32 *)(fx + 0x38) = y0 + dy;
    *(f32 *)(fx + 0x3C) += dz;
    *(f32 *)(fx + 0x40) += dx;
    *(f32 *)(fx + 0x44) += dy;
    *(f32 *)(fx + 0x48) += dz;
    x = *(f32 *)(fx + 0x34);
    y = *(f32 *)(fx + 0x38);
    z = *(f32 *)(fx + 0x3C);
    *(f32 *)(fx + 0x40) = x + (*(f32 *)(fx + 0x40) - x) * mv[6];
    *(f32 *)(fx + 0x44) = y + (*(f32 *)(fx + 0x44) - y) * mv[6];
    *(f32 *)(fx + 0x48) = z + (*(f32 *)(fx + 0x48) - z) * mv[6];
    probe[0] = x;
    probe[1] = y0 - *(f32 *)(fx + 0x30);
    probe[2] = *(f32 *)(fx + 0x3C);
    if (pos_in_world_bounds((u8 *)probe) == 0) {
        return 0;
    }
    if (collision_floor_probe(probe, 0, *(f32 *)(fx + 0x38) - *(f32 *)(fx + 0x30), (f32 *)(fx + 0x148)) != 0) {
        probe[1] = *(f32 *)(fx + 0x148);
        if (fx[0x165] == 3) {
            impact_dust_particle_spawn(fx[0x16C], *(f32 *)(fx + 0x2C) * *(f32 *)(fx + 0x30) * 0.25f, fx[0x5C], (s32)(fx + 0x14C),
                          probe, fx[0xC], fx[1]);
        } else if (random_int() & 1) {
            impact_debris_spawn(fx[0x16C], *(f32 *)(fx + 0x2C) * *(f32 *)(fx + 0x30) * D_800A83FC, fx[0x5C],
                          (s32)(fx + 0x14C), (struct17 *)probe, (random_int() % 41U) + 0x50, 1, 1, 0, fx[0xC],
                          fx[1]);
        } else {
            impact_splash_ring_spawn(fx[0x16C], *(f32 *)(fx + 0x2C) * *(f32 *)(fx + 0x30) * D_800A8400, fx[0x5C], probe, 1,
                          fx[0xC], fx[1]);
        }
        ret = 0;
    }
    return ret;
}

/* was func_15191DEC */
s32 drop_fade(struct_eu_1BAAA0_e *arg0) {
    s16 temp_v0 = arg0->unk1C;
    s32 temp_v1;

    if (temp_v0 < arg0->unk124) {
        temp_v1 = temp_v0 * arg0->unk126;
        if (temp_v1 < arg0->unk5C) {
            arg0->unk5C = temp_v1;
        }
    }
    return 1;
}

u8 *model_drip_create(u8 **, s32, u8, s32);

/* owner_effect_watch: P238: entry 13 of g_effect_node_update_fns_b (EU 0x8008A888, `void (u8 *)` handlers) for an effect e whose
 * 12-byte spawn record (owner pointer, id byte +4, s16 life +6, flags +8) sits at e +0x28. It kills itself
 * (node_destroy) when the owner is gone (owner word 0 is 0) or has another id (e[0x2C] vs owner[0x3B]). When the
 * owner's +0x1D4 is set it first re-spawns the record through model_drip_create(e + 0x28, 0, e[0xC], e[1]) (life = s16
 * e +0xE with flag bit 0 when e[0xD] bit 0 is set, else 300) and then kills itself. Otherwise nothing happens. */
/* was func_15191E2C */
void model_drip_wait_owner(u8 *e) {
    u8 *owner = *(u8 **) (e + 0x28);
    u8 *rec;
    s32 done = 0;

    if (*(s32 *) owner == 0 || e[0x2C] != owner[0x3B]) {
        done = 1;
    } else if (*(s32 *) (owner + 0x1D4) != 0) {
        rec = e + 0x28;
        done = 1;
        if (e[0xD] & 1) {
            rec[8] |= 1;
            *(s16 *) (rec + 6) = *(s16 *) (e + 0xE);
        } else {
            *(s16 *) (rec + 6) = 300;
        }
        model_drip_create((u8 **) rec, 0, e[0xC], e[1]);
    }
    if (done) {
        node_destroy((struct102 *) e);
    }
}

/* was func_15191EF0 */
void model_drip_on_message(struct102 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0xD) {
        if (((*(s32 *)((u8 *)arg0 + 0x10)) == (*(s32 *)((u8 *)arg1 + 0))) || (arg0->unk14 == (*(u8 *)((u8 *)arg1 + 4)))) {
            (*(s16 *)((u8 *)arg0 + 0x16)) = 0x64;
            arg0->unk18 |= 1;
        }
    } else if ((arg2 == 0xC) || (arg2 == 0x50) || (arg2 == 0xE)) {
        if (((*(s32 *)((u8 *)arg0 + 0x10)) == (*(s32 *)((u8 *)arg1 + 0))) || (arg0->unk14 == (*(u8 *)((u8 *)arg1 + 4)))) {
            node_destroy(arg0);
        }
    } else {
        if (arg2 == 0x4E) {
            node_destroy(arg0);
            return;
        }
        node_handle_link_message((s32) arg1, arg2, (s32) &arg0->unk10, (s32) &arg0->unk14, (s32) arg0);
    }
}
/* was func_15191FF4 */
void model_drip_wait_on_message(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_a2;
    u8 *temp_a2_2;
    u8 *temp_a2_3;

    if ((arg2 == 0xC) || (arg2 == 0xE) || (arg2 == 0x50)) {
        temp_a2 = &arg0->unk28;
        if (((*(s32 *)((u8 *)temp_a2 + 0)) == (*(s32 *)((u8 *)arg1 + 0))) || ((*(u8 *)((u8 *)temp_a2 + 4)) == (*(u8 *)((u8 *)arg1 + 4)))) {
            node_destroy(arg0);
        }
    } else {
        if (arg2 == 0x4E) {
            node_destroy(arg0);
            return;
        }
        if (arg2 == 0xD) {
            temp_a2_2 = &arg0->unk28;
            if (((*(s32 *)((u8 *)temp_a2_2 + 0)) == (*(s32 *)((u8 *)arg1 + 0))) || ((*(u8 *)((u8 *)temp_a2_2 + 4)) == (*(u8 *)((u8 *)arg1 + 4)))) {
                (*(s16 *)((u8 *)arg0 + 0xE)) = 0x64;
                (*(u8 *)((u8 *)arg0 + 0xD)) = (u8) ((*(u8 *)((u8 *)arg0 + 0xD)) | 1);
            }
        } else {
            temp_a2_3 = &arg0->unk28;
            node_handle_link_message((s32) arg1, arg2, (s32) temp_a2_3, (s32) (temp_a2_3 + 4), (s32) arg0);
        }
    }
}
extern s32 D_800A83F0;

/* was func_151920FC */
void model_drip_broadcast(s32 arg0, u8 arg1) {
    s32 sp1C;

    sp1C = D_800A83F0;
    effect_nodes_broadcast(arg0, arg1);
    node_broadcast_types(&sp1C, 1, arg0, arg1);
}
