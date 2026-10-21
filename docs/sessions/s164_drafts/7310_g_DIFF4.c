extern f32 D_800DD600[2];
extern f32 D_800DD608[4];
extern f32 D_800DD618[4];
void func_15167310(void) {
    s32 i;
    f32 a;
    s32 j;
    struct_eu_node *node;
    s32 k;

    for (k = 0; k < D_80082FA0 + 1; k++) {
        a = *(f32 *)((u8 *)D_800DBFF0 + k * 0x9A0 + 0x3A0);
        D_800DD608[k] = sinf(a);
        D_800DD618[k] = cosf(a);
    }
    a = D_800DBFF0->unk3A0;
    D_800DD600[0] = sinf(a);
    D_800DD600[1] = cosf(a);
    for (j = 0; j < 0x68; j++) {
        for (i = 0; i < 2; i++) {
            if (D_800DD280[i][j] != NULL && D_8008B848[j].fn0C != NULL) {
                node = D_800DD280[i][j];
                D_800DD5C0++;
                while (node != NULL) {
                    D_800DD5C8[D_800DD5C0] = node->next;
                    D_8008B848[j].fn0C(node);
                    node = D_800DD5C8[D_800DD5C0];
                }
                D_800DD5C0--;
            }
        }
    }
}
