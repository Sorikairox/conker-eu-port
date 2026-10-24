/* P197 */
/* character_effect_update: P197: update handler of the kind-0x21 character effect records that func_1518D1C0
 * (character_effect_attach) creates through func_1518E934 (fire, smoke, impacts ... on a model). See below. */
void func_15143134(void *arg0, void *arg1, void *arg2);
void func_1513F680(u8 *, u8, u8, u8, u8);
void func_1518E878(u8 *);
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
    u8 kind, b39, b3A;  /* +0x38 func_1513D524 arguments */
    u8 end[4];          /* +0x3B func_1513F680 arguments at release */
    u8 init;            /* +0x3F D_8008D9C0 index (spawn record initialiser) */
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
    s8 onEnd;           /* +0x21 D_8008D9C8 handler at the end of the time, -1 = remove */
    u8 effect;          /* +0x22 D_8008D980 index */
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

extern CharFxSet *D_8008D980[];
extern void (*D_8008D9C0[])(u8 *, u8 *, u8 *, u8 *, u8 *, u8 *, s16 *);
extern s32 (*D_8008D9C8[])(u8 *);

/* character_effect_update: per-frame handler (object type entry at D_8008BEFC) of a kind-0x21 character effect e
 * (func_1518D1C0 / func_1518E934), a particle emitter tied to the owner model e->owner. When e is not running it only
 * frees its particles (func_1518E878, mode 1). It removes itself (func_1516972C) when the owner is gone or has
 * another id, or when its time (e +0x1E, bit 0 of e +0x20) runs out (then the D_8008D9C8[onEnd] handler decides).
 * When the owner is hidden for this view (owner +0x74 bit D_80082FA4) the particles are freed. Otherwise the row of
 * D_8008D980[effect] for the owner's variant (+0x1C8) is picked: with matrices (+0x1D4) and a visible model
 * (+0x74 & 0xF != 0xF) the row whose id list holds owner +0x84 (else the default row), mode 4; without, the hidden
 * row (mode 2) at the owner position + yoff. A row / mode change restarts the effect (accumulator = max).
 * Live particles follow their model point (func_15143134) or the effect position + their offset; when their hold
 * time is over they are let go: velocity from the last move * D_800BEDC8 (x / z clamped to +-10), func_1513F680
 * with the template's end arguments, a life time. The accumulator gains rate per frame; for every whole unit a free
 * slot is picked at random and a particle record is spawned (D_8008D9C0[tpl->init] fills the spawn block,
 * func_1513D524, the 0x58-byte motion block to +0x110) at a model point or at the effect position + a random
 * sphere (shape 1) / ring (shape 2) offset. */
void func_1518DC50(u8 *arg0) {
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
            func_1518E878(arg0);
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
            e->time -= D_800BE9E4;
            if (e->time < 0) {
                if (e->onEnd == -1) {
                    kill = 1;
                } else {
                    kill = D_8008D9C8[e->onEnd](arg0);
                }
            }
        }
        owner = e->owner;
        vis = owner[0x74];
        if (vis & (1 << D_80082FA4)) {
            /* hidden in this view */
            if (!(e->mode & 1)) {
                func_1518E878(arg0);
                e->mode |= 1;
            }
        } else {
            fresh = 0;
            set = D_8008D980[e->effect];
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
                func_1518E878(arg0);
                fresh = 1;
                e->accum = (f32) cfg->max;
            }
            if (mode == 2) {
                owner = e->owner;
                e->pos[0] = *(f32 *) (owner + 0x14);
                e->pos[1] = *(f32 *) (owner + 0x18) + cfg->yoff;
                e->pos[2] = *(f32 *) (owner + 0x1C);
            } else if (cfg->attach == 2) {
                func_150A7E40((f32(*)[4]) (*(u8 **) (e->owner + 0x1D4) + cfg->matrix * 0x40), cfg->local[0],
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
                        func_15143134(pt, slot->obj + 0x34,
                                      *(u8 **) (e->owner + 0x1D4) + *(s16 *) (pt + 0xC) * 0x40);
                    }
                    slot->timer -= D_800BE9E4;
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
                        func_1513F680(slot->obj, m->tpl->end[0], m->tpl->end[1], m->tpl->end[2], m->tpl->end[3]);
                        k = func_150ADA20();
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
                            k = (u32) func_150ADA20() % (u32) (nfree + 1);
                            while (k-- != 0) {
                                tail = head;
                                head = head->next;
                            }
                            D_8008D9C0[tpl->init]((u8 *) &spawn, &b, &spawn.b10, &spawn.b11, &spawn.b12, &spawn.b13,
                                                  &spawn.flags);
                            rec = (u8 *) func_1513D524((s32) &spawn, tpl->kind, tpl->b39, 0, tpl->b3A, b, 0x58, 255, 0);
                            head->obj = rec;
                            if (rec != NULL) {
                                memcpy(rec + 0x110, (u8 **) &blk, 0x58);
                                *(s32 *) (head->obj + 0x58) |= 0x40000000;
                                if (cfg->attach == 2 || mode == 2) {
                                    switch (cfg->shape) {
                                    case 1: /* sphere */
                                        a = func_150ADA20();
                                        c = func_150ADA20();
                                        r = func_150ADA68() * cfg->radius;
                                        cb = func_151423D8((u8) (c - 0x40));
                                        sb = func_151423D8(c);
                                        ca = func_151423D8((u8) (a - 0x40));
                                        sa = func_151423D8(a);
                                        head->off[0] = r * sb * ca;
                                        head->off[1] = -r * cb;
                                        head->off[2] = r * sb * sa;
                                        break;
                                    case 2: /* ring */
                                        a = func_150ADA20();
                                        r = func_150ADA68() * cfg->radius;
                                        head->off[0] = func_151423D8(a) * r;
                                        head->off[1] = func_150ADA68() * cfg->height;
                                        head->off[2] = -func_151423D8((u8) (a - 0x40)) * r;
                                        break;
                                    }
                                    *(f32 *) (head->obj + 0x34) = e->pos[0] + head->off[0];
                                    *(f32 *) (head->obj + 0x38) = e->pos[1] + head->off[1];
                                    *(f32 *) (head->obj + 0x3C) = e->pos[2] + head->off[2];
                                } else {
                                    idx = head - e->slots;
                                    pt = cfg->points + idx * 0x10;
                                    func_15143134(pt, head->obj + 0x34,
                                                  *(u8 **) (e->owner + 0x1D4) + *(s16 *) (pt + 0xC) * 0x40);
                                }
                                obj = head->obj;
                                *(f32 *) (obj + 0x40) = *(f32 *) (obj + 0x34);
                                *(f32 *) (obj + 0x44) = *(f32 *) (obj + 0x38);
                                *(f32 *) (obj + 0x48) = *(f32 *) (obj + 0x3C);
                                head->timer = (u32) func_150ADA20() % (u32) (cfg->range + 1) + cfg->base;
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
        func_1516972C((struct102 *) arg0);
    }
}
