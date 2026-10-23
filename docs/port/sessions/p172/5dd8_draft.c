// dl_find_scroll_texture: finds, in display list `dl`, the (skip+1)-th G_SETTIMG (0xFD) that loads texture `texId`
// (w1 == D_800B1268[texId]; texId 0 = any texture). Returns the index of the first G_SETTILESIZE (0xF2) after it and
// stores in *tileCount the number of G_SETTILESIZE commands of the run there (1, plus one per following
// G_SETTILE / G_SETTILESIZE pair); returns -1 at G_ENDDL (0xDF) when there is no such texture.
s32 func_15195DD8(Gfx *dl, s32 texId, s32 skip, s32 *tileCount) {
    s32 i = -1;
    s32 j;
    u8 op;
    u8 next;
    u8 next2;

    *tileCount = 0;
    for (;;) {
        do {
            i++;
            op = dl[i].words.w0 >> 24;
        } while (op != 0xFD && op != 0xDF);
        if (op == 0xDF) {
            return -1;
        }
        if (texId == 0 || dl[i].words.w1 == D_800B1268[texId]) {
            if (skip <= 0) {
                break;
            }
            skip--;
        }
    }
    do {
        i++;
    } while ((u8)(dl[i].words.w0 >> 24) != 0xF2);
    j = i;
    do {
        (*tileCount)++;
        next = dl[j + 1].words.w0 >> 24;
        next2 = dl[j + 2].words.w0 >> 24;
        j += 2;
    } while (next == 0xF5 && next2 == 0xF2);
    return i;
}
