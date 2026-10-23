/* image_draw_tiled: draws the image described by img (the func_15095470 descriptor: +0 address or asset id, +4
 * animated flag, +6 tile width, +8 tile height, +0xA format, +0xB texel size) as a grid of textured rectangles.
 * The picture is w x h texels split into tiles of img's size whose asset ids follow each other (column-major,
 * frame * cols * rows first); with flags & 1 each tile has a 1-texel border on every side (the step is 2 smaller,
 * the s / t start skips the fraction). flags & 2 / & 4 mirror in x / y (negative dsdx / dtdy, s / t from the far
 * edge). (x, y) is the screen centre (10.2 units are made here), scaleX / scaleY are 4096-based (pixels per texel
 * * 4096); sOff is added to the s start, xAdd widens each rectangle's right edge. The top row and the right column
 * hold the remainders. Off-screen left / top edges are clipped with the matching s / t correction. Returns the new
 * display-list end. */
typedef struct {
    s32 tex;        // address or asset id
    u8 animated;
    u8 pad5;
    u16 width;
    u16 height;
    u8 fmt;
    u8 siz;
} ImageTileDesc;

// s / t start correction of a bordered tile: skips the sub-pixel part of the screen coordinate v (10.5 texels)
#define IMAGE_TILE_BORDER_FIX(v, scale) ((s32) (32.0f - ((v) - (f32) (s32) (v)) * 32.0f * (4096.0f / (scale))))

u32 *func_150966AC(u32 *gfx, ImageTileDesc *img, f32 scaleX, f32 scaleY, f32 x, f32 y, s32 w, s32 h, s32 flags, s32 sOff, s32 xAdd, s32 frame) {
    ImageTileDesc tile;
    s32 border;
    s32 tileW;
    s32 tileH;
    s32 s0;
    s32 t0;
    s32 dsdx;
    s32 dtdy;
    s32 cols;
    s32 rows;
    s32 colW;
    s32 topH;
    s32 i;
    s32 j;
    s32 sStart;
    s32 tStart;
    s32 xi;
    s32 yi;
    s32 uly;
    s32 sFix;
    s32 tFix;
    s16 ulx;
    s16 lrx;
    s16 lry;
    s16 clipX;
    s16 clipY;
    u32 dsdt;
    f32 nextX;
    f32 nextY;
    f32 curY;
    f32 rowScreenH;
    f32 topScreenH;

    tileW = img->width;
    tileH = img->height;
    border = flags & 1;
    if (border) {
        tileW -= 2;
        tileH -= 2;
    }
    if (flags & 2) {
        s0 = (img->width + 0xFF) << 5;
        dsdx = (s32) (-4194304.0f / scaleX) & 0xFFFF;
    } else {
        s0 = 0x2000;
        dsdx = (s32) (4194304.0f / scaleX);
    }
    if (flags & 4) {
        t0 = (img->height + 0xFF) << 5;
        dtdy = (s32) (-4194304.0f / scaleY) & 0xFFFF;
    } else {
        t0 = 0x2000;
        dtdy = (s32) (4194304.0f / scaleY);
    }
    cols = (w + tileW - 1) / tileW;
    rows = (h + tileH - 1) / tileH;
    x -= (f32) w * scaleX / 8192.0f;
    tile.tex = img->tex;
    tile.tex += frame * cols * rows;
    y -= (f32) h * scaleY / 8192.0f;
    tile.width = img->width;
    tile.fmt = img->fmt;
    tile.animated = 1;
    tile.siz = img->siz;
    topH = h - (rows - 1) * tileH;
    colW = tileW;
    topScreenH = (f32) topH * scaleY / 4096.0f;
    for (i = 0; i < cols; i++) {
        rowScreenH = topScreenH;
        curY = y;
        tile.height = topH;
        if (i + 1 == cols) {
            colW = w - (cols - 1) * tileW;
            tile.width = colW;
            if (border) {
                tile.width = (u16) colW + 2;
            }
        }
        sStart = s0;
        nextX = x + (f32) colW * scaleX / 4096.0f;
        if (border) {
            sStart = s0 + IMAGE_TILE_BORDER_FIX(x, scaleX);
        }
        sStart += sOff;
        if (border) {
            tile.height = topH + 2;
        }
        if (rows > 0) {
            dsdt = (dsdx << 16) | (dtdy & 0xFFFF);
            xi = (s32) x;
            ulx = xi * 4;
            lrx = ((s32) nextX + xAdd) * 4;
            for (j = 0; j < rows; j++) {
                nextY = curY + rowScreenH;
                tStart = t0;
                if (border) {
                    tStart = t0 + IMAGE_TILE_BORDER_FIX(curY, scaleY);
                }
                yi = (s32) curY;
                gfx = (u32 *) func_15095380((s32) gfx, (s32) &tile, 0, 0, 0, 0, 0, 2, 3);
                tile.tex++;
                uly = yi * 4;
                lry = (s32) nextY * 4;
                // gSPTextureRectangle (clamped at 0), then the s / t of the clipped left / top edge
                gfx[0] = 0xE4000000 | ((MAX(lrx, 0) & 0xFFF) << 12) | (MAX(lry, 0) & 0xFFF);
                clipY = uly;
                gfx[1] = ((MAX(ulx, 0) & 0xFFF) << 12) | (MAX(clipY, 0) & 0xFFF);
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
                    tFix = (clipY * (s16) dtdy) >> 7;
                    if ((s16) dtdy < 0) {
                        tFix = MAX(tFix, 0);
                    } else {
                        tFix = MIN(tFix, 0);
                    }
                }
                gfx[3] = ((sStart - sFix) << 16) | ((tStart - tFix) & 0xFFFF);
                gfx[4] = 0xF1000000;
                gfx[5] = dsdt;
                gfx += 6;
                if (j == 0) {
                    // rows after the top one are whole tiles
                    tile.height = img->height;
                    rowScreenH = (f32) tileH * scaleY / 4096.0f;
                }
                curY = nextY;
            }
        }
        x = nextX;
    }
    return gfx;
}
