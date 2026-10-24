#ifdef NON_MATCHING
// effect_child_update: one effect child per frame. Freed (func_1516972C) when its parent object is gone / hidden /
// re-used (id +0x3B != child +0x14) or has no bone matrices. Otherwise its position is its offset +0x18 through the
// parent's bone matrix (+0x1D4, bone +0x24); a timed child (+0x28 bit 0) counts +0x26 down by D_800BE9E4 and at
// expiry runs its end handler D_8008FFE8[+0x2A] (node, &pos) and is freed; the update handler D_8008FFE0[+0x29]
// (node, &pos) returning 0 frees it; else the position is stored at +0x34.
// NON_MATCHING copy: the handler table at 0x8008FFE0 (D_8008FFE0 [0..6], D_8008FFE8 = [2..6]) is called through one
// signature, s32 (child *, void *) (wasm call_indirect); variables.h declares D_8008FFE8 void-returning, so the
// end-handler call casts. The one-argument entries take and ignore the position (func_1518FD34, func_1518FE0C,
// func_151D33B8, func_1518FDC8).
void func_151D2C40(struct_eu_1FFF60_child *arg0) {
    struct_eu_1FFF60_parent *parent = arg0->unk10;
    struct17 pos;

    if (parent->unk0 == 0 || parent->unk4 == 0xFF || parent->unk3B != arg0->unk14 || parent->unk1D4 == NULL ||
        (parent->unk74 & 0xF) == 0xF) {
        func_1516972C(arg0);
        return;
    }
    func_15143134(&arg0->unk18, &pos, parent->unk1D4 + (arg0->unk24 << 6));
    if (arg0->unk28 & 1) {
        arg0->unk26 -= D_800BE9E4;
        if (arg0->unk26 < 0) {
            if (arg0->unk2A != -1) {
                ((s32 (*)(struct_eu_1FFF60_child *, void *))D_8008FFE8[arg0->unk2A])(arg0, &pos);
            }
            arg0->unk2C = 0;
            func_1516972C(arg0);
            return;
        }
    }
    if (arg0->unk29 != -1) {
        if (D_8008FFE0[arg0->unk29](arg0, &pos) == 0) {
            func_1516972C(arg0);
            return;
        }
    }
    arg0->unk34 = pos;
}
#else
void func_151D2C40(struct_eu_1FFF60_child *arg0) {
    struct_eu_1FFF60_parent *parent = arg0->unk10;
    struct17 pos;

    if (parent->unk0 == 0 || parent->unk4 == 0xFF || parent->unk3B != arg0->unk14 || parent->unk1D4 == NULL ||
        (parent->unk74 & 0xF) == 0xF) {
        func_1516972C(arg0);
        return;
    }
    func_15143134(&arg0->unk18, &pos, parent->unk1D4 + (arg0->unk24 << 6));
    if (arg0->unk28 & 1) {
        arg0->unk26 -= D_800BE9E4;
        if (arg0->unk26 < 0) {
            if (arg0->unk2A != -1) {
                D_8008FFE8[arg0->unk2A](arg0, &pos);
            }
            arg0->unk2C = 0;
            func_1516972C(arg0);
            return;
        }
    }
    if (arg0->unk29 != -1) {
        if (D_8008FFE0[arg0->unk29](arg0, &pos) == 0) {
            func_1516972C(arg0);
            return;
        }
    }
    arg0->unk34 = pos;
}
#endif
