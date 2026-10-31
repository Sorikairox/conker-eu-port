#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void shot_scorch_decal_spawn(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void fire_flash_light_spawn(u8 *arg0, u8 arg1, s32 arg2);


typedef struct {
    s8 u0;
    s8 u1;
    s8 u2;
    s16 u4;
    s32 u8_;
    s32 uC;
    s32 u10;
    s32 u14;
    s32 u18;
    s32 u1C;
    s32 u20;
    s8 u24;
    s8 u25;
    s32 u28;
    s32 u2C;
    s32 u30;
    s32 u34;
    s8 u38;
    u8 u39;
} Sa4b0;
typedef struct {
    u8 *p;
    u8 b;
} Ba4b0;
extern s8 g_mp_pad_share_slot[]; /* was D_800E0FFE */
u8 *mesh_effect_spawn(Sa4b0 *, s32, s32, u8, s32);
/* was func_151BA4B0 */
u8 *player_screen_uv_mesh_spawn(u8 *arg0, u8 arg1, s32 arg2)
{
  u8 *ret;
  Sa4b0 s;
  Ba4b0 b;
  s32 idx;
  if (arg0 == 0)
  {
    return 0;
  }
  b.p = arg0;
  b.b = arg0[0x3B];
  s.u0 = 2;
  s.u1 = -1;
  s.u2 = 3;
  s.u4 = 300;
  s.u30 = 9;
  s.u34 = 0x1AD;
  s.u39 = 0xFF;
  idx = (arg0 - ((u8 *) g_objects)) / 812;
  goto dummy_label_283214; // fakematch: label barrier (permuter) puts sw a0 (b.p) before the arg0[0x3B] load
  dummy_label_283214:
  ;
  if ((idx < 2) && (g_mp_pad_share_slot[idx] != 0))
  {
    if (g_human_player_count == 2)
    {
      s.u39 = 0xFD;
    }
    else
      if (g_human_player_count == 4)
    {
      if (idx == 0)
      {
        s.u39 = 0xFB;
      }
      else
      {
        s.u39 = 0xF7;
      }
    }
  }
  s.u8_ = 1;
  s.uC = 0x200205;
  s.u10 = 0x60600;
  s.u24 = 0;
  s.u25 = 0;
  s.u14 = 1;
  s.u18 = 0x36;
  s.u1C = 0x80;
  s.u20 = 0x20;
  s.u38 = 2;
  ret = mesh_effect_spawn(&s, 1, 8, arg1, arg2);
  if (ret != 0)
  {
    memcpy((ret + (*((s32 *) (ret + 0x50)))) + ((0, 0xF8)), &b, 8); // fakematch: comma expression (permuter) gives addu a0,v0,t9
  }
  return ret;
}

extern u8 g_cam_view_proj_mtx[]; /* was D_800DA130 */
extern u8 *g_objects_camera; /* was D_800CCA08 */

// object_screen_uv_project: g_mesh_effect_draw_fns kind-3 handler (s32 (u8 *, s32), called by mesh_effect_draw; same scheme as
// sky_dome_project_uv) of a 20-vertex record rec attached to an object (rec + +0x50 + 0xF8 = {obj, obj id}) for
// player view `slot`: releases the record (node_destroy) when the object is gone or replaced; returns 0 (not
// drawn) when the object has no matrix, is hidden ((+0x74 & 0xF) == 0xF) or is the object this view looks from
// (+0x318 / +0x31C rider check when g_mp_mode_active, else g_objects_camera / g_objects_state). Otherwise copies the object's
// matrix (+0x1D4 + 0x40, fixed point when g_mtx_fixed_point), with its fourth column set to (0, 0, 0, 1), into this frame's Mtx (rec +0x78 +
// g_dl_buf_index * 0x40), and maps each vertex of the slot's copy to texture coordinates: its screen position (object
// matrix, then view matrix g_cam_view_proj_mtx[slot]) times 2.002, relative to the screen position of the object point
// (0, 67, 159) truncated to a multiple of 1024. Returns 1.
/* was func_151BA634 */
s32 object_screen_uv_project(u8 *rec, s32 slot) {
    f32 view[4][4];
    f32 m[4][4];
    f32 ox, oy, oz;
    f32 cx, cy, cz;
    f32 wx, wy, wz;
    f32 sx, sy, sz;
    f32 baseX, baseY;
    u8 *p;
    u8 *obj;
    u8 *mtx;
    u8 *rider;
    Vtx *v;
    s32 i;

    slot = (s16) slot;
    p = rec + *(s32 *) (rec + 0x50) + 0xF8;
    obj = *(u8 **) p;
    if (*(s32 *) obj == 0 || p[4] != obj[0x3B]) {
        node_destroy((struct102 *) rec);
    }
    mtx = *(u8 **) (obj + 0x1D4);
    if (mtx == NULL) {
        return 0;
    }
    if ((obj[0x74] & 0xF) == 0xF) {
        return 0;
    }
    if (g_mp_mode_active) {
        rider = *(u8 **) (obj + 0x318);
        if (rider != NULL && *(u8 **) (obj + 0x31C) != NULL && (*(u8 **) (obj + 0x31C))[0x197] != 0
            && rider[0x23D] == slot) {
            return 0;
        }
    } else if (g_objects_camera != NULL && g_objects_state != NULL && g_objects_state[0x197] != 0 && g_objects_camera[0x23D] == slot) {
        return 0;
    }
    if (g_mtx_fixed_point) {
        guMtxL2F(m, (Mtx *) (mtx + 0x40));
    } else {
        memcpy(m, mtx + 0x40, 0x40);
    }
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    guMtxF2L(m, (Mtx *) (rec + 0x78 + g_dl_buf_index * 0x40));
    memcpy(view, g_cam_view_proj_mtx + slot * 0x40, 0x40);
    view[0][3] = 0.0f;
    view[1][3] = 0.0f;
    view[2][3] = 0.0f;
    view[3][3] = 1.0f;
    mtxf_transform_point(m, 0.0f, 67.0f, 159.0f, &ox, &oy, &oz);
    mtxf_transform_point(view, ox, oy, oz, &cx, &cy, &cz);
    cx *= 2.002f;
    cy *= 2.002f;
    baseX = (s32) (cx * (1.0f / 1024.0f)) * 1024.0f;
    baseY = (s32) (cy * (1.0f / 1024.0f)) * 1024.0f;
    for (i = 0; i < 20; i++) {
        v = *(Vtx **) (rec + g_dl_buf_index * 0x10 + slot * 4 + 0x58) + i;
        mtxf_transform_point(m, v->v.ob[0], v->v.ob[1], v->v.ob[2], &wx, &wy, &wz);
        mtxf_transform_point(view, wx, wy, wz, &sx, &sy, &sz);
        sx *= 2.002f;
        sy *= 2.002f;
        v->v.tc[0] = (s32) (sx - baseX);
        v->v.tc[1] = (s32) (sy - baseY);
    }
    return 1;
}

/* was func_151BAA18 */
void screen_uv_mesh_handle_message(u8 *arg0, s32 arg1, u8 arg2)
{
  u8 *q;
  s32 *p;
  s32 id;
  s32 t;
  q = arg0;
  q += *(s32 *)(arg0 + 0x50);
  q += 0xF8;
  p = (s32 *)q;
  id = p[0];
  t = id;
  if (arg2 == 0)
  {
    if ((t == ((s32 *)arg1)[0]) || (((u8 *) t)[0x3B] == ((u8 *) arg1)[4]))
    {
      node_destroy((struct102 *)arg0);
    }
  }
  else
    if (arg2 == 0x2D)
  {
    t = ((s32 *)arg1)[0];
    if (t == *p)
    {
      p[0] = ((s32 *)arg1)[1];
      ((u8 *) p)[4] = ((u8 *) arg1)[9];
    }
    else if (((s32 *)arg1)[1] == *p)
    {
      p[0] = t;
      ((u8 *) p)[4] = ((u8 *) arg1)[8];
    }
  }
}

/* emit_random_sprites smoke burst request (0x5C bytes): each value is base + random(0..range) */
typedef struct {
    /* 0x00 */ s16 a, aRange;
    /* 0x04 */ s16 b, bRange;
    /* 0x08 */ s32 count, countRange;
    /* 0x10 */ f32 pos[3];
    /* 0x1C */ f32 v0, v0Range;
    /* 0x24 */ f32 v1, v1Range;
    /* 0x2C */ f32 v2, v2Range;
    /* 0x34 */ s32 life, lifeRange;
    /* 0x3C */ f32 f3C, f40, f44, f48;
    /* 0x4C */ s16 s4C[6];
    /* 0x58 */ s8 u58;
} SmokeBurst;

/* mdl_particle_spawn_ex particle request (0x7C bytes; +0x34 velocity, +0x50 flags, +0x56 model id) */
typedef struct {
    /* 0x00 */ f32 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 sizeX;
    /* 0x0C */ f32 sizeZ;
    /* 0x10 */ f32 pos[3];
    /* 0x1C */ f32 scale[3];
    /* 0x28 */ f32 from[3];        /* launch point on the model (also the scratch for the direction) */
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 spinX;
    /* 0x44 */ f32 spinY;
    /* 0x48 */ f32 spinZ;
    /* 0x4C */ f32 gravity;
    /* 0x50 */ s32 flags;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 model;
    /* 0x58 */ u8  u58;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8  alpha;
    /* 0x61 */ u8  u61;
    /* 0x62 */ u8  u62[6];
    /* 0x68 */ u8  u68;
    /* 0x69 */ u8  pad69;
    /* 0x6A */ u8  u6A;
    /* 0x6C */ u8 *owner;
    /* 0x70 */ u8  ownerId;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x78 */ s32 u78;
} ShardRequest;

void mtx_decompose(Mtx *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void hitinfo_from_obj_floor(void *, u8 *);
void emit_random_sprites(u8 *, u8, s32);
u8 *mdl_particle_spawn_ex(u8 *req, s32 nTrails, s32 arg2, s32 *bounds, s32 extraSize, u8 arg5, s32 owner);
/* model-space launch points (rodata of this function, read through the ROM image) */
extern f32 g_shatter27_from[3];       /* piece 0x27: from / to; was D_800AA970 */
extern f32 g_shatter27_to[3]; /* was D_800AA97C */
extern f32 g_shatter28_from[3];       /* piece 0x28: from, to = one of two; was D_800AA988 */
extern f32 g_shatter28_to[2][3]; /* was D_800AA994 */
extern f32 g_shatter29_from[4][3];    /* pieces 0x29: from / to / size; was D_800AA9AC */
extern f32 g_shatter29_to[4][3]; /* was D_800AA9DC */
extern f32 g_shatter29_size[4]; /* was D_800AAA0C */
extern f32 g_shatter2b_from[3];       /* pieces 0x2B: common from, to, position offset; was D_800AAA1C */
extern f32 g_shatter2b_to[2][3]; /* was D_800AAA28 */
extern f32 g_shatter2b_pos_off[2][3]; /* was D_800AAA40 */
extern f32 g_shatter2c_from[4][3];    /* pieces 0x2C: from / to / position offset / size; was D_800AAA58 */
extern f32 g_shatter2c_to[4][3]; /* was D_800AAA88 */
extern f32 g_shatter2c_pos_off[4][3]; /* was D_800AAAB8 */
extern f32 g_shatter2c_size[4]; /* was D_800AAAE8 */

/* random launch speed factor 0.083..0.283 and spin -14.4..14.4 */
#define SHARD_SPEED() ((random_float() * 200.0f + 83.0f) * 0.001f)
#define SHARD_SPIN() ((random_float() * 28864.0f + -14432.0f) * 0.001f)

// object_model_shatter: an object's model breaks apart (object_destroy_effects, a0 = obj, 0xFF, 1): a smoke burst at the
// object (25 above its position) and, when it has a visible model instance (+0x1D4, +0x74 low nibble != 0xF),
// pieces 0x27 .. 0x2C flung from model-space points (transformed by the instance matrix +0x40) towards other
// points, spawned at the model's origin plus an offset, with random speed, life 30..65 and spin. The pieces
// 0x29 / 0x2B / 0x2C are each spawned with a 50 % chance.
/* was func_151BAAC8 */
void object_model_shatter(u8 *obj, u8 arg1, s32 arg2) {
    SmokeBurst smoke;
    ShardRequest req;
    s32 bounds[9];
    f32 origin[3];
    f32 rot[3];
    f32 scl[3];
    Mtx *mtx;
    f32 speed;
    s32 i;

    smoke.a = 0;
    smoke.aRange = 0xFF;
    smoke.b = -0x3F;
    smoke.bRange = 0x34;
    smoke.count = 6;
    smoke.countRange = 5 >> ((g_last_player_index >= 2) ? 1 : 0);
    smoke.pos[0] = *(f32 *)(obj + 0x14);
    smoke.pos[1] = *(f32 *)(obj + 0x18) + 25.0f;
    smoke.pos[2] = *(f32 *)(obj + 0x1C);
    smoke.life = 6;
    smoke.v0 = 50.0f;
    smoke.v0Range = 42.0f;
    smoke.v1 = 98.0f;
    smoke.v1Range = 68.0f;
    smoke.v2 = 609.0f;
    smoke.v2Range = 271.0f;
    smoke.lifeRange = 3 >> ((g_last_player_index >= 2 || g_player_count >= 8) ? 1 : 0);
    smoke.s4C[0] = 0x19;
    smoke.s4C[1] = 0xF;
    smoke.s4C[2] = 0x64;
    smoke.s4C[3] = 0x64;
    smoke.s4C[4] = 0xC;
    smoke.s4C[5] = 0x14;
    smoke.f3C = 18.0f;
    smoke.f40 = 0.76900005f;
    smoke.f44 = -0.16900001f;
    smoke.f48 = 0.0f;
    smoke.u58 = (g_last_player_index >= 2 || g_player_count >= 8) ? -1 : 0;
    emit_random_sprites((u8 *)&smoke, arg1, arg2);

    if (*(u8 **)(obj + 0x1D4) == NULL || (obj[0x74] & 0xF) == 0xF) {
        return;
    }
    hitinfo_from_obj_floor(bounds, obj);
    mtx = (Mtx *)(*(u8 **)(obj + 0x1D4) + 0x40);
    mtx_decompose(mtx, &scl[0], &scl[1], &scl[2], &origin[0], &origin[1], &origin[2], &rot[0], &rot[1], &rot[2]);

    req.u00 = 1.0f;
    req.scale[0] = 1.0f;
    req.scale[1] = 1.0f;
    req.scale[2] = 1.0f;
    req.flags = 0x39E9;
    req.u58 = 0;
    req.u5C = 0;
    req.alpha = 0xFF;
    req.u61 = 0xD;
    req.u62[0] = 0;
    req.u62[1] = 0xC;
    req.u62[2] = 0;
    req.u62[3] = 0;
    req.u62[4] = 0;
    req.u62[5] = 0;
    req.u68 = 2;
    req.u6A = 0;
    req.owner = obj;
    req.u04 = 0.7f;
    req.spinY = 0.0f;
    req.u72 = 0xC;
    req.u74 = 0x15;
    req.ownerId = obj[0x3B];

    /* piece 0x27 */
    speed = SHARD_SPEED();
    req.life = (random_int() % 36U) + 30;
    req.model = 0x27;
    req.sizeZ = 0.75f;
    req.sizeX = 0.75f;
    random_float();
    req.gravity = -0.48800004f; /* -488 * 0.001 */
    mtx_transform_point_or_origin(g_shatter27_from, req.from, mtx);
    mtx_transform_point_or_origin(g_shatter27_to, req.vel, mtx);
    req.vel[0] = (req.vel[0] - req.from[0]) * speed;
    req.vel[1] = (req.vel[1] - req.from[1]) * speed;
    req.vel[2] = (req.vel[2] - req.from[2]) * speed;
    req.pos[0] = origin[0];
    req.pos[1] = origin[1];
    req.pos[2] = origin[2];
    req.pos[0] += 109.0f;
    req.spinX = SHARD_SPIN();
    req.spinZ = SHARD_SPIN();
    mdl_particle_spawn_ex((u8 *)&req, 3, 0xFF, bounds, 0, arg1, arg2);

    /* piece 0x28: towards one of two points */
    speed = SHARD_SPEED();
    req.life = (random_int() % 36U) + 30;
    req.model = 0x28;
    req.sizeZ = 0.5f;
    req.sizeX = 0.5f;
    random_float();
    req.gravity = -0.48800004f;
    mtx_transform_point_or_origin(g_shatter28_from, req.from, mtx);
    mtx_transform_point_or_origin(g_shatter28_to[random_int() & 1], req.vel, mtx);
    req.vel[0] = (req.vel[0] - req.from[0]) * speed;
    req.vel[1] = (req.vel[1] - req.from[1]) * speed;
    req.vel[2] = (req.vel[2] - req.from[2]) * speed;
    req.pos[0] = origin[0];
    req.pos[1] = origin[1];
    req.pos[2] = origin[2];
    req.spinX = SHARD_SPIN();
    req.spinZ = SHARD_SPIN();
    mdl_particle_spawn_ex((u8 *)&req, 3, 0xFF, bounds, 0, arg1, arg2);

    /* pieces 0x29 */
    req.model = 0x29;
    for (i = 0; i < 4; i++) {
        if (random_int() & 1) {
            speed = SHARD_SPEED();
            req.life = (random_int() % 36U) + 30;
            req.sizeX = g_shatter29_size[i];
            req.sizeZ = g_shatter29_size[i];
            random_float();
            req.gravity = -0.48800004f;
            mtx_transform_point_or_origin(g_shatter29_from[i], req.from, mtx);
            mtx_transform_point_or_origin(g_shatter29_to[i], req.vel, mtx);
            req.vel[0] = (req.vel[0] - req.from[0]) * speed;
            req.vel[1] = (req.vel[1] - req.from[1]) * speed;
            req.vel[2] = (req.vel[2] - req.from[2]) * speed;
            req.pos[0] = origin[0];
            req.pos[1] = origin[1];
            req.pos[2] = origin[2];
            req.spinX = SHARD_SPIN();
            req.spinZ = SHARD_SPIN();
            mdl_particle_spawn_ex((u8 *)&req, 3, 0xFF, bounds, 0, arg1, arg2);
        }
    }

    /* pieces 0x2B: from one common point */
    req.model = 0x2B;
    mtx_transform_point_or_origin(g_shatter2b_from, req.from, mtx);
    req.sizeX = 0.551f;
    req.sizeZ = 0.551f;
    for (i = 0; i < 2; i++) {
        if (random_int() & 1) {
            speed = SHARD_SPEED();
            req.life = (random_int() % 36U) + 30;
            random_float();
            req.gravity = -0.48800004f;
            mtx_transform_point_or_origin(g_shatter2b_to[i], req.vel, mtx);
            req.vel[0] = (req.vel[0] - req.from[0]) * speed;
            req.vel[1] = (req.vel[1] - req.from[1]) * speed;
            req.vel[2] = (req.vel[2] - req.from[2]) * speed;
            req.pos[0] = origin[0];
            req.pos[1] = origin[1];
            req.pos[2] = origin[2];
            req.pos[0] += g_shatter2b_pos_off[i][0];
            req.pos[1] += g_shatter2b_pos_off[i][1];
            req.pos[2] += g_shatter2b_pos_off[i][2];
            req.spinX = SHARD_SPIN();
            req.spinZ = SHARD_SPIN();
            mdl_particle_spawn_ex((u8 *)&req, 3, 0xFF, bounds, 0, arg1, arg2);
        }
    }

    /* pieces 0x2C */
    req.model = 0x2C;
    for (i = 0; i < 4; i++) {
        if (random_int() & 1) {
            speed = SHARD_SPEED();
            req.life = (random_int() % 36U) + 30;
            req.sizeX = g_shatter2c_size[i];
            req.sizeZ = g_shatter2c_size[i];
            random_float();
            req.gravity = -0.48800004f;
            mtx_transform_point_or_origin(g_shatter2c_from[i], req.from, mtx);
            mtx_transform_point_or_origin(g_shatter2c_to[i], req.vel, mtx);
            req.vel[0] = (req.vel[0] - req.from[0]) * speed;
            req.vel[1] = (req.vel[1] - req.from[1]) * speed;
            req.vel[2] = (req.vel[2] - req.from[2]) * speed;
            req.pos[0] = origin[0];
            req.pos[1] = origin[1];
            req.pos[2] = origin[2];
            req.pos[0] += g_shatter2c_pos_off[i][0];
            req.pos[1] += g_shatter2c_pos_off[i][1];
            req.pos[2] += g_shatter2c_pos_off[i][2];
            req.spinX = SHARD_SPIN();
            req.spinZ = SHARD_SPIN();
            mdl_particle_spawn_ex((u8 *)&req, 3, 0xFF, bounds, 0, arg1, arg2);
        }
    }
}
#undef SHARD_SPEED
#undef SHARD_SPIN

s32 tank_engine_sound_update(u8 *voice, s32 arg1, s32 *vol, s32 arg3, s32 *pitch, s32 arg5, u16 *id);

/* was func_151BB5F4 */
void tank_engine_sound_start(u8 *arg0) {
    sfx_emitter_start(0x4A7U, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x1C)), 0x2000, 0x320U, 0xC8, (s32) &tank_engine_sound_update, arg0, 0, 8, 0);
}

s32 sound_pick_variant(s32, s32);

// tank_engine_sound_update: per-frame callback of the tank's engine voice (started by tank_engine_sound_start with id 0x4A7
// and by itself; same callback type as scope_motion_sound_update). voice +0x18 = the tank, voice +0x1C packs
// mode (bits 0-6: last drive state), fading (bit 7), level (bits 8-15) and a timer (bits 16-27). Returns 1 (and
// does nothing) without a tank or when its +0x1CA is clear. The voice follows the tank's position. Drive state:
// 1 = driving (speed +0x3C beyond +-1 in the direction of the throttle +0x44), 2 = skidding (speed beyond +-5
// against or without throttle), else 0. When the state changed it plays a one-shot (0x4A5 when skidding starts,
// else a pick of sound_pick_variant(0x4A3, 4)) on the tank unless one is playing (actor_sound2_is_playing). Starting to drive
// from idle (id 0x4A7) switches the voice to the run sound 0x4A8 (new voice at volume 0x2EE0, returns 1); stopping
// while running (0x4A8) switches back to idle 0x4A7 (0x2000); while the wind-down 0x4A9 plays it waits (returns 1).
// The run / wind-down voice fades its volume (*vol * level / 256) in (bit 7) or out by 8 a frame (returns 1 when
// faded out); with a timer it counts down by g_frame_ticks and, at the end while running, starts 0x4A9 and a new
// random (random_int & 0x200) timer. Its pitch is |speed| * +0xB8 / 2. Repacks +0x1C; when *vol is 0 or the
// voice was flagged (+0x10 & 0x80) it stops its sound (+0x24) and clears the id, the flag and *vol. Returns 0.
/* was func_151BB690 */
s32 tank_engine_sound_update(u8 *voice, s32 arg1, s32 *vol, s32 arg3, s32 *pitch, s32 arg5, u16 *id) {
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
            snd = sound_pick_variant(0x4A3, 4);
        }
        if (actor_sound2_is_playing((struct127 *) tank) == 0) {
            actor_sound_play(snd, (struct127 *) tank, 0x6D60, 0x12C, 0x708);
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
        sfx_emitter_start(newId, (s32) *(f32 *) (tank + 0x14), (s32) *(f32 *) (tank + 0x18),
                      (s32) *(f32 *) (tank + 0x1C), volume, 0x320, 0xC8, (s32) &tank_engine_sound_update, tank,
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
                    timer = (random_int() & 0x200) + 0x12C;
                    fading = 0;
                }
            } else {
                level -= 8;
                if (level <= 0) {
                    return 1;
                }
            }
        } else {
            timer -= g_frame_ticks;
            if (timer <= 0) {
                timer = 0;
                if (*id == 0x4A8) {
                    sfx_emitter_start(0x4A9, (s32) *(f32 *) (tank + 0x14), (s32) *(f32 *) (tank + 0x18),
                                  (s32) *(f32 *) (tank + 0x1C), 0x2EE0, 0x320, 0xC8, (s32) &tank_engine_sound_update, tank,
                                  drive | 0x880, 8, 0);
                    timer = (random_int() & 0x200) + 0x384;
                }
            }
        }
        *pitch = (s32) (fabsf(*(f32 *) (tank + 0x3C)) * *(f32 *) (tank + 0xB8) * 0.5f);
    }
    *(u32 *) (voice + 0x1C) = (fading << 7) | drive | (level << 8) | (timer << 16);
    if (*vol == 0 || (*(s32 *) (voice + 0x10) & 0x80)) {
        if (*(u16 *) (voice + 0x24) != 0) {
            sound_voice_stop(*(u16 *) (voice + 0x24));
            *(u16 *) (voice + 0x24) = 0;
        }
        *id = 0;
        *(s32 *) (voice + 0x10) &= ~0x80;
        *vol = 0;
    }
    return 0;
}

void explosion_sfx_play(s32, f32, f32, f32, s32);
s32 tri_calc_normal(s32 *, s32 *, s32 *, s32 *);
void impact_spark_flash_spawn(u8 *, u8, s32);
void impact_rumble_spawn(s32, u8, s32);
void impact_cam_shake_spawn(void *, u8, s32);
void impact_debris_emitter_spawn(s32, u8, s32);
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, void *, void *, s32, f32);
u8 prop_is_flagged(s32);
void emit_spray_from_surface(void *, u8, s32);
void emit_impact_flash_spray(void *, s32 *, f32 *, s32, u8, s32);
typedef struct { s16 v[9]; } HitSurface; /* 0x12-byte surface record written by collision_ray_cast */
/* impact flash keyframes for emit_impact_flash_spray: frame numbers and scales (rodata D_800AAAF8 / D_800AAB1C) */
static const s32 sImpactFlashFrames[9] = { 4, 4, 7, 8, 0x18, 0x19, 0x1D, 0x1E, 0x20 };
static const f32 sImpactFlashScales[9] = { 1.0f, 1.0f, 0.15f, 0.15f, 1.0f, 1.0f, 0.097f, 1.0f, 0.2f };
// shot_impact_effects: effects of a shot fired from `pos` towards `target` (obj only gates it): sound
// explosion_sfx_play and the muzzle effects (impact_rumble_spawn / impact_cam_shake_spawn / impact_spark_flash_spawn / fire_flash_light_spawn) at pos, then a
// ray cast (collision_ray_cast) along target - pos. On a hit: shot_scorch_decal_spawn when the hit object passes prop_is_flagged,
// impact_debris_emitter_spawn when the surface's third axis points down (tri_calc_normal), a spark spray off the surface
// (emit_spray_from_surface, 3 / 4 particles, range 494) and an animated impact flash (emit_impact_flash_spray, 9 keyframes).
// Called by obj_effect_shot_impact (effect handler 2 of obj_effect_run_handler) with g_obj_effect_pos / D_eu_800D1990.
/* was func_151BBBCC */
void shot_impact_effects(s32 obj, f32 *pos, f32 *target, u8 arg3, s32 arg4) {
    struct {
        f32 dir[3];
        HitSurface hit;
        f32 range;
        struct {
            s32 count;
            s32 u4;
            f32 pos[3];
            f32 f[6];
            s32 u24;
            s32 u28;
            f32 u2C;
            f32 u30[3];
            s16 s[6];
            s8 u48;
        } p;
    } spray; /* emit_spray_from_surface */
    struct {
        s32 u0;
        s32 u4;
        f32 pos[3];
        f32 dir[3];
        HitSurface hit;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        s16 u48;
        s16 u4A;
        f32 u4C;
        f32 u50;
        f32 u54;
    } flash; /* emit_impact_flash_spray */
    s32 frames[9];
    f32 scales[9];
    s32 i;
    f32 ax0[3];
    f32 ax1[3];
    f32 ax2[3];
    f32 dir[3];
    f32 hitPos[3];
    HitSurface hit;
    s32 hitObj;
    f32 nx;
    f32 ny;
    f32 nz;

    if (obj == 0) {
        return;
    }
    explosion_sfx_play(0, pos[0], pos[1], pos[2], 0);
    dir[0] = target[0] - pos[0];
    dir[1] = target[1] - pos[1];
    dir[2] = target[2] - pos[2];
    impact_rumble_spawn((s32) pos, arg3, arg4);
    impact_cam_shake_spawn(pos, arg3, arg4);
    impact_spark_flash_spawn((u8 *) pos, arg3, arg4);
    fire_flash_light_spawn((u8 *) pos, arg3, arg4);
    if (collision_ray_cast(pos[0], pos[1], pos[2], dir[0], dir[1], dir[2], 0, &hit, &hitPos[0], &hitPos[1], &hitPos[2],
                      NULL, &hitObj, 0, 0.0f) == 0) {
        return;
    }
    if (prop_is_flagged(hitObj) != 0) {
        shot_scorch_decal_spawn((s32) &hit, (s32) hitPos, arg3, arg4);
    }
    if (tri_calc_normal((s32 *) &hit, (s32 *) ax0, (s32 *) ax1, (s32 *) ax2) != 0 && ax2[1] < 0.0f) {
        impact_debris_emitter_spawn((s32) hitPos, arg3, arg4);
    }
    nx = -dir[0];
    ny = -dir[1];
    nz = -dir[2];

    spray.dir[0] = nx;
    spray.dir[1] = ny;
    spray.dir[2] = nz;
    spray.hit = hit;
    spray.range = 494.0f;
    spray.p.count = 3;
    spray.p.u4 = 4;
    spray.p.pos[0] = hitPos[0];
    spray.p.pos[1] = hitPos[1];
    spray.p.pos[2] = hitPos[2];
    spray.p.f[0] = 0.0609f;
    spray.p.f[1] = 0.0252f;
    spray.p.f[2] = 45.0f;
    spray.p.f[3] = 53.0f;
    spray.p.f[4] = 203.0f;
    spray.p.f[5] = 414.0f;
    spray.p.u24 = 7;
    spray.p.u28 = 3;
    spray.p.u2C = 15.0f;
    spray.p.u30[0] = 0.88000005f;
    spray.p.u30[1] = -0.39800003f;
    spray.p.u30[2] = 0.39100003f;
    spray.p.s[0] = 0x19;
    spray.p.s[1] = 0xF;
    spray.p.s[2] = 0x64;
    spray.p.s[3] = 0x64;
    spray.p.s[4] = 0xC;
    spray.p.s[5] = 0x14;
    spray.p.u48 = 0;
    emit_spray_from_surface(&spray, arg3, arg4);

    flash.u0 = 6;
    flash.u4 = 6;
    flash.pos[0] = hitPos[0];
    flash.pos[1] = hitPos[1];
    flash.pos[2] = hitPos[2];
    flash.dir[0] = nx;
    flash.dir[1] = ny;
    flash.dir[2] = nz;
    flash.hit = hit;
    flash.u34 = 456.0f;
    flash.u38 = 0.020000001f;
    flash.u3C = 0.020000001f;
    flash.u40 = -1.71f;
    flash.u44 = 0.448f;
    flash.u48 = 0x32;
    flash.u4A = 0x14;
    flash.u4C = 0.499f;
    flash.u50 = 0.70100003f;
    flash.u54 = 21.502f;
    for (i = 0; i < 9; i++) {
        frames[i] = sImpactFlashFrames[i];
        scales[i] = sImpactFlashScales[i];
    }
    emit_impact_flash_spray(&flash, frames, scales, 9, arg3, arg4);
}

s32 collision_floor_probe(f32 *, s32, f32, f32 *);
void hitinfo_from_obj_floor(void *, u8 *);
void explosion_sfx_play(s32, f32, f32, f32, s32);
s32 tri_calc_normal(s32 *, s32 *, s32 *, s32 *);
void emit_random_sprites(u8 *, u8, s32);
void impact_spark_flash_spawn(u8 *, u8, s32);
void impact_rumble_spawn(s32, u8, s32);
void impact_cam_shake_spawn(void *, u8, s32);
void impact_debris_emitter_spawn(s32, u8, s32);
extern s32 g_explosion_fx_vec_a; /* was D_8008FF40 */
extern s32 g_explosion_fx_vec_b; /* was D_8008FF4C */

/* was func_151BC04C */
void explosion_effects_at(s32 arg0, u8 *arg1, u8 *arg2, u8 arg3, s32 arg4) {
    struct {
        s32 u34;
        u8 pad38[0x8];
        s32 u40;
        u8 pad44[0x8];
        s32 u4C;
        s32 u50;
        s32 u54;
        u8 pad58[0x8];
        s16 u60;
        s16 u62;
        s16 u64;
        s16 u66;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s16 u78;
        s16 u7A;
        f32 u7C;
        f32 u80;
        f32 u84;
        s32 u88;
        s32 u8C;
        u8 pad90[0x4];
        s32 u94;
        u8 pad98[0x8];
        s32 uA0;
        u8 padA4[0x8];
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        s32 uC8;
        u8 padCC[0x1C];
        s16 uE8;
        s16 uEA;
        s16 uEC;
        s16 uEE;
        s32 uF0;
        s32 uF4;
        s32 uF8;
        u8 padFC[0x8];
        f32 u104;
        f32 u108;
        f32 u10C;
        f32 u110;
        f32 u114;
        f32 u118;
        s32 u11C;
        s32 u120;
        f32 u124;
        f32 u128;
        f32 u12C;
        f32 u130;
        s16 u134;
        s16 u136;
        s16 u138;
        s16 u13A;
        s16 u13C;
        s16 u13E;
        s8 u140;
        u8 pad141[0x3];
        f32 u144;
        f32 u148;
        f32 u14C;
    } sp;
    s32 var_v0;
    s32 var_v0_2;

    if (arg0 != 0) {
        sp.u144 = ((*(f32 *)((u8 *)arg1 + 0)) + (*(f32 *)((u8 *)arg2 + 0))) * 0.5f;
        sp.u148 = ((*(f32 *)((u8 *)arg1 + 4)) + (*(f32 *)((u8 *)arg2 + 4))) * 0.5f;
        sp.u14C = ((*(f32 *)((u8 *)arg1 + 8)) + (*(f32 *)((u8 *)arg2 + 8))) * 0.5f;
        impact_spark_flash_spawn(&sp.u144, arg3, arg4);
        impact_rumble_spawn(&sp.u144, arg3, arg4);
        impact_cam_shake_spawn(&sp.u144, arg3, arg4);
        explosion_sfx_play(1, sp.u144, sp.u148, sp.u14C, 0);
        fire_flash_light_spawn((u8 *) &sp.u144, arg3, arg4);
        sp.uE8 = 0;
        sp.uEA = 0xFF;
        sp.uEC = -0x40;
        sp.uEE = 0x47;
        sp.uF0 = 6;
        if (g_last_player_index >= 2) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        sp.uF4 = 4 >> var_v0;
        (*(f32 *)((u8 *)(&sp.uF8) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u144) + 0));
        (*(s32 *)((u8 *)(&sp.uF8) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u144) + 4));
        (*(s32 *)((u8 *)(&sp.uF8) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u144) + 8));
        sp.u11C = 7;
        sp.u104 = 23.0f;
        sp.u108 = 30.0f;
        sp.u10C = 45.0f;
        sp.u110 = 53.0f;
        sp.u114 = 203.0f;
        sp.u118 = 414.0f;
        if ((g_last_player_index >= 2) || (var_v0_2 = 0, ((g_player_count < 8) == 0))) {
            var_v0_2 = 1;
        }
        sp.u120 = 3 >> var_v0_2;
        sp.u134 = 0x19;
        sp.u136 = 0xF;
        sp.u138 = 0x64;
        sp.u13A = 0x64;
        sp.u13C = 0xC;
        sp.u13E = 0x14;
        sp.u124 = 15.0f;
        sp.u128 = 0.87200004f;
        sp.u12C = -0.39800003f;
        sp.u130 = 0.36400002f;
        if ((g_last_player_index >= 2) || (g_player_count >= 8)) {
            sp.u140 = -1;
        } else {
            sp.u140 = 0;
        }
        emit_random_sprites(&sp.uE8, arg3, arg4);
        hitinfo_from_obj_floor(&sp.uC4, arg0);
        sp.uBC = sp.u148 + 100.0f;
        sp.uB8 = sp.u144;
        sp.uC0 = sp.u14C;
        if (collision_floor_probe(&sp.uB8, 0, sp.u148 - 1000.0f, &sp.uC4) != 0) {
            sp.uAC = sp.uB8;
            sp.uB0 = sp.uC4;
            sp.uB4 = sp.uC0;
            shot_scorch_decal_spawn((s32) &sp.uC8, (s32) &sp.uAC, arg3, arg4);
            if ((tri_calc_normal(&sp.uC8, &sp.uA0, &sp.u94, &sp.u88) != 0) && (sp.u8C < 0.0f)) {
                impact_debris_emitter_spawn(&sp.uAC, arg3, arg4);
            }
        }
        (*(s32 *)((u8 *)(&sp.u40) + 0)) = (s32) (*(s32 *)((u8 *)(&g_explosion_fx_vec_a) + 0));
        (*(s32 *)((u8 *)(&sp.u40) + 4)) = (s32) (*(s32 *)((u8 *)(&g_explosion_fx_vec_a) + 4));
        (*(s32 *)((u8 *)(&sp.u40) + 8)) = (s32) (*(s32 *)((u8 *)(&g_explosion_fx_vec_a) + 8));
        (*(s32 *)((u8 *)(&sp.u34) + 0)) = (s32) (*(s32 *)((u8 *)(&g_explosion_fx_vec_b) + 0));
        (*(s32 *)((u8 *)(&sp.u34) + 4)) = (s32) (*(s32 *)((u8 *)(&g_explosion_fx_vec_b) + 4));
        (*(s32 *)((u8 *)(&sp.u34) + 8)) = (s32) (*(s32 *)((u8 *)(&g_explosion_fx_vec_b) + 8));
        sp.u4C = 4;
        sp.u50 = 8;
        (*(f32 *)((u8 *)(&sp.u54) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u144) + 0));
        (*(s32 *)((u8 *)(&sp.u54) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u144) + 4));
        (*(s32 *)((u8 *)(&sp.u54) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u144) + 8));
        sp.u68 = 12.0f;
        sp.u6C = 6.0f;
        sp.u60 = 0;
        sp.u62 = 0xFF;
        sp.u64 = -0x3F;
        sp.u66 = 0x57;
        sp.u78 = 0x32;
        sp.u7A = 0xA;
        sp.u70 = -1.4380001f;
        sp.u74 = 0.44900003f;
        sp.u7C = 0.24800001f;
        sp.u80 = 0.09900001f;
        sp.u84 = 22.859001f;
        emit_textured_burst(&sp.u4C, &sp.u40, &sp.u34, 3, 0.0f, 1U, (u8) (s32) arg3, arg4);
    }
}
/* was func_151BC494 */
void fire_flash_light_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (random_int() & 0xF) + 5;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    light_create_with_ctrl(sp48, sp3C, (random_int() % 21U) + 0x1E, 0xFF, 0x61, 0x36, 0xFFU, 0U, 0, arg1, arg2);
}

void fx_scorch_decal_spawn(f32, s32, s32, s32, s16, u8, u8, u8, u8, u8, u8, s32);

/* was func_151BC56C */
void shot_scorch_decal_spawn(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 pad;
    u32 sp40;
    f32 sp3C;

    sp3C = random_float();
    sp40 = random_int();
    fx_scorch_decal_spawn((sp3C * 75.0f) + 75.0f, ((sp40 % 56U) + 0xC8) & 0xFF, arg0, arg1, (random_int() % 205U) + 0x12B, 1, 1, 0, 0, 0, (s32) arg2, 0);
}

struct225 *light_create_obj_beam(struct127 *arg0, u8 arg1, struct17 *arg2, struct17 *arg3, f32 arg4, u8 arg5, s16 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 argB, u8 argC, u8 argD, u8 argE, s32 argF);
extern struct17 g_obj_beam_light_from; /* was D_800AAB40 */
extern struct17 g_obj_beam_light_to; /* was D_800AAB4C */

/* was func_151BC624 */
void obj_beam_light_attach(struct127 *arg0) {
    if (arg0 != NULL) {
        light_create_obj_beam(arg0, 1, &g_obj_beam_light_from, &g_obj_beam_light_to, 0.017699f, 2, 300, 255, 255, 255, 255, 1, 0, 0, 255, 1);
    }
}

s32 light_create_track_ptrs(s8 *, u8 *, u8 *, u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 g_fx_lod_scale_players; /* was D_800DCE54 */

/* was func_151BC6B4 */
void obj_trail_smoke_light_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s8 u60;
        s8 u61;
        s16 u62;
        s8 u64;
        u8 pad65[0x7];
        u8 * u6C;
        u8 u70;
        u8 pad71[0x3];
        u8 * u74;
        u8 u78;
        u8 pad79[0x3];
        s32 u7C;
        u8 pad80[0x8];
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        u8 pad98[0x4];
        s32 u9C;
        f32 uA0;
        f32 uA4;
        s16 uA8;
        s16 uAA;
        s32 uAC;
        u8 padB0[0x1];
        s8 uB1;
        u8 padB2[0x6];
        u8 * uB8;
        u8 uBC;
        u8 padBD[0x3];
        s32 uC0;
        s32 uC4;
        s32 uC8;
        f32 uCC;
        f32 uD0;
        s16 uD4;
        s8 uD6;
        s8 uD7;
        s8 uD8;
        s8 uD9;
    } sp;
    u8 *sp5C;
    u8 *sp58;
    u8 *sp54;
    s32 temp_v0;
    s32 temp_v0_3;
    u8 *temp_v0_2;

    if ((g_last_player_index < 2) && (g_player_count < 5)) {
        sp.uC0 = arg0 + 0x14;
        sp.uC4 = arg0 + 0x18;
        sp.uC8 = arg0 + 0x1C;
        sp.uD4 = 0x12C;
        sp.uD0 = 0.30339998f * g_fx_lod_scale_players;
        sp.uD6 = 4;
        sp.uD7 = 4;
        sp.uD8 = 1;
        sp.uD9 = 0;
        sp.uB8 = arg0;
        sp.uCC = 15.0f;
        sp.uBC = (*(u8 *)((u8 *)arg0 + 0x3B));
        temp_v0 = point_emitter_spawn((struct_eu_EF410 *) &sp.uC0, 8, arg1, arg2);
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x40, &sp.uB8, 8);
        }
    }
    sp.uB1 = 0x28;
    sp.u9C = (*(s32 *)((u8 *)arg0 + 0x14));
    sp.uA0 = (*(f32 *)((u8 *)arg0 + 0x18));
    sp.uA8 = 0x12C;
    sp.uAA = 6;
    sp.uAC = 0xC;
    sp.u74 = arg0;
    sp.uA4 = (*(f32 *)((u8 *)arg0 + 0x1C));
    sp.u78 = (*(u8 *)((u8 *)arg0 + 0x3B));
    (*(s32 *)((u8 *)(&sp.u7C) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.u9C) + 0));
    (*(s32 *)((u8 *)(&sp.u7C) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u9C) + 4));
    (*(s32 *)((u8 *)(&sp.u7C) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u9C) + 8));
    sp.u88 = 0.0f;
    sp.u8C = 0.0f;
    sp.u94 = -16384.0f;
    sp.u90 = -16384.0f;
    sp54 = arg0 + 0x1C;
    sp58 = arg0 + 0x18;
    sp5C = arg0 + 0x14;
    temp_v0_2 = fxrec_spawn(&sp.u9C, 0x28, 0x14, 0xA, 0xA, 0xA, 0, 0, 0, (u8) (s32) arg1, arg2);
    if (temp_v0_2 != NULL) {
        memcpy((*(s32 *)((u8 *)temp_v0_2 + 0x98)), &sp.u74, 0x24);
    }
    sp.u6C = arg0;
    sp.u60 = 2;
    sp.u61 = 0xE;
    sp.u70 = (*(u8 *)((u8 *)arg0 + 0x3B));
    sp.u62 = 0x12C;
    sp.u64 = 0x1F;
    temp_v0_3 = light_create_track_ptrs(&sp.u60, sp5C, sp58, sp54, 0, 0, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, 8, (s32) arg1, arg2);
    if (temp_v0_3 != 0) {
        memcpy(temp_v0_3 + 0x28, &sp.u6C, 8);
    }
}
void vec3_from_angles_byte(s16, s16, f32, void *);
s32 particle_puff_spawn(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* P95: f32 parameter */

/* was func_151BC920 */
void debris_spray_emit_b(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 sp6C[9];
    f32 temp_f2;

    sp6C[6] = arg0;
    sp6C[7] = arg1;
    sp6C[8] = arg2;
    vec3_from_angles_byte((s16) (random_int() & 0xFF), (s16) ((random_int() % 65U) - 0x20), random_float() * 1680.0f * 0.01f, &sp6C[3]);
    temp_f2 = (random_float() * 202.0f) + 208.0f;
    sp6C[0] = 0.0f;
    sp6C[1] = 0.0f;
    temp_f2 = temp_f2 * 0.001f;
    sp6C[2] = 0.0f;
    sp6C[3] += -arg3 * g_frame_step_inv * temp_f2;
    sp6C[4] += -arg4 * g_frame_step_inv * temp_f2;
    sp6C[5] += -arg5 * g_frame_step_inv * temp_f2;
    particle_puff_spawn(&sp6C[6], sp6C, &sp6C[3], 1.0f, ((random_float() * 1049.0f) + -1022.0f) * 0.001f, (random_float() * 124.0f) + 202.0f, (random_int() & 0xF) + 0x14, (random_int() % 201U) + 0x37, 0xF, 0xF, 0, -1, 0xCB, 0, 0, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1))); /* P95: float literal (asm passes the bits 0x3F800000) */
}

/* was func_151BCB30 */
s32 point_emitter_owner_valid(s32 **arg0) {
    s32 *temp_v0 = arg0[0x10];

    if (*temp_v0 == 0) {
        return 0;
    }
    return 1;
}

/* was func_151BCB54 */
void point_emitter_handle_message(void *arg0, void *arg1, u8 arg2) {
    s32 cur;
    u8 *temp_v0;
    cur = *(s32 *)((u8 *)arg0 + 0x40);
    if (arg2 == 0) {
        if (cur == (*(s32 *)((u8 *)arg1 + 0)) || ((*(u8 *)((u8 *)arg1 + 4)) == (*(u8 *)((u8 *)arg0 + 0x44)))) {
            node_destroy(arg0);
        }
    } else {
        temp_v0 = (u8 *)arg0 + 0x40;
        if (arg2 == 0x2D) {
            if (*(s32 *)((u8 *)arg1 + 0) == *(s32 *)(temp_v0 + 0)) {
                *(s32 *)(temp_v0 + 0) = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
                *(s32 *)(temp_v0 + 0) = *(s32 *)((u8 *)arg1 + 0);
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}

typedef struct { s32 x[3]; } S12_CBFC;
typedef struct { S12_CBFC pos; s16 t; u8 a; u8 pad[5]; } E20_CBFC;
/* was func_151BCBFC */
s32 trail_ring_life_fade_update(u8 *arg0) {
    s16 temp_a2;
    s32 temp_lo;
    u8 *temp_v0;
    s32 var_a1;
    u8 *temp_t4;
    u8 *temp_v1;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u16 *)((u8 *)arg0 + 0x1E)) & 8)) {
        return 0;
    }
    var_a1 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_a1 -= 1;
            if (var_a1 < 0) {
                var_a1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_v1 = (var_a1 * 0x14) + temp_v0;
            (*(s16 *)((u8 *)temp_v1 + 0xC)) = (s16) ((*(s16 *)((u8 *)temp_v1 + 0xC)) - g_frame_ticks);
            temp_a2 = (*(s16 *)((u8 *)temp_v1 + 0xC));
            if (temp_a2 < 0) {
                if (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    do {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                        }
                        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                    } while (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                }
            } else if (temp_a2 < 0xA) {
                temp_lo = temp_a2 * 0x19;
                if (temp_lo < (s32) (*(u8 *)((u8 *)temp_v1 + 0xE))) {
                    (*(u8 *)((u8 *)temp_v1 + 0xE)) = (u8) temp_lo;
                }
            }
        } while (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        *(S12_CBFC *)(arg0 + 0x54) = ((E20_CBFC *)temp_v0)[*(s8 *)(arg0 + 0x2D)].pos;
    } else {
        (*(f32 *)((u8 *)arg0 + 0x54)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    }
    return 1;
}

f32 vec3_length(void *);

/* was func_151BCD44 */
s32 trail_follow_owner_update(u8 *arg0) {
    struct {
        f32 u6C;
        f32 u70;
        f32 u74;
        u8 pad78[0x10];
        f32 u88;
        f32 u8C;
        f32 u90;
        u8 pad94[0x4];
        s32 u98;
        u8 * u9C;
    } sp;
    f32 sp4C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f20;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f14;
    f32 var_f16;
    s8 temp_v1;
    u8 *temp_a2;
    u8 *temp_t3;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_a2 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v0 = (*(u8 **)((u8 *)temp_a2 + 0));
    if (((*(s32 *)((u8 *)temp_v0 + 0)) == 0) || ((*(u8 *)((u8 *)temp_a2 + 4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B)))) {
        (*(u16 *)((u8 *)arg0 + 0x1E)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x1E)) | 8);
        return 1;
    }
    (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x18));
    (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x1C));
    sp.u88 = (*(f32 *)((u8 *)arg0 + 0x10)) - (*(f32 *)((u8 *)temp_a2 + 8));
    sp.u8C = (*(f32 *)((u8 *)arg0 + 0x14)) - (*(f32 *)((u8 *)temp_a2 + 0xC));
    sp.u98 = (*(s32 *)((u8 *)arg0 + 0x94));
    sp.u9C = temp_a2;
    sp.u90 = (*(f32 *)((u8 *)arg0 + 0x18)) - (*(f32 *)((u8 *)temp_a2 + 0x10));
    temp_f0 = vec3_length(&sp.u88);
    (*(f32 *)((u8 *)sp.u9C + 0x14)) = (f32) ((*(f32 *)((u8 *)sp.u9C + 0x14)) + (temp_f0 * 0.048708f * g_frame_step_f));
    temp_f2 = (*(f32 *)((u8 *)sp.u9C + 0x14));
    (*(f32 *)((u8 *)sp.u9C + 0x1C)) = (f32) ((*(f32 *)((u8 *)sp.u9C + 0x1C)) + (temp_f0 * 9.708836f));
    sp4C = temp_f2;
    if (temp_f2 > 1.0f) {
        temp_t3 = sp.u9C + 8;
        temp_f0_2 = 1.0f / sp4C;
        (*(f32 *)((u8 *)(&sp.u6C) + 0)) = (*(f32 *)((u8 *)temp_t3 + 0));
        (*(s32 *)((u8 *)(&sp.u6C) + 4)) = (s32) (*(s32 *)((u8 *)temp_t3 + 4));
        var_f16 = (*(f32 *)((u8 *)sp.u9C + 0x18)) + g_frame_step_f;
        (*(s32 *)((u8 *)(&sp.u6C) + 8)) = (s32) (*(s32 *)((u8 *)temp_t3 + 8));
        temp_f2_2 = (*(f32 *)((u8 *)sp.u9C + 0x20));
        var_f14 = temp_f2_2;
        temp_f20 = -(var_f16 * temp_f0_2);
        do {
            temp_v0_2 = ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x14) + sp.u98;
            (*(f32 *)((u8 *)temp_v0_2 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u6C) + 0));
            (*(s32 *)((u8 *)temp_v0_2 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u6C) + 4));
            (*(s16 *)((u8 *)temp_v0_2 + 0xC)) = 0xC;
            (*(s8 *)((u8 *)temp_v0_2 + 0xE)) = 0x64;
            (*(f32 *)((u8 *)temp_v0_2 + 0x10)) = var_f14;
            (*(s32 *)((u8 *)temp_v0_2 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u6C) + 8));
            if (var_f14 > 16384.0f) {
                do {
                    (*(f32 *)((u8 *)temp_v0_2 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x10)) - 32768.0f);
                } while ((*(f32 *)((u8 *)temp_v0_2 + 0x10)) > 16384.0f);
            }
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
            }
            temp_v1 = (*(s8 *)((u8 *)arg0 + 0x2D));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
            if (temp_v1 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v1 + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
            }
            var_f14 += ((*(f32 *)((u8 *)sp.u9C + 0x1C)) - temp_f2_2) * temp_f0_2;
            sp.u6C += sp.u88 * temp_f0_2;
            sp.u70 += sp.u8C * temp_f0_2;
            var_f16 += temp_f20;
            sp.u74 += sp.u90 * temp_f0_2;
            (*(f32 *)((u8 *)sp.u9C + 0x14)) = (f32) ((*(f32 *)((u8 *)sp.u9C + 0x14)) - 1.0f);
        } while ((*(f32 *)((u8 *)sp.u9C + 0x14)) > 1.0f);
        (*(f32 *)((u8 *)temp_t3 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u6C) + 0));
        (*(s32 *)((u8 *)temp_t3 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u6C) + 4));
        (*(s32 *)((u8 *)temp_t3 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u6C) + 8));
        (*(f32 *)((u8 *)sp.u9C + 0x20)) = var_f14;
        (*(f32 *)((u8 *)sp.u9C + 0x18)) = var_f16;
    }
    return 1;
}
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
Gfx *gfx_load_texture_cached(Gfx *gfx, s32 tex, s32 frame, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *flag, s32 argA);
Gfx *gfx_env_color_cached(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5);
Gfx *gfx_set_combine_mode(Gfx *arg0, u8 arg1, u8 *arg2);
Gfx *gfx_geometry_mode_cached(Gfx *gfx, s32 set, s32 clear);
u8 *gfx_other_mode_cached(Gfx *, s32, s32, u8 *);
f32 sqrtf(f32);
extern s32 g_gfx_tlut_mode; /* was D_800D30BC */
extern s32 g_render_mode_pairs[]; /* was D_800A4EA8 */
extern u8 g_ribbon_trail_texture[]; /* was D_80091084 */

/* one ribbon vertex: the strip point +- the side offset, texture s from the point, t 0 / 0x7FF */
#define RIBBON_VTX(v, x, y, z, s, t, a) \
    do { \
        (v)->ob[0] = (s32) (x); \
        (v)->ob[1] = (s32) (y); \
        (v)->ob[2] = (s32) (z); \
        (v)->tc[0] = (s); \
        (v)->tc[1] = (t); \
        (v)->cn[0] = 0xFF; \
        (v)->cn[1] = 0xFF; \
        (v)->cn[2] = 0xFF; \
        (v)->cn[3] = (a); \
        (v)->flag = 0; \
    } while (0)

// ribbon_strip_draw: g_fxrec_draw_fns draw handler (kind 10) of a ribbon through the point ring obj +0x94 (0x14 bytes:
// x, y, z, alpha byte +0xE, f32 texture s +0x10; ring of obj[0x25], newest obj +0x2E - 1, oldest obj +0x2D, count
// obj +0x2C). Each point gets two vertices 35 units either side along (point - previous point) x (point - camera);
// each segment loads 4 vertices and draws two triangles. With obj +0x1E bit 2 the strip starts at the object's
// position (+0x10, alpha 0x80, s 0) instead of the newest point. Texture g_ribbon_trail_texture, white, render mode
// g_gfx_tlut_mode | 0x82CA0 with the g_render_mode_pairs entry 3; vertices from vtx_slot_buffer_get (obj[0x25] * 32 + 0xA0 bytes).
// Returns the display list end; draws nothing with fewer than 2 points or no vertex buffer.
/* was func_151BD040 */
s32 ribbon_strip_draw(u8 *obj, s32 gfx, s16 arg2) {
    Vtx_t *vtx;
    f32 *cam;
    u8 *pts;
    u8 *p;
    Gfx *g;
    f32 cur[3];
    f32 next[3];
    f32 curS;
    f32 nextS;
    f32 vx, vy, vz;
    f32 dx, dy, dz;
    f32 nx, ny, nz;
    f32 len2;
    f32 k;
    s32 s;
    s32 i;
    s32 j;
    u8 curA;
    u8 nextA;
    u8 flag;

    if (*(s8 *) (obj + 0x2C) < 2) {
        return gfx;
    }
    vtx_slot_buffer_get((s32 *) (obj + 0x84), arg2, obj[0x25] * 32 + 0xA0, (s32 *) &vtx, NULL);
    if (vtx == NULL) {
        return gfx;
    }
    cam = camera_get_pos(arg2);
    pts = *(u8 **) (obj + 0x94);
    flag = 1;
    g = gfx_load_texture_cached((Gfx *) gfx, (s32) g_ribbon_trail_texture, 0, 0, 0, 0, 0x1F, 0, 0, &flag, 3);
    g = gfx_env_color_cached(g, 0xFF, 0xFF, 0xFF, 0xFF, &flag);
    g = gfx_set_combine_mode(g, 0x4E, &flag);
    g = gfx_geometry_mode_cached(g, 0x200005, 0x1F0600);
    g = (Gfx *) gfx_other_mode_cached(g, g_gfx_tlut_mode | 0x80000 | 0x2CA0, g_render_mode_pairs[7] | g_render_mode_pairs[6], &flag);

    if (*(u16 *) (obj + 0x1E) & 2) {
        j = *(s8 *) (obj + 0x2E) - 1;
        if (j < 0) {
            j = obj[0x25] - 1;
        }
        cur[0] = *(f32 *) (obj + 0x10);
        cur[1] = *(f32 *) (obj + 0x14);
        cur[2] = *(f32 *) (obj + 0x18);
        curA = 0x80;
        curS = 0.0f;
    } else {
        i = *(s8 *) (obj + 0x2E) - 1;
        if (i < 0) {
            i = obj[0x25] - 1;
        }
        j = i - 1;
        if (j < 0) {
            j = obj[0x25] - 1;
        }
        p = pts + i * 0x14;
        cur[0] = *(f32 *) (p + 0);
        cur[1] = *(f32 *) (p + 4);
        cur[2] = *(f32 *) (p + 8);
        curS = *(f32 *) (p + 0x10);
        curA = p[0xE];
    }
    p = pts + j * 0x14;
    next[0] = *(f32 *) (p + 0);
    next[1] = *(f32 *) (p + 4);
    next[2] = *(f32 *) (p + 8);
    nextA = p[0xE];
    nextS = *(f32 *) (p + 0x10);

    /* the first pair, at the start point */
    vx = cur[0] - cam[0];
    vy = cur[1] - cam[1];
    vz = cur[2] - cam[2];
    dx = cur[0] - next[0];
    dy = cur[1] - next[1];
    dz = cur[2] - next[2];
    nx = dy * vz - vy * dz;
    ny = dz * vx - vz * dx;
    nz = dx * vy - vx * dy;
    len2 = nx * nx + ny * ny + nz * nz;
    if (len2 == 0.0f) {
        nx = ny = nz = 0.0f;
    } else {
        k = 35.0f / sqrtf(len2);
        nx *= k;
        ny *= k;
        nz *= k;
    }
    s = (s32) curS;
    RIBBON_VTX(vtx, cur[0] + nx, cur[1] + ny, cur[2] + nz, s, 0, curA);
    vtx++;
    RIBBON_VTX(vtx, cur[0] - nx, cur[1] - ny, cur[2] - nz, s, 0x7FF, curA);
    vtx++;

    /* one segment per older point, until the oldest (+0x2D) */
    do {
        vx = next[0] - cam[0];
        vy = next[1] - cam[1];
        vz = next[2] - cam[2];
        i = j;
        j--;
        dx = cur[0] - next[0];
        dy = cur[1] - next[1];
        dz = cur[2] - next[2];
        nx = dy * vz - vy * dz;
        ny = dz * vx - vz * dx;
        nz = dx * vy - vx * dy;
        len2 = nx * nx + ny * ny + nz * nz;
        s = (s32) nextS;
        if (len2 == 0.0f) {
            nx = ny = nz = 0.0f;
        } else {
            k = 35.0f / sqrtf(len2);
            nx *= k;
            ny *= k;
            nz *= k;
        }
        RIBBON_VTX(vtx, next[0] + nx, next[1] + ny, next[2] + nz, s, 0, nextA);
        vtx++;
        RIBBON_VTX(vtx, next[0] - nx, next[1] - ny, next[2] - nz, s, 0x7FF, nextA);
        vtx++;
        ((s32 *) g)[0] = 0x01004008;           /* gSPVertex(vtx - 4, 4, 0) */
        ((s32 *) g)[1] = (s32) (vtx - 4);
        g++;
        ((s32 *) g)[0] = 0x05000204;           /* gSP1Triangle(0, 1, 2) */
        ((s32 *) g)[1] = 0;
        g++;
        ((s32 *) g)[0] = 0x05020604;           /* gSP1Triangle(1, 3, 2) */
        ((s32 *) g)[1] = 0;
        g++;
        if (j < 0) {
            j = obj[0x25] - 1;
        }
        if (i != *(s8 *) (obj + 0x2D)) {
            cur[0] = next[0];
            cur[1] = next[1];
            cur[2] = next[2];
            p = pts + j * 0x14;
            next[0] = *(f32 *) (p + 0);
            next[1] = *(f32 *) (p + 4);
            next[2] = *(f32 *) (p + 8);
            nextS = *(f32 *) (p + 0x10);
            nextA = p[0xE];
        }
    } while (i != *(s8 *) (obj + 0x2D));
    return (s32) g;
}
#undef RIBBON_VTX

/* was func_151BD7CC */
void trail_follow_handle_message(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 *p;
  s32 id;
  s32 t;
  p = *((s32 **) (arg0 + 0x98));
  id = p[0];
  t = id;
  if (arg2 == 0)
  {
    if ((t == arg1[0]) || (((u8 *) p)[4] == ((u8 *) arg1)[4]))
    {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (unfilled jr ra delay slot, s69)
      arg0[0x30] = 0;
      *((u16 *) (arg0 + 0x1E)) |= 8;
    }
  }
  else
    if (arg2 == 0x2D)
  {
    t = arg1[0];
    if (t == *p)
    {
      p[0] = arg1[1];
      ((u8 *) p)[4] = ((u8 *) arg1)[9];
      return;
    }
    if (arg1[1] == *p)
    {
      p[0] = t;
      ((u8 *) p)[4] = ((u8 *) arg1)[8];
    }
  }
}

/* was func_151BD86C */
s32 fx_owner_alive_check(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x28);

    if (*(s32 *)temp_v0 == 0) {
        return 0;
    }
    if (arg0[0x2C] != temp_v0[0x3B]) {
        return 0;
    }
    return 1;
}

typedef struct {
    u8 u0;
    u8 *u4;
    s8 u8_;
    f32 uC;
    f32 u10;
    f32 u14;
    f32 u18;
    f32 u1C;
    f32 u20;
    s8 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s8 u2E;
    s8 u2F;
    s8 u30;
    f32 u34;
    s8 u38;
    s8 u39;
} Sd8a8;
s32 bone_emitter_spawn(Sd8a8 *, s32, ...);
/* was func_151BD8A8 */
void obj_twin_bone_emitters_spawn(u8 *arg0, s32 arg1, s32 arg2)
{
  Sd8a8 s;
  s16 zp; // fakematch: unused pad, puts z at sp+0x20
  s16 z;
  s32 v;
  if (arg0 != 0)
  {
    s.u0 = arg0[0x3B];
    s.u4 = arg0;
    s.u8_ = 1;
    s.u24 = 0;
    s.u26 = 0x32;
    s.u28 = 0x64;
    s.u2A = 0x12C;
    s.uC = 31.0f;
    s.u2E = 4;
    s.u2F = 4;
    s.u30 = 3;
    s.u38 = 5;
    s.u39 = -1;
    z = 0;
    s.u10 = -34.0f;
    s.u14 = -117.0f;
    s.u18 = 35.0f;
    s.u1C = -24.0f;
    s.u20 = -182.0f;
    s.u34 = 0.30061f;
    v = bone_emitter_spawn(&s, 2);
    if (v != 0)
    {
      memcpy((void *) (v + 0x80), &z, 2);
    }
    s.uC = -s.uC;
    s.u18 = -s.u18;
    v = bone_emitter_spawn(&s, 2);
    if (v != 0)
    {
      memcpy((void *) (v + 0x80), &z, 2);
    }
  }
}

/* was func_151BD9DC */
s32 bone_emitter_timer_reset(s16 *arg0) {
    arg0[0x40] = 0;
    return 1;
}

s32 particle_spawn_basic(s32 *, s32, s32, u8, s32);

/* was func_151BD9EC */
void bone_emitter_particle_emit(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, f32 arg4, u8 *arg5) {
    struct {
        u8 * u38;
        u8 u3C;
        u8 pad3D[0x7];
        u8 * u44;
        s32 u48;
        s32 u4C;
        s16 u50;
        s16 u52;
        s32 u54;
        s32 u58;
        s8 u5C;
        s8 u5D;
        s8 u5E;
        s8 u5F;
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        s8 u64;
        s8 u65;
        s16 u66;
        s16 u68;
        s16 u6A;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        s32 uA0;
        u8 padA4[0x4];
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        s8 uAD;
    } sp;
    s32 sp2C;
    f32 temp_f10;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f6;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    if (((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x74)) & 0xF) != 0xF) {
        sp.u65 = 0x29;
        sp.u50 = 0xE03;
        sp.u48 = 0x200005;
        sp.u4C = 0;
        sp.u54 = 0;
        sp.u58 = 0;
        temp_f6 = random_float() * 251.0f;
        sp.u66 = 0x14;
        sp.u68 = 0xC;
        sp.u9C = (temp_f6 + 44.0f) * 0.001f;
        var_v1 = 0;
        if (random_int() & 1) {
            var_v1 = 0x40;
        }
        sp2C = var_v1;
        if (random_int() & 1) {
            var_v0 = 0x80;
        } else {
            var_v0 = 0;
        }
        sp.uA0 = var_v0 | 7 | var_v1 | 0xDE00;
        sp.uA8 = 3;
        sp.uA9 = 3;
        sp.uAB = -1;
        sp.uAC = -1;
        sp.uAD = 7;
        sp.u6A = 0x22;
        sp.u5C = 0xDD;
        sp.u5D = 0xD3;
        sp.u5E = 0xCD;
        sp.u5F = 0xFF;
        sp.u60 = 0x57;
        sp.u61 = 0x55;
        sp.u62 = 0x5A;
        sp.u44 = (u8 *)0x3F6F49BF;
        sp.u6C = 1.034358f;
        sp.u63 = (random_int() % 156U) + 0x64;
        sp.u64 = 0xFF;
        sp.u52 = (random_int() % 18U) + 0x19;
        temp_f18 = (random_float() * 53.0f) + 49.0f;
        sp.u74 = temp_f18;
        sp.u70 = temp_f18;
        temp_f16 = ((*(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)arg0 + 0))) * (*(f32 *)((u8 *)arg5 + 0x74));
        sp.u90 = temp_f16;
        temp_f10 = ((*(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)arg0 + 4))) * (*(f32 *)((u8 *)arg5 + 0x74));
        sp.u94 = temp_f10;
        temp_f18_2 = ((*(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)arg0 + 8))) * (*(f32 *)((u8 *)arg5 + 0x74));
        sp.u98 = temp_f18_2;
        sp.u78 = (*(f32 *)((u8 *)arg0 + 0)) - (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x14));
        sp.u7C = (*(f32 *)((u8 *)arg0 + 4)) - (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x18));
        sp.u80 = (*(f32 *)((u8 *)arg0 + 8)) - (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x1C));
        sp.u78 += temp_f16 * arg4;
        sp.u7C += temp_f10 * arg4;
        sp.u80 += temp_f18_2 * arg4;
        sp.u38 = (*(u8 **)((u8 *)arg5 + 0x1C));
        sp.uAA = 0x13;
        sp.u3C = (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x3B));
        sp.u84 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x14));
        sp.u88 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x18));
        sp.u8C = (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x1C));
        temp_v0 = particle_spawn_basic(&sp.u48, 1, 0x10, (*(u8 *)((u8 *)arg5 + 0xC)), (s32) (*(u8 *)((u8 *)arg5 + 1)));
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0xA8, &sp.u44, 4);
            memcpy(temp_v0 + 0xB0, &sp.u38, 8);
        }
    }
}
/* was func_151BDD00 */
f32 bone_emitter_timer_step(s16 *arg0) {
    s16 temp_v0 = arg0[0x40];
    f32 ret = (f32)temp_v0 * 2 * g_bone_emitter_timer_scale + g_bone_emitter_timer_base;

    arg0[0x40] = temp_v0 + g_frame_ticks;
    return ret;
}

s32 particle_upd_damp_vel();

/* P373: particle update handler (g_particle_update_fns [19], called by particle_sprite_update as s32 (particle, old
 * position); 0 = the particle dies and its death handler runs). The asm tail-calls particle_upd_damp_vel and returns with its
 * v0 untouched. The C used to be void, and the port's indirect call of a void function reads 0, so every particle
 * of this kind died in its first update (same class as P372's flame_flicker). */
/* was func_151BDD4C */
s32 particle_follow_owner_update(u8 *particle, s32 old_pos) {   /* particle was arg0, old_pos was arg1; P76: both pass through to particle_upd_damp_vel */
    u8 *owner; /* was temp_v0 */

    owner = (*(u8 **)((u8 *)particle + 0xB0));
    if (((*(s32 *)owner) != 0) && ((*(u8 *)((u8 *)owner + 4)) != 0xFF)) {
        (*(f32 *)((u8 *)particle + 0x4C)) = (f32) (*(f32 *)((u8 *)owner + 0x14));
        (*(f32 *)((u8 *)particle + 0x50)) = (f32) (*(f32 *)((u8 *)owner + 0x18));
        (*(f32 *)((u8 *)particle + 0x54)) = (f32) (*(f32 *)((u8 *)owner + 0x1C));
    }
    return particle_upd_damp_vel(particle, old_pos);
}

/* was func_151BDDA4 */
void obj_aura_burst_stop(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    effect_nodes_broadcast(&tmp, 0x3B);
}

/* effect3d_spawn_full's particle spec and particle_emitter_spawn's spawn block (0x58 bytes). */
typedef struct {
    /* 0x00 */ u8 texture;
    /* 0x01 */ u8 u01;
    /* 0x02 */ s16 texSet;
    /* 0x04 */ s16 life;
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ u8 color[4];
    /* 0x14 */ f32 halfW;
    /* 0x18 */ f32 halfH;
    /* 0x1C */ s32 angle[3];
    /* 0x28 */ s32 vel[3];
    /* 0x34 */ f32 scale[3];
    /* 0x40 */ s32 flags;
    /* 0x44 */ u8 u44;
    /* 0x45 */ u8 u45;
    /* 0x46 */ u8 u46;
    /* 0x47 */ u8 u47;
    /* 0x48 */ s32 u48;
    /* 0x4C */ u8 u4C;
    /* 0x4D */ u8 pad4D[0xB];
} PartSpecBDDD8;

/* particle_emitter_spawn's emitter block (filled up to 0x5A; the call passes size 0x78). */
typedef struct {
    /* 0x00 */ f32 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 u08;
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ s32 u24[8];
    /* 0x44 */ s32 u44;
    /* 0x48 */ f32 u48;
    /* 0x4C */ s16 u4C[4];
    /* 0x54 */ u8 u54[4];
    /* 0x58 */ u8 u58;
    /* 0x59 */ s8 u59;
    /* 0x5A */ u8 pad5A[2];
} EmitBDDD8;

/* 0x5C bytes copied to each particle's +0x110. */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 room;
    /* 0x05 */ u8 index;
    /* 0x08 */ f32 u08;
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 u38;
    /* 0x3C */ f32 u3C;
    /* 0x40 */ f32 scale[4];
    /* 0x50 */ u8 *group;
    /* 0x54 */ f32 midY;
    /* 0x58 */ u8 u58;
} PartExtraBDDD8;

/* 0x18 bytes copied to each emitter's +0x170. */
typedef struct {
    /* 0x00 */ s16 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ u8 *group;
    /* 0x0C */ u8 index;
    /* 0x10 */ u8 *obj;
    /* 0x14 */ u8 room;
} EmitExtraBDDD8;

/* 0x18 bytes copied to the group object's +0x28; the effects are recorded in it. */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 room;
    /* 0x08 */ u8 *part[2];
    /* 0x10 */ u8 *emit[2];
} GroupBDDD8;

struct260 *effect_node_create(s16 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, struct37 *arg6, u8 arg7, s32 arg8);
void *effect3d_spawn_full(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB);
u8 *particle_emitter_spawn(void *emit, s32 emitSize, void *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8, s32 arg9);
s32 random_int(void);
extern s32 g_effect3d_default_params; /* was D_800A4AA0 */

// object_aura_burst_spawn: the aura_group_spawn (object_aura_spawn) effect without its rumble_request / light_create_obj_joint calls: creates
// a group object (effect_node_create kind 300, flag 0, 0x18-byte block {obj, obj+0x3B}) and, when it exists, two particles
// (effect3d_spawn_full texture 0x5F, g_effect3d_default_params list, random blend 1 / 3; +0x110 gets index, object, room, group, mid height
// (obj +0x14C + +0x150) / 2 and this function's constants) and two emitters (particle_emitter_spawn texture 0x60, 0x2A; +0x170
// gets index, object, room, group); the group records them at +0x30 / +0x38. `alpha` / `owner` go to every spawner.
/* was func_151BDDD8 */
s32 aura_burst_group_spawn(u8 *obj, u8 alpha, s32 owner) {
    EmitExtraBDDD8 ee;
    PartSpecBDDD8 spawn;
    struct {
        EmitBDDD8 emit; /* particle_emitter_spawn reads 0x78 bytes: on into spec */
        PartSpecBDDD8 spec;
        PartExtraBDDD8 extra; /* kept next to spec as in the asm frame */
    } fr;
    GroupBDDD8 init;
    u8 *group;
    GroupBDDD8 *g;

    init.obj = obj;
    init.room = obj[0x3B];
    init.part[0] = NULL;
    init.part[1] = NULL;
    init.emit[0] = NULL;
    init.emit[1] = NULL;
    group = (u8 *)effect_node_create(300, -1, 0x40, -1, 0, 0x33, (struct37 *)0x18, alpha, owner);
    if (group != NULL) {
        g = (GroupBDDD8 *)(group + 0x28);
        memcpy((u8 *)g, (u8 *)&init, 0x18);

        fr.extra.u58 = 0;
        fr.extra.obj = obj;
        fr.extra.midY = (*(f32 *)(obj + 0x14C) + *(f32 *)(obj + 0x150)) * 0.5f;
        fr.extra.u08 = 15.045272f;
        fr.extra.u10 = 5.8676558f;
        fr.extra.u18 = 12.111444f;
        fr.extra.u0C = 0.396174f;
        fr.extra.room = obj[0x3B];
        fr.extra.u24 = 0.0f;
        fr.extra.u28 = 0.0f;
        fr.extra.u38 = 0.0f;
        fr.spec.halfW = 0.0f;
        fr.spec.halfH = 0.0f;
        fr.extra.u3C = 0.0f;
        fr.extra.scale[2] = 1.0f;
        fr.extra.scale[0] = 1.0f;
        fr.extra.scale[3] = 1.0f;
        fr.extra.scale[1] = 1.0f;
        fr.spec.texture = 0x5F;
        fr.spec.u01 = 8;
        fr.spec.texSet = 0x2203;
        fr.spec.life = 300;
        fr.spec.u08 = 0;
        fr.spec.u0C = 0;
        fr.spec.color[0] = 0xFF;
        fr.spec.color[1] = 0xFF;
        fr.spec.color[2] = 0xFF;
        fr.spec.color[3] = 0xFF;
        fr.extra.u14 = 0.1042563f;
        fr.extra.u20 = 0.5197371f;
        fr.extra.u1C = 0.34404588f;
        fr.extra.u2C = 160.0f;
        fr.extra.u30 = 95.0f;
        fr.extra.u34 = 207.5f;
        fr.extra.group = group;
        fr.spec.angle[0] = ((s32 *)g_vec3_zero)[0];
        fr.spec.angle[1] = ((s32 *)g_vec3_zero)[1];
        fr.spec.angle[2] = ((s32 *)g_vec3_zero)[2];
        fr.spec.vel[0] = ((s32 *)g_vec3_zero)[0];
        fr.spec.vel[1] = ((s32 *)g_vec3_zero)[1];
        fr.spec.vel[2] = ((s32 *)g_vec3_zero)[2];
        fr.spec.scale[0] = 1.0f;
        fr.spec.scale[1] = 1.0f;
        fr.spec.scale[2] = 1.0f;
        fr.spec.flags = 0x40EC0000;
        fr.spec.u44 = 0;
        fr.spec.u45 = 0xFF;
        fr.spec.u46 = 0;
        fr.spec.u47 = 7;
        fr.spec.u48 = 0;
        for (fr.extra.index = 0; fr.extra.index < 2; fr.extra.index++) {
            g->part[fr.extra.index] = effect3d_spawn_full(&fr.spec, (s32)&g_effect3d_default_params, 0, 0x25, 0, 0x1D,
                                              ((random_int() & 1) ? 2 : 0) + 1, 0, 0, 0x5C,
                                              alpha, owner);
            if (g->part[fr.extra.index] != NULL) {
                memcpy(g->part[fr.extra.index] + 0x110, (u8 *)&fr.extra, 0x5C);
            }
        }

        ee.u00 = 0;
        ee.u04 = 1.0f;
        ee.obj = obj;
        ee.group = group;
        ee.room = obj[0x3B];
        fr.emit.u24[0] = -1;
        fr.emit.u24[4] = -1;
        fr.emit.u24[1] = -1;
        fr.emit.u24[5] = -1;
        fr.emit.u24[2] = -1;
        fr.emit.u24[6] = -1;
        fr.emit.u24[3] = -1;
        fr.emit.u24[7] = -1;
        fr.emit.u59 = -1;
        fr.emit.u00 = 50.3f;
        fr.emit.u04 = 50.3f;
        fr.emit.u08 = 30.9f;
        fr.emit.u0C = 30.9f;
        fr.emit.u10 = 0.1f;
        fr.emit.u14 = 0.1f;
        fr.emit.u18 = 1.0f;
        fr.emit.u44 = 0;
        fr.emit.u48 = 1.0f;
        fr.emit.u4C[0] = 0;
        fr.emit.u4C[1] = 0;
        fr.emit.u4C[2] = 0;
        fr.emit.u4C[3] = 0;
        fr.emit.u54[0] = 0;
        fr.emit.u54[1] = 0;
        fr.emit.u54[2] = 0;
        fr.emit.u54[3] = 0;
        fr.emit.u58 = 0xF;
        spawn.texture = 0x60;
        spawn.u01 = 3;
        spawn.texSet = 0x2203;
        spawn.life = 300;
        spawn.u08 = 0;
        spawn.u0C = 0;
        spawn.color[0] = 0xFF;
        spawn.color[1] = 0xFF;
        spawn.color[2] = 0xFF;
        spawn.color[3] = 0xFF;
        spawn.halfW = 100.0f;
        spawn.halfH = 100.0f;
        fr.emit.u1C = 0.7f;
        fr.emit.u20 = 1e-06f;
        spawn.angle[0] = ((s32 *)g_vec3_zero)[0];
        spawn.angle[1] = ((s32 *)g_vec3_zero)[1];
        spawn.angle[2] = ((s32 *)g_vec3_zero)[2];
        spawn.vel[0] = ((s32 *)g_vec3_zero)[0];
        spawn.vel[1] = ((s32 *)g_vec3_zero)[1];
        spawn.vel[2] = ((s32 *)g_vec3_zero)[2];
        spawn.scale[0] = 1.0f;
        spawn.scale[1] = 1.0f;
        spawn.scale[2] = 1.0f;
        spawn.flags = 0xCD2002;
        spawn.u44 = 0xFF;
        spawn.u45 = 0xFF;
        spawn.u46 = 0;
        spawn.u47 = 7;
        spawn.u48 = 0;
        spawn.u4C = 0xFF;
        for (ee.index = 0; ee.index < 2; ee.index++) {
            g->emit[ee.index] = particle_emitter_spawn(&fr.emit, 0x78, &spawn, 0, 0x2A, 0, 0, -1, alpha, owner);
            if (g->emit[ee.index] != NULL) {
                memcpy(g->emit[ee.index] + 0x170, (u8 *)&ee, 0x18);
            }
        }
    }
    /* the asm returns what v0 last held: 0 without a group, else the final emitter index (2) */
    return group != NULL ? 2 : 0;
}

void mtx_transform_points(f32 **, f32 **, void *, s32);
extern f32 g_aura_burst_emit_pt0[3]; /* the two emitter offsets (bone space); was D_800AAB58 */
extern f32 g_aura_burst_emit_pt1[3]; /* was D_800AAB64 */
extern f32 g_aura_burst_dir_pt0[3]; /* the two direction points; was D_800AAB70 */
extern f32 g_aura_burst_dir_pt1[3]; /* was D_800AAB7C */
// player_twin_emitters_follow: handler 2 of D_8008A980 (`void (u8 *)`; same shape as twin_emitters_follow_owner).
// Ends the effect (+0xE = -1) when the owner (+0x28) is gone or its id +0x3B no longer matches +0x2C. While the
// owner has bone matrices (+0x1D4) and its +0x74 low nibble is not 0xF, it transforms the four points g_aura_burst_emit_pt0..7C
// by the first matrix (mtx_transform_points) and gives each of the two emitter pairs (+0x30 / +0x38 and +0x34 / +0x3C) its
// position and direction: the first kind gets the flag 1 at +0x168, the second the flag 2 (and loses 4) at +0x58;
// otherwise both flags are cleared. For the four players (owner index in g_objects below 4) the sizes follow the
// player's state word (g_cont_frame[0][player], bit 0x8000): first kind +0x158 / +0x15C = 6 / 21, else 3 / 8; second
// kind +0x174 = 1.5, else 1.
/* was func_151BE33C */
void aura_burst_follow_owner(u8 *arg0) {
    u8 *owner = *(u8 **) (arg0 + 0x28);
    u8 **a = (u8 **) (arg0 + 0x30);
    u8 **b = (u8 **) (arg0 + 0x38);
    f32 *src[4];
    f32 *dst[4];
    f32 pos[2][3]; /* sp88, sp94 */
    f32 dir[2][3]; /* sp70, sp7C */
    u8 *p;
    u8 i;
    s32 player;

    if (*(s32 *) owner == 0 || arg0[0x2C] != owner[0x3B]) {
        *(s16 *) (arg0 + 0xE) = -1;
        return;
    }
    if (*(u8 **) (owner + 0x1D4) != NULL && (owner[0x74] & 0xF) != 0xF) {
        src[0] = g_aura_burst_emit_pt0;
        src[1] = g_aura_burst_emit_pt1;
        src[2] = g_aura_burst_dir_pt0;
        src[3] = g_aura_burst_dir_pt1;
        dst[0] = pos[0];
        dst[1] = pos[1];
        dst[2] = dir[0];
        dst[3] = dir[1];
        mtx_transform_points(src, dst, *(u8 **) (owner + 0x1D4) + 0x40, 4);
        for (i = 0; i < 2; i++) {
            p = a[i];
            if (p != NULL) {
                p[0x168] |= 1;
                ((f32 *) (p + 0x34))[0] = pos[i][0];
                ((f32 *) (p + 0x34))[1] = pos[i][1];
                ((f32 *) (p + 0x34))[2] = pos[i][2];
                ((f32 *) (p + 0x40))[0] = dir[i][0];
                ((f32 *) (p + 0x40))[1] = dir[i][1];
                ((f32 *) (p + 0x40))[2] = dir[i][2];
            }
            p = b[i];
            if (p != NULL) {
                *(s32 *) (p + 0x58) |= 2;
                *(s32 *) (p + 0x58) &= ~4;
                ((f32 *) (p + 0x34))[0] = pos[i][0];
                ((f32 *) (p + 0x34))[1] = pos[i][1];
                ((f32 *) (p + 0x34))[2] = pos[i][2];
                ((f32 *) (p + 0x40))[0] = dir[i][0];
                ((f32 *) (p + 0x40))[1] = dir[i][1];
                ((f32 *) (p + 0x40))[2] = dir[i][2];
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (a[i] != NULL) {
                a[i][0x168] &= ~1;
            }
            if (b[i] != NULL) {
                *(s32 *) (b[i] + 0x58) &= ~2;
            }
        }
    }
    player = (owner - (u8 *) g_objects) / 0x32C;
    if (player < 4) {
        for (i = 0; i < 2; i++) {
            p = a[i];
            if (p != NULL) {
                if (*((u16 **) g_cont_frame[0])[(u8) player] & 0x8000) {
                    *(f32 *) (p + 0x158) = 6.0f;
                    *(f32 *) (p + 0x15C) = 21.0f;
                } else {
                    *(f32 *) (p + 0x158) = 3.0f;
                    *(f32 *) (p + 0x15C) = 8.0f;
                }
            }
            p = b[i];
            if (p != NULL) {
                if (*((u16 **) g_cont_frame[0])[(u8) player] & 0x8000) {
                    *(f32 *) (p + 0x174) = 1.5f;
                } else {
                    *(f32 *) (p + 0x174) = 1.0f;
                }
            }
        }
    }
}

typedef struct {
    s32 a;
    u8 b;
} K_E65C;
void node_destroy(struct102 *arg0);
s32 node_handle_link_message(s32, u8, s32, s32, s32);
/* was func_151BE65C */
void aura_burst_handle_message(struct102 *arg0, K_E65C *arg1, u8 arg2) {
    s32 t;
    K_E65C *p;
    struct102 **pa0 = &arg0; // fakematch: address taken keeps arg0 in its home slot
    K_E65C **pa1 = &arg1; // fakematch: address taken keeps arg1 in its home slot
    u8 *pa2 = &arg2; // fakematch: address taken keeps arg2 in its home slot

    if (*pa2 == 0x3B) {
        p = (K_E65C *)((u8 *)*pa0 + 0x28);
        t = (*pa1)->a == p->a;
        if (1) { // fakematch: empty block keeps the first compare in its own basic block
        }
        if (t || (*pa1)->b == p->b) {
            node_destroy(*pa0);
        }
    } else {
        p = (K_E65C *)((u8 *)*pa0 + 0x28);
        node_handle_link_message((s32)*pa1, *pa2, (s32)p, (s32)p + 4, (s32)*pa0);
    }
}

/* was func_151BE6E8 */
void aura_burst_free_effects(u8 *arg0)
{
  u8 *v = arg0 + 0x28; // fakematch: v defined first so IDO keeps it as a separate pointer (not folded into offsets)
  if (*(s32 *)(arg0 + 0x30) != 0) { node_destroy(*(struct102 **)(arg0 + 0x30)); }
  if (*(struct102 **)(v + 0xC)) { node_destroy(*(struct102 **)(v + 0xC)); } // fakematch: pointer-typed test gives one load (s32 test double-loads like line above)
  if (*(struct102 **)(v + 0x10)) { node_destroy(*(struct102 **)(v + 0x10)); }
  if (*(struct102 **)(v + 0x14)) { node_destroy(*(struct102 **)(v + 0x14)); }
}

/* was func_151BE768 */
void aura_burst_retire(struct260 * arg0) {
    aura_burst_free_effects(arg0);
    effect_node_retire(arg0);
}

/* was func_151BE794 */
void aura_burst_delete(struct260 * arg0) {
    aura_burst_free_effects(arg0);
    effect_node_free(arg0);
}

/* was func_151BE7C0 */
s32 aura_particle_flicker_update(u8 *arg0) {
    f32 *s = (f32 *)(arg0 + 0x110);

    s[9] -= g_frame_step_f;
    if (s[9] < 0.0f) {
        s[9] = random_float() * 4.0f;
        s[6] = s[2] + s[4] * random_float();
    }
    *(f32 *)(arg0 + 0x2C) += (s[6] - *(f32 *)(arg0 + 0x2C)) * 0.35f;
    s[10] -= g_frame_step_f;
    if (s[10] < 0.0f) {
        s[10] = random_float() * 9.0f;
        if (random_int() & 1) {
            s[7] = s[3] + s[5] * random_float();
        } else {
            s[7] = s[3] + s[8] * random_float();
        }
    }
    *(f32 *)(arg0 + 0x30) += (s[7] - *(f32 *)(arg0 + 0x30)) * 0.4f;
    s[14] -= g_frame_step_f;
    if (s[14] < 0.0f) {
        s[14] = random_float() * 10.0f;
        s[13] = s[11] + s[12] * random_float();
    }
    s[15] += (s[13] - s[15]) * 0.4f;
    arg0[0x5C] = s[15];
    s[16] += (s[18] - s[16]) * 0.65000004f;
    s[17] += (s[19] - s[17]) * 0.65000004f;
    return 1;
}

s32 beam_quad_build_cam(s32, s32, f32 *, s16);

/* was func_151BEA68 */
s32 aura_particle_draw(struct102 *arg0, s16 arg1) {
    u8 *temp_v0;
    u8 *temp_v0_2;
    f32 sp20[2];

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x110));
    if (((*(u8 *)((u8 *)arg0 + 0x114)) != (*(u8 *)((u8 *)temp_v0 + 0x3B))) || (temp_v0_2 = (u8 *)arg0 + 0x110, ((*(s32 *)((u8 *)temp_v0 + 0)) == 0))) {
        node_destroy(arg0);
        return 0;
    }
    if (!((*(u8 *)((u8 *)temp_v0_2 + 0x58)) & 1)) {
        return 0;
    }
    sp20[0] = (*(f32 *)((u8 *)temp_v0_2 + 0x54)) * (*(f32 *)((u8 *)temp_v0_2 + 0x40));
    sp20[1] = (*(f32 *)((u8 *)temp_v0_2 + 0x54)) * (*(f32 *)((u8 *)temp_v0_2 + 0x44));
    return beam_quad_build_cam(arg0, 0, sp20, arg1);
}

/* was func_151BEB08 */
void follow_particle_handle_message(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    s32 temp_v1;
    temp_v0 = (u8 *)arg0 + 0xB0;
    if (arg2 == 0x2D) {
        if (*(s32 *)(arg1 + 0) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 0);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
        goto dummy_label; dummy_label: ; // fakematch: b + target-copied lw ra
    } else if (arg2 == 0) {
        temp_v1 = *(s32 *)(arg1 + 0);
        if (temp_v1 == *(s32 *)(temp_v0 + 0) || *(u8 *)(temp_v0 + 4) == *(u8 *)(arg1 + 4)) {
            node_destroy(arg0);
        }
    }
}

/* was func_151BEBB4 */
void aura_particle_handle_link_msg(u8 *arg0, s32 arg1, u8 arg2) {
    node_handle_link_message(arg1, arg2, (s32)(arg0 + 0x110), (s32)(arg0 + 0x114), (s32)arg0);
}

/* was func_151BEBF4 */
void aura_particle_unlink(u8 *arg0) {
    u8 *temp_v0 = arg0 + 0x110;

    if (*(s32 *)(arg0 + 0x160) != 0) {
        u8 *temp_v1 = *(u8 **)(temp_v0 + 0x50);

        temp_v1 += 0x28;
        *(s32 *)(temp_v1 + temp_v0[5] * 4 + 8) = 0;
    }
}

/* was func_151BEC24 */
void aura_particle_retire(struct210 * arg0) {
    aura_particle_unlink(arg0);
    effect3d_retire(arg0);
}

/* was func_151BEC50 */
void aura_particle_free(struct210 * arg0) {
    aura_particle_unlink(arg0);
    effect3d_free(arg0);
}

typedef struct { s32 a[4]; } V4_151BEC7C;
extern V4_151BEC7C g_aura_flicker_values; /* was D_800AAB88 */
/* was func_151BEC7C */
s32 aura_emitter_flicker_update(u8 *arg0) {
    u8 *v = arg0 + 0x110;
    V4_151BEC7C sp24;
    f32 f;
    sp24 = g_aura_flicker_values;
    *(s16 *)(arg0 + 0x170) = *(s16 *)(arg0 + 0x170) - g_frame_ticks;
    if (*(s16 *)(arg0 + 0x170) < 0) {
        *(s8 *)(arg0 + 0x18) = sp24.a[random_int() & 3];
        *(s16 *)(arg0 + 0x170) = (random_int() & 7) + 3;
    }
    f = *(f32 *)(v + 0x48);
    *(f32 *)(v + 0x48) += (*(f32 *)(arg0 + 0x174) - f) * 0.65000004f;
    return 1;
}

/* was func_151BED38 */
void aura_emitter_handle_link_msg(u8 *arg0, s32 arg1, u8 arg2) {
    node_handle_link_message(arg1, arg2, (s32)(arg0 + 0x180), (s32)(arg0 + 0x184), (s32)arg0);
}

/* was func_151BED78 */
void aura_emitter_unlink(u8 *arg0) {
    u8 *temp_v0 = arg0 + 0x170;

    if (*(s32 *)(arg0 + 0x178) != 0) {
        u8 *temp_v1 = *(u8 **)(temp_v0 + 8);

        temp_v1 += 0x28;
        *(s32 *)(temp_v1 + temp_v0[0xC] * 4 + 0x10) = 0;
    }
}

/* was func_151BEDA8 */
void aura_emitter_retire(struct210 * arg0) {
    aura_emitter_unlink(arg0);
    effect_free_buffers_retire(arg0);
}

/* was func_151BEDD4 */
void aura_emitter_delete(struct210 * arg0) {
    aura_emitter_unlink(arg0);
    effect_free_buffers_delete(arg0);
}
