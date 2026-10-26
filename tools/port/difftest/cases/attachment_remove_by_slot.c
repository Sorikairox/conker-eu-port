/* P241 selftest: a candidate longer than the reference (8 words, matched C, no .s) that calls the function right
 * after it (attachment_remove_by_slot_n). The extra test reads D_800C3EE0 only; both paths make the same call. */
s32 attachment_remove_by_slot_n(u8 *arg0, s32 arg1, s32 arg2);
extern s32 D_800C3EE0;
void attachment_remove_by_slot(s32 arg0, s32 arg1) {
    if (D_800C3EE0 == 0x5A5A1234) {
        attachment_remove_by_slot_n((u8 *) arg0, arg1, 0xFF);
        return;
    }
    attachment_remove_by_slot_n((u8 *) arg0, arg1, 0xFF);
}
