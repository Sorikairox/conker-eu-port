void func_15042D94(s32, s32, s32, void *);
extern s16 D_800E0EB0;

Gfx *func_151EC11C(Gfx *gdl) {
    s32 pad[2];
    s16 a;
    s16 i;
    s32 n;
    s32 step;
    s32 y;
    s32 y0;
    u8 *s;

    if (D_800E0EB0 < 0) {
        return gdl;
    }
    if (D_800E0EC0 < 300) {
        a = D_800E0EC0 << 2;
        if (a >= 0x100) {
            a = 0xFF;
        }
    } else {
        a = (350 - D_800E0EC0) << 2;
        if (a < 0) {
            a = 0;
        }
        if (a >= 0x100) {
            a = 0xFF;
        }
    }
    n = 0;
    for (i = D_800E0EB0; ((u8 **)D_800E1008)[i][0] != '*'; i++) {
        n++;
    }
    if (n < 14) {
        step = 0x11;
    } else {
        step = 0xB;
    }
    func_1504332C(0xFF, 0, 0, a);
    i = D_800E0EB0;
    y0 = y = (0xD0 - n * step) >> 1;
    while ((s = ((u8 **)D_800E1008)[i])[0] != '*') {
        func_15042D94(0x94, y, 1, s);
        func_1504332C(0xFF, 0xFF, 0xFF, a);
        if (y == y0) {
            y += 0xC;
        }
        i++;
        y += step;
    }
    return gdl;
}
