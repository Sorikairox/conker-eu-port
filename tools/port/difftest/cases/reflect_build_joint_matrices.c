void guMtxF2L2(float mf[4][4], Mtx *m);
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
s32 approx_dist2_int(s32 x0, s32 z0, s32 x1, s32 z1);
void obj_hide_masked_joints(struct127 *obj);

/* IDO's f32 -> u32 conversion (cvt.w.s, truncating): a result below 0 gives 0xFFFFFFFF. In C a negative value
 * converted to u32 is undefined (wasm traps), e.g. mode 0 with the object below the plane (y < b). */
#define IDO_F2U8(v) (((v) <= -1.0f) ? 0xFF : (u8) (u32) (v))

/* P95: builds the mirrored joint matrices of one draw-queue entry `e` (reflect_queue_object: the object itself, then each
 * attachment) and sets the entry alpha e->unk0[4].
 *   src = `model`: nmtx joint matrices of 0x40 bytes (Mtx fixed point when `fixed` != 0, else f32 matrices whose
 *         last column is reset to (0, 0, 0, 1) in place); dst = `mtx` (f32, converted to Mtx in place when
 *         `tofixed` != 0).
 *   mode 0 / 1: reflection in the plane y = b: dst = src * diag(1, -1, 1, 1), dst.y = 2b - src.y. The fade distance
 *         is the height y - b of the object above the plane.
 *   mode 2: reflection about the vertical plane through (a, b, c) turned by `f` around y (rotate by -f, flip x,
 *         rotate by f, around the point). The fade distance is the 2D distance (a, c) - (x, z) (approx_dist2_int).
 *   other modes: nothing at all.
 * Alpha: 0 beyond h, `alpha` below g (mode 0: ramped in over the first 10 units), linear between g and h.
 * Finally an object with unk9C set gets obj_hide_masked_joints run on the new matrices (unk1D4 swapped for the call). */
void reflect_build_joint_matrices(struct127 *obj, struct_eu_size0C *e, s32 mode, s32 model, s32 mtx, s32 nmtx, f32 a, f32 b, f32 c,
                   f32 d, f32 f, f32 x, f32 y, f32 z, f32 g, f32 h, f32 alpha, s32 fixed, s32 tofixed) {
    f32 flip[4][4];
    f32 rot1[4][4];
    f32 rot2[4][4];
    f32 tmp[4][4];
    f32 (*src)[4];
    f32 (*dst)[4];
    f32 dist;
    struct255 *saved;
    s32 i;

    guMtxIdentF(flip);
    if (mode == 0 || mode == 1) {
        flip[1][1] = -1.0f;
        for (i = 0; i < nmtx; i++) {
            if (fixed) {
                guMtxL2F(tmp, (Mtx *) (model + (i << 6)));
                src = tmp;
            } else {
                src = (f32 (*)[4]) (model + (i << 6));
                src[0][3] = 0.0f;
                src[1][3] = 0.0f;
                src[2][3] = 0.0f;
                src[3][3] = 1.0f;
            }
            dst = (f32 (*)[4]) (mtx + (i << 6));
            mtxf_mul(src, flip, dst);
            dst[3][1] = src[3][1] - (src[3][1] - b) * 2;
            if (tofixed) {
                bcopy(dst, tmp, 0x40);
                guMtxF2L2(tmp, (Mtx *) dst);
            }
        }
        dist = y - b;
    } else if (mode == 2) {
        flip[0][0] = -1.0f;
        mtxf_rotate_xyz_deg(rot1, 0.0f, -f, 0.0f);
        mtxf_rotate_xyz_deg(rot2, 0.0f, f, 0.0f);
        for (i = 0; i < nmtx; i++) {
            if (fixed) {
                guMtxL2F(tmp, (Mtx *) (model + (i << 6)));
                src = tmp;
            } else {
                src = (f32 (*)[4]) (model + (i << 6));
                src[0][3] = 0.0f;
                src[1][3] = 0.0f;
                src[2][3] = 0.0f;
                src[3][3] = 1.0f;
            }
            dst = (f32 (*)[4]) (mtx + (i << 6));
            bcopy(src, dst, 0x40);
            dst[3][0] -= a;
            dst[3][1] -= b;
            dst[3][2] -= c;
            mtxf_mul(dst, rot1, dst);
            mtxf_mul(dst, flip, dst);
            mtxf_mul(dst, rot2, dst);
            dst[3][0] += a;
            dst[3][1] += b;
            dst[3][2] += c;
            if (tofixed) {
                bcopy(dst, tmp, 0x40);
                guMtxF2L2(tmp, (Mtx *) dst);
            }
        }
        dist = (f32) approx_dist2_int((s32) a, (s32) c, (s32) x, (s32) z);
    } else {
        return;
    }

    if (h < dist) {
        e->unk0[4] = 0;
    } else if (dist < g) {
        if (mode == 0 && dist < 10.0f) {
            e->unk0[4] = IDO_F2U8(alpha / 10.0f * dist);
        } else {
            e->unk0[4] = IDO_F2U8(alpha);
        }
    } else {
        e->unk0[4] = IDO_F2U8(alpha - alpha * (dist - g) / (h - g));
    }

    if (obj != NULL && obj->unk9C != 0) {
        saved = obj->unk1D4;
        obj->unk1D4 = (struct255 *) mtx;
        obj_hide_masked_joints(obj);
        obj->unk1D4 = saved;
    }
}

