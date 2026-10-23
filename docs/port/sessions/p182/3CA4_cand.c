// text_queue_get: takes the next record from the ring buffer q (see func_15043BB8) into dst (at most max - 1 bytes
// plus a 0 when it is longer; the rest is skipped); returns the record's length, 0 when the queue is empty.
s32 func_15043CA4(struct105 *q, u8 *dst, s32 max) {
    s32 len = 0;
    s32 pos = q->unk8;

    if (pos == q->unkC) {
        return 0;
    }
    pos = func_15043AC8((u8 *) q->unk0, q->unk4, pos, (u8 *) &len, 4);
    if (max < len) {
        max--;
        pos = func_15043AC8((u8 *) q->unk0, q->unk4, pos, dst, max);
        dst[max] = 0;
        pos = func_15043B70(q->unk0, q->unk4, pos, len - max);
    } else if (len != 0) {
        pos = func_15043AC8((u8 *) q->unk0, q->unk4, pos, dst, len);
    }
    q->unk8 = pos;
    return len;
}
