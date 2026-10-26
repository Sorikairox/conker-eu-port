#ifdef NON_MATCHING
// P225 selftest case: a nested #if inside a NON_MATCHING block (nm_resolve used to take the nested #else / #endif
// as the NM block's own and dropped the rest; DIFFTEST_NMNEST_OLD=1 = old). The difftest build has no PORT.
void sfx_cooldown_tick(void) {
    s32 i;

    for (i = 0; i < 4; i++)
    {
        if (D_800D9AB0[i]) {
            if (D_800D9AB0[i] > D_800BE9E4)
            {
#ifdef PORT
                D_800D9AB0[i] -= D_800BE9E4 + 1;
#else
                D_800D9AB0[i] -= D_800BE9E4;
#endif
            } else {
                D_800D9AB0[i] = 0;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/sfx_cooldown_tick.s")
#endif
