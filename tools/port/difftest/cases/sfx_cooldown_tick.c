#ifdef NON_MATCHING
// P225 selftest case: a nested #if inside a NON_MATCHING block (nm_resolve used to take the nested #else / #endif
// as the NM block's own and dropped the rest; DIFFTEST_NMNEST_OLD=1 = old). The difftest build has no PORT.
void sfx_cooldown_tick(void) {
    s32 i;

    for (i = 0; i < 4; i++)
    {
        if (g_sfx_cooldowns[i]) {
            if (g_sfx_cooldowns[i] > g_frame_ticks)
            {
#ifdef PORT
                g_sfx_cooldowns[i] -= g_frame_ticks + 1;
#else
                g_sfx_cooldowns[i] -= g_frame_ticks;
#endif
            } else {
                g_sfx_cooldowns[i] = 0;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/sfx_cooldown_tick.s")
#endif
