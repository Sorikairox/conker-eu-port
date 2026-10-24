extern f32 *D_8009002C[]; /* P216: per-mouth point (2 entries) */
extern u8 *D_80090034[];  /* P216: per-mouth bone index (2 entries) */
s32 func_15081A90(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
void func_15063A54(struct127 *);
s32 func_151D5FC8(struct127 *obj, f32 *out, f32 *dir, s32 arg3, s32 arg4, f32 *point, u8 bone);
// mouth_aim_ray: P216: for mouth `which` (0 / 1, table D_8009002C point + D_80090034 bone): the mouth point and
// aim direction (func_151D5FC8), the impact / target search (func_151D5724, two result pointers, NULL = use the
// mouth point / the direction), then the control block (obj +0x31C) gets flag +0x109 = 1 and the far point
// +0xB8 = hitA + hitB * 9999. The segment from the mouth to that point is normalised (func_15145128) and, when it has
// a length, cast as a ray (func_15081A90, result at control +0xB0, range 1.01 * length). Ends with func_15063A54.
// Callers (func_15063AA0, asm) ignore v0.
void func_151D5DA8(struct127 *obj, u8 which) {
    f32 mouth[3];
    f32 dir[3];
    f32 sp94[3];
    f32 sp88[3];
    f32 sp7C[3];
    f32 sp70[3];
    f32 *hitA;
    f32 *hitB;
    f32 seg[3];
    f32 len;
    u8 *ctl;

    func_151D5FC8(obj, mouth, dir, (s32)sp94, (s32)sp88, D_8009002C[which], *D_80090034[which]);
    func_151D5724((u8 *)obj, (u8 *)mouth, (struct17 *)dir, (struct17 *)sp94, (struct17 *)sp88, (u8 *)sp7C,
                  (u8 *)sp70, (u8 **)&hitA, (u8 **)&hitB, NULL);
    ((u8 *)obj->unk31C)[0x109] = 1;
    if (hitA == NULL) {
        hitA = mouth;
    }
    if (hitB == NULL) {
        hitB = dir;
    }
    *(f32 *)((u8 *)obj->unk31C + 0xB8) = hitA[0] + hitB[0] * 9999.0f;
    *(f32 *)((u8 *)obj->unk31C + 0xBC) = hitA[1] + hitB[1] * 9999.0f;
    *(f32 *)((u8 *)obj->unk31C + 0xC0) = hitA[2] + hitB[2] * 9999.0f;
    ctl = (u8 *)obj->unk31C;
    if (ctl[0x109] != 0) {
        seg[0] = *(f32 *)(ctl + 0xB8) - mouth[0];
        seg[1] = *(f32 *)((u8 *)obj->unk31C + 0xBC) - mouth[1];
        seg[2] = *(f32 *)((u8 *)obj->unk31C + 0xC0) - mouth[2];
        if (func_15145128(seg, seg, &len, NULL) != 0) {
            func_15081A90(obj, mouth[0], mouth[1], mouth[2], seg[0], seg[1], seg[2], (u8 *)obj->unk31C + 0xB0,
                          len * 1.01f, 0, 0, 0, -1, 0, 0);
        }
    }
    func_15063A54(obj);
}
