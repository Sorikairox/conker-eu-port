/* Indirect-call self-test (docs/port/MEMORY.md, "Indirect calls"). Compiled like a game TU (vbe
 * pass + icall rewrite), so every call below goes through the generated trampolines.
 *
 * Calls real entries of a function-pointer table from the ROM's game_data, D_8008FC10 (the
 * characterflamethrower effect handlers, relocated to wasm table indices at load), through
 * pointer types that do *not* match the targets. Without the icall pass each mismatched call is a
 * wasm `call_indirect` signature trap.
 *   [0] f32 func_15197F68(s32) { return 1.32f; }
 *   [2] f32 func_15197FD8(s32) { return 10.9f; }
 *   [11] void func_151992EC(s32) { }
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
static void check(const char *what, u32 got, u32 want) {
    if (got != want) fails++;
    port_log("[icalltest] %-34s got %08X want %08X %s\n", port_gstr(what), got, want,
             port_gstr(got == want ? "ok" : "FAIL"));
}
static u32 fbits(f32 f) { union { f32 f; u32 u; } x; x.f = f; return x.u; }

int port_icalltest(void) {
    void **t = (void **)port_n64_to_wasm(0x8008FC10);
    union { f64 d; u32 w[2]; } d;
    fails = port_icall_check() ? 1 : 0;
    check("[0] as f32(s32) (exact)", fbits(((FnF_I)t[0])(5)), fbits(1.32f));
    check("[2] as f32(s32) (exact)", fbits(((FnF_I)t[2])(5)), fbits(10.9f));
    check("[0] as s32(s32): f32 -> bits", (u32)((FnI_I)t[0])(5), fbits(1.32f));
    check("[2] as f32(void): missing arg", fbits(((FnF_V)t[2])()), fbits(10.9f));
    check("[11] as f32(s32): void -> 0", fbits(((FnF_I)t[11])(7)), 0);
    check("[11] as s32(s32,s32,s32,s32): extra", (u32)((FnI_IIII)t[11])(1, 2, 3, 4), 0);
    ((FnV_V)t[0])();
    check("[0] as void(void): no trap", 1, 1);
    d.d = ((FnD_III)t[2])(1, 2, 3);
    d.d = d.d - (f64)10.9f; /* f32 result widened to f64 */
    check("[2] as f64(s32,s32,s32): fpext", d.d == 0.0, 1);
    port_log("[icalltest] %s (%d failures)\n", port_gstr(fails ? "FAIL" : "PASS"), fails);
    return fails;
}
