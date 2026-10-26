#include <ultra64.h>
#include "functions.h"
#include "variables.h"


f32 wrap_angle_deg(f32);
/* was func_150ED750 */
f32 angle_diff_signed_deg(f32 arg0, f32 arg1) {
    f32 temp_f0;
    f32 var_f2;
    arg0 = wrap_angle_deg(arg0);
    temp_f0 = wrap_angle_deg(wrap_angle_deg(arg1) - arg0);
    var_f2 = temp_f0;
    if (temp_f0 > 180.0f) {
        var_f2 = -360.0f + temp_f0;
    }
    return var_f2;
}

f32 angle_diff_signed_deg(f32, f32);

/* was func_150ED7B4 */
f32 tank_yaw_offset_to_obj(u8 *arg0, u8 *arg1) {
    return angle_diff_signed_deg((f32) (math_atan2_u16((*(f32 *)((u8 *)arg1 + 0x14)) - (*(f32 *)((u8 *)arg0 + 0x14)), (*(f32 *)((u8 *)arg0 + 0x1C)) - (*(f32 *)((u8 *)arg1 + 0x1C)), 0) + 0x4000) * 0.005493164f, (*(f32 *)((u8 *)arg0 + 0x40)));
}

#ifdef NON_MATCHING
/* P249: readable C for tank_shell_aim_error (game_eu_11AF60, 191 insns). */
// tank_shell_aim_error: ballistic aim helper of the tank turret (tank_update). The shell leaves the muzzle at speed
// 148.25 with gravity 2.5 per frame. Muzzle: with a skeleton (+0x1D4), the translation of its matrix (+0xC0) and the
// elevation of the matrix's local +Z axis (which replaces `pitch`); without one, the object position and `pitch`.
// Returns the horizontal miss distance toward (x, y, z) (target distance - `radius`, at least 100, minus the flight
// time * horizontal speed; 5000 when the shell never comes down at a positive time), or, when the target is out of
// reach (no real root), 1000 * (the elevation needed - pitch) in degrees. Callers multiply the result by 0.001.
void mtxf_transform_point(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ);
f32 math_atan2f(f32, f32);
f32 math_asinf_lut(f32);
/* was func_150ED818 */
f32 tank_shell_aim_error(u8 *obj, f32 pitch, f32 x, f32 y, f32 z, f32 radius) {
    f32 mf[4][4];
    f32 ox, oy, oz;
    f32 dx, dy, dz;
    f32 dist, result, rad, vx, vy, disc, root, t, t2, a;
    u8 *skel;

    skel = *(u8 **) (obj + 0x1D4);
    if (skel != NULL) {
        guMtxL2F(mf, (Mtx *) (skel + 0xC0));
        mtxf_transform_point(mf, 0.0f, 0.0f, 1.0f, &ox, &oy, &oz);
        ox -= mf[3][0];
        oz -= mf[3][2];
        oy -= mf[3][1];
        a = math_atan2f(oy, sqrtf(ox * ox + oz * oz)) * 57.295776f;
        if (a > 180.0f) {
            a -= 360.0f;
        }
        pitch = a;
        ox = mf[3][0];
        oy = mf[3][1];
        oz = mf[3][2];
    } else {
        ox = *(f32 *) (obj + 0x14);
        oy = *(f32 *) (obj + 0x18);
        oz = *(f32 *) (obj + 0x1C);
    }
    dx = x - ox;
    dy = y - oy;
    dz = z - oz;
    dist = sqrtf(dx * dx + dz * dz) - radius;
    if (dist < 100.0f) {
        dist = 100.0f;
    }
    result = 5000.0f;
    rad = pitch * 0.017453292f;
    vx = cosf(rad) * 148.25f;
    vy = sinf(rad) * 148.25f;
    disc = vy * vy + 2.0f * (dy * -2.5f);
    if (disc > 0.0f) {
        root = sqrtf(disc);
        t = (-vy - root) / -2.5f;
        if (t > 0.0f) {
            t2 = (-vy + root) / -2.5f;
            if (t2 > 0.0f && t < t2) {
                t = t2;
            }
        }
        if (t > 0.0f) {
            result = dist - t * vx;
        }
    } else {
        result = (math_asinf_lut(sqrtf(-2.0f * dy * -2.5f) * 0.0067453627f) * 57.295776f - pitch) * 1000.0f;
    }
    return result;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11AF60/tank_shell_aim_error.s")
#endif

/* was func_150EDAF8 */
void tank_mark_driver_view(u8 *arg0) {
    struct127 *temp_v1;
    u8 var_v0;
    u8 *temp_v0;
    struct108 *cam;
    temp_v0 = *(u8 **)(arg0 + 0x31C);
    if ((temp_v0 != NULL) && (temp_v0[0x84] == 0)) {
        if (D_800BE616 != 0) {
            var_v0 = arg0[0x127];
        } else {
            var_v0 = arg0[0x124];
        }
        if (((u16 **)D_800BE728[0])[var_v0][0] & 0x10) {
            temp_v1 = &D_800CC2D0[var_v0];
            if (*((u8 *)temp_v1->unk31C + 0x197) != 0) {
                cam = temp_v1->camera;
                if (cam != NULL) {
                    arg0[0x2FC] |= 1 << *((u8 *)cam + 0x23D);
                }
            }
        }
    }
}

#ifdef NON_MATCHING
void obj_vtx_scroll_uv(u8 *, s32, s32, s32, s32, s32, s32, s32);
#else
s32 obj_vtx_scroll_uv(u8 *, s32, s32, s32, s32, s32, s32, s32);
#endif
/* was func_150EDBB8 */
void tank_set_track_speeds(u8 *arg0, s32 arg1, s32 arg2) {
    s32 t;
    s32 var_s0;
    arg1 = (arg1 < -0x2D) ? -0x2D : ((arg1 > 0x2D) ? 0x2D : arg1);
    arg2 = (arg2 < -0x2D) ? -0x2D : ((arg2 > 0x2D) ? 0x2D : arg2);
    if (arg0[4] == 0x28) {
        var_s0 = 0x7C;
    } else {
        t = arg1;
        arg1 = arg2;
        var_s0 = 0x1C;
        arg2 = t;
    }
    obj_vtx_scroll_uv(arg0, 0, 0, 0x800, 0x800, var_s0, -arg2 * 7, 0);
    obj_vtx_scroll_uv(arg0, 1, var_s0, 0x800, 0x800, var_s0, -arg1 * 7, 0);
}

#ifdef NON_MATCHING
/* P249: readable C for tank_update (game_eu_11AF60, 1407 insns). */
// tank_update: per-frame update of a drivable tank (multiplayer Tank / PLAY barrel; ids 0x77 / 0x28 also drive the
// track animation). The driver is player +0x124 (cleared here: player 0 in single player) or, in multiplayer
// (D_800BE616), player +0x127 (0xFF = none); `pad` = D_800BE748 entry (6 bytes: u16 flags, s8 stick x at +2, s8 stick
// y at +3), buttons = D_800BE728[0][player][0], the driver's part = D_800CC2D0[player] +0x31C.
//  - Driven when the driver's part +0x84 is 0 (multiplayer) or the tank has +0x13C (single player, which also sets the
//    skid state +0xD0 = 1 / 2 with +0x114 = 2.0 above |speed| 5). Boost: part +0x128 bit 0 + button 0x8000 with the
//    boost timer (part +0x12C, u16, minus D_800BE9E4 per frame; rail_pickup_slot_release(player, 0) when it runs out) doubles
//    the throttle gain (0.64 -> 1.28) and forces stick y to 0x50. Part +0x128 bit 0x80 timers make the tank immune.
//    Steering: +0x22B eases toward stick x by a quarter per frame (set directly in multiplayer, snapped to 0 within
//    -4..4 when centred), heading +0x78 = +0x7A - steer * rate (rate from the speed, at least 10). Button 0x10
//    (brake; single player, or part +0x128 bit 2) stops the tank and sets part +0x75 / +0x78 to 0x1F.
//    Throttle +0x44 = stick y * gain (0 while +0x89 counts down). D_800BEB30 bit 0x2000 fires (aiscript_find_by_kind).
//  - Not driven: ctl_decay_button_latches (AI) while D_800C3E78 < D_8008FD8C.
//  - Then obj_state_common_update (physics; skipped in multiplayer while part +0x120 is set), the hit reactions (+0x232 = 0xD,
//    single-player squash / bounce on player +0x124), the track speeds (tank_set_track_speeds), the turret: auto-aim at
//    object part +0x129 (with +0x12A lead) when the driver's part +0x84 is set, else (driven) D-pad yaw (flags
//    bits 0 / 1), lock-on to the best target in a 35-degree cone (tank_yaw_offset_to_obj / angle_diff_signed_deg) or along the camera
//    view (views D_800DBFF0, 0x9A0 bytes each; ray cast collision_ray_cast and object test ray_sphere_intersect; the view object
//    +0x3D4 bit 0x40 of +0x128 = an object was hit). Pitch (part +0x1B8) is kept in -20..80 and yaw (+0x1BC) in
//    0..360; +0x2E4 / +0x2E6 = yaw * 50 / -pitch * 50.
#define TANK_PART(o) ((u8 *) (o)->unk31C)
#define TURRET_PITCH(o) (*(f32 *) (TANK_PART(o) + 0x1B8))
#define TURRET_YAW(o) (*(f32 *) (TANK_PART(o) + 0x1BC))
#define PAD(k) ((u8 *) &D_800BE748[(k) * 3])
#define PAD_BUTTONS(k) (((u16 **) D_800BE728[0])[k][0])
extern s8 D_800E0FFE[];
extern u16 D_800BEB30[];
f32 angle_diff_signed_deg(f32, f32);
f32 tank_yaw_offset_to_obj(u8 *, u8 *);
f32 tank_shell_aim_error(u8 *, f32, f32, f32, f32, f32);
void tank_set_track_speeds(u8 *, s32, s32);
s32 rail_pickup_slot_release(s32, s32);
int aiscript_find_by_kind(s32, s32);
void ctl_decay_button_latches(struct127 *);
void obj_state_common_update(struct127 *);
f32 obj_carry_release(struct127 *, f32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 obj_carry_pickup(struct127 *, f32, f32, s32, s32);
f32 obj_dist_xz(struct127 *, struct127 *);
s32 char_fx_send_event(s32, s16, s32, s32);
f32 math_atan2f(f32, f32);
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);
s32 ray_sphere_intersect(struct17 *, struct17 *, struct17 *, f32, s32, s32, f32 *, f32 *);
/* was func_150EDCC8 */
void tank_update(struct127 *o) {
    u8 *ob = (u8 *) o;
    s32 aimer;      // player whose part +0x84 / D_800E0FFE / pad flags steer the turret
    s32 alive;      // the driver's health (1 when not driven)
    u8 driven;
    u8 player;
    u16 heading0;
    u8 *part;
    u8 *pad;
    struct127 *drv;
    struct127 *tgt;
    s8 stick;
    s32 brake;
    s16 rate;
    s32 btn;
    f32 gain;
    s32 left, right;
    s16 turn;
    f32 speed;
    s32 against;

    alive = 1;
    aimer = (D_800BE616 != 0) ? ob[0x127] : 0;
    ob[0x2FC] = 0;
    ob[0x124] = 0;
    driven = 0;
    player = ob[0x124];
    heading0 = *(u16 *) (ob + 0x7A);
    ob[0x247] = 0x10;
    ob[0x248] = 8;
    if (D_800BE616 == 0) {
        if (ob[0x13C] != 0) {
            driven = 1;
            if (fabsf(o->xz_velocity) > 5.0f) {
                ob[0xD0] = 1;
                *(f32 *) (ob + 0x114) = 2.0f;
                if (o->xz_velocity < 0.0f) {
                    ob[0xD0] = 2;
                }
            }
        }
    } else {
        player = ob[0x127];
        if (player != 0xFF) {
            if (((u8 *) D_800CC2D0[player].unk31C)[0x84] == 0) {
                driven = 1;
            }
            drv = &D_800CC2D0[player];
            if (drv->health != 0) {
                part = TANK_PART(drv);
                if (part[0x128] & 0x80) {
                    if (*(u16 *) (part + 0x12C) != 0) {
                        o->immune = 0xFF;
                        part = TANK_PART(drv);
                        if (D_800BE9E4 < *(u16 *) (part + 0x12C)) {
                            *(u16 *) (part + 0x12C) -= D_800BE9E4;
                        } else {
                            *(u16 *) (part + 0x12C) = 0;
                            rail_pickup_slot_release(player, 0);
                            o->immune = 0;
                        }
                    }
                } else if ((part[0x128] & 0x10) && *(u16 *) (part + 0x12C) == 0) {
                    rail_pickup_slot_release(player, 0);
                }
            }
        }
    }

    if (driven) {
        drv = &D_800CC2D0[player];
        gain = 0.0f;
        brake = 0;
        alive = drv->health;
        if (alive != 0) {
            pad = PAD(player);
            stick = (s8) pad[2];
            ob[0x247] = 0x32;
            ob[0x248] = 0x32;
            gain = 0.64f;
            btn = player;
            part = TANK_PART(drv);
            if ((part[0x128] & 1) && (PAD_BUTTONS(player) & 0x8000) && *(u16 *) (part + 0x12C) != 0) {
                ob[0x247] = 0x1C;
                ob[0x248] = 0x1C;
                pad[3] = 0x50;
                gain = 0.64f + 0.64f;
                part = TANK_PART(drv);
                if (D_800BE9E4 < *(u16 *) (part + 0x12C)) {
                    *(u16 *) (part + 0x12C) -= D_800BE9E4;
                } else {
                    *(u16 *) (part + 0x12C) = 0;
                    rail_pickup_slot_release(player, 0);
                }
            }
            rate = (s16) (((f32) (s16) (18.0f - o->xz_velocity * (0.32f / gain)) * 0.5f + 9.0f) * D_800BE9A4);
            if (rate < 10) {
                rate = 10;
            }
            if ((PAD_BUTTONS(player) & 0x10) && ((TANK_PART(drv)[0x128] & 2) || D_800BE616 == 0)) {
                gain = 0.0f;
                brake = 0x1F;
                stick = 0;
                *(s8 *) (ob + 0x22B) = 0;
                o->xz_velocity = 0.0f;
            }
            *(s8 *) (ob + 0x22B) += (stick - *(s8 *) (ob + 0x22B)) / 4;
            if (D_800BE616 != 0) {
                *(s8 *) (ob + 0x22B) = stick;
            }
            if (stick == 0 && *(s8 *) (ob + 0x22B) >= -4 && *(s8 *) (ob + 0x22B) < 5) {
                *(s8 *) (ob + 0x22B) = 0;
            }
            *(u32 *) (ob + 0xF4) |= 0x40;
            *(s16 *) (ob + 0x78) = *(u16 *) (ob + 0x7A) - *(s8 *) (ob + 0x22B) * rate;
            if (D_800BE616 != 0 && btn < 2 && D_800E0FFE[player] != 0) {
                btn = D_800E0FFE[player];
            }
            if (D_800BEB30[btn] & 0x2000) {
                *(s16 *) (ob + 0x21C) = 0;
                *(s32 *) (ob + 0x218) = aiscript_find_by_kind(0, 2);
            }
        }
        if (o->disable_run != 0) {
            gain = 0.0f;
            o->disable_run--;
        }
        *(f32 *) (ob + 0x44) = (f32) (s8) PAD(player)[3] * gain;
        TANK_PART(drv)[0x75] = brake;
        TANK_PART(drv)[0x78] = brake;
    } else if (D_800C3E78 < D_8008FD8C) {
        btn = player;
        ctl_decay_button_latches(o);
        if (btn < 4 && (PAD_BUTTONS(player) & 0x2000)) {
            D_800CC288 = 0x2000;
        }
        if (D_800CC288 & 0x2000) {
            *(s16 *) (ob + 0x244) = 1;
        }
    }
    ob[0x247] = 0x32;
    ob[0x248] = 0x32;
    if (D_800BE616 == 0 || D_800C3E78 >= D_8008FD8C || TANK_PART(o)[0x120] == 0) {
        obj_state_common_update(o);
    }
    if (*(s32 *) ob == 0) {
        return;
    }

    // hit reactions
    if (ob[0x232] == 0xD) {
        obj_carry_release(o, 180.0f, 5, 0x44, 1, 0x10, 0xFF, 0, 0, 0);
    } else if (D_800BE616 == 0 && (D_800CC268 & 1)) {
        tgt = &D_800CC2D0[ob[0x124]];
        if (((u8 *) tgt)[0x65] == 0 && TANK_PART(tgt)[0x78] == 0 && (*(u32 *) (ob + 0x25C) & 0x400)) {
            if (*(f32 *) ((u8 *) tgt + 0x44) > 15.0f && tgt->y_velocity > 10.0f) {
                obj_carry_pickup(o, 68.0f, 4.0f, 0xD, 5);
            } else if (tgt->disable_run == 0 && *(f32 *) ((u8 *) tgt + 0x28) > 70.0f && tgt->stunned == 0
                       && obj_dist_xz(tgt, o) < 100.0f) {
                obj_carry_release(o, 180.0f, 5, 0x44, 1, 0x10, 0xFF, 0, 1, 0);
            }
        }
    }

    // track speeds: forward speed (blended with the throttle above |4|) +- the turn rate
    left = 0;
    right = 0;
    if (o->health != 0) {
        turn = (s16) (*(u16 *) (ob + 0x7A) - heading0) / 70;
        speed = o->xz_velocity;
        if (fabsf(*(f32 *) (ob + 0x44)) > 4.0f) {
            speed = speed * 0.6f + *(f32 *) (ob + 0x44) * 0.4f;
        }
        left = (s32) speed + turn;
        right = (s32) speed - turn;
    }
    tank_set_track_speeds(ob, left, right);
    if (ob[4] == 0x77 || ob[4] == 0x28) {
        against = (o->xz_velocity > 5.0f && *(f32 *) (ob + 0x44) <= 0.0f)
               || (o->xz_velocity < -5.0f && *(f32 *) (ob + 0x44) >= 0.0f);
        char_fx_send_event((s32) o, 0x19, against ? 0xD : 0xE, 0);
        ob[0x6C] = against ? 0xC + 0xA : 0xF + 0xA;
        ob[0x6D] = 0x13;
    }

    // turret
    if (((u8 *) D_800CC2D0[aimer].unk31C)[0x84] != 0) {
        s8 k = (s8) TANK_PART(o)[0x129];

        if (k >= 0) {
            f32 lead, rad, sx, sz, ang, ry, cp, h, lv, sy;

            tgt = &D_800CC2D0[k];
            {
                f32 dx = tgt->x_position - o->x_position;
                f32 dz = tgt->z_position - o->z_position;

                lead = tgt->xz_velocity * (sqrtf(dx * dx + dz * dz) / 200.0f);
            }
            rad = *(f32 *) ((u8 *) tgt + 0x40) * 0.017453292f;
            sx = sinf(rad) * lead;
            sz = cosf(rad) * lead;
            tgt->x_position += sx;
            tgt->z_position += sz;
            ang = tank_yaw_offset_to_obj(ob, (u8 *) tgt) * 0.017453292f;
            ry = sinf(ang);
            ry = cosf(*(f32 *) (ob + 0xC4) * 0.017453292f) * ry;
            cp = cosf(ang);
            h = math_atan2f(ry * 1000.0f, cosf(*(f32 *) (ob + 0xB8) * 0.017453292f) * cp * 1000.0f);
            lv = (f32) (s8) TANK_PART(o)[0x12A];
            sy = lv * 400.0f;
            TURRET_YAW(o) -= angle_diff_signed_deg(h * 57.295776f + lv * 10.0f, TURRET_YAW(o)) * 0.125f;
            TURRET_PITCH(o) += tank_shell_aim_error(ob, TURRET_PITCH(o) - *(f32 *) (ob + 0xB8), tgt->x_position,
                                             tgt->y_position, tgt->z_position, sy) * 0.001f;
            tgt->x_position -= sx;
            tgt->z_position -= sz;
        } else {
            TURRET_YAW(o) *= 0.9f;
            TURRET_PITCH(o) *= 0.9f;
        }
    } else if (driven && alive) {
        f32 best = 0.0f;
        f32 step = 3.0f * D_800BE9A4;
        s32 pick = -1;
        s8 view = 0;
        s32 n = D_8008FD8C;
        s32 i;

        if (D_800BE616 != 0 && aimer < 2 && D_800E0FFE[aimer] != 0) {
            view = D_800E0FFE[aimer] + 1;
        } else {
            if (*(u16 *) PAD(aimer) & 1) {
                TURRET_YAW(o) += step;
            }
            if (*(u16 *) PAD(aimer) & 2) {
                TURRET_YAW(o) -= step;
            }
        }
        if (TANK_PART(&D_800CC2D0[player])[0x197] != 0) {
            view = aimer + 1;
        }
        if (D_800BE616 == 0) {
            n = 0x19;
        }
        if (view == 0) {
            // lock-on: the target in a 35-degree cone around the turret yaw with the best (35 - angle) / distance
            for (i = 0; i < n; i++) {
                f32 off, dx, dz, d, score;

                if (i == aimer) {
                    continue;
                }
                tgt = &D_800CC2D0[i];
                if (D_800BE616 == 0 && !(*(u32 *) ((u8 *) tgt + 0xF8) & 0x40)) {
                    continue;
                }
                off = angle_diff_signed_deg(tank_yaw_offset_to_obj(ob, (u8 *) tgt), TURRET_YAW(o));
                if (off < 0.0f) {
                    off = -off;
                }
                off = 35.0f - off;
                if (off < 0.0f) {
                    off = 0.0f;
                }
                if (off > 0.0f) {
                    dx = o->x_position - tgt->x_position;
                    dz = o->z_position - tgt->z_position;
                    d = sqrtf(dx * dx + dz * dz);
                    if (d < 7000.0f) {
                        if (d < 1.0f) {
                            d = 1.0f;
                        }
                        score = off / d;
                        if (best < score) {
                            best = score;
                            pick = i;
                        }
                    }
                }
            }
            if (pick != -1) {
                f32 ty, adj, lim;

                tgt = &D_800CC2D0[pick];
                if (D_800BE616 != 0) {
                    ty = tgt->y_position + 40.0f;
                } else {
                    ty = (f32) *(s16 *) ((u8 *) tgt + 0x1AA);
                }
                adj = tank_shell_aim_error(ob, 0.0f, tgt->x_position, ty, tgt->z_position, 0.0f) * 0.001f;
                lim = 4.0f * D_800BE9A4;
                if (lim < adj) {
                    adj = lim;
                }
                if (adj < -lim) {
                    adj = -lim;
                }
                TURRET_PITCH(o) += adj;
            } else {
                TURRET_PITCH(o) *= 0.9f;
            }
        } else {
            // aim along camera view `view` - 1
            u8 *vw = (u8 *) D_800DBFF0 + (view - 1) * 0x9A0;
            u8 *vobj = *(u8 **) (vw + 0x3D4);

            if (vobj[0x197] != 0) {
                f32 p = -*(f32 *) (vobj + 0x170) - *(f32 *) (ob + 0xB8);
                f32 y = (*(f32 *) (ob + 0x40) - 90.0f) - *(f32 *) (vobj + 0x16C);

                while (p > 180.0f) {
                    p -= 360.0f;
                }
                while (p < -180.0f) {
                    p += 360.0f;
                }
                while (y > 180.0f) {
                    y -= 360.0f;
                }
                while (y < -180.0f) {
                    y += 360.0f;
                }
                TURRET_PITCH(o) = p;
                TURRET_YAW(o) = y;
            } else {
                f32 dir[3];
                f32 hit[3];
                f32 dist, inv;
                f32 ohit[3], onorm[3], ot, ou;
                s32 res;
                struct127 *obj;

                dir[0] = *(f32 *) (vw + 0x2BC) - *(f32 *) (vw + 0x2F8);
                dir[1] = *(f32 *) (vw + 0x2C0) - *(f32 *) (vw + 0x2FC);
                dir[2] = *(f32 *) (vw + 0x2C4) - *(f32 *) (vw + 0x300);
                inv = 1.0f / sqrtf(dir[2] * dir[2] + (dir[0] * dir[0] + dir[1] * dir[1]));
                dir[0] *= inv;
                dir[1] *= inv;
                dir[2] *= inv;
                dist = 100000.0f;
                res = collision_ray_cast(*(f32 *) (vw + 0x2F8), *(f32 *) (vw + 0x2FC), *(f32 *) (vw + 0x300), dir[0],
                                    dir[1], dir[2], 0, NULL, &hit[0], &hit[1], &hit[2], &dist, 0, 0, 0.0f);
                if (res != 0) {
                    res = 1;
                }
                obj = D_800CC2D0;
                for (i = 0; i < D_8008FD8C; i++, obj++) {
                    if (ob[0x128] != ((u8 *) obj)[0x128]) {
                        hit[0] = obj->x_position - *(f32 *) (vw + 0x2F8);
                        hit[2] = obj->z_position - *(f32 *) (vw + 0x300);
                        if (sqrtf(hit[0] * hit[0] + hit[2] * hit[2]) + 200.0f < dist
                            && ray_sphere_intersect((struct17 *) (vw + 0x2F8), (struct17 *) dir,
                                             (struct17 *) &obj->x_position, 150.0f, (s32) ohit, (s32) onorm, &ot,
                                             &ou) != 0
                            && ot < dist) {
                            dist = ot;
                            res = 2;
                        }
                    }
                }
                vobj[0x128] &= ~0x40;
                if (res != 0) {
                    if (res == 2) {
                        vobj[0x128] |= 0x40;
                    }
                    hit[0] = dir[0] * dist + *(f32 *) (vw + 0x2F8);
                    hit[1] = dir[1] * dist + *(f32 *) (vw + 0x2FC);
                    hit[2] = dir[2] * dist + *(f32 *) (vw + 0x300);
                    TURRET_PITCH(o) += tank_shell_aim_error(ob, 0.0f, hit[0], hit[1], hit[2], 0.0f) * 0.001f;
                } else {
                    TURRET_PITCH(o) *= 0.9f;
                }
            }
        }
    }
    if (TURRET_PITCH(o) < -20.0f) {
        TURRET_PITCH(o) = -20.0f;
    }
    if (TURRET_PITCH(o) > 80.0f) {
        TURRET_PITCH(o) = 80.0f;
    }
    if (TURRET_YAW(o) > 360.0f) {
        TURRET_YAW(o) -= 360.0f;
    }
    if (TURRET_YAW(o) < 0.0f) {
        TURRET_YAW(o) += 360.0f;
    }
    *(s16 *) (ob + 0x2E4) = (s16) (s32) (TURRET_YAW(o) * 50.0f);
    *(s16 *) (ob + 0x2E6) = -(s32) (TURRET_PITCH(o) * 50.0f);
}
#undef TANK_PART
#undef TURRET_PITCH
#undef TURRET_YAW
#undef PAD
#undef PAD_BUTTONS
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11AF60/tank_update.s")
#endif

#ifdef NON_MATCHING
/* P241: readable C for tank_dismount_enter (game_eu_11AF60, 73 insns). */
// rider_dismount_enter: entry 2 of the state table D_80086440 (`void (u8 *)`, like its neighbour tank_parked_update):
// puts the object in state 3 (+5; +0xE4 = 0, +0x125 = 0xFF, +0x328 = 0). When it carries a rider (+0x318), resets
// the rider onto object slot k (camera_set_followed_obj; k = 1 for player 3, else 0), sets byte +0x78 of the object's part
// +0x31C to 0x29, clears bit 0x10 of D_800BE748 entry k (6-byte entries), marks the rider's player bit in
// D_800CC2D0[k] +0x2FC and, if D_800CC2D0[k] +0x10A was set, calls screen_tint_start(0xFF, 0, 0, 180, 20, player)
// and clears it.
void camera_set_followed_obj(struct108 *, s32);
void screen_tint_start(s32, s32, s32, s32, s32, s32);
/* was func_150EF204 */
void tank_dismount_enter(u8 *obj) {
    u8 *rider;
    u8 *slot;
    s32 k;

    obj[5] = 3;
    *(s16 *) (obj + 0xE4) = 0;
    obj[0x125] = 0xFF;
    obj[0x328] = 0;
    rider = *(u8 **) (obj + 0x318);
    if (rider == NULL) {
        return;
    }
    k = (rider[0x23D] == 3) ? 1 : 0;
    camera_set_followed_obj((struct108 *) rider, k);
    (*(u8 **) (obj + 0x31C))[0x78] = 0x29;
    D_800BE748[k * 3] &= ~0x10;
    slot = (u8 *) &D_800CC2D0[k];
    slot[0x2FC] |= 1 << rider[0x23D];
    if (slot[0x10A] != 0) {
        screen_tint_start(0xFF, 0, 0, 180, 20, rider[0x23D]);
        slot[0x10A] = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11AF60/tank_dismount_enter.s")
#endif

void stub_obj_set_param(u8 *, s32, f32);
#ifndef NON_MATCHING
s32 obj_state_common_update(struct127 *); /* P249: the definition is void; NM blocks above declare it so */
#endif
/* was func_150EF328 */
void tank_parked_update(u8 *arg0) {
    if (arg0[5] != 3) {
        stub_obj_set_param(arg0, 0xF, 250.0f);
        arg0[5] = 3;
        *(s16 *)(arg0 + 0xE4) = 0;
        arg0[0x125] = 0xFF;
    }
    obj_state_common_update(arg0);
}
