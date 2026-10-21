typedef struct {
    u8 pad0[0x10];
    u8 *p10;
    u8 pad14[8];
    s16 t1C;
    s16 vel1E;
    s16 h20;
    s16 h22;
    s16 h24;
    s16 h26;
    s16 h28;
    u8 pad2A[2];
    u8 b2C;
    u8 b2D;
    u8 b2E;
    s8 idx2F;
    s16 h30;
    s16 h32;
    u8 pad34[4];
    s16 timer38;
    s8 fade3A;
    u8 pad3B[4];
    u8 alpha3F;
    u8 pad40[4];
    u16 flags44;
    u8 pad46[2];
    s8 idx48;
} E0CObj;
extern void (*D_8008CD68[])(u8 *);
void func_15167E0C(E0CObj *arg0) {
    u8 done;
    s32 v;
    s32 max;

    done = 0;
    if (arg0->timer38 != 0x7FFF) {
        arg0->timer38 -= D_800BE9E4;
        if (arg0->timer38 < 0) {
            arg0->timer38 = 0;
            done = 1;
        }
    }
    if (arg0->fade3A > 0) {
        if (arg0->fade3A < arg0->alpha3F) {
            arg0->alpha3F -= arg0->fade3A;
        } else {
            arg0->timer38 = 0;
            done = 1;
        }
    }
    if (arg0->idx2F != -1 && D_8008CD68[arg0->idx2F] != NULL) {
        D_8008CD68[arg0->idx2F]((u8 *)arg0);
    }
    if (arg0->timer38 != 0) {
        arg0->h30 += arg0->h32;
        v = ((arg0->h22 << 8) | arg0->b2E) + arg0->h30 * D_800BE9E4;
        arg0->h22 = v >> 8;
        arg0->b2E = v;
        v = ((arg0->h20 << 8) | arg0->b2C) + arg0->h26 * D_800BE9E4;
        arg0->h20 = v >> 8;
        arg0->b2C = v;
        v = ((arg0->h24 << 8) | arg0->b2D) + arg0->h28 * D_800BE9E4;
        arg0->h24 = v >> 8;
        arg0->b2D = v;
        if (arg0->vel1E != 0) {
            arg0->t1C += arg0->vel1E * D_800BE9E4;
            max = (arg0->p10[4] << 8) - 1;
            if (max < arg0->t1C) {
                if (arg0->flags44 & 0x20) {
                    arg0->timer38 = 0;
                    done = 1;
                } else {
                    arg0->flags44 |= 0x80;
                    if (arg0->flags44 & 2) {
                        arg0->t1C = max - arg0->t1C % max;
                        arg0->vel1E = -arg0->vel1E;
                    } else {
                        do {
                            arg0->t1C -= max;
                        } while (max < arg0->t1C);
                    }
                }
            } else if (arg0->t1C < 0) {
                if (arg0->flags44 & 0x40) {
                    arg0->timer38 = 0;
                    done = 1;
                } else if (arg0->flags44 & 2) {
                    arg0->t1C = -arg0->t1C % max;
                    arg0->vel1E = -arg0->vel1E;
                } else {
                    do {
                        arg0->t1C += max;
                    } while (arg0->t1C < 0);
                }
            }
        }
    } else {
        done = 1;
    }
    if (done) {
        if (arg0->idx48 != -1) {
            D_8008CDC0[arg0->idx48]();
        }
        func_1516972C((struct102 *)arg0);
    }
}
