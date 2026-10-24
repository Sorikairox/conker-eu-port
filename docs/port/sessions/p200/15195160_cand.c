s32 func_1507CD64(struct127 *, s32);
void func_15063F14(struct127 *, s32);

// obj_hit_retire: per-kind reaction of object `obj` (kind obj[4]): most enemy / prop kinds (0..4, 0x11, 0x14, 0x3B and
// a set of kinds from 0x58 on) are switched off (func_15136C3C), released (func_15145A50), sent to state 6
// (func_1507CD64) and lose their attached model (func_15063F14) when its +0x19B is set; kind 0x16 is switched off and
// released, then like kind 0x7C hands back its rider: player obj[0x65] (1-based) gets +0x232 = 10, +0x218 = 0 and
// obj[0x65] is cleared. Other kinds: nothing.
void func_15195160(s32 arg0, u8 *obj, s8 *arg2) {
    u8 *p;
    u8 *model;

    switch (obj[4]) {
        case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x11: case 0x14: case 0x3B:
        case 0x58: case 0x5A: case 0x5B: case 0x5F: case 0x74: case 0x75: case 0x7A: case 0x80:
        case 0x87: case 0x88: case 0x90: case 0x96: case 0x98: case 0x9C: case 0x9D: case 0x9F:
        case 0xA0: case 0xB0: case 0xB1: case 0xB2: case 0xB4:
            func_15136C3C((s32) obj, 1, 1, 1, 1, 0, 0xFF, 1);
            func_15145A50((struct127 *) obj);
            func_1507CD64((struct127 *) obj, 6);
            model = *(u8 **) (obj + 0x31C);
            if (model != NULL && model[0x19B] != 0) {
                func_15063F14((struct127 *) obj, 0);
            }
            break;
        case 0x16:
            func_15136C3C((s32) obj, 1, 1, 1, 1, 0, 0xFF, 1);
            func_15145A50((struct127 *) obj);
            /* fallthrough */
        case 0x7C:
            if (obj[0x65] != 0) {
                p = (u8 *) &D_800CC2D0[obj[0x65] - 1];
                p[0x232] = 10;
                *(s32 *) (p + 0x218) = 0;
                obj[0x65] = 0;
            }
            break;
    }
}
