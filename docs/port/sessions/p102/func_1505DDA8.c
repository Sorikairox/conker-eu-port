f32 func_1505DF10(u8 *arg0, u8 arg1, u16 *arg2, f32 *arg3, f32 *arg4);

/* First player 0..D_80082FA0 (live object in D_800CC2D0) that `rec` sees: closer than rec +0x3C * scale / 2
 * (func_1505DF10 gives the squared distance and the direction) and within the cone of width `cone` around rec's
 * heading +0x76 ((u16)(heading - dir + cone / 2) < cone). Returns the player number, -1 for none. (The asm also
 * stores a 6th argument 0 for func_1505DF10, which its definition does not take; `unused` is not read.) */
s32 func_1505DDA8(struct127 *rec, s32 unused, u16 cone, f32 scale) {
    s32 i;
    f32 r;
    f32 d;
    u16 dir;
    f32 dy;
    f32 h;

    for (i = 0; i <= D_80082FA0; i = (u8)(i + 1)) {
        if (D_800CC2D0[i].interaction_state == 0) {
            continue;
        }
        r = rec->xz_velocity * scale * 0.5f;
        d = func_1505DF10((u8 *)rec, i, &dir, &dy, &h);
        if (d < r * r && (u16)(*(u16 *)((u8 *)rec + 0x76) - dir + cone / 2) < cone) {
            return (s8)i;
        }
    }
    return -1;
}
