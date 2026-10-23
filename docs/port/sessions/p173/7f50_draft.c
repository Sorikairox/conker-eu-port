// record_free_dispatch: calls the record kind's (+0x20, 0..19, else 0) free handler D_8008A690 with the record.
void func_15147F50(u8 *arg0) {
    s32 idx = *(s32 *)(arg0 + 0x20);

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 20) {
        idx = 0;
    }
    /* P173: the handlers take the record (the asm keeps a0 = arg0 at the jalr; browser P171: func_15147E64 freed
     * garbage at rec + 0x84 when it got no argument) */
    ((void (*)(u8 *)) D_8008A690[idx])(arg0);
}
