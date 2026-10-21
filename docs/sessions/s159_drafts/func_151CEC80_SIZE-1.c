s32 func_150455FC(f32 *, s32, f32 *);
s32 func_151432BC(s32, f32 *, f32 *, s32 *, f32 *);
typedef struct { f32 x, y, z; } V3_EC80;
typedef struct {
    u8 u0;
    s8 u1;
    s16 u2;
    s16 u4;
    s16 pad6;
    s32 u8;
    s32 uC;
    u8 u10[4];
    f32 u14;
    f32 u18;
    V3_EC80 u1C;
    f32 u28[3];
    f32 u34[3];
    s32 u40;
    u8 u44;
    u8 u45;
    s8 u46;
    s8 u47;
    u8 *u48;
    u8 u4C;
    s32 u50;
    s16 u54;
    s16 u56;
} Blk58_EC80;
typedef struct { s32 u0; f32 u4; f32 u8; u8 *uC; f32 u10; } S_EC80;

void func_151CEC80(u8 *arg0) {
    s32 i;
    s16 mask;
    S_EC80 *s = (S_EC80 *)(arg0 + 0x28);

    s->u8 += (5624.0f + (func_150ADA68() * 3973.0f)) * 1e-10f * D_800BE9A4 * s->u4;
    if (s->u8 > 1.0f) {
        Blk58_EC80 blk;
        s32 n;

        i = 0;
        mask = 0;
        for (; i <= D_80082FA0; i++) {
            mask |= 1 << i;
        }
        if (!(*(s16 *)(s->uC + 2) & mask)) {
            do {
                s->u8 -= 1.0f;
            } while (s->u8 > 1.0f);
            return;
        }
        blk.u0 = 0x6A;
        blk.u1 = 0;
        blk.u2 = 0x2203;
        blk.u4 = 0x64;
        blk.u8 = 0;
        blk.uC = 0;
        blk.u10[0] = 0xFF;
        blk.u10[1] = 0xFF;
        blk.u10[2] = 0xFF;
        blk.u10[3] = 0xFF;
        blk.u28[1] = 0.0f;
        blk.u28[2] = 0.0f;
        blk.u34[1] = 0.0f;
        blk.u34[2] = 1.0f;
        blk.u40 = 0x01CC0061;
        blk.u45 = 0xFF;
        blk.u46 = 0;
        blk.u47 = 7;
        blk.u48 = s->uC;
        do {
            blk.u28[0] = ((func_150ADA68() * 409.0f) + -1308.0f) * 0.001f;
            blk.u34[0] = ((func_150ADA68() * 121.0f) + 23.0f) * 0.001f;
            blk.u14 = (func_150ADA68() * 25.0f) + 10.0f;
            blk.u18 = (func_150ADA68() * 60.0f) + 60.0f;
            func_151432BC(s->u0, &blk.u1C.x, &blk.u1C.z, &n, &blk.u1C.y);
            if (func_150455FC(&blk.u1C.x, n, &s->u10) != 0) {
                blk.u1C.y = s->u10;
                blk.u44 = (func_150ADA20() % 101U) + 0x9B;
                func_1513D2F0(&blk, (s32)&D_800A4AA0, 0x1C, 0, 0, 0x22, 0, 0, 0, 0, arg0[0xC], arg0[1]);
            }
            s->u8 -= 1.0f;
        } while (s->u8 > 1.0f);
    }
}
