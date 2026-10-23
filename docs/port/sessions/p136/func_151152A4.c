
/*
 * object_sound_play: plays / updates the positional sound of a world object (handle u16 at obj +0x74, position s16
 * +0x10/+0x12/+0x14). flags 1: nothing to do when the handle still plays `sound` (func_1001147C). sound -1: stops
 * the handle (func_100111C8) and clears it. flags 8: start a new voice instead of reusing the handle. flags 4:
 * func_10010E78 (one-shot at the position, volume vol, ranges r0 / r1); the handle is cleared unless flags 8.
 * flags 2: releases the old handle (func_1001123C) and stores func_10010E78's new one. Otherwise releases it and
 * starts a tracked sound with func_1000FA64 (update callback func_15115244 with the object). Returns 0 (callers
 * declare s32 and ignore it; the asm returns nothing).
 */
s32 func_151152A4(u8 *obj, s32 sound, s32 vol, s16 r0, s16 r1, s32 flags) {
    u16 *handle = (u16 *) (obj + 0x74);
    s16 *pos = (s16 *) (obj + 0x10);
    u16 h;

    if ((flags & 1) && *handle != 0 && func_1001147C(*handle) == sound) {
        return 0;
    }
    if (sound == -1) {
        if (*handle != 0) {
            func_100111C8(*handle);
            *handle = 0;
        }
        return 0;
    }
    h = (flags & 8) ? 0 : *handle;
    if (flags & 4) {
        func_10010E78(h, sound, vol, 0, 0, -1, pos[0], pos[1], pos[2], r0, r1);
        if (!(flags & 8)) {
            *handle = 0;
        }
    } else if (flags & 2) {
        if (h != 0) {
            func_1001123C(h);
            h = 0;
        }
        *handle = func_10010E78(h, sound, vol, 0, 0, -1, pos[0], pos[1], pos[2], r0, r1);
    } else {
        if (h != 0) {
            func_1001123C(h);
        }
        *handle = func_1000FA64(sound, pos[0], pos[1], pos[2], vol, r1, r0, (s32) func_15115244, obj, 0, 0, 0);
    }
    return 0;
}
