void func_151347CC(struct161520 *arg0, struct161520_msg *arg1, u8 arg2) {
  s32 *key = &arg0->unk1C;
    if ((arg2 == 0) || (arg2 == 3)) {
        if ((arg1->unk0 == arg0->unk1C) || (arg1->unk4.b == arg0->unk18)) { func_1516972C((struct102 *)arg0); }
    } else if (arg2 == 0x11) {
        if ((arg0->unk3D == 5) && ((arg1->unk0 == arg0->unk1C) || (arg1->unk4.b == arg0->unk18))) { func_1516972C((struct102 *)arg0); }
    } else if (arg2 == 0x16) {
        if ((s32)arg1 == arg0->unk1C) { func_1516972C((struct102 *)arg0); }
    } else if (arg2 == 0x2D) {
        if (arg1->unk0 == *key) { arg0->unk1C = arg1->unk4.w; arg0->unk18 = arg1->unk9; }
        else if (arg1->unk4.w == *key) { arg0->unk1C = arg1->unk0; arg0->unk18 = arg1->unk8; }
    }
}
