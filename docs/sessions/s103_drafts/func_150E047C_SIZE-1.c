s32 func_15107C80(u8 *, s16, s16, s16, s32, f32, f32, s32, s32, u8 *, u8, u8);
s32 func_151080F8(u8 *, s16, s16, u8, u8);

typedef struct {
    u8 *o;
    u8 id;
    u8 pad5;
    s16 t6;
    s16 t8;
    s16 tA;
} SubE047C;

void func_150E047C(u8 *arg0) {
    SubE047C *s; u8 *obj; Header header; Header2 header2; s8 n; u8 col[4];

    s = (SubE047C *)(arg0 + 0x28);
    obj = s->o;
    if ((*(s32 *)obj == 0) || (s->id != obj[0x3B])) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    s->t6 -= D_800BE9E4;
    if (s->t6 < 0) {
        header2.unk0 = *(f32 *)(obj + 0x14);
        header2.unk4 = *(f32 *)(obj + 0x18);
        header.unk0 = 3;
        header.unk1 = -1;
        header2.unk8 = *(f32 *)(obj + 0x1C);
        header.unk2 = (func_150ADA20() % 11U) + 5;
        header.unk4 = 0;
        func_151602C0(&header, &header2, (func_150ADA20() % 121U) + 0x32, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg0[0xC], arg0[1]);
        s->t6 = (func_150ADA20() % 81U) + 0x45;
    }
    s->t8 -= D_800BE9E4;
    if (s->t8 < 0) {
        n = (func_150ADA20() % 3U) + 2;
        do {
            col[0] = 0xAE;
            col[1] = 0xD2;
            col[2] = 0xFF;
            col[3] = (func_150ADA20() % 61U) + 0x96;
            func_15107C80(obj, func_150ADA20() & 0xFF, (func_150ADA20() % 129U) - 0x3F, (func_150ADA20() % 21U) + 0xA, 4, 40.0f, (func_150ADA68() * 20.0f) + 25.0f, 0, 2, col, arg0[0xC], arg0[1]);
            n--;
        } while (n > 0);
        s->t8 = (func_150ADA20() % 141U) + 0x19;
    }
    s->tA -= D_800BE9E4;
    if (s->tA < 0) {
        func_151080F8(obj, func_150ADA20() & 0xFF, (func_150ADA20() & 0x7F) - 0x40, arg0[0xC], arg0[1]);
        s->tA = (func_150ADA20() % 26U) + 0xF;
    }
}
