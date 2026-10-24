Gfx *func_15142E24(Gfx *gfx, s32 tex, s32 frame, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *flag, s32 argA);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
Gfx *func_15095B70(Gfx *gfx, u8 *quad);
extern s32 D_800A4EA8[]; /* render mode pairs (2 words each) */

// sprite_quad_draw: P210: render-layer draw callback (D_8008B848 layer 3): draws the textured quad of node `obj`.
/* Texture obj +0x10 (word 0 = its frame table, indexed by frame s16 obj +0x14 >> 8), quad position / size s16
 * obj +0x18..+0x20, byte obj +0x23 copied into the quad; render mode D_800A4EA8 entry 3. Returns the display list end. */
s32 func_15167C58(s32 gdl, u8 *obj, s16 player) {
    struct {
        s16 x, y, z;
        s16 w, h;
        u8 bA;
        u8 padB[2];
        u8 bD;
    } quad;
    u8 flag;
    u8 *tex = *(u8 **)(obj + 0x10);
    s16 frame = *(s16 *)(obj + 0x14);
    s32 *mode;
    Gfx *gfx;

    /* the asm stores the word 1 at the flag's address; the byte the callees read (big-endian) is 0 */
    flag = 0;
    gfx = func_15142E24((Gfx *)gdl, (s32)tex, frame << 8, 2, 0x100, 0x100, (*(s32 **)tex)[frame >> 8], 5, (s32)&quad,
                        &flag, 3);
    quad.x = *(s16 *)(obj + 0x18);
    quad.y = *(s16 *)(obj + 0x1A);
    quad.z = *(s16 *)(obj + 0x1C);
    quad.w = *(s16 *)(obj + 0x1E);
    quad.h = *(s16 *)(obj + 0x20);
    quad.bA = obj[0x23];
    quad.bD = 0;
    /* the asm compares the s8 at obj +0x22 with 0xFF (entry 9), which never matches: always entry 3 */
    mode = &D_800A4EA8[3 * 2];
    gfx = func_15142FBC(gfx, 0x2C00, (mode[1] | mode[0]) | 4, &flag);
    return (s32)func_15095B70(gfx, (u8 *)&quad);
}
