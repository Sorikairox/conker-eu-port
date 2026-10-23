s32 func_1514654C(struct127 *, s32, s32, s32 **, u8 **, s32);
extern s32 D_800A0DA0;
extern s32 D_800A0DAC;

s32 func_150D4FF0(u8 *arg0, u8 *arg1, struct127 *arg2, s32 arg3) {
    s32 *sp34;
    s32 *sp30;
    u8 *sp2C;
    u8 *sp28;

    if (arg2->unk1D4 != NULL) {
        sp30 = &D_800A0DA0;
        sp34 = &D_800A0DAC;
        sp28 = arg0;
        sp2C = arg1;
        if (func_1514654C(arg2, arg3, 0, &sp30, &sp28, 2) != 0) {
            return 1;
        }
        return 0;
    }
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) arg2->x_position;
    (*(f32 *)((u8 *)arg0 + 4)) = (f32) (arg2->y_position + 100.0f);
    (*(f32 *)((u8 *)arg0 + 8)) = (f32) arg2->z_position;
    (*(f32 *)((u8 *)arg1 + 0)) = (f32) arg2->x_position;
    (*(f32 *)((u8 *)arg1 + 4)) = (f32) (arg2->y_position + 100.0f + 500.0f);
    (*(f32 *)((u8 *)arg1 + 8)) = (f32) arg2->z_position;
    return 2;
}
