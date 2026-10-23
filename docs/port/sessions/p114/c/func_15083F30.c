s32 func_1503D950(s32, s32);
s32 func_1503DA64(s32, s32);
struct127 *func_1505ED34(void);
void func_150615DC(struct127 *arg0);
s32 func_1515D9F0(s32);
s32 func_1515D9B0(void);
void func_15083E20(u8 *, u16, u8 *);
void func_15083C3C(s32 slot, s32 type, s32 arg2);
s32 func_15083D54(struct127 *, u16, s32, f32);

// object_spawn_attached: setup command type 0 (func_15083568): makes a new object of kind `kind` in a free slot
// (func_1505ED34; no NULL check, as the asm) attached to owner: +0x65 = owner slot + 1, +0x3B = 0xFF - own slot,
// +0x5C = mode, +0xAB = arg3, +0 = arg4, +0xAC = flags (bit 0: +0xF8 |= 0x4000 and +0x270 = kind record +0xE * scale;
// bit 1: passed to func_15083D54), +0x101 = keepScale (0: scales 1.0, else the owner's), copies of the owner's
// +0x66 (without bit 4) and +0x1DD..+0x1E2 (+0x1DF takes the owner's +0x1DE, as the asm does), per-camera slots
// +0x304.. from func_1515D9F0(1). While D_800C35EA == 1 the D_800C3638 byte is 0 during the kind setup. Returns it.
s32 func_15083F30(struct127 *owner, u8 mode, u8 kind, s32 arg3, s32 arg4, s32 flags, s32 keepScale, s32 arg7,
                         f32 arg8) {
    u8 *ow = (u8 *) owner;
    u8 *o;
    s32 *slot;
    s32 i;
    s32 flag2;
    s32 single;

    func_1503DA64(kind, 0);
    func_1503D950(kind, 0);
    o = (u8 *) func_1505ED34();
    o[0x3B] = 0xFF - (o - (u8 *) D_800CC2D0) / 0x32C;
    o[0xAB] = arg3;
    *(s32 *) o = arg4;
    func_150615DC((struct127 *) o);
    o[0x232] = 1;
    o[0x1CA] = 1;
    o[0x125] = 0xFF;
    o[0x65] = (ow - (u8 *) D_800CC2D0) / 0x32C + 1;
    *(s32 *) (o + 0x5C) = mode;
    o[0x123] = 1;
    o[4] = kind;
    o[0x66] = ow[0x66] & ~0x10;
    o[0x1DD] = ow[0x1DD];
    o[0x1DE] = ow[0x1DE];
    o[0x1DF] = ow[0x1DE];
    o[0x1E0] = ow[0x1E0];
    o[0x1E1] = ow[0x1E1];
    o[0x1E2] = ow[0x1E2];
    if (keepScale == 0) {
        *(f32 *) (o + 0x14C) = 1.0f;
        *(f32 *) (o + 0x150) = 1.0f;
        *(f32 *) (o + 0x154) = 1.0f;
        *(f32 *) (o + 0x158) = 1.0f;
    } else {
        *(f32 *) (o + 0x14C) = *(f32 *) (ow + 0x14C);
        *(f32 *) (o + 0x150) = *(f32 *) (ow + 0x150);
        *(f32 *) (o + 0x154) = *(f32 *) (ow + 0x154);
        *(f32 *) (o + 0x158) = *(f32 *) (ow + 0x158);
    }
    o[0x101] = keepScale;
    o[0xAC] = flags;
    func_1503DA64(kind, 0);
    if (flags & 1) {
        *(s32 *) (o + 0xF8) |= 0x4000;
        *(f32 *) (o + 0x270) = (f32) *(u16 *) ((u8 *) D_800D1C90[kind] + 0xE) * *(f32 *) (o + 0x14C);
    }
    flag2 = (flags & 2) ? 1 : 0;
    slot = (s32 *) (o + 0x304);
    for (i = 0; i <= D_80082FA0; i++) {
        slot[i] = func_1515D9F0(1);
    }
    if (slot[i - 1] != 0) {
        o[0x301] = 1;
    }
    *(s32 *) (o + 0x314) = func_1515D9B0();
    single = D_800C35EA == 1;
    if (single) {
        D_800C3638 = 0;
    }
    func_15083E20(o, kind, NULL);
    func_15083C3C((o - (u8 *) D_800CC2D0) / 0x32C, kind, 1);
    func_15083D54((struct127 *) o, arg7, flag2, arg8);
    if (single) {
        D_800C3638 = 1;
    }
    return (s32) o;
}
