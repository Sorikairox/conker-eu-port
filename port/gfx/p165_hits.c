/* P165 DIAGNOSTIC ?p165hits=1 / PORT_P165HITS=1: first-room checks of the P157 conversions (port).
 * Per-250-retrace call counts of the object sound emitters func_10010154 / func_10010344 (with the number of calls
 * that returned a voice handle != 0 and up to 6 distinct sound ids), the variant picker func_1000F568, the move
 * animation func_15064F50 (with how often it returned an animation id other than 0 / 999) and the B / context action
 * func_15064668. Every func_15064668 call with B pressed or a pending context action (ctx+0x7B) is logged with the
 * context bytes 0x7B / 0x75 / 0x7C / 0x4E / 0x198. Linker --wrap: calls from other translation units only.
 * Signatures = the NM definitions (init_EB00.c, game_eu_90F50.c). */
#include <stdint.h>
#include <stdio.h>
#include "../ultra/pc_mem.h" /* P171: ctx bytes via vbe_ld8 (virtual big-endian; P165 read the wrong bytes) */
typedef float f32; typedef int32_t s32; typedef uint8_t u8; typedef int16_t s16; typedef uint16_t u16;
int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;

enum { S154, S344, SF568, SF50, SF50A, S668, S154V, S344V, NS };
static const char *nm[NS] = { "snd10154", "snd10344", "pick_F568", "move_4F50", "move_4F50_anim", "ctx_4668", "snd10154_voice", "snd10344_voice" };
static unsigned cnt[NS], win = ~0u, ids[6], nid;
static int on(void) { static int f = -1; if (f < 0) f = port_flag("p165hits"); return f; }
static void tick(int i) {
    unsigned w = port_frame_count / 250;
    if (w != win) {
        if (win != ~0u) {
            char b[640]; int o = snprintf(b, sizeof b, "[p165hits] retraces %u..%u:", win * 250, win * 250 + 249);
            for (int k = 0; k < NS; k++) if (cnt[k]) o += snprintf(b + o, sizeof b - o, " %s=%u", nm[k], cnt[k]);
            if (nid) { o += snprintf(b + o, sizeof b - o, " sfx"); for (unsigned k = 0; k < nid; k++) o += snprintf(b + o, sizeof b - o, " %u", ids[k]); }
            port_log("%s\n", b);
        }
        win = w; nid = 0; for (int k = 0; k < NS; k++) cnt[k] = 0;
    }
    if (i >= 0) cnt[i]++;
}
static void sfx(unsigned id) { for (unsigned k = 0; k < nid; k++) if (ids[k] == id) return; if (nid < 6) ids[nid++] = id; }

u16 __real_func_10010154(u16 sfx_, void *obj, s32 vol, s16 a3, u16 a4);
u16 __wrap_func_10010154(u16 sfx_, void *obj, s32 vol, s16 a3, u16 a4) {
    u16 r = __real_func_10010154(sfx_, obj, vol, a3, a4);
    if (on()) { tick(S154); sfx(sfx_); if (r) cnt[S154V]++; }
    return r;
}
u16 __real_func_10010344(u16 sfx_, void *obj, s32 vol, s16 a3, u16 a4);
u16 __wrap_func_10010344(u16 sfx_, void *obj, s32 vol, s16 a3, u16 a4) {
    u16 r = __real_func_10010344(sfx_, obj, vol, a3, a4);
    if (on()) { tick(S344); sfx(sfx_); if (r) cnt[S344V]++; }
    return r;
}
u16 __real_func_1000F568(s32 base, u16 n);
u16 __wrap_func_1000F568(s32 base, u16 n) { if (on()) tick(SF568); return __real_func_1000F568(base, n); }
s32 __real_func_15064F50(void *pl, f32 v, f32 m, s32 a, f32 p);
s32 __wrap_func_15064F50(void *pl, f32 v, f32 m, s32 a, f32 p) {
    s32 r = __real_func_15064F50(pl, v, m, a, p);
    if (on()) { tick(SF50); if (r != 0 && r != 999) cnt[SF50A]++; }
    return r;
}
void __real_func_15064668(void *pl, s32 buttons, f32 h, s32 a3, s32 noPad);
void __wrap_func_15064668(void *pl, s32 buttons, f32 h, s32 a3, s32 noPad) {
    if (on()) {
        tick(S668);
        u8 *ctx = pl ? *(u8 **)((u8 *)pl + 0x31C) : 0;
        if (ctx && ((buttons & 0x4000) || vbe_ld8(ctx + 0x7B))) {
            static unsigned nlog;
            if (nlog++ < 200)
                port_log("[p165ctx] frame %u buttons %04x h %.1f a3 %d nopad %d ctx7B %u 75 %u 7C %u 4E %u 198 %u pos %.0f %.0f %.0f\n",
                         port_frame_count, buttons & 0xFFFF, h, a3, noPad, vbe_ld8(ctx + 0x7B), vbe_ld8(ctx + 0x75), vbe_ld8(ctx + 0x7C), vbe_ld8(ctx + 0x4E), vbe_ld8(ctx + 0x198),
                         *(f32 *)((u8 *)pl + 0x14), *(f32 *)((u8 *)pl + 0x18), *(f32 *)((u8 *)pl + 0x1C));
        }
    }
    __real_func_15064668(pl, buttons, h, a3, noPad);
}
