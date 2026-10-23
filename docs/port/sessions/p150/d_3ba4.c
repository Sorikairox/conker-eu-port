s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 memcpy(s32, f32 *, s32);

// particle template handed to func_151307F0 (0x67 bytes used)
typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ s32 u4;
    /* 0x08 */ u16 u08;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 uC;
    /* 0x10 */ s32 u10;
    /* 0x14 */ u8 colour[7];
    /* 0x1B */ s8 u1B;
    /* 0x1C */ u8 u1C;
    /* 0x1D */ u8 u1D;
    /* 0x1E */ s16 u1E;
    /* 0x20 */ s16 u20;
    /* 0x22 */ s16 u22;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 size[2];
    /* 0x30 */ f32 pos[3];
    /* 0x3C */ u8 pad3C[0xC];
    /* 0x48 */ f32 vel[3];
    /* 0x54 */ f32 u54;
    /* 0x58 */ s32 u58;
    /* 0x5C */ u8 pad5C[4];
    /* 0x60 */ u8 u60;
    /* 0x61 */ u8 u61;
    /* 0x62 */ s8 u62;
    /* 0x63 */ s8 u63;
    /* 0x64 */ u8 pad64[2];
    /* 0x66 */ u8 u66;
} BurstParticle;

// particle_burst_spawn: spawns a burst of particles from a request (e.g. the pickup flash of func_151BF678):
// count = +0 + random [0, +2]; each particle gets the request's fixed fields, a random life (+0x10 / +0x12),
// value +0x14 / +0x18, size (+0x30 + random * +0x34), byte +0x23 / +0x24 and +0x54 + random * +0x58, and a
// velocity of speed +0x4C + random * +0x50 along yaw +0x44 / +0x48 and pitch +0x46 / +0x4A (256 steps per
// turn). It is created through func_151307F0(template, +0x64, 0, 4, owner, ownerArg) and its +0xA8 gets +0x68.
// tag = template byte 0x66.
void func_15153BA4(u8 *req, s32 tag, s32 owner, s32 ownerArg) {
    BurstParticle p;
    f32 spin;
    f32 speed;
    f32 sinPitch;
    f32 cosPitch;
    f32 sinYaw;
    f32 cosYaw;
    f32 size;
    f32 horiz;
    s16 yaw;
    s16 pitch;
    s32 part;
    s32 count;

    count = (u32) func_150ADA20() % (u32) (*(s16 *)(req + 0x2) + 1) + *(s16 *)(req + 0x0);
    spin = *(f32 *)(req + 0x68);
    p.u0 = *(s32 *)(req + 0x8);
    p.u4 = *(s32 *)(req + 0xC);
    p.u08 = *(u16 *)(req + 0x6);
    p.uC = 0;
    p.colour[0] = req[0x1C];
    p.colour[1] = req[0x1D];
    p.colour[2] = req[0x1E];
    p.colour[3] = req[0x1F];
    p.colour[4] = req[0x20];
    p.colour[5] = req[0x21];
    p.colour[6] = req[0x22];
    p.u1C = req[0x25];
    p.u1D = req[0x4];
    p.u1E = *(s16 *)(req + 0x26);
    p.u20 = *(s16 *)(req + 0x28);
    p.u22 = *(s16 *)(req + 0x2A);
    p.u24 = *(f32 *)(req + 0x2C);
    p.pos[0] = *(f32 *)(req + 0x38);
    p.pos[1] = *(f32 *)(req + 0x3C);
    p.pos[2] = *(f32 *)(req + 0x40);
    p.u58 = *(s32 *)(req + 0x5C);
    p.u60 = req[0x62];
    p.u61 = req[0x63];
    p.u62 = req[0x60];
    p.u63 = req[0x61];
    p.u66 = tag;

    for (; count != 0; count--) {
        yaw = (u32) func_150ADA20() % (u32) (*(s16 *)(req + 0x48) + 1) + *(s16 *)(req + 0x44);
        pitch = (u32) func_150ADA20() % (u32) (*(s16 *)(req + 0x4A) + 1) + *(s16 *)(req + 0x46);
        sinPitch = func_151423D8(pitch);
        cosPitch = func_151423D8(pitch - 0x40);
        sinYaw = func_151423D8(yaw);
        cosYaw = func_151423D8(yaw - 0x40);
        speed = func_150ADA68() * *(f32 *)(req + 0x50) + *(f32 *)(req + 0x4C);
        p.life = (u32) func_150ADA20() % (u32) (*(s16 *)(req + 0x12) + 1) + *(s16 *)(req + 0x10);
        p.u10 = (u32) func_150ADA20() % (u32) (*(s32 *)(req + 0x18) + 1) + *(s32 *)(req + 0x14);
        size = func_150ADA68() * *(f32 *)(req + 0x34) + *(f32 *)(req + 0x30);
        p.size[1] = size;
        p.size[0] = size;
        horiz = speed * sinPitch;
        p.vel[0] = horiz * cosYaw;
        p.vel[1] = -speed * cosPitch;
        p.vel[2] = horiz * sinYaw;
        p.u54 = func_150ADA68() * *(f32 *)(req + 0x58) + *(f32 *)(req + 0x54);
        p.u1B = (u32) func_150ADA20() % (u32) (req[0x24] + 1) + req[0x23];
        part = func_151307F0((s32) &p, req[0x64], 0, 4, owner, ownerArg);
        if (part != 0) {
            memcpy(part + 0xA8, &spin, 4);
        }
    }
}
