// sfx_start_positional: claims the next of the 32 positional sound slots (D_80041FE0[D_80042B00++]) for sound id
// arg0 at (arg1, arg2, arg3) with volume arg4, ranges arg5 / arg6, update callback arg7 (+ its data arg8, arg9) and
// flags argA (with a callback: flags | 0x12, else (flags & 0x108) | 2; flag 0x40: arg2 is a joint index resolved by
// func_15083E0C((u8) arg1), -1 = fail), pitch argB cents. func_10011624 starts it; returns the voice handle (+0x24)
// when the slot count did not change meanwhile (and marks the slot 0x1000), else 0. 0 when all slots are used.
u16 func_1000FA64(u16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, s16 arg6, s32 arg7, void *arg8,
                  s32 arg9, s32 argA, s32 argB) {
    SfxEnt *e;
    s32 idx;
    s32 count;

    idx = D_80042B00;
    if (idx < 32) {
        D_80042B00 = idx + 1;
    } else {
        return 0;
    }
    e = &((SfxEnt *) D_80041FE0)[idx];
    if (arg7 != 0) {
        e->unk10 = argA | 0x12;
    } else {
        e->unk10 = (argA & 0x108) | 2;
    }
    if (argA & 0x40) {
        arg2 = func_15083E0C(arg1);
        if (arg2 == -1) {
            return 0;
        }
    }
    e->unk24 = 0;
    e->unk23 = 0;
    e->unk22 = 0;
    e->unk0 = arg0;
    e->unk2 = arg1;
    e->unk4 = arg2;
    e->unk6 = arg3;
    e->unk8 = arg5;
    e->unkA = arg6;
    e->unkC = arg4;
    e->unk14 = (void *) arg7;
    e->unk18 = (s32) arg8;
    e->unk1C = arg9;
    e->unk2C = alCents2Ratio(argB);
    e->unk26 = 0;
    e->unk28 = 0;
    e->unk20 = argB;
    count = D_80042B00;
    func_10011624(D_80041FE0, &D_80042B00, idx, idx + 1);
    if (count != D_80042B00) {
        return 0;
    }
    e->unk10 |= 0x1000;
    return e->unk24;
}
