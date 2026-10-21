extern u8 D_800A4648[];
extern u8 D_800A4650[];

typedef struct {
    s32 u2C;
    s32 u30;
    struct17 pos;
    s16 u40;
    s16 u42;
    s16 u44;
    s16 u46;
    f32 u48;
    f32 u4C;
    f32 u50;
    f32 u54;
    s16 u58;
    s16 u5A;
    f32 u5C;
    f32 u60;
    f32 u64;
} Blk15152700;

void func_1513A5E0(s32 arg0, u8 arg1, s32 arg2) {
    Blk15152700 s;

    s.u2C = 7;
    s.u30 = 7;
    s.pos = *(struct17 *)arg0;
    s.u40 = 0;
    s.u42 = 0xFF;
    s.u44 = -0x32;
    s.u46 = 0x1B;
    s.u48 = 4.0f;
    s.u4C = 4.0f;
    s.u50 = -0.43f;
    s.u54 = 0.272f;
    s.u58 = 0x19;
    s.u5A = 0x28;
    s.u5C = 0.0201f;
    s.u60 = 0.0201f;
    s.u64 = 20.187f;
    func_15152700(&s, D_800A4648, D_800A4650, 2, 0.0f, 1, arg1, arg2);
}
