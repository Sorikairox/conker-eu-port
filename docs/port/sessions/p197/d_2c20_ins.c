/* P197 */
s32 func_151A74B0(void *spray, s32 mode, u8 view, s32 arg3);
void func_1514CDC8(f32 x, f32 y, f32 z, f32 r, s16 yaw, s16 a0, s16 a1, s16 count, u8 kind, s32 arg9, f32 argA,
                   s32 argB, u8 argC);
void func_15153F24(u8 *arg0, u8 arg1);
void func_151534E0(u8 *arg0, s32 arg1);
u8 *func_150B443C(s32 *arg0, u8 *arg1, s16 arg2);

extern s32 D_800BEE08;

/* the three pipes (position, facing angle) */
typedef struct {
    f32 pos[3];
    u8 angle;
    u8 pad[3];
} PipeSpot;
static const PipeSpot D_8009FCF0[3] = {
    { { 975.0f, 351.0f, 1723.0f }, 0x94 },
    { { 1005.0f, 351.0f, -1706.0f }, 0xEA },
    { { -1980.0f, 351.0f, -17.0f }, 0x3F },
};

// pipe_explode_effects: P197 (difftest as a void variant, d_2c20.c): the effects of pipe `pipe` (0..2, D_8009FCF0: position and facing angle) bursting in
// view `view` ("../Effects/PipeExploded/pipeexploded.c"): func_1512D748 on the current player's state (7, 1), a spray
// of 3..4 pieces (func_151A74B0), 1..2 debris bursts (func_1514CDC8, radius 31..104, 4..6 pieces), a smoke cloud
// (func_15153F24), two spark bursts (func_151534E0), clears the pipe's two earlier effects of type 0x17
// (func_151494E0, keys 2 * pipe and 2 * pipe + 1), a water / steam jet 150 units in front of the pipe
// (func_150B443C, 20) and the sounds 0xE7 / 0x22 at the pipe (func_10010F88).
s32 func_150B2C20(s32 pipe, s32 view) {
    struct {
        s16 count;       /* 0x00 */
        u8 pad2[2];
        f32 pos[3];      /* 0x04 */
        s16 u10;         /* 0x10 */
        u8 pad12[2];
        f32 u14;         /* 0x14 */
        s16 u18[4];      /* 0x18 */
        f32 u20[12];     /* 0x20 */
        f32 u50;         /* 0x50 */
        u8 u54;          /* 0x54 */
        u8 u55;          /* 0x55 */
        s16 u56;         /* 0x56 */
        s16 u58;         /* 0x58 */
        u8 pad5A[2];
    } spray;
    struct {
        s16 base, range; /* 0x00 particle count base + rand % (range + 1) */
        f32 pos[3];      /* 0x04 */
        s16 u10[4];      /* 0x10 */
        f32 u18[4];      /* 0x18 */
        u8 c[8];         /* 0x28 */
        u8 u30;          /* 0x30 */
        u8 pad31;
        s16 u32, u34;    /* 0x32 */
        u16 u36;         /* 0x36 */
        f32 u38, u3C;    /* 0x38 */
        u8 u40, u41;     /* 0x40 */
        s16 u42, u44;    /* 0x42 */
        u8 u46;          /* 0x46 */
    } smoke;
    struct {
        f32 pos[3];      /* 0x00 */
        f32 u0C[6];      /* 0x0C */
        s16 u24[10];     /* 0x24 */
        u8 u38, u39;     /* 0x38 */
        u8 pad3A[2];
        s32 u3C[6];      /* 0x3C */
        u8 u54, u55;     /* 0x54 */
    } sparks;
    struct {
        f32 vel[3];      /* 0x00 */
        f32 u0C;         /* 0x0C */
        u8 u10;          /* 0x10 */
        u8 pad11[3];
        f32 u14, u18;    /* 0x14 */
        u8 u1C;          /* 0x1C */
        u8 pad1D[3];
        f32 u20;         /* 0x20 */
        u8 u24;          /* 0x24 */
        u8 pad25;
        s16 u26;         /* 0x26 */
        f32 u28, u2C;    /* 0x28 */
        u8 u30[6];       /* 0x30 */
        s16 u36;         /* 0x36 */
        u8 u38;          /* 0x38 */
        u8 pad39[3];
        f32 u3C;         /* 0x3C */
    } jet;
    f32 at[3];
    u8 key[8];
    const PipeSpot *p;
    s16 n;
    f32 r, s, c;

    func_1512D748((struct108 *) ((u8 *) D_800DBFF0 + D_800BEE08 * 0x9A0), 7, 1);

    /* spray of pieces */
    spray.count = (func_150ADA20() & 1) + 3;
    p = &D_8009FCF0[(u8) pipe];
    spray.pos[0] = p->pos[0];
    spray.pos[1] = p->pos[1];
    spray.pos[2] = p->pos[2];
    spray.u10 = 300;
    spray.u14 = 170.0f;
    spray.u18[0] = p->angle - 0x20;
    spray.u18[1] = 0x41;
    spray.u18[2] = -0x28;
    spray.u18[3] = 0x50;
    spray.u20[0] = 16.2f;
    spray.u20[1] = 17.6f;
    spray.u20[2] = 19.300001f;
    spray.u20[3] = 21.300001f;
    spray.u20[4] = 0.0f;
    spray.u20[5] = 0.0f;
    spray.u20[6] = 0.0f;
    spray.u20[7] = 0.467f;
    spray.u20[8] = 0.514f;
    spray.u20[9] = -1.0f;
    spray.u20[10] = -2.6000001f;
    spray.u20[11] = -5.0f;
    spray.u50 = 10.0f;
    spray.u54 = 1;
    spray.u55 = 0;
    spray.u56 = 0x32;
    spray.u58 = 0x19;
    func_151A74B0(&spray, 0, view, 1);

    /* debris bursts */
    n = (func_150ADA20() & 1) + 1;
    while (n-- != 0) {
        r = func_150ADA68() * 73.0f + 31.0f;
        func_1514CDC8(p->pos[0], p->pos[1], p->pos[2], r, p->angle + 0x40, 0, 0xFF, (u32) func_150ADA20() % 3 + 4,
                      9, 0, 0.009615385f, 0, view);
    }

    /* smoke */
    smoke.base = 0x1E;
    smoke.range = 0xF;
    smoke.pos[0] = p->pos[0];
    smoke.pos[1] = p->pos[1];
    smoke.pos[2] = p->pos[2];
    smoke.u10[0] = p->angle - 0x40;
    smoke.u10[1] = -0x2D;
    smoke.u10[2] = 0x80;
    smoke.u10[3] = 0x5A;
    smoke.u18[0] = 6.0f;
    smoke.u18[1] = 2.55f;
    smoke.u18[2] = 2.7f;
    smoke.u18[3] = 3.4199998f;
    smoke.c[0] = 0xFF;
    smoke.c[1] = 0xFF;
    smoke.c[2] = 0xFF;
    smoke.c[3] = 0xFF;
    smoke.c[4] = 0xFF;
    smoke.c[5] = 0xFF;
    smoke.c[6] = 0xFF;
    smoke.c[7] = 0xFF;
    smoke.u30 = 9;
    smoke.u32 = 0x10;
    smoke.u34 = 0x16;
    smoke.u36 = 0x1601;
    smoke.u38 = 4.14f;
    smoke.u3C = 4.8599997f;
    smoke.u40 = 0x7F;
    smoke.u41 = 0x7F;
    smoke.u42 = 0xA;
    smoke.u44 = 0x19;
    smoke.u46 = 0;
    func_15153F24((u8 *) &smoke, view);

    /* sparks, twice */
    sparks.pos[0] = p->pos[0];
    sparks.pos[1] = p->pos[1];
    sparks.pos[2] = p->pos[2];
    sparks.u0C[0] = 10.0f;
    sparks.u0C[1] = 30.0f;
    sparks.u0C[2] = 1.5f;
    sparks.u0C[3] = 1.0f;
    sparks.u0C[4] = 20.0f;
    sparks.u0C[5] = 40.0f;
    sparks.u24[0] = 0xF;
    sparks.u24[1] = 8;
    sparks.u24[2] = p->angle - 0x19;
    sparks.u24[3] = 0x32;
    sparks.u24[4] = -0x32;
    sparks.u24[5] = 0x3C;
    sparks.u24[6] = 3;
    sparks.u24[7] = 2;
    sparks.u24[8] = 0x3C;
    sparks.u24[9] = 0x14;
    sparks.u38 = 6;
    sparks.u39 = 8;
    sparks.u3C[0] = 1;
    sparks.u3C[1] = 7;
    sparks.u3C[2] = 0;
    sparks.u3C[3] = 0;
    sparks.u3C[4] = 0;
    sparks.u3C[5] = 0;
    sparks.u54 = 0xFF;
    sparks.u55 = 0xA0;
    func_151534E0((u8 *) &sparks, (u8) view);
    sparks.u24[0] = 0xA;
    sparks.u24[1] = 6;
    sparks.u24[8] = 0x64;
    sparks.u24[9] = 0;
    sparks.u39 = 9;
    sparks.u3C[3] = 5;
    func_151534E0((u8 *) &sparks, (u8) view);

    /* jet from 150 units in front of the pipe */
    s = func_151423D8(p->angle);
    c = func_151423D8((u8) (p->angle - 0x40));
    at[0] = p->pos[0] - 150.0f * c;
    at[1] = p->pos[1];
    at[2] = p->pos[2] - 150.0f * s;
    jet.u24 = 0x80;
    jet.u26 = 0xFF;
    jet.vel[0] = 10.0f * c;
    jet.vel[1] = 3.0f;
    jet.vel[2] = 10.0f * s;
    jet.u0C = -3.71f;
    jet.u30[0] = 2;
    jet.u30[1] = 5;
    jet.u10 = 4;
    jet.u38 = 0;
    jet.u36 = 0x1E;
    jet.u1C = 6;
    jet.u30[2] = 5;
    jet.u30[3] = 0x33;
    jet.u30[4] = 3;
    jet.u30[5] = 0x55;
    jet.u20 = 0.4f;
    jet.u2C = 47.0f;
    jet.u28 = 1.84f;
    jet.u14 = 3.3f;
    jet.u18 = 0.7f;
    jet.u3C = 0.3f;
    key[0] = (u8) pipe * 2;          /* D_8009FD20 {0, 2, 4} */
    func_151494E0((s32) key, 0x17);
    key[0] = (u8) pipe * 2 + 1;      /* D_8009FD2C {1, 3, 5} */
    func_151494E0((s32) key, 0x17);
    func_150B443C((s32 *) &jet, (u8 *) at, 20);

    func_10010F88(0xE7, 0x7FFF, 0, 2, 0, (s32) p->pos[0], (s32) p->pos[1], (s32) p->pos[2], 1000, 3000);
    func_10010F88(0x22, 0x7FFF, 0, 0, 0, (s32) p->pos[0], (s32) p->pos[1], (s32) p->pos[2], 1000, 3000);
    return 0; /* s32 for the caller game_eu_142E40.c (s32 (s32, s32)); nobody reads it (the asm leaves func_10010F88s v0) */
}
