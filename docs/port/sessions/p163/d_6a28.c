s32 func_15142A5C(u8 *);
void func_151D56F8(u8 *arg0);
void func_15145EA4(f32 **, f32 **, void *, s32);
void func_151D44C4(u8 *, u8, s32);
void func_151D49B8(u8 *, u8 *, s32, u8 *, f32, u8, s32);
void func_151C7320(s32 arg0, u8 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5);
void func_150F79F0(f32 *, void *, void *, void *, u8, u8 *, f32, f32, f32, u8 *, u8, u8, u8, u8, s32, s8, s32, u8, u8, s32);
extern u32 D_800AAEE0[];  /* [2 kind] bone matrix byte offset */
extern u8 D_800AAEE8[];   /* [2 kind] f32[3] muzzle point */
extern u8 D_800AAF18[];   /* [2 kind] f32[3] second point */
extern u8 D_800AAF30[];   /* [2 kind] f32[3] third point (direction = third - second) */
extern f32 D_800AAFE4;    /* flash position: fraction of the way from the muzzle to the linked record's point */
extern f32 D_800AAFE8;
extern f32 D_800AAFEC;

// object_muzzle_fire: for point kind arg1 (0 / 1) of obj (not while func_15142A5C says it is busy), moves the
// kind's three D_800AAEE8 / D_800AAF18 / D_800AAF30 points to world space by the bone matrix, spawns the muzzle
// puff (func_151D44C4), the tracer from the second point along (third - second) (func_151D49B8) and the shot
// (func_151C7320); when the object's link 0x1B record is active (+0x9C bit 0) with a light at +0x91, spawns its
// light effect (func_150F79F0) from the muzzle with a copy of the record's 0x64-byte light block whose position
// (+0x2C) is the record's point (+0x40), or for light kinds >= 2 part of the way from the muzzle to it
void func_151C6A28(u8 *obj, u8 arg1, u8 arg2, s32 arg3) {
    f32 *src[3];
    f32 *dst[3];
    u8 *bone;
    f32 dir[3];
    f32 second[3];
    f32 muzzle[3];
    struct_eu_link *link;
    u8 *rec;
    u8 *light;
    f32 at[3];
    u8 blk[0x64];
    s32 i;

    if (obj == NULL || arg1 >= 2) {
        return;
    }
    if (func_15142A5C(obj) != 0) {
        return;
    }
    func_151D56F8(obj);
    if (*(u8 **)(obj + 0x1D4) == NULL) {
        return;
    }
    src[0] = (f32 *)(D_800AAEE8 + arg1 * 12);
    src[1] = (f32 *)(D_800AAF18 + arg1 * 12);
    src[2] = (f32 *)(D_800AAF30 + arg1 * 12);
    dst[0] = muzzle;
    dst[1] = second;
    dst[2] = dir;
    bone = *(u8 **)(obj + 0x1D4) + D_800AAEE0[arg1];
    func_15145EA4(src, dst, bone, 3);
    dir[0] -= second[0];
    dir[1] -= second[1];
    dir[2] -= second[2];
    func_151D44C4(muzzle, arg2, arg3);
    func_151D49B8((u8 *)second, (u8 *)dir, (s32)bone, obj, 1.0f, arg2, arg3);
    func_151C7320((s32)obj, arg1, (s32)muzzle, -1, arg2, arg3);
    if (func_1514F250(*(struct_eu_link **)(obj + 0x2F4), 0x1B, &link) == 0) {
        return;
    }
    rec = *(u8 **)((u8 *)link + 0x10);
    if (!(rec[0x9C] & 1)) {
        return;
    }
    if (rec[0x91] == 0) {
        return;
    }
    light = rec + 0x38;
    if (light[0x59] >= 2) {
        at[0] = (*(f32 *)(light + 8) - muzzle[0]) * D_800AAFE4 + muzzle[0];
        at[1] = (*(f32 *)(light + 0xC) - muzzle[1]) * D_800AAFE4 + muzzle[1];
        at[2] = (*(f32 *)(light + 0x10) - muzzle[2]) * D_800AAFE4 + muzzle[2];
    } else {
        at[0] = *(f32 *)(light + 8);
        at[1] = *(f32 *)(light + 0xC);
        at[2] = *(f32 *)(light + 0x10);
    }
    for (i = 0; i < 0x64; i++) {
        blk[i] = light[i];
    }
    *(f32 *)(blk + 0x2C) = at[0];
    *(f32 *)(blk + 0x30) = at[1];
    *(f32 *)(blk + 0x34) = at[2];
    func_150F79F0(muzzle, NULL, NULL, NULL, 0, blk, D_800AAFE8, D_800AAFEC, 500.0f, obj, 0, (light[0x59] < 2) ? 1 : 0, 1,
                  0, 0x1A, -1, 0, 1, arg2, arg3);
}
