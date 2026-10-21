extern f32 D_800AB8F8;
extern f32 D_800AB8FC;
extern f32 D_800AB900;
extern f32 D_800AB904;

typedef struct {
    s16 u0[4];
    struct17 pos;
    s16 u14;
    s16 u16;
    f32 u18;
    f32 u1C;
    s16 u20;
    s16 u22;
    f32 u24;
    f32 u28;
    u8 u2C;
    u8 u2D;
    f32 u30;
    f32 u34;
    u8 u38;
    u8 u39;
    f32 u3C;
    u8 u40;
    f32 u44;
} S06E8;

s32 func_151506E8(S06E8 *, struct17 *, s32, u8, s32);
void func_151037D4(s16, u8, f32, u8 *, s32, u8, s32);
void func_15182BE0(s32, s32, s32, u8, s32, s32, u8, s32);
void func_151D44C4(u8 *, u8, s32);

void func_151DCC50(u8 *arg0, u8 arg1, s32 arg2) {
    S06E8 t;

    func_151037D4((u32)func_150ADA20() % 5 + 0xC, (u32)func_150ADA20() % 56 + 0xC8, func_150ADA68() * 600.0f + D_800AB8F8, arg0, 0xFF, arg1, arg2);
    {
    struct17 *p = &t.pos;
    *p = *(struct17 *)arg0;
    t.u18 = 8.0f;
    t.u1C = 10.0f;
    t.u14 = 0xC;
    t.u16 = 7;
    t.u0[0] = 0;
    t.u0[1] = 0xFF;
    t.u0[2] = -0x40;
    t.u24 = D_800AB8FC;
    t.u0[3] = 0x3C;
    t.u20 = 0x24;
    t.u22 = 0x3C;
    t.u28 = D_800AB900;
    t.u2C = 0xC8;
    t.u2D = 0x37;
    t.u38 = 0;
    t.u30 = 280.0f;
    t.u39 = 0xC;
    t.u34 = 390.0f;
    t.u40 = 1;
    t.u3C = D_800AB904;
    t.u44 = 1.0f;
    func_151506E8(&t, p, 0, arg1, arg2);
    }
    func_151D44C4(arg0, arg1, arg2);
    func_15182BE0(0xFF, 0xFF, 0xFF, (u32)func_150ADA20() % 51 + 0x96, (u32)func_150ADA20() % 5 + 8, 0, arg1, arg2);
}
