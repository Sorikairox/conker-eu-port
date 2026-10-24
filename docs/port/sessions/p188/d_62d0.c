s32 func_15142A5C(u8 *);
void func_151D56F8(u8 *arg0);
s32 func_1514654C(u8 *, u8 *, s32, f32 **, f32 **, s32);
void func_15145EA4(f32 **, f32 **, void *, s32);
void func_151D5724(u8 *, u8 *, void *, void *, void *, u8 *, u8 *, u8 **, u8 **, u8 *);
void func_151D44C4(u8 *, u8, s32);
void func_151D49B8(u8 *, u8 *, s32, u8 *, f32, u8, s32);
void func_151C7320(s32 arg0, u8 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5);
u8 *func_151C284C(u8 *, u8 *, u8 *, u8 *, u8, s32, f32, f32, f32, f32, f32, u8, u8 *, u8, u8, u8, u8, u8, u8, s8, s32, f32, u8, s8, s32, u8, s32);
extern u32 D_800AAEE0[]; /* [2 side] bone matrix byte offset */
extern u8 D_800AAEE8[];  /* [2 side] f32[3] muzzle point */
extern u8 D_800AAF00[];  /* [2 side] f32[3] aim point (with `aimed`) */
extern u8 D_800AAF18[];  /* [2 side] f32[3] second point */
extern u8 D_800AAF30[];  /* [2 side] f32[3] third point (direction = third - second) */
extern u8 D_800AAF48[];  /* [2 side] f32[3] shot start point */
extern f32 D_800AAFD8;   /* func_15145740 parameter */
extern f32 D_800AAFDC;   /* smallest direction component for a side offset */
extern f32 D_800AAFE0;   /* shot parameter (1 / 300) */
extern u8 D_800DCE50;

/*
 * object_gun_fire: P188: fires side `side` (0 / 1) of obj's gun (not while func_15142A5C says it is busy).
 * With a bone matrix (obj +0x1D4) the muzzle, second, third and shot-start points of the side (D_800AAEE8 /
 * D_800AAF18 / D_800AAF30 / D_800AAF48, plus the aim point D_800AAF00 when `aimed`) go to world space by the bone
 * (func_1514654C when an attachment `att` is given, which can refuse, else func_15145EA4); the tracer direction is
 * third - second and, when aimed, the aim direction is aim - muzzle. Without matrices (only when not aimed) the
 * muzzle is the object position +0x14.. + 49 up and 34 to the side (left for side 0) of the direction
 * func_15145740 gave, which also becomes the shot start. Then func_151D5724 (impact / target search), a sound
 * when the object has one (+0x318: func_151D8E18 with a random 11..21 pitch value and voice 1 << +0x23D), and with
 * matrices and a model that is not hidden (+0x74 & 0xF != 15): the muzzle puff (func_151D44C4), the tracer
 * (func_151D49B8) and the shot (func_151C7320), each always when aimed, otherwise only by chance (puff / tracer: 1
 * in 2 and single-player-ish modes D_80082FA0 < 2; shot: random & the D_800DCE50 mask is 0). Returns the projectile
 * func_151C284C creates (speed 300, random life / size, 26 = kind).
 */
s32 func_151C62D0(u8 *obj, u8 side, s32 aimed_, u8 *att, s32 kind, s32 flag, s32 arg6) {
    f32 *src[5];
    f32 *dst[5];
    f32 aim[3];      /* sp328 */
    f32 muzzle[3];   /* sp340 */
    f32 start[3];    /* sp316 */
    f32 second[3];   /* sp268 */
    f32 dir[3];      /* sp256 */
    f32 out280[3];
    f32 out228[3];
    f32 out304[3];
    f32 out292[3];
    u8 *hit244;
    u8 *hit240;
    u8 *bone;
    structEU_151D8E18 snd;
    u8 aimed = aimed_;
    f32 x, z, inv, px, pz, off;
    f32 r1, r2;
    u32 r;
    s32 n, mask;

    if (obj == NULL) {
        return 0;
    }
    if (side >= 2) {
        return 0;
    }
    if (func_15142A5C(obj) != 0) {
        return 0;
    }
    func_151D56F8(obj);
    if (!aimed) {
        func_15145740((struct127 *) obj, (s32) aim, (s32) out280, (s32) out228, D_800AAFD8);
    }
    if (*(u8 **) (obj + 0x1D4) != NULL) {
        bone = *(u8 **) (obj + 0x1D4) + D_800AAEE0[side];
        dst[0] = muzzle;
        dst[1] = second;
        dst[2] = dir;
        dst[3] = start;
        dst[4] = aim;
        src[0] = (f32 *) (D_800AAEE8 + side * 12);
        src[1] = (f32 *) (D_800AAF18 + side * 12);
        src[2] = (f32 *) (D_800AAF30 + side * 12);
        src[3] = (f32 *) (D_800AAF48 + side * 12);
        src[4] = (f32 *) (D_800AAF00 + side * 12);
        if (att != NULL) {
            if (func_1514654C(obj, att, 0, src, dst, aimed ? 5 : 4) == 0) {
                return 0;
            }
        } else {
            func_15145EA4(src, dst, bone, aimed ? 5 : 4);
        }
        dir[0] -= second[0];
        dir[1] -= second[1];
        dir[2] -= second[2];
        if (aimed) {
            aim[0] -= muzzle[0];
            aim[1] -= muzzle[1];
            aim[2] -= muzzle[2];
        }
    } else {
        if (aimed) {
            return 0;
        }
        x = aim[0];
        z = aim[2];
        if (D_800AAFDC < fabsf(x) || D_800AAFDC < fabsf(z)) {
            inv = 1.0f / sqrtf(x * x + z * z);
            pz = z * inv;
            px = -x * inv;
        } else {
            pz = 1.0f;
            px = 0.0f;
        }
        off = side ? 34.0f : -34.0f;
        muzzle[0] = *(f32 *) (obj + 0x14) + off * px;
        muzzle[1] = *(f32 *) (obj + 0x18) + 49.0f;
        muzzle[2] = *(f32 *) (obj + 0x1C) + off * pz;
        start[0] = muzzle[0];
        start[1] = muzzle[1];
        start[2] = muzzle[2];
    }
    func_151D5724(obj, (u8 *) muzzle, aim, out280, out228, (u8 *) out304, (u8 *) out292, &hit244, &hit240,
                  (u8 *) start);
    if (*(u8 **) (obj + 0x318) != NULL) {
        snd.unk0 = 1;
        snd.unk2 = (u32) func_150ADA20() % 11 + 11;
        snd.unk5 = 1 << (*(u8 **) (obj + 0x318))[0x23D];
        func_150ADA20();
        snd.unk4 = 8;
        snd.unk6 = -1;
        func_151D8E18(&snd, 0, 255, 1);
    }
    if (*(u8 **) (obj + 0x1D4) != NULL && (obj[0x74] & 0xF) != 15) {
        if (aimed || (D_80082FA0 < 2 && (func_150ADA20() & 1))) {
            func_151D44C4((u8 *) muzzle, flag, arg6);
        }
        if (aimed || D_80082FA0 < 2) {
            if (func_150ADA20() & 1) {
                func_151D49B8((u8 *) second, (u8 *) dir, (s32) bone, obj, 1.0f, flag, arg6);
            }
        }
        mask = 1;
        for (n = D_800DCE50; n != 0; n--) {
            mask |= 1 << n;
        }
        if (aimed || !(func_150ADA20() & mask)) {
            func_151C7320((s32) obj, side, (s32) muzzle, kind, flag, arg6);
        }
    }
    r1 = func_150ADA68();
    r2 = func_150ADA68();
    r = func_150ADA20();
    return (s32) func_151C284C((u8 *) start, (u8 *) aim, hit244, hit240, 1, 0, 300.0f, D_800AAFE0, r1 * 10.0f + 25.0f,
                               r2 * 150.0f + 400.0f, 50.0f, r % 156 + 100, obj, !aimed, !aimed, !aimed, 8, !aimed, 1,
                               0, 26, 0.0f, 255, -1, 0, flag, arg6);
}
