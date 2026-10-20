void func_151D58E4(s32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6);
s32 func_151030B8(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
extern struct17 D_80099F60;
extern struct17 D_80099F6C;

void func_15070F60(u8 arg0) {
    struct17 a;
    struct17 b;
    f32 f[2];
    f32 pos[3];
    Header header;
    Header2 header2;

    a = D_80099F60;
    b = D_80099F6C;
    if ((D_800D154C->unk1D4 != NULL) && ((D_800D154C->unk74 & 0xF) != 0xF)) {
        f[0] = (func_150ADA68() * 180.0f) + 150.0f;
        f[1] = (func_150ADA68() * 2.0f) + 2.5f;
        func_15143134(&a, pos, (u8 *)D_800D154C->unk1D4 + ((arg0 ? 1 : 2) << 6));
        func_151030B8(D_800D154C, arg0 ? 1 : 2, (u8 *)&a, (s32 *)&b, f, (func_150ADA20() % 5U) + 5, (func_150ADA20() % 156U) + 0x64, (func_150ADA68() * 4000.0f) + 4000.0f, pos, 0xFF, 0, -1, 0xFF, 0);
        header.unk0 = 3;
        header.unk1 = -1;
        header.unk2 = (func_150ADA20() % 5U) + 3;
        header.unk4 = 0;
        header2.unk0 = pos[0];
        header2.unk4 = pos[1];
        header2.unk8 = pos[2];
        func_151602C0(&header, &header2, (func_150ADA20() % 201U) + 0x37, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 0);
        func_151D5404((struct17 *)pos, 506.0f, 1013.0f, 0.0009871668880805373f, 0xF, 0x14, 0xFF, 0);
        func_151D58E4((s32)pos, 506.0f, 1013.0f, 0.0009871668880805373f, 5, 0xFF, 0);
    }
}
