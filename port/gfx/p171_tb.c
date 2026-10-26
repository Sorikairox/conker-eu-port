/* P171 DIAGNOSTIC ?p171tb=1 / PORT_P171TB=1: text box update (text_box_update, game_eu_1984F0.c, C since port-b P168).
 * Logs every change of the box state +0x15 (and of the line +0x20), with the descriptor's flags / line count / callback
 * and the pad word g_pad_pressed[0], plus a per-250-retrace count of update calls; logs every text_box_open (open)
 * call. Box memory is virtual big-endian: bytes via vbe_ld8,
 * aligned words plain. Linker --wrap: calls from other translation units only (the update is reached through the
 * kind table, see the log whether the wrap is hit).
 * P185: the ?p171fix wraps of fxrec_dispatch_free / fxrec_dispatch_b are gone (the game C passes the record since P173). */
#include <stdint.h>
#include "../ultra/pc_mem.h"
typedef int32_t s32; typedef uint8_t u8; typedef uint16_t u16;
int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern u16 g_pad_pressed[]; /* was D_800BEB30 */
static int on(void) { static int f = -1; if (f < 0) f = port_flag("p171tb"); return f; }

void __real_text_box_update(u8 *box);
void __wrap_text_box_update(u8 *box) {
    static unsigned win = ~0u, calls, nlog;
    if (!on()) { __real_text_box_update(box); return; }
    unsigned w = port_frame_count / 250;
    if (w != win) { if (win != ~0u && calls) port_log("[p171tb] retraces %u..%u: update calls %u\n", win * 250, win * 250 + 249, calls); win = w; calls = 0; }
    calls++;
    u8 *t = *(u8 **)(box + 0x10);
    unsigned s0 = vbe_ld8(box + 0x15), l0 = vbe_ld8(box + 0x20), f0 = t ? *(unsigned *)t : 0;
    unsigned cb = t ? *(unsigned *)(t + 0x2C) : 0, lines = t ? vbe_ld8(t + 8) : 0, b2b = t ? vbe_ld8(t + 0x2B) : 0;
    unsigned pad = vbe_ld16(&g_pad_pressed[0]);
    __real_text_box_update(box);
    /* the box may be freed in state 0x80: read it again only if the state was not 0x80 */
    unsigned s1 = s0 == 0x80 ? 0xFFu : vbe_ld8(box + 0x15), l1 = s0 == 0x80 ? l0 : vbe_ld8(box + 0x20);
    unsigned f1 = t ? *(unsigned *)t : 0;
    if ((s1 != s0 || l1 != l0 || (pad & 0xC000)) && nlog < 400) {
        nlog++;
        port_log("[p171tb] frame %u box %08x desc %08x state %02x -> %02x line %d -> %d lines %u flags %08x -> %08x cb %08x 2B %u pad %04x\n",
                 port_frame_count, (unsigned)(uintptr_t)box, (unsigned)(uintptr_t)t, s0, s1, (int)(signed char)l0, (int)(signed char)l1,
                 lines, f0, f1, cb, b2b, pad);
    }
}
s32 __real_text_box_open(s32 id, s32 player, s32 arg2, void (*callback)(s32, s32, s32), s32 *text, s32 arg5);
s32 __wrap_text_box_open(s32 id, s32 player, s32 arg2, void (*callback)(s32, s32, s32), s32 *text, s32 arg5) {
    s32 r = __real_text_box_open(id, player, arg2, callback, text, arg5);
    if (on()) port_log("[p171tb] frame %u open id %d player %d a2 %d cb %08x text %08x a5 %d -> box %08x\n", port_frame_count, id, player, arg2,
                       (unsigned)(uintptr_t)callback, (unsigned)(uintptr_t)text, arg5, (unsigned)r);
    return r;
}
