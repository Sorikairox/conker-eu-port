void func_150A7E40(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);
void func_15187B50(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7);
void func_15170648(f32 *quad, f32 x, f32 z, s32 arg3, f32 size, s32 arg5, s32 arg6, s32 arg7, s32 alpha, s32 arg9);

/*
 * P85: script command 8: as func_1506E2CC (command 11) with a 540 x 540 square (corners (+-270, 0, +-270) through
 * the object matrix +0x1D4, at the object's height +0x180); each corner also goes to func_15187B50 (corner x,
 * transformed y, z, 30, 20, 7, 0.13, 0.1), and func_15170648 gets 4 and the full +0x14C size.
 */
void func_1506E0EC(void) {
    f32 quad[4][3];
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    if (*(void **) ((u8 *) D_800D154C + 0x1D4) == NULL) {
        return;
    }
    x = 270.0f;
    z = 270.0f;
    for (i = 0; i < 4; i++) {
        y = 0.0f;
        func_150A7E40(*(f32 (**)[4]) ((u8 *) D_800D154C + 0x1D4), x, 0.0f, z, &x, &y, &z);
        quad[i][0] = x;
        quad[i][1] = *(f32 *) ((u8 *) D_800D154C + 0x180);
        quad[i][2] = z;
        func_15187B50(x, y, z, 30, 20, 7, 0.13f, 0.1f);
        if (i == 0) {
            z = 270.0f;
            x = -270.0f;
        } else if (i == 1) {
            x = -270.0f;
            z = -270.0f;
        } else if (i == 2) {
            x = 270.0f;
            z = -270.0f;
        }
    }
    func_15170648(&quad[0][0], *(f32 *) ((u8 *) D_800D154C + 0x14), *(f32 *) ((u8 *) D_800D154C + 0x1C), 4,
                  *(f32 *) ((u8 *) D_800D154C + 0x14C), 0, 4, 4, 0xFF, 0);
}
