s32 func_15145128(struct17 *, struct17 *, f32 *, f32 *);
void func_1514C390(u8 *arg0) {
    struct17 tgt;
    struct17 m;
    s32 pad1; // fakematch: unused slot between m and d
    struct17 d;
    f32 sp34;
    f32 sp30;
    s32 pad2; // fakematch: unused slot below sp30

    tgt.unk0 = *(f32 *)(arg0 + 0x34);
    tgt.unk4 = *(f32 *)(arg0 + 0x38) + 100.0f;
    tgt.unk8 = *(f32 *)(arg0 + 0x3C);
    m.unk0 = *(f32 *)(arg0 + 0x15C) * (tgt.unk0 - *(f32 *)(arg0 + 0x40)) + *(f32 *)(arg0 + 0x40);
    m.unk4 = *(f32 *)(arg0 + 0x15C) * (tgt.unk4 - *(f32 *)(arg0 + 0x44)) + *(f32 *)(arg0 + 0x44);
    m.unk8 = *(f32 *)(arg0 + 0x15C) * (tgt.unk8 - *(f32 *)(arg0 + 0x48)) + *(f32 *)(arg0 + 0x48);
    d.unk0 = m.unk0 - *(f32 *)(arg0 + 0x34);
    d.unk4 = m.unk4 - *(f32 *)(arg0 + 0x38);
    d.unk8 = m.unk8 - *(f32 *)(arg0 + 0x3C);
    if (func_15145128(&d, &d, &sp34, &sp30) != 0) {
        *(f32 *)(arg0 + 0x40) = *(f32 *)(arg0 + 0x34) + d.unk0 * 100.0f;
        *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x38) + d.unk4 * 100.0f;
        *(f32 *)(arg0 + 0x48) = *(f32 *)(arg0 + 0x3C) + d.unk8 * 100.0f;
    } else {
        *(struct17 *)(arg0 + 0x40) = *(struct17 *)(arg0 + 0x34);
    }
}
