/* Path length of actor `actor` of cutscene slot `slot` (needs >= 2 path keys, D_800C39E8 count; keys are the
 * 8-byte records D_eu_800C3C88[slot][actor], +6 = segment shape). For every segment the 4 control points come
 * from func_15020090; keys[seg] (D_800C3E70 actor +4) = the length up to the segment's start. A curved segment
 * (shape 0) is measured as a Catmull-Rom curve sampled every 0.01 (chords between successive samples, the
 * previous sample in the other half of `prev`, which carries over between segments), a straight one as the
 * distance between its two middle points. +0 = the total length, keys[count - 1] = it too; +0x3C = 0xFF. */
void func_15020430(s32 actor, s32 slot) {
    SceneActor *act;
    s32 seg;
    s32 c;
    u16 shape;
    u8 cur;
    f32 total;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d;
    f32 pts[4][3];
    f32 A[3];
    f32 B[3];
    f32 C[3];
    f32 D[3];
    f32 prev[2][3];

    if (D_800C39E8[slot][actor] < 2) {
        return;
    }
    D_800C3E70[slot][actor].pad3C[0] = 0xFF;
    total = 0.0f;
    cur = 0;
    for (seg = 0; seg < D_800C39E8[slot][actor] - 1; seg++) {
        shape = *(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6);
        /* P87: the asm leaves the key count in a3; func_15020090 reads it (dropped argument) */
        func_15020090((u8 *)pts, D_eu_800C3C88[slot][actor], seg, D_800C39E8[slot][actor]);
        ((f32 *)D_800C3E70[slot][actor].keys)[seg] = total;
        if (shape == 0) {
            for (c = 0; c < 3; c++) {
                A[c] = 0.5f * pts[3][c] + ((-0.5f * pts[0][c] + 1.5f * pts[1][c]) + -1.5f * pts[2][c]);
                B[c] = -0.5f * pts[3][c] + ((pts[0][c] + -2.5f * pts[1][c]) + (pts[2][c] + pts[2][c]));
                C[c] = 0.5f * pts[2][c] + -0.5f * pts[0][c];
                D[c] = pts[1][c];
            }
            for (c = 0; c < 3; c++) {
                prev[cur == 0][c] = D[c];
            }
            for (t = 0.01f; t <= 1.0f; t += 0.01f) {
                x = D[0] + ((A[0] * t + B[0]) * t + C[0]) * t;
                prev[cur][0] = x;
                y = D[1] + ((A[1] * t + B[1]) * t + C[1]) * t;
                prev[cur][1] = y;
                z = D[2] + ((A[2] * t + B[2]) * t + C[2]) * t;
                prev[cur][2] = z;
                dx = x - prev[cur == 0][0];
                dy = y - prev[cur == 0][1];
                dz = prev[cur][2] - prev[cur == 0][2];
                d = dx * dx + (dy * dy + dz * dz);
                if (d != 0.0f) {
                    total += sqrtf(d);
                }
                cur ^= 1;
            }
        } else {
            dz = pts[2][2] - pts[1][2];
            dx = pts[2][0] - pts[1][0];
            dy = pts[2][1] - pts[1][1];
            total += sqrtf(dz * dz + (dx * dx + dy * dy));
        }
    }
    ((f32 *)D_800C3E70[slot][actor].keys)[seg] = total;
    *(f32 *)D_800C3E70[slot][actor].pad0 = total;
    D_800C3E70[slot][actor].pad3C[0] = 0xFF;
}
