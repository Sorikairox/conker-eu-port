void func_15143794(s16, s16, f32, void *);
s32 allocate_memory(s32, s32, s32, s32);
s32 func_15132BBC(void *, s32, s32, s32, s32, s32, s32);
s32 memcpy(s32, f32 *, s32);

// base + rand % (extra + 1) (func_150ADA20, unsigned remainder)
#define RAND_SPREAD(base, extra) ((u32) func_150ADA20() % (u32) ((extra) + 1) + (base))

// debris_burst_spawn: spawns base + rand % (extra + 1) pieces (at most n) of the n kinds ids[] / scales[]; each
// piece takes a random kind not used yet in this burst (a temporary n-byte used map from allocate_memory), at the
// spec's point plus a random offset (func_15143794 with length arg10) moving in a random direction, with random
// spins, sway, life and size (scales[k] x random), solid (+0x50 bit 0, +0x61 = 0xD, +0x63 = spec +0x40) with
// chance spec +0x3C; effect kind 3 via func_15132BBC (arg9, extra bytes arg5 copied from arg4 to +0x170, arg13 /
// arg14). Option bits: arg7 -> 0x80, arg11 -> 0x4000, arg12 -> 0x100000. The result is unused by all callers.
void func_15150D7C(s32 *arg0, s32 *ids, s32 *scales, s32 n, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9, f32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    typedef struct {
        s32 countBase;      /* 0x00 */
        s32 countExtra;     /* 0x04 */
        f32 pos[3];         /* 0x08 */
        s16 angXBase;       /* 0x14 */
        s16 angXExtra;      /* 0x16 */
        s16 angYBase;       /* 0x18 */
        s16 angYExtra;      /* 0x1A */
        f32 speedBase;      /* 0x1C */
        f32 speedRange;     /* 0x20 */
        f32 u24Base;        /* 0x24 */
        f32 u24Range;       /* 0x28 */
        s16 lifeBase;       /* 0x2C */
        s16 lifeExtra;      /* 0x2E */
        f32 sizeBase;       /* 0x30 */
        f32 sizeRange;      /* 0x34 */
        f32 sway;           /* 0x38 */
        f32 solidChance;    /* 0x3C */
        u8 solidKind;       /* 0x40 */
    } DebrisSpec;
    struct {
        f32 u00;            /* 0x00 = 1 */
        f32 u04;            /* 0x04 = 0.5610 */
        f32 size[2];        /* 0x08 */
        f32 spin[3];        /* 0x10 */
        f32 u1C[3];         /* 0x1C = 1 */
        f32 pos[3];         /* 0x28 */
        f32 vel[3];         /* 0x34 */
        f32 swayX;          /* 0x40 */
        f32 u44;            /* 0x44 = 0 */
        f32 swayZ;          /* 0x48 */
        f32 u4C;            /* 0x4C */
        u32 flags;          /* 0x50 */
        s16 life;           /* 0x54 */
        s16 id;             /* 0x56 */
        u8 u58;             /* 0x58 = arg6 */
        s32 u5C;            /* 0x5C = 0 */
        u8 u60;             /* 0x60 = 0xFF */
        u8 u61;             /* 0x61 = 8 / 0xD */
        u8 u62;             /* 0x62 = 0 */
        u8 u63;             /* 0x63 */
        u8 u64[4];          /* 0x64 = 0 */
        u8 u68;             /* 0x68 = 2 */
        s8 u69;             /* 0x69 = arg8 */
        u8 u6A;             /* 0x6A = 0 */
        s32 u6C;            /* 0x6C = 0 */
        u8 u70;             /* 0x70 = 0 */
        s16 u72;            /* 0x72 = 0xC */
        s16 u74;            /* 0x74 = 0x15 */
    } fx;
    DebrisSpec *sp = (DebrisSpec *) arg0;
    u8 *used;
    u8 *p;
    s32 count;
    s32 left;
    s32 i;
    u32 r;
    s16 a;
    s16 b;
    u8 *e;

    used = (u8 *) allocate_memory(n, 2, 2, 1);
    if (used == NULL) {
        return;
    }
    for (i = 0; i < n; i++) {
        used[i] = 0;
    }
    left = n;
    fx.u00 = 1.0f;
    fx.u1C[0] = 1.0f;
    fx.u1C[1] = 1.0f;
    fx.u1C[2] = 1.0f;
    fx.u04 = 0.561000049f;
    fx.u44 = 0.0f;
    fx.flags = 0x13968 | ((u8) arg12 ? 0x100000 : 0) | ((u8) arg7 ? 0x80 : 0) | ((u8) arg11 ? 0x4000 : 0);
    count = RAND_SPREAD(sp->countBase, sp->countExtra);
    if (n < count) {
        count = n;
    }
    fx.u58 = arg6;
    fx.u5C = 0;
    fx.u60 = 0xFF;
    fx.u62 = 0;
    fx.u64[0] = 0;
    fx.u64[1] = 0;
    fx.u64[2] = 0;
    fx.u64[3] = 0;
    fx.u68 = 2;
    fx.u6A = 0;
    fx.u6C = 0;
    fx.u70 = 0;
    fx.u72 = 0xC;
    fx.u74 = 0x15;
    fx.u69 = arg8;
    for (; count != 0; count--) {
        a = RAND_SPREAD(sp->angXBase, sp->angXExtra);
        b = RAND_SPREAD(sp->angYBase, sp->angYExtra);
        func_15143794(a, b, func_150ADA68() * sp->speedRange + sp->speedBase, fx.vel);
        func_15143794(a, b, arg10, fx.pos);
        fx.pos[0] += sp->pos[0];
        fx.pos[1] += sp->pos[1];
        fx.pos[2] += sp->pos[2];
        fx.spin[0] = func_150ADA68() * 360.0f;
        fx.spin[1] = func_150ADA68() * 360.0f;
        fx.spin[2] = func_150ADA68() * 360.0f;
        fx.swayX = func_150ADA68() * (sp->sway + sp->sway) - sp->sway;
        fx.swayZ = func_150ADA68() * (sp->sway + sp->sway) - sp->sway;
        fx.u4C = func_150ADA68() * sp->u24Range + sp->u24Base;
        fx.life = RAND_SPREAD(sp->lifeBase, sp->lifeExtra);
        /* the r-th unused kind, counting round from 0 */
        r = (u32) func_150ADA20() % (u32) left;
        i = 0;
        p = used;
        for (;;) {
            while (*p != 0) {
                i++;
                p++;
            }
            if (r == 0) {
                break;
            }
            i++;
            r--;
            p++;
            if (i >= n) {
                i = 0;
                p = used;
            }
        }
        fx.id = ids[i];
        fx.size[1] = ((f32 *) scales)[i] * (sp->sizeBase + func_150ADA68() * sp->sizeRange);
        left--;
        fx.size[0] = fx.size[1];
        *p = 1;
        if (func_150ADA68() < sp->solidChance) {
            fx.flags |= 1;
            fx.u61 = 0xD;
            fx.u63 = sp->solidKind;
        } else {
            fx.flags &= ~1;
            fx.u63 = 0;
            fx.u61 = 8;
        }
        e = (u8 *) func_15132BBC(&fx, 3, 0xFF, arg9, arg5, (u8) arg13, arg14);
        if (arg4 != 0 && e != NULL) {
            memcpy((s32) (e + 0x170), (f32 *) arg4, arg5);
        }
    }
    return;
}
#undef RAND_SPREAD
