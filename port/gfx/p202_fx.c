/* P202 DIAGNOSTIC ?p202fx=N: character effects (port-b P197 made func_1518DC50 character_effect_update C).
 *  - func_1518D1C0 character_effect_attach (cross-TU calls only: game_eu_17A800 character spawn handlers, game_eu_51190
 *    event tracks, game_eu_1C1A20 impacts, game_981E0): frame, owner, owner id (+0x3B), position, type, time, clear,
 *    view, returned record. First N calls in detail, then every 64th.
 *  - func_1513D524 (particle spawn, all callers): count per 500 frames, to see whether effects spawn anything. */
#include <stdint.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;

static int fl = -1;
static int on(void) { if (fl < 0) fl = port_flag("p202fx"); return fl; }

void *__real_func_1518D1C0(void *obj, short type, short time, unsigned char clear, unsigned char view, int arg5, char *name);
void *__wrap_func_1518D1C0(void *obj, short type, short time, unsigned char clear, unsigned char view, int arg5, char *name) {
    static unsigned n, per[32];
    void *r = __real_func_1518D1C0(obj, type, time, clear, view, arg5, name);
    if (!on()) return r;
    n++; per[type & 31]++;
    if (n <= (unsigned)fl || n % 64 == 0) {
        const unsigned char *o = obj;
        port_log("[p202fx] attach %u frame %u: obj %08X id %02X pos %.1f %.1f %.1f type %d time %d clear %u view %02X a5 %d -> rec %08X (type count %u)\n",
                 n, port_frame_count, (unsigned)(uintptr_t)obj, o ? vbe_ld8(o + 0x3B) : 0, o ? *(const float *)(o + 0x14) : 0.f,
                 o ? *(const float *)(o + 0x18) : 0.f, o ? *(const float *)(o + 0x1C) : 0.f, type, time, clear, view, arg5,
                 (unsigned)(uintptr_t)r, per[type & 31]);
    }
    return r;
}

void *__real_func_1513D524(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
void *__wrap_func_1513D524(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
    static unsigned n, nok, last;
    void *r = __real_func_1513D524(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    if (!on()) return r;
    n++; if (r) nok++;
    if (port_frame_count / 500 != last) {
        last = port_frame_count / 500;
        port_log("[p202fx] spawn func_1513D524: %u calls, %u records by frame %u\n", n, nok, port_frame_count);
    }
    return r;
}
