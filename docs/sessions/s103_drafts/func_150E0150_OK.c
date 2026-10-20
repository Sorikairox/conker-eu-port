s32 func_1510D66C(s32, s32 *, s32, s32);
extern s32 D_800906D4[];
extern u8 D_800DD835;

Gfx *func_150E0150(Gfx *gfx) {
    s32 a;
    s32 sp48[3];
    s32 k;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (func_150DFE40(i)) {
            k = D_800DD835;
            a = D_800906D4[k + 9];
        } else {
            a = D_800906D4[8];
        }
        a = func_1510D66C(a, sp48, 3, 0);
        gSPSegment(gfx++, i + 2, a);
    }
    return gfx;
}
