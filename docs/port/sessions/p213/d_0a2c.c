// effect_node_release: P213: release handler of an effect node (entry of the D_8008FC60 handler table, void (u8 *),
/* dispatched by func_15199EF0): frees the attached record +0x84 (func_1516972C), then func_1000FD38(func_1518E808,
 * node, word +0x10) (func_1518E808 is the node's func_1000FA64 callback) and func_151D2B4C(word +0x78). */
void func_1000FD38(s32, s32, s32);
void func_15190A2C(u8 *node) {
    if (*(u8 **)(node + 0x84) != NULL) {
        func_1516972C(*(struct102 **)(node + 0x84));
    }
    func_1000FD38((s32)func_1518E808, (s32)node, *(s32 *)(node + 0x10));
    func_151D2B4C(*(s32 *)(node + 0x30 + 0x48));
}
