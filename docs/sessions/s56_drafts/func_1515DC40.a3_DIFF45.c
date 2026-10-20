void func_1515F4E4(s16 *);
extern s32 D_800DD140;
#define MW(g, a, b) { Gfx *_g = (g); _g->words.w0 = (a); _g->words.w1 = (b); }
#define HI(a, b) ((((a) >> 16) << 16) | (((b) >> 16) & 0xFFFF))
#define LO(a, b) (((a) << 16) | ((b) & 0xFFFF))
Gfx *func_1515DC40(Gfx *gdl, s32 arg1) {
    MW(gdl++, 0xDB020000, 0);
    MW(gdl++, 0xD9FFFFFF, 0x20000);
    func_1515F4E4((s16 *)((f32 (*)[16])((u8 *)D_800BE628 + arg1 * 0x180 + 0x100))[D_800BE9C0]);
    MW(gdl++, 0xDB100000, HI((&D_800DD140)[0], (&D_800DD140)[1]));
    MW(gdl++, 0xDB100008, HI((&D_800DD140)[0], (&D_800DD140)[1]));
    MW(gdl++, 0xDB100004, ((&D_800DD140)[2] >> 16) << 16);
    MW(gdl++, 0xDB10000C, ((&D_800DD140)[2] >> 16) << 16);
    MW(gdl++, 0xDB100010, LO((&D_800DD140)[0], (&D_800DD140)[1]));
    MW(gdl++, 0xDB100018, LO((&D_800DD140)[0], (&D_800DD140)[1]));
    MW(gdl++, 0xDB100014, (&D_800DD140)[2] << 16);
    MW(gdl++, 0xDB10001C, (&D_800DD140)[2] << 16);
    MW(gdl++, 0xDB100020, 0);
    MW(gdl++, 0xDB100024, (&D_800DD140)[3] << 16);
    MW(gdl++, 0xDB100028, 0);
    MW(gdl++, 0xDB10002C, (&D_800DD140)[3] << 16);
    return gdl;
}
