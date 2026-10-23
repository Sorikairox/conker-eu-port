// Relocate a loaded event block: the variable area (unk6 bytes) goes after the script at an 8-aligned offset
// (unkA), the whole block is copied to a new allocation, the variables cleared, the old block freed.
struct_eu_C8950_blk *func_1509B950(struct_eu_C8950_blk *blk) {
    struct_eu_C8950_blk *new;
    u16 pos;

    pos = blk->unk4 + (8 - (((s32) blk + blk->unk4) & 7));
    blk->unk4 = pos + blk->unk6;
    blk->unkA = pos;
    blk->unk4 = blk->unk4 - (((s32) blk + blk->unk4) & 7) + 8;
    new = (struct_eu_C8950_blk *) allocate_memory(blk->unk4, 0xFF, 2, 0);
    if (new == NULL) {
        while (1) {
        }
    }
    bcopy((void *) blk, (void *) new, blk->unk4);
    bzero((u8 *) new + new->unkA, new->unk6);
    func_10004074((s32) blk);
    return new;
}
