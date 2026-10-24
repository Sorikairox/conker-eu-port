extern f32 D_8009A5CC; /* 65536 / (2 pi) */
/* IDO's f32 -> u32 conversion (cvt.w.s, then 2^31 offset): -1 for NaN, values <= -1 and >= 2^32 */
#define P210_F2U(v) (((v) > -1.0f && (v) < 4294967296.0f) ? (u32)(v) : 0xFFFFFFFF)

// set_heading_cmd: P210: script command: sets the current object's target heading unk78 (or its heading unk76)
// from the 16-bit value D_800D1890 << 8 | D_800D1891 by mode D_800D1892: 0 heading + value, 1 heading - value,
// 2 value, 3 turn now (unk76 = unk7A = unk78), 4 direction from path point D_800D1890 to point D_800D1891
// (D_800D2104[unk13F]) + D_800D1893 << 8 + 0x4000, 5 random (func_150ADA20), 6 keep the heading, 7 unk76 = object
// unk222's facing + value, 8 unk76 = own facing unk7A.
void func_1507AA48(void) {
    u16 v = (D_800D1890 << 8) | D_800D1891;

    switch (D_800D1892) {
        case 0:
            D_800D154C->unk78 = D_800D154C->unk76 + v;
            break;
        case 1:
            D_800D154C->unk78 = D_800D154C->unk76 - v;
            break;
        case 2:
            D_800D154C->unk78 = v;
            break;
        case 3:
            D_800D154C->unk76 = D_800D154C->unk78;
            D_800D154C->unk7A = D_800D154C->unk78;
            break;
        case 4: {
            u8 *path = (u8 *)D_800D2104[D_800D154C->unk13F];
            s16 *from = (s16 *)(path + D_800D1890 * 8 + 8);
            s16 *to = (s16 *)(path + D_800D1891 * 8 + 8);
            f32 ang = func_150484A0(to[0] - from[0], to[2] - from[2]);

            D_800D154C->unk78 = P210_F2U(ang * D_8009A5CC) + (D_800D1893 << 8) + 0x4000;
            break;
        }
        case 5:
            D_800D154C->unk78 = func_150ADA20();
            break;
        case 6:
            D_800D154C->unk78 = D_800D154C->unk76;
            break;
        case 7:
            D_800D154C->unk76 = D_800CC2D0[D_800D154C->unk222].unk7A + v;
            break;
        case 8:
            D_800D154C->unk76 = D_800D154C->unk7A;
            break;
    }
}
