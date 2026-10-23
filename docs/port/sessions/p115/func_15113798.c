void func_150A7B80(Mtx *arg0);
void func_15114E8C(f32 (*arg0)[4], u8 *arg1);
extern s32 D_800895E0[];     /* per group: pointer to the group's entry list pointer (entries: u16 record id, u16) */
extern s32 D_800895F0[];     /* per DL buffer: pointer to the matrix array pointer (one Mtx per record id) */
extern u16 D_800DC318[];     /* per group: entry count */
extern f32 D_800DC338[][4][4]; /* per DL buffer: fallback matrix */

/* world_records_update_matrices: per-frame matrix pass over the world-object records (called by func_15019130, the
 * world update). For each group 0..D_80082FA0 that func_150859AC(group, 0) accepts, every listed record id gets its
 * Mtx in the current DL buffer's array (D_800895F0[D_800BE9C0]):
 *  - disabled record (+0x70 & 1): func_150A7B80;
 *  - kind +0x4E 3: left as it is; kind < 3: from func_15114E8C (record orientation / position);
 *  - kind 0x65..0x7C (follows object D_800CC2D0[kind - 100]): rotation from the record angles +0x2C / +0x30 /
 *    +0x34 (func_150A7CB0) at the object's position +0x14; with an attachment +0x1D4, at its +0x30 position,
 *    raised by the object's +0x90 (func_150442C0), and that point is written back to the record (+0x10 / 12 / 14);
 *  - any other kind: the buffer's fallback matrix D_800DC338[D_800BE9C0]. */
void func_15113798(void) {
    f32 mf[4][4];
    s32 group;
    s32 j;
    u16 id;
    u8 *rec;
    u8 *obj;
    u8 *att;
    s32 kind;

    for (group = 0; group <= D_80082FA0; group++) {
        if (func_150859AC((s16)group, 0) == 0) {
            continue;
        }
        for (j = 0; j < D_800DC318[group]; j++) {
            id = *(u16 *)(*(u8 **)D_800895E0[group] + j * 4);
            rec = (u8 *)D_800DBEF4 + id * 0xA0;
            if ((rec[0x70] & 1) == 1) {
                func_150A7B80((Mtx *)(*(u8 **)D_800895F0[D_800BE9C0] + id * 0x40));
                continue;
            }
            kind = rec[0x4E];
            if (kind == 3) {
                continue;
            }
            if (kind < 3) {
                func_15114E8C(mf, rec);
            } else if (kind >= 0x65 && kind < 0x7D) {
                obj = (u8 *)D_800CC2D0 + (kind - 100) * 0x32C;
                if (*(u8 **)(obj + 0x1D4) == NULL) {
                    func_150A7CB0(mf, *(s32 *)(rec + 0x2C), *(s32 *)(rec + 0x30), *(s32 *)(rec + 0x34));
                    mf[3][0] = *(f32 *)(obj + 0x14);
                    mf[3][1] = *(f32 *)(obj + 0x18);
                    mf[3][2] = *(f32 *)(obj + 0x1C);
                } else {
                    att = *(u8 **)(obj + 0x1D4);
                    func_150A7CB0(mf, *(s32 *)(rec + 0x2C), *(s32 *)(rec + 0x30), *(s32 *)(rec + 0x34));
                    mf[3][0] = *(f32 *)(att + 0x30);
                    mf[3][1] = *(f32 *)(att + 0x34);
                    mf[3][2] = *(f32 *)(att + 0x38);
                    func_150442C0(mf, 0.0f, (f32) * (s16 *)(obj + 0x90), 0.0f);
                    *(s16 *)(rec + 0x10) = (s32)mf[3][0];
                    *(s16 *)(rec + 0x12) = (s32)mf[3][1];
                    *(s16 *)(rec + 0x14) = (s32)mf[3][2];
                }
            } else {
                guMtxF2L(D_800DC338[D_800BE9C0], (Mtx *)(*(u8 **)D_800895F0[D_800BE9C0] + id * 0x40));
                continue;
            }
            id = *(u16 *)(*(u8 **)D_800895E0[group] + j * 4);
            guMtxF2L(mf, (Mtx *)(*(u8 **)D_800895F0[D_800BE9C0] + id * 0x40));
        }
    }
}
