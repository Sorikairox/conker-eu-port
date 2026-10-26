/* P25 self-test of the PC libgu/libc layer (port/ultra/pc_gu.c, pc_libc.c). Compiled like a game TU
 * (vbe IR pass), so it calls the functions exactly as the game does and checks game memory with N64
 * semantics. Expected values: port/tools/gu_expect.py (N64 definitions, single precision).
 *   1. guMtxF2L on edge values (round to nearest even, negatives, -0, fractions only)
 *   2. guMtxL2F (game C) on fixed-point words, then guMtxF2L back: round trip
 *   3. guPerspective (game C -> game sinf + PC cosf + PC guMtxF2L) against the Python matrix
 *   4. guMtxF2L of a guLookAtF matrix computed in Python
 *   5. cosf bit-exact against the libultra polynomial; Rare's fast sin/cos against sin/cos
 *   6. bcopy / bzero at mismatched alignments on vbe memory */
#include <ultra64.h>
#include "../stubs/gutest_expect.h"

void port_glog(const char *fmt, ...);
#define port_log port_glog
float cosf(float);
float func_150AD78C(float);
float func_150AD780(float);
void mtx_set_identity(Mtx *); /* game_D5030.c (P131) */

static int cmp_words(int what, /* 1 F2L, 2 L2F, 3 L2F->F2L, 4 perspF, 5 persp, 6 lookat, 7 ident */ const u32 *got, const unsigned *want, int n) {
    int bad = 0, i;
    for (i = 0; i < n; i++)
        if (got[i] != want[i]) {
            if (bad < 4) port_log("[gutest] check %d word %d: %08X, want %08X\n", what, i, got[i], want[i]);
            bad++;
        }
    return bad;
}

static f32 fabs_(f32 x) { return x < 0 ? -x : x; }

int port_gu_test(void) {
    Mtx m;
    f32 mf[4][4];
    u16 pn = 0;
    int bad = 0, i;
    static u8 buf[24], src[16];
    static Mtx id;

    /* 1 */
    guMtxF2L((float (*)[4])gu_f2l_in, &m);
    bad += cmp_words(1, (u32 *)&m, gu_f2l_want, 16);
    /* 2 */
    for (i = 0; i < 16; i++) ((u32 *)&m)[i] = gu_l2f_in[i];
    guMtxL2F(mf, &m);
    bad += cmp_words(2, (u32 *)mf, gu_l2f_want, 16);
    guMtxF2L(mf, &m);
    bad += cmp_words(3, (u32 *)&m, gu_l2f_in, 16);
    /* 3 */
    guPerspectiveF(mf, &pn, 45.0f, 60.0f, 10.0f, 10000.0f, 1.0f);
    bad += cmp_words(4, (u32 *)mf, gu_persp_float, 16);
    pn = 0;
    guPerspective(&m, &pn, 45.0f, 60.0f, 10.0f, 10000.0f, 1.0f);
    bad += cmp_words(5, (u32 *)&m, gu_persp_want, 16);
    if (pn != GU_PERSP_NORM) { port_log("[gutest] perspNorm %04X, want %04X\n", pn, GU_PERSP_NORM); bad++; }
    /* 4 */
    guMtxF2L((float (*)[4])gu_look_in, &m);
    bad += cmp_words(6, (u32 *)&m, gu_look_want, 16);
    /* identity (mtx_set_identity) == F2L(identity) */
    guMtxIdentF(mf);
    guMtxF2L(mf, &id);
    mtx_set_identity(&m);
    bad += cmp_words(7, (u32 *)&m, (const unsigned *)&id, 16);
    /* 5 */
    for (i = 0; i < 10; i++) {
        f32 c = cosf(gu_cos_in[i]);
        if (*(u32 *)&c != gu_cos_want[i]) { port_log("[gutest] cosf #%d %08X, want %08X\n", i, *(u32 *)&c, gu_cos_want[i]); bad++; }
    }
    for (i = -40; i <= 40; i++) {
        f32 x = i * 0.1f;
        f32 s = func_150AD78C(x), c = func_150AD780(x), rs = sinf(x), rc = cosf(x);
        if (fabs_(s - rs) > 2e-6f || fabs_(c - rc) > 2e-6f) {
            if (bad < 8) port_log("[gutest] fast sin/cos(%d/10) %d %d, want %d %d (x1e6)\n", i, (int)(s * 1e6f), (int)(c * 1e6f), (int)(rs * 1e6f), (int)(rc * 1e6f));
            bad++;
        }
    }
    /* 6: bytes are N64 bytes (this TU is vbe) */
    for (i = 0; i < 16; i++) src[i] = 0x10 + i;
    for (i = 0; i < 24; i++) buf[i] = 0xEE;
    bcopy(src + 1, buf + 2, 13);
    for (i = 0; i < 24; i++) {
        u8 want = (i >= 2 && i < 15) ? 0x11 + (i - 2) : 0xEE;
        if (buf[i] != want) { if (bad < 8) port_log("[gutest] bcopy byte %d %02X, want %02X\n", i, buf[i], want); bad++; }
    }
    bcopy(buf + 2, buf + 3, 9); /* overlapping, forward */
    if (buf[3] != 0x11 || buf[11] != 0x19 || buf[2] != 0x11 || buf[12] != 0x1B) { port_log("[gutest] bcopy overlap wrong\n"); bad++; }
    bzero(buf + 1, 6);
    for (i = 0; i < 8; i++) {
        u8 want = (i >= 1 && i < 7) ? 0 : (i == 0 ? 0xEE : 0x15);
        if (buf[i] != want) { port_log("[gutest] bzero byte %d %02X, want %02X\n", i, buf[i], want); bad++; }
    }
    port_log(bad ? "[gutest] FAIL (%d failures)\n" : "[gutest] PASS (%d failures)\n", bad);
    return bad;
}
