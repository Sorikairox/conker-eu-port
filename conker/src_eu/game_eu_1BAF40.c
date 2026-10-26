#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void bone_sparks_emit(s32);

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
    /* 0x00 */ u8 pad0[0x84];
    /* 0x84 */ s32 unk84;
} struct_eu_1BAAA0_b;

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[0x24];
    /* 0x40 */ struct_eu_1BAAA0_b *unk40;
} struct_eu_1BAAA0;

/* P177 */
u8 *character_effect_create(u8 **arg0, u8 arg1);
// character_effect_attach: attaches effect `type` (1..18: fire, smoke, impacts, ...) to obj: a kind-0x21 effect record
/* (character_effect_create, for view `view`) holding obj, obj's id byte +0x3B, a duration, a flag byte, a direction byte and the
 * effect number. With `clear`, first frees (node_destroy) every kind-0x21 record of both groups that belongs to obj
 * or to obj's id (the list walk keeps the next pointer in g_node_iter_next[depth] like the other list walks).
 * Types 13, 14, 15, 16 and 18 take `time` as the duration (13, 15, 16: flag 0 for time 999 = endless); types 10..12
 * set the flag from obj +0x1CA. Returns the record, NULL for no obj, an unknown type or no record.
 * `arg5` and `name` (the effect's debug name) are not used. */
/* was func_1518D1C0 */
u8 *character_effect_attach(u8 *obj, s16 type, s16 time, u8 clear, u8 view, s32 arg5, char *name) {
    struct {
        u8 *owner;  /* 0x0 */
        u8 id;      /* 0x4 obj +0x3B */
        u8 pad5;
        s16 time;   /* 0x6 */
        u8 flag;    /* 0x8 */
        s8 dir;     /* 0x9 */
        u8 effect;  /* 0xA */
        u8 padB;
    } e;
    struct_eu_node *node;
    s32 i;

    if (obj == NULL) {
        return NULL;
    }
    if (clear) {
        for (i = 0; i < 2; i++) {
            g_node_iter_depth++;
            node = g_node_lists[i][0x21];
            while (node != NULL) {
                g_node_iter_next[g_node_iter_depth] = node->next;
                if (*(u8 **)((u8 *)node + 0x18) == obj || obj[0x3B] == ((u8 *)node)[0x1C]) {
                    node_destroy((struct102 *)node);
                }
                node = g_node_iter_next[g_node_iter_depth];
            }
            g_node_iter_depth--;
        }
    }
    e.owner = obj;
    e.id = obj[0x3B];
    switch (type) {
    case 1: e.time = 500; e.flag = 1; e.dir = 0; e.effect = 1; break;
    case 2: e.time = 3000; e.flag = 1; e.dir = 1; e.effect = 7; break;
    case 3: e.time = 200; e.flag = 1; e.dir = -1; e.effect = 8; break;
    case 4: e.time = 200; e.flag = 1; e.dir = -1; e.effect = 9; break;
    case 5: e.time = 3000; e.flag = 0; e.dir = -1; e.effect = 2; break;
    case 6: e.time = 3000; e.flag = 0; e.dir = -1; e.effect = 3; break;
    case 7: e.time = 3000; e.flag = 0; e.dir = -1; e.effect = 4; break;
    case 8: e.time = 3000; e.flag = 0; e.dir = -1; e.effect = 5; break;
    case 9: e.time = 3000; e.flag = 0; e.dir = -1; e.effect = 6; break;
    case 10: e.time = 75; e.flag = obj[0x1CA] ? 1 : 0; e.dir = 1; e.effect = 7; break;
    case 11: e.time = 75; e.flag = obj[0x1CA] ? 1 : 0; e.dir = 0; e.effect = 1; break;
    case 12: e.time = 75; e.flag = obj[0x1CA] ? 1 : 0; e.dir = 1; e.effect = 7; break;
    case 13: e.time = time; e.flag = (time == 999) ? 0 : 1; e.dir = -1; e.effect = 10; break;
    case 14: e.time = time; e.flag = 1; e.dir = -1; e.effect = 11; break;
    case 15: e.time = time; e.flag = (time == 999) ? 0 : 1; e.dir = -1; e.effect = 12; break;
    case 16: e.time = time; e.flag = (time == 999) ? 0 : 1; e.dir = -1; e.effect = 13; break;
    case 17: e.time = 300; e.flag = 1; e.dir = -1; e.effect = 14; break;
    case 18: e.time = time; e.flag = 1; e.dir = -1; e.effect = 15; break;
    default: return NULL;
    }
    return character_effect_create((u8 **)&e, view);
}

/* P197 */
/* character_effect_update: P197: update handler of the kind-0x21 character effect records that character_effect_attach
 * (character_effect_attach) creates through character_effect_create (fire, smoke, impacts ... on a model). See below. */
void mtx_transform_point_or_origin(void *arg0, void *arg1, void *arg2);
void effect3d_set_handlers(u8 *, u8, u8, u8, u8);
void character_effect_free_particles(u8 *);
s32 memcpy(u8 *, u8 **, s32);

typedef struct CharFxSlot {
    u8 *obj;                 /* +0x00 particle record, NULL when free */
    s32 timer;               /* +0x04 frames until it is let go */
    f32 off[3];              /* +0x08 offset from the effect position (single-position effects) */
    struct CharFxSlot *next; /* +0x14 free list (circular while spawning) */
} CharFxSlot;

typedef struct {
    f32 size[5];        /* +0x00 scaled by the effect scale */
    f32 f14, f18;       /* +0x14 */
    f32 f1C[3];         /* +0x1C */
    s16 s28, s2A;       /* +0x28 */
    f32 f2C, f30;       /* +0x2C */
    s16 life, range;    /* +0x34 life after release: life + rand % (range + 1) */
    u8 kind, b39, b3A;  /* +0x38 effect3d_spawn_default arguments */
    u8 end[4];          /* +0x3B effect3d_set_handlers arguments at release */
    u8 init;            /* +0x3F g_char_effect_spawn_init_fns index (spawn record initialiser) */
} CharFxTpl;

typedef struct {
    CharFxTpl *tpl;     /* +0x00 */
    s32 count;          /* +0x04 slots / model points */
    u8 *points;         /* +0x08 0x10 bytes per point: local position, +0xC s16 matrix index */
    f32 rate;           /* +0x0C particles per frame */
    s32 max;            /* +0x10 most particles alive */
    s16 base, range;    /* +0x14 hold time base + rand % (range + 1) */
    u8 shape;           /* +0x18 single position: 1 = sphere, 2 = ring */
    u8 attach;          /* +0x19 2 = single position, else follow the model points */
    u8 pad1A[2];
    f32 radius;         /* +0x1C */
    f32 height;         /* +0x20 ring height */
    f32 yoff;           /* +0x24 y offset of the hidden-model position */
    f32 local[3];       /* +0x28 position in matrix `matrix` (attach 2) */
    u8 matrix;          /* +0x34 */
} CharFxCfg;

typedef struct {
    s16 len;
    u8 *ids;            /* model ids (owner +0x84) using this row */
} CharFxIds;

typedef struct {
    CharFxCfg **rows;   /* (n + 2) per owner +0x1C8 variant: n per model-id list, default, hidden model */
    s16 n;
    CharFxIds *lists;
} CharFxSet;

typedef struct {
    f32 size[2];        /* +0x00 */
    f32 mid;            /* +0x08 (size[0] + size[1]) / 2 on a fresh start, else 0 */
    f32 size2[3];       /* +0x0C */
    f32 mid2;           /* +0x18 */
    s16 s1C, s1E;       /* +0x1C 0 */
    f32 f20, f24;       /* +0x20 tpl f14, f18 */
    u8 pad28[4];        /* +0x28 (not set) */
    s16 s2C;            /* +0x2C 0 */
    u8 pad2E[2];
    f32 vel[3];         /* +0x30 set when the particle is let go */
    f32 f3C[3];         /* +0x3C tpl f1C.. */
    s16 s48, s4A;       /* +0x48 */
    f32 f4C, f50;       /* +0x4C */
    CharFxTpl *tpl;     /* +0x54 */
} CharFxMotion;         /* 0x58 bytes, copied to the particle record +0x110 */

typedef struct {
    u8 type;            /* +0x00 */
    u8 pad1;
    s16 flags;          /* +0x02 */
    u8 pad4[4];
    s32 w8;             /* +0x08 0 */
    s32 wC;             /* +0x0C (tpl f14 + f18) / 2 */
    u8 b10, b11, b12, b13;
    f32 f14, f18;       /* +0x14 the mids */
    f32 pos[3];         /* +0x1C (not set: the record position is written after the spawn) */
    f32 pos2[3];        /* +0x28 */
    f32 scale[3];       /* +0x34 1, 0, 1 */
    f32 f40;            /* +0x40 2 */
    u8 b44, b45;        /* +0x44 255, 255 */
} CharFxSpawn;

typedef struct {
    u8 pad0[0x10];
    s32 flags;          /* +0x10 bit 0: running */
    u8 pad14[4];
    u8 *owner;          /* +0x18 */
    u8 id;              /* +0x1C owner +0x3B at creation */
    u8 pad1D;
    s16 time;           /* +0x1E */
    u8 timed;           /* +0x20 bit 0: time runs out */
    s8 onEnd;           /* +0x21 g_char_effect_end_fns handler at the end of the time, -1 = remove */
    u8 effect;          /* +0x22 g_char_effect_sets index */
    u8 pad23;
    f32 accum;          /* +0x24 particles owed */
    s32 live;           /* +0x28 */
    u8 mode;            /* +0x2C last row kind (4 model, 2 hidden model); bit 3 = new */
    u8 attach;          /* +0x2D last row's attach */
    u8 pad2E[2];
    u8 *scaleSrc;       /* +0x30 scale = **(f32 **)(scaleSrc + 0x18) / 100 */
    f32 scale;          /* +0x34 */
    f32 pos[3];         /* +0x38 */
    u8 pad44[4];
    CharFxSlot slots[100]; /* +0x48 */
} CharFx;

extern CharFxSet *g_char_effect_sets[]; /* was D_8008D980 */
extern void (*g_char_effect_spawn_init_fns[])(u8 *, u8 *, u8 *, u8 *, u8 *, u8 *, s16 *); /* was D_8008D9C0 */
extern s32 (*g_char_effect_end_fns[])(u8 *); /* was D_8008D9C8 */

/* character_effect_update: per-frame handler (object type entry at D_8008BEFC) of a kind-0x21 character effect e
 * (character_effect_attach / character_effect_create), a particle emitter tied to the owner model e->owner. When e is not running it only
 * frees its particles (character_effect_free_particles, mode 1). It removes itself (node_destroy) when the owner is gone or has
 * another id, or when its time (e +0x1E, bit 0 of e +0x20) runs out (then the g_char_effect_end_fns[onEnd] handler decides).
 * When the owner is hidden for this view (owner +0x74 bit g_cur_view_player) the particles are freed. Otherwise the row of
 * g_char_effect_sets[effect] for the owner's variant (+0x1C8) is picked: with matrices (+0x1D4) and a visible model
 * (+0x74 & 0xF != 0xF) the row whose id list holds owner +0x84 (else the default row), mode 4; without, the hidden
 * row (mode 2) at the owner position + yoff. A row / mode change restarts the effect (accumulator = max).
 * Live particles follow their model point (mtx_transform_point_or_origin) or the effect position + their offset; when their hold
 * time is over they are let go: velocity from the last move * D_800BEDC8 (x / z clamped to +-10), effect3d_set_handlers
 * with the template's end arguments, a life time. The accumulator gains rate per frame; for every whole unit a free
 * slot is picked at random and a particle record is spawned (g_char_effect_spawn_init_fns[tpl->init] fills the spawn block,
 * effect3d_spawn_default, the 0x58-byte motion block to +0x110) at a model point or at the effect position + a random
 * sphere (shape 1) / ring (shape 2) offset. */
/* was func_1518DC50 */
void character_effect_update(u8 *arg0) {
    CharFx *e = (CharFx *) arg0;
    CharFxMotion blk;
    CharFxSpawn spawn;
    CharFxSet *set;
    CharFxCfg *cfg;
    CharFxCfg **row;
    CharFxTpl *tpl;
    CharFxSlot *slot, *head, *tail;
    CharFxMotion *m;
    u8 *owner, *obj, *rec, *pt;
    s8 kill = 0;
    u8 mode, fresh, live, ok, vis, b, a, c;
    s32 i, j, k, n, nfree, found, idx;
    f32 r, f, sb, cb, sa, ca;

    if (!(e->flags & 1)) {
        if (e->live != 0) {
            character_effect_free_particles(arg0);
            e->mode = 1;
        }
        return;
    }
    owner = e->owner;
    if (owner == NULL || *(s32 *) owner == 0 || e->id != owner[0x3B]) {
        kill = 1;
    } else {
        if (e->scaleSrc != NULL) {
            e->scale = **(f32 **) (e->scaleSrc + 0x18) * 0.01f;
        }
        if (e->timed & 1) {
            e->time -= g_frame_ticks;
            if (e->time < 0) {
                if (e->onEnd == -1) {
                    kill = 1;
                } else {
                    kill = g_char_effect_end_fns[e->onEnd](arg0);
                }
            }
        }
        owner = e->owner;
        vis = owner[0x74];
        if (vis & (1 << g_cur_view_player)) {
            /* hidden in this view */
            if (!(e->mode & 1)) {
                character_effect_free_particles(arg0);
                e->mode |= 1;
            }
        } else {
            fresh = 0;
            set = g_char_effect_sets[e->effect];
            nfree = 0;
            tail = NULL;
            head = NULL;
            n = set->n;
            row = set->rows + owner[0x1C8] * (n + 2);
            if (*(u8 **) (owner + 0x1D4) != NULL && (vis & 0xF) != 0xF) {
                mode = 4;
                cfg = row[n];
                found = 0;
                for (i = 0; i < n && !found; i++) {
                    for (j = 0; j < set->lists[i].len; j++) {
                        if (*(u16 *) (owner + 0x84) == set->lists[i].ids[j]) {
                            found = 1;
                            cfg = row[i];
                            break;
                        }
                    }
                }
            } else {
                mode = 2;
                cfg = row[n + 1];
            }
            if (!(e->mode & 8) && (mode != e->mode || e->attach != cfg->attach)) {
                /* other row: restart */
                character_effect_free_particles(arg0);
                fresh = 1;
                e->accum = (f32) cfg->max;
            }
            if (mode == 2) {
                owner = e->owner;
                e->pos[0] = *(f32 *) (owner + 0x14);
                e->pos[1] = *(f32 *) (owner + 0x18) + cfg->yoff;
                e->pos[2] = *(f32 *) (owner + 0x1C);
            } else if (cfg->attach == 2) {
                mtxf_transform_point((f32(*)[4]) (*(u8 **) (e->owner + 0x1D4) + cfg->matrix * 0x40), cfg->local[0],
                              cfg->local[1], cfg->local[2], &e->pos[0], &e->pos[1], &e->pos[2]);
            }

            /* move the live particles, let go of the expired ones, collect the free slots */
            for (i = 0, slot = e->slots; i < cfg->count; i++, slot++) {
                live = 1;
                if (slot->obj != NULL) {
                    obj = slot->obj;
                    *(f32 *) (obj + 0x40) = *(f32 *) (obj + 0x34);
                    *(f32 *) (obj + 0x44) = *(f32 *) (obj + 0x38);
                    *(f32 *) (obj + 0x48) = *(f32 *) (obj + 0x3C);
                    if (cfg->attach == 2 || mode == 2) {
                        *(f32 *) (slot->obj + 0x34) = e->pos[0] + slot->off[0];
                        *(f32 *) (slot->obj + 0x38) = e->pos[1] + slot->off[1];
                        *(f32 *) (slot->obj + 0x3C) = e->pos[2] + slot->off[2];
                    } else {
                        pt = cfg->points + i * 0x10;
                        mtx_transform_point_or_origin(pt, slot->obj + 0x34,
                                      *(u8 **) (e->owner + 0x1D4) + *(s16 *) (pt + 0xC) * 0x40);
                    }
                    slot->timer -= g_frame_ticks;
                    if (slot->timer < 0) {
                        obj = slot->obj;
                        m = (CharFxMotion *) (obj + 0x110);
                        m->vel[0] = (*(f32 *) (obj + 0x34) - *(f32 *) (obj + 0x40)) * D_800BEDC8;
                        if (10.0f < m->vel[0]) {
                            m->vel[0] = 10.0f;
                        } else if (m->vel[0] < -10.0f) {
                            m->vel[0] = -10.0f;
                        }
                        m->vel[2] = (*(f32 *) (obj + 0x3C) - *(f32 *) (obj + 0x48)) * D_800BEDC8;
                        if (10.0f < m->vel[2]) {
                            m->vel[2] = 10.0f;
                        } else if (m->vel[2] < -10.0f) {
                            m->vel[2] = -10.0f;
                        }
                        m->vel[1] = 0.0f;
                        effect3d_set_handlers(slot->obj, m->tpl->end[0], m->tpl->end[1], m->tpl->end[2], m->tpl->end[3]);
                        k = random_int();
                        *(s16 *) (slot->obj + 0x1C) = (u32) k % (u32) (m->tpl->range + 1) + m->tpl->life;
                        *(s32 *) (slot->obj + 0x58) |= 1;
                        slot->obj = NULL;
                        e->live--;
                    } else {
                        live = 0;
                    }
                }
                if (live) {
                    nfree++;
                    if (tail == NULL) {
                        tail = slot;
                    }
                    slot->next = head;
                    head = slot;
                }
            }

            /* spawn */
            if (nfree != 0) {
                e->accum += cfg->rate;
                if (1.0f < e->accum) {
                    tpl = cfg->tpl;
                    ok = 1;
                    tail->next = head; /* circular */
                    spawn.w8 = 0;
                    blk.f20 = tpl->f14;
                    blk.f24 = tpl->f18;
                    blk.s2C = 0;
                    spawn.wC = (s32) ((tpl->f14 + tpl->f18) * 0.5f);
                    blk.f3C[0] = tpl->f1C[0];
                    blk.f3C[1] = tpl->f1C[1];
                    blk.f3C[2] = tpl->f1C[2];
                    blk.f4C = tpl->f2C;
                    blk.f50 = tpl->f30;
                    blk.s48 = tpl->s28;
                    blk.s4A = tpl->s2A;
                    blk.size[0] = tpl->size[0] * e->scale;
                    blk.size[1] = tpl->size[1] * e->scale;
                    blk.s1C = 0;
                    if (fresh) {
                        f = (blk.size[0] + blk.size[1]) * 0.5f;
                    } else {
                        f = 0.0f;
                    }
                    spawn.f14 = f;
                    blk.mid = f;
                    blk.size2[0] = tpl->size[2] * e->scale;
                    blk.size2[1] = tpl->size[3] * e->scale;
                    blk.s1E = 0;
                    blk.size2[2] = tpl->size[4] * e->scale;
                    if (fresh) {
                        f = (blk.size2[0] + blk.size2[1]) * 0.5f;
                    } else {
                        f = 0.0f;
                    }
                    spawn.f18 = f;
                    blk.mid2 = f;
                    blk.tpl = tpl;
                    spawn.scale[0] = 1.0f;
                    spawn.scale[1] = 0.0f;
                    spawn.scale[2] = 1.0f;
                    spawn.f40 = 2.0f;
                    spawn.b44 = 255;
                    spawn.b45 = 255;
                    if (nfree != 0 && !(e->accum < 1.0f) && e->live < cfg->max) {
                        do {
                            /* pick a random free slot */
                            k = (u32) random_int() % (u32) (nfree + 1);
                            while (k-- != 0) {
                                tail = head;
                                head = head->next;
                            }
                            g_char_effect_spawn_init_fns[tpl->init]((u8 *) &spawn, &b, &spawn.b10, &spawn.b11, &spawn.b12, &spawn.b13,
                                                  &spawn.flags);
                            rec = (u8 *) effect3d_spawn_default((s32) &spawn, tpl->kind, tpl->b39, 0, tpl->b3A, b, 0x58, 255, 0);
                            head->obj = rec;
                            if (rec != NULL) {
                                memcpy(rec + 0x110, (u8 **) &blk, 0x58);
                                *(s32 *) (head->obj + 0x58) |= 0x40000000;
                                if (cfg->attach == 2 || mode == 2) {
                                    switch (cfg->shape) {
                                    case 1: /* sphere */
                                        a = random_int();
                                        c = random_int();
                                        r = random_float() * cfg->radius;
                                        cb = angle_byte_cos((u8) (c - 0x40));
                                        sb = angle_byte_cos(c);
                                        ca = angle_byte_cos((u8) (a - 0x40));
                                        sa = angle_byte_cos(a);
                                        head->off[0] = r * sb * ca;
                                        head->off[1] = -r * cb;
                                        head->off[2] = r * sb * sa;
                                        break;
                                    case 2: /* ring */
                                        a = random_int();
                                        r = random_float() * cfg->radius;
                                        head->off[0] = angle_byte_cos(a) * r;
                                        head->off[1] = random_float() * cfg->height;
                                        head->off[2] = -angle_byte_cos((u8) (a - 0x40)) * r;
                                        break;
                                    }
                                    *(f32 *) (head->obj + 0x34) = e->pos[0] + head->off[0];
                                    *(f32 *) (head->obj + 0x38) = e->pos[1] + head->off[1];
                                    *(f32 *) (head->obj + 0x3C) = e->pos[2] + head->off[2];
                                } else {
                                    idx = head - e->slots;
                                    pt = cfg->points + idx * 0x10;
                                    mtx_transform_point_or_origin(pt, head->obj + 0x34,
                                                  *(u8 **) (e->owner + 0x1D4) + *(s16 *) (pt + 0xC) * 0x40);
                                }
                                obj = head->obj;
                                *(f32 *) (obj + 0x40) = *(f32 *) (obj + 0x34);
                                *(f32 *) (obj + 0x44) = *(f32 *) (obj + 0x38);
                                *(f32 *) (obj + 0x48) = *(f32 *) (obj + 0x3C);
                                head->timer = (u32) random_int() % (u32) (cfg->range + 1) + cfg->base;
                                head = head->next;
                                tail->next = head;
                                e->live++;
                            } else {
                                ok = 0;
                            }
                            e->accum -= 1.0f;
                            nfree--;
                        } while (ok && nfree != 0 && !(e->accum < 1.0f) && e->live < cfg->max);
                    }
                    while (1.0f < e->accum) {
                        e->accum -= 1.0f;
                    }
                }
            }
            e->mode = mode;
            e->attach = cfg->attach;
        }
    }
    if (kill) {
        node_destroy((struct102 *) arg0);
    }
}

/* was func_1518E808 */
s32 effect_sound_follow_owner(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x1C));
    if ((temp_v1 != NULL) && ((*(s32 *)temp_v1) != 0)) {
        (*(s16 *)((u8 *)arg0 + 2)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x14));
        (*(s16 *)((u8 *)arg0 + 4)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x18));
        (*(s16 *)((u8 *)arg0 + 6)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x1C));
        return 0;
    }
    return 1;
}

/* was func_1518E878 */
void character_effect_free_particles(u8 *arg0) {
    s32 i;
    struct102 **var_s0;

    var_s0 = (struct102 **)(arg0 + 0x48);
    *(s32 *)(arg0 + 0x28) = 0;
    *(f32 *)(arg0 + 0x24) = 0.0f;
    for (i = 0; i < 100; i++) {
        if (*var_s0 != NULL) {
            node_destroy(*var_s0);
        }
        var_s0 = (struct102 **)((u8 *)var_s0 + 0x18);
    }
    bzero(arg0 + 0x48, 0x960);
}

/* was func_1518E8EC */
void character_effect_set_type(u8 *arg0, u8 arg1) {
    if (arg1 != arg0[0x22]) {
        character_effect_free_particles(arg0);
        arg0[0x22] = arg1;
    }
}

s32 memcpy(u8 *, u8 **, s32);

/* was func_1518E934 */
u8 *character_effect_create(u8 **arg0, u8 arg1) {
    u8 *temp_v0;
    u8 *sp24;

    if ((*(u8 *)((u8 *)(*arg0) + 4)) == 0x96) {
        return NULL;
    }
    temp_v0 = node_alloc(0x21, 1, 0x9EC, 1, (u8) (s32) arg1, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp24 = temp_v0;
    memcpy(temp_v0 + 0x18, arg0, 0xC);
    (*(s32 *)((u8 *)temp_v0 + 0x28)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x2C)) = 8;
    (*(s8 *)((u8 *)temp_v0 + 0x2D)) = 4;
    (*(s32 *)((u8 *)temp_v0 + 0x30)) = 0;
    (*(s32 *)((u8 *)temp_v0 + 0x10)) = 1;
    (*(s32 *)((u8 *)temp_v0 + 0x14)) = 0;
    (*(f32 *)((u8 *)temp_v0 + 0x24)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x38)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x3C)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x40)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x34)) = 1.0f;
    bzero(temp_v0 + 0x48, 0x960);
    return sp24;
}

/* was func_1518EA10 */
void character_effect_cleanup(struct_eu_1BAAA0 *arg0) {
    character_effect_free_particles(arg0);
    char_fx_detach_effect(arg0, arg0->unk18);
}

/* was func_1518EA3C */
void character_effect_retire(void *arg0) {
    character_effect_cleanup(arg0);
    node_retire(arg0);
}

/* was func_1518EA68 */
void character_effect_unlink_free(void *arg0) {
    character_effect_cleanup(arg0);
    node_unlink_free(arg0);
}

/* was func_1518EA94 */
void character_effect_init_spark(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, u8 *arg5, s16 *arg6) {
    s32 temp_v1;

    *arg1 = 2;
    if (random_int() & 1) {
        *arg1 |= 1;
    }
    temp_v1 = random_int() & 1;
    switch (temp_v1) {                              /* irregular */
    case 0:
        *arg0 = 0x13;
        break;
    case 1:
        *arg0 = 0x14;
        break;
    }
    *arg2 = 0;
    *arg3 = 0;
    *arg4 = 0;
    *arg5 = 0xFF;
    *arg6 = 0x301;
}

void fx_pick_random_color(s32, s32, s32, s32);

/* was func_1518EB48 */
void character_effect_init_smoke(s8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5, s16 *arg6) {
    s32 var_v0;

    if (random_int() & 1) {
        *arg1 |= 1;
    }
    *arg0 = 0x16;
    if (random_int() & 1) {
        var_v0 = 3;
    } else {
        var_v0 = 4;
    }
    fx_pick_random_color(var_v0 & 0xFF, arg2, arg3, arg4);
    *arg5 = 0xC8;
    *arg6 = 0x401;
}

u8 *character_effect_attach(u8 *, s16, s16, u8, u8, s32, char *);
extern s32 g_char_effect_name_chain3; /* was D_800A7840 */

/* was func_1518EBDC */
s32 character_effect_end_chain3(u8 *arg0) {
    character_effect_attach(*(u8 **)(arg0 + 0x18), 3, 0, 0, arg0[0xC], arg0[1], (char *)&g_char_effect_name_chain3);
    (*(s16 *)((u8 *)arg0 + 0x1E)) = 0x80;
    (*(s8 *)((u8 *)arg0 + 0x21)) = -1;
    return 0;
}

extern s32 g_char_effect_name_chain4; /* was D_800A787C */

/* was func_1518EC44 */
s32 character_effect_end_chain4(u8 *arg0) {
    character_effect_attach(*(u8 **)(arg0 + 0x18), 4, 0, 0, arg0[0xC], arg0[1], (char *)&g_char_effect_name_chain4);
    (*(s16 *)((u8 *)arg0 + 0x1E)) = 0x80;
    (*(s8 *)((u8 *)arg0 + 0x21)) = -1;
    return 0;
}

/* P203 */
void vtx_slot_buffer_get(s32, s16, s32, u8 **, u8 *);
f32 math_sin_u8(u8);
f32 math_cos_u8(u8);
extern f32 g_view_yaw_sin[]; /* per view: sin of the camera yaw; was D_800DD608 */
extern f32 g_view_yaw_cos[]; /* per view: cos of the camera yaw; was D_800DD618 */

// particle_quad_velocity_build: P203: entry 5 of the particle draw table g_effect3d_draw_fns (game_169510): builds the 4
// vertices of the particle `p` for view `view` (a quad stretched along its screen-space motion, e.g. the
// character-effect flames). vtx_slot_buffer_get gives the view's vertex block (p +0x100[view], 0x40 bytes); when it is
// new, both of its halves get the template vertices p +0xC0. Lean: the motion since the last frame (+0x40 - +0x34,
// +0x48 - +0x3C) across the view (cos / sin of the view, g_view_yaw_cos / g_view_yaw_sin) times D_800BEDC8, then
// sqrt(|t|) * p +0x160, at most pi / 2, negative for a forward motion; byte angle = lean * 256 / (2 pi) (Rare's
// unsigned conversion makes every negative angle 0xFF). Half width p +0x2C, half height p +0x30 rotated by the
// angle (math_sin_u8 sin, math_cos_u8 cos) around the position p +0x34; the s16 corners go to +0x00, +0x10,
// +0x20, +0x30 of the block (the view's horizontal axis is (cos, -sin) in x / z). Returns the block, NULL when
// none is available.
/* was func_1518ECAC */
u8 *particle_quad_velocity_build(u8 *p, s16 view) {
    u8 *blk;
    u8 fresh;
    s16 *v;
    f32 s, c, t, lean, sn, cs, a, b, hs, hc, e;
    s32 n, neg;
    u8 ang;

    vtx_slot_buffer_get((s32) (p + 0x100), view, 0x40, &blk, &fresh);
    if (blk == NULL) {
        return NULL;
    }
    if (fresh) {
        memcpy(*(u8 **) (p + 0x100 + view * 4), (u8 **) (p + 0xC0), 0x40);
        memcpy(*(u8 **) (p + 0x100 + view * 4) + 0x40, (u8 **) (p + 0xC0), 0x40);
    }
    s = g_view_yaw_sin[view];
    c = g_view_yaw_cos[view];
    t = ((*(f32 *) (p + 0x40) - *(f32 *) (p + 0x34)) * c - s * (*(f32 *) (p + 0x48) - *(f32 *) (p + 0x3C))) *
        D_800BEDC8;
    neg = TRUE;
    if (t < 0.0f) {
        t = -t;
        neg = FALSE;
    }
    lean = sqrtf(t) * *(f32 *) (p + 0x160);
    if (1.5707964f < lean) {
        lean = 1.5707964f;
    }
    if (neg) {
        lean = -lean;
    }
    /* (u32) conversion as IDO does it: truncation, a negative result becomes 0xFFFFFFFF */
    n = (s32) (lean * 40.7436638f);
    ang = (n < 0) ? 0xFF : n;
    sn = math_sin_u8(ang);
    cs = math_cos_u8(ang);
    a = *(f32 *) (p + 0x2C) * cs;
    b = *(f32 *) (p + 0x2C) * sn;
    hs = *(f32 *) (p + 0x30) * sn;
    hc = *(f32 *) (p + 0x30) * cs;
    v = (s16 *) blk;
    v[0] = *(f32 *) (p + 0x34) + a * c;
    v[1] = *(f32 *) (p + 0x38) + b;
    v[2] = *(f32 *) (p + 0x3C) - a * s;
    v[8] = *(f32 *) (p + 0x34) + -a * c;
    v[9] = *(f32 *) (p + 0x38) - b;
    v[10] = *(f32 *) (p + 0x3C) - -a * s;
    e = -(a + hs);
    v[16] = *(f32 *) (p + 0x34) + e * c;
    v[17] = (*(f32 *) (p + 0x38) + hc) - b;
    v[18] = *(f32 *) (p + 0x3C) - e * s;
    e = a - hs;
    v[24] = *(f32 *) (p + 0x34) + e * c;
    v[25] = (*(f32 *) (p + 0x38) + hc) + b;
    v[26] = *(f32 *) (p + 0x3C) - e * s;
    return blk;
}

/* P222: readable C for line_quad_build (game_eu_1BAF40, 273 words). */
/* vtx_slot_buffer_get is declared above in game_eu_1BAF40.c: (s32, s16, s32, u8 **, u8 *) */

// line_quad_build: builds the camera-facing quad of a line effect for display list slot `slot`: the line runs from
// A = +0x34/+0x38/+0x3C towards B = +0x40/+0x44/+0x48, cut at P = A + (B - A) * +0x30. Each end gets two vertices,
// offset by +-(half width +0x2C) along the normal of the plane through the end, the line and the slot's camera
// (g_player_views[slot] +0x2F8): A + n, A - n, P + n, P - n (a zero normal gives offset 0). vtx_slot_buffer_get hands out the
// slot's vertex buffer (pointer table at +0x100); when it is new, both halves (0x40 bytes each) are first filled from
// the template at +0xC0. Returns the written vertices, or NULL when no buffer is available. (Draw-table entry.)
/* was func_1518F080 */
u8 *line_quad_build(u8 *fx, s16 slot) {
    u8 *vtx;
    u8 *start;
    u8 fresh;
    f32 *cam;
    f32 px, py, pz;
    f32 dx, dy, dz;
    f32 ex, ey, ez;
    f32 nx, ny, nz;
    f32 len2, k;

    vtx_slot_buffer_get((s32) (fx + 0x100), slot, 0x40, &vtx, &fresh);
    start = vtx;
    if (vtx == NULL) {
        return NULL;
    }
    if (fresh) {
        memcpy(*(u8 **) (fx + 0x100 + slot * 4), (u8 **) (fx + 0xC0), 0x40);
        memcpy(*(u8 **) (fx + 0x100 + slot * 4) + 0x40, (u8 **) (fx + 0xC0), 0x40);
    }
    px = *(f32 *) (fx + 0x34) + (*(f32 *) (fx + 0x40) - *(f32 *) (fx + 0x34)) * *(f32 *) (fx + 0x30);
    py = *(f32 *) (fx + 0x38) + (*(f32 *) (fx + 0x44) - *(f32 *) (fx + 0x38)) * *(f32 *) (fx + 0x30);
    pz = *(f32 *) (fx + 0x3C) + (*(f32 *) (fx + 0x48) - *(f32 *) (fx + 0x3C)) * *(f32 *) (fx + 0x30);
    cam = (f32 *) ((u8 *) g_player_views + slot * 0x9A0 + 0x2F8);

    /* end A: normal = (P - A) x (A - camera) */
    dx = px - *(f32 *) (fx + 0x34);
    dy = py - *(f32 *) (fx + 0x38);
    dz = pz - *(f32 *) (fx + 0x3C);
    ex = *(f32 *) (fx + 0x34) - cam[0];
    ey = *(f32 *) (fx + 0x38) - cam[1];
    ez = *(f32 *) (fx + 0x3C) - cam[2];
    nx = dy * ez - ey * dz;
    ny = dz * ex - ez * dx;
    nz = dx * ey - ex * dy;
    len2 = nx * nx + ny * ny + nz * nz;
    if (len2 == 0.0f) {
        nx = ny = nz = 0.0f;
    } else {
        k = *(f32 *) (fx + 0x2C) / sqrtf(len2);
        nx *= k;
        ny *= k;
        nz *= k;
    }
    *(s16 *) (vtx + 0) = *(f32 *) (fx + 0x34) + nx;
    *(s16 *) (vtx + 2) = *(f32 *) (fx + 0x38) + ny;
    *(s16 *) (vtx + 4) = *(f32 *) (fx + 0x3C) + nz;
    *(s16 *) (vtx + 6) = 0;
    vtx += 0x10;
    *(s16 *) (vtx + 0) = *(f32 *) (fx + 0x34) - nx;
    *(s16 *) (vtx + 2) = *(f32 *) (fx + 0x38) - ny;
    *(s16 *) (vtx + 4) = *(f32 *) (fx + 0x3C) - nz;
    *(s16 *) (vtx + 6) = 0;
    vtx += 0x10;

    /* end P: normal = (A - P) x (P - camera) */
    dx = -dx;
    dy = -dy;
    dz = -dz;
    ex = px - cam[0];
    ey = py - cam[1];
    ez = pz - cam[2];
    nx = dy * ez - ey * dz;
    ny = dz * ex - ez * dx;
    nz = dx * ey - ex * dy;
    len2 = nx * nx + ny * ny + nz * nz;
    if (len2 == 0.0f) {
        nx = ny = nz = 0.0f;
    } else {
        k = *(f32 *) (fx + 0x2C) / sqrtf(len2);
        nx *= k;
        ny *= k;
        nz *= k;
    }
    *(s16 *) (vtx + 0) = px + nx;
    *(s16 *) (vtx + 2) = py + ny;
    *(s16 *) (vtx + 4) = pz + nz;
    *(s16 *) (vtx + 6) = 0;
    vtx += 0x10;
    *(s16 *) (vtx + 0) = px - nx;
    *(s16 *) (vtx + 2) = py - ny;
    *(s16 *) (vtx + 4) = pz - nz;
    *(s16 *) (vtx + 6) = 0;
    return start;
}

/* was func_1518F4C4 */
s32 line_particle_move_damped(u8 *arg0)
{
  u8 *p = arg0 + 0x110;
  f32 x;
  f32 y;
  f32 z;
  f32 f;
  u8 *q;
  f = *((f32 *) (arg0 + 0x150));
  *((f32 *) (arg0 + 0x140)) *= f;
  q = arg0; // fakematch: second name moves the g_frame_step_f address to v1 (s114 recipe 4)
  *((f32 *) (q + 0x144)) += (*((f32 *) (q + 0x14C))) * g_frame_step_f;
  *((f32 *) (q + 0x148)) *= f;
  x = (*((f32 *) (arg0 + 0x140))) * g_frame_step_f;
  y = (*((f32 *) (arg0 + 0x144))) * g_frame_step_f;
  z = (*((f32 *) (arg0 + 0x148))) * g_frame_step_f;
  *((f32 *) (arg0 + 0x34)) += x;
  *((f32 *) (q + 0x38)) += y;
  *((f32 *) (q + 0x3C)) += z;
  *((f32 *) (q + 0x40)) += x;
  *((f32 *) (q + 0x44)) += y;
  *((f32 *) (q + 0x48)) += z;
  *(f32 *)(arg0 + 0x40) = (*(f32 *)(arg0 + 0x40) - *(f32 *)(arg0 + 0x34)) * *(f32 *)(arg0 + 0x15C) + *(f32 *)(arg0 + 0x34);
  *(f32 *)(arg0 + 0x44) = (*(f32 *)(arg0 + 0x44) - *(f32 *)(arg0 + 0x38)) * *(f32 *)(p + 0x4C) + *(f32 *)(arg0 + 0x38);
  *(f32 *)(arg0 + 0x48) = (*(f32 *)(arg0 + 0x48) - *(f32 *)(arg0 + 0x3C)) * *(f32 *)(p + 0x4C) + *(f32 *)(arg0 + 0x3C);
  return 1;
}

/* was func_1518F5C8 */
s32 line_particle_move(u8 *arg0) {
    f32 x;
    f32 y;
    f32 z;
    f32 f;
    u8 *q;

    f = *(f32 *)(arg0 + 0x150);
    q = arg0; // fakematch: second name for arg0 puts the g_frame_step_f address in v1
    *(f32 *)(q + 0x140) *= f;
    *(f32 *)(q + 0x144) += *(f32 *)(q + 0x14C) * g_frame_step_f;
    *(f32 *)(q + 0x148) *= f;
    x = *(f32 *)(arg0 + 0x140) * g_frame_step_f;
    y = *(f32 *)(arg0 + 0x144) * g_frame_step_f;
    z = *(f32 *)(arg0 + 0x148) * g_frame_step_f;
    *(f32 *)(q + 0x34) += x;
    *(f32 *)(q + 0x38) += y;
    *(f32 *)(q + 0x3C) += z;
    *(f32 *)(q + 0x40) += x;
    *(f32 *)(q + 0x44) += y;
    *(f32 *)(q + 0x48) += z;
    return 1;
}

/* was func_1518F678 */
s32 particle_shrink_fade(struct_eu_1BAAA0_e *arg0) {
    arg0->unk30 = arg0->unk30 - (arg0->unk30 * arg0->unk154);
    arg0->unk2C = arg0->unk2C - (arg0->unk2C * arg0->unk154);
    if (arg0->unk1C < arg0->unk158) {
        arg0->unk5C = arg0->unk1C * arg0->unk15A;
    }
    return 1;
}

/* was func_1518F6CC */
s32 particle_shrink_height_fade(struct_eu_1BAAA0_e *arg0) {
    arg0->unk30 = arg0->unk30 - (arg0->unk30 * arg0->unk154);
    if (arg0->unk1C < arg0->unk158) {
        arg0->unk5C = arg0->unk1C * arg0->unk15A;
    }
    return 1;
}

/* was func_1518F710 */
s32 flame_particle_flicker(u8 *arg0) {
    u8 *p = arg0 + 0x110;
    s32 v;

    *(s16 *)(p + 0x1E) -= g_frame_ticks;
    if (*(s16 *)(p + 0x1E) < 0) {
        *(s16 *)(p + 0x1E) = random_int() % 6U;
        if (random_int() & 3) {
            *(f32 *)(p + 0x18) = *(f32 *)(p + 0x10) + (*(f32 *)(p + 0xC) - *(f32 *)(p + 0x10)) * random_float();
        } else {
            *(f32 *)(p + 0x18) = *(f32 *)(p + 0xC) + (*(f32 *)(p + 0x14) - *(f32 *)(p + 0xC)) * random_float();
        }
    }
    *(f32 *)(arg0 + 0x30) += (*(f32 *)(p + 0x18) - *(f32 *)(arg0 + 0x30)) * 0.359f;
    *(s16 *)(p + 0x1C) -= g_frame_ticks;
    if (*(s16 *)(p + 0x1C) < 0) {
        *(s16 *)(p + 0x1C) = random_int() % 17U;
        *(f32 *)(p + 0x8) = *(f32 *)(p + 0x4) + (*(f32 *)(p + 0x0) - *(f32 *)(p + 0x4)) * random_float();
    }
    *(f32 *)(arg0 + 0x2C) += (*(f32 *)(p + 0x8) - *(f32 *)(arg0 + 0x2C)) * 0.186f;
    *(s16 *)(p + 0x2C) -= g_frame_ticks;
    if (*(s16 *)(p + 0x2C) < 0) {
        *(s16 *)(p + 0x2C) = random_int() % 15U;
        *(f32 *)(p + 0x28) = *(f32 *)(p + 0x24) + (*(f32 *)(p + 0x20) - *(f32 *)(p + 0x24)) * random_float();
    }
    *(s32 *)(arg0 + 0x24) = (s32)((*(f32 *)(p + 0x28) - *(s32 *)(arg0 + 0x24)) * 0.231f) + *(s32 *)(arg0 + 0x24);
    return 1;
}

/* was func_1518F8F4 */
s32 flame_particle_settle(u8 *arg0) {
    u8 *p;

    if (*(s16 *)(arg0 + 0x12C) == 0) {
        p = arg0 + 0x110;
        *(f32 *)(p + 0x8) = *(f32 *)(p + 0x4) + (*(f32 *)(p + 0x0) - *(f32 *)(p + 0x4)) * random_float();
        *(s16 *)(p + 0x1C) = 1;
    }
    p = arg0 + 0x110;
    if (p) {} // fakematch: keeps p in v1 for the 0x1E test
    if (*(s16 *)(p + 0x1E) == 0) {
        *(f32 *)(p + 0x18) = *(f32 *)(p + 0x10) + (*(f32 *)(p + 0xC) - *(f32 *)(p + 0x10)) * random_float();
        *(s16 *)(p + 0x1E) = 1;
    }
    *(f32 *)(arg0 + 0x30) += (*(f32 *)(p + 0x18) - *(f32 *)(arg0 + 0x30)) * 0.359f;
    *(f32 *)(arg0 + 0x2C) += (*(f32 *)(p + 0x8) - *(f32 *)(arg0 + 0x2C)) * 0.186f;
    return 1;
}

// rodata_inject: size 0x24CB34 4
/* was func_1518F9CC */
void character_effect_broadcast(s32 arg0, u8 arg1) {
    const s32 sp1C[1] = {0x21};

    node_broadcast_types(sp1C, 1, arg0, arg1);
}

/* was func_1518FA0C */
void character_effect_on_message(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 v0;
    s32 v1;
    u8 a0;
    u8 a1;
    node_handle_link_message(arg1, arg2, arg0 + 0x18, arg0 + 0x1C, arg0);
    if (arg2 == 0x49) {
        v0 = *(s32 *)(arg0 + 0x18);
        v1 = *(s32 *)arg1;
        a0 = arg0[0x1C];
        a1 = arg1[4];
        if (v0 == v1 || a0 == a1) {
            node_destroy(arg0);
        }
    }
}

s32 bone_sparks_attach(s32, u8 *, s16, s8, s8, s8, u8, s32, u8, s32);
s32 bone_sparks_table_for_kind(s32, u8 *, u8);
extern u8 *g_bone_sparks_preset_tables[]; /* was D_8008D9D0 */
/* was func_1518FA8C */
s32 bone_sparks_attach_preset(s32 arg0, u8 arg1, s16 arg2, s8 arg3, s8 arg4, s8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    s32 sfpad; // fakematch: unused local shifts sp33 to the ref slot
    u8 sp33;

    if (arg0 == 0) {
        return 0;
    }
    if (bone_sparks_table_for_kind(arg0, &sp33, arg1) == 0) {
        return 0;
    }
    return bone_sparks_attach(arg0, g_bone_sparks_preset_tables[sp33] + arg1 * 0x50, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}

void *attach_ctrl_spawn(void *arg0, s32 arg1, u8 arg2, s32 arg3);
void attach_fx_asset_acquire(s32);
struct225 *bone_sparks_light_create(s32 arg0, u8 *arg1, u8 arg2, s16 arg3, u8 arg4, s32 arg5);
s32 effect_sound_follow_owner(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

typedef struct {
    s32 w[0x14];
} BlkFB40;

typedef struct {
    f32 unk0;
    BlkFB40 blk;
    s32 padAC;
    s8 unkB0;
    s8 unkB1;
    u8 unkB2;
    s32 unkB4;
} DataFB40;

typedef struct {
    u8 *obj;
    u8 id;
    s16 time;
    u8 flag;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
} HeadFB40;

/* was func_1518FB40 */
s32 bone_sparks_attach(s32 arg0, u8 *arg1, s16 arg2, s8 arg3, s8 arg4, s8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    HeadFB40 head;
    DataFB40 data;
    u8 *temp_v0;
    DataFB40 *d;
    u8 flag;

    data.unk0 = 0.0f;
    data.blk = *(BlkFB40 *)arg1;
    data.unkB0 = arg3;
    data.unkB1 = arg4;
    data.unkB2 = arg6;
    head.obj = (u8 *)arg0;
    head.id = ((u8 *)arg0)[0x3B];
    if (arg2 == -1) {
        head.time = 300;
    } else {
        head.time = arg2;
    }
    if (arg2 == -1) {
        flag = 0;
    } else {
        flag = 1;
    }
    head.flag = flag;
    head.unk9 = 0;
    head.unkA = 0;
    head.unkB = 0;
    head.unkC = 0;
    head.unkD = 1;
    temp_v0 = attach_ctrl_spawn(&head, arg7 + 0x60, arg8, arg9);
    if (temp_v0 != NULL) {
        d = (DataFB40 *)(temp_v0 + 0x30);
        memcpy(d, &data, 0x5C);
        if (arg5 != -1) {
            *(struct225 **)((u8 *)d + 0x54) = bone_sparks_light_create((s32)temp_v0, (u8 *)arg0, arg5, arg2, arg8, arg9);
        } else {
            *(struct225 **)((u8 *)d + 0x54) = NULL;
        }
        attach_fx_asset_acquire(*(s32 *)((u8 *)d + 0x48));
        sfx_emitter_start(0x4D, *(f32 *)((u8 *)arg0 + 0x14), *(f32 *)((u8 *)arg0 + 0x18), *(f32 *)((u8 *)arg0 + 0x1C), 15000, 2000, 800, (s32)effect_sound_follow_owner, temp_v0, arg0, 0, 0);
    }
    return (s32)temp_v0;
}

void bone_sparks_emit(s32);
// g_bone_sparks_tick_fns: the bone-spark emitter's tick handler table (0x8008DA1C: bone_sparks_tick_hurt, bone_sparks_owner_release). bone_sparks_tick
// indexes it with self +0x88 and returns the handler's result; bone_sparks_release indexes D_8008DA20 (= g_bone_sparks_tick_fns + 1)
// with self +0x89. One signature for both views (wasm call_indirect): s32 (u8 *).
extern s32 (*g_bone_sparks_tick_fns[])(u8 *); /* was D_8008DA1C */

// bone_sparks_tick: effect-child handler (g_attach_child_update_fns [3] / g_attach_child_end_fns [1]). Advances the emitter's spark counter
// (self +0x30) by (rate +0x34 + random f32 * spread +0x38) * g_frame_step_f (frame time), emits the sparks
// (bone_sparks_emit), then runs the tick handler g_bone_sparks_tick_fns[self +0x88] (none: -1) and returns its result (1 without).
// The second argument (the position the effect-node dispatchers pass) is not used; it is there for the table's
// common signature s32 (node, pos).
/* was func_1518FD34 */
s32 bone_sparks_tick(u8 *self, void *pos) {
    f32 *count = (f32 *)(self + 0x30);
    s8 tick;

    count[0] += (count[1] + random_float() * count[2]) * g_frame_step_f;
    bone_sparks_emit((s32)self);
    tick = (s8)self[0x88];
    if (tick != -1) {
        return g_bone_sparks_tick_fns[tick](self);
    }
    return 1;
}

// bone_sparks_release: effect-child handler (g_attach_child_update_fns [6] / g_attach_child_end_fns [4]): runs the release handler
// D_8008DA20[self +0x89] (= g_bone_sparks_tick_fns[self +0x89 + 1]; none: -1). The second argument is unused (table signature
// s32 (node, pos)); returns the handler's result (0 without; the dispatchers that reach it ignore v0).
/* was func_1518FDC8 */
s32 bone_sparks_release(u8 *self, void *pos) {
    s8 release = (s8)self[0x89];

    if (release != -1) {
        return g_bone_sparks_tick_fns[release + 1](self);
    }
    return 0;
}


// bone_sparks_burst: effect-child handler (g_attach_child_update_fns [4] / g_attach_child_end_fns [2]): sets the spark counter (self +0x30) to
// base +0x3C + random f32 * spread +0x40 and emits them at once (bone_sparks_emit). The second argument is unused (table
// signature s32 (node, pos)); returns 0 (the asm leaves bone_sparks_emit's v0; the dispatchers that reach it ignore it).
/* was func_1518FE0C */
s32 bone_sparks_burst(u8 *self, void *pos) {
    f32 *count = (f32 *)(self + 0x30);

    count[0] = count[3] + count[4] * random_float();
    bone_sparks_emit((s32)self);
    return 0;
}

u8 *flame_spawn(u8 *arg0, u8 *arg1, s16 arg2, u8 arg3, u8 *arg4, f32 arg5, f32 arg6, f32 arg7, u8 arg8, u8 arg9,
                  u8 argA, s32 argB, u8 argC, s16 argD, s16 argE, s32 argF, u8 arg10, s32 arg11);
void *attach_fx_spawn(void *arg0, void *arg1, s32 arg2, u8 arg3, s32 arg4);

// bone_sparks_emit: while the emitter's counter (self + 0x30) is above 1, emits one spark per unit (if the live
// count +0x20 is below the limit +0x5C): a random attachment point of set +0x78 (g_attach_fx_assets / g_attach_fx_point_counts: 16-byte
// entries, bone index + offset) is transformed by the owner's (+0x10) bone matrix, a particle (kind 0x13 / 0x14) is
// spawned there and a follower (attach_fx_spawn) ties it to the bone. Owners without matrices or hidden (nibble 0xF)
// only drain the counter.
/* was func_1518FE50 */
void bone_sparks_emit(s32 arg0) {
    u8 *self = (u8 *)arg0;
    u8 *owner = *(u8 **)(self + 0x10);
    f32 *count = (f32 *)(self + 0x30);
    u8 *point;
    u8 *part;
    s32 set;
    s32 size;
    s32 kind;
    f32 at[3];
    f32 speed[2];
    struct {
        u8 *owner;      /* 0x00 */
        u8 owner_id;    /* 0x04 */
        f32 offset[3];  /* 0x08 */
        u8 bone;        /* 0x14 */
        s16 life;       /* 0x16 */
        u8 u18;
        u8 u19;
        u8 u1A;
        u8 *particle;   /* 0x1C */
        u8 *emitter;    /* 0x20 */
    } rec;

    if (!(1.0f < *count)) {
        return;
    }
    if (*(void **)(owner + 0x1D4) == NULL || (owner[0x74] & 0xF) == 0xF) {
        do {
            *count -= 1.0f;
        } while (1.0f < *count);
        return;
    }
    do {
        if (*(s16 *)(self + 0x20) < *(s32 *)(self + 0x5C)) {
            set = *(s32 *)(self + 0x78);
            point = (u8 *)g_attach_fx_assets[set] + ((u32)random_int() % (u16)g_attach_fx_point_counts[set]) * 16;
            speed[0] = random_float() * *(f32 *)(self + 0x4C) + *(f32 *)(self + 0x44);
            speed[1] = random_float() * *(f32 *)(self + 0x50) + *(f32 *)(self + 0x48);
            mtx_transform_point_or_origin(point + 4, at, *(u8 **)(owner + 0x1D4) + (point[0] << 6));
            size = random_int();
            kind = (random_int() & 1) ? 0x13 : 0x14;
            part = flame_spawn((u8 *)at, (u8 *)speed, -1, (u32)size % (self[0x55] + 1) + self[0x54], g_vec3_zero,
                                 0.0f, 1.0f, *(f32 *)(self + 0x80), 0, 0x23, 0, kind, 1, 1, 0xFF, 0, self[0xC],
                                 self[1]);
            if (part != NULL) {
                rec.owner = owner;
                rec.owner_id = owner[0x3B];
                rec.offset[0] = ((f32 *)(point + 4))[0];
                rec.offset[1] = ((f32 *)(point + 4))[1];
                rec.offset[2] = ((f32 *)(point + 4))[2];
                rec.bone = point[0];
                rec.life = (u32)random_int() % (*(s16 *)(self + 0x58) + 1) + *(s16 *)(self + 0x56);
                rec.u18 = 1;
                rec.u19 = (self[0x7C] & 1) ? 1 : 0;
                rec.u1A = 0;
                rec.emitter = self;
                rec.particle = part;
                attach_fx_spawn(&rec, at, 0, self[0xC], self[1]);
            }
        }
        *count -= 1.0f;
    } while (1.0f < *count);
}

/* was func_15190174 */
s32 bone_spark_follow_look(struct_eu_1BAAA0_d *arg0, struct_eu_vec3 *arg1) {
    struct_eu_1BAAA0_c *temp_a0 = arg0->unk2C;

    temp_a0->unk34 = *arg1;
    effect3d_look_follow(temp_a0, arg1, arg0);
    return 1;
}

/* was func_151901B4 */
s32 bone_spark_follow_look_up(struct_eu_1BAAA0_d *arg0, struct_eu_vec3 *arg1) {
    struct_eu_1BAAA0_c *temp_a0 = arg0->unk2C;

    temp_a0->unk34 = *arg1;
    effect3d_look_set_up(temp_a0, arg1, arg0);
    return 1;
}

// effect_node_launch: P219. Entry 0 of the effect-node handler table g_attach_child_end_fns, called by game_1FFF60's C
// (node, &pos) and (child, &child->unk34). node +0x2C = the particle, node +0x30 = its config (NULL: the particle is freed
// with node_destroy). Otherwise the particle gets velocity (target - node pos +0x34) * cfg +0x60 (+0x148..+0x150),
// +0x154 = random f32 * cfg +0x68 + cfg +0x64, +0x158 = cfg +0x6C, +0x6C / +0x6E = cfg s16 +0x70 / +0x72,
// +0x1C = random % (cfg s16 +0x76 + 1) + cfg s16 +0x74, +0x70 = 0x21 when cfg +0x7C bit 0 else 0x20, +0x71 = 0x24,
// +0x58 |= 0x08000001.
// target (a1): P231: a real vec3. P215 / P219 took the table for g_emitter2_path_fx_fns (emitter2_trail_update's, whose three entries
// emitter2_path_fx_quarter / CEE0 / CF08 take one argument) and added a PORT-only "aim at the node itself" fallback; the real
// callers pass the position, so the fallback is gone and both builds use the target.
// Returns s32 only for the table signature (the siblings bone_spark_follow_look / bone_spark_follow_look_up return s32); the dispatcher
// never reads v0. Path 2 returns the random int (the asm leaves it in v0), path 1 returns 0.
/* was func_151901F4 */
s32 bone_spark_release_toward(struct_eu_1BAAA0_d *arg0, struct_eu_vec3 *target) {
    u8 *node = (u8 *)arg0;
    u8 *p = *(u8 **)(node + 0x2C);
    u8 *cfg = *(u8 **)(node + 0x30);
    s32 r;

    if (cfg == NULL) {
        node_destroy((struct102 *)p);
        return 0;
    }
    *(f32 *)(p + 0x148) = (target->x - *(f32 *)(node + 0x34)) * *(f32 *)(cfg + 0x60);
    *(f32 *)(p + 0x14C) = (target->y - *(f32 *)(node + 0x38)) * *(f32 *)(cfg + 0x60);
    *(f32 *)(p + 0x150) = (target->z - *(f32 *)(node + 0x3C)) * *(f32 *)(cfg + 0x60);
    *(f32 *)(p + 0x154) = random_float() * *(f32 *)(cfg + 0x68) + *(f32 *)(cfg + 0x64);
    *(f32 *)(p + 0x158) = *(f32 *)(cfg + 0x6C);
    *(s16 *)(p + 0x6C) = *(s16 *)(cfg + 0x70);
    *(s16 *)(p + 0x6E) = *(s16 *)(cfg + 0x72);
    r = random_int();
    *(s16 *)(p + 0x1C) = (u32)r % (u32)(*(s16 *)(cfg + 0x76) + 1) + *(s16 *)(cfg + 0x74);
    p[0x70] = (cfg[0x7C] & 1) ? 0x21 : 0x20;
    p[0x71] = 0x24;
    *(s32 *)(p + 0x58) |= 0x08000001;
    return r;
}

/* was func_15190334 */
s32 bone_sparks_table_for_kind(s32 arg0, u8 *arg1, u8 arg2) {
    switch (((u8 *)arg0)[4]) {
    case 0x87:
    case 0xB0:
        *arg1 = 0xD;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0xB1:
        *arg1 = 0xE;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0xB4:
        *arg1 = 0xF;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x70:
    case 0xB2:
        *arg1 = 0x10;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x53:
        *arg1 = 0x11;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x96:
        *arg1 = 0x12;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
        *arg1 = 0;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x49:
        *arg1 = 0x1;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x58:
        *arg1 = 0x2;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x50:
        *arg1 = 0x3;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x5A:
    case 0x5F:
    case 0x74:
    case 0x75:
    case 0x7A:
        *arg1 = 0x4;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x80:
        *arg1 = 0x5;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x11:
    case 0x14:
    case 0x3B:
    case 0x98:
    case 0x99:
        *arg1 = 0x6;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x16:
        *arg1 = 0x7;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x88:
    case 0x90:
        *arg1 = 0x8;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x9C:
        *arg1 = 0x9;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x9D:
        *arg1 = 0xA;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x9F:
        *arg1 = 0xB;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0xA0:
        *arg1 = 0xC;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    }
    return 0;
}

extern s32 g_bone_sparks_kind_87; /* was D_800A7EDC */
extern s32 g_bone_sparks_kind_b1; /* was D_800A7EE0 */
extern s32 g_bone_sparks_kind_b4; /* was D_800A7EE4 */
extern s32 g_bone_sparks_kind_70; /* was D_800A7EE8 */
extern s32 g_bone_sparks_kind_53; /* was D_800A7EEC */
extern s32 g_bone_sparks_kind_96; /* was D_800A7EF0 */
extern s32 g_bone_sparks_kind_00; /* was D_800A7EA8 */
extern s32 g_bone_sparks_kind_49; /* was D_800A7EAC */
extern s32 g_bone_sparks_kind_58; /* was D_800A7EB0 */
extern s32 g_bone_sparks_kind_50; /* was D_800A7EB4 */
extern s32 g_bone_sparks_kind_75; /* was D_800A7EB8 */
extern s32 g_bone_sparks_kind_80; /* was D_800A7EBC */
extern s32 g_bone_sparks_kind_11; /* was D_800A7EC0 */
extern s32 g_bone_sparks_kind_16; /* was D_800A7EC4 */
extern s32 g_bone_sparks_kind_88; /* was D_800A7EC8 */
extern s32 g_bone_sparks_kind_9c; /* was D_800A7ECC */
extern s32 g_bone_sparks_kind_9d; /* was D_800A7ED0 */
extern s32 g_bone_sparks_kind_9f; /* was D_800A7ED4 */
extern s32 g_bone_sparks_kind_a0; /* was D_800A7ED8 */

/* was func_151905AC */
s32 *bone_sparks_presets_for_kind(u8 *arg0, s32 *arg1) {
    s32 *p;

    switch (arg0[4]) {
    case 0x87:
    case 0xB0:
        p = &g_bone_sparks_kind_87;
        *arg1 = 1;
        break;
    case 0xB1:
        p = &g_bone_sparks_kind_b1;
        *arg1 = 1;
        break;
    case 0xB4:
        p = &g_bone_sparks_kind_b4;
        *arg1 = 1;
        break;
    case 0x70:
    case 0xB2:
        p = &g_bone_sparks_kind_70;
        *arg1 = 1;
        break;
    case 0x53:
        p = &g_bone_sparks_kind_53;
        *arg1 = 1;
        break;
    case 0x96:
        p = &g_bone_sparks_kind_96;
        *arg1 = 1;
        break;
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
        p = &g_bone_sparks_kind_00;
        *arg1 = 1;
        break;
    case 0x49:
        p = &g_bone_sparks_kind_49;
        *arg1 = 1;
        break;
    case 0x58:
        p = &g_bone_sparks_kind_58;
        *arg1 = 1;
        break;
    case 0x50:
        p = &g_bone_sparks_kind_50;
        *arg1 = 1;
        break;
    case 0x75:
        p = &g_bone_sparks_kind_75;
        *arg1 = 1;
        break;
    case 0x80:
        p = &g_bone_sparks_kind_80;
        *arg1 = 1;
        break;
    case 0x11:
    case 0x14:
    case 0x3B:
    case 0x98:
    case 0x99:
        p = &g_bone_sparks_kind_11;
        *arg1 = 1;
        break;
    case 0x16:
        p = &g_bone_sparks_kind_16;
        *arg1 = 1;
        break;
    case 0x88:
    case 0x90:
        p = &g_bone_sparks_kind_88;
        *arg1 = 1;
        break;
    case 0x9C:
        p = &g_bone_sparks_kind_9c;
        *arg1 = 1;
        break;
    case 0x9D:
        p = &g_bone_sparks_kind_9d;
        *arg1 = 1;
        break;
    case 0x9F:
        p = &g_bone_sparks_kind_9f;
        *arg1 = 1;
        break;
    case 0xA0:
        p = &g_bone_sparks_kind_a0;
        *arg1 = 1;
        break;
    default:
        p = NULL;
        *arg1 = 0;
        break;
    }
    return p;
}

/* was func_1519078C */
struct225 *bone_sparks_light_create(s32 arg0, u8 *arg1, u8 arg2, s16 arg3, u8 arg4, s32 arg5) {
    s32 pad; // fakematch: frame slot above the header
    Header header;
    struct {
        u8 *p;
        u8 b;
    } src;
    f32 f[8];
    s32 tmp;
    Header2 header2;
    struct225 *temp_v0;

    if (arg2 >= 24) {
        return NULL;
    }
    tmp = arg0;
    f[0] = g_light_flicker_mid_levels[arg2];
    f[1] = g_light_flicker_low_levels[arg2];
    f[2] = g_light_flicker_high_levels[arg2];
    f[3] = 1.0f;
    f[5] = 5.0f;
    f[4] = 0.0f;
    f[7] = 0.0f;
    f[6] = 0.2489f;
    header.unk0 = ((arg3 == -1) ? 0 : 1) | 2;
    header.unk1 = 0x12;
    if (arg3 == -1) {
        header.unk2 = 300;
    } else {
        header.unk2 = arg3;
    }
    header.unk4 = 0x25;
    src.p = arg1;
    src.b = arg1[0x3B];
    header2.unk0 = *(f32 *)(arg1 + 0x14);
    header2.unk4 = *(f32 *)(arg1 + 0x18);
    header2.unk8 = *(f32 *)(arg1 + 0x1C);
    temp_v0 = light_create_with_ctrl(&header, &header2, 0, 0xFF, 0xD1, 0, 0xFF, 0, 0x30, arg4, arg5);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, 8);
        memcpy((u8 *)temp_v0 + 0x20, f, 0x20);
        memcpy((u8 *)temp_v0 + 0x40, &tmp, 4);
    }
    return temp_v0;
}

void light_flicker_intensity_step(u8 *arg0, u8 *arg1);
s32 light_follow_obj_pos(u8 *arg0, u8 *arg1);

// light_effect_update_18: handler 18 of D_8008B490 (P251): the dispatcher light_ctrl_update tests the result, which is
// light_follow_obj_pos's v0 left in place by the matched void C; s32 here (as light_beh_follow_obj), one signature for wasm
/* was func_15190940 */
s32 bone_sparks_light_update(u8 *arg0) {
    light_flicker_intensity_step(arg0, arg0 + 0x20);
    return light_follow_obj_pos(arg0, arg0 + 0x18);
}

/* was func_15190970 */
void bone_sparks_light_on_event(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;
    u8 temp_a2;
    u8 temp_a3;

    if (arg2 == 0) {
        temp_v0 = *(s32 *)(arg0 + 0x18);
        temp_v1 = *(s32 *)arg1;
        temp_a2 = arg0[0x1C];
        temp_a3 = arg1[4];
        if ((temp_v0 == temp_v1) || (temp_a2 == temp_a3)) {
            node_destroy(arg0);
        }
    }
}

/* was func_151909C4 */
void bone_sparks_light_unlink(struct_eu_1BAAA0 *arg0) {
    struct_eu_1BAAA0_b *temp_v0 = arg0->unk40;

    temp_v0->unk84 = 0;
}

/* was func_151909D4 */
void bone_sparks_light_retire(void *arg0) {
    bone_sparks_light_unlink(arg0);
    light_ctrl_retire(arg0);
}

/* was func_15190A00 */
void bone_sparks_light_free(void *arg0) {
    bone_sparks_light_unlink(arg0);
    light_ctrl_free(arg0);
}

// effect_node_release: P213: release handler of an effect node (entry of the g_emitter2_release_fns handler table, void (u8 *),
/* dispatched by spec_emitter_cleanup): frees the attached record +0x84 (node_destroy), then sfx_emitter_stop_by_callback(effect_sound_follow_owner,
 * node, word +0x10) (effect_sound_follow_owner is the node's sfx_emitter_start callback) and attach_fx_asset_release(word +0x78). */
void sfx_emitter_stop_by_callback(s32, s32, s32);
/* was func_15190A2C */
void bone_sparks_node_release(u8 *node) {
    if (*(u8 **)(node + 0x84) != NULL) {
        node_destroy(*(struct102 **)(node + 0x84));
    }
    sfx_emitter_stop_by_callback((s32)effect_sound_follow_owner, (s32)node, *(s32 *)(node + 0x10));
    attach_fx_asset_release(*(s32 *)(node + 0x30 + 0x48));
}

/* was func_15190A88 */
void bone_sparks_detach_owner(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    node_broadcast_type(0x3E, (s32)&tmp, 0x2A);
}

void attach_ctrl_free_if_owner(u8 *, s32, u8);
extern void (*g_bone_sparks_msg_fns[])(u8 *, s32, u8); /* was D_8008DA24 */
/* was func_15190AC0 */
void bone_sparks_on_message(u8 *arg0, s32 arg1, u8 arg2) {
    void (*f)(u8 *, s32, u8);
    if (arg2 == 0x2A) {
        attach_ctrl_free_if_owner(arg0, arg1, arg2);
    }
    f = g_bone_sparks_msg_fns[arg0[0x8A]];
    if (f != NULL) {
        f(arg0, arg1, arg2);
    }
}

s32 obj_send_hit();

typedef struct {
    s32 step;
    s32 acc;
    struct127 *obj;
} Tick0B2C;

typedef struct {
    u8 pad0[0x10];
    struct127 *unk10;
    u8 pad14[0x7C];
    Tick0B2C t;
} Obj0B2C;

/* was func_15190B2C */
s32 bone_sparks_tick_hurt(Obj0B2C *arg0) {
    Tick0B2C *t = &arg0->t;
    u8 *v;

    arg0->t.acc += g_frame_ticks;
    while (t->acc >= t->step) {
        obj_send_hit(arg0->unk10, 0x60021, 0, t->obj - g_objects);
        t->acc -= t->step;
    }
    v = *(u8 **)((u8 *)arg0->unk10 + 0x31C);
    if (v != NULL && v[0x84] == 0) {
        *(s16 *)(v + 0x46) = 1000;
    }
    return 1;
}

// bone_sparks_owner_release: g_bone_sparks_tick_fns [1] (bone_sparks_release's release handler, also reachable as a tick handler from
// bone_sparks_tick): clears byte +0x1AC of the owner's (+0x10) attachment +0x31C, if any. Returns that pointer (the asm
// leaves it in v0, and bone_sparks_tick returns a tick handler's v0), so the table has one signature s32 (u8 *).
/* was func_15190C34 */
s32 bone_sparks_owner_release(u8 *self) {
    u8 *att = *(u8 **)(*(u8 **)(self + 0x10) + 0x31C);

    if (att != NULL) {
        att[0x1AC] = 0;
    }
    return (s32)att;
}

/* was func_15190C50 */
void bone_sparks_on_model_swap(u8 *arg0, s32 *arg1, u8 arg2) {
    s32 *p = (s32 *)(arg0 + 0x90);
    if (arg2 == 0x2D) {
        if (arg1[0] == p[2]) {
            p[2] = arg1[1];
            return;
        }
        if (arg1[1] == p[2]) {
            p[2] = arg1[0];
        }
    }
}

/* was func_1519072C */
void object_effects_detach_all(u8 *arg0)
{
  u8 *sp20[2];
  s32 sp1C;
  sp1C = 1;
  sp20[0] = arg0;
 if (0) { }
  if (sp1C)
  {
    sp1C = (s32) sp20;
    ((u8 *) sp20)[4] = arg0[0x3B];
    attach_ctrl_broadcast(sp1C, 0x2A);
  }
  character_effect_broadcast(0xFFFFFFFFFFFFFFFF & sp1C, 0x49);
}

typedef struct { u8 *p; u8 b; } S190770;
s32 model_drip_broadcast(void *, s32);
u8 impact_current_kind();

/* was func_15190770 */
u8 *model_drip_create(u8 **arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *obj;
    S190770 s;
    u8 *q;

    s.p = *arg0;
    s.b = (*arg0)[0x3B];
    model_drip_broadcast(&s, 0xE);
    obj = node_alloc(0x20, arg3, arg1 + 0x300, 1, arg2, 1);
    if (obj == NULL) {
        return NULL;
    }
    memcpy(obj + 0x10, arg0, 0xC);
    q = obj + 0x30;
    *(u8 **)(obj + 0x24) = q;
    *(u8 **)(obj + 0x28) = obj + 0x300;
    *(s32 *)(obj + 0x20) = 0;
    *(f32 *)(obj + 0x1C) = 0.0f;
    bzero(q, 0x2D0);
    *(s8 *)(obj + 0x2C) = impact_current_kind();
    return obj;
}
