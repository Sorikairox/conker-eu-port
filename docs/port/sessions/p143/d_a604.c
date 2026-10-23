extern s32 (*D_8008D940[])(u8 *, u8 *, s32);
// effect_follow_bone: update handler (D_8008A058 slot 2) that keeps an effect attached to a model bone. The
// attachment at +0x170 holds two local points (+0x170, +0x17C), the model (+0x188, looked up once from the id
// +0x18D with func_15083E90), the bone (+0x18C) and an optional visibility check (+0x18E, index into D_8008D940,
// -1 = none). Ends (0) when the model is missing, gone (+0) or reused for another id (+0x3B); a failing check also
// ends it, a hidden one (*visible == 0) skips the update. With bone matrices (+0x1D4) both points are transformed
// to +0x34 and +0x40 and flag 2 set (flag 4 cleared); without them flag 2 is cleared.
s32 func_1518A604(u8 *fx) {
    u8 *att = fx + 0x170;
    u8 *model;
    u8 *bones;
    f32 (*mtx)[4];
    s32 check;
    u8 visible;

    if (*(u8 **)(fx + 0x188) == NULL) {
        model = (u8 *)func_15083E90(att[0x1D]);
        *(u8 **)(att + 0x18) = model;
        if (model == NULL) {
            return 0;
        }
    }
    model = *(u8 **)(att + 0x18);
    if (*(s32 *)model == 0 || att[0x1D] != model[0x3B]) {
        return 0;
    }
    check = *(s8 *)(att + 0x1E);
    if (check != -1) {
        if (D_8008D940[check](fx, &visible, check) == 0) {
            return 0;
        }
        if (!visible) {
            return 1;
        }
        model = *(u8 **)(att + 0x18);
    }
    bones = *(u8 **)(model + 0x1D4);
    if (bones != NULL) {
        mtx = (f32 (*)[4])(bones + (att[0x1C] << 6));
        func_150A7E40(mtx, *(f32 *)(att + 0x0), *(f32 *)(att + 0x4), *(f32 *)(att + 0x8),
                      (f32 *)(fx + 0x34), (f32 *)(fx + 0x38), (f32 *)(fx + 0x3C));
        func_150A7E40(mtx, *(f32 *)(att + 0xC), *(f32 *)(att + 0x10), *(f32 *)(att + 0x14),
                      (f32 *)(fx + 0x40), (f32 *)(fx + 0x44), (f32 *)(fx + 0x48));
        *(s32 *)(fx + 0x58) |= 2;
        *(s32 *)(fx + 0x58) &= ~4;
    } else {
        *(s32 *)(fx + 0x58) &= ~2;
    }
    return 1;
}
