s32 func_1513F680(u8 *, s32, s32, s32, s32);
s32 memcpy(s32, f32 *, s32);
void func_1504715C(void *, u8 *);
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

/* drip_emitter_update: P186: update handler (D_8008B848 entry +0) of a drip emitter e (rain drops hanging off an
 * owner model e +0x10, config D_8008FE10[e[0x1A]], slots e +0x24, live count e +0x20, accumulator f32 e +0x1C).
 * Kills itself (func_1516972C) when its timer s16 e +0x16 runs out (flag e[0x18] & 1), the owner is gone or has
 * another id (e[0x14] vs owner[0x3B]), or the owner has no matrices (+0x1D4; then it first starts the ending
 * effect func_151491F4 with e +0x10..+0x1B copied to its +0x28). Hanging drops follow their point on the owner
 * (func_15143134 with the owner matrix), and once their timer is over they fall (velocity from the last move *
 * D_800BEDC8, func_1513F680, life from D_800AA120). The accumulator gains rate * dt; for every whole unit a free slot
 * is picked at random and, when the point is below the owner's +0x118 height limit, a drop object is created
 * (func_1513D524 with a 0x60-byte motion block at +0x110) and given a hang time. */
void func_15190E08(u8 *e) {
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
        u8 owner[0x24]; /* +0x38 func_1504715C */
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
            drop = (e[0x18] & 1) ? (u8 *) func_151491F4(*(s16 *) (e + 0x16), -1, 13, 1, 8, 12, 255, 0)
                                 : (u8 *) func_151491F4(300, -1, 13, 0, 8, 12, 255, 0);
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
                    func_15143134(cfg->points + i * 0x10, obj + 0x34,
                                  *(u8 **) (*(u8 **) (e + 0x10) + 0x1D4) + cfg->points[i * 0x10 + 0xC] * 0x40);
                    slot->timer -= D_800BE9E4;
                    if (slot->timer < 0) {
                        obj = slot->obj;
                        *(f32 *) (obj + 0x114) = 0.0f;
                        *(f32 *) (obj + 0x110) = (*(f32 *) (obj + 0x34) - *(f32 *) (obj + 0x40)) * D_800BEDC8;
                        *(f32 *) (obj + 0x118) = (*(f32 *) (obj + 0x3C) - *(f32 *) (obj + 0x48)) * D_800BEDC8;
                        r = &D_800AA120[obj[0x130]];
                        func_1513F680(obj, 13, 18, 0, 13);
                        *(s16 *) (obj + 0x1C) = (u32) func_150ADA20() % (u32) (r->range + 1) + r->base;
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
                    func_1504715C(blk.owner, *(u8 **) (e + 0x10));
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
                        k = (u32) func_150ADA20() % (u32) n;
                        while (k-- != 0) {
                            tail = head;
                            head = head->next;
                        }
                        idx = head - slots;
                        spawn.b44 = (u32) func_150ADA20() % 101 + 100;
                        spawn.f14 = 0.0f;
                        spawn.f18 = 0.0f;
                        blk.rng[0] = src[0];
                        blk.rng[1] = src[1];
                        blk.rng[2] = src[2];
                        blk.rng[3] = src[3];
                        blk.b23 = (u32) func_150ADA20() % 5 + 4;
                        blk.b24 = (u32) func_150ADA20() % 5 + 4;
                        func_15143134(cfg->points + idx * 0x10, spawn.pos,
                                      *(u8 **) (*(u8 **) (e + 0x10) + 0x1D4) + cfg->points[idx * 0x10 + 0xC] * 0x40);
                        spawn.pos2[0] = spawn.pos[0];
                        spawn.pos2[1] = spawn.pos[1];
                        spawn.pos2[2] = spawn.pos[2];
                        if (*(f32 *) (*(u8 **) (e + 0x10) + 0x118) <
                            spawn.pos[1] - *(f32 *) &blk.rng[1] - *(f32 *) &blk.rng[3]) {
                            func_150ADA20();
                            drop = (u8 *) func_1513D524((s32) &spawn, 12, 0, 0, 13, D_800AB7E4[e[0x2C]] ? 0 : 2, 96, 255, 0);
                            head->obj = drop;
                            if (drop != NULL) {
                                memcpy((s32) (drop + 0x110), (f32 *) &blk, 0x60);
                                head->timer = (u32) func_150ADA20() % (u32) (cfg->range + 1) + cfg->base;
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
        func_1516972C((struct102 *) e);
    }
}
