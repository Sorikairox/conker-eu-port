/* P49: ?p49walk=N runtime check of P47's walk handler func_1504CB98 (state 1), link-time wrap.
 * Logs the player record before / after each call (first N calls, then every `p49every` calls, default 32):
 * position, velocities, yaw (+0x76 / +0x7A), target speed (+0x44), the pad (D_800CC6A4), the handler's flag
 * word D_800CC6DC, and which asm stubs the handler reached (port_stub_trace_hook), with call counts. */
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern void (*port_stub_trace_hook)(const char *name);
extern unsigned D_800CC6A4, D_800CC6DC, D_800CC288, D_800CC6A0;
extern unsigned short D_800CC69E; /* u16 in game memory: read with vbe_ld16 */
extern unsigned char D_800BE616;

#define NSTUB 48
static const char *st_name[NSTUB];
static unsigned st_n[NSTUB], st_tot[NSTUB], st_count;
static void p49_hook(const char *name) {
    unsigned i;
    for (i = 0; i < st_count; i++)
        if (st_name[i] == name || !strcmp(st_name[i], name)) { st_n[i]++; st_tot[i]++; return; }
    if (st_count < NSTUB) { st_name[st_count] = name; st_n[st_count] = 1; st_tot[st_count] = 1; st_count++; }
}

#define F(o) (*(const float *)(r + (o)))
#define U8(o) vbe_ld8(r + (o))
#define U16(o) vbe_ld16(r + (o))
static void p49_line(const char *tag, const unsigned char *r) {
    const unsigned char *u = (const unsigned char *)(uintptr_t)*(const unsigned *)(r + 0x31C);
    const unsigned char *pad = (const unsigned char *)(uintptr_t)D_800CC6A4;
    port_log("[p49] %s frame %u: state %d pos %g %g %g yv %g grav %g xz %g +28 %g +44 %g +54 %g yaw76 %04X 7A %04X 78 %04X "
             "floor118 %g dis_run %02X stun %02X water %02X 81 %02X 83 %02X AA %02X 110 %02X F8 %08X | pad %04X %d,%d "
             "CC288 %04X CC6DC %03X CC69E %04X CC6A0 %04X hp %02X BE616 %02X | 31C %08X 78 %02X 84 %02X 4E %02X 52 %02X 197 %02X 198 %02X 11A %02X 12 %d\n",
             tag, port_frame_count, *(const int *)r, F(0x14), F(0x18), F(0x1C), F(0x20), F(0x24), F(0x3C), F(0x28), F(0x44),
             F(0x54), U16(0x76), U16(0x7A), U16(0x78), F(0x118), U8(0x89), U8(0x104), U8(0xAD), U8(0x81), U8(0x83), U8(0xAA),
             U8(0x110), *(const unsigned *)(r + 0xF8), pad ? vbe_ld16(pad) : 0, pad ? (signed char)vbe_ld8(pad + 2) : 0,
             pad ? (signed char)vbe_ld8(pad + 3) : 0, D_800CC288 & 0xFFFF, D_800CC6DC, vbe_ld16(&D_800CC69E), D_800CC6A0 & 0xFFFF, U8(0x1CA), vbe_ld8(&D_800BE616),
             (unsigned)(uintptr_t)u, u ? vbe_ld8(u + 0x78) : 0, u ? vbe_ld8(u + 0x84) : 0, u ? vbe_ld8(u + 0x4E) : 0,
             u ? vbe_ld8(u + 0x52) : 0, u ? vbe_ld8(u + 0x197) : 0, u ? vbe_ld8(u + 0x198) : 0, u ? vbe_ld8(u + 0x11A) : 0, u ? (short)vbe_ld16(u + 0x12) : 0);
}

void __real_func_1504CB98(void *arg0);
void __wrap_func_1504CB98(void *arg0) {
    static int flag = -1, every = -1;
    static unsigned calls;
    const unsigned char *r = (const unsigned char *)arg0;
    float x0, z0;
    int log;
    unsigned i;
    if (flag < 0) { flag = port_flag("p49walk"); every = port_flag("p49every"); if (every <= 0) every = 32; }
    if (!flag) { __real_func_1504CB98(arg0); return; }
    calls++;
    log = calls <= (unsigned)flag || calls % (unsigned)every == 0;
    x0 = F(0x14); z0 = F(0x1C);
    if (log) p49_line("pre ", r);
    for (i = 0; i < st_count; i++) st_n[i] = 0;
    port_stub_trace_hook = p49_hook;
    __real_func_1504CB98(arg0);
    port_stub_trace_hook = 0;
    if (log) {
        char buf[600]; int n = 0;
        p49_line("post", r);
        for (i = 0; i < st_count && n < 560; i++)
            if (st_n[i]) n += snprintf(buf + n, sizeof buf - n, " %s x%u", st_name[i], st_n[i]);
        buf[n] = 0;
        port_log("[p49] call %u: moved %g,%g; stubs inside:%s\n", calls, F(0x14) - x0, F(0x1C) - z0, n ? buf : " none");
    }
    if (calls % 512 == 0) {
        char buf[900]; int n = 0;
        for (i = 0; i < st_count && n < 860; i++) n += snprintf(buf + n, sizeof buf - n, " %s %u", st_name[i], st_tot[i]);
        buf[n] = 0;
        port_log("[p49] after %u calls, stub totals inside the walk handler:%s\n", calls, buf);
    }
}

/* P52: with ?p49walk set, also
 *  - wrap func_1505A770 (P50 C gravity; the call from the walk handler): y / y_velocity / +0x28 before and after,
 *    gravity +0x24 and the frame time D_800D1550[0] (an f32 array, P50), first p49walk calls then every p49every;
 *  - wrap func_1502C1D4 (P48 C object update loop, called from game_45B80.c): record 0's model fields after it
 *    (+0x1D4 model instance, +0x2D0 animation state, id +4, D_800D19A0[id] loaded model, D_800C52F0[id]). */
extern float D_800D1550[];
extern unsigned D_800D19A0[];
extern unsigned short D_800C52F0[];
extern unsigned char D_800CC2D0[];
void __real_func_1505A770(void *rec);
void __wrap_func_1505A770(void *rec) {
    static int flag = -1, every = -1;
    static unsigned calls;
    const unsigned char *r = (const unsigned char *)rec;
    float y0 = F(0x18), v0 = F(0x20), h0 = F(0x28);
    if (flag < 0) { flag = port_flag("p49walk"); every = port_flag("p49every"); if (every <= 0) every = 32; }
    __real_func_1505A770(rec);
    calls++;
    if (flag && (calls <= (unsigned)flag || calls % (unsigned)every == 0))
        port_log("[p52] gravity call %u frame %u: dt D_800D1550[0] %g (bits %08X) grav %g | y %g -> %g yv %g -> %g "
                 "+28 %g -> %g | +180 %g floor118 %g\n", calls, port_frame_count, D_800D1550[0],
                 *(const unsigned *)D_800D1550, F(0x24), y0, F(0x18), v0, F(0x20), h0, F(0x28), F(0x180), F(0x118));
}
void __real_func_1502C1D4(void);
void __wrap_func_1502C1D4(void) {
    static int flag = -1;
    static unsigned calls;
    const unsigned char *r = D_800CC2D0;
    __real_func_1502C1D4();
    if (flag < 0) { flag = port_flag("p49walk"); }
    calls++;
    if (flag && (calls <= 3 || (calls & 255) == 0)) {
        unsigned id = U8(4);
        port_log("[p52] func_1502C1D4 call %u frame %u: rec0 state %d id %02X +65 %02X +1D4 %08X +2D0 %08X "
                 "D_800D19A0[id] %08X D_800C52F0[id] %u +74 %02X\n", calls, port_frame_count, *(const int *)r, id,
                 U8(0x65), *(const unsigned *)(r + 0x1D4), *(const unsigned *)(r + 0x2D0), D_800D19A0[id],
                 vbe_ld16(&D_800C52F0[id]), U8(0x74));
    }
}

/* P52 diagnostic ?p52void=1: the floor query func_1510EE3C (C) only forwards to the asm stub func_1510EED0, so the
 * walk handler's floor height (its local spC4, arg 3) is never written and stays at whatever the stack held (0 in
 * practice): the handler then snaps y to spC4 - 1 = -1 every call. With p52void the wrapper writes "no floor"
 * (-10000, what the real query returns off the level) to arg 3 and arg 4 (+0x118), so gravity is visible. */
void __real_func_1510EE3C(int a0, int a1, int a2, int a3, int a4, int a5, float a6, float a7, float a8, float a9,
                          unsigned short aA, int aB, int aC, int aD, int aE);
void __wrap_func_1510EE3C(int a0, int a1, int a2, int a3, int a4, int a5, float a6, float a7, float a8, float a9,
                          unsigned short aA, int aB, int aC, int aD, int aE) {
    static int flag = -1;
    if (flag < 0) flag = port_flag("p52void");
    __real_func_1510EE3C(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE);
    if (flag) {
        if (a2) *(float *)(uintptr_t)a2 = -10000.0f;
        if (a3) *(float *)(uintptr_t)a3 = -10000.0f;
    }
}
