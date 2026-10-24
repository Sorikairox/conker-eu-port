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
    {   /* P236 TEST ?p205rec=N: the ?p205goto autopilot follows record N - 1 instead of D_800C3E78 (in Race A
         * D_800C3E78 names the CPU racer's record 1 in the look callback, so the autopilot steered by the CPU's position) */
        static int fp = -1;
        if (fp < 0) fp = port_flag("p205rec");
        if (fp > 0) p205_player = fp - 1;
    }
    { extern void p245_coldump(float, float, float); p245_coldump(0, 0, 0); }   /* P245 ?p245col=F triangle dump */
    { extern void p248_mesh(void); p248_mesh(); }   /* P248 ?p248mesh=F world objects, areas 2/3, gate watch */
    { extern void p223_hit_tick(void); p223_hit_tick(); }   /* P223 ?p223hit: follow a hit target */
    if (f < 0) f = port_flag("p205obj");
    if (f <= 0 || port_frame_count < (unsigned)f) return;
    if (last != ~0u && port_frame_count - last < 250) return;
    if (last == ~0u) {
        /* P212: once, the event zones D_800D34B8[D_800D3094] (0x34 bytes; event query 0x4nnn cmd 6 = "object not in
         * zone nnn"): s16 x y z +6, f32 +0x10, bytes +0x14..+0x17, words +0x18..+0x20, f32 +0x24..+0x30 */
        extern unsigned char *D_800D34B8; extern unsigned D_800D3094;
        unsigned k, nz = D_800D3094;
        port_log("[p212zone] frame %u %u zones\n", port_frame_count, nz);
        for (k = 0; k < nz && k < 256 && D_800D34B8; k++) {
            const unsigned char *z = D_800D34B8 + k * 0x34;
            port_log("[p212zone] %02X pos %d %d %d u6 %d f10 %.1f b14 %02X %02X %02X %02X w18 %X %X %X f24 %.1f %.1f %.1f %.1f\n",
                     k, (short)vbe_ld16(z), (short)vbe_ld16(z + 2), (short)vbe_ld16(z + 4), (short)vbe_ld16(z + 6),
                     F(z, 0x10), vbe_ld8(z + 0x14), vbe_ld8(z + 0x15), vbe_ld8(z + 0x16), vbe_ld8(z + 0x17),
                     *(const unsigned *)(z + 0x18), *(const unsigned *)(z + 0x1C), *(const unsigned *)(z + 0x20),
                     F(z, 0x24), F(z, 0x28), F(z, 0x2C), F(z, 0x30));
        }
    }
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
    {   /* P236 DIAGNOSTIC ?p236race=1 (with ?p205obj): the race / rail records D_80087640[humans + cpus] (0x84 bytes,
         * func_15088E84 rail_param_step): f32 param +8, s32 lap start +0x18 / time +0x1C / lap time +0x20, s16 node
         * counter +0x24, s8 lap length +0x26, lap +0x27, highest lap +0x28, nodes +0x2B..+0x2E, on rail +0x30, player
         * +0x31; laps D_800E1017, D_800BE616, humans D_80090130. */
        static int fr = -1;
        extern unsigned char *D_80087640; extern signed char D_800D27B8, D_800D27B9, D_800E1017, D_80090130;
        extern unsigned char D_800BE616;
        int k, n;
        if (fr < 0) fr = port_flag("p236race");
        if (fr > 0 && D_80087640) {
            extern unsigned p236_rail_calls[8], p236_rail_mode[8];
            port_log("[p236race] rail_track_update calls per record: %u %u %u %u %u %u (mode of last: %u %u)\n",
                     p236_rail_calls[0], p236_rail_calls[1], p236_rail_calls[2], p236_rail_calls[3], p236_rail_calls[4],
                     p236_rail_calls[5], p236_rail_mode[0], p236_rail_mode[1]);
            {   /* once: the rail nodes D_800D2778 (0x10 bytes: s16 x y z, links +9..+0xD, type +0xE, camera +0xF) */
                static int nd; extern unsigned char *D_800D2778; int j;
                if (!nd && D_800D2778) {
                    nd = 1;
                    for (j = 0; j < 100; j++) {
                        const unsigned char *q = D_800D2778 + j * 0x10;
                        port_log("[p236node] %d %d %d %d links %d %d %d %d %d type %d cam %d\n", j, (short)vbe_ld16(q),
                                 (short)vbe_ld16(q + 2), (short)vbe_ld16(q + 4), vbe_ld8(q + 9), vbe_ld8(q + 10),
                                 vbe_ld8(q + 11), vbe_ld8(q + 12), vbe_ld8(q + 13), vbe_ld8(q + 14), vbe_ld8(q + 15));
                    }
                }
            }
            n = vbe_ld8(&D_800D27B8) + vbe_ld8(&D_800D27B9);
            port_log("[p236race] frame %u: %d records, laps %d, BE616 %d, humans %d\n", port_frame_count, n,
                     (signed char)vbe_ld8(&D_800E1017), vbe_ld8(&D_800BE616), (signed char)vbe_ld8(&D_80090130));
            for (k = 0; k < n && k < 8; k++) {
                const unsigned char *q = D_80087640 + k * 0x84;
                port_log("[p236race]   %d: t %.3f start %d time %d lapt %d cnt %d len %d lap %d max %d nodes %d %d %d %d rail %d pl %d\n",
                         k, F(q, 8), *(const int *)(q + 0x18), *(const int *)(q + 0x1C), *(const int *)(q + 0x20),
                         (short)vbe_ld16(q + 0x24), (signed char)vbe_ld8(q + 0x26), (signed char)vbe_ld8(q + 0x27),
                         (signed char)vbe_ld8(q + 0x28), vbe_ld8(q + 0x2B), vbe_ld8(q + 0x2C), vbe_ld8(q + 0x2D),
                         vbe_ld8(q + 0x2E), (signed char)vbe_ld8(q + 0x30), (signed char)vbe_ld8(q + 0x31));
            }
        }
    }
}

/* P205 TEST ?p205goto=F:R:BTN:X1:Z1_X2:Z2_... (node: PORT_P205GOTO): pad autopilot for test routes. From retrace F
 * on, the stick of pad 0 (after ?padf) is replaced by one that steers the player record (D_800CC2D0[D_800C3E78 as
 * read in the look callback; at PIF time D_800C3E78 names other records])
 * towards the waypoints in turn (x / z, reached within R units). The stick-to-world angle depends on the camera, so it
 * is learned from the motion: offset = heading moved - stick angle, smoothed. After the last waypoint the stick is
 * released and BTN (hex, e.g. 8000 = A, 4000 = B) is tapped every 60 retraces (8 retraces down) for 30 taps;
 * BTN 0 = no taps. A step written tBTN:N (e.g. t8000:40) instead of X:Z taps BTN N times there, then goes on;
 * X:Z:R gives one waypoint its own radius. P223: jX:Z jumps (A) every 40 retraces on the way to that waypoint.
 * Logs [p205go] every 50 retraces and on each waypoint. */
#include <math.h>
#include <emscripten.h>
EM_JS(int, __port_p205_goto_char, (int i), {
    var v = null;
    if (typeof location !== 'undefined') { var m = /[?&]p205goto=([^&]*)/.exec(location.search); if (m) v = decodeURIComponent(m[1]); }
    else if (typeof process !== 'undefined' && process.env && process.env.PORT_P205GOTO !== undefined) v = process.env.PORT_P205GOTO;
    return v === null || i >= v.length ? 0 : v.charCodeAt(i);
});
#define GO_MAX 100   /* P236: 32 -> 100 (3 race laps) */
extern float D_800DD600[2];   /* camera yaw of view 0: sin, cos (func_15167310) */
static int go_n = -1, go_i, go_btn;
static unsigned go_f, go_arrive, go_stuck_f;
static float go_r, go_x[GO_MAX], go_z[GO_MAX];
static int go_tap[GO_MAX], go_ntap[GO_MAX];   /* step k is "tap go_tap[k] go_ntap[k] times" when go_ntap[k] > 0 */
static float go_rr[GO_MAX];                    /* per-waypoint radius (X:Z:R), else go_r */
static int go_jmp[GO_MAX];                     /* P223: jX:Z = jump (A, 8 of every 40 retraces) on the way there; P248: hX:Z = 2 (jump, then A held = helicopter hover; 200-retrace cycle) */
static unsigned go_tap_f;
static float go_px, go_pz, go_base, go_th, go_sx0, go_sz0;
static int go_sgn = -1, go_have, go_have_init;
static float wrapa(float a) { while (a > 3.14159265f) a -= 6.2831853f; while (a < -3.14159265f) a += 6.2831853f; return a; }
static void go_parse(void) {
    char s[4096]; int n = 0, c; char *p, *e;
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
        go_jmp[go_n] = 0; if (*p == 'j') { go_jmp[go_n] = 1; p++; } else if (*p == 'h') { go_jmp[go_n] = 2; p++; }
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
/* P240 TEST ?p240steer=F[:LOOK[:PCT]] (node: PORT_P240STEER): hoverboard steering controller for Race A. From retrace F on
 * the stick of pad 0 steers player record p205_player (?p205rec) towards a rail node ahead in the player's rail
 * record (D_80087640 entry whose +0x31 is 0): node list +0x2B..+0x2E, from slot LOOK (1 default .. 3), skipping nodes
 * already reached (within 900 units) or passed (the board is within the node's distance + 400 of the next slot's
 * node; nodes reached / passed are remembered, last 6); target = node + PCT% (default 50) of the way to its
 * type-4 edge node (link +0xB), from D_800D2778. Stick angle th = wrap(cam + pi - bearing)
 * (the P205 camera mapping, sgn -1, base pi; the board camera sits behind the board), limited to +-100 degrees,
 * magnitude 80. Stuck (< 30 units in 120 retraces): stick at +90 degrees with A for 40 retraces. Once the record's
 * highest lap (+0x28) reaches the lap count D_800E1017 the stick is released (P245: A taps every 60 retraces only from 1500 retraces later).
 * Logs [p240steer] every 40 retraces and on each node / lap change. Wins over ?p205goto. */
EM_JS(int, __port_p240_steer, (void), {
    var v = null;
    if (typeof location !== 'undefined') { var m = /[?&]p240steer=([^&]*)/.exec(location.search); if (m) v = decodeURIComponent(m[1]); }
    else if (typeof process !== 'undefined' && process.env && process.env.PORT_P240STEER !== undefined) v = process.env.PORT_P240STEER;
    if (v === null) return -1;
    var a = v.split(':'); return ((parseInt(a[0], 10) || 0) * 4 + ((parseInt(a[1] || '1', 10) || 1) & 3)) * 128 + Math.min(127, parseInt(a[2] || '50', 10));
});
/* P245: 4th field START: for START retraces from F the stick is held straight up (no target), as the CPU leaves the grid
 * (race7/8 stalled 120+ retraces on the grid steering sideways towards node 21, then respawned twice). */
EM_JS(int, __port_p240_start, (void), {
    var v = null;
    if (typeof location !== 'undefined') { var m = /[?&]p240steer=([^&]*)/.exec(location.search); if (m) v = decodeURIComponent(m[1]); }
    else if (typeof process !== 'undefined' && process.env && process.env.PORT_P240STEER !== undefined) v = process.env.PORT_P240STEER;
    if (v === null) return 0;
    return parseInt(v.split(':')[3] || '0', 10) || 0;
});
static int p240_start;
static float p240_frac = 0.5f;   /* ?p240steer=F:LOOK:PCT: target = node + PCT% of the way to its edge node */
static void node_centre(int ni, float *tx, float *tz) {   /* P240: rail node + its type-4 edge node (link +0xB), halved */
    extern unsigned char *D_800D2778;
    const unsigned char *nd = D_800D2778 + ni * 0x10, *ed;
    int e = vbe_ld8(nd + 0xB);
    *tx = (short)vbe_ld16(nd); *tz = (short)vbe_ld16(nd + 4);
    if (e < 100) { ed = D_800D2778 + e * 0x10; if (vbe_ld8(ed + 0xE) == 4) { *tx += ((short)vbe_ld16(ed) - *tx) * p240_frac; *tz += ((short)vbe_ld16(ed + 4) - *tz) * p240_frac; } }
}
static int p240_steer(int *btn, int *sx, int *sy) {
    static int cfg = -2, look, last_node = -1, last_lap = -1, unstick, done;
    static unsigned f0, st_f, done_f, log_f; static float st_x, st_z; static int reached[6], nreached;
    extern unsigned char *D_80087640, *D_800D2778; extern signed char D_800D27B8, D_800D27B9, D_800E1017;
    const unsigned char *r, *q = 0;
    float x, z, tx, tz, cam, b, th; int k, n, ni, lap, laps, passed, allseen;
    if (cfg == -2) { cfg = __port_p240_steer(); if (cfg >= 0) { p240_frac = (cfg & 127) / 100.f; cfg >>= 7; f0 = (unsigned)cfg >> 2; look = cfg & 3; if (look < 1) look = 1;
        p240_start = __port_p240_start();
        port_log("[p240steer] from retrace %u, look slot %d, edge fraction %.2f, start phase %d\n", f0, look, p240_frac, p240_start); } }
    if (cfg < 0 || port_frame_count < f0 || !D_80087640 || !D_800D2778) return cfg >= 0 && port_frame_count >= f0;
    n = vbe_ld8(&D_800D27B8) + vbe_ld8(&D_800D27B9);
    for (k = 0; k < n && k < 8; k++) if ((signed char)vbe_ld8(D_80087640 + k * 0x84 + 0x31) == 0) { q = D_80087640 + k * 0x84; break; }
    if (!q) return 1;
    r = D_800CC2D0 + (p205_player < 26 ? p205_player : 0) * REC;
    x = F(r, 0x14); z = F(r, 0x1C);
    lap = (signed char)vbe_ld8(q + 0x28); laps = (signed char)vbe_ld8(&D_800E1017);
    if (lap != last_lap) { port_log("[p240steer] retrace %u: lap %d (max) of %d, cnt %d, pos %.0f %.0f\n", port_frame_count, lap, laps,
                                    (short)vbe_ld16(q + 0x24), x, z); last_lap = lap; }
    if (laps > 0 && lap >= laps) {   /* finished: release, tap A */
        if (!done) { done = 1; done_f = port_frame_count; port_log("[p240steer] retrace %u: finished (%d laps)\n", port_frame_count, lap); }
        *sx = *sy = 0;   /* P245: no A for 1500 retraces (A on the STATS overlay picks RESTART: raceA2 lost the STATS view in 52 retraces) */
        if (port_frame_count - done_f >= 1500 && (port_frame_count - done_f) % 60 < 8) *btn |= 0x8000;
        return 1;
    }
    if (port_frame_count < f0 + (unsigned)p240_start) {   /* P245 start phase: stick up, no target */
        *sx = 0; *sy = 80; st_f = 0;
        if ((port_frame_count - f0) % 40 == 0) port_log("[p240steer] retrace %u: start phase pos %.0f %.0f\n", port_frame_count, x, z);
        return 1;
    }
    /* P240 r3: the first node in slots LOOK..3 not yet reached (within 900 units of its centre; the last 6 reached
     * nodes are remembered), else straight on. The record can lag behind the board (it advanced only at respawns in r2),
     * so a reached node must never become the target again (r2 turned back to node 22 and stuck on a wall). */
    allseen = 0;
    for (k = look; k <= 3; k++) {
        int j, seen = 0;
        ni = vbe_ld8(q + 0x2B + k);
        if (ni == 0xFF || ni >= 100) { if (k == look) return 1; ni = vbe_ld8(q + 0x2B + k - 1); break; }
        for (j = 0; j < 6; j++) if (reached[j] == ni + 1) seen = 1;
        if (seen && k < 3) continue;
        node_centre(ni, &tx, &tz);
        passed = 0;
        if (!seen && k < 3) {   /* passed: the board is nearer (+400) the next slot's node than this node is (r4: the slack lets a start-grid
                                     * place beside node 21 count as past it; race7 turned back there) */
            int nn = vbe_ld8(q + 0x2B + k + 1); float ux, uz;
            if (nn != 0xFF && nn < 100) {
                node_centre(nn, &ux, &uz);
                passed = sqrtf((ux - x) * (ux - x) + (uz - z) * (uz - z)) < sqrtf((ux - tx) * (ux - tx) + (uz - tz) * (uz - tz)) + 400.f;
            }
        }
        if (seen && k == 3) { allseen = 1; break; }
        if (!seen && (passed || (tx - x) * (tx - x) + (tz - z) * (tz - z) < 900.f * 900.f)) {
            reached[nreached++ % 6] = ni + 1;
            port_log("[p240steer] retrace %u: %s node %d at %.0f %.0f\n", port_frame_count, passed ? "passed" : "reached", ni, x, z);
            if (k < 3) continue;
        }
        break;
    }
    node_centre(ni, &tx, &tz);
    cam = atan2f(D_800DD600[0], D_800DD600[1]);
    b = atan2f(tx - x, tz - z);
    th = allseen ? 0.f : wrapa(cam + 3.14159265f - b);   /* every slot reached (record lags): straight on */
    if (th > 1.745f) th = 1.745f; else if (th < -1.745f) th = -1.745f;
    if (!st_f) { st_f = port_frame_count; st_x = x; st_z = z; }
    if (port_frame_count - st_f >= 120) {
        float d = sqrtf((x - st_x) * (x - st_x) + (z - st_z) * (z - st_z));
        if (d < 30.f) { unstick = 40; port_log("[p240steer] retrace %u: stuck at %.0f %.0f (moved %.0f), turn + A\n", port_frame_count, x, z, d); }
        st_f = port_frame_count; st_x = x; st_z = z;
    }
    if (unstick > 0) { unstick--; th = 1.5708f; *btn |= 0x8000; }
    *sx = (int)lrintf(80.f * sinf(th)); *sy = (int)lrintf(80.f * cosf(th));
    if (ni != last_node || port_frame_count - log_f >= 40) {
        log_f = port_frame_count;
        port_log("[p240steer] retrace %u: node %d (%.0f %.0f) pos %.0f %.1f %.0f cnt %d lap %d cam %.2f brg %.2f th %.2f stick %d,%d\n",
                 port_frame_count, ni, tx, tz, x, F(r, 0x18), z, (short)vbe_ld16(q + 0x24), (signed char)vbe_ld8(q + 0x27), cam, b, th, *sx, *sy);
        last_node = ni;
    }
    return 1;
}
void p205_goto_apply(int *btn, int *sx, int *sy) {
    if (p240_steer(btn, sx, sy)) return;
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
    else if (go_jmp[go_i] == 1 && port_frame_count % 40 < 8) *btn |= 0x8000;
    else if (go_jmp[go_i] == 2) {   /* P248 hX:Z: jump + helicopter: A 0-5, 10-15 (a second chance to jump when the
                                     * first press came during a landing), then held from 20; cycle 200 retraces */
        static int hi = -1; static unsigned hf;
        unsigned ht;
        if (hi != go_i) { hi = go_i; hf = port_frame_count; }
        ht = (port_frame_count - hf) % 200;
        if (ht < 6 || (ht >= 10 && ht < 16) || ht >= 20) *btn |= 0x8000;
    }
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

/* P236 DIAGNOSTIC: count func_150877C0 rail_track_update calls per rail record (callers: script cmd 18 in
 * game_eu_CBB40.c func_1509E3D4, thrown objects in game_eu_78230.c func_150538CC); printed by ?p236race. */
unsigned p236_rail_calls[8], p236_rail_mode[8];
void __real_func_150877C0(int player, int mode, float speed);
void __wrap_func_150877C0(int player, int mode, float speed) {
    static int rw = -1;
    extern unsigned char *D_80087640;
    const unsigned char *q = D_80087640 ? D_80087640 + (player & 7) * 0x84 : 0;
    int lg;
    float t0 = 0.f; int c0 = 0, n0 = 0;
    if ((unsigned)player < 8) { p236_rail_calls[player]++; p236_rail_mode[player] = (unsigned)mode; }
    if (rw < 0) rw = port_flag("p236rw");   /* ?p236rw=F: log player 0's tracking for retraces F .. F+600 */
    lg = rw > 0 && player == 0 && q && port_frame_count >= (unsigned)rw && port_frame_count < (unsigned)rw + 600;
    if (lg) { t0 = F(q, 8); c0 = (short)vbe_ld16(q + 0x24); n0 = vbe_ld8(q + 0x2C); }
    __real_func_150877C0(player, mode, speed);
    if (lg) {
        const unsigned char *o = D_800CC2D0 + (signed char)vbe_ld8(q + 0x31) * REC;
        port_log("[p236rw] %u pos %.0f %.0f %.0f | t %.3f cnt %d n %d -> t %.3f cnt %d nodes %d %d %d %d alt %d off %.2f n(%.2f %.2f)\n",
                 port_frame_count, F(o, 0x14), F(o, 0x18), F(o, 0x1C), t0, c0, n0, F(q, 8), (short)vbe_ld16(q + 0x24),
                 vbe_ld8(q + 0x2B), vbe_ld8(q + 0x2C), vbe_ld8(q + 0x2D), vbe_ld8(q + 0x2E), (signed char)vbe_ld8(q + 0x2F),
                 F(q, 0), F(q, 0xC), F(q, 0x10));
    }
}

/* P240 DIAGNOSTIC: count func_151B61A0 ripple_spawn_flat calls (P234 C; only caller func_1513783C in game_161520.c,
 * so the --wrap sees every call). ?p240rip=N logs the first N calls and then every 64th: frame, position, life,
 * result. Calls through unchanged. */
int __real_func_151B61A0(float *pos, float *vel, float scale, float *dir, float *acc, float speed, short life,
                         unsigned char alpha, int a8, float a9, unsigned char aA, unsigned char aB, unsigned char aC, int aD);
int __wrap_func_151B61A0(float *pos, float *vel, float scale, float *dir, float *acc, float speed, short life,
                         unsigned char alpha, int a8, float a9, unsigned char aA, unsigned char aB, unsigned char aC, int aD) {
    static int f = -1; static unsigned n;
    int r = __real_func_151B61A0(pos, vel, scale, dir, acc, speed, life, alpha, a8, a9, aA, aB, aC, aD);
    if (f < 0) f = port_flag("p240rip");
    n++;
    if (f > 0 && (n <= (unsigned)f || n % 64 == 0))
        port_log("[p240rip] call %u frame %u: pos %.1f %.1f %.1f scale %.2f speed %.2f life %d alpha %u -> %d\n", n,
                 port_frame_count, pos ? pos[0] : 0.f, pos ? pos[1] : 0.f, pos ? pos[2] : 0.f, scale, speed, life, alpha, r);
    return r;
}
