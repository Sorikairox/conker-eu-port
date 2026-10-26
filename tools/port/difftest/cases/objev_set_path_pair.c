#ifdef NON_MATCHING
/*
 * P80: script command: +0x282 = 0xFFFF, +0x276 = 5, and the byte pair +0x284 + 2 * i (i = bits 16..23 of the
 * command word g_cur_obj_cmd) = bits 8..15, bits 0..7.
 */
void objev_set_path_pair(void) {
    s32 w = g_cur_obj_cmd;
    s32 i = ((w >> 16) & 0xFF) * 2;

    *(u16 *) ((u8 *) g_cur_obj + 0x282) = 0xFFFF;
    *((u8 *) g_cur_obj + 0x276) = 5;
    *((u8 *) g_cur_obj + 0x284 + i) = w >> 8;
    *((u8 *) g_cur_obj + 0x285 + i) = w;
}
#endif
