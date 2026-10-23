void func_15143794(s16, s16, f32, void *);
s32 func_15157E08(s8 *, f32 *, s32, f32, s32, s32, s32, s32, s32);

// base + rand % (extra + 1) (func_150ADA20, unsigned remainder)
#define RAND_SPREAD(base, extra) ((u32) func_150ADA20() % (u32) ((extra) + 1) + (base))

// particle_burst_from_spec_b: as particle_burst_from_spec (func_151530A8) for the second spec layout: base +
// rand % (extra + 1) particles (func_15157E08, kind spec +0x3C, size base + rand x range) at the spec's point,
// each with a random life, three random angles (0..360), a random scalar, a random direction (func_15143794),
// three random colour scalars and one more random scalar; flags / colours / the rest are copied once.
// arg1 / arg2 go to func_15157E08. The result is unused by its caller (game_eu_1C13E0).
s32 func_15152A90(s32 *arg0, u8 arg1, s32 arg2) {
    typedef struct {
        s32 countBase;      /* 0x00 */
        s32 countExtra;     /* 0x04 */
        s32 pos[3];         /* 0x08 */
        s16 angXBase;       /* 0x14 */
        s16 angXExtra;      /* 0x16 */
        s16 angYBase;       /* 0x18 */
        s16 angYExtra;      /* 0x1A */
        f32 lenBase;        /* 0x1C */
        f32 lenRange;       /* 0x20 */
        f32 u24;            /* 0x24 */
        f32 u28Base;        /* 0x28 */
        f32 u28Range;       /* 0x2C */
        s16 lifeBase;       /* 0x30 */
        s16 lifeExtra;      /* 0x32 */
        s32 u34;            /* 0x34 */
        s32 u38;            /* 0x38 */
        s32 kind;           /* 0x3C */
        f32 sizeBase;       /* 0x40 */
        f32 sizeRange;      /* 0x44 */
        f32 u48Base;        /* 0x48 */
        f32 u48Range;       /* 0x4C */
        f32 colBase[3];     /* 0x50 */
        f32 colRange[3];    /* 0x5C */
        u8 colA[4];         /* 0x68 */
        u8 colB[4];         /* 0x6C */
        u8 flags;           /* 0x70 */
        u8 u71;             /* 0x71 */
        s16 u72;            /* 0x72 */
        s16 u74;            /* 0x74 */
    } BurstSpecB;
    struct {
        f32 ang[3];         /* 0x00 */
        f32 u0C;            /* 0x0C */
        f32 dir[3];         /* 0x10, func_15143794 */
        f32 col[3];         /* 0x1C */
        f32 u28;            /* 0x28 */
        f32 u2C;            /* 0x2C */
        u8 u30;             /* 0x30 */
    } part;
    struct {
        u8 flags;           /* 0x00 */
        u8 u01;             /* 0x01 = 0 */
        u8 u02;             /* 0x02 = 1 */
        s8 u03;             /* 0x03 = -1 */
        s8 u04;             /* 0x04 = -1 */
        s16 life;           /* 0x06 */
        s32 u08;            /* 0x08 */
        s32 u0C;            /* 0x0C */
        s32 u10;            /* 0x10 = 0 */
        s32 u14;            /* 0x14 = 0x220405 */
        s32 u18;            /* 0x18 = 0x40200 */
        s32 u1C;            /* 0x1C = 1 */
        s32 u20;            /* 0x20 = 0x38 */
        s32 u24;            /* 0x24 = 0x80 */
        s32 u28;            /* 0x28 = 0x20 */
        u8 u2C;             /* 0x2C = 0 */
        u8 u2D;             /* 0x2D = 8 */
        u8 pad2E[2];
        u8 colA[4];         /* 0x30 */
        u8 colB[4];         /* 0x34 */
        u8 u38;             /* 0x38 = 0 */
        s32 u3C;            /* 0x3C = 0 */
        u8 u40;             /* 0x40 = 0 */
        u8 u41;             /* 0x41 = 2 */
        s32 pos[3];         /* 0x44 */
        u8 pad50[4];
        s16 u54;            /* 0x54 */
        s16 u56;            /* 0x56 */
    } blk;
    BurstSpecB *sp = (BurstSpecB *) arg0;
    u32 count;
    u32 ra;
    u32 rb;
    f32 len;
    f32 size;
    s32 i;

    blk.u38 = 0;
    blk.flags = sp->flags | 2;
    blk.u01 = 0;
    blk.u02 = 1;
    blk.u03 = -1;
    blk.u04 = -1;
    blk.u08 = sp->u34;
    blk.u0C = sp->u38;
    blk.u10 = 0;
    blk.u14 = 0x220405;
    blk.u18 = 0x40200;
    blk.u1C = 1;
    blk.u20 = 0x38;
    blk.u24 = 0x80;
    blk.u28 = 0x20;
    blk.u2C = 0;
    blk.u2D = 8;
    blk.u3C = 0;
    blk.u40 = 0;
    blk.u41 = 2;
    blk.pos[0] = sp->pos[0];
    blk.pos[1] = sp->pos[1];
    blk.pos[2] = sp->pos[2];
    part.u2C = sp->u24;
    for (i = 0; i < 4; i++) {
        blk.colA[i] = sp->colA[i];
        blk.colB[i] = sp->colB[i];
    }
    blk.u54 = sp->u72;
    blk.u56 = sp->u74;
    part.u30 = sp->u71;
    count = RAND_SPREAD(sp->countBase, sp->countExtra);
    for (; count != 0; count--) {
        blk.life = RAND_SPREAD(sp->lifeBase, sp->lifeExtra);
        part.ang[0] = func_150ADA68() * 360.0f;
        part.ang[1] = func_150ADA68() * 360.0f;
        part.ang[2] = func_150ADA68() * 360.0f;
        part.u0C = func_150ADA68() * sp->u48Range + sp->u48Base;
        ra = func_150ADA20();
        rb = func_150ADA20();
        len = func_150ADA68() * sp->lenRange + sp->lenBase;
        func_15143794(ra % (u32) (sp->angXExtra + 1) + sp->angXBase, rb % (u32) (sp->angYExtra + 1) + sp->angYBase,
                      len, part.dir);
        for (i = 0; i < 3; i++) {
            part.col[i] = func_150ADA68() * sp->colRange[i] + sp->colBase[i];
        }
        part.u28 = func_150ADA68() * sp->u28Range + sp->u28Base;
        size = func_150ADA68() * sp->sizeRange + sp->sizeBase;
        func_15157E08((s8 *) &blk, (f32 *) &part, sp->kind, size, 0, 0, 0, arg1, arg2);
    }
    return 0;
}
#undef RAND_SPREAD
