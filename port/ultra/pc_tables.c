/* P58: game tables that live in the code segment, which the PC build does not load (the game code is native wasm).
 *
 * D_150AA11C: the sine table of the skeleton evaluator anim_eval_joint_matrices (nm_asm/D5E90_anim.c; in the unsplit
 * asm/D5E90.s right after mtx_rotate_scale_3x3): 513 f32 = sin(k * pi / 1024), k = 0..512, a quarter turn. Before P58 it
 * was a zero-filled 0x100-byte data stub (port/stubs/data_stubs.c, weak), so every rotation came out 0: all joint
 * matrices had a zero 3x3 part and every joint sat at the root joint's position. The ROM values are sin rounded to
 * 6 decimals, with 12 entries on the other side of the rounding (the original generator's sin was less precise near
 * the half); the corrections and the checksum were taken from the ROM words, so the table here is bit-exact, which
 * port_tables_check() verifies at boot ([tables] PASS). */
#include <math.h>

void port_log(const char *fmt, ...);

float D_150AA11C[516] __attribute__((aligned(16)));

static const short sin_fix[][2] = {{158, 1}, {167, 1}, {186, 1}, {220, 1}, {291, -1}, {314, -1}, {355, -1},
                                   {402, 1}, {419, -1}, {428, 1}, {435, 1}, {455, -1}};

__attribute__((constructor)) static void pc_tables_init(void) {
    for (int k = 0; k <= 512; k++) {
        double n = nearbyint(sin(k * 3.14159265358979323846 / 1024.0) * 1e6);
        for (unsigned i = 0; i < sizeof sin_fix / sizeof sin_fix[0]; i++) if (sin_fix[i][0] == k) n += sin_fix[i][1];
        D_150AA11C[k] = (float)(n / 1e6);
    }
}

void port_tables_check(void) {
    unsigned s = 0;
    for (int k = 0; k <= 512; k++) { unsigned w; __builtin_memcpy(&w, &D_150AA11C[k], 4); s = s * 31 + w; }
    port_log("[tables] sine table D_150AA11C %s (checksum %08X, ROM D7187CC3)\n", s == 0xD7187CC3u ? "PASS" : "FAIL", s);
}
