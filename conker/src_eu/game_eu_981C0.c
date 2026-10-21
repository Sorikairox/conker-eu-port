#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_151A74B0(s16 *, s32, s32, s32);

void func_1506A9B0(u8 *arg0, s32 arg1) {
    struct {
        s16 u1C;
        u8 pad1E[0x2];
        f32 u20;
        f32 u24;
        f32 u28;
        s16 u2C;
        u8 pad2E[0x2];
        f32 u30;
        s16 u34;
        s16 u36;
        s16 u38;
        s16 u3A;
        f32 u3C;
        f32 u40;
        u8 pad44[0x8];
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        s8 u70;
        s8 u71;
        s16 u72;
        s16 u74;
    } sp;

    sp.u1C = 3;
    sp.u20 = (*(f32 *)((u8 *)arg0 + 0x14));
    sp.u24 = (*(f32 *)((u8 *)arg0 + 0x18));
    sp.u28 = (*(f32 *)((u8 *)arg0 + 0x1C));
    sp.u3C = 15.1f;
    sp.u30 = 151.5f;
    sp.u40 = 25.2f;
    sp.u2C = 0x5A;
    sp.u34 = 0;
    sp.u36 = 0xFF;
    sp.u38 = -0x40;
    sp.u3A = 0x28;
    sp.u4C = 0.0f;
    sp.u50 = 0.0f;
    sp.u54 = 0.0f;
    sp.u70 = 0;
    sp.u71 = 0;
    sp.u72 = 0x32;
    sp.u74 = 0x19;
    sp.u58 = 0.388f;
    sp.u5C = 0.24300002f;
    sp.u60 = -1.0200001f;
    sp.u68 = -4.0f;
    sp.u64 = 0.0f;
    sp.u6C = 8.0f;
    func_151A74B0(&sp.u1C, 1, 0xFF, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506A9B0.s")
#endif
void func_1506AABC(s32 arg0, s32 arg1) {
    func_150E08C8(arg0, 0xFF, 1);
}

void func_1506AAE4(s32 arg0, s32 arg1) {
    func_151BBBCC(arg0, D_800D1980, D_eu_800D1990, 0xFF, 1);
}

void func_1506AB20(s32 arg0, s32 arg1) {
    func_151BC04C(arg0, D_800D1980, D_eu_800D1990, 0xFF, 1);
}

s32 func_151D3A30(f32 *, f32 *, s32, s32, s32, s32);

void func_1506AB5C(u8 *arg0, s32 arg1) {
    f32 sp2C[3];
    f32 sp20[3];

    sp2C[0] = *(f32 *)(arg0 + 0x14);
    sp2C[1] = *(f32 *)(arg0 + 0x18);
    sp2C[2] = *(f32 *)(arg0 + 0x1C);
    sp20[0] = ((f32 *)D_eu_800D1990)[0] - ((f32 *)D_800D1980)[0];
    sp20[1] = ((f32 *)D_eu_800D1990)[1] - ((f32 *)D_800D1980)[1];
    sp20[2] = ((f32 *)D_eu_800D1990)[2] - ((f32 *)D_800D1980)[2];
    func_151D3A30(sp2C, sp20, 0, 0, 0xFF, 1);
}

void func_1506ABFC(s32 arg0, s32 arg1) {
    func_151BC6B4(arg0, 0xFF, 1);
}

extern f32 D_80099DE8;

void func_1506AC24(struct127 *arg0, s32 arg1) {
    struct225 *temp_v0;
    Header header;
    struct {
        f32 unk0;
        f32 unk4;
        f32 unk8;
        f32 unkC;
    } data;
    Header2 header2;

    header2.unk0 = arg0->x_position;
    header2.unk4 = arg0->y_position + 50.0f;
    header2.unk8 = arg0->z_position;
    data.unk0 = 0.0f;
    data.unk8 = 0.0f;
    header.unk0 = 2;
    header.unk1 = 0xF;
    header.unk2 = 0x12C;
    header.unk4 = 5;
    data.unk4 = 80.0f;
    data.unkC = D_80099DE8;
    temp_v0 = func_151602C0(&header, &header2, 0, 0xFF, 0xFF, 0x5A, 0xFF, 0, sizeof(data), 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &data, sizeof(data));
    }
}

s32 func_151D3A30(f32 *, f32 *, s32, s32, s32, s32);

void func_1506AD28(u8 *arg0, s32 arg1) {
    f32 sp2C[3];
    f32 sp20[3];

    sp2C[0] = *(f32 *)(arg0 + 0x14);
    sp2C[1] = *(f32 *)(arg0 + 0x18);
    sp2C[2] = *(f32 *)(arg0 + 0x1C);
    sp20[0] = ((f32 *)D_eu_800D1990)[0] - ((f32 *)D_800D1980)[0];
    sp20[1] = ((f32 *)D_eu_800D1990)[1] - ((f32 *)D_800D1980)[1];
    sp20[2] = ((f32 *)D_eu_800D1990)[2] - ((f32 *)D_800D1980)[2];
    func_151D3A30(sp2C, sp20, 0, 1, 0xFF, 1);
}

void func_1506ADC8(s32 arg0, s32 arg1) {
    func_151B76F4(arg0, 0xFF, 1);
    func_151B68D0(arg0, 0xFF, 1);
}

void func_1506AE08(u8 *arg0, u8 *arg1) {
    typedef struct { s32 w[2]; } Blk8;
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        u8 pad5[3];
        Blk8 unk8;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = *(Blk8 *)arg1;
    temp_v0 = func_15149130(0xA, 7, 0x23, -1, 1, 0x21, 0x10, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506AEA0.s")

void func_1506AF3C(struct127 *arg0, u8 *arg1) {
    func_151043C0(arg0, *(struct127 **)arg1, (f32 *)(arg1 + 4), 1, *(s32 *)(arg1 + 0x10), 0xFF, 1);
}

void func_1506AF84(struct127 *arg0, u8 *arg1) {
    func_151043C0(arg0, *(struct127 **)arg1, (f32 *)(arg1 + 4), 2, *(s32 *)(arg1 + 0x10), 0xFF, 1);
}

void func_1506AFCC(u8 *arg0, s32 arg1) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151B78D8(&tmp, 0, 8, 0xFF, 1);
}

void func_1506B018(s32 arg0, s32 arg1) {
    func_151CF05C(arg0, 0, 1, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506B04C.s")
