s32 func_15183800(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150A29A0(Unk34B8 *arg0, s32 arg1) {
    s32 v;
    s32 r;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
    s32 g;
    s32 w;

    if (arg1 != 0xFF) {
        w = arg0->unk1C;
        v = w & 0xFF;
        if (v == 0 || arg0->unk17 == 9) {
            g = arg0->unk17;
            a = arg0->unk18 & 0xFF;
            b = *(s16 *)&arg0->unk18;
            c = ((u8 *)&arg0->unk18)[2];
            d = ((u8 *)&arg0->unk1C)[0];
            e = ((u8 *)&arg0->unk1C)[1];
            f = arg0->unk20;
            r = func_15183800(arg0->x, arg0->y + (e << 4), arg0->z, a, g,
                              arg0->unk6, arg1, b, c, d, f);
            if (r != -1 && arg0->unk17 != 9) {
                arg0->unk1C = ((r << 8) | 0xF0) | (arg0->unk1C & 0xFFFF0000);
            }
        } else {
            r = v;
            if (v < 2) {
                r = 2;
            }
            arg0->unk1C = (w & ~0xFF) | r;
        }
    }
}
