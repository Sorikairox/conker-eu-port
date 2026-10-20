typedef struct { s32 *a[2]; } Tbl2;
extern Tbl2 D_80088CA0;
s32 func_1510D66C(s32, s32 *, s32, s32);
Gfx *func_150D7B6C(Gfx *gfx) {
    Tbl2 t;
    s32 sp60;
    s32 i;
    s32 k;
    s32 n;

    k = 0;
    t = D_80088CA0;
    n = D_800D9D30 >> 8;
    for (i = 2; i != 8; i++) {
        if (i >= 6) {
            k = 1;
        }
        gSPSegment(gfx++, i, func_1510D66C(t.a[k][n % 5], &sp60, 3, 0));
        n += 13;
    }
    return gfx;
}
