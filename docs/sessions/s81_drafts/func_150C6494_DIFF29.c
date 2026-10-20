s32 func_15045AF0(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3);
s32 func_1513418C(void *, s32, u8, s32);
extern f32 D_800A07E0;
extern f32 D_800A07E4;
extern f32 D_800A07E8;

s32 func_150C6494(s32 arg0, u8 *arg1) {
    struct {
        s32 u40;
        s32 u44;
        u8 u48;
        s32 u4C;
        u8 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        u8 u6A;
        u8 u6B;
        u8 u6C;
        u8 u6D;
    } sp;
    struct {
        u8 *u34;
        u8 u38;
        f32 u3C;
    } blk;
    s32 obj;
    f32 pos[3];

    blk.u34 = arg1;
    blk.u38 = 1;
    pos[0] = *(f32 *)((u8 *)arg0 + 0x14);
    pos[1] = *(f32 *)((u8 *)arg0 + 0x18) + D_800A07E0;
    pos[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    if (func_15045AF0((u8 *)pos, 0, *(f32 *)((u8 *)arg0 + 0x18) - 100.0f, (u8 *)arg1 + 0x34)) {
        blk.u3C = *(f32 *)(arg1 + 0x34);
    } else {
        blk.u3C = *(f32 *)((u8 *)arg0 + 0x18) + D_800A07E4;
    }
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u48 = *((u8 *)arg0 + 0x3B);
    sp.u4C = arg0;
    sp.u50 = 0;
    sp.u54 = 0.0f;
    sp.u58 = 0.0f;
    sp.u5C = 0.0f;
    sp.u60 = 25.0f;
    sp.u64 = D_800A07E8;
    sp.u68 = 300;
    sp.u6A = 10;
    sp.u6B = 4;
    sp.u6C = 1;
    sp.u6D = 2;
    obj = func_1513418C(&sp, 0xC, 0xFF, 0);
    if (obj != 0) {
        memcpy((u8 *)obj + 0x58, &blk, 0xC);
    }
    return obj;
}
