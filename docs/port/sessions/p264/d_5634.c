#ifdef NON_MATCHING
// rocket_sound_update: per-frame callback (func_1000FA64, same type as object_sound_follow_cam) of the three sounds
// func_150D3870 starts for its object (voice +0x18 = the object's Data3870, voice +0x1C = sound id). Target volume
// and pitch per id: 0x5B3 follows the speed of data->obj (f32 +0x28): volume speed*25 (0 below 500, capped at 5000),
// pitch speed*5 (capped at 1000); state (data +5) 1 or 2 adds 7000 to the volume (1 also sets pitch 400); another
// state sets pitch 400 and jumps the volume to its target. 0x5BC: state 0 -> 24000 at once, else 400. 0x5B4: state
// 0 -> 16000 at once with pitch 400; 1 (or D_8008FD8C >= 5) -> 12000; else 0 with pitch 400. Volume (+0xC) and pitch
// (*pitch) move towards their targets by D_800BE9E4 * 256 a frame (pitch down by * 8). Below 500 the volume is 0;
// otherwise a voice without a sound restarts its id (+0 and *sound). Follows data->obj's position (+2/+4/+6), halves
// the volume (and *vol) in mode D_800C35EA == 1, stores the pitch (+0x20). When *vol is 0 it stops the playing sound
// (+0x24) and clears *sound. Returns 0.
s32 func_150D5634(u8 *e, s32 *pos, u32 *vol, s32 *pan, s32 *pitch, s32 *slot, u16 *sound) {
    Data3870 *data = *(Data3870 **) (e + 0x18);
    s32 id = *(s32 *) (e + 0x1C);
    s32 cur = *(s32 *) (e + 0xC);
    s32 curPitch = *pitch;
    s32 target = 0;
    s32 targetPitch = 0;
    u8 *obj;
    f32 speed;

    if (id == 0x5B3) {
        obj = (u8 *) data->obj;
        if (obj != NULL) {
            speed = *(f32 *) (obj + 0x28);
            target = (s32) (speed * 25.0f);
            if (target > 5000) {
                target = 5000;
            } else if (target < 500) {
                target = 0;
            }
            targetPitch = (s32) (0.0f + speed * 5.0f);
            if (targetPitch > 1000) {
                targetPitch = 1000;
            }
        }
        if (data->u05 == 2) {
            target += 7000;
        } else if (data->u05 == 1) {
            targetPitch = 400;
            target += 7000;
        } else {
            targetPitch = 400;
            if (target != 0) {
                cur = target;
            }
        }
    } else if (id == 0x5BC) {
        if (data->u05 == 0) {
            target = 24000;
            cur = 24000;
        } else {
            target = 400;
        }
    } else if (id == 0x5B4) {
        if (data->u05 == 0) {
            target = 16000;
            targetPitch = 400;
            cur = 16000;
        } else if (data->u05 == 1 || D_8008FD8C >= 5) {
            target = 12000;
        } else {
            targetPitch = 400;
        }
    }

    if (cur != target) {
        if (cur < target) {
            cur += D_800BE9E4 << 8;
            if (cur > target) {
                cur = target;
            }
        } else {
            cur -= D_800BE9E4 << 8;
            if (cur < target) {
                cur = target;
            }
        }
    }
    if (curPitch != targetPitch) {
        if (curPitch < targetPitch) {
            curPitch += D_800BE9E4 << 8;
            if (curPitch > targetPitch) {
                curPitch = targetPitch;
            }
        } else {
            curPitch -= D_800BE9E4 << 3;
            if (curPitch < targetPitch) {
                curPitch = targetPitch;
            }
        }
    }

    if (cur < 500) {
        cur = 0;
    } else if (*sound == 0) {
        *(s16 *) (e + 0) = id;
        *sound = id;
    }
    *(s16 *) (e + 2) = (s32) *(f32 *) ((u8 *) data->obj + 0x14);
    *(s16 *) (e + 4) = (s32) *(f32 *) ((u8 *) data->obj + 0x18);
    *(s16 *) (e + 6) = (s32) *(f32 *) ((u8 *) data->obj + 0x1C);
    if (D_800C35EA == 1) {
        *(s32 *) (e + 0xC) = cur >> 1;
        *vol >>= 1;
    } else {
        *(s32 *) (e + 0xC) = cur;
    }
    *(s16 *) (e + 0x20) = curPitch;
    *pitch = (s16) curPitch;
    if (*vol == 0) {
        if (*(u16 *) (e + 0x24) != 0) {
            func_100111C8(*(u16 *) (e + 0x24));
            *(u16 *) (e + 0x24) = 0;
        }
        *sound = 0;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D5634.s")
#endif
