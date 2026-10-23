// event_list_unlock: for each id of the 0xFFFF-terminated u16 list: calls cb(id) (func_1509D0C4 recurses into the
// event's own list), sets its state byte D_800D2E70[id] to 3 and its save bit in D_800D2E4C. arg2 is unused; the
// asm returns no value.
void func_1509D274(s32 listp, void (*cb)(s32), s32 arg2) {
    u16 *list = (u16 *)listp;

    while (*list != 0xFFFF) {
        cb(*list);
        ((u8 *)&D_800D2E70)[*list] = 3;
        ((u8 *)D_800D2E4C)[*list >> 3] |= 1 << (*list & 7);
        list++;
    }
}
