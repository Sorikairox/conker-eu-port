void func_10004074(void *);
// object_node_remove: unlinks node arg0 (an object's +0x154) from the list D_800DDD64 (next at +0x24, appended
// by func_1517E080) and frees it (func_10004074); a node that is not in the list is left alone (not freed).
// arg1 (the owner) is not read.
void func_1517E6A4(f32 *arg0, structEU_16DC80 *arg1) {
    u8 *node = (u8 *) arg0;
    u8 *prev;

    if (node == (u8 *) D_800DDD64) {
        D_800DDD64 = *(s32 *) (node + 0x24);
    } else {
        prev = (u8 *) D_800DDD64;
        while (prev != NULL && *(u8 **) (prev + 0x24) != node) {
            prev = *(u8 **) (prev + 0x24);
        }
        if (prev == NULL) {
            return;
        }
        *(s32 *) (prev + 0x24) = *(s32 *) (node + 0x24);
    }
    func_10004074(node);
}
