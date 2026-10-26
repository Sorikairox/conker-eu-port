extern s64 D_80088950;

/* MIPS III: a 64-bit add of the (sign-extended) argument */
void random_seed(s32 arg0) {
    D_80088950 = (s64)arg0 + 1;
}
