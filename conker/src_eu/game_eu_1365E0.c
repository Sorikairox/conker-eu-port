#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *mesh_effect_spawn(s8 *, s32, s32, s32, s32);
s32 light_ctrl_alloc(s8 *, s32, s32, s32, s32);
s32 memcpy(u8 *, u8 **, s32);

/* was func_15108850 */
void swing_lamp_spawn(s32 arg0) {
    struct {
        u8 * u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        s32 u3C;
        s8 u40;
        u8 pad41[0x3];
        s32 u44;
        s8 u48;
        u8 pad49[0x3];
        s8 u4C;
        s8 u4D;
        s8 u4E;
        u8 pad4F[0x1];
        s16 u50;
        u8 pad52[0x2];
        s32 u54;
        s32 u58;
        s32 u5C;
        s32 u60;
        s32 u64;
        s32 u68;
        s32 u6C;
        s8 u70;
        s8 u71;
        u8 pad72[0xA];
        s32 u7C;
        s32 u80;
        s8 u84;
        u8 pad85[0xB];
        u8 * u90;
        s8 u94;
        s8 u95;
        s16 u96;
        s8 u98;
        u8 pad99[0x3];
        u8 * u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        s32 uB0;
        s8 uB4;
        u8 padB5[0x3];
        s32 uB8;
        s8 uBC;
        u8 padBD[0x3];
        s8 uC0;
        s8 uC1;
        s8 uC2;
        u8 padC3[0x1];
        s16 uC4;
        u8 padC6[0x2];
        s32 uC8;
        s32 uCC;
        s32 uD0;
        s32 uD4;
        s32 uD8;
        s32 uDC;
        s32 uE0;
        s8 uE4;
        s8 uE5;
        u8 padE6[0xA];
        s32 uF0;
        s32 uF4;
        s8 uF8;
        u8 padF9[0x3];
        u8 * uFC;
    } sp;
    s32 temp_v0_2;
    u8 *temp_v0;
    u8 *temp_v0_3;

    sp.uB0 = 0x3E7;
    sp.uB4 = 0xFF;
    sp.uB8 = -1;
    sp.uBC = 1;
    sp.uC2 = 1;
    sp.uC4 = 0x12C;
    sp.uF0 = 9;
    sp.u9C = NULL;
    sp.uA0 = 0.0f;
    sp.uA4 = 0.0f;
    sp.uA8 = 0.0f;
    sp.uC0 = 0;
    sp.uC1 = 0;
    sp.uF4 = 0x1AB;
    sp.uC8 = 1;
    sp.uCC = 0x220205;
    sp.uD0 = 0x40600;
    sp.uE4 = 0;
    sp.uE5 = 0;
    sp.uD4 = 1;
    sp.uD8 = 0x36;
    sp.uDC = 0x80;
    sp.uE0 = 0x20;
    sp.uF8 = 1;
    sp.uAC = 226.0f;
    temp_v0 = mesh_effect_spawn(&sp.uC0, 1, 0x24, 0xFF, 1);
    if (temp_v0 != NULL) {
        sp.uFC = temp_v0;
        memcpy(temp_v0 + (*(s32 *)((u8 *)temp_v0 + 0x50)) + 0xF8, &sp.u9C, 0x24);
        sp.u90 = sp.uFC;
        sp.u94 = 2;
        sp.u95 = 8;
        sp.u96 = 0x12C;
        sp.u98 = 0x13;
        temp_v0_2 = light_ctrl_alloc(&sp.u94, arg0, 4, 0xFF, 1);
        if (temp_v0_2 != 0) {
            memcpy(temp_v0_2 + 0x18, &sp.u90, 4);
        }
    }
    sp.u3C = 0x3E7;
    sp.u40 = 0xFF;
    sp.u44 = -1;
    sp.u48 = 1;
    sp.u4D = 1;
    sp.u4E = 4;
    sp.u50 = 0x12C;
    sp.u7C = 9;
    sp.u28 = NULL;
    sp.u2C = 0.0f;
    sp.u30 = 0.0f;
    sp.u34 = 0.0f;
    sp.u4C = 0;
    sp.u80 = 0x1AC;
    sp.u54 = 1;
    sp.u58 = 0x220205;
    sp.u5C = 0x40600;
    sp.u70 = 0;
    sp.u71 = 0;
    sp.u60 = 1;
    sp.u64 = 0x36;
    sp.u68 = 0x80;
    sp.u6C = 0x20;
    sp.u84 = 1;
    sp.u38 = 226.0f;
    temp_v0_3 = mesh_effect_spawn(&sp.u4C, 1, 0x24, 0xFF, 1);
    if (temp_v0_3 != NULL) {
        memcpy(temp_v0_3 + (*(s32 *)((u8 *)temp_v0_3 + 0x50)) + 0xF8, &sp.u28, 0x24);
    }
}
s32 swing_lamp_target_timer_tick(u8 *);
s32 swing_lamp_height_update(u8 *);

/* was func_15109034 */
s32 swing_lamp_update(u8 *arg0) {
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *new_var;

    // permuter: the offset is read through a pointer local and added with +=
    temp_s0_2 = arg0 + 0x50;
    temp_s0 = arg0;
    temp_s0 += *(s32 *)temp_s0_2;
    temp_s0_2 = temp_s0 + 0xF8;
    *(f32 *)(temp_s0_2 + 8) = *(f32 *)(temp_s0 + 0x100) + (0.0857f * g_frame_step_f);
    *(f32 *)(temp_s0_2 + 0xC) = *(f32 *)(temp_s0_2 + 0xC) + (0.0783f * g_frame_step_f);
    temp_s0 = temp_s0_2;
    *(f32 *)(temp_s0 + 8) = wrap_angle_rad(*(f32 *)(temp_s0 + 8));
    *(f32 *)(temp_s0 + 0xC) = wrap_angle_rad(*(f32 *)(temp_s0 + 0xC));
    *(f32 *)(temp_s0 + 0) = sinf(*(f32 *)(temp_s0 + 8)) * 7.1050005f;
    new_var = temp_s0;
    *(f32 *)(temp_s0 + 4) = sinf(*(f32 *)(new_var + 0xC)) * 7.1050005f;
    swing_lamp_target_timer_tick(arg0);
    swing_lamp_height_update(arg0);
    return 1;
}

/* was func_15109100 */
s32 swing_lamp_target_timer_tick(u8 *arg0) {
    s32 temp_t0;
    u8 *temp_v0;

    temp_v0 = &arg0[(*(s32 *)((u8 *)arg0 + 0x50))];
    if ((*(s32 *)((u8 *)temp_v0 + 0x10C)) != 0x3E7) {
        temp_t0 = (*(s32 *)((u8 *)(&temp_v0[0xF8]) + 0x1C)) - g_frame_ticks;
        (*(s32 *)((u8 *)(&temp_v0[0xF8]) + 0x1C)) = temp_t0;
        if (temp_t0 < 0) {
            (*(s32 *)((u8 *)(&temp_v0[0xF8]) + 0x14)) = 0x3E7;
        }
    }
    return (s32) (temp_v0 + 0xF8);
}
/* was func_15109140 */
s32 swing_lamp_height_update(u8 *arg0) {
    s32 temp_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0_2 = &arg0[(*(s32 *)((u8 *)arg0 + 0x50))];
    temp_v1 = (*(s32 *)((u8 *)temp_v0_2 + 0x10C));
    temp_v0 = temp_v0_2 + 0xF8;
    if (temp_v1 == 0x3E7) {
        (*(f32 *)((u8 *)(&temp_v0_2[0xF8]) + 0x10)) = 226.0f;
        return (s32) temp_v0;
    }
    if (D_800C35EA == 1) {
        (*(f32 *)((u8 *)(&temp_v0_2[0xF8]) + 0x10)) = (f32) D_800C3958[temp_v1].unk4;
        return (s32) temp_v0;
    }
    (*(f32 *)((u8 *)(&temp_v0_2[0xF8]) + 0x10)) = 226.0f;
    return (s32) temp_v0;
}
extern f32 g_swing_lamp_phase_x_rate; /* was D_800A2850 */
extern f32 g_swing_lamp_phase_z_rate; /* was D_800A2854 */
extern f32 g_swing_lamp_amplitude; /* was D_800A2858 */
/* was func_151091B8 */
s32 swing_lamp_update_b(u8 *arg0) {
    u8 *temp_s0;
    u8 *temp_s0_2;

    temp_s0 = arg0 + (*(s32 *)((u8 *)arg0 + 0x50));
    temp_s0_2 = temp_s0 + 0xF8;
    (*(f32 *)((u8 *)temp_s0_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x100)) + (g_swing_lamp_phase_x_rate * g_frame_step_f));
    (*(f32 *)((u8 *)temp_s0_2 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s0_2 + 0xC)) + (g_swing_lamp_phase_z_rate * g_frame_step_f));
    (*(f32 *)((u8 *)temp_s0_2 + 8)) = wrap_angle_rad((*(f32 *)((u8 *)temp_s0_2 + 8)));
    (*(f32 *)((u8 *)temp_s0_2 + 0xC)) = wrap_angle_rad((*(f32 *)((u8 *)temp_s0_2 + 0xC)));
    (*(f32 *)((u8 *)temp_s0_2 + 0)) = (f32) (sinf((*(f32 *)((u8 *)temp_s0_2 + 8))) * g_swing_lamp_amplitude);
    (*(f32 *)((u8 *)temp_s0_2 + 4)) = (f32) (sinf((*(f32 *)((u8 *)temp_s0_2 + 0xC))) * g_swing_lamp_amplitude);
    swing_lamp_target_timer_tick(arg0);
    swing_lamp_height_update(arg0);
    if ((*(u8 *)((u8 *)temp_s0_2 + 0x20)) != 0) {
    s32 pad;
        (*(s8 *)((u8 *)arg0 + 0x12)) = 4;
        return 1;
    }
    (*(s8 *)((u8 *)arg0 + 0x12)) = 2;
    return 1;
}
/* was func_151092A4 */
s32 swing_lamp_matrix_build(u8 *arg0, s32 arg1) {
    f32 mf[4][4];
    u8 *q;

    q = arg0; q += *(s32 *)(arg0 + 0x50); q += 0xF8;
    mtxf_rotate_xyz_deg(mf, *(f32 *)q, 0.0f, *(f32 *)(q + 4));
    mf[3][1] = *(f32 *)(q + 0x10);
    mf[0][0] *= 0.157f;
    mf[0][1] *= 0.157f;
    mf[0][2] *= 0.157f;
    mf[1][0] *= 0.157f;
    mf[1][1] *= 0.157f;
    mf[1][2] *= 0.157f;
    mf[2][0] *= 0.157f;
    mf[2][1] *= 0.157f;
    mf[2][2] *= 0.157f;
    guMtxF2L(mf, &((Mtx *)(arg0 + 0x78))[g_dl_buf_index]);
    return 1;
}

s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, s32, s32, f32 *, f32 *, f32 *, s32, s32, s32, f32);
typedef struct { f32 x, y, z; } V3_09390;

/* was func_15109390 */
s32 swing_lamp_light_update(u8 *arg0)
{
  u8 *base;
  u8 *p;
  float new_var;
  V3_09390 out;
  f32 mf[4][4];
  s32 pad2[3]; // frame padding
  V3_09390 hit;
  base = *((u8 **) (arg0 + 0x18));
  p = base;
  p += *((s32 *) (base + 0x50));
  p += 0xF8;
  mtxf_rotate_xyz_deg(mf, *((f32 *) (p + 0)), 0.0f, *((f32 *) (p + 4)));
  mf[3][1] = *((f32 *) (p + 0x10));
  mf[0][0] *= 0.157f;
  mf[0][1] *= 0.157f;
  mf[0][2] *= 0.157f;
  mf[1][0] *= 0.157f;
  mf[1][1] *= 0.157f;
  mf[1][2] *= 0.157f;
  mf[2][0] *= 0.157f;
  mf[2][1] *= 0.157f;
  mf[2][2] *= 0.157f;
  mtxf_transform_point(mf, 0.0f, -1108.0f, 0.0f, &out.x, &out.y, &out.z);
  if ((arg0 && arg0) && arg0) // fakematch: permuter, scheduling
  {
  }
  new_var = out.y - (*((f32 *) (p + 0x10)));
  if (collision_ray_cast(0.0f, *((f32 *) (p + 0x10)), 0.0f, out.x, new_var, out.z, 0, 0, &hit.x, &hit.y, &hit.z, 0, 0, 0, 0.0f) == 0)
  {
    hit = out;
  }
  *((s16 *) ((*((u8 **) (arg0 + 0x14))) + 0xE)) = hit.x;
  *((s16 *) ((*((u8 **) (arg0 + 0x14))) + 0x10)) = hit.y;
  *((s16 *) ((*((u8 **) (arg0 + 0x14))) + 0x12)) = hit.z;
  if (p[0x20] != 0)
  {
    *((*((u8 **) (arg0 + 0x14))) + 9) = 0;
  }
  else
  {
    *((*((u8 **) (arg0 + 0x14))) + 9) = 1;
  }
  return 1;
}

/* was func_1510957C */
void swing_lamp_post_target(s32 arg0, s32 arg1, u8 arg2) {
    struct {
        s32 unk0;
        s32 unk4;
        u8 unk8;
    } sp24;
    s32 sp1C[2] = {0x38, 0x54};

    sp24.unk0 = arg0;
    sp24.unk4 = arg1;
    sp24.unk8 = arg2;
    node_broadcast_types(sp1C, 2, (s32)&sp24, 0x1D);
}

/* was func_151095E4 */
void swing_lamp_handle_event(u8 *arg0, s32 arg1, u8 arg2)
{
  u8 *p = arg0;
  p += *(s32 *)(arg0 + 0x50);
  p += 0xF8;
  switch (arg2) {
  case 0x1D:
    {
      s32 t; // fakematch: block-local declaration = basic-block boundary (unfilled jr ra delay slot, s69)
      *(s32 *)(p + 0x14) = ((s32 *)arg1)[0];
      p[0x18] = ((u8 *)arg1)[8];
      *(s32 *)(p + 0x1C) = ((s32 *)arg1)[1];
    }
    break;
  case 0x1E:
    if (p[0x20] != 0) {
      p[0x20] = 0;
    } else {
      p[0x20] = 1;
    }
    break;
  }
}

/* was func_1510965C */
void swing_lamp_post_toggle(void) {
    s32 sp18[2] = {0x38, 0x54};

    node_broadcast_types(sp18, 2, 0, 0x1E);
}

/* P204 */
// sky_dome_project_uv: g_mesh_effect_draw_fns kind-4 handler (s32 (u8 *, s32), called by mesh_effect_draw) of a double-buffered
// vertex record rec for player slot `slot`: builds this frame's matrix (rec +0x78 + g_dl_buf_index * 0x40) as a
// translation to (p[0], p[4], p[1]) with p = rec + +0x50 + 0xF8, scaled by 0.157, and maps the 16 vertices of the
// slot's copy (rec +0x58[g_dl_buf_index * 4 + slot]) to texture coordinates: each vertex goes through the matrix; s
// follows its position across the camera direction (camera_get_pos(slot), x / z normalised; straight ahead when its
// x and y are both tiny) as 32 * (26 + 0.213 * side), t its height as 32 * (81 + 0.358 * y). Returns 1.
/* was func_151096A0 */
s32 sky_dome_project_uv(u8 *rec, s32 slot) {
    f32 mtx[4][4];
    f32 ox;
    f32 oy;
    f32 oz;
    f32 *p;
    f32 *cam;
    f32 inv;
    f32 cx;
    f32 cz;
    Vtx *v;
    s32 i;

    p = (f32 *) (rec + *(s32 *) (rec + 0x50) + 0xF8);
    mtxf_rotate_xyz_deg(mtx, p[0], 0.0f, p[1]);
    mtx[3][1] = p[4];
    mtx[0][0] *= 0.157f;
    mtx[0][1] *= 0.157f;
    mtx[0][2] *= 0.157f;
    mtx[1][0] *= 0.157f;
    mtx[1][1] *= 0.157f;
    mtx[1][2] *= 0.157f;
    mtx[2][0] *= 0.157f;
    mtx[2][1] *= 0.157f;
    mtx[2][2] *= 0.157f;
    guMtxF2L(mtx, (Mtx *) (rec + 0x78 + g_dl_buf_index * 0x40));
    cam = camera_get_pos((s16) slot);
    if (fabsf(cam[0]) > 0.0001f || fabsf(cam[1]) > 0.0001f) {
        inv = 1.0f / sqrtf(cam[0] * cam[0] + cam[2] * cam[2]);
        cx = cam[2] * inv;
        cz = -cam[0] * inv;
    } else {
        cx = 1.0f;
        cz = 0.0f;
    }
    for (i = 0; i < 16; i++) {
        v = *(Vtx **) (rec + g_dl_buf_index * 0x10 + (s16) slot * 4 + 0x58) + i;
        mtxf_transform_point(mtx, v->v.ob[0], v->v.ob[1], v->v.ob[2], &ox, &oy, &oz);
        v->v.tc[0] = (s32) (((ox * cx + oz * cz) * 0.21300001f + 26.0f) * 32.0f);
        v->v.tc[1] = (s32) ((oy * 0.358f + 81.0f) * 32.0f);
    }
    return 1;
}
