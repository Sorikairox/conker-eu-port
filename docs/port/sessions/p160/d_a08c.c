extern f32 D_800AB850;
extern f32 D_800AB854;
extern f32 D_800AB858;
extern f32 D_800AB85C;

typedef struct { f32 x, y, z; } V3_151DA08C;

typedef struct {
    u8 u0;
    u8 u1;
    u8 u2;            /* rand % 5 + 2 */
    u8 u3;            /* rand % 5 + 2 */
    f32 u4;           /* (randf * D_800AB850 + D_800AB854) * scale */
    f32 u8;           /* (randf * D_800AB858 + D_800AB85C) * scale */
    f32 uC;           /* 0 */
    f32 scale;        /* 0x10 */
    f32 u14;          /* 1.0f with the default life, else arg2 */
    u8 kind;          /* 0x18 */
} Rec1C_151DA08C;     /* 0x1C bytes, copied to the record at +0x128 */

typedef struct {
    u8 u00;           /* the kind's D_800900A4 handler result */
    u8 u01;
    s16 u02;          /* 3 */
    s16 life;         /* 0x04: 300 or the caller's */
    s32 u08;
    s32 u0C;
    u8 u10[4];        /* 0, 0, 0, 0xFF */
    f32 u14[2];       /* scale */
    V3_151DA08C pos;  /* 0x1C */
    f32 u28[3];       /* 0 */
    f32 u34[3];       /* 1.0f */
    s32 u40;          /* 0x0CDC0008, | 1 with a caller's life */
    u8 u44;           /* arg3 */
    u8 u45;           /* 0xFF */
    u8 u46;           /* 4 */
    u8 u47;           /* 5 */
    s32 u48;
    u8 u4C;           /* 0xFF */
    s32 u50;
    s16 alpha;        /* 0x54: min(life, 255), 1 with the default life */
    s16 fade;         /* 0x56: 255 / life (1 if life >= 256), 255 with the default life */
} Blk58_151DA08C;

// smoke_puff_spawn: spawns one effect record of kind `kind` (func_1513D668 class 0xE / 0x13) at *pos with size
// `scale` and life `life` (-1: 300 frames, full alpha), then copies a 0x1C-byte parameter block (random speeds,
// the kind) into the record at +0x128. arg7 / arg8 are unused. Returns the record (0 if none).
s32 func_151DA08C(u8 kind, f32 scale, f32 arg2, u8 arg3, s16 life, s32 arg5, void *pos, s32 arg7, s32 arg8) {
    u8 (**handlers)(void) = (u8 (**)(void))&D_800900A4;
    Rec1C_151DA08C rec;
    Blk58_151DA08C blk;
    s32 ra;
    s32 rb;
    s32 rc;
    u8 *p;

    rec.scale = scale;
    rec.u0 = 0;
    rec.u1 = 0;
    rec.u2 = (u32)func_150ADA20() % 5 + 2;
    rec.u3 = (u32)func_150ADA20() % 5 + 2;
    rec.u4 = (func_150ADA68() * D_800AB850 + D_800AB854) * rec.scale;
    rec.u8 = (func_150ADA68() * D_800AB858 + D_800AB85C) * rec.scale;
    rec.kind = kind;
    rec.uC = 0.0f;
    blk.u00 = handlers[kind]();
    blk.u02 = 3;
    blk.u08 = 0;
    blk.u0C = 0;
    blk.u10[0] = 0;
    blk.u10[1] = 0;
    blk.u10[2] = 0;
    blk.u10[3] = 0xFF;
    blk.u14[1] = scale;
    blk.u14[0] = scale;
    blk.pos = *(V3_151DA08C *)pos;
    blk.u40 = 0x0CDC0008;
    blk.u34[0] = 1.0f;
    blk.u34[1] = 1.0f;
    blk.u34[2] = 1.0f;
    blk.u28[0] = 0.0f;
    blk.u28[1] = 0.0f;
    blk.u28[2] = 0.0f;
    if (life == -1) {
        blk.life = 300;
        rec.u14 = 1.0f;
        blk.alpha = 1;
        blk.fade = 255;
    } else {
        blk.life = life;
        blk.u40 = 0x0CDC0009;
        rec.u14 = arg2;
        blk.alpha = (life < 256) ? life : 255;
        blk.fade = (life < 256) ? 255 / life : 1;
    }
    blk.u45 = 0xFF;
    blk.u01 = 0;
    blk.u46 = 4;
    blk.u47 = 5;
    blk.u48 = 0;
    blk.u4C = 0xFF;
    blk.u50 = 0;
    blk.u44 = arg3;
    ra = func_150ADA20();
    rb = func_150ADA20();
    rc = func_150ADA20();
    p = (u8 *)func_1513D668((s32)&blk, 0, 0xE, 0x13, 0, (rb & 1) + (ra & 1), rc & 0xFF, 500.0f, 500.0f, 0, arg5, 0,
                            0x1C, 0xFF, 0);
    if (p != NULL) {
        memcpy(p + 0x128, &rec, 0x1C);
    }
    return (s32)p;
}
