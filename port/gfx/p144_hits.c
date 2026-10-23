/* P144 DIAGNOSTIC ?p144hits=1 / PORT_P144HITS=1: call counts of C functions converted in P136-P142 (port-b) that
 * still need a runtime check. Linker --wrap, so only calls from OTHER translation units are seen (same-file calls
 * and calls through tables built in the same file are not). Logs "[p144hits] NAME call N frame F" at call counts
 * 1, 2, 4, 8, ... (powers of two), so one line per doubling. Signatures = the NM definitions. */
#include <stdint.h>
typedef float f32; typedef int32_t s32; typedef uint8_t u8; typedef int16_t s16;
int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;

static void hit(const char *name, unsigned *n) {
    static int f = -1;
    if (f < 0) f = port_flag("p144hits");
    if (!f) return;
    ++*n;
    if ((*n & (*n - 1)) == 0) port_log("[p144hits] %s call %u frame %u\n", name, *n, port_frame_count);
}
#define W0(ret, fn, params, args) ret __real_##fn params; ret __wrap_##fn params { static unsigned hits_; hit(#fn, &hits_); return __real_##fn args; }
#define WV(fn, params, args) void __real_##fn params; void __wrap_##fn params { static unsigned hits_; hit(#fn, &hits_); __real_##fn args; }

void *__real_func_1518010C(void *g, s32 size, s32 tex, f32 dx, f32 dy, s32 view);
void *__wrap_func_1518010C(void *g, s32 size, s32 tex, f32 dx, f32 dy, s32 view) { /* scope_lens_draw: args logged too */
    static unsigned hits_; hit("func_1518010C", &hits_);
    if (port_flag("p144hits") && hits_ <= 48)
        port_log("[p144hits] lens #%u frame %u size %d tex %d d %.2f %.2f view %d\n", hits_, port_frame_count, size, tex, dx, dy, view);
    return __real_func_1518010C(g, size, tex, dx, dy, view);
}
WV(func_15111DD8, (void), ())                                                                                    /* star_field_generate */
W0(s32, func_151432BC, (u8 *r, f32 *x, f32 *z, f32 *t, f32 *b), (r, x, z, t, b))                                  /* spawn_region_random_point */
W0(s32, func_15096144, (s32 g, s32 s, s32 so, s32 to, s32 xa), (g, s, so, to, xa))                                 /* sprite_draw_rect */
W0(uint32_t *, func_150966AC, (uint32_t *g, void *img, f32 sx, f32 sy, f32 x, f32 y, s32 w, s32 h, s32 fl, s32 so, s32 xa, s32 fr),
   (g, img, sx, sy, x, y, w, h, fl, so, xa, fr))                                                                 /* image_draw_tiled */
W0(s32, func_15144CEC, (f32 *p, f32 *s, f32 *oz, f32 *ow, f32 *oi, u8 v), (p, s, oz, ow, oi, v))                  /* world_to_screen */
WV(func_15129EA4, (void *cam), (cam))                                                                            /* camera_follow_update */
WV(func_151BF678, (f32 *p), (p))                                                                                 /* pickup_burst_spawn */
W0(s32, func_151BEE00, (f32 *p, f32 a, u8 k, u8 fl, u8 sz, s32 a5, s32 a6), (p, a, k, fl, sz, a5, a6))             /* marker_sprite_spawn */
W0(s32, func_15053430, (void *o), (o))                                                                           /* object_death_resolve */
W0(s32, func_151152A4, (u8 *o, s32 snd, s32 vol, s16 r0, s16 r1, s32 fl), (o, snd, vol, r0, r1, fl))               /* object_sound_play */
W0(s32, func_151BF490, (f32 yaw, s32 p, s32 a2, u8 a3, s32 c, s32 fl, s32 a6, s32 a7, s32 a8), (yaw, p, a2, a3, c, fl, a6, a7, a8)) /* ring_particle_spawn */
WV(func_15095F18, (s32 s, f32 x, f32 y, f32 w, s32 alt, s32 *vis), (s, x, y, w, alt, vis))                         /* sprite_screen_rect */
W0(s32, func_15146078, (f32 *n, f32 *a, f32 *b), (n, a, b))                                                      /* plane_axes_from_normal */
W0(s32, func_15159C2C, (u8 *o, u8 *a), (o, a))                                                                   /* orbit_object_step */
W0(s32, func_1514654C, (u8 *o, u8 *nd, s32 i, f32 **in, f32 **out, s32 n), (o, nd, i, in, out, n))               /* model_node_points_to_world */
WV(func_151148C8, (s32 i, f32 *x, f32 *y, f32 *z), (i, x, y, z))                                                 /* world_object_rotate_point */
