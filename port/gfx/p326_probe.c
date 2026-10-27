/* P326 TEST ?p326=1 (called from p205_obj_hook, i.e. once per frame of Conker's look callback): measures the two
 * gameplay options "Longer breath" and "Longer tail spin" on player record 0 (Conker, g_objects[0], struct127):
 *   - air: logs the water entry / exit (+0xAD in_water), the air counter +0xB2 every 100 ticks and every health
 *     change (+0x1CA) while under water, with the frame step g_frame_ticks the counter grows by;
 *   - tail spin: logs every change of the helicopter counter ctl +0x31 (ctl = +0x31C): 1 = jumped, 3 = spin started,
 *     0 = dropped. The hover length is the frame of "-> 0" minus the frame of "-> 3".
 * ?p326sink=N (TEST ONLY, changes the game): while Conker is in water (in_water 1) his x / z are held at the entry
 * point and his y N below the water
 * surface (+0x118), y_velocity / gravity 0, and the "float water" flags of the state block are cleared, as if the player
 * kept diving in diving water, so the air runs out without a dive route. */
#include <stdint.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern unsigned char g_objects[]; /* was D_800CC2D0 */
extern int g_frame_ticks; /* was D_800BE9E4 */

static float F(const unsigned char *r, int o) { return *(const float *)(r + o); }

void p326_probe(void) {
    static int f = -1, fs = -1;
    static unsigned lastlog, lastlog2;
    static float hx, hz;
    static int water = -1, health = -1, glide = -1, lastair = -1;
    unsigned char *r = g_objects;
    const unsigned char *ctl;
    int w, h, air, g;
    if (f < 0) f = port_flag("p326");
    if (fs < 0) fs = port_flag("p326sink");
    if (f <= 0) return;
    {   /* P332 TEST ?p326tpf=F&p326tpx=X&p326tpz=Z: once, at retrace F, puts Conker at (X, -60, Z) (P333: Y from ?p326tpy) (e.g. over the
         * 0x29 river at 855, -1056) so a ?warp run reaches water without a route */
        static int tpf = -1;
        if (tpf < 0) tpf = port_flag("p326tpf");
        if (tpf > 0 && port_frame_count >= (unsigned)tpf) {
            tpf = 0;
            *(float *)(r + 0x14) = (float)port_flag("p326tpx");
            {   /* P333: ?p326tpy=Y sets the height too (default -60), e.g. high above dry ground for a hard landing */
                int tpy = port_flag("p326tpy");
                *(float *)(r + 0x18) = tpy ? (float)tpy : -60.0f;
            }
            *(float *)(r + 0x1C) = (float)port_flag("p326tpz");
            port_log("[p326] frame %u teleport to %.0f %.0f\n", port_frame_count, F(r, 0x14), F(r, 0x1C));
        }
    }
    w = vbe_ld8(r + 0xAD);
    {   /* P333 TEST ?p326nofloat=1 (changes the game): while Conker is in water, clears the "float water" flags of the
         * state block (+0x20 bit 0, +0x21) so the 0x29 river can be dived in. ?p333=1: every 20 retraces in water, logs
         * the swim state (interaction_state +0, entry flag +0x102), y, y_velocity, gravity and body pitch +0xB8. */
        static int nofloat = -1, swimlog = -1;
        static unsigned last333;
        unsigned char *st = (unsigned char *)(uintptr_t) * (const unsigned *)(r + 0x31C);
        if (nofloat < 0) nofloat = port_flag("p326nofloat");
        if (swimlog < 0) swimlog = port_flag("p333");
        if (nofloat > 0 && w && st) { vbe_st8(st + 0x20, vbe_ld8(st + 0x20) & ~1u); vbe_st8(st + 0x21, 0); }
        if (swimlog > 0 && w && port_frame_count - last333 >= 20) {
            last333 = port_frame_count;
            port_log("[p333] frame %u state %d e102 %d y %.1f vy %.2f grav %.3f pitch %.1f surf %.1f\n", port_frame_count,
                     *(const int *)r, vbe_ld8(r + 0x102), F(r, 0x18), F(r, 0x20), F(r, 0x24), F(r, 0xB8), F(r, 0x118));
        }
    }
    h = vbe_ld8(r + 0x1CA);
    air = vbe_ld16(r + 0xB2);
    {
        const unsigned char *st = (const unsigned char *)(uintptr_t) * (const unsigned *)(r + 0x31C);
        if (fs > 0 && w && st && port_frame_count - lastlog2 >= 50) {
            lastlog2 = port_frame_count;
            port_log("[p326] frame %u before: y %.1f top %d st20 %d st21 %d air %d\n", port_frame_count, F(r, 0x18),
                     (short)vbe_ld16(r + 0x1A6), vbe_ld8(st + 0x20), vbe_ld8(st + 0x21), air);
        }
    }
    if (fs > 0 && w == 1 && F(r, 0x118) != -10000.0f) {
        if (water != 1) { hx = F(r, 0x14); hz = F(r, 0x1C); }   /* x / z held at the water entry point */
        *(float *)(r + 0x14) = hx;
        *(float *)(r + 0x1C) = hz;
        *(float *)(r + 0x18) = F(r, 0x118) - (float)fs;
        *(float *)(r + 0x20) = 0.0f;
        *(float *)(r + 0x24) = 0.0f;
        {   /* the 0x29 river is "float" water: state block +0x20 bit 0 / +0x21 keep Conker at the top and the air
             * at 0 (no diving there); clear them so swim_water_physics runs its air / drowning code */
            unsigned char *st = (unsigned char *)(uintptr_t) * (const unsigned *)(r + 0x31C);
            if (st) { vbe_st8(st + 0x20, vbe_ld8(st + 0x20) & ~1u); vbe_st8(st + 0x21, 0); }
        }
    }
    if (w != water) {
        port_log("[p326] frame %u water %d -> %d air %d health %d y %.1f surface %.1f step %d\n", port_frame_count, water,
                 w, air, h, F(r, 0x18), F(r, 0x118), g_frame_ticks);
        water = w;
    }
    if (w && port_frame_count - lastlog >= 200) {
        lastlog = port_frame_count;
        const unsigned char *st = (const unsigned char *)(uintptr_t) * (const unsigned *)(r + 0x31C);
        port_log("[p326] frame %u y %.1f top %d st20 %d st21 %d air %d\n", port_frame_count, F(r, 0x18),
                 (short)vbe_ld16(r + 0x1A6), st ? vbe_ld8(st + 0x20) : -1, st ? vbe_ld8(st + 0x21) : -1, air);
    }
    if (w && (h != health || air / 100 != lastair / 100))
        port_log("[p326] frame %u air %d health %d\n", port_frame_count, air, h);
    health = h;
    lastair = air;
    ctl = (const unsigned char *)(uintptr_t) * (const unsigned *)(r + 0x31C);
    if (!ctl) return;
    g = vbe_ld8(ctl + 0x31);
    if (g != glide && (g <= 3 || glide <= 1))
        port_log("[p326] frame %u spin %d -> %d y %.1f\n", port_frame_count, glide, g, F(r, 0x18));
    glide = g;
}
