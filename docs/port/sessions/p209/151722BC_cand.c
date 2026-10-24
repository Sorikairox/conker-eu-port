extern s32 D_8008CDEC; /* sprite texture descriptors (u8 * per id): u16 width / height at +6 / +8 */
s32 func_15173090(u8 *, f32, f32, f32, f32, s32, s32, s32);

// sprite_spawn_at: allocates a sprite (func_15172210: kind `kind`, texture `tex`, flags ...) and places it at
// (x, y, z): normally through func_15173090 (size `size`, `arg7`, `radius`; the sprite is freed again with
// func_1516972C when that fails); with flags bit 1 as a flat quad of half side `radius` at height y, UVs from the
// texture's size (+6 / +8, + 0x100, << 5), 0x2000 on +0x18 / +0x1A / +0x2A / +0x48.
void func_151722BC(f32 x, f32 y, f32 z, s16 kind, u16 arg4, u8 tex, f32 size, s32 arg7, s32 radius, s32 flags,
                   s32 argA, s32 argB, u8 argC, s32 argD) {
    u8 *v;
    u8 *t;
    f32 r;
    s16 h;

    v = func_15172210(kind, arg4, tex, flags, argA, argB, argC, argD);
    if (v == NULL) {
        return;
    }
    if (!(flags & 2)) {
        if (func_15173090(v + 0x10, x, y, z, size, arg7, radius,
                          *(u16 *) (((u8 **) &D_8008CDEC)[v[0x58]] + 6)) == 0) {
            func_1516972C((struct102 *) v);
        }
        return;
    }
    r = radius;
    h = (s32) y;
    *(s16 *) (v + 0x42) = h;
    *(s16 *) (v + 0x32) = h;
    *(s16 *) (v + 0x22) = h;
    *(s16 *) (v + 0x12) = h;
    *(s16 *) (v + 0x40) = (s32) (x - r);
    *(s16 *) (v + 0x10) = (s32) (x - r);
    *(s16 *) (v + 0x48) = 0x2000;
    *(s16 *) (v + 0x30) = (s32) (r + x);
    *(s16 *) (v + 0x20) = (s32) (r + x);
    *(s16 *) (v + 0x18) = *(s16 *) (v + 0x48);
    *(s16 *) (v + 0x24) = (s32) (z - r);
    *(s16 *) (v + 0x14) = (s32) (z - r);
    *(s16 *) (v + 0x44) = (s32) (r + z);
    *(s16 *) (v + 0x34) = (s32) (r + z);
    t = ((u8 **) &D_8008CDEC)[tex];
    *(s16 *) (v + 0x2A) = 0x2000;
    *(s16 *) (v + 0x38) = (*(u16 *) (t + 6) + 0x100) << 5;
    *(s16 *) (v + 0x28) = (*(u16 *) (t + 6) + 0x100) << 5;
    *(s16 *) (v + 0x1A) = *(s16 *) (v + 0x2A);
    *(s16 *) (v + 0x4A) = (*(u16 *) (t + 8) + 0x100) << 5;
    *(s16 *) (v + 0x3A) = (*(u16 *) (t + 8) + 0x100) << 5;
}
