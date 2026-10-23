// dl_add_texture_scroll: as func_15195AA8 for a model display list `dl` (s32 address): each matching G_SETTIMG
// (`which`-th, -1: every one) is linked to the scroll entry with id texId (or, with `alwaysNew`, a new one for the
// first match) through func_15196270 (+0x18 chain: dl, G_SETTILESIZE index, tile count). New entries get speeds
// speedS / speedT. Does nothing while D_800BEAC0 is set. Returns the last entry used as s32 (0: none).
// The asm returns an uninitialised stack word when the very first search finds nothing (C: 0).
s32 func_15196344(s32 dl, s32 texId, s32 doubled, s32 which, s32 alwaysNew, s32 speedS, s32 speedT) {
    Gfx *gdl = (Gfx *) dl;
    Ent3C *e = NULL;
    s32 skip;
    s32 idx;
    s32 key;
    s32 tileCount;
    u32 w0;
    u32 w1;

    if (gdl == NULL) {
        return 0;
    }
    if (D_800BEAC0 != 0) {
        return 0;
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
        key = alwaysNew ? -1 : texId;
        for (e = (Ent3C *) D_800E0D18; e != NULL && e->x8 != key; e = (Ent3C *) e->node.prev) {
        }
        w1 = gdl[idx].words.w1;
        w0 = gdl[idx].words.w0;
        if (e == NULL) {
            e = func_15195EF4(texId, w1, w0, doubled);
            if (e == NULL) {
                return 0;
            }
            alwaysNew = 0;
            e->x12 = speedS;
            e->x13 = speedT;
        } else {
            idx = func_15195FF4(idx, (s32) e, w1, doubled);
            alwaysNew = 0;
        }
        if (e->x14 < tileCount) {
            e->x14 = tileCount;
        }
        func_15196270((u8 *) e, dl, idx, tileCount);
        skip++;
    } while (which == -1);
    if (texId == D_800E0D20) {
        D_800E0D20--;
    }
    return (s32) e;
}
