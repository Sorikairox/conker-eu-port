struct_eu_node *func_15105C24(s32 arg0) {
    u8 i;
    u8 j;
    struct_eu_node *p;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (p = D_800DD280[j][(&D_800A5770)[i]]; p != NULL; p = p->next) {
                if ((*(u8 *)((u8 *)p + 0x13) == 0x2E) && (arg0 == *(s32 *)((u8 *)p + 0x28))) {
                    return p;
                }
            next: ; // fakematch: label at the end of the inner loop body moves the j/i increments into the exit block
            }
        }
    }
    return NULL;
}
