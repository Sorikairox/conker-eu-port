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
extern unsigned char p91_D_800C3638[] __asm__("D_800C3638"); /* P91: cutscene flag (objects frozen while set), logged too */
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
    { void p103_frame(void); p103_frame(); } /* P103 ?p103boot */
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
    port_log("[p88] pos frame %u: player state %d pos %.1f %.1f %.1f | scene state %u counter %d cutscene %u\n", port_frame_count,
             (int)W(r), *(const float *)(r + 0x14), *(const float *)(r + 0x18), *(const float *)(r + 0x1C),
             B(p88_D_800C35EA), (int)W(p88_D_800C39D0), B(p91_D_800C3638));
}
static void p88_scene(void) {
    static int f = -1;
    p88_pos();
    static unsigned last[4], n;
    unsigned cur[4];
    if (flag(&f, "p88scene") == 0 || n >= (unsigned)f) return;
    cur[0] = B(p88_D_800C35EA) | B(p88_D_800C35EA + 1) << 8; cur[1] = W(p88_D_eu_800C3A60);
    cur[2] = W(p88_D_eu_800C3A60 + 4); cur[3] = B(D_800E101A_) | B(p91_D_800C3638) << 8;
    if (cur[0] == last[0] && cur[1] == last[1] && cur[2] == last[2] && cur[3] == last[3]) return;
    n++; last[0] = cur[0]; last[1] = cur[1]; last[2] = cur[2]; last[3] = cur[3];
    port_log("[p88] scene frame %u: state %u/%u counter %d/%d length %d/%d lang %u cutscene %u\n", port_frame_count, cur[0] & 0xFF,
             cur[0] >> 8, (int)W(p88_D_800C39D0), (int)W(p88_D_800C39D0 + 4), (int)cur[1], (int)cur[2], cur[3] & 0xFF, cur[3] >> 8);
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

/* P91: the P88 TEMPORARY guard __wrap_func_1501E364 (scene end: state + cutscene flag D_800C3638) was removed: the
 * port-b branch converted func_1501E888 in P87 (game_eu_4A070.c, NON_MATCHING). */

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

/* P91: the P88 TEMPORARY guard __wrap_func_1501D348 (restore of object records moved from uninitialised
 * D_800C3958 blocks) was removed: the port-b branch converted the producer func_1501ECA4 (and func_15020F6C) in P87. */

/* P105: the P97 TEMPORARY guard (__wrap_func_1501FD34 / __wrap_func_1501FF10 skipped the P92 path C while its
 * producer func_15020920 was an asm stub) was removed: port-b P96 converted func_15020920 (segment cubic). */

/* P110: the P105 TEMPORARY guard __wrap_func_151DA6F8 (skipped the P100 C particle spawner while its trail
 * handlers were asm stubs) was removed: port-b P108 converted the trail chain func_15148428 / func_151485AC /
 * func_15148E34 / func_15149114 / func_15149350. */

/* P110 DIAGNOSTIC ?p110part=1 (node PORT_P110PART=1): counts the particle spawner func_151DA6F8 (P100 C) and the trail
 * step / draw handlers func_15148428 / func_151485AC (P108 C); logs the first 3 calls of each and every 500th.
 * Pure pass-through. */
static int fp110 = -1; static unsigned np110[3];
static void p110log(int k, const char *n, void *r) {
    unsigned c = ++np110[k];
    if (flag(&fp110, "p110part") && (c <= 3 || c % 500 == 0))
        port_log("[p110] %s call %u frame %u ret %p\n", n, c, port_frame_count, r);
}
void *__real_func_151DA6F8(void *pos, void *vel, float scale, int sprite, int alpha, float speed, int tint, int fade,
                           float sx, float sy, int a10, int a11, int a12, int a13, int a14, int a15, int a16, int a17);
void *__wrap_func_151DA6F8(void *pos, void *vel, float scale, int sprite, int alpha, float speed, int tint, int fade,
                           float sx, float sy, int a10, int a11, int a12, int a13, int a14, int a15, int a16, int a17) {
    void *r = __real_func_151DA6F8(pos, vel, scale, sprite, alpha, speed, tint, fade, sx, sy, a10, a11, a12, a13, a14, a15, a16, a17);
    p110log(0, "func_151DA6F8 (spawn)", r);
    return r;
}
int __real_func_15148428(void *obj);
int __wrap_func_15148428(void *obj) { int r = __real_func_15148428(obj); p110log(1, "func_15148428 (trail step)", (void *)(long)r); return r; }
int __real_func_151485AC(void *obj, int gfx, int a2);
int __wrap_func_151485AC(void *obj, int gfx, int a2) { int r = __real_func_151485AC(obj, gfx, a2); p110log(2, "func_151485AC (trail draw)", (void *)(long)r); return r; }

/* P97 DIAGNOSTIC ?p97camh=N: first N calls (every 20th frame) of func_15124C38 (camera target height, P92 C): the
 * eased height +0x2C0 before / after, the holder's (+0x3D0) y +0x18, floor +0x180, height above floor +0x28, model
 * height +0xCC, the target's (+0x3D4) +0x114, camera flags +0x2C / +0x84 / +0x5F0, states +0x23C / +0x23E.
 * DIAGNOSTIC ?p97nocamh=1: func_15124C38 does nothing when out == NULL (the pre-P92 stub behaviour). */
static int fcamh = -1, fnocamh = -1, ncamh = 0;
static float F(const unsigned char *p) { return *(const float *)p; }
static int H(const unsigned char *p) { return *(const short *)((uintptr_t)p ^ 2); }
void __real_func_15124C38(unsigned char *cam, float *out);
void __wrap_func_15124C38(unsigned char *cam, float *out) {
    float before = F(cam + 0x2C0);
    unsigned char *hold = *(unsigned char **)(cam + 0x3D0), *pl = *(unsigned char **)(cam + 0x3D4);
    if (out == 0 && flag(&fnocamh, "p97nocamh")) return;
    __real_func_15124C38(cam, out);
    if (flag(&fcamh, "p97camh") && ncamh < fcamh && port_frame_count % 20 == 0) {
        ncamh++;
        port_log("[p97camh] frame %u out %d h %.1f -> %.1f | hold y %.1f floor %.1f above %.1f cc %d | pl %d 114 %d | 2C %08X 84 %08X 5F0 %08X 23C %u 23E %u 102 %u\n",
                 port_frame_count, out != 0, before, out ? *out : F(cam + 0x2C0), hold ? F(hold + 0x18) : -1.f,
                 hold ? F(hold + 0x180) : -1.f, hold ? F(hold + 0x28) : -1.f, hold ? H(hold + 0xCC) : -1, pl != 0,
                 pl ? H(pl + 0x114) : -1, W(cam + 0x2C), W(cam + 0x84), W(cam + 0x5F0), B(cam + 0x23C), B(cam + 0x23E),
                 hold ? B(hold + 0x102) : 0);
    }
}
