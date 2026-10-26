/* P174 DIAGNOSTIC ?p174ev=1 / PORT_P174EV=1: event-script queries / actions of the first room (level 0x22, event 0xCA
 * "First Death"). Wraps the VM natives event_native_query (native 5 = D_80088838 queries) and event_native_action (native 6 =
 * D_80088874 actions), reached through D_80088A44 (n64mem_tab refs -> --wrap applies). Logs every change of
 * (id, arg, result) per id, and every native-6 action. For table entry 0 (event_query_scene, scene queries) and entry 13 /
 * id 0x19 (event_query_effect, "no object in lists D_800A6440[0..2] has +0x48 == 2") it also computes what the asm answers.
 *
 * P185: the ?p174fix test (return the asm answer) is gone: both handlers are fixed in the game C since P176 (port); the log
 * still prints C and asm answers side by side. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../ultra/pc_mem.h"
typedef int32_t s32; typedef uint8_t u8; typedef uint16_t u16;
int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern u8 g_cutscene_pending, D_800C35EA, D_800C40B8, D_800C3A08, D_800C3A92; /* was D_800C35C4 */
extern u8 *g_node_lists[][104]; /* was D_800DD280 */
extern u8 D_800A6440[];
extern s32 g_level_id; /* was D_800BE9F0 */
static int on(void) { static int f = -1; if (f < 0) f = port_flag("p174ev"); return f; }

static s32 asm_CBD8(s32 a0, s32 a1) {
    unsigned c4 = vbe_ld8(&g_cutscene_pending), ea = vbe_ld8(&D_800C35EA), sc = vbe_ld8(&D_800C40B8), s2 = vbe_ld8(&D_800C3A08);
    switch (a1) {
    case 1: if (c4) return 0; if (!ea) return 1; return (unsigned)a0 == sc ? 0 : 1;
    case 2: return ea == 1 && (unsigned)a0 == sc;
    case 3: return ea == 1 && (unsigned)a0 == s2;
    case 4: return ea != 1;
    case 5: return vbe_ld8(&D_800C3A92);
    case 6: return ea == 1 && (unsigned)a0 == s2;
    }
    return 0;
}
/* the asm walk of event_query_effect case 0x19 / 4 (every node's +0x48); logs the nodes when the summary changes */
static s32 asm_DFCC19(void) {
    static unsigned lastkey = ~0u;
    char buf[768]; int k = 0, r = 1; unsigned key = 2166136261u;
    buf[0] = 0;
    for (int g = 0; g < 2; g++)
        for (int i = 0; i < 3; i++) {
            unsigned li = *(unsigned *)(D_800A6440 + 4 * i);
            u8 *n = g_node_lists[g][li];
            int cnt = 0;
            while (n && cnt < 32) {
                unsigned st = vbe_ld8(n + 0x48);
                if (st == 2) r = 0;
                key = (key ^ (unsigned)(uintptr_t)n ^ (st << 24)) * 16777619u;
                if (k < 700) k += snprintf(buf + k, sizeof buf - k, "g%d/L%02X %08x s%u pos %.0f %.0f %.0f; ", g, li,
                                           (unsigned)(uintptr_t)n, st, *(float *)(n + 0x54), *(float *)(n + 0x58), *(float *)(n + 0x5C));
                n = *(u8 **)(n + 8); cnt++;
            }
        }
    static unsigned lastf;
    if (key != lastkey || port_frame_count - lastf >= 500) {
        lastkey = key; lastf = port_frame_count;
        port_log("[p174ev] frame %u lists 36/4C/5B: %s-> asm answer %d (null+0x48 byte %u)\n", port_frame_count,
                 buf[0] ? buf : "(empty) ", r, vbe_ld8((void *)0x48));
    }
    return r;
}

/* the running event block (event_vm_run = event VM, called from game_C8950.c) */
static int cur_ev = -1;
void __real_event_vm_run(void *blk, s32 entry);
void __wrap_event_vm_run(void *blk, s32 entry) {
    int sv = cur_ev;
    /* blk is the script block (no id in it): tell the events of this route apart by their entry offsets +0x10 / +0x12
     * (ROM headers: CA 003E 0114, BF 00A0 01DC, CB 0190 01E0) */
    unsigned h8 = blk ? vbe_ld16((u8 *)blk + 0x10) : 0, h9 = blk ? vbe_ld16((u8 *)blk + 0x12) : 0;
    cur_ev = h8 == 0x3E && h9 == 0x114 ? 0xCA : h8 == 0xA0 && h9 == 0x1DC ? 0xBF : h8 == 0x190 && h9 == 0x1E0 ? 0xCB : 0x1000 | h8;
    if (on() && cur_ev == 0xBF) {   /* P178: which BF instance runs, its flags (on change, and from 22760) */
        static unsigned nb; static void *lb[8]; static unsigned lf[8];
        int j, chg = 1; unsigned fl = vbe_ld16(blk);
        for (j = 0; j < 8 && lb[j]; j++) if (lb[j] == blk) { chg = lf[j] != fl; break; }
        if (j < 8) { lb[j] = blk; lf[j] = fl; }
        if ((chg || port_frame_count >= 22760) && nb++ < 80) port_log("[p178bf] frame %u VM BF blk %08x entry %d flags %04x (before)\n", port_frame_count,
                                (unsigned)(uintptr_t)blk, (int)entry, vbe_ld16(blk));
    }
    __real_event_vm_run(blk, entry);
    cur_ev = sv;
}
/* native 5: D_80088838[n - 1](id & 0xFFFF0FFF, args[1], args) */
s32 __real_event_native_query(s32 *args);
s32 __wrap_event_native_query(s32 *args) {
    if (!on()) return __real_event_native_query(args);
    s32 id = args[0], arg = args[1], n = (id & 0xF000) >> 12;
    s32 r = __real_event_native_query(args), ra = r, fixed = 0;
    if (n == 1) { ra = asm_CBD8(id & 0xFFF, arg); }
    else if (n == 14 && (id & 0xFFF) == 0x19 && arg == 4) { ra = asm_DFCC19(); }
    if (on()) {
        /* one line per (id, arg) whenever its result (C or asm) changes */
        static s32 kid[64], karg[64], kr[64], kra[64]; static int nk; static unsigned nlog;
        s32 kk = id ^ (cur_ev << 20);
        int j; for (j = 0; j < nk; j++) if (kid[j] == kk && karg[j] == arg) break;
        if (j == nk && nk < 64) { kid[nk] = kk; karg[nk] = arg; kr[nk] = 0x7FFFFFFF; kra[nk] = 0x7FFFFFFF; nk++; }
        if (j < 64 && (kr[j] != r || kra[j] != ra) && nlog++ < 600) {
            port_log("[p174ev] frame %u ev %X q5 id %04X arg %d -> C %d asm %d%s (EA %u C4 %u scene 40B8 %u 3A08 %u 3A92 %u)\n",
                     port_frame_count, cur_ev, id & 0xFFFF, arg, r, ra, fixed ? " FIXED" : "", vbe_ld8(&D_800C35EA),
                     vbe_ld8(&g_cutscene_pending), vbe_ld8(&D_800C40B8), vbe_ld8(&D_800C3A08), vbe_ld8(&D_800C3A92));
            kr[j] = r; kra[j] = ra;
        }
    }
    return r;
}
/* native 6: game-state actions D_80088874[n - 1](id & 0xFFFF0FFF, args[1], args) */
s32 __real_event_native_action(s32 *args);
extern u8 D_800877B0[]; extern s32 D_800D3268; extern u8 *D_800D2E4C; void *event_find(s32);
static void p178fin(const char *w, s32 id) {   /* P178: state around action 1 (finish event) */
    u8 *e = (u8 *)event_find(id);
    port_log("[p178bf] frame %u %s 5%03X(1): 877B0[1] %u running %X save[%X] %02x bit %u ev %08x flags %04x\n", port_frame_count, w,
             (unsigned)id, vbe_ld8(D_800877B0 + 1), (unsigned)D_800D3268, (unsigned)(id >> 3),
             D_800D2E4C ? vbe_ld8(D_800D2E4C + (id >> 3)) : 0xFFu, (unsigned)(id & 7), (unsigned)(uintptr_t)e, e ? vbe_ld16(e) : 0);
}
s32 __wrap_event_native_action(s32 *args) {
    static unsigned nf;
    int fin = on() && (args[0] & 0xF000) == 0x5000 && args[1] == 1 && nf < 40;
    if (fin) nf++, p178fin("before", args[0] & 0xFFF);
    s32 r = __real_event_native_action(args);
    if (fin) p178fin("after ", args[0] & 0xFFF);
    if (on()) {
        static unsigned nlog; static s32 lid[1024], la1[1024]; static int nl;
        /* one line per (id, arg1) pair seen first (the menu's 0x2000 action runs every 4 retraces) */
        int j; for (j = 0; j < nl; j++) if (lid[j] == (args[0] & 0xFFFF) && la1[j] == args[1]) break;
        /* P212: repeats of a seen pair are no longer logged (level 0x29's A06F every 4 retraces used up the cap by 23413) */
        if (j == nl && nl < 1024) { lid[nl] = args[0] & 0xFFFF; la1[nl] = args[1]; nl++; } else j = -1;   /* table full: no more lines */
        if (j >= 0 && nlog++ < 1000)
            port_log("[p174ev] frame %u ev %X act6 id %04X args %d %d %d -> %d\n", port_frame_count, cur_ev, args[0] & 0xFFFF, args[1],
                     args[2], args[3], r);
    }
    return r;
}

/* P174 ?p174ev: pointer probe before objects_update_visibility (game_83300.c; it calls obj_check_visible per active object): the
 * pointers obj_check_visible dereferences (obj +0x144, D_800D2104[obj +0x13F] if D_800D2528[obj +0x13F], D_800D1C90[id]),
 * logged when outside the wasm memory (raw N64 addresses / garbage) - the trap at 10732 with ?p174fix (scene 3 of
 * level 0x18). Up to 40 lines. */
extern u8 g_objects[]; /* was D_800CC2D0 */
extern s32 *D_800D2104;
extern u8 *D_800D2528;
extern u8 *D_800D1C90[];
extern s32 D_80082FA0;
static int badp(unsigned p) { return p != 0 && (p < 0x1000 || p >= 0x16000000u); }
void __real_objects_update_visibility(void);
void __wrap_objects_update_visibility(void) {
    if (on()) {
        static unsigned nlog, nfr;
        if (port_frame_count >= 10731 && nfr < 16) {
            char b[1600]; int k = 0;
            for (int i = 0; i < 0x19; i++) { u8 *o = g_objects + 0x32C * i; if (*(s32 *)o) k += snprintf(b + k, sizeof b - k, " %d:id%u/74=%x/13F=%u/on%u/p%08x", i, vbe_ld8(o + 4), vbe_ld8(o + 0x74), vbe_ld8(o + 0x13F), D_800D2528 ? vbe_ld8(D_800D2528 + vbe_ld8(o + 0x13F)) : 99, D_800D2104 ? (unsigned)D_800D2104[vbe_ld8(o + 0x13F)] : 0); }
            k += snprintf(b + k, sizeof b - k, " | D2528 %08x D2104 %08x", (unsigned)(uintptr_t)D_800D2528, (unsigned)(uintptr_t)D_800D2104);
            nfr++; port_log("[p174ptr] frame %u D_80082FA0 %d objs%s\n", port_frame_count, D_80082FA0, b);
        }
        for (int i = 0; i < 0x19 && nlog < 40; i++) {
            u8 *o = g_objects + 0x32C * i;
            if (*(s32 *)o == 0) continue;
            unsigned id = vbe_ld8(o + 4), k = vbe_ld8(o + 0x13F), p144 = *(unsigned *)(o + 0x144);
            unsigned on2528 = D_800D2528 ? vbe_ld8(D_800D2528 + k) : 0xFFFF, p2104 = D_800D2104 ? (unsigned)D_800D2104[k] : 0;
            unsigned p1c90 = (unsigned)(uintptr_t)D_800D1C90[id];
            if (badp(p144) || badp(p1c90) || badp((unsigned)(uintptr_t)D_800D2528) || badp((unsigned)(uintptr_t)D_800D2104) ||
                (on2528 && on2528 != 0xFFFF && badp(p2104)))
                nlog++, port_log("[p174ptr] frame %u obj %d state %d id %u +144 %08x 13F %u D2528 %08x [%u] D2104 %08x [%08x] D1C90[id] %08x\n",
                                 port_frame_count, i, *(s32 *)o, id, p144, k, (unsigned)(uintptr_t)D_800D2528, on2528,
                                 (unsigned)(uintptr_t)D_800D2104, p2104, p1c90);
        }
    }
    __real_objects_update_visibility();
}
