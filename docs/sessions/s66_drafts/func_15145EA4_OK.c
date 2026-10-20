void func_15142314(Mtx *, s32, f32 *);

void func_15145EA4(f32 **arg0, f32 **arg1, Mtx *arg2, s32 arg3) {
    f32 **p;
    f32 mtx[4][4];
    f32 **q;
    f32 *v;
    f32 *o;

    if (D_800C42B0 != 0) {
        guMtxL2F(mtx, arg2);
        if (arg3 > 0) {
            p = arg0;
            q = arg1;
            do {
                v = *p;
                if (!arg3) {} // fakematch: extends arg3's live range (count in s1, not s2)
                if ((v != NULL) && ((v[0] != 0.0f) || (v[1] != 0.0f) || (v[2] != 0.0f))) {
                    o = *q;
                    func_150A7E40(mtx, v[0], v[1], v[2], o, o + 1, o + 2);
                } else {
                    func_15142314(arg2, 0, *q);
                }
                arg3--;
                p++;
                q++;
            } while (arg3 > 0);
        }
    } else {
        if (arg3 > 0) {
            p = arg0;
            q = arg1;
            do {
                v = *p;
                if ((v != NULL) && ((v[0] != 0.0f) || (v[1] != 0.0f) || (v[2] != 0.0f))) {
                    o = *q;
                    func_150A7E40((f32 (*)[4]) arg2, v[0], v[1], v[2], o, o + 1, o + 2);
                } else {
                    func_15142314(arg2, 0, *q);
                }
                arg3--;
                p++;
                q++;
            } while (arg3 > 0);
        }
    }
}
