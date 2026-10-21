typedef struct {
    s32 u48;
    s16 u4C;
    u8 u4E;
    s32 u50;
    s32 u54;
    u8 u58;
    u8 u59;
    u8 u5A;
    u8 u5B;
    u8 u5C;
    u8 u5D;
    u8 u5E;
    u8 u5F;
    s32 u60;
} Blk6918;

void func_15136918(f32 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4, s32 arg5, f32 *arg6, u8 arg7, s32 arg8) {
    Blk6918 s;

    s.u4E = 0x55;
    s.u48 = 0x300;
    s.u50 = 0;
    s.u54 = 0;
    s.u58 = arg1;
    s.u59 = arg2;
    s.u5A = 0;
    s.u5B = 0;
    s.u5C = 0;
    s.u5D = 0;
    s.u60 = 0x280001;
    s.u5E = 1;
    s.u5F = 1;
    if (arg3 == -1) {
        s.u4C = 300;
    } else {
        s.u48 = 0x301;
        s.u4C = arg3 + 0x20;
    }
    func_1513C73C((s32)&s, 0xD, 0, arg5, arg6[0], arg6[1], arg6[2], arg0, arg0, arg4, 0, 0, arg7, arg8);
}
