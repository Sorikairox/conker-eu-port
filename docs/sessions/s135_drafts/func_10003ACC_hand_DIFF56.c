void func_10003ACC(s32 r, s32 g, s32 b) {
    u16 *fb;
    u16 *fb2;
    s32 i;
    s32 n;

    fb = (u16 *)D_8002AAE8[0];
    i = 0;
    n = (s32)(D_800BE620 * D_800BE624 * 2) >> 1;
    if (fb != NULL) {
        while (i < n) {
            *fb++ = GPACK_RGBA5551(r, g, b, 1);
            i++;
        }
        fb2 = (u16 *)D_8002AAE8[1];
        for (i = 0; i < n; i++) {
            fb2[i] = GPACK_RGBA5551(r, g, b, 1);
        }
    }
}
