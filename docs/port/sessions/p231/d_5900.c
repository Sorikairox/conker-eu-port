#ifdef NON_MATCHING
s32 func_1510FE58(s32 x, s32 y, s32 z, s32 *tri);
s32 func_150ADA20(void);
extern s32 D_800DC26C; /* triangle table: 12 bytes per triangle */

// leaf_field_spawn: spawns up to `count` leaf / debris particles (func_15167A68 list `list` + rand % `listRand`)
// in a ring around (x, z): each axis offset is rand % (rMax - rMin) pushed out by rMin (away from 0), so |offset| is
// in rMin .. rMax - 1. Height: the floor below the point (func_1510FE58, +0xC8) when `mode` is 0, else
// y + rand % yRange (y when yRange is 0). flags (stored at +0x92): 0x40 = nothing when yRange <= 0; 0x10000 = yaw
// away from player `player`'s camera (+0x2F8) +-15 degrees (else a random yaw); 0x20000 = tilt (rand & 0x1F) - 15
// and fall -1. Model row (D_800DE2B8, +0xED): `model` + (rand & modelMask), + 0 for mask 0 and + the list offset for
// mask -1 (the asm reuses that register). Life 10..24, spin (rand & 0xFF) - 0x80 * 0.01, size base + rand * scale.
// The first particle of list 0xA starts sound 0xA2 (+0xEE). With `ground` & 1 the particle records the floor
// surface (+0xE8, colour D_800A7550[(type >> 5) & 3] at +0xEC; +0x92 |= 0x80). Called by game_eu_1B1010 (effects
// kinds with 18 arguments).
void func_15175900(s32 count, s32 slot, s32 x, s32 y, s32 z, s32 rMax, s32 player, s32 yRange, s32 rMin, s32 flags,
                   s32 list, s32 listRand, s32 model, s32 modelMask, s32 mode, f32 base, f32 scale, s32 ground) {
    struct { f32 x, y, z; } d;
    s32 tri;
    s32 yaw;
    s32 aimed;
    s32 tilt;
    s32 onGround;
    s32 i;
    s32 off;
    s32 range;
    s32 r;
    s32 px, py, pz;
    s32 a;
    u8 *pl;
    u8 *p;
    s32 v;

    if ((flags & 0x40) && yRange <= 0) {
        return;
    }
    aimed = flags & 0x10000;
    if (aimed) {
        pl = (u8 *)D_800DBFF0 + player * 0x9A0;
        d.x = (f32)x - *(f32 *)(pl + 0x2F8);
        d.y = (f32)y - *(f32 *)(pl + 0x2FC);
        d.z = (f32)z - *(f32 *)(pl + 0x300);
        yaw = (s32)func_15048FC8((struct17 *)&d);
    }
    for (i = 0; i < count; i++) {
        off = 0;
        if (listRand != 0) {
            off = (u32)func_150ADA20() % (u32)listRand;
        }
        p = func_15167A68(list + off, 0, 0xF8, 1, 0xFF, 1);
        if (p == NULL) {
            return;
        }
        onGround = ground & 1;
        tilt = flags & 0x20000;
        py = y;
        range = rMax - rMin;
        r = func_150ADA20() % range;
        px = (r < 0 ? r - rMin : r + rMin) + x;
        r = func_150ADA20() % range;
        pz = (r < 0 ? r - rMin : r + rMin) + z;
        if (mode == 0 || onGround) {
            *(f32 *)(p + 0xC8) = (f32)func_1510FE58(px, y, pz, &tri);
        }
        if (mode == 0) {
            py = (s32)*(f32 *)(p + 0xC8);
        } else if (yRange != 0) {
            py = y + (u32)func_150ADA20() % (u32)yRange;
        }
        p[0x90] = slot;
        *(s16 *)(p + 0x92) = flags;
        *(f32 *)(p + 0x98) = (f32)px;
        p[0x91] = mode;
        *(f32 *)(p + 0x9C) = (f32)py;
        *(f32 *)(p + 0xA0) = (f32)pz;
        *(s16 *)(p + 0xA4) = (u32)func_150ADA20() % 15 + 10;
        *(s16 *)(p + 0xA6) = 0;
        if (aimed) {
            a = (func_150ADA20() & 0x1F) + yaw - 15;
            if (a < 0) {
                a += 360;
            } else if (a >= 360) {
                a -= 360;
            }
        } else {
            a = (u32)func_150ADA20() % 360;
        }
        if (tilt) {
            *(f32 *)(p + 0xA8) = (f32)((func_150ADA20() & 0x1F) - 15);
            *(f32 *)(p + 0xB4) = -1.0f;
        } else {
            *(f32 *)(p + 0xA8) = 0.0f;
            *(f32 *)(p + 0xB4) = 0.0f;
        }
        *(f32 *)(p + 0xB0) = 0.0f;
        *(f32 *)(p + 0xAC) = (f32)a;
        *(f32 *)(p + 0xB8) = (f32)((func_150ADA20() & 0xFF) - 0x80) * 0.01f;
        *(f32 *)(p + 0xBC) = 0.0f;
        *(f32 *)(p + 0xC0) = (f32)(func_150ADA20() & 0xFFFF) * (1.0f / 32768.0f) * scale + base;
        if (modelMask == -1) {
            /* off (the list offset) is kept */
        } else if (modelMask == 0) {
            off = 0;
        } else {
            off = func_150ADA20() & modelMask;
        }
        off += model;
        p[0xED] = off;
        *(s32 *)(p + 0x94) = D_800DE2B8[off].x0;
        *(s16 *)(p + 0xD0) = x;
        *(s16 *)(p + 0xD2) = y;
        *(s16 *)(p + 0xD4) = z;
        *(s16 *)(p + 0xD8) = rMin;
        *(s16 *)(p + 0xD6) = rMax;
        *(s16 *)(p + 0xDC) = 0;
        *(s16 *)(p + 0xDE) = 0;
        *(s32 *)(p + 0xE8) = 0;
        *(f32 *)(p + 0xE0) = 0.0f;
        *(s16 *)(p + 0xDA) = yRange;
        if (i != 0) {
            *(u16 *)(p + 0xEE) = 0;
        } else if (list == 0xA) {
            *(u16 *)(p + 0xEE) = func_10010E78(0, 0xA2, 0x7D00, 0, 0, 0, px, py, pz, 1000, 4000);
        }
        if (onGround) {
            *(s16 *)(p + 0x92) |= 0x80;
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15175900.s")
#endif
