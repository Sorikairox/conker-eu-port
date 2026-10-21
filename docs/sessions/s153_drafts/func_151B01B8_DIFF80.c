extern u8 D_800AA500[];
extern f32 D_800AA680;
extern f32 D_800AA684;
extern f32 D_800AA688;
extern f32 D_800AA68C;
extern f32 D_800AA690;
s32 func_15134070(u8 *);

void func_151B01B8(u8 *arg0, u8 *arg1) {
    struct_eu_15154488 s;
    u8 x;
    s32 sp2C[9];
    s32 v;
    u8 *e;

    if (arg0 == NULL) {
        return;
    }
    if (*(s32 *)(arg0 + 0x1D4) == 0) {
        return;
    }
    if ((arg0[0x74] & 0xF) == 0xF) {
        return;
    }
    func_1504715C(sp2C, arg0);
    v = (arg1 == NULL) ? 4 : (arg1[4] == 0x53 || arg1[4] == 0xA5) ? 4 : func_15134070(arg1);
    if (v == 0x63) {
        return;
    }
    e = D_800A43B8[v];
    if (e[0xE] == 2) {
        return;
    }
    x = (*(u16 *)(arg0 + 0x7A) >> 8) + 0x40;
    func_15143134(D_800AA500, &s.unk8, *(u8 **)(arg0 + 0x1D4) + 0x180);
    s.unk14 = D_800AA680;
    s.unk18 = D_800AA684;
    s.unk1C = D_800AA688;
    s.unk20 = D_800AA68C;
    s.unk24 = 6.0f;
    s.unk28 = D_800AA690;
    s.unk2C = 0xA;
    s.unk2E = 0x14;
    s.unk0 = x - 0x68;
    s.unk2 = 0xD0;
    s.unk4 = -0x1B;
    s.unk6 = 0x36;
    s.unk30 = 3;
    s.unk32 = 2;
    s.unk34 = 0x1E;
    s.unk36 = 0x28;
    s.unk38 = 0x9B;
    s.unk3A = 0x64;
    s.unk40 = 0.5f;
    if (e[0xE] == 1) {
        s.unk3C = 1;
    } else {
        s.unk3C = 0;
    }
    s.unk44 = 0x10;
    s.unk46 = 0xF;
    s.unk48 = 0;
    func_15154488(&s, &s.unk8, (s32)sp2C, 0xFF, 1);
}
