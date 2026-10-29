/* P348 option "Photo mode" (PORT_OPT_PHOTO_MODE). A key (the page's "Photo mode" input, P / gamepad Back) freezes
 * the game; a free-flying camera shows the frozen moment from anywhere near, without the HUD, and the page saves the
 * picture as a PNG (also at twice the canvas resolution). Leaving photo mode puts the game back exactly where it was.
 *
 * Freeze: a snapshot of the whole game state (pc_nethash.c port_state_save: every game global, the N64 heap, the
 * libultra / scheduler / PIF / timer / audio HLE state and every game thread's stacks; the bytes the online desync hash
 * covers) is taken between two retraces, when every fiber is suspended. While photo mode is on, pc_sched.c frame()
 * runs no game retraces; it calls port_photo_tick() instead.
 *
 * Photo frames: the game's own pipeline draws them. Each one restores the snapshot, then runs retraces in a sandbox
 * (port_photo_sandbox = 1) until the game has built and drawn one frame: the next frame of the frozen moment, as the
 * game would have drawn it, with three changes made only in the sandbox (game_eu_15A210.c photo_camera_apply,
 * game_45B80.c):
 *   - the view: the photo camera's look-at (+ roll) is written into player 1's view matrices at the start of
 *     world_update and again after camera_update_all, so the object visibility test, the level's triangle culling, LOD
 *     and the draw all use the photo camera (geometry the game camera did not see is drawn too);
 *   - the field of view (zoom) through camera_projection_update;
 *   - the HUD (health, cash, letterbox bars, subtitles, fades, overlays) is not drawn (the L input shows it again).
 * Every sandboxed frame starts from the same snapshot, so the frozen moment never moves on: particles, water and the
 * animation stand still while the camera moves. Sandbox side effects that leave the game are held back: sound (no
 * audio buffer reaches the Web Audio ring), rumble, the EEPROM write callback (pc_os.c, pc_pif.c), the ?padrec log.
 * The game's clock stands still while photo mode is on (pc_os.c now_ms: the time at entry, plus one retrace period per
 * sandbox retrace) and goes on from there afterwards, like the page pause.
 * Leaving restores the snapshot once more: the next retrace runs from exactly the state the game had when photo mode
 * started (proof: ?nethash runs with and without a photo pause give the same hash for every retrace, P348).
 *
 * Not available: online sessions (port_net_on; the page also forces the option off: the other players would stall),
 * split screen (the photo camera is player 1's), and moments without a 3D view (pause menu, menus without a scene,
 * loading). The start pose is the view matrix on screen (any camera: follow, cutscene, look / aim, fixed), so photos of
 * cutscenes work too.
 *
 * Page API (main.js): port_photo_request(on), port_photo_status(), port_photo_input(...) every animation frame,
 * port_photo_render() (draw now, e.g. after the page resized the canvas for a 2x capture), port_photo_info(i).
 * Test aid: ?photoat=F enters photo mode after retrace F (or the first retrace after it where it can start), ?photofor=N leaves after N photo ticks,
 * ?photomove=FWD:RIGHT:UP:YAW:PITCH:ROLL:ZOOM (per tick: world units, degrees, zoom in % per tick) moves the camera,
 * ?photolog=N logs the pose every N ticks, ?photonodraw=1 enters and leaves without drawing photo frames. The entry /
 * exit lines carry the state hash (as ?nethash computes it) and the exit line the game's camera after the restore. */
#include <emscripten.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "port_options.h"

void port_log(const char *fmt, ...);
int port_flag(const char *name);
int port_option(int id);
extern unsigned port_frame_count;
extern int port_net_on;
double port_vi_period_ms(void);
void port_retrace_once(void);        /* pc_sched.c */
void port_video_frame(void);         /* pc_video.c */
size_t port_state_size(void);        /* pc_nethash.c */
int port_state_save(unsigned char *buf, size_t cap);
int port_state_restore(const unsigned char *buf);
void port_state_hash(uint32_t *hash_static, uint32_t *hash_stacks);
void port_photo_clock(int on);       /* pc_os.c */
/* game C (game_eu_15A210.c); weak: the scheduler demo links the PC layer without the game */
int photo_game_camera(float *out) __attribute__((weak));
void photo_look_scan(void) __attribute__((weak));   /* P358 game_eu_15A210.c: what Conker is made of (read-only) */

/* ---- state shared with pc_sched.c / pc_os.c / pc_pif.c and the game hooks. This object is left out of the snapshot
 * and the state hash (port/tools/net_regions.py), so restoring the game never resets photo mode itself. */
int port_photo_state;        /* 0 off, 1 entry requested, 2 on, 3 exit requested */
int port_photo_sandbox;      /* 1 while a photo frame's retraces run */
int port_photo_nohud;        /* 1 while a photo frame without the HUD is built (game_45B80.c) */
int port_photo_clock_on;     /* pc_os.c now_ms: the game's clock stands still at port_photo_clock_at + port_photo_clock_ms */
double port_photo_clock_at, port_photo_clock_ms;
int port_photo_watch;        /* ?photoat given: pc_sched.c calls port_photo_retrace_end after every retrace */

static unsigned char *snap;
static size_t snap_cap;
static struct {
    float eye[3], yaw, pitch, roll, zoom;   /* yaw: degrees, 0 = looking down -Z, + = to the right; pitch: + = up */
    float eye0[3], yaw0, pitch0;           /* the game's view at entry (B / reset) */
    float fov0[2];                         /* player 1's field of view at entry (x, y; degrees) */
    int hud;                               /* 1 = draw the HUD in photo frames */
} ph;
static int ph_dirty, ph_cam_applied, ph_drawn, ph_renders, ph_reason;

/* ---- P358 pose and outfit (the "look"). The page picks them (port_photo_look_set); the game applies them inside the
 * photo frames only (game_eu_15A210.c photo_look_apply and the draw hooks), so they vanish with the sandbox like the
 * photo camera. What the game reports about Conker (port_photo_look_report) is kept here, outside the snapshot.
 * Keys of the look (port_photo_look_set / port_photo_look_get, same numbers in main.js): */
enum {
    LK_ANIM = 0,       /* animation id, -1 = the game's own pose */
    LK_FRAME = 1,      /* frame within it (x 100, so the page can pass fractions) */
    LK_MODEL = 2,      /* model id from Conker's skeleton group, -1 = the game's model */
    LK_ITEM = 3,       /* i = 0..3: setup command list 1..63 run on Conker (held items / attachments), 0 = none */
    LK_ATT_HIDE = 4,   /* i = 0..15: key (asset << 8 | slot) of one of Conker's own attachments to hide, 0 = none */
    LK_DL_HIDE = 5,    /* bit k: hide display list k of the model (the game's own part mask, obj +0x94) */
    LK_DL_SHOW = 6,    /* bit k: show display list k although the game hides it */
    LK_FACE = 7,       /* i = 0..3: texture entry for segment 6 / 7 / 0xA / 0xB (eyes, mouth), -1 = the game's */
    LK_MAT_HIDE = 8,   /* i = material key (0..95): 1 = its triangles are not drawn */
    LK_MAT_TINT = 9,   /* i = material key: RGBA tint, A = strength (0 = none) */
    LK_MAT_TEX = 10,   /* i = material key: texture entry drawn instead, -1 = its own */
    LK_COUNT
};
#define LK_KEYS 96
static struct {
    int anim, frame100, model, item[4], att_hide[16], face[4], mat_tex[LK_KEYS];
    unsigned dl_hide, dl_show, mat_tint[LK_KEYS];
    unsigned char mat_hide[LK_KEYS];
} lk;
static int lk_any;   /* anything but the game's look is chosen */
static unsigned lk_serial;   /* photo frame number: port_photo_look_once */
static unsigned lk_once_tag[8], lk_once_serial[8];
/* reports (port_photo_look_report / port_photo_look_info). R_* ids, same numbers in main.js. */
enum {
    R_ANIM_COUNT = 0,  /* Conker's animation count */
    R_ANIM_BAD = 1,    /* i: 1 = animation i has no data (table entry 999 / >= 30000) */
    R_FRAMES = 2,      /* frame count of the animation the last photo frame showed */
    R_MODEL = 3,       /* Conker's model at entry */
    R_GROUP = 4,       /* i: the models sharing his skeleton and animations (i = 0..R_GROUP_N-1) */
    R_GROUP_N = 5,
    R_ITEM_KIND = 6,   /* i = list 1..63: command kinds (bit 0 attached object, bit 1 attachment, bit 2 animated attachment), 0 = empty */
    R_ITEM_ASSET = 7,  /* i = list: the first command's model / object id */
    R_ATT = 8,         /* i: key of Conker's own attachment i at entry (asset << 8 | slot) */
    R_ATT_N = 9,
    R_DRAWN_MODEL = 10,/* the model the last photo frame drew for Conker */
    R_DL_N = 11,       /* its display list count */
    R_DL_MASK = 12,    /* the game's hide mask (+0x94) in that frame */
    R_MAT_N = 13,      /* materials of that model: count */
    R_MAT_KEY = 14,    /* i: key of material i (0..63 texture entry, 64..67 face slot 6 / 7 / 0xA / 0xB, 80.. untextured group) */
    R_MAT_TRIS = 15,   /* i: its triangle count */
    R_TEX_N = 16,      /* texture entries of that model */
    R_TEX_ID = 17,     /* i: texture id */
    R_TEX_WH = 18,     /* i: width << 16 | height */
    R_FACE = 19,       /* i = 0..3: the texture entry the game put into segment 6 / 7 / 0xA / 0xB */
    R_ANIM_GAME = 20,  /* the animation Conker plays at entry */
    R_FRAME_GAME = 21, /* its frame at entry (x 100) */
    R_ERR = 22,        /* i: last problem (1 model did not load, 2 animation failed, 3 item failed) */
    R_COUNT
};
#define R_SLOTS 1024
static int rep_val[R_COUNT][R_SLOTS];
static unsigned ph_enter_retrace, ph_ticks;
static uint32_t ph_hash[2];
#define PH_RANGE 3000.0f   /* the camera stays within this distance (world units) of where it started */

static void forward(float yaw, float pitch, float *f) {
    float y = yaw * 0.017453292f, p = pitch * 0.017453292f;
    f[0] = sinf(y) * cosf(p); f[1] = sinf(p); f[2] = -cosf(y) * cosf(p);
}

/* game hook (photo_camera_apply): the photo camera of this frame. 0 outside photo frames. fov: wanted fields of view
 * (x, y degrees), 0 = keep the game's. */
int port_photo_camera(float *eye, float *at, float *roll, float *fov) {
    float f[3];
    if (!port_photo_sandbox || port_photo_state != 2) return 0;
    forward(ph.yaw, ph.pitch, f);
    for (int k = 0; k < 3; k++) { eye[k] = ph.eye[k]; at[k] = ph.eye[k] + f[k] * 100.0f; }
    *roll = ph.roll;
    if (ph.zoom != 1.0f && ph.fov0[0] > 0 && ph.fov0[1] > 0) {
        fov[0] = ph.fov0[0] * ph.zoom; fov[1] = ph.fov0[1] * ph.zoom;
        if (fov[0] > 150) fov[0] = 150; if (fov[1] > 150) fov[1] = 150;
    } else fov[0] = fov[1] = 0;
    return 1;
}
void port_photo_camera_applied(void) { ph_cam_applied = 1; }
/* pc_os.c osSpTaskStartGo: a gfx task ran; in a photo frame, it is the photo picture once the photo camera was set */
void port_photo_gfx_task(void) { if (port_photo_sandbox && ph_cam_applied) ph_drawn = 1; }

static void log_pose(const char *what) {
    port_log("[photo] %s: eye %.1f %.1f %.1f yaw %.1f pitch %.1f roll %.1f zoom %.2f (fov %.1f x %.1f) hud %d\n", what,
             ph.eye[0], ph.eye[1], ph.eye[2], ph.yaw, ph.pitch, ph.roll, ph.zoom, ph.fov0[0] * ph.zoom, ph.fov0[1] * ph.zoom, ph.hud);
}

/* game_45B80.c render_player_scene: player 1's 3D scene was drawn in this (real) frame */
static unsigned ph_scene_retrace;
static int ph_scene_seen;
void port_photo_scene_drawn(void) { if (!port_photo_sandbox) { ph_scene_retrace = port_frame_count; ph_scene_seen = 1; } }

static unsigned ph_refusals;
static int t_at = -1, t_for, t_log, t_nodraw, t_done;   /* test aid (below) */
static void refuse(int why, const char *text) {
    ph_reason = why; port_photo_state = 0;
    if (ph_refusals++ < 5) port_log("[photo] not started after retrace %u: %s\n", port_frame_count, text);
}
static void photo_enter(void) {
    float g[8];
    if (!port_option(PORT_OPT_PHOTO_MODE)) { refuse(1, "the option is off"); return; }
    if (port_net_on) { refuse(2, "online session"); return; }
    int cam = photo_game_camera ? photo_game_camera(g) : -0x80;
    if (cam != 1 || !ph_scene_seen || port_frame_count - ph_scene_retrace > 6) {
        if (ph_refusals < 5) port_log("[photo] no view: game check %d, 3D scene last drawn at retrace %u%s\n", cam, ph_scene_retrace, ph_scene_seen ? "" : " (never)");
        refuse(3, "no single-player 3D view now (menu, pause, split screen, loading)"); return;
    }
    size_t n = port_state_size();
    if (!n) { refuse(4, "the exclusion list conker_netx.txt is not loaded"); return; }
    if (snap_cap < n) {
        free(snap); snap_cap = n + (1u << 20); snap = malloc(snap_cap);
        if (!snap) { snap_cap = 0; refuse(5, "out of memory for the snapshot"); return; }
    }
    port_photo_clock(1);   /* before the save: the clock is not game state (pc_os.o wall time, this object) */
    if (port_state_save(snap, snap_cap)) { port_photo_clock(0); refuse(5, "snapshot failed"); return; }
    for (int k = 0; k < 3; k++) ph.eye[k] = ph.eye0[k] = g[k];
    {   /* yaw / pitch from the view's forward direction */
        float fx = g[3], fy = g[4], fz = g[5], h = sqrtf(fx * fx + fz * fz);
        ph.yaw = ph.yaw0 = atan2f(fx, -fz) * 57.29578f;
        ph.pitch = ph.pitch0 = atan2f(fy, h) * 57.29578f;
    }
    ph.fov0[0] = g[6]; ph.fov0[1] = g[7];
    ph.roll = 0; ph.zoom = 1;
    ph_reason = 0; ph_ticks = 0; ph_renders = 0;
    ph_enter_retrace = port_frame_count;
    port_state_hash(&ph_hash[0], &ph_hash[1]);
    port_log("[photo] on after retrace %u: snapshot %u KB, state hash %08X %08X\n", port_frame_count, (unsigned)(n >> 10), ph_hash[0], ph_hash[1]);
    log_pose("start (the game's view)");
    memset(rep_val, 0, sizeof rep_val);
    if (photo_look_scan) photo_look_scan();   /* P358: Conker's animations, models, items as the game has them now */
    port_log("[photo] look: model %d, %d animations (playing %d), %d models in his group, %d own attachments\n",
             rep_val[R_MODEL][0], rep_val[R_ANIM_COUNT][0], rep_val[R_ANIM_GAME][0], rep_val[R_GROUP_N][0], rep_val[R_ATT_N][0]);
    port_photo_state = 2; ph_dirty = 1; t_done = 1;
}
static void photo_leave(void) {
    uint32_t h[2];
    float g[8] = { 0 };
    int r = port_state_restore(snap);
    port_photo_clock(0);
    port_photo_state = 0;
    port_state_hash(&h[0], &h[1]);
    port_log("[photo] off: game back at retrace %u (entered after %u), %u photo frames, state hash %08X %08X (%s at entry)%s\n",
             port_frame_count, ph_enter_retrace, ph_renders, h[0], h[1], h[0] == ph_hash[0] && h[1] == ph_hash[1] ? "same as" : "DIFFERS from",
             r ? "; RESTORE FAILED" : "");
    if (photo_game_camera && photo_game_camera(g) == 1) {   /* the game's view after the restore: the start pose again */
        float h2 = sqrtf(g[3] * g[3] + g[5] * g[5]), yaw = atan2f(g[3], -g[5]) * 57.29578f, pitch = atan2f(g[4], h2) * 57.29578f;
        port_log("[photo] game camera after: eye %.1f %.1f %.1f yaw %.1f pitch %.1f (%s the start)\n", g[0], g[1], g[2], yaw, pitch,
                 g[0] == ph.eye0[0] && g[1] == ph.eye0[1] && g[2] == ph.eye0[2] && yaw == ph.yaw0 && pitch == ph.pitch0 ? "same as" : "DIFFERS from");
    }
}
/* one photo frame: the frozen moment, built by the game with the photo camera, drawn on the canvas */
static double ph_render_ms;
static int photo_render(void) {
    if (port_state_restore(snap)) return 0;
    double period = port_vi_period_ms(), t0 = emscripten_get_now();
    int k;
    port_photo_sandbox = 1; port_photo_nohud = !ph.hud;
    ph_cam_applied = ph_drawn = 0;
    lk_serial++;   /* P358: a new photo frame (port_photo_look_once); its reports of the pose start empty */
    rep_val[R_FRAMES][0] = 0; rep_val[R_ERR][0] = 0;
    for (k = 1; k <= 12 && !ph_drawn; k++) { port_photo_clock_ms = k * period; port_retrace_once(); }
    port_photo_sandbox = 0; port_photo_nohud = 0; port_photo_clock_ms = 0;
    port_video_frame();
    ph_renders++; ph_dirty = 0;
    ph_render_ms = emscripten_get_now() - t0;
    if (ph_renders <= 3 || !ph_drawn) port_log("[photo] frame %u: %d retraces, %.1f ms, %s\n", ph_renders, k - 1, ph_render_ms, ph_drawn ? "drawn" : "NOT drawn (the game built no frame)");
    return ph_drawn;
}

/* ---- P358 look: game side (game_eu_15A210.c). All of it only answers inside a photo frame of an active photo mode. */
/* 1 inside a photo frame: the game reports what Conker is made of and applies the chosen look (with nothing chosen
 * every hook leaves the frame as P348 drew it: the look's defaults change nothing) */
int port_photo_look_active(void) { return port_photo_sandbox && port_photo_state == 2; }
/* one value of the look (LK_*), index i for the arrays; the game's defaults when nothing is chosen */
int port_photo_look_get(int key, int i) {
    switch (key) {
    case LK_ANIM: return lk.anim;
    case LK_FRAME: return lk.frame100;
    case LK_MODEL: return lk.model;
    case LK_ITEM: return i >= 0 && i < 4 ? lk.item[i] : 0;
    case LK_ATT_HIDE: return i >= 0 && i < 16 ? lk.att_hide[i] : 0;
    case LK_DL_HIDE: return (int)lk.dl_hide;
    case LK_DL_SHOW: return (int)lk.dl_show;
    case LK_FACE: return i >= 0 && i < 4 ? lk.face[i] : -1;
    case LK_MAT_HIDE: return i >= 0 && i < LK_KEYS ? lk.mat_hide[i] : 0;
    case LK_MAT_TINT: return i >= 0 && i < LK_KEYS ? (int)lk.mat_tint[i] : 0;
    case LK_MAT_TEX: return i >= 0 && i < LK_KEYS ? lk.mat_tex[i] : -1;
    }
    return 0;
}
/* 1 the first time it is asked with this tag in the current photo frame (a frame's retraces may update the world
 * more than once: things that must happen once, e.g. adding an item or patching a display list, ask this) */
int port_photo_look_once(int tag) {
    int k, free_k = -1;
    for (k = 0; k < 8; k++) {
        if (lk_once_tag[k] == (unsigned)tag && lk_once_serial[k] == lk_serial) return 0;
        if (lk_once_serial[k] != lk_serial && free_k < 0) free_k = k;
    }
    if (free_k < 0) return 0;
    lk_once_tag[free_k] = (unsigned)tag; lk_once_serial[free_k] = lk_serial;
    return 1;
}
/* the game tells what Conker is made of (R_*; kept here, outside the snapshot) */
void port_photo_look_report(int what, int i, int value) {
    if (what >= 0 && what < R_COUNT && i >= 0 && i < R_SLOTS) rep_val[what][i] = value;
}
static void lk_reset(void) {
    int k;
    memset(&lk, 0, sizeof lk);
    lk.anim = -1; lk.model = -1;
    for (k = 0; k < 4; k++) lk.face[k] = -1;
    for (k = 0; k < LK_KEYS; k++) lk.mat_tex[k] = -1;
    lk_any = 0;
}
static void lk_update_any(void) {
    int k;
    lk_any = lk.anim >= 0 || lk.model >= 0 || lk.dl_hide || lk.dl_show;
    for (k = 0; k < 4; k++) lk_any |= lk.item[k] != 0 || lk.face[k] >= 0;
    for (k = 0; k < 16; k++) lk_any |= lk.att_hide[k] != 0;
    for (k = 0; k < LK_KEYS; k++) lk_any |= lk.mat_hide[k] || lk.mat_tint[k] || lk.mat_tex[k] >= 0;
}

/* ---- test aid: ?photoat / ?photofor / ?photomove / ?photolog (t_* declared above photo_enter) */
static float t_move[7];
/* field k of ?photomove (0 when absent). A number, not a string: a string result would be malloc'ed, and a heap layout
 * that depends on the URL moves the fiber stacks, whose addresses are game state (the hash would differ, P337) */
EM_JS(double, __photo_move_field, (int k), {
    if (typeof location === 'undefined') return 0;
    var v = new URLSearchParams(location.search).get('photomove');
    return v ? (parseFloat(v.split(':')[k]) || 0) : 0;
});
static void test_init(void) {
    if (t_at >= 0) return;
    t_at = port_flag("photoat"); t_for = port_flag("photofor"); t_log = port_flag("photolog"); t_nodraw = port_flag("photonodraw");
    for (int k = 0; k < 7; k++) t_move[k] = (float)__photo_move_field(k);
}
void port_photo_retrace_end(void) {   /* pc_sched.c retrace(), only while port_photo_watch */
    /* the first retrace from t_at on where photo mode can start (a refused start is tried again after the next one) */
    if (!port_photo_sandbox && port_photo_state == 0 && t_at > 0 && !t_done && port_frame_count >= (unsigned)t_at) {
        if (port_frame_count == (unsigned)t_at) port_log("[photo] ?photoat: entering after retrace %u\n", port_frame_count);
        port_photo_state = 1;
    }
}
void port_photo_input(float fwd, float right, float up, float dyaw, float dpitch, float droll, float zoom_mul, int flags);

/* pc_sched.c frame(), every main-loop tick while port_photo_state != 0 (not while the page is paused) */
void port_photo_tick(void) {
    if (port_photo_state == 1) photo_enter();
    if (port_photo_state == 3) { photo_leave(); return; }
    if (port_photo_state != 2) return;
    ph_ticks++;
    if (t_at > 0) {
        if (t_move[0] || t_move[1] || t_move[2] || t_move[3] || t_move[4] || t_move[5] || t_move[6])
            port_photo_input(t_move[0], t_move[1], t_move[2], t_move[3], t_move[4], t_move[5], 1.0f + t_move[6] / 100.0f, ph.hud);
        if (t_log > 0 && ph_ticks % (unsigned)t_log == 0) log_pose("pose");
        if (t_for > 0 && ph_ticks > (unsigned)t_for) { log_pose("last pose"); photo_leave(); return; }
    }
    if (ph_dirty && !t_nodraw) photo_render();
}

/* ---- page API */
/* on = 1: start photo mode at the next tick; 0: leave it. Returns the state, or -1 when the option is off / online. */
EMSCRIPTEN_KEEPALIVE int port_photo_request(int on) {
    if (on) {
        if (!port_option(PORT_OPT_PHOTO_MODE) || port_net_on) return -1;
        if (port_photo_state == 0) { port_photo_state = 1; ph_reason = 0; }
    } else {
        if (port_photo_state == 1) port_photo_state = 0;
        else if (port_photo_state == 2) port_photo_state = 3;
    }
    return port_photo_state;
}
/* the state (0 off, 1 starting, 2 on, 3 leaving); after a refused start: -reason (1 option off, 2 online, 3 no 3D view,
 * 4 no exclusion list, 5 memory) until the next request */
EMSCRIPTEN_KEEPALIVE int port_photo_status(void) { return port_photo_state ? port_photo_state : -ph_reason; }
/* this tick's camera movement: fwd / right / up in world units (along the view's heading, flat), dyaw / dpitch / droll
 * in degrees, zoom_mul multiplies the field of view (< 1 zooms in); flags: bit 0 = show the HUD, bit 1 = back to the
 * game's view */
EMSCRIPTEN_KEEPALIVE void port_photo_input(float fwd, float right, float up, float dyaw, float dpitch, float droll, float zoom_mul, int flags) {
    if (port_photo_state != 2) return;
    int hud = flags & 1;
    if (flags & 2) {
        for (int k = 0; k < 3; k++) ph.eye[k] = ph.eye0[k];
        ph.yaw = ph.yaw0; ph.pitch = ph.pitch0; ph.roll = 0; ph.zoom = 1; ph_dirty = 1;
    }
    if (hud != ph.hud) { ph.hud = hud; ph_dirty = 1; }
    if (!fwd && !right && !up && !dyaw && !dpitch && !droll && zoom_mul == 1.0f) return;
    ph.yaw = fmodf(ph.yaw + dyaw, 360.0f);
    ph.pitch += dpitch; if (ph.pitch > 89) ph.pitch = 89; if (ph.pitch < -89) ph.pitch = -89;
    ph.roll += droll; if (ph.roll > 180) ph.roll -= 360; if (ph.roll < -180) ph.roll += 360;
    ph.zoom *= zoom_mul; if (ph.zoom < 0.1f) ph.zoom = 0.1f; if (ph.zoom > 2.5f) ph.zoom = 2.5f;
    {   /* move along the flat heading (stick up = forward) and the world up axis */
        float y = ph.yaw * 0.017453292f, fx = sinf(y), fz = -cosf(y);
        float e[3] = { ph.eye[0] + fx * fwd - fz * right, ph.eye[1] + up, ph.eye[2] + fz * fwd + fx * right };
        float d[3] = { e[0] - ph.eye0[0], e[1] - ph.eye0[1], e[2] - ph.eye0[2] }, l = sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
        if (l > PH_RANGE) for (int k = 0; k < 3; k++) e[k] = ph.eye0[k] + d[k] * (PH_RANGE / l);
        for (int k = 0; k < 3; k++) ph.eye[k] = e[k];
    }
    ph_dirty = 1;
}
/* draw a photo frame now (the page calls it after resizing the canvas for a capture). The retraces switch fibers
 * (asyncify), so the value an export returns to JS is not reliable: port_photo_info(9) tells whether it drew. */
EMSCRIPTEN_KEEPALIVE void port_photo_render(void) { if (port_photo_state == 2) photo_render(); }
/* for the page's overlay: 0..2 eye, 3 yaw, 4 pitch, 5 roll, 6 zoom, 7 horizontal fov, 8 distance from the start,
 * 9 the last photo frame was drawn (1 / 0), 10 its cost in ms */
EMSCRIPTEN_KEEPALIVE float port_photo_info(int i) {
    switch (i) {
    case 0: case 1: case 2: return ph.eye[i];
    case 3: return ph.yaw; case 4: return ph.pitch; case 5: return ph.roll; case 6: return ph.zoom;
    case 7: return ph.fov0[0] * ph.zoom;
    case 9: return ph_drawn; case 10: return (float)ph_render_ms;
    case 8: { float d[3] = { ph.eye[0] - ph.eye0[0], ph.eye[1] - ph.eye0[1], ph.eye[2] - ph.eye0[2] }; return sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]); }
    }
    return 0;
}
/* P358 page API of the look. port_photo_look_set(key, i, value): one choice (LK_*); key -1 = back to the game's own
 * look (everything). The next photo frame shows it. port_photo_look_info(what, i): a report (R_*). */
EMSCRIPTEN_KEEPALIVE void port_photo_look_set(int key, int i, int v) {
    static int init;
    if (!init) { lk_reset(); init = 1; }
    switch (key) {
    case -1: lk_reset(); break;
    case LK_ANIM: lk.anim = v; break;
    case LK_FRAME: lk.frame100 = v < 0 ? 0 : v; break;
    case LK_MODEL: lk.model = v; break;
    case LK_ITEM: if (i >= 0 && i < 4) lk.item[i] = v; break;
    case LK_ATT_HIDE: if (i >= 0 && i < 16) lk.att_hide[i] = v; break;
    case LK_DL_HIDE: lk.dl_hide = (unsigned)v; break;
    case LK_DL_SHOW: lk.dl_show = (unsigned)v; break;
    case LK_FACE: if (i >= 0 && i < 4) lk.face[i] = v; break;
    case LK_MAT_HIDE: if (i >= 0 && i < LK_KEYS) lk.mat_hide[i] = v != 0; break;
    case LK_MAT_TINT: if (i >= 0 && i < LK_KEYS) lk.mat_tint[i] = (unsigned)v; break;
    case LK_MAT_TEX: if (i >= 0 && i < LK_KEYS) lk.mat_tex[i] = v; break;
    default: return;
    }
    lk_update_any();
    ph_dirty = 1;
}
EMSCRIPTEN_KEEPALIVE int port_photo_look_info(int what, int i) {
    return what >= 0 && what < R_COUNT && i >= 0 && i < R_SLOTS ? rep_val[what][i] : 0;
}

/* pc_sched.c port_run: arms the ?photoat test aid */
void port_photo_init(void) { if (!lk_any && lk.anim == 0 && lk.model == 0) lk_reset(); test_init(); port_photo_watch = t_at > 0; if (port_photo_watch) port_log("[photo] test aid: enter after retrace %d for %d ticks\n", t_at, t_for); }
