// text_queue_tempo_events: drains the text queue (func_100126E8 into a 0x100-byte buffer); every 'L' record carries a
// 28-bit big-endian 7-bit-packed value at bytes 4..7, divided by 441 (16 when that gives 0), which goes with the record's
// byte 3 minus one to func_15080830 for the current player's object D_800CC2D0[D_800D18D0].
void func_15080830(u8 *arg0, s32 arg1, s32 arg2);
void func_15080628(void) {
    u8 buf[0x100];
    s32 value;

    while (func_100126E8((s32)buf, 0x100) != 0) {
        if (buf[0] == 'L') {
            value = buf[4] & 0x7F;
            value = (buf[5] & 0x7F) | (value << 7);
            value = (buf[6] & 0x7F) | (value << 7);
            value = (buf[7] & 0x7F) | (value << 7);
            value /= 441;
            if (value == 0) {
                value = 16;
            }
            func_15080830((u8 *)&D_800CC2D0[D_800D18D0], buf[3] - 1, value);
        }
    }
}
