s32 func_1510D66C(s32, s32 *, s32, s32);

// hud_icon_sheet_load: P208: loads HUD icon sheet `sheet` (texture 0xD18 + sheet: CI4 64x64, its 16-colour RGBA16
// palette 0x800 bytes in) for the status icons of func_150918EC. *ready is 1 when the sheet is resident and the
// load commands were added; otherwise it is 0 and `gdl` is returned unchanged.
Gfx *func_15091534(Gfx *gdl, s32 sheet, u8 *ready) {
    s32 tex;

    *ready = 0;
    tex = func_1510D66C(0xD18 + sheet, NULL, 3, 0);
    if (tex == 0x80000000) {
        return gdl;
    }
    gdl->words.w0 = 0xFD500000; /* texture image CI16 */
    gdl->words.w1 = tex;
    gdl++;
    gdl->words.w0 = 0xF5500000;
    gdl->words.w1 = 0x07098260;
    gdl++;
    gDPLoadSync(gdl++);
    gdl->words.w0 = 0xF3000000;
    gdl->words.w1 = 0x073FF000;
    gdl++;
    gDPPipeSync(gdl++);
    gdl->words.w0 = 0xF5400800; /* render tile CI4, palette 0 */
    gdl->words.w1 = 0x00098260;
    gdl++;
    gdl->words.w0 = 0xF2000000;
    gdl->words.w1 = 0x000FC0FC;
    gdl++;
    gdl->words.w0 = 0xFD100000; /* palette image */
    gdl->words.w1 = tex + 0x800;
    gdl++;
    gDPLoadSync(gdl++);
    gdl->words.w0 = 0xF0000000; /* load TLUT, 16 colours */
    gdl->words.w1 = 0x0603C000;
    gdl++;
    gdl->words.w0 = 0xEF00AC3F; /* other modes: TLUT RGBA16 */
    gdl->words.w1 = 0x00504244;
    gdl++;
    *ready = 1;
    return gdl;
}
