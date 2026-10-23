s32 func_15145128(f32 *, f32 *, f32 *, s32 *);
s32 func_151C50BC(s32, s32 *, u8 *, s32 *, s32 *, f32, s32, u8 *, s32 *, s8 *, s32, f32, u8 *, s32, s32, s32, s32, s32);
s32 func_15146078(f32 *, s32 *, s32 *);
void func_15145974(void *, f32 *, f32 *);
s32 func_15132BBC(void *, s32, s32, s32, s32, s32, s32);
s32 memcpy(s32, s32 *, s32); /* as declared later in this file */

// light_effect_spawn: the muzzle-fire light (func_151C6A28) and others. Optional end points: a3's point copied
// (arg4 set) or resolved by func_15145128 (when a2 and a3 are given), else a1's point resolved; any failed resolve
// returns. func_151C50BC fills the 0xB4-byte light block (from arg5, the position a0, the points, arg7 / arg8 /
// arg9 / arg10 / arg12 / arg13 / arg15 / arg17 and the option byte: arg11 -> 1, arg12 -> 2, arg13 -> 4,
// | 1 when the block's +4 exceeds 150); func_15146078 gives its direction. The effect (func_15132BBC, 0xB4 extra
// bytes, arg18 / arg19) moves from a0 along the direction x arg6, angles from func_15145974, colour D_800A5860,
// owner arg9 (kind byte +0x3B) and, when arg16 is set, sound 0x4650 at a0 (func_10010F88 = func_10010E78(0, ...),
// called directly because the C func_10010F88 is void and drops the handle); the light block goes to +0x170.
void func_150F79F0(f32 *a0, void *a1, void *a2, void *a3, u8 arg4, u8 *arg5, f32 arg6, f32 arg7, f32 arg8, u8 *arg9,
                   u8 arg10, u8 arg11, u8 arg12, u8 arg13, s32 arg14, s8 arg15, s32 arg16, u8 arg17, u8 arg18,
                   s32 arg19) {
    struct {
        f32 u00[2];         /* 0x00 = 1 */
        f32 u08[2];         /* 0x08 = 0.02 */
        f32 angB;           /* 0x10, func_15145974 */
        f32 angA;           /* 0x14, func_15145974 */
        f32 u18;            /* 0x18 = 0 */
        f32 u1C[3];         /* 0x1C = 1 */
        f32 pos[3];         /* 0x28 */
        f32 vel[3];         /* 0x34 */
        f32 colour[3];      /* 0x40, D_800A5860 */
        f32 u4C;            /* 0x4C = 0 */
        s32 u50;            /* 0x50 = 0x120 */
        s16 u54;            /* 0x54 = 300 */
        s16 u56;            /* 0x56 = 0x2F */
        u8 u58;             /* 0x58 = 0 */
        s32 u5C;            /* 0x5C = 0 */
        u8 u60[10];         /* 0x60: FF, 0x13, 0.. */
        u8 u6A;             /* 0x6A = 0 */
        u8 *owner;          /* 0x6C */
        u8 ownerKind;       /* 0x70 */
        s16 u72;            /* 0x72 = 1 */
        s16 u74;            /* 0x74 = 0xFF */
        s32 sound;          /* 0x78 */
    } fx;
    struct {
        u8 u00[4];
        f32 u04;            /* 0x04 */
        u8 u08[0x30];
        f32 dir[3];         /* 0x38, func_15146078 */
        u8 u44[0x20];
        s32 u64;            /* 0x64 = arg14 */
        u8 u68[4];          /* 0x68, func_151C50BC */
        f32 u6C;            /* 0x6C = arg6 */
        u8 flags;           /* 0x70 */
        f32 u74[3];         /* 0x74, func_15146078 */
        f32 u80[3];         /* 0x80, func_15146078 */
        f32 u8C;            /* 0x8C = 0 */
        f32 u90;            /* 0x90 = 0 */
        f32 u94;            /* 0x94 = 70 arg7 */
        s32 pos[3];         /* 0x98 */
        f32 dir70[3];       /* 0xA4 */
        s8 uB0;             /* 0xB0 = arg15 */
    } lt;                   /* 0xB4 bytes */
    s32 ptA[3];
    s32 ptB[3];
    s32 hasA;
    s32 hasB;
    u8 *e;
    s32 i;

    hasA = arg4;
    hasB = 0;
    if (arg4) {
        ptA[0] = ((s32 *) a3)[0];
        ptA[1] = ((s32 *) a3)[1];
        ptA[2] = ((s32 *) a3)[2];
    }
    lt.flags = (arg13 ? 4 : 0) | (arg11 ? 1 : 0) | (arg12 ? 2 : 0);
    lt.uB0 = arg15;
    if (a2 != NULL && a3 != NULL) {
        if (!arg4) {
            if (func_15145128(a3, (f32 *) ptA, NULL, NULL) == 0) {
                return;
            }
            hasA = 1;
        }
    } else if (a1 != NULL) {
        if (func_15145128(a1, (f32 *) ptB, NULL, NULL) == 0) {
            return;
        }
        hasB = 1;
    }
    if (func_151C50BC((s32) arg5, (s32 *) &lt, (u8 *) a0, hasB ? ptB : NULL, (s32 *) lt.u68, arg7, arg10, a2,
                      hasA ? ptA : NULL, (s8 *) &lt.flags, 1, arg8, arg9, arg15, arg12, arg13, 0, arg17) == 0) {
        return;
    }
    if (func_15146078(lt.dir, (s32 *) lt.u74, (s32 *) lt.u80) == 0) {
        return;
    }
    lt.u64 = arg14;
    lt.u90 = 0.0f;
    lt.u8C = 0.0f;
    lt.u94 = 70.0f * arg7;
    lt.pos[0] = ((s32 *) a0)[0];
    lt.pos[1] = ((s32 *) a0)[1];
    lt.pos[2] = ((s32 *) a0)[2];
    lt.dir70[0] = lt.dir[0] * 70.0f;
    lt.dir70[1] = lt.dir[1] * 70.0f;
    lt.dir70[2] = lt.dir[2] * 70.0f;
    lt.u6C = arg6;
    lt.flags |= (150.0f < lt.u04) ? 1 : 0;
    fx.u00[0] = 1.0f;
    fx.u00[1] = 1.0f;
    fx.u08[1] = 0.0200000014f;
    fx.u08[0] = 0.0200000014f;
    func_15145974(lt.dir, &fx.angA, &fx.angB);
    fx.u1C[0] = 1.0f;
    fx.u1C[1] = 1.0f;
    fx.u1C[2] = 1.0f;
    fx.u18 = 0.0f;
    ((s32 *) fx.pos)[0] = ((s32 *) a0)[0];
    ((s32 *) fx.pos)[1] = ((s32 *) a0)[1];
    ((s32 *) fx.pos)[2] = ((s32 *) a0)[2];
    fx.vel[0] = lt.dir[0] * arg6;
    fx.vel[1] = lt.dir[1] * arg6;
    fx.vel[2] = lt.dir[2] * arg6;
    ((s32 *) fx.colour)[0] = ((s32 *) D_800A5860)[0];
    ((s32 *) fx.colour)[1] = ((s32 *) D_800A5860)[1];
    ((s32 *) fx.colour)[2] = ((s32 *) D_800A5860)[2];
    fx.u50 = 0x120;
    fx.u54 = 300;
    fx.u56 = 0x2F;
    fx.u58 = 0;
    fx.u5C = 0;
    fx.u60[0] = 0xFF;
    fx.u60[1] = 0x13;
    for (i = 2; i < 9; i++) {
        fx.u60[i] = 0;
    }
    fx.u6A = 0;
    fx.u4C = 0.0f;
    fx.owner = arg9;
    fx.ownerKind = arg9[0x3B];
    fx.u72 = 1;
    fx.u74 = 0xFF;
    if (arg16 != 0) {
        fx.sound = ((u16 (*)(s32, u16, s16, u8, s32, s16, s16, s16, s16, s16)) func_10010F88)(arg16, 0x4650, -500, 0, -1, (s32) fx.pos[0], (s32) fx.pos[1], (s32) fx.pos[2],
                                 1000, 2000);
    } else {
        fx.sound = 0;
    }
    e = (u8 *) func_15132BBC(&fx, 0, 0, 0, 0xB4, arg18, arg19);
    if (e != NULL) {
        memcpy((s32) (e + 0x170), (s32 *) &lt, 0xB4);
    }
}
