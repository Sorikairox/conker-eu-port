extern f32 D_80038400;     /* sprite size units -> screen x */
extern f32 D_80038404;     /* sprite size units -> screen y */
extern f32 D_800D3090;     /* last sprite rect: x scale */
extern f32 D_eu_800D3094;  /* y scale */
extern f32 D_800D309C;     /* top (D_800D3098 = left, declared as a struct array in variables.h) */
extern f32 D_800D30A0;     /* depth */
extern f32 D_800D30A4;     /* width */
extern f32 D_800D30A8;     /* height */

/*
 * sprite_screen_rect: screen rectangle of the sprite `spr` (s16 scale +6 / +8, texture +0x10 with u16 size +4 / +6)
 * centred on the screen point (sx, sy) at depth w, in the current player's viewport (D_800BE628 + D_80082FA4 *
 * 0x180; scales +0x14 / +0x18, or +0x1C / +0x20 when alt): width = tex w * (scale x * D_80038400 * vp scale) / w,
 * height likewise. *visible = 1 when the rectangle overlaps the viewport's clip box (x: +0x2C..+0x30, y:
 * +0x24..+0x28), else 0. The scales, corner, depth and size are left in D_800D3090..D_800D30A8 for the sprite
 * drawer. Nothing but *visible = 0 happens when a scale is 0. (void: the file prototypes said s32, no caller used it).
 */
void func_15095F18(s32 sprArg, f32 sx, f32 sy, f32 w, s32 alt, s32 *visible) {
    u8 *spr = (u8 *) sprArg;
    u8 *vp;
    u8 *tex;
    f32 scaleX;
    f32 scaleY;
    f32 inv;
    f32 width;
    f32 height;
    f32 left;
    f32 top;

    *visible = 0;
    if (*(s16 *) (spr + 6) == 0 || *(s16 *) (spr + 8) == 0) {
        return;
    }
    scaleX = (f32) *(s16 *) (spr + 6) * D_80038400;
    scaleY = (f32) *(s16 *) (spr + 8) * D_80038404;
    if (alt != 0) {
        vp = (u8 *) D_800BE628 + D_80082FA4 * 0x180;
        scaleX *= *(f32 *) (vp + 0x1C);
        scaleY *= *(f32 *) (vp + 0x20);
    } else {
        vp = (u8 *) D_800BE628 + D_80082FA4 * 0x180;
        scaleX *= *(f32 *) (vp + 0x14);
        scaleY *= *(f32 *) (vp + 0x18);
    }
    tex = *(u8 **) (spr + 0x10);
    inv = 1.0f / w;
    width = (f32) *(u16 *) (tex + 4) * scaleX * inv;
    height = (f32) *(u16 *) (tex + 6) * scaleY * inv;
    left = sx - width * 0.5f;
    top = sy - height * 0.5f;
    if (*(f32 *) (vp + 0x2C) <= left + width && left < *(f32 *) (vp + 0x30) && *(f32 *) (vp + 0x24) <= top + height &&
        top < *(f32 *) (vp + 0x28)) {
        *visible = 1;
    }
    D_800D3090 = scaleX;
    D_eu_800D3094 = scaleY;
    *(f32 *) D_800D3098 = left;
    D_800D309C = top;
    D_800D30A0 = w;
    D_800D30A4 = width;
    D_800D30A8 = height;
    return;
}
