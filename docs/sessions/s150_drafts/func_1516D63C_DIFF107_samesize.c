extern u16 D_80090912;
extern u16 D_80090932;
extern f32 D_800A71C4;
extern f32 D_800A71C8;

void func_1516D63C(u8 *arg0, f32 *arg1, f32 *arg2, s32 arg3) {
    f32 b[4];
    f32 off;
    f32 x;

    off = *(f32 *)(arg0 + 0x38) / (u32)D_80090912 * (u32)D_80090932 * 0.25f * *(f32 *)(arg0 + 0x28);
    x = cosf(*(f32 *)(arg0 + 0x58) + D_800A71C4) * (*(f32 *)(arg0 + 0x38) * 0.5f) * D_800A71C8 * *(f32 *)(arg0 + 0x28) + *arg1 - off;
    b[2] = *arg2;
    b[3] = b[2] - *(f32 *)(arg0 + 0x3C);
    b[1] = x - (*(f32 *)(arg0 + 0x38) * 0.5f);
    b[0] = (*(f32 *)(arg0 + 0x38) * 0.5f) + x;
    if (arg0 != NULL) {
        if (b[3] < *(f32 *)((u8 *)D_800BE628 + 0x24)) {
            *arg2 = *(f32 *)((u8 *)D_800BE628 + 0x24) + *(f32 *)(arg0 + 0x3C);
        } else if (*(f32 *)((u8 *)D_800BE628 + 0x28) < b[2]) {
            *arg2 = *(f32 *)((u8 *)D_800BE628 + 0x28);
        }
        if (b[1] < *(f32 *)((u8 *)D_800BE628 + 0x2C)) {
            *arg1 -= b[1] - *(f32 *)((u8 *)D_800BE628 + 0x2C);
        } else if (*(f32 *)((u8 *)D_800BE628 + 0x30) < b[0]) {
            *arg1 += *(f32 *)((u8 *)D_800BE628 + 0x30) - b[0];
        }
        *arg1 = (s32)*arg1;
        *arg2 = (s32)*arg2;
    }
}
