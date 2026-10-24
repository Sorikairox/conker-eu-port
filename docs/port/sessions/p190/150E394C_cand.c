void func_1000E7A0(u32, s32);
/*
 * sound_handle_release_cb: P190. Callback that func_150E3994 passes to func_1000FA64: 1 while the handle *handle is
 * 0, else releases it (func_1000E7A0(2, handle)) and returns 0.
 */
s32 func_150E394C(s32 arg0, s32 arg1, s32 *handle, s32 arg3) {
    if (*handle == 0) {
        return 1;
    }
    func_1000E7A0(2, *handle);
    return 0;
}
