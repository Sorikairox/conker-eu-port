typedef struct { f32 x, y, z; } V1694;
extern V1694 D_800AB37C[];

s32 func_151D1694(u8 *arg0, void *arg1, u8 arg2) {
    void *p;
    V1694 *v;

    v = &D_800AB37C[arg2];
    p = *(void **)(arg0 + 0x1D4);
    if (p == NULL) {
        return 0;
    }
    func_15143134(v, arg1, p);
    return 1;
}
