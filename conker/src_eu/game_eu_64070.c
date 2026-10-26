#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void mtxf_transform_point(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ);
extern s16 D_800C43E4[][3];
extern f32 D_80098130;

// vertex_anchor_follow: places the first vertex (s16 x, y, z at +0) of object `idx`'s vertex block D_800C3FC0[idx].
// Types 0x3E / 0x41, type 0x138 with its +0x2D0 record's +8 >= 36 and types 0x3D / 0xD9 with it > 21 put it at
// (-7, -17, -7) through matrix mfA (mtxf_transform_point) and store that in D_800C43E4[idx]. Otherwise the midpoint of the
// block's vertices 2 and 3 (+0x20 / +0x30) goes through matrix mfB and D_800C43E4[idx] moves towards it by a rate:
// 1.0 for types 0x138 / 0x139 and for 0x3D / 0xD9 with +8 > 7, else D_80098130 (0.7); the vertex takes that result.
/* was func_15036860 */
void player_strip_update_vertices(s32 idx, f32 mfA[4][4], f32 mfB[4][4]) {
    u8 *obj = (u8 *) D_800CC2D0 + idx * 0x32C;
    s16 *vtx = ((s16 **) &D_800C3FC0)[idx];
    u16 type = *(u16 *) (obj + 0x84);
    f32 h = *(f32 *) (*(u8 **) (obj + 0x2D0) + 8);
    s16 *cur;
    f32 x, y, z;
    f32 tx, ty, tz;
    f32 rate;
    f32 cx, cy, cz;

    if (type == 0x3E || type == 0x41 || (type == 0x138 && h >= 36.0f) ||
        ((type == 0x3D || type == 0xD9) && h > 21.0f)) {
        mtxf_transform_point(mfA, -7.0f, -17.0f, -7.0f, &x, &y, &z);
        cur = D_800C43E4[idx];
        cur[0] = (s32) x;
        cur[1] = (s32) y;
        cur[2] = (s32) z;
    } else {
        if (((type == 0x3D || type == 0xD9) && h > 7.0f) || type == 0x138 || type == 0x139) {
            rate = 1.0f;
        } else {
            rate = D_80098130;
        }
        x = (vtx[0x18] + vtx[0x10]) * 0.5f;
        y = (vtx[0x19] + vtx[0x11]) * 0.5f;
        z = (vtx[0x1A] + vtx[0x12]) * 0.5f;
        mtxf_transform_point(mfB, x, y, z, &tx, &ty, &tz);
        cur = D_800C43E4[idx];
        cx = cur[0];
        cy = cur[1];
        cz = cur[2];
        cur[0] = (s32) (cx + (tx - cx) * rate);
        cur[1] = (s32) (cy + (ty - cy) * rate);
        cur[2] = (s32) (cz + (tz - cz) * rate);
        x = cur[0];
        y = cur[1];
        z = cur[2];
    }
    vtx[0] = (s32) x;
    vtx[1] = (s32) y;
    vtx[2] = (s32) z;
}

u8 * attachment_find_by_slot(u8 *arg0, s32 arg1, s32 arg2);
void player_strip_update_vertices(s32 idx, f32 mfA[4][4], f32 mfB[4][4]);
u8 * light_write_light_cmds(u8 *, s32, u8, u8, u8 *);
extern s32 D_800846E0;
extern s32 D_8009076C;

/* was func_15036BB4 */
u8 *player_draw_slot8_strip(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *sp78;
    struct222 **sp3C;
    u8 *sp38;
    s32 temp_t2;
    s32 temp_v0_4;
    struct127 *temp_s0;
    struct222 **temp_t0;
    struct255 *temp_v0_5;
    u8 *temp_a2;
    u8 temp_v0_2;
    u8 *temp_v0;
    u8 *temp_v0_3;
    u8 *temp_v0_6;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *var_s1;

    temp_s0 = &D_800CC2D0[arg1];
    temp_v0_2 = temp_s0->unk31C->unk75;
    if ((temp_v0_2 != 2) && (temp_v0_2 != 0x13)) {
        return arg0;
    }
    temp_v0_3 = attachment_find_by_slot((u8 *) temp_s0, 8, 0);   /* the callee never reads a3 */
    sp78 = temp_v0_3;
    if (temp_v0_3 == NULL) {
        return arg0;
    }
    if (arg1 > 0) {
        return arg0;
    }
    temp_v1 = (*(u8 **)((u8 *)((temp_v0_3 + (D_800BE9C0 * 4))) + 0x28));
    temp_t0 = &(&D_800C3FC0)[arg1];
    temp_v0_4 = 1 * 0x10;
    (*(u8 *)((u8 *)(*temp_t0) + 0xC)) = (u8) (*(u8 *)((u8 *)temp_v1 + 0x30C));
    temp_v1_2 = temp_v1 + 0x300;
    (*(u8 *)((u8 *)(*temp_t0) + 0xD)) = (u8) (*(u8 *)((u8 *)temp_v1 + 0x30D));
    (*(u8 *)((u8 *)(*temp_t0) + 0xE)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xE));
    (*(u8 *)((u8 *)((u8 *) *temp_t0 + temp_v0_4) + 0xC)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xC));
    (*(u8 *)((u8 *)((u8 *) *temp_t0 + temp_v0_4) + 0xD)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xD));
    (*(u8 *)((u8 *)((u8 *) *temp_t0 + temp_v0_4) + 0xE)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xE));
    (*(u8 *)((u8 *)((u8 *) *temp_t0 + temp_v0_4) + 0x1C)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xC));
    (*(u8 *)((u8 *)((u8 *) *temp_t0 + temp_v0_4) + 0x1D)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xD));
    (*(u8 *)((u8 *)((u8 *) *temp_t0 + temp_v0_4) + 0x1E)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xE));
    (*(u8 *)((u8 *)((u8 *) *temp_t0 + temp_v0_4) + 0x2C)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xC));
    (*(u8 *)((u8 *)((u8 *) *temp_t0 + temp_v0_4) + 0x2D)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xD));
    (*(u8 *)((u8 *)((u8 *) *temp_t0 + temp_v0_4) + 0x2E)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xE));
    (*(u8 *)((u8 *)((u8 *) *temp_t0 + temp_v0_4) + 0x3C)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xC));
    (*(u8 *)((u8 *)((u8 *) *temp_t0 + temp_v0_4) + 0x3D)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xD));
    (*(u8 *)((u8 *)((u8 *) *temp_t0 + temp_v0_4) + 0x3E)) = (u8) (*(u8 *)((u8 *)temp_v1_2 + 0xE));
    temp_v0_5 = temp_s0->unk1D4;
    if (temp_v0_5 == NULL) {
        return arg0;
    }
    temp_a2 = &temp_v0_5->pad0[0x100];
    sp38 = temp_a2;
    sp3C = temp_t0;
    player_strip_update_vertices(arg1, (f32 (*)[4]) &temp_v0_5->unk240, (f32 (*)[4]) temp_a2);
    (*(s32 *)((u8 *)arg0 + 0)) = 0xDE000000;
    (*(s32 **)((u8 *)arg0 + 4)) = &D_800846E0;
    temp_v0_6 = light_write_light_cmds(arg0 + 8, (*(s32 *)((u8 *) temp_s0 + arg2 * 4 + 0x304)), temp_s0->unk301, temp_s0->unk302, temp_s0->unk314 + (D_800BE9C0 * 8));
    temp_t2 = temp_s0->unk66 & 0xC;
    if (temp_t2 == 0xC) {
        (*(s32 *)((u8 *)temp_v0_6 + 0)) = 0xD9FDFFFF;
        var_s1 = temp_v0_6 + 8;
        (*(s32 *)((u8 *)temp_v0_6 + 4)) = 0;
    } else if ((temp_t2 != 8) && (var_s1 = temp_v0_6 + 8, (((*(u8 *)((u8 *)sp78 + 4)) & 1) == 0))) {
        (*(s32 *)((u8 *)temp_v0_6 + 0)) = 0xD9FDFFFF;
        (*(s32 *)((u8 *)temp_v0_6 + 4)) = 0;
    } else {
        var_s1 = temp_v0_6 + 8;
        if (D_800DCD7C != 0) {
            (*(s32 *)((u8 *)temp_v0_6 + 4)) = 0x20000;
            (*(s32 *)((u8 *)temp_v0_6 + 0)) = 0xD9FFFFFF;
            var_s1 = temp_v0_6 + 8;
        } else {
            (*(s32 *)((u8 *)temp_v0_6 + 0)) = 0xD9FDFFFF;
            (*(s32 *)((u8 *)temp_v0_6 + 4)) = 0;
        }
    }
    sp3C = temp_t0;
    temp_v0 = sprite_load_texture(var_s1, &D_8009076C, 0, 0, 0, 0, 0, 2, 3);
    (*(u8 **)((u8 *)temp_v0 + 4)) = D_80089810;
    (*(s32 *)((u8 *)temp_v0 + 0)) = 0xDA380003;
    (*(s32 *)((u8 *)temp_v0 + 8)) = 0x01001002;
    (*(struct222 **)((u8 *)temp_v0 + 0xC)) = (struct222 *) *temp_t0;
    (*(s32 *)((u8 *)temp_v0 + 0x10)) = 0xDA380003;
    (*(u8 **)((u8 *)temp_v0 + 0x14)) = sp38;
    (*(s32 *)((u8 *)temp_v0 + 0x18)) = 0x0100400A;
    (*(struct222 **)((u8 *)temp_v0 + 0x1C)) = (struct222 *) ((u8 *) *temp_t0 + 0x10);
    (*(s32 *)((u8 *)temp_v0 + 0x20)) = 0x05000204;
    (*(s32 *)((u8 *)temp_v0 + 0x24)) = 0;
    (*(s32 *)((u8 *)temp_v0 + 0x28)) = 0x05000608;
    (*(s32 *)((u8 *)temp_v0 + 0x2C)) = 0;
    return temp_v0 + 0x30;
}