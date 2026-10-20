extern f32 D_80099108;
extern s32 D_800D3C50;
extern s32 D_800DC26C;
s32 func_150A49D0(s32, s32 *, s32);
s32 func_150A48C0(s32, s32, s32, s32 *);
u8 func_15046038(u8 *arg0, f32 arg1, s32 *arg2, HitInfo *arg3) {
    HitInfo *out;
    s32 best;
    s32 n;
    s32 i;
    f32 d;
    s32 j;
    s32 *q;
    s32 off;
    struct131 *s;

    arg3->t = D_80099108;
    best = -1;
    func_150A49D0(*arg2, &D_800D3C50, 0);
    n = func_150A48C0((s32) *(f32 *)(arg0 + 0), (s32) *(f32 *)(arg0 + 8), *arg2, &D_800D3C50);
    for (i = 0; i < n; i++) {
        d = D_800D3720[i].unk0 * 0.00390625f;
        if ((*(f32 *)(arg0 + 4) <= d) && (d < arg3->t)) {
            best = i;
            arg3->t = d;
        }
    }
    if (best != -1) {
        s32 k;

        q = D_800D3720[best].unk4;
        out = arg3;
        off = D_800D3720[best].unk8;
        for (j = 0; j < 3; j++) {
            s16 *p;

            p = (s16 *) (q[j] + off);
            out->pos.v[j * 3 + 0] = p[0];
            out->pos.v[j * 3 + 1] = p[1];
            out->pos.v[j * 3 + 2] = p[2];
        }
        k = D_800D3720[best].unkC;
        s = &D_800DBEF4[k];
        out->unk20 = (s32) s;
        if (*(s32 **)((u8 *)s + 0x44) != NULL) {
            s32 idx = ((s32) q - D_800DC26C) / 12 - *(u16 *)((u8 *)s + 0x58);

            out->unk18 = (*(s32 **)((u8 *)s + 0x44))[idx];
        } else {
            out->unk18 = *(s32 *)((u8 *)s + 0x40);
        }
        out->flags |= 6;
        if ((s->unk6F & 0x80) == 0x80) {
            out->flags |= 1;
        }
        out->unk1D = 3;
        if (out->t <= arg1) {
            arg3->flags |= 2;
            return 1;
        }
        return 0;
    }
    arg3->flags &= ~2;
    return 0;
}
