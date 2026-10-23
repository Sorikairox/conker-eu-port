extern u8 D_800D31C8;   /* sprite primitive colour r, g, b (alpha from the sprite) */
extern u8 D_800D31C9;
extern u8 D_800D31CA;
/* sprite_draw_rect: draws the sprite spr (+0xA alpha, +0xB animation speed, +0xC animation frame, +0xD flip x / y
 * bits 1 / 2, +0x10 texture descriptor: u16 width +4 / height +6, u8 frame count +0xA, bit 7 = ping-pong) as one
 * textured rectangle at the screen rectangle func_15095F18 left in D_800D3090..D_800D30A8 (x / y scale, left,
 * top, depth, width, height). sOff / tOff shift the texture start; tOff != 0 also shrinks the rectangle by one
 * texel on each side (the width / height globals keep the shrunk size). xAdd widens the right edge. Off-screen
 * left / top edges are clipped with the matching s / t correction. Unless D_800D31CB, sets the primitive colour
 * first. Then advances the animation frame (8 steps per frame, D_800BE9A0 ticks). Returns the new display-list
 * end. */
s32 func_15096144(s32 gfxAddr, s32 sprAddr, s32 sOff, s32 tOff, s32 xAdd) {
    u32 *gfx = (u32 *) gfxAddr;
    u8 *spr = (u8 *) sprAddr;
    u8 *tex;
    f32 xs;
    f32 ys;
    f32 left;
    f32 top;
    f32 depth;
    f32 width;
    f32 height;
    s32 xsi;
    s32 ysi;
    s32 lefti;
    s32 topi;
    s32 dsdx;
    s32 dtdy;
    s32 sStart;
    s32 tStart;
    s32 tFrac;
    s32 uly;
    s32 sFix;
    s32 tFix;
    s16 lrx;
    s16 lry;
    s16 ulx;
    s16 uly16;
    u8 flip;
    u8 frames;
    u8 step;
    u8 frame;

    xs = D_800D3090;
    ys = D_eu_800D3094;
    left = *(f32 *) D_800D3098;
    xsi = (s32) xs;
    top = D_800D309C;
    ysi = (s32) ys;
    depth = D_800D30A0;
    if (tOff != 0) {
        D_800D30A4 -= (xs + xs) / depth;
        D_800D30A8 -= (ys + ys) / depth;
        left += xs / depth;
        top += ys / depth;
    }
    width = D_800D30A4;
    height = D_800D30A8;
    if (width < 2.0f) {
        width = 2.0f;
    }
    dsdx = ((s32) depth << 10) / xsi;
    dtdy = ((s32) depth << 10) / ysi;
    if (D_800D31CB == 0) {
        // gDPSetPrimColor(0, 1, r, g, b, sprite alpha)
        gfx[0] = 0xFA000100;
        gfx[1] = (D_800D31C8 << 24) | (D_800D31C9 << 16) | (D_800D31CA << 8) | spr[0xA];
        gfx += 2;
    }
    lefti = (s32) left;
    sStart = (s32) ((32.0f - (left - (f32) lefti) * 32.0f) * depth / (f32) xsi) + sOff + 0x2000;
    topi = (s32) top;
    flip = spr[0xD];
    tFrac = (s32) ((32.0f - (top - (f32) topi) * 32.0f) * depth / (f32) ysi);
    tStart = tFrac + tOff + 0x2000;
    if (flip != 0) {
        if (flip & 1) {
            dsdx = -dsdx & 0xFFFF;
            sStart = (*(u16 *) (*(u8 **) (spr + 0x10) + 4) + 0xFF) << 5;
        }
        if (flip & 2) {
            dtdy = -dtdy & 0xFFFF;
            tStart = ((*(u16 *) (*(u8 **) (spr + 0x10) + 6) + 0xFF) << 5) - tFrac;
        }
    }
    // gSPTextureRectangle (clamped at 0), then the s / t of the clipped left / top edge
    lrx = ((s32) ((f32) xAdd + width - 1.0f) + lefti) * 4;
    lry = ((s32) (height - 1.0f) + topi) * 4;
    gfx[0] = 0xE4000000 | ((MAX(lrx, 0) & 0xFFF) << 12) | (MAX(lry, 0) & 0xFFF);
    ulx = lefti * 4;
    uly = topi * 4;
    uly16 = uly;
    gfx[1] = ((MAX(ulx, 0) & 0xFFF) << 12) | (MAX(uly16, 0) & 0xFFF);
    gfx[2] = 0xE1000000;
    sFix = 0;
    if (ulx < 0) {
        sFix = (ulx * (s16) dsdx) >> 7;
        if ((s16) dsdx < 0) {
            sFix = MAX(sFix, 0);
        } else {
            sFix = MIN(sFix, 0);
        }
    }
    tFix = 0;
    if (uly < 0) {
        tFix = (uly16 * (s16) dtdy) >> 7;
        if ((s16) dtdy < 0) {
            tFix = MAX(tFix, 0);
        } else {
            tFix = MIN(tFix, 0);
        }
    }
    gfx[3] = ((sStart - sFix) << 16) | ((tStart - tFix) & 0xFFFF);
    gfx[4] = 0xF1000000;
    gfx[5] = (dsdx << 16) | (dtdy & 0xFFFF);
    gfx += 6;

    // animation: frame counts in 1/8 frames; ping-pong textures use bit 7 of the counter as the direction
    tex = *(u8 **) (spr + 0x10);
    frames = tex[0xA];
    if (frames != 0) {
        step = spr[0xB] * D_800BE9A0;
        if (frames & 0x80) {
            frame = spr[0xC];
            if (frame & 0x80) {
                frame -= step;
                spr[0xC] = frame;
                if (!(frame & 0x80)) {
                    spr[0xC] = (frame + step) & 0x7F;
                }
            } else {
                frame += step;
                spr[0xC] = frame;
                if (frame >= (tex[0xA] & 0x7F) * 8) {
                    spr[0xC] = (frame - step) | 0x80;
                }
            }
        } else {
            frame = spr[0xC] + step;
            spr[0xC] = frame;
            if (frame >= tex[0xA] * 8) {
                spr[0xC] = frame - tex[0xA] * 8;
            }
        }
    }
    return (s32) gfx;
}
