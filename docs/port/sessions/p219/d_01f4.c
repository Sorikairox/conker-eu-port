s32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_1516972C(struct102 *);
// effect_node_launch: P219. Entry 0 of the effect-node handler table D_8008FC48 (EU 0x8008FFE8), run by the asm
// dispatcher func_1519AF14 (1C3530). node +0x2C = the particle, node +0x30 = its config (NULL: the particle is freed
// with func_1516972C). Otherwise the particle gets velocity (target - node pos +0x34) * cfg +0x60 (+0x148..+0x150),
// +0x154 = random f32 * cfg +0x68 + cfg +0x64, +0x158 = cfg +0x6C, +0x6C / +0x6E = cfg s16 +0x70 / +0x72,
// +0x1C = random % (cfg s16 +0x76 + 1) + cfg s16 +0x74, +0x70 = 0x21 when cfg +0x7C bit 0 else 0x20, +0x71 = 0x24,
// +0x58 |= 0x08000001.
// target (a1): the dispatcher never sets a1 at its jalr (stale register: a loop index on the early exits, memcpy /
// func_1513D2F0 leftovers on the loop path - see P215.md), so on N64 the velocity comes from whatever a1 points at.
// The N64 build keeps that read (byte-faithful behaviour, difftest-checked); the PORT build does not dereference the
// bogus pointer and aims at the node's own position instead (velocity 0).
// Returns s32 only for the table signature (the siblings func_15190174 / func_151901B4 return s32); the dispatcher
// never reads v0. Path 2 returns the random int (the asm leaves it in v0), path 1 returns 0.
s32 func_151901F4(struct_eu_1BAAA0_d *arg0, struct_eu_vec3 *target) {
    u8 *node = (u8 *)arg0;
    u8 *p = *(u8 **)(node + 0x2C);
    u8 *cfg = *(u8 **)(node + 0x30);
    s32 r;

    if (cfg == NULL) {
        func_1516972C((struct102 *)p);
        return 0;
    }
#ifdef PORT
    target = (struct_eu_vec3 *)(node + 0x34);
#endif
    *(f32 *)(p + 0x148) = (target->x - *(f32 *)(node + 0x34)) * *(f32 *)(cfg + 0x60);
    *(f32 *)(p + 0x14C) = (target->y - *(f32 *)(node + 0x38)) * *(f32 *)(cfg + 0x60);
    *(f32 *)(p + 0x150) = (target->z - *(f32 *)(node + 0x3C)) * *(f32 *)(cfg + 0x60);
    *(f32 *)(p + 0x154) = func_150ADA68() * *(f32 *)(cfg + 0x68) + *(f32 *)(cfg + 0x64);
    *(f32 *)(p + 0x158) = *(f32 *)(cfg + 0x6C);
    *(s16 *)(p + 0x6C) = *(s16 *)(cfg + 0x70);
    *(s16 *)(p + 0x6E) = *(s16 *)(cfg + 0x72);
    r = func_150ADA20();
    *(s16 *)(p + 0x1C) = (u32)r % (u32)(*(s16 *)(cfg + 0x76) + 1) + *(s16 *)(cfg + 0x74);
    p[0x70] = (cfg[0x7C] & 1) ? 0x21 : 0x20;
    p[0x71] = 0x24;
    *(s32 *)(p + 0x58) |= 0x08000001;
    return r;
}
