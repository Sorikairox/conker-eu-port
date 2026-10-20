void func_15143134(void *arg0, void *arg1, void *arg2);
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32 *, s32, f32);
u8 func_15145C90(s32 arg0);
f32 func_15143E64(void *arg0);
s32 func_15146078(void *, void *, void *);

typedef struct {
    s32 a;
    u8 b;
    u8 pad5[0xF];
    f32 p[3];
    u8 pad20[0x1B];
    u8 id;
    u8 pad3C[0x198];
    u8 *tbl;
} V8DA8;

typedef struct {
    V8DA8 *v;
    u8 id;
    u8 pad5[3];
    u8 x8[0xC];
    u8 idx;
    u8 pad15[3];
    f32 off[3];
    u8 pad24;
    u8 fl;
} L8DA8;

typedef struct {
    u8 pad0[0x1C];
    u8 flags;
    u8 pad1D[0x13];
    f32 pos[3];
    f32 tgt[3];
    u8 x48[0xC];
    f32 len;
    f32 inv;
    u8 pad5C[4];
    L8DA8 *link;
} O8DA8;

s32 func_151A8DA8(O8DA8 *arg0) {
    L8DA8 *l;
    V8DA8 *v;
    f32 vec[3];
    s32 sp78;
    u8 sp60[0x18];

    l = arg0->link;
    v = l->v;
    if (v->a == 0 || v->id != l->id || v->b == 0xFF) {
        return 0;
    }
    if (v->tbl != NULL) {
        func_15143134(l->x8, arg0->pos, v->tbl + (l->idx << 6));
        if (!(l->fl & 1)) {
            if (func_150ACEA0(arg0->pos[0], arg0->pos[1], arg0->pos[2],
                              arg0->pos[0] - (v->p[0] + l->off[0]),
                              arg0->pos[1] - (v->p[1] + l->off[1]),
                              arg0->pos[2] - (v->p[2] + l->off[2]),
                              0, NULL, &arg0->tgt[0], &arg0->tgt[1], &arg0->tgt[2], NULL, &sp78, 0, 0.0f)) {
                if (func_15145C90(sp78)) {
                    l->fl |= 1;
                } else {
                    arg0->flags &= ~2;
                    return 1;
                }
            } else {
                arg0->flags &= ~2;
                return 1;
            }
        }
        vec[0] = arg0->tgt[0] - arg0->pos[0];
        vec[1] = arg0->tgt[1] - arg0->pos[1];
        vec[2] = arg0->tgt[2] - arg0->pos[2];
        if ((arg0->len = func_15143E64(vec)) != 0.0f) {
            arg0->inv = 1.0f / arg0->len;
            func_15146078(vec, sp60, arg0->x48);
            arg0->flags |= 2;
        } else {
            arg0->flags &= ~2;
        }
    } else {
        arg0->flags &= ~2;
    }
    return 1;
}
