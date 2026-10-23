void func_1512BB6C(struct_eu_158110 *arg0, s32 arg1, s32 arg2);
extern s16 D_800DC634[];
extern s16 D_800DC636[];

/* Stick threshold test for free-camera axis `out` (called twice by func_1512B728): limit = the camera's player
 * table entry (D_800DC634 / D_800DC636 by `second`, 0x20 bytes per player, 8 per +0x1B4 slot), doubled with
 * +0x84 bit 0x8000. Below `lo` with `hi` past `value` on either side: direction 2 (hi > value) or 1 (hi < value),
 * func_1512BB6C(out, hi, lo) (it reads a2 = lo, which the asm leaves there), return 1. Otherwise the axis is reset
 * (+0 / +1 = 0, +8 = 0xFFFC) and 0 is returned. */
s32 func_1512BBA0(u8 *cam, u8 *out, s32 lo, s32 hi, s32 value, s32 second) {
    s32 v;
    s32 off = cam[0x23D] * 0x20 + *(s16 *)(cam + 0x1B4) * 8;

    if (second == 0) {
        v = *(s16 *)((u8 *)D_800DC634 + off);
    } else {
        v = *(s16 *)((u8 *)D_800DC636 + off);
    }
    if (*(s32 *)(cam + 0x84) & 0x8000) {
        v = (s16)(v << 1);
    }
    if (v < lo && hi < value) {
        out[0] = 2;
        func_1512BB6C((struct_eu_158110 *)out, hi, lo);
        return 1;
    }
    if (v < lo && value < hi) {
        out[0] = 1;
        func_1512BB6C((struct_eu_158110 *)out, hi, lo);
        return 1;
    }
    out[1] = 0;
    out[0] = 0;
    *(s32 *)(out + 8) = 0xFFFC;
    return 0;
}
