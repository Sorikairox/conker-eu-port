void func_100043B4(s32 *arg0, u32 arg1);
void func_10004074(s32);
void func_15031F04(u8 *);
void func_1503FAA8(s32);
void func_1518CF74(s32);

#define ATT_W(rec, off) (*(s32 *) ((rec) + (off)))

/*
 * P70: frees an attachment record of the list D_800C3EE0 (see func_15030758). now != 0 frees its buffers at
 * once (func_10004074), else they are released deferred (func_100043B4(buf, 4)) after func_15031F04.
 * Loaded records (+9) drop the two vertex copies +0x28 / +0x2C when they were made (+8), the +0x48 handle
 * (func_1503FAA8) and their asset (func_1518CF74(+1)). Then +0x34, +0x44 (always at once), +0x4C, +0x50, the
 * unlink from the doubly linked list (+0x54 next, +0x58 prev; the head D_800C3EE0) and the record itself.
 */
void func_15030448(struct127 *arg0, s32 now) {
    u8 *rec = (u8 *) arg0;
    u8 *next;
    u8 *prev;

    if (!now) {
        func_15031F04(rec);
    }
    if (rec[9] != 0) {
        if (rec[8] != 0) {
            if (now) {
                func_10004074(ATT_W(rec, 0x28));
                func_10004074(ATT_W(rec, 0x2C));
            } else {
                func_100043B4((s32 *) ATT_W(rec, 0x28), 4);
                func_100043B4((s32 *) ATT_W(rec, 0x2C), 4);
            }
        }
        if (ATT_W(rec, 0x48) != 0) {
            func_1503FAA8(ATT_W(rec, 0x48));
        }
        func_1518CF74(rec[1]);
    }
    if (ATT_W(rec, 0x34) != 0) {
        if (now) {
            func_10004074(ATT_W(rec, 0x34));
        } else {
            func_100043B4((s32 *) ATT_W(rec, 0x34), 4);
        }
    }
    if (ATT_W(rec, 0x44) != 0) {
        func_10004074(ATT_W(rec, 0x44));
    }
    if (ATT_W(rec, 0x4C) != 0) {
        if (now) {
            func_10004074(ATT_W(rec, 0x4C));
        } else {
            func_100043B4((s32 *) ATT_W(rec, 0x4C), 4);
        }
    }
    if (ATT_W(rec, 0x50) != 0) {
        if (now) {
            func_10004074(ATT_W(rec, 0x50));
        } else {
            func_100043B4((s32 *) ATT_W(rec, 0x50), 4);
        }
    }
    if ((u8 *) D_800C3EE0 == rec) {
        D_800C3EE0 = ATT_W(rec, 0x54);
    }
    prev = (u8 *) ATT_W(rec, 0x58);
    if (prev != NULL) {
        ATT_W(prev, 0x54) = ATT_W(rec, 0x54);
    }
    next = (u8 *) ATT_W(rec, 0x54);
    if (next != NULL) {
        ATT_W(next, 0x58) = ATT_W(rec, 0x58);
    }
    func_10004074((s32) rec);
}
