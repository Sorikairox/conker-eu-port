#ifdef NON_MATCHING
void func_15145EA4(f32 **, f32 **, void *, s32);
extern f32 D_800A209C[3]; /* the two emitter offsets (bone space) */
extern f32 D_800A20A8[3];
extern f32 D_800A20B4[3]; /* the two direction points */
extern f32 D_800A20C0[3];
extern f32 D_800A2164;
// twin_emitters_follow_owner: handler 15 of D_8008A980 (`void (u8 *)`). Ends the effect (+0xE = -1) when the owner
// (+0x28) is gone or its id +0x3B no longer matches +0x2C. With the owner's bone matrices (+0x1D4) it transforms the
// four offsets D_800A209C..C0 by the first matrix (func_15145EA4) and gives each of the two emitter pairs (+0x30 / +0x38
// and +0x34 / +0x3C) its position and direction: the first kind gets the flag 1 at +0x168, the second the flag 2 (and
// loses 4) at +0x58. Without matrices both flags are cleared. Then the first kind's +0x158 / +0x15C become 0 / 0 while
// +0xE < 10, else 6 / 15, and the second kind's +0x174 becomes 0, else D_800A2164 (1.306).
void func_150FA738(u8 *arg0) {
    u8 *owner = *(u8 **) (arg0 + 0x28);
    u8 **a = (u8 **) (arg0 + 0x30);
    u8 **b = (u8 **) (arg0 + 0x38);
    f32 *src[4];
    f32 *dst[4];
    f32 pos[2][3]; /* sp88, sp94 */
    f32 dir[2][3]; /* sp70, sp7C */
    u8 *p;
    u8 i;

    if (*(s32 *) owner == 0 || arg0[0x2C] != owner[0x3B]) {
        *(s16 *) (arg0 + 0xE) = -1;
        return;
    }
    if (*(u8 **) (owner + 0x1D4) != NULL) {
        src[0] = D_800A209C;
        src[1] = D_800A20A8;
        src[2] = D_800A20B4;
        src[3] = D_800A20C0;
        dst[0] = pos[0];
        dst[1] = pos[1];
        dst[2] = dir[0];
        dst[3] = dir[1];
        func_15145EA4(src, dst, *(u8 **) (owner + 0x1D4) + 0x40, 4);
        for (i = 0; i < 2; i++) {
            p = a[i];
            if (p != NULL) {
                p[0x168] |= 1;
                ((f32 *) (p + 0x34))[0] = pos[i][0];
                ((f32 *) (p + 0x34))[1] = pos[i][1];
                ((f32 *) (p + 0x34))[2] = pos[i][2];
                ((f32 *) (p + 0x40))[0] = dir[i][0];
                ((f32 *) (p + 0x40))[1] = dir[i][1];
                ((f32 *) (p + 0x40))[2] = dir[i][2];
            }
            p = b[i];
            if (p != NULL) {
                *(s32 *) (p + 0x58) |= 2;
                *(s32 *) (p + 0x58) &= ~4;
                ((f32 *) (p + 0x34))[0] = pos[i][0];
                ((f32 *) (p + 0x34))[1] = pos[i][1];
                ((f32 *) (p + 0x34))[2] = pos[i][2];
                ((f32 *) (p + 0x40))[0] = dir[i][0];
                ((f32 *) (p + 0x40))[1] = dir[i][1];
                ((f32 *) (p + 0x40))[2] = dir[i][2];
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (a[i] != NULL) {
                a[i][0x168] &= ~1;
            }
            if (b[i] != NULL) {
                *(s32 *) (b[i] + 0x58) &= ~2;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        p = a[i];
        if (p != NULL) {
            if (*(s16 *) (arg0 + 0xE) < 10) {
                *(f32 *) (p + 0x158) = 0.0f;
                *(f32 *) (p + 0x15C) = 0.0f;
            } else {
                *(f32 *) (p + 0x158) = 6.0f;
                *(f32 *) (p + 0x15C) = 15.0f;
            }
        }
        p = b[i];
        if (p != NULL) {
            if (*(s16 *) (arg0 + 0xE) < 10) {
                *(f32 *) (p + 0x174) = 0.0f;
            } else {
                *(f32 *) (p + 0x174) = D_800A2164;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FA738.s")
#endif
