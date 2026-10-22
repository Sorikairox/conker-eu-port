/* P75 runtime checks of port P70 / P74 C (link-time wraps; only cross-TU calls are seen).
 *  ?p75sky=1     func_15000AD0 (game_2DF70.c, sky / backdrop buffers; called by func_15007B3C per level): level,
 *                header +5..+8 (mode), D_80082FA0, the buffers D_800DC2E0 / D_800DC2B8[p][0..1] / D_800DC2B0, and in
 *                mode 2 the gradient texture (rows 0 / 32 / ... / 255) and the first quad's vertices. Also, every
 *                256 frames (from the tail wrap), the quad vertex t coordinates and the first Mtx word that func_150D1D20 writes (it is
 *                no longer wrapped: P72's TEMPORARY NULL guard is gone).
 *  ?p75tail=N    func_1503BCAC (P70 tail chain, called by func_1503482C in game_eu_61AE0.c): arg0, calls per frame,
 *                tail record of D_800CC2D0[arg0] (points p[0..4], phase, sway, timer, fade): first N calls, then
 *                every 64th.
 *  ?p75brk=N     func_1503E238 (P74 breakable state machine, called per object in game_eu_595D0.c when D_800C6A8F[slot * 16] != 0):
 *                slot, kind, state before -> after, piece buffer, first piece; first N calls + every state change.
 *  ?p75break=FRAME&p75bslot=SLOT&p75bkind=KIND  DIAGNOSTIC: at FRAME request a break of record SLOT with kind KIND (func_1503E1FC,
 *                what the level-script commands of game_A28B0.c / game_A9D90.c do via func_1503DE70). */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern unsigned char D_800CC2D0[];
extern unsigned char D_800DC2E0_[] __asm__("D_800DC2E0");
extern unsigned char D_800DC2B8_[] __asm__("D_800DC2B8");
extern unsigned char D_800DC2B0_[] __asm__("D_800DC2B0");
extern unsigned char D_800DC2D8_[] __asm__("D_800DC2D8");
extern unsigned char D_80082FA0_[] __asm__("D_80082FA0");
extern unsigned char D_800B0DF0_[] __asm__("D_800B0DF0");
extern unsigned char D_800C6660_[] __asm__("D_800C6660");

#define REC 0x32C
static unsigned W(const unsigned char *r, int o) { return *(const unsigned *)(r + o); }
static float F(const unsigned char *r, int o) { return *(const float *)(r + o); }
static int flag(int *f, const char *n) { if (*f < 0) *f = port_flag(n); return *f; }
static void brk_req(void);
static int fsky = -1, ftail = -1, fbrk = -1;

static void quad_dump(const char *what) {
    int np = (int)W(D_80082FA0_, 0), p, fb;
    if (np < 0 || np > 3) np = 0;
    for (p = 0; p <= np; p++)
        for (fb = 0; fb < 2; fb++) {
            const unsigned char *v = (const unsigned char *)(uintptr_t)W(D_800DC2B8_, p * 8 + fb * 4);
            if (!v) { port_log("[p75] %s quad[%d][%d] NULL\n", what, p, fb); continue; }
            port_log("[p75] %s quad[%d][%d] %p: v0 x %d y %d z %d flag %u s %d t %d | t1 %d t2 %d t3 %d\n", what, p, fb,
                     (void *)v, (short)vbe_ld16(v), (short)vbe_ld16(v + 2), (short)vbe_ld16(v + 4), vbe_ld16(v + 6),
                     (short)vbe_ld16(v + 8), (short)vbe_ld16(v + 0xA), (short)vbe_ld16(v + 0x1A),
                     (short)vbe_ld16(v + 0x2A), (short)vbe_ld16(v + 0x3A));
        }
    {
        const unsigned char *m = (const unsigned char *)(uintptr_t)W(D_800DC2E0_, 0);
        if (m) port_log("[p75] %s Mtx D_800DC2E0 %p: %08X %08X %08X %08X\n", what, (void *)m, W(m, 0), W(m, 4),
                        W(m, 8), W(m, 0x20));
    }
}

void __real_func_15000AD0(int level);
void __wrap_func_15000AD0(int level) {
    const unsigned char *h = (const unsigned char *)(uintptr_t)W(D_800B0DF0_, 0);
    unsigned m0 = h ? vbe_ld8(h + 8) : 0xFFFF;
    __real_func_15000AD0(level);
    if (!flag(&fsky, "p75sky")) return;
    port_log("[p75] func_15000AD0 frame %u level %d: header %p +5..+7 %u %u %u mode %u -> %u, D_80082FA0 %d, "
             "D_800DC2E0 %08X D_800DC2B0 %08X D_800DC2B8 %08X %08X %08X %08X\n", port_frame_count, level, (void *)h,
             vbe_ld8(D_800DC2D8_), vbe_ld8(D_800DC2D8_ + 1), vbe_ld8(D_800DC2D8_ + 2), m0, h ? vbe_ld8(h + 8) : 0xFFFF,
             (int)W(D_80082FA0_, 0), W(D_800DC2E0_, 0), W(D_800DC2B0_, 0), W(D_800DC2B8_, 0), W(D_800DC2B8_, 4),
             W(D_800DC2B8_, 8), W(D_800DC2B8_, 12));
    if (h && vbe_ld8(h + 8) == 2) {
        const unsigned char *t = (const unsigned char *)(uintptr_t)W(D_800DC2B0_, 0);
        int r;
        if (t)
            for (r = 0; r < 256; r += (r == 224 ? 31 : 32))
                port_log("[p75]   gradient row %3d: %08X %08X %08X %08X\n", r, W(t, r * 16), W(t, r * 16 + 4),
                         W(t, r * 16 + 8), W(t, r * 16 + 12));
    }
    quad_dump("after func_15000AD0");
}

static unsigned tail_calls, tail_frame, tail_inframe, tail_maxinframe, tail_nonzero;
void __real_func_1503BCAC(int arg0);
void __wrap_func_1503BCAC(int arg0) {
    const unsigned char *obj = D_800CC2D0 + arg0 * REC;
    if (port_frame_count != tail_frame) {
        if (tail_inframe > tail_maxinframe) tail_maxinframe = tail_inframe;
        tail_frame = port_frame_count; tail_inframe = 0;
        static unsigned next = 256;
        if (flag(&fsky, "p75sky") && port_frame_count >= next) { next = port_frame_count + 256; quad_dump("frame"); }
    }
    tail_inframe++;
    { /* ?p75sky also reports the first frame a word of the null zone 0x10..0xFF becomes nonzero */
        static int seen;
        if (!seen && flag(&fsky, "p75sky")) {
            unsigned a;
            for (a = 0x10; a < 0x100; a += 4)
                if (*(volatile unsigned *)(uintptr_t)a) {
                    seen = 1;
                    port_log("[p75] null zone dirty at frame %u: null+0x%X = %08X\n", port_frame_count, a,
                             *(volatile unsigned *)(uintptr_t)a);
                    break;
                }
        }
    }
    brk_req();
    if (arg0 != 0) tail_nonzero++;
    __real_func_1503BCAC(arg0);
    if (!flag(&ftail, "p75tail")) return;
    if (tail_calls++ < (unsigned)ftail || (tail_calls & 63) == 0) {
        const unsigned char *x = W(obj, 0x31C) ? (const unsigned char *)(uintptr_t)W(obj, 0x31C) : 0;
        const unsigned char *r = x ? (const unsigned char *)(uintptr_t)W(x, 0x11C) : 0;
        port_log("[p75] tail #%u frame %u arg0 %d (calls this frame %u, max %u, arg0!=0 %u) id %02X joints %08X "
                 "anim %04X", tail_calls, port_frame_count, arg0, tail_inframe, tail_maxinframe, tail_nonzero,
                 vbe_ld8(obj + 4), W(obj, 0x1D4), vbe_ld16(obj + 0x84));
        if (r) {
            int i;
            for (i = 0; i < 5; i++) port_log(" p%d(%.1f %.1f %.1f)", i, F(r, i * 12), F(r, i * 12 + 4), F(r, i * 12 + 8));
            port_log(" phase %.1f sway %.2f spd %.2f amp %.2f timer %d fade %u", F(r, 0x3C), F(r, 0x40), F(r, 0x44),
                     F(r, 0x48), (short)vbe_ld16(r + 0x4C), vbe_ld8(r + 0x4E));
        }
        port_log("\n");
    }
}

/* D_800C6660: struct106, 0x10 bytes: +0 pieces, +4 / +8 flag masks, +0xC timer, +0xE kind, +0xF state */
static void brk_req(void) {
    static int done = -1;
    static unsigned fr, slot, kind;
    if (done < 0) {
        fr = (unsigned)port_flag("p75break"); slot = (unsigned)port_flag("p75bslot"); kind = (unsigned)port_flag("p75bkind");
        done = fr ? 0 : 1;
    }
    if (done || port_frame_count < fr) return;
    done = 1;
    {
        void func_1503E1FC(int, int, int, int);
        const unsigned char *obj = D_800CC2D0 + slot * REC;
        port_log("[p75] DIAGNOSTIC break request frame %u: slot %u (id %02X joints %08X) kind %u\n", port_frame_count,
                 slot, vbe_ld8(obj + 4), W(obj, 0x1D4), kind);
        func_1503E1FC((int)slot, (int)kind, -1, -1);
    }
}

void __real_func_1503E238(int i);
void __wrap_func_1503E238(int i) {
    static unsigned calls;
    unsigned char *r = D_800C6660_ + i * 16;
    unsigned s0 = vbe_ld8(r + 0xF), s1;
    __real_func_1503E238(i);
    s1 = vbe_ld8(r + 0xF);
    if (!flag(&fbrk, "p75brk")) return;
    if (calls++ < (unsigned)fbrk || s0 != s1 || (calls & 7) == 0) {
        const unsigned char *pc = (const unsigned char *)(uintptr_t)W(r, 0);
        port_log("[p75] breakable #%u frame %u slot %d kind %u state %u -> %u timer %d pieces %p", calls,
                 port_frame_count, i, vbe_ld8(r + 0xE), s0, s1, (short)vbe_ld16(r + 0xC), (void *)pc);
        if (pc) {
            extern unsigned char D_80098CC4_[] __asm__("D_80098CC4");
            extern unsigned char D_800847E4_[] __asm__("D_800847E4");
            const unsigned char *att = (const unsigned char *)(uintptr_t)W(D_800847E4_, vbe_ld8(r + 0xE) * 4);
            unsigned n = vbe_ld8(D_80098CC4_ + vbe_ld8(r + 0xE)), k, act = 0, nfree = 0, first = ~0u;
            for (k = 0; k < n && k < 64; k++)
                if (vbe_ld8(pc + k * 0x68 + 0x64)) {
                    act++;
                    if (att && (signed char)vbe_ld8(att + k) == -1) { nfree++; if (first == ~0u) first = k; }
                }
            port_log(" n %u active %u free %u", n, act, nfree);
            if (first != ~0u) {
                const unsigned char *q = pc + first * 0x68;
                port_log(" first free #%u +0x24 (%.1f %.1f %.1f) angles (%.1f %.1f %.1f) vy %.2f g %.2f", first,
                         F(q, 0x24), F(q, 0x28), F(q, 0x2C), F(q, 0x30), F(q, 0x34), F(q, 0x38), F(q, 0x4C), F(q, 0x60));
            }
        }
        port_log("\n");
    }
}

