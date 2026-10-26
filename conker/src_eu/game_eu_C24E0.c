#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 (*D_800D3040)[4];
s32 skin_point_table_build(s32, u8 **);
/* was func_15094CD0 */
void skin_transform_points(s32 arg0, u8 *arg1) {
    u8 *sp50[16];
    u8 *v;
    u8 *p;
    s32 i;
    skin_point_table_build(arg0, sp50);
    for (i = 0; i < 16; i++) {
        p = sp50[i];
        if (p != NULL) {
            v = arg1 + i * 0xC;
            mtxf_transform_point(D_800D3040, (f32) *(s16 *)(p + 0), (f32) *(s16 *)(p + 2), (f32) *(s16 *)(p + 4), (f32 *)v, (f32 *)(v + 4), (f32 *)(v + 8));
        }
    }
}

/* was func_15094DAC */
s32 skin_point_table_build(s32 arg0, u8 **arg1) {
    s32 *temp_v0;
    s16 temp_a2;
    s16 temp_v1_2;
    s16 var_a3_2;
    s32 temp_t1;
    s32 temp_t6;
    s32 var_a3;
    u8 **var_a0;
    u8 **var_a0_2;
    u8 **var_a0_3;
    u8 **var_a0_4;
    u8 **var_a0_5;
    u8 *var_v0;
    u8 temp_v1;
    u8 *temp_v0_2;

    temp_v1 = (*(u8 *)((u8 *)arg0 + 1));
    var_v0 = (*(u8 **)((u8 *)arg0 + 4));
    var_a3 = 0;
    temp_a2 = temp_v1 & 0xF;
    temp_v1_2 = ((s32) temp_v1 >> 4) + 1;
    if (temp_a2 > 0) {
        temp_t1 = temp_a2 & 3;
        if (temp_t1 != 0) {
            var_a0 = &arg1[0];
            do {
                var_a3 += 1;
                *var_a0 = NULL;
                var_a0 = (u8 * *)((u8 *)var_a0 + (4));
            } while (temp_t1 != var_a3);
            if (var_a3 != temp_a2) {
                goto block_5;
            }
        } else {
block_5:
            var_a0_2 = &arg1[var_a3];
            do {
                var_a0_2 = (u8 * *)((u8 *)var_a0_2 + (0x10));
                (*(s32 *)((u8 *)var_a0_2 + -0xC)) = 0;
                (*(s32 *)((u8 *)var_a0_2 + -8)) = 0;
                (*(s32 *)((u8 *)var_a0_2 + -4)) = 0;
                (*(s32 *)((u8 *)var_a0_2 + -0x10)) = 0;
            } while (var_a0_2 != &arg1[temp_a2]);
        }
    }
    var_a3_2 = temp_a2;
    if (temp_a2 < temp_v1_2) {
        temp_t6 = (temp_v1_2 - temp_a2) & 3;
        if (temp_t6 != 0) {
            var_a0_3 = &arg1[temp_a2];
            do {
                *var_a0_3 = var_v0;
                var_a3_2 += 1;
                var_v0 += 0x10;
                var_a0_3 = (u8 * *)((u8 *)var_a0_3 + (4));
            } while ((temp_t6 + temp_a2) != var_a3_2);
            if (var_a3_2 != temp_v1_2) {
                goto block_12;
            }
        } else {
block_12:
            var_a0_4 = &arg1[var_a3_2];
            do {
                (*(u8 **)((u8 *)var_a0_4 + 0)) = var_v0;
                (*(u8 **)((u8 *)var_a0_4 + 4)) = (u8 *) (var_v0 + 0x10);
                temp_v0 = &(*(s32 *)((u8 *)(&var_v0[0x10]) + 0x10));
                (*(s32 **)((u8 *)var_a0_4 + 8)) = temp_v0;
                temp_v0_2 = ((s32 *)((u8 *)temp_v0 + 0x10));
                (*(u8 **)((u8 *)var_a0_4 + 0xC)) = temp_v0_2;
                var_a3_2 += 4;
                var_v0 = temp_v0_2 + 0x10;
                var_a0_4 = (u8 * *)((u8 *)var_a0_4 + (0x10));
            } while (var_a3_2 != temp_v1_2);
        }
    }
    if (var_a3_2 < 0x10) {
        var_a0_5 = &arg1[var_a3_2];
        do {
            var_a3_2 += 1;
            var_a0_5 = (u8 * *)((u8 *)var_a0_5 + (4));
            (*(s32 *)((u8 *)var_a0_5 + -4)) = 0;
        } while (var_a3_2 < 0x10);
    }
    return (s32) var_v0;
}
// uv_rotate: writes `count` texture coordinates (s16 u, v pairs of `uv`) rotated by `angle` degrees about the
// centre ((w / 2) * 32, (h / 2) * 32) to the vertices of `vtx` (stride 0x10, s, t at +8 / +0xA).
/* was func_15094EC8 */
void uv_rotate(u8 *vtx, s32 *uv, s32 count, f32 angle, s32 w, s32 h) {
    f32 rad = angle * 0.0174532924f; /* D_8009E270 */
    f32 s = sinf(rad);
    f32 c = cosf(rad);
    f32 cu;
    f32 cv;
    s16 *src;
    s32 i;

    for (i = 0; i < count; i++) {
        cu = (w / 2) * 32;
        cv = (h / 2) * 32;
        src = (s16 *) uv + i * 2;
        *(s16 *) (vtx + i * 0x10 + 8) = ((f32) src[0] - cu) * c - ((f32) src[1] - cv) * s + cu;
        *(s16 *) (vtx + i * 0x10 + 0xA) = ((f32) src[1] - cv) * c + ((f32) src[0] - cu) * s + cv;
    }
}

extern Mtx *D_800DC6D0[];
extern f32 D_800D30C8[][4][4];
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

/* was func_150952B0 */
void camera_build_view_proj(s32 arg0) {
    f32 a[4][4];
    f32 b[4][4];

    guMtxL2F(a, &D_800DC6D0[g_dl_buf_index][arg0]);
    guMtxL2F(b, &((Mtx *)((u8 *)&((struct_eu_BE628 *)g_player_cams)[arg0] + 0x100))[g_dl_buf_index]);
    mtxf_mul(a, b, D_800D30C8[arg0]);
}
