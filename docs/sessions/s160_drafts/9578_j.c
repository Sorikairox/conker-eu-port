typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[0xA];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 padD[3];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[0x10];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ s32 unk60;
} Obj9578;

s32 func_15139578(Obj9578 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    struct17 pos;
    f32 s;

    s = arg0->unk14;
    arg0->unk3C = arg0->unk10 + arg4;
    arg0->unk44 *= s;
    arg0->unk48 = arg0->unk48 * -s;
    arg0->unk4C *= s;
    arg0->unk50 *= s;
    arg0->unk54 *= s;
    arg0->unk58 *= s;
    if (fabsf(arg0->unk48) < 4.0f) {
        arg0->unk44 = 0.0f;
        arg0->unk60 &= ~0x69;
        arg0->unk48 = 0.0f;
        arg0->unk4C = 0.0f;
        arg0->unk50 = 0.0f;
        arg0->unk54 = 0.0f;
        arg0->unk58 = 0.0f;
        arg0->unk5C = 0.0f;
    }
    if (arg0->unk30 != 2.0f) {
        s32 r;
        f32 f;
        s32 flag;
        pos.unk0 = arg0->unk38;
        pos.unk4 = arg4;
        pos.unk8 = arg0->unk40;
        if (arg0->unk30 == 0.0f) {
            flag = 0;
        } else {
            flag = 1;
        }
        f = func_150ADA68();
        r = func_150ADA20();
        func_151D9B8C(flag, ((f * 27.6f) + 19.7f) * ((arg0->unk18 + arg0->unk1C) * 0.5f), (r % 101U) + 100, arg5, &pos,
                      (func_150ADA20() % 144U) + 80, 1, 1, 0, arg0->unkC, arg0->unk1);
    }
    return 1;
}
