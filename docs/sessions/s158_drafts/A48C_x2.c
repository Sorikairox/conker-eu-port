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

void func_1513A48C(struct17 *arg0, u8 arg1, s32 arg2) {
    Blk15152700 s;

    s.u2C = 8;
    s.u30 = 4;
    s.pos = *arg0;
    s.u40 = 0;
    s.u42 = 0xFF;
    s.u44 = -0x37;
    s.u46 = 0x20;
    s.u48 = 10.0f;
    s.u4C = 9.0f;
    s.u50 = D_800A4D34;
    s.u54 = D_800A4D38;
    s.u58 = 0x28;
    s.u5A = 0x14;
    s.u5C = s.u60 = D_800A4D30;
    s.u64 = D_800A4D3C;
    func_15152700(&s, D_800A4640, D_800A4644, 1, 0.0f, 1, arg1, arg2);
}
