#ifdef NON_MATCHING
// effect_node_children_free: effect-child handler (D_8008FFE0 [5] / D_8008FFE8 [3]): frees the node's children
// (func_1516972C on the first child +0x24 while the count +0x20 is above 0; each free unlinks it). The second
// argument (the position the dispatchers pass) is unused; s32 return and the second parameter are the table's common
// signature s32 (node, pos) (wasm call_indirect). Returns 0 (the dispatchers that reach it ignore v0).
s32 func_151D33B8(struct224 *arg0, void *pos) {
    while (arg0->unk20 > 0) {
        func_1516972C(arg0->unk24);
    }
    return 0;
}
#else
void func_151D33B8(struct224 *arg0) {
    while (arg0->unk20 > 0) {
        func_1516972C(arg0->unk24);
    };
}
#endif
