void *func_15167D84(void *, s32, s32, s32, s32, s32);
extern s32 D_800908C4;
extern u8 D_800A8B50[]; /* 0x18-byte burst descriptors: f32 radius, speed base, speed range; s16 pairs (base, range) */

// spray_particles_burst: while the owner's counter (+0x88 of arg0's data) is above 1, spawns one particle per unit
// (func_15167D84, the 0x38-byte template below, P124: one struct instead of m2c's 26 separate locals): random
// direction on a sphere of the descriptor's radius around arg1, velocity = offset from arg0's position times a
// random speed, random life / size / scale from the descriptor (D_800A8B50[data[0x80]]).
void func_1519961C(u8 *arg0, u8 *arg1) {
    struct {
        void *u0;
        s32 u4;
        s32 u8;
        s16 uC;
        s16 uE;
        s16 u10;
        s16 u12;
        s16 u14;
        s16 u16;
        s16 u18;
        s16 u1A;
        s8 u1C;
        s8 u1D;
        s8 u1E;
        s8 u1F;
        s16 u20;
        s16 u22;
        s16 u24;
        s16 u26;
        s16 u28;
        u8 u2A;
        u8 u2B;
        u8 u2C;
        u8 u2D;
        u8 u2E;
        u8 u2F;
        u8 u30;
        u8 u31;
        u8 u32;
        u8 pad33;
        s16 u34;
        u8 pad36[2];
    } t;
    u8 *data;
    u8 *desc;
    f32 speed;
    f32 radius;
    f32 ring;
    f32 sinA;
    f32 cosA;
    f32 sinB;
    s32 a;
    s32 b;
    s16 v;

    data = *(u8 **)(arg0 + 0x98);
    t.u10 = *(f32 *)(arg0 + 0x10);
    desc = &D_800A8B50[data[0x80] * 0x18];
    t.u12 = *(f32 *)(arg0 + 0x14);
    t.u1C = 0;
    t.u1E = 0;
    t.u1D = 0;
    t.u2C = 0xFF;
    t.u2D = 0xFF;
    t.u2E = 0xFF;
    t.u30 = 0;
    t.u31 = 0;
    t.u32 = 0;
    t.u2F = 0xFF;
    t.u1F = -1;
    t.u34 = 0x12;
    t.uC = 0;
    t.uE = 0;
    t.u0 = &D_800908C4;
    t.u28 = 300;
    t.u14 = *(f32 *)(arg0 + 0x18);
    do {
        speed = func_150ADA68() * *(f32 *)(desc + 8) + *(f32 *)(desc + 4);
        a = func_150ADA20() & 0xFF;
        b = func_150ADA20() & 0xFF;
        sinA = func_151423D8((a - 0x40) & 0xFF);
        cosA = func_151423D8(a);
        sinB = func_151423D8((b - 0x40) & 0xFF);
        radius = *(f32 *)(desc + 0);
        ring = radius * func_151423D8(b);
        t.u16 = ((*(f32 *)(arg1 + 0) + ring * sinA) - *(f32 *)(arg0 + 0x10)) * speed;
        t.u20 = ((*(f32 *)(arg1 + 4) - radius * sinB) - *(f32 *)(arg0 + 0x14)) * speed;
        t.u18 = ((*(f32 *)(arg1 + 8) + ring * cosA) - *(f32 *)(arg0 + 0x18)) * speed;
        t.u22 = func_150ADA20() % (u32) (*(s16 *)(desc + 0xE) + 1) + *(s16 *)(desc + 0xC);
        t.u2A = func_150ADA20() % (u32) (*(s16 *)(desc + 0x12) + 1) + *(s16 *)(desc + 0x10);
        v = func_150ADA20() % (u32) (*(s16 *)(desc + 0x16) + 1) + *(s16 *)(desc + 0x14);
        t.u26 = v;
        t.u24 = v;
        func_15167D84(&t, 0, 0, -1, arg0[0xC], arg0[1]);
        *(f32 *)(data + 0x88) -= 1.0f;
    } while (*(f32 *)(data + 0x88) > 1.0f);
}
