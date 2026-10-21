void func_15141E38(struct127 *arg0, s32 arg1) {
    s32 pad;
    struct_eu_link *sp58;
    s32 pad2[3];
    struct_eu_link *temp;
    struct {
        s32 unk0;
        struct127 *unk4;
        u8 unk8;
    } sp40;
    struct_eu_link *found;
    struct260 *temp_v0;

    found = NULL;
    sp58 = arg0->unk2F4;
    if (func_1514F250(sp58, 0x1A, &sp58)) {
        do {
            if (arg1 == sp58->unk10->unk28) {
                found = sp58;
                sp58->unk10->unkE = D_8008A0B4[arg1].unk4;
            }
            temp = sp58->unk14;
            sp58 = temp;
        } while (func_1514F250(temp, 0x1A, &sp58));
    }
    if (found == NULL) {
        sp40.unk0 = arg1;
        sp40.unk4 = arg0;
        sp40.unk8 = arg0->unique_id;
        temp_v0 = func_15149130(D_8008A0B4[arg1].unk4, -1, -1, -1, 1, 0x32, 0xC, 0xFF, 1);
        if (temp_v0 != NULL) {
            memcpy((u8 *)temp_v0 + 0x28, &sp40, 0xC);
            func_1514F18C(temp_v0, arg0, 0x1A);
        }
    }
}
