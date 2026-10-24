#ifdef NON_MATCHING
void func_1510F800(s32 arg0);
s32 func_150A3F50(s32 x, s32 z);
extern s32 D_800D3720; /* floor candidates (16 bytes: +0 height in 24.8) left by func_150A3F50 */

// leaf_drop_spawn: spawns up to `count` leaves of model row 7 (func_15167A68 list 0x13) in a `width` square around
// (x, z) at height y: life 4..6, spin / tilt jitter, size `base` + rand * `scale`. Each leaf takes the lowest floor
// below it (func_150A3F50; none -> the leaf is freed with func_1516979C). mode 0 (after func_1510F800(0)) puts the
// leaf 10 above that floor in state 1; otherwise it falls from 300..427 above it in state 4 (+0x91 = 2).
// `player` is not used.
void func_15175514(s32 count, s32 slot, s32 x, s32 y, s32 z, s32 width, s32 player, s32 mode, f32 base, f32 scale) {
    u8 *p;
    s32 i;
    s32 k;
    s32 n;
    s32 half;
    s32 px, pz;
    s32 floorY;
    s32 h;

    if (mode == 0) {
        func_1510F800(0);
    }
    for (i = 0; i < count; i++) {
        p = func_15167A68(0x13, 0, 0xF8, 1, 0xFF, 1);
        if (p == NULL) {
            break;
        }
        half = width >> 1;
        px = (u32)func_150ADA20() % width + x - half;
        pz = (u32)func_150ADA20() % width + z - half;
        *(f32 *)(p + 0x98) = (f32)px;
        *(f32 *)(p + 0x9C) = (f32)y;
        *(f32 *)(p + 0xA0) = (f32)pz;
        p[0x90] = slot;
        *(s16 *)(p + 0xA4) = (u32)func_150ADA20() % 3 + 4;
        *(s16 *)(p + 0xA6) = 0;
        *(f32 *)(p + 0xA8) = (f32)((func_150ADA20() & 0x1F) - 15);
        *(f32 *)(p + 0xAC) = (f32)((u32)func_150ADA20() % 360);
        *(f32 *)(p + 0xB0) = (f32)((func_150ADA20() & 0x1F) - 15);
        *(f32 *)(p + 0xB4) = 0.0f;
        *(f32 *)(p + 0xB8) = 3.0f;
        *(f32 *)(p + 0xBC) = 0.0f;
        *(f32 *)(p + 0xC0) = (f32)(func_150ADA20() & 0xFFFF) * (1.0f / 32768.0f) * scale + base;
        *(s32 *)(p + 0x94) = D_800DE2B8[7].x0;
        p[0xED] = 7;

        n = func_150A3F50(px, pz);
        if (n == 0) {
            func_1516979C((struct102 *)p);
            continue;
        }
        floorY = (&D_800D3720)[0];
        for (k = 1; k < n; k++) {
            h = (&D_800D3720)[k * 4];
            if (h < floorY) {
                floorY = h;
            }
        }
        floorY >>= 8;
        *(f32 *)(p + 0xC8) = (f32)floorY;
        if (mode == 0) {
            p[0x91] = 0;
            *(s16 *)(p + 0x92) = 1;
            *(f32 *)(p + 0x9C) = (f32)(floorY + 10);
        } else {
            p[0x91] = 2;
            *(s16 *)(p + 0x92) = 4;
            *(f32 *)(p + 0xE4) = (f32)((func_150ADA20() & 0x7F) + floorY + 300);
            *(f32 *)(p + 0x9C) = (f32)((func_150ADA20() & 0x7F) + floorY + 300);
        }
        *(f32 *)(p + 0xCC) = 0.0f;
        *(s16 *)(p + 0xD0) = x;
        *(s16 *)(p + 0xD4) = z;
        *(s16 *)(p + 0xD6) = half;
        *(f32 *)(p + 0xE0) = 0.0f;
        *(s16 *)(p + 0xDC) = 0;
        *(s32 *)(p + 0xE8) = 0;
        p[0xEC] = 0;
        p[0xF0] = 0;
        p[0xF1] = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15175514.s")
#endif
