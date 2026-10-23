extern u16 D_800DA290[]; /* [player * 3 + i]: wobble phase (12 bits, the sine angle is phase >> 4) */
extern u8 D_800DA2A8[];  /* [player * 3 + i]: phase speed */
extern u8 D_800DA2B8[];  /* [player * 3 + i]: wobble amplitude */
extern u8 D_800DA2C8[];  /* [player * 3 + i]: current level */
extern u8 D_800DA2D4[];  /* [i]: default level */
extern u8 D_800DA2D8[];  /* [player * 3 + i]: requested level; element 0 != 0 = a request is pending */
f32 func_150489B0(u8);

/* tint_channels_update: per frame for a player whose D_800DBFF0 record has +0x5F0 & 1: three colour channels.
 * Each level D_800DA2C8 moves by 2 * step (D_800BE9E4) toward the requested level (D_800DA2D8, when a request is
 * pending, else the default D_800DA2D4); a sine wobble (func_150489B0(phase >> 4) * amplitude) around it, minus
 * 0x7F, is added to the "up" byte D_800D9F88 when >= 0, else to the "down" byte D_800D9F98 (both capped at 0x7F);
 * the phase advances by its speed (mod 0x1000). The request flag is cleared afterwards. */
void func_1510D090(s32 player) { /* s32: the asm uses a0 as it is (callers pass an s16) */
    s32 step;
    s32 pending;
    s32 i;
    s32 j;
    s32 level;
    s32 target;
    s32 d;
    s32 v;

    if (!(*(s32 *) ((u8 *) D_800DBFF0 + player * 0x9A0 + 0x5F0) & 1)) {
        return;
    }
    step = D_800BE9E4 * 2;
    pending = D_800DA2D8[player * 3];
    for (i = 0; i < 3; i++) {
        j = player * 3 + i;
        level = D_800DA2C8[j];
        target = pending ? D_800DA2D8[j] : D_800DA2D4[i];
        d = target - level;
        if (d != 0) {
            if ((d < 0 ? -d : d) < step) {
                level = target;
            } else if (d >= 0) {
                level += step;
            } else {
                level -= step;
            }
            D_800DA2C8[j] = level;
        }
        v = (s32) (func_150489B0((D_800DA290[j] >> 4) & 0xFF) * D_800DA2B8[j]) + level - 0x7F; /* level not truncated to u8 here (as in the asm) */
        if (v >= 0) {
            D_800D9F88[j] += v;
        } else {
            D_800D9F98[j] -= v;
        }
        if (D_800D9F88[j] >= 0x80) {
            D_800D9F88[j] = 0x7F;
        }
        if (D_800D9F98[j] >= 0x80) {
            D_800D9F98[j] = 0x7F;
        }
        D_800DA290[j] = (D_800DA290[j] + D_800DA2A8[j]) & 0xFFF;
    }
    D_800DA2D8[player * 3] = 0;
}
