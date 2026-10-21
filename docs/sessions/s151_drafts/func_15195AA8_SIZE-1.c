typedef struct { s32 a; s32 b; } Tok;
s32 func_15195DD8(Tok *, s32, s32, s32 *);
extern s32 D_800E0D20;

void *func_15195AA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 val;
    Ent3C *p;
    s32 idx;
    s32 cnt;
    s32 n;
    s32 i;
    Tok *t;

    n = arg3;
    p = NULL;
    if (arg0 == 0) {
        return NULL;
    }
    if (arg3 == -1) {
        n = 0;
    }
    do {
        idx = func_15195DD8((Tok *)arg0, arg1, n, &cnt);
        if (idx == -1) {
            arg3 = 0;
            continue;
        }
        if (arg1 == 0) {
            arg1 = D_800E0D20;
        }
        p = (Ent3C *)D_800E0D18;
        t = &((Tok *)arg0)[idx];
        val = t->b;
        while (p != NULL && p->x8 != 0) {
            p = (Ent3C *)p->node.prev;
        }
        if (p == NULL) {
            p = func_15195EF4(arg1, val, t->a, arg2);
            if (p != NULL) {
                arg4 = 0;
                p->x12 = arg6;
                p->x13 = arg7;
            } else {
                return NULL;
            }
        } else {
            arg4 = 0;
            idx = func_15195FF4(idx, (s32)p, val, arg2);
        }
        n++;
        if (p->x14 < cnt) {
            p->x14 = cnt;
        }
        if (arg5 == 0) {
            for (i = 0; i < 5 && p->a[i] != -1; i++) {
            }
            if (i < 5) {
                p->a[i] = idx;
                ((u8 *)p->x30)[i] = cnt;
            }
        } else {
            for (i = 0; i < 5 && p->b[i] != -1; i++) {
            }
            if (i < 5) {
                p->b[i] = idx;
                ((u8 *)p->x30)[i + 5] = cnt;
            }
        }
    } while (arg3 == -1);
    if (arg1 == D_800E0D20) {
        D_800E0D20--;
    }
    return p;
}
