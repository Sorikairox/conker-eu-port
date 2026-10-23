#ifdef NON_MATCHING
/* Category of object `obj` for the interaction tables D_8008A084 / D_8008A0B4 (func_15141A7C), from its type id
 * (+0x04). Jump tables jtbl_800A55F8 (ids 121..165) and D_eu_800A56AC (ids 0..88); anything else is 11. */
s32 func_15141C0C(struct127 *obj) {
    switch (obj->id) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 150:
            return 0;
        case 16:
        case 145:
            return 1;
        case 43:
            return 2;
        case 69:
            return 3;
        case 75:
            return 4;
        case 84:
            return 5;
        case 54:
        case 83:
        case 165:
            return 6;
        case 88:
            return 7;
        case 123:
            return 8;
        case 33:
            return 9;
        case 121:
            return 10;
        default:
            return 11;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141C0C.s")
#endif
