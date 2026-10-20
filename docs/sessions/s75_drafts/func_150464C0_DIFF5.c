u8 func_150464C0(u8 *arg0, u16 arg1, f32 arg2, HitInfo *arg3) {
    s32 sp74;
    s32 sp70;
    HitInfo a;
    HitInfo b;
    u8 r1;
    u8 r2;

    if (arg2 < *(f32 *)(arg0 + 4)) {
        arg3->flags &= ~2;
        return 0;
    }
    a = *arg3;
    b = *arg3;
    func_15045A04(arg0, arg1, &sp74, (s32)&sp70);
    r1 = func_15045B70(arg0, arg2, &sp74, &a);
    r2 = func_15046038(arg0, arg2, &sp70, &b);
    if (r1 != 0 && r2 != 0) {
        if (a.t < b.t) {
            *arg3 = a;
            return 1;
        }
        *arg3 = b;
        return 1;
    }
    if (r1 != 0) {
        *arg3 = a;
        return 1;
    }
    if (r2 != 0) {
        *arg3 = b;
        return 1;
    }
    if (a.t < b.t) {
        *arg3 = a;
    } else {
        *arg3 = b;
    }
    arg3->flags &= ~2;
    return 0;
}
