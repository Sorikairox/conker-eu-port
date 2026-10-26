void attachment_set_alpha_by_slot(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_v0 = attachment_find_by_slot(arg0, arg1, arg3);
    if (temp_v0 != NULL) {
        temp_v0[3] = arg2;
    }
}
