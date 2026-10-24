#ifdef NON_MATCHING
s32 func_150ADA20(void);
extern f32 D_8008CFA0[3]; /* spread per variant: 571, 130, 130 */
extern u8 D_8008CFAC[9];  /* colour per variant (3 bytes) */

// quad_edge_sparks_spawn: walks the 4 edges of `quad` (4 points of 3 floats) and spawns `countA` (edges 0 / 2) or
// `countB` (edges 1 / 3) sparks evenly along each edge (func_1516DA58 type 0xD, variant `variant`'s colour): the
// spark's push is the edge midpoint relative to (x, z) (doubled, as hi / lo bytes), its speed 731 * size + rand
// modulo 836 * size, life 15..46, spread 143 * size + rand modulo D_8008CFA0[variant] * size. The caller's D_8008CF94 copy is unused.
void func_15170648(f32 *quad, f32 x, f32 z, s32 kind, f32 size, s32 variant, s32 countA, s32 countB, s32 alpha,
                   s32 owner) {
    f32 *p;
    f32 *q;
    u8 *col;
    s32 edge;
    s32 next;
    s32 n;
    s32 i;
    s32 range;
    s32 vx, vz;
    s32 speedBase, speedRange, spreadBase;
    s32 life;
    s32 speed;
    f32 mx, mz;
    f32 step;
    f32 t;
    f32 px, py, pz;

    range = (s32)(D_8008CFA0[variant] * size);
    p = quad;
    for (edge = 0; edge < 4; edge++, p += 3) {
        next = (edge == 3) ? 0 : edge + 1;
        n = (edge == 0 || edge == 2) ? countA : countB;
        q = &quad[next * 3];
        col = &D_8008CFAC[variant * 3];
        mx = (q[0] + p[0]) * 0.5f - x;
        mz = (q[2] + p[2]) * 0.5f - z;
        vx = (s32)(mx + mx);
        vz = (s32)(mz + mz);
        if (n <= 0) {
            continue;
        }
        speedBase = (s32)(731.0f * size);
        speedRange = (s32)(836.0f * size);
        spreadBase = (s32)(143.0f * size);
        step = 1.0f / (f32)(n - 1);
        for (i = 0; i < n; i++) {
            t = (f32)i * step;
            px = (q[0] - p[0]) * t + p[0];
            py = (q[1] - p[1]) * t + p[1];
            pz = (q[2] - p[2]) * t + p[2];
            life = (func_150ADA20() & 0x1F) + 15;
            speed = (u32)func_150ADA20() % (u32)speedRange + speedBase;
            func_1516DA58((s16)(s32)px, (s16)(s32)py, (s16)(s32)pz, 0xD, 0, col[0], col[1], col[2], 0, 0, 0, 0, 2,
                          (vx >> 8) & 0xFF, vx & 0xFF, (vz >> 8) & 0xFF, vz & 0xFF, 0, 0, kind, 0, 0, 0, speed, speed,
                          life, (u32)func_150ADA20() % (u32)range + spreadBase, 0, 0, alpha, owner);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_15170648.s")
#endif
