void func_1510F800(s32);
s32 func_1510FD20(s32, s32);
s32 func_150ADA20(void);

/* P128: the two stack blocks of func_15149AC0. Spark15149AC0Wave is copied into the new record at +0x110 (0x50 bytes,
 * three wave channels read by func_15149DA8); Spark15149AC0Params is the spawn parameter block that func_1513D2F0
 * copies into the record at +0x18 (0x58 bytes: the last 0xC bytes are never written, as in the asm). */
typedef struct {
    f32 a0;    /* +00 rec[0xC] */
    f32 a1;    /* +04 rec[0x14] */
    f32 aMid;  /* +08 */
    s16 aT;    /* +0C */
    s16 aTMax; /* +0E */
    f32 aRate; /* +10 */
    f32 b0;    /* +14 rec[0x10] */
    f32 b1;    /* +18 rec[0x18] */
    f32 b2;    /* +1C rec[0x1C] */
    f32 bMid;  /* +20 */
    s16 bT;    /* +24 */
    s16 bTMax; /* +26 */
    f32 bRate; /* +28 */
    s32 c0;    /* +2C rec s16 0x20 */
    s32 c1;    /* +30 rec s16 0x22 */
    s32 c2;    /* +34 */
    s16 cT;    /* +38 */
    s16 cTMax; /* +3A */
    f32 cRate; /* +3C */
    f32 d0;    /* +40 rec[0x40] */
    f32 d1;    /* +44 rec[0x44] */
    u8 d2;     /* +48 rec[0x34] */
    u8 pad49[3];
    f32 d3;    /* +4C rec[0x3C] */
} Spark15149AC0Wave; /* size 0x50 */

typedef struct {
    u8 kind;       /* +00 0x13 / 0x14 / 0x71 */
    u8 pad01;
    s16 mode;      /* +02 0x301 */
    s16 u04;       /* +04 rec s16 0x24 */
    s16 pad06;
    s32 u08;       /* +08 0 */
    s32 u0C;       /* +0C (rec s16 0x20 + s16 0x22) >> 1 */
    u8 col[4];     /* +10 rec[0x26..0x29] */
    f32 u14;       /* +14 */
    f32 u18;       /* +18 */
    f32 pos[3];    /* +1C rec[0..2] */
    f32 u28;       /* +28 */
    f32 u2C;       /* +2C */
    f32 u30;       /* +30 */
    f32 u34;       /* +34 rec[0x38] */
    f32 u38;       /* +38 */
    f32 scale;     /* +3C 1.0 */
    s32 flags;     /* +40 rec u16 0x2A | 0x40000000, bit 0x01000000 = on ground */
    u8 u44;        /* +44 rec[0x2C] */
    u8 u45;        /* +45 rec[0x2D] */
    u8 pad46[2];
    s32 ground;    /* +48 func_1510FD20 result or 0 */
    u8 tail[0xC];  /* +4C never written (func_1513D2F0 copies 0x58 bytes) */
} Spark15149AC0Params; /* size 0x58 */

// spark_spawn_from_desc: spawns a menu spark/sprite record from the 0x48-byte descriptor desc (position +0, three wave
// channels +0xC..+0x44, colour +0x26, flags +0x2A, sizes +0x2C/+0x2D/+0x2E/+0x2F, extra +0x30): builds the spawn
// parameter block (kind 0x13/0x71 by kind_sel, random 0x13/0x14 otherwise; ground lookup when area != 0), creates
// the record through func_1513D524 (texture desc[0x2E], 0xE, desc[0x2F], layer, random | 2, desc[0x30] + 0x50, u4,
// owner) and copies the wave block to record + 0x110. Returns the record (0 when none was free).
s32 func_15149AC0(f32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *desc = (u8 *) arg0;
    Spark15149AC0Wave w;
    Spark15149AC0Params p;
    u8 area = arg2;
    u8 kind_sel = arg3;
    s32 layer = arg1 & 0xFF; /* the u8 arguments are narrowed here (callers pass s32) */
    s32 u4 = arg4 & 0xFF;
    struct210 *rec;

    p.flags = *(u16 *) (desc + 0x2A) | 0x40000000;
    p.pos[0] = ((f32 *) desc)[0];
    p.pos[1] = ((f32 *) desc)[1];
    p.pos[2] = ((f32 *) desc)[2];
    if (area != 0) {
        p.flags |= 0x01000000;
        func_1510F800(0);
        p.ground = func_1510FD20((s32) p.pos[0], (s32) p.pos[2]);
    } else {
        p.flags &= ~0x01000000;
        p.ground = 0;
    }
    if (kind_sel == 1) {
        p.kind = 0x13;
    } else if (kind_sel == 2) {
        p.kind = 0x71;
    } else if (func_150ADA20() & 1) {
        p.kind = 0x13;
    } else {
        p.kind = 0x14;
    }
    p.mode = 0x301;
    p.u04 = *(s16 *) (desc + 0x24);
    p.col[0] = desc[0x26];
    p.col[1] = desc[0x27];
    p.col[2] = desc[0x28];
    p.col[3] = desc[0x29];
    p.u44 = desc[0x2C];
    p.u28 = 0.0f;
    p.u2C = 0.0f;
    p.u30 = 0.0f;
    p.u45 = desc[0x2D];
    p.u38 = 0.0f;
    p.scale = 1.0f;
    p.u34 = *(f32 *) (desc + 0x38);

    w.a0 = *(f32 *) (desc + 0xC);
    w.a1 = *(f32 *) (desc + 0x14);
    w.aT = 0;
    w.aTMax = 6;
    w.aRate = 0.186f;
    w.aMid = (w.a0 + w.a1) * 0.5f;
    w.b0 = *(f32 *) (desc + 0x10);
    w.b1 = *(f32 *) (desc + 0x18);
    w.b2 = *(f32 *) (desc + 0x1C);
    w.bT = 0;
    w.bTMax = 0x11;
    w.bRate = 0.359f;
    w.bMid = (w.b0 + w.b1) * 0.5f;
    w.c0 = *(s16 *) (desc + 0x20);
    w.c1 = *(s16 *) (desc + 0x22);
    w.c2 = 0;
    w.cT = 0;
    w.cTMax = 0xF;
    w.cRate = 0.231f;
    w.d0 = *(f32 *) (desc + 0x40);
    w.d1 = *(f32 *) (desc + 0x44);
    w.d2 = desc[0x34];
    w.d3 = *(f32 *) (desc + 0x3C);
    p.u08 = 0;
    p.u0C = (w.c0 + w.c1) >> 1;
    p.u14 = 0.0f;
    p.u18 = 0.0f;

    rec = func_1513D524((s32) &p, desc[0x2E], 0xE, desc[0x2F], layer, (func_150ADA20() & 1) | 2,
                        *(s32 *) (desc + 0x30) + 0x50, u4, arg5);
    if (rec != NULL) {
        memcpy((u8 *) rec + 0x110, &w, sizeof(w));
    }
    return (s32) rec;
}
