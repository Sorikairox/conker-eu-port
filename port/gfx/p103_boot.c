/* P103 DIAGNOSTICS (off by default): the boot sequence and the level-start event list.
 *
 * ?p103boot=1 : one line per change of the game mode g_game_mode or the level g_level_id (called from the
 *               game_mode_frame_step wrap in p84_checks.c): mode, previous mode g_game_mode_prev, mode timer g_game_mode_timer,
 *               osTvType D_80000300, world objects g_world_obj_count, level events D_800D2F3C, scene slot 0 D_800C35EA.
 *               Also logs every event_start_level_events call (level-start event pass: the event ids D_800D2F40[0..n-1], their
 *               D_800877D0 record, and what the asm event_prereqs_met would answer, computed here from its asm), every
 *               event_start call (start one event) and every cutscene_scene_load call (scene load).
 * ?p103ev=1   : TEST ONLY. event_prereqs_met (game_eu_CA630.c, still an asm stub = always 0) answers with the C below, so
 *               event_start_level_events goes on to event_start (also an asm stub). Shows which events the stub suppresses.
 *
 * event_prereqs_met(id) from the asm: the u16 list D_800877D0[id] + 0xC (0xFFFF-terminated) holds prerequisite event ids;
 * for each one p, recurse on p, then require save flag bit p (g_save_progress_bits byte p >> 3, bit p & 7) and the recursion's
 * result; an empty list answers 1. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;

extern unsigned char g_game_mode, g_game_mode_prev, D_800D2F3C, D_800C35EA; /* was D_800E0B94; was D_800E0FC5 */
extern int g_level_id, g_game_mode_timer, D_80000300, g_world_obj_count; /* was D_800DC320; was D_800BE9F0; was D_800E0EC0 */
extern unsigned char *D_800D2F40;  /* u16 ids */
extern unsigned char *g_save_progress_bits;  /* save flags (pointer); was D_800D2E4C */
extern unsigned char D_800877D0[]; /* 0x14-byte records */

static int fboot = -1, fev = -1;
static int flag(int *f, const char *n) { if (*f < 0) *f = port_flag(n); return *f; }

/* P154: the upper bound is the wasm memory size (was 0x20000000: a stale queue pointer in 0x16000000..0x1FFFFFFF trapped
 * the ?p103boot event log in __wrap_scene_event_track_pass at the Gregg scene load, frame 12441) */
static int memok(const void *p) {
    uintptr_t a = (uintptr_t)p;
    /* P199: compare without the a + 0x20 overflow: an end-of-list / sentinel pointer such as 0xFFFFFFF0 wrapped to a
     * small value, passed, and crashed the ?p103boot event log at frame 17820 (level 6 scene 20) */
    uintptr_t top = (uintptr_t)__builtin_wasm_memory_size(0) * 65536u;
    return a >= 0x100 && top >= 0x20 && a <= top - 0x20;
}

static int p103_prereq(int id, int depth) {
    const unsigned char *rec = D_800877D0 + id * 0x14;
    const unsigned char *p = (const unsigned char *)(uintptr_t)*(const unsigned *)(rec + 0xC);
    const unsigned char *save = g_save_progress_bits;
    unsigned e;
    if (depth > 16 || !memok(p) || !memok(save)) return -1;
    e = vbe_ld16(p);
    while (e != 0xFFFF) {
        int ok = p103_prereq(e, depth + 1);
        e = vbe_ld16(p);
        if (!(vbe_ld8(save + (e >> 3)) & (1u << (e & 7))) || ok <= 0) return 0;
        p += 2;
        e = vbe_ld16(p);
    }
    return 1;
}

void p123_gates(void);
void p103_frame(void) {
    static int lmode = -1, llevel = -1;
    p123_gates();
    int m = vbe_ld8(&g_game_mode), l = g_level_id;
    if (flag(&fboot, "p103boot") && m == 3) { /* P121: menu record g_menu_state (P117 map): +8 page fade f32, +0x2C titlePage,
                                                * +0x3E menu, +0x3F mainPage; on change of the bytes, else every 240 frames */
        extern unsigned char *g_menu_state; extern unsigned char g_screen_fade_alpha, g_menu_fade_speed, g_menu_alpha;
        static unsigned lastkey = ~0u, nl, next;
        const unsigned char *r = g_menu_state;
        if (memok(r) && nl < 60) {
            unsigned fw = *(const unsigned *)(r + 8), key = vbe_ld8(r + 0x2C) | vbe_ld8(r + 0x3E) << 8 | vbe_ld8(r + 0x3F) << 16 |
                (unsigned)vbe_ld8(&g_menu_fade_speed) << 24;
            float fade; memcpy(&fade, &fw, 4);
            static unsigned lastfw;
            if (key != lastkey || fw != lastfw || port_frame_count >= next) {
                nl++; lastkey = key; lastfw = fw; next = port_frame_count + 240;
                port_log("[p121] menu frame %u: rec %08X fade %g titlePage %d menu %d mainPage %d input %04X | overlay D_800E0FC6 %u speed D_80090114 %u page alpha D_800E0EC4 %u\n", port_frame_count,
                         (unsigned)(uintptr_t)r, fade, (signed char)vbe_ld8(r + 0x2C), (signed char)vbe_ld8(r + 0x3E),
                         (signed char)vbe_ld8(r + 0x3F), vbe_ld16(r + 0x20),
                         vbe_ld8(&g_screen_fade_alpha), vbe_ld8(&g_menu_fade_speed), vbe_ld8(&g_menu_alpha));
                { /* camera 0: non-finite floats, target */
                    extern unsigned char *g_player_views; const unsigned *c = (const unsigned *)g_player_views; int o, bad = 0, first = -1;
                    if (memok(c))
                    for (o = 0; o < 0x9A0 / 4; o++) if (((c[o] >> 23) & 0xFF) == 0xFF) { bad++; if (first < 0) first = o * 4; }
                    port_log("[p121]   camera 0: %d non-finite words (first +%X) target +3D4 %08X +5F0 %08X +18C %08X %08X %08X\n",
                             bad, first, c[0x3D4 / 4], c[0x5F0 / 4],
                             c[0x18C / 4], c[0x190 / 4], c[0x194 / 4]);
                }
            }
        }
    }
    if (!flag(&fboot, "p103boot") || (m == lmode && l == llevel)) return;
    port_log("[p103] frame %u: mode %d (prev %d) level %X timer %d tv %d | objects %d events %u scene0 %u\n",
             port_frame_count, m, vbe_ld8(&g_game_mode_prev), l, g_game_mode_timer, D_80000300, g_world_obj_count, vbe_ld8(&D_800D2F3C),
             vbe_ld8(&D_800C35EA));
    lmode = m; llevel = l;
}

int __real_event_prereqs_met(int id);
int __wrap_event_prereqs_met(int id) {
    if (flag(&fev, "p103ev")) {
        int r = p103_prereq(id, 0);
        return r > 0;
    }
    return __real_event_prereqs_met(id);
}

void __real_event_start_level_events(int a0, int a1);
void __wrap_event_start_level_events(int a0, int a1) {
    if (flag(&fboot, "p103boot")) {
        int n = vbe_ld8(&D_800D2F3C), i;
        port_log("[p103] event_start_level_events(%d, %d) frame %u level %X mode %d: %d level events, save flags %08X\n", a0, a1,
                 port_frame_count, g_level_id, vbe_ld8(&g_game_mode), n, (unsigned)(uintptr_t)g_save_progress_bits);
        for (i = 0; i < n && i < 32 && memok(D_800D2F40); i++) {
            int id = (short)vbe_ld16(D_800D2F40 + 2 * i);
            const unsigned *r = (const unsigned *)(D_800877D0 + id * 0x14);
            const unsigned char *pl = (const unsigned char *)(uintptr_t)r[3];
            char pre[64]; int k, o = 0;
            for (k = 0; k < 6 && memok(pl); k++) {
                unsigned e = vbe_ld16(pl + 2 * k);
                o += snprintf(pre + o, sizeof pre - o, "%X ", e);
                if (e == 0xFFFF) break;
            }
            pre[o] = 0;
            port_log("[p103]   event %d: id %X rec %08X %08X %08X %08X %08X prereqs [%s] -> asm would answer %d\n", i, id,
                     r[0], r[1], r[2], r[3], r[4], pre, p103_prereq(id, 0));
        }
    }
    __real_event_start_level_events(a0, a1);
}

void *__real_event_start(int id, int a1);
void *__wrap_event_start(int id, int a1) {
    if (flag(&fboot, "p103boot"))
        port_log("[p103] event_start(%X, %d) frame %u (start event)\n", id, a1, port_frame_count);
    { /* P110 TEST ONLY ?p110noev=1: do not start events (= the pre-P106 asm stub, returns 0). Since port P106 the
       * LogoScreen event 0xC9 starts a 1416-frame scene on level 0x21; at its end object removal (stubs
       * obj_release_models / obj_forget_target) corrupts the heap. This keeps the old walk / death / 0x2C test path. */
        static int fnoev = -1;
        if (flag(&fnoev, "p110noev")) return 0;
    }
    { /* P178: the started event's struct (+0 = flags | id) */
        void *e = __real_event_start(id, a1);
        /* P185: the P178 ?p178evid test (event id put back) is gone: vbe.py aligns stack slots to 4 since P185 */
        if (flag(&fboot, "p103boot"))
            port_log("[p103]   -> e %08x unk0 %04x unk2 %04x w0 %08x\n", (unsigned)(uintptr_t)e, e ? vbe_ld16(e) : 0, e ? vbe_ld16((char *)e + 2) : 0, e ? *(unsigned *)e : 0);
        return e;
    }
}

void __real_cutscene_scene_load(int level, int scene, int slot, int cb, int cbarg);
void __wrap_cutscene_scene_load(int level, int scene, int slot, int cb, int cbarg) {
    if (flag(&fboot, "p103boot"))
        port_log("[p103] cutscene_scene_load(level %X, scene %d, slot %d, cb %d, %d) frame %u mode %d\n", level, scene, slot, cb,
                 cbarg, port_frame_count, vbe_ld8(&g_game_mode));
    { /* P123 TEST ONLY ?p123noscene=1: do not start the menu level's scene (mode 3), as when menu_mode_update was a stub */
        static int fns = -1;
        if (flag(&fns, "p123noscene") && vbe_ld8(&g_game_mode) == 3) { port_log("[p123] menu scene start skipped\n"); return; }
    }
    __real_cutscene_scene_load(level, scene, slot, cb, cbarg);
}

/* P113 DIAGNOSTIC: on a ?p113watch hit, list the words of the camera records g_player_views (struct108 *, 2 x 0x800+)
 * that point within +-0x400 of the watched address (a stale camera target into a freed block). */
extern unsigned char *g_player_views; /* was D_800DBFF0 */
extern void (*p113_watch_hook)(unsigned addr);
static void p113_cam_scan(unsigned a) {
    unsigned o;
    for (o = 0; o < 0x1000; o += 4) {
        unsigned v = *(const unsigned *)(g_player_views + o);
        if (v + 0x400 - a < 0x800) port_log("[p113w]   D_800DBFF0+%03X = %08X (ADDR%+d)\n", o, v, (int)(v - a));
    }
}

/* P113 OPT-IN emulation ?p113g84=1 (remove when obj_model_refs_release is game C): obj_model_refs_release (game_eu_AF2A0, asm stub) is the
 * part-reference release under the object removal chain obj_remove -> obj_release_models (C since port P112) ->
 * obj_model_refs_release_all (C). The stub left the object's part words +0x28C + j*8 set, the shared-block reference counts
 * D_800D1F80[slot] up and the private copies allocated, and the heap was corrupt right after the LogoScreen scene
 * end (frame 2133-2137). This wrap does what the asm does (EU asm read by hand, 0x60 bytes): for both words of
 * part j: word == D_800D19A0[slot] -> D_800D1F80[slot]--, else heap_set_block_tag(word, 3); then the word = 0.
 * Result: it is NOT the cause of the heap corruption (same corruption with it), so it is opt-in; default = the stub. */
extern unsigned D_800D19A0[];
extern unsigned char D_800D1F80[];
void heap_set_block_tag(int *p, unsigned tag);
void __real_obj_model_refs_release(unsigned char *obj, int j);
void __wrap_obj_model_refs_release(unsigned char *obj, int j) {
    static int fnog = -1, n;
    p113_watch_hook = p113_cam_scan; /* (set here: a constructor would pull game data into the scheduler demo) */
    unsigned *w = (unsigned *)(obj + 0x28C + j * 8);
    unsigned slot;
    int k;
    if (flag(&fboot, "p103boot") && n++ < 40)
        port_log("[p113] obj_model_refs_release(obj %08X, part %d) frame %u: words %08X %08X\n", (unsigned)(uintptr_t)obj, j,
                 port_frame_count, w[0], w[1]);
    if (!flag(&fnog, "p113g84")) { __real_obj_model_refs_release(obj, j); return; }
    if (w[0] == 0 && w[1] == 0) return;
    slot = (*(unsigned char **)(obj + 0x2C4))[j];
    for (k = 0; k < 2; k++) {
        if (w[k] == 0) continue;
        if (w[k] == D_800D19A0[slot]) D_800D1F80[slot]--;
        else heap_set_block_tag((int *)(uintptr_t)w[k], 3);
        w[k] = 0;
    }
}

/* P113 DIAGNOSTIC: checkpoints of the ?p113watch write watch (pc_sched.c) around the calls of world_update between its
 * heap_age_tagged_blocks and node_lists_run_update, to find the stale writer after the LogoScreen scene end (pass-through wraps). */
void p113_watch(const char *where);
#define P113W0(f) void __real_##f(void); void __wrap_##f(void) { p113_watch(#f " in"); __real_##f(); p113_watch(#f " out"); }
#define P113W1(f) void __real_##f(int); void __wrap_##f(int a) { p113_watch(#f " in"); __real_##f(a); p113_watch(#f " out"); }
#define P113W2(f) void __real_##f(int, int); void __wrap_##f(int a, int b) { p113_watch(#f " in"); __real_##f(a, b); p113_watch(#f " out"); }
P113W0(reflect_queue_reset)
P113W0(camera_matrices_refresh_all)
P113W1(collision_select_area)
P113W0(world_records_flag_active)
P113W0(timedfx_update_all)
/* P116: scene_event_track_pass also logs, when slot 0's +0x65 (parent) changed during the call, the scene events it queued in
 * D_800C4170 ({event ptr, time << 8, s8 track, s16 index}, 0xC bytes) this frame (first 8 entries). */
void __real_scene_event_track_pass(int, int);
void __wrap_scene_event_track_pass(int a, int b) {
    extern unsigned char g_objects[];
    extern unsigned char *D_800C4170;
    static unsigned nlog;
    unsigned before = vbe_ld8(g_objects + 0x65), after;
    p113_watch("scene_event_track_pass in");
    __real_scene_event_track_pass(a, b); /* (P121: the P116 test-only ?p116walk copy is gone: the game C has the fix since P117) */
    p113_watch("scene_event_track_pass out");
    { /* P121 (?p103boot): log queued events of the scene's last track (13: camera switch 3/0xD, exit 5/0x67) and any
       * type-3 / 5-0x67 event, first 24 hits */
        static int fb = -1; static unsigned n121; static const unsigned char *lastev;
        int i;
        if (flag(&fb, "p103boot") && D_800C4170)
            for (i = 0; i < 16 && n121 < 24; i++) {
                const unsigned char *e = D_800C4170 + i * 0xC;
                const unsigned char *ev;
                if (!memok(e)) break; /* P154 */
                ev = (const unsigned char *)(uintptr_t)*(const unsigned *)e;
                int tr = (signed char)vbe_ld8(e + 8);
                if (!memok(ev)) break;
                if (ev == lastev) continue;
                if (tr == 13 || (vbe_ld8(ev) == 3 && vbe_ld16(ev + 2) == 0xD) || (vbe_ld8(ev) == 5 && vbe_ld16(ev + 2) == 0x67)) {
                    lastev = ev; n121++;
                    port_log("[p121] walker(%d, %d) frame %u queued ev %08X time %d track %d: type %02X id %04X b4 %d b5 %d w6 %d\n",
                             a, b, port_frame_count, (unsigned)(uintptr_t)ev, *(const int *)(e + 4) >> 8, tr, vbe_ld8(ev),
                             vbe_ld16(ev + 2), (signed char)vbe_ld8(ev + 4), (signed char)vbe_ld8(ev + 5), (short)vbe_ld16(ev + 6));
                }
            }
    }
    after = vbe_ld8(g_objects + 0x65);
    if (after != before && nlog++ < 8) {
        int i;
        port_log("[p116] slot 0 +0x65 %02X -> %02X in scene_event_track_pass(%d, %d) frame %u; queue:\n", before, after, a, b,
                 port_frame_count);
        if (nlog == 1) { /* the slot-0 scene tables: event track i -> events pointer / count, and its ref entry */
            extern int D_800C3AA8[][30]; extern unsigned short *D_800C39F8[]; extern unsigned char *D_800C3A10[];
            extern unsigned char D_800C3A5A[];
            int n = vbe_ld8(D_800C3A5A);
            for (i = 0; i < n && i < 30; i++) {
                const unsigned char *rf = D_800C3A10[0] + i * 8;
                /* P199: bounds-safe (frame 17820, level 6 scene 20: a stale table pointer read out of bounds) */
                int nev = memok(D_800C39F8[0] + i) ? vbe_ld16(&D_800C39F8[0][i]) : -1;
                port_log("[p116]   track %d: events %08X n %d | ref kind %d id %d\n", i, (unsigned)D_800C3AA8[0][i],
                         nev, memok(rf) ? vbe_ld16(rf) : -1, memok(rf) ? vbe_ld8(rf + 2) : -1);
            }
        }
        for (i = 0; i < 8 && D_800C4170; i++) {
            const unsigned char *e = D_800C4170 + i * 0xC;
            const unsigned char *ev;
            if (!memok(e)) break; /* P199 */
            ev = (const unsigned char *)(uintptr_t)*(const unsigned *)e;
            if (!memok(ev)) break;
            port_log("[p116]   ev %08X time %d track %d idx %d: type %02X delta %02X id %04X b4 %d b5 %d w6 %d\n",
                     (unsigned)(uintptr_t)ev, *(const int *)(e + 4) >> 8, (signed char)vbe_ld8(e + 8), (short)vbe_ld16(e + 0xA),
                     vbe_ld8(ev), vbe_ld8(ev + 1), vbe_ld16(ev + 2), (signed char)vbe_ld8(ev + 4), (signed char)vbe_ld8(ev + 5),
                     (short)vbe_ld16(ev + 6));
        }
    }
}
P113W1(cutscene_camera_track_pass)
P113W1(cutscene_apply_cameras)
P113W1(cutscene_check_finished)
P113W0(camera_update_all)
P113W0(objects_update_tank_views)
P113W1(player_zone_update)
P113W2(level_update_frame)
P113W0(frame_hook_nop_1501c860)
P113W1(frame_hook_nop_1511fc20)
P113W1(afterimage_list_update)
P113W0(objects_update_blob_shadows)
P113W0(world_records_update_shadows)
P113W1(fog_apply_level_default)

/* P113 guard REMOVED in P137: after the LogoScreen scene on level 0x21 (frame 2133) and the menu scene end (3053) the
 * object removal obj_remove used to leave camera record g_player_views[i] (struct108, 0x9A0 bytes) with the freed +0x31C
 * record as its target unk3D4, and the guard re-pointed it at a zeroed parking record. Since the scene VM / walker
 * fixes (P117) and the P127..P133 conversions the case no longer occurs: P137 runs (4 new-game Chrome runs incl.
 * ?p113noguard=1, node new game, noev walks) had 0 guard / NO GUARD lines. Kept as a check only: a stale target is
 * logged ("[p113] STALE camera target"), never patched. */
extern int g_last_player_index; /* was D_80082FA0 */
void __real_obj_remove(unsigned char *obj, int mode);
void __wrap_obj_remove(unsigned char *obj, int mode) {
    static int n;
    unsigned rec = *(unsigned *)(obj + 0x31C);
    int i;
    __real_obj_remove(obj, mode);
    if (rec == 0) return;
    for (i = 0; i <= g_last_player_index && i < 4; i++) {
        unsigned *t = (unsigned *)(g_player_views + i * 0x9A0 + 0x3D4);
        if (*t == rec && n++ < 16)
            port_log("[p113] STALE camera target: camera %d target %08X freed with object %08X (mode %d) frame %u\n", i, rec,
                     (unsigned)(uintptr_t)obj, mode, port_frame_count);
    }
}

/* P116 (?p103boot): log every setup command list run (obj_setup_run, called from scene handler A scene_event_run_a for
 * type 0xD b4 0 and from other TUs): owner slot, list n, result. */
int __real_obj_setup_run(void *obj, int n, float f, int a3);
int __wrap_obj_setup_run(void *obj, int n, float f, int a3) {
    static unsigned cnt;
    extern unsigned char g_objects[];
    { static int f131 = -1; if (f131 < 0) f131 = port_flag("p131mdl"); /* P131: also log before the call (a trap inside never returns) */
      if (f131 > 0 && port_frame_count >= (f131 > 1 ? (unsigned)f131 : 4400u)) port_log("[p131] obj_setup_run enter obj %08X list %d frame %u\n", (unsigned)(uintptr_t)obj, n, port_frame_count); }
    int r = __real_obj_setup_run(obj, n, f, a3);
    if (flag(&fboot, "p103boot") && cnt++ < 60) {
        long so = ((unsigned char *)obj - g_objects), sr = ((unsigned char *)(uintptr_t)(unsigned)r - g_objects);
        port_log("[p116] obj_setup_run(obj %08X slot %ld, list %d, %g, %d) frame %u -> %08X slot %ld (+65 %02X)\n",
                 (unsigned)(uintptr_t)obj, so / 0x32C, n, f, a3, port_frame_count, (unsigned)r, sr / 0x32C,
                 r ? vbe_ld8((unsigned char *)(uintptr_t)(unsigned)r + 0x65) : 0);
    }
    return r;
}

/* P116 (?p116find=1): log the object lookups by setup id of the scene handlers (obj_find_by_setup_id / obj_slot_by_setup_id, called
 * from game_eu_51190.c): id -> slot, first 80 calls whose answer changes per id. */
void *__real_obj_find_by_setup_id(unsigned char id);
int __real_obj_slot_by_setup_id(unsigned char id);
static int ffind = -1;
static void p116_find_log(const char *fn, unsigned id, long slot) {
    static long last[256]; static int init; static unsigned n;
    if (!init) { int i; for (i = 0; i < 256; i++) last[i] = -1000; init = 1; }
    if (!flag(&ffind, "p116find") || n >= 80 || last[id & 0xFF] == slot) return;
    last[id & 0xFF] = slot; n++;
    port_log("[p116] %s(%u) frame %u -> slot %ld\n", fn, id, port_frame_count, slot);
}
void *__wrap_obj_find_by_setup_id(unsigned char id) {
    extern unsigned char g_objects[];
    void *r = __real_obj_find_by_setup_id(id);
    p116_find_log("obj_find_by_setup_id", id, r ? ((unsigned char *)r - g_objects) / 0x32C : -1);
    return r;
}
int __wrap_obj_slot_by_setup_id(unsigned char id) {
    int r = __real_obj_slot_by_setup_id(id);
    p116_find_log("obj_slot_by_setup_id", id, r);
    return r;
}

/* P121 (?p103boot): log the scene-end menu request (menu_reset_and_enter, from scene handler A event 5/0x67). */
void __real_menu_reset_and_enter(void);
void __wrap_menu_reset_and_enter(void) {
    static int fb = -1;
    if (flag(&fb, "p103boot")) port_log("[p121] menu_reset_and_enter (5/0x67 menu request) frame %u\n", port_frame_count);
    __real_menu_reset_and_enter();
}

/* P121 TEST ONLY ?p121spr=1: run the copy of menu_sprites_load without the KSEG0 OR (port/boot/p69_pcold.c). */
void __real_menu_sprites_load(void);
void __wrap_menu_sprites_load(void) {
    static int fs = -1;
    void p121_sprites_fixed(void);
    if (flag(&fs, "p121spr")) p121_sprites_fixed(); else __real_menu_sprites_load();
}

/* P123 DIAGNOSTIC ?p123fade=1: every screen-colour/fade request screen_fade_start(r, g, b, frames, dir, player) with the
 * frame and the JS stack, and (from p103_frame, mode 3 and every 120 frames) the world-render gates of
 * render_player_frame_setup / render_player_scene: g_game_paused, g_scene_render_suspend, screen_fade_is_opaque(0) (fade level 0xFF = skip), D_800D18A0. */
void p123_requests_stack(void);
void __real_screen_fade_start(int r, int g, int b, int n, int dir, int pl);
void __wrap_screen_fade_start(int r, int g, int b, int n, int dir, int pl) {
    static int ff = -1, nl;
    if (flag(&ff, "p123fade") && nl++ < 80) {
        void port_js_stack(int skip, int n);
        port_log("[p123] screen_fade_start(rgb %d %d %d, frames %d, dir %d, player %d) frame %u mode %d\n", r, g, b, n,
                 (signed char)dir, pl, port_frame_count, vbe_ld8(&g_game_mode));
        port_js_stack(1, 4);
    }
    __real_screen_fade_start(r, g, b, n, dir, pl);
}
void p123_gates(void) {
    static int ff = -1; static unsigned next;
    extern unsigned char g_game_paused, g_screen_fade_dir, g_screen_fade_alpha_override[]; extern int g_scene_render_suspend; extern unsigned short D_800D18A0;
    extern int g_screen_fade_timer, g_screen_fade_duration; int screen_fade_alpha(int);
    if (!flag(&ff, "p123fade") || port_frame_count < next) return;
    next = port_frame_count + 120;
    port_log("[p123] gates frame %u mode %d level %X: D_800BEAC0 %u D_80084810 %d D_800D18A0 %X | fade level %d (dir %d timer %d/%d forced %u)\n",
             port_frame_count, vbe_ld8(&g_game_mode), g_level_id, vbe_ld8(&g_game_paused), g_scene_render_suspend, vbe_ld16(&D_800D18A0),
             screen_fade_alpha(0), (signed char)vbe_ld8(&g_screen_fade_dir), g_screen_fade_timer, g_screen_fade_duration, vbe_ld8(&g_screen_fade_alpha_override[0]));
}


/* P123 ?p123fadeev (TEST-ONLY wrap of handler C scene_event_run_c, 5/1 fade branch) removed in P126: port P124 converted
 * scene_event_run_c to C and the menu fades in by itself. */

/* P131 (?p131mdl=1 or =FRAME, DIAGNOSTIC): log texture_resolve_dl_ids's display lists from frame 4400 (or FRAME) on (asset 9 models of the new
 * game's level 0x18 trapped in it): dl, outList slot, first words, and how far the walk to G_ENDDL stays inside
 * the wasm memory. */
int __real_texture_resolve_dl_ids(void *dl, int skip, int addRef, int age, void *outList);
int __wrap_texture_resolve_dl_ids(void *dl, int skip, int addRef, int age, void *outList) {
    static int f = -1; static unsigned n;
    extern unsigned char g_shared_dl_tex_lists[];
    if (f < 0) f = port_flag("p131mdl");
    if (f > 0 && port_frame_count >= (f > 1 ? (unsigned)f : 4400u) && n < 200) {
        unsigned lim = (unsigned)__builtin_wasm_memory_size(0) * 65536u, a = (unsigned)(uintptr_t)dl, k = 0, end = 0;
        n++;
        if (a >= 0x1000 && a + 8 <= lim) {
            for (k = 0; a + 8 * k + 8 <= lim && k < 0x100000; k++)
                if ((((uint32_t *)dl)[2 * k] >> 24) == 0xDF) { end = 1; break; }
        }
        port_log("[p131] texture_resolve_dl_ids #%u frame %u: dl %08X (mem %08X) out %08X (idx %ld) age %X | w %08X %08X | %s after %u cmds\n",
                 n, port_frame_count, a, lim, (unsigned)(uintptr_t)outList,
                 outList ? (long)(((unsigned char *)outList - g_shared_dl_tex_lists) / 4) : -1L, age,
                 (a >= 0x1000 && a + 8 <= lim) ? ((uint32_t *)dl)[0] : 0, (a >= 0x1000 && a + 8 <= lim) ? ((uint32_t *)dl)[1] : 0,
                 end ? "ENDDL" : "NO-END/OUT", k);
    }
    return __real_texture_resolve_dl_ids(dl, skip, addRef, age, outList);
}

/* P131 (?p131mdl, DIAGNOSTIC): asset loads of type 9 (models) from the same start frame: index, header, header words
 * 0..4 and the first two words at header[0] (table of DL offsets for model_asset9_load_refcounted, a DL for shared_dl_acquire). The
 * loader is variadic: forward up to 4 extra arguments (arg3 = their count). */
#include <stdarg.h>
int __real_asset_load_with_subfiles(int *a0, int a1, int *a2, int a3, ...);
int __wrap_asset_load_with_subfiles(int *a0, int a1, int *a2, int a3, ...) {
    static int f = -1; static unsigned n;
    int v[4] = {0, 0, 0, 0}, r, k;
    va_list ap;
    va_start(ap, a3);
    for (k = 0; k < a3 && k < 4; k++) v[k] = va_arg(ap, int);
    va_end(ap);
    switch (a3) {
    case 0: r = __real_asset_load_with_subfiles(a0, a1, a2, a3); break;
    case 1: r = __real_asset_load_with_subfiles(a0, a1, a2, a3, v[0]); break;
    case 2: r = __real_asset_load_with_subfiles(a0, a1, a2, a3, v[0], v[1]); break;
    case 3: r = __real_asset_load_with_subfiles(a0, a1, a2, a3, v[0], v[1], v[2]); break;
    default: r = __real_asset_load_with_subfiles(a0, a1, a2, a3, v[0], v[1], v[2], v[3]); break;
    }
    if (f < 0) f = port_flag("p131mdl");
    if (f > 0 && a3 == 2 && v[0] == 9 && port_frame_count >= (f > 1 ? (unsigned)f : 4400u) && n < 100) {
        uint32_t *h = (uint32_t *)(uintptr_t)(unsigned)r;
        n++;
        if (h) {
            uint32_t t = h[0];
            int ok = t >= (unsigned)r && t < (unsigned)r + 0x100000;
            port_log("[p131] asset(9, %d) frame %u -> %08X: hdr %08X %08X %08X %08X %08X | at hdr[0]: %08X %08X\n", v[1], port_frame_count,
                     (unsigned)r, h[0], h[1], h[2], h[3], h[4], ok ? ((uint32_t *)(uintptr_t)t)[0] : 0, ok ? ((uint32_t *)(uintptr_t)t)[1] : 0);
        } else
            port_log("[p131] asset(9, %d) frame %u -> 0\n", v[1], port_frame_count);
    }
    return r;
}

/* P131 (?p131mdl, DIAGNOSTIC): level-setup entry spawns (setup_entry_spawn, 0x30-byte entries of D_800D20FC): idx and the
 * whole entry (+0x28 setup id, +0x29 setup command list), from the same start frame. */
int __real_setup_entry_spawn(unsigned char *e, int idx, int a2, int a3, int reuse);
int __wrap_setup_entry_spawn(unsigned char *e, int idx, int a2, int a3, int reuse) {
    static int f = -1; static unsigned n;
    extern unsigned char D_800D20FC[];
    if (f < 0) f = port_flag("p131mdl");
    if (f > 0 && port_frame_count >= (f > 1 ? (unsigned)f : 4400u) && n < 60) {
        char hex[0x30 * 2 + 1]; int k;
        n++;
        for (k = 0; k < 0x30; k++) snprintf(hex + 2 * k, 3, "%02X", vbe_ld8(e + k));
        port_log("[p131] setup_entry_spawn e %08X (entry %ld) idx %d a3 %d frame %u: %s\n", (unsigned)(uintptr_t)e,
                 (long)(e - D_800D20FC) / 0x30, idx, a3, port_frame_count, hex);
    }
    return __real_setup_entry_spawn(e, idx, a2, a3, reuse);
}

/* P131 (?p131mdl, DIAGNOSTIC): the level-setup asset load (asset_load_into(dst, 0, 2, 0xE, level), game_eu_44010.c):
 * size and the first entry it wrote (entry 5 of D_800D20FC on level 0x18), logged at load time (any frame). */
int __real_asset_load_into(int a0, int a1, int a2, ...);
int __wrap_asset_load_into(int a0, int a1, int a2, ...) {
    static int f = -1;
    int v[4] = {0, 0, 0, 0}, r, k;
    va_list ap;
    va_start(ap, a2);
    for (k = 0; k < a2 && k < 4; k++) v[k] = va_arg(ap, int);
    va_end(ap);
    switch (a2) {
    case 0: r = __real_asset_load_into(a0, a1, a2); break;
    case 1: r = __real_asset_load_into(a0, a1, a2, v[0]); break;
    case 2: r = __real_asset_load_into(a0, a1, a2, v[0], v[1]); break;
    case 3: r = __real_asset_load_into(a0, a1, a2, v[0], v[1], v[2]); break;
    default: r = __real_asset_load_into(a0, a1, a2, v[0], v[1], v[2], v[3]); break;
    }
    if (f < 0) f = port_flag("p131mdl");
    if (f > 0 && a2 == 2 && v[0] == 0xE) {
        char hex[0x30 * 2 + 1]; unsigned char *e = (unsigned char *)(uintptr_t)(unsigned)a0;
        for (k = 0; k < 0x30; k++) snprintf(hex + 2 * k, 3, "%02X", vbe_ld8(e + k));
        port_log("[p131] setup asset (2, E, %X) frame %u -> dst %08X size %X: %s\n", v[1], port_frame_count, (unsigned)a0, (unsigned)r, hex);
    }
    return r;
}
