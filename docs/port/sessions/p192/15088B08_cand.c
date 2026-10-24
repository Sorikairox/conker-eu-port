// cpu_player_slot_claim: takes the first free computer-player slot (bit i of D_800D27B4, i < D_800D27B9), resets
// its record D_80087640[D_800D27B8 + i] (func_15088CA0), marks it used (+0x30 = 1) for the object record objp
// (+0x31 = its D_800CC2D0 index) and returns the record index; -1 when none is free or there are no records.
// arg1 is unused (the caller passes the object twice).
s32 func_15088B08(s32 objp, s32 arg1) {
    s32 bit = 1;
    s32 n = D_800D27B9;
    s32 i;

    if (D_80087640 == NULL) {
        return -1;
    }
    for (i = 0; i < n; i++, bit <<= 1) {
        if (!(D_800D27B4 & bit)) {
            D_800D27B4 |= bit;
            i += D_800D27B8;
            func_15088CA0((u8 *)&D_80087640[i]);
            *((u8 *)&D_80087640[i] + 0x30) = 1;
            D_80087640[i].unk31 = ((u8 *)objp - (u8 *)D_800CC2D0) / 0x32C;
            return i;
        }
    }
    return -1;
}
