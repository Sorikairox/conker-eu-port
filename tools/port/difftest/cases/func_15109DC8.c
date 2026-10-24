extern f32 D_800A2A04;
extern f32 D_800A2A08;
extern f32 D_800A2A0C;
extern f32 D_800A2A10;
extern f32 D_800A2A14;
extern f32 D_800A2A18;
extern f32 D_800A2A1C;
s32 func_151308E4(void *, s32, s32, u8, s32);
s32 func_151530A8(void *, u8, s32);

/* particle template of func_151308E4 (0x70 bytes; bytes 0x5C-0x5F / 0x66-0x6F unset, as in the asm) */
typedef struct {
    s32 u0;           /* 0x00 */
    s32 u4;           /* 0x04 */
    u16 flags;        /* 0x08 */
    s16 life;         /* 0x0A */
    s32 uC;           /* 0x0C */
    s32 u10;          /* 0x10 */
    u8 colour[9];     /* 0x14 */
    u8 kind;          /* 0x1D */
    s16 u1E;          /* 0x1E */
    s16 u20;          /* 0x20 */
    s16 u22;          /* 0x22 */
    f32 u24;          /* 0x24 */
    f32 size[2];      /* 0x28 */
    f32 pos[3];       /* 0x30 */
    f32 vel[3];       /* 0x3C */
    f32 dir[3];       /* 0x48 */
    f32 u54;          /* 0x54 */
    s32 mode;         /* 0x58 */
    u8 pad5C[4];
    u8 u60[6];        /* 0x60 */
    u8 pad66[0xA];
} PartTmpl9DC8;

/* emitter block of func_151530A8 (0x74 bytes; bytes 0x59-0x5B / 0x6B unset, as in the asm) */
typedef struct {
    s32 u0;           /* 0x00 */
    s32 u4;           /* 0x04 */
    f32 pos[3];       /* 0x08 */
    f32 u14[4];       /* 0x14 */
    f32 u24;          /* 0x24 */
    f32 u28;          /* 0x28 */
    s16 u2C;          /* 0x2C */
    s16 u2E;          /* 0x2E */
    s16 u30;          /* 0x30 */
    s16 u32;          /* 0x32 */
    s32 u34;          /* 0x34 */
    s32 u38;          /* 0x38 */
    s16 u3C;          /* 0x3C */
    s16 u3E;          /* 0x3E */
    s16 u40;          /* 0x40 */
    u8 u42[0x17];     /* 0x42 */
    u8 pad59[3];
    s32 u5C;          /* 0x5C */
    s32 u60;          /* 0x60 */
    s16 u64;          /* 0x64 */
    s16 u66;          /* 0x66 */
    s16 u68;          /* 0x68 */
    u8 u6A;           /* 0x6A */
    u8 pad6B;
    f32 u6C;          /* 0x6C */
    s8 u70[4];        /* 0x70 */
} EmitBlk9DC8;

// spark_burst_spawn: P232. Handler 0 of the D_80089004 point-effect table (called by func_15109A7C with the
// object, the point `pos` and three more points; `dir` = the unit direction): spawns one spark particle (kind 0x2B,
// random life 10..25, random size 35..60, velocity dir * a random scale, random flip bits 0x40 / 0x80) through
// func_151308E4 and a small emitter (func_151530A8) at the same point. b / c / d are not used.
void func_15109DC8(u8 *obj, f32 *pos, f32 *b, f32 *c, f32 *d, f32 *dir) {
    PartTmpl9DC8 t;
    f32 scale;
    EmitBlk9DC8 e;
    f32 size;
    s32 flipX;
    s32 flipY;
    s32 i;

    scale = (func_150ADA68() * D_800A2A04 + D_800A2A08) * D_800A2A0C;
    t.kind = 0x2B;
    t.flags = 0x4401;
    t.u0 = 0x200005;
    t.u4 = 0x20000;
    t.life = (func_150ADA20() & 0xF) + 10;
    t.uC = 0;
    t.u10 = 0;
    for (i = 0; i < 9; i++) {
        t.colour[i] = 0xFF;
    }
    size = func_150ADA68() * 25.0f + 35.0f;
    t.size[1] = size;
    t.size[0] = size;
    t.pos[0] = pos[0];
    t.pos[1] = pos[1];
    t.pos[2] = pos[2];
    t.vel[0] = 0.0f;
    t.vel[1] = 0.0f;
    t.vel[2] = 0.0f;
    t.dir[0] = dir[0] * scale;
    t.dir[1] = dir[1] * scale;
    t.u1E = 5;
    t.u20 = 0x33;
    t.u22 = 1;
    t.u54 = 0.0f;
    t.u24 = 1.0f;
    t.dir[2] = dir[2] * scale;
    flipX = (func_150ADA20() & 1) ? 0x40 : 0;
    flipY = (func_150ADA20() & 1) ? 0x80 : 0;
    t.mode = flipY | 5 | flipX | 0xC200;
    t.u60[0] = 6;
    t.u60[1] = 6;
    t.u60[2] = 0xFF;
    t.u60[3] = 0xFF;
    t.u60[4] = 0xFF;
    t.u60[5] = 4;
    func_151308E4(&t, 1, 0, obj[0xC], obj[1]);

    e.u0 = 1;
    e.u4 = 4;
    e.pos[0] = pos[0];
    e.pos[1] = pos[1];
    e.pos[2] = pos[2];
    e.u14[0] = D_800A2A10;
    e.u14[1] = D_800A2A14;
    e.u14[2] = D_800A2A18;
    e.u14[3] = D_800A2A1C;
    e.u24 = 2.0f;
    e.u28 = 6.0f;
    e.u2C = 0;
    e.u2E = 0xFF;
    e.u30 = -0x40;
    e.u32 = 0x2E;
    e.u34 = 4;
    e.u38 = 3;
    e.u3C = 0x14;
    e.u3E = 0xF;
    e.u40 = 1;
    /* 0x42..0x58: 0C 02 03 FF FF FF FF 00 00 00 00 FF FF FF FF 00 00 00 00 FF 00 03 24 */
    e.u42[0] = 0xC;
    e.u42[1] = 2;
    e.u42[2] = 3;
    for (i = 3; i < 7; i++) {
        e.u42[i] = 0xFF;
    }
    for (i = 7; i < 0xB; i++) {
        e.u42[i] = 0;
    }
    for (i = 0xB; i < 0xF; i++) {
        e.u42[i] = 0xFF;
    }
    for (i = 0xF; i < 0x13; i++) {
        e.u42[i] = 0;
    }
    e.u42[0x13] = 0xFF;
    e.u42[0x14] = 0;
    e.u42[0x15] = 3;
    e.u42[0x16] = 0x24;
    e.u5C = 0x200005;
    e.u60 = 0x60600;
    e.u64 = 0xA;
    e.u66 = 0x19;
    e.u68 = 1;
    e.u6A = 0;
    e.u6C = 1.0f;
    e.u70[0] = -1;
    e.u70[1] = 0;
    e.u70[2] = -1;
    e.u70[3] = -1;
    func_151530A8(&e, obj[0xC], obj[1]);
}
