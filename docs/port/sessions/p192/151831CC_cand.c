// water_mesh_wave_update: rebuilds a water object's world vertices for this frame's buffer (+0x20[D_800BE9C0]) from
// its model vertices (+0x28, 16 bytes each): the vertex z picks a slot of the wave profile D_800DE290[+0x3C]
// (func_151834C8, 0..39, linear blend of neighbouring samples), whose height / 16 is added to the vertex y; the
// vertex goes through a translation by -D_8008D400 (the water type's depth) and is offset by the object position
// +0x10. The vertex count comes from the type's model record (D_800DBEF4[D_8008D402].+0x16).
extern s16 D_8008D400[][12];
f32 func_151834C8(s32 arg0, s32 arg1);


void func_151831CC(u8 *obj) {
    f32 mtx[4][4];
    f32 ox, oy, oz;
    s32 water = *(s32 *)(obj + 0x3C);
    u8 *kind = &D_800DE284[water];
    s16 *out = *(s16 **)(obj + 0x20 + D_800BE9C0 * 4);
    s32 i;
    s32 off;
    f32 pos;
    s32 slot;
    s32 next;
    f32 frac;
    f32 a;
    f32 b;
    s16 *v;

    func_150A8050(mtx, 0.0f, (f32)-D_8008D400[*kind][0], 0.0f);
    for (i = 0, off = 0; i < *(u16 *)((u8 *)&D_800DBEF4[D_8008D400[*kind][1]] + 0x16); i++, off += 0x10, out += 8) {
        pos = func_151834C8(*(s16 *)(*(u8 **)(obj + 0x28) + off + 4), water);
        slot = (s32)pos;
        next = slot + 1;
        if (next >= 40) {
            next = 39;
        }
        frac = pos - (f32)slot;
        a = *(f32 *)(((u8 **)&D_800DE290)[water] + slot * 12 + 8) * (1.0f - frac);
        b = *(f32 *)(((u8 **)&D_800DE290)[water] + next * 12 + 8) * frac;
        v = (s16 *)(*(u8 **)(obj + 0x28) + off);
        func_150A7E40(mtx, (f32)v[0], (f32)(v[1] + ((s32)(b + a) >> 4)), (f32)v[2], &ox, &oy, &oz);
        out[0] = (s32)((f32)*(s16 *)(obj + 0x10) + ox);
        out[1] = (s32)((f32)*(s16 *)(obj + 0x12) + oy);
        out[2] = (s32)((f32)*(s16 *)(obj + 0x14) + oz);
    }
}
