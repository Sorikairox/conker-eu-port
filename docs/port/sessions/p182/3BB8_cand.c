// text_queue_put: appends a record (u32 length padded to 4, then the bytes) to the ring buffer q (D_800427A0:
// +0 buffer, +4 size, +8 read, +C write); returns 1 when it does not fit, else 0 (also for no data). The padded
// length is copied from src too (up to 3 bytes past len, as on N64).
s32 func_15043BB8(struct105 *q, u8 *src, s32 len) {
    s32 total;
    s32 pos;

    if (len == 0) {
        return 0;
    }
    if (src != NULL) {
        total = (len + 4 + 3) & ~3;
        len = total;
        if (q->unkC < q->unk8) {
            if (!(q->unkC + total < q->unk8)) {
                return 1;
            }
        } else if (!(q->unkC + len - q->unk4 < q->unk8)) {
            return 1;
        }
        len -= 4;
        pos = func_15043A20((u8 *) q->unk0, q->unk4, q->unkC, (u8 *) &len, 4);
        q->unkC = func_15043A20((u8 *) q->unk0, q->unk4, pos, src, len);
    }
    return 0;
}
