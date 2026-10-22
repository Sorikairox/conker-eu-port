void func_150A7DA0(f32 (*)[4], s32, s32, s32); /* axis as f32 bit patterns (game_D5250.c) */
void func_150A8050(f32 (*)[4], f32, f32, f32);
void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_150A7E40(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);

/* P64 (level load): bounding box of a 0x34-byte zone (s16 x / y / z at +0, size +6 / +8 / +0xA, f32 angles +0xC /
 * +0x10, shape = +0x15 & 3) into the 0x28-byte zone record `out` (s16 min x / max x / min y / max y / min z / max z
 * at +0x1A..+0x24). Shape 0: cylinder-like (size6, size8 / 2, size6), 1: cube (size6), 2: box (size6, size8 / 2,
 * sizeA), each rotated by func_150A7DA0 / func_150A8050 except shape 1; shape 3 gives the point box. The eight
 * corners (+-1, +-1, +-1) of the transformed unit cube are taken; min / max start at 0, so the box always holds the
 * zone origin, and a corner only raises the max when it did not lower the min (as the asm does). */
void func_15017FA4(u8 *zone, u8 *out) {
    f32 rot[4][4];
    f32 m[4][4];
    f32 cx, cy, cz;
    f32 px, py, pz;
    s32 point_only = FALSE;
    s32 min_x = 0, max_x = 0, min_y = 0, max_y = 0, min_z = 0, max_z = 0;
    s32 i;
    union {
        f32 f;
        s32 bits;
    } sx, sy, sz; /* functions.h declares func_150A7CB0 (scale matrix) with s32 arguments: f32 bit patterns */

    switch (zone[0x15] & 3) {
        case 0:
            func_150A7DA0(rot, 0, 0x3F800000, 0); /* (0, 1.0f, 0) */
            sx.f = *(s16 *)(zone + 6);
            sy.f = *(s16 *)(zone + 8) * 0.5f;
            sz.f = *(s16 *)(zone + 6);
            func_150A7CB0(m, sx.bits, sy.bits, sz.bits);
            func_150A7A48(rot, m, m);
            func_150A8050(rot, *(f32 *)(zone + 0xC), *(f32 *)(zone + 0x10), 0.0f);
            func_150A7A48(m, rot, m);
            break;
        case 1:
            sx.f = *(s16 *)(zone + 6);
            sy.f = *(s16 *)(zone + 6);
            sz.f = *(s16 *)(zone + 6);
            func_150A7CB0(m, sx.bits, sy.bits, sz.bits);
            break;
        case 2:
            func_150A7DA0(rot, 0, 0x3F800000, 0); /* (0, 1.0f, 0) */
            sx.f = *(s16 *)(zone + 6);
            sy.f = *(s16 *)(zone + 8) * 0.5f;
            sz.f = *(s16 *)(zone + 0xA);
            func_150A7CB0(m, sx.bits, sy.bits, sz.bits);
            func_150A7A48(rot, m, m);
            func_150A8050(rot, *(f32 *)(zone + 0xC), *(f32 *)(zone + 0x10), 0.0f);
            func_150A7A48(m, rot, m);
            break;
        default:
            point_only = TRUE;
            break;
    }

    if (!point_only) {
        for (i = 0; i < 8; i++) {
            cx = (i & 1) ? 1.0f : -1.0f;
            cy = (i & 2) ? 1.0f : -1.0f;
            cz = (i & 4) ? 1.0f : -1.0f;
            func_150A7E40(m, cx, cy, cz, &px, &py, &pz);
            if (px < min_x) {
                min_x = px;
            } else if (max_x < px) {
                max_x = px;
            }
            if (py < min_y) {
                min_y = py;
            } else if (max_y < py) {
                max_y = py;
            }
            if (pz < min_z) {
                min_z = pz;
            } else if (max_z < pz) {
                max_z = pz;
            }
        }
    }
    *(s16 *)(out + 0x1A) = *(s16 *)(zone + 0) + min_x;
    *(s16 *)(out + 0x1C) = *(s16 *)(zone + 0) + max_x;
    *(s16 *)(out + 0x1E) = *(s16 *)(zone + 2) + min_y;
    *(s16 *)(out + 0x20) = *(s16 *)(zone + 2) + max_y;
    *(s16 *)(out + 0x22) = *(s16 *)(zone + 4) + min_z;
    *(s16 *)(out + 0x24) = *(s16 *)(zone + 4) + max_z;
}
