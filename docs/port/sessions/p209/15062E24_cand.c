extern u8 *D_800C5758[]; /* per object type: 12-byte texture entries, u16 size at +8 / +0xA */
void func_15094EC8(u8 *, s32 *, s32, f32, s32, s32);

// type_texture_scroll_apply: for every live object (+0x0) of `type` (+0x4) with +0x2FA set and a display list
// for the current screen (+0x28C[D_800BE9C0]), calls func_15094EC8 on entry `dl` (16-byte steps) of it with the
// type's texture-command table D_800C6360[type] at `cmd`, `arg2`, the amount `amount`, and the size of texture
// `tex` of D_800C5758[type] (doubled when `twice`).
void func_15062E24(s32 type, s32 dl, s32 arg2, s32 cmd, s32 amount, s32 tex, s32 twice) {
    s32 *table;
    struct127 *o;
    u8 *entry;
    u8 *list;
    s32 w;
    s32 h;
    s32 i;

    if (D_800C6360[type] == 0) {
        return;
    }
    for (i = 0, o = D_800CC2D0; i < 25; i++, o++) {
        if (*(s32 *) o == 0 || type != *((u8 *) o + 4) || o->unk2FA == 0) {
            continue;
        }
        entry = D_800C5758[type] + tex * 12;
        w = *(u16 *) (entry + 8);
        h = *(u16 *) (entry + 0xA);
        if (twice) {
            w *= 2;
            h *= 2;
        }
        list = ((u8 **) &D_800CC2D0[i].unk28C)[D_800BE9C0];
        if (list != NULL) {
            table = (s32 *) D_800C6360[type];
            func_15094EC8(list + dl * 16, &table[cmd], arg2, (f32) amount, h, w);
        }
    }
}
