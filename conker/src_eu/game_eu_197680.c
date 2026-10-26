#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15169E70 */
u8 *image_fx_spawn(u8 *arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = node_alloc(0x5E, 0, 0x4C, 0, (u8) arg1, 1U);
    if (temp_v0 != NULL) {
        bcopy(arg0, temp_v0 + 0x10, 0x3C);
    }
    return temp_v0;
}

// effect_spawn_template: spawns an effect record from a 0x3C-byte template (image_fx_spawn with priority 0xFF) and
// returns it. P124: the matching body is `void` and leaves the record in v0 for its callers (game_eu_E48B0 stores
// it); in the port a void function returns nothing, so the NM body returns the record.
/* was func_15169ED8 */
u8 *image_fx_spawn_template(void *arg0) {
    return image_fx_spawn(arg0, 0xFF);
}

/* was func_15169EF8 */
void image_fx_update(u8 *arg0) {
    s32 v;
    s32 r;
    s32 t;

    if (*(s8 *)(arg0 + 0x40) != 0) {
        ((void (*)(u8 *))D_8008CDC0[*(s8 *)(arg0 + 0x40)])(arg0);
    }
    v = *(s16 *)(arg0 + 0x26);
    v += *(s16 *)(arg0 + 0x28) * D_800BE9E4;
    r = arg0[0x41] << 8;
    if (v >= r) {
        v -= r;
    } else if (v < 0) {
        v += r;
    }
    *(s16 *)(arg0 + 0x26) = v;
    t = *(s16 *)(arg0 + 0x24);
    if (t != 0) {
        t -= D_800BE9E4;
        if (t <= 0) {
            node_destroy((struct102 *)arg0);
        } else {
            *(s16 *)(arg0 + 0x24) = t;
        }
    }
}

/* P142 */
Gfx *gfx_set_combine_mode(Gfx *gfx, u8 combineId, u8 *needSync);
Gfx *gfx_other_mode_cached(Gfx *gfx, s32 modeL, s32 modeH, u8 *needSync);
Gfx *sprite_load_texture(Gfx *gfx, s32 tex, s32 tmem, s32 tile, s32 cm, s32 age, s32 sfrac, s32 uls, s32 ult);
u32 *image_draw_tiled(u32 *gfx, void *img, f32 scaleX, f32 scaleY, f32 x, f32 y, s32 w, s32 h, s32 flags, s32 sOff, s32 xAdd, s32 frame);
extern u32 D_800A4EA8[][2];
extern s32 D_800D30BC;
/* image_effect_draw: draw callback of the 2D image effect (type 0x5E, image_fx_spawn; e.g. the new-game title
 * cards). Effect data: +0x10 image descriptor, +0x14 second texture (flags & 1; loaded to TMEM 0x100, tile 1,
 * s fraction from +0x34 when flags & 2), +0x26 frame (8.8), +0x2C / +0x30 screen x / y, +0x34 s offset, +0x36 x
 * widening, +0x38 / +0x3A scale x / y (4096 = 1:1; 0 hides), +0x3C / +0x3E size in texels, +0x42..0x45 primitive
 * RGBA, +0x46 render-mode index (D_800A4EA8), +0x47 combiner id, +0x48 2 = extra other-mode bit 0x100000, +0x49
 * flags (1 second texture, 2 its s offset, 4 / 8 mirror x / y, 0x10 1-texel tile border, 0x20 set the
 * primitive depth). Returns the new display-list end. */
/* was func_15169FB8 */
Gfx *image_fx_draw(Gfx *gfx, u8 *fx, s32 arg2) {
    u8 needSync;
    s32 sfrac;
    s32 tileFlags;
    s32 modeL;
    u32 *mode;
    u8 fl;

    if (*(s16 *) (fx + 0x38) == 0 || *(s16 *) (fx + 0x3A) == 0) {
        return gfx;
    }
    needSync = 1;
    gfx = gfx_set_combine_mode(gfx, fx[0x47], &needSync);
    // gDPSetPrimColor(0, 1, r, g, b, a)
    gfx->words.w0 = 0xFA000100;
    gfx->words.w1 = (fx[0x42] << 24) | (fx[0x43] << 16) | (fx[0x44] << 8) | fx[0x45];
    gfx++;
    fl = fx[0x49];
    if (fl & 1) {
        if (fl & 2) {
            sfrac = (*(s16 *) (fx + 0x34) * 4) >> 5;
        } else {
            sfrac = 0;
        }
        gfx = sprite_load_texture(gfx, *(s32 *) (fx + 0x14), 0, 0, 0x100, 1, sfrac, 2, 3);
        fl = fx[0x49];
    }
    if (fl & 0x10) {
        tileFlags = 1;
    } else {
        tileFlags = 0;
    }
    if (fl & 4) {
        tileFlags |= 2;
    }
    if (fl & 8) {
        tileFlags |= 4;
    }
    if (fl & 0x20) {
        // gDPSetPrimDepth(0x795A, 0)
        gfx->words.w1 = 0x795A0000;
        gfx->words.w0 = 0xEE000000;
        gfx++;
    }
    if (fx[0x48] == 2) {
        modeL = 0x100000;
    } else {
        modeL = 0;
    }
    mode = D_800A4EA8[fx[0x46]];
    gfx = gfx_other_mode_cached(gfx, modeL | D_800D30BC | 0x2CA0, (mode[1] | mode[0]) | 4, &needSync);
    return (Gfx *) image_draw_tiled((u32 *) gfx, *(void **) (fx + 0x10), (f32) *(s16 *) (fx + 0x38),
                                 (f32) *(s16 *) (fx + 0x3A), *(f32 *) (fx + 0x2C), *(f32 *) (fx + 0x30),
                                 *(u16 *) (fx + 0x3C), *(u16 *) (fx + 0x3E), tileFlags, *(s16 *) (fx + 0x34),
                                 *(s16 *) (fx + 0x36), *(s16 *) (fx + 0x26) >> 8);
}
