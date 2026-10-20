typedef struct { f32 x, y, z; } FFC60_V;
extern s32 D_800A242C;
extern s32 D_800A2438;
extern s32 D_800A2444;
extern FFC60_V D_800A2450[2][6];

s32 func_150FFC60(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3, s32 arg4, s32 arg5, s32 arg6) {
    void *ptrs[10];
    s32 vals[10];
    s32 r;
    s32 i;

    r = func_150ADA20() & 1;
    ptrs[0] = &D_800A2420;
    ptrs[1] = &D_800A2438;
    ptrs[2] = &D_800A2444;
    ptrs[3] = &D_800A242C;
    for (i = 0; i < 6; i = (u8)(i + 1)) {
        ptrs[i + 4] = &D_800A2450[r][i];
        vals[i + 4] = arg0 + (u8)i * 12;
    }
    vals[1] = (s32)arg2;
    vals[2] = (s32)arg3;
    vals[0] = arg1;
    vals[3] = arg4;
    if (func_1514654C(arg5, arg6, 0, ptrs, vals, 10) != 0) {
        arg3[0] -= arg2[0];
        arg3[1] -= arg2[1];
        arg3[2] -= arg2[2];
        return 1;
    }
    return 0;
}
