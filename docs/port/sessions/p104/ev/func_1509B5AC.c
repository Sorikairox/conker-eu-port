void func_1509B8FC(s16 arg0);
struct249 *func_1509B704(s16 arg0);
void func_1509B810(struct249 *arg0);
s32 func_150ADFD0(struct249 *, s32);
// Start event `id` (arg1 = 0: level start, only if its done bit is clear). A new event is loaded, linked and run
// once (func_150ADFD0(e, 0)) unless the save bit (flags & 0x3FF) is set; 0x4000 marks it started. An event already
// running with flags 0x1000 and not 0x800 gets its variables cleared.
int func_1509B5AC(s32 id, s32 arg1) { // commit as struct249 * with a prototype above func_1509B4A0
    u16 *e = (u16 *) func_1509B704(id);
    u16 flags;
    s32 bit;

    if (arg1 == 0 && (((u8 *) D_800D2E4C)[id >> 3] & (1 << (id & 7)))) {
        return 0;
    }
    if (e == NULL) {
        e = ((u16 *(*)(s16)) func_1509B8FC)(id); // commit: func_1509B8FC returns func_1509B950(...)
        func_1509B810((struct249 *) e);
        flags = e[0];
        bit = flags & 0x3FF;
        if (!(((u8 *) D_800D2E4C)[bit >> 3] & (1 << (bit & 7)))) {
            D_8003C8E0 = 0x6000000;
            func_150ADFD0((struct249 *) e, 0);
            D_8003C8E0 = 0;
            flags = e[0];
        }
        if (arg1 == 0 || (flags & 0x400)) {
            e[0] = flags | 0x4000;
        }
        return (s32) e;
    }
    if (arg1 != 0) {
        flags = e[0];
        if ((flags & 0x1000) && !(flags & 0x800)) {
            bzero((u8 *) e + e[5], e[3]);
        }
    }
    return (s32) e;
}
