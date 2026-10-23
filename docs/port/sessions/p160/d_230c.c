s32 func_15081A90(s32, f32, f32, f32, f32, f32, f32, s32 *, f32, s32, s32, s32, s32, u8 *, s32);
extern f32 D_800AADA4;

typedef struct { f32 x, y, z; } V3_151C230C;
typedef struct { u16 h[9]; } Blk12_151C230C; /* 0x12 bytes, 2-byte aligned */

// ray_cast_through_passable: casts the ray `dir` from `start` (func_15081A90, hit record `hit`) and, while the hit
// object has (obj[0x4F] & 0x60) == 0x40 (a see-through object), records that object (its hit point in passPos,
// the distance so far in passDist, and a 0x24-byte pass record) and casts again from just behind it
// (D_800AADA4 along the hit normal). Finally restores the record's start (hit+0x2C) and stores the total distance
// in hit+4. Always returns 0.
s32 func_151C230C(s32 arg0, u8 *start, f32 *dir, u8 *hit, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s8 arg8,
                  u8 *arg9, f32 *passPos, f32 *passDist, u8 *pass, s32 argD) {
    V3_151C230C pos;
    f32 dist;
    f32 step;
    u8 *obj;
    s32 again;

    dist = 0.0f;
    *passDist = 0.0f;
    pos = *(V3_151C230C *)start;
    step = D_800AADA4;
    do {
        func_15081A90(arg0, pos.x, pos.y, pos.z, dir[0], dir[1], dir[2], (s32 *)hit, arg4, arg5, arg6, arg7, arg8,
                      arg9, argD);
        obj = *(u8 **)(hit + 0x5C);
        dist += *(f32 *)(hit + 4);
        again = 0;
        if (obj != NULL && (obj[0x4F] & 0x60) == 0x40) {
            pos.x = *(f32 *)(hit + 0x8) + *(f32 *)(hit + 0x38) * step;
            pos.y = *(f32 *)(hit + 0xC) + *(f32 *)(hit + 0x3C) * step;
            pos.z = *(f32 *)(hit + 0x10) + *(f32 *)(hit + 0x40) * step;
            *(V3_151C230C *)passPos = *(V3_151C230C *)(hit + 8);
            *passDist = dist;
            dist += step;
            *(f32 *)(pass + 0) = *(f32 *)(hit + 0xC);
            *(Blk12_151C230C *)(pass + 4) = *(Blk12_151C230C *)(hit + 0x44);
            *(s32 *)(pass + 0x18) = *(s32 *)(hit + 0x60);
            pass[0x1C] = 7;
            pass[0x1D] = 3;
            *(u8 **)(pass + 0x20) = obj;
            again = 1;
        }
    } while (again);
    *(V3_151C230C *)(hit + 0x2C) = *(V3_151C230C *)start;
    *(f32 *)(hit + 4) = dist;
    return 0;
}
