s32 func_150AE5F8(s32 *args) {
    s32 id = args[0];
    s32 n = (id & 0xF000) >> 12;

    if (n == 0) {
        return 0;
    }
    return D_80088838[n - 1](id & 0xFFFF0FFF, args[1], args);
}
