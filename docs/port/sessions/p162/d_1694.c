void func_15143134(void *arg0, void *arg1, void *arg2);
extern f32 D_800AB37C[2][3];
s32 func_151D1694(u8 *obj, f32 *out, u8 which) {
    void *mtx = *(void **)(obj + 0x1D4);

    if (mtx == NULL) {
        return 0;
    }
    func_15143134(D_800AB37C[which], out, mtx);
    return 1;
}
