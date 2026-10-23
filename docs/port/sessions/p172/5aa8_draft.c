// level_dl_add_texture_scroll: registers texture scrolling for texture `texId` (0: any texture, with a new id
// from D_800E0D20) in level display list `dl` (s32 address): for the `which`-th matching G_SETTIMG (-1: every one),
// the G_SETTILESIZE index and its tile count go into the first free slot of the scroll entry's level-DL-0 list
// (+0x1C / +0x30) or, with `secondDl`, its level-DL-1 list (+0x26 / +0x35). The entry is the first in D_800E0D18
// (oldest first, link +4) with id 0 (none: a new one from func_15195EF4 with `doubled`, speeds speedS / speedT). `unused` is not read.
// Returns the last entry used (NULL when dl is NULL, nothing matched or allocation failed).
void *func_15195AA8(s32 dl, s32 texId, s32 doubled, s32 which, s32 unused, s32 secondDl, s32 speedS, s32 speedT) {
    Gfx *gdl = (Gfx *) dl;
    Ent3C *e = NULL;
    s32 skip;
    s32 idx;
    s32 tileCount;
    u32 w0;
    u32 w1;
    s32 k;

    if (gdl == NULL) {
        return NULL;
    }
    skip = which;
    if (which == -1) {
        skip = 0;
    }
    do {
        idx = func_15195DD8(gdl, texId, skip, &tileCount);
        if (idx == -1) {
            which = 0;
            continue;
        }
        if (texId == 0) {
            texId = D_800E0D20;
        }
        w1 = gdl[idx].words.w1;
        w0 = gdl[idx].words.w0;
        for (e = (Ent3C *) D_800E0D18; e != NULL && e->x8 != 0; e = (Ent3C *) e->node.prev) {
        }
        if (e == NULL) {
            e = func_15195EF4(texId, w1, w0, doubled);
            if (e == NULL) {
                return NULL;
            }
            e->x12 = speedS;
            e->x13 = speedT;
        } else {
            idx = func_15195FF4(idx, (s32) e, w1, doubled);
        }
        skip++;
        if (e->x14 < tileCount) {
            e->x14 = tileCount;
        }
        if (!secondDl) {
            for (k = 0; k < 5 && e->a[k] != -1; k++) {
            }
            if (k < 5) {
                e->a[k] = idx;
                ((u8 *) e)[0x30 + k] = tileCount;
            }
        } else {
            for (k = 0; k < 5 && e->b[k] != -1; k++) {
            }
            if (k < 5) {
                e->b[k] = idx;
                ((u8 *) e)[0x35 + k] = tileCount;
            }
        }
    } while (which == -1);
    if (texId == D_800E0D20) {
        D_800E0D20--;
    }
    return e;
}
