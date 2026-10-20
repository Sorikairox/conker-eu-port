typedef struct {
    f32 unk0;
    f32 unk4;
    u8 pad8[0x10];
} E86C;

void func_151AE86C(f32 *arg0, u8 *arg1, s32 arg2, f32 arg3) {
    s32 n = arg1[0x42];
    s32 i;
    E86C *e;
    f32 prev;
    f32 d;
    f32 frac;

    for (i = 0; i < n - 1; i++) {
        if (arg3 <= (*(E86C **)(arg1 + 0x38))[i].unk4) {
            break;
        }
    }
    if (i >= n - 2) {
        *arg0 = 1.0f;
        return;
    }
    if (i == 0) {
        *arg0 = 0.0f;
        return;
    }
    e = &(*(E86C **)(arg1 + 0x38))[i];
    prev = e[-1].unk4;
    frac = e->unk4 - prev;
    if (frac != 0.0f) {
        frac = (arg3 - prev) / frac;
    } else {
        frac = 0.0f;
    }
    *arg0 = (f32) (i - 1) / (f32) (n - 3) + frac / (f32) (n - 1);
}
