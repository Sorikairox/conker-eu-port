#ifdef NON_MATCHING
s32 func_15142E24(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
u8 *func_15095B70(u8 *, u8 *);
extern u8 *D_8008CDEC[];
extern s16 D_800DD5EC; /* last sprite other-mode (1 / 2 / 3), shared with func_150A6D40 */
extern s32 D_800D30BC; /* TLUT bit of the last loaded texture */
extern u8 D_800D31C8;
extern u8 D_800D31C9;
extern u8 D_800D31CA;
// tinted_sprite_draw: draw handler of the particle type whose tick is func_1516DBE8 (D_8008BBF8 / D_8008CD3C, same
// slot as func_150A6D40). Loads the texture D_8008CDEC[+0x1A] frame +0x1B (func_15142E24), picks the combine mode
// (2 for a texture of format 5 at +0xA, else 1; set only when it differs from D_800DD5EC, after a pipe sync), sets the
// other mode 0x2C00 | TLUT | (0x100000 for mode 2), the colour D_800D31C8..CA from +0x1C..+0x1E and the env colour
// +0x20..+0x22 (only when it differs from D_800DD5F8..FC; alpha 0), and draws the quad (+0xE..+0x16, alpha +0x1F)
// with func_15095B70. Returns the advanced display list.
// The asm leaves its other-mode word (sp+0x5C) uninitialised when the combine mode is unchanged (a stale stack
// word); the C uses the word that belongs to the mode, i.e. what the previous draw of this mode set.
u8 *func_1516DCA8(u8 *gfx, u8 *obj, s32 arg2) {
    struct {
        s16 x, y, z;
        s16 sizeX, sizeZ;
        u8 alpha;
        u8 pad[2];
        u8 flag;
    } quad; /* sp84 */
    s32 *tex;
    s32 synced; /* the s32 at sp78; func_15142E24 / func_15142FBC see it as a byte */
    s32 mode;
    s32 other;
    s32 r;
    s32 g;
    s32 b;

    synced = 0;
    D_800D31CB = 0;
    tex = (s32 *) D_8008CDEC[obj[0x1A]];
    gfx = (u8 *) func_15142E24((s32) gfx, (s32) tex, obj[0x1B] << 8, 2, 0x100, 0x100, 0, 6, (s32) &quad,
                               (u8 *) &synced, 3);
    if (((u8 *) tex)[0xA] == 5) {
        mode = 2;
    } else {
        mode = 1;
    }
    other = (mode == 1) ? 0 : 0x100000;
    if (mode != D_800DD5EC) {
        if (synced == 0) {
            ((s32 *) gfx)[0] = 0xE7000000; /* gDPPipeSync */
            ((s32 *) gfx)[1] = 0;
            gfx += 8;
            synced = 1;
        }
        D_800DD5EC = mode;
        if (mode == 1) {
            ((s32 *) gfx)[0] = 0xFC30B261; /* gDPSetCombine */
            ((s32 *) gfx)[1] = 0x5566FF7F;
        } else {
            ((s32 *) gfx)[0] = 0xFC30B5FF;
            ((s32 *) gfx)[1] = 0x5FFEFE38;
        }
        gfx += 8;
    }
    gfx = (u8 *) func_15142FBC((Gfx *) gfx, other | D_800D30BC | 0x2C00, 0x5049DC, (u8 *) &synced);

    quad.x = *(s16 *) (obj + 0xE);
    quad.y = *(s16 *) (obj + 0x10);
    quad.z = *(s16 *) (obj + 0x12);
    quad.sizeX = *(s16 *) (obj + 0x14);
    quad.sizeZ = *(s16 *) (obj + 0x16);
    quad.flag = 0;
    quad.alpha = obj[0x1F];
    D_800D31C8 = obj[0x1C];
    D_800D31C9 = obj[0x1D];
    D_800D31CA = obj[0x1E];
    r = obj[0x20];
    g = obj[0x21];
    b = obj[0x22];
    if (r != D_800DD5F8 || g != D_800DD5FA || b != D_800DD5FC) {
        D_800DD5F8 = r;
        D_800DD5FA = g;
        D_800DD5FC = b;
        if (synced == 0) {
            ((s32 *) gfx)[0] = 0xE7000000; /* gDPPipeSync */
            ((s32 *) gfx)[1] = 0;
            gfx += 8;
        }
        ((s32 *) gfx)[0] = 0xFB000000; /* gDPSetEnvColor(r, g, b, 0) */
        ((s32 *) gfx)[1] = (r << 24) | (g << 16) | (b << 8);
        gfx += 8;
    }
    return func_15095B70(gfx, (u8 *) &quad);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516DCA8.s")
#endif
