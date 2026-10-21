extern s32 D_8008CDEC;
s32 func_15173090(u8 *, f32, f32, f32, f32, s32, s32, s32);

void func_151722BC(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u16 arg4, u8 arg5, f32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, u8 argC, s32 argD) {
    u8 *t;
    Vtx *v;
    f32 f;

    t = func_15172210(arg3, arg4, arg5, arg9, argA, argB, argC, argD);
    if (t == NULL) {
        return;
    }
    if (!(arg9 & 2)) {
        if (!func_15173090(t + 0x10, arg0, arg1, arg2, arg6, arg7, arg8, *(u16 *)(((u8 **)&D_8008CDEC)[t[0x58]] + 6))) {
            func_1516972C((struct102 *)t);
        }
        return;
    }
    v = (Vtx *)(t + 0x10);
    f = arg8;
    v[0].v.ob[1] = v[1].v.ob[1] = v[2].v.ob[1] = v[3].v.ob[1] = arg1;
    v[0].v.ob[0] = v[3].v.ob[0] = arg0 - f;
    v[0].v.tc[0] = v[3].v.tc[0] = 0x2000;
    v[1].v.ob[0] = v[2].v.ob[0] = f + arg0;
    v[0].v.ob[2] = v[1].v.ob[2] = arg2 - f;
    v[2].v.ob[2] = v[3].v.ob[2] = f + arg2;
    v[0].v.tc[1] = v[1].v.tc[1] = 0x2000;
    v[1].v.tc[0] = v[2].v.tc[0] = (*(u16 *)(((u8 **)&D_8008CDEC)[arg5] + 6) + 0x100) << 5;
    v[2].v.tc[1] = v[3].v.tc[1] = (*(u16 *)(((u8 **)&D_8008CDEC)[arg5] + 8) + 0x100) << 5;
}
