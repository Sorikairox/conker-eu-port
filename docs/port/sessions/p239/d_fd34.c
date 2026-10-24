#ifdef NON_MATCHING
void func_1518FE50(s32);
// D_8008DA1C: the bone-spark emitter's tick handler table (0x8008DA1C: func_15190B2C, func_15190C34). func_1518FD34
// indexes it with self +0x88 and returns the handler's result; func_1518FDC8 indexes D_8008DA20 (= D_8008DA1C + 1)
// with self +0x89. One signature for both views (wasm call_indirect): s32 (u8 *).
extern s32 (*D_8008DA1C[])(u8 *);

// bone_sparks_tick: effect-child handler (D_8008FFE0 [3] / D_8008FFE8 [1]). Advances the emitter's spark counter
// (self +0x30) by (rate +0x34 + random f32 * spread +0x38) * D_800BE9A4 (frame time), emits the sparks
// (func_1518FE50), then runs the tick handler D_8008DA1C[self +0x88] (none: -1) and returns its result (1 without).
// The second argument (the position the effect-node dispatchers pass) is not used; it is there for the table's
// common signature s32 (node, pos).
s32 func_1518FD34(u8 *self, void *pos) {
    f32 *count = (f32 *)(self + 0x30);
    s8 tick;

    count[0] += (count[1] + func_150ADA68() * count[2]) * D_800BE9A4;
    func_1518FE50((s32)self);
    tick = (s8)self[0x88];
    if (tick != -1) {
        return D_8008DA1C[tick](self);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_1518FD34.s")
#endif
