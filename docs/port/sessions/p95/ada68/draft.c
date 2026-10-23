extern s64 D_80088950;

/* P95: random float in [0, 1]: one step of the 64-bit shift-register generator in D_80088950 (as func_150ADA20),
 * low 16 bits of the new state times 1/65535 (rodata D_8009FB10 = 0x37800080). */
f32 func_150ADA68(void) {
    u64 x = (u64) D_80088950;
    u64 t;

    t = ((x << 63) >> 31) | ((x << 31) >> 32);
    t ^= (x << 44) >> 32;
    x = ((t >> 20) & 0xFFF) ^ t;
    D_80088950 = (s64) x;
    return (f32) (s32) (x & 0xFFFF) * 1.5259022e-05f;
}

