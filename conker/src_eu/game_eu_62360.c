#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* obj_adjust_entries_face (P57): per-object adjustment entries for the face (eyelids / mouth), appended to buf as
 * {u16 offset, s16 value} pairs for anim_eval_joint_matrices; returns the end (obj_adjust_list_build writes the 0x1000 terminator).
 * obj = &g_objects[i] (bytes): +4 type, +0x1FE blink amount, +0x1FF blink state, +0x200 blink timer,
 * +0x201 blink angle, +0x202 random blink offset, +0x203 blink speed; +0x204 mouth amount (s16), +0x206 mouth
 * state, +0x207 mouth timer, +0x208 mouth angle (s8), +0x209 mouth speed. a2 / a3: joint indices (0xFF = none). */
extern s16 D_800C4310;
/* was func_15034B50 */
s16 *obj_adjust_entries_face(s16 *buf, u8 *obj, s32 a2, s32 a3) {
    s32 type = obj[4];
    s32 noeye = (type == 0x70);
    s32 off1, off2, rnd, sp, lo, r, sgn, v;
    s32 go, neg;
    f32 f;

    if (type == 0x7C) { off1 = 4; off2 = 0; } else { off1 = 0; off2 = 2; }
    if (type == 0x69 || type == 0x7C || type == 0x87) rnd = 0; else rnd = 10;

    if (a2 != 0xFF) {
        if (obj[0x201] == 0) f = 8191.875f;
        else f = (f32)obj[0x201] * 182.04445f;
        v = (s16)(s32)(((f32)obj[0x1FE] * f) * 0.003921569f);
        if (!noeye) { buf[0] = a2 * 6 + off1; buf[1] = v; buf += 2; }
        D_800C4310 = v;
        r = ((s8)obj[0x202] * (s32)obj[0x1FE]) / 255;
        v = (s16)(s32)(((f32)r * 65535.0f) * 0.003921569f);
        if (!noeye) { buf[0] = a2 * 6 + off2; buf[1] = v; buf += 2; }

        lo = 0x28; sp = 0x3C;
        if (obj[4] == 0x42) { lo = 0x50; sp = 0x78; }
        v = obj[0x1FF];
        if (v == 0) {
            obj[0x203] = -sp;
        } else if (v == 2) {
            obj[0x203] = sp;
            obj[0x202] = 0;
        } else if ((s8)obj[0x203] == 0 || obj[0x1FE] == 0 || obj[0x1FE] == 0xFF) {
            r = random_int();
            obj[0x203] = (u32)r % (u32)(sp - lo) + lo;
            if (obj[0x1FE] == 0xFF) {
                obj[0x203] = -(s8)obj[0x203];
            } else if (obj[0x1FE] == 0 && rnd != 0) {
                r = random_int();
                obj[0x202] = (u32)r % (u32)(rnd * 2) - rnd;
            }
        }
        v = (s16)(obj[0x1FE] + (s8)obj[0x203]);
        if (v < 0) v = 0;
        else if (v >= 0x100) v = 0xFF;
        obj[0x1FE] = v;
        if (obj[0x1FF] == 3) {
            if ((s32)obj[0x200] < g_frame_ticks) { obj[0x200] = 0; obj[0x1FF] = 0; }
            else obj[0x200] = obj[0x200] - g_frame_ticks;
        }
    }
    if (a3 == 0xFF) return buf;

    sgn = 1;
    if ((s8)obj[0x208] == 0) f = 8191.875f;
    else f = (f32)(s8)obj[0x208] * 182.04445f;
    if (f < 0.0f) sgn = -1;
    buf[0] = a3 * 6 + off1;
    buf[1] = -(s32)(((f32)*(s16 *)(obj + 0x204) * (f < 0.0f ? -f : f)) * 0.003921569f);
    buf += 2;
    go = 0; neg = 0;
    if (obj[0x206] == 0) {
        obj[0x209] = (sgn > 0) ? -0x3C : 0x3C;
    } else if (obj[0x206] == 2) {
        obj[0x209] = (sgn > 0) ? 0x3C : -0x3C;
    } else {
        s32 s = (s8)obj[0x209];
        if (s == 0) go = 1;
        else {
            v = *(s16 *)(obj + 0x204);
            if (sgn > 0) {
                if (v < 0 && s < 0) neg = 1;
                else if (v == 0 && s < 0) go = 1;
                else if (v == 0xFF) { neg = 1; go = 1; }
            } else {
                if (v > 0 && s > 0) neg = 1;
                else if (v == 0 && s > 0) go = 1;
                else if (v == -0xFF) { neg = 1; go = 1; }
            }
        }
    }
    if (go) {
        r = random_int();
        obj[0x209] = (u32)r % 20 + 0x28;
        obj[0x209] = (s8)obj[0x209] * sgn;
    }
    if (neg) obj[0x209] = -(s8)obj[0x209];
    {
        s32 s = (s8)obj[0x209];
        *(s16 *)(obj + 0x204) = *(s16 *)(obj + 0x204) + s;
        v = *(s16 *)(obj + 0x204);
        if (sgn > 0) {
            if (v < 0 && s < 0) *(s16 *)(obj + 0x204) = 0;
            else if (v >= 0x100) *(s16 *)(obj + 0x204) = 0xFF;
        } else {
            if (v > 0 && s > 0) *(s16 *)(obj + 0x204) = 0;
            else if (v < -0xFF) *(s16 *)(obj + 0x204) = -0xFF;
        }
    }
    if (obj[0x206] == 3) {
        if ((s32)obj[0x207] < g_frame_ticks) { obj[0x207] = 0; obj[0x206] = 0; }
        else obj[0x207] = obj[0x207] - g_frame_ticks;
    }
    return buf;
}

extern s16 D_800C4310;

/* was func_150351A4 */
void obj_lower_joints_by_face(u8 *arg0, s32 arg1, s32 arg2)
{
  f32 temp_f0;
  s32 temp_v1;
  u8 *temp_a2;
  s32 new_var;
  if (D_800C4310 != 0)
  {
    u8 *temp_v0;
    temp_v1 = (new_var = /* fakematch: permuter chain */ *((s32 *) (((u8 *) arg0) + 0x1D4)));
    temp_a2 = (arg1 << 6) + temp_v1;
    temp_v0 = (arg2 << 6) + new_var;
    temp_v1 = D_800C4310;
    temp_f0 = ((f32) temp_v1) * 0.00076296274f;
    temp_f0 *= *((f32 *) (((u8 *) arg0) + 0x14C));
    *((f32 *) (((u8 *) temp_a2) + 0x34)) = (f32) ((*((f32 *) (((u8 *) temp_a2) + 0x34))) - temp_f0);
    if (((0, arg2)) != (-1)) // fakematch: permuter comma
    {
      *((f32 *) (((u8 *) ((arg2 << 6) + new_var)) + 0x34)) = (f32) ((*((f32 *) (((u8 *) temp_v0) + 0x34))) - temp_f0);
    }
  }
}

/* was func_15035210 */
void reflect_queue_reset(void) {
    D_800C4320 = 0;
}

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
/* was func_15035220 */
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

/* was func_150359B8 */
struct_eu_size0C *reflect_queue_alloc(void) {
    if (D_800C4320 == 15) {
        return NULL;
    }
    D_800C4320++;
    return &D_800C4328[D_800C4320 - 1];
}

s32 camera_view_test_sphere(s32, s32 *, f32, f32, f32, f32, f32, f32);
extern s32 g_view_mtxf; /* was D_800DA030 */
extern f32 D_80098120;

/* was func_15035A04 */
s32 reflect_is_culled(s32 arg0, u8 *arg1, u8 *arg2, f32 arg3) {
    s32 sp28 = g_player_cams;
    struct124 *e = D_800D1C90[arg1[4]];
    f32 w = (f32)(u16)e->unkE;
    f32 h = (f32)*(s16 *)((u8 *)e + 0x10) * *(f32 *)(arg1 + 0x150);
    f32 y;

    if (arg0 == 1 || arg0 == 0) {
        y = arg3 - ((*(f32 *)(arg1 + 0x18) + h) - arg3);
    } else {
        y = *(f32 *)(arg1 + 0x18) + h;
    }
    return camera_view_test_sphere(sp28, &g_view_mtxf, *(f32 *)(arg2 + 0x30), y, *(f32 *)(arg2 + 0x38),
                         w * *(f32 *)(arg1 + 0x14C), w * *(f32 *)(arg1 + 0x150), D_80098120) == 0;
}
void reflect_build_joint_matrices(struct127 *obj, struct_eu_size0C *e, s32 mode, s32 model, s32 mtx, s32 nmtx, f32 a, f32 b, f32 c, f32 d, f32 f, f32 x, f32 y, f32 z, f32 g, f32 h, f32 alpha, s32 shadow, s32 sub);
s32 model_joint_mtx_count(s32 id);
void obj_ambient_colour(s32 id, u8 *col);
s32 approx_dist3_int(s32 dx, s32 dy, s32 dz);
s32 attachment_get_matrices(u8 *att, u8 *obj, s32 *model, s32 *out);
f32 *allocate_memory(s32, s32, s32, s32);

/* P93: queue the draw (and shadow) of object `idx` for this frame. Fades out between max - 200 and max (max = 1400,
 * or 10000 when D_800C35EA == 1) of the camera distance, scaled by obj->unk7 (0xFF = opaque). Reserves the
 * object's joint matrices in the D_800C42A8 arena (model_joint_mtx_count(id) x 0x40 bytes) unless reflect_is_culled culls it,
 * then adds one entry per attachment of D_800C3EE0 that belongs to the object (attachment_get_matrices accepts it). */
/* was func_15035AF8 */
void reflect_queue_object(s32 mode, s32 idx, f32 a, f32 b, f32 c, f32 d, f32 f, f32 g, f32 h, f32 alpha) {
    struct127 *obj;
    struct_eu_size0C *e;
    u8 *att;
    u8 *next;
    s32 col[3];
    s32 model;
    s32 out[4];
    s32 nmtx;
    s32 max;
    s32 dist;
    s32 fade;
    s32 a8;
    s32 mtx;
    s32 shadow;
    u8 opacity;

    if (D_800C4320 == 15) {
        return;
    }
    max = 1400;
    if (mode == 0 && g_objects[idx].interaction_state != 1) {
        return;
    }
    obj = &g_objects[idx];
    if (obj->unk1D4 == NULL || (obj->unk74 & 0xF) == 0xF) {
        return;
    }
    opacity = obj->unk7;
    if (opacity == 0) {
        return;
    }
    nmtx = model_joint_mtx_count(obj->id);
    if ((u32) (g_matrix_arena_count << 6) < (u32) (D_800C42A8 + (nmtx << 6) - D_800C42AC)) {
        return;   /* the matrix arena is full */
    }
    if (D_800C35EA == 1) {
        max = 10000;
    }
    dist = approx_dist3_int((s32) (g_player_views->unk2F8 - obj->x_position), (s32) (g_player_views->unk2FC - obj->y_position),
                         (s32) (g_player_views->unk300 - obj->z_position));
    if ((f32) max < (f32) dist) {
        return;
    }
    fade = 0x100;
    if ((f32) (max - 200) < (f32) dist) {
        fade = (s32) (((f32) max - (f32) dist) * 256.0f / (f32) (max - 200));
    }
    if (opacity != 0xFF) {
        fade = (s32) ((u32) fade * opacity) >> 8;
    }

    e = reflect_queue_alloc();
    if (e == NULL) {
        return;
    }
    *(s32 *) &e->unk0[0] = D_800C42A8;
    obj_ambient_colour(idx, (u8 *) col);
    e->unk0[5] = col[0];
    e->unk0[6] = col[1];
    e->unk0[7] = col[2];
    e->unk0[0xB] = 0;
    e->unk0[8] = idx;
    e->unk0[9] = obj->unique_id;
    model = (s32) obj->unk1D4;
    reflect_build_joint_matrices(obj, e, mode, model, *(s32 *) &e->unk0[0], nmtx, a, b, c, d, f, obj->x_position, obj->y_position,
                  obj->z_position, g, h, alpha, 0, 0);
    e->unk0[4] = (s32) ((u32) e->unk0[4] * fade) >> 8;
    if (reflect_is_culled(mode, (u8 *) obj, (u8 *) model, b) != 0) {
        D_800C4320--;   /* culled: drop the entry again */
        return;
    }
    D_800C42A8 += nmtx << 6;
    D_800C429A += nmtx;

    for (att = (u8 *) D_800C3EE0; att != NULL; att = next) {
        next = *(u8 **) (att + 0x54);
        if (att[0] != obj->unique_id || att[3] == 0) {
            continue;
        }
        e = reflect_queue_alloc();
        if (e == NULL) {
            return;
        }
        e->unk0[5] = col[0];
        e->unk0[6] = col[1];
        e->unk0[7] = col[2];
        e->unk0[0xB] = 1;
        e->unk0[8] = idx;
        e->unk0[9] = obj->unique_id;
        e->unk0[0xA] = att[6];
        if (attachment_get_matrices(att, (u8 *) obj, &model, out) == 0) {
            continue;
        }
        a8 = (s32) alpha;
        nmtx = 1;
        if (*(u8 **) (att + 0x48) != NULL) {
            nmtx = (*(u8 **) (att + 0x48))[0x3F4];
        }
        mtx = ((s32 *) (att + 0x4C))[g_dl_buf_index];
        if (mtx == 0) {
            ((s32 *) (att + 0x4C))[g_dl_buf_index] = (s32) allocate_memory(nmtx << 6, 1, 2, 0);
            mtx = ((s32 *) (att + 0x4C))[g_dl_buf_index];
        }
        *(s32 *) &e->unk0[0] = mtx;
        shadow = *(s32 *) (att + 0x34) != 0 || *(s32 *) (att + 0x48) != 0;
        reflect_build_joint_matrices(NULL, e, mode, model, mtx, nmtx, a, b, c, d, f, obj->x_position, obj->y_position, obj->z_position,
                      g, h, (f32) ((s32) ((u32) a8 * att[3]) >> 8), shadow, 1);
        e->unk0[4] = (s32) ((u32) e->unk0[4] * fade) >> 8;
    }
}

extern s32 D_80083350;
extern s32 D_800834D0;

/* was func_1503605C */
u8 *reflect_emit_entries_dl(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 *temp_s4;
    s32 *var_a0_2;
    s32 temp_t6;
    s32 var_v0;
    struct_eu_size0C *var_a2;
    struct_eu_size0C *var_s3;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *var_a0;

    var_a0 = arg0;
    if (D_800C4320 == 0) {

    } else {
        (*(s32 *)((u8 *)var_a0 + 4)) = 0x200;
        var_a0_2 = var_a0 + 8;
        (*(s32 *)((u8 *)var_a0 + 0)) = 0xD9FFFFFF;
        var_a2 = D_800C4328;
        if ((s32) D_800C4320 > 0) {
            do {
                if (var_a2->unk0[0xB] != 1) {
                    var_s3 = &D_800C4328[D_800C4320];
                } else if ((*(u8 *)((u8 *)arg1 + 0)) != var_a2->unk0[9]) {
                    var_s3 = &D_800C4328[D_800C4320];
                } else if ((*(u8 *)((u8 *)arg1 + 6)) != var_a2->unk0[0xA]) {
                    var_s3 = &D_800C4328[D_800C4320];
                } else {
                    temp_a0 = ((s32 *)((u8 *)var_a0_2 + 8));
                    temp_t6 = (s32) (var_a2->unk0[4] * (*(u8 *)((u8 *)arg1 + 3))) >> 8;
                    (*(s32 *)((u8 *)var_a0_2 + 0)) = 0xE7000000;
                    (*(s32 *)((u8 *)var_a0_2 + 4)) = 0;
                    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xDB06000C;
                    temp_a0_2 = temp_a0 + 8;
                    (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) (*(s32 *)((u8 *)var_a2 + 0));
                    (*(s32 *)((u8 *)temp_a0_2 + 4)) = (s32) ((arg2 << 0x18) | ((arg3 & 0xFF) << 0x10) | ((arg4 & 0xFF) << 8) | (temp_t6 & 0xFF));
                    temp_a0_3 = temp_a0_2 + 8;
                    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xFB000000;
                    var_v0 = 0;
                    if (temp_t6 < 0xFF) {
                        (*(s32 *)((u8 *)temp_a0_3 + 0)) = 0xDB060020;
                        (*(s32 **)((u8 *)temp_a0_3 + 4)) = &D_80083350;
                        var_a0_2 = temp_a0_3 + 8;
                    } else {
                        (*(s32 *)((u8 *)temp_a0_3 + 0)) = 0xDB060020;
                        (*(s32 **)((u8 *)temp_a0_3 + 4)) = &D_800834D0;
                        var_a0_2 = temp_a0_3 + 8;
                    }
                    if ((s32) (*(u8 *)((u8 *)arg1 + 0x14)) > 0) {
                        do {
                            temp_s4 = var_a0_2;
                            if (!((*(u8 *)((u8 *)arg1 + 0x13)) & (1 << var_v0))) {
                                (*(s32 *)((u8 *)temp_s4 + 0)) = 0xDE000000;
                                var_a0_2 = (s32 *)((u8 *)var_a0_2 + (8));
                                (*(s32 *)((u8 *)temp_s4 + 4)) = (s32) *(s32 *)((*(s32 *)((u8 *)arg1 + 0x24)) + (var_v0 * 4));
                            }
                            var_v0 += 1;
                        } while (var_v0 < (s32) (*(u8 *)((u8 *)arg1 + 0x14)));
                    }
                    var_s3 = &D_800C4328[D_800C4320];
                }
                var_a2 = (struct_eu_size0C *)((u8 *)var_a2 + (0xC));
            } while ((u32) var_a2 < (u32) var_s3);
        }
        (*(s32 *)((u8 *)var_a0_2 + 0)) = 0xD9FFFDFF;
        (*(s32 *)((u8 *)var_a0_2 + 4)) = 0;
        var_a0 = ((s32 *)((u8 *)var_a0_2 + 8));
    }
    return var_a0;
}
Gfx *obj_draw_model_dl(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 *color, s32 arg6, s32 arg7);

/* Draw the D_800C4320 entries of D_800C4328 that have no unkB flag through obj_draw_model_dl, after a
 * geometry-mode / othermode setup. */
/* was func_150362D8 */
Gfx *reflect_draw_queue(Gfx *gdl, s32 arg1) {
    struct_eu_size0C *e;
    s32 color[4];

    if (D_800C4320 == 0) {
        return gdl;
    }
    gdl->words.w0 = 0xD9FFFFFF;
    gdl->words.w1 = 0x200004;
    gdl++;
    gdl->words.w0 = 0xD9EEFFFF;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xE2001E01;
    gdl->words.w1 = 0;
    gdl++;
    for (e = D_800C4328; e < &D_800C4328[D_800C4320]; e++) {
        if (e->unk0[0xB] != 0) {
            continue;
        }
        color[0] = e->unk0[5];
        color[1] = e->unk0[6];
        color[2] = e->unk0[7];
        color[3] = 0xFF;
        gdl = obj_draw_model_dl(gdl, e->unk0[8], arg1, *(s32 *)e->unk0, e->unk0[4], color, 0, 1);
    }
    return gdl;
}
void reflect_queue_object(s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 obj_collision_cylinder(struct127 *, s16 *, s32 *, s32 *);

/* was func_15036438 */
void reflect_queue_objects_over_water(void) {
    struct {
        s32 u8E;
        s16 u92;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    s32 var_s1;
    struct127 *var_s0;
    u8 temp_v0;

    var_s0 = g_objects;
    var_s1 = 0;
    if (!(g_player_views->unk5F0 & 1)) {
        do {
            if ((var_s0->interaction_state != 0) && ((temp_v0 = var_s0->unk5, (temp_v0 == 0)) || (temp_v0 == 1))) {
                temp_f0 = var_s0->unk118;
                if ((temp_f0 != -10000.0f) && (temp_f0 < var_s0->y_position) && (var_s0->unk180 < temp_f0) && (var_s0->unk28 > 5.0f)) {
                    obj_collision_cylinder(var_s0, &sp.u92, &(*(s32 *)((u8 *)&sp + 0x2)), &sp.u8E);
                    temp_f0_2 = var_s0->unk118;
                    if ((f32) sp.u92 < (temp_f0_2 - var_s0->unk180)) {
                        reflect_queue_object(1, var_s1, var_s0->x_position, temp_f0_2, var_s0->z_position, 0.0f, 0.0f, 100.0f, 150.0f, 127.0f);
                    }
                }
            }
            var_s1 += 1;
            var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
        } while (var_s1 != 0x19);
    }
}