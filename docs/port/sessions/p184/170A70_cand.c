extern u16 D_800CC76A;
s32 func_151EFDD0(void);
f32 func_150489B0(s32 angle); // defined (u8); the file's unprototyped declaration rules out u8 here
// spark_particle_spawn: one spark at (x, y, z) thrown in direction `angle` (the camera angle D_800CC76A when `flare`
// is 0) with a random pitch (rand % 50, both signs), horizontal speed from sin / cos of the angle, fixed fall -0x32;
// flare != 0: long-lived flare particle (func_1516DA58), else short spark (func_1516DF0C). alpha and arg6 pass through.
// Called by ambient_emitters_update (func_1517C11C) for torch / fire sparks and flare-ups.
void func_15170A70(s32 x, s32 y, s32 z, s32 angle, s32 flare, s32 alpha, s32 arg6) {
    s32 pitch;
    f32 dirX;
    f32 dirZ;
    f32 tilt;
    f32 dx;
    f32 dz;
    f32 dy;
    s32 vx;
    s32 vz;
    s32 vy;

    if (flare == 0) {
        angle = D_800CC76A;
    }
    pitch = func_151EFDD0() % 50;
    dirX = func_150489B0(angle & 0xFF);
    dirZ = -func_15048A40(angle & 0xFF);
    tilt = func_150489B0(pitch & 0xFF);
    dx = dirX * tilt;
    dz = dirZ * tilt;
    dy = 0.0f;
    dx = dx + dx;
    dz = dz + dz;
    dy = dy + dy;
    vx = dx * 256.0f;
    vz = dz * 256.0f;
    vy = dy * 256.0f;
    if (flare != 0) {
        func_1516DA58(x, y, z, 0x2A, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 6, vx >> 8, vx & 0xFF, vz >> 8, vz & 0xFF,
                      0, 0, 0, 0, 0, 1, 0x200, 0x166, 0xFF, vy - 0x32, 0, 0, alpha & 0xFF, arg6);
    } else {
        func_1516DF0C(x, y, z, 0x2A, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 6, vx >> 8, vx & 0xFF, vz >> 8, vz & 0xFF,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x200, 0x166, 0, 0, 0x14, 0, 0, 0xFF, 0xFF, vy - 0x32, 0xC8, 9,
                      1, 0, 1, 0x32, 0x14, 0, 0, 0, alpha & 0xFF, arg6);
    }
}
