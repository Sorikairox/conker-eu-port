/* P69 DIAGNOSTIC: ?p69pc=MASK runs the removed P63 PC versions instead of the P65 game C (bisecting the respawn
 * hang): 1 = func_1502AF04, 2 = func_150A69E0, 4 = func_1510E908 (link-time wraps; this TU goes through vbe like
 * pc_overrides.c). Without the flag the game C runs. */
#include <ultra64.h>
int port_flag(const char *name);
static int pcmask = -1;
static int m(int b) { if (pcmask < 0) pcmask = port_flag("p69pc"); return pcmask & b; }
/* P63: TEMPORARY PC func_1502AF04 (game_57FA0.c, asm, 76 lines; remove when the port branch converts it). The
 * animation header lookup of func_1505E0C4 (object model +0x58 path) and the last step of func_1502B110 (the
 * other path): reads n 8-byte records {offset, size} at base + index * 8 from ROM and makes their first words
 * absolute (+= base). As a gen_stubs stub it returned base itself, so func_1505E0C4 read garbage / no header and
 * Conker stayed in the bind pose. Read from the asm:
 *   src = base + index * 8;  dst = (buf + 8) & ~15;
 *   func_10004514(src & ~15, dst, ((src & 0xE) + n * 8 + 15) & ~15, 1);
 *   rec = dst + (src & 0xF);  for i < n: rec[2 * i] += base;  return rec. */
s32 func_10004514(s32, void *, u32, s32);
static s32 pc_1502AF04(s32 base, s32 buf, s32 index, s32 n) {
    u32 src = (u32)base + (u32)index * 8;
    u32 dst = ((u32)buf + 8) & ~15u;
    s32 *rec;
    s32 i;

    func_10004514(src & ~15u, (void *)dst, ((src & 0xE) + (u32)n * 8 + 15) & ~15u, 1);
    rec = (s32 *)(dst + (src & 0xF));
    for (i = 0; i < n; i++) {
        rec[i * 2] += base;
    }
    return (s32)rec;
}

/* P63: TEMPORARY PC func_150A69E0 (game_eu_D3880.c, asm, 13 instructions; remove when the port branch converts it):
 *   return func_150A6A48(a0, a1, a2, a3, a0, a1, -10000, 20000);
 * (the asm stores a0 / a1 / -10000 / 0x4E20 as the 5th..8th stack arguments and jumps to the C func_150A6A48). Its
 * caller func_15045A04 (game_eu_71E70.c) passes a2 = &count; as a gen_stubs stub the count stayed uninitialised
 * stack, and func_1504627C -> func_150A49D0(count, ...) walked a garbage id list: a "memory access out of bounds"
 * that came and went with the stack layout (seen in P63 with ?p49walk, frame 723). */
s32 func_150A6A48(s32, s32, s32 *, s32, s32, s32, s32, s32);
static s32 pc_150A69E0(s32 a0, s32 a1, s32 a2, s32 a3) {
    return func_150A6A48(a0, a1, (s32 *)a2, a3, a0, a1, -10000, 20000);
}

/* P63: TEMPORARY PC func_1510E908 (game_eu_13B700.c, asm, 188 lines; remove when the port branch converts it). The
 * floor-slope solver behind func_1510FDA0 (P60's func_15051558 floor push): for the floor triangle given either as
 * 3 vertex pointers (tris, s16 x/y/z each) or, when tris is NULL, as 3 packed s16 x/y/z vertices (verts, stride 6,
 * the record's +0x18C copy), it tries the edge pairs (P1 = v[i], P0 = v[i+1], P2 = v[i+2], i = 0..2, then the same
 * three with the two edges swapped) until one gives a non-degenerate system, and returns
 *   *outB = (e2.x * e1.y - e1.x * e2.y) / (e2.x * e1.z - e1.x * e2.z),  *outA = (e2.y - *outB * e2.z) / e2.x
 * (e1 = P0 - P1, e2 = P2 - P1), result 1; all degenerate (or the 6th try reached), or both inputs NULL: 0 / 0, result
 * 0. As a gen_stubs stub it wrote nothing, so func_1510FDA0's dx / dz were stack leftovers: on the flat start floor
 * of level 0x21 func_15051558 saw a "strong push" (dx^2 + dz^2 > 1) every frame, started a slide (D_800CC69C = 1,
 * +0x110 = 3, animation 0x28E) and pushed the player off the level (P63). Read from the asm instruction by instruction
 * (the 6th try forces "fail" even when it is not degenerate, as the asm does). */
static s32 pc_1510E908(s32 tris, s32 verts, f32 *outA, f32 *outB) {
    s32 t = 0, ok, i0, i1, i2, first;
    f32 e1x, e1y, e1z, e2x, e2y, e2z, sw, p, q;
    const s16 *P0, *P1, *P2;

    if (tris == 0 && verts == 0) {
        *outB = 0.0f;
        *outA = 0.0f;
        return 0;
    }
    for (;;) {
        ok = 1;
        i0 = (t < 3) ? t : t - 3;
        first = t < 3;
        i1 = (i0 == 2) ? 0 : i0 + 1;
        t++;
        i2 = (i1 == 2) ? 0 : i1 + 1;
        if (verts != 0) {
            P0 = (const s16 *)(verts + i1 * 6);
            P1 = (const s16 *)(verts + i0 * 6);
            P2 = (const s16 *)(verts + i2 * 6);
        } else {
            P0 = ((const s16 **)tris)[i1];
            P1 = ((const s16 **)tris)[i0];
            P2 = ((const s16 **)tris)[i2];
        }
        e1x = (f32)(P0[0] - P1[0]);
        e1y = (f32)(P0[1] - P1[1]);
        e1z = (f32)(P0[2] - P1[2]);
        e2x = (f32)(P2[0] - P1[0]);
        e2y = (f32)(P2[1] - P1[1]);
        e2z = (f32)(P2[2] - P1[2]);
        if (!first) {
            sw = e1x; e1x = e2x; e2x = sw;
            sw = e1y; e1y = e2y; e2y = sw;
            sw = e1z; e1z = e2z; e2z = sw;
        }
        p = e1x * e2z;
        q = e2x * e1z;
        if (p == q) ok = 0;
        if (e2x == 0.0f) ok = 0;
        if (t == 6) ok = 2;
        if (ok != 0) break;
    }
    if (ok == 2) {
        *outA = 0.0f;
        *outB = 0.0f;
        return 0;
    }
    *outB = (e2x * e1y - e1x * e2y) / (q - p);
    *outA = (e2y - *outB * e2z) / e2x;
    return 1;
}

s32 __real_func_1502AF04(s32, s32, s32, s32);
s32 __wrap_func_1502AF04(s32 a, s32 b, s32 c, s32 d) { return m(1) ? pc_1502AF04(a, b, c, d) : __real_func_1502AF04(a, b, c, d); }
s32 __real_func_150A69E0(s32, s32, s32, s32);
s32 __wrap_func_150A69E0(s32 a, s32 b, s32 c, s32 d) { return m(2) ? pc_150A69E0(a, b, c, d) : __real_func_150A69E0(a, b, c, d); }
s32 __real_func_1510E908(s32, s32, f32 *, f32 *);
s32 __wrap_func_1510E908(s32 a, s32 b, f32 *c, f32 *d) { return m(4) ? pc_1510E908(a, b, c, d) : __real_func_1510E908(a, b, c, d); }
