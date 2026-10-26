/* P81 runtime checks of port P76 C (look target, attachment draw).
 *  ?p81look=N   after each look_frame_cb_current (Conker's per-frame look callback, via p69's wrap): slot g_look_cb_calls, target
 *               g_look_target_point, aim point g_look_aim_point, record +0x2CA, LookTrack (+0x324) yaw / pitch / hold / fade of
 *               the slots, and the joint 7 / 12 matrices (+0x1D4): row lengths and translation (the slerp blend must
 *               keep them). First N calls, then every 64th and every call where a blend (fade) runs (first 300).
 *  ?p81att=N    attachment_draw_all_for_player / attachment_draw_for_object (attachment passes of game_eu_5D910.c, called from game_eu_595D0.c):
 *               commands written, G_DL part lists and the segment 3 matrix found in them, plus the attachment list
 *               g_attachment_list (+0 model, +2 joint, +7 callback, +0x1C timer, +0x1E sub model, +3 alpha, +5 visible, +0x13 / +0x14 mask / parts, +0x24 part DLs). First N
 *               calls, then every 256th.
 *  DIAGNOSTIC ?p81noatt=1  the two attachment passes return the display list unchanged (nothing drawn). */
#include <stdint.h>
#include <math.h>
#include <emscripten.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern unsigned char g_objects[]; /* was D_800CC2D0 */
extern unsigned char D_800C441A_[] __asm__("g_look_cb_calls"); /* was D_800C441A */
extern unsigned char D_800C4408_[] __asm__("g_look_target_point"); /* was D_800C4408 */
extern unsigned char D_800C43F0_[] __asm__("g_look_aim_point"); /* was D_800C43F0 */
extern unsigned char D_800C3E78_[] __asm__("g_cur_obj_index"); /* was D_800C3E78 */
extern unsigned char D_800C3EE0_[] __asm__("g_attachment_list"); /* was D_800C3EE0 */
extern unsigned char D_800C6A70_[] __asm__("g_look_points"); /* was D_800C6A70 */
extern unsigned char D_800C6A74_[] __asm__("g_look_points_count"); /* was D_800C6A74 */
extern unsigned char D_800C35EA_[] __asm__("g_cutscene_slot_state"); /* was D_800C35EA */

#define REC 0x32C
static unsigned W(const unsigned char *r, int o) { return *(const unsigned *)(r + o); }
static float F(const unsigned char *r, int o) { return *(const float *)(r + o); }
static int flag(int *f, const char *n) { if (*f < 0) *f = port_flag(n); return *f; }
static int flook = -1, fatt = -1, fnoatt = -1;

static void joint(const char *tag, const unsigned char *mtx, int j) {
    const float *m = (const float *)(mtx + j * 64);
    float l0 = sqrtf(m[0] * m[0] + m[1] * m[1] + m[2] * m[2]), l1 = sqrtf(m[4] * m[4] + m[5] * m[5] + m[6] * m[6]),
          l2 = sqrtf(m[8] * m[8] + m[9] * m[9] + m[10] * m[10]);
    float d01 = m[0] * m[4] + m[1] * m[5] + m[2] * m[6];
    port_log("[p81] %s j%d rows %.3f %.3f %.3f dot01 %.3f row0 %.3f %.3f %.3f T %.1f %.1f %.1f w %.2f\n", tag, j, l0,
             l1, l2, d01, m[0], m[1], m[2], m[12], m[13], m[14], m[15]);
}

/* called by p69_checks.c's __wrap_look_frame_cb_current before (pre = 1) and after (pre = 0) the real function */
void p81_look_hook(int pre) {
    static unsigned n, nb;
    static int slot0;
    int id = vbe_ld8(D_800C3E78_), s, fade = 0;
    const unsigned char *r, *lt, *mtx;
    {   /* P189 TEST ONLY ?p189y=F: from frame F, 240 calls: Conker's state, y, y_velocity (+0x20), gravity (+0x24),
         * +0x28, floor (+0x118), in_water (+0xAD), +0x31C, xz_velocity */
        static int fy = -1, fsw = -1; static unsigned ny;
        /* P189 TEST ONLY ?p189swim=1: stand-in for the asm stub swim_water_physics (swim update, called by the C
         * obj_state_walk while in_water != 0): keep a swimming Conker at the water surface (+0x118 - 25) instead of
         * letting the buoyancy (gravity -3) accelerate him upward forever. */
        if (flag(&fsw, "p189swim") && !pre && id <= 64) {
            unsigned char *q = g_objects + id * REC;
            float surf = F(q, 0x118);
            if (vbe_ld8(q + 0xAD) == 1 && surf != -10000.0f && F(q, 0x18) > surf - 25.0f) {
                *(float *)(q + 0x18) = surf - 25.0f;
                *(float *)(q + 0x20) = 0.0f;
                *(float *)(q + 0x24) = 0.0f;
            }
        }
        if (flag(&fy, "p189y") && !pre && id <= 64 && port_frame_count >= (unsigned)fy && ny++ < 240) {
            const unsigned char *q = g_objects + id * REC;
            port_log("[p189y] frame %u st %08x y %.2f vy %.3f g %.3f u28 %.3f floor %.2f water %d u31C %08x xzv %.2f old_y %.2f\n",
                     port_frame_count, W(q, 0), F(q, 0x18), F(q, 0x20), F(q, 0x24), F(q, 0x28), F(q, 0x118),
                     vbe_ld8(q + 0xAD), W(q, 0x31C), F(q, 0x3C), F(q, 0x30));
        }
    }
    if (!pre) { extern void p205_obj_hook(void); p205_obj_hook(); }
    if (!flag(&flook, "p81look") || id > 64) return;
    r = g_objects + id * REC;
    if (pre) { slot0 = vbe_ld8(D_800C441A_); return; }
    lt = (const unsigned char *)(uintptr_t)W(r, 0x324);
    mtx = (const unsigned char *)(uintptr_t)W(r, 0x1D4);
    if (!lt) return;
    n++;
    for (s = 0; s < 3; s++) fade |= vbe_ld8(lt + 0x33 + s);
    if (!(n <= (unsigned)flook || n % 64 == 0 || (fade && nb++ < 300))) return;
    port_log("[p81] look %u frame %u rec %d slot %d->%d target %.1f %.1f %.1f aim %.1f %.1f %.1f b2CA %d pos %.1f %.1f %.1f\n",
             n, port_frame_count, id, slot0, vbe_ld8(D_800C441A_), F(D_800C4408_, 0), F(D_800C4408_, 4),
             F(D_800C4408_, 8), F(D_800C43F0_, 0), F(D_800C43F0_, 4), F(D_800C43F0_, 8), (signed char)vbe_ld8(r + 0x2CA),
             F(r, 0x14), F(r, 0x18), F(r, 0x1C));
    if (n <= (unsigned)flook || n % 64 == 0) {
        const unsigned char *lp = (const unsigned char *)(uintptr_t)W(D_800C6A70_, 0);
        unsigned np = W(D_800C6A74_, 0), k;
        port_log("[p81]   inputs: look points %u at %p, cutscene %d %d\n", np, (void *)lp, vbe_ld8(D_800C35EA_),
                 vbe_ld8(D_800C35EA_ + 1));
        for (k = 0; lp && k < np && k < 3; k++)
            port_log("[p81]   lp[%u] %d %d %d unk6 %u range2 %u x window %d..%d anim %d\n", k,
                     (short)vbe_ld16(lp + k * 0x14), (short)vbe_ld16(lp + k * 0x14 + 2), (short)vbe_ld16(lp + k * 0x14 + 4),
                     vbe_ld16(lp + k * 0x14 + 6), W(lp + k * 0x14, 8), (short)vbe_ld16(lp + k * 0x14 + 0x10),
                     (short)vbe_ld16(lp + k * 0x14 + 0xE), (short)vbe_ld16(lp + k * 0x14 + 0x12));
    }
    for (s = 0; s < 3; s++)
        port_log("[p81]   lt[%d] yaw %.2f pitch %.2f vel %.2f %.2f hold %d fade %d ofs %d %d\n", s, F(lt, 4 * s),
                 F(lt, 0xC + 4 * s), F(lt, 0x18 + 4 * s), F(lt, 0x24 + 4 * s), vbe_ld8(lt + 0x30 + s),
                 vbe_ld8(lt + 0x33 + s), (short)vbe_ld16(lt + 0x3A + 2 * s), (short)vbe_ld16(lt + 0x40 + 2 * s));
    if (mtx) { joint("look", mtx, 7); joint("look", mtx, 12); joint("look", mtx, 0); }
}

static void att_log(const char *fn, unsigned n, unsigned in, unsigned out, int a1, int a2) {
    const unsigned char *g = (const unsigned char *)(uintptr_t)in, *a;
    int cmds = (int)(out - in) / 8, dls = 0, k = 0;
    unsigned mtx = 0, first_dl = 0;
    for (; g < (const unsigned char *)(uintptr_t)out; g += 8) {
        unsigned w0 = W(g, 0), w1 = W(g, 4);
        if (w0 == 0xDE000000u) { if (!dls++) first_dl = w1; }
        if (w0 == 0xDB06000Cu) mtx = w1;
    }
    port_log("[p81] att %s %u frame %u t %.0f ms args %d %d: %d cmds, %d part DLs (first %08X), seg3 mtx %08X\n", fn, n,
             port_frame_count, emscripten_get_now(), a1, a2, cmds, dls, first_dl, mtx);
    for (a = (const unsigned char *)(uintptr_t)W(D_800C3EE0_, 0); a && k < 8; a = (const unsigned char *)(uintptr_t)W(a, 0x54), k++)
        port_log("[p81]   att#%d %p model %d joint %d cb %d timer %04X sub %d | alpha %d vis %d mask %02X parts %d dl0 %08X seg1 %08X tex %04X %04X\n", k,
                 (void *)a, vbe_ld8(a), vbe_ld8(a + 2), vbe_ld8(a + 7), vbe_ld16(a + 0x1C), vbe_ld16(a + 0x1E), vbe_ld8(a + 3), vbe_ld8(a + 5), vbe_ld8(a + 0x13), vbe_ld8(a + 0x14),
                 W(a, 0x24) ? W((const unsigned char *)(uintptr_t)W(a, 0x24), 0) : 0, W(a, 0x28), vbe_ld16(a + 0x18),
                 vbe_ld16(a + 0x1A));
}

int __real_attachment_draw_all_for_player(int gdl, int a1, int a2);
int __wrap_attachment_draw_all_for_player(int gdl, int a1, int a2) {
    static unsigned n, drew, listed;
    int out = flag(&fnoatt, "p81noatt") ? gdl : __real_attachment_draw_all_for_player(gdl, a1, a2);
    n++;
    unsigned sig = 0;
    static unsigned lastsig;
    const unsigned char *a;
    if (out != gdl) drew++;
    for (a = (const unsigned char *)(uintptr_t)W(D_800C3EE0_, 0); a; a = (const unsigned char *)(uintptr_t)W(a, 0x54))
        sig = sig * 31 + (unsigned)(uintptr_t)a + vbe_ld8(a + 5) + vbe_ld8(a + 7) * 7;
    if (flag(&fatt, "p81att") && (n <= (unsigned)fatt || n % 256 == 0 || (out != gdl && drew <= 12) ||
                                  (sig != lastsig && listed++ < 40))) {
        lastsig = sig;
        att_log("10F8", n, (unsigned)gdl, (unsigned)out, a1, a2);
        port_log("[p81]   (%u of %u calls drew)\n", drew, n);
    }
    return out;
}

int __real_attachment_draw_for_object(int gdl, unsigned char *obj, int a2, int a3);
int __wrap_attachment_draw_for_object(int gdl, unsigned char *obj, int a2, int a3) {
    static unsigned n;
    int out = flag(&fnoatt, "p81noatt") ? gdl : __real_attachment_draw_for_object(gdl, obj, a2, a3);
    n++;
    if (flag(&fatt, "p81att") && (n <= (unsigned)fatt || n % 256 == 0))
        att_log("1284", n, (unsigned)gdl, (unsigned)out, obj ? (int)((obj - g_objects) / REC) : -1, a2);
    return out;
}

/* P189 TEST ONLY ?p189nopush=1: obj_floor_push_turn (swim_push_update, C since port P179; an asm stub = no-op in the port
 * before) returns without doing anything, as before the merge. Without the flag: the real function, plus a log
 * of the first 40 calls that set a push (+0xF8 bits 19/20) when ?p189y is on. */
void __real_obj_floor_push_turn(unsigned char *obj);
void __wrap_obj_floor_push_turn(unsigned char *obj) {
    static int fnp = -1, fy2 = -1; static unsigned n;
    if (flag(&fnp, "p189nopush")) return;
    if (flag(&fy2, "p189y") && n < 40 && port_frame_count >= (unsigned)fy2) {
        n++;
        port_log("[p189push] frame %u id %d F8 %08x u28 %.2f before 164 %.3f 168 %.3f\n", port_frame_count, vbe_ld8(obj + 4),
                 W(obj, 0xF8), F(obj, 0x28), F(obj, 0x164), F(obj, 0x168));
        __real_obj_floor_push_turn(obj);
        port_log("[p189push]   after 164 %.3f 168 %.3f\n", F(obj, 0x164), F(obj, 0x168));
        return;
    }
    __real_obj_floor_push_turn(obj);
}
