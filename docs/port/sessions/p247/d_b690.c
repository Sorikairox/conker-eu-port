#ifdef NON_MATCHING
s32 func_1000F568(s32, s32);

// tank_engine_sound_update: per-frame callback of the tank's engine voice (started by func_151BB5F4 with id 0x4A7
// and by itself; same callback type as scope_motion_sound_update). voice +0x18 = the tank, voice +0x1C packs
// mode (bits 0-6: last drive state), fading (bit 7), level (bits 8-15) and a timer (bits 16-27). Returns 1 (and
// does nothing) without a tank or when its +0x1CA is clear. The voice follows the tank's position. Drive state:
// 1 = driving (speed +0x3C beyond +-1 in the direction of the throttle +0x44), 2 = skidding (speed beyond +-5
// against or without throttle), else 0. When the state changed it plays a one-shot (0x4A5 when skidding starts,
// else a pick of func_1000F568(0x4A3, 4)) on the tank unless one is playing (func_10010894). Starting to drive
// from idle (id 0x4A7) switches the voice to the run sound 0x4A8 (new voice at volume 0x2EE0, returns 1); stopping
// while running (0x4A8) switches back to idle 0x4A7 (0x2000); while the wind-down 0x4A9 plays it waits (returns 1).
// The run / wind-down voice fades its volume (*vol * level / 256) in (bit 7) or out by 8 a frame (returns 1 when
// faded out); with a timer it counts down by D_800BE9E4 and, at the end while running, starts 0x4A9 and a new
// random (func_150ADA20 & 0x200) timer. Its pitch is |speed| * +0xB8 / 2. Repacks +0x1C; when *vol is 0 or the
// voice was flagged (+0x10 & 0x80) it stops its sound (+0x24) and clears the id, the flag and *vol. Returns 0.
s32 func_151BB690(u8 *voice, s32 arg1, s32 *vol, s32 arg3, s32 *pitch, s32 arg5, u16 *id) {
    u8 *tank = *(u8 **) (voice + 0x18);
    u32 packed;
    s32 mode;
    s32 fading;
    s32 level;
    s32 timer;
    s32 drive;
    s32 changed;
    u16 snd;
    u16 newId;
    s32 volume;

    if (tank == NULL || tank[0x1CA] == 0) {
        return 1;
    }
    packed = *(u32 *) (voice + 0x1C);
    fading = (packed >> 7) & 1;
    timer = (packed >> 16) & 0xFFF;
    level = (packed >> 8) & 0xFF;
    mode = packed & 0x7F;
    newId = 0;
    *(s16 *) (voice + 2) = (s32) *(f32 *) (tank + 0x14);
    *(s16 *) (voice + 4) = (s32) *(f32 *) (tank + 0x18);
    *(s16 *) (voice + 6) = (s32) *(f32 *) (tank + 0x1C);
    drive = 0;
    if ((*(f32 *) (tank + 0x3C) > 1.0f && *(f32 *) (tank + 0x44) > 0.0f)
        || (*(f32 *) (tank + 0x3C) < -1.0f && *(f32 *) (tank + 0x44) < 0.0f)) {
        drive = 1;
    } else if ((*(f32 *) (tank + 0x3C) > 5.0f && *(f32 *) (tank + 0x44) <= 0.0f)
               || (*(f32 *) (tank + 0x3C) < -5.0f && *(f32 *) (tank + 0x44) >= 0.0f)) {
        drive = 2;
    }
    changed = (drive ^ mode) & 0x7F;
    if (changed != 0) {
        if ((changed & 2) && (drive & 2)) {
            snd = 0x4A5;
        } else {
            snd = func_1000F568(0x4A3, 4);
        }
        if (func_10010894((struct127 *) tank) == 0) {
            func_10010154(snd, (struct127 *) tank, 0x6D60, 0x12C, 0x708);
        }
    }
    if (drive != 0) {
        if (*id == 0x4A7) {
            newId = 0x4A8;
            volume = 0x2EE0;
        }
    } else if (*id == 0x4A9 || *id == 0x4A8) {
        if (*id == 0x4A9) {
            return 1;
        }
        newId = 0x4A7;
        volume = 0x2000;
    }
    if (newId != 0) {
        func_1000FA64(newId, (s32) *(f32 *) (tank + 0x14), (s32) *(f32 *) (tank + 0x18),
                      (s32) *(f32 *) (tank + 0x1C), volume, 0x320, 0xC8, (s32) &func_151BB690, tank,
                      drive | 0x12CFF00, 8, 0);
        return 1;
    }
    if (*id != 0x4A7) {
        if (timer == 0) {
            *vol = (u32) (*vol * level) >> 8;
            if (fading) {
                level += 8;
                if (level >= 0x100) {
                    level = 0xFF;
                    timer = (func_150ADA20() & 0x200) + 0x12C;
                    fading = 0;
                }
            } else {
                level -= 8;
                if (level <= 0) {
                    return 1;
                }
            }
        } else {
            timer -= D_800BE9E4;
            if (timer <= 0) {
                timer = 0;
                if (*id == 0x4A8) {
                    func_1000FA64(0x4A9, (s32) *(f32 *) (tank + 0x14), (s32) *(f32 *) (tank + 0x18),
                                  (s32) *(f32 *) (tank + 0x1C), 0x2EE0, 0x320, 0xC8, (s32) &func_151BB690, tank,
                                  drive | 0x880, 8, 0);
                    timer = (func_150ADA20() & 0x200) + 0x384;
                }
            }
        }
        *pitch = (s32) (fabsf(*(f32 *) (tank + 0x3C)) * *(f32 *) (tank + 0xB8) * 0.5f);
    }
    *(u32 *) (voice + 0x1C) = (fading << 7) | drive | (level << 8) | (timer << 16);
    if (*vol == 0 || (*(s32 *) (voice + 0x10) & 0x80)) {
        if (*(u16 *) (voice + 0x24) != 0) {
            func_100111C8(*(u16 *) (voice + 0x24));
            *(u16 *) (voice + 0x24) = 0;
        }
        *id = 0;
        *(s32 *) (voice + 0x10) &= ~0x80;
        *vol = 0;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BB690.s")
#endif
