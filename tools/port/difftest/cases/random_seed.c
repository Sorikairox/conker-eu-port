extern s64 g_random_seed; /* was D_80088950 */

/* MIPS III: a 64-bit add of the (sign-extended) argument */
void random_seed(s32 arg0) {
    g_random_seed = (s64)arg0 + 1;
}
