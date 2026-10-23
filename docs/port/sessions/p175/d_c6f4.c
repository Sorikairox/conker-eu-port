void func_151D6310(s32 *, s16, s32, Vtx **, u8 *);
void func_151441A4(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
void func_151442FC(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
s32 func_15142E24(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
s32 func_1513F4E4(s32, u8, s8 *);
s32 func_15142B7C(s32, s32, s32);
s32 func_15142CF0(s32, s32, s32, s16, s32, s32, s32, s8 *);
s32 func_15142C10(s32, s32, s32, s32, s32, s8 *);
s32 func_15142FBC(s32, s32, s32, s8 *);
f32 sqrtf(f32);
extern s32 D_80091228[];  /* streak texture descriptor */
extern s32 D_800D30BC;
extern s32 D_800A4EA8[];  /* render mode pairs (2 words each) */

/* One streak vertex: position, flag 0, texture (s, t), colour white with alpha a. */
#define STREAK_VTX(v, px, py, pz, s, t, a) \
    do { \
        (v)->v.ob[0] = (s32) (px); \
        (v)->v.ob[1] = (s32) (py); \
        (v)->v.ob[2] = (s32) (pz); \
        (v)->v.tc[0] = (s); \
        (v)->v.tc[1] = (t); \
        (v)->v.cn[0] = 0xFF; \
        (v)->v.cn[1] = 0xFF; \
        (v)->v.cn[2] = 0xFF; \
        (v)->v.cn[3] = (a); \
        (v)->v.flag = 0; \
    } while (0)

/* Half-width offset of a streak point: the normal of (segment a - b) x (point - camera), scaled to rec +0. */
#define STREAK_NORMAL(px, py, pz) \
    do { \
        dx = (px) - cam[0]; \
        dy = (py) - cam[1]; \
        dz = (pz) - cam[2]; \
        ex = ax - bx; \
        ey = ay - by; \
        ez = az - bz; \
        cx = ey * dz - dy * ez; \
        cy = ez * dx - dz * ex; \
        cz = ex * dy - dx * ey; \
        len2 = cx * cx + cy * cy + cz * cz; \
        if (len2 == 0.0f) { \
            nx = ny = nz = 0.0f; \
        } else { \
            k = *(f32 *) (rec + 0) / sqrtf(len2); \
            nx = cx * k; \
            ny = cy * k; \
            nz = cz * k; \
        } \
    } while (0)

// particle_streak_draw: draws a streak particle as a camera-facing ribbon (kind 8 of D_8008A644).
/* The points (obj +0x94, 0x10 bytes: x, y, z, vy) run from the newest (+0x2E - 1) back to the oldest (+0x2D), ring
 * of +0x25 entries, count +0x2C. Each point gets two vertices offset by +-n (STREAK_NORMAL; camera of view arg2 at
 * D_800DBFF0 + arg2 * 0x9A0 + 0x2F8): texture s runs 0..0x800 along the ribbon, t = 0x3FF / 0 across it, and the
 * alpha fades from 0 at the head to rec +0x1A at the tail. Each segment emits one 4-vertex load and two triangles.
 * Vertices come from func_151D6310 (2 per point + 10 spare). Sets the texture D_80091228 (combine 0x3E), combine
 * rec +0x21, geometry mode rec +0x24 / +0x28, the env / prim colours from rec +0x15..+0x1F (func_151441A4 /
 * func_151442FC), render mode 0x80000 | 0x2CA0 | D_800D30BC (| 0x100000 with rec +0x14 flag 1) with the
 * D_800A4EA8 entry rec +0x20. Returns the display list end; draws nothing with fewer than 2 points. */
s32 func_1515C6F4(u8 *obj, s32 gfx, s16 arg2) {
    u8 *rec;
    u8 *pts;
    f32 *cam;
    Vtx *v;
    f32 *p1;
    s32 i;
    s32 j;
    s32 ds;
    s32 da;
    s32 s;
    s32 a;
    s8 flag;
    s16 r0, g0, b0, a0;
    s16 r1, g1, b1, a1;
    f32 ax, ay, az;
    f32 bx, by, bz;
    f32 dx, dy, dz;
    f32 ex, ey, ez;
    f32 cx, cy, cz;
    f32 nx, ny, nz;
    f32 len2;
    f32 k;

    if (*(s8 *) (obj + 0x2C) < 2) {
        return gfx;
    }
    func_151D6310((s32 *) (obj + 0x84), arg2, obj[0x25] * 0x20 + 0xA0, &v, NULL);
    if (v == NULL) {
        return gfx;
    }
    rec = *(u8 **) (obj + 0x98);
    flag = 1;
    pts = *(u8 **) (obj + 0x94);
    cam = (f32 *) ((u8 *) D_800DBFF0 + arg2 * 0x9A0 + 0x2F8);
    func_151441A4(&r0, &g0, &b0, &a0, rec[0x1B], rec[0x1C], rec[0x1D], rec[0x1E], rec[0x17], rec[0x18], rec[0x19],
                  rec[0x1A], rec[0x1F], rec[0x15]);
    func_151442FC(&r1, &g1, &b1, &a1, rec[0x1B], rec[0x1C], rec[0x1D], rec[0x1E], rec[0x17], rec[0x18], rec[0x19],
                  rec[0x1A], rec[0x1F], rec[0x16]);
    gfx = func_15142E24(gfx, D_80091228, 0, 0, 0, 0, 0x42, 0, 0, &flag, 0x3E);
    gfx = func_1513F4E4(gfx, rec[0x21], &flag);
    gfx = func_15142B7C(gfx, *(s32 *) (rec + 0x24), *(s32 *) (rec + 0x28));
    gfx = func_15142CF0(gfx, 0, 0, r0, g0, b0, a0, &flag);
    gfx = func_15142C10(gfx, r1, g1, b1, a1, &flag);
    gfx = func_15142FBC(gfx, ((rec[0x14] & 1) ? 0x100000 : 0) | 0x80000 | D_800D30BC | 0x2CA0,
                        D_800A4EA8[rec[0x20] * 2 + 1] | D_800A4EA8[rec[0x20] * 2], &flag);

    i = *(s8 *) (obj + 0x2E) - 1;
    if (i < 0) {
        i = obj[0x25] - 1;
    }
    j = i - 1;
    if (j < 0) {
        j = obj[0x25] - 1;
    }
    ax = ((f32 *) (pts + i * 0x10))[0];
    ay = ((f32 *) (pts + i * 0x10))[1];
    az = ((f32 *) (pts + i * 0x10))[2];
    p1 = (f32 *) (pts + j * 0x10);
    bx = p1[0];
    by = p1[1];
    bz = p1[2];
    ds = 0x800 / (*(s8 *) (obj + 0x2C) - 1);
    da = 0xFF / (*(s8 *) (obj + 0x2C) - 1);

    /* the newest point: alpha 0, s = 0 */
    STREAK_NORMAL(ax, ay, az);
    STREAK_VTX(v, ax + nx, ay + ny, az + nz, 0, 0x3FF, 0);
    v++;
    STREAK_VTX(v, ax - nx, ay - ny, az - nz, 0, 0, 0);
    v++;

    /* one segment per older point */
    s = ds;
    a = da;
    do {
        i = j;
        j--;
        STREAK_NORMAL(bx, by, bz);
        STREAK_VTX(v, bx + nx, by + ny, bz + nz, s, 0x3FF, (u32) (rec[0x1A] * a) >> 8);
        v++;
        STREAK_VTX(v, bx - nx, by - ny, bz - nz, s, 0, (u32) (rec[0x1A] * a) >> 8);
        v++;
        s += ds;
        a += da;
        ((s32 *) gfx)[0] = 0x01004008; /* gSPVertex(v - 4, 4, 0) */
        ((s32 *) gfx)[1] = (s32) (v - 4);
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05000204; /* gSP1Triangle(0, 1, 2) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05020604; /* gSP1Triangle(1, 3, 2) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        p1 -= 4;
        if (j < 0) {
            j = obj[0x25] - 1;
            p1 = (f32 *) (pts + j * 0x10);
        }
        ax = bx;
        ay = by;
        az = bz;
        bx = p1[0];
        by = p1[1];
        bz = p1[2];
    } while (i != *(s8 *) (obj + 0x2D));
    return gfx;
}
#undef STREAK_VTX
#undef STREAK_NORMAL
