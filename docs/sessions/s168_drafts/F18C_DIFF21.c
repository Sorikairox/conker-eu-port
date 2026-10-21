s32 func_15095A4C(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32);
typedef struct {
    s32 shift;
    s32 base;
} Tbl18C;
extern Tbl18C D_800899D0[];

s32 func_1517F18C(u8 *arg0, u32 *arg1) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;
    u16 k;
    Tbl18C *t;
    f32 sx;
    f32 sz;

    if (func_15095A4C(*(f32 *)(arg0 + 0), *(f32 *)(arg0 + 4), *(f32 *)(arg0 + 8), (f32 *)(arg0 + 0xC), (f32 *)(arg0 + 0x10), &sx, &sz, 4000.0f) == 1) {
        if (arg0[0x2E] & 4) {
            dx = *(f32 *)(arg0 + 0) - D_800DBFF0->unk2F8;
            dy = *(f32 *)(arg0 + 4) - D_800DBFF0->unk2FC;
            dz = *(f32 *)(arg0 + 8) - D_800DBFF0->unk300;
            len = sqrtf(dx * dx + dy * dy + dz * dz);
            if ((dx * *(f32 *)(arg0 + 0x14) + dy * *(f32 *)(arg0 + 0x18) + dz * *(f32 *)(arg0 + 0x1C)) / len < *(f32 *)(arg0 + 0x20)) {
                return 1;
            }
        }
        k = *(u16 *)(arg0 + 0x2A);
        t = &D_800899D0[k >> 13];
        *arg1 = (u32)(t->base + (((k >> 2) & 0x7FF) << t->shift)) >> 3;
        *(u16 *)(arg0 + 0x2C) = (u32)((*(s16 *)((u8 *)D_800BE628 + D_800BE9C0 * 0x10 + 0x4C) + (sx / sz) * *(s16 *)((u8 *)D_800BE628 + D_800BE9C0 * 0x10 + 0x44)) * 32.0f);
        return 1;
    }
    return 0;
}
