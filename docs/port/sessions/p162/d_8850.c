void func_150C8850(void) {
    s32 i;
    u8 *r;
    s32 speed;
    s32 target;
    s32 diff;
    s32 step;
    s32 pos;

    for (i = 0; i < 10; i++) {
        r = (u8 *)&D_eu_800BE900[i];
        speed = *(s16 *)(r + 6);
        if (speed != *(s16 *)(r + 8)) {
            target = *(s16 *)(r + 8);
            if (speed < 0) {
                target = -target;
            }
            diff = target - speed;
            step = D_800BE9E4 * 16;
            if ((diff < 0 ? -diff : diff) < step) {
                *(s16 *)(r + 6) = target;
            } else {
                *(s16 *)(r + 6) = speed + step * (diff >= 0 ? 1 : -1);
            }
            speed = *(s16 *)(r + 6);
        }
        *(s16 *)(r + 4) += speed * *(s8 *)(r + 2) * D_800BE9A0;
        pos = *(s16 *)(r + 4);
        if (pos >= 0x500) {
            *(s16 *)(r + 4) = 0x500 - (s16)(pos - 0x500);
            *(s8 *)(r + 2) = -*(s8 *)(r + 2);
            if (*(s16 *)(r + 4) >= 0x500) {
                *(s16 *)(r + 4) = 0x4FF;
            }
        } else if (pos < 0) {
            *(s16 *)(r + 4) = -pos;
            *(s8 *)(r + 2) = -*(s8 *)(r + 2);
            if (*(s16 *)(r + 4) < 0) {
                *(s16 *)(r + 4) = 0;
            }
        }
    }
}
