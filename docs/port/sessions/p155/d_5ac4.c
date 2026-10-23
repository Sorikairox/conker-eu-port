void func_15150258(u8 *, u8, s32);
// smoke_cloud_spawn: spawns a smoke cloud at pos (f32[3]) through func_15150258 with a fixed emitter block (0x5C
// bytes: 9 puffs over 3 frames, colours 323 / 214 / 203 / 263, sizes 677..895, drift (0.602, -1.732, 1.512) at 45).
// Returns 0 (the asm leaves func_15150258's v0; callers ignore it).
s32 func_151D5AC4(u8 *pos, u8 arg1, s32 arg2) {
    struct {
        s16 u1C;
        s16 u1E;
        s16 u20;
        s16 u22;
        s32 u24;
        s32 u28;
        s32 pos[3];
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s32 u50;
        s32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        s16 u6A;
        s16 u6C;
        s16 u6E;
        s16 u70;
        s16 u72;
        s8 u74;
    } sp;

    sp.u1C = 0;
    sp.u1E = 0xFF;
    sp.u20 = -0x40;
    sp.u22 = 0x4A;
    sp.u24 = 9;
    sp.u28 = 3;
    sp.pos[0] = ((s32 *)pos)[0];
    sp.pos[1] = ((s32 *)pos)[1];
    sp.pos[2] = ((s32 *)pos)[2];
    sp.u38 = 323.0f;
    sp.u3C = 214.0f;
    sp.u40 = 203.0f;
    sp.u44 = 263.0f;
    sp.u48 = 677.0f;
    sp.u4C = 895.0f;
    sp.u50 = 7;
    sp.u54 = 3;
    sp.u58 = 45.0f;
    sp.u5C = 0.60200006f;
    sp.u60 = -1.7320001f;
    sp.u64 = 1.5120001f;
    sp.u68 = 0xF;
    sp.u6A = 0xF;
    sp.u6C = 0x64;
    sp.u6E = 0x64;
    sp.u70 = 0xC;
    sp.u72 = 0x14;
    sp.u74 = 0;
    func_15150258((u8 *)&sp, arg1, arg2);
    return 0;
}
