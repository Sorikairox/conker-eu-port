/* P144 DIAGNOSTIC ?p144hits=1 / PORT_P144HITS=1: call counts of C functions converted in P136-P142 (port-b) that
 * still need a runtime check. Linker --wrap, so only calls from OTHER translation units are seen (same-file calls
 * and calls through tables built in the same file are not). Logs "[p144hits] NAME call N frame F" at call counts
 * 1, 2, 4, 8, ... (powers of two), so one line per doubling. Signatures = the NM definitions. */
#include <stdint.h>
#include <stdio.h>
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

void *__real_hud_scope_lens_draw(void *g, s32 size, s32 tex, f32 dx, f32 dy, s32 view);
void *__wrap_hud_scope_lens_draw(void *g, s32 size, s32 tex, f32 dx, f32 dy, s32 view) { /* scope_lens_draw: args logged too */
    static unsigned hits_; hit("hud_scope_lens_draw", &hits_);
    if (port_flag("p144hits") && hits_ <= 48)
        port_log("[p144hits] lens #%u frame %u size %d tex %d d %.2f %.2f view %d\n", hits_, port_frame_count, size, tex, dx, dy, view);
    return __real_hud_scope_lens_draw(g, size, tex, dx, dy, view);
}
WV(star_field_generate, (void), ())                                                                                    /* star_field_generate */
W0(s32, spawn_region_random_point, (u8 *r, f32 *x, f32 *z, f32 *t, f32 *b), (r, x, z, t, b))                                  /* spawn_region_random_point */
W0(s32, sprite_draw_rect, (s32 g, s32 s, s32 so, s32 to, s32 xa), (g, s, so, to, xa))                                 /* sprite_draw_rect */
W0(uint32_t *, image_draw_tiled, (uint32_t *g, void *img, f32 sx, f32 sy, f32 x, f32 y, s32 w, s32 h, s32 fl, s32 so, s32 xa, s32 fr),
   (g, img, sx, sy, x, y, w, h, fl, so, xa, fr))                                                                 /* image_draw_tiled */
W0(s32, world_to_screen, (f32 *p, f32 *s, f32 *oz, f32 *ow, f32 *oi, u8 v), (p, s, oz, ow, oi, v))                  /* world_to_screen */
WV(camera_pivot_follow_update, (void *cam), (cam))                                                                            /* camera_follow_update */
WV(pickup_burst_spawn, (f32 *p), (p))                                                                                 /* pickup_burst_spawn */
W0(s32, life_pickup_spawn, (f32 *p, f32 a, u8 k, u8 fl, u8 sz, s32 a5, s32 a6), (p, a, k, fl, sz, a5, a6))             /* marker_sprite_spawn */
W0(s32, obj_death_resolve, (void *o), (o))                                                                           /* object_death_resolve */
W0(s32, world_object_sound_play, (u8 *o, s32 snd, s32 vol, s16 r0, s16 r1, s32 fl), (o, snd, vol, r0, r1, fl))               /* object_sound_play */
W0(s32, life_pickup_ring_spawn, (f32 yaw, s32 p, s32 a2, u8 a3, s32 c, s32 fl, s32 a6, s32 a7, s32 a8), (yaw, p, a2, a3, c, fl, a6, a7, a8)) /* ring_particle_spawn */
WV(sprite_screen_rect, (s32 s, f32 x, f32 y, f32 w, s32 alt, s32 *vis), (s, x, y, w, alt, vis))                         /* sprite_screen_rect */
W0(s32, vec3_make_basis, (f32 *n, f32 *a, f32 *b), (n, a, b))                                                      /* plane_axes_from_normal */
W0(s32, smoke_wobble_step, (u8 *o, u8 *a), (o, a))                                                                   /* orbit_object_step */
W0(s32, model_node_points_to_world, (u8 *o, u8 *nd, s32 i, f32 **in, f32 **out, s32 n), (o, nd, i, in, out, n))               /* model_node_points_to_world */
WV(world_object_rotate_point, (s32 i, f32 *x, f32 *y, f32 *z), (i, x, y, z))                                                 /* world_object_rotate_point */

/* P149 DIAGNOSTIC ?p149hits=1 / PORT_P149HITS=1: per-250-retrace call counts of the P145 functions (framebuffer effect
 * pass fb_fx_apply_all and its handlers, particle update particle_sprite_update, its handler spark_burst_update, death handler
 * pool_slot_release, object free node_destroy). Same --wrap limits as above (calls from other TUs / tables only). */
static const char *p149_names[] = { "fx_pass_15160310", "lens_151CB6C0", "fx_150CE960", "fx_150AFC70", "particle_1513095C",
                                    "spark_151A4DEC", "pdeath_150C1698", "free_1516972C" };
static unsigned p149_n[8], p149_w = ~0u;
static void hit149(int i) {
    static int f = -1;
    if (f < 0) f = port_flag("p149hits");
    if (!f) return;
    unsigned w = port_frame_count / 250;
    if (w != p149_w) {
        if (p149_w != ~0u) {
            char b[512]; int o = snprintf(b, sizeof b, "[p149hits] retraces %u..%u:", p149_w * 250, p149_w * 250 + 249);
            for (int k = 0; k < 8; k++) if (p149_n[k]) o += snprintf(b + o, sizeof b - o, " %s=%u", p149_names[k], p149_n[k]);
            port_log("%s\n", b);
        }
        p149_w = w; for (int k = 0; k < 8; k++) p149_n[k] = 0;
    }
    p149_n[i]++;
}
void __real_fb_fx_apply_all(uint16_t *fb);  void __wrap_fb_fx_apply_all(uint16_t *fb) { hit149(0); __real_fb_fx_apply_all(fb); }
void __real_fb_lens_warp_draw(u8 *e, uint16_t *fb); void __wrap_fb_lens_warp_draw(u8 *e, uint16_t *fb) { hit149(1); __real_fb_lens_warp_draw(e, fb); }
void __real_fb_zoom_fx_apply(u8 *e, uint16_t *fb); void __wrap_fb_zoom_fx_apply(u8 *e, uint16_t *fb) { hit149(2); __real_fb_zoom_fx_apply(e, fb); }
void __real_fb_fx_gray_callback(s32 a, s32 b);       void __wrap_fb_fx_gray_callback(s32 a, s32 b) { hit149(3); __real_fb_fx_gray_callback(a, b); }
void __real_particle_sprite_update(u8 *r);              void __wrap_particle_sprite_update(u8 *r) { hit149(4); __real_particle_sprite_update(r); }
s32  __real_spark_burst_update(u8 *r, f32 *p);      s32  __wrap_spark_burst_update(u8 *r, f32 *p) { hit149(5); return __real_spark_burst_update(r, p); }
void __real_pool_slot_release(u8 *r);              void __wrap_pool_slot_release(u8 *r) { hit149(6); __real_pool_slot_release(r); }
void __real_node_destroy(void *o);            void __wrap_node_destroy(void *o) { hit149(7); __real_node_destroy(o); }

/* P152 DIAGNOSTIC ?p152hits=1 / PORT_P152HITS=1: per-250-retrace call counts of the P143-P150 (port-b) and P148 (port)
 * frame-path conversions: 3D effect update effect3d_update and its draw effect3d_draw, particle sprite draw
 * particle_draw_sprite, player morph blend player_morph_blend, mtxf_transform_point_w / camera_world_to_screen (projection), water drop
 * water_drop_splash_update, burst spawner emit_particle_burst_req. Same --wrap limits (calls from other TUs / tables in other TUs only). */
static const char *p152_names[] = { "fx3d_1513CFE4", "fx3d_draw_1513DB00", "psprite_1513100C", "morph_1517B270",
                                    "xform_150A7EE0", "w2s_1501A764", "drop_151928C8", "burst_15153BA4" };
static unsigned p152_n[8], p152_w = ~0u;
static void hit152(int i) {
    static int f = -1;
    if (f < 0) f = port_flag("p152hits");
    if (!f) return;
    unsigned w = port_frame_count / 250;
    if (w != p152_w) {
        if (p152_w != ~0u) {
            char b[512]; int o = snprintf(b, sizeof b, "[p152hits] retraces %u..%u:", p152_w * 250, p152_w * 250 + 249);
            for (int k = 0; k < 8; k++) if (p152_n[k]) o += snprintf(b + o, sizeof b - o, " %s=%u", p152_names[k], p152_n[k]);
            port_log("%s\n", b);
        }
        p152_w = w; for (int k = 0; k < 8; k++) p152_n[k] = 0;
    }
    p152_n[i]++;
}
void __real_effect3d_update(u8 *fx); void __wrap_effect3d_update(u8 *fx) { hit152(0); __real_effect3d_update(fx); }
u8 *__real_effect3d_draw(u8 *a, u8 *b, s16 c); u8 *__wrap_effect3d_draw(u8 *a, u8 *b, s16 c) { hit152(1); return __real_effect3d_draw(a, b, c); }
void *__real_particle_draw_sprite(void *g, u8 *p, s16 v); void *__wrap_particle_draw_sprite(void *g, u8 *p, s16 v) { hit152(2); return __real_particle_draw_sprite(g, p, v); }
s32 __real_player_morph_blend(s32 t, s32 f, s32 i); s32 __wrap_player_morph_blend(s32 t, s32 f, s32 i) { hit152(3); return __real_player_morph_blend(t, f, i); }
void __real_mtxf_transform_point_w(f32 (*mf)[4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz, f32 *ow);
void __wrap_mtxf_transform_point_w(f32 (*mf)[4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz, f32 *ow) { hit152(4); __real_mtxf_transform_point_w(mf, x, y, z, ox, oy, oz, ow); }
void __real_camera_world_to_screen(s32 v, f32 x, f32 y, f32 z, f32 *sx, f32 *sy, f32 *sz);
void __wrap_camera_world_to_screen(s32 v, f32 x, f32 y, f32 z, f32 *sx, f32 *sy, f32 *sz) { hit152(5); __real_camera_world_to_screen(v, x, y, z, sx, sy, sz); }
s32 __real_water_drop_splash_update(u8 *a, s32 b); s32 __wrap_water_drop_splash_update(u8 *a, s32 b) { hit152(6); return __real_water_drop_splash_update(a, b); }
void __real_emit_particle_burst_req(u8 *r, s32 t, s32 o, s32 a); void __wrap_emit_particle_burst_req(u8 *r, s32 t, s32 o, s32 a) { hit152(7); __real_emit_particle_burst_req(r, t, o, a); }
