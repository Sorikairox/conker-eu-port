s32 func_1513477C(struct102 *arg0) {
    s32 idx = arg0->unk3D;

    if (idx >= 10) {
        idx = 0;
        arg0 = 0;
    }
    if (idx < 0) {
        idx = 0;
    }
    return ((s32 (*)(struct102 *)) D_80089AD4[idx])(arg0);
}
