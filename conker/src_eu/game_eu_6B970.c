#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
s32 breakable_slot_has_piece_flag(s32 arg0, s32 arg1);
void breakable_release(s32 arg0);
extern u8 D_80098CC4[];


void breakable_request_flags(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 *D_800847FC[];

/*
 * P71 (EU 0x1503E160): sets the flags of entry `entry` of flag set D_800847FC[set] on object obj's record
 * (breakable_request_flags with its slot index); entry -1 sets all bits.
 */
/* was func_1503DE70 */
void breakable_request_flag_entry(struct127 *obj, s32 set, s32 entry) {
    s32 *e;

    if (entry != -1) {
        e = &D_800847FC[set][entry * 2];
        breakable_request_flags(obj - g_objects, set, e[0], e[1]);
    } else {
        breakable_request_flags(obj - g_objects, set, -1, -1);
    }
}

/* was func_1503E1FC */
void breakable_request_flags(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct106 *temp_v0;
    temp_v0 = &D_800C6660[arg0];
    temp_v0->unk4 |= arg2;
    temp_v0->unk8 |= arg3;
    temp_v0->pad[2] = arg1;
    temp_v0->unkF = 2;
}

extern s8 *D_800847E4[];
extern u8 D_80098CC4[];
extern void (*D_800847C0[])(s32, s32);  /* per kind: piece init (pc, slot) */
extern void (*D_800847CC[])(s32);       /* per kind: start (slot) */
extern void (*D_800847D8[])(s32);       /* per kind: update (slot) */
s32 allocate_memory(s32, s32, s32, s32);
s32 breakable_slot_has_piece_flag(s32 arg0, s32 arg1);
void breakable_init_piece(s32 i, s32 piece, s32 jointOffset, u8 *pc, s32 detached);
void breakable_move_free_pieces(s32 i);
void breakable_write_matrices(s32 i);

/*
 * P74: per-frame breakable update of slot i (record D_800C6660[i], kind = byte 0xE, state = byte 0xF).
 * State 2 (requested): object flag 0x80 at +0x74, and once the object has joint matrices (unk1D4) go on as state 3.
 * State 3 (break): allocate the D_80098CC4[kind] pieces (0x68 bytes, inactive) if needed (return if that fails),
 * initialise every piece that is not excluded (-2), whose flag bit is set on the slot (breakable_slot_has_piece_flag) and that is not
 * yet active, from its joint (breakable_init_piece, kind callback D_800847C0) and mark it active; then D_800847CC[kind] and
 * state 1. State 1 (running): D_800847D8[kind], then while the state stays non-zero move the pieces (breakable_move_free_pieces)
 * and rebuild their matrices (breakable_write_matrices).
 */
/* was func_1503E238 */
void breakable_update_slot(s32 i) {
    struct106 *rec = &D_800C6660[i];
    struct127 *obj;
    s32 state = rec->unkF;
    s32 n;
    s32 k;
    s8 *att;
    u8 *pc;
    u8 *buf;

    if (state == 2) {
        obj = &g_objects[i];
        *((u8 *) obj + 0x74) |= 0x80;
        if (obj->unk1D4 == NULL) {
            return;
        }
        state = 3;
    }
    if (state == 3) {
        n = D_80098CC4[(u8) rec->pad[2]];
        if (rec->unk0 == 0) {
            buf = (u8 *) allocate_memory(n * 0x68, 1, 0, 0);
            if (buf == NULL) {
                return;
            }
            rec->unk0 = (s32) buf;
            for (k = 0; k < n; k++) {
                buf[k * 0x68 + 0x64] = 0;
            }
        }
        att = D_800847E4[(u8) rec->pad[2]];
        for (k = 0; k < n; k++) {
            if (att[k] == -2) {
                continue;
            }
            pc = (u8 *) rec->unk0 + k * 0x68;
            if (breakable_slot_has_piece_flag(k, i) == 0 || pc[0x64] != 0) {
                continue;
            }
            breakable_init_piece(i, k, 0, pc, 0);
            D_800847C0[(u8) rec->pad[2]]((s32) pc, i);
            pc[0x64] = 1;
        }
        D_800847CC[(u8) rec->pad[2]](i);
        rec->unkF = 1;
        state = 1;
    }
    if (state == 1) {
        D_800847D8[(u8) rec->pad[2]](i);
        if (rec->unkF != 0) {
            breakable_move_free_pieces(i);
            breakable_write_matrices(i);
        }
    }
}

extern s32 D_800C6A84;
extern s32 D_800C6A88;
/* was func_1503E4E4 */
s32 breakable_slot_has_piece_flag(s32 arg0, s32 arg1)
{
  if (arg0 < 0x20) {
    if ((*(s32 *)((u8 *)&D_800C6A84 + arg1 * 0x10)) & (1 << arg0)) {
      return 1;
    }
  } else {
    if ((*(s32 *)((u8 *)&D_800C6A88 + arg1 * 0x10)) & (1 << arg0)) {
      return 1;
    }
  }
  return 0;
}

void heap_free(s32);
extern s32 D_800847F0;

/* was func_1503E550 */
void breakable_release(s32 arg0) {
    struct127 *sp3C;
    s32 temp_v1_2;
    s32 var_s0;
    struct106 *temp_s7;
    struct127 *temp_v0_2;
    struct127 *temp_v0_3;
    u8 *temp_v0;
    u8 *var_s1;
    u8 temp_s6;
    u8 temp_v1;

    temp_s7 = &D_800C6660[arg0];
    if (temp_s7->unkF != 0) {
        temp_v1 = (u8) temp_s7->pad[2];
        temp_v0 = *(s32 *)((u8 *)&D_800847F0 + (temp_v1 * 4));
        if (temp_v0 != NULL) {
            temp_s6 = D_80098CC4[temp_v1];
            var_s0 = 0;
            var_s1 = temp_v0;
            if ((s32) temp_s6 > 0) {
                do {
                    if ((*var_s1 != 0xFF) && (breakable_slot_has_piece_flag(var_s0, arg0) != 0)) {
                        temp_v0_2 = &g_objects[arg0];
                        temp_v0_2->unk94 |= 1 << *var_s1;
                    }
                    var_s0 += 1;
                    var_s1 += 1;
                } while (var_s0 != temp_s6);
            }
        }
        temp_v1_2 = temp_s7->unk0;
        temp_s7->unkF = 0;
        temp_v0_3 = &g_objects[arg0];
        if (temp_v1_2 != 0) {
            sp3C = temp_v0_3;
            heap_free(temp_v1_2);
        }
        temp_s7->unk0 = 0;
        temp_v0_3->unk74 &= 0xFF7F;
    }
}
extern s8 *D_800847E4[];
void math_mtx_affine_inverse(f32 arg0[4][4], f32 arg1[4][4]);
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void mtxf_decompose(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);

/*
 * P74: initialises breakable piece pc (0x68 bytes; piece number `piece`) of slot i from object i's joint matrix
 * unk1D4[piece + jointOffset]: made relative to its parent piece's matrix (inverse, math_mtx_affine_inverse) unless `detached`
 * is set or the piece has no parent (D_800847E4[kind][piece] == -1); decomposed (mtxf_decompose) into
 * position +0x00, angles +0x0C, scale +0x18, copied to the rest pose +0x24..+0x44; +0x48 = unit vector from the
 * object's position (30 units up) to the piece (a zero distance counts as 1).
 */
/* was func_1503E6B4 */
void breakable_init_piece(s32 i, s32 piece, s32 jointOffset, u8 *pc, s32 detached) {
    struct127 *obj = &g_objects[i];
    f32 mat[4][4];
    f32 inv[4][4];
    s32 parent;
    s32 k;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;

    bcopy((u8 *) obj->unk1D4 + (piece + jointOffset) * 0x40, mat, sizeof(mat));
    if (detached != 0) {
        parent = -1;
    } else {
        parent = D_800847E4[(u8) D_800C6660[i].pad[2]][piece];
    }
    if (parent != -1) {
        math_mtx_affine_inverse((f32 (*)[4]) ((u8 *) obj->unk1D4 + parent * 0x40), inv);
        mat[0][3] = 0.0f;
        mat[1][3] = 0.0f;
        mat[2][3] = 0.0f;
        mat[3][3] = 1.0f;
        mtxf_mul(mat, inv, mat);
    }
    mtxf_decompose((f32 *) mat, (f32 *) (pc + 0x00), (f32 *) (pc + 0x04), (f32 *) (pc + 0x08), (f32 *) (pc + 0x0C),
                  (f32 *) (pc + 0x10), (f32 *) (pc + 0x14), (f32 *) (pc + 0x18), (f32 *) (pc + 0x1C), (f32 *) (pc + 0x20));
    for (k = 0; k < 9; k++) {
        ((f32 *) (pc + 0x24))[k] = ((f32 *) pc)[k];
    }
    dx = *(f32 *) (pc + 0x24) - obj->x_position;
    dy = *(f32 *) (pc + 0x28) - obj->y_position - 30.0f;
    dz = *(f32 *) (pc + 0x2C) - obj->z_position;
    len = sqrtf(dx * dx + dy * dy + dz * dz);
    if (len == 0.0f) {
        len = 1.0f;
    }
    len = 1.0f / len;
    *(f32 *) (pc + 0x48) = dx * len;
    *(f32 *) (pc + 0x4C) = dy * len;
    *(f32 *) (pc + 0x50) = dz * len;
}

f32 vec3f_magnitude(f32 *arg0);
void vec3f_cross(u8 *, u8 *, u8 *);
f32 vec3f_dot(f32 *a, f32 *b);
f32 math_asin_scaled(f32 arg0);
f32 fast_cosf(f32);
f32 math_atan2f(f32 arg0, f32 arg1);

/*
 * P74: decomposes the f32 4x4 matrix m into translation (*x, *y, *z = row 3), Euler angles in degrees
 * (*rx, *ry, *rz) and scale (*sx, *sy, *sz = lengths of rows 0..2, a zero length counted as 1e-4). The rows are
 * normalised; when row 0 points against row 1 x row 2 (a mirrored matrix) the scale and the rows are negated.
 * ry = asin(-m[0][2]) (math_asin_scaled); with cos(ry) != 0: rx = atan2(m[1][2], m[2][2]), rz = atan2(m[0][1], m[0][0]);
 * otherwise (gimbal lock) rx = atan2(m[1][0], m[1][1]), rz = 0 (math_atan2f / fast_cosf).
 */
/* was func_1503E5F8 */
void mtxf_decompose(f32 *m, f32 *x, f32 *y, f32 *z, f32 *rx, f32 *ry, f32 *rz, f32 *sx, f32 *sy, f32 *sz) {
    f32 mat[4][4];
    f32 cross[4];
    f32 len;
    f32 ax;
    f32 ay;
    f32 az;
    s32 r;
    s32 c;

    bcopy(m, mat, sizeof(mat));
    *x = mat[3][0];
    *y = mat[3][1];
    *z = mat[3][2];
    for (r = 0; r < 3; r++) {
        len = vec3f_magnitude(mat[r]);
        if (len == 0.0f) {
            len = 0.0001f;
        }
        if (r == 0) {
            *sx = len;
        } else if (r == 1) {
            *sy = len;
        } else {
            *sz = len;
        }
        vec3_scale((struct17 *) mat[r], 1.0f / len, (struct17 *) mat[r]);
    }
    vec3f_cross((u8 *) mat[1], (u8 *) mat[2], (u8 *) cross);
    if (vec3f_dot(mat[0], cross) < 0.0f) {
        *sx = -*sx;
        *sy = -*sy;
        *sz = -*sz;
        for (r = 0; r < 3; r++) {
            for (c = 0; c < 3; c++) {
                mat[r][c] = -mat[r][c];
            }
        }
    }
    ay = math_asin_scaled(-mat[0][2]);
    if (fast_cosf(ay) != 0.0f) {
        ax = math_atan2f(mat[1][2], mat[2][2]);
        az = math_atan2f(mat[0][1], mat[0][0]);
    } else {
        ax = math_atan2f(mat[1][0], mat[1][1]);
        az = 0.0f;
    }
    *rx = ax * 57.295776f;
    *ry = ay * 57.295776f;
    *rz = az * 57.295776f;
}

extern s8 *D_800847E4[];
extern u8 D_80098CC4[];
void mtxf_translate(u8 *, s32, s32, s32);
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

/*
 * P74: matrices of slot i's breakable pieces into object i's joint matrices (unk1D4, one f32 4x4 per piece).
 * Pieces marked -2 in D_800847E4[kind] and inactive pieces (+0x64 == 0) are skipped. A free piece (-1) gets
 * rotation (+0x30..+0x38) then scale (+0x3C..+0x44) and translation (+0x24..+0x2C) by mtxf_scale_set_trans. A piece attached
 * to piece `parent` gets translate(+0x24..) * parent's matrix, then its rotation, times that, then scale
 * (mtxf_scale) times the result. The translate / scale helpers take the floats as bit patterns.
 */
/* was func_1503EB1C */
void breakable_write_matrices(s32 i) {
    struct127 *obj = &g_objects[i];
    struct106 *rec;
    s8 *att;
    s32 n;
    s32 k;
    s32 parent;
    u8 *pc;
    f32 (*m)[4];
    f32 tmp[4][4];

    if (obj->unk1D4 == NULL) {
        return;
    }
    rec = &D_800C6660[i];
    att = D_800847E4[(u8) rec->pad[2]];
    n = D_80098CC4[(u8) rec->pad[2]];
    for (k = 0; k < n; k++) {
        if (att[k] == -2) {
            continue;
        }
        pc = (u8 *) rec->unk0 + k * 0x68;
        if (pc[0x64] == 0) {
            continue;
        }
        parent = D_800847E4[(u8) rec->pad[2]][k];
        m = (f32 (*)[4]) ((u8 *) obj->unk1D4 + k * 0x40);
        if (parent != -1) {
            mtxf_translate((u8 *) tmp, *(s32 *) (pc + 0x24), *(s32 *) (pc + 0x28), *(s32 *) (pc + 0x2C));
            mtxf_mul(tmp, (f32 (*)[4]) ((u8 *) obj->unk1D4 + parent * 0x40), tmp);
            pc = (u8 *) rec->unk0 + k * 0x68;
            mtxf_rotate_xyz_deg(m, *(f32 *) (pc + 0x30), *(f32 *) (pc + 0x34), *(f32 *) (pc + 0x38));
            mtxf_mul(m, tmp, m);
            pc = (u8 *) rec->unk0 + k * 0x68;
            mtxf_scale(tmp, *(s32 *) (pc + 0x3C), *(s32 *) (pc + 0x40), *(s32 *) (pc + 0x44));
            mtxf_mul(tmp, m, m);
        } else {
            mtxf_rotate_xyz_deg(m, *(f32 *) (pc + 0x30), *(f32 *) (pc + 0x34), *(f32 *) (pc + 0x38));
            pc = (u8 *) rec->unk0 + k * 0x68;
            mtxf_scale_set_trans(m, *(f32 *) (pc + 0x3C), *(f32 *) (pc + 0x40), *(f32 *) (pc + 0x44),
                          *(f32 *) (pc + 0x24), *(f32 *) (pc + 0x28), *(f32 *) (pc + 0x2C));
        }
    }
}

extern s8 *D_800847E4[];
extern u8 D_80098CC4[];

/*
 * P74: advances the free pieces of slot i's breakable (D_800C6660[i].unk0: D_80098CC4[kind] pieces of 0x68 bytes,
 * kind = record byte 0xE) by one frame of g_frame_ticks ticks: a piece that is active (+0x64) and not attached
 * (D_800847E4[kind][piece] == -1) moves its 6 floats +0x24..+0x38 by the rates +0x48..+0x5C; the rate +0x4C
 * itself changes by +0x60 (gravity) after it is used.
 */
/* was func_1503ED44 */
void breakable_move_free_pieces(s32 i) {
    struct106 *rec = &D_800C6660[i];
    f32 dt = g_frame_ticks;
    s32 n = D_80098CC4[(u8) rec->pad[2]];
    s32 k;
    u8 *pc;

    for (k = 0; k < n; k++) {
        pc = (u8 *) rec->unk0 + k * 0x68;
        if (pc[0x64] == 0 || D_800847E4[(u8) rec->pad[2]][k] != -1) {
            continue;
        }
        *(f32 *) (pc + 0x24) += *(f32 *) (pc + 0x48) * dt;
        *(f32 *) (pc + 0x28) += *(f32 *) (pc + 0x4C) * dt;
        *(f32 *) (pc + 0x2C) += *(f32 *) (pc + 0x50) * dt;
        *(f32 *) (pc + 0x30) += *(f32 *) (pc + 0x54) * dt;
        *(f32 *) (pc + 0x34) += *(f32 *) (pc + 0x58) * dt;
        *(f32 *) (pc + 0x38) += *(f32 *) (pc + 0x5C) * dt;
        *(f32 *) (pc + 0x4C) += *(f32 *) (pc + 0x60) * dt;
    }
}

extern f32 D_80098CD4;
/* was func_1503EE68 */
void breakable_scatter_pieces(s32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    struct {
        f32 u50;
        f32 u54;
        f32 u58;
        s32 u5C;
    } sp;
    f32 *var_s1;
    f32 temp_f0;
    f32 temp_f18;
    f32 temp_f8;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;

    if (arg3 != 0) {
        var_s3 = 0x80;
        var_s4 = 0x7F;
    } else {
        var_s3 = 0xFF;
        var_s4 = 0;
    }
    temp_f0 = arg1 * 0.02745098f;
    var_s0 = arg0;
    var_s1 = &sp.u50;
    sp.u50 = temp_f0;
    sp.u58 = temp_f0;
    sp.u54 = arg2 * 0.02745098f;
    do {
        temp_f8 = *var_s1;
        temp_f18 = (*(f32 *)((u8 *)var_s0 + 0x48));
        var_s1 = (f32 *)((u8 *)var_s1 + (4));
        var_s0 += 4;
        (*(f32 *)((u8 *)var_s0 + 0x44)) = (f32) (temp_f18 * (((f32) (s32) ((random_int() & var_s3) + var_s4) * temp_f8) + 2.0f));
    } while ((u32) var_s1 < (u32) &sp.u5C);
    var_s2 = 0;
    var_s0_2 = arg0;
    do {
        var_s2 += 1;
        var_s0_2 += 4;
        (*(f32 *)((u8 *)var_s0_2 + 0x50)) = (f32) ((f32) (s32) ((random_int() & 0xFF) - 0x80) * 0.03125f);
    } while (var_s2 != 3);
    *(f32 *)((u8 *)arg0 + 0x60) = D_80098CD4;
}
extern s8 *D_800847E4[];
extern u8 D_80098CC4[];
void collision_select_area(s32);
s32 collision_level_nearest_height(s32, s32, s32, s32 *);

/*
 * P74: ground collision of slot i's free breakable pieces (see breakable_move_free_pieces): after collision_select_area(0), every active,
 * unattached piece with a non-zero gravity (+0x60) that has fallen below the floor height under it
 * (collision_level_nearest_height + 5) is put on the floor; when it hit fast (y rate +0x4C < -4) it bounces (x / z rates * 0.8,
 * y rate * -0.5, spins +0x54 / +0x5C reversed, +0x58 * 0.4), otherwise it comes to rest (all rates and the gravity 0).
 */
/* was func_1503EF90 */
void breakable_pieces_ground_collide(s32 i) {
    struct106 *rec;
    s32 n;
    s32 k;
    u8 *pc;
    f32 floor;

    collision_select_area(0);
    rec = &D_800C6660[i];
    n = D_80098CC4[(u8) rec->pad[2]];
    for (k = 0; k < n; k++) {
        pc = (u8 *) rec->unk0 + k * 0x68;
        if (pc[0x64] == 0 || D_800847E4[(u8) rec->pad[2]][k] != -1) {
            continue;
        }
        if (*(f32 *) (pc + 0x60) == 0.0f) {
            continue;
        }
        floor = collision_level_nearest_height((s32) *(f32 *) (pc + 0x24), (s32) *(f32 *) (pc + 0x28), (s32) *(f32 *) (pc + 0x2C), NULL) + 5;
        if (!(*(f32 *) (pc + 0x28) < floor)) {
            continue;
        }
        *(f32 *) (pc + 0x28) = floor;
        if (*(f32 *) (pc + 0x4C) < -4.0f) {
            *(f32 *) (pc + 0x48) *= 0.8f;
            *(f32 *) (pc + 0x4C) *= -0.5f;
            *(f32 *) (pc + 0x50) *= 0.8f;
            *(f32 *) (pc + 0x54) *= -1.0f;
            *(f32 *) (pc + 0x58) *= 0.4f;
            *(f32 *) (pc + 0x5C) *= -1.0f;
        } else {
            *(f32 *) (pc + 0x5C) = 0.0f;
            *(f32 *) (pc + 0x58) = 0.0f;
            *(f32 *) (pc + 0x54) = 0.0f;
            *(f32 *) (pc + 0x60) = 0.0f;
            *(f32 *) (pc + 0x50) = 0.0f;
            *(f32 *) (pc + 0x4C) = 0.0f;
            *(f32 *) (pc + 0x48) = 0.0f;
        }
    }
}

/* was func_1503F1A8 */
void breakable_cb_nop(void) {
}

void breakable_pieces_ground_collide(s32);
/* was func_1503F1B0 */
void breakable_cb_fall_then_remove(s32 arg0) {
    s32 temp_v0;
    struct106 *temp_v1;

    breakable_pieces_ground_collide(arg0);
    temp_v1 = &D_800C6660[arg0];
    temp_v0 = *(s16 *)((u8 *)temp_v1 + 0xC);
    temp_v0 = temp_v0 - g_frame_ticks; // fakematch: split load/subtract (permuter) gives the ref register order
    (*(s16 *)((u8 *)temp_v1 + 0xC)) = temp_v0;
    if (temp_v0 <= 0) {
        obj_remove(&g_objects[arg0], 1);
    }
}

extern s32 *D_800847FC[];

/*
 * P71: entry (flagsA, flagsB) of flag set D_800847FC[set] is satisfied by object slot i when every non-zero word
 * shares a bit with the slot's flags D_800C6A84 / D_800C6A88 (the +4 / +8 words of its 16-byte record, as in
 * breakable_slot_has_piece_flag). Returns 1 / 0.
 */
/* was func_1503F23C */
s32 breakable_flag_entry_matches(s32 set, s32 entry, s32 i) {
    s32 *e = &D_800847FC[set][entry * 2];

    if (e[0] != 0 && !(e[0] & *(s32 *) ((u8 *) &D_800C6A84 + i * 0x10))) {
        return 0;
    }
    if (e[1] != 0 && !(e[1] & *(s32 *) ((u8 *) &D_800C6A88 + i * 0x10))) {
        return 0;
    }
    return 1;
}

extern u8 D_80098CC4[];

/* was func_1503F2B4 */
void breakable_cb_init_random_spin(s32 arg0) {
    struct106 *p;
    s32 n;
    s32 i;

    p = &D_800C6660[arg0];
    *(s16 *)&p->pad[0] = 0x78;
    n = D_80098CC4[(u8)p->pad[2]];
    for (i = 0; i < n; i++) {
        *(f32 *)(p->unk0 + i * 0x68 + 0x4C) = (s32)(random_int() % 20U) - 5;
    }
}

/* was func_1503F368 */
void breakable_cb_scatter_a(s32 arg0, s32 arg1) {
    breakable_scatter_pieces(arg0, 2.0f, 2.0f, 0);
}

/* was func_1503F39C */
void breakable_cb_scatter_b(s32 arg0, s32 arg1) {
    breakable_scatter_pieces(arg0, 1.0f, 2.0f, 1);
}

/* was func_1503F3C8 */
void breakable_cb_scatter_c(s32 arg0, s32 arg1) {
    breakable_scatter_pieces(arg0, 2.06f, 3.0f, 1);
}

extern s32 D_800CC784;

/* was func_1503F3F8 */
void breakable_cb_init_timer140(s32 arg0) {
    struct106 *temp_v0;

    temp_v0 = &D_800C6660[arg0];
    (*(s16 *)((u8 *)temp_v0 + 0xC)) = 0x8C;
    *(s32 *)((u8 *)&D_800CC784 + (arg0 * 0x32C)) = 6;
    (*(f32 *)((u8 *)(temp_v0->unk0) + 0x1EC)) = 10.0f;
}

s32 breakable_flag_entry_matches(s32, s32, s32);

/*
 * P74: slot i's record timer (+0xC) = 300; then for the flag-set 2 entries satisfied by the slot
 * (breakable_flag_entry_matches): entry 0 sets object flag 0x40 and clears 0x200, entry 1 sets 0x80 and clears 0x100,
 * entry 2 clears 0x400 (g_objects[i].unk94).
 */
/* was func_1503F45C */
void breakable_cb_init_flags(s32 i) {
    *(s16 *) ((u8 *) &D_800C6660[i] + 0xC) = 300;
    if (breakable_flag_entry_matches(2, 0, i) != 0) {
        g_objects[i].unk94 |= 0x40;
        g_objects[i].unk94 &= ~0x200;
    }
    if (breakable_flag_entry_matches(2, 1, i) != 0) {
        g_objects[i].unk94 |= 0x80;
        g_objects[i].unk94 &= ~0x100;
    }
    if (breakable_flag_entry_matches(2, 2, i) != 0) {
        g_objects[i].unk94 &= ~0x400;
    }
}

void breakable_pieces_ground_collide(s32);
s32 breakable_flag_entry_matches(s32, s32, s32);

/* was func_1503F5A0 */
void breakable_cb_settle(s32 arg0) {
    struct106 *temp_v0;
    struct127 *temp_v0_2;
    struct127 *temp_v0_3;
    struct127 *temp_v0_4;

    breakable_pieces_ground_collide(arg0);
    temp_v0 = &D_800C6660[arg0];
    (*(s16 *)((u8 *)temp_v0 + 0xC)) = (s16) ((*(s16 *)((u8 *)temp_v0 + 0xC)) - g_frame_ticks);
    if ((*(s16 *)((u8 *)temp_v0 + 0xC)) <= 0) {
        breakable_release(arg0);
        if (breakable_flag_entry_matches(2, 0, arg0) != 0) {
            temp_v0_2 = &g_objects[arg0];
            temp_v0_2->unk94 |= 8;
        }
        if (breakable_flag_entry_matches(2, 1, arg0) != 0) {
            temp_v0_3 = &g_objects[arg0];
            temp_v0_3->unk94 |= 4;
        }
        if (breakable_flag_entry_matches(2, 2, arg0) != 0) {
            temp_v0_4 = &g_objects[arg0];
            temp_v0_4->unk94 |= 2;
        }
    }
}

void mtxf_decompose(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);

/* was func_1503F6F4 */
void mtx_decompose(Mtx *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, f32 *arg9) {
    f32 sp30[16];
    if (D_800C42B0 != 0) {
        guMtxL2F((f32 (*)[4]) sp30, arg0);
    } else {
        memcpy(sp30, arg0, 0x40);
    }
    mtxf_decompose(sp30, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}
