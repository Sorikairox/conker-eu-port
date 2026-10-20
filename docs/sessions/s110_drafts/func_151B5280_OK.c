typedef struct {
    s32 u24;
    s32 u28;
    u8 u2C;
    u8 *u30;
    s8 u34;
    f32 u38;
    f32 u3C;
    f32 u40;
    f32 u44;
    f32 u48;
    s16 u4C;
    s8 u4E;
    s8 u4F;
    s8 u50;
    s8 u51;
} Spawn5280;
extern u8 D_800A43C6[];
s32 func_15134070(u8 *);
void func_1516962C(s32, u8 *, u8);
u8 *func_1513418C(void *, s32, u8, s32);

u8 *func_151B5280(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *ret;
    Spawn5280 sp;
    u8 flag[1];
    s32 id;

    if (arg0 == NULL) {
        return 0;
    }
    id = func_15134070(arg0);
    if (id == 0x63) {
        return 0;
    }
    if (D_800A43C6[id * 16] == 2) {
        return 0;
    }
    func_1516962C(0x28, arg0, 0x16);
    sp.u24 = 0;
    sp.u28 = 0;
    sp.u2C = arg0[0x3B];
    sp.u34 = 2;
    sp.u4E = 6;
    sp.u30 = arg0;
    sp.u38 = 0.0f;
    sp.u3C = -27.0f;
    sp.u40 = 16.0f;
    sp.u44 = 15.0f;
    sp.u48 = 0.448f;
    sp.u4C = func_150ADA20() % 21U + 0x28;
    sp.u4F = 8;
    sp.u50 = -1;
    sp.u51 = 7;
    if (D_800A43C6[id * 16] == 1) {
        flag[0] = 1;
    } else {
        flag[0] = 0;
    }
    ret = func_1513418C(&sp, 1, arg1, arg2);
    if (ret != NULL) {
        memcpy(ret + 0x58, flag, 1);
    }
    return ret;
}
