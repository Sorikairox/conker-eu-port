/* libgu / libm pieces of the PC libultra layer (session P25). Native PC code, so game memory is
 * accessed through the virtual big-endian rules of docs/port/MEMORY.md: 32-bit words (Mtx words,
 * floats) are plain native accesses; nothing here touches a sub-word field.
 *
 * Every function is written from the game's own code (the EU ROM disassembly in conker/asm and the
 * decomp's C reconstruction of it), not copied from ultralib: see port/ultra/LICENSES.md.
 *
 *   guMtxF2L        libultra/gu/guMtxF2L.s   (Rare's unrolled version: cvt.w.s, i.e. round to nearest)
 *   (func_150A7B80 guMtxIdent: now game_D5030.c's NON_MATCHING C, P131)
 *   cosf            libultra/gu/cosf.s       (game TUs call it as vbe.cosf, port/tools/vbe.py LIBC_VBE)
 */
#include <stdint.h>
#include <string.h>
#include "pc_mem.h"

typedef union { uint32_t i; float f; } fu;

/* cvt.w.s with FCSR.RM = 0 (round to nearest even; __osInitialize leaves RM at 0). Out of range is an
 * "unimplemented operation" trap on the R4300; the PC saturates instead. */
static int32_t cvt_w_s(float x) {
    if (x != x) return 0x7FFFFFFF;
    if (x >= 2147483648.0f) return 0x7FFFFFFF;
    if (x < -2147483648.0f) return (int32_t)0x80000000;
    return (int32_t)__builtin_rintf(x);
}

/* Mtx (gbi.h): long m[4][4]; words 0..7 hold the integer halves, words 8..15 the fraction halves, two
 * elements per word, the even column in the high half. The asm stores halfwords (sh e at +0x20, sh
 * e>>16 at +0); composing the same two halves into one 32-bit word gives the identical big-endian
 * bytes, and a 32-bit word is a plain native store in vbe memory. */
int port_flag(const char *name);
void port_log(const char *fmt, ...);
void port_js_stack(int skip, int n);
unsigned port_gu_f2l_calls; /* P25: ?gulog=N logs the first N guMtxF2L calls with a stack */

void guMtxF2L(const float *mf, uint32_t *m) {
    static int gl = -1;
    if (gl < 0) gl = port_flag("gulog");
    if (gl && port_gu_f2l_calls < (unsigned)gl) {
        port_log("[gu] guMtxF2L #%u -> %p: %.3f %.3f %.3f %.3f | %.3f %.3f %.3f %.3f | ... | %.3f %.3f %.3f %.3f\n",
                 port_gu_f2l_calls, (void *)m, mf[0], mf[1], mf[2], mf[3], mf[4], mf[5], mf[6], mf[7],
                 mf[12], mf[13], mf[14], mf[15]);
        port_js_stack(2, 6);
    }
    port_gu_f2l_calls++;
    for (int k = 0; k < 8; k++) {
        uint32_t e1 = (uint32_t)cvt_w_s(mf[2 * k] * 65536.0f);
        uint32_t e2 = (uint32_t)cvt_w_s(mf[2 * k + 1] * 65536.0f);
        m[k] = (e1 & 0xFFFF0000u) | (e2 >> 16);
        m[k + 8] = (e1 << 16) | (e2 & 0xFFFFu);
    }
}

/* func_150A7B80 (guMtxIdent): removed in P131, game_D5030.c has the NON_MATCHING C (void (Mtx *)). */

/* ---- cosf (libultra; the game's copy: P in .rodata EU 0x23E3A0, scalars in .data 0x22B4C0; values
 * from the decomp's reconstruction in conker/src_eu/libultra/gu/cosf.c) ---- */
static const fu cP[] = { {0x3F800000}, {0xBE2AAAA6}, {0x3C088769}, {0xB94FB7FD}, {0x362EDEFA} };
static const fu c_rpi = {0x3EA2F984}, c_pihi = {0x40490FDC}, c_pilo = {0x330885A3};

float port_cosf(float x) __asm__("vbe.cosf");
float port_cosf(float x) {
    fu u = { .f = x };
    int xpt = ((int32_t)u.i >> 22) & 0x1FF;
    if (xpt < 0x136) {
        float absx = x > 0 ? x : -x;
        float dn = absx * c_rpi.f + 0.5f;
        int n = (int)((dn >= 0.0f) ? (dn + 0.5f) : (dn - 0.5f));
        dn = (float)n;
        dn = dn - 0.5f;
        float dx = absx - dn * c_pihi.f;
        dx = dx - dn * c_pilo.f;
        float xsq = dx * dx;
        float poly = ((cP[4].f * xsq + cP[3].f) * xsq + cP[2].f) * xsq + cP[1].f;
        float r = dx + (dx * xsq) * poly;
        return (n & 1) ? -r : r;
    }
    if (x != x) { fu q = {0x7FBFFFFF}; return q.f; } /* __libm_qnan_f */
    return 0.0f;
}

/* P26: Rare's fast sin/cos (func_150AD78C / func_150AD780, asm/D5E90.s) were PC copies here in P25.
 * The port branch now has them as game C (conker/src_eu/nm_asm/D5E90.c, P24), which wins. */
