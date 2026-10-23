extern s32 D_8008ADA0;

/*
 * spawn_ring_emit: emits count (s16) points on a circle of radius r around (x, y, z) in the x/z plane, starting at
 * the byte angle angle0 and stepping by the signed byte step (wrapping at 256). Each point goes to the spawn
 * handler kind of D_8008ADA0 as (1, i, x + r * sin(a - 0x40), y, z + r * sin(a), x, y, z, a, angle0, r, arg8,
 * arg9, argA, argB) (func_151423D8 = byte-angle sine); the walk stops early when a handler returns 0, a missing
 * handler skips the point. Returns 0 (callers declare s32 and ignore it; the asm leaves no defined value).
 */
s32 func_1514C860(f32 x, f32 y, f32 z, f32 r, u8 angle0, s8 step, s16 count, u8 kind, s32 arg8, f32 arg9, s32 argA,
                  u8 argB) {
    s32 (*handler)(s32, s16, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, f32, s32, s32);
    s32 a = angle0;
    f32 c, s;
    s16 i;

    for (i = 0; i < count; i++) {
        c = func_151423D8((a - 0x40) & 0xFF);
        s = func_151423D8(a & 0xFF);
        handler = ((void **) &D_8008ADA0)[kind];
        if (handler != NULL && handler(1, i, x + r * c, y, z + r * s, x, y, z, a, angle0, r, arg8, arg9, argA, argB) == 0) {
            break;
        }
        a = (a + step) & 0xFF;
    }
    return 0;
}
