s32 func_1505D024();

typedef struct {
    s32 step;
    s32 acc;
    struct127 *obj;
} Tick0B2C;

typedef struct {
    u8 pad0[0x10];
    struct127 *unk10;
    u8 pad14[0x7C];
    Tick0B2C t;
} Obj0B2C;

s32 func_15190B2C(Obj0B2C *arg0) {
    Tick0B2C *t = &arg0->t;
    u8 *v;

    arg0->t.acc += D_800BE9E4;
    while (t->acc >= t->step) {
        func_1505D024(arg0->unk10, 0x60021, 0, t->obj - D_800CC2D0);
        t->acc -= t->step;
    }
    v = *(u8 **)((u8 *)arg0->unk10 + 0x31C);
    if (v != NULL && v[0x84] == 0) {
        *(s16 *)(v + 0x46) = 1000;
    }
    return 1;
}
