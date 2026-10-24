/* P204 */
// model_tile_fade_cb: model-node callback (D_800845xx table, s32 (u8 *, u8 *)) for node n of the character pl:
// does nothing while pl +0x2D0 is NULL. State n +0x38: 0 = start (becomes 1 once pl +0x84 is 5, else the tile is
// reset to t 2), 1 = shown (fade 1), 2 = gone (fade 0). While pl +0x84 is 5 the fade follows the height
// (+0x2D0)->+8: 1 below 69, 0 above 84 (state 2), linear in between. The first G_SETTILESIZE of the node's
// display list (*(n +0x24)) gets ult = 44 + 58 * fade (uls 2). Returns 0.
// Rare leaves the fade uninitialised for a state other than 0..2 when pl +0x84 is not 5 (asm: a stack slot); 0 here.
s32 func_150F5FD4(u8 *n, u8 *pl) {
    u8 *ref = *(u8 **) (pl + 0x2D0);
    Gfx *dl;
    s32 reset;
    f32 fade = 0.0f;
    f32 y;
    s32 i;
    s32 t;

    if (ref == NULL) {
        return 0;
    }
    dl = **(Gfx ***) (n + 0x24);
    reset = FALSE;
    switch (*(s32 *) (n + 0x38)) {
        case 0:
            if (*(u16 *) (pl + 0x84) == 5) {
                *(s32 *) (n + 0x38) = 1;
                fade = 1.0f;
            } else {
                reset = TRUE;
            }
            break;
        case 1:
            fade = 1.0f;
            break;
        case 2:
            fade = 0.0f;
            break;
    }
    if (*(u16 *) (pl + 0x84) == 5) {
        y = *(f32 *) (ref + 8);
        if (y < 69.0f) {
            fade = 1.0f;
        } else if (y > 84.0f) {
            fade = 0.0f;
            *(s32 *) (n + 0x38) = 2;
        } else {
            fade = 1.0f - (y - 69.0f) / 15.0f;
        }
    }
    for (i = 0; (s8) (dl[i].words.w0 >> 24) != (s8) G_SETTILESIZE; i++) {
    }
    if (reset) {
        t = 2;
    } else {
        t = (s32) (58.0f * fade + 44.0f);
    }
    dl[i].words.w0 = (G_SETTILESIZE << 24) | (2 << 12) | (t & 0xFFF);
    return 0;
}
