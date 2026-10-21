void func_1516968C(struct102 *arg0, u8 *arg1, u8 arg2);
void func_15143D18(s32 *, s32 *, s32, s32);
typedef struct { u8 pad0[0x1C]; void (*fn)(struct_eu_node *, s32, u8); u8 pad20[0x14]; } Tbl9070;
extern Tbl9070 D_8008B848[];
void func_15169070(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 j;
    s32 i;
    struct_eu_node *node;

    func_15143D18(&arg0, &arg1, 2, 0x68);
    for (j = arg0; j < arg1; j++) {
        for (i = 0; i < 2; i++) {
            if (D_8008B848[j].fn != NULL) {
                node = D_800DD280[i][j];
                D_800DD5C0++;
                while (node != NULL) {
                    D_800DD5C8[D_800DD5C0] = node->next;
                    func_1516968C((struct102 *)node, (u8 *)arg2, arg3);
                    D_8008B848[j].fn(node, arg2, arg3);
                    node = D_800DD5C8[D_800DD5C0];
                }
                D_800DD5C0--;
            } else {
                node = D_800DD280[i][j];
                D_800DD5C0++;
                while (node != NULL) {
                    D_800DD5C8[D_800DD5C0] = node->next;
                    func_1516968C((struct102 *)node, (u8 *)arg2, arg3);
                    node = D_800DD5C8[D_800DD5C0];
                }
                D_800DD5C0--;
            }
        }
    }
}
