typedef struct {
    f32 f0;
    s32 u4[5];
    s32 u18;
    s32 u1C[2];
} St73F4;
u8 func_151D8E20(void);
void func_15142180(u8, f32 *, s32, f32, f32);
s32 func_151DAB58(u8, f32, u8, f32 *, s32, s32, s32);

void func_151473F4(u8 *arg0, u8 arg1, s32 arg2) {
    f32 v[3];
    St73F4 st;
    u8 id;
    f32 pos[3];

    if (*(s32 *)(arg0 + 0x1D4) != 0 && func_15146E00(v, arg0, (s32)&st, arg1) != 0) {
        id = func_151D8E20();
        if (arg2 >= 0x47) {
            func_15142180(id, v, st.u18, 1.0f, 1.0f);
        }
        pos[0] = v[0];
        pos[1] = st.f0;
        pos[2] = v[2];
        if (func_150ADA20() & 1) {
            func_151D9B8C(id, func_150ADA68() * 10.0f + 10.0f, func_150ADA20() % 101U + 0x64, (s32)&st.u4[0], (struct17 *)pos, func_150ADA20() % 41U + 0x50, 1, 1, 0, 0xFF, 1);
            return;
        }
        func_151DAB58(id, func_150ADA68() * 8.0f + 5.0f, func_150ADA20() % 101U + 0x64, pos, 1, 0xFF, 1);
    }
}
