/* Frees the tables of cutscene slot `slot` (scene teardown, func_1501E888), when a scene asset is loaded
 * (D_800C3A88[slot], first word = its header {u16 nActors, ...}): every actor's path length table and sample
 * table (SceneActor +4 / +0x38, actors with path keys only), the actor array D_800C3E70, the camera records
 * D_800C3958, the per-actor blocks D_800C3D80, the u16 tables D_800C39E8 / D_800C39F0 / D_800C39F8, the words
 * D_800C3A00, the shared D_800C4170 and the asset itself; all pointers become NULL. */
void func_1501E5AC(s32 slot) {
    u16 *hdr;
    s32 i;

    if ((&D_800C3A88)[slot] == 0) {
        return;
    }
    hdr = *(u16 **)(&D_800C3A88)[slot];
    for (i = 0; i < hdr[0]; i++) {
        if (D_800C39E8[slot][i] != 0) {
            func_10004074((s32)D_800C3E70[slot][i].keys);
            func_10004074((s32)D_800C3E70[slot][i].state);
        }
    }
    func_10004074((s32)D_800C3E70[slot]);
    D_800C3E70[slot] = NULL;
    func_10004074((s32)(&D_800C3958)[slot]);
    (&D_800C3958)[slot] = NULL;
    for (i = 0; i < hdr[0]; i++) {
        func_10004074((s32)D_800C3D80[slot][i]);
        D_800C3D80[slot][i] = NULL;
    }
    func_10004074((s32)D_800C39E8[slot]);
    func_10004074((s32)D_800C39F0[slot]);
    func_10004074((s32)D_800C39F8[slot]);
    func_10004074((s32)D_800C3A00[slot]);
    D_800C39E8[slot] = NULL;
    D_800C39F0[slot] = NULL;
    D_800C39F8[slot] = NULL;
    D_800C3A00[slot] = NULL;
    func_10004074((s32)D_800C4170);
    D_800C4170 = NULL;
    func_10004074((&D_800C3A88)[slot]);
    (&D_800C3A88)[slot] = 0;
}
