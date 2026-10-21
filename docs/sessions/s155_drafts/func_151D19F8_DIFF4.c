typedef struct {
    u8 *obj;
    u8 pad4[4];
    void *res;
    u8 padC[0xC];
    struct17 pos;
} Link19F8;

typedef struct {
    struct17 pos;
    s16 xC;
    s16 xE;
    s32 x10;
    u8 x14;
    u8 x15;
    s32 x18;
} SpA19F8;

typedef struct {
    u8 *owner;
    f32 x4;
    u8 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
} SpB19F8;

void func_151D19F8(u8 *arg0) {
    s32 pad;
    SpB19F8 b;
    SpA19F8 a;
    Link19F8 *l = (Link19F8 *)(arg0 + 0x28);
    u8 *r;
    u8 *obj;

    obj = l->obj;
    b.owner = arg0;
    b.x8 = 0xFF;
    b.x4 = 0.0f;
    if (obj[4] == 0x25) {
        b.xC = 800.0f;
        b.x10 = 36.0f;
        b.x14 = 50.0f;
        b.x18 = 200.0f;
    } else {
        if (D_80082FA0 > 0) {
            b.xC = 260.0f;
        } else {
            b.xC = 500.0f;
        }
        b.x10 = 40.0f;
        b.x14 = 40.0f;
        b.x18 = 180.0f;
    }
    b.x1C = *(f32 *)(l->obj + 0x14C);
    a.x15 = 0x19;
    a.pos = l->pos;
    a.xC = 0x12C;
    a.xE = 0x36;
    a.x10 = 0x13;
    a.x14 = 6;
    a.x18 = 0;
    r = func_15147FF0(&a, 0x20, 0x28, 0, 0x11, 0x12, 0, 0, 0, arg0[0xC], arg0[1]);
    if (r != NULL) {
        memcpy(*(void **)(r + 0x98), &b, 0x20);
        l->res = r;
    }
}
