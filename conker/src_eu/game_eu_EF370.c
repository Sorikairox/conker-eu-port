#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* s32 slots as in game_eu_EF6D0: the caller masks the tag itself (andi), IDO would skip the mask for a u8 parameter */
s32 spawn_ring_emit(f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, s32, s32);

/* spawn_ring_kind2_small: P238: emits 25 points of spawn handler kind 2 (g_emit_point_spawn_fns) on a radius-80 ring around
 * (x, y, z), starting at byte angle 0 and stepping by 3, with arg8 / arg9 / argA 0 and the byte `tag` as argB
 * (spawn_ring_emit, spawn_ring_emit). Its only caller (bouncing_bomb_update, asm) passes 0xFF and ignores v0; the asm leaves
 * spawn_ring_emit's v0 in place, so it is returned. */
/* was func_150C1B60 */
s32 spawn_ring_kind2_small(f32 x, f32 y, f32 z, s32 tag) {
    return spawn_ring_emit(x, y, z, 80.0f, 0, 3, 0x19, 2, 0, 0.0f, 0, tag & 0xFF);
}

f32 angle_byte_cos(u8);
u8 *trail_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                  s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);

/* emit_point_debris: g_emit_point_spawn_fns spawn handler (`s32 (s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0,
 * s32 a, s32 angle0, f32 r, s32 arg8, f32 arg9, s32 argA, s32 argB)`, as the game_eu_EF6D0 emitters): spawns one
 * kind-5 particle (trail_spawn) at (x, y, z) flying out along the byte angle a with a random pitch of -63..-51
 * (rand % 13 - 63) and speed 25.5..42.9 (17.4 * rand + 25.5): velocity (v sin(p) sin(a - 0x40), -v sin(p - 0x40),
 * v sin(p) sin(a)) (angle_byte_cos = byte-angle sine); sprite 0x5A..0x99, tint 5..13, motion speed 24.7..44.9, scale
 * 0.4..0.6, flags 0x28, kind 0xA; owner byte argB. The asm leaves the spawn block's -1 / owner words and the motion
 * block's floor / timers unset (stack garbage), and so does this C. Always returns 1 (go on). */
/* was func_150C1BC0 */
s32 emit_point_debris(s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a, s32 angle0, f32 r, s32 arg8,
                  f32 arg9, s32 argA, s32 argB) {
    struct {
        s32 render[3];      /* spC8: words 0, 1, 0x160600 */
        s32 mode[4];        /* 3, 0x10, 0x80, 0x20 */
        u8 b0;              /* 0 */
        u8 b1;              /* 9 */
    } rb;
    struct {
        f32 speed;          /* spE8 */
        f32 vel[3];
        f32 scale;
        f32 floor;          /* not set */
        u8 flags;
        u8 kind;
        u8 full;
        u8 alpha;
        s16 t0;             /* not set */
        s16 t1;             /* not set */
    } mb;
    struct {
        f32 pos[3];         /* sp108 */
        s16 sprite;
        s16 model;
        s32 count;
        s8 minus1;          /* not set */
        u8 tint;
        s32 owner;          /* not set */
    } sb;
    s32 n;
    s16 pitch;
    f32 sp, cp, sa, ca, v, h;

    rb.render[0] = 0;
    rb.render[1] = 1;
    rb.render[2] = 0x160600;
    rb.mode[0] = 3;
    rb.mode[1] = 0x10;
    rb.mode[2] = 0x80;
    rb.mode[3] = 0x20;
    rb.b0 = 0;
    rb.b1 = 9;
    sb.count = 1;
    sb.model = 1;
    mb.kind = 0xA;
    mb.full = 0xFF;
    mb.flags = 0x28;
    mb.alpha = 0xFF;
    sb.pos[0] = x;
    sb.pos[1] = y;
    sb.pos[2] = z;
    n = 1;
    do {
        pitch = (u32) random_int() % 13U - 0x3F;
        sp = angle_byte_cos(pitch & 0xFF);
        cp = angle_byte_cos((pitch - 0x40) & 0xFF);
        sa = angle_byte_cos(a & 0xFF);
        ca = angle_byte_cos((a - 0x40) & 0xFF);
        v = random_float() * 17.4f + 25.5f;
        sb.tint = (u32) random_int() % 9U + 5;
        sb.sprite = (random_int() & 0x3F) + 0x5A;
        mb.speed = random_float() * 20.2f + 24.7f;
        mb.scale = random_float() * 0.2f + 0.4f;
        h = v * sp;
        mb.vel[0] = h * ca;
        mb.vel[1] = -v * cp;
        mb.vel[2] = h * sa;
        trail_spawn((u8 *) &sb, (s32) &mb, 0, 1, 5, 0, 0, 0, 0, 0, 0, (u8 *) &rb, 0, argB & 0xFF, 0);
        n--;
    } while (n != 0);
    return 1;
}

/* was func_150C1E78 */
s32 trail_alpha_by_life_update(u8 *arg0)
{
  s32 t;
  s32 v;
  u8 *q;
  q = *((u8 **) (arg0 + 0x98));
  v = *((s16 *) (arg0 + 0x1C));
  t = (v * 8) & 0xFFFFFFFFFFFFFFFF; // fakematch: 64-bit mask keeps t in a temp register
  v = t;
  if (t >= 0x100)
  {
    v = 0xFF;
  }
  q[0x1B] = v;
  if ((v & 0xFF) < 0)
  {
    return 0;
  }
  return 1;
}
