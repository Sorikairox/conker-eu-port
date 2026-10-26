// object_state_dispatch_a (P211 selftest case; the two range checks swapped, equivalent for the u8 state):
// calls the D_80089AAC state handler with the object (a0 passed through to the jalr untouched).
s32 object_state_dispatch_a(struct102 *arg0) {
    s32 idx = arg0->unk3D;

    if (idx >= 10) {
        idx = 0; /* hi */
    }
    if (idx < 0) {
        idx = 0;
    }
    return ((s32 (*)(struct102 *)) D_80089AAC[idx])(arg0);
}
