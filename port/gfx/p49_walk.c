/* P49: ?p49walk=N runtime check of P47's walk handler func_1504CB98 (state 1), link-time wrap.
 * Logs the player record before / after each call (first N calls, then every `p49every` calls, default 32):
 * position, velocities, yaw (+0x76 / +0x7A), target speed (+0x44), the pad (D_800CC6A4), the handler's flag
 * word D_800CC6DC, and which asm stubs the handler reached (port_stub_trace_hook), with call counts. */
#include <stdint.h>
#include <string.h>
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

void __real_func_1504CB98(void *arg0);
void __wrap_func_1504CB98(void *arg0) {
    static int flag = -1, every = -1;
    static unsigned calls;
    const unsigned char *r = (const unsigned char *)arg0;
    float x0, z0;
    int log;
    unsigned i;
    if (flag < 0) { flag = port_flag("p49walk"); every = port_flag("p49every"); if (every <= 0) every = 32; }
    if (!flag) { __real_func_1504CB98(arg0); return; }
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
    __real_func_1504CB98(arg0);
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
 *  - wrap func_1505A770 (P50 C gravity; the call from the walk handler): y / y_velocity / +0x28 before and after,
 *    gravity +0x24 and the frame time D_800D1550[0] (an f32 array, P50), first p49walk calls then every p49every;
 *  - wrap func_1502C1D4 (P48 C object update loop, called from game_45B80.c): record 0's model fields after it
 *    (+0x1D4 model instance, +0x2D0 animation state, id +4, D_800D19A0[id] loaded model, D_800C52F0[id]). */
extern float D_800D1550[];
extern unsigned D_800D19A0[];
extern unsigned short D_800C52F0[];
extern unsigned char D_800CC2D0[];
void __real_func_1505A770(void *rec);
void __wrap_func_1505A770(void *rec) {
    static int flag = -1, every = -1;
    static unsigned calls;
    const unsigned char *r = (const unsigned char *)rec;
    float y0 = F(0x18), v0 = F(0x20), h0 = F(0x28);
    if (flag < 0) { flag = port_flag("p49walk"); every = port_flag("p49every"); if (every <= 0) every = 32; }
    __real_func_1505A770(rec);
    calls++;
    if (flag && (calls <= (unsigned)flag || calls % (unsigned)every == 0))
        port_log("[p52] gravity call %u frame %u: dt D_800D1550[0] %g (bits %08X) grav %g | y %g -> %g yv %g -> %g "
                 "+28 %g -> %g | +180 %g floor118 %g\n", calls, port_frame_count, D_800D1550[0],
                 *(const unsigned *)D_800D1550, F(0x24), y0, F(0x18), v0, F(0x20), h0, F(0x28), F(0x180), F(0x118));
}
void __real_func_1502C1D4(void);
void __wrap_func_1502C1D4(void) {
    static int flag = -1;
    static unsigned calls;
    const unsigned char *r = D_800CC2D0;
    __real_func_1502C1D4();
    if (flag < 0) { flag = port_flag("p49walk"); }
    calls++;
    if (flag && (calls <= 3 || (calls & 255) == 0)) {
        unsigned id = U8(4);
        port_log("[p52] func_1502C1D4 call %u frame %u: rec0 state %d id %02X +65 %02X +1D4 %08X +2D0 %08X "
                 "D_800D19A0[id] %08X D_800C52F0[id] %u +74 %02X\n", calls, port_frame_count, *(const int *)r, id,
                 U8(0x65), *(const unsigned *)(r + 0x1D4), *(const unsigned *)(r + 0x2D0), D_800D19A0[id],
                 vbe_ld16(&D_800C52F0[id]), U8(0x74));
    }
}

/* P52 diagnostic ?p52void=1 (P55: now off by default and only a diagnostic; the floor query is real C since P53/P54):
 * forces "no floor" (-10000) into arg 3 (spC4) and arg 4 (+0x118) after the real query.
 * P55 ?p49walk: for record 0 (argB == D_800CC2D0) logs the query's inputs / outputs and an independent float floor
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
int __real_func_150A48C0(int x, int z, int cnt, int ids);
int __wrap_func_150A48C0(int x, int z, int cnt, int ids) {
    int n = __real_func_150A48C0(x, z, cnt, ids);
    if (r_on) r_n48c0 = n;
    return n;
}
int __real_func_150A5480(int x, int z);
int __wrap_func_150A5480(int x, int z) {
    int n = __real_func_150A5480(x, z);
    if (r_on) r_n5480 = n;
    return n;
}
static float r_minx, r_maxx, r_minz, r_maxz, r_miny, r_maxy;
int __real_func_150A3F50(int x, int z);
int __wrap_func_150A3F50(int x, int z) {
    int n = __real_func_150A3F50(x, z);
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
 * through vbe (s16 vertices and bounds), then func_1510EE3C runs over an integer grid with y = prevY = 1000 (so the
 * highest floor below wins) and record 0 = NULL. Its height is compared with a float barycentric reference. All
 * globals are restored afterwards. */
extern unsigned char D_800894C0[];
void __real_func_1510EE3C(int a0, int a1, int a2, int a3, int a4, int a5, float a6, float a7, float a8, float a9,
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
        if (uz * wx - ux * wz < 0) { t = b; b = c; c = t; } /* func_1510EBF0: cross(b - a, c - a).y >= 0 = floor */
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
            __real_func_1510EE3C((int)(uintptr_t)&tri, (int)(uintptr_t)vtx, (int)(uintptr_t)&h, (int)(uintptr_t)&ceil,
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
 * D_800B0E00[0..3], and the world objects (D_800DC320 records of 0xA0 at D_800DBEF4: DL +0x1C, flags +0x4F, first tri
 * +0x58, count +0x56, +0x10..+0x14). */
extern int D_800DC208[], D_800DBE18[], D_800DC320, D_800B0E00[];
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
             vbe_ld8(&D_800894C0[3]), D_800B0E00[0], D_800B0E00[1], D_800B0E00[2], D_800B0E00[3], D_800DC320);
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
    for (i = 0; D_800DBEF4 && i < D_800DC320 && i < 64; i++) {
        const unsigned char *o = D_800DBEF4 + i * 0xA0;
        port_log("[p101]   obj %d: DL %08X +4F %02X tri %u +%u | +10 %d %d %d\n", i, *(const unsigned *)(o + 0x1C),
                 vbe_ld8(o + 0x4F), vbe_ld16(o + 0x58), vbe_ld16(o + 0x56), (short)vbe_ld16(o + 0x10),
                 (short)vbe_ld16(o + 0x12), (short)vbe_ld16(o + 0x14));
    }
}
void __real_func_1510EE3C(int a0, int a1, int a2, int a3, int a4, int a5, float a6, float a7, float a8, float a9,
                          unsigned short aA, int aB, int aC, int aD, int aE);
void __wrap_func_1510EE3C(int a0, int a1, int a2, int a3, int a4, int a5, float a6, float a7, float a8, float a9,
                          unsigned short aA, int aB, int aC, int aD, int aE) {
    static int flag = -1, walk = -1, every = -1;
    static unsigned calls;
    static int lastfloor = 2;
    if (flag < 0) { flag = port_flag("p52void"); walk = port_flag("p49walk"); every = port_flag("p49every"); if (every <= 0) every = 32; }
    if (r_minx == 0 && r_maxx == 0) { r_minx = 1e9f; r_maxx = -1e9f; r_minz = 1e9f; r_maxz = -1e9f; r_miny = 1e9f; r_maxy = -1e9f; }
    r_on = walk && aB == (int)(uintptr_t)D_800CC2D0; r_y = a7; r_calls = 0; r_bi = -3; r_n3f50 = -1; r_n48c0 = -1; r_n5480 = -1; r_ntri = 0; r_best = r_top = -10000.0f;
    __real_func_1510EE3C(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE);
    r_on = 0;
    if (flag) {
        if (a2) *(float *)(uintptr_t)a2 = -10000.0f;
        if (a3) *(float *)(uintptr_t)a3 = -10000.0f;
    }
    if (walk && aB == (int)(uintptr_t)D_800CC2D0) {
        static int synth = -1;
        if (synth < 0) { synth = port_flag("p55synth"); if (synth) p55_synth(); }
    }
    if (walk && aB == (int)(uintptr_t)D_800CC2D0) {
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
    if (aB == (int)(uintptr_t)D_800CC2D0) p101_col(a2 ? *(float *)(uintptr_t)a2 : 0, a6, a7, a8);
}

/* P55 ?p49walk: landing func_1505A9AC (P54 C, called by the walk handler with +0x180): y / vy / +0x28 / +0x180 before and
 * after, and the record state. */
void __real_func_1505A9AC(void *rec, float a1);
void __wrap_func_1505A9AC(void *rec, float a1) {
    static int flag = -1, every = -1;
    static unsigned calls;
    const unsigned char *r = (const unsigned char *)rec;
    float y0 = F(0x18), v0 = F(0x20), h0 = F(0x28);
    int s0 = *(const int *)r;
    if (flag < 0) { flag = port_flag("p49walk"); every = port_flag("p49every"); if (every <= 0) every = 32; }
    __real_func_1505A9AC(rec, a1);
    calls++;
    if (flag && (calls <= (unsigned)flag || calls % (unsigned)every == 0 || v0 != F(0x20) || s0 != *(const int *)r))
        port_log("[p55] landing call %u frame %u: arg1 %g | state %d -> %d y %g -> %g yv %g -> %g +28 %g -> %g +180 %g\n",
                 calls, port_frame_count, a1, s0, *(const int *)r, y0, F(0x18), v0, F(0x20), h0, F(0x28), F(0x180));
}

/* P101 DIAGNOSTIC ?p101mus=1: at each call of the level-start music function func_150000B0 (game_2D4B0.c, still an
 * asm stub = does nothing; its m2c draft starts the level songs from the level header D_800B0DF0 +0x2C..+0x39 through
 * func_1000D96C): the level D_800BE9F0, the header bytes +0x2C..+0x39, and the level model count D_800B1248. */
extern unsigned char *D_800B0DF0;
extern int D_800BE9F0, D_800B1248;
int port_p110_inmus;
void __real_func_150000B0(void);
void __wrap_func_150000B0(void) {
    static int f = -1;
    if (f < 0) f = port_flag("p101mus");
    if (f) {
        const unsigned char *h = D_800B0DF0;
        char b[64]; int i, o = 0;
        for (i = 0x2C; h && i < 0x3A; i++) o += snprintf(b + o, sizeof b - o, "%02X%s", vbe_ld8(h + i), (i & 3) == 3 ? " " : "");
        port_log("[p101] func_150000B0 (level music start, asm stub) frame %u: level %X header %08X +2C: %s| models %d\n",
                 port_frame_count, D_800BE9F0, (unsigned)(uintptr_t)h, h ? b : "-", D_800B1248);
    }
    port_p110_inmus = 1; /* P110: func_1000D96C / DE1C calls from inside are logged by p61_checks.c */
    __real_func_150000B0();
    port_p110_inmus = 0;
}
