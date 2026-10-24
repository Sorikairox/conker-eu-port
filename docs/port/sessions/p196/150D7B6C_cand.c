extern s32 *D_80088CA0[2];
s32 func_1510D66C(s32, s32 *, s32, s32);

// anim_segments_set: points segments 2..7 at textures (func_1510D66C, mode 3) taken from the two 5-entry texture id
// tables of D_80088CA0 (segments 2..5 from the first, 6 and 7 from the second): entry (D_800D9D30 >> 8) + 13 per
// segment, mod 5, so the frames cycle with the D_800D9D30 clock (func_150D7B40). Returns the advanced display list.
Gfx *func_150D7B6C(Gfx *gdl) {
    s32 *tabs[2];
    s32 size[4];
    s32 tab;
    s32 frame;
    s32 seg;
    s32 tex;

    tabs[0] = D_80088CA0[0];
    tabs[1] = D_80088CA0[1];
    tab = 0;
    frame = D_800D9D30 >> 8;
    for (seg = 2; seg < 8; seg++, frame += 13) {
        if (seg >= 6) {
            tab = 1;
        }
        tex = func_1510D66C(tabs[tab][frame % 5], size, 3, 0);
        gSPSegment(gdl++, seg, tex);
    }
    return gdl;
}
