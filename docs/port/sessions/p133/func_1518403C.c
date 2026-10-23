s32 func_1510D3E0(Gfx *, s32, s32, s32, s16 **);

/*
 * hud_model_load: loads model idx once (asset 9, id idx + 0xAD, through func_1502B6BC) into the 0x14-byte slot
 * D_800DDE80[idx]: +0 the asset, +4 / +8 / +0xC its words 0 / 2 / 6, +0x10 the vertex list func_1510D3E0 fills
 * while relocating the asset's display list (word 4, also kept in D_800DDF78[idx]); D_800DDF68[idx] = 1 marks it
 * loaded. Nothing when the slot is already set or the asset is missing.
 */
void func_1518403C(s32 idx) {
    s32 *slot = (s32 *) ((u8 *) D_800DDE80 + idx * 0x14);
    s32 *asset;

    if (slot[0] != 0) {
        return;
    }
    asset = (s32 *) func_1502B6BC(0, 0, 0, 2, 9, idx + 0xAD);
    if (asset == NULL) {
        return;
    }
    slot[0] = (s32) asset;
    slot[1] = asset[0];
    slot[2] = asset[2];
    slot[3] = asset[6];
    D_800DDF78[idx] = asset[4];
    func_1510D3E0((Gfx *) asset[4], 0, 1, 0x3E, (s16 **) &slot[4]);
    D_800DDF68[idx] = 1;
}
