extern s64 D_80088950;
// 64-bit shift-register random number (state D_80088950), low word returned.
s32 func_150ADA20(void) {
    u64 x = (u64) D_80088950;
    u64 t;

    t = ((x & 1) << 32) | ((x >> 1) & 0xFFFFFFFF);
    t ^= (x & 0xFFFFF) << 12;
    t ^= (t >> 20) & 0xFFF;
    D_80088950 = t;
    return (s32) t;
}
