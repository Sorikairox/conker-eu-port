Gfx *func_1510D338(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3);
u8 *func_1510DE40(u8 *arg0, s32 arg1);
Gfx *func_150CFAF8(Gfx *gdl);
Gfx *func_150A55A0(s32, Gfx *, u8 *, s32, s32, s32);
extern u8 D_800840D0[];   /* combiner/othermode block for translucent meshes (segment 6 + 0x20) */
extern u8 D_80084250[];   /* the same block for opaque meshes */
extern u8 D_800DA030[];   /* per player: 0x40-byte view matrix (float) */
extern s32 D_800BEFC4;    /* display list capacity (commands) */

// world_mesh_draw: P183: draws one world mesh record `obj` (0xA0 bytes) for `player`: alpha =
// obj[0x8B + player] * obj[0x8A] / 255 (0xFF when both are 0xFF), nothing when 0 or when the opaque/translucent
// pass flag `pass` (0 or 0x10) does not match (opaque meshes draw only when obj[0x4F] & 0x10 differs from pass,
// translucent ones only in pass 0). Flags obj+0x6C bits 0/4/5 call the debug position hooks. Then pipe sync,
// render-mode block (D_800840D0 translucent / D_80084250 opaque), cull mode (obj[0x4F] & 2), func_1510D338 colour
// (0xFF, alpha), func_1510DE40, segment 1 = obj+0x20[frame], matrix `mtx`, optional func_150CFAF8 (flag 0x200),
// the mesh (func_150A55A0 when obj[0x70] & 2, else a G_DL to obj+0x1C). Returns the new gdl, or the start when
// the frame display list overflows. `unused` is never read.
s32 func_15113D54(s32 arg0, u8 *obj, s32 mtx, s16 player, s32 unused, s32 pass) {
    Gfx *gdl = (Gfx *) arg0;
    Gfx *start = gdl;
    s32 a = obj[0x8B + player];
    s32 alpha;
    u16 flags;

    if (a == 0xFF && obj[0x8A] == 0xFF) {
        alpha = 0xFF;
    } else {
        alpha = (s32) (a * obj[0x8A]) / 0xFF;
        if (alpha == 0) {
            return (s32) gdl;
        }
    }
    if (alpha == 0xFF) {
        if (pass == (obj[0x4F] & 0x10)) {
            return (s32) gdl;
        }
    } else if (pass != 0) {
        return (s32) gdl;
    }

    flags = *(u16 *) (obj + 0x6C);
    if (flags != 0) {
        if (flags & 1) {
            gdl = func_1511FC2C(gdl, (f32) *(s16 *) (obj + 0x10),
                                (f32) *(s16 *) (obj + 0x12) + *(f32 *) (obj + 0x18),
                                (f32) *(s16 *) (obj + 0x14), *(f32 *) (obj + 0x4), player);
        } else if (flags & 0x10) {
            gdl = func_1511FC2C(gdl, (f32) *(s16 *) (obj + 0x10),
                                (f32) *(s16 *) (obj + 0x12) + *(f32 *) (obj + 0x18),
                                (f32) *(s16 *) (obj + 0x14), (f32) *(s32 *) (obj + 0x7C), player);
        } else if (flags & 0x20) {
            gdl = func_1511FC44(gdl, (f32) *(s16 *) (obj + 0x10),
                                (f32) *(s16 *) (obj + 0x12) + *(f32 *) (obj + 0x18),
                                (f32) *(s16 *) (obj + 0x14), player);
        }
    }

    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xDB060020;
    if (alpha < 0xFF) {
        gdl->words.w1 = (u32) D_800840D0;
    } else {
        gdl->words.w1 = (u32) D_80084250;
    }
    gdl++;
    if ((obj[0x4F] & 2) == 2) {
        gdl->words.w0 = 0xD9FFFFFF;
        gdl->words.w1 = 0x400000;
    } else {
        gdl->words.w0 = 0xD9BFFFFF;
        gdl->words.w1 = 0;
    }
    gdl++;
    gdl->words.w0 = 0xD9FFFFFF;
    gdl->words.w1 = 0x20000;
    gdl++;
    gdl = func_1510D338(gdl, 0xFF, alpha, player);
    gdl = (Gfx *) func_1510DE40((u8 *) gdl, (s32) obj);
    if (pass == 0) {
        gdl->words.w0 = 0xD9FFFFFF;
        gdl->words.w1 = 0x110000;
        gdl++;
    }
    gdl->words.w0 = 0xDB060004;
    gdl->words.w1 = *(u32 *) (obj + 0x20 + D_800BE9C0 * 4);
    gdl++;
    gdl->words.w0 = 0xDA380003;
    gdl->words.w1 = mtx;
    gdl++;
    gdl->words.w0 = 0xD9F7FFFF;
    gdl->words.w1 = 0;
    gdl++;
    if (*(u16 *) (obj + 0x6C) & 0x200) {
        gdl = func_150CFAF8(gdl);
    }
    if ((obj[0x70] & 2) == 2) {
        gdl = func_150A55A0(*(s32 *) (obj + 0x1C), gdl, D_800DA030 + player * 0x40, 0, 0,
                            *(s32 *) (obj + 0x20 + D_800BE9C0 * 4) + 0xFF000000);
    } else {
        gdl->words.w0 = 0xDE000000;
        gdl->words.w1 = *(u32 *) (obj + 0x1C);
        gdl++;
    }
    gdl->words.w0 = 0xD9EEFFFF;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl++;
    if (D_800BEFC4 < (((u8 *) gdl - (u8 *) D_800BEDE8[D_800BE9C0]) >> 3)) {
        return (s32) start;
    }
    return (s32) gdl;
}
