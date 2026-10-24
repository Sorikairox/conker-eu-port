#ifdef NON_MATCHING
// effect_node_release: runs the node's release hook D_8008FFFC[+0x1D] (if any), then for every child (list +0x24,
// next +0x40) its end handler D_8008FFE8[+0x2A] (child, &child +0x34) and frees it (func_1516972C), then releases
// the node (func_1514EDF0 with +0x10).
// NON_MATCHING copy: the end handler is called through the table's common signature s32 (child *, void *) (see
// func_151D2C40).
void func_151D3130(struct_eu_1FFF60 *arg0) {
    struct_eu_1FFF60_child *child;

    if (D_8008FFFC[arg0->unk1D] != NULL) {
        D_8008FFFC[arg0->unk1D](arg0);
    }
    child = arg0->unk24;
    while (child != NULL) {
        struct_eu_1FFF60_child *next = child->unk40;
        if (child->unk2A != -1) {
            ((s32 (*)(struct_eu_1FFF60_child *, void *))D_8008FFE8[child->unk2A])(child, &child->unk34);
        }
        child->unk2C = 0;
        func_1516972C(child);
        child = next;
    }
    func_1514EDF0(arg0, arg0->unk10);
}
#else
void func_151D3130(struct_eu_1FFF60 *arg0) {
    struct_eu_1FFF60_child *child;

    if (D_8008FFFC[arg0->unk1D] != NULL) {
        D_8008FFFC[arg0->unk1D](arg0);
    }
    child = arg0->unk24;
    while (child != NULL) {
        struct_eu_1FFF60_child *next = child->unk40;
        if (child->unk2A != -1) {
            D_8008FFE8[child->unk2A](child, &child->unk34);
        }
        child->unk2C = 0;
        func_1516972C(child);
        child = next;
    }
    func_1514EDF0(arg0, arg0->unk10);
}
#endif
