/* P84 runtime checks after merging port-b P68 / P73 / P77 / P82.
 *  ?p84text=N      func_151E5928 (per game mode text bank choice, game_eu_20B730.c, called from game_45B80.c) ->
 *                  func_151E7110 (text bank loader, P68 C): language D_800E101A / D_800BEECB, loaded bank D_800E1003,
 *                  bank D_800E1004, string table D_800E1008, bank-1 extras D_80090178 / D_800E0FB8 when they change
 *                  (first N changes).
 *  DIAGNOSTIC ?p84notext=1  func_151E5928 does nothing (the pre-merge asm stub behaviour): bisects the text bank load. */
#include <stdint.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern unsigned char D_800E101A_[] __asm__("D_800E101A");
extern unsigned char D_800BEECB_[] __asm__("D_800BEECB");
extern unsigned char D_800E1003_[] __asm__("D_800E1003");
extern unsigned char D_800E1004_[] __asm__("D_800E1004");
extern unsigned char D_800E1008_[] __asm__("D_800E1008");
extern unsigned char D_80090178_[] __asm__("D_80090178");
extern unsigned char D_800E0FB8_[] __asm__("D_800E0FB8");

extern unsigned char p88_D_800C35EA[] __asm__("D_800C35EA");
extern unsigned char p88_D_800C39D0[] __asm__("D_800C39D0");
extern unsigned char p88_D_eu_800C3A60[] __asm__("D_eu_800C3A60");
static int flag(int *f, const char *n) { if (*f < 0) *f = port_flag(n); return *f; }
static unsigned B(const unsigned char *p) { return *(const unsigned char *)((uintptr_t)p ^ 3); } /* virtual BE byte */
static unsigned W(const unsigned char *p) { return *(const unsigned *)p; }
static int ftext = -1, fnotext = -1;

void __real_func_151E5928(void);
void __wrap_func_151E5928(void) {
    static unsigned last[6], n;
    unsigned cur[6];
    int i, changed = 0;
    void p84_frame(void);
    void p84_hang_init(void);
    void p88_watch_init(void);
    p84_hang_init();
    p88_watch_init();
    p84_frame();
    if (flag(&fnotext, "p84notext")) return;
    __real_func_151E5928();
    if (!flag(&ftext, "p84text")) return;
    cur[0] = B(D_800E101A_) | B(D_800BEECB_) << 8 | B(D_800E1003_) << 16;
    cur[1] = W(D_800E1004_); cur[2] = W(D_800E1008_); cur[3] = W(D_80090178_); cur[4] = W(D_800E0FB8_);
    for (i = 0; i < 5; i++) changed |= cur[i] != last[i];
    if (!changed || n >= (unsigned)ftext) return;
    n++;
    for (i = 0; i < 5; i++) last[i] = cur[i];
    port_log("[p84] text frame %u: lang %u loaded-lang %u bank %u | D_800E1004 %08X D_800E1008 %08X D_80090178 %08X "
             "D_800E0FB8 %08X\n", port_frame_count, cur[0] & 0xFF, cur[0] >> 8 & 0xFF, cur[0] >> 16 & 0xFF, cur[1],
             cur[2], cur[3], cur[4]);
    if (cur[1] >= 0x10000000u && cur[2] >= 0x10000000u) {
        const unsigned char *s = (const unsigned char *)(uintptr_t)W((const unsigned char *)(uintptr_t)cur[2]);
        char buf[33];
        for (i = 0; i < 32; i++) { unsigned c = B(s + i); buf[i] = (c >= 32 && c < 127) ? (char)c : '.'; }
        buf[32] = 0;
        port_log("[p84]   string 0 at %08X: \"%s\"\n", (unsigned)(uintptr_t)s, buf);
    }
}

/* ?p84lang=N: watch the language byte D_800E101A at every asm-stub hit (port_stub_trace_hook; don't combine with
 * ?p69watch / ?p49walk) and at each func_151E5928 call; log the first N changes with the last stub and the JS stack. */
extern void (*port_stub_trace_hook)(const char *name);
void port_js_stack(int skip, int n);
static int flang = -1;
static const char *l_last = "-";
static unsigned l_val, l_n;
static void lang_watch(const char *where) {
    unsigned v = B(D_800E101A_);
    if (v != l_val && l_n < (unsigned)flang) {
        l_n++;
        port_log("[p84] lang D_800E101A frame %u at %s (last stub %s): %u -> %u\n", port_frame_count, where, l_last,
                 l_val, v);
        port_js_stack(1, 10);
    }
    l_val = v;
}
static void lang_hook(const char *name) { lang_watch("stub"); l_last = name; }
/* P88 ?p88scene=N: scene slots 0 / 1 (state D_800C35EA[slot], counter D_800C39D0[slot], length D_eu_800C3A60[slot],
 * func_1501CE34 C since the P83 merge) and the language byte, logged when the state or length changes (first N). */
extern unsigned char p88_D_800C35EA[] __asm__("D_800C35EA");
extern unsigned char p88_D_800C39D0[] __asm__("D_800C39D0");
extern unsigned char p88_D_eu_800C3A60[] __asm__("D_eu_800C3A60");
/* P88 ?p88pos=N: every N frames from frame 940 to 1300, player record 0 (D_800CC2D0, 0x32C bytes) state / position and
 * the slot 0 scene state / counter. */
extern unsigned char p88_D_800CC2D0[] __asm__("D_800CC2D0");
static void p88_pos(void) {
    static int f = -1;
    static unsigned last;
    const unsigned char *r = p88_D_800CC2D0;
    if (flag(&f, "p88pos") == 0 || port_frame_count < 940 || port_frame_count > 3000 || port_frame_count - last < (unsigned)f) return;
    last = port_frame_count;
    port_log("[p88] pos frame %u: player state %d pos %.1f %.1f %.1f | scene state %u counter %d\n", port_frame_count,
             (int)W(r), *(const float *)(r + 0x14), *(const float *)(r + 0x18), *(const float *)(r + 0x1C),
             B(p88_D_800C35EA), (int)W(p88_D_800C39D0));
}
static void p88_scene(void) {
    static int f = -1;
    p88_pos();
    static unsigned last[4], n;
    unsigned cur[4];
    if (flag(&f, "p88scene") == 0 || n >= (unsigned)f) return;
    cur[0] = B(p88_D_800C35EA) | B(p88_D_800C35EA + 1) << 8; cur[1] = W(p88_D_eu_800C3A60);
    cur[2] = W(p88_D_eu_800C3A60 + 4); cur[3] = B(D_800E101A_);
    if (cur[0] == last[0] && cur[1] == last[1] && cur[2] == last[2] && cur[3] == last[3]) return;
    n++; last[0] = cur[0]; last[1] = cur[1]; last[2] = cur[2]; last[3] = cur[3];
    port_log("[p88] scene frame %u: state %u/%u counter %d/%d length %d/%d lang %u\n", port_frame_count, cur[0] & 0xFF,
             cur[0] >> 8, (int)W(p88_D_800C39D0), (int)W(p88_D_800C39D0 + 4), (int)cur[1], (int)cur[2], cur[3]);
}
void p84_frame(void) {
    if (flang < 0) { flang = port_flag("p84lang"); if (flang) port_stub_trace_hook = lang_hook; }
    if (flang) lang_watch("text");
    p88_scene();
}

/* ?p84hang=N: hang finder. At every asm-stub hit (port_stub_trace_hook; don't combine with ?p84lang / ?p69watch /
 * ?p49walk): when port_frame_count has not moved for 3 s of wall time, log the stub and the JS stack (N times, 3 s
 * apart). Installed from main via p84_hang_init (called by the func_151E5928 wrap on its first call). */
#include <emscripten.h>
static int fhang = -1;
static unsigned h_frame, h_n, h_hits;
static double h_t0, h_last;
static void hang_hook(const char *name) {
    double t = emscripten_get_now();
    h_hits++;
    if (port_frame_count != h_frame) { h_frame = port_frame_count; h_t0 = t; h_hits = 0; return; }
    if (t - h_t0 > 3000 && t - h_last > 3000 && h_n < (unsigned)fhang) {
        h_n++; h_last = t;
        port_log("[p84] hang? frame %u unchanged for %.0f ms, %u stub hits since; now in stub %s\n", h_frame, t - h_t0,
                 h_hits, name);
        port_js_stack(1, 14);
    }
}
void p84_hang_init(void) {
    if (fhang < 0) { fhang = port_flag("p84hang"); if (fhang) port_stub_trace_hook = hang_hook; }
}

/* P88: the TEMPORARY __wrap_func_1501E364 guard (P84, scene length 0) was removed: the port-b branch converted the
 * scene length func_1501CE34 in P83 (game_eu_4A070.c, NON_MATCHING). */

/* P88 TEMPORARY guard (remove when the port-b branch converts func_1501E888, game_eu_4A070.c, GLOBAL_ASM, 133 insns,
 * "scene end"): with func_1501CE34 now C the level 0 scene has a real length (250), func_1501E46C clamps the counter
 * to it, and func_1501E364 then loops "while state == 1 && counter >= length: func_1501E888(0, slot)". The asm
 * func_1501E888 ends the scene: it stores 0 into the state byte D_800C35EA[slot] (2 when a chained scene
 * D_800C39E2 != 0 is started through func_1501D348), sets the counter to D_800C40AE, D_800C39D8[slot] = -100, and calls
 * func_15169040 / 1501D2C4 / 1501E7A8 / 1502348C / 15023684 / 1501EA84 / 1501E5AC / 1510B8AC. As a stub it changes
 * nothing, so the loop never ends (V8 profile, P88: 100 % in func_1501E364 -> stubs func_1501E888 / 1501ECA4 /
 * 15020F6C / 1501E0C8, at frame ~1220). The guard only does the state store of the non-chained path, at the one
 * call site that hangs, so func_1501E364 ends, plus its store of 0 into the cutscene flag D_800C3638 (while it is
 * set, object updates are skipped and the player stays frozen after the scene); nothing else of the scene end happens. ?p88noguard=1 turns it off. */
int func_1501E888(int a0, int slot); /* the asm stub is (i32, i32) -> i32 */
void __real_func_1501E364(int slot);
void __wrap_func_1501E364(int slot) {
    static int fno = -1;
    static unsigned n;
    extern unsigned char p88_D_800C40AC[] __asm__("D_800C40AC");
    unsigned char *st = (unsigned char *)((uintptr_t)(p88_D_800C35EA + slot) ^ 3);
    int len = (int)W(p88_D_eu_800C3A60 + slot * 4), cnt = (int)W(p88_D_800C39D0 + slot * 4);
    if (!flag(&fno, "p88noguard") && *st == 1 && cnt >= len && B(p88_D_800C40AC) == 0) {
        func_1501E888(0, slot);
        if (*st == 1) {
            extern unsigned char p88_D_800C3638[] __asm__("D_800C3638");
            *st = 0;
            *(unsigned char *)((uintptr_t)p88_D_800C3638 ^ 3) = 0; /* the cutscene flag (objects frozen while set) */
            if (n++ < 8) port_log("[p88] guard: scene end of slot %d at frame %u (counter %d, length %d): func_1501E888 "
                                  "is a stub, state 1 -> 0\n", slot, port_frame_count, cnt, len);
        }
    }
    __real_func_1501E364(slot);
}

/* P88 ?p88watch=N: from frame 960 watch player record 0 position (+0x14 / +0x18 / +0x1C) at every asm-stub hit
 * (port_stub_trace_hook; don't combine with ?p84lang / ?p84hang / ?p69watch / ?p49walk); log the first N changes with
 * the previous stub, the current stub and the JS stack. Installed from p88_watch_init (func_151E5928 wrap). */
static int fwatch = -1;
static unsigned w_val[3], w_n;
static const char *w_last = "-";
static void watch_hook(const char *name) {
    const unsigned char *r = p88_D_800CC2D0;
    unsigned v[3];
    if (port_frame_count >= 960 && w_n < (unsigned)fwatch) {
        v[0] = W(r + 0x14); v[1] = W(r + 0x18); v[2] = W(r + 0x1C);
        if (v[0] != w_val[0] || v[1] != w_val[1] || v[2] != w_val[2]) {
            w_n++;
            port_log("[p88] watch frame %u: player pos %08X %08X %08X -> %08X %08X %08X between stub %s and stub %s\n",
                     port_frame_count, w_val[0], w_val[1], w_val[2], v[0], v[1], v[2], w_last, name);
            port_js_stack(1, 12);
        }
        w_val[0] = v[0]; w_val[1] = v[1]; w_val[2] = v[2];
    }
    w_last = name;
}
void p88_watch_init(void) {
    if (fwatch < 0) { fwatch = port_flag("p88watch"); if (fwatch) port_stub_trace_hook = watch_hook; }
}

/* P88 TEMPORARY guard (remove when the port-b branch converts func_1501ECA4, game_eu_4A070.c, GLOBAL_ASM, 779 lines,
 * "scene step": interpolates the actor keys into the per-actor frame blocks D_800C3958[slot] + i * 0x44).
 * The scene loader func_1501D348 (P73 C) allocates those blocks without clearing them; func_1501ECA4 (stub) never
 * fills them, then the C actor pass func_150225D0 (P83) -> func_15021834 copies the block into the actor's object:
 * at the checkpoint restart scene (func_1507DFE4 -> func_1501D348) the player record 0 goes from the checkpoint
 * (348, 0, -2284) to (0, -7.69e11 = 0xD3330000, 49.25) (?p88watch), and the player is killed again when the scene
 * ends (func_1507D4F8 life lost every 256 frames). The guard snapshots the 26 object records D_800CC2D0[0..25]
 * (0x32C bytes each) and restores every record whose position (+0x14 / +0x18 / +0x1C) the call changed.
 * ?p88noactor=1 turns it off. */
#include <string.h>
#define P88_RECS 26
#define P88_REC 0x32C
void __real_func_1501D348(int level, int scene, int slot, int cb, int cbarg);
void __wrap_func_1501D348(int level, int scene, int slot, int cb, int cbarg) {
    static int fno = -1;
    static unsigned n;
    static unsigned char save[P88_RECS * P88_REC];
    int i;
    if (flag(&fno, "p88noactor")) { __real_func_1501D348(level, scene, slot, cb, cbarg); return; }
    memcpy(save, p88_D_800CC2D0, sizeof save);
    __real_func_1501D348(level, scene, slot, cb, cbarg);
    for (i = 0; i < P88_RECS; i++) {
        unsigned char *r = p88_D_800CC2D0 + i * P88_REC;
        const unsigned char *o = save + i * P88_REC;
        if (memcmp(r + 0x14, o + 0x14, 12) == 0) continue;
        if (n++ < 8) port_log("[p88] actor guard: func_1501D348(level %d, scene %d, slot %d) at frame %u moved record %d "
                              "to %08X %08X %08X from uninitialised D_800C3958 (func_1501ECA4 is a stub): restored\n",
                              level, scene, slot, port_frame_count, i, W(r + 0x14), W(r + 0x18), W(r + 0x1C));
        memcpy(r, o, P88_REC);
    }
}
