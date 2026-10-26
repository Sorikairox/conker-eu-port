/* P49: ?p49walk=N runtime check of P47's walk handler obj_state_walk (state 1), link-time wrap.
 * Logs the player record before / after each call (first N calls, then every `p49every` calls, default 32):
 * position, velocities, yaw (+0x76 / +0x7A), target speed (+0x44), the pad (D_800CC6A4), the handler's flag
 * word D_800CC6DC, and which asm stubs the handler reached (port_stub_trace_hook), with call counts. */
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern void (*port_stub_trace_hook)(const char *name);
extern unsigned D_800CC6A4, D_800CC6DC, D_800CC288, D_800CC6A0;
extern unsigned short D_800CC69E; /* u16 in game memory: read with vbe_ld16 */
extern unsigned char D_800BE616;

#define NSTUB 48
static const char *st_name[NSTUB];
static unsigned st_n[NSTUB], st_tot[NSTUB], st_count;
static void p49_hook(const char *name) {
    unsigned i;
    for (i = 0; i < st_count; i++)
        if (st_name[i] == name || !strcmp(st_name[i], name)) { st_n[i]++; st_tot[i]++; return; }
    if (st_count < NSTUB) { st_name[st_count] = name; st_n[st_count] = 1; st_tot[st_count] = 1; st_count++; }
}

#define F(o) (*(const float *)(r + (o)))
#define U8(o) vbe_ld8(r + (o))
#define U16(o) vbe_ld16(r + (o))
static void p49_line(const char *tag, const unsigned char *r) {
    const unsigned char *u = (const unsigned char *)(uintptr_t)*(const unsigned *)(r + 0x31C);
    const unsigned char *pad = (const unsigned char *)(uintptr_t)D_800CC6A4;
    port_log("[p49] %s frame %u: state %d pos %g %g %g yv %g grav %g xz %g +28 %g +44 %g +54 %g yaw76 %04X 7A %04X 78 %04X "
             "floor118 %g dis_run %02X stun %02X water %02X 81 %02X 83 %02X AA %02X 110 %02X F8 %08X | pad %04X %d,%d "
             "CC288 %04X CC6DC %03X CC69E %04X CC6A0 %04X hp %02X BE616 %02X | 31C %08X 78 %02X 84 %02X 4E %02X 52 %02X 197 %02X 198 %02X 11A %02X 12 %d\n",
             tag, port_frame_count, *(const int *)r, F(0x14), F(0x18), F(0x1C), F(0x20), F(0x24), F(0x3C), F(0x28), F(0x44),
             F(0x54), U16(0x76), U16(0x7A), U16(0x78), F(0x118), U8(0x89), U8(0x104), U8(0xAD), U8(0x81), U8(0x83), U8(0xAA),
             U8(0x110), *(const unsigned *)(r + 0xF8), pad ? vbe_ld16(pad) : 0, pad ? (signed char)vbe_ld8(pad + 2) : 0,
             pad ? (signed char)vbe_ld8(pad + 3) : 0, D_800CC288 & 0xFFFF, D_800CC6DC, vbe_ld16(&D_800CC69E), D_800CC6A0 & 0xFFFF, U8(0x1CA), vbe_ld8(&D_800BE616),
             (unsigned)(uintptr_t)u, u ? vbe_ld8(u + 0x78) : 0, u ? vbe_ld8(u + 0x84) : 0, u ? vbe_ld8(u + 0x4E) : 0,
             u ? vbe_ld8(u + 0x52) : 0, u ? vbe_ld8(u + 0x197) : 0, u ? vbe_ld8(u + 0x198) : 0, u ? vbe_ld8(u + 0x11A) : 0, u ? (short)vbe_ld16(u + 0x12) : 0);
}

void __real_obj_state_walk(void *arg0);
void __wrap_obj_state_walk(void *arg0) {
    static int flag = -1, every = -1;
    static unsigned calls;
    const unsigned char *r = (const unsigned char *)arg0;
    float x0, z0;
    int log;
    unsigned i;
    if (flag < 0) { flag = port_flag("p49walk"); every = port_flag("p49every"); if (every <= 0) every = 32; }
    if (!flag) { __real_obj_state_walk(arg0); return; }
    calls++;
    log = calls <= (unsigned)flag || calls % (unsigned)every == 0;
    x0 = F(0x14); z0 = F(0x1C);
    { /* P55 ?p55drop=Y (diagnostic): at walk-handler call 8 put record 0 at height Y (y and +0x1CC, the fall start) so
       * the C gravity / floor query / landing can be watched on a fall onto the level 0x21 floor */
      static int drop = -1;
      if (drop < 0) drop = port_flag("p55drop");
      if (drop && calls == 8) {
          *(float *)(r + 0x18) = (float)drop; *(float *)(r + 0x1CC) = (float)drop;
          port_log("[p55] drop: record 0 y set to %d at frame %u\n", drop, port_frame_count);
      } }
    if (log) p49_line("pre ", r);
    for (i = 0; i < st_count; i++) st_n[i] = 0;
    { void (*prev_hook)(const char *) = port_stub_trace_hook; /* P88: restore, don't clear (?p88watch) */
    port_stub_trace_hook = p49_hook;
    __real_obj_state_walk(arg0);
    port_stub_trace_hook = prev_hook; }
    if (log) {
        char buf[600]; int n = 0;
        p49_line("post", r);
        for (i = 0; i < st_count && n < 560; i++)
            if (st_n[i]) n += snprintf(buf + n, sizeof buf - n, " %s x%u", st_name[i], st_n[i]);
        buf[n] = 0;
        port_log("[p49] call %u: moved %g,%g; stubs inside:%s\n", calls, F(0x14) - x0, F(0x1C) - z0, n ? buf : " none");
    }
    if (calls % 512 == 0) {
        char buf[900]; int n = 0;
        for (i = 0; i < st_count && n < 860; i++) n += snprintf(buf + n, sizeof buf - n, " %s %u", st_name[i], st_tot[i]);
        buf[n] = 0;
        port_log("[p49] after %u calls, stub totals inside the walk handler:%s\n", calls, buf);
    }
}

/* P52: with ?p49walk set, also
 *  - wrap obj_apply_gravity (P50 C gravity; the call from the walk handler): y / y_velocity / +0x28 before and after,
 *    gravity +0x24 and the frame time g_obj_time_step[0] (an f32 array, P50), first p49walk calls then every p49every;
 *  - wrap objects_update_all (P48 C object update loop, called from game_45B80.c): record 0's model fields after it
 *    (+0x1D4 model instance, +0x2D0 animation state, id +4, D_800D19A0[id] loaded model, D_800C52F0[id]). */
extern float g_obj_time_step[]; /* was D_800D1550 */
extern unsigned D_800D19A0[];
extern unsigned short D_800C52F0[];
extern unsigned char g_objects[]; /* was D_800CC2D0 */
void __real_obj_apply_gravity(void *rec);
void __wrap_obj_apply_gravity(void *rec) {
    static int flag = -1, every = -1;
    static unsigned calls;
    const unsigned char *r = (const unsigned char *)rec;
    float y0 = F(0x18), v0 = F(0x20), h0 = F(0x28);
    if (flag < 0) { flag = port_flag("p49walk"); every = port_flag("p49every"); if (every <= 0) every = 32; }
    __real_obj_apply_gravity(rec);
    calls++;
    if (flag && (calls <= (unsigned)flag || calls % (unsigned)every == 0))
        port_log("[p52] gravity call %u frame %u: dt D_800D1550[0] %g (bits %08X) grav %g | y %g -> %g yv %g -> %g "
                 "+28 %g -> %g | +180 %g floor118 %g\n", calls, port_frame_count, g_obj_time_step[0],
                 *(const unsigned *)g_obj_time_step, F(0x24), y0, F(0x18), v0, F(0x20), h0, F(0x28), F(0x180), F(0x118));
}
void __real_objects_update_all(void);
/* P116: objects_update_all follows each record's +0x65 parent chain (1-based slot) with no bound; a cycle hangs the game
 * thread (seen after the scene-1 setup spawns of obj_spawn_attached). If one is found, the 25 records are logged (first 4
 * times) and the frame's object update is skipped instead of hanging. */
static int p116_cycle(void) {
    static unsigned logged;
    int i, k, bad = -1;
    for (i = 0; i < 25 && bad < 0; i++) {
        const unsigned char *q = (const unsigned char *)g_objects + i * 0x32C;
        if (*(const int *)q == 0 || vbe_ld8(q + 0x65) == 0) continue;
        for (k = 0; k < 26 && vbe_ld8(q + 0x65) != 0; k++) {
            unsigned p = vbe_ld8(q + 0x65);
            if (p > 25) { k = 26; break; }
            q = (const unsigned char *)g_objects + (p - 1) * 0x32C;
        }
        if (k >= 26) bad = i;
    }
    if (bad >= 0 && logged++ < 4) {
        port_log("[p116] +0x65 parent cycle from slot %d, frame %u; records:\n", bad, port_frame_count);
        for (i = 0; i < 25; i++) {
            const unsigned char *q = (const unsigned char *)g_objects + i * 0x32C;
            if (*(const int *)q == 0 && vbe_ld8(q + 0x65) == 0) continue;
            port_log("[p116]   slot %2d %08X state %d kind %02X +65 %02X +3B %02X +5C %d +123 %d +1D4 %08X\n", i,
                     (unsigned)(uintptr_t)q, *(const int *)q, vbe_ld8(q + 4), vbe_ld8(q + 0x65), vbe_ld8(q + 0x3B),
                     *(const int *)(q + 0x5C), vbe_ld8(q + 0x123), *(const unsigned *)(q + 0x1D4));
        }
    }
    return bad >= 0;
}
void __wrap_objects_update_all(void) {
    static int flag = -1;
    static unsigned calls;
    const unsigned char *r = g_objects;
    if (p116_cycle()) return;
    __real_objects_update_all();
    if (flag < 0) { flag = port_flag("p49walk"); }
    calls++;
    if (flag && (calls <= 3 || (calls & 255) == 0)) {
        unsigned id = U8(4);
        port_log("[p52] objects_update_all call %u frame %u: rec0 state %d id %02X +65 %02X +1D4 %08X +2D0 %08X "
                 "D_800D19A0[id] %08X D_800C52F0[id] %u +74 %02X\n", calls, port_frame_count, *(const int *)r, id,
                 U8(0x65), *(const unsigned *)(r + 0x1D4), *(const unsigned *)(r + 0x2D0), D_800D19A0[id],
                 vbe_ld16(&D_800C52F0[id]), U8(0x74));
    }
}

/* P52 diagnostic ?p52void=1 (P55: now off by default and only a diagnostic; the floor query is real C since P53/P54):
 * forces "no floor" (-10000) into arg 3 (spC4) and arg 4 (+0x118) after the real query.
 * P55 ?p49walk: for record 0 (argB == g_objects) logs the query's inputs / outputs and an independent float floor
 * height: every level triangle (D_800DC26C, D_800DBE4C of them, vertices s16 at the offsets) whose x/z projection
 * holds (x, z), with the plane y there; the highest such y that is <= y + 15 (step), and the count of hits. */
extern unsigned D_800DC26C, D_800DBE4C;
extern unsigned char D_800DBE62;
extern int D_800D3720[];
static int p55_ref(float x, float z, float ylim, float *best, float *top, int *ntri) {
    const unsigned *vo = (const unsigned *)(uintptr_t)D_800DC26C;
    unsigned i, n = D_800DBE4C;
    int hits = 0, bi = -1;
    *best = -10000.0f; *top = -10000.0f;
    if (!vo || n > 20000) { *ntri = 0; return -1; }
    *ntri = (int)n;
    for (i = 0; i < n; i++) {
        float v[3][3], d, l0, l1, l2, y;
        int k;
        for (k = 0; k < 3; k++) {
            const unsigned char *q = (const unsigned char *)(uintptr_t)vo[i * 3 + k];
            v[k][0] = (short)vbe_ld16(q); v[k][1] = (short)vbe_ld16(q + 2); v[k][2] = (short)vbe_ld16(q + 4);
        }
        d = (v[1][2] - v[2][2]) * (v[0][0] - v[2][0]) + (v[2][0] - v[1][0]) * (v[0][2] - v[2][2]);
        if (d == 0.0f) continue;
        l0 = ((v[1][2] - v[2][2]) * (x - v[2][0]) + (v[2][0] - v[1][0]) * (z - v[2][2])) / d;
        l1 = ((v[2][2] - v[0][2]) * (x - v[2][0]) + (v[0][0] - v[2][0]) * (z - v[2][2])) / d;
        l2 = 1.0f - l0 - l1;
        if (l0 < -1e-4f || l1 < -1e-4f || l2 < -1e-4f) continue;
        y = l0 * v[0][1] + l1 * v[1][1] + l2 * v[2][1];
        hits++;
        if (y > *top) *top = y;
        if (y <= ylim && y > *best) { *best = y; bi = (int)i; }
    }
    return hits ? bi : -2;
}
static float r_best, r_top, r_y; static int r_bi = -3, r_ntri, r_n3f50 = -1, r_calls, r_on;
static int r_n48c0 = -1, r_n5480 = -1;
int __real_floor_collect_world_obj_tris(int x, int z, int cnt, int ids);
int __wrap_floor_collect_world_obj_tris(int x, int z, int cnt, int ids) {
    int n = __real_floor_collect_world_obj_tris(x, z, cnt, ids);
    if (r_on) r_n48c0 = n;
    return n;
}
int __real_floor_collect_record_tris(int x, int z);
int __wrap_floor_collect_record_tris(int x, int z) {
    int n = __real_floor_collect_record_tris(x, z);
    if (r_on) r_n5480 = n;
    return n;
}
static float r_minx, r_maxx, r_minz, r_maxz, r_miny, r_maxy;
int __real_floor_collect_level_tris(int x, int z);
int __wrap_floor_collect_level_tris(int x, int z) {
    int n = __real_floor_collect_level_tris(x, z);
    if (r_on) {
        float b, t; int nt, bi;
        r_calls++;
        bi = p55_ref((float)x, (float)z, r_y + 15.0f, &b, &t, &nt);
        if (nt > 0) { r_n3f50 = n; r_bi = bi; r_best = b; r_top = t; r_ntri = nt; } /* keep the area with triangles */
        if (r_minx > r_maxx) { /* level extent, once */
            const unsigned *vo = (const unsigned *)(uintptr_t)D_800DC26C;
            unsigned i;
            for (i = 0; vo && i < D_800DBE4C * 3; i++) {
                const unsigned char *q = (const unsigned char *)(uintptr_t)vo[i];
                float vx = (short)vbe_ld16(q), vy = (short)vbe_ld16(q + 2), vz = (short)vbe_ld16(q + 4);
                if (vx < r_minx) r_minx = vx; if (vx > r_maxx) r_maxx = vx;
                if (vz < r_minz) r_minz = vz; if (vz > r_maxz) r_maxz = vz;
                if (vy < r_miny) r_miny = vy; if (vy > r_maxy) r_maxy = vy;
            }
            port_log("[p55] level area tables: %u triangles, x %g..%g y %g..%g z %g..%g, D_800DBE62 %u\n", D_800DBE4C,
                     r_minx, r_maxx, r_miny, r_maxy, r_minz, r_maxz, vbe_ld8(&D_800DBE62));
        }
    }
    return n;
}

/* P55 ?p55synth=1: one-shot in-wasm check of the C floor query on sloped synthetic geometry (level 0x21 is flat, y 0).
 * At the first record-0 floor query: only area 0 enabled (D_800894C0), and after func_150A4ED4(0) the area-0 tables
 * D_800DC26C / D_800DC270 / D_800DBE4C / D_800DBE62 (0: all-triangles path) / D_800DBE5C point at PC buffers written
 * through vbe (s16 vertices and bounds), then collision_find_floor_no_fallback runs over an integer grid with y = prevY = 1000 (so the
 * highest floor below wins) and record 0 = NULL. Its height is compared with a float barycentric reference. All
 * globals are restored afterwards. */
extern unsigned char D_800894C0[];
void __real_collision_find_floor_no_fallback(int a0, int a1, int a2, int a3, int a4, int a5, float a6, float a7, float a8, float a9,
                          unsigned short aA, int aB, int aC, int aD, int aE);
extern unsigned D_800DC270, D_800DBE5C;
static int synth_on;
static short syn_v[8][3] = {
    {-200, 0, -200}, {200, 80, -200}, {200, 120, 200}, {-200, 40, 200},   /* sloped quad: tris 0-1-2, 0-2-3 */
    {-50, 300, -50}, {60, 330, -40}, {0, 270, 90}, {0, 0, 0}};           /* raised slanted shelf: 4-5-6 */
static int syn_t[3][3] = {{0, 1, 2}, {0, 2, 3}, {4, 5, 6}};
static unsigned syn_vbuf[8 * 2 + 2], syn_ofs[3 * 3], syn_bnd[3 * 2], syn_flags[4];
static void synth_tables(void) {
    int i, k;
    for (i = 0; i < 7; i++)
        for (k = 0; k < 3; k++) vbe_st16((char *)syn_vbuf + i * 6 + k * 2, (unsigned short)syn_v[i][k]);
    for (i = 0; i < 3; i++) {
        int a = syn_t[i][0], b = syn_t[i][1], c = syn_t[i][2], t;
        float ux = syn_v[b][0] - syn_v[a][0], uz = syn_v[b][2] - syn_v[a][2];
        float wx = syn_v[c][0] - syn_v[a][0], wz = syn_v[c][2] - syn_v[a][2];
        short mnx = 32767, mnz = 32767, mxx = -32768, mxz = -32768;
        if (uz * wx - ux * wz < 0) { t = b; b = c; c = t; } /* collision_candidate_is_floor: cross(b - a, c - a).y >= 0 = floor */
        syn_ofs[i * 3 + 0] = (unsigned)(uintptr_t)((char *)syn_vbuf + a * 6);
        syn_ofs[i * 3 + 1] = (unsigned)(uintptr_t)((char *)syn_vbuf + b * 6);
        syn_ofs[i * 3 + 2] = (unsigned)(uintptr_t)((char *)syn_vbuf + c * 6);
        for (k = 0; k < 3; k++) {
            short x = syn_v[syn_t[i][k]][0], z = syn_v[syn_t[i][k]][2];
            if (x < mnx) mnx = x; if (x > mxx) mxx = x; if (z < mnz) mnz = z; if (z > mxz) mxz = z;
        }
        vbe_st16((char *)syn_bnd + i * 8 + 0, (unsigned short)mnx); vbe_st16((char *)syn_bnd + i * 8 + 2, (unsigned short)mnz);
        vbe_st16((char *)syn_bnd + i * 8 + 4, (unsigned short)mxx); vbe_st16((char *)syn_bnd + i * 8 + 6, (unsigned short)mxz);
    }
}
static float syn_ref(float x, float z, int *inside) {
    int i, k; float best = -10000.0f; *inside = 0;
    for (i = 0; i < 3; i++) {
        float v[3][3], d, l0, l1, l2;
        for (k = 0; k < 3; k++) { v[k][0] = syn_v[syn_t[i][k]][0]; v[k][1] = syn_v[syn_t[i][k]][1]; v[k][2] = syn_v[syn_t[i][k]][2]; }
        d = (v[1][2] - v[2][2]) * (v[0][0] - v[2][0]) + (v[2][0] - v[1][0]) * (v[0][2] - v[2][2]);
        l0 = ((v[1][2] - v[2][2]) * (x - v[2][0]) + (v[2][0] - v[1][0]) * (z - v[2][2])) / d;
        l1 = ((v[2][2] - v[0][2]) * (x - v[2][0]) + (v[0][0] - v[2][0]) * (z - v[2][2])) / d;
        l2 = 1.0f - l0 - l1;
        if (l0 < 0 || l1 < 0 || l2 < 0) continue;
        (*inside)++;
        { float y = l0 * v[0][1] + l1 * v[1][1] + l2 * v[2][1]; if (y > best) best = y; }
    }
    return best;
}
void __real_func_150A4ED4(int area);
void __wrap_func_150A4ED4(int area) {
    __real_func_150A4ED4(area);
    if (synth_on && area == 0) {
        D_800DC26C = (unsigned)(uintptr_t)syn_ofs; D_800DC270 = (unsigned)(uintptr_t)syn_bnd; D_800DBE4C = 3;
        vbe_st8(&D_800DBE62, 0); D_800DBE5C = (unsigned)(uintptr_t)syn_flags;
    }
}
static void p55_synth(void) {
    unsigned s26c = D_800DC26C, s270 = D_800DC270, s24c = D_800DBE4C, s25c = D_800DBE5C, s62 = vbe_ld8(&D_800DBE62);
    unsigned char en[4]; int i, x, z, n = 0, nin = 0, miss = 0, extra = 0, bad = 0, edge = 0; float maxd = 0, sumd = 0;
    char ex[400]; int exn = 0;
    unsigned tri, vtx[5], flags; short area[2]; float h, ceil;
    for (i = 0; i < 4; i++) { en[i] = vbe_ld8(&D_800894C0[i]); vbe_st8(&D_800894C0[i], i == 0); }
    synth_tables();
    synth_on = 1;
    ex[0] = 0;
    for (z = -197; z <= 197; z += 6)
        for (x = -197; x <= 197; x += 6) {
            int inside; float r = syn_ref((float)x, (float)z, &inside), d;
            __real_collision_find_floor_no_fallback((int)(uintptr_t)&tri, (int)(uintptr_t)vtx, (int)(uintptr_t)&h, (int)(uintptr_t)&ceil,
                                 (int)(uintptr_t)&flags, (int)(uintptr_t)area, (float)x, 1000.0f, (float)z, 1000.0f, 0, 0,
                                 0, 0, 0);
            n++;
            if (inside) nin++;
            if (r == -10000.0f && h == -10000.0f) continue;
            if (r == -10000.0f || h == -10000.0f) {
                /* within 3 units of an edge the game's +-1 / +-2 widening may disagree with the exact test */
                int in2; syn_ref((float)x + 3, (float)z, &in2); int in3; syn_ref((float)x - 3, (float)z, &in3);
                int in4; syn_ref((float)x, (float)z + 3, &in4); int in5; syn_ref((float)x, (float)z - 3, &in5);
                if ((in2 != inside) || (in3 != inside) || (in4 != inside) || (in5 != inside)) { edge++; continue; }
                if (r == -10000.0f) extra++; else miss++;
                if (exn < 360) exn += snprintf(ex + exn, sizeof ex - exn, " (%d,%d ref %g got %g)", x, z, r, h);
                continue;
            }
            {   /* height mismatch next to a triangle edge (overlapping layers) */
                int a1, a2, a3, a4; syn_ref((float)x + 2, (float)z, &a1); syn_ref((float)x - 2, (float)z, &a2);
                syn_ref((float)x, (float)z + 2, &a3); syn_ref((float)x, (float)z - 2, &a4);
                if ((a1 != inside || a2 != inside || a3 != inside || a4 != inside) && h != r) { edge++; continue; }
            }
            d = h - r; if (d < 0) d = -d;
            sumd += d;
            if (d > maxd) maxd = d;
            if (d > 1.5f) { bad++; if (exn < 360) exn += snprintf(ex + exn, sizeof ex - exn, " (%d,%d ref %g got %g)", x, z, r, h); }
        }
    synth_on = 0;
    for (i = 0; i < 4; i++) vbe_st8(&D_800894C0[i], en[i]);
    D_800DC26C = s26c; D_800DC270 = s270; D_800DBE4C = s24c; D_800DBE5C = s25c; vbe_st8(&D_800DBE62, s62);
    port_log("[p55] synth floor: %d grid points, %d inside a triangle; height |C - float| max %g mean %g; >1.5: %d; "
             "missed %d, extra %d, edge-ambiguous %d;%s %s\n", n, nin, maxd, nin ? sumd / nin : 0, bad, miss, extra, edge,
             ex, (bad || miss || extra) ? "FAIL" : "PASS");
}
/* P101 DIAGNOSTIC ?p101col=N: on the first N floor -> void changes of record 0's floor query: the 4 collision areas
 * (enable D_800894C0, triangle count D_800DBE18, x / y / z extent of the table D_800DC208), the level DLs
 * g_level_part_dls[0..3], and the world objects (g_world_obj_count records of 0xA0 at D_800DBEF4: DL +0x1C, flags +0x4F, first tri
 * +0x58, count +0x56, +0x10..+0x14). */
extern int D_800DC208[], D_800DBE18[], g_world_obj_count, g_level_part_dls[]; /* was D_800B0E00; was D_800DC320 */
extern unsigned char *D_800DBEF4;
extern unsigned char D_800E0B94;
extern unsigned D_8009018C[];
static void p101_col(float h, float x, float y, float z) {
    static int f = -1, n, last = 2;
    int isfloor = h != -10000.0f, a, i, was = last;
    if (f < 0) f = port_flag("p101col");
    last = isfloor;
    if (!f || isfloor || was != 1 || n >= f) return;
    n++;
    port_log("[p101] game mode D_800E0B94 %u, handlers D_8009018C[0..9] %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X\n",
             vbe_ld8(&D_800E0B94), D_8009018C[0], D_8009018C[1], D_8009018C[2], D_8009018C[3], D_8009018C[4],
             D_8009018C[5], D_8009018C[6], D_8009018C[7], D_8009018C[8], D_8009018C[9]);
    port_log("[p101] void at frame %u: x %g y %g z %g; enable %u %u %u %u; level DLs %08X %08X %08X %08X; objects %d\n",
             port_frame_count, x, y, z, vbe_ld8(&D_800894C0[0]), vbe_ld8(&D_800894C0[1]), vbe_ld8(&D_800894C0[2]),
             vbe_ld8(&D_800894C0[3]), g_level_part_dls[0], g_level_part_dls[1], g_level_part_dls[2], g_level_part_dls[3], g_world_obj_count);
    for (a = 0; a < 4; a++) {
        const unsigned *vo = (const unsigned *)(uintptr_t)D_800DC208[a];
        float mn[3] = {1e9f, 1e9f, 1e9f}, mx[3] = {-1e9f, -1e9f, -1e9f};
        int k, cnt = D_800DBE18[a];
        for (i = 0; vo && cnt > 0 && cnt < 40000 && i < cnt * 3; i++)
            for (k = 0; k < 3; k++) {
                float v = (short)vbe_ld16((const unsigned char *)(uintptr_t)vo[i] + 2 * k);
                if (v < mn[k]) mn[k] = v;
                if (v > mx[k]) mx[k] = v;
            }
        port_log("[p101]   area %d: table %08X, %d tris, x %g..%g y %g..%g z %g..%g\n", a, (unsigned)(uintptr_t)vo, cnt,
                 mn[0], mx[0], mn[1], mx[1], mn[2], mx[2]);
    }
    for (i = 0; D_800DBEF4 && i < g_world_obj_count && i < 64; i++) {
        const unsigned char *o = D_800DBEF4 + i * 0xA0;
        port_log("[p101]   obj %d: DL %08X +4F %02X tri %u +%u | +10 %d %d %d\n", i, *(const unsigned *)(o + 0x1C),
                 vbe_ld8(o + 0x4F), vbe_ld16(o + 0x58), vbe_ld16(o + 0x56), (short)vbe_ld16(o + 0x10),
                 (short)vbe_ld16(o + 0x12), (short)vbe_ld16(o + 0x14));
    }
}
/* P245 DIAGNOSTIC ?p245col=F: once, on the first p205_obj_hook call (needs ?p205obj) at retrace >= F (the floor-query wrap is not reached for Conker on 0x29), dump every triangle of collision areas
 * 0 and 1 (D_800DC208 vertex-pointer table, 3 pointers to s16 x y z per triangle, count D_800DBE18) as
 * "[p245tri] area idx x0 y0 z0 x1 y1 z1 x2 y2 z2 flags" (flags = D_800DBE5C entry when the area is the current one,
 * D_800DC26C, else -1), plus the caller's position. For offline path planning (level 0x29 river). */
void p245_coldump(float x, float y, float z) {
    static int f = -2, done;
    int a, i, k, cnt;
    if (f == -2) f = port_flag("p245col");
    if (f <= 0 || done || port_frame_count < (unsigned)f) return;
    done = 1;
    port_log("[p245col] frame %u pos %g %g %g; area counts %d %d %d %d, current table %08X\n", port_frame_count, x, y, z,
             D_800DBE18[0], D_800DBE18[1], D_800DBE18[2], D_800DBE18[3], (unsigned)D_800DC26C);
    for (a = 0; a < 2; a++) {
        const unsigned *vo = (const unsigned *)(uintptr_t)D_800DC208[a];
        cnt = D_800DBE18[a];
        if (!vo || cnt <= 0 || cnt > 40000) continue;
        for (i = 0; i < cnt; i++) {
            short v[9]; long fl = -1;
            for (k = 0; k < 9; k++) v[k] = (short)vbe_ld16((const unsigned char *)(uintptr_t)vo[i * 3 + k / 3] + 2 * (k % 3));
            if ((uintptr_t)D_800DC26C == (uintptr_t)vo && D_800DBE5C) fl = (long)((const unsigned *)(uintptr_t)D_800DBE5C)[i];
            port_log("[p245tri] %d %d %d %d %d %d %d %d %d %d %d %lX\n", a, i, v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], fl);
        }
    }
    port_log("[p245col] done\n");
}
/* P248 DIAGNOSTIC ?p248mesh=F (needs ?p205obj; called from p205_obj_hook): once at retrace >= F, dump the world objects
 * (g_world_obj_count records of 0xA0 at D_800DBEF4): angle +0x0, yaw +0x4, pos +0x10..+0x14, scale +0x2C..+0x34, update
 * +0x38 (compared with gate_swing_update scenery_gate_swing_update), +0x4F, tri +0x58 / count +0x56, +0x5A pos, +0x6E busy,
 * +0x6F flags, +0x73 state; and every triangle of collision areas 2 and 3 ("[p248tri] area idx x0 .. z2").
 * Then every retrace: a "[p248gate]" line whenever a world object's +0x0 angle (rounded) or +0x73 changes, with
 * player 0's position and ctx +0x6B (gate push state) and the pad buttons. */
extern void scenery_gate_swing_update(unsigned char *);
void p248_mesh(void) {
    static int f = -2, done, n0;
    static int lastang[256], last73[256], last6b = -1;
    int i, k, a, n = g_world_obj_count;
    const unsigned char *pl = g_objects, *q;
    if (f == -2) f = port_flag("p248mesh");
    if (f <= 0 || port_frame_count < (unsigned)f || !D_800DBEF4) return;
    if (n > 256) n = 256;
    if (!done) {
        done = 1; n0 = n;
        port_log("[p248mesh] frame %u: %d world objects, gate fn %08X, area counts %d %d %d %d\n", port_frame_count, n,
                 (unsigned)(uintptr_t)scenery_gate_swing_update, D_800DBE18[0], D_800DBE18[1], D_800DBE18[2], D_800DBE18[3]);
        for (i = 0; i < n; i++) {
            const unsigned char *o = D_800DBEF4 + i * 0xA0;
            port_log("[p248mesh] %d ang %.1f yaw %.1f pos %d %d %d scale %.2f %.2f %.2f upd %08X%s 4F %02X tri %u +%u pos5A %d %d %d busy %u fl %02X 73 %02X DL %08X\n",
                     i, *(const float *)o, *(const float *)(o + 4), (short)vbe_ld16(o + 0x10), (short)vbe_ld16(o + 0x12),
                     (short)vbe_ld16(o + 0x14), *(const float *)(o + 0x2C), *(const float *)(o + 0x30),
                     *(const float *)(o + 0x34), *(const unsigned *)(o + 0x38),
                     *(const unsigned *)(o + 0x38) == (unsigned)(uintptr_t)scenery_gate_swing_update ? " GATE" : "",
                     vbe_ld8(o + 0x4F), vbe_ld16(o + 0x58), vbe_ld16(o + 0x56), (short)vbe_ld16(o + 0x5A),
                     (short)vbe_ld16(o + 0x5C), (short)vbe_ld16(o + 0x5E), vbe_ld8(o + 0x6E), vbe_ld8(o + 0x6F),
                     vbe_ld8(o + 0x73), *(const unsigned *)(o + 0x1C));
            lastang[i] = (int)*(const float *)o; last73[i] = vbe_ld8(o + 0x73);
        }
        for (a = 2; a < 4; a++) {
            const unsigned *vo = (const unsigned *)(uintptr_t)D_800DC208[a];
            int cnt = D_800DBE18[a];
            if (!vo || cnt <= 0 || cnt > 40000) continue;
            for (i = 0; i < cnt; i++) {
                short v[9];
                for (k = 0; k < 9; k++) v[k] = (short)vbe_ld16((const unsigned char *)(uintptr_t)vo[i * 3 + k / 3] + 2 * (k % 3));
                port_log("[p248tri] %d %d %d %d %d %d %d %d %d %d %d\n", a, i, v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);
            }
        }
        {   /* the level's event zones (as P212's [p212zone], which fires before the level loads in EEPROM boots) */
            extern unsigned char *D_800D34B8; extern unsigned D_800D3094;
            unsigned kz;
            for (kz = 0; kz < D_800D3094 && kz < 256 && D_800D34B8; kz++) {
                const unsigned char *z = D_800D34B8 + kz * 0x34;
                port_log("[p248zone] %02X pos %d %d %d u6 %d f10 %.1f b14 %02X %02X %02X %02X\n", kz, (short)vbe_ld16(z),
                         (short)vbe_ld16(z + 2), (short)vbe_ld16(z + 4), (short)vbe_ld16(z + 6), *(const float *)(z + 0x10),
                         vbe_ld8(z + 0x14), vbe_ld8(z + 0x15), vbe_ld8(z + 0x16), vbe_ld8(z + 0x17));
            }
        }
        port_log("[p248mesh] done\n");
    }
    q = *(const unsigned char *const *)(pl + 0x31C);
    for (i = 0; i < n && i < n0; i++) {
        const unsigned char *o = D_800DBEF4 + i * 0xA0;
        int ang = (int)*(const float *)o, s = vbe_ld8(o + 0x73), b6 = q ? vbe_ld8(q + 0x6B) : -1;
        if (ang != lastang[i] || s != last73[i] || (*(const unsigned *)(o + 0x38) == (unsigned)(uintptr_t)scenery_gate_swing_update && b6 != last6b)) {
            port_log("[p248gate] frame %u obj %d ang %d (was %d) 73 %02X (was %02X) 7C %08X | player %.1f %.1f %.1f ctx6B %d\n",
                     port_frame_count, i, ang, lastang[i], s, last73[i], *(const unsigned *)(o + 0x7C),
                     *(const float *)(pl + 0x14), *(const float *)(pl + 0x18), *(const float *)(pl + 0x1C), b6);
            lastang[i] = ang; last73[i] = s;
        }
    }
    if (q) last6b = vbe_ld8(q + 0x6B);
    {   /* P261 DIAGNOSTIC ?p261lever=1: every 10 retraces while player 0 is within 600 (x/z) of a gate's handle point,
         * log the handle point as gate_swing_update (scenery_gate_swing_update) computes it on levels 1 / 0x29 (offset -13 76 354
         * scaled, rotated by +0x0 then yaw +0x4, plus pos +0x10), the player's feet y, head y (+0x18 + s16 +0xE6), the
         * squared distance (head) vs reach 10000*sz^2, feet+40 < handle y, and the busy bytes the gate skips on
         * (+0x65, +0x104, ctx +0x17, +0x27, +0x6B >= 4). */
        static int lf = -2, zlev = -1;
        if (lf == -2) lf = port_flag("p261lever");
        {   /* P261: the event zones again whenever the level (g_level_id) changes, 60 retraces after */
            extern unsigned char *D_800D34B8; extern unsigned D_800D3094; extern int g_level_id;
            static unsigned zf;
            if (lf > 0 && g_level_id != zlev) { zlev = g_level_id; zf = port_frame_count + 60; }
            if (lf > 0 && zf && port_frame_count >= zf) {
                unsigned kz;
                zf = 0;
                for (kz = 0; kz < D_800D3094 && kz < 256 && D_800D34B8; kz++) {
                    const unsigned char *z = D_800D34B8 + kz * 0x34;
                    port_log("[p261zone] level %02X %02X pos %d %d %d u6 %d f10 %.1f b14 %02X %02X %02X %02X\n", zlev, kz,
                             (short)vbe_ld16(z), (short)vbe_ld16(z + 2), (short)vbe_ld16(z + 4), (short)vbe_ld16(z + 6),
                             *(const float *)(z + 0x10), vbe_ld8(z + 0x14), vbe_ld8(z + 0x15), vbe_ld8(z + 0x16), vbe_ld8(z + 0x17));
                }
            }
        }
        static unsigned lc; if (lf > 0 && (lc++ % 4) == 0 && q) {
            for (i = 0; i < n && i < n0; i++) {
                const unsigned char *o = D_800DBEF4 + i * 0xA0;
                float a, b, sx, sy, sz, hx, hy, hz, t0, t1, t2, px, py, pz, hd, dx, dy, dz;
                if (*(const unsigned *)(o + 0x38) != (unsigned)(uintptr_t)scenery_gate_swing_update) continue;
                sx = *(const float *)(o + 0x2C); sy = *(const float *)(o + 0x30); sz = *(const float *)(o + 0x34);
                a = *(const float *)o * 0.017453292f; b = *(const float *)(o + 4) * 0.017453292f;
                t0 = -13.f * sx; t1 = 76.f * sy * cosf(a) - 354.f * sz * sinf(a); t2 = 76.f * sy * sinf(a) + 354.f * sz * cosf(a);
                hx = t2 * sinf(b) + t0 * cosf(b) + (short)vbe_ld16(o + 0x10);
                hy = t1 + (short)vbe_ld16(o + 0x12);
                hz = t2 * cosf(b) - t0 * sinf(b) + (short)vbe_ld16(o + 0x14);
                px = *(const float *)(pl + 0x14); py = *(const float *)(pl + 0x18); pz = *(const float *)(pl + 0x1C);
                if ((px - hx) * (px - hx) + (pz - hz) * (pz - hz) > 600.f * 600.f) continue;
                hd = py + (short)vbe_ld16(pl + 0xE6);
                dx = px - hx; dy = hd - hy; dz = pz - hz;
                port_log("[p261lever] frame %u obj %d handle %.0f %.0f %.0f | player %.1f %.1f %.1f head %.1f d2 %.0f (< %.0f) "
                         "feet+40<hy %d | 65 %u 104 %u c17 %u c27 %u c6B %u 73 %02X ang %.1f\n",
                         port_frame_count, i, hx, hy, hz, px, py, pz, hd, dx * dx + dy * dy + dz * dz, 10000.f * sz * sz,
                         py + 40.f < hy, vbe_ld8(pl + 0x65), vbe_ld8(pl + 0x104), vbe_ld8(q + 0x17), vbe_ld8(q + 0x27),
                         vbe_ld8(q + 0x6B), vbe_ld8(o + 0x73), *(const float *)o);
            }
        }
    }
}
void __real_collision_find_floor_no_fallback(int a0, int a1, int a2, int a3, int a4, int a5, float a6, float a7, float a8, float a9,
                          unsigned short aA, int aB, int aC, int aD, int aE);
void __wrap_collision_find_floor_no_fallback(int a0, int a1, int a2, int a3, int a4, int a5, float a6, float a7, float a8, float a9,
                          unsigned short aA, int aB, int aC, int aD, int aE) {
    static int flag = -1, walk = -1, every = -1;
    static unsigned calls;
    static int lastfloor = 2;
    if (flag < 0) { flag = port_flag("p52void"); walk = port_flag("p49walk"); every = port_flag("p49every"); if (every <= 0) every = 32; }
    if (r_minx == 0 && r_maxx == 0) { r_minx = 1e9f; r_maxx = -1e9f; r_minz = 1e9f; r_maxz = -1e9f; r_miny = 1e9f; r_maxy = -1e9f; }
    r_on = walk && aB == (int)(uintptr_t)g_objects; r_y = a7; r_calls = 0; r_bi = -3; r_n3f50 = -1; r_n48c0 = -1; r_n5480 = -1; r_ntri = 0; r_best = r_top = -10000.0f;
    __real_collision_find_floor_no_fallback(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE);
    r_on = 0;
    if (flag) {
        if (a2) *(float *)(uintptr_t)a2 = -10000.0f;
        if (a3) *(float *)(uintptr_t)a3 = -10000.0f;
    }
    if (walk && aB == (int)(uintptr_t)g_objects) {
        static int synth = -1;
        if (synth < 0) { synth = port_flag("p55synth"); if (synth) p55_synth(); }
    }
    if (walk && aB == (int)(uintptr_t)g_objects) {
        float best = r_best, top = r_top, h = a2 ? *(float *)(uintptr_t)a2 : 0, f118 = a3 ? *(float *)(uintptr_t)a3 : 0;
        int ntri = r_ntri, bi = r_bi, isfloor = h != -10000.0f;
        calls++;
        if (calls <= (unsigned)walk || calls % (unsigned)every == 0 || isfloor != lastfloor)
            port_log("[p55] floor call %u frame %u: in x %g y %g z %g prevY(a9) %g | out spC4 %g +118 %g tri %08X "
                     "flags %08X area %d | n 3F50 %d (x%d) 48C0 %d 5480 %d | ref best %g (tri %d) top %g, %d tris, all-tri path %d | ref-out %g%s\n",
                     calls, port_frame_count, a6, a7, a8, a9, h, f118, a0 ? *(unsigned *)(uintptr_t)a0 : 0,
                     a4 ? *(unsigned *)(uintptr_t)a4 : 0, a5 ? (short)vbe_ld16((void *)(uintptr_t)a5) : -1, r_n3f50, r_calls, r_n48c0, r_n5480, best, bi, top, ntri,
                     vbe_ld8(&D_800DBE62) == 0, best - h, isfloor != lastfloor ? " (floor/void change)" : "");
        lastfloor = isfloor;
    }
    if (aB == (int)(uintptr_t)g_objects) p101_col(a2 ? *(float *)(uintptr_t)a2 : 0, a6, a7, a8);
}

/* P55 ?p49walk: landing obj_ctrl_floor_contact (P54 C, called by the walk handler with +0x180): y / vy / +0x28 / +0x180 before and
 * after, and the record state. */
void __real_obj_ctrl_floor_contact(void *rec, float a1);
void __wrap_obj_ctrl_floor_contact(void *rec, float a1) {
    static int flag = -1, every = -1;
    static unsigned calls;
    const unsigned char *r = (const unsigned char *)rec;
    float y0 = F(0x18), v0 = F(0x20), h0 = F(0x28);
    int s0 = *(const int *)r;
    if (flag < 0) { flag = port_flag("p49walk"); every = port_flag("p49every"); if (every <= 0) every = 32; }
    __real_obj_ctrl_floor_contact(rec, a1);
    calls++;
    if (flag && (calls <= (unsigned)flag || calls % (unsigned)every == 0 || v0 != F(0x20) || s0 != *(const int *)r))
        port_log("[p55] landing call %u frame %u: arg1 %g | state %d -> %d y %g -> %g yv %g -> %g +28 %g -> %g +180 %g\n",
                 calls, port_frame_count, a1, s0, *(const int *)r, y0, F(0x18), v0, F(0x20), h0, F(0x28), F(0x180));
}

/* P101 DIAGNOSTIC ?p101mus=1: at each call of the level-start music function level_start_music (game_2D4B0.c, still an
 * asm stub = does nothing; its m2c draft starts the level songs from the level header D_800B0DF0 +0x2C..+0x39 through
 * music_play_song): the level g_level_id, the header bytes +0x2C..+0x39, and the level model count D_800B1248. */
extern unsigned char *D_800B0DF0;
extern int g_level_id, D_800B1248; /* was D_800BE9F0 */
int port_p110_inmus;
void __real_level_start_music(void);
void __wrap_level_start_music(void) {
    static int f = -1;
    if (f < 0) f = port_flag("p101mus");
    if (f) {
        const unsigned char *h = D_800B0DF0;
        char b[64]; int i, o = 0;
        for (i = 0x2C; h && i < 0x3A; i++) o += snprintf(b + o, sizeof b - o, "%02X%s", vbe_ld8(h + i), (i & 3) == 3 ? " " : "");
        port_log("[p101] level_start_music (level music start, asm stub) frame %u: level %X header %08X +2C: %s| models %d\n",
                 port_frame_count, g_level_id, (unsigned)(uintptr_t)h, h ? b : "-", D_800B1248);
    }
    port_p110_inmus = 1; /* P110: music_play_song / DE1C calls from inside are logged by p61_checks.c */
    __real_level_start_music();
    port_p110_inmus = 0;
}
/* P261 DIAGNOSTIC (always on, logs only on a bad key): --wrap of anim_events_run (game_981E0, anim event keys). Before
 * the real call, walks the keys the real code would dispatch (time <= arg1, < 900) and logs any key byte (+7) whose
 * D_8008679C handler word is not a small table index, with the record and the key list. The real function runs. */
extern float __real_anim_events_run(unsigned char *a0, float a1, int a2);
extern unsigned char D_8008679C[];
float __wrap_anim_events_run(unsigned char *a0, float a1, int a2) {
    static int nlog;
    const unsigned char *keys = (const unsigned char *)(uintptr_t)*(const unsigned *)(a0 + 0x1C4);
    if (keys && vbe_ld8(a0 + 5) != 4 && nlog < 20) {
        unsigned idx = vbe_ld8(a0 + 0x138), k;
        if (a1 < *(const float *)(a0 + 0xB4)) idx = 0;
        for (k = idx; k < idx + 16; k++) {
            const unsigned char *e = keys + k * 0xC;
            float t = *(const float *)e;
            unsigned key = vbe_ld8(e + 7), fn;
            if (!(t <= a1)) break;
            if (t >= 900.f) continue;
            fn = *(const unsigned *)(D_8008679C + key * 4);
            if (key && (fn == 0 || fn > 0x10000)) {
                nlog++;
                port_log("[p261key] frame %u rec %p id %02X key %u (#%u t %.1f now %.1f) handler word %08X | keys %p idx %u b4 %.1f 2D0 %08X\n",
                         port_frame_count, (void *)a0, vbe_ld8(a0 + 4), key, k, t, a1, fn, (const void *)keys, idx,
                         *(const float *)(a0 + 0xB4), *(const unsigned *)(a0 + 0x2D0));
            }
        }
    }
    return __real_anim_events_run(a0, a1, a2);
}
/* P261 (port-side, not a diagnostic): EU 0x1506D8AC is a separate 2-instruction function (jr ra; nop) that the split
 * glued to the end of objev_throw_object's asm (game_981E0). It is entry 16 of the anim-key handler table D_8008679C
 * (dispatched by anim_events_run). Without a definition the table word stayed the N64 address and call_indirect trapped
 * ("table index is out of bounds") when the level-0x2E mushroom played its hit animation. port/tools/n64mem.py lists it
 * in VM_NATIVES so the relocation maps the word here. Proper fix: split it in game_981E0 (port). */
void func_1506D8AC(void) {}
