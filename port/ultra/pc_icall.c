/* Indirect-call signature registry (docs/port/MEMORY.md, "Indirect calls"; port/tools/icall.py).
 * A wasm function pointer is its index in the function table; port_fsig[index] holds the wasm
 * signature id of the function there (0 = unknown). Filled before main by the constructors of
 * every vbe-compiled TU and of the generated port/stubs/icall_tab.c. */
#include <stdint.h>
#include "pc_ultra.h"
#include "pc_icall.h"

#define FSIG_MAX (1 << 16)
static unsigned port_fsig[FSIG_MAX];
static unsigned fsig_regs, fsig_over, fsig_clash;
unsigned port_icall_slow_calls;

void __port_fsig_reg(const PortFsig *t, int n) {
    for (int i = 0; i < n; i++) {
        uintptr_t idx = (uintptr_t)t[i].fn;
        if (idx >= FSIG_MAX) { fsig_over++; continue; }
        if (port_fsig[idx] && port_fsig[idx] != t[i].sig) fsig_clash++;
        port_fsig[idx] = t[i].sig;
        fsig_regs++;
    }
}

unsigned __port_fsig(void *fp) {
    uintptr_t idx = (uintptr_t)fp;
    return idx < FSIG_MAX ? port_fsig[idx] : 0;
}

static const char *site_str(int n, unsigned k, unsigned rk, char *buf) {
    static const char L[] = "iIfd";
    char *p = buf;
    *p++ = rk == 4 ? 'v' : L[rk];
    *p++ = ':';
    for (int i = 0; i < n && i < 16; i++) *p++ = L[(k >> (2 * i)) & 3];
    *p = 0;
    return buf;
}

/* the generated port/stubs/icall_tab.c has the real one (the scheduler demo links without it) */
__attribute__((weak)) const char *port_fsig_name(unsigned id) { (void)id; return "?"; }

/* P29: the registered signature of a function pointer, for game-TU self-tests (icall.py owns __port_fsig there) */
const char *port_fsig_of(void *fp) { return port_fsig_name(__port_fsig(fp)); }

/* P373: a void function called through a value-returning pointer (rk != 4). On the N64 the caller reads whatever
 * the callee left in v0 / f0; here the result is 0 (port_icall_slow). P372's flame_flicker was such a case: the asm
 * returned 1, the port 0, and every flame died at once. Each such target must be audited (does the caller use the
 * value? what does the asm leave in v0?) and listed in port/tools/icall_void_audit.tsv; the generated
 * port_icall_void_audited() (port/stubs/icall_tab.c) knows the listed ones. Any other is logged once, with a count in
 * port_icall_report(); the test scripts fail on the "UNAUDITED" line. Log-only: the call itself is unchanged. */
__attribute__((weak)) const char *port_icall_void_audited(void *fp) { (void)fp; return 0; }
#define VOID_SEEN_MAX 256
static void *void_seen[VOID_SEEN_MAX];
static unsigned void_nseen, void_unaudited;

static void void_as_value(void *fp, unsigned tsig, int n, unsigned k, unsigned rk) {
    for (unsigned i = 0; i < void_nseen; i++)
        if (void_seen[i] == fp) return;
    if (void_nseen < VOID_SEEN_MAX) void_seen[void_nseen++] = fp;
    if (port_icall_void_audited(fp)) return;
    if (void_unaudited++ < 64) {
        char b[24];
        port_log("[icall] UNAUDITED void target fn #%u (%s) called as %s at retrace %u: reads 0 here, v0 on the N64 "
                 "(port/tools/icall_void_audit.tsv; name: port/tools/wasm_fn_name.py conker.wasm %u)\n",
                 (unsigned)(uintptr_t)fp, port_fsig_name(tsig), site_str(n, k, rk, b), port_frame_count, (unsigned)(uintptr_t)fp);
        port_js_stack(4, 4);   /* from __port_icall_slow: the trampoline, the calling game function, its caller */
    }
}

void port_icall_note(void *fp, unsigned tsig, int n, unsigned k, unsigned rk) {
    if (rk != 4 && port_fsig_name(tsig)[0] == 'v') void_as_value(fp, tsig, n, k, rk);
    if (port_icall_slow_calls++ < 16) {
        char b[24];
        port_log("[icall] signature mismatch: fn #%u is %s, called as %s (converted)\n",
                 (unsigned)(uintptr_t)fp, port_fsig_name(tsig), site_str(n, k, rk, b));
    }
}

void port_icall_report(void) {
    port_log("[icall] %u functions registered (%u beyond table cap, %u re-registered with another signature), "
             "%u mismatched calls converted, %u void targets called as values (%u unaudited)\n", fsig_regs, fsig_over,
             fsig_clash, port_icall_slow_calls, void_nseen, void_unaudited);
}
