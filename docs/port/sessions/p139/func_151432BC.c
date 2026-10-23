/*
 * spawn_region_random_point: random point inside the spawn region `rgn` (s16 centre x / y / z +0 / +2 / +4, s16
 * radius +6, s16 height +8, s16 half depth +0xA, f32 angle in degrees +0x10, shape = +0x15 & 3). Writes x, z and
 * the vertical span top / bottom:
 *   0 disc: random byte direction, random distance < radius; top = y + height, bottom = y;
 *   1 the same disc with bottom = y - height;
 *   2 box rotated by the angle (degrees * 256 / 360 as a byte; IDO f32 -> u32 conversion): random offsets
 *     in -radius..radius and -depth..depth; top = y + height, bottom = y;
 *   3 the centre line: x, z, top = y + height, bottom = y - height.
 * (func_151423D8 = byte-angle sine; x += d * sin(a), z -= d * sin(a - 0x40).) Returns 0 (callers declare s32 or
 * void and ignore it; the asm leaves no defined value).
 */
s32 func_151432BC(u8 *rgn, f32 *x, f32 *z, f32 *top, f32 *bottom) {
    s16 *r = (s16 *) rgn;
    f32 c, s;
    f32 d;
    f32 u, v;
    f32 deg;
    u32 a;
    u8 ang;

    switch (rgn[0x15] & 3) {
        case 0:
            ang = func_150ADA20();
            c = func_151423D8((ang - 0x40) & 0xFF);
            s = func_151423D8(ang);
            d = func_150ADA68() * (f32) r[3];
            *x = (f32) r[0] + d * s;
            *z = (f32) r[2] - d * c;
            *top = (f32) (r[1] + r[4]);
            *bottom = (f32) r[1];
            break;
        case 1:
            ang = func_150ADA20();
            c = func_151423D8((ang - 0x40) & 0xFF);
            s = func_151423D8(ang);
            d = func_150ADA68() * (f32) r[3];
            *x = (f32) r[0] + d * s;
            *z = (f32) r[2] - d * c;
            *top = (f32) (r[1] + r[4]);
            *bottom = (f32) (r[1] - r[4]);
            break;
        case 2:
            deg = *(f32 *) (rgn + 0x10) * 0.7111111f;
            /* f32 -> u32 as IDO converts it (negative / NaN / too large -> 0xFFFFFFFF); only the low byte is used */
            if (deg >= 2147483648.0f) {
                a = (deg - 2147483648.0f < 2147483648.0f) ? ((u32) (s32) (deg - 2147483648.0f) | 0x80000000)
                                                           : 0xFFFFFFFF;
            } else if (deg > -1.0f) {
                a = (u32) (s32) deg;
            } else {
                a = 0xFFFFFFFF;
            }
            ang = a;
            c = func_151423D8((a - 0x40) & 0xFF);
            s = func_151423D8(ang);
            u = func_150ADA68() * ((f32) r[3] + (f32) r[3]) + (f32) -r[3];
            v = func_150ADA68() * ((f32) r[5] + (f32) r[5]) + (f32) -r[5];
            *x = (f32) r[0] + (u * s + v * c);
            *z = (f32) r[2] + (v * s - u * c);
            *top = (f32) (r[1] + r[4]);
            *bottom = (f32) r[1];
            break;
        default:
            *x = (f32) r[0];
            *z = (f32) r[2];
            *top = (f32) (r[1] + r[4]);
            *bottom = (f32) (r[1] - r[4]);
            break;
    }
    return 0;
}
