extern f32 D_80098CD0;
extern f32 D_80098CD4;
void func_1503EE68(s32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    f32 v[3];
    s32 i;
    s32 mask;
    s32 base;

    if (arg3 != 0) {
        mask = 0x80;
        base = 0x7F;
    } else {
        mask = 0xFF;
        base = 0;
    }
    v[0] = v[2] = arg1 * D_80098CD0;
    v[1] = arg2 * D_80098CD0;
    for (i = 0; i < 3; i++) {
        ((f32 *)(arg0 + 0x48))[i] = ((f32 *)(arg0 + 0x48))[i] * ((f32)((func_150ADA20() & mask) + base) * v[i] + 2.0f);
    }
    for (i = 0; i < 3; i++) {
        ((f32 *)(arg0 + 0x54))[i] = (f32)((func_150ADA20() & 0xFF) - 0x80) * 0.03125f;
    }
    *(f32 *)(arg0 + 0x60) = D_80098CD4;
}
