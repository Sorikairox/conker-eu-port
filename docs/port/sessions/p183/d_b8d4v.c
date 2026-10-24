s32 func_15046F70(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3);
s32 func_151530A8(s32 *arg0, u8 arg1, s32 arg2);
void func_151534E0(u8 *arg0, s32 arg1);
void func_1514B5A4(u8 *arg0, s32 arg1, s32 arg2);
s32 func_150ADA20(void);

// lava_splash_effect: P183: when the point `pos` has ground within +-200 units below/above it (func_15046F70 with
// `owner`), spawns the lava impact effects there: a 10-particle burst from spec A (func_151530A8, owner byte
// arg2, extra arg3), a spark burst from spec B (func_151534E0, alpha 0x9B + rand 0..100), the third burst
// func_1514B5A4 (pos, arg2, arg3), and one 0x38-type particle 10 units above pos (func_1513D668, size 100 x 100,
// random colour / frame bits, link owner + 4). The asm returns the stale func_1513D668 v0 (callers ignore it);
// kept s32 for the callers' prototype (returns 0).
void func_1514B8D4(f32 *pos, u8 *owner, u8 arg2, s32 arg3) {
    struct {
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
        s8 u72[2];          /* 0x72 */
    } specA;
    struct {
        s32 pos[3];         /* 0x00 */
        f32 f0C[6];         /* 0x0C */
        s16 h24[10];        /* 0x24 */
        u8 b38[2];          /* 0x38 */
        s32 w3C[6];         /* 0x3C */
        u8 b54[2];          /* 0x54 */
    } specB;
    struct {
        u8 type;            /* 0x00 */
        s16 u02;            /* 0x02 */
        s16 u04;            /* 0x04 */
        s32 u08;            /* 0x08 */
        s32 u0C;            /* 0x0C */
        u8 col[4];          /* 0x10 */
        f32 u14[2];         /* 0x14 */
        f32 pos[3];         /* 0x1C */
        f32 u28[3];         /* 0x28 */
        f32 u34;            /* 0x34 */
        f32 u38[2];         /* 0x38 */
        s32 flags;          /* 0x40 */
        u8 u44[4];          /* 0x44 */
    } part;
    f32 probe[3];
    s32 at[3];
    s32 r6, r7, r8;

    at[0] = ((s32 *) pos)[0];
    at[1] = ((s32 *) pos)[1];
    at[2] = ((s32 *) pos)[2];
    probe[0] = pos[0];
    probe[1] = pos[1] + 200.0f;
    probe[2] = pos[2];
    if (func_15046F70((u8 *) probe, 0, pos[1] - 200.0f, owner) == 0) {
        return;
    }

    specA.countBase = 10;
    specA.countExtra = 0;
    specA.aBase = 9.900001f;
    specA.aRange = 21.0f;
    specA.bBase = -3.0000002f;
    specA.bRange = 1.016f;
    specA.lenBase = 30.0f;
    specA.lenRange = 30.4f;
    specA.angXBase = 0;
    specA.angXExtra = 0xFF;
    specA.angYBase = -0x3F;
    specA.angYExtra = 0x2B;
    specA.flagBase = 4;
    specA.flagExtra = 5;
    specA.lifeBase = 30;
    specA.lifeExtra = 30;
    specA.u40 = 1;
    specA.u42[0] = 0xC;
    specA.u42[1] = 2;
    specA.u42[2] = 3;
    specA.colABase[0] = 0xB4;
    specA.colABase[1] = 0;
    specA.colABase[2] = 0;
    specA.colABase[3] = 0x9B;
    specA.colAExtra[0] = 0x32;
    specA.colAExtra[1] = 0x64;
    specA.colAExtra[2] = 0;
    specA.colAExtra[3] = 0x64;
    specA.colBBase[0] = 0xFF;
    specA.colBBase[1] = 0xFF;
    specA.colBBase[2] = 0xFF;
    specA.colBBase[3] = 0xFF;
    specA.colBExtra[0] = 0;
    specA.colBExtra[1] = 0;
    specA.colBExtra[2] = 0;
    specA.colBExtra[3] = 0;
    specA.u55Base = 0xFF;
    specA.u55Extra = 0;
    specA.u57[0] = 1;
    specA.u57[1] = 0x24;
    specA.u5C = 0x200005;
    specA.u60 = 0x60600;
    specA.u64 = 20;
    specA.u66 = 12;
    specA.u68 = 1;
    specA.u6A = 0;
    specA.u6C = 1.0f;
    specA.u70 = -1;
    specA.u71 = 0;
    specA.u72[0] = -1;
    specA.u72[1] = -1;
    specA.pos[0] = at[0];
    specA.pos[1] = at[1];
    specA.pos[2] = at[2];
    func_151530A8((s32 *) &specA, arg2, arg3);

    specB.pos[0] = at[0];
    specB.pos[1] = at[1];
    specB.pos[2] = at[2];
    specB.f0C[0] = 3.99f;
    specB.f0C[1] = 8.11f;
    specB.f0C[2] = 0.60200006f;
    specB.f0C[3] = 0.407f;
    specB.f0C[4] = 10.139999f;
    specB.f0C[5] = 10.2699995f;
    specB.h24[0] = 8;
    specB.h24[1] = 8;
    specB.h24[2] = 0;
    specB.h24[3] = 0xFF;
    specB.h24[4] = -0x40;
    specB.h24[5] = 0x2C;
    specB.h24[6] = 5;
    specB.h24[7] = 4;
    specB.h24[8] = 0x42;
    specB.h24[9] = 30;
    specB.b38[0] = 10;
    specB.b38[1] = 0x21;
    specB.w3C[0] = 1;
    specB.w3C[1] = 12;
    specB.w3C[2] = 0;
    specB.w3C[3] = 0;
    specB.w3C[4] = 0;
    specB.w3C[5] = 0;
    specB.b54[0] = 0xFF;
    specB.b54[1] = (u32) func_150ADA20() % 101 + 0x9B;
    func_151534E0((u8 *) &specB, 0xFF);

    func_1514B5A4((u8 *) at, arg2, arg3);

    part.type = 0x38;
    part.u02 = 1;
    part.u04 = 50;
    part.u08 = 0;
    part.u0C = 0x6666;
    part.col[3] = 0xFF;
    part.u14[0] = 1.0f;
    part.u14[1] = 1.0f;
    part.pos[0] = *(f32 *) &at[0];
    part.pos[1] = *(f32 *) &at[1] + 10.0f;
    part.pos[2] = *(f32 *) &at[2];
    part.u28[0] = 0.0f;
    part.u28[1] = 0.0f;
    part.u28[2] = 0.0f;
    part.u34 = 0.2f;
    part.u38[0] = 1.0f;
    part.u38[1] = 1.0f;
    part.flags = 0x400C0001;
    part.u44[0] = (u32) func_150ADA20() % 101 + 100;
    part.u44[1] = 0xFF;
    part.u44[2] = 0;
    part.u44[3] = 6;
    part.col[0] = (u32) func_150ADA20() % 51 + 0xB4;
    part.col[1] = (u32) func_150ADA20() % 101;
    func_150ADA20();
    part.col[2] = 0;
    r6 = func_150ADA20();
    r7 = func_150ADA20();
    r8 = func_150ADA20();
    func_1513D668((s32) &part, 0, 0x12, 0x1D, 0, (r7 & 1) + (r6 & 1), r8 & 0xFF, 100.0f, 100.0f, 0, (s32) (owner + 4),
                  0, 0, arg2, arg3);

}
