void func_15143794(s16, s16, f32, void *);
void *func_1515C2F0(s32 *, s32, void *, s32, u8, s32);

// base + rand % (extra + 1) (func_150ADA20, unsigned remainder)
#define RAND_SPREAD(base, extra) ((u32) func_150ADA20() % (u32) ((extra) + 1) + (base))

// particle_burst_from_spec: spawns base + rand % (extra + 1) particles (func_1515C2F0) at the spec's point; each
// one gets random life / flag byte, two random scalars, a random direction (func_15143794: two s16 angles and a
// length, each base + random) and two random 4-byte colours; the rest of the 0x3C-byte particle block is copied
// from the spec once. arg1 / arg2 go to func_1515C2F0 (owner byte, extra word). The result is unused by all callers.
void func_151530A8(s32 *arg0, u8 arg1, s32 arg2) {
    typedef struct {
        s32 countBase;      /* 0x00 */
        s32 countExtra;     /* 0x04 */
        s32 pos[3];         /* 0x08 */
        f32 aBase;          /* 0x14 */
        f32 aRange;         /* 0x18 */
        f32 bBase;          /* 0x1C */
        f32 bRange;         /* 0x20 */
        f32 lenBase;        /* 0x24 */
        f32 lenRange;       /* 0x28 */
        s16 angXBase;       /* 0x2C */
        s16 angXExtra;      /* 0x2E */
        s16 angYBase;       /* 0x30 */
        s16 angYExtra;      /* 0x32 */
        s32 flagBase;       /* 0x34 */
        s32 flagExtra;      /* 0x38 */
        s16 lifeBase;       /* 0x3C */
        s16 lifeExtra;      /* 0x3E */
        u16 u40;            /* 0x40 */
        u8 u42[3];          /* 0x42 */
        u8 colABase[4];     /* 0x45 */
        u8 colAExtra[4];    /* 0x49 */
        u8 colBBase[4];     /* 0x4D */
        u8 colBExtra[4];    /* 0x51 */
        u8 u55Base;         /* 0x55 */
        u8 u55Extra;        /* 0x56 */
        u8 u57[2];          /* 0x57 */
        s32 u5C;            /* 0x5C */
        s32 u60;            /* 0x60 */
        s16 u64;            /* 0x64 */
        s16 u66;            /* 0x66 */
        s16 u68;            /* 0x68 */
        u8 u6A;             /* 0x6A */
        f32 u6C;            /* 0x6C */
        s8 u70;             /* 0x70 */
        s8 u71;             /* 0x71 */
    } BurstSpec;
    struct {
        f32 a;              /* 0x00 */
        f32 dir[3];         /* 0x04, func_15143794 */
        f32 b;              /* 0x10 */
        u8 u14[3];          /* 0x14 */
        u8 colA[4];         /* 0x17 */
        u8 colB[4];         /* 0x1B */
        u8 u1F;             /* 0x1F */
        u8 u20[2];          /* 0x20 */
        s32 u24;            /* 0x24 */
        s32 u28;            /* 0x28 */
        s16 u2C;            /* 0x2C */
        s16 u2E;            /* 0x2E */
        s16 u30;            /* 0x30 */
        u8 u32;             /* 0x32 */
        f32 u34;            /* 0x34 */
        s8 u38;             /* 0x38 */
        s8 u39;             /* 0x39 */
    } part;                 /* 0x3C bytes, copied by func_1515C2F0 */
    struct {
        s32 pos[3];         /* 0x00 */
        s16 life;           /* 0x0C */
        u16 u0E;            /* 0x0E */
        s32 u10;            /* 0x10, func_1515C2F0 also sets 10 */
        u8 pad14;
        u8 flag;            /* 0x15 */
    } spawn;
    BurstSpec *sp = (BurstSpec *) arg0;
    u32 count;
    u32 ra;
    u32 rb;
    f32 len;
    s32 i;

    count = RAND_SPREAD(sp->countBase, sp->countExtra);
    spawn.pos[0] = sp->pos[0];
    spawn.pos[1] = sp->pos[1];
    spawn.pos[2] = sp->pos[2];
    spawn.u10 = 10;
    spawn.u0E = sp->u40;
    part.u14[0] = sp->u42[0];
    part.u14[1] = sp->u42[1];
    part.u14[2] = sp->u42[2];
    part.u20[0] = sp->u57[0];
    part.u20[1] = sp->u57[1];
    part.u24 = sp->u5C;
    part.u28 = sp->u60;
    part.u2C = sp->u64;
    part.u2E = sp->u66;
    part.u38 = sp->u70;
    part.u39 = sp->u71;
    part.u30 = sp->u68;
    part.u32 = sp->u6A;
    part.u34 = sp->u6C;
    for (; count != 0; count--) {
        spawn.flag = RAND_SPREAD(sp->flagBase, sp->flagExtra);
        spawn.life = RAND_SPREAD(sp->lifeBase, sp->lifeExtra);
        part.a = func_150ADA68() * sp->aRange + sp->aBase;
        part.b = func_150ADA68() * sp->bRange + sp->bBase;
        ra = func_150ADA20();
        rb = func_150ADA20();
        len = func_150ADA68() * sp->lenRange + sp->lenBase;
        func_15143794(ra % (u32) (sp->angXExtra + 1) + sp->angXBase, rb % (u32) (sp->angYExtra + 1) + sp->angYBase,
                      len, part.dir);
        for (i = 0; i < 4; i++) {
            part.colA[i] = RAND_SPREAD(sp->colABase[i], sp->colAExtra[i]);
        }
        for (i = 0; i < 4; i++) {
            part.colB[i] = RAND_SPREAD(sp->colBBase[i], sp->colBExtra[i]);
        }
        part.u1F = RAND_SPREAD(sp->u55Base, sp->u55Extra);
        func_1515C2F0(spawn.pos, 0, &part, 0, arg1, arg2);
    }
    return;
}
#undef RAND_SPREAD
