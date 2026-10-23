/*
 * drift_object_spawn: creates an object of the given type (func_15167A68(type, 0, 0xB8, 1, 0xFF, 1)) and sets it up:
 * position (x, y, z) at +0x90/+0x92/+0x94, s16 velocity +0xA0 / +0xA2 / +0xA4 = (random in -spread/2..,
 * (s8) tilt, random), +0x96..+0x9A cleared, random byte spins +0x9C..+0x9E (each rand % jitter - jitter / 2),
 * scale +0xA8 = (140 + rand & 0x7F) * 0.01, +0xA6 = arg5, +0x9F = colour, +0xAC = mode, +0xAE = arg9, +0xB2 = 0,
 * +0xB3 = 0xFF. Mode 5 starts it one 4x velocity step ahead (x += 4 vx, y -= 4 vy, z += 4 vz). Nothing when
 * the object cannot be created.
 */
void func_1517A550(u8 colour, s16 x, s16 y, s16 z, s8 tilt, u16 arg5, u16 mode, u8 spread, u8 jitter, u8 arg9,
                   s32 type) {
    u8 *obj = func_15167A68(type, 0, 0xB8, 1, 0xFF, 1);

    if (obj == NULL) {
        return;
    }
    *(s16 *) (obj + 0x90) = x;
    *(s16 *) (obj + 0x92) = y;
    *(s16 *) (obj + 0x94) = z;
    *(s16 *) (obj + 0xA2) = tilt;
    *(s16 *) (obj + 0xA0) = (u32) func_150ADA20() % spread - (spread >> 1);
    *(s16 *) (obj + 0xA4) = (u32) func_150ADA20() % spread - (spread >> 1);
    if (mode == 5) {
        *(s16 *) (obj + 0x90) += *(s16 *) (obj + 0xA0) * 4;
        *(s16 *) (obj + 0x92) -= *(s16 *) (obj + 0xA2) * 4;
        *(s16 *) (obj + 0x94) += *(s16 *) (obj + 0xA4) * 4;
    }
    *(s16 *) (obj + 0x96) = 0;
    *(s16 *) (obj + 0x98) = 0;
    *(s16 *) (obj + 0x9A) = 0;
    obj[0x9C] = (u32) func_150ADA20() % jitter - (jitter >> 1);
    obj[0x9D] = (u32) func_150ADA20() % jitter - (jitter >> 1);
    obj[0x9E] = (u32) func_150ADA20() % jitter - (jitter >> 1);
    *(f32 *) (obj + 0xA8) = (f32) ((func_150ADA20() & 0x7F) + 0x8C) * 0.01f;
    *(u16 *) (obj + 0xA6) = arg5;
    obj[0x9F] = colour;
    *(u16 *) (obj + 0xAC) = mode;
    obj[0xB2] = 0;
    obj[0xB3] = 0xFF;
    *(s16 *) (obj + 0xAE) = arg9;
}
