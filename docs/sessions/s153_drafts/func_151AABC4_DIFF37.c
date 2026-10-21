u8 func_151D8E20(void);
extern u8 D_800A9350[];
extern f32 D_800A93AC;
extern f32 D_800A93B0;
extern f32 D_800A93B4;
extern f32 D_800A93B8;
extern f32 D_800A93BC;
s32 func_15142314(s32, s32, f32 *);
s32 func_15046C6C(f32 *, s32, f32, f32 *);

void func_151AABC4(u8 *arg0, u8 arg1) {
    f32 spBC[3];
    f32 sp98[9];
    s32 pad;
    f32 sp88[3];
    u8 kind;
    struct17 pos;
    struct_eu_15154488 s;
    f32 y;

    if (arg0 == NULL) {
        return;
    }
    if (*(s32 *)(arg0 + 0x1D4) == 0) {
        return;
    }
    kind = func_151D8E20();
    func_15142314(*(s32 *)(arg0 + 0x1D4), D_800A9350[arg1], spBC);
    func_1504715C(sp98, arg0);
    sp88[0] = spBC[0];
    sp88[1] = y = spBC[1] + 50.0f;
    sp88[2] = spBC[2];
    if (func_15046C6C(sp88, 0, y - 100.0f, sp98)) {
        pos.unk0 = spBC[0];
        pos.unk4 = sp98[0];
        pos.unk8 = spBC[2];
        func_151DBCBC(kind, 40.0f, 0x96, (s32)&sp98[1], &pos, 0xFF, 1);
        s.unk8 = pos;
        s.unk14 = 2.5f;
        s.unk18 = D_800A93AC;
        s.unk1C = D_800A93B0;
        s.unk20 = D_800A93B4;
        s.unk24 = D_800A93B8;
        s.unk28 = D_800A93BC;
        s.unk2E = 3;
        s.unk2C = 3;
        s.unk2 = 0xFF;
        s.unk4 = -0x40;
        s.unk6 = 0x1A;
        s.unk0 = 0;
        s.unk30 = 3;
        s.unk32 = 1;
        s.unk34 = 0x1E;
        s.unk36 = 0x14;
        s.unk38 = 0x9B;
        s.unk3A = 0x64;
        s.unk44 = 0x10;
        s.unk46 = 0xF;
        s.unk48 = 0;
        s.unk3C = kind;
        s.unk40 = 0.0f;
        func_15154488(&s, &s.unk8, (s32)sp98, 0xFF, 1);
    }
}
