void func_15182D40(void);
s32 func_150ADA20(void);
// level_ambient_cue_update: level update handler (D_8008D0A4[14]): runs func_15182D40, then counts the cue timer
// (byte at D_800D9D10) down by the frame delta D_800BE9E4; when it has run out, the first of the objects 0x15 /
// 0x1A / 0x1B / 0x1C / 0x1D / 0x20 that func_150A29C8 reports absent (0) gets a random sound 0x6C..0x6E played at
// its point in D_800D34B8 (0x34-byte records), and the timer restarts at 0x80..0xFF.
void func_150D0C40(s32 arg0) {
    u8 *timer = (u8 *) D_800D9D10;
    s16 *pos;
    s32 id;

    id = 0;
    func_15182D40();
    if (*timer != 0) {
        if (D_800BE9E4 < *timer) {
            *timer -= D_800BE9E4;
        } else {
            *timer = 0;
        }
        return;
    }
    if (func_150A29C8(0, 0x15) == 0) {
        id = 0x15;
    } else if (func_150A29C8(0, 0x1A) == 0) {
        id = 0x1A;
    } else if (func_150A29C8(0, 0x1B) == 0) {
        id = 0x1B;
    } else if (func_150A29C8(0, 0x1C) == 0) {
        id = 0x1C;
    } else if (func_150A29C8(0, 0x1D) == 0) {
        id = 0x1D;
    } else if (func_150A29C8(0, 0x20) == 0) {
        id = 0x20;
    }
    if (id == 0) {
        return;
    }
    *timer = (func_150ADA20() & 0x7F) + 0x80;
    pos = (s16 *) (D_800D34B8 + id * 0x34);
    func_10010F88((u32) func_150ADA20() % 3 + 0x6C, 0x5DC0, 0, 0, 0, pos[0], pos[1], pos[2], 0x320, 0x5DC);
}
