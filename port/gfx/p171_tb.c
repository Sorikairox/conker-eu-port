/* P171 DIAGNOSTIC ?p171tb=1 / PORT_P171TB=1: text box update (func_1516AFE0, game_eu_1984F0.c, C since port-b P168).
 * Logs every change of the box state +0x15 (and of the line +0x20), with the descriptor's flags / line count / callback
 * and the pad word D_800BEB30[0], plus a per-250-retrace count of update calls; logs every func_1516AD20 (open)
 * call. Box memory is virtual big-endian: bytes via vbe_ld8,
 * aligned words plain. Linker --wrap: calls from other translation units only (the update is reached through the
 * kind table, see the log whether the wrap is hit). */
#include <stdint.h>
#include "../ultra/pc_mem.h"
typedef int32_t s32; typedef uint8_t u8; typedef uint16_t u16;
int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern u16 D_800BEB30[];
static int on(void) { static int f = -1; if (f < 0) f = port_flag("p171tb"); return f; }

void __real_func_1516AFE0(u8 *box);
void __wrap_func_1516AFE0(u8 *box) {
    static unsigned win = ~0u, calls, nlog;
    if (!on()) { __real_func_1516AFE0(box); return; }
    unsigned w = port_frame_count / 250;
    if (w != win) { if (win != ~0u && calls) port_log("[p171tb] retraces %u..%u: update calls %u\n", win * 250, win * 250 + 249, calls); win = w; calls = 0; }
    calls++;
    u8 *t = *(u8 **)(box + 0x10);
    unsigned s0 = vbe_ld8(box + 0x15), l0 = vbe_ld8(box + 0x20), f0 = t ? *(unsigned *)t : 0;
    unsigned cb = t ? *(unsigned *)(t + 0x2C) : 0, lines = t ? vbe_ld8(t + 8) : 0, b2b = t ? vbe_ld8(t + 0x2B) : 0;
    unsigned pad = vbe_ld16(&D_800BEB30[0]);
    __real_func_1516AFE0(box);
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
s32 __real_func_1516AD20(s32 id, s32 player, s32 arg2, void (*callback)(s32, s32, s32), s32 *text, s32 arg5);
s32 __wrap_func_1516AD20(s32 id, s32 player, s32 arg2, void (*callback)(s32, s32, s32), s32 *text, s32 arg5) {
    s32 r = __real_func_1516AD20(id, player, arg2, callback, text, arg5);
    if (on()) port_log("[p171tb] frame %u open id %d player %d a2 %d cb %08x text %08x a5 %d -> box %08x\n", port_frame_count, id, player, arg2,
                       (unsigned)(uintptr_t)callback, (unsigned)(uintptr_t)text, arg5, (unsigned)r);
    return r;
}

/* P171 ?p171fix=1 (TEST of a dropped argument, like P161's p161fix): func_15147F50 / func_15147FA0 (game_eu_1754C0.c,
 * matching C, the free / second handlers of the D_8008A5A0 record family) call D_8008A690[idx]() / D_8008A6E0[idx]()
 * with no argument (arity_scan rows func_15147F50 / func_15147FA0, a0:E: the asm keeps a0 = the record at the jalr).
 * The handler func_15147E64 takes the record (func_15147E40: func_151D5E30(rec + 0x84) releases 4 blocks), so in the
 * port it got garbage: new-game trap at retrace 6241 after the P164 merge (records of this family are now freed).
 * This wrap passes the record (what the game C fix must do); off = the game C as it is. Counts in [p171fix] lines. */
#include "../ultra/pc_icall.h"
extern void *D_8008A690[], *D_8008A6E0[];
static int fixon(void) { static int f = -1; if (f < 0) f = port_flag("p171fix"); return f; }
static void call_rec(void **tab, u8 *rec, const char *nm) {
    static unsigned n;
    s32 idx = *(s32 *)(rec + 0x20);
    if (idx < 0 || idx >= 20) idx = 0;
    void *fp = tab[idx];
    if (n++ < 8) port_log("[p171fix] frame %u %s rec %08x idx %d\n", port_frame_count, nm, (unsigned)(uintptr_t)rec, idx);
    if (fp) { u64_ b[1] = { (unsigned)(uintptr_t)rec }; __port_icall_slow(fp, __port_fsig(fp), b, 1, 0, 4); }
}
void __real_func_15147F50(u8 *arg0);
void __wrap_func_15147F50(u8 *arg0) { if (fixon() > 0) call_rec(D_8008A690, arg0, "F50"); else __real_func_15147F50(arg0); }
void __real_func_15147FA0(u8 *arg0);
void __wrap_func_15147FA0(u8 *arg0) { if (fixon() > 0) call_rec(D_8008A6E0, arg0, "FA0"); else __real_func_15147FA0(arg0); }
