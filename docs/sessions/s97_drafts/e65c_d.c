typedef struct {
    s32 a;
    u8 b;
} K_E65C;
void func_1516972C(struct102 *arg0);
s32 func_15169850(s32, u8, s32, s32, s32);
void func_151BE65C(struct102 *arg0, K_E65C *arg1, u8 arg2) {
    s32 p = (s32)arg0 + 0x28;

    if (arg2 == 0x3B) {
        if (arg1->a == ((K_E65C *)p)->a || arg1->b == ((K_E65C *)p)->b) {
            func_1516972C(arg0);
        }
    } else {
        func_15169850((s32)arg1, arg2, p, p + 4, (s32)arg0);
    }
}
