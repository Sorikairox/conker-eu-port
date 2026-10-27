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
    {   /* P334 TEST ?p334aim=T (e.g. 0x18): from retrace 120 on, keeps Conker's context-pad kind (player record +0x31C,
         * +0x75) at T, as standing on a weapon pad would. Pressing B then takes the item (player_item_action ->
         * player_try_begin_action: +0x78 = T) and holding R (0x10) enters that kind's aim mode
         * (camera_update_aim_mode / camera_look_enter) without a level route.
         * ?p334log=1: every 30 retraces logs kind, item phase, aim state +0x197, look state +0x198, the camera's copy of the
         * kind, and in first-person aim the fire ray (record +0x13C / +0x130) next to the camera eye and look vector. */
        static int aim = -1, aimlog = -1, resets;
        static unsigned last334;
        unsigned char *st = (unsigned char *)(uintptr_t) * (const unsigned *)(r + 0x31C);
        if (aim < 0) aim = port_flag("p334aim");
        if (aimlog < 0) aimlog = port_flag("p334log");
        if (aim > 0 && st && port_frame_count >= 120 && vbe_ld8(st + 0x7C) != (unsigned)aim) {
            vbe_st8(st + 0x7C, aim);
            resets++;
        }
        if (aimlog > 0 && st && port_frame_count - last334 >= 30) {
            last334 = port_frame_count;
            extern unsigned g_player_views; /* struct108 *, was D_800DBFF0 */
            const unsigned char *cam = (const unsigned char *)(uintptr_t)g_player_views;
            port_log("[p334] frame %u kind 0x%x phase %d aim %d look %d yaw %.1f pitch %.1f | cam type 0x%x mode %d "
                     "flags 0x%x tgt %d | obj 104 %d h28 %.1f 65 %d resets %d\n", port_frame_count,
                     vbe_ld8(st + 0x78), vbe_ld8(st + 0x11A), vbe_ld8(st + 0x197), vbe_ld8(st + 0x198), F(st, 0x16C),
                     F(st, 0x170), vbe_ld8(cam + 0x23E), (short)vbe_ld16(cam + 0x73C), *(const unsigned *)(cam + 0x2C),
                     *(const unsigned *)(cam + 0x3D4) == (unsigned)(uintptr_t)st, vbe_ld8(r + 0x104), F(r, 0x28),
                     vbe_ld8(r + 0x65), resets);
            if (vbe_ld8(st + 0x197) == 2)   /* fire ray (obj_ray_cast_from_ctl) vs the aim camera's eye / look target */
                port_log("[p334] ray from %.1f %.1f %.1f dir %.4f %.4f %.4f | cam eye %.1f %.1f %.1f at-eye %.4f %.4f %.4f\n",
                         F(st, 0x13C), F(st, 0x140), F(st, 0x144), F(st, 0x130), F(st, 0x134), F(st, 0x138),
                         F(cam, 0x2F8), F(cam, 0x2FC), F(cam, 0x300), F(cam, 0x2BC) - F(cam, 0x2F8),
                         F(cam, 0x2C0) - F(cam, 0x2FC), F(cam, 0x2C4) - F(cam, 0x300));
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
