f32 func_150489B0(u8);
f32 func_15048A40(u8 arg0);
s32 func_150A44A4(f32 x, f32 z, s32 tri, u8 *packed, f32 *out);
s32 func_1510E908(s16 **tris, s16 *verts, f32 *outA, f32 *outB);
void func_1510ED24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD);

/* blob_shadow_update: per frame, the blob shadow record rec (func_1510DEF0) of its owner *(rec + 0x110):
 * rec[0x120] 0 = an object (f32 position +0x14..+0x1C, floor height +0x180 (id 0x25 uses it as its height), floor
 * triangles +0x188 / +0x18C, size u16 +0x160 * f32 +0x14C, facing u16 +0x7A), 1 = a node with s16 position +0x10..
 * +0x14 (skipped when its byte +0x6E is 1; its floor comes from func_150A44A4 on the packed floor *(+0x94) + 0x128,
 * else func_1510ED24 fills it; size (byte +0x4D * 4) * f32 +0x2C). Stores the floor point at +0x114..+0x11C; above
 * the floor, gets the floor slope (func_1510E908), scales the shadow by size / clamp(200 + height, 800), sets the
 * alpha +0x122 (fade in by 5 per frame step when rec[0x124] & 1, else 32000 / distance up to 0xA0) and writes the
 * quad corners A, B, -A, -B (100 units along / across the facing, tilted onto the slope, normalised and scaled) into
 * the 4 vertices +0x90 of this frame's buffer (D_800BE9C0, 0x40 each); rec[0x123] = 1 when drawn.
 * Other rec[0x120] values are never created (the asm would use stale stack values); they do nothing here. */
void func_1510E004(u8 *rec) {
    u8 *o;
    s16 **tris;
    s16 *verts;
    u8 *packed;
    f32 a[3];
    f32 b[3];
    f32 x, y, z, floor_y;
    f32 size, dist, scale;
    f32 slope_x, slope_z;
    f32 s, c;
    f32 len_a, len_b;
    s32 alpha;
    u8 angle;
    s16 *vtx;
    s32 i;

    rec[0x123] = 0;
    if (rec[0x120] == 0) {
        o = *(u8 **) (rec + 0x110);
        x = *(f32 *) (o + 0x14);
        z = *(f32 *) (o + 0x1C);
        y = *(f32 *) (o + 0x18);
        floor_y = *(f32 *) (o + 0x180);
        if (o[4] == 0x25) {
            y = floor_y;
        }
        verts = (s16 *) (o + 0x18C);
        tris = *(s16 ***) (o + 0x188);
        size = *(u16 *) (o + 0x160) * *(f32 *) (o + 0x14C);
        angle = (*(u16 *) (o + 0x7A) >> 8) + 0x20;
    } else if (rec[0x120] == 1) {
        o = *(u8 **) (rec + 0x110);
        if (o[0x6E] == 1) {
            return;
        }
        packed = *(u8 **) (o + 0x94) + 0x128;
        if (func_150A44A4(*(s16 *) (o + 0x10), *(s16 *) (o + 0x14), 0, packed, &floor_y) == 0) {
            y = *(s16 *) (o + 0x12);
            func_1510ED24(0, (s32) packed, (s32) &floor_y, 0, 0, 0, *(s16 *) (o + 0x10), y, *(s16 *) (o + 0x14), y,
                          o[0x71] + 1, 0, -10000.0f, y);
        }
        tris = NULL;
        verts = (s16 *) packed;
        x = *(s16 *) (o + 0x10);
        y = *(s16 *) (o + 0x12);
        z = *(s16 *) (o + 0x14);
        angle = 0;
        size = (f32) (o[0x4D] * 4) * *(f32 *) (o + 0x2C);
    } else {
        return;
    }
    *(f32 *) (rec + 0x114) = x;
    *(f32 *) (rec + 0x118) = z;
    *(f32 *) (rec + 0x11C) = floor_y;
    if (y < floor_y) {
        return;
    }
    if (func_1510E908(tris, verts, &slope_x, &slope_z) == 0) {
        return;
    }
    if (size == 0.0f) {
        size = 1.0f;
    }
    dist = 200.0f + (y - floor_y);
    if (dist == 0.0f) {
        dist = 0.0001f;
    }
    if (dist > 800.0f) {
        dist = 800.0f;
    }
    scale = size / dist;
    if (rec[0x124] & 1) {
        alpha = rec[0x122];
        if (alpha != 0xFF) {
            alpha += D_800BE9E4 * 5;
            if (alpha >= 0x100) {
                alpha = 0xFF;
            }
        }
    } else {
        alpha = (s32) (32000.0f / dist);
        if (alpha >= 0xA1) {
            alpha = 0xA0;
        }
    }
    rec[0x122] = alpha;

    /* A = (0, -100) and B = (-100, 0) in x / z, turned by the facing */
    a[0] = 0.0f;
    a[2] = -100.0f;
    if (angle != 0) {
        s = func_15048A40(angle);
        c = func_150489B0(angle);
        a[0] = 0.0f * c + -100.0f * s;
        a[2] = -100.0f * c - 0.0f * s;
    }
    a[1] = a[2] * slope_z + slope_x * a[0];
    b[0] = -100.0f;
    b[2] = 0.0f;
    if (angle != 0) {
        b[0] = -100.0f * c + 0.0f;
        b[2] = 0.0f - -100.0f * s;
    }
    b[1] = b[2] * slope_z + slope_x * b[0];

    len_a = (a[0] * a[0] + a[1] * a[1]) + a[2] * a[2];
    if (1e8f < len_a) {
        len_a = 1e8f;
    }
    if (len_a < 10000.0f) {
        len_a = 10000.0f;
    }
    len_a = sqrtf(len_a);
    len_b = (b[0] * b[0] + b[1] * b[1]) + b[2] * b[2];
    if (1e8f < len_b) {
        len_b = 1e8f;
    }
    if (len_b < 10000.0f) {
        len_b = 10000.0f;
    }
    len_b = sqrtf(len_b);

    for (i = 0; i < 3; i++) {
        a[i] = a[i] * 100.0f * scale / len_a;
        b[i] = b[i] * 100.0f * scale / len_b;
        vtx = (s16 *) (rec + D_800BE9C0 * 0x40 + 0x90);
        vtx[i] = (s32) a[i];
        vtx[8 + i] = (s32) b[i];
        vtx[16 + i] = (s32) -a[i];
        vtx[24 + i] = (s32) -b[i];
    }
    rec[0x123] = 1;
}
