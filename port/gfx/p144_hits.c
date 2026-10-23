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

/* P149 DIAGNOSTIC ?p149hits=1 / PORT_P149HITS=1: per-250-retrace call counts of the P145 functions (framebuffer effect
 * pass func_15160310 and its handlers, particle update func_1513095C, its handler func_151A4DEC, death handler
 * func_150C1698, object free func_1516972C). Same --wrap limits as above (calls from other TUs / tables only). */
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
void __real_func_15160310(uint16_t *fb);  void __wrap_func_15160310(uint16_t *fb) { hit149(0); __real_func_15160310(fb); }
void __real_func_151CB6C0(u8 *e, uint16_t *fb); void __wrap_func_151CB6C0(u8 *e, uint16_t *fb) { hit149(1); __real_func_151CB6C0(e, fb); }
void __real_func_150CE960(u8 *e, uint16_t *fb); void __wrap_func_150CE960(u8 *e, uint16_t *fb) { hit149(2); __real_func_150CE960(e, fb); }
void __real_func_150AFC70(s32 a, s32 b);       void __wrap_func_150AFC70(s32 a, s32 b) { hit149(3); __real_func_150AFC70(a, b); }
void __real_func_1513095C(u8 *r);              void __wrap_func_1513095C(u8 *r) { hit149(4); __real_func_1513095C(r); }
s32  __real_func_151A4DEC(u8 *r, f32 *p);      s32  __wrap_func_151A4DEC(u8 *r, f32 *p) { hit149(5); return __real_func_151A4DEC(r, p); }
void __real_func_150C1698(u8 *r);              void __wrap_func_150C1698(u8 *r) { hit149(6); __real_func_150C1698(r); }
void __real_func_1516972C(void *o);            void __wrap_func_1516972C(void *o) { hit149(7); __real_func_1516972C(o); }
