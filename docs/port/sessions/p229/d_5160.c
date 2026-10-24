#ifdef NON_MATCHING
s32 func_1510FE58(s32 x, s32 y, s32 z, s32 *tri);
extern s32 D_800DC26C; /* triangle table: 12 bytes per triangle */

// leaf_burst_spawn: spawns up to `count` falling leaves (func_15167A68 list 0xA, type 3) around (x, y, z) facing away
// from player `player`'s camera position (+0x2F8): position jittered by -63..64 in x / z, life 10..24, yaw = the
// direction +-15 degrees, speed jitter 0.01 * (-128..127), fall -1, size `base` + rand * `scale`, one of the two
// D_800DE2B8 models. Only the first leaf starts sound 0xA2. With `ground` & 1 each leaf records the floor below it
// (func_1510FE58: height +0xC8, surface type +0xE8, colour D_800A7550[(type >> 5) & 3] at +0xEC).
void func_15175160(s32 count, s32 slot, s32 x, s32 y, s32 z, s32 player, f32 base, f32 scale, s32 ground) {
    struct { f32 x, y, z; } d;
    s32 tri;
    u8 *pl;
    u8 *p;
    s32 yaw;
    s32 i;
    s32 onGround;
    s32 px, pz;
    s32 a;
    s32 v;
    s32 m;
    f32 fy;

    pl = (u8 *)D_800DBFF0 + player * 0x9A0;
    d.x = (f32)x - *(f32 *)(pl + 0x2F8);
    fy = (f32)y;
    d.y = fy - *(f32 *)(pl + 0x2FC);
    d.z = (f32)z - *(f32 *)(pl + 0x300);
    yaw = (s32)func_15048FC8((struct17 *)&d);

    for (i = 0; i < count; i++) {
        p = func_15167A68(0xA, 0, 0xF8, 1, 0xFF, 1);
        if (p == NULL) {
            break;
        }
        onGround = ground & 1;
        px = (func_150ADA20() & 0x7F) + x - 0x3F;
        pz = (func_150ADA20() & 0x7F) + z - 0x3F;
        *(s16 *)(p + 0x92) = 3;
        *(f32 *)(p + 0x98) = (f32)px;
        *(f32 *)(p + 0x9C) = fy;
        *(f32 *)(p + 0xA0) = (f32)pz;
        p[0x90] = slot;
        *(s16 *)(p + 0xA4) = (u32)func_150ADA20() % 15 + 10;
        *(s16 *)(p + 0xA6) = 1;
        a = (func_150ADA20() & 0x1F) + yaw - 15;
        if (a < 0) {
            a += 360;
        } else if (a >= 360) {
            a -= 360;
        }
        *(f32 *)(p + 0xA8) = (f32)((func_150ADA20() & 0x1F) - 15);
        *(f32 *)(p + 0xAC) = (f32)a;
        *(f32 *)(p + 0xB0) = 0.0f;
        *(f32 *)(p + 0xB4) = -1.0f;
        *(f32 *)(p + 0xB8) = (f32)((func_150ADA20() & 0xFF) - 0x80) * 0.01f;
        *(f32 *)(p + 0xBC) = 0.0f;
        *(f32 *)(p + 0xC0) = (f32)(func_150ADA20() & 0xFFFF) * (1.0f / 32768.0f) * scale + base;
        m = func_150ADA20() & 1;
        *(s32 *)(p + 0x94) = D_800DE2B8[m].x0;
        p[0xED] = m;
        if (i == 0) {
            *(u16 *)(p + 0xEE) = func_10010E78(0, 0xA2, 0x7D00, 0, 0, 0, px, y, pz, 1000, 4000);
        } else {
            *(u16 *)(p + 0xEE) = 0;
        }
        *(s32 *)(p + 0xE8) = 0;
        if (onGround) {
            *(s16 *)(p + 0x92) |= 0x80;
            *(f32 *)(p + 0xC8) = (f32)func_1510FE58(px, y, pz, &tri);
            v = 0;
            if (tri != 0) {
                v = ((s32 *)D_800DBE5C)[(tri - D_800DC26C) / 12];
            }
            *(s32 *)(p + 0xE8) = v;
            p[0xEC] = D_800A7550[((u32)v >> 5) & 3];
        } else {
            p[0xEC] = 0;
        }
        p[0xF0] = 0;
        p[0xF1] = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15175160.s")
#endif
