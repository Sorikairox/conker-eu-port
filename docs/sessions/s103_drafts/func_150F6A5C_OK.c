s32 func_1510819C(u8 *, s32, f32 *, s16, s32, s32, s32, f32, f32, s32, s32, u8 *, u8, u8);
extern f32 D_800A1F00[];

typedef struct {
    u8 *o;
    u8 id;
    u8 pad5;
    s16 t6;
} Sub6A5C;

void func_150F6A5C(u8 *arg0) {
    Sub6A5C *s;
    u8 *obj;
    s8 n;
    f32 pos[3];
    Header header;
    Header2 header2;
    u8 col[4];

    s = (Sub6A5C *)(arg0 + 0x28);
    obj = s->o;
    if ((*(s32 *)obj == 0) || (s->id != obj[0x3B])) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if ((*(s32 *)(obj + 0x1D4) != 0) && !(*(s32 *)(obj + 0x94) & 2)) {
        s->t6 -= D_800BE9E4;
        if (s->t6 < 0) {
            func_10010F88(0x679, 0x18CE, 0, 0, 0, *(f32 *)(obj + 0x14), *(f32 *)(obj + 0x18), *(f32 *)(obj + 0x1C), 0x7918, 0x7D00);
            n = (func_150ADA20() & 1) + 2;
            goto lbl; // fakematch: scheduling barrier (permuter)
            lbl:
            func_15143134(D_800A1F00, pos, *(u8 **)(obj + 0x1D4));
            header.unk0 = 3;
            header.unk1 = -1;
            header.unk2 = (func_150ADA20() % 9U) + 0xA;
            header.unk4 = 0;
            header2.unk0 = pos[0];
            header2.unk4 = pos[1];
            header2.unk8 = pos[2];
            func_151602C0(&header, &header2, (func_150ADA20() % 61U) + 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg0[0xC], arg0[1]);
            do {
                col[0] = 0xA0;
                col[1] = 0xA0;
                col[2] = 0xFF;
                col[3] = (func_150ADA20() % 101U) + 0x9B;
                func_1510819C(obj, 0, D_800A1F00, func_150ADA20() & 0xFF, (func_150ADA20() % 43U) - 0x32, (func_150ADA20() % 18U) + 5, 4, 27.0f, (func_150ADA68() * 16.0f) + 20.0f, 0, 2, col, arg0[0xC], arg0[1]);
                n--;
            } while (n > 0);
            s->t6 = (func_150ADA20() % 91U) + 0x5A;
        }
    }
}
