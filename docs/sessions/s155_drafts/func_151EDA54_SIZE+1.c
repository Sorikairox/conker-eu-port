extern u8 D_8009E280[];
extern u8 D_8009E284[];
extern u8 D_8009E288[];
extern u8 D_8009E28C[];

typedef struct {
    u8 pad0[6];
    u16 w;
    u16 h;
    u8 fmt;
    u8 siz;
} TexHdrA54;

Gfx *func_151EDA54(Gfx *gdl, TexHdrA54 *tex, s32 *size) {
    s32 masks;
    s32 maskt;
    s32 n;
    Gfx *g;

    g = gdl++;
    *size = (D_8009E280[tex->siz] + tex->w * tex->h) >> D_8009E284[tex->siz];
    masks = 1;
    n = 2;
    while (n < tex->w) {
        n *= 2;
        masks++;
    }
    maskt = 1;
    n = 2;
    while (n < tex->h) {
        n *= 2;
        maskt++;
    }
    g->words.w0 = 0xE7000000;
    g->words.w1 = 0;
    g = gdl++;
    g->words.w0 = 0xF5000000 | ((tex->fmt & 7) << 21) | ((D_8009E28C[tex->siz] & 3) << 19);
    g->words.w1 = 0x07000000;
    g = gdl++;
    g->words.w0 = 0xF5000000 | ((tex->fmt & 7) << 21) | ((tex->siz & 3) << 19) | ((((D_8009E288[tex->siz] * tex->w + 7) >> 3) & 0x1FF) << 9);
    g->words.w1 = 0x80000 | ((maskt & 0xF) << 14) | 0x200 | ((masks & 0xF) << 4);
    g = gdl++;
    g->words.w0 = 0xF2000000;
    g->words.w1 = ((((tex->w - 1) << 2) & 0xFFF) << 12) | (((tex->h - 1) << 2) & 0xFFF);
    return gdl;
}
