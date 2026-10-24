// obj_yaw_clamp_to_track: keeps the object's yaw (+0x76) within 0x2400 of a quarter turn (+0x4000) past player
// `player`'s track direction (record D_80087640 + player * 0x84, vector +0x10 / +0xC, func_1505A630). Nothing without
// player records. Returns func_1505A630's raw result (the asm leaves v0 unset without records; the one caller
// ignores it).
void func_150882C4(u8 player, struct127 *obj) {
    struct_eu_80087640 *rec;
    s32 r;
    u16 dir;
    u16 diff;

    if (D_80087640 == NULL) {
        return;
    }
    rec = &D_80087640[player];
    r = func_1505A630(*(f32 *) ((u8 *) rec + 0x10), *(f32 *) ((u8 *) rec + 0xC), 0);
    dir = r + 0x4000;
    diff = dir - *(u16 *) ((u8 *) obj + 0x76);
    if (diff & 0x8000) {
        if (diff < 0xDBFF) {
            *(u16 *) ((u8 *) obj + 0x76) = dir + 0x2400;
        }
    } else if (diff > 0x2400) {
        *(u16 *) ((u8 *) obj + 0x76) = dir - 0x2400;
    }
    
}
