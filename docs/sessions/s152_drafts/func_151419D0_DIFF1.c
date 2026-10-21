void func_151419D0(struct_eu_151419D0 *arg0, struct_eu_151419D0_msg *arg1, u8 arg2) {
    struct_eu_151419D0_sub *sub = &arg0->unk28;
    s32 id;
    s32 cur;

    if (arg2 == 0) {
        id = arg1->unk0;
        if ((id == sub->unk4) || (sub->unk8 == *(u8 *)&arg1->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        cur = sub->unk4;
        id = arg1->unk0;
        if (id == cur) {
            sub->unk4 = arg1->unk4;
            sub->unk8 = arg1->unk9;
        } else if (arg1->unk4 == cur) {
            sub->unk4 = id;
            sub->unk8 = arg1->unk8;
        }
    }
}
