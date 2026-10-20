typedef struct { u8 u0; u8 pad1[3]; s16 u4; u8 pad6[4]; } E10;
typedef struct { s32 *a[2]; } P2;
extern P2 D_eu_80088BB0;
extern E10 *D_eu_800BE900;
s32 func_1510D66C(s32, s32 *, s32, s32);
Gfx *func_150C8B00(Gfx *gfx) {
    s32 i;
    s32 buf[3];
    s32 lvl;
    P2 tabs = D_eu_80088BB0;

    for (i = 0; i < 10; i++) {
        lvl = D_eu_800BE900[i].u4 >> 8;
        if (lvl < 0) {
            lvl = 0;
        } else if (lvl >= 5) {
            lvl = 4;
        }
        if (D_eu_800BE900[i].u0 >= 2) {
            D_eu_800BE900[i].u0 = 0;
        }
        lvl = func_1510D66C(tabs.a[D_eu_800BE900[i].u0][lvl], buf, 3, 0);
        gSPSegment(gfx++, i + 1, lvl);
    }
    return gfx;
}
