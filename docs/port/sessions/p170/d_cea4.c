void func_15042BC4(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3);
Gfx *func_15041A9C(Gfx *arg0, f32 arg1, f32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8, f32 arg9, s32 argA);
extern Gfx D_80085D30[]; /* text render state display list */
extern s32 D_800BEFC4;  /* display list capacity, in Gfx commands */

// text_box_draw_text: draws a text box's string (+0x24, lines split at '\n', leading newlines skipped) from the
// box's corner (+0x50 / +0x54 minus +0x30 / +0x34). Each line is measured (func_15042BC4: width, height, advance)
// and printed by func_15041A9C at 4096 x 4096 scale with its length: descriptor flag 0x20000 centres it on +0x30,
// flag 0x40000 prints it white one pixel right, flag 4 in colour r / g / b, otherwise black one pixel right.
// Returns the original gfx (drops the text) once the frame display list is full.
Gfx *func_1516CEA4(Gfx *gfx, u8 *box, u8 r, u8 g, u8 b, u8 a) {
    Gfx *start = gfx;
    u8 line[84];
    s32 width;
    s32 height;
    s32 advance;
    s32 i = 0;
    s32 n = 0;
    s32 first;
    s32 flags;
    u8 c;
    f32 x;
    f32 y;
    f32 dx;

    x = *(f32 *) (box + 0x50) - *(f32 *) (box + 0x30);
    y = *(f32 *) (box + 0x54) - *(f32 *) (box + 0x34);
    gSPDisplayList(gfx++, D_80085D30);
    first = 1;
    if ((*(u8 **) (box + 0x24))[0] == '\n') {
        do {
            i++;
        } while ((*(u8 **) (box + 0x24))[i] == '\n');
    }
    do {
        if (gfx - D_800BEDE8[D_800BE9C0] > D_800BEFC4) {
            return start;
        }
        c = (*(u8 **) (box + 0x24))[i];
        line[n] = c;
        if (c == '\n') {
            line[n] = 0;
            c = 0;
        }
        if (c != 0) {
            n++;
        } else {
            func_15042BC4(line, &width, &height, &advance);
            if (!first) {
                y += (f32) height;
            } else {
                first = 0;
            }
            flags = **(s32 **) (box + 0x10);
            if (flags & 0x20000) {
                dx = *(f32 *) (box + 0x30) - (f32) (width >> 1) - 1.0f;
            } else {
                dx = 0.0f;
            }
            if (flags & 0x40000) {
                gfx = func_15041A9C(gfx, x + dx + 1.0f, y, line, 0xFF, 0xFF, 0xFF, a, 4096.0f, 4096.0f, n);
            } else if (!(flags & 4)) {
                gfx = func_15041A9C(gfx, x + dx + 1.0f, y, line, 0, 0, 0, a, 4096.0f, 4096.0f, n);
            } else {
                gfx = func_15041A9C(gfx, x + dx, y, line, r, g, b, a, 4096.0f, 4096.0f, n);
            }
            n = 0;
            y += (f32) advance;
        }
    } while ((*(u8 **) (box + 0x24))[i++] != 0);
    return gfx;
}
