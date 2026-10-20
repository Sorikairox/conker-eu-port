s32 func_151030B8(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern struct17 D_80099F48;
extern struct17 D_80099F54;

void func_15070D24(s32 arg0) {
    struct17 a;
    struct17 b;
    f32 f[2];
    f32 pos[3];
    Header header;
    Header2 header2;

    a = D_80099F48;
    b = D_80099F54;
    if ((D_800D154C->unk1D4 != NULL) && ((D_800D154C->unk74 & 0xF) != 0xF)) {
        f[0] = (func_150ADA68() * 101.0f) + 151.0f;
        f[1] = (func_150ADA68() * 4.0f) + 4.0f;
        func_15143134(&a, pos, (u8 *)D_800D154C->unk1D4 + 0x40);
        func_151030B8(D_800D154C, 1, (u8 *)&a, (s32 *)&b, f, (func_150ADA20() % 6U) + 5, (func_150ADA20() % 156U) + 0x64, (func_150ADA68() * 2496.0f) + 3496.0f, (s32)pos, 0xFF, 0, -1, 0xFF, 0);
        header.unk0 = 3;
        header.unk1 = -1;
        header.unk2 = (func_150ADA20() % 6U) + 0xA;
        header.unk4 = 0;
        header2.unk0 = pos[0];
        header2.unk4 = pos[1];
        header2.unk8 = pos[2];
        func_151602C0(&header, &header2, (func_150ADA20() % 201U) + 0x37, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 0);
    }
}
