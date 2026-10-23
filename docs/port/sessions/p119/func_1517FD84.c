extern u8 D_800DA130[];   /* per player: 0x40-byte HUD projection matrix */
void func_150A7EE0(u8 *, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);

/* hud_lens_set_target: sets the player's lens / zoom centre D_800DE218[player] (offset from the viewport centre
 * +0x0C / +0x10 of D_800BE628 + player * 0x180). With project == 0, (x, y, z) is a world point: projected with
 * D_800DA130[player] (func_150A7EE0; w 0 counts as 1) to viewport coordinates (+0x2C / +0x24 added, y down);
 * else x / y are taken as they are. Both are clamped to [-10000, 10000] (rodata D_800A7660..68). */
void func_1517FD84(s32 project, f32 x, f32 y, f32 z, s32 player) {
    f32 sx;
    f32 sy;
    f32 sz;
    f32 w;
    u8 *vp;

    if (project == 0) {
        func_150A7EE0(D_800DA130 + player * 0x40, x, y, z, &sx, &sy, &sz, &w);
        if (w == 0.0f) {
            w = 1.0f;
        }
        vp = (u8 *) D_800BE628 + player * 0x180;
        sx = *(f32 *) (vp + 0xC) * sx / w;
        sy = *(f32 *) (vp + 0x10) * sy / w;
        sx = sx + *(f32 *) (vp + 0xC);
        sy = *(f32 *) (vp + 0x10) - sy;
        sx = sx + *(f32 *) (vp + 0x2C);
        sy = sy + *(f32 *) (vp + 0x24);
    } else {
        sx = x;
        sy = y;
        vp = (u8 *) D_800BE628 + player * 0x180;
    }
    if (sx > 10000.0f) {
        sx = 10000.0f;
    } else if (sx < -10000.0f) {
        sx = -10000.0f;
    }
    if (sy > 10000.0f) {
        sy = 10000.0f;
    } else if (sy < -10000.0f) {
        sy = -10000.0f;
    }
    D_800DE218[player][0] = sx - *(f32 *) (vp + 0xC);
    D_800DE218[player][1] = sy - *(f32 *) (vp + 0x10);
}
