s32 func_151030B8(void *, u8, f32 *, f32 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
void func_15145EA4(f32 **, f32 **, s32, s32);
extern f32 D_800A1A5C[2][4][2][3];
extern f32 D_800A1B1C[2][4][2][3];
extern u8 D_800A1BDC[2][2];
typedef struct { u8 m[2]; } MaskS101;
extern MaskS101 D_800A1BE0;

void func_150F1C5C(u8 *volatile arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    f32 pos[3];
    u8 k;
    MaskS101 mask;
    f32 *in[1];
    f32 *out[1];
    Header header;
    Header2 header2;
    f32 f[2];

    if ((arg0 != NULL) && (arg2 < 4) && (arg1 < 2)) {
        if (arg0[4] == 0x23) {
            k = 1;
        } else {
            mask = D_800A1BE0;
            if (*(s32 *)(arg0 + 0x94) & mask.m[arg1]) {
                return;
            }
            k = 0;
        }
        if (*(s32 *)(arg0 + 0x1D4) != 0) {
            in[0] = D_800A1A5C[k][arg2][arg1];
            out[0] = pos;
            func_15145EA4(in, out, (D_800A1BDC[k][arg1] << 6) + *(s32 *)(arg0 + 0x1D4), 1);
            header.unk0 = 3;
            header.unk1 = -1;
            header.unk2 = (func_150ADA20() % 5U) + 4;
            header.unk4 = 0;
            header2.unk0 = pos[0];
            header2.unk4 = pos[1];
            header2.unk8 = pos[2];
            func_151602C0(&header, &header2, (func_150ADA20() % 51U) + 0x50, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg3, arg4);
            f[1] = ((func_150ADA68() * 701.0f) + 1925.0f) * 0.001f;
            f[0] = ((func_150ADA68() * 1155.0f) + 1526.0f) * 0.1f;
            func_151030B8(arg0, D_800A1BDC[k][arg1], D_800A1A5C[k][arg2][arg1], D_800A1B1C[k][arg2][arg1], f, (func_150ADA20() % 6U) + 8, (func_150ADA20() % 1U) + 0xFF, (func_150ADA68() * 1877.0f) + 2414.0f, pos, 0xFF, 0, -1, arg3, arg4);
        }
    }
}
