/* P223 DIAGNOSTIC ?p223hit=N: knock-back check. Wraps obj_receive_hit (object_receive_hit, game_83300.c; its callers are
 * in game_8FCB0.c, so --wrap sees them): logs the first N calls (then every 32nd) with the attacker / target records
 * (index into g_objects, id, uid), the target's reaction type (+0x239), the hit descriptor (kind, handler, damage,
 * push, xz / y speed), the result bits, and the target's speeds / angle / health / stun before and after. After a
 * landed hit the target is followed for 60 frames (position + speeds every 6 frames) from p205_obj_hook. */
#include <stdint.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern unsigned char g_objects[]; /* was D_800CC2D0 */
#define REC 0x32C
static float F(const unsigned char *r, int o) { return *(const float *)(r + o); }
static int on(void) { static int f = -1; if (f < 0) f = port_flag("p223hit"); return f; }
static int recno(const unsigned char *r) {
    long d = r - g_objects;
    return d >= 0 && d < 26 * REC && d % REC == 0 ? (int)(d / REC) : -1;
}
static const unsigned char *fol; static unsigned fol_f;

static void st(const char *w, const unsigned char *o) {
    port_log("[p223hit]   %s pos %.1f %.1f %.1f vy %.2f vxz %.2f ang %04X hp %u stun %u 10B %02X 109 %02X\n", w,
             F(o, 0x14), F(o, 0x18), F(o, 0x1C), F(o, 0x20), F(o, 0x3C), vbe_ld16(o + 0x76), vbe_ld8(o + 0x1CA),
             vbe_ld8(o + 0x104), vbe_ld8(o + 0x10B), vbe_ld8(o + 0x109));
}

int __real_obj_receive_hit(void *self, void *obj, void *descs, int idx, int slot, int hits, int mask);
int __wrap_obj_receive_hit(void *self, void *obj, void *descs, int idx, int slot, int hits, int mask) {
    static unsigned n;
    const unsigned char *s = self, *o = obj, *d = descs ? (const unsigned char *)descs + idx * 0x28 : 0;
    int r, lg;
    if (on() <= 0) return __real_obj_receive_hit(self, obj, descs, idx, slot, hits, mask);
    n++;
    lg = n <= (unsigned)on() || n % 32 == 0;
    if (lg) {
        port_log("[p223hit] call %u frame %u: self rec %d id %02X uid %02X -> obj rec %d id %02X uid %02X type %02X | desc %d kind %02X"
                 " handler %u dmg %02X push %02X xz %.2f y %.2f flags %04X | slot %d hits %X mask %X\n",
                 n, port_frame_count, recno(s), s ? vbe_ld8(s + 4) : 0, s ? vbe_ld8(s + 0x3B) : 0, recno(o), o ? vbe_ld8(o + 4) : 0,
                 o ? vbe_ld8(o + 0x3B) : 0, o ? vbe_ld8(o + 0x239) : 0, idx, d ? vbe_ld8(d) : 0, d ? vbe_ld8(d + 8) : 0,
                 d ? vbe_ld8(d + 0xF) : 0, d ? vbe_ld8(d + 0x10) : 0, d ? F(d, 0x14) : 0.f, d ? F(d, 0x18) : 0.f,
                 d ? vbe_ld16(d + 0x24) : 0, slot, (unsigned)hits, (unsigned)mask);
        if (d) { /* P252: the raw descriptor (0x28 bytes, N64 byte order) to find it in the ROM data, and the attacker's angle */
            char hx[0x28 * 2 + 1]; static const char H[] = "0123456789ABCDEF";
            for (int k = 0; k < 0x28; k++) { unsigned v = vbe_ld8(d + k); hx[2 * k] = H[v >> 4]; hx[2 * k + 1] = H[v & 15]; }
            hx[0x50] = 0;
            port_log("[p223hit]   desc bytes %s | self ang %04X pos %.1f %.1f %.1f\n", hx, s ? vbe_ld16(s + 0x76) : 0,
                     s ? F(s, 0x14) : 0.f, s ? F(s, 0x18) : 0.f, s ? F(s, 0x1C) : 0.f);
        }
        if (o) st("before", o);
    }
    r = __real_obj_receive_hit(self, obj, descs, idx, slot, hits, mask);
    if (lg) {
        port_log("[p223hit]   -> %X (%s)\n", (unsigned)r, r != hits ? "landed" : "no change");
        if (o) st("after ", o);
    }
    if (o && r != hits && (!fol || port_frame_count - fol_f > 60)) { fol = o; fol_f = port_frame_count; }
    return r;
}

/* called once per frame from p205_obj_hook */
void p223_hit_tick(void) {
    unsigned t;
    static unsigned lastf = ~0u;
    if (!fol || on() <= 0) return;
    if (lastf == port_frame_count) return; /* P252: the hook runs twice in some frames; one line per frame */
    lastf = port_frame_count;
    t = port_frame_count - fol_f;
    if (t > 60) { fol = 0; return; }
    if (t % 6 == 0) {
        char w[24];
        int k = 0; unsigned v = t;
        w[k++] = '+'; if (v >= 10) w[k++] = '0' + v / 10; w[k++] = '0' + v % 10; w[k] = 0;
        st(w, fol);
    }
}
