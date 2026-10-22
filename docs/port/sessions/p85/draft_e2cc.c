void func_150A7E40(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);
void func_15170648(f32 *quad, f32 x, f32 z, s32 arg3, f32 size, s32 arg5, s32 arg6, s32 arg7, s32 alpha, s32 arg9);

/*
 * P85: script command 11: a 200 x 200 square around the current object (D_800D154C) in its model space
 * (corners (+-100, 0, +-100) through the object matrix +0x1D4, at the object's height +0x180) is passed to
 * func_15170648 with the object position (+0x14 / +0x1C) and half the object's +0x14C size. Nothing without a matrix.
 */
void func_1506E2CC(void) {
    f32 quad[4][3];
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    if (*(void **) ((u8 *) D_800D154C + 0x1D4) == NULL) {
        return;
    }
    x = 100.0f;
    z = 100.0f;
    for (i = 0; i < 4; i++) {
        y = 0.0f;
        func_150A7E40(*(f32 (**)[4]) ((u8 *) D_800D154C + 0x1D4), x, 0.0f, z, &x, &y, &z);
        quad[i][0] = x;
        quad[i][1] = *(f32 *) ((u8 *) D_800D154C + 0x180);
        quad[i][2] = z;
        if (i == 0) {
            z = 100.0f;
            x = -100.0f;
        } else if (i == 1) {
            x = -100.0f;
            z = -100.0f;
        } else if (i == 2) {
            x = 100.0f;
            z = -100.0f;
        }
    }
    func_15170648(&quad[0][0], *(f32 *) ((u8 *) D_800D154C + 0x14), *(f32 *) ((u8 *) D_800D154C + 0x1C), 5,
                  *(f32 *) ((u8 *) D_800D154C + 0x14C) * 0.5f, 0, 4, 4, 0xFF, 0);
}
