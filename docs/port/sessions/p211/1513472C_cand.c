// object_state_dispatch_a: calls the D_80089AAC state handler picked by the object's +0x3D state (0..9, else 0)
// with the object and returns the handler's result.
s32 func_1513472C(struct102 *arg0) {
    s32 idx = arg0->unk3D;

    if (idx < 0) {
        idx = 0;
    }
    if (idx >= 10) {
        idx = 0;
    }
    return ((s32 (*)(struct102 *)) D_80089AAC[idx])(arg0);
}
