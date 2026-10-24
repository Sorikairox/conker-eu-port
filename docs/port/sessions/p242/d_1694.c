#ifdef NON_MATCHING
extern f32 D_800AB37C[2][3];

// object_offset_point: transforms the fixed offset D_800AB37C[which] by the object's matrix (obj + 0x1D4) into
// out; returns 0 (out untouched) when the object has no matrix, 1 otherwise
s32 func_151D1694(u8 *obj, f32 *out, u8 which) {
    void *mtx = *(void **)(obj + 0x1D4);

    if (mtx == NULL) {
        return 0;
    }
    func_15143134(D_800AB37C[which], out, mtx);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1694.s")
#endif
