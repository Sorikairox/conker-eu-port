typedef struct {
    s32 u18;
    s32 u1C;
    u8 u20;
    u8 pad21[3];
    u8 *u24;
    s8 u28;
    u8 pad29[3];
    f32 u2C;
    f32 u30;
    f32 u34;
    f32 u38;
    f32 u3C;
    s16 u40;
    s8 u42;
    s8 u43;
    s8 u44;
    s8 u45;
} Spawn4B40;
u8 *func_1513418C(void *, s32, u8, s32);

void func_151A4B40(u8 *arg0, u8 arg1) {
    Spawn4B40 sp;


    if (arg0 == NULL) {
        return;
    }
    {
        sp.u18 = 0;
        sp.u1C = 0;
        sp.u24 = arg0;
        sp.u20 = arg0[0x3B];
        sp.u28 = 1;
        sp.u40 = 0x64;
        sp.u42 = 0xA;
        sp.u43 = 1;
        sp.u44 = -1;
        sp.u45 = 0;
        sp.u2C = 0.0f;
        sp.u30 = 0.0f;
        sp.u34 = 0.0f;
        sp.u38 = 14.7f;
        sp.u3C = 3.0f;
        func_1513418C(&sp, 0, arg1, 0);
    }
}
