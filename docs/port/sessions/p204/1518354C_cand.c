/* P204 */
extern u8 D_800DE284[];
extern s32 D_8008D3F0;
extern s32 D_800DE290;
f32 func_151834C8(s32, s32);

// water_wave_push: how strongly wave slot `slot` (0..39) of water `water` pushes player pl: 0 when the player
// rises faster than 3 (+0x28), is more than 300 above / below the slot's wave surface (model height +0x12 plus
// the profile sample D_800DE290[water][slot] +8 / 16), or lies outside the water's box (the player's offset from the
// model origin, moved down by the type's depth +0x10: z in [+0xC, 0], x in [0, +0xE]). Otherwise the type's push
// strength (s8 +0x16) when the player's own wave slot (func_151834C8 of z) is `slot`, 4 / 7 of it for a
// neighbouring slot, else 0. Water types: D_8008D3F0 (0x18 bytes) indexed by D_800DE284[water].
s32 func_1518354C(struct127 *pl, s32 slot, s32 water) {
    u8 *kind = &D_800DE284[water];
    u8 *type;
    u8 *model;
    f32 surface;
    f32 mtx[4][4];
    f32 dx;
    f32 dz;
    f32 ox;
    f32 oy;
    f32 oz;
    s32 own;
    s32 push;

    if (pl->unk28 > 3.0f) {
        return 0;
    }
    type = (u8 *) &D_8008D3F0 + *kind * 0x18;
    model = (u8 *) D_800DBEF4 + *(s16 *) (type + 0x12) * 0xA0;
    surface = *(f32 *) (((u8 **) &D_800DE290)[water] + slot * 12 + 8) * 0.0625f + (f32) *(s16 *) (model + 0x12);
    if (pl->y_position < surface - 300.0f || surface + 300.0f < pl->y_position) {
        return 0;
    }
    dx = pl->x_position - (f32) *(s16 *) (model + 0x10);
    dz = pl->z_position - (f32) *(s16 *) (model + 0x14);
    func_150A8050(mtx, 0.0f, (f32) *(s16 *) (type + 0x10), 0.0f);
    func_150A7E40(mtx, dx, 0.0f, dz, &ox, &oy, &oz);
    type = (u8 *) &D_8008D3F0 + *kind * 0x18;
    if (oz > 0.0f || oz < (f32) *(s16 *) (type + 0xC) || ox < 0.0f || ox > (f32) *(s16 *) (type + 0xE)) {
        return 0;
    }
    own = (s32) func_151834C8((s32) oz, water);
    push = *(s8 *) ((u8 *) &D_8008D3F0 + *kind * 0x18 + 0x16);
    if (slot == own) {
        return push;
    }
    if (slot == own + 1 || slot + 1 == own) {
        return push * 4 / 7;
    }
    return 0;
}
