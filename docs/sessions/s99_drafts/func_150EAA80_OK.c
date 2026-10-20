typedef struct {
    s32 u40;
    s32 u44;
    u8 u48;
    s32 u4C;
    s8 u50;
    f32 u54;
    f32 u58;
    f32 u5C;
    f32 u60;
    f32 u64;
    s16 u68;
    u8 u6A;
    u8 u6B;
    s8 u6C;
    u8 u6D;
} sp_EAA80;
u8 *func_1513418C(void *, s32, u8, s32);
void func_150EAA80(u8 *arg0, s16 arg1, f32 arg2, u8 arg3) {
    sp_EAA80 sp;
    s32 v;

    sp.u40 = 0;
    sp.u44 = 0;
    sp.u48 = arg0[0x3B];
    sp.u4C = (s32)arg0;
    sp.u50 = 1;
    sp.u54 = 0.0f;
    sp.u58 = 0.0f;
    sp.u5C = 0.0f;
    sp.u60 = 25.0f;
    sp.u64 = 0.26497f;
    if (arg1 == -1) {
        sp.u68 = 300;
    } else {
        sp.u68 = arg1;
    }
    if (arg1 == -1) {
        v = 0;
    } else {
        v = 4;
    }
    sp.u6A = v | 0xA;
    sp.u6B = 7;
    sp.u6C = -1;
    sp.u6D = 6;
    func_1513418C(&sp, 0, 0xFF, 0);
}
