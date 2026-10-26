#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 D_800DE284[];


s32 water_wave_push(struct127 *, s32, s32);
extern s32 D_8008D3F0;
extern s32 D_8008D407;
extern s32 D_800DE290;

/* was func_15182D40 */
void water_waves_update(void) {
    struct {
        s32 uA4;
    } sp;
    u8 *sp90;
    f32 *temp_v0_3;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f20;
    f32 temp_f22;
    s32 *var_s2;
    s32 *var_s2_2;
    s32 *var_s3;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_s7;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    struct127 *temp_s0;
    struct127 *var_s0;
    u8 temp_v0_8;
    u8 temp_v1_2;
    u8 *temp_v0_2;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v0_7;
    u8 *temp_v1;
    u8 *temp_v1_3;

    var_s7 = 0;
    if ((s32) D_800DDE50 > 0) {
        var_s3 = &D_800DE290;
        sp90 = D_800DE284;
        do {
            var_s5 = 0;
            var_s6 = 0;
            temp_v1 = ((s32 *)((u8 *)&D_8008D3F0 + (*sp90 * 0x18)));
            temp_f20 = (*(f32 *)((u8 *)temp_v1 + 0));
            temp_f22 = (*(f32 *)((u8 *)temp_v1 + 4));
            var_s4 = 1;
            var_s2 = &sp.uA4;
loop_3:
            *var_s2 = 0;
            var_s0 = D_800CC2D0;
            var_s1 = 0;
loop_4:
            if (var_s0->interaction_state != 0) {
                temp_v0 = water_wave_push(var_s0, var_s4, var_s7);
                var_v1 = temp_v0;
                if (var_s0->unk84.uh == 0x4B) {
                    var_v1 = temp_v0 * 2;
                }
                *var_s2 += var_v1;
                if (var_v1 != 0) {
                    var_s5 = var_s1 + 1;
                }
            }
            var_s1 += 1;
            var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
            if (var_s1 != 4) {
                goto loop_4;
            }
            var_s4 += 1;
            var_s2 = (s32 *)((u8 *)var_s2 + (4));
            if (var_s4 != 0x27) {
                goto loop_3;
            }
            var_s1_2 = 0;
loop_12:
            var_s2_2 = &sp.uA4;
            var_v1_2 = 0xC;
loop_13:
            temp_v0_2 = *var_s3 + var_v1_2;
            temp_f0 = (*(f32 *)((u8 *)temp_v0_2 + 8));
            (*(f32 *)((u8 *)temp_v0_2 + 0)) = (f32) ((f32) ((s32) ((*(f32 *)((u8 *)temp_v0_2 + -4)) - temp_f0) + (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x14)) - temp_f0)) + temp_f20);
            temp_v0_3 = *var_s3 + var_v1_2;
            *temp_v0_3 += (f32) *var_s2_2;
            temp_v0_4 = *var_s3 + var_v1_2;
            (*(f32 *)((u8 *)temp_v0_4 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v0_4 + 4)) + (*(f32 *)((u8 *)temp_v0_4 + 0)));
            temp_v0_5 = *var_s3 + var_v1_2;
            (*(f32 *)((u8 *)temp_v0_5 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v0_5 + 4)) * temp_f22);
            temp_v0_6 = *var_s3 + var_v1_2;
            temp_f0_2 = (*(f32 *)((u8 *)temp_v0_6 + 4));
            var_v1_2 += 0xC;
            if (fabsf(temp_f0_2) < 1.0f) {
                (*(f32 *)((u8 *)temp_v0_6 + 4)) = 0.0f;
            }
            var_s2_2 = (s32 *)((u8 *)var_s2_2 + (4));
            if (var_v1_2 < 0x1D4) {
                goto loop_13;
            }
            var_v1_3 = 0xC;
loop_17:
            temp_v0_7 = *var_s3 + var_v1_3;
            (*(f32 *)((u8 *)temp_v0_7 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0_7 + 8)) + (*(f32 *)((u8 *)temp_v0_7 + 4)));
            if ((var_s5 != 0) && ((*(f32 *)((u8 *)((*var_s3 + var_v1_3)) + 4)) < -30.0f)) {
                var_s6 = 1;
            }
            var_v1_3 += 0xC;
            if (var_v1_3 != 0x1D4) {
                goto loop_17;
            }
            if (var_s5 == 0) {
                *(s32 *)((u8 *)&D_8008D407 + (*sp90 * 0x18)) = 0;
            }
            if ((var_s6 != 0) && (*(s32 *)((u8 *)&D_8008D407 + (*sp90 * 0x18)) == 0)) {
                temp_s0 = &D_800CC2D0[var_s5];
                temp_v1_2 = *sp90;
                *(s32 *)((u8 *)&D_8008D407 + (temp_v1_2 * 0x18)) = (random_int() & 0x3F) + 0x96;
                if ((temp_v1_2 == 2) || (temp_v1_2 == 3)) {
                    sound_play_at((random_int() & 8) + 0x507, 0x5DC0U, 0, 0U, 0, (s16) (s32) (*(f32 *)((u8 *)temp_s0 + -0x318)), (s16) (s32) (*(f32 *)((u8 *)temp_s0 + -0x314)), (s16) (s32) (*(f32 *)((u8 *)temp_s0 + -0x310)), 0x12C, 0x320);
                } else {
                    sound_play_at(0xF, 0x5DC0U, 0, 0U, 0, (s16) (s32) (*(f32 *)((u8 *)temp_s0 + -0x318)), (s16) (s32) (*(f32 *)((u8 *)temp_s0 + -0x314)), (s16) (s32) (*(f32 *)((u8 *)temp_s0 + -0x310)), 0x12C, 0x320);
                }
            } else if (var_s6 == 0) {
                temp_v1_3 = ((s32 *)((u8 *)&D_8008D3F0 + (*sp90 * 0x18)));
                temp_v0_8 = (*(u8 *)((u8 *)temp_v1_3 + 0x17));
                if ((temp_v0_8 != 0) && (temp_v0_8 != 0)) {
                    (*(u8 *)((u8 *)temp_v1_3 + 0x17)) = (u8) (temp_v0_8 - D_800BE9E4);
                }
            }
            var_s1_2 += 1;
            if (var_s1_2 != 3) {
                goto loop_12;
            }
            var_s7 += 1;
            sp90 += 1;
            var_s3 = (s32 *)((u8 *)var_s3 + (4));
        } while (var_s7 < (s32) D_800DDE50);
    }
}
// water_mesh_wave_update: rebuilds a water object's world vertices for this frame's buffer (+0x20[D_800BE9C0]) from
// its model vertices (+0x28, 16 bytes each): the vertex z picks a slot of the wave profile D_800DE290[+0x3C]
// (water_wave_slot_of_z, 0..39, linear blend of neighbouring samples), whose height / 16 is added to the vertex y; the
// vertex goes through a translation by -D_8008D400 (the water type's depth) and is offset by the object position
// +0x10. The vertex count comes from the type's model record (D_800DBEF4[D_8008D402].+0x16).
extern s16 D_8008D400[][12];
f32 water_wave_slot_of_z(s32 arg0, s32 arg1);


/* was func_151831CC */
void water_mesh_wave_update(u8 *obj) {
    f32 mtx[4][4];
    f32 ox, oy, oz;
    s32 water = *(s32 *)(obj + 0x3C);
    u8 *kind = &D_800DE284[water];
    s16 *out = *(s16 **)(obj + 0x20 + D_800BE9C0 * 4);
    s32 i;
    s32 off;
    f32 pos;
    s32 slot;
    s32 next;
    f32 frac;
    f32 a;
    f32 b;
    s16 *v;

    mtxf_rotate_xyz_deg(mtx, 0.0f, (f32)-D_8008D400[*kind][0], 0.0f);
    for (i = 0, off = 0; i < *(u16 *)((u8 *)&D_800DBEF4[D_8008D400[*kind][1]] + 0x16); i++, off += 0x10, out += 8) {
        pos = water_wave_slot_of_z(*(s16 *)(*(u8 **)(obj + 0x28) + off + 4), water);
        slot = (s32)pos;
        next = slot + 1;
        if (next >= 40) {
            next = 39;
        }
        frac = pos - (f32)slot;
        a = *(f32 *)(((u8 **)&D_800DE290)[water] + slot * 12 + 8) * (1.0f - frac);
        b = *(f32 *)(((u8 **)&D_800DE290)[water] + next * 12 + 8) * frac;
        v = (s16 *)(*(u8 **)(obj + 0x28) + off);
        mtxf_transform_point(mtx, (f32)v[0], (f32)(v[1] + ((s32)(b + a) >> 4)), (f32)v[2], &ox, &oy, &oz);
        out[0] = (s32)((f32)*(s16 *)(obj + 0x10) + ox);
        out[1] = (s32)((f32)*(s16 *)(obj + 0x12) + oy);
        out[2] = (s32)((f32)*(s16 *)(obj + 0x14) + oz);
    }
}

extern u8 D_800DE284[];
extern f32 D_8008D3F8[][6];

/* was func_151834C8 */
f32 water_wave_slot_of_z(s32 arg0, s32 arg1) {
    f32 x;

    x = D_8008D3F8[D_800DE284[arg1]][0] * (f32)(arg0 * 40);
    if (x < 0.0f) {
        x = 0.0f;
    } else if (x > 39.0f) {
        x = 39.0f;
    }
    return x;
}

/* P204 */
extern u8 D_800DE284[];
extern s32 D_8008D3F0;
extern s32 D_800DE290;
f32 water_wave_slot_of_z(s32, s32);

// water_wave_push: how strongly wave slot `slot` (0..39) of water `water` pushes player pl: 0 when the player
// rises faster than 3 (+0x28), is more than 300 above / below the slot's wave surface (model height +0x12 plus
// the profile sample D_800DE290[water][slot] +8 / 16), or lies outside the water's box (the player's offset from the
// model origin, moved down by the type's depth +0x10: z in [+0xC, 0], x in [0, +0xE]). Otherwise the type's push
// strength (s8 +0x16) when the player's own wave slot (water_wave_slot_of_z of z) is `slot`, 4 / 7 of it for a
// neighbouring slot, else 0. Water types: D_8008D3F0 (0x18 bytes) indexed by D_800DE284[water].
/* was func_1518354C */
s32 water_wave_push(struct127 *pl, s32 slot, s32 water) {
    u8 *kind = &D_800DE284[water];
    u8 *type;
    u8 *model;
    f32 surface;
    f32 mtx[4][4];
    f32 dx;
    f32 dz;
    f32 ox;
    f32 oy;
    f32 oz;
    s32 own;
    s32 push;

    if (pl->unk28 > 3.0f) {
        return 0;
    }
    type = (u8 *) &D_8008D3F0 + *kind * 0x18;
    model = (u8 *) D_800DBEF4 + *(s16 *) (type + 0x12) * 0xA0;
    surface = *(f32 *) (((u8 **) &D_800DE290)[water] + slot * 12 + 8) * 0.0625f + (f32) *(s16 *) (model + 0x12);
    if (pl->y_position < surface - 300.0f || surface + 300.0f < pl->y_position) {
        return 0;
    }
    dx = pl->x_position - (f32) *(s16 *) (model + 0x10);
    dz = pl->z_position - (f32) *(s16 *) (model + 0x14);
    mtxf_rotate_xyz_deg(mtx, 0.0f, (f32) *(s16 *) (type + 0x10), 0.0f);
    mtxf_transform_point(mtx, dx, 0.0f, dz, &ox, &oy, &oz);
    type = (u8 *) &D_8008D3F0 + *kind * 0x18;
    if (oz > 0.0f || oz < (f32) *(s16 *) (type + 0xC) || ox < 0.0f || ox > (f32) *(s16 *) (type + 0xE)) {
        return 0;
    }
    own = (s32) water_wave_slot_of_z((s32) oz, water);
    push = *(s8 *) ((u8 *) &D_8008D3F0 + *kind * 0x18 + 0x16);
    if (slot == own) {
        return push;
    }
    if (slot == own + 1 || slot + 1 == own) {
        return push * 4 / 7;
    }
    return 0;
}
