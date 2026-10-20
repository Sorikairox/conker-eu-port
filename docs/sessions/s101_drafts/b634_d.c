void func_1506E8D8(void);

void func_1506B634(u8 arg0) {
    u8 i;
    struct126 *p;

    i = (u32)func_150ADA20() % arg0;
    p = D_800D154C->unk31C;
    if (p->unk16 != 0) {
        if ((D_800BE9F0 == 0x29) && (i == 7)) {
            i = 0;
        }
        p->unkE = D_80099E7C[i];
    } else {
        p->unkE = D_80099E74[i];
    }
    if (D_800D154C->unk31C->unkE == 0xA7) {
        D_800D1580 = 0xFF020144;
        D_800D154C->unk31C->unkC = (func_150ADA20() % 3U) + 2;
        func_1506E8D8();
        D_800D154C->xz_velocity *= 0.2f;
    }
}
