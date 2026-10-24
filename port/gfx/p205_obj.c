/* P205 DIAGNOSTIC ?p205obj=F: from retrace F, every 250 retraces (called from p81_checks.c's look hook, i.e. once per
 * frame of Conker's look callback), dump the character / object records D_800CC2D0[26] (struct127, 0x32C bytes) that
 * are in use: index, interaction_state (+0x00), id (+0x04), unique_id (+0x3B), position (+0x14), +0xAD in_water, and
 * the current player record index D_800C3E78. Used to find NPCs (the level 0x29 scarecrow) and steer a pad route. */
#include <stdint.h>
#include <stdlib.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern unsigned char D_800CC2D0[];
extern unsigned char D_800C3E78_p205[] __asm__("D_800C3E78");

#define REC 0x32C
static float F(const unsigned char *r, int o) { return *(const float *)(r + o); }

static int p205_player;   /* D_800C3E78 as seen in Conker's look callback (elsewhere it names other records) */
void p205_obj_hook(void) {
    static int f = -1;
    static unsigned last = ~0u;
    int i;
    p205_player = vbe_ld8(D_800C3E78_p205);
    if (f < 0) f = port_flag("p205obj");
    if (f <= 0 || port_frame_count < (unsigned)f) return;
    if (last != ~0u && port_frame_count - last < 250) return;
    last = port_frame_count;
    port_log("[p205obj] frame %u player %d\n", port_frame_count, vbe_ld8(D_800C3E78_p205));
    for (i = 0; i < 26; i++) {
        const unsigned char *r = D_800CC2D0 + i * REC;
        unsigned st = *(const unsigned *)r;
        int id = vbe_ld8(r + 4), uid = vbe_ld8(r + 0x3B);
        float x = F(r, 0x14), y = F(r, 0x18), z = F(r, 0x1C);
        if (!st && !id && !uid && x == 0.f && y == 0.f && z == 0.f) continue;
        port_log("[p205obj]   rec %2d st %08X id %02X uid %02X pos %.1f %.1f %.1f water %d\n", i, st, id, uid, x, y, z,
                 vbe_ld8(r + 0xAD));
    }
}

/* P205 TEST ?p205goto=F:R:BTN:X1:Z1_X2:Z2_... (node: PORT_P205GOTO): pad autopilot for test routes. From retrace F
 * on, the stick of pad 0 (after ?padf) is replaced by one that steers the player record (D_800CC2D0[D_800C3E78 as
 * read in the look callback; at PIF time D_800C3E78 names other records])
 * towards the waypoints in turn (x / z, reached within R units). The stick-to-world angle depends on the camera, so it
 * is learned from the motion: offset = heading moved - stick angle, smoothed. After the last waypoint the stick is
 * released and BTN (hex, e.g. 8000 = A, 4000 = B) is tapped every 60 retraces (8 retraces down) for 30 taps;
 * BTN 0 = no taps. A step written tBTN:N (e.g. t8000:40) instead of X:Z taps BTN N times there, then goes on;
 * X:Z:R gives one waypoint its own radius.
 * Logs [p205go] every 50 retraces and on each waypoint. */
#include <math.h>
#include <emscripten.h>
EM_JS(int, __port_p205_goto_char, (int i), {
    var v = null;
    if (typeof location !== 'undefined') { var m = /[?&]p205goto=([^&]*)/.exec(location.search); if (m) v = decodeURIComponent(m[1]); }
    else if (typeof process !== 'undefined' && process.env && process.env.PORT_P205GOTO !== undefined) v = process.env.PORT_P205GOTO;
    return v === null || i >= v.length ? 0 : v.charCodeAt(i);
});
#define GO_MAX 32
extern float D_800DD600[2];   /* camera yaw of view 0: sin, cos (func_15167310) */
static int go_n = -1, go_i, go_btn;
static unsigned go_f, go_arrive, go_stuck_f;
static float go_r, go_x[GO_MAX], go_z[GO_MAX];
static int go_tap[GO_MAX], go_ntap[GO_MAX];   /* step k is "tap go_tap[k] go_ntap[k] times" when go_ntap[k] > 0 */
static float go_rr[GO_MAX];                    /* per-waypoint radius (X:Z:R), else go_r */
static unsigned go_tap_f;
static float go_px, go_pz, go_base, go_th, go_sx0, go_sz0;
static int go_sgn = -1, go_have, go_have_init;
static float wrapa(float a) { while (a > 3.14159265f) a -= 6.2831853f; while (a < -3.14159265f) a += 6.2831853f; return a; }
static void go_parse(void) {
    char s[1024]; int n = 0, c; char *p, *e;
    while (n < (int)sizeof s - 1 && (c = __port_p205_goto_char(n)) != 0) s[n++] = (char)c;
    s[n] = 0; go_n = 0;
    if (!n) return;
    p = s;
    go_f = (unsigned)strtoul(p, &e, 10); if (*e != ':') return; p = e + 1;
    go_r = strtof(p, &e); if (*e != ':') return; p = e + 1;
    go_btn = (int)strtol(p, &e, 16); if (*e != ':') return; p = e + 1;
    while (*p && go_n < GO_MAX) {
        if (*p == 't') {   /* tap step tBTN:N */
            go_tap[go_n] = (int)strtol(p + 1, &e, 16); if (*e != ':') break; p = e + 1;
            go_ntap[go_n] = (int)strtol(p, &e, 10); go_n++; p = e;
            if (*p == '_') { p++; continue; } else break;
        }
        go_x[go_n] = strtof(p, &e); if (*e != ':') break; p = e + 1;
        go_z[go_n] = strtof(p, &e); p = e;
        go_rr[go_n] = go_r;
        if (*p == ':') { go_rr[go_n] = strtof(p + 1, &e); p = e; }
        go_n++;
        if (*p == '_') p++; else break;
    }
    port_log("[p205go] %d waypoints from retrace %u, radius %.0f, taps %X\n", go_n, go_f, go_r, go_btn);
}
/* stick angle th (from up towards right) -> world heading atan2(dx, dz) = cam + base + sgn * th, cam from
 * D_800DD600. Fitted on the P205 goB log: sgn = -1, base ~ pi (start value); base is refined slowly from the motion
 * (the game polls the pad only on some retraces, so no frame-exact calibration). Stuck (< 8 units in 100 retraces):
 * jump (A) and turn the stick +90 degrees for 50 retraces. */
void p205_goto_apply(int *btn, int *sx, int *sy) {
    const unsigned char *r;
    float x, z, dx, dz, d, cam, th;
    unsigned t;
    if (go_n < 0) go_parse();
    if (go_n <= 0 || port_frame_count < go_f) return;
    r = D_800CC2D0 + (p205_player < 26 ? p205_player : 0) * REC;
    x = F(r, 0x14); z = F(r, 0x1C);
    cam = atan2f(D_800DD600[0], D_800DD600[1]);
    if (!go_have_init) { go_have_init = 1; go_sgn = -1; go_base = 3.14159265f; go_px = x; go_pz = z; go_sx0 = x; go_sz0 = z; go_stuck_f = port_frame_count; }
    if (go_i >= go_n) {   /* arrived: release the stick, tap the buttons */
        t = port_frame_count - go_arrive;
        *sx = 0; *sy = 0;
        if (go_btn && t < 60 * 30 && (t % 60) < 8) *btn |= go_btn;
        return;
    }
    {   /* refine base from the motion */
        float mx = x - go_px, mz = z - go_pz;
        if (mx * mx + mz * mz > 4.f && mx * mx + mz * mz < 400.f && go_th < 50.f)
            go_base = wrapa(go_base + 0.03f * wrapa(atan2f(mx, mz) - cam - go_sgn * go_th - go_base));
        go_px = x; go_pz = z;
    }
    if (go_ntap[go_i] > 0) {   /* tap step: stick released, BTN every 60 retraces (8 down) */
        if (!go_tap_f) { go_tap_f = port_frame_count; port_log("[p205go] retrace %u: tap step %d: %X x %d at %.1f %.1f %.1f\n", port_frame_count, go_i, go_tap[go_i], go_ntap[go_i], x, F(r, 0x18), z); }
        t = port_frame_count - go_tap_f;
        *sx = *sy = 0; go_th = 100.f;   /* no stick: no refinement from this motion */
        if ((t % 60) < 8) *btn |= go_tap[go_i];
        if (t >= 60u * go_ntap[go_i]) {
            go_tap_f = 0;
            if (++go_i >= go_n) go_arrive = port_frame_count;
            go_sx0 = x; go_sz0 = z; go_stuck_f = port_frame_count;
        }
        return;
    }
    dx = go_x[go_i] - x; dz = go_z[go_i] - z; d = sqrtf(dx * dx + dz * dz);
    if (d < go_rr[go_i]) {
        port_log("[p205go] retrace %u: waypoint %d (%.0f %.0f) reached at %.1f %.1f %.1f\n", port_frame_count, go_i,
                 go_x[go_i], go_z[go_i], x, F(r, 0x18), z);
        if (++go_i >= go_n || go_ntap[go_i] > 0) { if (go_i >= go_n) go_arrive = port_frame_count; *sx = *sy = 0; go_th = 100.f; return; }
        dx = go_x[go_i] - x; dz = go_z[go_i] - z; d = sqrtf(dx * dx + dz * dz);
    }
    th = wrapa(go_sgn * (atan2f(dx, dz) - cam - go_base));
    if (port_frame_count - go_stuck_f >= 100) {
        float sd = sqrtf((x - go_sx0) * (x - go_sx0) + (z - go_sz0) * (z - go_sz0));
        if (sd < 8.f) { go_have = 50; port_log("[p205go] retrace %u: stuck at %.1f %.1f, jump + turn\n", port_frame_count, x, z); }
        go_sx0 = x; go_sz0 = z; go_stuck_f = port_frame_count;
    }
    if (go_have > 0) { go_have--; th = wrapa(th + 1.5708f); if (go_have > 40) *btn |= 0x8000; }
    go_th = th;
    *sx = (int)lrintf(80.f * sinf(th)); *sy = (int)lrintf(80.f * cosf(th));
    if (port_frame_count % 50 == 0)
        port_log("[p205go] retrace %u: wp %d dist %.0f pos %.1f %.1f %.1f cam %.2f base %.2f stick %d,%d\n", port_frame_count,
                 go_i, d, x, F(r, 0x18), z, cam, go_base, *sx, *sy);
}

/* P205 DIAGNOSTIC ?p205dust=N: func_150CA150 landing_dust_burst (port-b P201 C; only caller func_15070014 in
 * game_981E0.c, so the --wrap sees every call): frame, character, position and floor (+0x180) before the call, first N
 * calls then every 16th. */
int __real_func_150CA150(unsigned char *obj);
int __wrap_func_150CA150(unsigned char *obj) {
    static int f = -1; static unsigned n;
    int r;
    if (f < 0) f = port_flag("p205dust");
    if (f > 0) {
        n++;
        if (n <= (unsigned)f || n % 16 == 0)
            port_log("[p205dust] call %u frame %u: obj %08X uid %02X pos %.1f %.1f %.1f vy %.2f floor %.1f\n", n,
                     port_frame_count, (unsigned)(uintptr_t)obj, obj ? vbe_ld8(obj + 0x3B) : 0, obj ? F(obj, 0x14) : 0.f,
                     obj ? F(obj, 0x18) : 0.f, obj ? F(obj, 0x1C) : 0.f, obj ? F(obj, 0x20) : 0.f, obj ? F(obj, 0x180) : 0.f);
    }
    r = __real_func_150CA150(obj);
    if (f > 0 && n <= (unsigned)f) port_log("[p205dust] call %u done\n", n);
    return r;
}
