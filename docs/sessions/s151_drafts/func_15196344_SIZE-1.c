typedef struct { s32 a; s32 b; } Tok;
s32 func_15195DD8(Tok *, s32, s32, s32 *);
Ent3C *func_15195EF4(s32, s32, s32, s32);
s32 func_15196270(Ent3C *, Tok *, s32, s32);
extern u8 D_800BEAC0;

Ent3C *func_15196344(Tok *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 cnt;
    s32 val;
    s32 key;
    Ent3C *p;
    s32 idx;
    s32 n;
    Tok *t;

    n = arg3;
    if (arg0 == NULL) {
        return NULL;
    }
    if (D_800BEAC0) {
        return NULL;
    }
    if (arg3 == -1) {
        n = 0;
    }
    do {
        idx = func_15195DD8(arg0, arg1, n, &cnt);
        if (idx == -1) {
            arg3 = 0;
            continue;
        }
        if (arg1 == 0) {
            arg1 = D_800E0D20;
        }
        key = arg4 ? -1 : arg1;
        p = (Ent3C *)D_800E0D18;
        for (; p != NULL; p = (Ent3C *)p->node.prev) {
            if (p->x8 == key) {
                break;
            }
        }
        t = &arg0[idx];
        val = t->b;
        if (p == NULL) {
            p = func_15195EF4(arg1, val, t->a, arg2);
            if (p != NULL) {
                p->x12 = arg5;
                p->x13 = arg6;
                arg4 = 0;
            } else {
                return NULL;
            }
        } else {
            idx = func_15195FF4(idx, (s32)p, val, arg2);
            arg4 = 0;
        }
        if (p->x14 < cnt) {
            p->x14 = cnt;
        }
        func_15196270(p, arg0, idx, cnt);
        n++;
    } while (arg3 == -1);
    if (arg1 == D_800E0D20) {
        D_800E0D20--;
    }
    return p;
}
