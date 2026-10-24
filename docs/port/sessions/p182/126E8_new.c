// text_queue_read: takes the next record of the text queue D_800427A0 into the buffer arg0 (at most arg1 bytes,
// func_15043CA4) and returns its length (P182: the asm caller func_15080628 loops while it is non-zero; it was void).
s32 func_100126E8(s32 arg0, s32 arg1) {
    return func_15043CA4(&D_800427A0, arg0, arg1);
}

