/*
 * P65: floor slope of a triangle, given as 3 vertex pointers (tris) or, when verts != NULL, as 3
 * packed s16 x/y/z vertices (verts, stride 6). Tries the corners in turn: P1 = v[i], edges e1 = v[i+1] - P1 and
 * e2 = v[i+2] - P1 (indices mod 3), i = 0..2, then the same three with e1 / e2 swapped, until
 * e1.x * e2.z != e2.x * e1.z and e2.x != 0. Then
 *   *outB = (e2.x * e1.y - e1.x * e2.y) / (e2.x * e1.z - e1.x * e2.z),  *outA = (e2.y - *outB * e2.z) / e2.x
 * and returns 1 (y = *outA * x + *outB * z on the plane, up to the offset). No triangle, or the 6th attempt (even a
 * good one, as the asm does): both 0, returns 0.
 */
s32 func_1510E908(s16 **tris, s16 *verts, f32 *outA, f32 *outB) {
    s32 attempt = 0;
    s32 state;
    s32 swap;
    s32 i0, i1, i2;
    s16 *p0, *p1, *p2;
    f32 e1x, e1y, e1z, e2x, e2y, e2z, t;
    f32 p, q;

    if (tris == NULL && verts == NULL) {
        *outB = 0.0f;
        *outA = 0.0f;
        return 0;
    }
    do {
        state = 1;
        swap = (attempt >= 3);
        i0 = swap ? attempt - 3 : attempt;
        i1 = (i0 == 2) ? 0 : i0 + 1;
        attempt++;
        i2 = (i1 == 2) ? 0 : i1 + 1;
        if (verts != NULL) {
            p0 = verts + i1 * 3;
            p1 = verts + i0 * 3;
            p2 = verts + i2 * 3;
        } else {
            p0 = tris[i1];
            p1 = tris[i0];
            p2 = tris[i2];
        }
        e1x = p0[0] - p1[0];
        e1y = p0[1] - p1[1];
        e1z = p0[2] - p1[2];
        e2x = p2[0] - p1[0];
        e2y = p2[1] - p1[1];
        e2z = p2[2] - p1[2];
        if (swap) {
            t = e1x; e1x = e2x; e2x = t;
            t = e1y; e1y = e2y; e2y = t;
            t = e1z; e1z = e2z; e2z = t;
        }
        p = e1x * e2z;
        q = e2x * e1z;
        if (p == q) {
            state = 0;
        }
        if (0) {
            state = 0;
        }
        if (attempt == 6) {
            state = 2;
        }
    } while (state == 0);

    if (state == 2) {
        *outA = 0.0f;
        *outB = 0.0f;
        return 0;
    }
    *outB = (e2x * e1y - e1x * e2y) / (q - p);
    *outA = (e2y - *outB * e2z) / e2x;
    return 1;
}
