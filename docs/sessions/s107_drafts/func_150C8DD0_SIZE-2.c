extern f32 D_800A08F8;
f32 sinf(f32);
f32 cosf(f32);
typedef struct { f32 s; f32 c; } SC;
typedef struct { u8 d[0x50]; } X50;
typedef struct { u8 pad0[0x14]; s32 n; u8 pad18[0x18]; } Cfg;
typedef struct {
    u8 pad0[0x10];
    Cfg cfg;
    f32 u40, u44, u48;
    s16 u4C;
    f32 u50;
    X50 *u54;
    X50 *u58;
    u8 pad5C[0x360 - 0x5C];
    SC *u360;
    X50 *u364;
    SC u368[1];
} Obj;
Obj *func_150C8DD0(Cfg *arg0, s32 arg1, u8 arg2, s32 arg3) {
    Obj *p;
    s32 i;
    f32 a;

    p = func_15167A68(0x31, arg3, arg1 + arg0->n * sizeof(SC) + (arg0->n + 1) * sizeof(X50) * 2 + 0x368, 1, arg2, 1);
    if (p == NULL) {
        return NULL;
    }
    memcpy(&p->cfg, arg0, sizeof(Cfg));
    p->u360 = p->u368;
    p->u54 = (X50 *)(p->u368 + arg0->n);
    p->u58 = (X50 *)(p->u368 + arg0->n) + (arg0->n + 1);
    p->u40 = 0.0f;
    p->u44 = 0.0f;
    p->u364 = (X50 *)(p->u368 + arg0->n) + (arg0->n + 1) * 2;
    p->u50 = 0.0f;
    p->u4C = *(s16 *)&p->cfg.pad18[0];
    p->u48 = D_800A08F8 / p->cfg.n;
    for (i = 0, a = 0.0f; i < p->cfg.n; i++) {
        p->u360[i].s = sinf(a);
        p->u360[i].c = cosf(a);
        a += p->u48;
    }
    return p;
}
