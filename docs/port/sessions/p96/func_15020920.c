/* Prepares segment `seg` of the path of actor `actor` of cutscene slot `slot` (needs seg < key count - 1).
 * The segment's control points P0..P3 (func_15020090, xyz each) give the Catmull-Rom cubic
 * D + (C + (B + A u) u) u with D = P1, C = (P2 - P0) / 2, B = P0 - 2.5 P1 + 2 P2 - P3 / 2,
 * A = (P3 - P0) / 2 + 1.5 (P1 - P2), stored per axis at SceneActor +0x08 / +0x14 / +0x20 / +0x2C.
 * The 101-entry length table (SceneActor +0x38) gets the path length at each sample: on a curved segment (key
 * shape +6 == 0) the segment start length (keys[seg]) plus the chord lengths between the samples at u = 0, 0.01,
 * ...; on a straight one i / 101 of the segment length (keys[seg + 1] - keys[seg]), from 0. SceneActor +0x3C
 * remembers the prepared segment. */
void func_15020920(s32 actor, s32 seg, s32 slot) {
    SceneActor *a;
    f32 pts[12];
    f32 cA[3];
    f32 cB[3];
    f32 cC[3];
    f32 cD[3];
    f32 prev[2][3];
    f32 *c;
    f32 *cur;
    f32 *old;
    f32 len;
    f32 step;
    f32 u;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d2;
    s32 cnt;
    s32 i;
    u16 shape;
    u8 flip;

    cnt = D_800C39E8[slot][actor];
    if (seg >= cnt - 1) {
        return;
    }
    a = &D_800C3E70[slot][actor];
    len = ((f32 *)a->keys)[seg];
    shape = *(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6);
    flip = 0;
    func_15020090((u8 *)pts, D_eu_800C3C88[slot][actor], seg, cnt);
    if (shape == 0) {
        c = (f32 *)a->pad8;
        for (i = 0; i < 3; i++) {
            cA[i] = pts[9 + i] * 0.5f + ((-0.5f * pts[i] + 1.5f * pts[3 + i]) + -1.5f * pts[6 + i]);
            cB[i] = pts[9 + i] * -0.5f + ((pts[i] + -2.5f * pts[3 + i]) + (pts[6 + i] + pts[6 + i]));
            cC[i] = pts[6 + i] * 0.5f + -0.5f * pts[i];
            cD[i] = pts[3 + i];
            c[i] = cD[i];
            c[3 + i] = cC[i];
            c[6 + i] = cB[i];
            c[9 + i] = cA[i];
        }
        ((f32 *)a->state)[0] = len;
        for (i = 0; i < 3; i++) {
            prev[1][i] = cD[i];
        }
        step = D_80096D9C;
        i = 1;
        for (u = step; u <= 1.0f; u += step) {
            cur = prev[flip];
            old = prev[flip == 0];
            cur[0] = cD[0] + ((cA[0] * u + cB[0]) * u + cC[0]) * u;
            cur[1] = cD[1] + ((cA[1] * u + cB[1]) * u + cC[1]) * u;
            cur[2] = cD[2] + ((cA[2] * u + cB[2]) * u + cC[2]) * u;
            dx = cur[0] - old[0];
            dy = cur[1] - old[1];
            dz = cur[2] - old[2];
            d2 = dx * dx + (dy * dy + dz * dz);
            if (d2 != 0.0f) {
                len += sqrtf(d2);
            }
            ((f32 *)a->state)[i] = len;
            flip ^= 1;
            i++;
        }
    } else {
        len = ((f32 *)a->keys)[seg + 1] - len;
        for (i = 0; i < 101; i++) {
            ((f32 *)a->state)[i] = (f32)i * len / 101.0f;
        }
    }
    a->pad3C[0] = seg;
}
