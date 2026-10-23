s32 func_1501370C(struct16 *arg0) {
    u8 idx = arg0->unk17;
    void (*func)(struct16 *) = (void (*)(struct16 *)) D_80082EA0[idx];

    if (func != NULL) {
        func(arg0);
    }
    return 1;
}
