s32 func_1505D024(struct127 *, s32, s32, u8);

void func_15073A50(void) {
    s32 pad;
    s32 i;
    struct127 *p;
    s32 v;

    i = D_800D154C->unk124;
    p = &D_800CC2D0[i];
    if (p->unk65 != 0) {
        v = D_800D1580;
        D_800D154C->unk13C = 0;
        p->immune = 0;
        func_1505D024(p, D_800D1580 & 0xFF00FF, 0, D_800C3E78);
        p->unk1CC = 100000.0f;
        if (v & 0x40000000) {
            p->unk1CC = D_800D154C->y_position;
        }
        p->immune = 0x14;
        p->unk76 = D_800D154C->unk7A + v;
    }
}
