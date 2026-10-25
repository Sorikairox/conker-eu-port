/* ---- P294: the wall engine (func_150AB708 behind the entries func_150AB6D0 / func_150AC8C4), readable ----
 * A sliding move of a record (struct127, 0x32C bytes) from its position (rec+0x14..0x1C) towards a target, against
 * the collision triangles near the swept box (map: docs/port/sessions/P53.md section 5). The asm kept its state in
 * s0-s7 / fp / gp, f29-f31 and a 0x268-byte frame and jumped through 4 continuation pointers the entry stub stored
 * at sp+0x1D0..0x1DC; here the frame is NmwState (asm frame offsets in the comments) and the continuations are the
 * `ledge` flag:
 *   func_150AB6D0 (walls):  box = move + radius, triangles pushed out of (face or nearest edge), result written back;
 *   func_150AC8C4 (ledges): box around the record turned by its heading, triangles only looked at (ledge grab
 *                           data in D_800CC214..21C / D_800CC1B0..B8, D_800CC1C0[record] = 1), nothing written back. */
#define NMW_F32(sym) (*(f32 *) (sym))
#define NMW_REC_SIZE 812 /* struct127 */

typedef struct {
    u8 *rec;             /* 0x140 the moving record */
    s32 nObjs;           /* s1: area kind 2: objects func_150A69A8 listed in D_800D3C00 (else 0) */
    s32 cur;             /* 0x148 kind 2: current object index; kind 3: current record (pointer); else 0 */
    s32 curFirst;        /* 0x14C kind 2: the object's first triangle; kind 3: end of the records */
    u32 vbase;           /* 0x150 base of the triangles' vertex offsets (0: absolute) */
    s32 listPos;         /* 0x154 kind 2: position in D_800D3C00 */
    s32 count;           /* 0x154 kind 3: triangles of the current record's model */
    s32 recNo;           /* 0x144 kind 3: 1 + index of the current record */
    s32 margin;          /* 0x158 widening of the xz box (s16 from func_1507C7C0) */
    s32 radius;          /* 0x15C (s16 from func_1507C7C0) */
    f32 radiusF;         /* 0x160 walls: how far triangles push the position away */
    s32 moved;           /* 0x164 result: 1 once a triangle pushed the position */
    s32 mark;            /* 0x168 kind 2: mark the objects touched */
    u32 noSlope;         /* 0x16C the triangle's flag 0x1000000: no "too flat to be a wall" test */
    u32 mask;            /* 0x28 triangle flags that must all be set (ledges: 0x0E000000) */
    f32 co, si;          /* 0x2C / 0x30 the frame's heading: walls: -dz, dx of the move (normalised); ledges: the
                          * record's heading (-cos, sin) */
    f32 pos[3];          /* 0x34 the position being resolved (starts at the record's) */
    f32 tgt[3];          /* 0x40 the target */
    u32 keepFall;        /* 0x4C rec+0x20 copy; walls clear rec+0x20 when this was zeroed */
    NmwReg dy;           /* 0x50 rec+0x20 (bits), after the first push pos y - target y */
    f32 yoff;            /* 0x54 D_800CC1FC: box centre above the record */
    f32 half[3];         /* 0x58 box half extents (D_800CC64C..54, set by func_150492CC) */
    s32 prev;            /* 0x64 previous triangle of the leaf list (relative entries) */
    s32 nVisited;        /* 0x68 / gp */
    u16 visited[100];    /* 0x6C level triangles already tested (a triangle can be in several leaves) */
    f32 mid[3];          /* 0x134 box centre (y without yoff in walls mode) */
    NmrNode *node;       /* s0 next BSP node to walk (NULL: none) */
    u8 *cursor;          /* s7 position in the leaf's triangle list (NULL: walk to the next leaf) */
    s32 xmin, xmax;      /* s2 / s3 integer xz box of the move */
    s32 zmin, zmax;      /* s4 / s5 */
    s32 y;               /* fp rint(pos y) */
    s32 tri;             /* s6 current triangle */
    TriPt tv[3];         /* 0x20C its vertices in the box frame */
    f32 ledgeLo, ledgeHi; /* 0x1E0 / 0x1E4 ledges: 64 / 65, the ledge height window */
    f32 ledgeBest;       /* 0x208 ledges: squared xz distance of the nearest ledge so far */
} NmwState;

/* move_box (func_150AC6A4): the integer xz box from the position p to the target widened by the margin, y = rint(p y);
 * also the move's heading (si, co) = (dx, -dz) / |(dx, dz)| when it has an xz length, and dy */
static void nmw_set_box(NmwState *w, f32 px, f32 py, f32 pz) {
    f32 dx, dz, l, x0, x1, z0, z1;

    w->y = nmD5E90_rint(py);
    dx = px - w->tgt[0];
    w->dy.f = py - w->tgt[1];
    dz = pz - w->tgt[2];
    l = dx * dx + dz * dz;
    if (l != 0.0f) {
        l = sqrtf(l);
        w->si = dx / l;
        w->co = -dz / l;
    }
    if (w->tgt[0] >= px) {
        x0 = px;
        x1 = w->tgt[0];
    } else {
        x0 = w->tgt[0];
        x1 = px;
    }
    if (w->tgt[2] >= pz) {
        z0 = pz;
        z1 = w->tgt[2];
    } else {
        z0 = w->tgt[2];
        z1 = pz;
    }
    w->xmin = (s32) x0 - w->margin;
    w->xmax = (s32) x1 + w->margin;
    w->zmin = (s32) z0 - w->margin;
    w->zmax = (s32) z1 + w->margin;
}

/* next_record (part of func_150ABBD0): area kind 3, the next record after w->cur that is not the mover, exists,
 * has flag 0x4000 at +0xF8 and a vertex base at +0x264; selects its model's triangles (D_800DC26C = D_800C6070[kind],
 * count D_800C5D38[kind]). 0 when the records run out. */
static s32 nmw_next_record(NmwState *w) {
    u8 *r = (u8 *) w->cur;
    s32 no = w->recNo;
    u32 base;

    for (;;) {
        r += NMW_REC_SIZE;
        no++;
        if (r == (u8 *) w->curFirst) {
            return 0;
        }
        if (r == w->rec || *(u32 *) r == 0 || !(*(u32 *) (r + 0xF8) & 0x4000)) {
            continue;
        }
        base = *(u32 *) (r + 0x264);
        if (base != 0) {
            break;
        }
    }
    w->cur = (s32) r;
    w->recNo = no;
    w->vbase = base;
    *(s32 *) D_800DC26C = D_800C6070[r[4]];
    w->count = ((u16 *) D_800C5D38)[r[4]];
    w->tri = 0;
    return 1;
}

/* walk_tree (func_150ABB24 .. ABBCC): from w->node, the next BSP leaf whose square (centre, half size) meets the xz box;
 * sets the list cursor and the node to continue from. 0 when the tree is done. Kind 2 starts the list at the
 * object's first triangle (the asm adds the index to the list pointer). */
static s32 nmw_walk_tree(NmwState *w) {
    NmrNode *node = w->node;
    s32 step;

    for (;;) {
        if (w->xmax < node->cx - node->half || node->cx + node->half < w->xmin ||
            w->zmax < node->cz - node->half || node->cz + node->half < w->zmin) {
            step = node->next;
            node = (NmrNode *) ((u8 *) node + step);
            if (step == 0) {
                return 0;
            }
        } else if (node->child != 0) {
            node = (NmrNode *) ((u8 *) node + node->child);
        } else {
            break;
        }
    }
    w->cursor = node->list;
    w->node = node->next == 0 ? NULL : (NmrNode *) ((u8 *) node + node->next);
    if (w->nObjs != 0) {
        w->cursor += w->curFirst;
        w->prev = w->curFirst - 1;
    }
    return 1;
}

/* next_triangle (func_150ABBD0 .. ABE60): the next triangle (w->tri) whose bounds meet the box (xz overlap, y within
 * 200 of rint(pos y)) and whose flags hold the mask; level triangles are tested once (visited list, 100 entries).
 * Kind 3 runs over the records' own models instead of the tree. Kind 2: list entries past the current object's
 * triangles move to the next listed object (whose flags +0x40 apply to that first triangle; the others use the
 * level's D_800DBE5C). 0 when there is none left. */
static s32 nmw_next_triangle(NmwState *w) {
    s16 *xz;
    s16 *yr;
    u8 *obj;
    u32 flags;
    s32 t, b, i, first, n;

    for (;;) {
        if (w->nObjs == 0 && w->cur != 0) {
            if (++w->tri == w->count && !nmw_next_record(w)) {
                return 0;
            }
            t = w->tri;
            xz = (s16 *) *(u32 *) ((u8 *) w->cur + 0x268) + t * 4;
            yr = (s16 *) *(u32 *) ((u8 *) w->cur + 0x26C);
        } else {
            if (w->cursor == NULL && !nmw_walk_tree(w)) {
                return 0;
            }
            b = *w->cursor++;
            if (b == 0) { /* end of the leaf (func_150AC770) */
                w->cursor = NULL;
                if (w->node == NULL) {
                    return 0;
                }
                continue;
            }
            t = b & 0x7F;
            if (t == b) {
                t += w->prev;
            } else {
                t = (t << 8) | *w->cursor++;
            }
            if (w->nObjs != 0) {
                obj = (u8 *) D_800DBEF4 + w->cur * NMR_OBJ_SIZE;
                first = w->curFirst;
                n = NMR_OBJ_U16(obj, NMR_OBJ_NTRIS);
                if (t >= n + first) {
                    if (++w->listPos == w->nObjs) {
                        return 0;
                    }
                    w->cur = ((u16 *) D_800D3C00)[w->listPos];
                    obj = (u8 *) D_800DBEF4 + w->cur * NMR_OBJ_SIZE;
                    t = w->curFirst = NMR_OBJ_U16(obj, NMR_OBJ_TRI0);
                    w->vbase = D_800DC328[w->cur];
                    w->cursor += t - first - n;
                    flags = *(u32 *) (obj + NMR_OBJ_FLAGS);
                    goto test_flags;
                }
            }
            flags = D_800DBE5C != 0 ? ((u32 *) D_800DBE5C)[t] : 0;
        test_flags:
            w->prev = t;
            if ((flags & w->mask) != w->mask) {
                continue;
            }
            w->noSlope = flags & 0x1000000;
            xz = *(s16 **) D_800DC270 + t * 4;
            yr = *(s16 **) D_800DC274;
        }
        w->tri = t;
        if (!(xz[0] < w->xmax) || !(w->xmin < xz[2]) || !(xz[1] < w->zmax) || !(w->zmin < xz[3])) {
            continue;
        }
        if (!(yr[t * 2] < w->y + 200) || !(w->y - 200 < yr[t * 2 + 1])) {
            continue;
        }
        if (w->cur == 0 && w->nObjs == 0) {
            for (i = 0; i < w->nVisited; i++) {
                if (w->visited[i] == t) {
                    break;
                }
            }
            if (i < w->nVisited) {
                continue;
            }
            if (w->nVisited != 100) {
                w->visited[w->nVisited++] = t;
            }
        }
        return 1;
    }
}

/* projects_inside (func_150AC200): p projected onto the plane n (n . q = n[3]) inside the triangle w->tv? The three
 * edge cross products (e = a - b, q - b for the edges v1-v0, v2-v1, v0-v2) are compared on the axis where the first
 * one is largest: inside when their signs agree. *side = the second edge's component on that axis (the asm leaves
 * it in f4, and its caller reads it). */
static s32 nmw_projects_inside(NmwState *w, f32 *n, f32 *p, f32 *side) {
    f32 cr[3][3];
    f32 q[3], e[3], u[3];
    f32 s;
    TriPt *a;
    TriPt *b;
    s32 k, bits;

    s = (n[3] - n[0] * p[0] - n[1] * p[1] - n[2] * p[2]) / (n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
    q[0] = s * n[0] + p[0];
    q[1] = s * n[1] + p[1];
    q[2] = s * n[2] + p[2];
    for (k = 0; k < 3; k++) {
        a = &w->tv[(k + 1) % 3];
        b = &w->tv[k];
        e[0] = a->x - b->x;
        e[1] = a->y - b->y;
        e[2] = a->z - b->z;
        u[0] = q[0] - b->x;
        u[1] = q[1] - b->y;
        u[2] = q[2] - b->z;
        cr[k][0] = e[1] * u[2] - e[2] * u[1];
        cr[k][1] = e[2] * u[0] - e[0] * u[2];
        cr[k][2] = e[0] * u[1] - e[1] * u[0];
    }
    if (NM_FABS(cr[0][0]) <= NM_FABS(cr[0][1])) {
        k = NM_FABS(cr[0][2]) > NM_FABS(cr[0][1]) ? 2 : 1;
    } else {
        k = NM_FABS(cr[0][2]) > NM_FABS(cr[0][0]) ? 2 : 0;
    }
    bits = 0;
    if (cr[0][k] < 0.0f) bits |= 1;
    if (cr[1][k] < 0.0f) bits |= 2;
    if (cr[2][k] < 0.0f) bits |= 4;
    *side = cr[1][k];
    return bits == 0 || bits == 7;
}

/* edge_push (func_150AC3CC .. AC5D4): the point of the triangle's edges nearest to p (box frame); when it is nearer
 * than the radius, move the position away from it by the difference (turned back to world axes). 1 if pushed. */
static s32 nmw_edge_push(NmwState *w, f32 *p) {
    f32 best = 65536.0f;
    f32 bp[3];
    f32 d[3], c[3], u[3];
    f32 t, dist, k;
    TriPt *a;
    TriPt *b;
    s32 i;

    for (i = 0; i < 3; i++) {
        a = &w->tv[(i + 1) % 3];
        b = &w->tv[i];
        d[0] = b->x - a->x;
        d[1] = b->y - a->y;
        d[2] = b->z - a->z;
        t = (d[0] * p[0] + d[1] * p[1] + d[2] * p[2] - d[0] * a->x - d[1] * a->y - d[2] * a->z) /
            (d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
        if (t < 0.0f) {
            t = 0.0f;
        } else if (t > 1.0f) {
            t = 1.0f;
        }
        c[0] = a->x + t * d[0];
        c[1] = a->y + t * d[1];
        c[2] = a->z + t * d[2];
        dist = sqrtf((c[0] - p[0]) * (c[0] - p[0]) + (c[1] - p[1]) * (c[1] - p[1]) + (c[2] - p[2]) * (c[2] - p[2]));
        if (!(dist >= best)) {
            best = dist;
            bp[0] = c[0];
            bp[1] = c[1];
            bp[2] = c[2];
        }
    }
    if (best >= w->radiusF) {
        return 0;
    }
    u[0] = p[0] - bp[0];
    u[1] = p[1] - bp[1];
    u[2] = p[2] - bp[2];
    k = (w->radiusF - best) / sqrtf(u[0] * u[0] + u[1] * u[1] + u[2] * u[2]);
    u[0] = u[0] * k;
    u[1] = u[1] * k;
    u[2] = u[2] * k;
    w->pos[0] = w->pos[0] + (u[0] * w->co - u[2] * w->si);
    w->pos[1] = w->pos[1] + u[1];
    w->pos[2] = w->pos[2] + (u[2] * w->co + u[0] * w->si);
    return 1;
}

/* wall_triangle (func_150ABE68 .. AC694, walls): test the current triangle against the box at the middle of the
 * move; on contact mark it (kind 2 objects / kind 3 records), skip it when the move's first vertex test says it
 * faces away or (without the noSlope flag / D_800CC1F2) it is floor-like (normal y / |n| >= 0.5), clamp the
 * position to 60 units from the target (unless D_800CC1F4), then push the position out of the face (when the
 * target or the position projects inside the triangle, or D_800CC1F3 and the second edge's sign component <= 0.8)
 * or away from the nearest edge. 1 if the position moved. */
static s32 nmw_wall_triangle(NmwState *w) {
    u32 *tri = (u32 *) (*(u32 *) D_800DC26C + w->tri * 12);
    u8 *obj;
    f32 n[4];
    f32 p[3];
    f32 len2, len, a, b, c, side, dist, k, h, ox, oy, oz, sx, sz;
    s32 in;

    w->mid[0] = (w->tgt[0] + w->pos[0]) * 0.5f;
    w->mid[1] = (w->tgt[1] + w->pos[1]) * 0.5f;
    w->mid[2] = (w->tgt[2] + w->pos[2]) * 0.5f;
    nmw_tri_to_local(tri, w->vbase, w->mid[0], w->mid[1] + w->yoff, w->mid[2], w->si, w->co, &w->tv[0].x);
    if (nmw_tri_misses_box(w->tv, w->half[0], w->half[1], w->half[2])) {
        return 0;
    }
    if (w->nObjs != 0 && w->mark != 0) {
        obj = (u8 *) D_800DBEF4 + w->cur * NMR_OBJ_SIZE;
        obj[0x4F] |= 0x80;
        (*(u32 **) D_800DC3C4)[w->cur] |= 1 << ((s32) (w->rec - (u8 *) D_800CC2D0) / NMW_REC_SIZE & 31);
    } else if (w->cur != 0) {
        w->rec[0x275] = w->recNo;
    }
    n[0] = D_800CC630;
    n[1] = D_800CC634;
    n[2] = D_800CC638;
    n[3] = D_800CC63C;
    len2 = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
    if (len2 == 0.0f) {
        len2 = 1.0f;
    }
    len = sqrtf(len2);
    a = w->mid[0] - w->tgt[0];
    b = w->mid[1] - w->tgt[1];
    c = w->mid[2] - w->tgt[2];
    if (n[0] * (a * w->co + w->tv[0].x + c * w->si) + n[1] * (w->tv[0].y + b) +
            n[2] * (w->tv[0].z - a * w->si + c * w->co) >= 0.0f) {
        return 0;
    }
    if (w->noSlope == 0 && *D_800CC1F2 == 0 && n[1] / len >= 0.5f) {
        return 0;
    }
    ox = w->pos[0];
    oy = w->pos[1];
    if (*D_800CC1F4 == 0) {
        oz = w->pos[2];
        a = ox - w->tgt[0];
        b = oy - w->tgt[1];
        c = oz - w->tgt[2];
        *D_800CC1F4 = 0;
        dist = sqrtf(a * a + b * b + c * c);
        if (dist != 0.0f && !(dist <= 60.0f)) {
            k = 60.0f / dist;
            w->pos[0] = a * k + w->tgt[0];
            w->mid[0] = (w->pos[0] + w->tgt[0]) * 0.5f;
            w->pos[1] = b * k + w->tgt[1];
            w->mid[1] = (w->pos[1] + w->tgt[1]) * 0.5f;
            w->pos[2] = c * k + w->tgt[2];
            w->mid[2] = (w->pos[2] + w->tgt[2]) * 0.5f;
        }
    } else {
        oz = w->mid[2]; /* the asm's f8 still holds the box centre z here, not the position's */
    }
    /* the target relative to the (unclamped) position, in the box frame */
    a = w->tgt[0] - ox;
    p[1] = w->tgt[1] - oy;
    c = w->tgt[2] - oz;
    p[0] = a * w->co + c * w->si;
    p[2] = c * w->co - a * w->si;
    in = nmw_projects_inside(w, n, p, &side);
    /* the position relative to the box centre, in the box frame */
    sx = w->pos[0] - w->mid[0];
    p[1] = w->pos[1] - w->mid[1];
    sz = w->pos[2] - w->mid[2];
    p[0] = sx * w->co + sz * w->si;
    p[2] = sz * w->co - sx * w->si;
    if (!(*D_800CC1F3 != 0 && side <= 0.8f) && in != 1 && nmw_projects_inside(w, n, p, &side) != 1) {
        return nmw_edge_push(w, p);
    }
    /* face push (func_150AC5D8): out along the normal until the plane is radius away */
    h = n[3] + w->radiusF * len - n[0] * p[0] - n[1] * p[1] - n[2] * p[2];
    if (h <= 0.0f) {
        return 0;
    }
    if (!(n[1] / len >= -0.2f) && !(w->dy.f <= 0.0f)) {
        w->keepFall = 0;
    }
    h = h / len2;
    sx = n[0] * w->co - n[2] * w->si;
    sz = n[2] * w->co + n[0] * w->si;
    w->pos[0] = h * sx + w->pos[0];
    w->pos[1] = h * n[1] + w->pos[1];
    w->pos[2] = h * sz + w->pos[2];
    return 1;
}

/* ledge_triangle (func_150AC960 .. ACE8C, ledges): a triangle in the box around the record (turned by its heading)
 * that is flat enough (normal y / |n| > D_8009FAC4) and whose plane height (+ yoff) is within the 64..65 window
 * around the half move: its xz edges (x along the heading) are lines z = slope x + icept; the one passing nearest to
 * the record (foot of the perpendicular, clamped to the edge) is the ledge candidate. When it beats the best so far,
 * has an end on each side of the record (x > 0 and x < 0) and |slope| < 4: the grab point is where the line meets
 * the circle of radius^2 D_8009FACC (the root on the record's side), stored with the ledge height and the edge's
 * angle in D_800CC214 / D_800CC1B4 (icept negative) or D_800CC218 / D_800CC1B8, and D_800CC1C0[record] = 1. */
static void nmw_ledge_triangle(NmwState *w) {
    u32 *tri = (u32 *) (*(u32 *) D_800DC26C + w->tri * 12);
    f32 *v = &w->tv[0].x;
    f32 nx, ny, nz, d, len, top, hm, x0, z0, x1, z1, dx, m, ic, fx, fz, footx, footz, d2, best, tmp;
    f32 bestFoot[2], bestSlope, bestX0, bestX1;
    NmwReg bestIcept;
    f32 a, bq, cq, disc, sq, t, lx, wx, wz, height, ang;
    s32 first, i, sides, j0, j1;

    w->mid[1] = (w->tgt[1] + w->pos[1]) * 0.5f + w->yoff;
    nmw_tri_to_local(tri, w->vbase, w->pos[0], w->mid[1], w->pos[2], w->si, w->co, v);
    if (nmw_tri_misses_box(w->tv, w->half[0], w->half[1], w->half[2])) {
        return;
    }
    nx = D_800CC630;
    ny = D_800CC634;
    nz = D_800CC638;
    d = D_800CC63C;
    len = sqrtf(nx * nx + ny * ny + nz * nz);
    if (len == 0.0f || ny / len <= NMW_F32(D_8009FAC0 + 4)) {
        return;
    }
    top = d / ny + w->yoff;
    hm = (w->tgt[1] - w->pos[1]) * 0.5f;
    if (top + hm <= w->ledgeLo || top - hm >= w->ledgeHi) {
        return;
    }
    first = 1;
    best = len;
    for (i = 0; i < 3; i++) {
        j0 = 3 * i;
        j1 = 3 * ((i + 1) % 3);
        x0 = v[j0];
        z0 = v[j0 + 2];
        x1 = v[j1];
        z1 = v[j1 + 2];
        dx = x1 - x0;
        if (!(NM_FABS(dx) >= 4.0f) && !(NM_FABS(z1 - z0) >= 4.0f) && (first == 0 || i < 2)) {
            continue; /* a short edge, unless it is the last chance */
        }
        if (dx == 0.0f) {
            m = NMW_F32(D_8009FAC8);
            ic = x1;
            fx = x1;
            fz = 0.0f;
        } else {
            m = (z1 - z0) / dx;
            if (m == 0.0f) {
                ic = z1;
                fx = 0.0f;
                fz = z1;
            } else {
                ic = z0 - m * x0;
                tmp = m * m + 1.0f;
                fx = -ic * m / tmp;
                fz = ic / tmp;
            }
        }
        footx = fx;
        footz = fz;
        if (!(x0 <= x1)) {
            tmp = x0, x0 = x1, x1 = tmp;
            tmp = z0, z0 = z1, z1 = tmp;
        }
        if (!(x0 <= fx)) {
            fx = x0;
            fz = z0;
        } else if (!(x1 >= fx)) {
            fx = x1;
            fz = z1;
        } else {
            if (!(z0 <= z1)) {
                tmp = x0, x0 = x1, x1 = tmp;
                tmp = z0, z0 = z1, z1 = tmp;
            }
            if (!(z0 <= fz)) {
                fx = x0;
                fz = z0;
            } else if (!(z1 >= fz)) {
                fx = x1;
                fz = z1;
            }
        }
        d2 = fx * fx + fz * fz;
        if (first || !(d2 >= best)) {
            bestFoot[0] = footx;
            bestFoot[1] = footz;
            best = d2;
            bestSlope = m;
            bestIcept.f = ic;
            first = 0;
            bestX0 = x0;
            bestX1 = x1;
        }
    }
    if (best >= w->ledgeBest) {
        return;
    }
    w->ledgeBest = best;
    sides = 0;
    if (bestX0 > 0.0f || bestX1 > 0.0f) {
        sides |= 1;
    }
    if (bestX0 < -0.0f || bestX1 < -0.0f) {
        sides |= 2;
    }
    if (sides != 3 || NM_FABS(bestSlope) >= 4.0f || ny == 0.0f) {
        return;
    }
    height = d / ny + (w->mid[1] - 54.0f);
    m = bestSlope;
    a = 1.0f + m * m;
    bq = 2.0f * (m * bestFoot[0] - bestFoot[1]);
    cq = bestFoot[0] * bestFoot[0] - NMW_F32(D_8009FACC) + bestFoot[1] * bestFoot[1];
    disc = bq * bq - 4.0f * a * cq;
    if (!(disc > 0.0f)) {
        disc = 0.0f;
    }
    sq = sqrtf(disc);
    if (bestIcept.f > 0.0f) {
        sq = -sq;
    }
    t = (sq - bq) / (2.0f * a);
    lx = -m * t;
    wx = lx * w->co - t * w->si;
    wz = lx * w->si + t * w->co;
    D_800CC21C = wx + *(f32 *) (w->rec + 0x14);
    NMW_F32(D_800CC1B0) = wz + *(f32 *) (w->rec + 0x1C);
    ang = func_150484A0(1.0f, m) * NMW_F32(D_8009FAD0) - 90.0f;
    if (bestIcept.i < 0) {
        D_800CC214 = height;
        NMW_F32(D_800CC1B4) = ang;
    } else {
        D_800CC218 = height;
        NMW_F32(D_800CC1B8) = ang;
    }
    ((s16 *) D_800CC1C0)[(s32) (w->rec - (u8 *) D_800CC2D0) / NMW_REC_SIZE] = 1;
}

/* wall_engine (func_150AB708): see the block comment above. Area kind D_800DC280: 2 = the objects func_150A69A8
 * lists near the target (sorted by func_150A49D0; nothing listed or no vertex base -> 0), 3 = the other records'
 * models, else the level. Returns 1 if a wall moved the record (walls; ledges return 0). */
static s32 nmw_engine(u8 *rec, f32 x, f32 y, u32 zbits, s32 mark, s32 ledge) {
    NmwState w;
    union {
        s32 w;
        s16 h[2];
    } yo;
    s16 mg, rd;
    NmwReg z;
    f32 dx, dz, ang;

    z.u = zbits;
    w.rec = rec;
    w.mask = ledge ? 0x0E000000 : 0;
    w.vbase = 0;
    w.moved = 0;
    w.mark = mark;
    w.cur = 0;
    w.tgt[0] = x;
    w.tgt[1] = y;
    w.tgt[2] = z.f;
    func_1507C7C0((struct127 *) rec, &yo.h[0], &mg, &rd);
    w.nObjs = 0;
    if (D_800DC280 == 2) {
        w.nObjs = func_150A69A8(nmD5E90_rint(x), nmD5E90_rint(z.f), &yo.w, nmD5E90_rint(y) + yo.h[0]);
        if (w.nObjs == 0) {
            return 0;
        }
        func_150A49D0(w.nObjs, (s32 *) D_800D3C00, 0);
        w.cur = *(u16 *) D_800D3C00;
        w.curFirst = NMR_OBJ_U16((u8 *) D_800DBEF4 + w.cur * NMR_OBJ_SIZE, NMR_OBJ_TRI0);
        w.vbase = D_800DC328[w.cur];
        if (w.vbase == 0) {
            return 0;
        }
        w.listPos = 0;
    } else if (D_800DC280 == 3) {
        w.curFirst = (s32) ((u8 *) D_800CC2D0 + 25 * NMW_REC_SIZE);
        w.cur = (s32) ((u8 *) D_800CC2D0 - NMW_REC_SIZE);
        w.tri = -1;
        w.count = 0;
        w.recNo = 0;
    }
    w.noSlope = 0;
    if (ledge) {
        w.radius = rd + 10;
        w.margin = mg + 10;
        w.ledgeLo = 64.0f;
        w.ledgeHi = 65.0f;
        w.ledgeBest = 65536.0f; /* func_150AC8C4 sets it before joining the engine */
        w.yoff = NMW_F32(D_800CC1FC);
        func_150492CC((f32) w.margin * 2.0f, NMW_F32(D_800CC1F8) + 0.0f, (f32) w.radius * 2.0f);
    } else {
        w.radiusF = rd;
        w.radius = rd;
        w.margin = mg;
        w.yoff = NMW_F32(D_800CC1FC);
        dx = x - *(f32 *) (rec + 0x14);
        dz = z.f - *(f32 *) (rec + 0x1C);
        func_150492CC((f32) w.margin * 2.0f, NMW_F32(D_800CC1F8), (f32) w.radius * 2.0f + sqrtf(dx * dx + dz * dz));
    }
    w.nVisited = 0;
    w.si = 0.0f;
    w.co = -1.0f;
    w.pos[0] = *(f32 *) (rec + 0x14);
    w.pos[1] = *(f32 *) (rec + 0x18);
    w.pos[2] = *(f32 *) (rec + 0x1C);
    nmw_set_box(&w, w.pos[0], w.pos[1], w.pos[2]);
    w.keepFall = w.dy.u = *(u32 *) (rec + 0x20);
    w.half[0] = D_800CC64C;
    w.half[1] = D_800CC650;
    w.half[2] = D_800CC654;
    w.node = *(NmrNode **) D_800DC278;
    w.cursor = NULL;
    if (ledge) {
        ang = *(f32 *) (rec + 0x40) * NMW_F32(D_8009FAC0);
        w.si = sinf(ang);
        w.co = -cosf(ang);
    }
    while (nmw_next_triangle(&w)) {
        if (ledge) {
            nmw_ledge_triangle(&w);
        } else if (nmw_wall_triangle(&w)) {
            w.moved = 1;
            nmw_set_box(&w, w.pos[0], w.pos[1], w.pos[2]);
        }
    }
    if (!ledge) {
        *(f32 *) (rec + 0x14) = w.pos[0];
        *(f32 *) (rec + 0x18) = w.pos[1];
        *(f32 *) (rec + 0x1C) = w.pos[2];
        if (w.keepFall == 0) {
            *(u32 *) (rec + 0x20) = 0;
        }
    }
    return w.moved;
}
