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
void p84_frame(void) {
    if (flang < 0) { flang = port_flag("p84lang"); if (flang) port_stub_trace_hook = lang_hook; }
    if (flang) lang_watch("text");
}
