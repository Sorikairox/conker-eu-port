s32 func_15134070(s32);
extern u8 D_800A43C6[];
extern f64 D_800A8680;
extern f32 D_800A8688;
extern f32 D_800A868C;
extern f32 D_800A8690;
extern f32 D_800A8694;
extern f32 D_800A8698;

void func_15194B3C(u8 *arg0, struct127 *arg1, s32 arg2) {
    struct17 pos;
    s16 x;
    struct_eu_15154488 s;
    s32 sp30[9];
    s32 v;
    s32 k;

    x = (*(u16 *)(arg0 + 0x7A) >> 8) - 0x40;
    pos.unk0 = *(f32 *)((u8 *)arg1 + 0x14);
    pos.unk4 = *(f32 *)((u8 *)arg1 + 0x18) + D_800A8680;
    pos.unk8 = *(f32 *)((u8 *)arg1 + 0x1C);
    func_1504715C(sp30, arg1);
    v = func_15134070((s32)arg1);
    if (v != 0x63) {
        k = D_800A43C6[v * 16];
        if (k != 2) {
            s.unk8 = pos;
            s.unk14 = D_800A8688;
            s.unk18 = D_800A868C;
            s.unk1C = D_800A8690;
            s.unk20 = 0.0f;
            s.unk24 = D_800A8694;
            s.unk28 = D_800A8698;
            s.unk2C = 0xF;
            s.unk2E = 0xC;
            s.unk0 = x - 0x40;
            s.unk2 = 0x80;
            s.unk4 = -0xA0;
            s.unk6 = 0x20;
            s.unk30 = 3;
            s.unk32 = 1;
            s.unk34 = 0x1F;
            s.unk36 = 0x13;
            s.unk38 = 0x9B;
            s.unk3A = 0x64;
            s.unk44 = 0x10;
            s.unk46 = 0xF;
            s.unk48 = 0;
            s.unk40 = 0.5f;
            if (k == 1) {
                s.unk3C = 1;
            } else {
                s.unk3C = 0;
            }
            func_15154488(&s, &s.unk8, (s32)sp30, 0xFF, 1);
        }
    }
    func_151B5280(arg1, 0xFF, 1);
}
