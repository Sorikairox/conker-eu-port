#ifdef NON_MATCHING
// P239 TEST VARIANT (void: the shipped body returns constant 0, the asm leaves node_destroy's v0).
// effect_node_children_free: effect-child handler (g_attach_child_update_fns [5] / g_attach_child_end_fns [3]): frees the node's children
// (node_destroy on the first child +0x24 while the count +0x20 is above 0; each free unlinks it). The second
// argument (the position the dispatchers pass) is unused; s32 return and the second parameter are the table's common
// signature s32 (node, pos) (wasm call_indirect). Returns 0 (the dispatchers that reach it ignore v0).
void attach_ctrl_destroy_children(struct224 *arg0, void *pos) {
    while (arg0->unk20 > 0) {
        node_destroy(arg0->unk24);
    }
}
#else
void attach_ctrl_destroy_children(struct224 *arg0) {
    while (arg0->unk20 > 0) {
        node_destroy(arg0->unk24);
    };
}
#endif
