#ifdef NON_MATCHING
/*
 * P80: script command: +0x282 = 0xFFFF, +0x276 = 5, and the byte pair +0x284 + 2 * i (i = bits 16..23 of the
 * command word D_800D1580) = bits 8..15, bits 0..7.
 */
void objev_set_path_pair(void) {
    s32 w = D_800D1580;
    s32 i = ((w >> 16) & 0xFF) * 2;

    *(u16 *) ((u8 *) D_800D154C + 0x282) = 0xFFFF;
    *((u8 *) D_800D154C + 0x276) = 5;
    *((u8 *) D_800D154C + 0x284 + i) = w >> 8;
    *((u8 *) D_800D154C + 0x285 + i) = w;
}
#endif
