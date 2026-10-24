/* P204 */
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
s32 func_15142E24(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
Gfx *func_15142B7C(Gfx *, s32, s32);
Gfx *func_15142C10(Gfx *, s32, s32, s32, s32, u8 *);
Gfx *func_15142CF0(Gfx *, s32, s32, s32, s32, s32, s32, u8 *);
Gfx *func_1513F4E4(Gfx *, u8, u8 *);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
extern u8 D_800911BC[];
extern s32 D_800D30BC;
/* trail point (0x24 bytes): the same layout as port-b's TrailPointFD60 (func_1519FD60 writes them) */
typedef struct {
    f32 x;        /* 0x00 */
    f32 z;        /* 0x04 */
    f32 y;        /* 0x08 */
    f32 width;    /* 0x0C */
    s16 alpha;    /* 0x10 */
    s16 hold;     /* 0x12 */
    s16 fade;     /* 0x14: alpha scale, 0xFF = full */
    s16 texU;     /* 0x16 */
    s16 life;     /* 0x18 */
    s16 pad1A;
    f32 vx;       /* 0x1C */
    f32 vz;       /* 0x20 */
} TrailPoint03DC;

// foot_trail_draw: D_8008A644 draw handler (kind 5) of a foot trail / water ripple effect t (ring of t[0x25] points
// at t +0x94, tail t +0x2D, head t +0x2E, count t +0x2C; record rec = t +0x98). Returns gfx unchanged when there are
// fewer than 2 points or no vertex buffer (func_151D6310 slot `slot` in t +0x84, 0x30 bytes per point + 0x120).
// Otherwise: rec flag 2 sets the points' fade (+0x14) from the tail on, 0, +rec[0x41], ... for rec[0x40] points;
// rec flag 4 scales the fade from the head back by 0, rec[0x43], ... / 256 for rec[0x42] points. Then the render
// state (texture D_800911BC, colour rec +0x2A..0x2C, combine) and a strip from the newest point back to the tail:
// three vertices per point (left edge, centre, right edge across the trail direction, half width = point width;
// edges alpha 0, centre alpha = alpha * fade / 256, texture v from rec +0x46 (wrapped to +-1024 when +0x46 + +0x4A
// overflows) / middle / +0x46 + +0x4A, mirrored for the right foot (t +0x20 != 6)), four triangles per segment.
// With t +0x1E bit 2 the strip starts at the live foot position t +0x10 (width rec +0x38) instead of the newest point.
s32 func_151A03DC(u8 *t, s32 gfxArg, s16 slot) {
    Gfx *gfx = (Gfx *) gfxArg;
    u8 *rec;
    TrailPoint03DC *pts;
    TrailPoint03DC *p;
    TrailPoint03DC *q;
    Vtx *vtx;
    u8 flag;
    s16 tv[3];
    f32 cur[3];
    f32 nxt[3];
    f32 width;
    f32 qWidth;
    f32 dx;
    f32 dz;
    f32 inv;
    f32 ox;
    f32 oz;
    s32 i;
    s32 prev;
    s32 n;
    u8 step;
    s32 alpha;
    s32 qAlpha;
    s16 u;
    s16 qU;
    s32 l;
    s32 r;

    if (*(s8 *) (t + 0x2C) < 2) {
        return (s32) gfx;
    }
    func_151D6310((s32 *) (t + 0x84), slot, t[0x25] * 0x30 + 0x120, (s32 *) &vtx, NULL);
    if (vtx == NULL) {
        return (s32) gfx;
    }
    rec = *(u8 **) (t + 0x98);
    pts = *(TrailPoint03DC **) (t + 0x94);
    flag = 1;

    if (rec[4] & 2) {
        /* fade in from the tail */
        n = (s16) rec[0x40];
        i = *(s8 *) (t + 0x2D);
        step = 0;
        do {
            pts[i].fade = step;
            i++;
            n = (s16) (n - 1);
            step += rec[0x41];
            if (i == t[0x25]) {
                i = 0;
            }
            if (n == 0) {
                break;
            }
        } while (i != *(s8 *) (t + 0x2E));
    }
    if (rec[4] & 4) {
        /* fade out towards the head */
        i = *(s8 *) (t + 0x2E) - 1;
        n = (s16) rec[0x42];
        step = 0;
        if (i < 0) {
            i = t[0x25] - 1;
        }
        do {
            p = &pts[i];
            n = (s16) (n - 1);
            i--;
            p->fade = (p->fade * step) >> 8;
            step += rec[0x43];
            if (i < 0) {
                i = t[0x25] - 1;
            }
            if (n == 0) {
                break;
            }
        } while (i != *(s8 *) (t + 0x2E));
    }

    gfx = (Gfx *) func_15142E24((s32) gfx, (s32) D_800911BC, 0, 0, 0, 0, 0x39, 0, 0, &flag, 0x3E);
    gfx = func_15142B7C(gfx, 1, 0x160600);
    gfx = func_15142C10(gfx, rec[0x2A], rec[0x2B], rec[0x2C], 0xFF, &flag);
    gfx = func_15142CF0(gfx, 0, 0, 0xFF, 0xFF, 0xFF, 0, &flag);
    gfx = func_1513F4E4(gfx, 7, &flag);
    gfx = func_15142FBC(gfx, D_800D30BC | 0x80000 | 0x2CA0, 0x5049D8, &flag);

    /* first cross-section: the live foot position or the newest point; q = the next point towards the tail */
    if (*(u16 *) (t + 0x1E) & 2) {
        prev = *(s8 *) (t + 0x2E) - 1;
        if (prev < 0) {
            prev = t[0x25] - 1;
        }
        cur[0] = *(f32 *) (t + 0x10);
        cur[1] = *(f32 *) (t + 0x14);
        cur[2] = *(f32 *) (t + 0x18);
        q = &pts[prev];
        alpha = (q->alpha * q->fade) >> 8;
        width = *(f32 *) (rec + 0x38);
        u = q->texU;
    } else {
        i = *(s8 *) (t + 0x2E) - 1;
        if (i < 0) {
            i = t[0x25] - 1;
        }
        prev = i - 1;
        if (prev < 0) {
            prev = t[0x25] - 1;
        }
        p = &pts[i];
        cur[0] = p->x;
        cur[1] = p->y;
        cur[2] = p->z;
        q = &pts[prev];
        alpha = (p->alpha * p->fade) >> 8;
        width = p->width;
        u = p->texU;
    }
    nxt[0] = q->x;
    nxt[1] = q->y;
    nxt[2] = q->z;
    dx = nxt[0] - cur[0];
    dz = nxt[2] - cur[2];
    qAlpha = (q->alpha * q->fade) >> 8;
    qU = q->texU;
    qWidth = q->width;
    if (fabsf(dx) > 0.0001f || fabsf(dz) > 0.0001f) {
        inv = 1.0f / sqrtf(dx * dx + dz * dz);
    } else {
        inv = 1.0f;
    }

    /* texture v across the trail */
    tv[0] = *(s16 *) (rec + 0x46);
    tv[2] = *(s16 *) (rec + 0x46) + *(s16 *) (rec + 0x4A);
    if (tv[2] < tv[0]) {
        tv[0] = tv[0] % 1024;
        *(s16 *) (rec + 0x46) = tv[0];
        tv[2] = *(s16 *) (rec + 0x46) + *(s16 *) (rec + 0x4A);
    }
    tv[1] = (tv[2] + tv[0]) >> 1;
    if (*(s32 *) (t + 0x20) == 6) {
        l = 0;
        r = 2;
    } else {
        l = 2;
        r = 0;
    }

    ox = -dz * inv * width;
    oz = dx * inv * width;
    vtx->v.ob[0] = (s32) (cur[0] + ox);
    vtx->v.ob[1] = (s32) cur[1];
    vtx->v.ob[2] = (s32) (cur[2] + oz);
    vtx->v.tc[0] = u;
    vtx->v.tc[1] = tv[l];
    vtx->v.cn[0] = 0xFF;
    vtx->v.cn[1] = 0xFF;
    vtx->v.cn[2] = 0xFF;
    vtx->v.cn[3] = 0;
    vtx->v.flag = 0;
    vtx++;
    vtx->v.ob[0] = (s32) cur[0];
    vtx->v.ob[1] = (s32) cur[1];
    vtx->v.ob[2] = (s32) cur[2];
    vtx->v.tc[0] = u;
    vtx->v.tc[1] = tv[1];
    vtx->v.cn[0] = 0xFF;
    vtx->v.cn[1] = 0xFF;
    vtx->v.cn[2] = 0xFF;
    vtx->v.cn[3] = alpha;
    vtx->v.flag = 0;
    vtx++;
    vtx->v.ob[0] = (s32) (cur[0] - ox);
    vtx->v.ob[1] = (s32) cur[1];
    vtx->v.ob[2] = (s32) (cur[2] - oz);
    vtx->v.tc[0] = u;
    vtx->v.tc[1] = tv[r];
    vtx->v.cn[0] = 0xFF;
    vtx->v.cn[1] = 0xFF;
    vtx->v.cn[2] = 0xFF;
    vtx->v.cn[3] = 0;
    vtx->v.flag = 0;
    vtx++;

    /* one cross-section per older point, joined to the previous one by four triangles */
    for (;;) {
        ox = -dz * inv * qWidth;
        oz = dx * inv * qWidth;
        vtx->v.ob[0] = (s32) (nxt[0] + ox);
        vtx->v.ob[1] = (s32) nxt[1];
        vtx->v.ob[2] = (s32) (nxt[2] + oz);
        vtx->v.tc[0] = qU;
        vtx->v.tc[1] = tv[l];
        vtx->v.cn[0] = 0xFF;
        vtx->v.cn[1] = 0xFF;
        vtx->v.cn[2] = 0xFF;
        vtx->v.cn[3] = 0;
        vtx->v.flag = 0;
        vtx++;
        vtx->v.ob[0] = (s32) nxt[0];
        vtx->v.ob[1] = (s32) nxt[1];
        vtx->v.ob[2] = (s32) nxt[2];
        vtx->v.tc[0] = qU;
        vtx->v.tc[1] = tv[1];
        vtx->v.cn[0] = 0xFF;
        vtx->v.cn[1] = 0xFF;
        vtx->v.cn[2] = 0xFF;
        vtx->v.cn[3] = qAlpha;
        vtx->v.flag = 0;
        vtx++;
        vtx->v.ob[0] = (s32) (nxt[0] - ox);
        vtx->v.ob[1] = (s32) nxt[1];
        vtx->v.ob[2] = (s32) (nxt[2] - oz);
        vtx->v.tc[0] = qU;
        vtx->v.tc[1] = tv[r];
        vtx->v.cn[0] = 0xFF;
        vtx->v.cn[1] = 0xFF;
        vtx->v.cn[2] = 0xFF;
        vtx->v.cn[3] = 0;
        vtx->v.flag = 0;
        vtx++;
        gSPVertex(gfx++, vtx - 6, 6, 0);
        gSP1Triangle(gfx++, 0, 3, 4, 0);
        gSP1Triangle(gfx++, 0, 4, 1, 0);
        gSP1Triangle(gfx++, 1, 4, 5, 0);
        gSP1Triangle(gfx++, 1, 5, 2, 0);

        i = prev;
        prev--;
        if (prev < 0) {
            prev = t[0x25] - 1;
        }
        if (i == *(s8 *) (t + 0x2D)) {
            break;
        }
        cur[0] = nxt[0];
        cur[1] = nxt[1];
        cur[2] = nxt[2];
        q = &pts[prev];
        nxt[0] = q->x;
        nxt[1] = q->y;
        nxt[2] = q->z;
        qAlpha = (q->alpha * q->fade) >> 8;
        qU = q->texU;
        dx = nxt[0] - cur[0];
        dz = nxt[2] - cur[2];
        if (nxt[0] == cur[0] && dz == 0.0f) {
            inv = 1.0f;
        } else {
            inv = 1.0f / sqrtf(dx * dx + dz * dz);
        }
        qWidth = q->width;
    }
    return (s32) gfx;
}
