/* P72 runtime check of port-b P64's func_150D1D20 (game_eu_FF530.c, view quad), the cause of the P69
 * walk-after-respawn hang (link-time wrap; its callers are in other TUs).
 *  ?p72quad=N   log the first N calls: the args, the player index / frame, the Mtx buffer pointer D_800DC2E0 and the
 *               vertex pointer D_800DC2B8[p][frame] it writes through.
 *  ?p72skip=1   DIAGNOSTIC: skip the C body (return gdl unchanged, like the old asm stub).
 *
 * TEMPORARY port-side workaround (remove when func_15000AD0, game_2DF70.c, is C): func_150D1D20 is correct against
 * the asm, but its two buffers are allocated by func_15000AD0 (allocate_memory -> sw D_800DC2E0 at 0x15000C70 /
 * 0x150012DC; the D_800DC2B8 vertex table at 0x15000B60 / 0x150012E8), which is still an asm stub. So D_800DC2E0 and
 * D_800DC2B8[p][fb] are NULL in the port, and the C writes a Mtx (guMtxF2L, (p * 2 + fb) * 0x40) and four vertex t
 * coordinates (+0xA / +0x1A / +0x2A / +0x3A) into the null zone at 0x00..0xFF. Other asm stubs return NULL, and the
 * game then reads "objects" there: a nonzero word left at 0x0..0xFF became the garbage node 0x243C / 0x2450 in
 * D_800DD280[1][0], func_15169824 freed it twice and func_10003C6C spun forever (the P69 respawn hang; P72.md).
 * Until the buffers exist, a call with a NULL buffer returns gdl unchanged (what the asm stub did). */
#include <stdint.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern unsigned char D_800DC2E0_[] __asm__("D_800DC2E0");
extern unsigned char D_800DC2B8_[] __asm__("D_800DC2B8");
extern unsigned char D_80082FA4_[] __asm__("D_80082FA4");
extern unsigned char D_800BE9C0_[] __asm__("D_800BE9C0");
extern unsigned char D_800BE628_[] __asm__("D_800BE628");
extern unsigned char D_800DC2B0_[] __asm__("D_800DC2B0");

static int fq = -1, fs = -1;
static unsigned W(const unsigned char *r, int o) { return *(const unsigned *)(r + o); }

void *__real_func_150D1D20(void *gdl, int a1, int a2, int a3, float scroll, int a5, float angle);
void *__wrap_func_150D1D20(void *gdl, int a1, int a2, int a3, float scroll, int a5, float angle) {
    static unsigned n;
    if (fq < 0) fq = port_flag("p72quad");
    if (fs < 0) fs = port_flag("p72skip");
    if (n++ < (unsigned)fq) {
        unsigned p = W(D_80082FA4_, 0), fr = vbe_ld8(D_800BE9C0_);
        port_log("[p72] func_150D1D20 #%u frame %u gdl %p args %d %d %d scroll %f %d angle %f: player %u fb %u "
                 "D_800DC2E0 %08X D_800DC2B8[p][fb] %08X D_800BE628 %08X D_800DC2B0 %08X\n", n, port_frame_count, gdl,
                 a1, a2, a3, scroll, a5, angle, p, fr, W(D_800DC2E0_, 0), p < 4 && fr < 2 ? W(D_800DC2B8_, p * 8 + fr * 4) : 0,
                 W(D_800BE628_, 0), W(D_800DC2B0_, 0));
    }
    if (fs > 0) return gdl;
    {
        unsigned p = W(D_80082FA4_, 0), fr = vbe_ld8(D_800BE9C0_);
        unsigned v = p < 4 && fr < 2 ? W(D_800DC2B8_, p * 8 + fr * 4) : 0;
        static unsigned skipped;
        if (W(D_800DC2E0_, 0) == 0 || v == 0) { /* TEMPORARY (see the header) */
            if (skipped++ == 0)
                port_log("[p72] func_150D1D20 frame %u: D_800DC2E0 %08X / D_800DC2B8[%u][%u] %08X NULL (func_15000AD0 is an "
                         "asm stub): skipped (TEMPORARY)\n", port_frame_count, W(D_800DC2E0_, 0), p, fr, v);
            return gdl;
        }
    }
    return __real_func_150D1D20(gdl, a1, a2, a3, scroll, a5, angle);
}
