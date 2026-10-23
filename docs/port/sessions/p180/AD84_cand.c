// ambient_slot_setup: sets up ambient sound slot `slot` for sound `id` (0xFF = empty) from its 10-byte sound info
// (D_80096090): phase range D_800DE000 (+1; minus 1 and also D_800DE010 when info flag 0x10), D_800DE020 (2 when
// flag 0x80), the two slot parameters D_800BE858 (+4 / +6), the id, the placement row (flags & 0x7F, bit 0x80 sets
// the slot's D_800DDC00 bit), D_800DDC04 / D_800DDC08 bits from info flags 1 / 8; always clears the slot's
// emitter count D_800BE898 and sets both D_800DE050 bytes to D_80096074[slot].
void func_1500AD84(s32 slot, s32 id, s32 flags) {
    u8 *info;
    u8 infoFlags;
    u8 b;

    if (id != 0xFF) {
        info = &D_80096090[id * 10];
        infoFlags = info[0];
        D_800DE000[slot] = info[1];
        if (infoFlags & 0x10) {
            D_800DE000[slot] = info[1] - 1;
            D_800DE010[slot] = info[1] - 1;
        } else {
            D_800DE010[slot] = 0;
        }
        if (infoFlags & 0x80) {
            D_800DE020[slot] = 2;
        } else {
            D_800DE020[slot] = 1;
        }
        D_800BE858[slot * 2 + 0] = *(s16 *) (info + 4);
        D_800BE858[slot * 2 + 1] = *(s16 *) (info + 6);
        D_800DDFF0[slot] = id;
        D_800DE0B0[slot] = flags & 0xFF7F;
        if (flags & 0x80) {
            D_800DDC00 |= 1 << slot;
        }
        if (infoFlags & 1) {
            D_800DDC04 |= 1 << slot;
        }
        if (infoFlags & 8) {
            D_800DDC08 |= 1 << slot;
        }
    } else {
        D_800DE000[slot] = 0;
    }
    b = D_80096074[slot];
    D_800BE898[slot] = 0;
    D_800DE050[slot * 2 + 0] = b;
    D_800DE050[slot * 2 + 1] = b;
}
