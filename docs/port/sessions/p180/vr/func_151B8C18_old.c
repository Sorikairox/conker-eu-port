s32 func_151B8C18(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *p;
    struct_eu_EF410 sp18;

    p = arg0;

    sp18.unk0 = (s32) (p + 0x38);
    sp18.unk4 = (s32) (p + 0x3C);
    sp18.unk8 = (s32) (p + 0x40);
    sp18.unkC = 10.0f;
    sp18.unk10 = 0.2075f * D_800DCE54;
    sp18.unk14 = 300;
    sp18.unk16 = 0;
    sp18.unk17 = 3;
    sp18.unk18 = 0;
    func_15134908(&sp18, 0, arg1, arg2);
}
