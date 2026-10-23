s32 func_15081A90(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
void func_1502ED88(u8 *, s32, s32, s32, s32, s32, s32);
s32 func_1505D024(struct127 *, s32, u16, s32);
// tether_beam_update: update handler (D_8008A058 slot 29) of a beam from a bone of a source object (+0x110, id
// +0x114; gone when +0x3B differs, +0 is clear or +4 is 0xFF) to a target object (+0x118, id +0x11C). Ends (0)
// when either object is gone or the source's +0x94 flags hit the beam kind's mask D_800A1A0C[+0x11D]. The start
// is the kind's bone point (D_800A19C0 / bone D_800A1A08) of the source skeleton, the end the target position;
// +0x140 / +0x14C / +0x150 get the normalised direction, its length and the second func_15145128 output, and bit 0
// of +0x128 says whether that worked. Width (+0x2C) and alpha (+0x5C) pulse with two phases (+0x120, +0x124). A
// valid beam moves its sound / light (+0x13C) to the start and is ray cast (func_15081A90, bounds only, filter 4);
// an object hit gets tinted and animation 0xA0038 with the source's slot. Otherwise the light is hidden.
s32 func_150EF90C(u8 *fx) {
    u8 *st = fx + 0x110;
    u8 *src = *(u8 **)(fx + 0x110);
    u8 *dst = *(u8 **)(fx + 0x118);
    u8 *bones;
    u8 *p;
    s16 *pos;
    s32 kind;
    s32 hit[0x19];

    if (fx[0x114] != src[0x3B] || *(s32 *)src == 0 || src[4] == 0xFF) {
        return 0;
    }
    if (st[0xC] != dst[0x3B] || *(s32 *)dst == 0) {
        return 0;
    }
    if (D_800A1A0C[st[0xD]] & *(s32 *)(src + 0x94)) {
        return 0;
    }
    st[0x18] &= ~1;
    bones = *(u8 **)(src + 0x1D4);
    if (bones != NULL) {
        kind = st[0xD];
        func_15143134(&D_800A19C0[kind], fx + 0x34, bones + (D_800A1A08[kind] << 6));
        *(f32 *)(fx + 0x40) = *(f32 *)(dst + 0x14);
        *(f32 *)(fx + 0x44) = *(f32 *)(dst + 0x18);
        *(f32 *)(fx + 0x48) = *(f32 *)(dst + 0x1C);
        *(f32 *)(st + 0x30) = *(f32 *)(fx + 0x40) - *(f32 *)(fx + 0x34);
        *(f32 *)(st + 0x34) = *(f32 *)(fx + 0x44) - *(f32 *)(fx + 0x38);
        *(f32 *)(st + 0x38) = *(f32 *)(fx + 0x48) - *(f32 *)(fx + 0x3C);
        if (func_15145128((f32 *)(st + 0x30), (f32 *)(st + 0x30), (f32 *)(st + 0x3C), (f32 *)(st + 0x40)) != 0) {
            st[0x18] |= 1;
        }
    }
    *(f32 *)(st + 0x10) += 0.16000001f * D_800BE9A4;
    *(f32 *)(st + 0x10) = func_15144B68(*(f32 *)(st + 0x10));
    *(f32 *)(fx + 0x2C) = sinf(*(f32 *)(st + 0x10)) * 5.0f + 16.0f;
    *(f32 *)(st + 0x14) += 0.16000001f * D_800BE9A4;
    *(f32 *)(st + 0x14) = func_15144B68(*(f32 *)(st + 0x14));
    fx[0x5C] = (u32)(sinf(*(f32 *)(st + 0x14)) * 25.0f + 230.0f);
    if (st[0x18] & 1) {
        p = *(u8 **)(st + 0x2C);
        if (p != NULL) {
            (*(u8 **)(p + 0x14))[9] = 0;
            pos = (s16 *)(*(u8 **)(*(u8 **)(st + 0x2C) + 0x14) + 0xE);
            pos[0] = *(f32 *)(fx + 0x34);
            pos[1] = *(f32 *)(fx + 0x38);
            pos[2] = *(f32 *)(fx + 0x3C);
        }
        func_15081A90((struct127 *)src, *(f32 *)(fx + 0x34), *(f32 *)(fx + 0x38), *(f32 *)(fx + 0x3C),
                      *(f32 *)(st + 0x30), *(f32 *)(st + 0x34), *(f32 *)(st + 0x38), (u8 *)hit, *(f32 *)(st + 0x3C), 1,
                      0, 1, 4, 0, 0);
        if (((u8 *)hit)[0x59] >= 2) {
            func_1502ED88(*(u8 **)hit, 0xFF, 0, 0, 0x90, 0, 1);
            func_1505D024(*(struct127 **)hit, 0xA0038, 0, (s32)(src - (u8 *)D_800CC2D0) / 0x32C);
        }
    } else {
        p = *(u8 **)(st + 0x2C);
        if (p != NULL) {
            (*(u8 **)(p + 0x14))[9] = 1;
        }
    }
    return 1;
}
