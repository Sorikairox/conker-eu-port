// mover_bob_y_update: P194. World mesh record (D_800DBEF4, 0xA0 bytes) handler: moves the record's y (+0x12) towards
// base + (phase * amplitude) / 256, where phase = the upper half of +0x3C (unsigned), amplitude = +0x80 and the base y
// is latched once into +0x84 (low half = the starting y, bit 31 marks it as set). It moves at most +0x7C (speed) per
// call; +0x7C == 0 does nothing. The "arrived" bits 0 / 1 of +0x73 are cleared while it moves and both set when y is
// already at the target.
void func_15119974(u8 *rec) {
    s16 *y = (s16 *) (rec + 0x12);
    s32 speed;
    s32 target;
    s32 diff;

    if (*(s32 *) (rec + 0x84) == 0) {
        *(s32 *) (rec + 0x84) = *y | 0x80000000;
    }
    speed = *(s32 *) (rec + 0x7C);
    if (speed == 0) {
        return;
    }
    rec[0x73] &= ~3;
    target = (s32) ((u16) (*(s32 *) (rec + 0x3C) >> 16) * *(s32 *) (rec + 0x80)) / 256 + (s16) *(s32 *) (rec + 0x84);
    if (target == *y) {
        rec[0x73] |= 3;
        return;
    }
    diff = *y - target;
    if (diff < 0) {
        if (-diff < speed) {
            *y = target;
        } else {
            *y += speed;
        }
    } else if (diff < speed) {
        *y = target;
    } else {
        *y -= speed;
    }
}
