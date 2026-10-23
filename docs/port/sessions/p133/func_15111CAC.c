void func_10004074(s32);
void func_1510DC14(s32);
void func_15111DD8(void);
s32 func_1502B7F0(s32 *, s32, ...);
extern s32 *D_8008955C[];

/*
 * overlay_mode_set: switches the camera overlay (D_800B0DF0: +8 state, +9 overlay id). mode 1: state 1, frees the
 * overlay asset D_800DC2B0 (when loaded) and calls func_15111DD8. Other modes, only when the id changes and the
 * state is 4: releases the 0x168 textures of the current overlay (D_8008955C[id], when D_80038080 is set), frees
 * D_800DC2B0, stores the new id and loads its asset (type 0xD) into D_800DC2B0 with func_1502B7F0.
 */
void func_15111CAC(s32 mode) {
    s32 i;

    if (mode == 1) {
        D_800B0DF0->unk8 = 1;
        if (D_800DC2B0 != 0) {
            func_10004074(D_800DC2B0);
        }
        func_15111DD8();
        return;
    }
    if (mode == D_800B0DF0->unk9 || D_800B0DF0->unk8 != 4) {
        return;
    }
    if (D_80038080 != 0) {
        for (i = 0; i < 0x168; i++) {
            func_1510DC14(*D_8008955C[D_800B0DF0->unk9] + i);
        }
    }
    func_10004074(D_800DC2B0);
    D_800B0DF0->unk9 = mode;
    func_1502B7F0(&D_800DC2B0, 2, 0xD, D_800B0DF0->unk9);
}
