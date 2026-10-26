#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *allocate_memory(s32, s32, s32, s32);

/* was func_1503BAB0 */
void tail_record_alloc(u8 *arg0) {
    (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x11C)) = allocate_memory(0x50, 1, 0, 0);
    bzero((*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x11C)), 0x50);
    (*(f32 *)((u8 *)((*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x11C))) + 0x44)) = 30.0f;
    (*(s16 *)((u8 *)((*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x11C))) + 0x4C)) = (s16) (random_int() % 30U);
}

extern u16 D_80098BE0[3];
extern u16 D_80098B2C;
extern u16 D_80098B2E;
extern u16 D_80098B30[88];

/*
 * P70: object kind flags (called from obj_model_reset after it clears +0x2FB). Only for the active state 1:
 * an animation / model id +0x84 listed in D_80098BE0 (3 ids) sets bit 1 (2), one of D_80098B2C, D_80098B2E or the
 * 88 ids of D_80098B30 sets bit 0 (1). The first table wins.
 */
/* was func_1503B840 */
void obj_set_kind_look_flags(struct127 *obj) {
    u16 kind;
    s32 i;

    if (obj->interaction_state != 1) {
        return;
    }
    kind = obj->unk84.uh;
    for (i = 0; i < 3; i++) {
        if (kind == D_80098BE0[i]) {
            obj->unk2FB |= 2;
            return;
        }
    }
    if (kind == D_80098B2C) {
        obj->unk2FB |= 1;
        return;
    }
    if (kind == D_80098B2E) {
        obj->unk2FB |= 1;
        return;
    }
    for (i = 0; i < 88; i++) {
        if (kind == D_80098B30[i]) {
            obj->unk2FB |= 1;
            return;
        }
    }
}

extern u8 D_800CC9EB;
/* was func_1503BC4C */
s32 tail_get_mode(s32 arg0, u8 *arg1) {
    s32 temp_v0;
    temp_v0 = *((u8 *)&D_800CC9EB + (arg0 * 0x32C));
    if (temp_v0 & 2) {
        arg1[0x4E] = 0;
        return 0;
    }
    if (temp_v0 & 1) {
        return 0;
    }
    return 1;
}

f32 sinf(f32);
f32 cosf(f32);
f32 math_angle_diff_deg(f32, f32);
f32 math_atan2f(f32, f32);
f32 math_acosf_lut(f32);
extern u8 g_slowmo_divisor; /* was D_800BEE2C */
extern u8 D_800C40BD;
extern f32 D_800C4428[3];
extern f32 D_80098AA0[4];
extern f32 D_80098AB0[4];
extern f32 D_80098AC0[4];
extern f32 D_80098AD0[4];
extern f32 D_80098AE0[4];
extern f32 D_80098AF0[5];
extern f32 D_80098B04[5];
extern f32 D_80098B18[5];
extern f32 D_80098BE8;
extern f32 D_80098BEC;
extern f32 D_80098BF0;
extern f32 D_80098BF4;
extern f32 D_80098BF8;
extern f32 D_80098BFC;
extern f32 D_80098C00;
extern f32 D_80098C04;
extern f32 D_80098C08;
extern f32 D_80098C0C;
void tail_record_alloc(u8 *);
s32 tail_get_mode(s32, u8 *);
void tail_build_joint_matrices(s32, s32, f32, u8 *);

/* Tail chain record (obj->unk31C->unk11C, 0x50 bytes, allocated by tail_record_alloc). */
typedef struct {
    /* 0x00 */ f32 p[5][3];    /* chain points: p[0] = root joint 24, p[1..4] simulated */
    /* 0x3C */ f32 phase;      /* walk wave phase (degrees) */
    /* 0x40 */ f32 sway;       /* idle sway angle (degrees) */
    /* 0x44 */ f32 swaySpeed;
    /* 0x48 */ f32 swayAmp;
    /* 0x4C */ s16 timer;      /* idle timer: counts down to a new random sway */
    /* 0x4E */ u8 fade;        /* frames of fade-in left (mode 2) */
} TailRec;

/* the joint matrices (obj->unk1D4): 0x40 bytes each, translation at +0x30 */
#define JOINT_POS(obj, i) ((f32 *) ((u8 *) (obj)->unk1D4 + (i) * 0x40 + 0x30))
#define CAM_S32(cam, off) (*(s32 *) ((u8 *) (cam) + (off)))
#define CAM_F32(cam, off) (*(f32 *) ((u8 *) (cam) + (off)))
#define OBJ_F32(obj, off) (*(f32 *) ((u8 *) (obj) + (off)))
#define OBJ_U8(obj, off) (*(u8 *) ((u8 *) (obj) + (off)))
#define OBJ_U16(obj, off) (*(u16 *) ((u8 *) (obj) + (off)))

/* the camera of the object (+0x318) is in its close-follow mode (0x100) and above -17 */
#define CAMERA_CLOSE(cam) ((cam) != NULL && CAM_S32(cam, 0x2C) == 0x100 && CAM_F32(cam, 0x388) > -17.0f)

/*
 * P70: Conker's tail (chain of 4 segments hanging from joint 24, called from obj_update_tail_for_conker).
 * The record is created on first use. tail_get_mode gives the mode: 0 = hidden / not simulated (the chain just
 * follows the joints 24..27), 1 = simulated, 2 = simulated and fading in (+0x4E frames left, given to tail_build_joint_matrices
 * as a 0..1 factor). Without joint matrices the object is only marked in D_800C4000 to reset the chain next time.
 * Simulation: per-segment offsets off[] (walk wave from the xz speed, lift by animation, idle sway or a turn towards
 * the close camera) are added to each point's target; each point eases towards it (D_80098AC0 / D_80098AD0 weights,
 * none on a reset), is pulled back when the bend exceeds 45 degrees (D_80098AE0), and is put at the segment length
 * (D_80098AA0, or D_80098AB0 for ids 0x80 / 0xB0) from the previous point, scaled by the object scale.
 * D_800C4428 is the anchor before the first point (joint 0). The pause flags g_game_paused / g_slowmo_divisor freeze the
 * state but still rebuild the chain.
 */
/* was func_1503BCAC */
void tail_update_conker(s32 arg0) {
    struct127 *obj = &g_objects[arg0];
    TailRec *rec;
    struct108 *cam;
    f32 *len;
    f32 *lift_tbl;
    f32 off[5][3];
    f32 goal[3];
    f32 dir[3];
    f32 d[3];
    f32 speed, wave, lift, a, b, s, c, ang, f, mag, fade;
    s32 mode, reset, camLook, i, k;
    u16 anim;

    camLook = 0;
    if (obj->unk31C == NULL) {
        return;
    }
    rec = *(TailRec **) ((u8 *) obj->unk31C + 0x11C);
    if (rec == NULL) {
        tail_record_alloc((u8 *) obj);
        rec = *(TailRec **) ((u8 *) obj->unk31C + 0x11C);
    }
    mode = tail_get_mode(arg0, (u8 *) rec);

    if (obj->unk1D4 == NULL) {
        D_800C4000 |= 1 << arg0;
        return;
    }

    /* reset: requested while the joints were missing, or by g_camera_timers / +0x2FD */
    reset = 0;
    if (D_800C4000 & (1 << arg0)) {
        D_800C4000 &= ~(1 << arg0);
        reset = 1;
    }
    if (*(s32 *) g_camera_timers != 0 || OBJ_U8(obj, 0x2FD) != 0) {
        reset = 1;
    }
    if (reset) {
        rec->swaySpeed = 30.0f;
        rec->phase = 0.0f;
        rec->sway = 0.0f;
        rec->swayAmp = 100.0f;
        rec->timer = random_int() % 30U;
    }

    /* hidden: count down the fade-in instead */
    if (mode == 0) {
        if ((s32) rec->fade > g_frame_ticks) {
            if (g_game_paused == 0) {
                rec->fade -= g_frame_ticks;
            }
            mode = 2;
        } else {
            rec->fade = 0;
        }
    }

    D_800C4428[0] = JOINT_POS(obj, 0)[0];
    D_800C4428[1] = JOINT_POS(obj, 0)[1];
    D_800C4428[2] = JOINT_POS(obj, 0)[2];

    if (mode == 0) {
        for (i = 0; i < 4; i++) {
            rec->p[i][0] = JOINT_POS(obj, 24 + i)[0];
            rec->p[i][1] = JOINT_POS(obj, 24 + i)[1];
            rec->p[i][2] = JOINT_POS(obj, 24 + i)[2];
        }
        return;
    }

    rec->p[0][0] = JOINT_POS(obj, 24)[0];
    rec->p[0][1] = JOINT_POS(obj, 24)[1];
    rec->p[0][2] = JOINT_POS(obj, 24)[2];
    if (obj->id == 0x80 || obj->id == 0xB0) {
        len = D_80098AB0;
    } else {
        len = D_80098AA0;
    }
    for (k = 0; k < 5; k++) {
        off[k][0] = 0.0f;
        off[k][1] = 0.0f;
        off[k][2] = 0.0f;
    }

    /* walk wave: up / down at the root and the tip, phase advanced by the speed */
    speed = obj->xz_velocity;
    if (speed < 0.0f) {
        speed = 0.0f;
    } else if (speed > 60.0f) {
        speed = 60.0f;
    }
    if (obj->unk28 > 3.0f) {
        speed *= 0.5f;
    }
    wave = sinf(rec->phase * D_80098BE8) * speed;
    if (g_game_paused == 0 && g_slowmo_divisor == 0) {
        rec->phase += speed;
        if (rec->phase >= 360.0f) {
            rec->phase -= 360.0f;
        }
    }
    off[0][1] += wave;
    off[4][1] += sinf((rec->phase + 180.0f) * D_80098BEC) * speed;

    /* close camera: swing the tail out of the view (angle between the facing +0x76 and the camera) */
    cam = obj->camera;
    if (CAMERA_CLOSE(cam)) {
        s32 pushed = 0;

        a = math_atan2f((CAM_F32(cam, 0x2F8) + CAM_F32(cam, 0x74C)) - obj->x_position,
                          (CAM_F32(cam, 0x300) + CAM_F32(cam, 0x754)) - obj->z_position) * D_80098BF0 + 90.0f;
        if (a >= 360.0f) {
            a -= 360.0f;
        }
        b = math_angle_diff_deg((f32) OBJ_U16(obj, 0x76) * 0.005493164f, a);
        if (fabsf(b) < 90.0f) {
            if (fabsf(b) < 0.5f) {
                b = 0.0f;
            }
            if (b < -15.0f) {
                b = -15.0f;
            } else if (b > 15.0f) {
                b = 15.0f;
            }
            if (b > 0.0f) {
                if (b < 23.0f) {
                    b = 23.0f;
                    pushed = 1;
                }
            } else if (b > -23.0f) {
                b = -23.0f;
                pushed = 1;
            }
            if (pushed) {
                b = rec->sway + (b - rec->sway) * D_80098BF4;
            }
            rec->sway = b;
            rec->timer = 60;
            rec->swayAmp = 200.0f;
            camLook = 1;
        }
    }

    /* facing */
    anim = obj->unk84.uh;
    a = obj->unk40 * D_80098BF8;
    if (anim == 0x122 || anim == 0x128 || anim == 0x129 || anim == 0x12A) {
        a -= D_80098BFC;
    }
    s = sinf(a);
    c = cosf(a);

    anim = obj->unk84.uh;
    if (anim == 0x24 || anim == 0x22 || anim == 0xD1) {
        /* these animations: anchor at the root height, moved one unit forward while +0xB8 > 0 */
        D_800C4428[1] = rec->p[0][1];
        if (OBJ_F32(obj, 0xB8) > 0.0f) {
            D_800C4428[0] = rec->p[0][0] + s;
            D_800C4428[2] = rec->p[0][2] + c;
        }
        off[0][1] -= wave;
        off[1][1] += wave;
    } else if (obj->unk28 < 0.5f) {
        /* on the ground: lift the tail, less with speed */
        speed = obj->xz_velocity;
        if (speed < 0.0f) {
            speed = 0.0f;
        } else if (speed > 30.0f) {
            speed = 30.0f;
        }
        lift = 60.0f - (speed + speed);
        if (D_800C35EA == 1 && D_800C40BD < 100) {
            lift = lift * (f32) D_800C40BD * D_80098C00;
        }
        if (obj->id == 0x80 || obj->id == 0xB0) {
            lift_tbl = D_80098B18;
        } else if (anim == 0x1B || anim == 0x18B) {
            for (k = 0; k < 5; k++) {
                off[k][1] = 0.0f;
            }
            lift_tbl = D_80098B04;
            lift = 60.0f;
        } else {
            lift_tbl = D_80098AF0;
        }
        if (*((u8 *) obj->unk31C + 0x78) == 0x3B && CAMERA_CLOSE(cam)) {
            lift = 0.0f;
        }
        for (k = 0; k < 5; k++) {
            off[k][1] += lift * lift_tbl[k];
        }

        if (speed == 0.0f) {
            if (rec->timer != 0 && !camLook) {
                /* idle: wait, then pick a new random sway */
                rec->timer -= g_frame_ticks;
                if (rec->timer <= 0) {
                    rec->sway = 0.0f;
                    rec->swayAmp = (f32) (u32) (random_int() % 100U);
                    f = (f32) (u32) (random_int() % 10U + 10);
                    if (random_int() & 1) {
                        rec->swaySpeed = f;
                    } else {
                        rec->swaySpeed = -f;
                    }
                    rec->timer = 0;
                }
            } else {
                /* sway sideways (root and tip), across the facing */
                a = sinf(rec->sway * D_80098C04) * rec->swayAmp;
                b = sinf((rec->sway + 30.0f) * D_80098C08) * rec->swayAmp * 5.0f;
                off[4][0] += c * b;
                off[0][0] += c * a;
                off[4][2] += -s * b;
                off[0][2] += -s * a;
                if (g_game_paused == 0 && g_slowmo_divisor == 0 && !camLook) {
                    f = rec->swaySpeed;
                    rec->sway += f;
                    if (rec->sway > 360.0f || rec->sway < -360.0f) {
                        if (fabsf(f) > 15.0f) {
                            rec->swaySpeed = f * 0.5f;
                            rec->swayAmp *= 0.5f;
                            if (rec->sway > 360.0f) {
                                rec->sway -= 360.0f;
                            } else {
                                rec->sway += 360.0f;
                            }
                        } else {
                            rec->timer = random_int() % 200U;
                        }
                    }
                }
            }
        } else if (g_game_paused == 0 && g_slowmo_divisor == 0) {
            rec->timer = 200;
        }
    }

    if (mode == 2) {
        fade = (f32) (30 - rec->fade) / 30.0f;
    } else {
        fade = 0.0f; /* the asm passes an unset stack word here */
    }

    /* the chain: point i+1 follows point i */
    for (i = 0; i < 4; i++) {
        f32 *p0 = rec->p[i];
        f32 *p1 = rec->p[i + 1];

        /* direction of the previous segment (into p0, moved by the offset) */
        d[0] = off[i][0] * obj->xz_scale + p0[0];
        d[1] = off[i][1] * obj->y_scale + p0[1];
        d[2] = off[i][2] * obj->xz_scale + p0[2];
        if (i == 0) {
            d[0] -= D_800C4428[0];
            d[1] -= D_800C4428[1];
            d[2] -= D_800C4428[2];
        } else {
            d[0] -= rec->p[i - 1][0];
            d[1] -= rec->p[i - 1][1];
            d[2] -= rec->p[i - 1][2];
        }
        mag = 1.0f / sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
        d[0] *= mag;
        d[1] *= mag;
        d[2] *= mag;
        goal[0] = len[i] * d[0] * obj->xz_scale + p0[0];
        goal[1] = len[i] * d[1] * obj->y_scale + p0[1];
        goal[2] = len[i] * d[2] * obj->xz_scale + p0[2];

        /* ease towards the straight continuation */
        if (g_game_paused == 0 && g_slowmo_divisor == 0) {
            f = goal[0] - p1[0];
            if (!reset) {
                f *= D_80098AC0[i];
            }
            p1[0] += f;
            f = goal[1] - p1[1];
            if (!reset) {
                f *= D_80098AD0[i];
            }
            p1[1] += f;
            f = goal[2] - p1[2];
            if (!reset) {
                f *= D_80098AC0[i];
            }
            p1[2] += f;
        }

        /* limit the bend */
        dir[0] = p1[0] - p0[0];
        dir[1] = p1[1] - p0[1];
        dir[2] = p1[2] - p0[2];
        mag = 1.0f / sqrtf(dir[2] * dir[2] + (dir[0] * dir[0] + dir[1] * dir[1]));
        dir[0] *= mag;
        dir[1] *= mag;
        dir[2] *= mag;
        ang = fabsf(math_acosf_lut(dir[2] * d[2] + (d[0] * dir[0] + d[1] * dir[1])) * D_80098C0C);
        if (g_game_paused == 0 && g_slowmo_divisor == 0 && D_80098AE0[i] < ang) {
            f = 1.0f - D_80098AE0[i] / ang;
            if (reset) {
                f = 1.0f;
            }
            p1[0] += (goal[0] - p1[0]) * f;
            p1[1] += (goal[1] - p1[1]) * f;
            p1[2] += (goal[2] - p1[2]) * f;
        }

        /* keep the segment length */
        dir[0] = p1[0] - p0[0];
        dir[1] = p1[1] - p0[1];
        dir[2] = p1[2] - p0[2];
        mag = 1.0f / sqrtf(dir[2] * dir[2] + (dir[0] * dir[0] + dir[1] * dir[1]));
        dir[0] *= mag;
        dir[1] *= mag;
        dir[2] *= mag;
        p1[0] = len[i] * dir[0] * obj->xz_scale + p0[0];
        p1[1] = len[i] * dir[1] * obj->y_scale + p0[1];
        p1[2] = len[i] * dir[2] * obj->xz_scale + p0[2];
    }
    tail_build_joint_matrices(arg0, mode, fade, (u8 *) rec);
}

void mtx_rotate_scale_3x3(f32 mtx[4][4], f32, f32, f32, f32, f32, f32);
void mtxf_look_at(f32 mtx[4][4], f32 posx, f32 posy, f32 posz, f32 lookx, f32 looky, f32 lookz, f32 upx, f32 upy, f32 upz);
void mtxf_scale_set_trans(f32 mtx[4][4], f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6);

/*
 * P70: tail joint matrices from the chain of tail_update_conker (rec = the 0x50-byte tail record, points p[0..4]).
 * Joint 24 + i looks from p[i] to p[i+1], with the up vector of the previous joint (the object's root rotation
 * +0xB8 / +0x40 / +0xC4 for i = 0), then gets the object scale and p[i] as translation. In mode 2 (fading in) both
 * points are first blended towards the animated joints 24..27 (and the tip extrapolated from 26 -> 27) by fade;
 * otherwise the fade counter +0x4E is re-armed to 30 frames.
 */
/* was func_1503CE88 */
void tail_build_joint_matrices(s32 idx, s32 mode, f32 fade, u8 *rec) {
    struct127 *obj = &g_objects[idx];
    f32 (*pts)[3] = (f32 (*)[3]) rec;
    f32 root[4][4];
    f32 anim[5][3];
    f32 up[3];
    f32 (*joint)[4];
    f32 (*prev)[4];
    f32 ax, ay, az, bx, by, bz, mag;
    s32 i;

    mtx_rotate_scale_3x3(root, OBJ_F32(obj, 0xB8), obj->unk40, OBJ_F32(obj, 0xC4), 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 4; i++) {
        joint = (f32 (*)[4]) ((u8 *) obj->unk1D4 + (24 + i) * 0x40);
        prev = (i == 0) ? root : (f32 (*)[4]) ((u8 *) obj->unk1D4 + (23 + i) * 0x40);
        up[0] = prev[1][0];
        up[1] = prev[1][1];
        up[2] = prev[1][2];
        mag = sqrtf(up[2] * up[2] + (up[0] * up[0] + up[1] * up[1]));
        if (mag != 0.0f) {
            mag = 1.0f / mag;
            up[0] *= mag;
            up[1] *= mag;
            up[2] *= mag;
        }
        ax = pts[i][0];
        ay = pts[i][1];
        az = pts[i][2];
        bx = pts[i + 1][0];
        by = pts[i + 1][1];
        bz = pts[i + 1][2];
        if (mode == 2) {
            if (i == 0) {
                s32 k;

                for (k = 0; k < 4; k++) {
                    anim[k][0] = JOINT_POS(obj, 24 + k)[0];
                    anim[k][1] = JOINT_POS(obj, 24 + k)[1];
                    anim[k][2] = JOINT_POS(obj, 24 + k)[2];
                }
                anim[4][0] = anim[3][0] + (anim[3][0] - anim[2][0]);
                anim[4][1] = anim[3][1] + (anim[3][1] - anim[2][1]);
                anim[4][2] = anim[3][2] + (anim[3][2] - anim[2][2]);
            }
            ax += (anim[i][0] - ax) * fade;
            ay += (anim[i][1] - ay) * fade;
            az += (anim[i][2] - az) * fade;
            bx += (anim[i + 1][0] - bx) * fade;
            by += (anim[i + 1][1] - by) * fade;
            bz += (anim[i + 1][2] - bz) * fade;
        }
        if (ax == bx && az == bz) {
            ax += 1.0f; /* straight down: avoid a degenerate look-at */
        }
        mtxf_look_at(joint, ax, ay, az, bx, by, bz, up[0], up[1], up[2]);
        mtxf_scale_set_trans(joint, obj->xz_scale, obj->y_scale, obj->xz_scale, ax, ay, az);
    }
    if (mode != 2) {
        rec[0x4E] = 30;
    }
}
