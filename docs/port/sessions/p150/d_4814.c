// object_model_refs_release: drops entry slot's two model block references (struct127 words +0x28C + slot * 8).
// A reference to the slot's shared block D_800D19A0[model] (model = ((u8 *)+0x2C4)[slot]) only lowers its user
// count D_800D1F80[model] (bytes); any other block is freed with func_100043B4(block, 3).
void func_15084814(struct127 *obj, s32 slot) {
    s32 **ref;
    s32 model;
    s32 i;

    ref = (s32 **)((u8 *)obj + 0x28C + slot * 8);
    if (ref[0] == NULL && ref[1] == NULL) {
        return;
    }
    model = (*(u8 **)((u8 *)obj + 0x2C4))[slot];
    for (i = 0; i < 2; i++) {
        if (ref[i] == NULL) {
            continue;
        }
        if (ref[i] == ((s32 **)&D_800D19A0)[model]) {
            ((u8 *)D_800D1F80)[model]--;
        } else {
            func_100043B4(ref[i], 3);
        }
        ref[i] = NULL;
    }
}
