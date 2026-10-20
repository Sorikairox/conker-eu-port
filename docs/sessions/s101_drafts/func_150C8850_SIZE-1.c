typedef struct {
    u8 pad0[2];
    s8 u2;
    u8 pad3;
    s16 u4;
    s16 u6;
    s16 u8;
} S8850;
extern S8850 *D_eu_800BE900;

void func_150C8850(void) {
    s32 i;
    s32 cur;
    s32 tgt;
    s32 d;
    s32 ad;
    s32 step;

    for (i = 0; i < 10; i++) {
        cur = D_eu_800BE900[i].u6;
        if (cur != D_eu_800BE900[i].u8) {
            tgt = D_eu_800BE900[i].u8;
            if (cur < 0) {
                tgt = -tgt;
            }
            d = tgt - cur;
            step = D_800BE9E4 * 16;
            ad = d;
            if (d < 0) {
                ad = -d;
            }
            if (ad < step) {
                D_eu_800BE900[i].u6 = tgt;
            } else {
                D_eu_800BE900[i].u6 = cur + step * ((d < 0) ? -1 : 1);
            }
        }
        D_eu_800BE900[i].u4 += D_eu_800BE900[i].u6 * D_eu_800BE900[i].u2 * D_800BE9A0;
        if (D_eu_800BE900[i].u4 >= 0x500) {
            D_eu_800BE900[i].u4 -= 0x500;
            D_eu_800BE900[i].u4 = 0x500 - D_eu_800BE900[i].u4;
            D_eu_800BE900[i].u2 = -D_eu_800BE900[i].u2;
            if (D_eu_800BE900[i].u4 >= 0x500) {
                D_eu_800BE900[i].u4 = 0x4FF;
            }
        } else if (D_eu_800BE900[i].u4 < 0) {
            D_eu_800BE900[i].u4 = -D_eu_800BE900[i].u4;
            D_eu_800BE900[i].u2 = -D_eu_800BE900[i].u2;
            if (D_eu_800BE900[i].u4 < 0) {
                D_eu_800BE900[i].u4 = 0;
            }
        }
    }
}
