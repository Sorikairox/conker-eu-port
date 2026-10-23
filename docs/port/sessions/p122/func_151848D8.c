/* Shadow light list (D_800DCD78): the lights an object's shadow can be cast from. */
typedef struct ShadowLight {
    struct ShadowLight *next; /* 0x00 */
    u8 off;                   /* 0x04: != 0: ignored */
    u8 pad5[4];
    u8 hidden;                /* 0x09: != 0: ignored */
    u8 padA[4];
    s16 x;                    /* 0x0E: position */
    s16 y;                    /* 0x10 */
    s16 z;                    /* 0x12 */
} ShadowLight;

extern s32 D_800DE464;        /* != 0: no point lights (only the default direction) */
extern f32 D_800DE440[3];     /* default light direction (reset to (100, 600, -200) when its y <= 0) */
extern f32 D_800DE46C;        /* world scale of the shadow distances */
extern s32 D_800DE468;        /* shadow detail level: >= 2 snaps the light positions */
extern f32 D_800DE3E0[][3];   /* per shadow slot: smoothed light position */
extern f32 D_800DFB28;        /* distance object -> light of the last projection */
extern s8 D_800DE470;         /* != 0: the minimum light height grows with the horizontal distance */
extern f32 D_800DE458;        /* far clip depth (before the scale) */
extern s8 D_800DF511;         /* != 0: flat shadows: y size / 4, half the far depth */
extern s32 D_800DF528;        /* [slot] f32 [4][4]: light view matrix */
extern s8 D_8008D798[8][3];   /* the 8 corners (+-1, +-1, +-1) of the object's box */
extern f32 D_800D3AA0[2];     /* projection x / y scale (>= 1) */
extern u16 D_800DF500[];      /* [slot]: perspNorm of the projection */
extern u8 D_800DF728[];       /* [slot][frame] Mtx (0x40 bytes): fixed-point projection */
extern u8 D_800DE478[];       /* shadow texture buffer (D_800DF4B8 = its 64-byte aligned start) */
extern s32 D_800DF4B8;
extern f32 D_800DE45C;        /* shadow alpha */
s32 func_150AD9A0(s32, s32, s32);
void func_15047680(f32 mf[4][4], f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_150A7A48(f32 a[4][4], f32 b[4][4], f32 c[4][4]);
void func_15048F90(struct17 *, struct17 *, struct17 *);
f32 func_150AD930(f32 *);
void func_150A7E40(f32 mf[4][4], f32, f32, f32, f32 *, f32 *, f32 *);
void func_150A7CB0(f32 mtx[4][4], s32, s32, s32);
f32 func_150484A0(f32, f32);

/* shadow_light_projection: sets up shadow slot `slot` of object record `obj` (box half sizes sx, sy, sz).
 * Light: unless D_800DE464, the nearest enabled light of the list D_800DCD78 whose integer distance
 * (func_150AD9A0) is above prev_dist and below 5000; with none, 0 is returned when prev_dist != 0, else the default
 * direction D_800DE440 (scaled by D_800DE46C) from the object is used with distance 1. The slot's light position
 * D_800DE3E0[slot] snaps to it (detail >= 2 or *D_800DBFF4) or moves 0.3 of the way. The light is pushed out to at
 * least 200 units and to a minimum height (10, or 0.57735 * the horizontal distance when D_800DE470); beyond
 * 5000 * scale nothing is cast. A look-at matrix from the light to the object (D_800DF528[slot]) projects the 8 box
 * corners; their largest |x / z|, |y / z| (>= 0.01, else nothing) give the projection scale D_800D3AA0 and the
 * nearest corner depth (< -1, else nothing) the near clip D_800D3AAC (far clip D_800D3AA8 = -(D_800DE458 * scale)
 * - distance, half that and y size / 4 when D_800DF511). A perspective (halved in scale until every element of
 * view * persp is below 32767) times a (0.5, 0.5, 1) scale goes to the Mtx D_800DF728[slot][D_800BE9C0]. The shadow
 * alpha D_800DE45C = 255 - (+0x1DD >> 1), at most 185, fades when +0xCC is below -10 (0 returned at <= 5).
 * Returns the light distance (1 for the default light), or 0 when no shadow is cast; D_800D3AA8 / D_800D3AAC are
 * cleared then (except for the early returns before the light is moved). */
f32 func_151848D8(s32 obj, s32 slot, f32 sx, f32 sy, f32 sz, f32 prev_dist) {
    struct127 *rec;
    ShadowLight *light;
    f32 pos[3];
    f32 target[3];
    f32 dir[3];
    f32 *lit;
    f32 (*view)[4];
    f32 mf[4][4];
    f32 scale_mf[4][4];
    f32 best;
    f32 lx, ly, lz;
    f32 d;
    f32 k;
    f32 min_h;
    f32 px, py, pz;
    f32 max_x, max_y, max_z;
    f32 persp_scale;
    f32 fovy;
    f32 m;
    f32 cc;
    s32 found;
    s32 done;
    s32 i;

    rec = &D_800CC2D0[obj];
    done = 0;
    best = 5000.0f;
    pos[0] = rec->x_position;
    persp_scale = 2.0f;
    pos[1] = rec->y_position;
    found = 0;
    pos[2] = rec->z_position;

    if (D_800DE464 == 0) {
        for (light = (ShadowLight *) D_800DCD78; light != NULL; light = light->next) {
            if (light->off != 0 || light->hidden != 0) {
                continue;
            }
            lx = light->x;
            ly = light->y;
            lz = light->z;
            d = func_150AD9A0((s32) (lx - pos[0]), (s32) (ly - pos[1]), (s32) (lz - pos[2]));
            if (d < best && prev_dist < d) {
                best = d;
                found++;
                target[0] = lx;
                target[1] = ly;
                target[2] = lz;
            }
        }
    }
    if (found == 0) {
        if (prev_dist != 0.0f) {
            return 0.0f;
        }
        if (D_800DE440[1] <= 0.0f) {
            D_800DE440[1] = 600.0f;
            D_800DE440[0] = 100.0f;
            D_800DE440[2] = -200.0f;
        }
        best = 1.0f;
        target[0] = D_800DE440[0] * D_800DE46C + pos[0];
        target[1] = D_800DE440[1] * D_800DE46C + pos[1];
        target[2] = D_800DE440[2] * D_800DE46C + pos[2];
    }

    lit = D_800DE3E0[slot];
    if (*(s32 *) D_800DBFF4 != 0 || D_800DE468 >= 2) {
        lit[0] = target[0];
        lit[1] = target[1];
        lit[2] = target[2];
    } else {
        lit[0] += (target[0] - lit[0]) * 0.3f;
        lit[1] += (target[1] - lit[1]) * 0.3f;
        lit[2] += (target[2] - lit[2]) * 0.3f;
    }

    func_15048F90((struct17 *) pos, (struct17 *) lit, (struct17 *) dir);
    D_800DFB28 = func_150AD930(dir);
    if (D_800DFB28 < 200.0f) {
        /* at least 200 units away along the same direction */
        k = 200.0f / D_800DFB28;
        D_800DFB28 = 200.0f;
        for (i = 0; i < 3; i++) {
            d = dir[i] * k;
            lit[i] += d - dir[i];
            dir[i] = d;
        }
    }
    if (D_800DE470 != 0) {
        min_h = sqrtf(dir[0] * dir[0] + dir[2] * dir[2]) * 0.57735f;
        if (min_h < 10.0f) {
            min_h = 10.0f;
        }
    } else {
        min_h = 10.0f;
    }
    if (dir[1] < min_h) {
        /* raise the light, then rescale the offset to the old distance */
        lit[1] += min_h - dir[1];
        dir[1] = min_h;
        d = func_150AD9A0((s32) dir[0], (s32) dir[1], (s32) dir[2]);
        k = D_800DFB28 / d;
        D_800DFB28 = d;
        for (i = 0; i < 3; i++) {
            lit[i] += dir[i] * k - dir[i];
        }
    }
    if (5000.0f * D_800DE46C < D_800DFB28) {
        D_800D3AA8 = 0.0f;
        D_800D3AAC = D_800D3AA8;
        return 0.0f;
    }
    if (D_800DF511 != 0) {
        sy *= 0.25f;
        D_800D3AA8 = -(D_800DE458 * D_800DE46C * 0.5f) - D_800DFB28;
    } else {
        D_800D3AA8 = -D_800DE458 * D_800DE46C - D_800DFB28;
    }

    view = (f32 (*)[4]) ((u8 *) &D_800DF528 + slot * 0x40);
    func_15047680(view, lit[0], lit[1], lit[2], pos[0], pos[1], pos[2], 0.0f, 1.0f, 0.0f);
    max_y = 0.0f;
    max_x = 0.0f;
    max_z = -1000000.0f;
    for (i = 0; i < 8; i++) {
        func_150A7E40(view, D_8008D798[i][0] * sx + pos[0], D_8008D798[i][1] * sy + pos[1],
                      D_8008D798[i][2] * sz + pos[2], &px, &py, &pz);
        if (pz == 0.0f) {
            pz = 0.0001f;
        }
        px = px / pz;
        py = py / pz;
        if (px < 0.0f) {
            px = -px;
        }
        if (max_x < px) {
            max_x = px;
        }
        if (py < 0.0f) {
            py = -py;
        }
        if (max_y < py) {
            max_y = py;
        }
        if (max_z < pz) {
            max_z = pz;
        }
    }
    if (max_x < 0.01f || max_y < 0.01f) {
        D_800D3AA8 = 0.0f;
        D_800D3AAC = D_800D3AA8;
        return 0.0f;
    }
    D_800D3AA0[0] = 1.0f / max_x;
    D_800D3AA0[1] = 1.0f / max_y;
    if (D_800D3AA0[0] < 1.0f) {
        D_800D3AA0[0] = 1.0f;
    }
    if (D_800D3AA0[1] < 1.0f) {
        D_800D3AA0[1] = 1.0f;
    }
    if (!(max_z < -1.0f)) {
        D_800D3AA8 = 0.0f;
        D_800D3AAC = D_800D3AA8;
        return 0.0f;
    }
    D_800D3AAC = max_z;
    do {
        m = 1.0f;
        fovy = func_150484A0(1.0f, D_800D3AA0[1]);
        guPerspectiveF(mf, &D_800DF500[slot], fovy * 57.295776f, func_150484A0(1.0f, D_800D3AA0[0]) * 57.295776f,
                       -D_800D3AAC, -D_800D3AA8, persp_scale);
        func_150A7A48(view, mf, mf);
        for (i = 0; i < 16; i++) {
            d = mf[i >> 2][i & 3];
            if (d < 0.0f) {
                d = -d;
            }
            if (m < d) {
                m = d;
            }
        }
        if (m < 32767.0f) {
            done = 1;
        } else {
            persp_scale *= 0.5f;
        }
    } while (done == 0);
    func_150A7CB0(scale_mf, 0x3F000000, 0x3F000000, 0x3F800000); /* f32 bits: scale (0.5, 0.5, 1) */
    func_150A7A48(mf, scale_mf, mf);
    guMtxF2L(mf, (Mtx *) (D_800DF728 + slot * 0x80 + D_800BE9C0 * 0x40));
    D_800DF4B8 = ((s32) D_800DE478 + 0x3F) & ~0x3F;

    D_800DE45C = 0xFF - (rec->unk1DD >> 1);
    if (D_800DE45C > 185.0f) {
        D_800DE45C = 185.0f;
    }
    cc = rec->unkCC;
    if (cc < -10.0f) {
        D_800DE45C += D_800DE45C * (cc + 10.0f) * 0.02f;
        if (D_800DE45C <= 5.0f) {
            return 0.0f;
        }
    }
    return best;
}
