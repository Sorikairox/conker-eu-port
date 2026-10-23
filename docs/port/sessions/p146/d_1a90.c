extern s32 (*D_80087030[])(u8 *, s32, s32);
s32 func_1508154C(u8 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, s32 *, s32 *, s32 *, u8 *);
s32 func_15082020(f32 *, f32 *, u8 *, f32 *, f32 *, f32 *, f32 *);
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32 *, u8 *, f32 *, f32 *, f32 *, f32 *, s32 *, u8 *, f32);
// ray_cast_world: casts the ray (x, y, z) + t * (dx, dy, dz) against the level (unless noLevel) and the 25 objects
// of D_800CC2D0 (unless noObjects) and keeps the nearest hit closer than maxDist (0 = 9999999) in hit:
// +0 object, +4 distance (-1 = none), +0x8 point, +0x14 normal (model hits), +0x20 exit point, +0x2C start,
// +0x38 direction, +0x44 level surface, +0x56 / +0x58 / +0x5A model hit data, +0x59 kind (0 none, 1 level,
// 2 object bounds, 3 object model), +0x5C level material (D_800DBEF4 entry), +0x60 level hit extra. Objects are
// skipped when in skipMask, the caster's own slot (+0x124 - 1) or the caster itself, inactive, of type 3
// (+0x5), not hittable (+0xF8 bit 0x40), or rejected by filter D_80087030[filter](obj, caster, filterArg)
// (-1 = none). Without boundsOnly the object model is tested (func_1508154C) and its bounds only when that
// returns -1; an object linked (+0x65) to the previous model hit is not taken again. The original returns
// nothing (callers ignore the value); 0 here.
s32 func_15081A90(struct127 *caster, f32 x, f32 y, f32 z, f32 dx, f32 dy, f32 dz, u8 *hit, f32 maxDist, s32 noLevel,
                  s32 noObjects, s32 boundsOnly, s32 filter, s32 filterArg, s32 skipMask) {
    f32 start[3];
    f32 dir[3];
    u8 link[0x19];
    f32 point[3];
    f32 exitPoint[3];
    f32 normal[3];
    f32 dist;
    f32 dist2;
    f32 hx;
    f32 hy;
    f32 hz;
    s32 surface;
    s32 material;
    s32 modelA;
    s32 modelB;
    s32 modelC;
    u8 modelD[8];
    s32 own;
    s32 last;
    s32 res;
    s32 i;
    u8 *obj;

    start[0] = x;
    start[1] = y;
    start[2] = z;
    dir[0] = dx;
    dir[1] = dy;
    dir[2] = dz;
    *(f32 *)(hit + 0x4) = -1.0f;
    *(u8 **)(hit + 0x0) = NULL;
    hit[0x59] = 0;
    *(f32 *)(hit + 0x2C) = start[0];
    *(f32 *)(hit + 0x30) = start[1];
    *(f32 *)(hit + 0x34) = start[2];
    *(f32 *)(hit + 0x38) = dir[0];
    *(f32 *)(hit + 0x3C) = dir[1];
    *(u8 **)(hit + 0x5C) = NULL;
    *(s32 *)(hit + 0x60) = 0;
    *(f32 *)(hit + 0x40) = dir[2];
    last = -1;
    if (maxDist == 0.0f) {
        maxDist = 9999999.0f;
    }
    if (caster != NULL) {
        own = ((u8 *)caster)[0x124] - 1;
    } else {
        own = -1;
    }
    bzero(link, sizeof(link));
    for (i = 0; i < 25; i++) {
        obj = (u8 *)&D_800CC2D0[0] + i * 0x32C;
        if (*(s32 *)obj != 0 && obj[0x65] != 0) {
            link[obj[0x65] - 1] = i + 1;
        }
    }

    if (noLevel == 0 &&
        func_150ACEA0(x, y, z, dx, dy, dz, &surface, hit + 0x44, &hx, &hy, &hz, &dist, &material, hit + 0x60, 0.0f) !=
            0 &&
        dist < maxDist) {
        *(f32 *)(hit + 0x4) = dist;
        hit[0x59] = 1;
        *(f32 *)(hit + 0x8) = hx;
        *(f32 *)(hit + 0xC) = hy;
        *(f32 *)(hit + 0x20) = *(f32 *)(hit + 0x8);
        *(f32 *)(hit + 0x10) = hz;
        *(f32 *)(hit + 0x24) = *(f32 *)(hit + 0xC);
        *(f32 *)(hit + 0x28) = *(f32 *)(hit + 0x10);
        if (material != -1) {
            *(u8 **)(hit + 0x5C) = (u8 *)D_800DBEF4 + material * 0xA0;
        } else {
            *(u8 **)(hit + 0x5C) = NULL;
        }
    }

    if (noObjects != 0) {
        return 0;
    }
    for (i = 0; i < 25; i++) {
        if ((1 << i) & skipMask) {
            continue;
        }
        if (own == i) {
            continue;
        }
        obj = (u8 *)&D_800CC2D0[0] + i * 0x32C;
        if (*(s32 *)obj == 0 || obj[0x5] == 3 || obj == (u8 *)caster || !(*(s32 *)(obj + 0xF8) & 0x40)) {
            continue;
        }
        if ((s8)filter != -1 && D_80087030[(s8)filter](obj, (s32)caster, filterArg) == 0) {
            continue;
        }
        if (boundsOnly == 0) {
            res = func_1508154C(obj, start, dir, point, exitPoint, normal, &dist, &modelA, &modelB, &modelC, modelD);
            if (res > 0 && dist < maxDist &&
                (*(f32 *)(hit + 0x4) == -1.0f || dist < *(f32 *)(hit + 0x4)) && last != link[i]) {
                *(f32 *)(hit + 0x4) = dist;
                *(u8 **)(hit + 0x0) = obj;
                last = i + 1;
                hit[0x58] = modelC;
                *(s16 *)(hit + 0x56) = modelB;
                *(f32 *)(hit + 0x8) = point[0];
                *(f32 *)(hit + 0xC) = point[1];
                *(f32 *)(hit + 0x10) = point[2];
                *(f32 *)(hit + 0x14) = normal[0];
                *(f32 *)(hit + 0x18) = normal[1];
                *(f32 *)(hit + 0x1C) = normal[2];
                hit[0x5A] = modelA;
                *(f32 *)(hit + 0x20) = exitPoint[0];
                *(f32 *)(hit + 0x24) = exitPoint[1];
                hit[0x59] = 3;
                *(f32 *)(hit + 0x28) = exitPoint[2];
            }
            if (res != -1) {
                continue;
            }
        }
        if (func_15082020(start, dir, obj, point, exitPoint, &dist, &dist2) != 0 && dist < maxDist &&
            (*(f32 *)(hit + 0x4) == -1.0f || dist < *(f32 *)(hit + 0x4)) && last != link[i]) {
            *(f32 *)(hit + 0x4) = dist;
            *(u8 **)(hit + 0x0) = obj;
            last = i + 1;
            *(f32 *)(hit + 0x8) = point[0];
            *(f32 *)(hit + 0xC) = point[1];
            *(f32 *)(hit + 0x10) = point[2];
            *(f32 *)(hit + 0x20) = exitPoint[0];
            *(f32 *)(hit + 0x24) = exitPoint[1];
            hit[0x59] = 2;
            *(f32 *)(hit + 0x28) = exitPoint[2];
        }
    }
    return 0;
}
