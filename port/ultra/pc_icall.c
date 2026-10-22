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

void port_icall_note(void *fp, unsigned tsig, int n, unsigned k, unsigned rk) {
    if (port_icall_slow_calls++ < 16) {
        char b[24];
        port_log("[icall] signature mismatch: fn #%u is %s, called as %s (converted)\n",
                 (unsigned)(uintptr_t)fp, port_fsig_name(tsig), site_str(n, k, rk, b));
    }
}

void port_icall_report(void) {
    port_log("[icall] %u functions registered (%u beyond table cap, %u re-registered with another signature), "
             "%u mismatched calls converted\n", fsig_regs, fsig_over, fsig_clash, port_icall_slow_calls);
}
