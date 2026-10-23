u8 *func_15031C4C(u8 *, u16, s32);
s32 func_15031360(u8 *, u8 *, Mtx **, s32 *);

/*
 * model_node_points_to_world: transforms n local points (in[i] -> out[i], 3 f32 each) by the matrix of node `node`
 * of a model instance obj (obj +0x1D4 = its matrix array, required). The matrix comes from, in order: the node's
 * attached instance (+0x48: its frame matrix array +0x3E8[D_800BE9C0] + idx * 0x40, 0 when that instance is not
 * ready (+0x3F6)); a sub-model (+0x1E id, func_15031C4C / func_15031360, entry +0x20 when that model is
 * skinned (+0x48)); the node's own frame matrices (+0x34 + D_800BE9C0 * 0x40); else func_15145EA4 with obj's
 * matrix + node byte +2 * 0x40. Mtx (s15.16) -> float with guMtxL2F, points with func_150A7E40.
 * Returns 1, or 0 when something is missing.
 */
s32 func_1514654C(u8 *obj, u8 *node, s32 idx, f32 **in, f32 **out, s32 n) {
    f32 mf[4][4];
    Mtx *mtx;
    s32 unused;
    u8 *sub;
    u8 *att;
    s32 i;

    if (obj == NULL || node == NULL || *(s32 *) (obj + 0x1D4) == 0) {
        return 0;
    }
    att = *(u8 **) (node + 0x48);
    if (att != NULL) {
        if (att[0x3F6] == 0) {
            return 0;
        }
        mtx = (Mtx *) (((u8 **) (att + 0x3E8))[D_800BE9C0] + (idx << 6));
    } else if (*(u16 *) (node + 0x1E) != 0) {
        sub = func_15031C4C(obj, *(u16 *) (node + 0x1E), 0);
        if (sub == NULL) {
            return 0;
        }
        if (func_15031360(sub, obj, &mtx, &unused) == 0) {
            return 0;
        }
        if (*(s32 *) (sub + 0x48) != 0) {
            mtx = (Mtx *) ((u8 *) mtx + (*(u16 *) (node + 0x20) << 6));
        }
    } else if (*(u8 **) (node + 0x34) != NULL) {
        mtx = (Mtx *) (*(u8 **) (node + 0x34) + (D_800BE9C0 << 6));
    } else {
        func_15145EA4(in, out, (Mtx *) (*(u8 **) (obj + 0x1D4) + (node[2] << 6)), n);
        return 1;
    }
    if (mtx == NULL) {
        return 0;
    }
    guMtxL2F(mf, mtx);
    for (i = 0; i < n; i++) {
        func_150A7E40(mf, in[i][0], in[i][1], in[i][2], &out[i][0], &out[i][1], &out[i][2]);
    }
    return 1;
}
