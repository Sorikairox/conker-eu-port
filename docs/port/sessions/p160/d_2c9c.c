s32 func_151308E4(void *, s32, s32, u8, s32);
s32 func_150ADA20(void);

typedef struct { f32 x, y, z; } V3_151A2C9C;
typedef struct {
    s32 u00;          /* 0x00: 0x200005 */
    s32 u04;
    s16 u08;          /* 0x08: 0x5203 */
    s16 u0A;
    s32 u0C;
    s32 u10;
    u8 color[3];      /* 0x14 */
    u8 u17[4];        /* 0x17: 0xFF */
    u8 u1B;
    u8 u1C;           /* 0xFF */
    u8 u1D;           /* 0x27 */
    s16 period;       /* 0x1E */
    s16 step;         /* 0x20: 255 / period */
    s16 u22;          /* 1 */
    f32 u24;          /* 1.0f */
    f32 scale[2];     /* 0x28 */
    V3_151A2C9C pos;  /* 0x30 */
    V3_151A2C9C vel;  /* 0x3C */
    V3_151A2C9C acc;  /* 0x48 */
    f32 u54;
    s32 flags;        /* 0x58 */
    s32 pad5C;
    u8 u60[6];        /* 7, 2, 0x11, 0xFF, 0xFF, 2 */
} Blk_151A2C9C;

typedef struct {
    f32 u0;
    s16 fadePeriod;   /* 0x4 */
    s16 fadeStep;     /* 0x6: 255 / fadePeriod */
    s16 u8;
    s8 uA;
} Extra_151A2C9C;

// particle_puff_spawn: spawns one particle (func_151308E4 class 1 / 0x10) at pos with velocity vel and
// acceleration acc; the two fade periods are clamped to at least 1 and give 255 / period steps, the flags get
// random 0x40 / 0x80 bits; ex bytes 0..7 go to the particle at +0xA8 and bytes 4..11 at +0xB0 (overlapping copies; byte 11 is padding). Returns 0.
s32 func_151A2C9C(f32 *pos, f32 *vel, f32 *acc, f32 arg3, f32 arg4, f32 scale, s32 arg6, s32 arg7, s32 period,
                  s32 fadePeriod, s32 argA, s32 argB, s32 r, s32 g, s32 b, s32 argF, s32 arg10) {
    Blk_151A2C9C blk;
    Extra_151A2C9C ex;
    s32 bit40;
    s32 bit80;
    u8 *p;

    period = (s16)period;
    fadePeriod = (s16)fadePeriod;
    if (period <= 0) {
        period = 1;
    }
    if (fadePeriod <= 0) {
        fadePeriod = 1;
    }
    ex.u0 = arg3;
    ex.fadePeriod = fadePeriod;
    ex.fadeStep = 255 / fadePeriod;
    ex.u8 = argA;
    ex.uA = argB;
    blk.u00 = 0x200005;
    blk.u04 = 0;
    blk.u08 = 0x5203;
    blk.u0A = arg6;
    blk.u0C = 0;
    blk.u10 = 0;
    blk.color[0] = r;
    blk.color[1] = g;
    blk.color[2] = b;
    blk.u17[0] = 0xFF;
    blk.u17[1] = 0xFF;
    blk.u17[2] = 0xFF;
    blk.u17[3] = 0xFF;
    blk.u1B = arg7;
    blk.u1C = 0xFF;
    blk.u1D = 0x27;
    blk.period = period;
    blk.step = 255 / period;
    blk.u22 = 1;
    blk.u24 = 1.0f;
    blk.scale[0] = scale;
    blk.scale[1] = scale;
    blk.pos = *(V3_151A2C9C *)pos;
    blk.vel = *(V3_151A2C9C *)vel;
    blk.acc = *(V3_151A2C9C *)acc;
    blk.u54 = arg4;
    bit40 = (func_150ADA20() & 1) ? 0x40 : 0;
    bit80 = (func_150ADA20() & 1) ? 0x80 : 0;
    blk.flags = bit80 | 7 | bit40 | 0x80D200;
    blk.u60[0] = 7;
    blk.u60[1] = 2;
    blk.u60[2] = 0x11;
    blk.u60[3] = 0xFF;
    blk.u60[4] = 0xFF;
    blk.u60[5] = 2;
    p = (u8 *)func_151308E4(&blk, 1, 0x10, argF, arg10);
    if (p != NULL) {
        memcpy(p + 0xA8, &ex.u0, 8);
        memcpy(p + 0xB0, &ex.fadePeriod, 8);
    }
    return 0;
}
