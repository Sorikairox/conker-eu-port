extern f32 D_800990F4;
extern f32 D_800DC298;
extern f32 D_800DC29C;
extern f32 D_800DC2A4;
extern s32 D_800DC26C;
s32 func_150A3F50(s32, s32);

/* P67: floor probe (sibling of func_15045674). Of the collision triangles func_150A3F50 lists under pos (x, z), takes
 * the highest one at or below pos[1] (heights in D_800D3720 are 24.8 fixed point) and copies its vertices into out.
 * The probe point is also stored in D_800DC298..D_800DC2A4 (D_800DC2A0 is declared as a pointer in variables.h).
 * Returns 1 when the floor is at or above maxY (out flag 2 set). */
s32 func_150453BC(u8 *arg0, f32 maxY, u8 *arg2) {
    f32 *pos = (f32 *)arg0;
    Unk45674 *out = (Unk45674 *)arg2;
    s32 best;
    s32 n;
    s32 i;
    s32 j;
    f32 d;
    s32 *q;
    s32 off;

    if (pos[1] < maxY) {
        out->unk1C &= ~2;
        return 0;
    }
    out->unk0 = D_800990F4;
    best = -1;
    func_1510F800(0);
    D_800DC298 = pos[0];
    D_800DC29C = pos[1];
    *(f32 *)&D_800DC2A0 = pos[2];
    D_800DC2A4 = maxY;
    n = func_150A3F50((s32)pos[0], (s32)pos[2]);
    for (i = 0; i < n; i++) {
        d = D_800D3720[i].unk0 * 0.00390625f;
        if (d <= pos[1] && out->unk0 < d) {
            best = i;
            out->unk0 = d;
        }
    }
    if (best == -1) {
        out->unk1C &= ~2;
        return 0;
    }
    q = D_800D3720[best].unk4;
    off = D_800D3720[best].unk8 * 16;
    for (j = 0; j < 3; j++) {
        s16 *p = (s16 *)(q[j] + off);

        out->unk4[j][0] = p[0];
        out->unk4[j][1] = p[1];
        out->unk4[j][2] = p[2];
    }
    if (D_800DBE5C != 0) {
        /* surface type of the triangle (index of its vertex list in D_800DC26C, 12 bytes each) */
        out->unk18 = ((s32 *)D_800DBE5C)[((s32)D_800D3720[best].unk4 - D_800DC26C) / 12];
    } else {
        out->unk18 = 0;
    }
    out->unk1D = 1;
    out->unk1C |= 7;
    out->unk20 = 0;
    if (maxY <= out->unk0) {
        out->unk1C |= 2;
        return 1;
    }
    return 0;
}
