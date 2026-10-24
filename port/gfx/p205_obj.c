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

void p205_obj_hook(void) {
    static int f = -1;
    static unsigned last = ~0u;
    int i;
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
 * on, the stick of pad 0 (after ?padf) is replaced by one that steers the player record (D_800CC2D0[D_800C3E78])
 * towards the waypoints in turn (x / z, reached within R units). The stick-to-world angle depends on the camera, so it
 * is learned from the motion: offset = heading moved - stick angle, smoothed. After the last waypoint the stick is
 * released and BTN (hex, e.g. 8000 = A, 4000 = B) is tapped every 60 retraces (8 retraces down) for 30 taps;
 * BTN 0 = no taps. Logs [p205go] every 50 retraces and on each waypoint. */
#include <math.h>
#include <emscripten.h>
EM_JS(int, __p205_goto_char, (int i), {
    var v = null;
    if (typeof location !== 'undefined') { var m = /[?&]p205goto=([^&]*)/.exec(location.search); if (m) v = decodeURIComponent(m[1]); }
    else if (typeof process !== 'undefined' && process.env && process.env.PORT_P205GOTO !== undefined) v = process.env.PORT_P205GOTO;
    return v === null || i >= v.length ? 0 : v.charCodeAt(i);
});
#define GO_MAX 32
static int go_n = -1, go_i, go_btn;
static unsigned go_f, go_arrive;
static float go_r, go_x[GO_MAX], go_z[GO_MAX];
static float go_px, go_pz, go_off, go_sa;
static int go_have, go_last_sx, go_last_sy;
static float wrapa(float a) { while (a > 3.14159265f) a -= 6.2831853f; while (a < -3.14159265f) a += 6.2831853f; return a; }
static void go_parse(void) {
    char s[1024]; int n = 0, c; char *p, *e;
    while (n < (int)sizeof s - 1 && (c = __p205_goto_char(n)) != 0) s[n++] = (char)c;
    s[n] = 0; go_n = 0;
    if (!n) return;
    p = s;
    go_f = (unsigned)strtoul(p, &e, 10); if (*e != ':') return; p = e + 1;
    go_r = strtof(p, &e); if (*e != ':') return; p = e + 1;
    go_btn = (int)strtol(p, &e, 16); if (*e != ':') return; p = e + 1;
    while (*p && go_n < GO_MAX) {
        go_x[go_n] = strtof(p, &e); if (*e != ':') break; p = e + 1;
        go_z[go_n] = strtof(p, &e); go_n++; p = e;
        if (*p == '_') p++; else break;
    }
    port_log("[p205go] %d waypoints from retrace %u, radius %.0f, taps %X\n", go_n, go_f, go_r, go_btn);
}
void p205_goto_apply(int *btn, int *sx, int *sy) {
    const unsigned char *r;
    float x, z, dx, dz, d, hd, ang;
    if (go_n < 0) go_parse();
    if (go_n <= 0 || port_frame_count < go_f) return;
    r = D_800CC2D0 + vbe_ld8(D_800C3E78_p205) * REC;
    x = F(r, 0x14); z = F(r, 0x1C);
    if (go_i >= go_n) {   /* arrived: release the stick, tap the buttons */
        unsigned t = port_frame_count - go_arrive;
        *sx = 0; *sy = 0;
        if (go_btn && t < 60 * 30 && (t % 60) < 8) *btn |= go_btn;
        return;
    }
    if (go_have) {   /* learn the stick -> world angle offset from the last motion */
        float mx = x - go_px, mz = z - go_pz;
        if (mx * mx + mz * mz > 0.25f && (go_last_sx || go_last_sy))
            go_off = wrapa(go_off + 0.25f * wrapa(atan2f(mx, mz) - go_sa - go_off));
    }
    go_px = x; go_pz = z; go_have = 1;
    dx = go_x[go_i] - x; dz = go_z[go_i] - z; d = sqrtf(dx * dx + dz * dz);
    if (d < go_r) {
        port_log("[p205go] retrace %u: waypoint %d (%.0f %.0f) reached at %.1f %.1f %.1f\n", port_frame_count, go_i,
                 go_x[go_i], go_z[go_i], x, F(r, 0x18), z);
        if (++go_i >= go_n) { go_arrive = port_frame_count; *sx = *sy = 0; go_last_sx = go_last_sy = 0; return; }
        dx = go_x[go_i] - x; dz = go_z[go_i] - z; d = sqrtf(dx * dx + dz * dz);
    }
    hd = atan2f(dx, dz);
    go_sa = wrapa(hd - go_off);
    ang = go_sa;
    /* stick: angle measured from up (y) towards right (x) */
    *sx = (int)lrintf(80.f * sinf(ang)); *sy = (int)lrintf(80.f * cosf(ang));
    go_last_sx = *sx; go_last_sy = *sy;
    if (port_frame_count % 50 == 0)
        port_log("[p205go] retrace %u: wp %d dist %.0f pos %.1f %.1f %.1f off %.2f stick %d,%d\n", port_frame_count, go_i, d,
                 x, F(r, 0x18), z, go_off, *sx, *sy);
}
