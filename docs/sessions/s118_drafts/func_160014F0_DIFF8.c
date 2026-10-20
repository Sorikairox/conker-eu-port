//HOIST u16 *func_160014F0();
extern u16 D_1600388C;
extern s32 D_160038A8;
extern u8 D_16003CE0[];
extern u8 D_16003CE0[];
u16 *func_160014F0(fb, c)
    u16 *fb;
    u8 c;
{
    u16 *p = fb;
    s32 color = D_1600388C;
    u16 bits;
    u16 val;
    s32 ch;
    s32 i;
    u8 *glyph;
    s32 j;

    ch = c;
    if (ch < 0x20) {
        ch = 0x20;
    }
    glyph = D_16003CE0 + ((ch - 0x20) << 3);
    for (i = 0; i < 8; i++) {
        bits = *glyph;
        for (j = 0; j < 8; j++) {
            if (bits & 0x80) {
                val = color;
            } else {
                val = 1;
            }
            bits <<= 1;
            *p++ = val;
        }
        glyph++;
        p += D_160038A8 - 8;
    }
    return fb + 8;
}
