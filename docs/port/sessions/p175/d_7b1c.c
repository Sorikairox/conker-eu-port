void func_1510F800(s32);
s32 func_1516284C(void *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15145128(f32 *, f32 *, s32 *, s32 *);
void func_151C9748(u8 **out, f32 *pos, u8 *tri, f32 *dir, s32 ground, u8 alt, u8 noshadow, u8 arg7, s32 arg8);
u8 *func_151C957C(u8 *rec, f32 *from, f32 *to, u8 r, u8 g, u8 b, s32 ground, u8 noshadow, u8 arg8, s32 arg9);
s32 func_151C8D5C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6);
s32 memcpy(s32, u8 *, s32);

/* The beam's emitter block (0xA0 bytes, copied to the beam record +0x110; read by func_151C8880 / func_151C8448). */
typedef struct {
    f32 u00[4];      /* 0x00: random sizes */
    f32 u10[2];      /* 0x10 */
    f32 phase[2];    /* 0x18: random 0..2pi */
    f32 rate[2];     /* 0x20: random 0.05..0.13 */
    u8 *owner2;      /* 0x28: arg5 */
    s32 sound;       /* 0x2C: func_1516284C handle or 0 */
    u8 pad30[4];     /* 0x30: never written */
    u8 *glowA;       /* 0x34: written in the record after the copy */
    u8 *glowB;       /* 0x38 */
    u8 *pieceA[3];   /* 0x3C: func_151C9748 at end A */
    u8 *pieceB[3];   /* 0x48: at end B */
    f32 u54;         /* 0x54 = 0 */
    u8 u58;          /* 0x58 = 0 */
    u8 pad59;
    u8 triA[0x12];   /* 0x5A: hit triangle A */
    u8 triB[0x12];   /* 0x6C: hit triangle B */
    s16 len[3];      /* 0x7E: args 10..12 */
    s16 len01;       /* 0x84: arg10 + arg11 */
    u8 opt;          /* 0x86: option bits */
    u8 pad87;
    u8 *owner;       /* 0x88: arg4 (the level record) */
    s32 groundA;     /* 0x8C */
    s32 groundB;     /* 0x90 */
    u8 u94;          /* 0x94: arg17 */
    f32 u98;         /* 0x98: arg19 */
    f32 u9C;         /* 0x9C: arg20 */
} BeamEmit;

/* The beam record's spawn block (func_1513D4B8 argument 0, 0x58 bytes, as func_151407D0's). */
typedef struct {
    u8 kind;         /* 0x00 = 0x59 */
    u8 u01;          /* 0x01 = 6 */
    u16 flags;       /* 0x02 = 0x5A03 */
    u16 life;        /* 0x04 = 300 */
    u8 pad06[2];
    s32 u08;         /* 0x08 = 0 */
    s32 u0C;         /* 0x0C = 0 */
    u8 rgba[4];      /* 0x10 */
    f32 size[2];     /* 0x14 = 0, 20 */
    f32 from[3];     /* 0x1C: end A */
    f32 to[3];       /* 0x28: end B */
    f32 d[3];        /* 0x34: B - A */
    s32 u40;         /* 0x40 */
    u8 u44[4];       /* 0x44 = FF, FF, 0, 6 */
    u8 pad48[0x10];
} BeamSpawn;

// beam_create: builds a beam between two geometry hits (func_151C7750, record_beam_start). Needs a ground id at
/* both ends (func_1510FD20). Spawns the three end pieces at each end (func_151C9748, base oriented by the hit
 * triangle; if any of the six fails, all are freed and nothing is built), an optional hum (arg9: func_1516284C at
 * the middle) and the beam record (func_1513D4B8, kind 0x59, colour r / g / b) whose +0x110 gets the emitter block
 * (BeamEmit: random sizes / phases / rates, pieces, triangles, args 10..12, option bits). With arg16 and a valid
 * direction (func_15145128) a glow record (func_151C957C) runs 500 units inwards from 20 units inside each end.
 * Unless arg21 (repeat) the owner's +0x14 is set to 1 (one-shot). With the hum, func_1000FA64 attaches the
 * func_151C8D5C sound callback. Returns the beam record or NULL. */
u8 *func_151C7B1C(f32 *hitA, u8 *triA, f32 *hitB, u8 *triB, u8 *owner, u8 *arg5, u8 r, u8 g, u8 b, u8 hum,
                  s16 len0, s16 len1, s16 len2, u8 opt0, u8 opt1, u8 noshadow, u8 glow, u8 arg17, u8 opt3,
                  f32 arg19, f32 arg20, u8 repeat, u8 arg22, s32 arg23) {
    BeamEmit e;
    BeamSpawn spawn;
    struct {
        u8 u0;       /* = 2 */
        u8 u1;       /* = 2 */
        s16 life;    /* = 300 */
        u8 u4;       /* = 0 */
    } snd;
    s32 mid[3];
    f32 neg[3];
    f32 u[3];
    s32 w0;
    s32 w1;
    f32 p[3];
    f32 q[3];
    f32 rp[3];
    f32 rq[3];
    f32 ux;
    f32 uy;
    f32 uz;
    f32 vx;
    f32 vy;
    f32 vz;
    u8 *rec;
    u8 alt;
    s32 i;

    func_1510F800(0);
    e.groundA = func_1510FD20((s32) hitA[0], (s32) hitA[2]);
    e.groundB = func_1510FD20((s32) hitB[0], (s32) hitB[2]);
    if (e.groundA == 0 || e.groundB == 0) {
        return NULL;
    }
    e.owner = owner;
    e.opt = (repeat ? 0x10 : 0) | (opt0 ? 1 : 0) | (opt1 ? 0 : 2) | (noshadow ? 4 : 0) | (opt3 ? 8 : 0);
    if (!repeat) {
        owner[0x14] = 1;
    }
    e.u98 = arg19;
    e.u9C = arg20;
    e.u94 = arg17;
    for (i = 0; i < 0x12; i++) {
        e.triA[i] = triA[i];
    }
    for (i = 0; i < 0x12; i++) {
        e.triB[i] = triB[i];
    }
    e.len01 = len0 + len1;
    e.len[0] = len0;
    e.len[1] = len1;
    e.len[2] = len2;
    e.u00[0] = e.u00[2] = func_150ADA68() * 1024.0f + -2560.0f + 2048.0f;
    e.u00[1] = e.u00[3] = func_150ADA68() * 1024.0f + 1536.0f + 2048.0f;
    e.u10[0] = func_150ADA68() * 768.0f + 768.0f;
    e.u10[1] = func_150ADA68() * 768.0f + 768.0f;
    e.phase[0] = func_150ADA68() * 6.2831855f;
    e.phase[1] = func_150ADA68() * 6.2831855f;
    e.rate[0] = (func_150ADA68() * 80.0f + 50.0f) * 0.001f;
    e.rate[1] = (func_150ADA68() * 80.0f + 50.0f) * 0.001f;
    spawn.d[0] = hitB[0] - hitA[0];
    spawn.d[1] = hitB[1] - hitA[1];
    spawn.d[2] = hitB[2] - hitA[2];
    alt = r < b;
    neg[0] = -spawn.d[0];
    neg[1] = -spawn.d[1];
    neg[2] = -spawn.d[2];
    /* func_151C9748 leaves the pointers unwritten when the hit triangle is degenerate (stack garbage on N64) */
    for (i = 0; i < 3; i++) {
        e.pieceA[i] = NULL;
        e.pieceB[i] = NULL;
    }
    func_151C9748(e.pieceA, hitA, triA, neg, e.groundA, alt, noshadow, arg22, 0);
    func_151C9748(e.pieceB, hitB, triB, spawn.d, e.groundB, alt, noshadow, arg22, 0);
    if (e.pieceA[0] == NULL || e.pieceA[1] == NULL || e.pieceA[2] == NULL || e.pieceB[0] == NULL ||
        e.pieceB[1] == NULL || e.pieceB[2] == NULL) {
        for (i = 0; i < 3; i++) {
            if (e.pieceA[i] != NULL) {
                func_1516972C((struct102 *) e.pieceA[i]);
            }
        }
        for (i = 0; i < 3; i++) {
            if (e.pieceB[i] != NULL) {
                func_1516972C((struct102 *) e.pieceB[i]);
            }
        }
        return NULL;
    }
    e.u58 = 0;
    e.u54 = 0.0f;
    e.owner2 = arg5;
    if (hum) {
        mid[0] = (s32) (hitA[0] + spawn.d[0] * 0.5f);
        mid[1] = (s32) (hitA[1] + spawn.d[1] * 0.5f);
        mid[2] = (s32) (hitA[2] + spawn.d[2] * 0.5f);
        snd.u0 = 2;
        snd.u1 = 2;
        snd.life = 300;
        snd.u4 = 0;
        e.sound = func_1516284C(&snd, mid, r, g, b, 0xFF, 0, 0, 0x10, arg22, arg23);
    } else {
        e.sound = 0;
    }
    spawn.kind = 0x59;
    spawn.u01 = 6;
    spawn.flags = 0x5A03;
    spawn.life = 300;
    spawn.u08 = 0;
    spawn.u0C = 0;
    spawn.rgba[0] = r;
    spawn.rgba[1] = g;
    spawn.rgba[2] = b;
    spawn.rgba[3] = 0xFF;
    spawn.size[0] = 0.0f;
    spawn.size[1] = 20.0f;
    spawn.from[0] = hitA[0];
    spawn.from[1] = hitA[1];
    spawn.from[2] = hitA[2];
    spawn.to[0] = hitB[0];
    spawn.to[1] = hitB[1];
    spawn.to[2] = hitB[2];
    spawn.u40 = ((D_800BE9F0 == 0x36) ? 0 : 0x2000000) | 0x6C0000 | 0x40000000;
    spawn.u44[0] = 0xFF;
    spawn.u44[1] = 0xFF;
    spawn.u44[2] = 0;
    spawn.u44[3] = 6;
    rec = (u8 *) func_1513D4B8((s32) &spawn, (s32) &D_800A4AA0, 0x1A, 0, 0, 0x18, 0, 0xA0, arg22, arg23);
    if (rec == NULL) {
        return NULL;
    }
    memcpy((s32) (rec + 0x110), (u8 *) &e, 0xA0);
    u[0] = spawn.d[0];
    u[1] = spawn.d[1];
    u[2] = spawn.d[2];
    if (func_15145128(u, u, &w0, &w1) != 0 && glow) {
        /* from 20 units inside each end, 500 units inwards */
        ux = u[0] * 20.0f;
        uy = u[1] * 20.0f;
        uz = u[2] * 20.0f;
        vx = u[0] * 500.0f;
        vy = u[1] * 500.0f;
        vz = u[2] * 500.0f;
        p[0] = hitA[0] + ux;
        p[1] = hitA[1] + uy;
        p[2] = hitA[2] + uz;
        q[0] = vx + p[0];
        q[1] = vy + p[1];
        q[2] = vz + p[2];
        rp[0] = hitB[0] - ux;
        rp[1] = hitB[1] - uy;
        rp[2] = hitB[2] - uz;
        rq[0] = rp[0] - vx;
        rq[1] = rp[1] - vy;
        rq[2] = rp[2] - vz;
        ((BeamEmit *) (rec + 0x110))->glowA = func_151C957C(rec, p, q, r, g, b, e.groundA, noshadow, arg22, arg23);
        ((BeamEmit *) (rec + 0x110))->glowB = func_151C957C(rec, rp, rq, r, g, b, e.groundB, noshadow, arg22, arg23);
    } else {
        ((BeamEmit *) (rec + 0x110))->glowA = NULL;
        ((BeamEmit *) (rec + 0x110))->glowB = NULL;
    }
    if (((BeamEmit *) (rec + 0x110))->sound != 0) {
        func_1000FA64(0x4D0, mid[0], mid[1], mid[2], 0x1F40, 0xFA, 0x64, (s32) func_151C8D5C, rec + 0x110, 0, 8,
                      func_150ADA20() & 0xFF);
    }
    return rec;
}
