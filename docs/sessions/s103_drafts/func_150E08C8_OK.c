typedef struct { f32 x, y, z; } VecE08C8;
u8 *func_1513418C(void *, s32, u8, s32);

void func_150E08C8(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u0;
        s32 u4;
        u8 u8;
        u8 pad9[3];
        u8 *uC;
        s8 u10;
        u8 pad11[3];
        VecE08C8 u14;
        f32 u20;
        f32 u24;
        s16 u28;
        u8 u2A;
        u8 u2B;
        s8 u2C;
        s8 u2D;
    } sp;

    sp.u0 = 0;
    sp.u4 = 0;
    sp.u8 = arg0[0x3B];
    sp.uC = arg0;
    sp.u10 = 0;
    sp.u14 = *(VecE08C8 *)D_800A5860;
    sp.u28 = 0x12C;
    sp.u2A = 0x1B;
    sp.u2B = 0xB;
    sp.u2C = -1;
    sp.u2D = 0;
    sp.u20 = 10.900001f;
    sp.u24 = 0.23121f;
    func_1513418C(&sp, 0, arg1, arg2);
}
