#ifdef NON_MATCHING
void ambient_emitters_update(s32, s32, s32, s32, f32, s32, s32, s32);

/* Per-frame refresh of the 15 positional sound slots (records of 0x68 bytes at g_ambient_slots, word 0 = active) and
 * their voices (16-byte records at g_ambient_voices: +8 voice handle, +0xC "heard this frame"). With g_ambient_emitter_count set,
 * every "heard" flag is cleared, ambient_emitters_update marks the slots in range of object 0 / player 0 (radius 1500,
 * player +0x380, +0x2F8 position), and each active slot that was not marked is switched off together with its
 * voice handle. */
void ambient_slots_refresh(void) {
    u8 *voices = (u8 *) &g_ambient_voices;
    u8 *slots = (u8 *) &g_ambient_slots;
    s32 i;

    if (g_ambient_emitter_count == 0) {
        return;
    }
    for (i = 0; i < 15; i++) {
        voices[i * 0x10 + 0xC] = 0;
    }
    ambient_emitters_update((s32) g_objects[0].x_position, (s32) g_objects[0].y_position, (s32) g_objects[0].z_position,
                  1500, g_player_views->unk380, (s32) g_player_views->unk2F8, (s32) g_player_views->unk2FC,
                  (s32) g_player_views->unk300);
    for (i = 0; i < 15; i++) {
        if (*(s32 *) (slots + i * 0x68) != 0 && voices[i * 0x10 + 0xC] == 0) {
            *(s32 *) (slots + i * 0x68) = 0;
            *(s32 *) (voices + i * 0x10 + 8) = 0;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/ambient_slots_refresh.s")
#endif
