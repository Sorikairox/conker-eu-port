struct225 *func_1519078C(s32 arg0, u8 *arg1, u8 arg2, s16 arg3, u8 arg4, s32 arg5) {
    Header2 header2;
    s32 tmp;
    f32 f[8];
    struct {
        u8 *p;
        u8 b;
    } src;
    Header header;
    struct225 *temp_v0;

    if (arg2 >= 24) {
        return NULL;
    }
    tmp = arg0;
    f[0] = D_800A67C0[arg2];
    f[1] = D_800A6760[arg2];
    f[2] = D_800A6820[arg2];
    f[3] = 1.0f;
    f[5] = 5.0f;
    f[4] = 0.0f;
    f[7] = 0.0f;
    f[6] = 0.2489f;
    header.unk0 = (arg3 != -1) | 2;
    header.unk1 = 0x12;
    if (arg3 == -1) {
        header.unk2 = 300;
    } else {
        header.unk2 = arg3;
    }
    header.unk4 = 0x25;
    src.p = arg1;
    src.b = arg1[0x3B];
    header2.unk0 = *(f32 *)(arg1 + 0x14);
    header2.unk4 = *(f32 *)(arg1 + 0x18);
    header2.unk8 = *(f32 *)(arg1 + 0x1C);
    temp_v0 = func_151602C0(&header, &header2, 0, 0xFF, 0xD1, 0, 0xFF, 0, 0x30, arg4, arg5);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, 8);
        memcpy((u8 *)temp_v0 + 0x20, f, 0x20);
        memcpy((u8 *)temp_v0 + 0x40, &tmp, 4);
    }
    return temp_v0;
}
