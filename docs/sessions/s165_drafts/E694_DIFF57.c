typedef struct { f32 x, y, z; u8 pad[0xC]; } PtE694;
s32 func_151AE86C(u8 *, u8 *, f32, f32, f32);
u8 *func_151AEB40(u8);
s32 func_151AE694(u8 *arg0, u8 arg1) {
    u8 *v;
    f32 pos[3];
    f32 dx, dy, dz;
    s32 off;
    u8 *o;

    v = func_151AEB40(arg1);
    if (v == NULL) {
        for (;;) {}
    }
    if (*(s16 *)(v + 0x52) == 0 && arg0[0x1CA] != 0 && arg0[0x104] == 0) {
        func_151AE86C(*(u8 **)(arg0 + 0x31C) + 0xA0, v, *(f32 *)(arg0 + 0x14), *(f32 *)(arg0 + 0x18), *(f32 *)(arg0 + 0x1C));
        off = (s32)((f32)(v[0x42] - (s32)(140.0f / *(f32 *)(v + 0x3C)) - 1) * *(f32 *)(*(u8 **)(arg0 + 0x31C) + 0xA0)) * 0x18;
        pos[0] = *(f32 *)(*(u8 **)(v + 0x38) + off);
        pos[1] = *(f32 *)(*(u8 **)(v + 0x38) + off + 4);
        pos[2] = *(f32 *)(*(u8 **)(v + 0x38) + off + 8);
        dx = pos[0] - *(f32 *)(arg0 + 0x14);
        dy = pos[1] - *(f32 *)(arg0 + 0x18);
        dz = pos[2] - *(f32 *)(arg0 + 0x1C);
        if (!(dz * dz + (dx * dx + dy * dy) > 10000.0f)) {
            *(u8 *)(*(u8 **)(arg0 + 0x31C) + 0x98) = arg1;
            arg0[0x8A] = 0x12;
            *(u8 **)(*(u8 **)(arg0 + 0x31C) + 0x9C) = v;
            *(u8 **)(v + 0x44) = arg0;
        }
    }
}
