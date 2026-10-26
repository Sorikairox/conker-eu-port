void heap_set_block_tag(s32 *arg0, u32 arg1);
void heap_free(s32);
void attachment_undo_kind_effects(u8 *);
void animmodel_free(s32);
void shared_dl_release(s32);

#define ATT_W(rec, off) (*(s32 *) ((rec) + (off)))

/*
 * P70: frees an attachment record of the list g_attachment_list (see attachment_update_all). now != 0 frees its buffers at
 * once (heap_free), else they are released deferred (heap_set_block_tag(buf, 4)) after attachment_undo_kind_effects.
 * Loaded records (+9) drop the two vertex copies +0x28 / +0x2C when they were made (+8), the +0x48 handle
 * (animmodel_free) and their asset (shared_dl_release(+1)). Then +0x34, +0x44 (always at once), +0x4C, +0x50, the
 * unlink from the doubly linked list (+0x54 next, +0x58 prev; the head g_attachment_list) and the record itself.
 */
void attachment_free(struct127 *arg0, s32 now) {
    u8 *rec = (u8 *) arg0;
    u8 *next;
    u8 *prev;

    if (!now) {
        attachment_undo_kind_effects(rec);
    }
    if (rec[9] != 0) {
        if (rec[8] != 0) {
            if (now) {
                heap_free(ATT_W(rec, 0x28));
                heap_free(ATT_W(rec, 0x2C));
            } else {
                heap_set_block_tag((s32 *) ATT_W(rec, 0x28), 4);
                heap_set_block_tag((s32 *) ATT_W(rec, 0x2C), 4);
            }
        }
        if (ATT_W(rec, 0x48) != 0) {
            animmodel_free(ATT_W(rec, 0x48));
        }
        shared_dl_release(rec[1]);
    }
    if (ATT_W(rec, 0x34) != 0) {
        if (now) {
            heap_free(ATT_W(rec, 0x34));
        } else {
            heap_set_block_tag((s32 *) ATT_W(rec, 0x34), 4);
        }
    }
    if (ATT_W(rec, 0x44) != 0) {
        heap_free(ATT_W(rec, 0x44));
    }
    if (ATT_W(rec, 0x4C) != 0) {
        if (now) {
            heap_free(ATT_W(rec, 0x4C));
        } else {
            heap_set_block_tag((s32 *) ATT_W(rec, 0x4C), 4);
        }
    }
    if (ATT_W(rec, 0x50) != 0) {
        if (now) {
            heap_free(ATT_W(rec, 0x50));
        } else {
            heap_set_block_tag((s32 *) ATT_W(rec, 0x50), 4);
        }
    }
    if ((u8 *) g_attachment_list == rec) {
        g_attachment_list = ATT_W(rec, 0x54);
    }
    prev = (u8 *) ATT_W(rec, 0x58);
    if (prev != NULL) {
        ATT_W(prev, 0x54) = ATT_W(rec, 0x54);
    }
    next = (u8 *) ATT_W(rec, 0x54);
    if (next != NULL) {
        ATT_W(next, 0x58) = ATT_W(rec, 0x58);
    }
    heap_free((s32) rec);
}
