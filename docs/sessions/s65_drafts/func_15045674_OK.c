typedef struct { s32 unk0; s32 *unk4; s32 unk8; s32 unkC; } Unk3720;
typedef struct { f32 unk0; s16 unk4[3][3]; s32 unk18; u8 unk1C; u8 unk1D; s32 unk20; } Unk45674;
extern Unk3720 D_800D3720[];
extern f32 D_800990F8; // 99999.9f
void func_1510F800(s32);
s32 func_150A5480(s32, s32);

s32 func_15045674(f32 *arg0, f32 arg1, Unk45674 *arg2) {
    Unk45674 *out;
    s32 best;
    s32 n;
    s32 i;
    f32 d;
    s32 j;
    s32 *q;
    s32 off;

    if (arg1 < arg0[1]) {
        arg2->unk1C &= ~2;
        return 0;
    }
    arg2->unk0 = D_800990F8;
    best = -1;
    func_1510F800(3);
    n = func_150A5480((s32) arg0[0], (s32) arg0[2]);
    for (i = 0; i < n; i++) {
        d = D_800D3720[i].unk0 * 0.00390625f;
        if ((arg0[1] <= d) && (d < arg2->unk0)) {
            best = i;
            arg2->unk0 = d;
        }
    }
    if (best != -1) {
        q = D_800D3720[best].unk4;
        out = arg2;
        off = D_800D3720[best].unk8;
        for (j = 0; j < 3; j++) {
            s16 *p;

            p = (s16 *) (q[j] + off);
            out->unk4[j][0] = p[0];
            out->unk4[j][1] = p[1];
            out->unk4[j][2] = p[2];
        }
        out->unk18 = 0;
        out->unk1C |= 6;
        out->unk1D = 4;
        out->unk20 = 0;
        if (out->unk0 <= arg1) {
            arg2->unk1C |= 2;
            return 1;
        }
        return 0;
    }
    arg2->unk1C &= ~2;
    return 0;
}
