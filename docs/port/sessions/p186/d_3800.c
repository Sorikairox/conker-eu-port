void func_15177F90(u8 kind, u8 *pos, s32, s32 x, s32 y, s32 z, s32, s32 span, s32 flag, s32, s32 w6);
void func_15175900(s32, s32 slot, s32 x, s32 y, s32 z, s32, s32 player, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32);
void func_15175514(s32, s32 slot, s32 x, s32 y, s32 z, s32, s32 player, s32, f32, f32);
void func_15175160(s32, s32 slot, s32 x, s32 y, s32 z, s32 player, f32, f32, s32);
void func_1517AF90(f32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_15183E20(s32 arg0);
void func_15183EE4(s32 arg0);
void func_15183F60(s32 arg0, s32 arg1);
s32 func_15184688(u8 *arg0);
void func_1518403C(s32);
extern u8 D_800CC704[];

/* weather_effect_start: P186: starts weather / screen effect `kind` (0..11) in the first free of the 4 slots
 * D_800DDF5C (returns -1 when all are busy). Effect position (x, y, z), a = the effect parameter (colour / id),
 * player view `player` (D_800DBFF0 + player * 0x9A0, +0x3D0 = its camera record), sizes s1..s3 (* 16), last = the
 * last argument of the spawners. Kinds: 0 / 1 func_15177F90 bursts (1 with D_800CC704), 2 / 5 / 6 / 7 / 11
 * func_15175900 particle fields (with their sound / setup calls func_15183E20 / func_1518403C / func_15183EE4),
 * 3 func_15175160 (only when func_15184688 accepts the camera, else -1), 4 / 10 func_15175514 (width s1 * 64),
 * 8 -1, 9 func_1517AF90 at the camera (+0x14..+0x1C, +0x3C) without taking the slot. Other kinds start nothing
 * but still take the slot. Returns the slot index. `unused` is not read. */
s32 func_15183800(s32 x, s32 y, s32 z, s32 a, s32 kind, s32 unused, s32 player, s32 s1, s32 s2, s32 s3, s32 last) {
    s32 slot;
    u8 *cam;

    for (slot = 0; slot < 4; slot++) {
        if (D_800DDF5C[slot] == 0) {
            break;
        }
    }
    if (slot == 4) {
        return -1;
    }
    s1 <<= 4;
    s2 <<= 4;
    s3 <<= 4;
    cam = *(u8 **) ((u8 *) D_800DBFF0 + player * 0x9A0 + 0x3D0);
    switch (kind) {
        case 0:
            func_15177F90(a, NULL, 0xFE, x, y, z, 0, 0x7FFF, 0xFF, 1, 0);
            break;
        case 1:
            func_15177F90(a, D_800CC704, 0xFE, x, y, z, 0, 0x7FFF, 0xFF, 1, 0);
            break;
        case 2:
            func_15183E20(0);
            func_15175900(a, slot, x, y, z, 0x3F, player, 30, 0, 0x30003, 10, 0, 0, 1, 2, 0.8f, 0.5f, last);
            break;
        case 3:
            if (func_15184688(cam) == 0) {
                return -1;
            }
            func_15175160(a, slot, x, y, z, player, 0.8f, 0.5f, last);
            break;
        case 4:
            func_15183F60(7, 10);
            func_15175514(a, slot, x, y, z, s1 * 4, player, 0, 0.8f, 0.5f);
            break;
        case 10:
            func_1518403C(7);
            func_15175514(a, slot, x, y, z, s1 * 4, player, 1, 0.8f, 0.5f);
            break;
        case 11:
            func_1518403C(2);
            func_1518403C(3);
            func_1518403C(4);
            func_1518403C(5);
            func_15175900(a, slot, x, y, z, s1, player, s2, s3, 77, 21, 3, 2, -1, 0, 0.8f, 0.5f, last);
            break;
        case 5:
            func_1518403C(2);
            func_1518403C(3);
            func_1518403C(4);
            func_1518403C(5);
            func_15175900(a, slot, x, y, z, s1, player, s2, s3, 77, 21, 3, 2, -1, 2, 0.8f, 0.5f, last);
            break;
        case 6:
            func_15183EE4(8);
            func_15175900(a, slot, x, y, z, s1, player, s2, s3, 125, 68, 2, 8, -1, 2, 0.8f, 0.5f, last);
            break;
        case 7:
            func_1518403C(6);
            func_15175900(a, slot, x, y, z, s1, player, s2, s3, 77, 20, 0, 6, 0, 2, 0.04f, 0.025f, last);
            break;
        case 8:
            return -1;
        case 9:
            func_1517AF90(*(f32 *) (cam + 0x3C), (s32) *(f32 *) (cam + 0x14), (s32) *(f32 *) (cam + 0x18),
                         (s32) *(f32 *) (cam + 0x1C), a);
            break;
    }
    if (kind != 9) {
        D_800DDF5C[slot] = 1;
    }
    return slot;
}
