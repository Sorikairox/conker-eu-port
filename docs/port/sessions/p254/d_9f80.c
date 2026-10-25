#ifdef NON_MATCHING
extern s32 (*D_8008FC64[])(u8 *); /* emitter2 check handlers (result 0 = stop) */
extern void (*D_8008FC5C[])(u8 *); /* emitter2 sound update handlers */
void func_1519C38C(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3);
// emitter2_path_update: entry 12 of D_8008A5A0 (`s32 (u8 *)`). Updates a path emitter: clears flag 0x10 of the
// owner's (+0x98) +0x150; returns 0 if a short path (+0x2C < 2) has flag 8 in +0x1E, or if the owner's check handler
// D_8008FC64[owner +0x48] (-1 = none) returns 0. Else moves every point from the head +0x2E back to the current
// point +0x2D (ring of +0x25 points of 0x28 bytes at +0x94: func_1519C38C with gravity owner +0x20 over
// D_800BE9A4, and +0x18 grows by owner +0x30 per frame), puts the owner's model (+0x148 -> +0x14, s16 +0x0E..+0x12)
// on the current point when the path has 2+ points, runs the sound handler D_8008FC5C[owner +0x38], clears flag 1 of
// +0x150 and copies the current point (or zero when +0x2C <= 0) to +0x54..+0x5C. Returns 1.
s32 func_15199F80(u8 *arg0) {
    u8 *owner = *(u8 **) (arg0 + 0x98);
    u8 *points = *(u8 **) (arg0 + 0x94);
    u8 *pt;
    s16 *model;
    s32 i;

    owner[0x150] &= ~0x10;
    if (*(s8 *) (arg0 + 0x2C) < 2 && (*(u16 *) (arg0 + 0x1E) & 8)) {
        return 0;
    }
    i = *(s8 *) (owner + 0x48);
    if (i != -1 && D_8008FC64[i](arg0) == 0) {
        return 0;
    }
    i = *(s8 *) (arg0 + 0x2E);
    while (i != *(s8 *) (arg0 + 0x2D)) {
        i--;
        if (i < 0) {
            i = arg0[0x25] - 1;
        }
        pt = points + i * 0x28;
        func_1519C38C((f32 *) pt, (f32 *) (pt + 0xC), *(f32 *) (owner + 0x20), D_800BE9A4);
        *(f32 *) (pt + 0x18) += *(f32 *) (owner + 0x30) * D_800BE9A4;
    }
    if (*(u8 **) (owner + 0x148) != NULL && *(s8 *) (arg0 + 0x2C) >= 2) {
        pt = points + *(s8 *) (arg0 + 0x2D) * 0x28;
        model = *(s16 **) (*(u8 **) (owner + 0x148) + 0x14);
        model[7] = (s32) ((f32 *) pt)[0];
        model[8] = (s32) ((f32 *) pt)[1];
        model[9] = (s32) ((f32 *) pt)[2];
    }
    i = *(s8 *) (owner + 0x38);
    if (i != -1) {
        D_8008FC5C[i](arg0);
    }
    owner[0x150] &= ~1;
    if (*(s8 *) (arg0 + 0x2C) > 0) {
        pt = points + *(s8 *) (arg0 + 0x2D) * 0x28;
        *(s32 *) (arg0 + 0x54) = ((s32 *) pt)[0];
        *(s32 *) (arg0 + 0x58) = ((s32 *) pt)[1];
        *(s32 *) (arg0 + 0x5C) = ((s32 *) pt)[2];
    } else {
        *(f32 *) (arg0 + 0x54) = 0.0f;
        *(f32 *) (arg0 + 0x58) = 0.0f;
        *(f32 *) (arg0 + 0x5C) = 0.0f;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15199F80.s")
#endif
