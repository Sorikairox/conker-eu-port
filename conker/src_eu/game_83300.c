#include <ultra64.h>

#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void obj_follow_path(struct127 *obj, s32 path);
void tri_compute_plane(s32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2);
s32 cutscene_obj_takes_part(struct127 *);
extern u8 D_800C3A78;
s32 anim_start_entry(struct127 *, s32, u8 *, s32, s32, s32, s32, f32, f32, f32, f32, s32);
void obj_update_ground_tilt(struct127 *);
void obj_apply_gravity(struct127 *);
void obj_sfx_play_alt(s32 arg0, struct127 *arg1);
void obj_contact_pass(struct127 *, s32);
s32 attack_hit_test(struct127 *self, s32 skip);
void obj_remove(struct127 *obj, s32 mode);
void obj_release_models(struct127 *);
void obj_remove_children(struct127 *, s32);
void obj_forget_target(struct127 *);
void obj_sync_collision_link(struct127 *, s32, s32);
void breakable_release(s32 arg0);
void heap_free(s32 arg0);
s32 char_fx_clear_all(u8 *arg0);
void node_broadcast_obj_all(u8 *arg0, u8 arg1);
s32 attachment_remove_all_of_owner(u8 *arg0);
void afterimage_remove_object(s32 arg0);
extern u8 *g_setup_entry_flags; /* was D_800D252C */
void objects_animate_textures(void);
void gfx_tile_scroll_coords(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void obj_type_tex_scroll_apply(s32, s32, s32, s32, s32, s32, s32);
void obj_vtx_scroll_uv(u8 *, s32, s32, s32, s32, s32, s32, s32);
s32 random_int(void);
f32 math_cos_u8(u8);
void obj_vertex_colours_blend(struct127 *, f32 *, s32);
void obj7b_set_anim_ids(u8 *arg0);
extern s32 g_tex_anim_5b_frames[]; /* was D_800997EC */
extern s32 g_tex_anim_phase_steps; /* was D_80086490 */
extern s32 D_800C4440;
extern s32 g_obj_anim_shared; /* was D_800CC298 */
extern s32 g_obj_scratch_rec; /* was D_800D121C */
extern s32 g_level_id; /* was D_800BE9F0 */


void obj_water_buoyancy(struct127 *arg0, f32, f32);
void obj_reset(struct127 *arg0);
u8   obj_turn_towards(struct127 *arg0, u8 arg1, u16 arg2);
void move_xz_towards(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4);
f32  obj_approach_speed(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4);

u8  obj_apply_hit(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u8 arg6);
s32 obj_receive_hit(struct127 *arg0, struct127 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

extern u8 *D_800D1CD0;

/* was func_15055E50 */
void obj_push_out_of_blockers(struct127 *arg0, s32 arg1) {
    f32 sp40;
    f32 sp3C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f2;
    f32 var_f30;
    s16 temp_a1;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_v0;
    s32 var_v1;
    u16 temp_a1_2;
    u16 temp_t1;
    u16 temp_t2;
    u8 *temp_t0;
    u8 *var_a2;
    u8 *var_t0;

    var_v0 = 1;
    var_v1 = 0;
    if (arg0->id == 0x3A) {
        if (arg0->x_position > 1200.0f) {
            arg0->x_position = 1200.0f;
        }
        if (arg0->x_position < -1200.0f) {
            arg0->x_position = -1200.0f;
        }
        if (arg0->z_position > 1200.0f) {
            arg0->z_position = 1200.0f;
        }
        if (arg0->z_position < -1200.0f) {
            arg0->z_position = -1200.0f;
        }
    }
    if ((arg1 != 0) && (D_800D1CD0 != NULL) && ((s32) arg0->unk13D < 0x64)) {
        var_f30 = 1e9f;
        var_a3 = 0;
        if (arg1 != (*(u16 *)((u8 *)D_800D1CD0 + 6))) {
            var_t0 = D_800D1CD0;
loop_14:
            if ((*(s32 *)((u8 *)var_t0 + 0)) != 0) {
                temp_t2 = (*(u16 *)((u8 *)var_t0 + 0xE));
                var_a3 += 1;
                var_t0 += 8;
                if (arg1 == temp_t2) {
                    goto block_16;
                }
                goto loop_14;
            }
        } else {
block_16:
            temp_t0 = D_800D1CD0 + (var_a3 * 8);
            temp_t1 = (*(u16 *)((u8 *)temp_t0 + 4));
            var_a3_2 = 0;
            var_a2 = (*(u8 **)((u8 *)temp_t0 + 0));
            if ((s32) temp_t1 > 0) {
                do {
                    var_a3_2 += 1;
                    if ((var_v0 != 0) || ((*(u16 *)((u8 *)var_a2 + 8)) & 0x8000)) {
                        temp_a1 = (*(s16 *)((u8 *)var_a2 + 4));
                        temp_f0 = arg0->y_position;
                        if (((f32) temp_a1 <= temp_f0) && (temp_f0 <= (f32) ((*(s16 *)((u8 *)var_a2 + 6)) + temp_a1))) {
                            temp_a1_2 = (*(u16 *)((u8 *)var_a2 + 8));
                            temp_f24 = (f32) (*(s16 *)((u8 *)var_a2 + 0));
                            temp_f20 = (f32) (*(s16 *)((u8 *)var_a2 + 2));
                            temp_f2 = (f32) (temp_a1_2 & 0x7FFF);
                            temp_f16 = arg0->x_position - temp_f24;
                            temp_f18 = arg0->z_position - temp_f20;
                            if (temp_a1_2 & 0x8000) {
                                temp_f12 = (temp_f16 * temp_f16) + (temp_f18 * temp_f18) + 0.1f;
                                if (temp_f12 < (temp_f2 * temp_f2)) {
                                    temp_f14 = 1.0f / sqrtf(temp_f12);
                                    arg0->x_position = temp_f24 + (temp_f16 * temp_f14 * temp_f2);
                                    arg0->unkF4 |= 0x2000;
                                    arg0->z_position = (f32) (*(s16 *)((u8 *)var_a2 + 2)) + (temp_f18 * temp_f14 * temp_f2);
                                }
                            } else {
                                var_v1 = 1;
                                temp_f12_2 = (temp_f16 * temp_f16) + (temp_f18 * temp_f18) + 0.1f;
                                if (temp_f12_2 < (temp_f2 * temp_f2)) {
                                    var_v0 = 0;
                                } else {
                                    temp_f22 = sqrtf(temp_f12_2);
                                    if ((temp_f22 - temp_f2) < var_f30) {
                                        temp_f14_2 = 1.0f / temp_f22;
                                        var_f30 = temp_f22 - temp_f2;
                                        sp40 = temp_f24 + (temp_f16 * temp_f14_2 * temp_f2);
                                        sp3C = temp_f20 + (temp_f18 * temp_f14_2 * temp_f2);
                                    }
                                }
                            }
                        }
                    }
                    var_a2 += 0xA;
                } while (var_a3_2 != temp_t1);
            }
            if ((var_v0 != 0) && (var_v1 != 0)) {
                arg0->x_position = sp40;
                arg0->unkF4 |= 0x2000;
                arg0->z_position = sp3C;
            }
        }
    }
}
/* was func_15056150 */
void obj_leash_to_spawn(struct127 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f2;
    s16 *temp_v1;

    if (arg0->unk2E8 != 0) {
        temp_v1 = g_path_points[arg0->unk13F];
        temp_f2 = temp_v1[4];
        temp_f12 = temp_v1[6];
        temp_f14 = temp_v1[5];
        temp_f16 = arg0->unk2E8;
        temp_f16 = temp_f16 * 8.0f;
        temp_f18 = arg0->x_position - temp_f2;
        temp_f20 = arg0->z_position - temp_f12;
        temp_f22 = arg0->y_position - temp_f14;
        temp_f0 = sqrtf((temp_f18 * temp_f18) + (temp_f20 * temp_f20) + (temp_f22 * temp_f22) + 0.1f);
        temp_f18 *= 1.0f / temp_f0;
        temp_f20 *= 1.0f / temp_f0;
        temp_f22 *= 1.0f / temp_f0;
        if (temp_f16 < temp_f0) {
            arg0->x_position = temp_f18 * temp_f16 + temp_f2;
            arg0->z_position = temp_f20 * temp_f16 + temp_f12;
            arg0->y_position = temp_f22 * temp_f16 + temp_f14;
        }
    }
}

/* was func_15056258 */
void obj_follow_water_level(struct127 *arg0) {
    f32 temp_f2;
    f32 temp_f4;
    f32 phi_f12;

    temp_f4 = arg0->unk11C;
    temp_f2 = arg0->unk118 - arg0->unk11C;
    arg0->unk11C = arg0->unk118;
    phi_f12 = 2.0f * (arg0->y_position - ((arg0->unk118 - 60.0f) - 170.0f));
    if (!(phi_f12 < 0.0f)) {
        if (!(fabsf(temp_f2) > 30.0f)) {
            if (phi_f12 > 300.0f) {
                phi_f12 = 300.0f;
            }
            arg0->y_position += (phi_f12 * temp_f2 * 0.002997f);
        }
    }
}

// object_carried_update: P213: per-frame update of object `obj` while it is held by the object in slot unk13D - 100
/* (port P209: void, one argument). Sets 30 frames of immunity, copies the carrier's unk180, keeps the height in
 * unk1CC, gravity 4.5, no fall speed; the hold timer unk21C counts up by D_800BE9A0 to 30. Per type (0x57, 0x8C
 * after 10 frames - else nothing more; 0xA8 / 0xA9; 0x5E with offset 16) the carrier's animation unk84 picks the
 * column (0..2) of the reaction row and the carrier's grab is synced (obj_slot_sync_anim_frame); other types use row 13
 * column 0. The reaction row comes from obj_find_reaction_row (0x24 for 0x57 with carrier anim 0x114, else 13); a
 * swimming player carrier (state 1, in_water) uses column 1 when the row has one. The object is moved towards
 * the point `offset` (unk10F, 204 for type 0x13) in front of the carrier along its facing unk7A + unk13E << 8,
 * by unk21C / 50 per frame (1 with g_level_first_frame) until 20 frames, then 0.8; a carrier with a model (unk1D4) lifts
 * it to the model's height + unk10C / 100 (ramped over 14 frames) after 7 frames. Carrier state 0x15: row 0x39,
 * same facing, 10 below the carrier, no forward speed, turn speed unkC4 eases to the carrier's; column 1 when
 * unk28 > 100 after 21 frames, else no animation offset. Starts the row's animation (obj_start_anim) and marks
 * the holder in unk65 (slot + 1, unk101 bit 2) for the typed cases, else clears unk65. */
void obj_slot_sync_anim_frame(s32, s32);
/* was func_150562FC */
void obj_carried_update(struct127 *obj) {
    u8 slot;
    s32 typed;
    f32 anim_offset;
    struct127 *holder;
    u16 anim;
    u32 col;
    u32 row;
    u8 *rows;
    u8 *cell;
    f32 weight;
    f32 offset;
    f32 dz;
    f32 dy;
    f32 lift;
    u16 t;
    u8 id;

    slot = obj->unk13D - 100;
    typed = 0;
    anim_offset = 5.0f;
    obj->immune = 30;
    holder = &g_objects[slot];
    obj->unk180 = holder->unk180;
    obj->unk1CC = obj->y_position;
    obj->gravity = 4.5f;
    obj->y_velocity = 0.0f;
    if (obj->unk21C < 30) {
        obj->unk21C += D_800BE9A0;
    }
    col = 0;
    row = 13;
    id = obj->id;
    if (id == 0x57) {
        obj->unk5C = 9;
        if (obj->unk21C < 10) {
            return;
        }
        anim = holder->unk84.uh;
        typed = 1;
        if (anim == 0x114) {
            row = 0x24;
        }
        if (anim == 0x116) {
            col = 1;
        }
        if (anim == 0x117) {
            col = 2;
        }
        obj_slot_sync_anim_frame(slot, g_cur_obj_index);
    } else if (id == 0x8C) {
        obj->unk5C = 4;
        if (obj->unk21C < 10) {
            return;
        }
        anim = holder->unk84.uh;
        typed = 1;
        if (anim == 0x1A6) {
            col = 1;
        }
        if (anim == 0x1A7) {
            col = 2;
        }
        obj_slot_sync_anim_frame(slot, g_cur_obj_index);
    } else if (id == 0xA8 || id == 0xA9) {
        obj->unk5C = 9;
        anim = holder->unk84.uh;
        typed = 1;
        if (anim == 0x1B0) {
            col = 1;
        }
        if (anim == 0x1B1) {
            col = 2;
        }
    } else if (id == 0x5E) {
        obj->unk5C = 9;
        anim_offset = 16.0f;
        anim = holder->unk84.uh;
        typed = 1;
        if (anim == 0x286) {
            col = 2;
        }
        if (anim == 0x27E) {
            col = 1;
        }
    }
    row = obj_find_reaction_row(row, obj);
    rows = *(u8 **)((u8 *)D_800D1588[obj->id] - 8);
    if (holder->interaction_state == 1 && holder->in_water != 0) {
        obj->unk5C = 4;
        typed = 1;
        if (*(u16 *)(rows + row * 0x18 + 0xE) != 0) {
            col = 1;
        }
    }
    t = obj->unk21C;
    if (t < 20) {
        weight = (f32)t / 50.0f;
        if (g_level_first_frame != 0) {
            weight = 1.0f;
        }
    } else {
        weight = 0.8f;
    }
    offset = obj->unk10F;
    obj_turn_towards(obj, 0x10, holder->unk7A + (obj->unk13E << 8));
    if (holder->unk1D4 != NULL) {
        lift = obj->unk10C / 100;
        if (holder->interaction_state != 0x15) {
            t = obj->unk21C;
            if (t >= 7) {
                obj->y_position = *(s16 *)((u8 *)holder->unk1D4 + 0x240 + 0x1A);
                if (t < 14) {
                    lift = (t / 14.0f) * lift;
                }
                obj->y_position = obj->y_position + lift;
            }
            if (obj->id == 0xE) {
                obj->unkC4 = 0.0f;
            } else if (obj->id == 0x13) {
                offset = 204.0f;
                obj->unkC4 = 0.0f;
            }
        }
    }
    if (holder->interaction_state == 0x15) {
        row = obj_find_reaction_row(0x39, obj);
        obj->unk7A = holder->unk7A;
        obj->y_position = holder->y_position - 10.0f;
        if (obj->unk28 > 100.0f && obj->unk21C >= 21) {
            col = 1;
        } else {
            anim_offset = 0.0f;
        }
        offset = 0.0f;
        obj->xz_velocity = 0.0f;
        obj->unkC4 = obj->unkC4 + (holder->unkC4 - obj->unkC4) * 0.12f;
    }
    vec_from_yaw_pitch(holder->unk7A, offset, 0.0f, &offset, &dz, &dy);
    obj->x_position = obj->x_position + ((holder->x_position + offset) - obj->x_position) * weight;
    obj->z_position = obj->z_position + ((holder->z_position + dz) - obj->z_position) * weight;
    cell = rows + row * 0x18 + col * 4;
    obj_start_anim(obj, *(u16 *)(cell + 0xA), cell[0xC] / 100.0f, anim_offset, 0.0f, 0.0f, 0);
    if (typed) {
        obj->unk65 = slot + 1;
        obj->unk101 |= 4;
    } else {
        obj->unk65 = 0;
    }
}
// NON-MATCHING: 10% of the way there...
// void obj_carried_update(struct127 *arg0) {
//     f32 sp70;
//     f32 sp6C;
//     f32 sp68;
//     u8 sp63;
//     s32 sp54;
//     f32 sp4C;
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f14;
//
//     s32 *temp_a3;
//     // s32 temp_t1;
//     s32 temp_t1_2;
//     s32 temp_t2;
//     s32 temp_t9;
//     s32 temp_v0_6;
//     struct255 *temp_v1_2;
//     u16 temp_v0_2;
//     u16 temp_v0_3;
//     u16 temp_v0_4;
//     u16 temp_v0_5;
//     u16 temp_v0_7;
//     u16 temp_v0_8;
//     u16 temp_v1;
//     u8 temp_v0;
//     struct127 *temp_t0;
//     struct127 *temp_t0_2;
//     u8 *temp_v0_11;
//     s32 phi_a2;
//     s32 phi_t1;
//     s32 phi_t1_2;
//     s32 phi_t1_3;
//     s32 phi_a2_2;
//     f32 phi_f18;
//     s32 phi_t1_4;
//     f32 phi_f0;
//     s32 phi_t1_5;
//     s32 phi_t2;
//
//     sp63 = arg0->unk13D - 0x64;
//     sp54 = 0;
//     sp4C = 5.0f;
//     arg0->immune = (u8)0x1E;
//     temp_t0 = &g_objects[sp63];
//     arg0->unk180 = (f32) temp_t0->unk180;
//     arg0->unk1CC = (f32) arg0->y_position;
//     arg0->gravity = 4.5f;
//     arg0->y_velocity = 0.0f;
//     if ((s32) arg0->unk21C < 0x1E) {
//         arg0->unk21C += D_800BE9A0;
//     }
//     temp_v0 = arg0->id;
//     if (temp_v0 == 0x57) {
//         arg0->unk5C = 9;
//         if ((s32) arg0->unk21C >= 0xA) {
//             temp_v0_2 = temp_t0->unk84.uh;
//             sp54 = 1;
//             phi_a2 = 0xD;
//             if (temp_v0_2 == 0x114) {
//                 phi_a2 = 0x24;
//             }
//             phi_t1 = 0;
//             if (temp_v0_2 == 0x116) {
//                 phi_t1 = 1;
//             }
//             if (temp_v0_2 == 0x117) {
//                 phi_t1 = 2;
//             }
//             func_150649A0(sp63, g_cur_obj_index, phi_a2);
//             phi_t1_3 = phi_t1;
//             phi_a2_2 = phi_a2;
//         } else if (temp_v0 == 0x8C) {
//             arg0->unk5C = 4;
//             if ((s32) arg0->unk21C >= 0xA) {
//                 temp_v0_2 = temp_t0->unk84.uh;
//                 sp54 = 1;
//                 phi_t1_2 = 0;
//                 if (temp_v0_2 == 0x1A6) {
//                     phi_t1_2 = 1;
//                 }
//                 if (temp_v0_2 == 0x1A7) {
//                     phi_t1_2 = 2;
//                 }
//                 func_150649A0(sp63, g_cur_obj_index, 0xD);
//                 phi_t1_3 = phi_t1_2;
//                 phi_a2_2 = 0xD;
//             }
//         } else {
//             if ((temp_v0 == 0xA8) || (temp_v0 == 0xA9)) {
//                 arg0->unk5C = 9;
//                 temp_v0_2 = temp_t0->unk84.uh;
//                 sp54 = 1;
//                 phi_t1_3 = 0;
//                 if (temp_v0_2 == 0x1B0) {
//                     phi_t1_3 = 1;
//                 }
//                 phi_a2_2 = 0xD;
//                 if (temp_v0_2 == 0x1B1) {
//                     phi_t1_3 = 2;
//                     phi_a2_2 = 0xD;
//                 }
//             } else {
//                 phi_t1_3 = 0;
//                 phi_a2_2 = 0xD;
//                 if (temp_v0 == 0x5E) {
//                     arg0->unk5C = 9;
//                     temp_v0_2 = temp_t0->unk84.uh;
//                     sp54 = 1;
//                     sp4C = 16.0f;
//                     phi_t1_3 = 0;
//                     if (temp_v0_2 == 0x286) {
//                         phi_t1_3 = 2;
//                     }
//                     phi_a2_2 = 0xD;
//                     if (temp_v0_2 == 0x27E) {
//                         phi_t1_3 = 1;
//                         phi_a2_2 = 0xD;
//                     }
//                 }
//             }
//         }
//         temp_v0_6 = obj_find_reaction_row(phi_a2_2, arg0); //, phi_a2_2);
//         temp_t0_2 = &g_objects[sp63];
//         phi_t1_4 = phi_t1_3;
//         temp_t2 = temp_v0_6;
//         temp_a3 = D_800D1588[arg0->id] - 8;
//         if (temp_t0_2->interaction_state == 1) {
//             if (temp_t0_2->in_water != 0) {
//                 temp_t9 = temp_v0_6 * 3;
//                 arg0->unk5C = 4;
//                 sp54 = 1;
//                 if (((temp_a3 + (temp_t9 * 8)) + 14) != 0) { // unkE
//                     phi_t1_4 = 1;
//                 }
//             }
//         }
//         if ((s32) arg0->unk21C < 0x14) {
//             phi_f18 = (f32) (u32) arg0->unk21C / 50.0f;
//             if (g_level_first_frame != 0) {
//                 phi_f18 = 1.0f;
//             }
//         } else {
//             phi_f18 = D_80099448;
//         }
//
//         sp70 = (f32) arg0->unk10F;
//
//         obj_turn_towards(arg0, 0x10, (temp_t0_2->unk7A + (arg0->unk13E << 8)) & 0xFFFF); //, temp_a3);
//         temp_t1_2 = phi_t1_4;
//         temp_v1_2 = temp_t0_2->unk1D4;
//         if (temp_v1_2 != 0) {
//             temp_f0 = (f32) ((s32) arg0->unk10C / 0x64);
//             if (temp_t0_2->interaction_state != 0x15) {
//                 temp_v0_8 = arg0->unk21C;
//                 if ((s32) temp_v0_8 >= 7) {
//                     arg0->y_position = (f32) temp_v1_2->unk240->unk1A;
//                     if ((s32) temp_v0_8 < 0xE) {
//                         // temp_f6 = (f32) temp_v0_8;
//                         temp_f0 = (temp_v0_8 / 14.0f) * temp_f0;
//                     }
//                     arg0->y_position = (f32) (arg0->y_position + temp_f0);
//                 }
//                 if (arg0->id == 0xE) {
//                     arg0->unkC4 = 0.0f;
//                 } else if (arg0->id == 0x13) {
//                     sp70 = 204.0f;
//                     arg0->unkC4 = 0.0f;
//                 }
//             }
//         }
//         phi_t1_5 = phi_t1_4;
//         phi_t2 = temp_t2;
//         if (temp_t0_2->interaction_state == 0x15) {
//             phi_t2 = obj_find_reaction_row(0x39, arg0);
//             arg0->unk7A = (u16) temp_t0_2->unk7A;
//             arg0->y_position = (f32) (temp_t0_2->y_position - 10.0f);
//             if ((arg0->unk28 > 100.0f) && ((s32) arg0->unk21C >= 0x15)) {
//                 phi_t1_5 = 1;
//             } else {
//                 sp4C = 0.0f;
//                 phi_t1_5 = phi_t1_4;
//             }
//             sp70 = 0.0f;
//             temp_f0 = arg0->unkC4;
//             arg0->xz_velocity = 0.0f;
//             arg0->unkC4 = (f32) (temp_f0 + ((temp_t0_2->unkC4 - temp_f0) * D_8009944C));
//         }
//         vec_from_yaw_pitch(g_objects[sp63].unk7A,  sp70, 0, &sp70, &sp6C, &sp68);
//         temp_t0_2 = &g_objects[sp63];
//         temp_f12 = temp_t0_2->x_position + sp70;
//
//         temp_f14 = temp_t0_2->z_position + sp6C;
//         arg0->x_position = (f32) (arg0->x_position + ((temp_f12 - arg0->x_position) * phi_f18));
//         arg0->z_position = (f32) (arg0->z_position + ((temp_f14 - arg0->z_position) * phi_f18));
//         temp_v0_11 = temp_a3 + (phi_t2 * 0x18) + (phi_t1_5 * 4);
//         obj_start_anim(arg0, temp_v0_11[0xA],  temp_v0_11[0xC] / 100.0f, sp4C, 0.0f, 0.0f, 0);
//         if (sp54 != 0) {
//             arg0->unk65 = (s8) (sp63 + 1);
//             arg0->unk101 = (u8) (arg0->unk101 | 4);
//         } else {
//             arg0->unk65 = (u8)0;
//         }
//     }
// }

/* was func_1505693C */
s32 obj_in_spawn_radius(struct127 *arg0, s32 arg1) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;

    u16 *temp_v0 = (u16*)g_path_points[(u16)arg0->unk13F];

    if (temp_v0[3] == 0) {
        return 1;
    }

    temp_f0 = temp_v0[3] * 8;
    temp_f0 = temp_f0 * temp_f0;
    temp_f2 = (s16)temp_v0[0] - g_objects[arg1].x_position;
    temp_f12 = (s16)temp_v0[2] - g_objects[arg1].z_position;

    if ((temp_f2 * temp_f2) + (temp_f12 * temp_f12) < temp_f0) {
        return 1;
    }
    return 0;
}

/* Hit reaction of an object: row g_hit_reaction_anims[row] gives an animation per strength (a1 above row[7]: heavy,
 * above row[2]: medium, else light) and side (front / back from the angles +0x76 / +0x78); 0xFF = none. Starts
 * it: health +0x218 -5, stun timer +0x21C, state 13, speed +0x44 = 0, move flags +0xF4 = 4, faces +0x76. */
/* was func_15056A00 */
void obj_start_hit_reaction(struct127 *obj, s32 arg1, u8 row) {
    u8 *o = (u8 *)obj;
    u8 strength = arg1;
    u8 *anims = g_hit_reaction_anims[row];
    u8 idx;
    u16 angle;

    idx = 0;
    if (anims[7] < strength) {
        idx = 5;
    } else if (anims[2] < strength) {
        idx = 2;
    }
    angle = *(u16 *)(o + 0x76);
    if ((*(u16 *)(o + 0x78) - angle) & 0x8000) {
        idx += 3;
    } else {
        idx += 4;
    }
    if (anims[idx] != 0xFF) {
        *(s32 *)(o + 0x218) -= 5;
        *(s16 *)(o + 0x21C) = 20000;
        o[0x223] = 13;
        *(f32 *)(o + 0x44) = 0.0f;
        *(s32 *)(o + 0xF4) = (*(s32 *)(o + 0xF4) & ~0xE) | 4;
        *(u16 *)(o + 0x78) = angle;
        *(u16 *)(o + 0x7A) = angle;
        o[0x138] = 0;
        *(s16 *)(o + 0x244) = anims[idx];
    }
}
void mtxf_look_at_f(f32 mf[4][4], f32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 obj_turn_to_target_yaw(struct127 *arg0, u16 arg1);
struct216 *aiscript_find_by_kind(s32, s32);
extern f32 g_obj0_x; /* was D_800CC704 */
extern f32 g_obj0_z; /* was D_800CC70C */
extern s32 g_obj_update_counter; /* was D_800D1968 */

/* was func_15056B08 */
void obj_walk_update(struct127 *arg0) {
    f32 sp98[4][4];
    u8 *temp_v0_13;
    u8 var_v1_4;
    u8 var_v1_2;
    u8 var_v1;
    u8 var_t0_2;
    u8 var_t0;
    u8 temp_v1_7;
    u8 temp_v1_6;
    u8 temp_v1_5;
    u8 temp_v1_2;
    u8 temp_v0_9;
    u8 temp_v0_8;
    u8 temp_v0_5;
    u8 temp_v0_4;
    u8 temp_v0_2;
    u8 temp_v0_17;
    u8 temp_v0_16;
    u8 temp_v0_15;
    u8 temp_v0_11;
    u8 temp_v0;
    u8 temp_t9;
    u8 temp_t8_2;
    u8 temp_t8;
    u8 temp_t6;
    u8 temp_t5;
    u8 temp_t4;
    u8 temp_t1_2;
    u8 temp_t1;
    u8 temp_a0_2;
    u8 temp_a0;
    u16 var_v0_2;
    u16 var_a2_3;
    u16 temp_v1_3;
    u16 temp_v0_10;
    u16 temp_t3;
    u16 temp_a1;
    struct216 *var_v0;
    struct127 *var_a2;
    struct127 *var_a0;
    struct127 *temp_v1_4;
    struct127 *temp_v0_18;
    struct127 *temp_v0_14;
    struct127 *temp_v0_12;
    struct126 *temp_v0_7;
    struct126 *temp_v0_6;
    s8 temp_v1_8;
    s32 var_v1_3;
    s32 var_a3;
    s32 var_a2_2;
    s32 var_a1;
    s32 temp_v1;
    s32 temp_v0_3;
    s32 temp_v0_19;
    s32 temp_t7;
    s32 temp_hi;
    f32 var_f8_3;
    f32 var_f8_2;
    f32 var_f8;
    f32 var_f6_3;
    f32 var_f6_2;
    f32 var_f6;
    f32 var_f4;
    f32 var_f2_3;
    f32 var_f2_2;
    f32 var_f2;
    f32 var_f16_2;
    f32 var_f16;
    f32 var_f14;
    f32 var_f12;
    f32 var_f10_2;
    f32 var_f10;
    f32 var_f0_3;
    f32 var_f0_2;
    f32 var_f0;
    f32 temp_f8_2;
    f32 temp_f8;
    f32 temp_f4_5;
    f32 temp_f4_4;
    f32 temp_f4_3;
    f32 temp_f4_2;
    f32 temp_f4;
    f32 temp_f2_5;
    f32 temp_f2_4;
    f32 temp_f2_3;
    f32 temp_f2_2;
    f32 temp_f2;
    f32 temp_f18;
    f32 temp_f16;
    f32 temp_f14_3;
    f32 temp_f14_2;
    f32 temp_f14;
    f32 temp_f12_6;
    f32 temp_f12_5;
    f32 temp_f12_4;
    f32 temp_f12_3;
    f32 temp_f12_2;
    f32 temp_f12;
    f32 temp_f10;
    f32 temp_f0_3;
    f32 temp_f0_2;
    f32 temp_f0;
    f32 sp3C;
    struct127 *sp48;
    s32 sp4C;
    f32 sp60;
    f32 sp64;
    f32 sp68;
    u16 sp78;
    f32 sp7C;
    f32 sp80;
    f32 sp84;
    s32 sp88;
    f32 sp8C;
    f32 sp90;
    f32 sp94;
    f32 spE0;
    f32 spE4;
    u8 spEB;
    s32 spF0;
    f32 spF4;
    f32 sp100;
    s32 sp104;
    s32 sp108;
    s32 sp10C;
    f32 sp11C;
    f32 sp120;
    f32 sp124;
    f32 sp12C;
    f32 sp130;
    struct124 *sp134;
    u8 sp13B;
    f32 sp13C;
    f32 sp144;
    u8 sp149;
    u16 sp14A;
    f32 sp14C;
    u8 sp153;
    f32 sp154;
    f32 sp158;
    u8 sp15F;
    f32 sp160;
    f32 sp164;
    f32 sp16C;
    f32 sp170;
    f32 sp174;

    sp13B = 1;
    temp_v0 = arg0->unk23A;
    if (temp_v0 != 0) {
        arg0->unk218 = aiscript_find_by_kind(4, temp_v0);
        arg0->unk21C = 0;
        arg0->unk23A = 0;
    }
    if ((D_800C3638 == 0) || (cutscene_obj_takes_part(arg0) == 0)) {
        if ((arg0->unkF4 & 0x1000) && (arg0->unk28 < 0.2f)) {
            arg0->unk21C = 0;
        }
        aiscript_run(arg0);
        var_v1 = arg0->unk223;
        var_t0 = var_v1;
        if ((var_v1 == 0xE) || (var_v1 == 0xF) || (var_v1 == 0x10)) {
            var_v1 = 1;
            var_t0 = 1;
        }
        if (var_t0 == 0x11) {
            var_v1 = 0;
        }
        if (arg0->stunned == 0) {
            sp14A = (u16) ((s32) (((arg0->unk1E5 << 8) + arg0->unk1E7) * D_800CC264) / 100);
            sp149 = arg0->unk1E6;
            temp_v0_2 = arg0->unk13F;
            if (D_800D2528[temp_v0_2] == 0) {
                arg0->xz_velocity = 0.0f;
                obj_update_move_anim(arg0, 0.0f);
                return;
            }
            var_t0_2 = var_v1;
            sp134 = D_800D1C90[arg0->id];
            temp_a0 = arg0->unk23D;
            if (temp_a0 == 0xFF) {
                sp164 = 1e9f;
            } else {
                temp_f4 = (f32) (temp_a0 * 8);
                sp164 = temp_f4;
                sp164 = temp_f4 * temp_f4;
            }
            temp_v1 = g_path_points[temp_v0_2];
            if ((*(u16 *)((u8 *)temp_v1 + 6)) != 0) {
                sp174 = (f32) (*(s16 *)((u8 *)temp_v1 + 0)) - arg0->x_position;
                sp170 = (f32) (*(s16 *)((u8 *)temp_v1 + 4)) - arg0->z_position;
            }
            temp_v0_3 = arg0->unk25C;
            if ((temp_v0_3 & 4) && !(temp_v0_3 & 1) && ((var_t0_2 == 1) || (var_t0_2 == 3))) {
                arg0->unk21C = 0;
            }
            if ((arg0->unk25C & 1) && ((var_t0_2 == 0) || (var_t0_2 == 5))) {
                sp4C = (s32) var_t0_2;
                var_t0_2 = (u8) sp4C;
                if (obj_in_spawn_radius(arg0, (s32) arg0->unk25B) != 0) {
                    sp4C = (s32) var_t0_2;
                    temp_v1_2 = arg0->unk25B;
                    var_t0_2 = (u8) sp4C;
                    arg0->unk218 = aiscript_find_by_kind(1, arg0->unk233);
                    arg0->unk21C = 0;
                    arg0->unkA8 = temp_v1_2 | 0x80;
                    arg0->unk222 = temp_v1_2;
                }
            }
            temp_v0_4 = arg0->unk25A;
            if (temp_v0_4 != 0) {
                var_f10 = (f32) temp_v0_4;
                if ((s32) temp_v0_4 < 0) {
                    var_f10 += 4294967296.0f;
                }
                arg0->unk44 = var_f10;
            }
            if ((var_t0_2 == 1) || (var_t0_2 == 0xC) || (var_t0_2 == 2) || (var_t0_2 == 3) || (var_t0_2 == 9) || (var_t0_2 == 0xA) || ((var_t0_2 == 6) && !(arg0->unk22C & 1))) {
                var_v1_2 = arg0->unk222;
                var_a2 = &g_objects[var_v1_2];
                sp174 = var_a2->x_position;
                sp170 = var_a2->z_position;
                sp16C = var_a2->y_position;
                if (arg0->unk223 == 0x10) {
                    sp15F = var_v1_2;
                    sp48 = var_a2;
                    sp4C = (s32) var_t0_2;
                    temp_f0 = obj_dist_3d(var_a2, arg0);
                    sp120 = temp_f0;
                    temp_t6 = arg0->unk231;
                    var_f8 = (f32) temp_t6;
                    if ((s32) temp_t6 < 0) {
                        var_f8 += 4294967296.0f;
                    }
                    temp_f4_2 = sp48->xz_velocity * (temp_f0 / var_f8);
                    sp124 = temp_f4_2;
                    vec_from_yaw_pitch(sp48->unk76, temp_f4_2, 0.0f, &sp124, &sp120, &sp11C);
                    var_v1_2 = sp15F;
                    var_t0_2 = (u8) sp4C;
                    var_a2 = sp48;
                    sp174 += sp124;
                    sp170 += sp120;
                }
                temp_f8 = sp174 - arg0->x_position;
                sp130 = temp_f8;
                var_f16 = sp170 - arg0->z_position;
                var_f12 = sqrtf((temp_f8 * temp_f8) + (var_f16 * var_f16));
                if ((var_t0_2 == 1) && (arg0->unk44 > 1.0f) && (sqrtf(sp164) < (var_f12 * 0.8f))) {
                    arg0->unk21C = 0;
                }
                temp_v0_5 = arg0->id;
                if (temp_v0_5 != 0x16) {
                    if ((var_t0_2 == 1) && (arg0->unk234 != 0) && ((var_f12 < 370.0f) || (temp_v0_5 == 0x21)) && ((s32) var_v1_2 < 4) && ((arg0->xz_velocity > 15.0f) || (temp_v0_5 == 0x53))) {
                        temp_v0_6 = var_a2->unk31C;
                        if (temp_v0_6 != NULL) {
                            temp_v0_6->chased = 0xA;
                        }
                    }
                    if ((var_t0_2 == 2) && (var_f12 < 470.0f) && ((s32) var_v1_2 < 4) && (((arg0->unk76 - var_a2->unk76) - 0x4000) & 0x8000)) {
                        temp_v0_7 = var_a2->unk31C;
                        if (temp_v0_7 != NULL) {
                            temp_v0_7->chasing = 6;
                        }
                    }
                }
                switch (var_t0_2) {                 /* irregular */
                case 9:
                    break;
                default:
                    sp13B = 0;
                    /* fallthrough */
                case 10:
                case 12:
                    if ((arg0->unk22C & 0x80) && (fabsf((arg0->y_position - arg0->unk28) - (var_a2->y_position - var_a2->unk28)) > 30.0f)) {
                        arg0->unk21C = 0;
                    }
                    sp48 = var_a2;
                    if (arg0->unk223 != 0xF) {
                        sp12C = var_f16;
                        sp160 = var_f12;
                        sp4C = (s32) var_t0_2;
                        sp48 = var_a2;
                        var_t0_2 = (u8) sp4C;
                        var_f12 = sp160;
                        var_f16 = sp12C;
                        if (obj_in_spawn_radius(arg0, (s32) arg0->unk222) == 0) {
                            arg0->unk21C = 0;
                        }
                    }
                    if ((u16) arg0->unk22E != 0) {
                        var_f2 = 0.0f;
                    } else {
                        temp_v0_8 = arg0->unk236;
                        if (temp_v0_8 == 0) {
                            var_f2 = (f32) (arg0->unk23C * 8);
                        } else if (temp_v0_8 == 0xFF) {
                            var_f2 = 3000000.0f;
                        } else {
                            var_f2 = (f32) (temp_v0_8 * 8);
                        }
                    }
                    if (((var_t0_2 == 1) || (var_t0_2 == 6) || (var_t0_2 == 0xA)) && (arg0->unk234 != 0) && (var_f12 < var_f2)) {
                        var_v1_3 = 1;
                        if ((arg0->id == 8) && (var_f2 < fabsf(arg0->y_position - sp48->y_position))) {
                            var_v1_3 = 0;
                        }
                        temp_v0_9 = arg0->unk22A;
                        if (temp_v0_9 != 0) {
                            var_f4 = (f32) temp_v0_9;
                            if ((s32) temp_v0_9 < 0) {
                                var_f4 += 4294967296.0f;
                            }
                            if ((g_cur_obj_index != 0) && (fabsf(arg0->y_position - *g_obj0_y) < (var_f4 * 8.0f))) {
                                var_v1_3 = 0;
                            }
                        }
                        if (var_v1_3 != 0) {
                            sp4C = (s32) var_t0_2;
                            temp_v0_10 = math_atan2_u16(sp130, -var_f16, 0);
                            temp_a0_2 = arg0->unk237;
                            var_t0_2 = (u8) sp4C;
                            if ((temp_a0_2 != 0) && (((((s32) (arg0->unk76 - temp_v0_10) >> 8) + ((s32) temp_a0_2 / 2)) & 0xFF) < (s32) temp_a0_2)) {
                                sp4C = (s32) var_t0_2;
                                var_t0_2 = (u8) sp4C;
                                arg0->unk218 = aiscript_find_by_kind(2, arg0->unk234);
                                arg0->unk21C = 0;
                            }
                        }
                    }
                    break;
                }
            }
            if (sp13B != 0) {
                temp_v1_3 = (u16) arg0->unk22E;
                if (arg0->unk235 != 0) {
                    sp10C = 0;
                } else {
                    sp10C = 1;
                }
                if (temp_v1_3 != 0) {
                    if ((s32) D_800BE9A0 >= (s32) temp_v1_3) {
                        arg0->unk22E = 0;
                    } else {
                        arg0->unk22E = temp_v1_3 - D_800BE9A0;
                    }
                }
                if (arg0->unk241 != 0) {
                    var_a3 = 0;
                    var_a0 = g_objects;
                    var_a1 = 0;
                    var_f16_2 = (f32) (arg0->unk23F * 8);
                    do {
                        if ((var_a0->interaction_state != 0) && (arg0->unk240 == var_a0->id) && (var_a0->unk2FA != 0)) {
                            temp_f12 = var_a0->x_position - arg0->x_position;
                            temp_f14 = arg0->z_position - var_a0->z_position;
                            temp_f2 = sqrtf((temp_f12 * temp_f12) + (temp_f14 * temp_f14));
                            if (temp_f2 < var_f16_2) {
                                sp100 = var_f16_2;
                                spF4 = temp_f2;
                                spF0 = (s32) (sp134->unk17 * 3) / 2;
                                sp4C = (s32) var_t0_2;
                                sp104 = var_a3;
                                sp108 = var_a1;
                                sp48 = var_a0;
                                var_a0 = sp48;
                                var_a1 = sp108;
                                var_a3 = sp104;
                                var_t0_2 = (u8) sp4C;
                                var_f16_2 = sp100;
                                if ((((((s32) arg0->unk7A >> 8) - (math_atan2_u16(temp_f12, temp_f14, 0) >> 8)) + (spF0 / 2)) & 0xFF) < spF0) {
                                    var_a3 = var_a1 + 1;
                                    var_f16_2 = spF4;
                                }
                            }
                        }
                        var_a1 += 1;
                        var_a0 += 1;
                    } while (var_a1 != 0x19);
                    if (var_a3 != 0) {
                        sp4C = (s32) var_t0_2;
                        sp104 = var_a3;
                        var_t0_2 = (u8) sp4C;
                        arg0->unk218 = aiscript_find_by_kind(0, arg0->unk241);
                        arg0->unk21C = 0;
                        arg0->unk222 = sp104 - 1;
                        arg0->unkA8 = sp104 + 0x7F;
                        arg0->unk22E = 5;
                        if (arg0->unk242 != 0) {
                            temp_v1_4 = &g_objects[sp104];
                            g_cur_obj = temp_v1_4 - 1;
                            sp4C = (s32) var_t0_2;
                            sp48 = temp_v1_4;
                            (*(struct216 **)((u8 *)sp48 + -0x114)) = aiscript_find_by_kind(0, arg0->unk242);
                            (*(s16 *)((u8 *)sp48 + -0x110)) = 0;
                            var_t0_2 = (u8) sp4C;
                            (*(u8 *)((u8 *)sp48 + -0x10A)) = (u8) g_cur_obj_index;
                            g_cur_obj = arg0;
                        }
                    }
                }
                if (((u16) arg0->unk22E == 0) && (var_t0_2 != 4) && (var_t0_2 != 7) && (((sp10C == 0) && (arg0->unk235 != 0)) || ((sp10C == 1) && (arg0->unk233 != 0) && !(arg0->unk25C & 4)))) {
                    temp_t8 = (*(u8 *)((u8 *)sp134 + 0x18));
                    var_f10_2 = (f32) temp_t8;
                    if ((s32) temp_t8 < 0) {
                        var_f10_2 += 4294967296.0f;
                    }
                    if (var_f10_2 <= arg0->xz_velocity) {
                        sp4C = (s32) var_t0_2;
                        var_t0_2 = (u8) sp4C;
                        if (obj_in_spawn_radius(arg0, 0) != 0) {
                            spEB = 0;
                            temp_f12_2 = g_obj0_x - (f32) arg0->unk1A4;
                            temp_f14_2 = (f32) arg0->unk1A8 - g_obj0_z;
                            if ((arg0->id == 0x9E) && (arg0->unk2E4 == 0)) {
                                sp164 = 129600.0f;
                            }
                            temp_f0_2 = (temp_f12_2 * temp_f12_2) + (temp_f14_2 * temp_f14_2);
                            if ((temp_f0_2 < sp164) && (temp_f0_2 < 1e8f)) {
                                sp4C = (s32) var_t0_2;
                                spE4 = temp_f12_2;
                                spE0 = temp_f14_2;
                                var_t0_2 = (u8) sp4C;
                                if (obj_in_spawn_radius(arg0, 0) != 0) {
                                    temp_v0_11 = arg0->unk229;
                                    if (temp_v0_11 == 0xFF) {
                                        var_f2_2 = sqrtf(sp164);
                                    } else {
                                        var_f6 = (f32) temp_v0_11;
                                        if ((s32) temp_v0_11 < 0) {
                                            var_f6 += 4294967296.0f;
                                        }
                                        var_f2_2 = var_f6 * 8.0f;
                                    }
                                    if ((g_cur_obj_index != 0) && ((temp_v0_11 == 0) || (fabsf(arg0->y_position - *g_obj0_y) < var_f2_2))) {
                                        if (arg0->id == 0x9E) {
                                            sp4C = (s32) var_t0_2;
                                            vec_from_yaw_pitch(arg0->unk7A, 9000.0f, arg0->unkB8, &sp94, &sp90, &sp8C);
                                            temp_f10 = sp94 + arg0->x_position;
                                            sp94 = temp_f10;
                                            temp_f8_2 = sp90 + arg0->z_position;
                                            sp90 = temp_f8_2;
                                            temp_f4_3 = sp8C + arg0->y_position;
                                            sp8C = temp_f4_3;
                                            mtxf_look_at_f(sp98, arg0->x_position, arg0->y_position, arg0->z_position, temp_f10, temp_f4_3, temp_f8_2, 0.0f, 1.0f, 0.0f);
                                            var_t0_2 = (u8) sp4C;
                                            if (math_mtx_box_in_frustum(sp98, g_obj0_x, *g_obj0_y, g_obj0_z, 80.0f, 80.0f, 0.0f, 4000.0f, 320.0f, 320.0f) != 0) {
                                                spEB = 1;
                                            }
                                        } else {
                                            var_v1_4 = sp134->unk17;
                                            if (sp10C == 0) {
                                                var_v1_4 *= 3;
                                            }
                                            sp88 = (s32) var_v1_4;
                                            sp4C = (s32) var_t0_2;
                                            var_t0_2 = (u8) sp4C;
                                            if (((((((s32) arg0->unk7A >> 8) + arg0->unk2CA) - (math_atan2_u16(spE4, spE0, 0) >> 8)) + (sp88 / 2)) & 0xFF) < sp88) {
                                                spEB = 1;
                                            }
                                        }
                                    }
                                }
                            }
                            if (spEB != 0) {
                                if (sp10C == 0) {
                                    sp4C = (s32) var_t0_2;
                                    var_v0 = aiscript_find_by_kind(3, arg0->unk235);
                                    var_t0_2 = (u8) sp4C;
                                } else {
                                    sp4C = (s32) var_t0_2;
                                    var_v0 = aiscript_find_by_kind(1, arg0->unk233);
                                    var_t0_2 = (u8) sp4C;
                                }
                                arg0->unk218 = var_v0;
                                arg0->unk21C = 0;
                                arg0->unk222 = spEB - 1;
                                arg0->unkA8 = spEB + 0x7F;
                            }
                        }
                    }
                }
                if (var_t0_2 != 9) {
                    if ((var_t0_2 == 6) || (var_t0_2 == 0xC)) {
                        temp_v0_12 = &g_objects[arg0->unk222];
                        sp174 = temp_v0_12->x_position;
                        sp170 = temp_v0_12->z_position;
                        sp16C = temp_v0_12->y_position;
                    } else {
                        temp_v0_13 = g_path_points[arg0->unk13F] + (arg0->unk21E * 8);
                        sp174 = (f32) (*(s16 *)((u8 *)temp_v0_13 + 8));
                        sp170 = (f32) (*(s16 *)((u8 *)temp_v0_13 + 0xC));
                        sp16C = (f32) (*(s16 *)((u8 *)temp_v0_13 + 0xA));
                    }
                    if ((var_t0_2 == 5) || (var_t0_2 == 6)) {
                        if ((var_t0_2 == 6) && (arg0->unk22C & 1)) {
                            arg0->unk86 = (u8) (g_objects[arg0->unk222].unk7A >> 8);
                        }
                        temp_t4 = arg0->unk258;
                        arg0->unk86 += arg0->unk257;
                        var_f8_2 = (f32) temp_t4;
                        if ((s32) temp_t4 < 0) {
                            var_f8_2 += 4294967296.0f;
                        }
                        temp_f4_4 = var_f8_2 * 16.0f;
                        sp84 = temp_f4_4;
                        sp4C = (s32) var_t0_2;
                        vec_from_yaw_pitch((arg0->unk86 << 8) & 0xFFFF, temp_f4_4, 0.0f, &sp84, &sp80, &sp7C);
                        var_t0_2 = (u8) sp4C;
                        sp174 += sp84;
                        sp170 += sp80;
                    }
                }
            }
            temp_f12_3 = arg0->unk44;
            sp14C = temp_f12_3;
            if ((var_t0_2 != 7) && (var_t0_2 != 8)) {
                temp_f16 = arg0->x_position;
                temp_f4_5 = sp174 - temp_f16;
                sp174 = temp_f4_5;
                temp_f18 = arg0->z_position;
                sp170 = temp_f18 - sp170;
                sp16C = arg0->y_position - sp16C;
                if ((var_t0_2 == 6) && (arg0->unk22C & 1) && ((fabsf(sp170) + fabsf(temp_f4_5)) < 100.0f)) {
                    sp14C = 0.0f;
                    sp4C = (s32) var_t0_2;
                    temp_v0_14 = &g_objects[arg0->unk222];
                    sp174 = temp_v0_14->x_position - temp_f16;
                    sp170 = temp_f18 - temp_v0_14->z_position;
                    var_v0_2 = math_atan2_u16(sp174, sp170, 0);
                    var_t0_2 = (u8) sp4C;
                    goto block_182;
                }
                if ((temp_f12_3 >= 0.5f) && !(arg0->unkF4 & 0x40)) {
                    sp4C = (s32) var_t0_2;
                    var_v0_2 = math_atan2_u16(sp174, sp170, 0);
                    var_t0_2 = (u8) sp4C;
block_182:
                    arg0->unk78 = var_v0_2;
                }
            }
            temp_t8_2 = arg0->unk247;
            var_f6_2 = (f32) temp_t8_2;
            if ((s32) temp_t8_2 < 0) {
                var_f6_2 += 4294967296.0f;
            }
            sp158 = var_f6_2 / 10.0f;
            temp_f12_4 = (sp174 * sp174) + (sp170 * sp170);
            var_f2_3 = temp_f12_4;
            if (arg0->unk22C & 8) {
                var_f2_3 = temp_f12_4 + (sp16C * sp16C);
            }
            temp_f2_2 = sqrtf(var_f2_3);
            if ((var_t0_2 != 4) && (var_t0_2 != 7) && (var_t0_2 != 8)) {
                sp78 = arg0->unk76;
                if (var_t0_2 == 2) {
                    temp_t3 = arg0->unk78 ^ 0x8000;
                    arg0->unk78 = temp_t3;
                    if (!(arg0->unkF4 & 0x4000)) {
                        arg0->unk78 = temp_t3 + (((((s32) arg0->unk21C / 100) & 0x20) - 0x10) << 8);
                    }
                }
                if (arg0->unk223 == 0x11) {
                    arg0->unk78 += ((((s32) arg0->unk21C / 100) & 0x10) - 8) << 9;
                }
                if ((arg0->unkF4 & 0x200) && (arg0->unk1F4 < 3.0f)) {
                    sp14A = 0;
                    sp149 = 0;
                }
                sp3C = temp_f12_4;
                sp144 = temp_f2_2;
                sp4C = (s32) var_t0_2;
                sp13C = (f32) (arg0->unk23E * 8);
                temp_v0_15 = obj_turn_to_target_yaw(arg0, sp14A);
                sp153 = temp_v0_15;
                if (sp4C != 0xD) {
                    temp_v1_5 = (u8) arg0->unk24F;
                    if ((temp_v1_5 != 0) && ((sp4C != 0) || (sp13C < sp144))) {
                        temp_t9 = (temp_v1_5 - 1) & 0xFF;
                        if ((s32) *g_hit_reaction_anims[temp_t9] < (temp_v0_15 & 0xFF)) {
                            arg0->unk76 = sp78;
                            obj_start_hit_reaction(arg0, (s32) sp153, temp_t9);
                        }
                    }
                }
                if (sp4C == 0xD) {
                    sp14A = 0;
                    sp149 = 0;
                }
                if (((s32) (*(u8 *)((u8 *)sp134 + 0x19)) < (s32) sp153) && (sp4C != 2)) {
                    sp14C = 0.0f;
                    temp_v0_16 = arg0->unk24A;
                    if ((temp_v0_16 != 0) && (arg0->xz_velocity > 15.0f)) {
                        arg0->unk218 = aiscript_find_by_kind(6, temp_v0_16);
                        arg0->unk21C = 0;
                        arg0->unk222 = 0;
                    }
                }
                if (((sp4C == 0) || (sp4C == 0xA)) && (sp144 < sp13C)) {
                    temp_v0_17 = arg0->unk13F;
                    temp_v1_6 = arg0->unk21F;
                    var_a2_2 = (D_800D2528[temp_v0_17] - 1) & 0xFF;
                    if (temp_v1_6 != 0) {
                        var_a2_2 = temp_v1_6 & 0xFF;
                    }
                    temp_a1 = arg0->unk22C;
                    if (temp_a1 & 4) {
                        temp_t7 = arg0->unk21E * 8;
                        arg0->x_position = (f32) (*(s16 *)((u8 *)((g_path_points[temp_v0_17] + temp_t7)) + 8));
                        arg0->unk1FC |= 8;
                        arg0->z_position = (f32) (*(s16 *)((u8 *)((g_path_points[temp_v0_17] + temp_t7)) + 0xC));
                        if (temp_a1 & 8) {
                            arg0->y_position = (f32) (*(s16 *)((u8 *)((g_path_points[temp_v0_17] + temp_t7)) + 0xA));
                        }
                    }
                    if (!(arg0->unkF4 & 0x10)) {
                        arg0->unk21C = 0;
                    }
                    temp_v1_7 = arg0->unk220;
                    temp_t5 = arg0->unk21E + arg0->unk221;
                    temp_t1 = (temp_t5 & 0xFF) + var_a2_2;
                    temp_hi = (s32) (temp_t1 & 0xFF) % var_a2_2;
                    arg0->unk21E = temp_t5;
                    arg0->unk21E = temp_t1;
                    arg0->unk21E = (u8) temp_hi;
                    if ((temp_hi & 0xFF) < (s32) temp_v1_7) {
                        arg0->unk21E = temp_v1_7;
                    }
                }
                var_a2_3 = arg0->unk78;
                if (arg0->unkF4 & 0x20000) {
                    temp_v0_18 = &g_objects[arg0->unk222];
                    var_a2_3 = math_atan2_u16(temp_v0_18->x_position - arg0->x_position, arg0->z_position - temp_v0_18->z_position, 0) & 0xFFFF;
                }
                sp153 = obj_turn_towards(arg0, sp149, var_a2_3);
                temp_t1_2 = arg0->unk248;
                var_f6_3 = (f32) temp_t1_2;
                if ((s32) temp_t1_2 < 0) {
                    var_f6_3 += 4294967296.0f;
                }
                sp154 = var_f6_3 / 10.0f;
                temp_v1_8 = arg0->unk3A;
                if ((temp_v1_8 != 0) && (arg0->unk28 == 0.0f) && !(temp_v1_8 & 3 & g_obj_update_counter)) {
                    arg0->unk84.uh = 0xFF;
                    arg0->y_velocity = (f32) temp_v1_8;
                }
                temp_v0_19 = arg0->unkF4;
                if (temp_v0_19 & 1) {
                    sp14C = 0.0f;
                }
                if ((arg0->unk22C & 0x10) && (arg0->unk28 == 0.0f)) {
                    sp14C = 0.0f;
                    sp158 = 1.0f;
                }
                if (arg0->interaction_state == 1) {
                    arg0->unk44 = sp14C;
                    return;
                }
                if (temp_v0_19 & 0x80000) {
                    temp_f0_3 = sp16C + 70.0f;
                    var_f14 = temp_f0_3;
                    if (g_level_id == 0x26) {
                        var_f14 = temp_f0_3 - (45.0f * arg0->y_scale);
                    }
                    obj_step_tilt_toward(arg0, (s8) ((s16) math_atan2_u16(sqrtf(sp3C), var_f14, 0) / 200), 0);
                } else if (arg0->unk1D1 != 0) {
                    obj_step_tilt_toward(arg0, 0, 0);
                }
                if (arg0->unkF8 & 0x40000) {
                    sp14C = arg0->unk44;
                    vec_from_yaw_pitch(arg0->unk78, sp14C, 0.0f, &sp68, &sp64, &sp60);
                    if ((sp14C < 1.0f) || (var_f0 = sp158, ((((sp78 - arg0->unk78) + 0x4000) & 0x8000) != 0))) {
                        var_f0 = sp154;
                    }
                    move_xz_towards(sp68, sp64, var_f0, &arg0->unk174, &arg0->unk178);
                    temp_f2_3 = arg0->unk174;
                    temp_f12_5 = arg0->unk178;
                    arg0->unk76 = math_atan2_u16(arg0->unk174, -arg0->unk178, 0);
                    arg0->xz_velocity = 2.0f * sqrtf((temp_f2_3 * temp_f2_3) + (temp_f12_5 * temp_f12_5));
                } else {
                    obj_approach_speed(sp14C, arg0, sp158, sp154, (u8) (s32) sp153);
                }
                goto block_251;
            }
            sp3C = temp_f12_4;
            obj_turn_towards(arg0, arg0->unk1E6, arg0->unk78);
            arg0->unk76 = arg0->unk78;
            arg0->xz_velocity = sp14C;
block_251:
            obj_update_move_anim(arg0, sp158);
            if ((arg0->unk22C & 8) && !(arg0->unk1FC & 8)) {
                temp_f2_4 = (f32) math_atan2_u16(sqrtf(sp3C), sp16C, 0) * 0.005493164f;
                var_f0_2 = temp_f2_4;
                if (temp_f2_4 > 180.0f) {
                    var_f0_2 = temp_f2_4 - 360.0f;
                }
                temp_f12_6 = arg0->unkB8;
                var_f0_3 = (var_f0_2 - temp_f12_6) * 0.25f;
                var_f8_3 = (f32) sp14A;
                if ((s32) sp14A < 0) {
                    var_f8_3 += 4294967296.0f;
                }
                temp_f2_5 = var_f8_3 * 0.005493164f;
                temp_f14_3 = -temp_f2_5;
                if (temp_f2_5 < var_f0_3) {
                    var_f0_3 = temp_f2_5;
                }
                if (var_f0_3 < temp_f14_3) {
                    var_f0_3 = temp_f14_3;
                }
                arg0->unkB8 = temp_f12_6 + var_f0_3;
            }
        }
    }
}
extern f32 g_move_anim_rate_scale; /* was D_80099828 */
extern f32 g_move_anim_speed_base; /* was D_8009982C */
extern f32 g_move_anim_speed_bonus; /* was D_80099830 */
extern f32 g_move_anim_input_bias; /* was D_80099838 */
extern f32 g_move_anim_input_scale; /* was D_8009983C */
extern s32 D_80041C50;
extern u8 D_80041D40;

/* was func_1505841C */
void obj_update_move_anim(struct127 *arg0, f32 arg1) {
    f32 temp_f12;
    f32 var_f0;
    f32 var_f0_2;
    struct197 *temp_v0_2;
    u8 temp_v0;

    temp_v0 = arg0->unk246;
    var_f0 = (f32) (((temp_v0 & 0x1F) << 8) + arg0->unk249) * g_move_anim_rate_scale;
    if (!(temp_v0 & 0x80)) {
        temp_f12 = arg0->xz_velocity;
        if ((temp_f12 <= 1.0f) || ((arg0->unk22C & 0x10) && (arg0->unk28 == 0.0f))) {
            var_f0 = arg1;
        } else {
            var_f0 = ((temp_f12 * (0.5f / arg0->xz_scale)) / (var_f0 * 10.0f)) + g_move_anim_speed_base;
            if (!(temp_v0 & 0x20)) {
                var_f0 += g_move_anim_speed_bonus;
            }
        }
    }
    if (arg0->unk223 == 0xD) {
        var_f0 = (f32) (arg0->unk250 & 0x7F) * g_move_anim_speed_base;
    }
    if (temp_v0 == 0xFF) {
        var_f0 = 0.0f;
    }
    obj_start_anim(arg0, (u16) arg0->unk244, var_f0, (f32) arg0->unk1D0, 0.0f, 0.0f, 0);
    if (arg0->unk246 == 0xFF) {
        var_f0_2 = ((f32) *(&D_80041C50 + (D_80041D40 << 6)) - g_move_anim_input_bias) * g_move_anim_input_scale;
        if (var_f0_2 < 0.0f) {
            var_f0_2 = 0.0f;
        }
        temp_v0_2 = arg0->unk2D0;
        temp_v0_2->unk8 = ((temp_v0_2->unk18 - 1.0f) * (32768.0f - var_f0_2)) / 32768.0f;
    }
}
// NON-MATCHING: JUSTREG
// void obj_update_move_anim(struct127 *arg0, f32 arg1) {
//     struct197 *temp_v0_2;
//     f32 temp_f0;
//     f32 temp_f1;
//     s32 idx;
//
//     temp_f0 = (((arg0->unk246 & 0x1F) << 8) + arg0->unk249) * D_80099468;
//     if ((arg0->unk246 & 0x80) == 0) {
//         if ((arg0->xz_velocity <= 1.0f) || (((arg0->unk22C & 0x10) != 0) && (arg0->unk28 == 0.0f))) {
//             temp_f0 = arg1;
//         } else {
//             // regalloc off here
//             temp_f1 = (arg0->xz_velocity * (0.5f / arg0->xz_scale));
//             temp_f0 = temp_f1 / (temp_f0 * 10.0f);
//             temp_f0 += D_8009946C;
//
//             if ((arg0->unk246 & 0x20) == 0) {
//                 temp_f0 += D_80099470;
//             }
//         }
//     }
//     if (arg0->unk223 == 0xD) {
//         temp_f0 = (arg0->unk250 & 0x7F) * D_80099474;
//     }
//     if (arg0->unk246 == 0xFF) {
//         temp_f0 = 0.0f;
//     }
//     obj_start_anim(arg0, arg0->unk244, temp_f0, arg0->unk1D0, 0.0f, 0.0f, 0);
//
//     if (arg0->unk246 == 0xFF) {
//         // regalloc off here
//         idx = D_800419A0 << 4;
//         temp_f0 = D_800418B0[idx];
//         if (temp_f0 >= 0.0f) {
//             temp_v0_2 = arg0->unk2D0;
//             temp_v0_2->unk8 = (f32) ((temp_v0_2->unk18 * (32768.0f - temp_f0)) / 32768.0f);
//         }
//     }
// }

// object_stun_update: P210: per-frame stun / hit-recovery update of object `obj` (port P209: void, one argument).
/* Hover physics obj_approach_speed (speed unk109 / 10); remembers the height in unk1CC while it is unset (>= 100000);
 * while lifted (+0xAD 1..9) no gravity, the upward speed fades (x0.9 below 60) and above unk118 - 20 the lift
 * ends (gravity 4). unk21C is cleared unless a player in multiplayer. Unless stunned 0xFF: the stun counter
 * counts down (0xFE stays; a dead player keeps it), the hit timer unk10C by D_800CC264 (cleared when unk28 < 0.2
 * with flag 0x100; at 0 the controller's byte 0x7D is cleared and obj_hit_reaction_advance runs). Stun over: speeds and
 * turning stop (players: objev_anim_d1_by_depth when lifted, else gravity 4 and flag 0x8000 cleared), unk23A = unk238 when
 * set. Still stunned: the hit reaction obj_turn_towards(obj, 12, heading (turned round with unk10B bit 4)) unless
 * unk10B bit 2, with unk80 = 10. */
/* was func_150585F0 */
void obj_stun_update(struct127 *obj) {
    u8 *b = (u8 *)obj;
    u8 lift;
    u8 stun;
    u8 hit;
    u16 heading;

    obj_approach_speed(0.0f, obj, 1.0f, obj->unk109 * 0.1f, 0);
    if (obj->unk1CC < 100000.0f) {
        obj->unk1CC = obj->y_position;
    }
    lift = b[0xAD];
    if (lift != 0 && lift < 10) {
        obj->gravity = 0.0f;
        if (obj->y_velocity < 60.0f) {
            obj->y_velocity *= 0.9f;
        }
        if (obj->unk118 - 60.0f + 40.0f < obj->y_position) {
            obj->unk81 = 0;
            obj->unk83 = 0;
            b[0xAD] = 0;
            obj->unkB8 = 0.0f;
            obj->gravity = 4.0f;
        }
    }
    if (D_800BE616 == 0 || obj->interaction_state != 1) {
        obj->unk21C = 0;
    }
    stun = obj->stunned;
    if (stun == 0xFF) {
        return;
    }
    if (stun != 0xFE && (obj->health != 0 || obj->interaction_state != 1)) {
        obj->stunned = stun - 1;
    }
    obj->unk10C -= D_800CC264;
    if (obj->unk28 < 0.2f && (obj->unkF4 & 0x100)) {
        obj->unk10C = 0;
    }
    if (obj->unk10C <= 0) {
        if (obj->unk31C != NULL) {
            ((u8 *)obj->unk31C)[0x7D] = 0;
        }
        obj->unk10C = 0;
        obj_hit_reaction_advance(g_cur_obj_index, obj);
    }
    if (obj->stunned == 0) {
        obj->xz_velocity = 0.0f;
        obj->unk81 = 0;
        obj->unk78 = obj->unk7A;
        obj->unk76 = obj->unk7A;
        if (b[0xAD] != 0) {
            obj->y_velocity = 0.0f;
            if (obj->interaction_state == 1) {
                objev_anim_d1_by_depth();
            }
        } else if (obj->interaction_state == 1) {
            obj->unkF8 &= ~0x8000;
            obj->gravity = 4.0f;
        }
        if (obj->unk238 != 0) {
            obj->unk23A = obj->unk238;
        }
    } else {
        hit = obj->unk10B;
        if (!(hit & 2)) {
            heading = obj->unk76;
            if (hit & 4) {
                heading ^= 0x8000;
            }
            obj->unk80 = 10;
            obj_turn_towards(obj, 12, heading);
        }
    }
}
// NON-MATCHING: 80% there
// void obj_stun_update(struct127 *arg0) {
//     f32 temp_f0;
//     u16 phi_a2;
//
//     obj_approach_speed(arg0->unk109 * D_80099478, arg0, 1.0f, arg0->unk109 * D_80099478, 0);
//     if (arg0->unk1CC < D_8009947C) {
//         arg0->unk1CC = arg0->y_position;
//     }
//     if ((arg0->in_water != 0) && ((s32) arg0->in_water < 0xA)) {
//         arg0->gravity = 0.0f;
//         if (arg0->y_velocity < 60.0f) {
//             arg0->y_velocity *= D_80099480;
//         }
//         if (((arg0->unk118 - 60.0f) + 40.0f) < arg0->y_position) {
//             arg0->unk81 = (u8)0;
//             arg0->unk83 = (u8)0;
//             arg0->in_water = (u8)0U;
//             arg0->unkB8 = 0.0f;
//             arg0->gravity = 4.0f;
//         }
//     }
//     if ((D_800BE616 == 0) || (arg0->interaction_state != 1)) {
//         arg0->unk21C = (u16)0;
//     }
//     if (arg0->stunned != 0xFF) {
//         if (arg0->stunned != 0xFE) {
//             if ((arg0->health != 0) || (1 != arg0->interaction_state)) {
//                 arg0->stunned -= 1;
//             }
//         }
//         arg0->unk10C -= D_800CC264;
//         if ((arg0->unk28 < D_80099484) && ((arg0->unkF4 & 0x100) != 0)) {
//             arg0->unk10C = (u16)0;
//         }
//         if ((s32) arg0->unk10C <= 0) {
//             if (arg0->unk31C != 0) {
//                 arg0->unk31C->matrix_physics = (u8)0;
//             }
//             arg0->unk10C = (u16)0;
//             obj_hit_reaction_advance(0.0f, g_cur_obj_index);
//         }
//         if (arg0->stunned == 0) {
//             arg0->xz_velocity = 0.0f;
//             arg0->unk81 = (u8)0;
//             arg0->unk76 = arg0->unk78 = arg0->unk7A;
//             if (arg0->in_water != 0) {
//                 arg0->y_velocity = 0.0f;
//                 if (arg0->interaction_state == 1) {
//                     objev_anim_d1_by_depth();
//                 }
//             } else if (arg0->interaction_state == 1) {
//                 arg0->unkF8 &= 0xFFFF7FFF;
//                 arg0->gravity = 4.0f;
//             }
//             if (arg0->unk238 != 0) {
//                 arg0->unk23A = arg0->unk238;
//             }
//         } else {
//             if ((arg0->unk10B & 2) == 0) {
//                 phi_a2 = arg0->unk76;
//                 if ((arg0->unk10B & 4) != 0) {
//                     phi_a2 ^= 0x8000;
//                 }
//                 arg0->unk80 = (u8)0xA;
//                 obj_turn_towards(arg0, 12, phi_a2);
//             }
//         }
//     }
// }

s32 floor_tri_height(f32 x, f32 z, s32 tri, u8 *packed, f32 *out);
void collision_find_floor_no_fallback(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, s32 argC, s32 argD, s32 argE);
f32 collision_object_floor_height(f32, f32, f32);
s32 collision_obj_walls(f32, f32, s32, u8 *, s32, s32);
void water_splash_spawn(u8 *obj, f32 x, f32 z, u8, s32); /* port-b C signature (P150) */
s32 obj_find_visible_target(u8 *, u16 *, s32, s32, s32);
extern u8 g_wall_coll_soft_edges; /* was D_800CC1F3 */
extern s32 g_cur_obj_cmd; /* was D_800D1580 */

// object_move_collide: per-frame floor and wall step of a moving object (P151). Clears the floor height (+0x118) and
// runs cutscene_actor_apply_track; frozen (+0xF8 bit 0x8000: +0x28 = 0 for sub-type 7 else 1) and fixed-height objects (bit
// 0x200000: floor +0x180 = (s16)+0x224) stop there. Otherwise finds the floor below (floor_tri_height on the cached
// triangle when walls are solid for it - bit 2 of its own or of player 0's flags when owned by player 0 - else
// collision_find_floor_no_fallback; collision_object_floor_height for the floor height with bit 8). With wall collision (bit 4 of its own flags, or
// of its owner's for owner 100 + n unless the object is type 0x9A) the move from the old position is clipped by
// collision_obj_walls; if that moved it, it marks +0xF4 0x10000, ends a carry (+0x24E, type 0xC releases via
// water_splash_spawn), and with bit 0x1000 bounces: the heading is mirrored about the wall direction, the speed +0x3C
// scaled (0.9 for state 0x21 and for a state-4 object with +0x103, which also re-aims at the nearest visible
// player via obj_find_visible_target, else 0.3), a bounce sound (+0x2CC via objev_sound_300_1800 when faster than 5), and for state
// 4 gravity 3. Then the floor is looked up again at the new position. Finally a fall deeper than +0x256 * 8 below
// the last floor with +0x255 set (and not stunned) stops it and starts the +0x255 fall effect (aiscript_find_by_kind);
// else +0x180 = the floor height.
/* was func_15058898 */
void obj_update_floor(struct127 *arg0, f32 arg1) {
    u8 *p = (u8 *)arg0;
    f32 floorY;
    f32 x0, z0;
    s32 flags;
    s32 solid;
    s32 wallFlags;
    u16 ang;
    u16 aim;
    u8 owner;

    arg0->unk118 = -10000.0f;
    cutscene_actor_apply_track(arg0, 0, -1);
    flags = arg0->unkF8;
    if (flags & 0x8000) {
        arg0->unk28 = (arg0->unk5 == 7) ? 0.0f : 1.0f;
        return;
    }
    if (flags & 0x200000) {
        arg0->unk180 = (s16)arg0->unk224;
        return;
    }

    solid = flags & 2;
    if (arg0->unk13C >= 100 && arg0->unk13C - 100 == 0) {
        solid = g_objects[arg0->unk13C - 100].unkF8 & 2;
    }
    if (solid != 0 && floor_tri_height(arg0->x_position, arg0->z_position, arg0->unk188, (u8 *)&arg0->unk18C, &floorY) != 0) {
        if (arg0->unkF8 & 8) {
            arg0->unk118 = collision_object_floor_height(arg0->x_position, arg0->y_position, arg0->z_position);
        }
    } else {
        flags = arg0->unkF8;
        collision_find_floor_no_fallback((s32)&arg0->unk188, (s32)&arg0->unk18C, (s32)&floorY, (flags & 8) ? (s32)&arg0->unk118 : 0,
                      (s32)&arg0->unk184, (s32)arg0->pad1A2, arg0->x_position, arg0->y_position, arg0->z_position,
                      arg1, 0, (s32)arg0, (s32)0xC61C4000 /* -10000.0f */, *(s32 *)&arg0->y_position, flags & 0x04000000);
    }

    wallFlags = arg0->unkF8;
    owner = arg0->unk13C;
    if (owner != 0 && arg0->id != 0x9A) {
        wallFlags = g_objects[owner - 100].unkF8;
    }
    if ((wallFlags & 4) && arg0->unk13D == 0 &&
        !(arg0->unk127 == 0xFF && arg0->old_x_position == arg0->x_position && floorY == arg0->old_y_position &&
          arg0->unk28 == 0.0f && arg0->old_z_position == arg0->z_position)) {
        x0 = arg0->x_position;
        z0 = arg0->z_position;
        if (arg0->id == 0x1B || arg0->id == 0x7E) {
            g_wall_coll_soft_edges = 1;
        }
        collision_obj_walls(arg0->old_x_position, arg0->old_y_position, *(s32 *)&arg0->old_z_position, p, 1, 0);
        if (arg0->id == 0x1B || arg0->id == 0x7E) {
            g_wall_coll_soft_edges = 0;
        }
        if (arg0->x_position != x0 || arg0->z_position != z0) {
            arg0->unkF4 |= 0x10000;
            if (arg0->unk24E != 0) {
                if (arg0->id == 0xC) {
                    water_splash_spawn(p, x0, z0, 0xFF, 0);
                }
                arg0->unk232 = arg0->unk24E;
                arg0->unk24E = 0;
                arg0->unk218 = NULL;
                arg0->unk7A = arg0->unk76;
                arg0->unk78 = arg0->unk76;
            }
            if (arg0->unkF8 & 0x1000) {
                ang = math_atan2_u16(arg0->x_position - x0, z0 - arg0->z_position, 0);
                arg0->unk76 = (ang - arg0->unk76) + ang + 0x8000;
                if (arg0->interaction_state == 0x21) {
                    arg0->xz_velocity *= 0.9f;
                } else if (arg0->interaction_state == 0x26) {
                    arg0->xz_velocity *= 0.3f;
                } else if (arg0->interaction_state == 4 && arg0->unk103 != 0) {
                    arg0->xz_velocity *= 0.9f;
                    arg0->unk7A = arg0->unk76;
                    if (obj_find_visible_target(p, &aim, 0, (u8)(arg0->unk124 - 1), 20) != 0xFF) {
                        arg0->unk76 = aim;
                    }
                } else {
                    arg0->xz_velocity *= 0.3f;
                }
                if (arg0->unk2CC != 0 && 5.0f < arg0->xz_velocity) {
                    g_cur_obj_cmd = arg0->unk2CC;
                    objev_sound_300_1800();
                }
                if (arg0->interaction_state == 4) {
                    arg0->unk102 = 0;
                    arg0->gravity = 3.0f;
                }
            }
            collision_find_floor_no_fallback((s32)&arg0->unk188, (s32)&arg0->unk18C, (s32)&floorY, (s32)&arg0->unk118,
                          (s32)&arg0->unk184, (s32)arg0->pad1A2, arg0->x_position, arg0->y_position, arg0->z_position,
                          arg1, 0, (s32)arg0, (s32)0xC61C4000 /* -10000.0f */, *(s32 *)&arg0->y_position, arg0->unkF8 & 0x04000000);
        }
    }

    if (arg0->unk255 != 0 && arg0->stunned == 0 && floorY < arg0->unk180 - (f32)(arg0->unk256 * 8)) {
        arg0->y_velocity = 0.0f;
        arg0->gravity = 0.0f;
        arg0->xz_velocity = 0.0f;
        arg0->unk218 = aiscript_find_by_kind(0, arg0->unk255);
        arg0->unk21C = 0;
        arg0->unk255 = 0;
        return;
    }
    arg0->unk180 = floorY;
}

/* was func_15058EA4 */
void obj_set_gravity_band(struct127 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    if (arg1 < arg0->y_position) {
        arg0->gravity = arg2;
    } else if (arg0->y_position < arg3) {
        arg0->gravity = arg4;
    }
    if (arg5 < arg0->y_velocity) {
        arg0->y_velocity = arg5;
    } else if (arg0->y_velocity < arg6) {
        arg0->y_velocity = arg6;
    }
}

/* was func_15058F24 */
void obj_water_buoyancy(struct127 *arg0, f32 arg1, f32 arg2) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 var_f20;

    var_f20 = arg1;
    temp_f12 = var_f20;
    temp_f16 = 0.5f - var_f20;
    if (var_f20 >= 0.5f) {
        var_f20 -= 0.5f;
    }
    temp_f2 = arg0->y_position;
    temp_f14 = arg0->unk118 + 9.0f;
    if ((temp_f2 < temp_f14) || ((s32) arg0->in_water >= 0x64)) {
        if (arg0->in_water == 0) {
            arg0->y_position = temp_f14;
            arg0->in_water = 0x64;
            arg0->gravity = temp_f16 * -6.0f;
            arg0->y_velocity *= temp_f12;
        } else {
            if ((temp_f14 + 100.0f) < temp_f2) {
                arg0->in_water = 0;
            }
            if (temp_f16 < 0.0f) {
                arg0->gravity = temp_f16 * -6.0f;
            } else {
                temp_f2_2 = arg0->y_position;
                temp_f12_2 = temp_f2_2 - ((temp_f14 + 10.0f) - (120.0f * var_f20));
                if ((fabsf(temp_f12_2) < 2.0f) && (fabsf(arg0->y_velocity) < 2.0f)) {
                    arg0->y_velocity = 0.0f;
                    arg0->gravity = 1.0f;
                    arg0->y_position = temp_f2_2 - (temp_f12_2 * 0.6f);
                } else {
                    temp_f0 = arg0->y_velocity;
                    if (temp_f12_2 > 0.0f) {
                        if (temp_f0 > 0.0f) {
                            arg0->gravity = temp_f16 * 6.0f;
                            arg0->y_velocity = temp_f0 * 0.5f;
                        }
                    } else {
                        temp_f2_3 = temp_f16 * 80.0f;
                        if (temp_f2_3 < temp_f0) {
                            arg0->y_velocity = temp_f2_3;
                        }
                        arg0->gravity = temp_f16 * -6.0f;
                    }
                }
            }
        }
        temp_f2_4 = -100.0f * var_f20;
        if (arg0->y_velocity < temp_f2_4) {
            arg0->y_velocity = temp_f2_4;
        }
    }
}
// NON-MATCHING: besides missing mov.s, its just a few regallocs
// void obj_water_buoyancy(struct127 *arg0, f32 arg1, f32 arg2) {
//     f32 temp_f12;
//     f32 temp_f14;
//     f32 tmp;
//     f32 temp_f16;
//
//     temp_f16 = 0.5f - arg1;
//     if (arg1 >= 0.5f) {
//         arg1 -= 0.5f;
//     }
//     temp_f14 = arg0->unk118 + 9.0f;
//     if ((arg0->y_position < temp_f14) || ((arg0->in_water < 0x64) == 0)) {
//
//         if (0) {};
//
//         if (arg0->in_water == 0) {
//             arg0->y_position = temp_f14;
//             arg0->in_water = (u8)0x64U;
//             arg0->gravity = temp_f16 * -6.0f;
//             arg0->y_velocity *= arg1;
//         } else {
//             if ((temp_f14 + 100.0f) < arg0->y_position) {
//                 arg0->in_water = (u8)0U;
//             }
//             if (temp_f16 < 0.0f) {
//                 arg0->gravity = temp_f16 * -6.0f;
//             } else {
//                 temp_f12 = arg0->y_position - ((temp_f14 + 10.0f) - (120.0f * arg1));
//                 if ((fabsf(temp_f12) < 2.0f) && (fabsf(arg0->y_velocity) < 2.0f)) {
//                     tmp = temp_f12 * D_800994A4;
//                     arg0->gravity = 1.0f;
//                     arg0->y_velocity = 0.0f;
//                     arg0->y_position -= tmp;
//                 } else {
//                     if (temp_f12 > 0.0f) {
//                         if (arg0->y_velocity > 0.0f) {
//                             arg0->gravity = temp_f16 * 6.0f;
//                             arg0->y_velocity *= 0.5f;
//                         }
//                     } else {
//                         temp_f12 = temp_f16 * 80.0f;
//                         if (arg0->y_velocity > temp_f12) {
//                             arg0->y_velocity = temp_f12;
//                         }
//                         arg0->gravity = temp_f16 * -6.0f;
//                     }
//                 }
//             }
//         }
//         temp_f12 = -100.0f * arg1;
//         if (arg0->y_velocity < temp_f12) {
//             arg0->y_velocity = temp_f12;
//         }
//     }
// }

/* was func_15059140 */
void obj_physics_step(struct127 *arg0) {
    f32 sp2C;

    sp2C = 0.5f;
    g_obj_contact_mask = 0;
    if ((arg0->unk13D == 0) || ((s32) arg0->unk21C < 0x10)) {
        if (arg0->unk223 != 8) {
            obj_update_ground_tilt(arg0);
            obj_apply_gravity(arg0);
        }
    }
    obj_contact_pass(arg0, g_cur_obj_index);
    obj_push_out_of_blockers(arg0, arg0->unk1E4);
    if (arg0->id == 8) {
        obj_leash_to_spawn(arg0);
    }
    if (arg0->unk13D < 0x64) {
        obj_update_floor(arg0, arg0->old_y_position);
    }
    if (arg0->unkF4 & 0x40000) {
        if (((arg0->unkF4 & 0x12000) != 0) || (g_obj_contact_mask != 0)) {
            arg0->unk21C = 0U;
        }
    }
    if (arg0->unkB0 != 0) {
        obj_water_buoyancy(arg0, arg0->unkB0 * 0.01f, 1.0f);
    }
    if (arg0->unkF8 & 0x20000) {
        obj_follow_water_level(arg0);
    }
    if (arg0->in_water != 0) {
        obj_apply_level_current(arg0);
    }
    if (arg0->id == 0xA) {
        arg0->unk180 = -5000.0f;
    }
    if ((arg0->unkF8 & 0x180000) != 0) {
        obj_floor_push_turn(arg0);
    }
    obj_land_on_floor(arg0, arg0->unk180);
    if (((arg0->unkF4 & 0x1000) != 0) && (arg0->unk28 < 0.2f)) {
        obj_walk_update(arg0);
    }
    if (arg0->unkF8 & 0x80000) {
        sp2C = 0.15f;
    }
    move_xz_towards(0, 0, sp2C, &arg0->unk164, &arg0->unk168);
    if (arg0->unkD0 != 0) {
        attack_hit_test(arg0, g_cur_obj_index);
    }
    if (arg0->unk13D == 0) {
        if (D_800BE9A0 >= arg0->unk10F) {
            arg0->unk10F = 0U;
        } else {
            arg0->unk10F -= D_800BE9A0;
        }
    }
    if (arg0->unk107 != 0) {
        arg0->unk107 -= 1;
    }
    if (arg0->immune != 0xFF) {
        if (D_800BE9A0 >= arg0->immune) {
            arg0->immune = 0U;
        } else {
            arg0->immune -= D_800BE9A0;
        }
    }
}

/* was func_150593C4 */
void obj_blend_push_velocity(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    vec_from_yaw_pitch(arg1, arg2, 0, &sp2C, &sp28, &sp24);
    arg0->unk16C += (sp2C - arg0->unk16C) * arg3;
    arg0->unk170 += (sp28 - arg0->unk170) * arg3;
}

/* was func_15059444 */
void obj_apply_level_current(struct127 *arg0) {
    s32 sp1C;
    s32 phi_v0;
    s32 tmp;

    sp1C = -1;

    switch (g_level_id) {
        case 4:
            obj_blend_push_velocity(arg0, 0x4000, 50.0f, 0.05999999865889549f);
            break;
        case 6:
            sp1C = setup_entry_find_by_id(28);
            break;
        case 41:
            if (trigger_test_player(g_cur_obj_index, 0x4028) == 0) {
                phi_v0 = 12;
            } else if (trigger_test_player(g_cur_obj_index, 0x400E) == 0) {
                phi_v0 = 10;
            } else if (trigger_test_player(g_cur_obj_index, 0x400D) == 0) {
                phi_v0 = 9;
            } else {
                phi_v0 = 6;
            }
            sp1C = setup_entry_find_by_id(phi_v0);
            // FIXME: fakematch to force regalloc
            dummy_label_858530:;
            break;
        case 43:
            sp1C = setup_entry_find_by_id(18);
            break;
        case 65:
            if (trigger_test_player(g_cur_obj_index, 0x401F) == 0) {
                phi_v0 = 27;
            } else {
                phi_v0 = 26;
            }
            sp1C = setup_entry_find_by_id(phi_v0);
            break;
    }

    if (sp1C != -1) {
        obj_follow_path(arg0, sp1C);
    }
}

/* was func_1505959C */
void obj_attach_to_carrier(struct127 *arg0, s32 arg1) {
    struct252 *temp_v0;
    s32 *temp_v1;
    s32 phi_v1;

    arg0->unkF8 &= 0xFF7FFFFF;
    arg0->unk13D = arg1 + 100;
    arg0->unk21C = 0;
    arg0->gravity = 4.0f;
    arg0->unk25C &= ~8;

    g_objects[arg1].unk83 = 0xFF;
    g_objects[arg1].disable_run = 0xFF;
    phi_v1 = 0;
    if (arg0->id == 0x57) {
        phi_v1 = 1;
    }
    if (g_objects[arg1].id == 0x9B) {
        phi_v1 = 2;
    }
    if (arg0->id == 0x5E) {
        phi_v1 = 3;
    }
    if (arg0->id == 0x3C) {
        phi_v1 = 4;
        g_objects[arg1].unk13C = (u8)0;
        g_objects[arg1].unk76 = math_atan2_u16(arg0->x_position - g_objects[arg1].x_position, g_objects[arg1].z_position - arg0->z_position, 0);
    }
    if (arg0->id == 0x89) {
        phi_v1 = 5;
    }
    obj_start_anim(&g_objects[arg1], g_carry_anim_ids[phi_v1], g_carry_anim_speeds[phi_v1], 0.0f, 0.0f, 0.0f, 0);
    arg0->stunned = 0xFE;
    arg0->unk105 = 0;
    arg0->unk106 = obj_find_reaction_row(g_carry_reaction_rows[phi_v1], arg0);
    arg0->unk84.uh = 0xFFFF;
    obj_hit_reaction_advance(g_cur_obj_index, arg0);
    temp_v1 = (s32*)D_800D1588[arg0->id];
    if (temp_v1 != 0) {
        temp_v0 = (struct252 *)*(temp_v1 - 2);
        if ((temp_v0 != 0) && ((temp_v0[arg0->unk106].unk15 & 2) != 0)) {
            arg0->unk7A = g_objects[arg1].unk7A;
        }
        if ((temp_v0 == 0) || ((temp_v0[arg0->unk106].unk15 & 1) == 0)) {
            arg0->unk13E = (arg0->unk7A - g_objects[arg1].unk7A) >> 8;
        } else {
            arg0->unk13E = 0;
        }
    } else {
        arg0->unk13E = (arg0->unk7A - g_objects[arg1].unk7A) >> 8;
    }
}

/* was func_150597FC */
void obj_find_carrier(struct127 *arg0)
{
  s32 var_a1;
  struct126 *temp_a2;
  s32 new_var;
  struct127 *temp_v0;
  struct127 *temp_v0_2;
  int temp_v1;
  new_var = g_obj_contact_mask;
  var_a1 = 0;
  // fakematch: s32 blk_t; block-local declarations below are basic-block boundaries (blkvar, s69)
  if (g_player_count > 0)
  {
    s32 blk_t;
    loop_2:
    if ((((((!((1 << var_a1) & new_var)) || ((temp_v0 = &g_objects[var_a1], temp_v0->unk13C != 0))) || (temp_v0->disable_run != 0)) || (temp_v0->interaction_state != 1)) || (temp_v0->stunned != 0)) || (temp_v0->unk127 == 0xFF))
    {
      s32 blk_t;
      var_a1 += 1;
      if (var_a1 < g_player_count)
      {
        s32 blk_t;
        if (1) { } // fakematch: permuter empty if (BB split)
        goto loop_2;
      }
      if (!arg0->unk28) { } // fakematch: permuter empty if (BB split)
    }

  }
  if (var_a1 != g_player_count)
  {
    s32 blk_t;
    temp_v0_2 = &g_objects[var_a1];
    if (temp_v0_2->unk13C == 0)
    {
      s32 blk_t;
      temp_a2 = temp_v0_2->unk31C;
      if ((((((((((temp_a2->unk27 == 0) && (temp_v0_2->health != 0)) && (arg0->unk13D == 0)) && (((arg0->stunned != 0) || (arg0->unk25C & 0x1000)) || (arg0->id == 0x57))) && (arg0->unk28 == 0.0f)) && (temp_v0_2->unk28 == 0.0f)) && (arg0->unk25C & 8)) && (temp_a2->unk19B == 0)) && (((temp_v1 = arg0->id, temp_v1 != 0xA9)) || ((*((u8 *) (((u8 *) temp_v0_2) + 0x128))) == 0))) && ((temp_v1 != 0xA8) || ((*((u8 *) (((u8 *) temp_v0_2) + 0x128))) != 0)))
      {
        s32 blk_t;
        temp_v0_2->unk13C = g_cur_obj_index + 0x64;
        temp_v0_2->xz_velocity = 0.0f;
        *((s16 *) (((u8 *) temp_a2) + 0x18)) = 0;
        obj_attach_to_carrier(arg0, var_a1);
      }
    }
  }
}
/* was func_150599C8 */
u8 obj_turn_towards(struct127 *arg0, u8 arg1, u16 arg2) {
    s16 temp_a2;
    s16 temp_t3;
    s16 temp_v1;
    s16 var_a3;
    s32 temp_lo;
    s32 var_v0;
    u16 temp_t0;
    u16 temp_t1;
    u16 temp_t2;

    temp_t0 = arg0->unk7A;
    temp_t1 = arg0->unk1EA;
    var_a3 = (arg2 & 0xFFFF) - temp_t0;
    var_v0 = (s32) ((((arg1 & 0xFF) << 8) + arg0->unk1E8) * D_800CC264) / 100;
    if (temp_t1 != 0) {
        temp_t2 = arg0->unk1EC;
        temp_lo = (s32) (temp_t1 * D_800CC264) / 100;
        temp_a2 = temp_t2 + temp_lo;
        temp_t3 = temp_t2 - temp_lo;
        if (temp_a2 < var_a3) {
            var_a3 = temp_a2;
        }
        if (var_a3 < temp_t3) {
            var_a3 = temp_t3;
        }
    }
    temp_v1 = var_a3;
    if (var_a3 < 0) {
        var_a3 ^= 0xFFFF;
    }
    if (var_a3 < var_v0) {
        var_v0 = (s32) var_a3;
    }
    if (!(arg0->unkF4 & 1) && (arg0->unk80 != 0)) {
        if (temp_v1 < 0) {
            arg0->unk7A = temp_t0 - var_v0;
        } else {
            arg0->unk7A = temp_t0 + var_v0;
        }
    }
    return (var_a3 >> 8) & 0xFF;
}
/* was func_15059B54 */
s32 obj_turn_to_target_yaw(struct127 *arg0, u16 arg1) {
    s16 temp_a1_2;
    s16 temp_t0;
    s16 temp_t2;
    s16 temp_v0;
    s16 var_a2;
    s16 var_v0;
    s32 temp_lo;
    u16 temp_a1;
    u16 temp_t1;
    u16 temp_v1;

    temp_v1 = arg0->unk76;
    temp_v0 = arg0->unk78 - temp_v1;
    var_v0 = temp_v0;
    var_a2 = temp_v0;
    if (temp_v0 < 0) {
        var_a2 = temp_v0 ^ 0xFFFF;
    }
    temp_a1 = arg0->unk1EA;
    if (temp_a1 != 0) {
        temp_t1 = arg0->unk1EC;
        temp_lo = (s32) (temp_a1 * D_800CC264) / 100;
        temp_t0 = temp_t1 + temp_lo;
        temp_t2 = temp_t1 - temp_lo;
        if (temp_t0 < var_v0) {
            var_v0 = temp_t0;
        }
        if (var_v0 < temp_t2) {
            var_v0 = temp_t2;
        }
    }
    temp_a1_2 = var_v0;
    if (var_v0 < 0) {
        var_v0 ^= 0xFFFF;
    }
    if (var_v0 < (s32) arg1) {
        arg1 = (u16) var_v0;
    }
    if (!(arg0->unkF4 & 1)) {
        if (temp_a1_2 < 0) {
            arg0->unk76 = temp_v1 - arg1;
            arg0->unk1EC = (u16) -(s32) arg1;
        } else {
            arg0->unk76 = temp_v1 + arg1;
            arg0->unk1EC = arg1;
        }
    }
    return (var_a2 >> 8) & 0xFF;
}
// NON-MATCHING: 90% there, missing an s16 cast
// u8 obj_turn_to_target_yaw(struct127 *arg0, u16 arg1) {
//     s16 temp_t8;
//     s16 temp_t8_2;
//     s16 temp_t2;
//     s32 temp_lo;
//     s16 phi_a2;
//
//     temp_t8 = arg0->unk78 - arg0->unk76;
//     phi_a2 = temp_t8;
//     if (phi_a2 < 0) {
//         phi_a2 = phi_a2 ^ 0xFFFF;
//     }
//     if (arg0->unk1EA != 0) {
//         temp_lo = (s32) (arg0->unk1EA * D_800CC264) / 0x64;
//         temp_t8_2 = arg0->unk1EC + temp_lo;
//         temp_t2 = arg0->unk1EC - temp_lo;
//         if (temp_t8_2 < temp_t8) {
//             temp_t8 = temp_t8_2;
//         }
//         if (temp_t8 < temp_t2) {
//             temp_t8 = temp_t2;
//         }
//     }
//
//     if (temp_t8 < 0) {
//         temp_t8 ^= 0xFFFF;
//     }
//     if (temp_t8 < arg1) {
//         arg1 = temp_t8;
//     }
//     if ((arg0->unkF4 & 1) == 0) {
//         if (temp_t8 < 0) {
//             arg0->unk76 -= arg1;
//             arg0->unk1EC = -arg1;
//         } else {
//             arg0->unk76 += arg1;
//             arg0->unk1EC = arg1;
//         }
//     }
//     return phi_a2 >> 8;
// }

extern f32 D_800CC630;
extern f32 D_800CC634;
extern f32 D_800CC638;
extern s32 g_obj_update_counter; /* was D_800D1968 */

/* was func_15059C84 */
void obj_update_ground_tilt(struct127 *rec) {
    u8 *arg0 = (u8 *) rec;
    f32 tri[9];
    s32 i;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    u16 sp76;
    s32 sp74;
    s32 sp50;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f6;
    f32 temp_f8;
    f32 var_f12;
    s16 var_t5;
    u16 temp_t5;
    u8 temp_v0;
    u8 temp_v0_3;
    u8 temp_v0_5;
    u8 *temp_v0_2;
    u8 *temp_v0_4;
    u8 *temp_v1;
    u8 *var_v0;
    u8 *var_v1;

    var_f12 = (*(f32 *)((u8 *)arg0 + 0x3C));
    sp76 = (*(u16 *)((u8 *)arg0 + 0x76));
    if (g_obj_update_counter != 1) {
        temp_v0 = (*(u8 *)((u8 *)arg0 + 0x1FC));
        if (temp_v0 & 8) {
            (*(u8 *)((u8 *)arg0 + 0x1FC)) = (u8) (temp_v0 & 0xFFF7);
            return;
        }
        if ((*(u8 *)((u8 *)arg0 + 0x127)) != 0xFF) {
            temp_v0_2 = (*(u8 **)((u8 *)arg0 + 0x31C));
            if ((*(s16 *)((u8 *)temp_v0_2 + 0x46)) > 0) {
                temp_t5 = sp76 + (*(u16 *)((u8 *)temp_v0_2 + 0x10));
                sp76 = temp_t5;
                (*(u16 *)((u8 *)arg0 + 0x7A)) = temp_t5;
            }
        }
        if (((*(f32 *)((u8 *)arg0 + 0x3C)) < 1.0f) && ((*(f32 *)((u8 *)arg0 + 0x3C)) >= 0.0f) && !((*(u8 *)((u8 *)arg0 + 0x1FC)) & 1)) {
            temp_v0_3 = (*(u8 *)((u8 *)arg0 + 0x7E));
            if ((s32) temp_v0_3 < 0xFA) {
                (*(u8 *)((u8 *)arg0 + 0x7E)) = (u8) (temp_v0_3 + 1);
            }
            if (((*(f32 *)((u8 *)arg0 + 0x164)) == 0.0f) && ((*(f32 *)((u8 *)arg0 + 0x168)) == 0.0f) && ((*(f32 *)((u8 *)arg0 + 0x16C)) == 0.0f) && ((*(f32 *)((u8 *)arg0 + 0x170)) == 0.0f)) {
                (*(f32 *)((u8 *)arg0 + 0x1F4)) = 0.0f;
                return;
            }
            goto block_17;
        }
        (*(u8 *)((u8 *)arg0 + 0x7E)) = 0U;
block_17:
        if ((((*(u8 *)((u8 *)arg0 + 0xAD)) != 0) && ((temp_v0_4 = (*(u8 **)((u8 *)arg0 + 0x31C)), (temp_v0_4 == NULL)) || ((*(u8 *)((u8 *)temp_v0_4 + 0x21)) == 0))) || ((*(u16 *)((u8 *)arg0 + 0x22C)) & 8)) {
            sp84 = (*(f32 *)((u8 *)arg0 + 0xB8));
            if (sp84 > 90.0f) {
                sp84 = 90.0f;
            } else if (sp84 < -90.0f) {
                sp84 = -90.0f;
            }
        } else {
            sp84 = 0.0f;
        }
        temp_v0_5 = (*(u8 *)((u8 *)arg0 + 0x1FC));
        if (temp_v0_5 & 1) {
            (*(u8 *)((u8 *)arg0 + 0x1FC)) = (u8) (temp_v0_5 & 0xFFFE);
            if (*g_obj_time_step != 0.0f) {
                var_f12 = 2.0f * (((*(f32 *)((u8 *)arg0 + 0x1F4)) * (*(f32 *)((u8 *)arg0 + 0x14C))) / *g_obj_time_step);
            }
            (*(f32 *)((u8 *)arg0 + 0x1F4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C));
            sp76 = (*(u16 *)((u8 *)arg0 + 0x7A));
        }
        (*(f32 *)((u8 *)arg0 + 0x1F4)) = var_f12;
        vec_from_yaw_pitch(sp76, var_f12, sp84, &sp84, &sp80, &sp7C);
        sp84 += (*(f32 *)((u8 *)arg0 + 0x164)) + (*(f32 *)((u8 *)arg0 + 0x16C));
        sp80 += (*(f32 *)((u8 *)arg0 + 0x168)) + (*(f32 *)((u8 *)arg0 + 0x170));
        if ((*(u8 *)((u8 *)arg0 + 0xAD)) == 0xA) {
            sp7C = 0.0f;
        }
        if ((((*(s32 *)((u8 *)arg0 + 0)) != 1) || ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x4F)) == 0)) && ((*(f32 *)((u8 *)arg0 + 0x28)) <= 0.0f) && ((*(u8 *)((u8 *)arg0 + 0xAD)) == 0)) {
            if (!((*(u16 *)((u8 *)arg0 + 0x22C)) & 8)) {
                for (i = 0; i < 9; i++) {
                    tri[i] = (f32) (*(s16 *)((u8 *)arg0 + 0x18C + i * 2));
                }
                /* P77: the nine floats as arguments (the asm passes them in a0..a3 and the stack; the old call
                 * passed one 36-byte struct, a single argument in the port) */
                tri_compute_plane(*(s32 *)&tri[0], tri[1], tri[2], tri[3], tri[4], tri[5], tri[6], tri[7], tri[8]);
                if ((D_800CC634 != 0.0f) && ((temp_f12 = ((-D_800CC630 * sp84) - (D_800CC638 * sp80)) / D_800CC634, (temp_f12 > 4.0f)) || ((*(s32 *)((u8 *)arg0 + 0)) != 1) || ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x4E)) != 2))) {
                    temp_f14 = (sp84 * sp84) + (sp80 * sp80);
                    temp_f2 = sqrtf(temp_f14 + (temp_f12 * temp_f12));
                    if (temp_f2 != 0.0f) {
                        temp_f0 = sqrtf(temp_f14);
                        sp84 = (sp84 * temp_f0) / temp_f2;
                        sp7C = (temp_f12 * temp_f0) / temp_f2;
                        sp80 = (sp80 * temp_f0) / temp_f2;
                    }
                }
            }
        }
        temp_f8 = sp84 * *g_obj_time_step;
        temp_f6 = sp80 * *g_obj_time_step;
        temp_f10 = sp7C * *g_obj_time_step;
        sp84 = temp_f8;
        sp80 = temp_f6;
        sp7C = temp_f10;
        (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) + temp_f8);
        (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x1C)) + temp_f6);
        (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x18)) + temp_f10);
    }
}
extern f32 g_yaw_pitch_deg_to_rad; /* was D_80099880 */
extern f32 g_yaw_u16_to_rad; /* was D_80099884 */
/* was func_1505A184 */
void vec_from_yaw_pitch(u16 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    f32 var_f18;
    f32 temp_f20_2;
    f32 temp_f20;
    f32 temp_f16;
    f32 temp_f12_2;
    f32 temp_f12;
    f32 sp20;
    f32 sp2C;

    temp_f20 = arg1 * 0.5f;
    temp_f12 = arg2 * g_yaw_pitch_deg_to_rad;
    arg2 = temp_f12;
    *arg5 = fast_sinf(temp_f12) * -temp_f20;
    temp_f20_2 = fast_cosf(arg2) * temp_f20;
    var_f18 = (f32) arg0;
    if ((s32) arg0 < 0) {
        var_f18 += 4294967296.0f;
    }
    temp_f12_2 = var_f18 * g_yaw_u16_to_rad;
    sp20 = temp_f12_2;
    sp2C = fast_cosf(temp_f12_2);
    temp_f16 = -fast_sinf(sp20);
    *arg3 = sp2C * temp_f20_2;
    *arg4 = temp_f16 * temp_f20_2;
}
/* was func_1505A250 */
void move_xz_towards(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4) {
    f32 sp4;
    f32 sp0;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;

    temp_f16 = *arg3;
    temp_f2 = arg0 - temp_f16;
    temp_f18 = arg1 - *arg4;
    if ((temp_f2 != 0.0f) || (temp_f18 != 0.0f)) {
        temp_f10 = arg2 * *g_obj_time_step;
        temp_f0 = sqrtf((temp_f2 * temp_f2) + (temp_f18 * temp_f18));
        arg2 = temp_f10;
        sp4 = temp_f0;
        sp0 = fabsf((temp_f2 / temp_f0) * temp_f10);
        temp_f0_2 = fabsf((temp_f18 / sp4) * temp_f10);
        if (temp_f2 >= 0.0f) {
            *arg3 = temp_f16 + sp0;
            if (arg0 < *arg3) {
                goto block_6;
            }
        } else {
            *arg3 = temp_f16 - sp0;
            if (*arg3 < arg0) {
block_6:
                *arg3 = arg0;
            }
        }
        if (temp_f18 >= 0.0f) {
            *arg4 += temp_f0_2;
            if (arg1 < *arg4) {
                goto block_11;
            }
        } else {
            *arg4 -= temp_f0_2;
            if (*arg4 < arg1) {
block_11:
                *arg4 = arg1;
            }
        }
    }
}
extern f32 g_speed_water_factor; /* was D_80099888 */
extern f32 g_speed_flag40_value; /* was D_8009988C */
extern f32 g_speed_flags_factor; /* was D_80099890 */
extern f32 g_speed_ae_factor; /* was D_80099894 */
extern f32 g_speed_near_max_factor; /* was D_80099898 */
extern u8 D_800CC69C;

/* was func_1505A3A8 */
f32 obj_approach_speed(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4) {
    f32 var_f12;
    f32 var_f14;
    f32 var_f20;
    u8 temp_v0;

    var_f12 = arg0;
    var_f20 = arg2 * *g_obj_time_step;
    var_f14 = arg3 * *g_obj_time_step;
    if ((D_800CC69C != 0) && (arg1->unk28 < 5.0f) && (arg1->interaction_state != 0x1E)) {
        var_f20 = 0.0f;
    }
    if (arg1->interaction_state == 1) {
        if (arg1->in_water != 0) {
            var_f20 = 2.0f;
            var_f14 *= g_speed_water_factor;
        }
        if (arg1->unkA8 != 0) {
            var_f14 *= 0.25f;
        }
        temp_v0 = arg1->unk81;
        if (temp_v0 != 0) {
            if (temp_v0 & 0x40) {
                if (temp_v0 & 0x20) {
                    var_f14 = 0.0f;
                } else {
                    var_f14 = g_speed_flag40_value;
                }
            } else {
                var_f14 *= g_speed_flags_factor;
                if ((s32) arg4 >= 0x2E) {
                    var_f20 *= 0.5f;
                }
                if ((s32) arg4 >= 0x5B) {
                    var_f12 *= 0.5f;
                }
            }
        }
        if (arg1->unkAE != 0) {
            var_f14 *= g_speed_ae_factor;
        }
    }
    if (var_f12 < 0.0f) {
        if (arg1->xz_velocity > 0.0f) {
            var_f14 += var_f20;
        } else {
            var_f14 = var_f20;
        }
    } else if (arg1->xz_velocity < 0.0f) {
        var_f20 += var_f14;
    }
    if (var_f12 < arg1->xz_velocity) {
        arg1->xz_velocity -= var_f14;
        if (arg1->xz_velocity < var_f12) {
            goto block_32;
        }
    } else {
        if ((var_f12 - 1.0f) < arg1->xz_velocity) {
            var_f20 *= g_speed_near_max_factor;
        }
        arg1->xz_velocity += var_f20;
        if (var_f12 < arg1->xz_velocity) {
block_32:
            arg1->xz_velocity = var_f12;
        }
    }
    return arg1->xz_velocity;
}
/* was func_1505A5CC */
f32 pad_stick_speed(struct49 *arg0) {
    f32 x, y;
    f32 ret;

    // regalloc nonsense
    ret = arg0->unk2;
    x = ret;
    y = arg0->unk3;

    x = sqrtf(x*x + y*y) * 0.6f;
    ret = x;

    if (ret > 35.0f) {
        ret = 35.0f;
    }

    return ret;
}

/* was func_1505A630 */
u16 math_atan2_u16(f32 arg0, f32 arg1, s32 arg2) {
    return ((u16) (u32) (math_atan2f(-arg0, arg1) * 10430.378f)) + 16384;
}

/* was func_1505A6F8 */
f32 obj_dist_xz(struct127 *arg0, struct127 *arg1) {
    f32 x, z;

    x = arg0->x_position - arg1->x_position;
    x *= x;
    z = arg0->z_position - arg1->z_position;
    z *= z;
    return sqrtf(x + z);
}

// distance between two objects?
/* was func_1505A72C */
f32 obj_dist_3d(struct127 *arg0, struct127 *arg1) {
    f32 x, y, z;

    x = arg0->x_position - arg1->x_position;
    x *= x;
    z = arg0->z_position - arg1->z_position;
    z *= z;
    y = arg0->y_position - arg1->y_position;
    y *= y;
    return sqrtf(x + z + y);
}

/* P50: gravity. Airborne (+0x28 height != 0 or rising): g_obj_time_step / 0.1 steps of vy -= g * 0.1, y += vy * 0.05
 * (IDO unrolled this loop by 4); on the ground: one step of the whole frame. vy is clamped at -500. */
/* was func_1505A770 */
void obj_apply_gravity(struct127 *rec) {
    u8 *arg0 = (u8 *) rec;
    f32 g;
    s32 n;
    s32 i;
    f32 v;

    if (((*(f32 *)(arg0 + 0x28)) != 0.0f) || ((*(f32 *)(arg0 + 0x20)) > 0.0f)) {
        g = (*(f32 *)(arg0 + 0x24)) * 0.1f;
        n = (s32) (*g_obj_time_step / 0.1f);
        for (i = 0; i < n; i++) {
            *(f32 *)(arg0 + 0x20) = *(f32 *)(arg0 + 0x20) - g;
            *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x18) + (*(f32 *)(arg0 + 0x20) * 0.05f);
        }
        if ((*(f32 *)(arg0 + 0x20)) < -500.0f) {
            *(f32 *)(arg0 + 0x20) = -500.0f;
        }
    } else {
        *(f32 *)(arg0 + 0x20) = *(f32 *)(arg0 + 0x20) - ((*(f32 *)(arg0 + 0x24)) * *g_obj_time_step);
        v = *(f32 *)(arg0 + 0x20);
        *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x18) + (v * *g_obj_time_step * 0.5f);
        if (v < -500.0f) {
            *(f32 *)(arg0 + 0x20) = -500.0f;
        }
    }
}
// a big one, but could be ok
void player_start_shrink_death(struct127 *);
s32 player_hit_reaction(struct127 *, s32);
void object_break_effects_floor(struct127 *, s32, s32);
extern u8 D_800CC69C;

/* was func_1505A9AC */
void obj_ctrl_floor_contact(struct127 *arg0, f32 arg1) {
    u8 sp6F;
    u8 sp6E;
    u8 sp63;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    f32 sp50;
    s32 sp4C;
    u8 sp4B;
    s32 sp3C;
    s32 *temp_v0_4;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f2;
    f32 var_f12;
    f32 var_f2;
    f32 var_f2_2;
    s32 temp_t3;
    s32 temp_t5;
    s32 temp_v1;
    s32 temp_v1_4;
    s32 var_a3;
    s32 var_t0;
    s32 var_t0_3;
    s32 var_t1;
    s32 var_t2;
    s32 var_v1;
    struct126 *temp_v0;
    struct126 *temp_v0_5;
    u16 temp_v0_8;
    u8 temp_a0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_6;
    u8 temp_v0_7;
    u8 temp_v0_9;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 var_t0_2;

    sp6F = 0;
    sp6E = 1;
    var_f2 = arg0->y_position - arg1;
    if (arg0->unk31C->pad4F[0] != 0) {
        if (var_f2 < 0.0f) {
            arg0->unk1CC = arg1;
            var_f2 = 0.0f;
        }
        arg0->unk28 = var_f2;
        temp_f2 = arg0->y_position - (arg0->unk118 - 34.0f);
        if (temp_f2 < 70.0f) {
            temp_f0 = arg0->y_velocity;
            if (temp_f0 < 18.0f) {
                if (temp_f0 > -25.0f) {
                    arg0->unk31C->pad4F[0] = 2;
                }
                if (temp_f2 < 0.0f) {
                    if (arg0->y_velocity < -12.0f) {
                        arg0->unk81 = 0;
                        if (arg0->y_velocity < -25.0f) {
                            arg0->y_velocity = -30.0f;
                            arg0->xz_velocity *= 0.4f;
                        }
                        arg0->y_velocity *= 0.85f;
                    }
                    arg0->gravity = -1.9f;
                    return;
                }
                if ((arg0->y_velocity > 10.0f) && (arg0->y_velocity < 25.0f)) {
                    arg0->y_velocity = 10.0f;
                }
                arg0->gravity = 2.2f;
            }
        }
    } else {
        if (arg0->unk65 != 0) {
            if (var_f2 < 0.0f) {
                arg0->unk1CC = arg1;
                var_f2 = 0.0f;
                arg0->y_position = arg1;
            }
            goto block_172;
        }
        if (var_f2 < 0.0f) {
            sp63 = 0;
            if (arg0->in_water == 0) {
                arg0->unk137 = 0;
                arg0->gravity = 5.0f;
            }
            if (arg0->in_water == 0) {
                arg0->unk31C->unk55 = 4;
            }
            if (arg0->unk28 > 0.0f) {
                arg0->unk31C->pad4F[2] = 1;
                arg0->unk31C->unk31 = 0;
            }
            arg0->unk100 &= 0xFD;
            if ((((u32) arg0->unk184 >> 0xC) & 0xF) == 1) {
                if (g_level_id == 0x14) {
                    object_break_effects_floor(arg0, 0xFF, 1);
                    player_hit_reaction(arg0, 8);
                    return;
                }
                player_start_shrink_death(arg0);
                return;
            }
            if (g_level_id == 0x43) {
                var_f2_2 = 1000.0f;
            } else {
                var_f2_2 = 600.0f * 3.0f;
            }
            if ((arg0->unk1CC - arg0->y_position) > 600.0f) {
                temp_v0 = arg0->unk31C;
                if ((temp_v0->unk120 == 0) && (temp_v0->unk78 != 1)) {
                    var_f12 = 1.3f;
                    temp_v0->unk95 = 0;
                    var_t2 = 0;
                    arg0->unk31C->pad4F[2] = 2;
                    var_t1 = 0;
                    var_a3 = 0;
                    var_t0 = 0x30;
                    if (g_level_id != 0x29) {
                        temp_v1 = arg0->unk184;
                        if (((((u32) temp_v1 >> 0xC) & 0xF) == 2) || ((temp_v1 == 0x13) & 0x1F)) {
                            sp58 = 0xC8;
                            sp54 = 0;
                            sp5C = 0;
                            obj_sfx_play_simple(0x1B8, arg0);
                            var_f12 = 1.0f;
                            var_t0 = 0xC8;
                            var_t1 = 0;
                            var_t2 = 0;
                        } else {
                            temp_v0_2 = arg0->health;
                            if (temp_v0_2 != 0) {
                                if (arg0->unk31C->unk78 == 0x21) {
                                    var_t1 = 1;
                                }
                                if (arg0->id == 0x75) {
                                    var_t1 |= 2;
                                }
                            }
                            temp_f0_2 = arg0->unk1CC;
                            if ((temp_f0_2 < 90000.0f) && (var_f2_2 < (temp_f0_2 - arg0->y_position))) {
                                if (!(var_t1 & 2)) {
                                    arg0->health = 0;
                                    if ((temp_v1 & 0x1F) != 0xE) {
                                        sp4C = 0;
                                        sp58 = 0x30;
                                        sp54 = var_t1;
                                        sp50 = 1.3f;
                                        object_break_effects_floor(arg0, 0xFF, 1);
                                        var_a3 = 0;
                                        var_t0 = 0x30;
                                        var_f12 = 1.3f;
                                        var_t2 = 1;
                                    }
                                } else {
                                    var_a3 = 1;
                                    if (temp_v0_2 != 0) {
                                        arg0->health = temp_v0_2 - 1;
                                    }
                                }
                            }
                            if (var_t1 == 0) {
                                temp_v0_3 = arg0->health;
                                arg0->stunned = 8;
                                if (temp_v0_3 != 0) {
                                    arg0->health = temp_v0_3 - 1;
                                }
                            }
                            if (var_t1 & 1) {
                                var_f12 = 1.0f;
                                var_t0 = 0x19D;
                            } else if (var_t1 & 2) {
                                if (var_a3 != 0) {
                                    goto block_64;
                                }
                                var_t0 = 9;
                            } else if (arg0->health != 0) {
block_64:
                                var_t0 = 0x27;
                            }
                            if ((var_t0 == 0x27) && (arg0->unk31C->unk78 == 0x25)) {
                                var_t0 = 0x1AA;
                            }
                        }
                    }
                    if (var_t2 == 0) {
                        sp54 = var_t1;
                        sp5C = var_t2;
                        obj_start_anim(arg0, var_t0 & 0xFFFF, var_f12, 2.0f, 6.0f, 0.0f, 0);
                    }
                    arg0->stunned = 0;
                    arg0->unk83 = 0xFF;
                    arg0->disable_run = 0xFE;
                    if (var_t1 != 0) {
                        arg0->unk228 = 0xA;
                    } else {
                        arg0->unk228 = 0x1E;
                    }
                    arg0->unk28 = 0.0f;
                    arg0->unk100 &= 0x8B;
                    arg0->unk76 = arg0->unk7A;
                    arg0->unkA9 = 0;
                    arg0->y_position = arg1;
                    arg0->y_velocity = -4.0f;
                    arg0->unk1CC = arg1;
                    if (var_t2 == 0) {
                        fx_dust_puff_behind_obj((s32) g_cur_obj_index, 0, 0x1F, 0, 0x199, 4, 0xAA, 0xFFU, 0);
                        return;
                    }
                    player_hit_reaction(arg0, 8);
                    return;
                }
            }
            arg0->unk1CC = arg1;
            if (arg0->in_water != 0) {
                arg0->unk28 = 0.0f;
                arg0->y_position = arg1;
                return;
            }
            if (arg0->stunned == 0) {
                if ((arg0->unk7F == 0) && (arg0->xz_velocity < 9.0f)) {
                    arg0->unk76 = arg0->unk7A;
                }
                temp_t5 = ((s32) (arg0->unk76 - arg0->unk7A) >> 8) & 0xFF;
                var_v1 = temp_t5;
                if (temp_t5 >= 0x81) {
                    var_v1 = -temp_t5 & 0xFF;
                }
                if ((arg0->unk7F == 0) && (var_v1 < 0x50)) {
                    arg0->unk7F = 0xA;
                }
                if (arg0->unkA9 == 2) {
                    temp_v1_2 = arg0->unk274;
                    var_t0_2 = 0;
                    if (temp_v1_2 != 0) {
                        temp_v0_4 = &(*(s32 *)((u8 *)(&g_objects[temp_v1_2]) + -0x32C));
                        temp_a0 = (*(u8 *)((u8 *)temp_v0_4 + 0x24C));
                        if (temp_a0 != 0) {
                            var_t0_2 = 1;
                            (*(s32 *)((u8 *)temp_v0_4 + 0x218)) = 0;
                            (*(u8 *)((u8 *)temp_v0_4 + 0x232)) = temp_a0;
                        }
                    }
                    arg0->xz_velocity = 0.0f;
                    arg0->unk83 = 0xFF;
                    sp63 = 0xFF;
                    sp4B = var_t0_2;
                    obj_start_anim(arg0, 0x4BU, 1.0f, 2.0f, 0.0f, 0.0f, 0);
                    if ((s32) g_cur_obj_index < 4) {
                        arg0->unk31C->unk57 = 1;
                    }
                    if (var_t0_2 == 0) {
                        obj_sfx_play_alt(0x19, arg0);
                    }
                } else {
                    var_t0_3 = 0;
                    if ((s32) arg0->unk28 > 0) {
                        temp_v0_5 = arg0->unk31C;
                        temp_v1_3 = temp_v0_5->unk11A;
                        if ((temp_v1_3 != 1) && (temp_v1_3 != 3) && (temp_v0_5->unk4E == 0) && ((temp_v0_6 = arg0->unk100, temp_v1_4 = temp_v0_6 & 0x10, (temp_v1_4 != 0)) || (!(temp_v0_6 & 8) && (((arg0->unk44 == 0.0f) && (arg0->unkA8 == 0)) || (temp_v0_6 & 4))))) {
                            if (temp_v1_4 != 0) {
                                arg0->unk83 = 8;
                                if (!(temp_v0_6 & 0x40)) {
                                    arg0->xz_velocity = 0.0f;
                                    arg0->unk83 = 0xD;
                                    sp63 = 5;
                                }
                            } else if (temp_v0_6 & 4) {
                                arg0->unk83 = 0x14;
                                arg0->xz_velocity *= 0.7f;
                            } else {
                                arg0->xz_velocity = 0.0f;
                                arg0->unk83 = 0x10;
                            }
                            temp_v0_7 = arg0->unk31C->unk78;
                            if (temp_v0_7 == 0x21) {
                                var_t0_3 = 0x19D;
                            } else {
                                var_t0_3 = 0x36;
                                if (temp_v0_7 == 0x25) {
                                    var_t0_3 = 0xD8;
                                }
                            }
                        }
                    }
                    temp_v0_8 = arg0->unk84.uh;
                    if ((temp_v0_8 == 0x3B) || (temp_v0_8 == 0x3C)) {
                        sp63 = 0xFE;
                        sp6E = 0;
                        temp_t3 = arg0->unk184 & 0x1F;
                        arg0->unk83 = 0xFF;
                        if ((temp_t3 == 0xA) || (temp_t3 == 0xB) || (temp_t3 == 0xC) || (temp_t3 == 0xF) || (temp_t3 == 0x13)) {
                            sp3C = 0xC8;
                            obj_sfx_play_simple(0x1B8, arg0);
                        } else if ((temp_t3 == 1) || (temp_t3 == 2) || (temp_t3 == 7) || (temp_t3 == 0x11)) {
                            sp3C = 0xC8;
                            obj_sfx_play_simple(0xA7, arg0);
                        } else {
                            sp3C = 0x27;
                            obj_sfx_play_simple(0xA7, arg0);
                        }
                        var_t0_3 = sp3C;
                    }
                    if ((var_t0_3 != 0) && !(arg0->unk100 & 0x20)) {
                        obj_start_anim(arg0, var_t0_3 & 0xFFFF, 1.0f, 2.0f, 0.0f, 0.0f, 0);
                    }
                    if (!(arg0->unk100 & 0x80)) {
                        arg0->unk100 = 1;
                    }
                    if (sp6E == 0) {
                        arg0->unk100 = 0x90;
                    }
                }
                if ((arg0->unk28 > 0.0f) && !(arg0->unk100 & 8)) {
                    if (D_800CC69C != 0) {
                        if (arg0->xz_velocity > 20.0f) {
                            arg0->xz_velocity = 20.0f;
                        }
                    } else if (arg0->unk110 == 0) {
                        arg0->unk164 = 0.0f;
                        arg0->unk168 = 0.0f;
                    }
                    arg0->disable_run = sp63;
                    if ((arg0->unk31C->unk4E == 1) && (arg0->y_velocity < -10.0f)) {
                        sp6F = 2;
                    }
                }
                arg0->unkA9 = 0;
            }
            if (!(arg0->unk100 & 8)) {
                var_f2 = 0.0f;
            } else {
                var_f2 = 0.1f;
            }
            arg0->y_position = arg1;
            if ((arg0->stunned == 0) && !(sp6F & 2)) {
                arg0->y_velocity = -4.0f;
            } else {
                if (arg0->unkF4 & 0x80) {
                    arg0->y_velocity = -20.0f;
                } else {
                    temp_f0_3 = arg0->y_velocity;
                    if (temp_f0_3 > -10.0f) {
                        arg0->y_velocity = 0.0f;
                    } else {
                        arg0->y_velocity = temp_f0_3 * -0.5f;
                        if (arg0->y_velocity > 28.0f) {
                            arg0->y_velocity = 28.0f;
                        }
                    }
                }
                if (arg0->unk109 != 0) {
                    arg0->xz_velocity *= 0.6f;
                }
            }
            temp_v0_9 = arg0->unk7F;
            arg0->unk81 = 0;
            if ((s32) temp_v0_9 < 0xFA) {
                arg0->unk7F = temp_v0_9 + 1;
            }
            arg0->unk100 &= 0x9F;
            goto block_168;
        }
        if ((var_f2 < 1.0f) && (arg0->unk28 > 0.0f)) {
            var_f2 = 1.0f;
        }
block_168:
        if (var_f2 > 20.0f) {
            arg0->unk7F = 0;
        }
        if (arg0->in_water != 0) {
            arg0->unk1CC = arg0->y_position;
        }
block_172:
        arg0->unk28 = var_f2;
    }
}
/* was func_1505B5F8 */
void obj_land_on_floor(struct127 *arg0, f32 arg1) {
    f32 sp3C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f2;
    f32 var_f10;
    f32 var_f16;
    s32 temp_v0_4;
    struct129 *temp_v1;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;

    var_f16 = arg0->unk28;
    if (!(arg0->unkF8 & 0x8000)) {
        temp_v0 = arg0->unk252;
        if ((temp_v0 != 0) && ((f32) (arg0->unk253 * 8) < (arg0->unk1CC - arg0->y_position)) && (arg0->stunned == 0)) {
            arg0->stunned = 0xFE;
            arg0->unk105 = 0;
            sp3C = var_f16;
            arg0->unk106 = obj_find_reaction_row((s32) temp_v0, arg0);
            arg0->unk84.uh = 0xFF;
            obj_hit_reaction_advance(g_cur_obj_index, arg0);
            arg0->y_position = arg0->old_y_position;
        }
        temp_f0 = arg0->y_position;
        arg0->unk28 = temp_f0 - arg1;
        if (temp_f0 <= arg1) {
            arg0->unkF4 |= 0x8000;
            temp_v0_2 = g_level_header->unk13;
            if ((temp_v0_2 != 0) && (var_f16 != 0.0f)) {
                sp3C = var_f16;
                fx_dust_puff_behind_obj((s32) g_cur_obj_index, 0, 0x1000 / (s32) temp_v0_2, 0, 0x199, 4, 0xAA, 0xFFU, 0);
            }
            arg0->y_position = arg1;
            arg0->unk28 = 0.0f;
            if ((arg0->stunned != 0) || !(arg0->unkF8 & 0x10000)) {
                if (arg0->interaction_state == 1) {
                    if (arg0->y_velocity < -6.0f) {
                        arg0->y_velocity = -6.0f;
                    }
                } else {
                    if ((arg0->unk1CC - arg0->y_position) > 450.0f) {
                        temp_v0_3 = arg0->health;
                        if ((s32) temp_v0_3 > 0) {
                            temp_v1 = arg0->unk144;
                            if ((temp_v1 != NULL) && !(temp_v1->unkE & 0x80)) {
                                arg0->health = temp_v0_3 - 1;
                            }
                        }
                    }
                    arg0->unk1CC = arg1;
                    if ((arg0->stunned == 0) && (temp_f2 = arg0->gravity, (temp_f2 > 0.5f))) {
                        if ((arg0->unkF8 & 0x800) && (var_f16 != 0.0f) && (temp_f0_2 = arg0->y_velocity, (temp_f0_2 < (-4.0f * temp_f2 * *g_obj_time_step)))) {
                            temp_v0_4 = arg0->unk2CC;
                            arg0->y_velocity = (0.0f - temp_f0_2) * ((f32) arg0->unk2CB * 0.01f);
                            if ((temp_v0_4 != 0) && (arg0->y_velocity > 5.0f)) {
                                g_cur_obj_cmd = temp_v0_4;
                                objev_sound_300_1800();
                            }
                        } else if (arg0->interaction_state != 7) {
                            arg0->y_velocity = -4.0f * *g_obj_time_step;
                        }
                    } else {
                        if (arg0->unkF4 & 0x80) {
                            var_f10 = -4.0f;
                            goto block_35;
                        }
                        if ((var_f16 == 0.0f) || (temp_f0_3 = arg0->y_velocity, ((-1.5f * arg0->gravity * *g_obj_time_step) < temp_f0_3))) {
                            arg0->y_velocity = 0.0f;
                        } else {
                            var_f10 = (0.0f - temp_f0_3) * ((f32) arg0->unk2CB * 0.01f);
block_35:
                            arg0->y_velocity = var_f10;
                        }
                        arg0->xz_velocity *= 0.9f;
                    }
                }
            }
        }
    }
}
// void obj_land_on_floor(struct127 *arg0, f32 arg1) {
//     f32 tmp;
//     u8 temp_v0_2;
//
//     if ((arg0->unkF8 & 0x8000) == 0) {
//         if (arg0->unk252 != 0) {
//             if ((arg0->unk253 * 8) < (arg0->unk1CC - arg0->y_position)) {
//                 if (arg0->stunned == 0) {
//                     arg0->stunned = (u8)0xFEU;
//                     arg0->unk105 = (u8)0;
//                     arg0->unk106 = obj_find_reaction_row(arg0->unk252, arg0);
//                     arg0->unk84.uh = (u16)0xFF;
//                     obj_hit_reaction_advance(g_cur_obj_index, arg0);
//                     arg0->y_position = (f32) arg0->old_y_position;
//                 }
//             }
//         }
//         arg0->unk28 = arg0->y_position - arg1;
//         if (arg0->y_position <= arg1) {
//             arg0->unkF4 |= 0x8000;
//             temp_v0_2 = g_level_header->unk13;
//             if (temp_v0_2 != 0) {
//                 if (arg0->unk28 != 0.0f) {
//                     fx_dust_puff_behind_obj(g_cur_obj_index, 0, 0x1000 / (s32) temp_v0_2, 0, 0x199, 4, 0xAA, 0xFF, 0); // 0.0f, arg1,
//                 }
//             }
//             arg0->y_position = arg1;
//             tmp = arg0->unk28;
//             arg0->unk28 = 0.0f;
//             if ((arg0->stunned != 0) || ((arg0->unkF8 << 0xF) >= 0)) {
//                 if (arg0->interaction_state == 1) {
//                     if (arg0->y_velocity < -6.0f) {
//                         arg0->y_velocity = -6.0f;
//                     }
//                 } else {
//                     if ((arg0->unk1CC - arg0->y_position) > 450.0f) {
//                         if (arg0->health > 0) {
//                             if ((arg0->unk144 != 0) && ((arg0->unk144->unkE & 0x80) == 0)) {
//                                 arg0->health = (u8) (arg0->health - 1);
//                             }
//                         }
//                     }
//                     arg0->unk1CC = arg1;
//                     if ((arg0->stunned == 0) && (arg0->gravity > 0.5f)) {
//                         if (((arg0->unkF8 & 0x800) != 0) && (tmp != 0.0f) && ((arg0->y_velocity < (-4.0f * arg0->gravity * g_obj_time_step[0])))) {
//                             arg0->y_velocity = ((0.0f - arg0->y_velocity) * ((f32) arg0->unk2CB * D_8009950C));
//                             if ((arg0->unk2CC != 0) && (arg0->y_velocity > 5.0f)) {
//                                 g_cur_obj_cmd = arg0->unk2CC;
//                                 objev_sound_300_1800();
//                             }
//                         } else if (arg0->interaction_state != 7) {
//                             arg0->y_velocity = -4.0f * g_obj_time_step[0];
//                         }
//                     } else {
//                         if ((arg0->unkF4 & 0x80) != 0) {
//                             arg0->y_velocity = -4.0f;
//                         } else if ((tmp == 0.0f) || (((-1.5f * arg0->gravity * g_obj_time_step[0]) < arg0->y_velocity))) {
//                             arg0->y_velocity = 0.0f;
//                         } else {
//                             arg0->y_velocity = (0.0f - arg0->y_velocity) * ((f32) arg0->unk2CB * D_80099510);
//                         }
//                         arg0->xz_velocity *= D_80099514;
//                     }
//                 }
//             }
//         }
//     }
// }

void mp_report_hit(struct127 *, struct127 *, u8);
void rope_release(u8 *);
s32 sound_word_resolve(struct127 *, s32 *, s32);
f32 anim_events_run(struct127 *, f32, s32);
extern void (*g_hit_handlers[])(struct127 *, struct127 *, u8 *); /* hit handlers (void/3, tablesig); was D_80086A34 */
extern f32 D_800CC690;
extern f32 D_800CC694;
extern f32 D_800CC698;

/* P210: one hit descriptor (0x28 bytes): the attack tables of obj_get_hit_rules (indexed by the attack number) and
 * g_hit_desc_table. Fields 0x09..0x0E are the attack's hit volume (attack_hit_test's AttackBox). */
typedef struct {
    /* 0x00 */ u8  kind;      /* & 0x7F: hit kind; 0x80: the entry's own kind wins over the base entry's */
    /* 0x01 */ u8  pad1[3];
    /* 0x04 */ s32 sound;     /* effect / sound id (sound_word_resolve), 0 = none */
    /* 0x08 */ u8  handler;   /* index into g_hit_handlers; 0 = use the base entry's */
    /* 0x09 */ u8  pad9[6];
    /* 0x0F */ u8  damage;    /* low bits (masked by the caller): health taken; 0x20 flag, 0x40 keep the angle */
    /* 0x10 */ u8  push;      /* high byte added to the attacker's moving angle */
    /* 0x11 */ u8  pad11[3];
    /* 0x14 */ f32 xz_speed;
    /* 0x18 */ f32 y_speed;
    /* 0x1C */ f32 gravity;
    /* 0x20 */ u8  unk20;     /* -> obj->unk109 */
    /* 0x21 */ u8  pad21;
    /* 0x22 */ u8  immune;    /* 0x80: obj->immune = & 0x3F */
    /* 0x23 */ u8  pad23;
    /* 0x24 */ u16 flags;
    /* 0x26 */ u8  pad26[2];
} HitDesc;

// object_apply_hit: applies hit descriptor `idx` from attacker `self` to object `obj` (number `slot` - 1).
/* `base_tbl` is the attacker's own table, `cur_tbl` the one in effect (obj_receive_hit may redirect it into
 * g_hit_desc_table). Sets the knock-back (angle from the attacker, speeds, gravity), takes `damage & mask` health,
 * makes a ridden player drop off (and the carrier let go of it), runs the descriptor's handler (not for kind
 * 0x27), reports the hit (mp_report_hit in multiplayer, two node_broadcast_range events), plays the sound and sets the
 * hit state of `obj` (stun 0xFE, obj_find_reaction_row / obj_hit_reaction_advance reaction, flags in unk10B). Returns the base
 * entry's byte 0x22 (unused by the callers). */
/* was func_1505B9C4 */
u8 obj_apply_hit(struct127 *self, struct127 *obj, s32 base_tbl, s32 cur_tbl, u8 idx, s32 slot, u8 mask) {
    HitDesc *base = &((HitDesc *)base_tbl)[idx];
    HitDesc *cur = &((HitDesc *)cur_tbl)[idx];
    struct {
        struct127 *obj;
        u8 uid;
    } ev;
    u8 kind;
    u8 dmg;
    u8 handler;

    if (cur->kind & 0x80) {
        kind = cur->kind & 0x7F;
    } else {
        kind = base->kind & 0x7F;
    }
    obj->unk10B = 0;
    if ((base->flags & 1) && obj->stunned != 0) {
        mask = 0;
    }
    if (!(cur->damage & 0x40)) {
        obj->unk76 = (cur->push << 8) + self->unk76;
        if (base->flags & 0x10) {
            obj->unk76 = math_atan2_u16(obj->x_position - self->x_position, self->z_position - obj->z_position, 0);
        }
        if (self->id == 0x44) {
            obj->unk76 = 0;
        }
    }
    if ((cur->damage | base->damage) & 0x20) {
        obj->unk10B |= 2;
    }
    obj->unk3A = 0;
    obj->unk109 = cur->unk20;
    obj->y_velocity = cur->y_speed;
    obj->xz_velocity = cur->xz_speed;
    obj->unk100 &= 0xD6;
    obj->gravity = cur->gravity;
    dmg = cur->damage & mask;
    if (dmg < obj->health) {
        obj->health -= dmg;
    } else {
        obj->health = 0;
    }

    if (obj->interaction_state == 1) {
        /* a player: run its drop-off with obj as the current object, then clear its riding state */
        struct127 *saved = g_cur_obj;
        u8 savedNum = g_cur_obj_index;
        s32 num = ((s32)obj - (s32)g_objects) / 0x32C;
        struct126 *ctl;

        g_cur_obj = obj;
        g_cur_obj_index = num;
        ctl = g_objects[(u8)num].unk31C;
        if (ctl->unk4E != 2) {
            ctl->unk4E = 0;
        }
        anim_events_run(obj, 800.0f, 1);
        g_cur_obj = saved;
        g_cur_obj_index = savedNum;
        obj->unkF8 &= ~0x01008000;
        obj->unk31C->unk95 = 0;
        obj->unk31C->unk6B = 0;
        if (obj->unk31C->pad98[0] != 0) {
            rope_release((u8 *)obj);
        }
        obj->unk31C->unk54 = 0;
        obj->unk137 = 0;
        if (obj->unk65 != 0) {
            /* carried by object unk65 - 1: ids 0x8A / 0x23 only let go when the hit is hard enough */
            struct127 *carrier = &g_objects[(u8)(obj->unk65 - 1)];
            u8 id = carrier->id;

            if ((id != 0x8A && id != 0x23) || obj->health == 0 || (base->flags & 2)
                || (D_800BE616 != 0 && (30.0f < obj->y_velocity || 110.0f < obj->xz_velocity))) {
                s32 state = (id == 0x8A) ? 1 : 0;

                if (id == 0x23) {
                    state = 10;
                }
                if (id == 0xC) {
                    state = 15;
                }
                if (state != 0) {
                    carrier->unk232 = state;
                    carrier->unk218 = NULL;
                }
                carrier->unk2FC = 0;
                carrier->unk13C = 0;
                obj->unk239 = 0;
                obj->unk65 = 0;
            }
        }
    }

    handler = cur->handler;
    if (handler == 0) {
        handler = base->handler;
    }
    if (kind != 0x27) {
        g_hit_handlers[handler](self, obj, &kind);
    }
    if (D_800BE616 != 0) {
        mp_report_hit((self->unk124 != 0) ? &g_objects[self->unk124 - 1] : self, obj, kind);
    }
    ev.obj = self;
    ev.uid = self->unique_id;
    node_broadcast_range(0, 0x68, (s32)&ev, 2);
    ev.obj = obj;
    ev.uid = obj->unique_id;
    node_broadcast_range(0, 0x68, (s32)&ev, 2);

    if (base->sound != 0) {
        g_cur_obj_cmd = base->sound;
        if (sound_word_resolve(obj, &g_cur_obj_cmd, 0) != 0) {
            actor_sound_play_untracked(g_cur_obj_cmd_sound, obj, 0x6D60, 0x12C, 0x708);
        }
    } else if (cur->sound != 0) {
        g_cur_obj_cmd = cur->sound;
        if (sound_word_resolve(obj, &g_cur_obj_cmd, 0) != 0) {
            actor_sound_play_untracked(g_cur_obj_cmd_sound, obj, 0x6D60, 0x12C, 0x708);
        }
    }

    self->unk107 = 0x3C;
    if (D_800BE616 == 0 || obj->interaction_state != 1) {
        obj->unk21C = 0;
        if (base->flags & 0x100) {
            obj->unk218 = NULL;
        }
    }
    obj->unkD0 = 0;
    if (self->unk124 != 0) {
        obj->unk10A = self->unk124 + 0x7F;
    } else {
        obj->unk10A = g_cur_obj_index | 0x80;
    }
    self->unk108 = (slot - 1) | 0x80;

    if (kind != 0x27) {
        if ((base->flags & 0x40) && obj->interaction_state == 1) {
            /* player hit by a player: halfword 0x46 of the attacker's controller */
            *(s16 *)((u8 *)g_objects[slot - 1].unk31C + 0x46) = 8000;
        } else {
            if (obj->unk23B != 0) {
                kind = obj->unk23B;
            }
            obj->stunned = 0xFE;
            obj->unk105 = 0;
            obj->unk106 = obj_find_reaction_row(kind, obj);
            obj->unk84.uh = 0xFFFF;
            obj_hit_reaction_advance(slot - 1, obj);
            if (base->flags & 0x200) {
                obj->unk10B |= 0x20;
            }
            if (0.0f < obj->y_velocity) {
                obj->unk28 += 0.1f;
            }
            if (base->flags & 8) {
                obj->unk10B |= 0x40;
                D_800CC690 = self->x_position;
                D_800CC694 = self->z_position;
                D_800CC698 = self->y_position;
            }
        }
        if (base->flags & 2) {
            obj->unk10B |= 0x80;
        }
    }
    if ((base->flags & 0x400) || (cur->flags & 0x400)) {
        obj->unk10B |= 4;
    }
    if (base->immune & 0x80) {
        obj->immune = base->immune & 0x3F;
    }
    return base->immune;
}

/* was func_1505C140 */
s16 obj_facing_angle_diff(struct127 *arg0, struct127 *arg1) {
    s16 ret = math_atan2_u16(arg0->x_position - arg1->x_position, arg1->z_position - arg0->z_position, 0);
    ret -= arg1->unk7A;

    if (ret < 0) {
        ret = -ret;
    }
    return ret;
}

/* was func_1505C1A4 */
struct252 *obj_get_hit_rules(struct127 *arg0) {
    s32 *temp_v1;
    struct252 *ret;

    if ((arg0->id != 0xFF) && (D_800D1588[arg0->id] != 0)) {
        temp_v1 = (s32*)D_800D1588[arg0->id] - 3;
        ret = *temp_v1;
    } else {
        ret = &g_hit_sender_default;
    }
    return ret;
}

s32 sound_word_resolve(struct127 *, s32 *, s32);
void obj_sfx_play_vol(s32 arg0, struct127 *arg1, s32 arg2);
s16 obj_facing_angle_diff(struct127 *arg0, struct127 *arg1);
u8 obj_apply_hit(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u8 arg6);
extern void (*g_hit_handlers[])(struct127 *, struct127 *, u8 *); /* hit handlers (void/3, tablesig); was D_80086A34 */

/* HitDesc: see obj_apply_hit */
/* P210: one hit reaction rule (4 bytes) of the per-type lists g_hit_rule_lists[type] (g_hit_rule_counts[type] rules each). */
typedef struct {
    u8 cond;    /* 1: obj faces the attacker (obj_facing_angle_diff <= 0x4000), 2: turned away (>= 0x4000), 3: obj stunned,
                 * 4: obj not stunned; other values: always */
    u8 kind;    /* the hit kind the rule is for */
    u8 action;  /* & 0x7F: reaction; 0x80: the rule is for every kind except `kind` */
    u8 param;
} HitRule;

extern u8 g_hit_rule_counts[]; /* was D_8009AA60 */
extern HitRule *g_hit_rule_lists[]; /* was D_80086E40 */

// object_receive_hit: hit descriptor `idx` of table `descs` from `self` hits object `obj` (number `slot` - 1).
/* The first matching rule of obj's reaction list (type obj->unk239 & 0x7F) may change the hit: actions 0 / 1
 * (attacker on the front / back side) and 2 / 4 pick another descriptor, 5 / 6 / 7 take descriptor `param` of
 * g_hit_desc_table (7 only when the damage reaches obj's health, then obj's health is cleared), 4 / 6 make it harmless
 * (mask 0); 3, 8 (obj catches the attacker), 10, 11, 12, 13 (handler only) handle it here. Rules whose action or
 * condition fails are skipped. Unless handled, obj_apply_hit applies the hit. Returns `hits` with obj's bit set
 * when the hit landed (or when 8 / 13 handled it). */
/* was func_1505C1E4 */
s32 obj_receive_hit(struct127 *self, struct127 *obj, void *descs, s32 idx, s32 slot, s32 hits, s32 mask) {
    HitDesc *desc = &((HitDesc *)descs)[idx];
    HitDesc *tbl = descs;   /* tbl[idx] is the descriptor obj_apply_hit applies */
    u8 kind = desc->kind & 0x7F;
    u8 type = obj->unk239 & 0x7F;
    s32 handled = FALSE;
    HitRule *rule;
    s32 count;
    s32 n;
    u8 action;
    u8 scratch[4]; /* the handler's kind byte; the asm passes an unset stack word and ignores it */

    if (type != 0 && (count = g_hit_rule_counts[type]) > 0) {
        rule = g_hit_rule_lists[type];
        for (n = 0; n < count; n++, rule++) {
            if (rule->action & 0x80) {
                if (rule->kind == kind) {
                    continue;
                }
            } else if (rule->kind != kind) {
                continue;
            }
            action = rule->action & 0x7F;
            if (rule->cond == 1 && obj_facing_angle_diff(self, obj) > 0x4000) {
                action = 0xFF;
            }
            if (rule->cond == 2 && obj_facing_angle_diff(self, obj) < 0x4000) {
                action = 0xFF;
            }
            if (rule->cond == 3 && obj->stunned == 0) {
                action = 0xFF;
            }
            if (rule->cond == 4 && obj->stunned != 0) {
                action = 0xFF;
            }
            switch (action) {
                case 0:
                case 1: {
                    /* 0: the attacker is in front of obj, 1: behind it */
                    u16 ang = math_atan2_u16(self->x_position - obj->x_position, obj->z_position - self->z_position, 0);

                    if (action == ((((s32)ang - obj->unk7A + 0x4000) >> 15) & 0xFFFF)) {
                        idx = rule->param;
                    }
                    break;
                }
                case 2:
                    idx = rule->param;
                    break;
                case 3:
                    handled = TRUE;
                    break;
                case 4:
                    if (rule->param != 0xFF) {
                        idx = rule->param;
                    }
                    mask = 0;
                    break;
                case 5:
                    tbl = (HitDesc *)g_hit_desc_table + rule->param - idx;
                    break;
                case 6:
                    tbl = (HitDesc *)g_hit_desc_table + rule->param - idx;
                    mask = 0;
                    break;
                case 7:
                    if ((desc->damage & mask) < obj->health) {
                        continue;
                    }
                    tbl = (HitDesc *)g_hit_desc_table + rule->param - idx;
                    obj->health = 0;
                    break;
                case 8:
                    /* obj catches the attacker */
                    handled = TRUE;
                    obj->unkF4 &= ~0x00040040;
                    hits |= 1 << ((slot - 1) & 0x1F);
                    self->unk108 = slot + 0x7F;
                    self->unk107 = 0x3C;
                    obj->unk1C4 = 0;
                    obj->unk218 = NULL;
                    obj->disable_run = 1;
                    obj->unkD0 = 0;
                    obj->unk232 = rule->param;
                    g_cur_obj_cmd = desc->sound;
                    if (desc->sound != 0) {
                        objev_sound_300_1800();
                    }
                    if (obj->interaction_state == 1) {
                        struct126 *ctl = obj->unk31C;

                        if (ctl->unk4E == 2 && ctl->unk84 == 0) {
                            ctl->pad4F[1] = 30; /* byte 0x50 */
                            obj->unk81 = 0;
                            obj->y_velocity = 50.0f;
                            obj->gravity = 2.0f;
                        }
                    }
                    break;
                case 9:
                    break;
                case 10:
                    if (obj->unk84.uh == 0x283) {
                        obj->unk76 = self->unk7A;
                        obj->xz_velocity = 25.0f;
                        g_cur_obj_cmd = 0xFF0102E2;
                        objev_sound_300_1800();
                        self->unkD0 = 0;
                        self->unk232 = 0xD;
                        self->unk218 = NULL;
                        handled = TRUE;
                    }
                    break;
                case 11:
                    if (8.0f < obj->unk28) {
                        handled = TRUE;
                    }
                    break;
                case 12:
                    if (obj->unk28 == 0.0f) {
                        self->unk2EC = 100;
                        self->unkD0 = 0;
                    }
                    handled = TRUE;
                    break;
                case 13: {
                    /* only the descriptor's handler (and obj's effect unkFC) */
                    u8 handler = desc->handler;
                    s32 effect;

                    g_cur_obj_cmd = desc->sound;
                    if (desc->sound != 0) {
                        objev_sound_300_1800();
                    }
                    g_hit_handlers[handler](self, obj, scratch);
                    if (obj->unkFC != 0) {
                        effect = obj->unkFC;
                        if (sound_word_resolve(self, &effect, 1) != 0) {
                            obj_sfx_play_vol(effect, obj, 0x5DC0);
                        }
                    }
                    hits |= 1 << ((slot - 1) & 0x1F);
                    handled = TRUE;
                    break;
                }
                default:
                    continue; /* failed condition (0xFF) or no reaction */
            }
            break;
        }
    }
    if (handled) {
        return hits;
    }
    obj_apply_hit(self, obj, (s32)descs, (s32)tbl, idx, slot, mask);
    return hits | (1 << ((slot - 1) & 0x1F));
}
extern f32 g_attack_deg_to_rad; /* pi / 180; was D_800998E4 */
extern struct127 g_obj_table_minus128[]; /* was D_800B30F0 */
s32 obj_receive_hit(struct127 *arg0, struct127 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 obj_collision_cylinder(struct127 *, s16 *, s16 *, s16 *);
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, void *, void *, f32 *, f32 *, f32 *, f32 *, s32, s32, f32); /* P151: args 7 / 8 are out-pointers (obj_find_visible_target) */
f32 vec3_length(f32 *vec);

/* P67: one attack descriptor (0x28 bytes) of the table obj_get_hit_rules returns; rec->unkD0 - 1 is the active one. */
typedef struct {
    /* 0x00 */ u8  pad0[9];
    /* 0x09 */ u8  angle;   /* sphere: high byte of the angle offset from the facing; box: half length / 5 */
    /* 0x0A */ u8  dist;    /* sphere: distance in front (/ 0.125 scale); box: half width / 5 */
    /* 0x0B */ u8  padB;
    /* 0x0C */ s16 height;  /* height of the hit point (/ 0.25 scale) */
    /* 0x0E */ u8  radius;  /* sphere: radius / 4 (scale); box: s8 forward offset / 5 */
    /* 0x0F */ u8  padF[0x15];
    /* 0x24 */ u16 flags;   /* 0x80 box, 0x1000 may hit unk124, 0x2000 line of sight, 4 keep unk21C, 0x800 keep */
    /* 0x26 */ u8  pad26[2];
} AttackBox;

/* P67: attack hit test. Tests the active attack (sphere in front of the attacker, or a box in its frame) against
 * every live, vulnerable record except `skip`, optionally checks the line of sight (ray cast from the eyes), and
 * calls obj_receive_hit for each hit. Returns obj_receive_hit's last result (0 = no hit). */
/* was func_1505C7D8 */
s32 attack_hit_test(struct127 *self, s32 skip) {
    AttackBox *boxes;
    AttackBox *box;
    struct127 *target;
    s32 cur;
    s32 i;
    s32 count;
    s32 hits = 0;
    f32 hitX = 0.0f; /* the asm leaves these unset in box mode (reads its stack slot) */
    f32 hitY;
    f32 hitZ = 0.0f;
    f32 radius = 0.0f;
    f32 dx, dy, dz, ofs;
    f32 dist, limit;

    if (self->unk114 < 254.0f) {
        self->unk114 -= g_obj_time_step[0];
    }
    if (self->unk114 < 0.0f) {
        self->unkD0 = 0;
        return 0;
    }
    if (D_800C35EA == 1) {
        return 0;
    }
    skip = (skip & 0x7F) + 1;
    cur = self->unkD0 - 1;
    boxes = (AttackBox *)obj_get_hit_rules(self);
    box = &boxes[cur];

    /* the hit point: sphere centre in front of the attacker */
    if (box->flags & 0x80) {
        hitY = self->y_position;
    } else {
        vec_from_yaw_pitch(((box->angle << 8) + self->unk7A) & 0xFFFF, box->dist * (self->xz_scale / 0.125f), 0.0f,
                      &hitX, &hitZ, &hitY);
        hitX += self->x_position;
        hitY += self->y_position;
        hitZ += self->z_position;
        radius = box->radius;
        radius *= self->xz_scale * 4.0f;
    }
    hitY += box->height * (self->y_scale / 0.25f);

    count = (self->unkF8 & 0x100) ? 4 : 26;
    for (i = 1; i < count; i++) {
        target = &g_objects[i - 1];
        if (target->interaction_state == 0 || i == skip || target->health == 0 || target->immune != 0) {
            continue;
        }
        box = &boxes[cur];
        if (i == self->unk124 && !(box->flags & 0x1000)) {
            continue;
        }
        if (box->flags & 0x80) {
            /* box: target position in the attacker's frame (forward / side / up) */
            f32 angle, s, c, fwd, side, halfY, halfF, halfS;

            dx = target->x_position - self->x_position;
            dz = target->z_position - self->z_position;
            if (target->unkD8 != 0 || target->unkDA != 0) {
                dx += math_rotate_offset_deg(target->unk40, target->unkDA, target->unkD8, 1.0f, &ofs);
                dz += ofs;
            }
            angle = -((self->unk40 - 90.0f) * g_attack_deg_to_rad);
            s = fast_cosf(angle);
            c = fast_sinf(angle);
            fwd = (dx * s + dz * c) - (s16)((s8)box->radius * 5) * self->xz_scale;
            side = -dx * c + dz * s;
            dy = hitY - (target->y_position + target->unkD6);
            halfY = target->unkD4 + 25.0f;
            halfF = box->angle * 5 * self->xz_scale + target->unkD2;
            halfS = box->dist * 5 * self->xz_scale + target->unkD2;
            if (!(-halfY < dy && dy < halfY && -halfF < fwd && fwd < halfF && -halfS < side && side < halfS)) {
                continue;
            }
        } else {
            /* sphere against the target's ellipsoid (radius unkD2, half height unkD4) */
            f32 r, h, k;

            dx = hitX - target->x_position;
            dz = hitZ - target->z_position;
            if (target->unkD8 != 0 || target->unkDA != 0) {
                dx -= math_rotate_offset_deg(target->unk40, target->unkDA, target->unkD8, 1.0f, &ofs);
                dz -= ofs;
            }
            dy = hitY - (target->y_position + target->unkD6);
            h = target->unkD4;
            r = target->unkD2;
            if (h == 0.0f) {
                continue;
            }
            limit = (r + radius) * (r + radius);
            k = h / (radius + h);
            dy *= (r / h) * k + (1.0f - k);
            dist = dx * dx + dy * dy + dz * dz;
            if (!(dist < limit)) {
                continue;
            }
        }

        if ((box->flags & 0x2000) && i != self->unk13D) {
            /* line of sight: ray from the attacker's eyes to the target's middle */
            f32 eye[3];
            f32 ray[3];
            f32 hx, hy, hz, t;
            f32 aim;
            s16 eyeH;

            if (self->unk2F4 != NULL) {
                eye[0] = ((f32 *)self->unk2F4)[0];
                eye[1] = ((f32 *)self->unk2F4)[1];
                eye[2] = ((f32 *)self->unk2F4)[2];
            } else {
                obj_collision_cylinder(self, &eyeH, NULL, NULL);
                eye[0] = self->x_position;
                eye[1] = self->y_position + (eyeH >> 1);
                eye[2] = self->z_position;
            }
            if (target->unk31C != NULL) {
                aim = (s16)target->unk31C->unk114 * 0.5f;
            } else {
                aim = 20.0f;
            }
            ray[0] = target->x_position - eye[0];
            ray[1] = (aim + target->y_position) - eye[1];
            ray[2] = target->z_position - eye[2];
            if (collision_ray_cast(eye[0], eye[1], eye[2], ray[0], ray[1], ray[2], 0, 0, &hx, &hy, &hz, &t, 0, 0, 0.0f) != 0
                && t < vec3_length(ray)) {
                continue; /* blocked */
            }
        }

        g_hit_point_x = hitX;
        g_hit_point_y = hitY;
        g_hit_point_z = hitZ;
        hits = obj_receive_hit(self, target, boxes, cur, i, hits, 15);
        cur = self->unkD0 - 1;
    }

    if (hits != 0) {
        box = &boxes[cur];
        if (g_obj_table_minus128[self->unk108].interaction_state == 1 && self->unk254 != 0) {
            self->unk232 = self->unk254;
            self->unk218 = NULL;
        }
        if (!(box->flags & 4)) {
            self->unk21C = 0;
        }
        if (!(box->flags & 0x800)) {
            self->unkD0 = 0;
        }
    }
    return hits;
}
struct252 *obj_get_hit_rules(struct127 *arg0);
s32 obj_receive_hit(struct127 *arg0, struct127 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
u8 obj_apply_hit(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u8 arg6);
extern s16 g_obj_scratch_7a; /* the asm's name for this halfword (D_800D1296 in the US list); was D_800D16B6 */

// object_send_hit: sends a hit / message of kind `flags & 0xFF` to the object `obj` from the current object.
/* Nothing (returns 0) while D_800C35EA is 1, or when the object is immune (flag 0x20000), stunned (0x40000) or has
 * no health (unless flag 0x100000). Sets the parameter g_obj_scratch_owner (arg3 + 1, 0 for -1) and the value `val` in
 * g_obj_scratch_yaw / g_obj_scratch_7a. The sender record is g_hit_sender_default, or obj_get_hit_rules(g_cur_obj) with flag 0x10000.
 * Flag 0x80000 uses obj_receive_hit and returns its result; else obj_apply_hit and returns the object's bit
 * (1 << its index in g_objects). */
/* was func_1505D024 */
s32 obj_send_hit(struct127 *obj, s32 flags, u16 val, s32 arg3) {
    struct252 *from = &g_hit_sender_default;
    s32 idx;
    s32 bit;

    if (D_800C35EA == 1) {
        return 0;
    }
    if ((flags & 0x20000) && obj->immune != 0) {
        return 0;
    }
    if ((flags & 0x40000) && obj->stunned != 0) {
        return 0;
    }
    if (!(flags & 0x100000) && obj->health == 0) {
        return 0;
    }
    if (arg3 == -1) {
        g_obj_scratch_owner = 0;
    } else {
        g_obj_scratch_owner = arg3 + 1;
    }
    g_obj_scratch_yaw = val;
    g_obj_scratch_7a = val;
    if (flags & 0x10000) {
        from = obj_get_hit_rules(g_cur_obj);
    }
    idx = ((s32)obj - (s32)g_objects) / 0x32C;
    bit = 1 << idx;
    if (flags & 0x80000) {
        return obj_receive_hit((struct127 *)&g_obj_scratch_rec, obj, from, flags & 0xFF, idx + 1, 0, 7);
    }
    obj_apply_hit((struct127 *)&g_obj_scratch_rec, obj, (s32)from, (s32)from, flags & 0xFF, idx + 1, 7);
    return bit;
}
// NON-MATCHING: 1 line + regalloc
// s32 obj_send_hit(struct127 *arg0, s32 arg1, u16 arg2, s32 arg3) {
//     s32 pad;
//     s32 ret;
//     s32 temp_lo;
//     struct252 *sp30;
//
//     sp30 = &g_hit_sender_default;
//     if (D_800C35EA == 1) {
//         return 0;
//     }
//     if ((arg1 & 0x20000) && (arg0->immune != 0)) {
//         return 0;
//     }
//     if ((arg1 & 0x40000) && (arg0->stunned != 0)) {
//         return 0;
//     }
//     if (((arg1 << 0xB) >= 0) && (arg0->health == 0)) {
//         return 0;
//     }
//     if (arg3 == -1) {
//         g_obj_scratch_owner = (u8)0;
//     } else {
//         g_obj_scratch_owner = arg3 + 1;
//     }
//     g_obj_scratch_yaw = arg2;
//     D_800D1296 = arg2;
//     if (arg1 & 0x10000) {
//         sp30 = obj_get_hit_rules(g_cur_obj);
//     }
//
//     temp_lo = ((s32)arg0 - (s32)g_objects) / (s32)sizeof(struct127);
//     ret = 1 << temp_lo;
//     if (arg1 & 0x80000) {
//         // lw instead of move.
//         ret = obj_receive_hit(&g_obj_scratch_rec, arg0, sp30, arg1 & 0xFF, temp_lo + 1, 0, 7);
//     } else {
//         obj_apply_hit(&g_obj_scratch_rec, arg0, sp30, sp30, arg1 & 0xFF, temp_lo + 1, 7);
//     }
//     return ret;
// }

// effect_spawn_at: spawns effect / sound `arg3` at (arg0, arg1, arg2) for object index arg4 through the shared
// spawn record g_obj_scratch_rec; returns attack_hit_test's result (P289: was void, the asm leaves it in v0).
/* was func_1505D1C4 */
s32 attack_spawn_at_point(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, u16 arg5, s32 arg6, s32 arg7) {
    s32 ret;
    s32 tmp;

    tmp = g_cur_obj_index;
    obj_reset(&g_obj_scratch_rec);
    g_obj_scratch_x = arg0;
    g_obj_scratch_y = arg1;
    g_obj_scratch_z = arg2;
    g_obj_scratch_owner = arg4 + 1;
    g_obj_scratch_13d = arg6;
    g_obj_scratch_yaw = arg5;
    g_cur_obj_index = 25;
    g_obj_scratch_links = arg7;
    g_obj_scratch_114 = 100.0f;
    g_obj_scratch_d0 = (arg3 & 0xFFFF) + 1;
    g_obj_scratch_xz_scale = 0.5f;
    g_obj_scratch_y_scale = 0.5f;
    ret = attack_hit_test(&g_obj_scratch_rec, 25);
    g_cur_obj_index = tmp;
    return ret;
}

/* was func_1505D2B8 */
void obj_start_knockback(struct127 *arg0, u8 arg1) {
    struct253 *temp_v0;

    temp_v0 = &g_hit_desc_table[arg1];
    arg0->y_velocity = temp_v0->unk18;
    arg0->xz_velocity = temp_v0->unk14;
    arg0->gravity = temp_v0->unk1C;
    arg0->stunned = 0xFE;
    arg0->unk105 = 0;
    arg0->unk106 = obj_find_reaction_row(arg0->unk10E & 0x7F, arg0);
    arg0->unk10E = 0xFF;
    obj_hit_reaction_advance(g_cur_obj_index, arg0);
}

/* was func_1505D34C */
f32 math_rotate_offset_deg(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    f32 sp24;
    f32 temp_f0;
    f32 temp_f12;

    if (arg3 != 1.0f) {
        arg1 = arg1 * arg3;
        arg2 = arg2 * arg3;
    }
    temp_f12 = (arg0 - 90.0f) * 0.017453292f; // 0.01745329238474369f;
    sp24 = fast_cosf(temp_f12);
    temp_f0 = fast_sinf(temp_f12);
    *arg4 = (-arg1 * temp_f0) + (arg2 * sp24);
    return (arg1 * sp24) + arg2 * temp_f0;
}

extern s8 D_800CC68C;
extern s8 g_contact_grab_obj_id; /* was D_800CC68D */

/* was func_1505D408 */
void obj_contact_resolve(struct127 *arg0, struct127 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7) {
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f18;
    f32 temp_f8;
    f32 var_f12;
    f32 var_f14;
    f32 var_f2;
    s32 temp_a2;
    s32 temp_t0;
    s32 var_v0;
    s32 var_v1;

    var_f14 = arg2;
    var_f12 = arg5;
    var_f2 = 0.4f;
    var_v0 = 0;
    var_v1 = 0;
    if (var_f12 < 1.0f) {
        var_f12 = 1.2f;
    }
    if ((var_f14 == 0.0f) && (arg4 == 0.0f)) {
        var_f14 = 1.0f;
    }
    g_obj_contact_mask |= 1 << arg7;
    if (!(arg1->unkF8 & 0x10) || (D_800CC68C = (s8) arg7, var_f2 = 0.8f, (arg1->id != 0x61)) || (arg0->interaction_state != 1)) {
        temp_t0 = arg0->unkF8;
        temp_a2 = arg1->unkF8;
        if (temp_t0 & 1) {
            var_v0 = 1;
        }
        if (temp_t0 & 0x200) {
            var_v0 = (var_v0 | 2) & 0xFF;
        }
        if (temp_a2 & 1) {
            var_v1 = 1;
        }
        if (temp_a2 & 0x200) {
            var_v1 = (var_v1 | 2) & 0xFF;
        }
        if (var_v1 >= var_v0) {
            if ((temp_a2 & 0x400) && (arg1->unk28 == 0.0f)) {
                g_contact_grab_obj_id = arg7 + 0x64;
            }
            temp_f0 = sqrtf(var_f12);
            temp_f18 = 1.0f / temp_f0;
            temp_f8 = arg6 - temp_f0;
            arg6 = temp_f8;
            temp_f10 = temp_f8 * var_f2;
            arg3 *= temp_f18;
            arg6 = temp_f10;
            arg0->x_position += temp_f10 * (var_f14 * temp_f18);
            arg0->z_position += arg6 * (arg4 * temp_f18);
            arg0->y_position += arg6 * arg3;
        }
    }
}
f32 math_rotate_offset_deg(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4);
void obj_contact_resolve(struct127 *arg0, struct127 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7);

/* Box test of record `rec` (at x, y, z; height `scale`, radius `radius`) against object `o` (id 0x34, called by
 * obj_contact_pass): o's box has radius r and height h (scaled by o +0x14C / +0x150), centre offset (ox, oz) turned
 * by o's heading (math_rotate_offset_deg) and height cy (scaled by +0x150). The vertical distance is scaled by
 * (scale + r / h) / 2; inside the sphere of radius radius + r: obj_contact_resolve (push out). */
/* was func_1505D5D0 */
void obj_box_contact_test(struct127 *rec, struct127 *o, f32 x, f32 y, f32 z, f32 scale, f32 radius, s32 i, f32 r, f32 h,
                   f32 cy, f32 ox, f32 oz) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d2;
    f32 lim;

    dx = math_rotate_offset_deg(o->unk40, ox, oz, *(f32 *)((u8 *)o + 0x14C), &oz);
    r = r * *(f32 *)((u8 *)o + 0x14C);
    h = h * *(f32 *)((u8 *)o + 0x150);
    dx = x - (o->x_position + dx);
    dz = z - (o->z_position + oz);
    dy = y - (o->y_position + cy * *(f32 *)((u8 *)o + 0x150));
    dy = dy * ((scale + r / h) * 0.5f);
    d2 = dx * dx + dy * dy + dz * dz;
    lim = radius + r;
    if (d2 < lim * lim) {
        obj_contact_resolve(rec, o, dx, dy, dz, d2, lim, i);
    }
}
void obj_contact_resolve(struct127 *, struct127 *, f32, f32, f32, f32, f32, s32);
void obj_box_contact_test(struct127 *, struct127 *, f32, f32, f32, f32, f32, s32, f32, f32, f32, f32, f32);
extern s8 D_800CC68C;
extern s8 g_contact_grab_obj_id; /* was D_800CC68D */

/* Record-vs-record push / contact pass for record idx (rec = &g_objects[idx]): clears the contact mask
 * g_obj_contact_mask and the D_800CC68C / 68D flags, then tests rec's cylinder (radius unkE4, height offset unkE8, vertical
 * scale unkEC) against the other 25 records (only record 0 when rec->unkF8 has 0x02000000). Overlaps go to
 * obj_contact_resolve; record id 0x34 gets the special box test obj_box_contact_test. In multiplayer, a player close to
 * another team's player who holds the flag (+0x78 in the controller) sets its own chase timer (+0x4A = 20). */
/* was func_1505D6F0 */
void obj_contact_pass(struct127 *rec, s32 idx) {
    struct127 *o;
    u8 *ctl;
    s32 i;
    s32 count;
    f32 radius, scale, x, y, z;
    f32 dx, dy, dz, d2, reach;
    s16 oradius;

    g_obj_contact_mask = 0;
    D_800CC68C = 0;
    g_contact_grab_obj_id = 0;
    count = 25;
    if (rec->interaction_state == 1) {
        ctl = (u8 *)g_objects[idx].unk31C;
        if (ctl[0x4E] != 0 || ctl[0x27] != 0) {
            return;
        }
    }
    if (rec->unk13D >= 100 || rec->unkE4 == 0 || rec->unk65 != 0) {
        return;
    }
    if ((rec->unkF8 & 0x01000000) || (rec->unkF8 & 0x4000)) {
        return;
    }
    scale = rec->unkEC;
    x = rec->x_position;
    z = rec->z_position;
    radius = rec->unkE4;
    y = rec->y_position + (s16)rec->unkE8;
    if (rec->unkF8 & 0x02000000) {
        count = 1;
    }
    for (i = 0, o = g_objects; i < count; i++, o++) {
        if (o->interaction_state == 0) {
            continue;
        }
        oradius = o->unkE4;
        if (oradius < 2) {
            continue;
        }
        if ((o->unkF8 & 0x02000000) && rec->unk127 == 0xFF) {
            continue;
        }
        if ((o->unkF8 & 0x01000000) || i == idx || o->unk65 == idx + 1 || o->unk13D >= 100 || o->unk2FA == 0) {
            continue;
        }
        dx = x - o->x_position;
        dz = z - o->z_position;
        dy = (y - (o->y_position + (s16)o->unkE8)) * ((scale + o->unkEC) * 0.5f);
        if (D_800BE616 != 0 && dx * dx + dy * dy + dz * dz < 30000.0f && rec->interaction_state == 1 &&
            o->interaction_state == 1 && o->unk128 != rec->unk128) {
            ctl = (u8 *)rec->unk31C;
            if (ctl[0x78] == 0 && ((u8 *)o->unk31C)[0x78] != 0) {
                ctl[0x4A] = 20;
            }
        }
        reach = radius + oradius;
        d2 = dx * dx + dy * dy + dz * dz;
        if (d2 < reach * reach) {
            obj_contact_resolve(rec, o, dx, dy, dz, d2, reach, i);
        }
        if (o->id == 0x34) {
            if (o->unk251 == 2) {
                obj_box_contact_test(rec, o, x, y, z, scale, radius, i, 120.0f, 250.0f, 120.0f, -130.0f, 0.0f);
            } else {
                obj_box_contact_test(rec, o, x, y, z, scale, radius, i, 130.0f, 140.0f, 250.0f, -50.0f, 0.0f);
            }
        }
    }
}
u16 math_atan2_u16(f32 arg0, f32 arg1, s32 arg2);
f32 obj_vec_to_record(u8 *arg0, u8 arg1, u16 *arg2, f32 *arg3, f32 *arg4);
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, void *, void *, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);

// player_find_visible_target: picks the player (0..24 of g_objects) that `rec` can see best (P151). Skips empty or
// inactive slots (+0x1CA, +0x2FA, flag 0x40 of +0xF8 clear), rec itself and `skip`. A candidate must be closer than
// the best so far (initially 1e7, 40000 when skip is 0xFE) - or, when the best one is stunned (+0x104) and this one
// is not, at any distance - lie within the heading cone `cone` (in 1/256 turns, half width) and within 16/256 of the
// pitch `pitch`, and have a clear ray (collision_ray_cast from rec's position + 80 up) or a hit beyond it. Writes the
// winner's direction to *outDir and returns its number, 0xFF for none. (Like obj_find_seen_player, the asm passes a 6th
// argument 0 to obj_vec_to_record.)
/* was func_1505DADC */
s32 obj_find_visible_target(u8 *rec, u16 *outDir, s32 pitch, s32 skip, s32 cone) {
    struct127 *self = (struct127 *)rec;
    struct127 *o;
    f32 best = (u8)skip == 0xFE ? 40000.0f : 10000000.0f;
    u8 bestStunned = 0;
    u8 bestIdx = 0xFF;
    u8 i;
    u16 dir;
    f32 h2, dy, d2;
    f32 tri, nx, ny, nz, hx, t;

    for (i = 0; i < 25; i++) {
        o = &g_objects[i];
        if (o->interaction_state == 0 || ((u8 *)o)[0x1CA] == 0 || (u8)(self - g_objects) == i || !(o->unkF8 & 0x40) ||
            (u8)skip == i || o->unk2FA == 0) {
            continue;
        }
        d2 = obj_vec_to_record(rec, i, &dir, &h2, &dy);
        if (!(d2 < best) && (o->stunned != 0 || bestStunned == 0)) {
            continue;
        }
        if ((u8)(((s32)(dir - self->unk7A) >> 8) + (u8)cone) >= (u8)cone * 2) {
            continue;
        }
        if ((u8)((u8)(math_atan2_u16(sqrtf(h2), -dy, 0) >> 8) - (u8)pitch + 0x10) >= 0x20) {
            continue;
        }
        if (collision_ray_cast(self->x_position, self->y_position + 80.0f, self->z_position, o->x_position - self->x_position,
                          o->y_position - self->y_position, o->z_position - self->z_position, &tri, &nx, &ny, &nz, &hx,
                          &t, 0, 0, 0.0f) != 0) {
            t = t * t;
            if (t < d2) {
                continue;
            }
        }
        bestStunned = o->stunned;
        bestIdx = i;
        best = d2;
        *outDir = dir;
    }
    return bestIdx;
}
f32 obj_vec_to_record(u8 *arg0, u8 arg1, u16 *arg2, f32 *arg3, f32 *arg4);

/* First player 0..g_last_player_index (live object in g_objects) that `rec` sees: closer than rec +0x3C * scale / 2
 * (obj_vec_to_record gives the squared distance and the direction) and within the cone of width `cone` around rec's
 * heading +0x76 ((u16)(heading - dir + cone / 2) < cone). Returns the player number, -1 for none. (The asm also
 * stores a 6th argument 0 for obj_vec_to_record, which its definition does not take; `unused` is not read.) */
/* was func_1505DDA8 */
s32 obj_find_seen_player(struct127 *rec, s32 unused, u16 cone, f32 scale) {
    s32 i;
    f32 r;
    f32 d;
    u16 dir;
    f32 dy;
    f32 h;

    for (i = 0; i <= g_last_player_index; i = (u8)(i + 1)) {
        if (g_objects[i].interaction_state == 0) {
            continue;
        }
        r = rec->xz_velocity * scale * 0.5f;
        d = obj_vec_to_record((u8 *)rec, i, &dir, &dy, &h);
        if (d < r * r && (u16)(*(u16 *)((u8 *)rec + 0x76) - dir + cone / 2) < cone) {
            return (s8)i;
        }
    }
    return -1;
}
/* was func_1505DF10 */
f32 obj_vec_to_record(u8 *arg0, u8 arg1, u16 *arg2, f32 *arg3, f32 *arg4) {
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f2;
    struct127 *temp_v0;

    temp_v0 = &g_objects[arg1];
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x18)) - temp_v0->y_position;
    temp_f12_2 = temp_v0->x_position - (*(f32 *)((u8 *)arg0 + 0x14));
    *arg4 = temp_f2;
    temp_f14_2 = (*(f32 *)((u8 *)arg0 + 0x1C)) - temp_v0->z_position;
    sp20 = temp_f12_2;
    sp1C = temp_f2;
    sp18 = temp_f14_2;
    temp_f12 = temp_f12_2 * temp_f12_2;
    *arg2 = math_atan2_u16(temp_f12_2, temp_f14_2, 0);
    temp_f14 = temp_f14_2 * temp_f14_2;
    *arg3 = temp_f12 + temp_f14;
    return temp_f12 + (temp_f2 * temp_f2) + temp_f14;
}
/* was func_1505DFDC */
void obj_anim_reset(struct127 *arg0) {
    s32 id;
    struct_eu_anim *anim = (struct_eu_anim *)arg0->unk2D0;

    arg0->unk84.uh = 0xFFFF;
    if (anim != NULL) {
        id = arg0->id;
        anim->unk28 = 0;
        bzero(anim->unk40, 0x3A0);
        anim->unk40[1] = D_800C52F0[id] + 1;
        anim->unk210[1] = D_800C52F0[id] + 1;
        anim->unk30 = 0;
        anim->unk34 = 0;
    }
}
/* was func_1505E060 */
void anim_state_snapshot(struct_eu_anim *arg0) {
    arg0->unk6 = arg0->unk4;
    arg0->unkC = arg0->unk8;
    arg0->unk14 = arg0->unk10;
    arg0->unk24 = arg0->unk20;
    arg0->unk1C = arg0->unk18;
    arg0->unk39 = arg0->unk38;
    arg0->unk2C = arg0->unk28;
    bcopy(arg0->unk40, arg0->unk210, 0x1D0);
}
s32 *asset_rec_fetch_block(s32, u8 *, s32, s32);
s32 asset_lookup_records(u8 *, s32, s32, u32, ...);
extern s32 g_anim_file_bases[]; /* was D_800866AC */
extern u16 g_anim_last_frame_92[]; /* was D_800997B8 */

/* P60: start / restart animation `id` on the animation state `anim` (struct_eu_anim) of object `obj` (may be NULL;
 * animmodel_start_anim passes NULL / NULL). entry: the object's animation table entry (u16 file id, u16 callback index,
 * s32 value for obj +0x1C4), NULL = file id 2 * id.
 * The animation restarts when `restart` is set (no blend then), the id differs from anim +4 (low 15 bits) or, with
 * an object, from obj +0x84 (or that is 0xFFFF, or obj +0x103 is set). Else only the speed and the hold flag change
 * (and the frame, when D_800C35EA == 1 and the animation holds).
 * Restart: the previous animation is kept for blending (anim +6..+0x2C and the 0x1D0 block copied to +0x210) unless
 * the blend countdown +0x3C is >= 600; the countdown restarts at 0x3FF (blend >= 1: step +0x3A = 500 / blend; a
 * blend into the same animation reverses the countdown); the animation header (file `entry[0]`, 2 words: data
 * address / size, +0x28 = the next word) is looked up with asset_rec_fetch_block (object model +0x58) or asset_lookup_records,
 * then DMAed to anim +0x40 (no header: obj_anim_reset). +0x18 = last frame (header byte 3; 0xFF: per type).
 * With an object, its contact / flag state is reset and obj_model_reset(obj) runs. */
/* was func_1505E0C4 */
s32 anim_start_entry(struct127 *obj, s32 entry_addr, u8 *anim_addr, s32 unused, s32 restart, s32 id, s32 set,
                  f32 speed, f32 blend, f32 frame, f32 loop_start, s32 hold) {
    struct_eu_anim *anim = (struct_eu_anim *) anim_addr;
    u16 *entry = (u16 *) entry_addr;
    s32 start = 0;
    s32 kind;
    s32 index;
    s32 file;
    s32 *hdr;
    s32 data = 0;
    s32 size = 0;
    s16 count;
    s32 size16;
    u32 flags;
    u8 buf[0x38];

    if (restart != 0) {
        start = 1;
        blend = 0.0f;
    } else if (id != (anim->unk4 & 0x7FFF)) {
        start = 1;
    } else if (obj != NULL && (id != obj->unk84.uh || obj->unk84.uh == 0xFFFF || obj->unk103 != 0)) {
        start = 1;
    }

    if (start == 0) {
        if (obj != NULL) {
            obj->animation_speed = speed;
        }
        anim->unk10 = speed;
        if (hold != 0) {
            anim->unk4 |= 0x8000;
        } else {
            anim->unk4 &= 0x7FFF;
        }
        if (D_800C35EA == 1 && (anim->unk4 & 0x8000)) {
            anim->unk8 = frame;
        }
    } else {
        kind = 10;
        if (obj != NULL) {
            index = (s32) ((u8 *) obj - (u8 *) g_objects) / (s32) sizeof(struct127);
            set = obj->unk6;
            kind = 2;
        }
        file = (entry != NULL) ? entry[0] : id * 2;
        if (obj != NULL) {
            obj->unk84.uh = id;
            obj->animation_speed = speed;
            obj->unk138 = 0;
            obj->unk103 = 0;
            obj->unkB4 = 0.0f;
            obj->unk1C4 = *(s32 *) (entry + 2);
            if (index < g_player_count) {
                g_objects[index].unk31C->unk58 = 0;
                g_objects[index].unk31C->unk5A = 0;
                g_objects[index].unk31C->unk59 = 0;
            }
        }
        if (anim->unk28 != 0) {
            count = anim->unk3C;
            if (1.0f <= blend) {
                anim->unk3A = 500 / (s16) (s32) blend;
                if (anim->unk3C > 0 && id == (anim->unk6 & 0x7FFF)) {
                    anim->unk3C = 0x3FF - anim->unk3C;
                    count = 0;
                } else if (count < 600) {
                    anim->unk3C = 0x3FF;
                }
            } else {
                anim->unk3C = 0;
            }
            if (count < 600) {
                anim->unk6 = anim->unk4;
                anim->unkC = anim->unk8;
                anim->unk14 = anim->unk10;
                anim->unk24 = anim->unk20;
                anim->unk1C = anim->unk18;
                anim->unk39 = anim->unk38;
                anim->unk2C = anim->unk28;
                bcopy(anim->unk40, anim->unk210, 0x1D0);
            }
        }
        anim->unk4 = id;
        if (hold != 0) {
            anim->unk4 = id | 0x8000;
        }
        anim->unk8 = frame;
        anim->unk10 = speed;
        anim->unk20 = loop_start;
        anim->unk0 = (entry != NULL) ? g_anim_file_bases[entry[1]] : 0;

        if (obj != NULL && obj->unk58 != 0) {
            hdr = asset_rec_fetch_block(obj->unk58, buf, file, 2);
        } else {
            hdr = (s32 *) asset_lookup_records(NULL, 2, (s32) buf, 3, kind, set, file);
        }
        /* asm: with no header, data / size are stack leftovers; 0 here (= no animation) */
        if (hdr != NULL) {
            anim->unk28 = hdr[2];
            size = hdr[1];
            data = hdr[0];
        }
        if (size == 0) {
            obj_anim_reset(obj);
            return 0;
        }
        size16 = (size + 15) & ~15;
        if (size16 < 200) {
            rom_read_direct(data, anim->unk40, size16);
        } else {
            rom_dma_read(data, anim->unk40, size16, 1);
        }

        anim->unk18 = anim->unk40[3];
        if (anim->unk40[3] == 0xFF && obj != NULL) {
            switch (obj->id) {
                case 0x92:
                    anim->unk18 = g_anim_last_frame_92[obj->unk84.uh];
                    break;
                case 0xB7:
                case 0xB8:
                case 0xB9:
                    anim->unk18 = 641.0f;
                    break;
            }
        }
        if (obj != NULL) {
            obj->unk24E = 0;
            obj->unk1FC = (obj->unk1FC | 2) & ~1;
            flags = (obj->stunned == 0) ? 0x30B : 0x303;
            obj->unkF4 &= ~flags;
            if (obj->unkF4 & 0x20) {
                obj->unkF4 |= 2;
                obj->unkF4 &= ~0x20;
            }
            obj->unk1FD = (anim->unk40[7] & 0x20) ? anim->unk40[0xB] : 0;
        }
        if (anim->unk40[5] == 0) {
            anim->unk28 = 1;
        }
    }
    if (obj != NULL && start != 0) {
        obj_model_reset(obj);
    }
    return 0;
}
/* P38: start animation `anim` of an object (+4 = type): skipped when the cutscene flag D_800C3638 is set and
 * D_800C3A78 is clear or cutscene_obj_takes_part(obj) says so, for type 0xFF, a type without animations (D_800C5A90[type] == 0),
 * no model (+0x2D0) or anim out of range. No table D_800D1588[type] or an entry id >= 30000: obj_anim_reset(obj).
 * Entry id 999 (or table[0] == 999): nothing. Else anim_start_entry(obj, &table[anim], model, 0, 0, anim, 0, speed,
 * arg3 (0 unless +0x2FF), arg4, arg5, arg6). */
/* was func_1505E650 */
void obj_start_anim(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    u8 *obj = (u8 *) arg0;
    s32 type = obj[4];
    s32 anim = arg1;
    s32 n;
    s32 model;
    u16 *tbl;
    u16 *e;

    if (D_800C3638 != 0) {
        if (D_800C3A78 == 0) {
            return;
        }
        if (cutscene_obj_takes_part(arg0) != 0) {
            return;
        }
    }
    if (obj[4] == 0xFF) {
        return;
    }
    n = (u16) D_800C5A90[obj[4]];
    if (n == 0) {
        return;
    }
    model = *(s32 *) (obj + 0x2D0);
    if (model == 0) {
        return;
    }
    if (anim >= n) {
        return;
    }
    tbl = (u16 *) D_800D1588[type];
    if (tbl == NULL) {
        obj_anim_reset(arg0);
        return;
    }
    if (anim >= (u16) D_800C5A90[type]) {
        return;
    }
    if (tbl[0] == 999) {
        return;
    }
    e = tbl + anim * 4;
    if (*e == 999) {
        return;
    }
    if (*e >= 30000) {
        obj_anim_reset(arg0);
        return;
    }
    if (obj[0x2FF] == 0) {
        arg3 = 0.0f;
    }
    anim_start_entry(arg0, (s32) e, (u8 *) model, 0, 0, anim, 0, arg2, arg3, arg4, arg5, arg6);
}
/* was func_1505E7CC */
u32 obj_find_reaction_row(s32 arg0, struct127 *arg1)
{
  s32 temp_v1;
  u32 temp_v0_2;
  u32 var_v1;
  u8 *temp_a0;
  u8 *var_a1;
  u8 temp_v0;
  temp_v0 = arg1->id;
  if (temp_v0 == 0xFF)
  {
    return 0U;
  }
  temp_v1 = D_800D1588[temp_v0];
  if (temp_v1 == 0)
  {
    return 0U;
  }
  temp_v0_2 = *((u32 *) (((u8 *) temp_v1) + (-4)));
  if (temp_v0_2 == 0)
  {
    return 0U;
  }
  temp_v0_2 = temp_v0_2 / 24U;
  temp_a0 = *((u8 **) (((u8 *) temp_v1) + (-8)));
  if (temp_a0 == 0)
  {
    return 0U;
  }
  var_v1 = 0;
  if (temp_v0_2 != 0)
  {
    var_a1 = temp_a0;
    loop_10:
    if (arg0 == (*var_a1))
    {
      return var_v1;
    }
    var_v1 += 1;
    var_a1 += 0x18;
    if (var_v1 < temp_v0_2)
    {
      goto loop_10;
    }
  }
  return 0U;
}
// hit_reaction_advance: P213: plays the next phase of object `obj`'s current hit reaction (port P209: void; the
/* first argument is not read). Reaction row unk106 of the type's row table (D_800D1588[id] - 8, 0x18-byte rows:
 * +0 kind, +4 sound, +8 unk10F value, +0xA three phases {u16 anim, u8 speed %, u8 flags}). Phase 0 (unk105)
 * first: unk10F from the row, jump flag and the controller's byte 0x26 cleared, the row's sound (0x33 through
 * obj_sfx_play_vol, others obj_sfx_play) when sound_word_resolve allows it; type 0x5E held by a carrier blends with 0.
 * Move flags 0x000C014E cleared. Phases 0..2: hit bit unk10B bit 0 = the phase flag's bit 0; phase 0 of a living
 * player-like object (unk127 != 0xFF, controller byte 0x197) shakes the camera (screen_tint_start). A living object
 * past its last phase gets an end action (player_hit_reaction: type 0x9A 14, 0x53 10, swimming 4, ground kinds 14 / 19
 * outside level 0x34 13, else by the row kind) and phase 3. Otherwise the hit timer unk10C = flags x 100 (flags
 * 200: move flag 8 and hit bit 0) and the phase's animation starts (obj_start_anim, speed % / 100, 1 when 0,
 * blend 6); no animation (or phase 3+, timer 20000) ends the reaction: stun, hit bits and unk10F cleared, a
 * player's controller byte 0x58 and flags 0x01000200 of unkF8 cleared. */
void screen_tint_start(s32, s32, s32, s32, s32, s32);
void obj_sfx_play(s32, struct127 *);
/* was func_1505E874 */
void obj_hit_reaction_advance(u8 arg0, struct127 *obj) {
    f32 blend;
    u16 row;
    u8 *rows;
    u8 *r;
    u8 *cell;
    u8 phase;
    u8 flags;
    u8 player;
    s32 sound;
    s32 last;
    s32 end;
    f32 speed;
    u16 anim;
    s32 m;

    blend = 6.0f;
    if (obj->id == 0xFF) {
        return;
    }
    row = obj->unk106;
    rows = *(u8 **)((u8 *)D_800D1588[obj->id] - 8);
    if (rows == NULL) {
        return;
    }
    if (obj->unk105 == 0) {
        r = rows + row * 0x18;
        obj->disable_jump = 0;
        obj->unk10F = r[8];
        if (obj->unk31C != NULL) {
            ((u8 *)obj->unk31C)[0x26] = 0;
        }
        if (obj->id == 0x5E && obj->unk13D != 0) {
            blend = 0.0f;
        }
        sound = *(s32 *)(r + 4);
        if (sound != 0 && sound_word_resolve(obj, &sound, 1) != 0) {
            if (sound == 0x33) {
                obj_sfx_play_vol(sound, obj, 0x5DC0);
            } else {
                obj_sfx_play(sound, obj);
            }
        }
    }
    obj->unkF4 &= ~0x000C014E;
    phase = obj->unk105;
    if (phase < 3) {
        r = rows + row * 0x18;
        cell = r + phase * 4;
        flags = cell[0xD] & 0xFE;
        obj->unk10B = (obj->unk10B & 0xFE) | (cell[0xD] & 1);
        player = obj->unk127;
        if (player != 0xFF && phase == 0 && obj->unk31C != NULL && obj->camera != NULL
            && ((u8 *)obj->unk31C)[0x197] != 0) {
            screen_tint_start(0xFF, 0, 0, 0xB4, 0x14, ((u8 *)obj->camera)[0x23D]);
            player = obj->unk127;
        }
        if (player != 0xFF && obj->health == 0) {
            phase = obj->unk105;
            last = phase;
            while (*(u16 *)(r + last * 4 + 0xA) != 0) {
                last++;
            }
            if (last < 2) {
                last = 2;
            }
            if (last == phase + 1) {
                if (obj->id == 0x9A) {
                    end = 14;
                } else if (obj->id == 0x53) {
                    end = 10;
                } else if (obj->in_water != 0) {
                    end = 4;
                } else {
                    m = obj->unk184 & 0x1F;
                    if ((m == 14 || m == 19) && g_level_id != 0x34) {
                        end = 13;
                    } else {
                        switch (r[0]) {
                            case 14:
                            case 15:
                                end = 16;
                                break;
                            case 16:
                                ((u8 *)obj->unk31C)[0x1AC] = 1;
                                g_cur_obj_cmd = (s32)0xFF010434;
                                objev_sound_300_1800();
                                g_cur_obj_cmd = (s32)0xFF070169;
                                objev_sound_alt_300_1800();
                                end = 0;
                                break;
                            case 32:
                            case 33:
                            case 37:
                            case 38:
                            case 51:
                            case 52:
                            case 72:
                                end = 0;
                                break;
                            case 44:
                                end = 8;
                                break;
                            case 45:
                            case 46:
                            case 47:
                                end = 7;
                                break;
                            case 66:
                                end = 12;
                                break;
                            case 67:
                                end = 11;
                                break;
                            default:
                                end = 1;
                                break;
                        }
                    }
                }
                player_hit_reaction(obj, end);
                obj->unk105 = 3;
                return;
            }
        }
        if (flags == 200) {
            obj->unkF4 |= 8;
            obj->unk10B |= 1;
        }
        obj->unk10C = flags * 100;
        phase = obj->unk105;
        cell = r + phase * 4;
        speed = cell[0xC] / 100.0f;
        anim = *(u16 *)(cell + 0xA);
        if (anim != 0) {
            obj->unk105 = phase + 1;
        }
        if (speed == 0.0f) {
            speed = 1.0f;
        }
    } else {
        obj->unk10C = 20000;
        speed = 1.0f;
        anim = 0;
    }
    if (anim == 0) {
        obj->unkF4 &= ~8;
        obj->stunned = 0;
        obj->unk10B = 0;
        obj->unk10F = 0;
        if (obj->interaction_state == 1) {
            ((u8 *)obj->unk31C)[0x58] = 0;
            obj->unkF8 &= ~0x01000200;
        }
    } else {
        obj_start_anim(obj, anim, speed, blend, 0.0f, 0.0f, 0);
    }
}
extern s32 g_obj0_mtx_block; /* was D_800CC8C4 */

/* was func_1505ED34 */
struct127 *obj_alloc_slot(void) {
    s32 sp1C;
    struct127 *sp18;
    s32 var_v0;
    struct127 *var_a0;

    var_v0 = 0;
    var_a0 = g_objects;
    if (g_objects->interaction_state != 0) {
loop_1:
        var_v0 += 1;
        var_a0 = (struct127 *)((u8 *)var_a0 + (0x32C));
        if (var_v0 < 0x19) {
            if (var_a0->interaction_state != 0) {
                goto loop_1;
            }
        }
    }
    if (var_v0 == 0x19) {
        var_a0 = g_objects;
        var_v0 = 0;
        if ((g_objects->interaction_state != 0x27) || (g_obj0_mtx_block != 0)) {
loop_6:
            var_v0 += 1;
            var_a0 = (struct127 *)((u8 *)var_a0 + (0x32C));
            if (var_v0 < 0x19) {
                if ((var_a0->interaction_state != 0x27) || (var_a0->unk1D4 != NULL)) {
                    goto loop_6;
                }
            }
        }
        if ((var_v0 != 0x19) && (var_a0->interaction_state != 0)) {
            sp1C = var_v0;
            sp18 = var_a0;
            obj_remove(var_a0, 0);
        }
    }
    if (var_v0 == 0x19) {
        var_a0 = g_objects;
        var_v0 = 0;
        if (g_objects->interaction_state != 0x27) {
loop_14:
            var_v0 += 1;
            var_a0 = (struct127 *)((u8 *)var_a0 + (0x32C));
            if (var_v0 < 0x19) {
                if (var_a0->interaction_state != 0x27) {
                    goto loop_14;
                }
            }
        }
        if ((var_v0 != 0x19) && (var_a0->interaction_state != 0)) {
            sp1C = var_v0;
            sp18 = var_a0;
            obj_remove(var_a0, 0);
        }
    }
    if ((var_v0 == 0x19) && (var_a0->interaction_state != 0)) {
        sp18 = var_a0;
        obj_remove(var_a0, 0);
    }
    sp18 = var_a0;
    obj_reset(var_a0);
    return sp18;
}
/* was func_1505EEB0 */
struct127 *obj_find_by_state(s32 state, s32 *arg1) {
    struct127 *tmp;
    s32 i;

    for (tmp = g_objects, i = 0; i < 25 && state != tmp->interaction_state; tmp++, i++) {
    }
    *arg1 = i;
    return tmp;
}

/* was func_1505EEF4 */
struct127 *obj_find_by_spawn(s32 arg0) {
    s32 i;
    struct127 *p = g_objects;
    for (i = 0; i < 25; i++) {
        if (p->interaction_state != 0 && p->unk13F == arg0) {
            return p;
        }
        p++;
    }
    return NULL;
}
/* was func_1505EFD0 */
struct127 *obj_find_by_link(s32 arg0) {
    s32 i;
    struct127 *p = g_objects;
    for (i = 0; i < 25; i++) {
        if (p->interaction_state != 0 && p->unk127 == arg0) {
            return p;
        }
        p++;
    }
    return NULL;
}
/* was func_1505F0AC */
struct127 *obj_find_by_id(s32 arg0) {
    s32 i;
    struct127 *p = g_objects;
    for (i = 0; i < 25; i++) {
        if (p->interaction_state != 0 && p->id == arg0) {
            return p;
        }
        p++;
    }
    return NULL;
}
/* was func_1505F188 */
void obj_reset(struct127 *arg0) {
    struct127 *temp_v1;
    struct127 *var_v0;

    temp_v1 = ((struct127 *)((u8 *)arg0 + 0x32C));
    var_v0 = arg0;
    if ((u32) arg0 < (u32) temp_v1) {
        do {
            var_v0 = (struct127 *)((u8 *)var_v0 + (4));
            (*(s32 *)((u8 *)var_v0 + -4)) = 0;
        } while ((u32) var_v0 < (u32) temp_v1);
    }
    arg0->unk2FD = 2;
    (*(s16 *)((u8 *)arg0 + 0x38)) = -0x2710;
    arg0->xz_scale = 1.0f;
    arg0->y_scale = 1.0f;
    arg0->unk118 = -10000.0f;
    arg0->unk180 = -10000.0f;
    arg0->unk1DC = 0xFF;
    arg0->unk127 = 0xFF;
    arg0->unk84.uh = 0xFFFF;
    arg0->unk13F = 0xFF;
    arg0->unk2C4 = (s32) &arg0->id;
    arg0->unk2C8 = 1;
    arg0->unk2C9 = 1;
    arg0->id = 0xFF;
    arg0->unk2CB = 0x32;
    arg0->unk48 = 1.0f;
    arg0->gravity = 3.3f;
    arg0->unk6E = (random_int() % 50U) + 0x32;
    obj_fade_reset(arg0);
    arg0->unk1DD = 0xFF;
    arg0->unk1DE = 0xFF;
    arg0->unk1DF = 0xFF;
    (*(s16 *)((u8 *)arg0 + 0x18C)) = 0;
    (*(s16 *)((u8 *)arg0 + 0x18E)) = 0;
    arg0->unk190 = 0;
    arg0->unk192 = 0;
    arg0->unk194 = 0;
    (*(s16 *)((u8 *)arg0 + 0x196)) = 0xA;
    (*(s16 *)((u8 *)arg0 + 0x198)) = 0xA;
    (*(s16 *)((u8 *)arg0 + 0x19A)) = 0;
    arg0->unk19C = 0;
}
void obj_ctrl_action_update(struct127 *, s32, s32, f32, s32); /* P102: arg3 = height, f32 */
s32 sound_word_resolve(struct127 *, s32 *, s32);
void rope_release(u8 *);
void obj_attached_model_fx_spawn(u8 *, u8, s32);
void obj_sfx_play(s32, struct127 *);
void swim_exit_water(struct127 *);
void obj_fade_command(struct127 *, u8, u8, u8, u8);
void objev_anim_38(void);
void actor_sound_stop(struct127 *);
extern s32 g_obj_id_by_slot1; /* was D_800CC3C8 */
extern u8 D_800CC69C;
extern char g_glide_sfx_cb_data[]; /* was D_800997E8 */
s32 sfx_cb_follow_object_anim(struct_eu_sfx *, s32, s32 *, struct11 *, s32, s32 *, u16 *);


/* P64: the jump / swim / glide handler of a walking record, once per walk-handler call (obj_ctrl_floor_contact family).
 * `pad` = the controller: +0 buttons (0x8000 = A / jump, 0x4000 = B, 0x2000 = Z, 0x10), +3 stick y (s8).
 * D_800CC288 = the buttons pressed this frame. ctl = rec->unk31C. Sections:
 *   1. guards: stunned / dead stop the record (target speed 0); nothing while ctl +0x46 > 0, ctl +0x36 >= 100 or
 *      ctl +0x6B. `height` = rec +0x28 (ground clearance), -150 with ctl +0x4E == 2 (carried state), 0 with
 *      ctl +0x4F == 2, +50 while rising.
 *   2. in water (rec +0xAD, not ctl +0x95, anim != 0x262): surface jump-out (A near the surface), B / swim
 *      strokes, treading water; animation and obj_ctrl_action_update (in-water move); returns.
 *   3. rec +0x137 == 1 (hanging): stick up climbs (0xEA), stick down drops (0x38), A / ctl +0x84 lets go (0x40);
 *      returns when an animation was started.
 *   4. jump start: riding a record of id 0x28 (not level 0x23) / 0x8A / 0x23 (rec +0x65), or on the ground / ctl
 *      +0x55: A starts a jump (0x32, the run jump 0x37 / 0x19E, the high jump 0x279 with ctl +0x17, the item jump
 *      0x43 with ctl +8, the super jump with ctl +0x1A, the Z long jump 0xEB) with floor-kind and D_800CC69C
 *      (low gravity) adjustments; a ride is left (obj_reset_link_state) with a push-off speed.
 *   5. obj_ctrl_action_update (air move), then the double jump (ctl +0x98 / +0x95: 0x37 again), the high-fall 0x3B, and
 *      the helicopter glide (ctl +0x31: start 0xE9 with the sound 0x61E, then the spin-down counter); the
 *      animation; the sound of section 4 (obj_sfx_play); releasing A cuts a rising jump (gravity 6.2). */
/* was func_1505F298 */
void obj_jump_swim_glide_update(struct127 *rec, u8 *pad) {
    struct126 *ctl;
    s32 sound = 0;         /* sp88: sound id resolved by sound_word_resolve */
    f32 speed = 1.0f;      /* sp84: animation speed */
    f32 jump_v;            /* sp80 */
    u8 glide = rec->unk31C->unk31;
    f32 blend = 0.0f;      /* f12 */
    f32 height;            /* f14 */
    s32 buttons;           /* sp68 */
    s32 anim;
    s32 ride;              /* id + 1 of the ridden record */
    s32 ride_jump;
    s32 jumped;
    u16 a;

    /* 1. guards */
    if (rec->stunned != 0 || rec->health == 0) {
        rec->target_speed = 0.0f;
        return;
    }
    ctl = rec->unk31C;
    if (*(s16 *)((u8 *)ctl + 0x46) > 0 || ctl->unk36 >= 100 || ctl->unk6B != 0) {
        return;
    }
    height = rec->unk28;
    if (ctl->unk4E == 2) {
        height = height - 150.0f;
    } else if (ctl->pad4F[0] == 2) {
        height = 0.0f;
    } else if (rec->y_velocity > 0.0f) {
        height += 50.0f;
    }
    if (rec->unk110 != 0) {
        buttons = *(u16 *)pad & ~0x2000;
    } else {
        buttons = *(u16 *)pad;
    }

    /* 2. in water */
    if (rec->in_water != 0 && ctl->unk95 == 0 && rec->unk84.uh != 0x262) {
        anim = 0; /* the asm reads a stack slot here when in_water != 1 (never written on that path): UNVERIFIED */
        if (rec->in_water == 1) {
            blend = 2.0f;
            anim = 0;
            if ((D_800CC288 & 0x8000) && (g_level_id != 0x29 || (s16)ctl->unk8 <= 0)
                && rec->unk118 - 60.0f - 30.0f < rec->y_position) {
                /* jump out of the water */
                swim_exit_water(rec);
                rec->unk31C->unk31 = 0;
                ctl = rec->unk31C;
                anim = 0x32;
                blend = 0.0f;
                if (ctl->pad79[2] != 7 && ctl->pad79[2] != 8) {
                    ctl->unk31 = 1;
                }
                ctl = rec->unk31C;
                a = ctl->unk4C;
                rec->unk78 = a;
                rec->unk7A = a;
                rec->unk76 = a;
                if (*(u16 *)((u8 *)ctl + 0x68) != 0 && (((a - *(u16 *)((u8 *)ctl + 0x68)) + 0x4000) & 0x8000)) {
                    rec->xz_velocity = 0.0f;
                    rec->disable_run = 0xFF;
                }
                rec->unkAE = 0xC;
                rec->y_velocity = 46.0f;
                rec->unk81 = 2;
                rec->unk83 = 0;
                rec->gravity = 3.3f;
            }
            rec->target_speed = 0.0f;
            if ((D_800CC288 & 0x4000) && !(*(u16 *)pad & 0x10)) {
                ctl = rec->unk31C;
                if ((s8)ctl->pad17[0xB] < 0x69) {
                    ctl->pad17[0xB] = 0xF;
                }
            }
            ctl = rec->unk31C;
            if ((rec->xz_velocity > 2.0f && ctl->pad17[0xA] != 0)
                || (ctl->pad17[0xA] == 0
                    && ((s8)ctl->pad17[0xB] > 0 || (!(*(u16 *)pad & 0x10) && (*(u16 *)pad & 0x4000))))) {
                if (anim != 0x32) {
                    /* swim stroke */
                    blend = 9.0f;
                    rec->unk83 = 0;
                    if (rec->unk118 - 60.0f < rec->y_position) {
                        speed = 1.2f;
                        anim = 0x22;
                        rec->target_speed = 15.0f;
                    } else {
                        speed = 1.2f;
                        anim = 0xCE;
                        rec->target_speed = 23.0f;
                    }
                }
            }
        }
        if (anim == 0) {
            /* treading water */
            blend = 10.0f;
            speed = 1.2f;
            anim = 0xD1;
            if (rec->unk118 - rec->y_position < 70.0f) {
                anim = 0xCC;
                speed = 0.9f;
            }
            rec->target_speed -= 0.2f;
            if (rec->target_speed < 0.0f) {
                rec->target_speed = 0.0f;
            }
        }
        ctl = rec->unk31C;
        if (rec->in_water != 0 && rec->unk13C != 0) {
            blend = 7.0f;
            anim = 0xCB;
        }
        if (ctl->unk11A != 0 || (ctl->unk78 != 0 && ctl->unk78 != 0x27)) {
            obj_ctrl_action_update(rec, 0, 0, height, 1);
        }
        if (anim != 0) {
            obj_start_anim(rec, anim, speed, blend, 0.0f, 0.0f, 0);
        }
        return;
    }

    /* 3. hanging */
    if (rec->unk137 == 1) {
        anim = 0;
        if (ctl->pad53 == 0) {
            if ((s8)pad[3] > 0x32) {
                speed = 2.2f;
                ctl->unk54 = 0xC;
                anim = 0xEA;
                rec->unk137 = 0;
                rec->disable_run = 0x10;
                rec->unk81 = 1;
                rec->gravity = 5.0f;
                rec->y_velocity = 48.0f;
            } else if ((s8)pad[3] < -0x32) {
                anim = 0x38;
                rec->unk137 = 0;
                rec->gravity = 3.5f;
            }
        }
        if ((D_800CC288 & 0x8000) || rec->unk31C->unk84 != 0) {
            rec->unk137 = 2;
            anim = 0x40;
            speed = 3.0f;
        }
        if (anim != 0) {
            obj_start_anim(rec, anim, speed, 4.0f, 0.0f, 0.0f, 0);
            return;
        }
    }

    /* 4. jump start */
    ride = 0;
    ride_jump = 0;
    anim = 0;
    if (rec->unk65 != 0) {
        u8 id = ((u8 *)&g_obj_id_by_slot1)[rec->unk65 * 0x32C]; /* = g_objects[rec->unk65 - 1].id */
        if ((id == 0x28 && g_level_id != 0x23) || id == 0x8A || id == 0x23) {
            ride = id + 1;
            ride_jump = 1;
        }
    }
    if (ride != 0 || height <= 0.0f || rec->unk31C->unk55 != 0) {
        rec->unk137 = 0;
        jumped = 0;
        jump_v = 0.0f;
        if ((D_800CC288 & 0x8000) && rec->unk31C->unk11A != 1 && rec->unk31C->unk11A != 3
            && (ride != 0 || (rec->unk13C < 100 && rec->disable_jump == 0 && rec->disable_run != 0xFF))) {
            jumped = 1;
            jump_v = 15.0f;
            rec->unk100 &= 0xFE;
            if (ride_jump != 0) {
                obj_fade_command(rec, 1, 0xFF, 0, 0);
            }
            ctl = rec->unk31C;
            if (ctl->pad17[0] != 0) {
                /* high jump */
                jump_v = 0.0f;
                anim = 0x279;
                speed = 1.25f;
                rec->unk84.uh = 0;
                rec->disable_jump = 0xA;
                rec->disable_run = 0xFF;
                rec->unk83 = 0xFF;
            } else if ((s16)ctl->unk8 != 0) {
                /* item jump */
                rec->unk83 = 0xFF;
                rec->disable_run = 0xFF;
                obj_start_anim(rec, 0x43, 1.3f, 2.0f, 0.0f, 0.0f, 0);
                anim = 0;
                jumped = 0;
            } else {
                anim = 0x32;
                if (ctl->pad17[3] != 0) {
                    /* super jump */
                    jump_v = 0.0f;
                    rec->disable_run = 0xFF;
                    rec->unk81 = 1;
                    rec->y_velocity = 47.0f;
                    rec->gravity = 6.0f;
                } else if (!(buttons & 0x2000) || ctl->pad79[2] == 7 || ctl->pad79[2] == 8) {
                    /* normal / run jump */
                    if (rec->disable_run != 0) {
                        rec->disable_run = 0;
                        a = ctl->unk4C;
                        rec->unk76 = a;
                        rec->unk7A = a;
                    }
                    anim = 0x32;
                    if (rec->xz_velocity < 9.0f) {
                        jump_v = 0.0f;
                        ctl->unk31 = 1;
                    } else {
                        speed = 0.8f;
                        ctl->unk31 = 2;
                        anim = 0x37;
                        if (rec->unk31C->unk78 == 0x21) {
                            anim = 0x19E;
                            speed = 1.4f;
                        }
                    }
                    if (rec->unk31C->pad79[2] == 7 || rec->unk31C->pad79[2] == 8) {
                        rec->unk31C->unk31 = 0;
                    }
                    if (rec->unk31C->unk4E == 1) {
                        rec->y_velocity = 40.0f;
                    } else {
                        rec->y_velocity = 59.0f;
                    }
                    if (rec->unk31C->unk4E == 2) {
                        rec->y_velocity = 80.0f;
                        sound = 0x7E2;
                    }
                    rec->gravity = 4.0f;
                    if ((rec->unk184 & 0x1F) == 0xC) {
                        rec->y_velocity *= 0.7f;
                    }
                    if ((rec->unk184 & 0x1F) == 0x13) {
                        anim = 0x32;
                        rec->y_velocity *= 0.55f;
                    }
                    if (D_800CC69C != 0) {
                        rec->unk81 = 0x82;
                    } else {
                        rec->unk81 = 2;
                    }
                } else {
                    /* Z long jump */
                    if (D_800CC69C == 0) {
                        rec->unk81 = 1;
                    } else {
                        rec->unk81 = 0x81;
                    }
                    jump_v = 0.0f;
                    speed = 1.08f;
                    rec->disable_run = 0x17;
                    rec->unk83 = 0x64;
                    anim = 0xEB;
                    if (D_800CC69C != 0) {
                        rec->xz_velocity = rec->xz_velocity;
                        rec->y_velocity *= 1.4f;
                        rec->gravity = 3.8f;
                    }
                }
            }
        }
        if (jumped != 0) {
            if (sound != 0 && sound_word_resolve(rec, &sound, 1) != 0) {
                obj_sfx_play(sound, rec);
            }
            glide = 0;
            if (ride != 0) {
                /* push off the ridden record */
                rec->xz_velocity = 20.0f;
                if (ride == 0x29) {
                    obj_reset_link_state(rec->unk65 - 1, 0xE);
                } else if (ride == 0x8B) {
                    obj_reset_link_state(rec->unk65 - 1, 5);
                    rec->xz_velocity = 30.0f;
                    if (D_800BE616 != 0) {
                        rec->unk7A = 0x3000;
                        if (rec->z_position > 0.0f) {
                            rec->unk7A = 0xB000;
                        }
                    }
                } else if (ride == 0x24) {
                    obj_reset_link_state(rec->unk65 - 1, 0xE);
                    rec->xz_velocity = 27.0f;
                }
                rec->unk31C->unk30 = 0;
                rec->immune = 0x14;
                rec->unk76 = rec->unk7A + 0x1200;
                rec->unk65 = 0;
                rec->disable_run = 0xFF;
                rec->y_velocity = 30.0f;
                rec->unk31C->unk31 = 0;
            }
            sound = 0;
            rec->unk31C->unk55 = 0;
            if (rec->unk31C->unk4E != 0) {
                rec->unkA9 = 5;
            }
            if (anim != 0xEB && anim != 0x279) {
                rec->unk83 = 0;
                rec->unk28 = 80.0f;
            }
            if (rec->unk31C->unk4E != 2) {
                obj_start_anim(rec, anim, speed, 2.0f, jump_v, 0.0f, 0);
            }
            height = 25.0f;
            rec->unkB8 = 0.0f;
            rec->unk110 = 0;
            rec->unk100 &= 0x53;
        }
    }

    /* 5. in the air */
    obj_ctrl_action_update(rec, buttons, D_800CC288, height, 0);
    anim = 0;
    ctl = rec->unk31C;
    blend = 2.0f;
    if ((ctl->pad98[0] != 0 || ctl->unk95 != 0) && rec->disable_jump == 0 && (D_800CC288 & 0x8000)) {
        /* double jump */
        a = ctl->unk4C;
        rec->unk7A = a;
        rec->unk76 = a;
        ctl->unk31 = 1;
        rec->unk80 = 0xA;
        rec->unk83 = 0;
        rec->unk100 |= 8;
        rec->disable_run = 0;
        rec->unk100 &= 0xDE;
        anim = 0x37;
        speed = 1.3f;
        if (rec->in_water == 0) {
            rec->y_velocity = 40.0f;
            rec->gravity = 3.2f;
        }
        rec->xz_velocity = rec->unk44 * 0.6f + 15.0f;
        if (rec->unk44 < 4.0f) {
            rec->unk7A = rec->unk76 = rec->unk76 + 0x8000;
        }
        rec->unk31C->unk95 = 0;
        rec->unk31C->unk97 = 0;
        if (rec->unk31C->pad98[0] != 0) {
            rope_release((u8 *)rec);
            anim = 0x37;
            blend = 2.0f;
        }
        rec->unk31C->unk54 = 0;
    } else if ((D_800CC288 & 0x8000) && ctl->unk4E == 0) {
        /* high fall */
        if (rec->unk84.uh != 0x3B && rec->unk84.uh != 0x3C && rec->unk137 == 0 && rec->unk13C == 0
            && ctl->unk95 == 0 && ctl->unk31 == 0 && height > 55.0f) {
            if (rec->unk118 != -10000.0f && rec->unk118 - rec->unk180 > 100.0f) {
                rec->unk81 = 1;
                rec->disable_run = 0x78;
                rec->unk137 = 0;
                anim = 0x3B;
                rec->gravity = 6.0f;
                rec->unk1CC = rec->y_position;
            }
        }
    }
    if (D_800BE616 == 0 && glide != 0 && rec->in_water == 0 && rec->unk13C <= 100 && rec->id != 0x96) {
        ctl = rec->unk31C;
        if (ctl->unk31 != 0 && ctl->unk4E == 0) {
            if (ctl->unk31 < 3) {
                /* helicopter glide start */
                if ((D_800CC288 & 0x8000) && rec->unk28 > 1.0f) {
                    blend = 6.0f;
                    anim = 0xE9;
                    rec->xz_velocity *= 0.3f;
                    ctl->unk31 = 3;
                    rec->y_velocity = 0.0f;
                    rec->unk81 = 1;
                    rec->gravity = 1.0f;
                    rec->unk1CC = rec->y_position;
                    if (rec->unk84.uh != 0xE9) {
                        actor_sound_stop(rec);
                        sfx_emitter_start(0x61E, rec->x_position, rec->y_position, rec->z_position, 0x7FFF, 0x1F4, 0xC8,
                                      (s32)sfx_cb_follow_object_anim, rec, (s32)g_glide_sfx_cb_data, 0, 0);
                        obj_attached_model_fx_spawn((u8 *)rec, 0xFF, 1);
                        anim = 0xE9;
                        blend = 6.0f;
                    }
                }
            } else {
                /* gliding: count up; A held keeps it to 0x3E frames, else 0x13 */
#ifdef PORT
                /* P326 option "Longer tail spin": while A is held the spin lasts to 0x79 instead of 0x3E, i.e.
                 * 3 + 2 * (0x3E - 3): twice the hover. The rise (< 0xD), the spin-up (< 0x11) and the early stop
                 * when A is released (>= 0x13) are unchanged. */
#define GLIDE_HOLD_MAX (port_option(PORT_OPT_LONG_TAILSPIN) ? 0x79 : 0x3E)
#else
#define GLIDE_HOLD_MAX 0x3E
#endif
                ctl->unk31 += D_800BE9A0;
                if (rec->unk31C->unk31 < 0xD) {
                    rec->y_velocity = 8.0f;
                }
                if (rec->unk31C->unk31 < 0x11) {
                    rec->animation_speed += 0.25f;
                } else {
                    rec->animation_speed += (0.6f - rec->animation_speed) * 0.1f;
                }
                anim = 0xE9;
                speed = rec->animation_speed;
                rec->unk31C->pad3C[0] = 6;
                if ((!(*(u16 *)pad & 0x8000) && rec->unk31C->unk31 >= 0x13) || rec->unk31C->unk31 >= GLIDE_HOLD_MAX) {
                    rec->disable_run = 0xFF;
                    rec->unk100 = 0x55;
                    rec->unk31C->unk31 = 0;
                    rec->gravity = 4.5f;
                    objev_anim_38();
                    blend = 2.0f;
                    anim = 0;
                } else {
                    rec->unk80 = 1;
                    rec->unkAA = 0x4B;
                    rec->unk83 = 1;
                    if (rec->y_velocity < -8.0f) {
                        rec->y_velocity = -8.0f;
                    }
                }
            }
        }
    }
    if (anim != 0) {
        obj_start_anim(rec, anim, speed, blend, 0.0f, 0.0f, 0);
    }
    if (sound != 0) {
        obj_sfx_play(sound, rec);
    }
    if ((rec->unk81 & 7) == 2 && !(*(u16 *)pad & 0x8000)) {
        rec->unk81 = rec->unk81 - 1;
        rec->gravity = 6.2f;
    }
}
#undef GLIDE_HOLD_MAX
void player_context_action(struct127 *, s32, f32, s32, s32); /* P157: no return value (asm leaves a scratch v0). P102: arg2 = height (f32, was float bits in s32) */
s32 player_item_action(struct127 *, s32, s32, f32, s32, s32, s32, s32, s32); /* P102: arg3 = height */
s32 hint_action_has_hint(u8);
extern s32 g_obj_id_by_slot1; /* was D_800CC3C8 */
extern u16 *D_800CC6A4;

/* was func_1506045C */
void obj_ctrl_action_update(struct127 *arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    s32 sp4C;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 var_t1;
    s32 var_t2;
    s32 var_t4;
    struct126 *temp_v1;
    struct126 *temp_v1_2;
    u16 temp_v0;
    u8 temp_a0;
    u8 temp_t0;
    u8 temp_t8;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 var_s0;

    var_t4 = 0;
    if (D_800C35EA != 1) {
        sp40 = 0;
        temp_v1 = arg0->unk31C;
        var_t1 = 0;
        var_t2 = 0;
        temp_v0 = (*(u16 *)((u8 *)temp_v1 + 0x72));
        if ((temp_v0 != 0) && (arg4 == 0)) {
            if (g_frame_ticks < (s32) temp_v0) {
                (*(u16 *)((u8 *)temp_v1 + 0x72)) = (u16) (temp_v0 - g_frame_ticks);
            } else {
                (*(u16 *)((u8 *)temp_v1 + 0x72)) = 0U;
                var_t2 = 1;
            }
        }
        temp_v0_2 = arg0->unk31C->pad79[3];
        temp_t8 = arg0->unk31C->unk75 & ~0x80;
        var_s0 = temp_t8;
        if ((temp_v0_2 != 0) && (temp_t8 == 0)) {
            var_s0 = temp_v0_2;
        }
        if ((g_level_id != 0x29) && (g_level_id != 0x2E) && (arg0->unk31C->unk78 == 0) && (*D_800CC6A4 & 0x20)) {
            sp4C = 0;
            sp44 = var_t2;
            sp3C = 0;
            var_t1 = 0;
            var_t4 = 0;
            if (hint_action_has_hint(var_s0) != 0) {
                var_s0 = 0x1A;
            }
        }
        temp_v1_2 = arg0->unk31C;
        temp_t0 = temp_v1_2->unk78;
        if (temp_t0 == 0x1A) {
            var_s0 = 0x1A;
        }
        if (temp_t0 == 0x2A) {
            var_s0 = 0x2A;
        }
        if ((arg0->unk13C != 0) || (arg0->unk137 != 0)) {
            if (arg4 == 0) {
                var_s0 = 0;
            } else {
                sp40 = 1;
            }
        }
        temp_a0 = arg0->unk65;
        if ((temp_a0 != 0) && (arg4 == 0)) {
            temp_v0_3 = *((u8 *)&g_obj_id_by_slot1 + (temp_a0 * 0x32C));
            if (temp_v0_3 != 0xC) {
                if (temp_v0_3 != 0x23) {
                    var_s0 = 0;
                    if (temp_v0_3 != 0x28) {
                        if (temp_v0_3 != 0x8A) {
                            var_s0 = 0xE;
                        } else {
                            goto block_32;
                        }
                    }
                } else {
block_32:
                    var_s0 = 0x1B;
                }
            } else {
                var_s0 = 8;
            }
        }
        if (temp_v1_2->pad17[0] != 0) {
            var_s0 = 0x3C;
        }
        if ((arg4 == 0) && (temp_t0 != 0) && (var_s0 != (temp_t0 & ~0x80))) {
            sp38 = (s32) temp_v1_2->unk75;
            temp_v1_2->unk75 = temp_t0;
            sp3C = 0;
            sp44 = var_t2;
            sp4C = 0;
            obj_ctrl_action_update(arg0, arg1, arg2, arg3, 1);
            var_t1 = 0;
            var_t4 = 0;
            arg0->unk31C->unk75 = (u8) sp38;
            arg0->unk31C->unk78 = 0;
        }
        if (arg0->stunned != 0) {
            var_t1 = 1;
            arg2 = 0;
            arg1 = 0;
        }
        if ((var_s0 != 0) && (arg0->unk31C->unk4E == 0)) {
            var_t4 = player_item_action(arg0, arg1, arg2, arg3, arg4, (s32) var_s0, var_t1, var_t2, sp40);
        }
        if ((arg0->unk31C->pad79[2] != 0) || (arg2 & 0x4000)) {
            player_context_action(arg0, arg2, arg3, sp40, var_t4);
        }
    }
}
/* was func_15060778 */
void obj_sfx_play_attached(s32 arg0, struct127 *arg1, u16 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 sp54;
    u16 *sp4C;
    s32 sp44;
    s32 temp_a0;
    s32 temp_t2;
    s32 var_a0;
    s32 var_t0;
    u16 *var_t1;
    u16 temp_v1;
    u16 var_v0;

    var_t1 = NULL;
    if (arg6 & 8) {
        var_t0 = 0;
    } else {
        var_t0 = ((u32) arg1->unk184 >> 3) & 0x30;
    }
    temp_t2 = arg6 & 3;
    switch (temp_t2) {                              /* irregular */
    default:
        var_a0 = 0 & 0xFFFF;
block_15:
        if (arg6 & 4) {
            sp4C = var_t1;
            var_v0 = sound_voice_play_at((u16) var_a0, arg0, (arg2 + (var_t0 * 0x32)) & 0xFFFF, (s16) arg3, (u8) var_t0, 0, (s16) (s32) arg1->x_position, (s16) (s32) arg1->y_position, (s16) (s32) arg1->z_position, (s16) arg4, (s16) arg5);
        } else {
            sp4C = var_t1;
            var_v0 = sound_voice_play((u16) var_a0, arg0, (arg2 + (var_t0 * 0x32)) & 0xFFFF, 0x40U, (s16) arg3, (u8) var_t0, 1U);
        }
        if (sp4C != NULL) {
            *sp4C = var_v0;
        }
        return;
    case 1:
        var_t1 = &arg1->unk8C;
        var_a0 = (s32) arg1->unk8C;
        goto block_15;
    case 2:
    case 3:
        var_t1 = &arg1->unk8E;
        temp_v1 = arg1->unk8E;
        if (temp_t2 == 2) {
            var_a0 = temp_v1 & 0xFFFF;
            goto block_15;
        }
        temp_a0 = temp_v1 & 0xFFFF;
        sp44 = temp_a0;
        sp54 = var_t0;
        sp4C = var_t1;
        var_a0 = temp_a0;
        if ((sound_voice_get_id((u16) temp_a0) == arg0) & 0x7FFF) {
            if (arg6 & 4) {
                sound_voice_update_3d((u16) var_a0, (arg2 + (var_t0 * 0x32)) & 0xFFFF, (s16) ((arg1->unk13F * 0xA) + arg3), var_t0 & 0xFF, 0, (s16) (s32) arg1->x_position, (s16) (s32) arg1->y_position, (s16) (s32) arg1->z_position, (s16) arg4, (s16) arg5);
                return;
            }
            sp44 = var_a0;
            sp54 = var_t0;
            sound_voice_set_param((u16) var_a0, 0x10, arg3);
            sound_voice_set_param((u16) var_a0, 8, arg2 + (var_t0 * 0x32));
            return;
        }
        arg0 |= 0x8000;
        goto block_15;
    }
}
/* was func_15060A30 */
void obj_sfx_play(s32 arg0, struct127 *arg1) {
    if (arg1->camera == NULL) {
        actor_sound_play2(arg0, arg1, 28000, 500, 2500);
    } else {
        obj_sfx_play_attached(arg0, arg1, 24000, 0, 500, 2500, 1);
    }
}
/* was func_15060A9C */
void obj_sfx_play_alt(s32 arg0, struct127 *arg1) {
    if (arg1->camera == NULL) {
        actor_sound_play_untracked(arg0, arg1, 24000, 500, 2500);
    } else {
        obj_sfx_play_attached(arg0, arg1, 24000, 0, 500, 2500, 0);
    }
}

/* was func_15060B04 */
void obj_sfx_play_vol(s32 arg0, struct127 *arg1, s32 arg2) {
    if (arg1->camera == NULL) {
        actor_sound_play_untracked(arg0, arg1, arg2, 500, 2500);
    } else {
        obj_sfx_play_attached(arg0, arg1, arg2, 0, 500, 2500, 0);
    }
}

/* was func_15060B70 */
void obj_sfx_play_simple(s32 arg0, void *arg1) {
    actor_sound_play(arg0, arg1, 0x6D60, 0x1F4, 0x9C4);
}

/* was func_15060BA4 */
s32 obj_add_health(struct127 *arg0, s32 arg1) {
    if (arg0->health == 6) {
        return 0;
    }
    arg0->health += arg1;
    if (arg0->health >= 7) {
        arg0->health = 6;
    }
    return 1;
}
/* was func_15060BE0 */
void obj_calc_bone_offset(u8 *arg0) {
    f32 sp4;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f18;
    f32 var_f2;
    s32 temp_a1;
    s32 var_v0;
    struct124 *temp_v0;
    u8 temp_v1;
    u8 *temp_a2;

    temp_v1 = (*(u8 *)((u8 *)arg0 + 4));
    var_v0 = 0;
    if (temp_v1 != 0xFF) {
        temp_a1 = (*(s32 *)((u8 *)arg0 + 0x1D4));
        if ((temp_a1 != 0) && (D_800C42B0 == 0)) {
            temp_v0 = D_800D1C90[temp_v1];
            temp_a2 = temp_a1 + ((*(u8 *)((u8 *)temp_v0 + 0x27)) << 6);
            temp_f2 = (f32) (*(s16 *)((u8 *)temp_v0 + 0x14)) * (*(f32 *)((u8 *)arg0 + 0x150));
            if (temp_f2 != 0.0f) {
                temp_f12 = (*(f32 *)((u8 *)temp_a2 + 0x10));
                temp_f14 = (*(f32 *)((u8 *)temp_a2 + 0x14));
                temp_f16 = (*(f32 *)((u8 *)temp_a2 + 0x18));
                temp_f0 = sqrtf((temp_f12 * temp_f12) + (temp_f14 * temp_f14) + (temp_f16 * temp_f16));
                var_f18 = temp_f0;
                if (temp_f0 != 0.0f) {
                    var_f18 = temp_f2 / temp_f0;
                }
                var_f0 = temp_f12 * var_f18;
                var_f2 = temp_f14 * var_f18;
                sp4 = temp_f16 * var_f18;
            } else {
                var_f0 = 0.0f;
                sp4 = 0.0f;
                var_f2 = 0.0f;
            }
            var_v0 = 1;
            (*(s16 *)((u8 *)arg0 + 0x1BC)) = (s16) (s32) ((*(f32 *)((u8 *)temp_a2 + 0x30)) + var_f0);
            (*(s16 *)((u8 *)arg0 + 0x1BE)) = (s16) (s32) ((*(f32 *)((u8 *)temp_a2 + 0x34)) + var_f2);
            (*(s16 *)((u8 *)arg0 + 0x1C0)) = (s16) (s32) ((*(f32 *)((u8 *)temp_a2 + 0x38)) + sp4);
        }
    }
    if (var_v0 == 0) {
        (*(s16 *)((u8 *)arg0 + 0x1BC)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14));
        (*(s16 *)((u8 *)arg0 + 0x1BE)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18));
        (*(s16 *)((u8 *)arg0 + 0x1C0)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x1C));
    }
}
// object_forget_target: clear the target byte +0x65 (object index + 1) of the first 25 live objects that point
// at `obj` (called by the object removal obj_remove).
/* was func_15060D54 */
void obj_forget_target(struct127 *obj) {
    s32 idx = obj - g_objects;
    u8 *o;
    s32 i;

    for (i = 0; i < 25; i++) {
        o = (u8 *) &g_objects[i];
        if (*(s32 *) o != 0 && o[0x65] == idx + 1) {
            o[0x65] = 0;
        }
    }
}
/* Removal of an object (struct127, ends its fade mode 5 / 6 in obj_fade_update). mode 0 = plain, 1 = killed
 * (obj_sync_collision_link(obj, 1, 0) and breakable_release(slot)), 2 = removed without a trace (marker byte cleared).
 * Releases its model / sound / effect, gives back the map marker byte g_setup_entry_flags[+0x13F] (kept as 0x80 or
 * cleared, depending on the marker record +0x144), frees the buffers +0x260.. and the per-player handles +0x304. */
/* was func_15060F28 */
void obj_remove(struct127 *obj, s32 mode) {
    u8 *o = (u8 *)obj;
    u8 *rec;
    u8 *p;
    u8 slot;
    s32 i;

    char_fx_clear_all(o);
    node_broadcast_obj_all(o, 0);
    if (o[5] != 2 && o[5] != 3) {
        obj_release_models(obj);
        obj_remove_children(obj, mode);
    }
    if (mode == 1) {
        obj_sync_collision_link(obj, 1, 0);
        breakable_release(obj - g_objects);
    }
    slot = o[0x13F];
    if (slot != 0xFF) {
        if (mode == 2) {
            g_setup_entry_flags[slot] = 0;
        } else {
            rec = *(u8 **)(o + 0x144);
            if (rec == NULL) {
                g_setup_entry_flags[slot] &= 0x80;
            } else if (*(u16 *)rec & 0x20) {
                rec[2] = 1;
                g_setup_entry_flags[o[0x13F]] = 0;
            } else if (*(u16 *)rec & 1) {
                g_setup_entry_flags[slot] = 0;
            } else {
                rec[2] = 1;
                p = g_setup_entry_flags + o[0x13F];
                *p &= 0x80;
            }
        }
    }
    if (*(s32 *)(o + 0x260) != 0) {
        heap_free(*(s32 *)(o + 0x260));
    }
    if (*(s32 *)(o + 0x264) != 0) {
        heap_free(*(s32 *)(o + 0x264));
    }
    if (*(s32 *)(o + 0x268) != 0) {
        heap_free(*(s32 *)(o + 0x268));
    }
    if (*(s32 *)(o + 0x26C) != 0) {
        heap_free(*(s32 *)(o + 0x26C));
    }
    if (*(s32 *)(o + 0x1D8) != 0) {
        heap_free(*(s32 *)(o + 0x1D8));
    }
    if (*(s32 *)(o + 0x2D4) != 0) {
        node_destroy(*(struct102 **)(o + 0x2D4));
    }
    /* per-player handles: only the first one is tested */
    if (*(s32 *)(o + 0x304) != 0) {
        for (i = 0; i <= g_last_player_index; i = (i + 1) & 0xFF) {
            heap_set_block_tag(*(s32 **)(o + 0x304 + i * 4), 4);
        }
    }
    if (*(s32 *)(o + 0x314) != 0) {
        heap_set_block_tag(*(s32 **)(o + 0x314), 4);
    }
    if (*(s32 *)(o + 0x2D0) != 0) {
        heap_free(*(s32 *)(o + 0x2D0));
    }
    if (*(s32 *)(o + 0x324) != 0) {
        heap_free(*(s32 *)(o + 0x324));
    }
    if (*(u8 **)(o + 0x31C) != NULL && *(s32 *)(*(u8 **)(o + 0x31C) + 0x11C) != 0) {
        heap_free(*(s32 *)(*(u8 **)(o + 0x31C) + 0x11C));
    }
    actor_sounds_stop_loops(obj);
    attachment_remove_all_of_owner(o);
    obj_forget_target(obj);
    afterimage_remove_object((s32)obj);
    if (*(s32 *)(o + 0x31C) != 0) {
        heap_free(*(s32 *)(o + 0x31C));
    }
    obj_reset(obj);
}
// path_face_nearest_segment: turns obj toward its path `path` (g_path_points[path], D_800D2528[path] points of s16
// {x, y, z, speed}; at least 3): finds the point nearest to obj's x / z (squared distance, first minimum wins);
// unless that is the first or the last point, steps back one point when obj is 0x6D61 or more away from it and the
// previous point is nearer than the next one; then faces along the segment to the next point
// (obj_blend_push_velocity(obj, angle, speed, min(speed * 0.0025, 1)); speed 0 = 8); above speed 20 the angle | 1 also goes
// to obj's linked object (+0x31C, +0x68).
/* was func_150611E8 */
void obj_follow_path(struct127 *obj, s32 path) {
    s32 count;
    s16 *pts;
    s16 *seg;
    s16 x;
    s16 z;
    s32 dx;
    s32 dz;
    s32 d;
    s32 best;
    s32 nearest;
    s32 i;
    u16 speed;
    f32 fspeed;
    f32 turn;
    u16 angle;

    count = D_800D2528[path];
    if (count < 3) {
        return;
    }
    x = obj->x_position;
    z = obj->z_position;
    best = 0x7FFFFFFF;
    nearest = 0;
    pts = (s16 *) g_path_points[path];
    for (i = 0; i < count; i++) {
        dx = x - pts[i * 4 + 0];
        dz = z - pts[i * 4 + 2];
        d = (s32) ((u32) dx * dx + (u32) dz * dz); // wraps like multu
        if (d < best) {
            nearest = i;
            best = d;
        }
    }
    if (nearest == 0 || nearest + 1 == count) {
        return;
    }
    if (best >= 0x6D61) {
        s32 dNext;
        s32 dPrev;

        dx = x - pts[(nearest + 1) * 4 + 0];
        dz = z - pts[(nearest + 1) * 4 + 2];
        dNext = (s32) ((u32) dx * dx + (u32) dz * dz);
        dx = x - pts[(nearest - 1) * 4 + 0];
        dz = z - pts[(nearest - 1) * 4 + 2];
        dPrev = (s32) ((u32) dx * dx + (u32) dz * dz);
        if (dPrev < dNext) {
            nearest--;
        }
    }
    seg = &pts[nearest * 4];
    speed = seg[7];
    if (speed == 0) {
        fspeed = 8.0f;
    } else {
        fspeed = speed;
    }
    turn = fspeed * 0.0025f;
    if (1.0f < turn) {
        turn = 1.0f;
    }
    angle = math_atan2_u16(seg[4] - seg[0], seg[2] - seg[6], 0);
    if (obj->unk31C != NULL && 20.0f < fspeed) {
        *(u16 *) ((u8 *) obj->unk31C + 0x68) = angle | 1;
    }
    obj_blend_push_velocity(obj, angle, fspeed, turn);
}

// TODO: is this really struct127?
/* was func_150615DC */
void obj_fade_reset(struct127 *arg0) {
    arg0->unk7 = 0xFF;
    arg0->unk8 = 0xFF;
    arg0->unk9 = 0;
    arg0->unkA = 0;
    arg0->unkE.ub[1] = 0;
    arg0->unkB = arg0->unkC = arg0->unkD = arg0->unkE.ub[0] = 0xFF;
}

/* Fade / visibility command for an object (struct127). Commands >= 8 work on player p's visibility:
 * 8 = hide (bit p of +0x0F set, target 0), 10 = hide at once (bit p + 4 set), others = show (bit p cleared,
 * target 0xFF); a pending "at once" bit p + 4 sets the byte +0x0B + p and is cleared; the byte also jumps to the
 * target when +0x2FD or g_camera_timers[p] is set. Commands < 8 start an alpha fade (+0x0A mode, +0x07 alpha,
 * +0x08 target, +0x09 step) unless a fade of a higher mode runs: 4 = fade in from 0, 5 / 6 = fade out (then
 * removal, obj_fade_update), 2 = fade to a2 by a3, 1 = set alpha a2 and stop. With g_camera_timers set the alpha
 * jumps to the target. */
/* was func_1506160C */
void obj_fade_command(struct127 *obj, u8 cmd, u8 a2, u8 a3, u8 p) {
    u8 *o = (u8 *)obj;
    u8 target;
    s32 bit;

    if (cmd >= 8) {
        if (cmd == 10) {
            o[0xF] |= (1 << p) << 4;
            target = 0;
        } else {
            bit = 1 << p;
            if (cmd == 8) {
                o[0xF] |= bit;
                target = 0;
            } else {
                o[0xF] &= ~bit;
                target = 0xFF;
            }
            if (o[0xF] & (bit << 4)) {
                o[0xB + p] = target;
            }
            o[0xF] &= ~(bit << 4);
        }
        if (o[0x2FD] != 0 || g_camera_timers[p] != 0) {
            o[0xB + p] = target;
        }
        return;
    }
    if (cmd < o[0xA]) {
        return;
    }
    switch (cmd) {
        case 4:
            o[0xA] = cmd;
            o[7] = 0;
            o[8] = 0xFF;
            o[9] = 0x20;
            break;
        case 5:
            o[0xA] = cmd;
            o[8] = 0;
            o[9] = 0x20;
            break;
        case 6:
            o[0xA] = cmd;
            o[8] = 0;
            o[9] = 8;
            break;
        case 2:
            o[0xA] = cmd;
            o[8] = a2;
            o[9] = a3;
            break;
        case 1:
            o[0xA] = 0;
            o[7] = a2;
            o[8] = a2;
            break;
    }
    if (*(s32 *)g_camera_timers != 0) {
        o[7] = o[8];
    }
}
/* Per-frame fades of an object (struct127): per player i (0..g_last_player_index) the visibility byte +0x0B + i moves by
 * 50 towards 0 when bit i of +0x0F is set, else towards 0xFF (jumps there when g_camera_timers[i] is set). With a
 * fade mode (+0x0A) the alpha +0x07 steps by +0x09 towards +0x08; on arrival mode 6 / 5 calls
 * obj_remove(obj, 1 / 2), any other mode ends (+0x0A = 0). */
/* was func_150617BC */
void obj_fade_update(struct127 *obj) {
    u8 *o = (u8 *)obj;
    s32 i;
    s32 bit;
    s32 v;

    if (*(s32 *)o == 0) {
        return;
    }
    for (i = 0, bit = 1; i <= g_last_player_index; i++, bit <<= 1) {
        v = o[0xB + i];
        if (o[0xF] & bit) {
            if (v > 0) {
                if (g_camera_timers[i] != 0) {
                    v = 0;
                } else {
                    v -= 50;
                    if (v < 0) {
                        v = 0;
                    }
                }
                o[0xB + i] = v;
            }
        } else if (v < 0xFF) {
            if (g_camera_timers[i] != 0) {
                v = 0xFF;
            } else {
                v += 50;
                if (v > 0xFF) {
                    v = 0xFF;
                }
            }
            o[0xB + i] = v;
        }
    }
    if (o[0xA] == 0) {
        return;
    }
    if (o[8] != o[7]) {
        if (o[7] < o[8]) {
            v = o[7] + o[9];
            if (v > o[8]) {
                v = o[8];
            }
        } else {
            v = o[7] - o[9];
            if (v < o[8]) {
                v = o[8];
            }
        }
        o[7] = v;
    }
    if (o[8] != o[7]) {
        return;
    }
    if (o[0xA] == 6) {
        obj_remove(obj, 1);
    } else if (o[0xA] == 5) {
        obj_remove(obj, 2);
    } else {
        o[0xA] = 0;
    }
}
// ???
/* was func_1506196C */
s32 obj_get_player_alpha(struct127 *arg0, s32 arg1) {
    s32 v = (&arg0->unkB)[arg1] * arg0->unk7;

    if (v == 0xFE01) {
        v = 0xFF;
    } else {
        v = v >> 8;
    }
    return v;
}

void obj_fade_update(struct127 *);
s32 obj_check_visible(struct127 *);

/* was func_150619A8 */
void objects_update_visibility(void) {
    struct {
        u8 u5C;
    } sp;
    s32 var_s0_2;
    s32 var_s4_2;
    s32 var_s6;
    struct127 *temp_s3;
    struct127 *temp_v0_2;
    struct127 *var_s0;
    struct127 *var_s1;
    u8 *var_s5;
    u8 temp_a0;
    u8 temp_v0;
    u8 var_s4;

    var_s6 = 0;
    var_s0 = g_objects;
    var_s4 = 0;
    do {
        if (var_s0->interaction_state != 0) {
            temp_v0 = var_s0->unk2FD;
            if (temp_v0 != 0) {
                var_s0->unk2FD = temp_v0 - 1;
            }
            obj_fade_update(var_s0);
            if (obj_check_visible(var_s0) != 0) {
                var_s0->unk2FA |= 1;
            } else {
                var_s0->unk2FA &= ~1;
                if ((var_s0->unk20B != 0) || (var_s0->unk20C != 0) || (var_s0->unk20D != 0) || (var_s0->unk20E != 0)) {
                    (&sp.u5C)[var_s6] = var_s4;
                    var_s6 += 1;
                }
            }
        }
        var_s4 += 1;
        var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
    } while ((s32) var_s4 < 0x19);
    if (var_s6 != 0) {
        var_s4_2 = 0;
        if (var_s6 > 0) {
            var_s5 = &sp.u5C;
            do {
                temp_s3 = &g_objects[*var_s5];
                var_s1 = temp_s3;
                var_s0_2 = 0;
loop_16:
                temp_a0 = var_s1->unk20B;
                if ((temp_a0 != 0) && (temp_v0_2 = obj_find_by_setup_id(temp_a0), (temp_v0_2 != NULL)) && (temp_v0_2->unk2FA & 1)) {
                    temp_s3->unk2FA |= 1;
                } else {
                    var_s0_2 += 1;
                    var_s1 = (struct127 *)((u8 *)var_s1 + (1));
                    if (var_s0_2 != 4) {
                        goto loop_16;
                    }
                }
                var_s4_2 += 1;
                var_s5 += 1;
            } while (var_s4_2 != var_s6);
        }
    }
}
/* Shared animation state of some object kinds (g_obj_anim_shared, 0x18 bytes). */
struct ObjAnimShared {
    /* 0x00 */ f32 scrollU;   /* kind 0x24: texture scroll, degrees */
    /* 0x04 */ f32 scrollV;
    /* 0x08 */ s8 jitter;     /* kind 0x24: random -2..2 */
    /* 0x09 */ s8 pulse;      /* kind 0x2C: 0..41 ping-pong */
    /* 0x0A */ s8 pulseStep;
    /* 0x0B */ u8 phase[4];   /* kind 0x3A: colour phases, stepped by the bytes of g_tex_anim_phase_steps */
    /* 0x0F */ u8 frameTimer; /* kind 0x4B */
    /* 0x10 */ u8 glow;       /* kind 0x54: 0..255 */
};
#define OBJ_ANIM (*(struct ObjAnimShared *)&g_obj_anim_shared)

/* Per-frame texture / colour animation of the live objects (g_objects[], +0x2FA visible), by kind (+0x04).
 * Effects shared by every object of one kind (gfx_tile_scroll_coords texture scroll, obj_type_tex_scroll_apply, obj_vertex_colours_blend
 * colours) run for the first such object only (done[]). */
/* was func_15061B4C */
void objects_animate_textures(void) {
    u8 done[10];
    u8 *obj;
    u8 type;
    s32 i;
    s32 v;
    u8 steps[4];
    f32 colours[4];
    f32 glow;
    s32 **tex;

    bzero(done, sizeof(done));
    for (obj = (u8 *)g_objects; obj != (u8 *)&g_obj_scratch_rec; obj += sizeof(struct127)) {
        if (*(s32 *)obj == 0 || obj[0x2FA] == 0) {
            continue;
        }
        type = obj[4];
        switch (type) {
            case 0x13:
                if (!done[0]) {
                    gfx_tile_scroll_coords(type, 0x5E, 0, -1, 0, 0);
                    gfx_tile_scroll_coords(type, 0x60, 0, -1, 0, 0);
                    gfx_tile_scroll_coords(type, 0x62, 0, -1, 0, 0);
                    gfx_tile_scroll_coords(type, 0x64, 0, -1, 0, 0);
                    done[0] = 1;
                }
                break;
            case 0x23:
                if (!done[1]) {
                    gfx_tile_scroll_coords(type, 0x1E9, 0, -1, 0, 0);
                    gfx_tile_scroll_coords(type, 0x1EB, 0, -1, 0, 0);
                    gfx_tile_scroll_coords(type, 0x1ED, 0, -1, 0, 0);
                    gfx_tile_scroll_coords(type, 0x1EF, 0, -1, 0, 0);
                    done[1] = 1;
                }
                break;
            case 0x24:
                if (!done[2]) {
                    if ((u32)random_int() % 1000 < 300) {
                        OBJ_ANIM.jitter = (u32)random_int() % 5 - 2;
                    }
                    gfx_tile_scroll_coords(type, 4, -4, OBJ_ANIM.jitter, 0, 0);
                    tex = &((s32 **)&D_800C4440)[type];
                    if (*tex != NULL) {
                        obj_type_tex_scroll_apply(type, (*tex)[0], 0x37, 0, (s32)OBJ_ANIM.scrollV, 2, 1);
                        obj_type_tex_scroll_apply(type, (*tex)[1], 0x27, 0x37, (s32)OBJ_ANIM.scrollU, 1, 0);
                    }
                    OBJ_ANIM.scrollU += -4.0f * (f32)g_frame_ticks;
                    if (OBJ_ANIM.scrollU <= 0.0f) {
                        OBJ_ANIM.scrollU += 360.0f;
                    }
                    OBJ_ANIM.scrollV += -0.5f * (f32)g_frame_ticks;
                    if (OBJ_ANIM.scrollV <= 0.0f) {
                        OBJ_ANIM.scrollV += 360.0f;
                    }
                    done[2] = 1;
                }
                break;
            case 0x2C:
                if (!done[3]) {
                    v = OBJ_ANIM.pulse;
                    if (v > 40) {
                        OBJ_ANIM.pulseStep = -1;
                    } else if (v <= 0) {
                        OBJ_ANIM.pulseStep = 1;
                    }
                    OBJ_ANIM.pulse = v + OBJ_ANIM.pulseStep;
                    gfx_tile_scroll_coords(type, 0xAA, OBJ_ANIM.pulse, 0, 0, 1);
                    done[3] = 1;
                }
                break;
            case 0x3A:
                if (!done[4]) {
                    *(s32 *)steps = g_tex_anim_phase_steps;
                    if (*(s32 *)(obj + 0x1D4) != 0) {
                        for (i = 0; i < 4; i++) {
                            colours[i] = (math_cos_u8(OBJ_ANIM.phase[i]) + 1.0f) * 0.5f;
                            OBJ_ANIM.phase[i] += steps[i];
                        }
                        obj_vertex_colours_blend((struct127 *)obj, colours, 1);
                        done[4] = 1;
                    }
                }
                break;
            case 0x3F:
                if (!done[5]) {
                    gfx_tile_scroll_coords(type, 4, 0, -4, 0, 0);
                    done[5] = 1;
                }
                break;
            case 0x4B:
                if (!done[6]) {
                    done[6] = 1;
                    gfx_tile_scroll_coords(type, 0x173, -4, 0, 0, 0);
                    gfx_tile_scroll_coords(type, 0x175, -2, 0, 0, 0);
                    gfx_tile_scroll_coords(type, 0x177, -1, 0, 0, 0);
                }
                /* frame +0x68 cycles 15, 16, 17, 18, 17, 16 (+0x69 = 0..5), one step every 4 ticks */
                if (OBJ_ANIM.frameTimer >= 4) {
                    OBJ_ANIM.frameTimer = 0;
                    if (obj[0x69] == 5) {
                        obj[0x69] = 0;
                    } else {
                        obj[0x69]++;
                    }
                    if (obj[0x69] >= 3) {
                        obj[0x68] = 5 - obj[0x69];
                    } else {
                        obj[0x68] = obj[0x69];
                    }
                    obj[0x68] += 15;
                } else {
                    OBJ_ANIM.frameTimer += g_frame_ticks;
                }
                break;
            case 0x45:
                v = obj[0x6D];
                obj[0x68] = (v >= 10) ? v - 10 : v * 2 + 6;
                break;
            case 0x5B:
                for (i = 0; i < 2; i++) {
                    v = obj[0x6C + i];
                    obj[0x68 + i] = (v >= 10) ? v - 10 : g_tex_anim_5b_frames[v];
                }
                break;
            case 0x54:
                if (*(s32 *)(obj + 0x2EC) != 0) {
                    OBJ_ANIM.glow = (OBJ_ANIM.glow < 0xEB) ? OBJ_ANIM.glow + 20 : 0xFF;
                } else {
                    OBJ_ANIM.glow = (OBJ_ANIM.glow <= 20) ? 0 : OBJ_ANIM.glow - 20;
                }
                glow = OBJ_ANIM.glow * (1.0f / 255.0f);
                obj_vertex_colours_blend((struct127 *)obj, &glow, 0);
                break;
            case 0x8A:
                if (g_level_id != 0x30) {
                    if (*(u16 *)(obj + 0x84) == 1) {
                        gfx_tile_scroll_coords(type, 0x253, 0, 0x10, 0, 0);
                        gfx_tile_scroll_coords(type, 0x255, 0, 8, 0, 0);
                        gfx_tile_scroll_coords(type, 0x257, 0, 4, 0, 0);
                    }
                } else {
                    obj_vtx_scroll_uv(obj, 0, 0, 0x1000, 0x1000, 0xC, 0,
                                  (*(u16 *)(obj + 0x84) == 1) ? -g_frame_ticks * 40 : 0);
                }
                break;
            case 0x42:
                v = *(u16 *)(obj + 0x84);
                if (v == 2 || v == 1) {
                    if (obj[0x68] == 0xD) {
                        obj[0x68] = 0xC;
                    }
                    if ((random_int() & 3) == 0) {
                        obj[0x68] = (obj[0x68] == 0x15) ? 0xC : 0x15;
                    }
                } else {
                    obj[0x68] = 0xD;
                }
                break;
            case 0x7B:
                obj7b_set_anim_ids(obj);
                break;
            case 0x92:
                if (!done[9]) {
                    gfx_tile_scroll_coords(type, 4, 0, -2, 0, 0);
                    gfx_tile_scroll_coords(type, 0x13B, 0, -2, 0, 0);
                    gfx_tile_scroll_coords(type, 0x20D, 0, -2, 0, 0);
                    done[9] = 1;
                }
                break;
            case 0x43:
                gfx_tile_scroll_coords(type, 4, 0x14, 8, 0, 0);
                break;
        }
    }
}
s32 cutscene_obj_takes_part(struct127 *);
s32 camera_view_test_sphere(s32, s32 *, f32, f32, f32, f32, f32, f32);
extern s32 g_view_mtxf; /* was D_800DA030 */

/* was func_150623F4 */
s32 obj_check_visible(struct127 *arg0) {
    s32 sp54;
    s32 sp4C;
    s32 *var_s1;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f2;
    f32 var_f22;
    s32 temp_t9;
    s32 var_a0;
    s32 var_s0;
    s32 var_t0;
    s32 var_t0_2;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    struct127 *var_v0_2;
    struct127 *var_v0_3;
    struct129 *temp_v0;
    u16 temp_t6;
    u16 temp_t7;
    u8 temp_a2;
    u8 temp_t1;

    temp_v0 = arg0->unk144;
    if (temp_v0 != NULL) {
        temp_t6 = (*(u16 *)((u8 *)temp_v0 + 0x2A));
        var_f22 = (f32) temp_t6;
        if ((s32) temp_t6 < 0) {
            var_f22 += 4294967296.0f;
        }
    } else {
        var_f22 = 0.0f;
    }
    if (var_f22 == 0.0f) {
        return 1;
    }
    if (arg0->unk127 != 0xFF) {
        return 1;
    }
    if ((D_800C3638 != 0) && (cutscene_obj_takes_part(arg0) != 0)) {
        return 1;
    }
    if (arg0->interaction_state == 0x27) {
        return 1;
    }
    var_a0 = 0;
    var_v0_2 = arg0;
    if (g_last_player_index >= 0) {
        do {  /* P117: bytes +0xB .. +0xB + g_last_player_index (was a struct127 stride) */
            temp_t1 = var_v0_2->unkB;
            var_v0_2 = (struct127 *) ((u8 *) var_v0_2 + 1);
            var_a0 += temp_t1;
        } while ((u32) ((u8 *) arg0 + g_last_player_index) >= (u32) var_v0_2);
    }
    if (var_a0 == 0) {
        return 0;
    }
    if ((arg0->unk74 & 0xF) != 0xF) {
        return 1;
    }
    temp_a2 = arg0->unk13F;
    if (D_800D2528[temp_a2] != 0) {
        var_t0 = 1;
        var_v1 = 0;
        if (g_player_count > 0) {
            temp_t9 = g_path_points[temp_a2];
            var_v0_3 = g_objects;
            temp_t7 = (*(u16 *)((u8 *)temp_t9 + 6));
loop_22:
            var_v1 += 1;
            temp_f0 = (f32) (*(s16 *)((u8 *)temp_t9 + 0)) - var_v0_3->x_position;
            temp_f2 = (f32) (*(s16 *)((u8 *)temp_t9 + 4)) - var_v0_3->z_position;
            if (((temp_f0 * temp_f0) + (temp_f2 * temp_f2)) < (f32) (temp_t7 * temp_t7)) {
                var_t0 = 0;
            } else {
                var_v0_3 += 1; /* P117: next object (was 0x32C objects) */
                if (var_v1 < g_player_count) {
                    goto loop_22;
                }
            }
        }
        sp4C = var_t0;
        if (var_t0 == 0) {
            return 1;
        }
        goto block_27;
    }
block_27:
    var_t0_2 = sp4C;
    var_s1 = &g_view_mtxf;
    var_v1_2 = 0;
    var_s0 = 0;
    temp_f20 = (f32) (*(s16 *)((u8 *)(D_800D1C90[arg0->id]) + 0x10)) * arg0->y_scale;
    if (g_last_player_index >= 0) {
        sp4C = 1;
loop_29:
        sp54 = var_v1_2;
        if (camera_view_test_sphere(var_s0 + g_player_cams, var_s1, arg0->x_position, arg0->y_position + temp_f20, arg0->z_position, var_f22, var_f22, 20000.0f) != 0) {
            sp4C = 0;
            var_t0_2 = 0;
        } else {
            var_v1_2 += 1;
            var_s0 += 0x180;
            var_s1 = (s32 *) ((u8 *) var_s1 + 0x40); /* P117: 0x40 bytes (was 0x40 words) */
            if (g_last_player_index < var_v1_2) {
                var_t0_2 = sp4C;
            } else {
                goto loop_29;
            }
        }
    }
    var_v0 = 0;
    if (var_t0_2 == 0) {
        var_v0 = 1;
    }
    return var_v0;
}
/* Removes the objects attached to obj (+0x65 = obj's slot + 1, +0x127 = 0xFF) with obj_remove(child, mode). */
/* was func_150626EC */
void obj_remove_children(struct127 *obj, s32 mode) {
    struct127 *o;

    for (o = g_objects; o != (struct127 *)&g_obj_scratch_rec; o++) {
        if (*(s32 *)o != 0 && ((u8 *)o)[0x65] == (obj - g_objects) + 1 && ((u8 *)o)[0x127] == 0xFF) {
            obj_remove(o, mode);
        }
    }
}

/* was func_150627D4 */
void obj_model_reset(struct127 *arg0) {
    arg0->unk2FB = 0;
    obj_set_kind_look_flags(arg0);
    look_record_setup(arg0);
}
