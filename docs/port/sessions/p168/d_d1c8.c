void func_1516D63C(u8 *, f32 *, f32 *, s32);
void func_1501A764(s32 arg0, f32 x, f32 y, f32 z, f32 *sx, f32 *sy, f32 *sz);
extern u8 D_8009090C[]; /* box sprite header: u16 width +6, height +8 */
extern u8 D_8009092C[]; /* pointer sprite header: u16 width +6, height +8 */
extern u8 D_800CC730[]; /* per-player records (0x32C bytes): f32 heading at +0 */

// text_box_place: screen position of a text box (+0x5C / +0x60, copied to +0x40 / +0x44) and the angle +0x58 of
// its pointer (towards the speaker). Descriptor flag 0x8000: position from the descriptor's percentages (+0x18 /
// +0x1C words point at f32 x / y in %, +0x20 at the pointer angle in %, 55..125 degrees) scaled to the viewport
// (D_800BE628 +4 / +8), kept on screen by func_1516D63C when flag 0x10000 is set. Otherwise the speaker's world
// point (descriptor +0xC..+0x14) projected once (func_1501A764) and the angle from the player's heading relative to
// the camera (D_800DBFF0 +0x37C), always kept on screen. +0x50 / +0x54: the pointer's corner.
void func_1516D1C8(u8 *box) {
    u8 *t;
    u8 *vp;
    f32 a;
    f32 sx;
    f32 sy;
    f32 sz;
    s32 ox;
    s32 oy;

    t = *(u8 **) (box + 0x10);
    if (*(s32 *) t & 0x8000) {
        vp = (u8 *) D_800BE628;
        *(f32 *) (box + 0x5C) = *(f32 *) (vp + 4) * ((*(f32 **) (t + 0x18))[0] * 0.01f);
        vp = (u8 *) D_800BE628;
        *(f32 *) (box + 0x60) = *(f32 *) (vp + 8) * (1.0f - (*(f32 **) (t + 0x1C))[0] * 0.01f);
        a = (*(f32 **) (t + 0x20))[0] * 0.01f;
        if (a < 0.0f) {
            a = 0.0f;
        } else if (1.0f < a) {
            a = 1.0f;
        }
        *(f32 *) (box + 0x58) = (70.0f * a + 55.0f) * 0.0174532924f;
        if (*(s32 *) t & 0x10000) {
            func_1516D63C(box, (f32 *) (box + 0x5C), (f32 *) (box + 0x60), (s32) (box + 0x58));
        }
    } else {
        func_1501A764(0, *(f32 *) (t + 0xC), *(f32 *) (t + 0x10), *(f32 *) (t + 0x14), &sx, &sy, &sz);
        if (box[0x1F] == 0) {
            *(f32 *) (box + 0x64) = sx;
            *(f32 *) (box + 0x68) = sy;
            box[0x1F] = 1;
            *(f32 *) (box + 0x6C) =
                *(f32 *) (D_800CC730 + t[9] * 0x32C) - *(f32 *) ((u8 *) D_800DBFF0 + 0x37C) - 180.0f;
        }
        a = *(f32 *) (box + 0x6C);
        *(f32 *) (box + 0x5C) = *(f32 *) (box + 0x64);
        *(f32 *) (box + 0x60) = *(f32 *) (box + 0x68);
        if (a < 0.0f) {
            a += 360.0f;
        }
        if (180.0f < a) {
            a -= 360.0f;
        }
        if (90.0f < a) {
            a = 180.0f - a;
        } else if ((f64) a < -90.0) {
            a = -180.0f - a;
        }
        *(f32 *) (box + 0x58) = (70.0f * (a / -180.0f + 0.5f) + 55.0f) * 0.0174532924f;
        func_1516D63C(box, (f32 *) (box + 0x5C), (f32 *) (box + 0x60), (s32) (box + 0x58));
    }
    *(f32 *) (box + 0x40) = *(f32 *) (box + 0x5C);
    *(f32 *) (box + 0x44) = *(f32 *) (box + 0x60);
    ox = *(f32 *) (box + 0x38) / (f32) *(u16 *) (D_8009090C + 6) * (f32) *(u16 *) (D_8009092C + 6) * 0.25f;
    oy = *(f32 *) (box + 0x3C) / (f32) *(u16 *) (D_8009090C + 8) * (f32) *(u16 *) (D_8009092C + 8) * 0.5f;
    *(f32 *) (box + 0x50) =
        (s32) (cosf(*(f32 *) (box + 0x58) + 3.14159274f) * (*(f32 *) (box + 0x38) * 0.5f) * 1.15f
               + *(f32 *) (box + 0x5C) - (f32) ox);
    *(f32 *) (box + 0x54) =
        sinf(*(f32 *) (box + 0x58) + 3.14159274f) * (*(f32 *) (box + 0x3C) * 0.5f) * 1.04f + *(f32 *) (box + 0x60)
        - (f32) oy;
}
