typedef struct {
    u8 pad0[0x10];
    s32 flags10;
    u8 pad14[4];
    u8 b18;
    u8 pad19[3];
    s16 t1C;
    u8 pad1E[2];
    s32 pos20;
    s32 vel24;
    u8 pad28[3];
    s8 b2B;
    u8 pad2C[0x2C];
    s32 flags58;
    u8 b5C;
    u8 pad5D[0xF];
    s16 h6C;
    s16 h6E;
    u8 b70;
    u8 b71;
    u8 b72;
} CFE4Obj;
extern s32 (*D_8008A058[])(void);
extern s32 (*D_8008A100[])(void);
extern s32 (*D_8008A1B0[])(void);
void func_1513CFE4(CFE4Obj *arg0) {
    s32 pad;
    s8 done;
    CFE4Obj *q;
    s32 v;
    s32 vel;
    s32 max;
    s32 pos;

    if (arg0->flags10 & 1) {
        done = 0;
        if (arg0->flags58 & 1) {
            arg0->t1C -= D_800BE9E4;
            if (arg0->t1C < 0) {
                done = 1;
            }
        }
        if (arg0->b70 != 0) {
            if (D_8008A058[arg0->b70]() == 0) {
                done = 1;
            }
        }
        if (arg0->b71 != 0) {
            if (D_8008A100[arg0->b71]() == 0) {
                done = 1;
            }
        }
        q = arg0;
        if ((q->flags58 & 0x08000000) && !done && q->t1C < q->h6C) {
            v = q->t1C * q->h6E;
            if (v < q->b5C) {
                q->b5C = v;
            }
        }
        if ((q->flags58 & 0x10000000) && !done && q->t1C < q->h6C) {
            v = q->t1C * q->h6E;
            if (v < q->b5C) {
                q->b2B = v;
            }
        }
        if (!done) {
            vel = q->vel24;
            if (vel != 0) {
                max = (D_80090F14[q->b18][0] << 16) - 1;
                q->pos20 += vel * D_800BE9E4;
                pos = q->pos20;
                if (max < pos) {
                    if (q->flags58 & 0x800) {
                        done = 1;
                    } else if (q->flags58 & 0x400) {
                        q->pos20 = max - (pos % max);
                        q->vel24 = -vel;
                    } else {
                        do {
                            pos = q->pos20 = pos - max;
                        } while (max < pos);
                    }
                } else if (pos < 0) {
                    if (q->flags58 & 0x1000) {
                        done = 1;
                    } else if (q->flags58 & 0x400) {
                        q->pos20 = -pos % max;
                        q->vel24 = -vel;
                    } else {
                        do {
                            pos = q->pos20 = pos + max;
                        } while (pos < 0);
                    }
                }
            }
        }
        if (done && q->b72 != 0) {
            if (D_8008A1B0[q->b72]() != 0) {
                done = 0;
            }
        }
        if (done) {
            func_1516972C((struct102 *)q);
        }
    }
}
