/*
 * P65: the last step of func_1502B110 (animation header lookup): DMA the n 8-byte records {offset, size} starting
 * at entry index of the ROM table at base into buf (16-byte aligned block that covers them, starting at the
 * 16-aligned buf + 8), turn each offset into an absolute ROM address (+= base) and return the first record.
 */
s32 func_1502AF04(s32 base, s32 buf, s32 index, u32 n) {
    u32 src = base + index * 8;
    u32 dst = (buf + 8) & ~0xF;
    s32 *rec;
    u32 i;

    func_10004514(src & ~0xF, (void *) dst, ((src & 0xE) + n * 8 + 0xF) & ~0xF, 1);
    rec = (s32 *) (dst + (src & 0xF));
    for (i = 0; i < n; i++) {
        rec[i * 2 + 1] += base;
    }
    return (s32) rec;
}
