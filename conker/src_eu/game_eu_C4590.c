#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15096970 */
void camera_timed_records_clear(void) {
    bzero(D_800D31E0, 0x6C);
    D_800D2DB4 = 0;
}

/* was func_15096DB0 */
s32 camera_timed_records_any_active(s32 arg0)
{
  s32 i;
  for (i = 0; i < arg0; i++) {
    if (*((u8 *)D_800D31E0 + i * 0x24) != 0) {
      return 1;
    }
  }
  return 0;
}

extern f32 D_800C3A20[];
extern s32 D_800DC450;
extern f32 D_800D31D8;
extern s32 D_800D3250[];
void camera_queue_event(struct108 *, s32, void *);

// camera_timed_record_update: steps timed camera record `idx` (D_800D31E0, 0x24 bytes, filled by camera script op 12:
// +1 camera id, +2 marker, +4 s16 timer, +0xC flags, +0x10 f32 speed, +0x20 saved +0x3A4). State 1 starts it: saves the
// camera's +0x2C0, builds the D_800C3A20 path record from marker D_800DC450[+2] (as op 10), switches the camera to
// modes 5 / 7, hides the camera object (+7 = 0, flag 0x200) unless flags bit 0, stores the speed as an int in
// D_800D3250[idx] and goes to state 2. State 2 counts the timer down by D_800BE9A0 (to 0 at once when the camera
// object's +0x1CA is 0); at 0 it restores +0x3A4 / +0x2C0, leaves mode 6 (unless flags bit 1), shows the object again
// (unless bit 0) and clears the record. Returns 0 when the record ended this call, 1 otherwise.
/* was func_15096E78 */
s32 camera_timed_record_update(s32 idx) {
    u8 *rec = D_800D31E0 + idx * 0x24;
    struct108 *cam;
    u8 *mk;

    if (rec[0] == 1) {
        cam = (struct108 *) ((u8 *) g_player_views + rec[1] * 0x9A0);
        D_800D31D8 = cam->unk2C0;
        D_800D2DB4 = 1;
        g_camera_timers[rec[1]] = 3;
        mk = (u8 *) D_800DC450 + rec[2] * 0x18;
        ((s32 *) D_800C3A20)[0] = 1;
        ((s32 *) D_800C3A20)[1] = 0;
        D_800C3A20[5] = (f32) *(s16 *) (mk + 0);
        D_800C3A20[6] = (f32) *(s16 *) (mk + 2);
        D_800C3A20[7] = (f32) *(s16 *) (mk + 4);
        D_800C3A20[8] = *(f32 *) (mk + 0x14);
        D_800C3A20[9] = *(f32 *) (mk + 0xC);
        D_800C3A20[2] = 0.0f;
        D_800C3A20[10] = *(f32 *) (mk + 0x10);
        camera_queue_event(cam, 5, NULL);
        camera_queue_event(cam, 7, D_800C3A20);
        if (!(*(s32 *) (rec + 0xC) & 1)) {
            *((u8 *) cam->unk3D0 + 7) = 0;
            *(s32 *) ((u8 *) cam->unk3D0 + 0x25C) |= 0x200;
        }
        D_800D3250[idx] = (s32) *(f32 *) (rec + 0x10);
        rec[0] = 2;
        return 1;
    }
    if (rec[0] == 2) {
        cam = (struct108 *) ((u8 *) g_player_views + rec[1] * 0x9A0);
        *(s16 *) (rec + 4) -= D_800BE9A0;
        if (*((u8 *) cam->unk3D0 + 0x1CA) == 0) {
            *(s16 *) (rec + 4) = 0;
        }
        if (*(s16 *) (rec + 4) > 0) {
            return 1;
        }
        *(f32 *) ((u8 *) cam + 0x3A4) = *(f32 *) (rec + 0x20);
        if (!(*(s32 *) (rec + 0xC) & 2)) {
            camera_queue_event(cam, 6, NULL);
        }
        D_800D2DB4 = 0;
        if (!(*(s32 *) (rec + 0xC) & 1)) {
            *(s32 *) ((u8 *) cam->unk3D0 + 0x25C) &= ~0x200;
            *((u8 *) cam->unk3D0 + 7) = 0xFF;
        }
        *(s16 *) (rec + 4) = 0;
        rec[0] = 0;
        cam->unk2C0 = D_800D31D8;
        return 0;
    }
    return 1;
}

s32 camera_timed_record_update(s32);

/* was func_15097118 */
void camera_timed_records_update(void) {
    s32 var_s0;
    u8 *var_s1;

    var_s0 = 0;
    if (D_800C35EA != 1) {
        var_s1 = D_800D31E0;
loop_2:
        if (*var_s1 != 0) {
            if (camera_timed_record_update(var_s0) == 0) {
                goto block_6;
            }
            return;
        }
block_6:
        var_s0 += 1;
        var_s1 += 0x24;
        if (var_s0 == 3) {

        } else {
            goto loop_2;
        }
    }
}

extern s32 D_800D3C60;
extern f32 D_800C3A20[];
extern u8 D_800C3A80;
extern s32 D_800DC740;
extern s32 g_camera_restore_skip; /* was D_800898C0 */
void camera_update_eye_base(struct108 *);
void camera_queue_event(struct108 *, s32, void *);
s32 obj_slot_by_spawn(s32);
void camera_set_followed_obj(struct108 *, s32);
s32 camera_timed_records_any_active(s32);
extern s32 D_800DC450;

#define CAM_F(c, off) (*(f32 *) ((u8 *) (c) + (off)))
#define CAM_B(c, off) (*(u8 *) ((u8 *) (c) + (off)))

/* camera_script_set: the "set" half of the camera script commands (table EU 80088894, the "get" half is
 * event_query_camera at 80088858). `id` picks the camera record g_player_views[id] (0x9A0 bytes), `op` the command and
 * `cmd` its words (arguments from cmd + 8). Covers the camera position / target vectors (+0x2A4, +0x2BC, +0x2F8),
 * the door camera (op 10 / 11: the D_800C3A20 path record from a D_800DC450 marker, camera_queue_event modes 5 / 7 / 6,
 * object 0's flag 0x200), timed camera records (op 12, D_800D31E0), fixed-point (/ 65536) speeds and the
 * remaining per-camera settings. Returns 1 for ops 4-9, 0 otherwise; 0 when id > g_last_player_index. */
/* was func_15097188 */
s32 event_action_camera(s32 id, s32 op, u8 *cmd) {
    struct108 *cam = (struct108 *) ((u8 *) g_player_views + id * 0x9A0);
    s32 *a = (s32 *) cmd;
    u8 *rec;
    u8 *mk;

    if (g_last_player_index < id) {
        return 0;
    }
    switch (op) {
    case 2: /* camera target */
        cam->unk2F8 = (f32) a[2];
        cam->unk2FC = (f32) a[3];
        cam->unk358 = cam->unk2FC;
        cam->unk300 = (f32) a[4];
        camera_update_eye_base(cam);
        return 0;
    case 3: /* camera position */
        cam->unk2A4 = (f32) a[2];
        cam->unk2A8 = (f32) a[3];
        CAM_F(cam, 0x2AC) = (f32) a[4];
        return 0;
    case 4:
        camera_push_mode(cam, a[2], a[3], a[4], 0x11);
        return 1;
    case 5:
        camera_pop_mode(cam, 0x11);
        return 1;
    case 6: /* set / clear flags */
        if (a[2] != 0) {
            cam->unk84 |= a[3];
        } else {
            cam->unk84 &= ~a[3];
        }
        return 1;
    case 7:
        cam->unk1E0 = a[2];
        cam->unk1B4 = a[3];
        return 1;
    case 8:
        if (*((u8 *) cam->unk3D4 + 0x120) == 0) {
            cam->unk374 = (f32) a[2];
            cam->unk34C = (f32) a[3];
            cam->unk348 = (f32) a[3];
        }
        return 1;
    case 9:
        cam->unk134 = a[2];
        return 1;
    case 10: /* door camera on: path record from marker a[2] */
        D_800D2DB4 = 1;
        g_camera_timers[id] = 3;
        mk = (u8 *) D_800DC450 + (a[2] & 0xFFF) * 0x18;
        ((s32 *) D_800C3A20)[0] = 1;
        ((s32 *) D_800C3A20)[1] = 0;
        D_800C3A20[5] = (f32) *(s16 *) (mk + 0);
        D_800C3A20[6] = (f32) *(s16 *) (mk + 2);
        D_800C3A20[7] = (f32) *(s16 *) (mk + 4);
        D_800C3A20[8] = *(f32 *) (mk + 0x14);
        D_800C3A20[9] = *(f32 *) (mk + 0xC);
        D_800C3A20[2] = 0.0f;
        D_800C3A20[10] = *(f32 *) (mk + 0x10);
        D_800C3A80 = 0;
        camera_queue_event(cam, 5, NULL);
        camera_queue_event(cam, 7, D_800C3A20);
        *(s32 *) ((u8 *) g_objects + 0x25C) |= 0x200;
        return 0;
    case 11: /* door camera off */
        camera_queue_event(cam, 6, NULL);
        D_800D2DB4 = 0;
        *(s32 *) ((u8 *) g_objects + 0x25C) &= ~0x200;
        return 0;
    case 12: /* timed camera record a[2] */
        rec = D_800D31E0 + a[2] * 0x24;
        *(f32 *) (rec + 0x20) = cam->unk37C;
        rec[1] = id;
        rec[2] = a[3];
        *(s16 *) (rec + 4) = a[4];
        rec[0] = 1;
        if (D_800D3C60 >= 6) {
            *(s32 *) (rec + 0xC) = a[5];
        } else {
            *(s32 *) (rec + 0xC) = 0;
        }
        if (D_800D3C60 >= 7) {
            *(f32 *) (rec + 0x10) = (f32) a[6] * (1.0f / 65536.0f);
        } else {
            *(f32 *) (rec + 0x10) = 1.0f;
        }
        if (camera_timed_records_any_active(a[2]) == 0) {
            camera_timed_record_update(a[2]);
        }
        return 0;
    case 14: /* position, second position and target */
        cam->unk2A4 = (f32) a[2];
        cam->unk2A8 = (f32) a[3];
        CAM_F(cam, 0x2AC) = (f32) a[4];
        cam->unk2BC = (f32) a[2];
        cam->unk2C0 = (f32) a[3];
        cam->unk2C4 = (f32) a[4];
        cam->unk2F8 = (f32) a[5];
        cam->unk2FC = (f32) a[6];
        cam->unk358 = cam->unk2FC;
        cam->unk300 = (f32) a[7];
        camera_update_eye_base(cam);
        return 0;
    case 15:
        cam->unk198 = (f32) a[2];
        if (D_800D3C60 == 4) {
            cam->unk194 = (f32) a[3];
        }
        return 0;
    case 16:
        cam->unk190 = (f32) a[2];
        if (D_800D3C60 == 4) {
            cam->unk18C = (f32) a[3];
        }
        return 0;
    case 17:
        if ((D_800D3C60 == 5 && a[4] != 0) || *(s32 *) ((u8 *) &D_800DC740 + id * 0x68) == 5) {
            camera_shake_start(cam, a[2], a[3]);
            return 1;
        }
        return 0;
    case 18:
        camera_set_followed_obj(cam, obj_slot_by_spawn(a[2] & 0xFFF));
        return 0;
    case 19:
        camera_set_second_target(cam, obj_slot_by_spawn(a[2] & 0xFFF));
        return 0;
    case 20: /* 16.16 speeds */
        cam->unk1A4 = (f32) a[2] * (1.0f / 65536.0f);
        cam->unk1A8 = (f32) a[3] * (1.0f / 65536.0f);
        if (D_800D3C60 == 5 && a[4] != 0) {
            cam->unk19C = cam->unk1A4;
            cam->unk1A0 = cam->unk1A8;
        }
        return 0;
    case 21: /* move marker a[2] */
        mk = (u8 *) D_800DC450 + (a[2] & 0xFFF) * 0x18;
        *(s16 *) (mk + 0) = a[3];
        *(s16 *) (mk + 2) = a[4];
        *(s16 *) (mk + 4) = a[5];
        return 0;
    case 22:
        cam->unk23C = 1;
        return 0;
    case 23:
        CAM_F(cam, 0x7C0) = (f32) a[2] * (1.0f / 65536.0f);
        return 0;
    case 24:
        if (D_800D3C60 == 5) {
            CAM_B(cam, 0x78C) = 1;
            CAM_F(cam, 0x794) = (f32) a[2];
            CAM_F(cam, 0x790) = (f32) a[3];
            CAM_F(cam, 0x798) = (f32) a[4];
        } else {
            CAM_B(cam, 0x78C) = 0;
        }
        return 0;
    case 25:
        cam->pad3A4 = (f32) a[2] * (1.0f / 65536.0f);
        g_camera_event_heading = cam->pad3A4;
        return 0;
    case 26:
        camera_init_controller(cam);
        return 0;
    case 27:
        g_camera_restore_skip = a[2] - 1;
        return 0;
    default:
        return 0;
    }
}
#undef CAM_F
#undef CAM_B

f32 vec3f_dot(f32 *, struct17 *);
extern s32 D_800DC450;

/* was func_150979AC */
s32 event_query_camera(s32 arg0, s32 arg1, u8 *arg2) {
    struct {
        struct127 * u28;
        f32 u2C;
        struct17 u30;
        f32 u3C;
        f32 u40;
        f32 u44;
        u8 pad48[0x4];
        struct108 * u4C;
    } sp;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f2;
    struct108 *temp_a3;
    struct127 *temp_v0;
    u8 *temp_v1;

    temp_a3 = &g_player_views[arg0];
    if (g_last_player_index < arg0) {
        goto block_13;
    }
    switch (arg1) {
    case 31:
        return (s32) (temp_a3->unk390 * 65536.0f);
    case 30:
        return (s32) (temp_a3->unk37C * 65536.0f);
    case 29:
        return (s32) *(D_800D31E0 + ((*(s32 *)((u8 *)arg2 + 8)) * 0x24));
    case 32:
        temp_v1 = (((*(s32 *)((u8 *)arg2 + 8)) & 0xFFF) * 0x18) + D_800DC450;
        temp_f2 = temp_a3->unk2F8 - (f32) (*(s16 *)((u8 *)temp_v1 + 0));
        temp_f12 = temp_a3->unk300 - (f32) (*(s16 *)((u8 *)temp_v1 + 4));
        return (s32) sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
    case 33:
        sp.u4C = temp_a3;
        temp_v0 = obj_find_by_spawn((*(s32 *)((u8 *)arg2 + 8)) & 0xFFF, temp_a3);
        sp.u28 = temp_v0;
        if (temp_v0 == NULL) {
            return -1;
        }
        sp.u4C = temp_a3;
        temp_f12_2 = temp_a3->unk39C + 1.5707964f;
        sp.u2C = temp_f12_2;
        sp.u3C = sinf(temp_f12_2);
        sp.u40 = 0.0f;
        sp.u44 = cosf(temp_f12_2);
        vec3_diff((struct17 *) &temp_a3->unk2F8, (struct17 *) &sp.u28->x_position, &sp.u30);
        sp.u30.unk4 = 0.0f;
        if (vec3f_dot(&sp.u3C, &sp.u30) >= 0.0f) {
            return -1;
        }
        return 1;
    default:
block_13:
        return 0;
    }
}
extern s32 D_800D3250[];
/* Pushes player `id` back along the direction between its two position vectors (+0x2A4 and +0x2F8): d =
 * normalised direction (vec3_diff / vec3_normalize); both vectors move by d * (-2.5, -2.0, -2.5) times the
 * per-player factor D_800D3250[id]. Only while D_800D2DB4 is set. Returns the record (v0 holds it on both paths;
 * the caller in game_14FF90 declares s32 and ignores it). */
/* was func_15097BA8 */
s32 camera_timed_push_back(s32 id) {
    struct108 *r = &g_player_views[id];
    struct17 *a;
    struct17 *b;
    struct17 d;

    if (D_800D2DB4 != 0) {
        a = (struct17 *) &r->unk2A4;
        b = (struct17 *) &r->unk2F8;
        vec3_diff(a, b, &d);
        vec3_normalize(&d, &d);
        a->unk0 += d.unk0 * -2.5f * (f32) D_800D3250[id];
        a->unk4 += d.unk4 * -2.0f * (f32) D_800D3250[id];
        a->unk8 += d.unk8 * -2.5f * (f32) D_800D3250[id];
        b->unk0 += d.unk0 * -2.5f * (f32) D_800D3250[id];
        b->unk4 += d.unk4 * -2.0f * (f32) D_800D3250[id];
        b->unk8 += d.unk8 * -2.5f * (f32) D_800D3250[id];
    }
    return (s32) r;
}
