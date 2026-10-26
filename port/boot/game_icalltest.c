/* Indirect-call self-test (docs/port/MEMORY.md, "Indirect calls"). Compiled like a game TU (vbe
 * pass + icall rewrite), so every call below goes through the generated trampolines.
 *
 * Calls real entries of a function-pointer table from the ROM's game_data, D_8008FC10 (the
 * characterflamethrower effect handlers, relocated to wasm table indices at load), through
 * pointer types that do *not* match the targets. Without the icall pass each mismatched call is a
 * wasm `call_indirect` signature trap.
 *   [0] f32 emitter_speed_const_a(s32) { return 1.32f; }
 *   [2] f32 emitter_speed_const_b(s32) { return 10.9f; }
 *   [11] void emitter_sound_noop(s32) { }
 * port_icall_check() (generated, port/stubs/icall_tab.c) additionally checks that the registry
 * gives the right signature for every C-defined entry of five ROM tables. */
#include <ultra64.h>
#include "../ultra/pc_mem.h"

void port_glog(const char *fmt, ...);
#define port_log port_glog
const char *port_gstr(const char *gamestr);
int port_icall_check(void);

typedef f32 (*FnF_I)(s32);
typedef s32 (*FnI_I)(s32);
typedef void (*FnV_V)(void);
typedef f32 (*FnF_V)(void);
typedef f64 (*FnD_III)(s32, s32, s32);
typedef s32 (*FnI_IIII)(s32, s32, s32, s32);

static int fails;
static void ict_check(const char *what, u32 got, u32 want) {
    if (got != want) fails++;
    port_log("[icalltest] %-34s got %08X want %08X %s\n", port_gstr(what), got, want,
             port_gstr(got == want ? "ok" : "FAIL"));
}
static u32 fbits(f32 f) { union { f32 f; u32 u; } x; x.f = f; return x.u; }

/* P29: view_background_draw's camera callback site (port P28, game_eu_13DC30.c:104):
 *   gdl = D_80089578[D_800B0DF0->unk8](gdl, x, y, z, yaw, pitch, roll, handle);
 * typed Gfx *(*)(Gfx *, f32 x6, s32), i.e. the wasm site i:iffffffi. o32 (int first argument): the 3 first
 * floats travel as bits in a1..a3, the rest on the stack, so a C callee written with int parameters must
 * see the float bit patterns. Both an exact-typed and an int-typed callee are called through that site. */
typedef Gfx *(*FnCam)(Gfx *, f32, f32, f32, f32, f32, f32, s32);
static u32 cam_seen[8];
static Gfx *cam_exact(Gfx *g, f32 x, f32 y, f32 z, f32 a, f32 b, f32 c, s32 h) {
    cam_seen[0] = (u32)g; cam_seen[1] = fbits(x); cam_seen[2] = fbits(y); cam_seen[3] = fbits(z);
    cam_seen[4] = fbits(a); cam_seen[5] = fbits(b); cam_seen[6] = fbits(c); cam_seen[7] = (u32)h;
    return g + 3;
}
static s32 cam_ints(s32 g, s32 x, s32 y, s32 z, s32 a, s32 b, s32 c, s32 h) {
    cam_seen[0] = g; cam_seen[1] = x; cam_seen[2] = y; cam_seen[3] = z;
    cam_seen[4] = a; cam_seen[5] = b; cam_seen[6] = c; cam_seen[7] = h;
    return g + 5 * 8;
}
static void cam_site_check(const char *what, void *fn, int adv) {
    static const f32 v[6] = { 1.5f, -2.25f, 1000.0f, -179.5f, 359.0f, 0.125f };
    Gfx buf[8];
    Gfx *r;
    volatile FnCam f = (FnCam)fn;
    int bad = 0, i;
    for (i = 0; i < 8; i++) cam_seen[i] = 0xDEADBEEF;
    r = f(buf, v[0], v[1], v[2], v[3], v[4], v[5], 0x1234567);
    if (cam_seen[0] != (u32)buf || cam_seen[7] != 0x1234567) bad++;
    for (i = 0; i < 6; i++) if (cam_seen[1 + i] != fbits(v[i])) bad++;
    ict_check(what, bad, 0);
    ict_check("  ... returned gdl advance", (u32)((u8 *)r - (u8 *)buf), adv * 8);
}

int port_icalltest(void) {
    void **t = (void **)port_n64_to_wasm(0x8008FC10);
    union { f64 d; u32 w[2]; } d;
    fails = port_icall_check() ? 1 : 0;
    ict_check("[0] as f32(s32) (exact)", fbits(((FnF_I)t[0])(5)), fbits(1.32f));
    ict_check("[2] as f32(s32) (exact)", fbits(((FnF_I)t[2])(5)), fbits(10.9f));
    ict_check("[0] as s32(s32): f32 -> bits", (u32)((FnI_I)t[0])(5), fbits(1.32f));
    ict_check("[2] as f32(void): missing arg", fbits(((FnF_V)t[2])()), fbits(10.9f));
    ict_check("[11] as f32(s32): void -> 0", fbits(((FnF_I)t[11])(7)), 0);
    ict_check("[11] as s32(s32,s32,s32,s32): extra", (u32)((FnI_IIII)t[11])(1, 2, 3, 4), 0);
    ((FnV_V)t[0])();
    ict_check("[0] as void(void): no trap", 1, 1);
    d.d = ((FnD_III)t[2])(1, 2, 3);
    d.d = d.d - (f64)10.9f; /* f32 result widened to f64 */
    ict_check("[2] as f64(s32,s32,s32): fpext", d.d == 0.0, 1);
    cam_site_check("cam cb exact i:iffffffi", (void *)cam_exact, 3);
    cam_site_check("cam cb as s32 x8 (slow path)", (void *)cam_ints, 5);
    { void **ct = (void **)port_n64_to_wasm(0x80089578); /* the ROM table D_80089578 */
      extern const char *port_fsig_of(void *fp);
      int i;
      for (i = 0; i < 4; i++)
          port_log("[icalltest] D_80089578[%d] = fn #%u sig %s\n", i, (u32)ct[i], port_fsig_of(ct[i])); }
    port_log("[icalltest] %s (%d failures)\n", port_gstr(fails ? "FAIL" : "PASS"), fails);
    return fails;
}
