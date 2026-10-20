typedef struct {
    u8 u0;
    s32 u4;
    f32 f8;
    f32 fC;
    f32 f10[3];
    f32 f1C;
    f32 f20;
    s8 u24;
    s8 u25;
    s8 u26;
} S9940;
typedef struct {
    f32 a;
    f32 b;
    u8 c8;
    u8 c9;
    u8 cA;
    u8 cB;
    u8 cC;
    u8 padD[3];
    void *p10;
} T9940;
typedef struct {
    u8 fl;
    u8 b1;
    s16 s2;
    u8 b4;
} P9940;
extern T9940 D_8008FD4C[];
struct260 *func_151A8B20(void *arg0, s16 arg1, s32 arg2, u8 arg3, s32 arg4);

void func_151A9940(u8 arg0, u8 arg1, void *arg2, s32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8) {
    S9940 s;
    P9940 p;
    s32 v[3];
    T9940 *t;
    s32 fl;
    u8 *r;

    fl = arg0;
    if (arg1 < 9) {
        t = &D_8008FD4C[arg1];
        s.u0 = ((fl & 2) ? 8 : 0) | 1 | ((arg2 != NULL) ? 2 : 0) | ((fl & 1) ? 4 : 0);
        s.u4 = (s32)arg2;
        s.f8 = t->a;
        s.fC = t->b;
        if (arg3 != 0) {
            *(V3BD4 *)s.f10 = *(V3BD4 *)arg3;
        } else {
            s.f10[0] = 0.0f;
            s.f10[1] = 0.0f;
            s.f10[2] = 0.0f;
        }
        s.f1C = arg4;
        s.f20 = arg5;
        s.u24 = 2;
        s.u25 = -1;
        s.u26 = 1;
        r = (u8 *)func_151A8B20(&s, arg6, 0x2C, arg7, arg8);
        if (r != NULL) {
            r += 0x80;
            memcpy(r, t->p10, 0x2C);
            if (fl & 8) {
                r[0x28] |= 1;
            }
            if (fl & 0x10) {
                r[0x28] |= 2;
            }
        }
        if (fl & 4) {
            p.fl = ((arg6 == -1) ? 0 : 1) | 2;
            p.b1 = 2;
            p.s2 = (arg6 == -1) ? 300 : arg6;
            p.b4 = t->cB;
            if (arg3 != 0) {
                v[0] = ((f32 *)arg3)[0];
                v[1] = ((f32 *)arg3)[1];
                v[2] = ((f32 *)arg3)[2];
            } else {
                v[0] = ((s16 *)arg2)[0];
                v[1] = ((s16 *)arg2)[1];
                v[2] = ((s16 *)arg2)[2];
            }
            func_1516284C((Header *)&p, (s32)v, t->c8, t->c9, t->cA, 0xFF, 0, 0, t->cC, 0xFF, 1);
        }
    }
}
