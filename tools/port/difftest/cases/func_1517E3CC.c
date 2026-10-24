#ifdef NON_MATCHING
void func_1517C11C(s32, s32, s32, s32, f32, s32, s32, s32);

/* Per-frame refresh of the 15 positional sound slots (records of 0x68 bytes at D_800DD478, word 0 = active) and
 * their voices (16-byte records at D_800DDA90: +8 voice handle, +0xC "heard this frame"). With D_800DDD20 set,
 * every "heard" flag is cleared, func_1517C11C marks the slots in range of object 0 / player 0 (radius 1500,
 * player +0x380, +0x2F8 position), and each active slot that was not marked is switched off together with its
 * voice handle. */
void func_1517E3CC(void) {
    u8 *voices = (u8 *) &D_800DDA90;
    u8 *slots = (u8 *) &D_800DD478;
    s32 i;

    if (D_800DDD20 == 0) {
        return;
    }
    for (i = 0; i < 15; i++) {
        voices[i * 0x10 + 0xC] = 0;
    }
    func_1517C11C((s32) D_800CC2D0[0].x_position, (s32) D_800CC2D0[0].y_position, (s32) D_800CC2D0[0].z_position,
                  1500, D_800DBFF0->unk380, (s32) D_800DBFF0->unk2F8, (s32) D_800DBFF0->unk2FC,
                  (s32) D_800DBFF0->unk300);
    for (i = 0; i < 15; i++) {
        if (*(s32 *) (slots + i * 0x68) != 0 && voices[i * 0x10 + 0xC] == 0) {
            *(s32 *) (slots + i * 0x68) = 0;
            *(s32 *) (voices + i * 0x10 + 8) = 0;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517E3CC.s")
#endif
