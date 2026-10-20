s32 func_1516DF0C(s16, s16, s16, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15170F24(s32, s32, s32, s32, f32, s32, s32);
s32 func_15171770(s32, s32, f32, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, s32);
s32 func_151BA1A0(s32, s32, s16, s16, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_150C3D48(s32 arg0);
extern f32 D_800A0708;
s32 func_151EF800(u32, u32 *);
s32 func_10004074(s32);

void func_150C3D5C(struct127 *arg0) {
    s32 sum;
    s32 pad[2]; // fakematch: unused 8-byte slot above the Header locals
    Header header;
    Header2 header2;

    func_151BA1A0(0x2F, 1, arg0->x_position, arg0->y_position, arg0->z_position, 0x578, 0x500, 0x320, 0x4B0, 0x200, 0x200, 0x1E, 1, 0, 0xFF, 0);
    ((s32 (*)(u32, u32 *))func_151EF800)(func_150C3D48(sum = 0xC23459B8), (u32 *)&sum);
    if (sum != 0x0330C820) {
        ((u32 *)&func_10004074)[0] = 0x03E00008;
        ((u32 *)&func_10004074)[1] = 0;
    }
    func_15171770(3, 0xCB, arg0->x_position, arg0->y_position, arg0->z_position, 10.0f, 1.0f, 2.0f, 60.0f, 3, 0x3C, D_800A0708, 0xFF, 0);
    func_15170F24(arg0->x_position, arg0->y_position + 20.0f, arg0->z_position, 0xA, 2000.0f, 0xFF, 0);
    func_1516DF0C(arg0->x_position, arg0->y_position, arg0->z_position, 0xD, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xFF, 0, 0, 0, 0x14, 0x14, 2, 0, 0, 0, 0, 0x51, 0x51, 0x51, 0x51, 0xA, 1, 0, 0xFF, 0xA, 0x578, 0x190, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0xFF, 0);
    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() % 11U) + 0xA;
    header.unk4 = 0;
    header2.unk0 = arg0->x_position;
    header2.unk4 = arg0->y_position;
    header2.unk8 = arg0->z_position;
    func_151602C0(&header, &header2, (func_150ADA20() % 52U) + 0x28, 0xFF, 0xFF, 0x5A, 0xFF, 0, 0, 0xFF, 1);
}
