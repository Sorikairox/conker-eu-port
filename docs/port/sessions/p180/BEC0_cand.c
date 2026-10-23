// ambient_emitters_build: level start: sets up the 15 ambient sound slots (ids / flags at D_800BE4A0), allocates
// the emitter records (capacity D_800B0DF0 +0x18, 14 bytes each) and, for every level triangle whose flag word
// (D_800DBE5C) has a slot (bits 16-19, 1-based), runs the placer of the slot's row and the triangle's kind (bits
// 20-22) from D_8008D2A0 / D_8008D258 with mode ((flags >> 5) & 3) ^ 3, counting emitters per slot in D_800BE898;
// then clears +0xB of every emitter, sorts them by x (func_1517BE0C) and seeds the per-slot random offsets
// D_800DE0C0 / D_800DE040. Skipped when the level has no emitter capacity, in scene 0x1D, or in scene 6 unless
// D_80038080 is set.
void func_1500BEC0(void) {
    u16 *slots;
    u32 flags;
    s32 slot;
    s32 kind;
    s16 *placer;
    s32 i;
    s32 q;

    func_1500BE68();
    if (*(u16 *) ((u8 *) D_800B0DF0 + 0x18) == 0) {
        return;
    }
    if ((D_800BE9F0 == 6 && D_80038080 == 0) || D_800BE9F0 == 0x1D) {
        return;
    }
    slots = (u16 *) &D_800BE4A0;
    for (i = 0; i < 15; i++) {
        func_1500AD84(i, slots[i * 2], slots[i * 2 + 1]);
    }
    D_800DE148 = allocate_memory(*(u16 *) ((u8 *) D_800B0DF0 + 0x18) * 14, 1, 2, 0);
    func_1510F800(0);
    if (D_800DBE5C != 0) {
        for (i = 0; i < D_800DBE4C; i++) {
            flags = ((u32 *) D_800DBE5C)[i];
            if (flags & 0xF0000) {
                slot = ((flags >> 16) & 0xF) - 1;
                kind = (flags >> 20) & 7;
                placer = D_8008D2A0[D_800DE0B0[slot]][kind];
                D_800DDD20 = D_8008D258[placer[0]].place(placer[1], kind, slot, ((flags >> 5) & 3) ^ 3, D_800DDD20,
                                                         (s16 **) (D_800DC26C + i * 12));
                D_800BE898[slot]++;
            }
        }
    }
    for (i = 0; i < D_800DDD20; i++) {
        D_800DE148[i].unkB = 0;
    }
    D_8008D254 = 0;
    func_1517BE0C(0, D_800DDD20 - 1);
    for (i = 0; i < 60; i++) {
        q = i >> 2;
        if (D_800DE000[q] != 0) {
            D_800DE0C0[i] = (func_151EFDD0() % D_800DE000[q]) << 8;
        } else {
            D_800DE0C0[i] = 0;
        }
        D_800DE040[q] = func_151EFDD0();
    }
}
