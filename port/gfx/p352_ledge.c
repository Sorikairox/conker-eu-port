/* P352 TEST aids for the ledge grab (called from p205_obj_hook, i.e. once per frame of Conker's look callback; nothing
 * happens without the flags):
 *   ?p352=F[&p352n=N]  from retrace F, for N retraces (default 600), one line per call with player record 0's position,
 *                      y velocity (+0x20), height above the floor (+0x28), heading (+0x7A), animation (+0x84), the ledge
 *                      state (+0x137: 0 none, 1 hanging, 2 climbing up, 0xFF just landed from a climb), the ledge results
 *                      of this frame's wall pass (g_wall_ledge_h_neg / _h_pos) and in_water; once, the acos table check.
 *                      Ledge-state changes are logged again as [p352ev] lines.
 *   ?p352tpf=F&p352tpx=X&p352tpy=Y&p352tpz=Z[&p352yaw=DEG]  once at retrace F: puts Conker at (X, Y, Z), speeds 0,
 *                      heading DEG degrees (u16 heading DEG * 65536 / 360: 0 faces +x, 90 -z, 180 -x, 270 +z) (changes the
 *                      game: test only).
 *   ?p352hang=...      pad script once Conker hangs (p352_pad_apply below). */
#include <stdint.h>
#include <stdio.h>
#include <emscripten.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern unsigned char g_objects[];          /* was D_800CC2D0 */
extern float g_wall_ledge_h_neg;           /* was D_800CC214 */
extern float g_wall_ledge_h_pos;           /* was D_800CC218 */
extern float g_wall_ledge_angle_neg, g_wall_ledge_angle_pos, g_wall_ledge_grab_x, g_wall_ledge_grab_z;

EM_JS(int, __port_p352_hang_char, (int i), {
    var v = null;
    if (typeof location !== 'undefined') { var m = /[?&]p352hang=([^&]*)/.exec(location.search); if (m) v = decodeURIComponent(m[1]); }
    return v === null || i >= v.length ? 0 : v.charCodeAt(i);
});
static float F(const unsigned char *r, int o) { return *(const float *)(r + o); }

void p352_ledge_probe(void) {
    static int f = -2, n, tpf;
    static int last137 = -1;
    unsigned char *r = g_objects;
    if (f == -2) {
        f = port_flag("p352");
        n = port_flag("p352n");
        if (n <= 0) n = 600;
        tpf = port_flag("p352tpf");
    }
    static int kdone;
    if (f > 0 && port_frame_count >= (unsigned)f && !kdone++) {
        /* the acos table check of the P352 n64mem fix: N64 values 32768 32442, pi/2 for acos(0) */
        extern unsigned char g_acos_table_coarse[];
        extern float math_atan2f(float, float), math_acosf_lut(float);
        port_log("[p352] acos table %u %u, acos(0) %g, atan2(1, -1e-6) %g\n", vbe_ld16(g_acos_table_coarse),
                 vbe_ld16(g_acos_table_coarse + 2), math_acosf_lut(0), math_atan2f(1, -1e-6f));
    }
    if (tpf > 0 && port_frame_count >= (unsigned)tpf) {
        int yaw = port_flag("p352yaw");
        unsigned h = (unsigned)((yaw % 360 + 360) % 360 * 65536 / 360) & 0xFFFF;
        tpf = 0;
        *(float *)(r + 0x14) = (float)port_flag("p352tpx");
        *(float *)(r + 0x18) = (float)port_flag("p352tpy");
        *(float *)(r + 0x1C) = (float)port_flag("p352tpz");
        *(float *)(r + 0x20) = 0.0f;
        vbe_st16(r + 0x76, h);
        vbe_st16(r + 0x7A, h);
        *(float *)(r + 0x40) = (float)(h + 0x4000) * 0.005493164f;   /* +0x40 heading in degrees, as obj_state_walk sets it */
        port_log("[p352] frame %u teleport to %.0f %.0f %.0f heading 0x%04X\n", port_frame_count, F(r, 0x14), F(r, 0x18),
                 F(r, 0x1C), h);
    }
    if (f <= 0 || port_frame_count < (unsigned)f || port_frame_count >= (unsigned)(f + n)) return;
    {
        int s137 = vbe_ld8(r + 0x137);
        port_log("[p352] %u pos %.1f %.1f %.1f vy %.1f h %.1f hd %04X anim %X ledge %d hneg %.0f hpos %.0f water %d\n",
                 port_frame_count, F(r, 0x14), F(r, 0x18), F(r, 0x1C), F(r, 0x20), F(r, 0x28), vbe_ld16(r + 0x7A),
                 vbe_ld16(r + 0x84), s137, g_wall_ledge_h_neg, g_wall_ledge_h_pos, vbe_ld8(r + 0xAD));
        if (s137 != last137) {
            port_log("[p352ev] %u ledge state %d -> %d at %.1f %.1f %.1f anim %X heading %04X (%.1f deg) | probe angle %.1f / %.1f grab %.1f %.1f\n",
                     port_frame_count, last137, s137, F(r, 0x14), F(r, 0x18), F(r, 0x1C), vbe_ld16(r + 0x84),
                     vbe_ld16(r + 0x7A), F(r, 0x40), g_wall_ledge_angle_neg, g_wall_ledge_angle_pos, g_wall_ledge_grab_x,
                     g_wall_ledge_grab_z);
            last137 = s137;
        }
    }
}

/* P352 TEST ?p352hang=WAIT:BTN:SX:SY:DUR (hex BTN, e.g. 8000 = A, 2000 = Z): called first by p205_goto_apply (pad 0
 * after ?padf). From the first retrace Conker hangs (+0x137 == 1) the pad is neutral for WAIT retraces, then holds BTN
 * and stick SX, SY for DUR retraces, then is neutral for good; the ?p205goto autopilot is off from the hang on.
 * Returns 1 while it owns the pad. */
int p352_pad_apply(int *btn, int *sx, int *sy) {
    static int cfg = -1, wait, b, x, y, dur;
    static unsigned hang_f;
    if (cfg < 0) {
        char s[64]; int n = 0, c;
        extern int __port_p352_hang_char(int);
        while (n < 63 && (c = __port_p352_hang_char(n)) != 0) s[n++] = (char)c;
        s[n] = 0;
        cfg = n > 0 && sscanf(s, "%d:%x:%d:%d:%d", &wait, &b, &x, &y, &dur) == 5;
        if (cfg) port_log("[p352] hang script: wait %d, buttons %X stick %d,%d for %d\n", wait, b, x, y, dur);
    }
    if (!cfg) return 0;
    if (!hang_f) {
        if (vbe_ld8(g_objects + 0x137) != 1) return 0;
        hang_f = port_frame_count;
        port_log("[p352] retrace %u: hanging, script starts\n", hang_f);
    }
    *btn = 0; *sx = 0; *sy = 0;
    if (port_frame_count >= hang_f + wait && port_frame_count < hang_f + wait + dur) { *btn = b; *sx = x; *sy = y; }
    return 1;
}
