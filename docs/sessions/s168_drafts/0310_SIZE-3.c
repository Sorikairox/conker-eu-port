s32 func_15182238(s32);
s32 func_1517F470(s32);
extern void (*D_8008B478[])(struct_eu_node *, s32);

void func_15160310(s32 arg0) {
    u8 i;
    struct_eu_node *node;
    s32 run;
    u8 flags;

    for (i = 0; i < 2; i++) {
        node = D_800DD280[i][52];
        D_800DD5C0++;
        while (node != NULL) {
            D_800DD5C8[D_800DD5C0] = node->next;
            flags = ((u8 *)node)[0xE];
            if (flags & 4) {
                ((u8 *)node)[0xE] = flags & ~4;
                node = D_800DD5C8[D_800DD5C0];
                continue;
            }
            if (((s8 *)node)[0x10] != -1) {
                run = 1;
                if ((flags & 2) && D_800C35EA == 1) {
                    run = 0;
                }
                if ((flags & 8) && (func_15182238(0) == 0 || func_1517F470(0) != 0)) {
                    run = 0;
                }
                if (run) {
                    D_8008B478[((s8 *)node)[0x10]](node, arg0);
                }
                node = D_800DD5C8[D_800DD5C0];
                continue;
            }
            node = D_800DD5C8[D_800DD5C0];
        }
        D_800DD5C0--;
    }
}
