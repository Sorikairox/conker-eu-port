s32 func_1510D66C(s32, s32 *, s32, s32);
Gfx *func_151E8E94(Gfx *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
typedef struct {
    s32 v[7];
} Div7;
extern Div7 D_8009044C;
extern s32 D_80090424[];

#define GW(g, a, b) { Gfx *_g = (Gfx *)(g); _g->words.w0 = (a); _g->words.w1 = (b); }

Gfx *func_151EB5AC(Gfx *gdl, s32 x, s32 y, s32 n) {
    s32 i;
    s32 q;
    s32 started;
    s32 tex;
    Div7 d = D_8009044C;

    x *= 4;
    y *= 4;
    if (n >= 10000000) {
        n = 9999999;
    }
    if (n < 0) {
        n = 0;
    }
    started = 0;
    for (i = 6; i >= 0; i--) {
        q = n / d.v[i];
        n = n % d.v[i];
        if (q > 0 || started || i == 0) {
            tex = func_1510D66C(D_80090424[q], NULL, 3, 0);
            started = 1;
            if (tex != 0x80000000) {
                GW(gdl++, 0xFD180000, tex);
                GW(gdl++, 0xF5180000, 0x07094250);
                GW(gdl++, 0xE6000000, 0);
                GW(gdl++, 0xF3000000, 0x073FF000);
                GW(gdl++, 0xE7000000, 0);
                GW(gdl++, 0xF5181000, 0x00094250);
                GW(gdl++, 0xF2000000, 0x0007C07C);
                gdl = func_151E8E94(gdl, x, y, x + 0x80, y + 0x80, 0, 0, 0, 0x400, 0x400);
            }
            x += 0x60;
        }
    }
    return gdl;
}
