extern s32 D_800A9650[];

struct_eu_node *func_151AEB40(u8 arg0) {
    u8 i;
    u8 j;
    struct_eu_node *n;
    struct_eu_node *next;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (n = D_800DD280[j][D_800A9650[i]]; n != NULL; n = next) {
                next = n->next;
                if (((u8 *)n)[0x10] == arg0) {
                    return n;
                }
            }
        }
    }
    return NULL;
}
