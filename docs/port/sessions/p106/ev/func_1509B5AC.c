struct249 *func_1509B704(s16 arg0);
struct249 *func_1509B8FC(s16 arg0);
void func_1509B810(struct249 *arg0);
void func_150ADFD0(struct249 *, s32);

/* Start event `id` (arg1 = 0: level start, skipped when the event's own save bit is set). An event not yet in the
 * list is loaded (func_1509B8FC), linked (func_1509B810) and run once from entry 0 unless the save bit of its flags
 * (flags & 0x3FF) is set; flag 0x4000 marks it started (always at level start, else only with flag 0x400). An event
 * already in the list with flag 0x1000 and not 0x800 gets its variables cleared when arg1 != 0. */
struct249 *func_1509B5AC(s32 id, s32 arg1) {
    struct249 *e = func_1509B704(id);
    u8 *save = (u8 *) D_800D2E4C;
    u16 flags;
    s32 bit;

    if (arg1 == 0 && (save[id >> 3] & (1 << (id & 7)))) {
        return NULL;
    }
    if (e == NULL) {
        e = func_1509B8FC(id);
        func_1509B810(e);
        flags = e->unk0;
        bit = flags & 0x3FF;
        if (!(save[bit >> 3] & (1 << (bit & 7)))) {
            D_8003C8E0 = 0x6000000;
            func_150ADFD0(e, 0);
            D_8003C8E0 = 0;
            flags = e->unk0;
        }
        if (arg1 == 0 || (flags & 0x400)) {
            e->unk0 = flags | 0x4000;
        }
        return e;
    }
    if (arg1 != 0) {
        flags = e->unk0;
        if ((flags & 0x1000) && !(flags & 0x800)) {
            bzero((u8 *) e + ((struct_eu_C8950_blk *) e)->unkA, ((struct_eu_C8950_blk *) e)->unk6);
        }
    }
    return e;
}
