void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
f32 *func_15144B34(s32 arg0);
s32 func_1514306C(s32, s32, s32, u8);
s32 func_150954E4(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_151441A4(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
void func_151442FC(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
s32 func_15142B7C(s32, s32, s32);
s32 func_15142C10(s32, s32, s32, s32, s32, s8 *);
s32 func_15142CF0(s32, s32, s32, s16, s32, s32, s32, s8 *);
s32 func_1513F4E4(s32, u8, s8 *);
u8 *func_15142FBC(s32, s32, s32, s8 *);
f32 sqrtf(f32);
extern s32 D_80091914[];
extern s32 D_80091954[];
extern s32 D_800D30BC;
extern s32 D_800A4EA8[];

/* One strip vertex: position, flag 0, s = 0x43C0 (outer edge) or 0x4000 (inner edge), t = point +0x10 + 0x4000,
 * colour white. */
#define TRAIL_VTX(v, px, py, pz, s, t) \
    do { \
        *(s16 *)((v) + 0x0) = (s32)(px); \
        *(s16 *)((v) + 0x2) = (s32)(py); \
        *(s16 *)((v) + 0x4) = (s32)(pz); \
        *(s16 *)((v) + 0xA) = (t) + 0x4000; \
        *(s16 *)((v) + 0x8) = (s); \
        (v)[0xC] = 0xFF; \
        (v)[0xD] = 0xFF; \
        (v)[0xE] = 0xFF; \
        (v)[0xF] = 0xFF; \
        *(s16 *)((v) + 0x6) = 0; \
    } while (0)

// trail_draw: draws a trail particle as a camera-facing strip (type table D_8008A644 entry 1).
/* The points (obj +0x94, 0x14 bytes: x, y, z, vy, s16 texture t at +0x10) run from the newest (+0x2E - 1) back to
 * the oldest (+0x2D), ring of +0x25 entries. Each point gets two vertices, offset by +-n where n is the normal of
 * (point - camera) x (segment) scaled to the half width rec +0; each segment emits one 4-vertex load and two
 * triangles. Vertices come from func_151D6310 (2 per point but the last, double-buffered on D_800BE9C0). Sets the
 * texture (func_150954E4, only when it changed: D_800DD5E0), the colours rec +0x44 / +0x45 at alpha rec +0x1B,
 * the geometry mode rec +0x2C / +0x30, combine rec +0x3B and render mode rec +0x28 | +0x3C | +0x40 with the
 * D_800A4EA8 entry rec +0x34. Returns the display list end; draws nothing with fewer than 2 points. */
s32 func_151485AC(u8 *obj, s32 gfx, s16 arg2) {
    u8 *rec = *(u8 **)(obj + 0x98);
    u8 *pts;
    f32 *cam;
    u8 *v;
    u8 *p0;
    u8 *p1;
    s32 tex;
    s32 i;
    s32 j;
    s8 flag;
    s16 r0, g0, b0, a0;
    s16 r1, g1, b1, a1;
    f32 ax, ay, az;
    f32 bx, by, bz;
    f32 dx, dy, dz;
    f32 ex, ey, ez;
    f32 cx, cy, cz;
    f32 nx, ny, nz;
    f32 len;
    f32 k;

    if (*(s8 *)(obj + 0x2C) < 2) {
        return gfx;
    }
    func_151D6310((s32 *)(obj + 0x84), arg2, obj[0x25] * 0x20 - 0x20, (s32 *)&v, NULL);
    if (v == NULL) {
        return gfx;
    }
    if (D_800BE9C0 != 0) {
        v += (obj[0x25] * 2 - 2) * 0x10;
    }
    flag = 1;
    cam = func_15144B34(arg2);
    pts = *(u8 **)(obj + 0x94);
    tex = func_1514306C(0, rec[0x19], 0, 2);
    if (tex != D_800DD5E0) {
        D_80091954[0] = D_80091914[rec[0x19]];
        gfx = func_150954E4(gfx, D_80091954, 0, 0, 0, 0, 2, 0x100, 0x100, (rec[0x18] & 0x80) ? 0x3E : 3);
        D_800DD5E0 = tex;
    }
    func_151441A4(&r0, &g0, &b0, &a0, 0, 0, 0, 0, 0, 0, 0, rec[0x1B], rec[0x1A], *(s8 *)(rec + 0x44));
    func_151442FC(&r1, &g1, &b1, &a1, 0, 0, 0, 0, 0, 0, 0, rec[0x1B], rec[0x1A], *(s8 *)(rec + 0x45));
    gfx = func_15142B7C(gfx, *(s32 *)(rec + 0x2C), *(s32 *)(rec + 0x30));
    gfx = func_15142C10(gfx, r1, g1, b1, a1, &flag);
    gfx = func_15142CF0(gfx, 0, 0, r0, g0, b0, a0, &flag);
    gfx = func_1513F4E4(gfx, rec[0x3B], &flag);
    gfx = (s32)func_15142FBC(gfx, *(s32 *)(rec + 0x28) | 0x80000 | D_800D30BC | 0x2C00 | *(s32 *)(rec + 0x3C) | *(s32 *)(rec + 0x40),
                             D_800A4EA8[*(s32 *)(rec + 0x34) * 2 + 1] | D_800A4EA8[*(s32 *)(rec + 0x34) * 2], &flag);

    i = *(s8 *)(obj + 0x2E) - 1;
    if (i < 0) {
        i = obj[0x25] - 1;
    }
    j = i - 1;
    if (j < 0) {
        j = obj[0x25] - 1;
    }
    p0 = pts + i * 0x14;
    p1 = pts + j * 0x14;
    ax = *(f32 *)(p0 + 0);
    ay = *(f32 *)(p0 + 4);
    az = *(f32 *)(p0 + 8);
    bx = *(f32 *)(p1 + 0);
    by = *(f32 *)(p1 + 4);
    bz = *(f32 *)(p1 + 8);

    /* the newest point */
    dx = ax - cam[0];
    dy = ay - cam[1];
    dz = az - cam[2];
    ex = ax - bx;
    ey = ay - by;
    ez = az - bz;
    cx = ey * dz - dy * ez;
    cy = ez * dx - dz * ex;
    cz = ex * dy - dx * ey;
    len = sqrtf(cx * cx + cy * cy + cz * cz);
    if (len == 0.0f) {
        nx = ny = nz = 0.0f;
    } else {
        k = *(f32 *)(rec + 0) / len;
        nx = cx * k;
        ny = cy * k;
        nz = cz * k;
    }
    TRAIL_VTX(v, ax + nx, ay + ny, az + nz, 0x43C0, *(u16 *)(p0 + 0x10));
    v += 0x10;
    TRAIL_VTX(v, ax - nx, ay - ny, az - nz, 0x4000, *(u16 *)(p0 + 0x10));
    v += 0x10;

    /* one segment per older point */
    do {
        i = j;
        j--;
        dx = bx - cam[0];
        dy = by - cam[1];
        dz = bz - cam[2];
        ex = ax - bx;
        ey = ay - by;
        ez = az - bz;
        cx = ey * dz - dy * ez;
        cy = ez * dx - dz * ex;
        cz = ex * dy - dx * ey;
        len = sqrtf(cx * cx + cy * cy + cz * cz);
        if (len == 0.0f) {
            nx = ny = nz = 0.0f;
        } else {
            k = *(f32 *)(rec + 0) / len;
            nx = cx * k;
            ny = cy * k;
            nz = cz * k;
        }
        TRAIL_VTX(v, bx + nx, by + ny, bz + nz, 0x43C0, *(u16 *)(p1 + 0x10));
        v += 0x10;
        TRAIL_VTX(v, bx - nx, by - ny, bz - nz, 0x4000, *(u16 *)(p1 + 0x10));
        v += 0x10;
        ((s32 *)gfx)[0] = 0x01004008;           /* gSPVertex(v - 4, 4, 0) */
        ((s32 *)gfx)[1] = (s32)(v - 0x40);
        gfx += 8;
        ((s32 *)gfx)[0] = 0x05000204;           /* gSP1Triangle(0, 1, 2) */
        ((s32 *)gfx)[1] = 0;
        gfx += 8;
        ((s32 *)gfx)[0] = 0x05020604;           /* gSP1Triangle(1, 3, 2) */
        ((s32 *)gfx)[1] = 0;
        gfx += 8;
        p1 -= 0x14;
        if (j < 0) {
            j = obj[0x25] - 1;
            p1 = pts + j * 0x14;
        }
        p0 = pts + i * 0x14;
        ax = *(f32 *)(p0 + 0);
        ay = *(f32 *)(p0 + 4);
        az = *(f32 *)(p0 + 8);
        bx = *(f32 *)(p1 + 0);
        by = *(f32 *)(p1 + 4);
        bz = *(f32 *)(p1 + 8);
    } while (i != *(s8 *)(obj + 0x2D));
    return gfx;
}
#undef TRAIL_VTX
