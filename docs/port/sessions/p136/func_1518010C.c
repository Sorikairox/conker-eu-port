/*
 * scope_lens_draw: draws the four quadrants of a round lens / range-finder texture (tex x tex texels, tile 0
 * already loaded by the caller) as mirrored scissored texture rectangles of size x size pixels around the view's
 * lens centre (viewport centre +0x0C / +0x10 of D_800BE628 + view * 0x180, plus D_800DE218[view]). (dx, dy) moves
 * the lower-right quadrant to (cx + dx, cy + dy) and the upper-left one to (cx - dx, cy - dy); the other two take
 * one coordinate from each. Texture steps are +-tex / size in s5.10; the quadrants on the +x / +y side start at
 * texel tex and step backwards, the others start at 0, each with the sub-pixel fraction of its corner
 * (s10.5 = the corner's fraction * 32). Returns the display list after the 4 * 3 commands.
 */
Gfx *func_1518010C(Gfx *gdl, s32 size, s32 tex, f32 dx, f32 dy, s32 view) {
    u8 *vp = (u8 *) D_800BE628 + view * 0x180;
    f32 *lens = D_800DE218[view];
    f32 cx = *(f32 *) (vp + 0x0C) + lens[0];
    f32 cy = *(f32 *) (vp + 0x10) + lens[1];
    f32 r = (f32) size;
    f32 x0 = cx + dx; /* +x side: x0 .. x0 + r */
    f32 y0 = cy + dy; /* +y side: y0 .. y0 + r */
    f32 x1 = cx - dx; /* -x side: x1 - r .. x1 */
    f32 y1 = cy - dy; /* -y side: y1 - r .. y1 */
    s32 ts = tex << 5;
    s32 k = (u32) ((f32) tex / r * 1024.0f) & 0xFFFF;

    /* lower right: mirrored in s and t */
    gSPScisTextureRectangle(gdl++, (s32) x0 * 4, (s32) y0 * 4, (s32) (x0 + r) * 4, (s32) (y0 + r) * 4, 0,
                            ts + ((s32) (x0 * 32.0f) & 0x1F), ts + ((s32) (y0 * 32.0f) & 0x1F), -k, -k);
    /* upper left: forward in s and t */
    gSPScisTextureRectangle(gdl++, (s32) (x1 - r) * 4, (s32) (y1 - r) * 4, (s32) x1 * 4, (s32) y1 * 4, 0,
                            0x1F - ((s32) ((x1 - r) * 32.0f) & 0x1F), 0x1F - ((s32) ((y1 - r) * 32.0f) & 0x1F), k, k);
    /* upper right: mirrored in s */
    gSPScisTextureRectangle(gdl++, (s32) x0 * 4, (s32) (y1 - r) * 4, (s32) (x0 + r) * 4, (s32) y1 * 4, 0,
                            ts + ((s32) (x0 * 32.0f) & 0x1F), 0x1F - ((s32) ((y1 - r) * 32.0f) & 0x1F), -k, k);
    /* lower left: mirrored in t */
    gSPScisTextureRectangle(gdl++, (s32) (x1 - r) * 4, (s32) y0 * 4, (s32) x1 * 4, (s32) (y0 + r) * 4, 0,
                            0x1F - ((s32) ((x1 - r) * 32.0f) & 0x1F), ts + ((s32) (y0 * 32.0f) & 0x1F), k, -k);
    return gdl;
}
