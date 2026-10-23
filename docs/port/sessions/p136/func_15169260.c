/*
 * node_lists_update_types: for each of the n type ids in types[] (arg0), walks that type's node lists in both rows of
 * D_800DD280 and calls func_1516968C(node, arg2, arg3) on every node, then the type's D_8008B848 handler (+0x1C)
 * when it has one. The next node is kept in D_800DD5C8[++D_800DD5C0] (as func_15169070) so a call may unlink or
 * free the current node or the saved next one.
 */
void func_15169260(void *arg0, s32 n, s32 arg2, u8 arg3) {
    s32 *types = arg0;
    struct_eu_node *node;
    s32 k;
    s32 i;

    for (k = 0; k < n; k++, types++) {
        for (i = 0; i < 2; i++) {
            if (D_8008B848[*types].fn != NULL) {
                node = D_800DD280[i][*types];
                D_800DD5C0++;
                while (node != NULL) {
                    D_800DD5C8[D_800DD5C0] = node->next;
                    func_1516968C((struct102 *) node, (u8 *) arg2, arg3);
                    D_8008B848[*types].fn(node, arg2, arg3);
                    node = D_800DD5C8[D_800DD5C0];
                }
                D_800DD5C0--;
            } else {
                node = D_800DD280[i][*types];
                D_800DD5C0++;
                while (node != NULL) {
                    D_800DD5C8[D_800DD5C0] = node->next;
                    func_1516968C((struct102 *) node, (u8 *) arg2, arg3);
                    node = D_800DD5C8[D_800DD5C0];
                }
                D_800DD5C0--;
            }
        }
    }
}
