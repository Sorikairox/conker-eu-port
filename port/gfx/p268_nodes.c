/* P268 DIAGNOSTIC ?p268nodes=1: validates the render-node lists D_800DD280[2][104] (game_1944C0: u8 list index +0,
 * u8 group +1, prev +4, next +8) before and after the per-frame node update (func_151670C0) and before the node draw
 * (func_151674F8). The first broken link is logged with the node bytes and the JS stack, once per phase. */
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

/* The update loop of func_151670C0 (game_1944C0), re-done here with a list check after every handler call, so the
 * first handler that breaks a list is named (its type j and node). Same order and cursor protocol as the game C. */
extern unsigned char D_8008B4A8_[] __asm__("D_8008B4A8");
extern unsigned char D_800DD5C8_[] __asm__("D_800DD5C8");
extern signed char D_800DD5C0_ __asm__("D_800DD5C0");
#define D_800DD5C0 (*(signed char *)((uintptr_t)&D_800DD5C0_ ^ 3))   /* vbe: game bytes live at address ^ 3 */
void __real_func_151670C0(void);
void __wrap_func_151670C0(void) {
    int i, j;
    if (on < 0) on = port_flag("p268nodes");
    if (!on) { __real_func_151670C0(); return; }
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
void *__real_func_151674F8(void *gdl, int group, short a2, int list);
void *__wrap_func_151674F8(void *gdl, int group, short a2, int list) {
    if (on < 0) on = port_flag("p268nodes");
    if (on) check("before draw");
    return __real_func_151674F8(gdl, group, a2, list);
}
