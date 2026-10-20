extern f32 D_800A6C60[];
extern f32 D_800A6C74[];
extern f32 D_800A6C88[];
extern f32 D_800A6C9C[];
extern f32 D_800A6CB0[];
extern f32 D_800A6CC4[];

struct225 *func_1516295C(struct226 *arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4, s8 arg5, s8 arg6, s8 arg7, s8 arg8, s8 arg9, s32 argA, u8 argB, s32 argC) {
    struct225 *temp_v0;
    Header header;
    struct {
        f32 unk0;
        f32 unk4;
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        s8 unk24;
        s8 unk25;
        s8 unk26;
        s8 unk27;
        s8 unk28;
    } tmp;
    f32 c;
    f32 d;

    if (arg1 >= 5) {
        return NULL;
    }
    tmp.unk0 = D_800A6C60[arg1];
    tmp.unk4 = D_800A6C74[arg1];
    tmp.unkC = D_800A6C88[arg1];
    c = D_800A6C9C[arg1];
    d = D_800A6CB0[arg1];
    tmp.unk8 = tmp.unk0 - tmp.unk4;
    tmp.unk14 = d + c;
    tmp.unk18 = D_800A6CC4[arg1] + tmp.unk14;
    tmp.unk10 = c;
    tmp.unk1C = d + tmp.unk18;
    tmp.unk25 = arg6;
    tmp.unk26 = arg7;
    tmp.unk27 = arg8;
    tmp.unk28 = arg9;
    if (tmp.unkC < c) {
        tmp.unk24 = 0;
    } else if (tmp.unkC < tmp.unk14) {
        tmp.unk24 = 1;
    } else if (tmp.unkC < tmp.unk18) {
        tmp.unk24 = 2;
    } else if (tmp.unkC < tmp.unk1C) {
        tmp.unk24 = 3;
    } else {
        tmp.unk24 = 4;
    }
    header.unk0 = arg3;
    header.unk1 = arg5;
    header.unk2 = arg4;
    header.unk4 = arg2;
    tmp.unk20 = 1.0f / d;
    temp_v0 = func_1516037C(&header, arg0, argA + 0x30, argB, argC);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp, 0x30);
    }
    return temp_v0;
}
