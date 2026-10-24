f32 func_150484A0(f32, f32);
extern u8 D_800CC9D4[];
extern u8 D_800CC9D8[];
extern u8 D_800CC9DC[];
extern u8 D_800CC734[];
extern u8 D_800CC82C[];
extern u8 D_800CC718[];
extern u8 D_800CC7F2;
extern u8 D_800BEE0C;
extern u8 D_800CC8BA[];
extern u8 D_800CC922[];
extern u8 D_800CC779[];

// script_test_object_value: P183: script condition: reads value D_800D1892 (0..18) of object `idx` (0x32C-byte
// records of D_800CC2D0; some values come from the global object D_800CCA0C or the player's +0x222 object) and
// compares it with D_800D1893 by operator D_800D1891 (0 ==, 1 !=, 2 <, 3 >, 4 <=, 5 >=). Value 6 is the angle
// difference 0..128 (256 per turn) between the object's heading (+0x7A >> 8, - 0x40) and its direction to the
// player D_800D154C; value 9 is 2 when the object's +0xCA0C record has +0x8 and +0x16 set. Returns 1 when true.
// For a value kind above 18 the asm compares an unset stack slot (kept: `v` uninitialised there).
s32 func_15078A60(s32 idx) {
    s32 v;
    s32 off = idx * 0x32C;
    u8 *obj;
    u8 *rec;
    u8 heading;
    u8 diff;

    switch (D_800D1892) {
        case 0:
            v = *(f32 *) ((u8 *) D_800CC30C + off);
            break;
        case 1:
            v = *(s32 *) (D_800CC9D4 + off);
            break;
        case 2:
            v = *(s32 *) (D_800CC9D8 + off);
            break;
        case 3:
            v = *(s32 *) (D_800CC9DC + off);
            break;
        case 4:
            v = *(f32 *) ((u8 *) D_800CC2E8 + off);
            break;
        case 5:
            v = *(f32 *) (D_800CC734 + off);
            break;
        case 6:
            obj = (u8 *) D_800CC2D0 + off;
            heading = (*(u16 *) (obj + 0x7A) >> 8) - 0x40;
            diff = (u32) (func_150484A0(*(f32 *) (obj + 0x14) - *(f32 *) ((u8 *) D_800D154C + 0x14),
                                        *(f32 *) (obj + 0x1C) - *(f32 *) ((u8 *) D_800D154C + 0x1C)) *
                          40.743664f) -
                   heading;
            v = diff;
            if (diff > 0x80) {
                v = 0x100 - diff;
            }
            break;
        case 7:
            v = D_800CC82C[off];
            break;
        case 8:
            v = D_800CC3D4[off];
            break;
        case 9:
            rec = *(u8 **) ((u8 *) &D_800CCA0C + off);
            v = 0;
            if (*(s16 *) (rec + 0x8) != 0 && rec[0x16] != 0) {
                v = 2;
            }
            break;
        case 10:
            v = *(f32 *) (D_800CC718 + off);
            break;
        case 11:
            v = D_800CCA0C[0x78];
            break;
        case 12:
            v = D_800CCA0C[0x7D];
            break;
        case 13:
            v = D_800CC7F2;
            break;
        case 14:
            v = D_800BEE0C;
            break;
        case 15:
            v = D_800CC2D4[((u8 *) D_800D154C)[0x222] * 0x32C];
            break;
        case 16:
            v = D_800CC8BA[off];
            break;
        case 17:
            v = D_800CC922[((u8 *) D_800D154C)[0x222] * 0x32C];
            break;
        case 18:
            v = D_800CC779[off];
            break;
    }
    if ((D_800D1891 == 0 && v == D_800D1893) || (D_800D1891 == 1 && v != D_800D1893) ||
        (D_800D1891 == 2 && v < D_800D1893) || (D_800D1891 == 3 && D_800D1893 < v) ||
        (D_800D1891 == 4 && !(D_800D1893 < v)) || (D_800D1891 == 5 && !(v < D_800D1893))) {
        return 1;
    }
    return 0;
}
