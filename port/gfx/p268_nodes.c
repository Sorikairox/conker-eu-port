/* P268 DIAGNOSTIC ?p268nodes=1: validates the render-node lists D_800DD280[2][104] (game_1944C0: u8 list index +0,
 * u8 group +1, prev +4, next +8) before and after the per-frame node update (node_lists_run_update) and before the node draw
 * (node_render_layers_draw). The first broken link is logged with the node bytes and the JS stack, once per phase. */
#include <stdint.h>
#include <string.h>
#include "../ultra/pc_mem.h"

extern unsigned port_frame_count;
int port_flag(const char *name);
void port_log(const char *fmt, ...);
void port_js_stack(int skip, int n);
extern unsigned char D_800DD280_[] __asm__("D_800DD280");

static int on = -1, logged;
static unsigned W(const unsigned char *r, int o) { unsigned v; memcpy(&v, r + o, 4); return v; }
static int bad_ptr(unsigned p) { return p < 0x10000000u || p >= 0x10000000u + 96u * 1024 * 1024 || (p & 3); }

static void dump(const char *tag, unsigned p) {
    if (bad_ptr(p)) return;
    const unsigned char *q = (const unsigned char *)(uintptr_t)p;
    port_log("[p268]   %s %08X: %08X %08X %08X %08X %08X %08X %08X %08X | %08X %08X %08X %08X %08X %08X %08X %08X\n", tag, p,
             W(q, 0), W(q, 4), W(q, 8), W(q, 12), W(q, 16), W(q, 20), W(q, 24), W(q, 28),
             W(q, 0x30), W(q, 0x34), W(q, 0x38), W(q, 0x3C), W(q, 0x40), W(q, 0x44), W(q, 0x48), W(q, 0x4C));
    port_log("[p268]   %s heap header: %08X %08X %08X\n", tag, W(q - 0xC, 0), W(q - 0xC, 4), W(q - 0xC, 8));
}

static int check(const char *where) {
    int g, i, n;
    for (g = 0; g < 2; g++)
        for (i = 0; i < 104; i++) {
            unsigned prev = 0, p = W(D_800DD280_, (g * 104 + i) * 4);
            for (n = 0; p && n < 20000; n++) {
                const char *why = 0;
                if (bad_ptr(p)) why = "bad pointer";
                else {
                    const unsigned char *q = (const unsigned char *)(uintptr_t)p;
                    if (q[0 ^ 3] != i) why = "list index";
                    else if (q[1 ^ 3] != g) why = "group";
                    else if (W(q, 4) != prev) why = "prev";
                    else if ((W(q - 0xC, 8) >> 24) == 0) why = "freed block";
                }
                if (why) {
                    if (logged++ < 6) {
                        port_log("[p268] %s frame %u: list [%d][%d] node #%d %08X (prev %08X): %s\n", where, port_frame_count,
                                 g, i, n, p, prev, why);
                        dump("node", p); dump("prev", prev);
                        port_js_stack(1, 8);
                    }
                    return 1;
                }
                prev = p; p = W((const unsigned char *)(uintptr_t)p, 8);
            }
        }
    return 0;
}

/* The update loop of node_lists_run_update (game_1944C0), re-done here with a list check after every handler call, so the
 * first handler that breaks a list is named (its type j and node). Same order and cursor protocol as the game C. */
extern unsigned char D_8008B4A8_[] __asm__("D_8008B4A8");
extern unsigned char D_800DD5C8_[] __asm__("D_800DD5C8");
extern signed char D_800DD5C0_ __asm__("D_800DD5C0");
#define D_800DD5C0 (*(signed char *)((uintptr_t)&D_800DD5C0_ ^ 3))   /* vbe: game bytes live at address ^ 3 */
void __real_node_lists_run_update(void);
void __wrap_node_lists_run_update(void) {
    int i, j;
    if (on < 0) on = port_flag("p268nodes");
    if (!on) { __real_node_lists_run_update(); return; }
    check("before update");
    for (i = 0; i < 2; i++)
        for (j = 0; j < 101; j++) {
            void (*fn)(void *) = (void (*)(void *))(uintptr_t)W(D_8008B4A8_, j * 0x34);
            unsigned node;
            if (!fn) continue;
            node = W(D_800DD280_, (i * 104 + j) * 4);
            D_800DD5C0++;
            while (node) {
                unsigned *cur = (unsigned *)(D_800DD5C8_ + D_800DD5C0 * 4);
                *cur = W((const unsigned char *)(uintptr_t)node, 8);
                if (on == 2 && j == 77) {   /* P269 ?p268nodes=2: cheap mode, only type-77 nodes, watch the 0x20 bytes past the block */
                    const unsigned char *q = (const unsigned char *)(uintptr_t)node;
                    unsigned sz = W(q - 0xC, 8) & 0xFFFFFF, k, before[8];
                    static unsigned seen[64]; static int nseen, nhit;
                    unsigned key = sz << 8 ^ vbe_ld8(q + 0x2F) << 16 ^ vbe_ld8(q + 0x30) << 4 ^ (vbe_ld8(q + 0x24) & 0xF) ^ (unsigned)(*(unsigned short *)((uintptr_t)(q + 0x1E) ^ 2)) << 24;
                    for (k = 0; k < (unsigned)nseen && seen[k] != key; k++) ;
                    if (k == (unsigned)nseen && nseen < 64) { seen[nseen++] = key;
                        port_log("[p269] type77 frame %u node %08X size %X +1E %04X +24 %d +2F %d +30 %d +31 %d +25 %d\n", port_frame_count, node, sz,
                                 *(unsigned short *)((uintptr_t)(q + 0x1E) ^ 2), (signed char)vbe_ld8(q + 0x24), vbe_ld8(q + 0x2F), vbe_ld8(q + 0x30), vbe_ld8(q + 0x31), vbe_ld8(q + 0x25)); }
                    for (k = 0; k < 8; k++) before[k] = W(q, sz + k * 4);
                    fn((void *)(uintptr_t)node);
                    for (k = 0; k < 8; k++) if (W(q, sz + k * 4) != before[k] && nhit++ < 20) {
                        port_log("[p269] OVERRUN frame %u node %08X size %X: +%X %08X -> %08X | +1E %04X +24 %d +2F %d +30 %d +2C %d +2D %d +2E %d +25 %d\n", port_frame_count, node, sz,
                                 sz + k * 4, before[k], W(q, sz + k * 4), *(unsigned short *)((uintptr_t)(q + 0x1E) ^ 2), (signed char)vbe_ld8(q + 0x24),
                                 vbe_ld8(q + 0x2F), vbe_ld8(q + 0x30), (signed char)vbe_ld8(q + 0x2C), (signed char)vbe_ld8(q + 0x2D), (signed char)vbe_ld8(q + 0x2E), vbe_ld8(q + 0x25));
                        dump("handled", node); dump("handled+80", node + 0x80); dump("handled+98", W(q, 0x98)); dump("handled+94", W(q, 0x94)); }
                    node = *(unsigned *)(D_800DD5C8_ + D_800DD5C0 * 4);
                    continue;
                }
                if (on == 2) { fn((void *)(uintptr_t)node); node = *(unsigned *)(D_800DD5C8_ + D_800DD5C0 * 4); continue; }
                fn((void *)(uintptr_t)node);
                if (!logged && check("after handler")) { const unsigned char *q = (const unsigned char *)(uintptr_t)node;
                    port_log("[p268]   handler of type %d (group %d) on node %08X: +1E %04X +24 %d +2F %d +30 %d +20 %08X\n", j, i, node,
                             *(unsigned short *)((uintptr_t)(q + 0x1E) ^ 2), (signed char)vbe_ld8(q + 0x24), vbe_ld8(q + 0x2F), vbe_ld8(q + 0x30), W(q, 0x20));
                    dump("handled", node); dump("handled+380", node + 0x380); }
                node = *(unsigned *)(D_800DD5C8_ + D_800DD5C0 * 4);
            }
            D_800DD5C0--;
        }
}
void *__real_node_render_layers_draw(void *gdl, int group, short a2, int list);
void *__wrap_node_render_layers_draw(void *gdl, int group, short a2, int list) {
    if (on < 0) on = port_flag("p268nodes");
    if (on) check("before draw");
    return __real_node_render_layers_draw(gdl, group, a2, list);
}

/* P269 DIAGNOSTIC (?p268nodes=2): the three behaviours of the type-77 trail nodes of fx_carrier_attach_trail (game_eu_204F70),
 * each checked for writes past the node's heap block (8 words from the block end), with the ring state before. */
static void p269_beh(const char *name, int (*real)(void *), int *ret, unsigned char *q) {
    unsigned sz = W(q - 0xC, 8) & 0xFFFFFF, k, before[8];
    signed char c = vbe_ld8(q + 0x2C), o = vbe_ld8(q + 0x2D), h = vbe_ld8(q + 0x2E);
    static int nhit;
    for (k = 0; k < 8; k++) before[k] = W(q, sz + k * 4);
    *ret = real(q);
    if (on != 2) return;
    for (k = 0; k < 8; k++) if (W(q, sz + k * 4) != before[k] && nhit++ < 20) {
        port_log("[p269] %s wrote past node %08X (size %X): +%X %08X -> %08X | before +2C %d +2D %d +2E %d, after +2C %d +2D %d +2E %d, +25 %d +1E %04X ret %d\n",
                 name, (unsigned)(uintptr_t)q, sz, sz + k * 4, before[k], W(q, sz + k * 4), c, o, h, (signed char)vbe_ld8(q + 0x2C),
                 (signed char)vbe_ld8(q + 0x2D), (signed char)vbe_ld8(q + 0x2E), vbe_ld8(q + 0x25), *(unsigned short *)((uintptr_t)(q + 0x1E) ^ 2), *ret);
        dump("ring", W(q, 0x94)); dump("state", W(q, 0x98));
        port_js_stack(1, 6);
    }
}
int __real_glow_trail_points_update(void *); int __real_glow_trail_emit_points(void *); int __real_glow_trail_limit_length(void *);
int __wrap_glow_trail_points_update(void *o) { int r; p269_beh("glow_trail_points_update", __real_glow_trail_points_update, &r, o); return r; }
int __wrap_glow_trail_emit_points(void *o) { int r; p269_beh("glow_trail_emit_points", __real_glow_trail_emit_points, &r, o); return r; }
int __wrap_glow_trail_limit_length(void *o) { int r; p269_beh("glow_trail_limit_length", __real_glow_trail_limit_length, &r, o); return r; }
