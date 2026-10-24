extern u8 D_800D1CC4[];
extern u16 D_800D1CC2;
extern s8 D_80090134;
void func_15062800(struct127 *, struct127 *);

#define RAIL_WORDS(off) ((s32 *) ((u8 *) D_800D27D0 + (off)))

// rail_racer_take_over: script command 15 (func_1509E3D4). Racer i takes over racer j's place: only when i's
// D_800D1CC4 byte is >= 0x33 and i is not yet marked in D_800D1CC2. Marks i there, moves the D_800D18A0 bit from i to
// j, gives i j's func_150859AC(j, 3) value through func_15085710 (j gets 0), moves the rail flag word +0x18 bit i -> j,
// copies j's rail slots (+0x9C, +0x39C, +0x3DC, +0xEB0 with its back link +0xF70, +0x16C0) to i, swaps the two
// objects (func_15062800), on level 0x3F re-points the D_800D3268 record's racer entry of the object's carrier
// (unk13C >= 100) at the moved object, then resets object i (+0x125 = 0x5A, unk31C state byte 0x84, 0x1AA kept from
// before the swap, 0x1AF = 0x40), refreshes its camera (func_15128774) and counts D_80090134. Returns 0 (asm too).
s32 func_1508ECF8(s32 i, s32 j) {
    s32 mask;
    s32 jbit;
    s32 k;
    s32 saved1AA;
    struct127 *obj;
    struct127 *carrier;
    s32 slot;
    s8 *rec;
    u8 *entry;

    if (D_800D1CC4[i] < 0x33) {
        return 0;
    }
    mask = 1 << i;
    if (D_800D1CC2 & mask) {
        return 0;
    }
    jbit = 1 << j;
    D_800D18A0 &= ~mask;
    D_800D1CC2 |= mask;
    D_800D18A0 |= jbit;
    func_15085710(i, 2, func_150859AC(j, 3));
    func_15085710(j, 2, 0);

    if (RAIL_WORDS(0x18)[0] != 0) {
        RAIL_WORDS(0x18)[0] &= ~mask;
        RAIL_WORDS(0x18)[0] |= jbit;
    }
    if (RAIL_WORDS(0x9C) != NULL) {
        RAIL_WORDS(0x9C)[i] = RAIL_WORDS(0x9C)[j];
    }
    if (RAIL_WORDS(0x39C) != NULL) {
        RAIL_WORDS(0x39C)[i] = RAIL_WORDS(0x39C)[j];
    }
    if (RAIL_WORDS(0x3DC) != NULL) {
        RAIL_WORDS(0x3DC)[i] = RAIL_WORDS(0x3DC)[j];
    }
    if (RAIL_WORDS(0xEB0) != NULL) {
        RAIL_WORDS(0xEB0)[i] = RAIL_WORDS(0xEB0)[j];
        k = RAIL_WORDS(0xEB0)[i];
        if (k >= 0) {
            RAIL_WORDS(0xF70)[k] = i;
        }
    }
    RAIL_WORDS(0x16C0)[i] = RAIL_WORDS(0x16C0)[j];

    obj = &D_800CC2D0[i];
    saved1AA = obj->unk31C->unk1AA;
    func_15062800(&D_800CC2D0[j], obj);
    if (D_800BE9F0 == 0x3F && obj->unk13C >= 100) {
        carrier = &D_800CC2D0[(u8) (obj->unk13C - 100)];
        rec = func_1509B570(D_800D3268);
        if (rec != NULL) {
            slot = obj - D_800CC2D0;
            entry = (u8 *) rec + (carrier->unique_id - 0x14) * 4;
            *(s32 *) (entry + 0x24B8) = slot | 0x2000;
            *(s32 *) (entry + 0x24DC) = slot;
        }
    }
    obj->unk31C->unk84 = 0;
    obj->immune = 0x5A;
    obj->unk31C->unk1AA = saved1AA;
    *((u8 *) obj->unk31C + 0x1AF) = 0x40;
    func_15128774(obj->camera, obj);
    D_80090134++;
    return 0;
}

#undef RAIL_WORDS
