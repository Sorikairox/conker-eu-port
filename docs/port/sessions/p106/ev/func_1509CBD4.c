// Event prerequisites: D_800877D0[id] +0xC is a 0xFFFF-terminated list of event ids. The event may start when every
// prerequisite has its save bit set (D_800D2E4C bit field) and its own prerequisites hold. Empty list: 1.
s32 func_1509CBD4(s32 id) {
    u16 *p = *(u16 **) ((u8 *) D_800877D0 + id * 0x14 + 0xC);
    u16 e;
    s32 ok;

    e = *p;
    while (e != 0xFFFF) {
        ok = func_1509CBD4(e);
        e = *p;
        if (!(((u8 *) D_800D2E4C)[e >> 3] & (1 << (e & 7))) || ok == 0) {
            return 0;
        }
        p++;
        e = *p;
    }
    return 1;
}
