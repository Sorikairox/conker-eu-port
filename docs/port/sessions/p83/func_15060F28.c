/* Removal of an object (struct127, ends its fade mode 5 / 6 in func_150617BC). mode 0 = plain, 1 = killed
 * (func_1504AF10(obj, 1, 0) and func_1503E550(slot)), 2 = removed without a trace (marker byte cleared).
 * Releases its model / sound / effect, gives back the map marker byte D_800D252C[+0x13F] (kept as 0x80 or
 * cleared, depending on the marker record +0x144), frees the buffers +0x260.. and the per-player handles +0x304. */
void func_15060F28(struct127 *obj, s32 mode) {
    u8 *o = (u8 *)obj;
    u8 *rec;
    u8 *p;
    u8 slot;
    s32 i;

    func_1514D880(o);
    func_151695F0(o, 0);
    if (o[5] != 2 && o[5] != 3) {
        func_150849C0(obj);
        func_150626EC(obj, mode);
    }
    if (mode == 1) {
        func_1504AF10(obj, 1, 0);
        func_1503E550(obj - D_800CC2D0);
    }
    slot = o[0x13F];
    if (slot != 0xFF) {
        if (mode == 2) {
            D_800D252C[slot] = 0;
        } else {
            rec = *(u8 **)(o + 0x144);
            if (rec == NULL) {
                D_800D252C[slot] &= 0x80;
            } else if (*(u16 *)rec & 0x20) {
                rec[2] = 1;
                D_800D252C[o[0x13F]] = 0;
            } else if (*(u16 *)rec & 1) {
                D_800D252C[slot] = 0;
            } else {
                rec[2] = 1;
                p = D_800D252C + o[0x13F];
                *p &= 0x80;
            }
        }
    }
    if (*(s32 *)(o + 0x260) != 0) {
        func_10004074(*(s32 *)(o + 0x260));
    }
    if (*(s32 *)(o + 0x264) != 0) {
        func_10004074(*(s32 *)(o + 0x264));
    }
    if (*(s32 *)(o + 0x268) != 0) {
        func_10004074(*(s32 *)(o + 0x268));
    }
    if (*(s32 *)(o + 0x26C) != 0) {
        func_10004074(*(s32 *)(o + 0x26C));
    }
    if (*(s32 *)(o + 0x1D8) != 0) {
        func_10004074(*(s32 *)(o + 0x1D8));
    }
    if (*(s32 *)(o + 0x2D4) != 0) {
        func_1516972C(*(struct102 **)(o + 0x2D4));
    }
    /* per-player handles: only the first one is tested */
    if (*(s32 *)(o + 0x304) != 0) {
        for (i = 0; i <= D_80082FA0; i = (i + 1) & 0xFF) {
            func_100043B4(*(s32 **)(o + 0x304 + i * 4), 4);
        }
    }
    if (*(s32 *)(o + 0x314) != 0) {
        func_100043B4(*(s32 **)(o + 0x314), 4);
    }
    if (*(s32 *)(o + 0x2D0) != 0) {
        func_10004074(*(s32 *)(o + 0x2D0));
    }
    if (*(s32 *)(o + 0x324) != 0) {
        func_10004074(*(s32 *)(o + 0x324));
    }
    if (*(u8 **)(o + 0x31C) != NULL && *(s32 *)(*(u8 **)(o + 0x31C) + 0x11C) != 0) {
        func_10004074(*(s32 *)(*(u8 **)(o + 0x31C) + 0x11C));
    }
    func_10010AA8(obj);
    func_150306D4(o);
    func_15060D54(obj);
    func_15189040((s32)obj);
    if (*(s32 *)(o + 0x31C) != 0) {
        func_10004074(*(s32 *)(o + 0x31C));
    }
    func_1505F188(obj);
}
