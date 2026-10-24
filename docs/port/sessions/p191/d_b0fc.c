void func_15060A30(s32, struct127 *);
s32 func_1507CD64(struct127 *, s32);
void func_1510FDA0(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3, s32 arg4, f32 *arg5, f32 *arg6);
f32 func_1505210C(u8 *, f32, f32, f32 *, f32);
extern u8 *D_800CC6A4;
/* player fields used by the swim update (struct127 has no names for them yet) */
#define SWIM_U8(p, o) (*(u8 *) ((u8 *) (p) + (o)))
#define SWIM_U16(p, o) (*(u16 *) ((u8 *) (p) + (o)))
#define SWIM_S16(p, o) (*(s16 *) ((u8 *) (p) + (o)))
#define SWIM_F32(p, o) (*(f32 *) ((u8 *) (p) + (o)))
#define SWIM_SURFACE(p) SWIM_F32(p, 0x118)  /* water surface height, -10000 = none */
#define SWIM_PITCH(p) SWIM_F32(p, 0xB8)     /* body pitch, -90..90 */
#define SWIM_PITCHVEL(p) SWIM_F32(p, 0xBC)  /* pitch rate, -2.7..2.7 per frame */
#define SWIM_AIR(p) SWIM_U16(p, 0xB2)       /* time under water (breath) */
#define SWIM_ANIM(p) SWIM_U16(p, 0x84)      /* current animation / move id */
#define SWIM_ST(p) ((u8 *) (p)->unk31C)     /* player state block */

// player_swim_update: P191: the player's per-frame water physics while p->in_water (called by player_update
// func_1504CB98 with the frame step dt). Depth below the surface (+0x118 minus 60) gives a float-up push for
// shallow water (when the state block +0x20 bit 0 / +0x21 is set: at most 8 * D_800D1550 per frame up to 400), and
// for a swimming player (in_water == 1) the swim pitch target (+0xB8 eases towards it at 2.7 deg per frame, clamped
// to -90..90; 2.25 * the input's dive value, or 0 while +0x21), a buoyancy rise (min(2 * depth, 300) * dt * 0.002997),
// the bob speed in the state block +0x1C (up to 2.5 near the surface, +0.05 per frame), a clamp 14 above the surface
// line (0.65 of the excess), the air timer +0xB2 (drowning sounds 0x1A7 / 0x168 / 0x499, health loss every 0x605
// ticks, func_1507CD64 death 3 / 4 at health 0), the floor push (func_1510FDA0 / func_1505210C when +0x28 < 40) and
// the controller-driven turn (+0x76 -= (dive + 8) / 18 * D_800CC264 * 256 / 100). Close to the bottom (+0x28 < 10,
// y below the surface line + 20) the player leaves the swim (func_15052408) with xz speed <= 16. Returns the speed
// for the caller: target_speed, the clamped xz speed, or 0 when the player is stunned / in move 0x262; with no
// surface (-10000) it calls func_15052408 and returns 0. When the state block +0x95 is set, y goes back to
// old_y_position and in_water clears unless y stays below the surface line.
f32 func_1504B0FC(struct127 *p, f32 dt) {
    f32 ret = 0.0f;
    f32 targetPitch;
    f32 lift;
    f32 depth2;
    f32 step;
    f32 line;
    f32 over;
    f32 delta;
    f32 mag;
    f32 dummy58, dummy54;
    f32 fx, fz;
    s32 slide;
    s32 dive;
    s8 turn;
    s32 q;
    u16 air;

    SWIM_S16(SWIM_ST(p), 0x68) = 0;
    dive = 0;
    SWIM_U8(p, 0x110) = 0;
    if (p->stunned == 0 && p->health != 0 && SWIM_ST(p)[0x198] == 0) {
        turn = ((s8 *) D_800CC6A4)[2];
        dive = ((s8 *) D_800CC6A4)[3];
    } else {
        turn = 0;
    }
    if ((s8) SWIM_ST(p)[0x22] >= 0x65) {
        dive = 0x50;
    }
    depth2 = p->y_position - ((SWIM_SURFACE(p) - 60.0f) - 170.0f);
    depth2 = depth2 + depth2;
    if ((SWIM_ST(p)[0x20] & 1) || SWIM_ST(p)[0x21] != 0) {
        SWIM_AIR(p) = 0;
        if (depth2 < 400.0f) {
            step = 8.0f * D_800D1550[0];
            if (dive >= 0xB) {
                dive = 0xA;
            }
            if (400.0f < depth2 + step) {
                step = 400.0f - depth2;
            }
            p->y_position = p->y_position + step;
        }
    }
    if (p->in_water == 1) {
        SWIM_F32(p, 0x1CC) = p->y_position;
        if (SWIM_SURFACE(p) == -10000.0f) {
            func_15052408(p);
            return 0.0f;
        }
        if (dive != 0 || (SWIM_SURFACE(p) - 60.0f) - 175.0f < p->y_position) {
            targetPitch = dive * 2.25f;
        } else {
            targetPitch = SWIM_PITCH(p);
        }
        if (SWIM_ST(p)[0x21] != 0) {
            targetPitch = 0.0f;
        }
        func_15059444(p);
        if (p->stunned != 0 && (p->health != 0 || 60.0f <= p->y_velocity)) {
            return 0.0f;
        }
        if (SWIM_ANIM(p) == 0x262) {
            return 0.0f;
        }
        if (0.0f < depth2 && SWIM_ANIM(p) != 0x22) {
            if (300.0f < depth2) {
                depth2 = 300.0f;
            }
            p->y_position = p->y_position + depth2 * dt * 0.002997f;
        }
    } else if (p->gravity < 0.0f) {
        if (0.0f < p->y_velocity) {
            p->gravity = 0.0f;
            p->y_velocity = 0.0f;
        }
    } else if (0.0f < p->gravity) {
        if (p->y_velocity < 0.0f) {
            p->gravity = 0.0f;
            p->y_velocity = 0.0f;
        }
    }

    if (p->in_water == 1 && SWIM_F32(p, 0x28) < 10.0f &&
        !(p->y_position < (SWIM_SURFACE(p) - 60.0f) + 20.0f)) {
        /* touching the bottom in shallow water: leave the swim */
        func_15052408(p);
        if (16.0f < p->xz_velocity) {
            p->xz_velocity = 16.0f;
        }
        ret = p->xz_velocity;
    } else {
        if (p->in_water == 1) {
            if (((f32) SWIM_S16(p, 0x1A6) > SWIM_SURFACE(p) - 50.0f || (SWIM_ST(p)[0x20] & 1)) && p->health != 0) {
                /* surfaced: gasp by how long the player was under */
                air = SWIM_AIR(p);
                if (air >= 0x1F) {
                    if (air >= 0x5D3) {
                        func_15060A30(0x1A7, p);
                    } else if (air >= 0x2D1) {
                        func_15060A30(0x168, p);
                    }
                }
                SWIM_AIR(p) = 0;
            } else {
                air = SWIM_AIR(p) + D_800BE9E4;
                SWIM_AIR(p) = air;
                if (air >= 0x605 || (p->health == 0 && SWIM_ST(p)[0x120] == 0)) {
                    /* out of air: lose one health per 0x605 - 0x32 ticks */
                    SWIM_AIR(p) = air - 0x32;
                    if (p->health >= 2) {
                        if (p->health == 4) {
                            func_15060A30(0x499, p);
                        }
                        p->health = p->health - 1;
                    } else {
                        p->health = 0;
                        if (p->stunned != 0) {
                            p->gravity = 0.0f;
                            func_1507CD64(p, 4);
                        } else {
                            func_1507CD64(p, 3);
                        }
                    }
                } else if (air >= 0x5A1 && air < 0x5D2) {
                    SWIM_AIR(p) = air + 100;
                    if (p->health < 4) {
                        func_15060A30(0x499, p);
                    }
                }
            }
            if (p->gravity < 0.0f && 0.0f < p->y_velocity) {
                p->gravity = 0.0f;
                p->y_velocity = 0.0f;
            }
            /* bob towards the surface line */
            if ((SWIM_SURFACE(p) - 60.0f) - 175.0f < p->y_position && SWIM_ANIM(p) != 0x28) {
                if (SWIM_F32(SWIM_ST(p), 0x1C) < 2.5f) {
                    SWIM_F32(SWIM_ST(p), 0x1C) = SWIM_F32(SWIM_ST(p), 0x1C) + 0.05f;
                }
            } else {
                SWIM_F32(SWIM_ST(p), 0x1C) = 0.0f;
            }
            p->y_position = p->y_position + SWIM_F32(SWIM_ST(p), 0x1C) * D_800D1550[0];
            over = p->y_position - ((SWIM_SURFACE(p) - 60.0f) + 14.0f);
            if (0.0f < over) {
                p->y_position = p->y_position - over * 0.65f;
                SWIM_F32(SWIM_ST(p), 0x1C) = 0.0f;
            }
            if ((SWIM_SURFACE(p) - 60.0f) - 75.0f < p->y_position) {
                targetPitch = targetPitch - 30.0f;
            }
        }
        if (SWIM_ANIM(p) == 0x22 && targetPitch < -20.0f) {
            targetPitch = -20.0f;
        }
        if (SWIM_F32(p, 0x28) < 40.0f) {
            func_1510FDA0(*(s32 *) ((u8 *) p + 0x188), (s32) ((u8 *) p + 0x18C), &dummy58, &dummy54, (s32) &slide,
                          &fx, &fz);
            fx = func_1505210C((u8 *) p, fx, fz, &fz, 180.0f);
            if (fz < SWIM_PITCH(p)) {
                SWIM_PITCH(p) = SWIM_PITCH(p) + (fz - SWIM_PITCH(p)) * 0.2f;
            }
        }
        delta = targetPitch - SWIM_PITCH(p);
        SWIM_PITCHVEL(p) = delta;
        mag = delta < 0.0f ? -delta : delta;
        if (mag < 2.7f * D_800D1550[0]) {
            SWIM_PITCH(p) = targetPitch;
        } else {
            if (2.7f < SWIM_PITCHVEL(p)) {
                SWIM_PITCHVEL(p) = 2.7f;
            }
            if (SWIM_PITCHVEL(p) < -2.7f) {
                SWIM_PITCHVEL(p) = -2.7f;
            }
            SWIM_PITCH(p) = SWIM_PITCH(p) + SWIM_PITCHVEL(p) * D_800D1550[0];
        }
        if (SWIM_PITCH(p) < -90.0f) {
            SWIM_PITCH(p) = -90.0f;
        }
        if (90.0f < SWIM_PITCH(p)) {
            SWIM_PITCH(p) = 90.0f;
        }
        if (SWIM_ST(p)[0x21] == 0) {
            q = (turn + 8) / 18;
            if (q != 0) {
                SWIM_U8(p, 0x7E) = 0x17;
                p->unk76 = p->unk76 - ((q * D_800CC264) << 8) / 100;
            }
            ret = p->target_speed;
        }
        SWIM_U8(p, 0x80) = 1;
    }
    if (SWIM_ST(p)[0x95] != 0) {
        p->y_position = p->old_y_position;
        if (SWIM_SURFACE(p) == -10000.0f || !(p->y_position < SWIM_SURFACE(p) - 60.0f)) {
            p->in_water = 0;
        }
    }
    return ret;
}
#undef SWIM_U8
#undef SWIM_U16
#undef SWIM_S16
#undef SWIM_F32
#undef SWIM_SURFACE
#undef SWIM_PITCH
#undef SWIM_PITCHVEL
#undef SWIM_AIR
#undef SWIM_ANIM
#undef SWIM_ST
