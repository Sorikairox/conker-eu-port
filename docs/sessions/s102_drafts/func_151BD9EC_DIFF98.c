s32 func_151308E4(void *, s32, s32, u8, s32);
void func_151BD9EC(f32 *arg0, f32 *arg1, s32 arg2, s32 arg3, f32 arg4, u8 *arg5) {
    u8 *p;
    s32 b;
    struct {
        s32 u48;
        s32 u4C;
        s16 u50;
        s16 u52;
        s32 u54;
        s32 u58;
        u8 u5C;
        u8 u5D;
        u8 u5E;
        u8 u5F;
        u8 u60;
        u8 u61;
        u8 u62;
        u8 u63;
        u8 u64;
        s8 u65;
        s16 u66;
        s16 u68;
        s16 u6A;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78[3];
        f32 u84[3];
        f32 u90[3];
        f32 u9C;
        s32 uA0;
        u8 padA4[4];
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        s8 uAD;
        u8 padAE[0x2];
    } sp;
    f32 scale;
    s32 obj;
    struct {
        u8 *p;
        u8 b;
    } info;
    s32 a;
    f32 dx;
    f32 dy;
    f32 dz;

    p = *(u8 **)(arg5 + 0x1C);
    if ((p[0x74] & 0xF) != 0xF) {
        sp.u65 = 0x29;
        sp.u50 = 0xE03;
        sp.u48 = 0x200005;
        sp.u4C = 0;
        sp.u54 = 0;
        sp.u58 = 0;
        sp.u9C = ((func_150ADA68() * 251.0f) + 44.0f) * 0.001f;
        sp.u66 = 0x14;
        sp.u68 = 0xC;
        if (func_150ADA20() & 1) {
            a = 0x40;
        } else {
            a = 0;
        }
        if (func_150ADA20() & 1) {
            b = 0x80;
        } else {
            b = 0;
        }
        sp.uA0 = b | 7 | a | 0xDE00;
        sp.uA8 = 3;
        sp.uA9 = 3;
        sp.uAB = -1;
        sp.uAC = -1;
        sp.uAD = 7;
        sp.u6A = 0x22;
        sp.u5C = 0xDD;
        sp.u5D = 0xD3;
        sp.u5E = 0xCD;
        sp.u5F = 0xFF;
        sp.u60 = 0x57;
        sp.u61 = 0x55;
        sp.u62 = 0x5A;
        scale = 0.934719f;
        sp.u6C = 1.034358f;
        sp.u63 = (func_150ADA20() % 156U) + 0x64;
        sp.u64 = 0xFF;
        sp.u52 = (func_150ADA20() % 18U) + 0x19;
        sp.u70 = sp.u74 = (func_150ADA68() * 53.0f) + 49.0f;
        dx = (arg1[0] - arg0[0]) * *(f32 *)(arg5 + 0x74);
        sp.u90[0] = dx;
        dy = (arg1[1] - arg0[1]) * *(f32 *)(arg5 + 0x74);
        sp.u90[1] = dy;
        dz = (arg1[2] - arg0[2]) * *(f32 *)(arg5 + 0x74);
        sp.u90[2] = dz;
        sp.u78[0] = arg0[0] - *(f32 *)(*(u8 **)(arg5 + 0x1C) + 0x14);
        sp.u78[1] = arg0[1] - *(f32 *)(*(u8 **)(arg5 + 0x1C) + 0x18);
        sp.u78[2] = arg0[2] - *(f32 *)(*(u8 **)(arg5 + 0x1C) + 0x1C);
        sp.u78[0] += dx * arg4;
        sp.u78[1] += dy * arg4;
        sp.u78[2] += dz * arg4;
        info.p = *(u8 **)(arg5 + 0x1C);
        sp.uAA = 0x13;
        info.b = *(*(u8 **)(arg5 + 0x1C) + 0x3B);
        sp.u84[0] = *(f32 *)(*(u8 **)(arg5 + 0x1C) + 0x14);
        sp.u84[1] = *(f32 *)(*(u8 **)(arg5 + 0x1C) + 0x18);
        sp.u84[2] = *(f32 *)(*(u8 **)(arg5 + 0x1C) + 0x1C);
        obj = func_151308E4(&sp, 1, 0x10, arg5[0xC], arg5[1]);
        if (obj != 0) {
            memcpy(obj + 0xA8, &scale, 4);
            memcpy(obj + 0xB0, &info, 8);
        }
    }
}
