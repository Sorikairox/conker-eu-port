typedef struct {
    f32 x;      // 0x00
    f32 y;      // 0x04
    f32 scaleA; // 0x08
    f32 scaleB; // 0x0C
    u8 kind;    // 0x10 (D_80088E04)
    s16 life;   // 0x12
    u16 flags;  // 0x14
    s16 u16;    // 0x16
    s16 u18;    // 0x18
    u8 u1A;
    u8 u1B;
    u8 u1C;
    u8 u1D;
    u8 u1E;
    u8 u1F;
    u8 u20;
    u8 u21;
    u8 u22;
    u8 u23;
    s32 u24;
    s32 u28;
    s32 u2C;
    s32 u30;
    s32 u34;
    s32 u38;
    s32 u3C;
    u8 u40;
    u8 u41;
} SpawnSpecE7B20;
extern u8 D_80088E04;
s32 func_151559FC(void *, s32, s32, s32, s32, s32, s32);

// particle_spawn_simple: fills a particle spec (position x / y from `pos`, both scales `scale`, kind D_80088E04,
// lifetime `life`, flags `flags` | 0x40, the colour / fade bytes and fixed defaults) and spawns it with func_151559FC
// (`arg8`, `arg9`, `arg10`, `arg11`). Returns the spawned record.
s32 func_150E7B20(f32 *pos, f32 scale, s16 life, u8 flags, u8 arg4, u8 arg5, s16 arg6, s16 arg7, s32 arg8, s32 arg9,
                  u8 arg10, s32 arg11) {
    SpawnSpecE7B20 spec;

    spec.x = pos[0];
    spec.y = pos[1];
    spec.scaleA = scale;
    spec.scaleB = scale;
    spec.kind = D_80088E04;
    spec.life = life;
    spec.flags = flags | 0x40;
    spec.u16 = arg6;
    spec.u18 = arg7;
    spec.u1A = 4;
    spec.u1B = 0xFF;
    spec.u1C = 0xE6;
    spec.u1D = 0xBE;
    spec.u1E = arg4;
    spec.u1F = 0xFF;
    spec.u20 = 0xFF;
    spec.u21 = 0xFF;
    spec.u22 = 0xFF;
    spec.u23 = arg5;
    spec.u24 = 1;
    spec.u28 = 0;
    spec.u2C = 0;
    spec.u30 = 7;
    spec.u34 = 0x3C;
    spec.u38 = 0x80;
    spec.u3C = 0x20;
    spec.u40 = 0;
    spec.u41 = 0xA;
    return func_151559FC(&spec, 0, arg8, arg9, 0, arg10, arg11);
}
