#ifdef NON_MATCHING
s32 func_150AD9A0(s32, s32, s32);

/* Aim offset from player `player` to object `obj`: d = distance (func_150AD9A0 of the truncated delta between the
 * object position and the player's +0x2F8 vector). Beyond 2000 units, or when the offset func_151846C0 writes to
 * (*x, *y, *z) (scaled by 1.3, D_800A7758) has a zero component, the clip heights D_800D3AA8 / D_800D3AAC are
 * cleared and 0 is returned; else d. */
s32 func_15185360(s32 obj, s32 player, f32 *x, f32 *y, f32 *z) {
    struct127 *o = &D_800CC2D0[obj];
    struct108 *p = &D_800DBFF0[player];
    s32 d;

    d = func_150AD9A0((s32) (o->x_position - p->unk2F8), (s32) (o->y_position - p->unk2FC),
                      (s32) (o->z_position - p->unk300));
    if (d > 2000) {
        D_800D3AA8 = 0.0f;
        D_800D3AAC = D_800D3AA8;
        return 0;
    }
    func_151846C0(obj, x, y, z);
    *x *= 1.3f;
    *y *= 1.3f;
    *z *= 1.3f;
    if (*x == 0.0f || *y == 0.0f || *z == 0.0f) {
        D_800D3AA8 = 0.0f;
        D_800D3AAC = D_800D3AA8;
        return 0;
    }
    return d;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15185360.s")
#endif
