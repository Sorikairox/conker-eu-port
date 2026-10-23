// ambient_emitter_add: writes emitter `index` (D_800DE148, 14 bytes) of slot `slot` at (x, y, z) and returns
// index + 1; when index is not below the level's emitter capacity - 1 (D_800B0DF0 +0x18) nothing is written and
// the capacity - 1 is returned. Phase byte: 0x3C for slots with a range below 2, else slot * 4 + (phase & 1) for
// D_800DDC00 slots or slot * 4 + (index & 3). +0xC / +0xD = the slot parameters scaled by a random factor
// (0x100 + rand % spread, the second one + 4 * (rand % spread) more when the sound info has flag 4) >> 10, or
// the parameters >> 2 when spread is 0.
s32 func_1500AF08(u32 index, s32 slot, s32 mode, s16 x, s16 y, s16 z, s32 spread, u8 kind, s32 phase) {
    s32 limit = *(u16 *) ((u8 *) D_800B0DF0 + 0x18) - 1;
    AmbientEmitter *e;
    s16 scale;
    s16 *param;

    if (!(index < (u32) limit)) {
        return limit;
    }
    D_800DE148[index].x = x;
    D_800DE148[index].y = y;
    D_800DE148[index].z = z;
    if (D_800DE000[slot] >= 2) {
        if (D_800DDC00 & (1 << slot)) {
            D_800DE148[index].phase = slot * 4 + (phase & 1);
        } else {
            D_800DE148[index].phase = (index & 3) + slot * 4;
        }
    } else {
        D_800DE148[index].phase = 0x3C;
    }
    D_800DE148[index].slotMode = (mode << 5) | slot;
    D_800DE148[index].kind = kind;
    D_800DE148[index].id = D_800DDFF0[slot];
    param = &D_800BE858[slot * 2];
    if (spread != 0) {
        scale = func_151EFDD0() % spread + 0x100;
        D_800DE148[index].unkC = (param[0] * scale) >> 10;
        if (D_80096090[D_800DDFF0[slot] * 10] & 4) {
            scale = (func_151EFDD0() % spread) * 4 + scale;
        }
        D_800DE148[index].unkD = (param[1] * scale) >> 10;
    } else {
        D_800DE148[index].unkC = param[0] >> 2;
        D_800DE148[index].unkD = param[1] >> 2;
    }
    return index + 1;
}
