extern u16 D_80089880[2][3];   /* per sound set: { moving id, stop id, idle id }: { 0x603, 0x604, 0x605 }, { 0x620, 0x621, 0x622 } */
void func_151CC840(s32 arg0);

/*
 * scope_motion_sound_update: per-frame callback of the scope's motion sounds (registered with func_1000FA64 by the
 * scope code above with id 0x605, or 0x622 with bit 31 of the value set; voice +0x18 = the holder, voice +0x1C =
 * (set << 31) | last value). The set (bit 31) picks a row of D_80089880. A pending idle id is cleared to 0, then
 * the voice position (+2/+4/+6) follows the holder's position (holder +0x3D0, floats +0x14..+0x1C, truncated).
 * While the holder's player (+0x3D4) is in state 2 (+0x197): the value is holder +0x1A4 * -10000 converted to u32
 * (IDO conversion: out of range / negative -> 0xFFFFFFFF). When it changed it is stored and, unless the id is the
 * row's moving id already, the voice's sound (+0x24) is stopped (func_100111C8) and the id becomes the moving
 * id. When it did not change and the id is the moving id: the sound is stopped and the stop id is played
 * (func_10010F30(id, 20000, 0x40, 0, 0)) and becomes the id; else, if flag 0x80 of +0x10 is set,
 * func_151CC840(holder) and the idle sound is played. Flag 0x80 is always cleared. Returns 0 (keep the voice); 1
 * when the player is not in state 2.
 */
s32 func_15127520(u8 *voice, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *id) {
    u32 packed = *(u32 *) (voice + 0x1C);
    u8 *holder = *(u8 **) (voice + 0x18);
    u32 set = packed >> 31;
    u32 last = packed & 0xFFFFFF;
    u16 *ids = D_80089880[set];
    f32 v = *(f32 *) (holder + 0x1A4) * -10000.0f;
    s32 changed = 0;
    u32 cur;
    f32 *pos;

    if (*id == ids[2]) {
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
    /* f32 -> u32 as the asm converts it (truncation; negative / NaN / too large give 0xFFFFFFFF) */
    if (v >= 2147483648.0f) {
        cur = (v - 2147483648.0f < 2147483648.0f) ? ((u32) (s32) (v - 2147483648.0f) | 0x80000000) : 0xFFFFFFFF;
    } else if (v > -1.0f) {
        cur = (u32) (s32) v;
    } else {
        cur = 0xFFFFFFFF;
    }
    if (last != cur) {
        changed = 1;
        *(u32 *) (voice + 0x1C) = (set << 31) | cur;
    }
    if (changed) {
        if (*id != ids[0]) {
            if (*(u16 *) (voice + 0x24) != 0) {
                func_100111C8(*(u16 *) (voice + 0x24));
            }
            *(u16 *) (voice + 0x24) = 0;
            *(s32 *) (voice + 0x10) &= ~0x80;
            *id = ids[0];
        }
    } else if (*id == ids[0]) {
        if (*(u16 *) (voice + 0x24) != 0) {
            func_100111C8(*(u16 *) (voice + 0x24));
        }
        *(u16 *) (voice + 0x24) = 0;
        *id = ids[1];
        func_10010F30(ids[1], 20000, 0x40, 0, 0);
        *(s32 *) (voice + 0x10) &= ~0x80;
    } else if (*(s32 *) (voice + 0x10) & 0x80) {
        func_151CC840((s32) holder);
        func_10010F30(ids[2], 20000, 0x40, 0, 0);
    }
    *(s32 *) (voice + 0x10) &= ~0x80;
    return 0;
}
