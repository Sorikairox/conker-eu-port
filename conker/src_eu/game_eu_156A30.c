#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 camera_event_queue_empty(u8 *arg0);
s32 event_dispatch(s32, s32, ...);
void camera_queue_event(u8 *, s32, void *);
s32 camera_pop_mode(struct108 *arg0, s32 arg1);
u8 *camera_dequeue_event(u8 *arg0);
void camera_exit_aim_mode(struct108 *);
void camera_shake_reset(struct108 *arg0);
void aim_hud_clear(u8 *arg0);
s32 camera_push_mode(struct108 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void camera_start_transition(struct108 *arg0, s32 arg1, s32 arg2);
void camera_apply_request(struct108 *);
void aim_hud_spawn_for_mode(u8 *arg0, s32 arg1);
void camera_update_follow(struct108 *);
void triggers_update(s32 arg0);
void trigger_zones_update_object(struct127 *arg0);
void camera_dispatch_mode(struct108 *);
void camera_lean_from_heading(struct108 *, f32 *, f32 *);
f32 math_angle_diff_deg(f32 arg0, f32 arg1);
void camera_projection_update(s32 player, f32 fovX, f32 fovY, f32 scale, f32 width);
void camera_update_dir_vector(s32 player);
void collision_find_floor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD);
void camera_update_state_flags(struct108 *arg0);
f32 sinf(f32);
f32 cosf(f32);
extern u8 *D_800DC440;       /* saved camera states, 0x9A0 bytes each */
extern u16 D_800BEB30[];     /* per player: view flags (camera +0x36A) */
extern s32 D_800898C0;       /* frames to skip the "restore saved camera" event */
extern s32 D_800898C4[];     /* per player: saved +0x3D4 byte 0x197 */
extern s32 D_800898D4[];     /* per player: saved +0x3D4 byte 0x198 */
extern f32 D_800898E4[3];    /* event 7 orbit offset {0, 0, -400} */
extern u8 D_800C3A92;
extern s32 D_800C3A98;
extern s32 D_800C3A9C;
extern f32 D_800C3A6C;

/* camera_process_events: per-frame camera event pump (called by camera_update_controller and the game camera setup in
 * game_eu_4A070.c). +0x6CC = 0; a pending script request +0x734 is started (camera_queue_event with record
 * D_800D34B8[id & 0xFFF], 0x34 bytes, id kept in +0x700) when event_dispatch(1, id, 6, 0x9000) and +0x738 allow it,
 * else cleared. If the queue (camera_event_queue_empty) is busy, only flag 1 of +0x2C sets mode 0xC; otherwise every queued
 * event (camera_dequeue_event: {type, data}) is handled until the queue is empty:
 *  1: copy a camera request (mode, values, point, ...) from the data into +0x6FC..+0x72C, +0x6CC = 1;
 *  5: save the camera: D_800DC440[data] = D_800DBFF0[player], keeping the target's +0x197 / +0x198 bytes in
 *     D_800898C4 / D_800898D4 (or resetting them, mode 1, when the target's +0x78 is 0); then mode 0xA;
 *  6: restore it (unless D_800898C0 counts down, only in camera mode 0x40000): with +0x834 set only the view flags
 *     and camera_start_transition; else D_800DBFF0[player] = D_800DC440[data], re-applies the request and the target bytes,
 *     resets eye / target history, and reruns the per-frame camera steps;
 *  7: place the camera at a fixed eye (+0x2F8) and target (data kind 0 / 2: given; else orbiting the eye at
 *     -400 by the data angles), then optional FOV (camera_projection_update) and the camera collision probe collision_find_floor;
 *  8: +0x3A4 = data[3]; 9: +0x364 = data[0]; 10: +0x834 = data +0x10, +0x820 = data[3] (999: target heading - 180).
 */
/* was func_15129220 */
void camera_process_events(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    s32 *ev;
    u8 *d;
    u8 *tgt;
    s32 *dst;
    s32 *src;
    s32 i;
    u8 pl;
    f32 heading;
    f32 ang;
    f32 pos[3];
    f32 probe;

    *(s16 *)(p + 0x6CC) = 0;
    if (*(s32 *)(p + 0x734) != 0 && camera_event_queue_empty(p) != 0) {
        if (event_dispatch(1, *(s32 *)(p + 0x734), 6, 0x9000) != 0 && *(s32 *)(p + 0x738) != 0) {
            camera_queue_event(p, 1, (s32 *)(D_800D34B8 + (*(s32 *)(p + 0x734) & 0xFFF) * 0x34));
            *(s16 *)(p + 0x700) = *(s32 *)(p + 0x734) & 0xFFF;
        } else {
            *(s32 *)(p + 0x734) = 0;
            *(s32 *)(p + 0x738) = 0;
        }
    }
    if (camera_event_queue_empty(p) != 0) {
        if (*(s32 *)(p + 0x2C) & 1) {
            camera_pop_mode(arg0, 0xC);
        }
        return;
    }
    while (camera_event_queue_empty(p) == 0) {
        ev = (s32 *)camera_dequeue_event(p);
        switch (ev[0]) {
        case 5: /* save the camera state */
            tgt = *(u8 **)(p + 0x3D4);
            p[0x23E] = tgt[0x78];
            if (p[0x23E] == 0) {
                camera_pop_mode(arg0, 1);
                (*(u8 **)(p + 0x3D4))[0x198] = 0;
                (*(u8 **)(p + 0x3D4))[0x197] = 0;
                *(s16 *)(p + 0x5F8) = 1;
                *(s16 *)(p + 0x5FC) = 2;
                (*(u8 **)(p + 0x3D4))[0x198] = 0;
                *(s16 *)(p + 0x73C) = 0;
                camera_exit_aim_mode(arg0);
                D_800898C4[p[0x23D]] = 0;
                D_800898D4[p[0x23D]] = 0;
            } else {
                D_800898C4[p[0x23D]] = tgt[0x197];
                D_800898D4[p[0x23D]] = (*(u8 **)(p + 0x3D4))[0x198];
            }
            camera_shake_reset(arg0);
            if (p[0x84C] != 0) {
                aim_hud_clear(p);
                p[0x84C] = 0;
            }
            src = (s32 *)((u8 *)D_800DBFF0 + p[0x23D] * 0x9A0);
            dst = (s32 *)(D_800DC440 + ev[1] * 0x9A0);
            for (i = 0; i < 0x9A0 / 4; i++) {
                dst[i] = src[i];
            }
            camera_push_mode(arg0, 0x40000, 0, 0, 0xA);
            *(s32 *)(p + 0x5F0) |= 4;
            *(f32 *)(p + 0x3A4) = -1.0f;
            break;

        case 6: /* restore the saved camera state */
            p[0x23E] = (*(u8 **)(p + 0x3D4))[0x78];
            if (D_800898C0 != 0) {
                D_800898C0--;
                break;
            }
            if (*(s32 *)(p + 0x2C) != 0x40000) {
                break;
            }
            heading = *(f32 *)(p + 0x3A4);
            if (D_800D2DB0 != 999.0f) {
                heading = D_800D2DB0;
                D_800D2DB0 = 999.0f;
            }
            camera_pop_mode(arg0, 0xA);
            if (D_800C3A92 != 0) {
                *(f32 *)(p + 0x820) = 999.0f;
                *(s16 *)(p + 0x834) = 0;
                *(s16 *)(p + 0x7F4) = 0;
            }
            if (*(u16 *)(p + 0x834) != 0) {
                pl = p[0x23D];
                *(s32 *)(p + 0x36C) = ((s32 *)D_800BE728[0])[pl];
                *(u16 *)(p + 0x36A) = D_800BEB30[pl];
                camera_start_transition(arg0, D_800C3A9C, D_800C3A98);
                p[0x23C] = 0;
                break;
            }
            src = (s32 *)(D_800DC440 + ev[1] * 0x9A0);
            dst = (s32 *)((u8 *)D_800DBFF0 + p[0x23D] * 0x9A0);
            for (i = 0; i < 0x9A0 / 4; i++) {
                dst[i] = src[i];
            }
            pl = p[0x23D];
            tgt = *(u8 **)(p + 0x3D4);
            *(s32 *)(p + 0x36C) = ((s32 *)D_800BE728[0])[pl];
            *(u16 *)(p + 0x36A) = D_800BEB30[pl];
            p[0x23C] = 1;
            p[0x23E] = tgt[0x78];
            camera_apply_request(arg0);
            if (D_800898D4[p[0x23D]] != 0) {
                *(u16 *)(p + 0x36A) |= 0x10;
                **(u16 **)(p + 0x36C) |= 0x10;
                heading = *(f32 *)(p + 0x774);
            } else if (D_800898C4[p[0x23D]] != 0) {
                if ((p[0x23E] == 0xC && *(u16 *)(*(u8 **)(p + 0x3D0) + 0x84) != 0x76) || p[0x23E] == 0x1B
                    || (**(u16 **)(p + 0x36C) & 0x10)) {
                    *(u16 *)(p + 0x36A) |= 0x10;
                    **(u16 **)(p + 0x36C) |= 0x10;
                    (*(u8 **)(p + 0x3D4))[0x197] = D_800898C4[p[0x23D]];
                    aim_hud_spawn_for_mode(p, p[0x23E]);
                    heading = *(f32 *)(p + 0x774);
                } else {
                    (*(u8 **)(p + 0x3D4))[0x198] = 0;
                    *(s16 *)(p + 0x73C) = 0;
                    D_800898C4[p[0x23D]] = 0;
                    D_800898D4[p[0x23D]] = 0;
                    camera_exit_aim_mode(arg0);
                }
            } else {
                (*(u8 **)(p + 0x3D4))[0x198] = 0;
                *(s16 *)(p + 0x73C) = 0;
                camera_exit_aim_mode(arg0);
            }
            camera_update_follow(arg0);
            if (*(s32 *)(p + 0x5F0) & 2) {
                heading = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x40) - 180.0f;
            }
            *(f32 *)(p + 0x37C) = heading;
            *(f32 *)(p + 0x39C) = heading * 0.017453292f;
            for (i = 0; i < 3; i++) {
                ((f32 *)(p + 0x2E0))[i] = ((f32 *)(p + 0x2BC))[i];
            }
            for (i = 0; i < 3; i++) {
                ((f32 *)(p + 0x2EC))[i] = ((f32 *)(p + 0x2F8))[i];
            }
            for (i = 0; i < 3; i++) {
                ((f32 *)(p + 0x2C8))[i] = ((f32 *)(p + 0x2BC))[i];
            }
            for (i = 0; i < 3; i++) {
                ((f32 *)(p + 0x304))[i] = ((f32 *)(p + 0x2F8))[i];
            }
            triggers_update(D_800BE9E4);
            trigger_zones_update_object((struct127 *)((u8 *)D_800CC2D0 + p[0x23D] * 0x32C));
            camera_apply_request(arg0);
            camera_lean_from_heading(arg0, NULL, NULL);
            camera_dispatch_mode(arg0);
            camera_update_follow(arg0);
            *(s32 *)(p + 0x5F0) |= 4;
            *(f32 *)(p + 0x670) = 0.0f;
            *(f32 *)(p + 0x678) = 0.0f;
            p[0x8ED] = 1;
            p[0x23C] = 1;
            *(f32 *)(p + 0x674) = 1.0f;
            break;

        case 8:
            *(f32 *)(p + 0x3A4) = ((f32 *)ev[1])[3];
            break;

        case 9:
            *(f32 *)(p + 0x364) = ((f32 *)ev[1])[0];
            break;

        case 10:
            d = (u8 *)ev[1];
            *(s16 *)(p + 0x834) = *(s32 *)(d + 0x10);
            if (*(f32 *)(d + 0xC) == 999.0f) {
                *(f32 *)(p + 0x820) = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x40) - 180.0f;
            } else {
                *(f32 *)(p + 0x820) = *(f32 *)(d + 0xC);
            }
            break;

        case 7: /* fixed camera: eye from the data, target given or orbiting the eye */
            d = (u8 *)ev[1];
            *(f32 *)(p + 0x2F8) = *(f32 *)(d + 0x14);
            *(f32 *)(p + 0x2FC) = *(f32 *)(d + 0x18);
            *(f32 *)(p + 0x300) = *(f32 *)(d + 0x1C);
            if (*(s32 *)d == 0 || *(s32 *)d == 2) {
                *(f32 *)(p + 0x2A4) = *(f32 *)(d + 0x20);
                *(f32 *)(p + 0x2A8) = *(f32 *)(d + 0x24);
                *(f32 *)(p + 0x2AC) = *(f32 *)(d + 0x28);
                *(f32 *)(p + 0x19C) = *(f32 *)(d + 0x30);
                *(f32 *)(p + 0x1A0) = *(f32 *)(d + 0x34);
                *(f32 *)(p + 0x1A4) = *(f32 *)(d + 0x30);
                *(f32 *)(p + 0x1A8) = *(f32 *)(d + 0x34);
                for (i = 0; i < 3; i++) {
                    ((f32 *)(p + 0x2BC))[i] = ((f32 *)(p + 0x2A4))[i];
                }
                *(f32 *)(p + 0x3A8) = 0.0f;
                *(f32 *)(p + 0x5E8) = 0.0f;
                *(f32 *)(p + 0x38C) = 0.0f;
                *(f32 *)(p + 0x5EC) = *(f32 *)(d + 0x2C);
            } else {
                pos[0] = D_800898E4[0];
                pos[1] = D_800898E4[1];
                pos[2] = D_800898E4[2];
                while (*(f32 *)(d + 0x20) > 180.0f) {
                    *(f32 *)(d + 0x20) -= 360.0f;
                }
                while (*(f32 *)(d + 0x24) > 180.0f) {
                    *(f32 *)(d + 0x24) -= 360.0f;
                }
                while (*(f32 *)(d + 0x28) > 180.0f) {
                    *(f32 *)(d + 0x28) -= 360.0f;
                }
                *(f32 *)(p + 0x5EC) = *(f32 *)(d + 0x20);
                /* pitch by +0x24 */
                ang = *(f32 *)(d + 0x24) * 0.017453292f;
                pos[1] = sinf(ang) * -pos[2];
                pos[2] = cosf(ang) * pos[2];
                if (D_800DBFF4[0] != 0) {
                    *(f32 *)(p + 0x37C) = *(f32 *)(d + 0x28);
                    *(f32 *)(p + 0x380) = *(f32 *)(d + 0x28);
                    *(f32 *)(p + 0x39C) = *(f32 *)(p + 0x37C) * 0.017453292f;
                    *(f32 *)(p + 0x3A0) = *(f32 *)(p + 0x380) * 0.017453292f;
                }
                /* yaw: from the current heading +0x37C toward +0x28 */
                heading = *(f32 *)(p + 0x37C);
                ang = (heading + math_angle_diff_deg(heading, *(f32 *)(d + 0x28)) * 1.0f) * 0.017453292f;
                pos[0] = sinf(ang) * pos[2];
                pos[2] = cosf(ang) * pos[2];
                pos[0] += *(f32 *)(d + 0x14);
                pos[1] += *(f32 *)(d + 0x18);
                pos[2] += *(f32 *)(d + 0x1C);
                *(f32 *)(p + 0x19C) = *(f32 *)(d + 0x2C);
                *(f32 *)(p + 0x1A0) = *(f32 *)(d + 0x30);
                *(f32 *)(p + 0x1A4) = *(f32 *)(d + 0x2C);
                *(f32 *)(p + 0x1A8) = *(f32 *)(d + 0x30);
                *(f32 *)(p + 0x2A4) = pos[0];
                *(f32 *)(p + 0x2A8) = pos[1];
                *(f32 *)(p + 0x2AC) = pos[2];
                for (i = 0; i < 3; i++) {
                    ((f32 *)(p + 0x2BC))[i] = ((f32 *)(p + 0x2A4))[i];
                }
                *(f32 *)(p + 0x3A8) = 0.0f;
                *(f32 *)(p + 0x5E8) = 0.0f;
                *(f32 *)(p + 0x38C) = 0.0f;
            }
            if ((&D_800C35EA)[*(s32 *)(d + 4)] == 1) {
                D_800C3A6C = *(f32 *)(d + 8);
                camera_projection_update(p[0x23D], *(f32 *)(p + 0x19C), *(f32 *)(p + 0x1A0), 1.0f, 0.0f);
            }
            if (D_800DBFF4[0] != 0) {
                camera_update_dir_vector(0);
            }
            if (D_800BEAC0 == 0) {
                collision_find_floor((s32)(p + 0x644), (s32)(p + 0x648), (s32)&probe, (s32)(p + 0x360), (s32)(p + 0x640), 0,
                              *(f32 *)(p + 0x2F8), *(f32 *)(p + 0x2FC), *(f32 *)(p + 0x300), *(f32 *)(p + 0x2FC), 0, 0,
                              -10000.0f, *(f32 *)(p + 0x2FC));
                camera_update_state_flags(arg0);
            }
            break;

        case 1: /* camera request */
            d = (u8 *)ev[1];
            *(s32 *)(p + 0x6FC) = d[0x17];
            *(s32 *)(p + 0x718) = *(s32 *)(d + 0x18);
            *(s32 *)(p + 0x71C) = *(s32 *)(d + 0x1C);
            *(s32 *)(p + 0x704) = *(s32 *)(d + 0x20);
            *(s16 *)(p + 0x70C) = *(s16 *)(d + 0x0);
            *(s16 *)(p + 0x70E) = *(s16 *)(d + 0x2);
            *(s16 *)(p + 0x710) = *(s16 *)(d + 0x4);
            *(s16 *)(p + 0x712) = *(s16 *)(d + 0x6);
            *(s16 *)(p + 0x714) = *(s16 *)(d + 0x8);
            *(s16 *)(p + 0x716) = *(s16 *)(d + 0xA);
            *(f32 *)(p + 0x720) = *(f32 *)(d + 0x28);
            *(f32 *)(p + 0x724) = *(f32 *)(d + 0x24);
            *(f32 *)(p + 0x728) = *(f32 *)(d + 0x30);
            *(s16 *)(p + 0x6CC) = 1;
            *(f32 *)(p + 0x72C) = *(f32 *)(d + 0x2C);
            break;
        }
    }
}

extern s16 D_800898F0;
extern u8 D_800DC458[];
extern f32 D_800A39F0;

/* was func_15129E30 */
void camera_pivot_slot_reset(u8 *arg0, s32 arg1)
{
  if (D_800898F0 != 0)
  {
    *((s16 *) (D_800DC458 + arg0[0x23D] * 0x24 + 2)) = 0;
    *((f32 *) (D_800DC458 + arg0[0x23D] * 0x24 + 4)) = -1.0f;
    *((f32 *) (D_800DC458 + arg0[0x23D] * 0x24 + 8)) = D_800A39F0;
  }
}

/* P142 */
void vec3_diff(struct17 *a, struct17 *b, struct17 *out);
void vec3_normalize(struct17 *v, struct17 *out);
void vec3_scale(struct17 *v, f32 len, struct17 *out);
void math_spring_approach(f32 *cur, f32 target, f32 *vel, f32 arg3, f32 arg4, f32 arg5);
s32 floor_tri_height(f32 x, f32 z, s32 tri, u8 *packed, f32 *out);
void collision_find_floor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD);
s32 camera_yaw_fade_in(struct108 *);
void camera_update_state_flags(struct108 *);
extern s16 D_800898F0;
extern f32 D_800A39F4;
extern f32 D_800A39F8;
extern f32 D_800A39FC;
/* camera_follow_update: camera mode 0x40 (camera_dispatch_mode). Unless D_800898F0 is 0 or +0x73C is set: the pivot
 * +0x27C = +0x288; the camera target is the pivot plus the direction pivot -> eye (+0x2BC) scaled to the eye
 * distance minus +0x278 (at least 0), its y part scaled by D_800A39F4 unless +0x704 & 0xF. The camera position
 * +0x2F8 eases towards it (math_spring_approach with velocity +0x3C0, rates 3 / 2 / 3, +0x7B4), or snaps there (also
 * +0x304, velocity 0) when +0x23C. Then camera_yaw_fade_in; when snapped, flag 0x400000 of +0x84, or no floor under
 * the camera (floor_tri_height into +0x35C), the collision probe collision_find_floor runs (+0x360 kept unless the result
 * +0x364 equals D_800A39FC) and camera_update_state_flags. Finally the four zoom pairs +0x964..+0x980 = 1 / 2. */
/* was func_15129EA4 */
void camera_pivot_follow_update(struct108 *cam) {
    u8 *c = (u8 *) cam;
    f32 dir[3];
    s32 probe[4];
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 tx;
    f32 ty;
    f32 tz;

    if (D_800898F0 == 0 || *(s16 *) (c + 0x73C) != 0) {
        return;
    }
    *(f32 *) (c + 0x27C) = *(f32 *) (c + 0x288);
    *(f32 *) (c + 0x280) = *(f32 *) (c + 0x28C);
    *(f32 *) (c + 0x284) = *(f32 *) (c + 0x290);
    vec3_diff((struct17 *) (c + 0x27C), (struct17 *) (c + 0x2BC), (struct17 *) dir);
    vec3_normalize((struct17 *) dir, (struct17 *) dir);
    dx = *(f32 *) (c + 0x2BC) - *(f32 *) (c + 0x27C);
    dy = *(f32 *) (c + 0x2C0) - *(f32 *) (c + 0x280);
    dz = *(f32 *) (c + 0x2C4) - *(f32 *) (c + 0x284);
    dist = sqrtf(dx * dx + dy * dy + dz * dz) - *(f32 *) (c + 0x278);
    if (dist < 0.0f) {
        dist = 0.0f;
    }
    vec3_scale((struct17 *) dir, dist, (struct17 *) dir);
    tx = *(f32 *) (c + 0x27C) + dir[0];
    if (*(s32 *) (c + 0x704) & 0xF) {
        ty = *(f32 *) (c + 0x280);
    } else {
        ty = *(f32 *) (c + 0x280) + dir[1] * D_800A39F4;
    }
    tz = *(f32 *) (c + 0x284) + dir[2];
    if (c[0x23C] != 0) {
        *(f32 *) (c + 0x2F8) = tx;
        *(f32 *) (c + 0x304) = tx;
        *(f32 *) (c + 0x3C0) = 0.0f;
    } else {
        math_spring_approach((f32 *) (c + 0x2F8), tx, (f32 *) (c + 0x3C0), 1.0f, 3.0f, *(f32 *) (c + 0x7B4));
    }
    if (c[0x23C] != 0) {
        *(f32 *) (c + 0x2FC) = ty;
        *(f32 *) (c + 0x308) = ty;
        *(f32 *) (c + 0x3C4) = 0.0f;
    } else {
        math_spring_approach((f32 *) (c + 0x2FC), ty, (f32 *) (c + 0x3C4), 1.0f, 2.0f, *(f32 *) (c + 0x7B4));
    }
    if (c[0x23C] != 0) {
        *(f32 *) (c + 0x300) = tz;
        *(f32 *) (c + 0x30C) = tz;
        *(f32 *) (c + 0x3C8) = 0.0f;
    } else {
        math_spring_approach((f32 *) (c + 0x300), tz, (f32 *) (c + 0x3C8), 1.0f, 3.0f, *(f32 *) (c + 0x7B4));
    }
    camera_yaw_fade_in(cam);
    if (c[0x23C] != 0 || (*(s32 *) (c + 0x84) & 0x400000) ||
        floor_tri_height(*(f32 *) (c + 0x2F8), *(f32 *) (c + 0x300), *(s32 *) (c + 0x644), c + 0x648,
                      (f32 *) (c + 0x35C)) == 0) {
        collision_find_floor(0, 0, (s32) probe, (s32) (c + 0x360), (s32) (c + 0x640), 0, *(f32 *) (c + 0x2F8),
                      *(f32 *) (c + 0x2FC), *(f32 *) (c + 0x300), *(f32 *) (c + 0x2FC), 0, 0, D_800A39F8,
                      *(f32 *) (c + 0x2FC));
        if (D_800A39FC != *(f32 *) (c + 0x364)) {
            *(f32 *) (c + 0x360) = *(f32 *) (c + 0x364);
        }
        camera_update_state_flags(cam);
    }
    *(f32 *) (c + 0x974) = 1.0f;
    *(f32 *) (c + 0x964) = 1.0f;
    *(f32 *) (c + 0x97C) = 1.0f;
    *(f32 *) (c + 0x96C) = 1.0f;
    *(f32 *) (c + 0x978) = 2.0f;
    *(f32 *) (c + 0x968) = 2.0f;
    *(f32 *) (c + 0x980) = 2.0f;
    *(f32 *) (c + 0x970) = 2.0f;
}
