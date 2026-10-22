u8 *func_1515EAB4(u8 *, s32, u8, u8, u8 *);
u8 *func_1515DE84(u8 *, s16, s32, s32, s32, s32, s32, s32, u8 *, u8 *, s32, s32, s32, s32);
extern s32 D_800DA230[];
extern u8 D_800DA240;
extern u8 D_800DA241;
extern u8 D_800D9FF0[];
/* Lights of a model part (arg1: +0x00 count, +0x04 out list, +0x08 per-player light buffers, +0x18 lookat,
 * +0x1C mask). kind (arg2) 1: the object's own light set (arg3 +0x301 / +0x302 / +0x304 / +0x314) when it is
 * alive and in room arg4, else (2) the level's default lights; other kinds: the nearest point lights at arg6. */
u8 *func_151462C8(u8 *gfx, u8 *arg1, u8 arg2, u8 *arg3, u8 arg4, s16 arg5, f32 *arg6, u8 arg7, s32 arg8) {
    s32 buf = *(s32 *)(arg1 + 8 + arg5 * 4);
    s32 lookat;
    s32 kind;
    s32 flags;

    if (buf == 0) {
        return gfx;
    }
    lookat = *(s32 *)(arg1 + 0x18);
    if (lookat == 0) {
        return gfx;
    }
    kind = arg2;
    if (arg2 == 1) {
        if (arg3 == NULL) {
            kind = 0;
        } else if ((*(s32 *)arg3 != 0) && (arg4 == arg3[0x3B]) && (arg3[4] != 0xFF) && (arg3[0x302] != 0)) {
            kind = 1;
        } else {
            kind = 2;
        }
    }
    if (kind == 1) {
        return func_1515EAB4(gfx, *(s32 *)(arg3 + 0x304 + arg5 * 4), arg3[0x301], arg3[0x302], *(u8 **)(arg3 + 0x314));
    }
    if (kind == 2) {
        return func_1515EAB4(gfx, D_800DA230[arg5], D_800DA240, D_800DA241, D_800D9FF0 + arg5 * 16 + D_800BE9C0 * 8);
    }
    flags = ((arg7 & 2) ? 0x10 : 0) | 8 | ((arg7 & 1) ? 2 : 0);
    return func_1515DE84(gfx, arg5, (s32)arg6[0], (s32)arg6[1], (s32)arg6[2], arg8, buf, *(s32 *)arg1, (u8 *)lookat,
                         arg1 + 4, *(s32 *)(arg1 + 0x1C), 0, flags, 0);
}
