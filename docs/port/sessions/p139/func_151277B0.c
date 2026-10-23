/*
 * scope_zoom_sound_update: per-frame callback of the 0x622 zoom sound (registered with func_1000FA64 by the scope
 * code above; voice +0x18 = the holder, voice +0x1C = (stall count << 24) | low 24 bits of the last zoom product).
 * A pending id 0x622 is cleared to 0 first, then the voice position (+2/+4/+6) follows the holder's position
 * (holder +0x3D0, floats +0x14..+0x1C, truncated). While the holder's player (+0x3D4) is in state 2 (+0x197):
 * the zoom product (+0x174 * +0x178, its low 24 float bits) is compared with the last one: equal -> count 0;
 * changed by more than 100 (unsigned difference) -> the count grows by the frame time D_800BE9E4; a count of 10
 * or more means the zoom has stopped: the voice's sound (+0x24) is stopped (func_100111C8), flag 0x80 of +0x10
 * cleared and the id set to 0x61C (end sound) once. When it moves again after 0x61C, the sound is stopped and
 * the id becomes 0x61D (restart). Without a sound and id the flag 0x80 is cleared. Returns 0 (keep the voice);
 * 1 when the player is no longer in state 2.
 */
s32 func_151277B0(u8 *voice, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *id) {
    u8 *holder = *(u8 **) (voice + 0x18);
    u32 packed = *(u32 *) (voice + 0x1C);
    u8 *pl = *(u8 **) (holder + 0x3D4);
    u32 last = packed & 0xFFFFFF;
    u32 count = packed >> 24;
    s32 stopped = 0;
    union {
        f32 f;
        u32 w;
    } zoom;
    u32 cur;
    f32 *pos;

    zoom.f = *(f32 *) (pl + 0x174) * *(f32 *) (pl + 0x178);
    cur = zoom.w & 0xFFFFFF;
    if (*id == 0x622) {
        *id = 0;
    }
    pos = *(f32 **) (holder + 0x3D0);
    *(s16 *) (voice + 2) = (s32) pos[5];
    pos = *(f32 **) (holder + 0x3D0);
    *(s16 *) (voice + 4) = (s32) pos[6];
    pos = *(f32 **) (holder + 0x3D0);
    *(s16 *) (voice + 6) = (s32) pos[7];
    if ((*(u8 **) (holder + 0x3D4))[0x197] != 2) {
        return 1;
    }
    if (last != cur) {
        if (count < 10) {
            if (last - cur > 100) {
                count += D_800BE9E4;
            }
        } else {
            stopped = 1;
        }
    } else {
        count = 0;
    }
    *(u32 *) (voice + 0x1C) = (count << 24) | cur;
    if (stopped) {
        if (*id != 0x61C) {
            if (*(u16 *) (voice + 0x24) != 0) {
                func_100111C8(*(u16 *) (voice + 0x24));
            }
            *(u16 *) (voice + 0x24) = 0;
            *(s32 *) (voice + 0x10) &= ~0x80;
            *id = 0x61C;
        }
    } else if (*id == 0x61C) {
        if (*(u16 *) (voice + 0x24) != 0) {
            func_100111C8(*(u16 *) (voice + 0x24));
        }
        *(u16 *) (voice + 0x24) = 0;
        *id = 0x61D;
        *(s32 *) (voice + 0x10) &= ~0x80;
    }
    if (*(u16 *) (voice + 0x24) == 0 && *id == 0) {
        *(s32 *) (voice + 0x10) &= ~0x80;
    }
    return 0;
}
