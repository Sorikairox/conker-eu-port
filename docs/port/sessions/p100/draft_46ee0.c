#ifdef NON_MATCHING
s32 func_151420F8(struct127 *);
s32 func_150A2FCC(u32, s32, s32 *);

/* Interaction hook (D_8008A084 table, called by func_15141A7C with the mode from func_15141CC0 and the object):
 * maps mode 0..8 to an entry of D_8008A0B4, -1 = none. Mode 1 in level 4 (D_800BE9F0) asks func_151420F8; mode 6
 * looks the object up with the five ids 0x401D..0x4021 (D_800A5AB0) through func_150A2FCC. */
s32 func_15146EE0(s32 mode, struct127 *obj) {
    s32 ids[5];

    switch (mode) {
        case 0:
            return 0;
        case 1:
            if (D_800BE9F0 == 4) {
                if (func_151420F8(obj) != 0) {
                    return 6;
                }
                return 3;
            }
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        case 5:
            return 5;
        case 6:
            /* D_800A5AB0; filled by hand: an initialised local array lands in .data, which the NM link drops */
            ids[0] = 0x401D;
            ids[1] = 0x401E;
            ids[2] = 0x401F;
            ids[3] = 0x4020;
            ids[4] = 0x4021;
            if (func_150A2FCC(obj - D_800CC2D0, 5, ids) == -1) {
                return -1;
            }
            return 6;
        case 7:
            return 15;
        case 8:
            return 16;
        default:
            return -1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_15146EE0.s")
#endif
