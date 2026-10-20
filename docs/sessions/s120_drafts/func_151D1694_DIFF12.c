typedef struct { f32 x, y, z; } V1694;
extern V1694 D_800AB37C[];

s32 func_151D1694(s32 arg0, s32 arg1, u8 arg2) {
    void **pp;
    void *p;
    V1694 *v;

    v = &D_800AB37C[arg2];
    pp = (void **)(arg0 + 0x1D4);
    p = *pp;
    if (p == NULL) {
        return 0;
    }
    func_15143134(v, (void *)arg1, p);
    return 1;
}
