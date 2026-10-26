#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s16 *obj_adjust_entries_player(s16 *arg0, s32 arg1);
s16 *obj_adjust_entries_type98(s16 *arg0, s32 arg1);
s16 *obj_adjust_entries_tilt(s16 *arg0, s32 arg1);
u8 *obj_adjust_entries_type8a(u8 *arg0, s32 arg1);
s16 *obj_adjust_entries_type28(s16 *arg0, s32 arg1);
s16 *obj_adjust_entries_type21(s16 *arg0, s32 arg1);
s16 *obj2b_write_msg(s16 *arg0, s32 arg1);
u8 *obj_adjust_entries_type4b(u8 *arg0, s32 arg1);
s16 *obj7b_joint_swing_entries(s16 *arg0, s32 arg1);
u8 model_get_face_joint(s32 arg0, s32 arg1);
s16 *obj_adjust_entries_face(s16 *buf, u8 *obj, s32 a2, s32 a3);

/* obj_adjust_list_build (P57): build the per-object adjustment list for anim_eval_joint_matrices (sbuf of objects_update_carried):
 * {u16 offset, s16 value} pairs ending with 0x1000. No skeleton (+0x1D4 == 0): just the terminator.
 * The player (obj+0 == 1) gets obj_adjust_entries_player's entries, other objects a per-type helper; then the face
 * entries of obj_adjust_entries_face for the model's two face joints (model_get_face_joint(type, 0 / 1)). */
/* was func_150342D0 */
void obj_adjust_list_build(s16 *buf, s32 arg1) {
    struct127 *obj = &D_800CC2D0[arg1];
    s16 *p = buf;
    s32 j0;

    if (*(s32 *)((u8 *)obj + 0x1D4) == 0) {
        buf[0] = 0x1000;
        return;
    }
    if (*(s32 *)((u8 *)obj + 0) == 1) {
        p = obj_adjust_entries_player(buf, arg1);
    } else {
        switch (((u8 *)obj)[4]) {
        case 0x21: p = obj_adjust_entries_type21(buf, arg1); break;
        case 0x28: case 0x77: p = obj_adjust_entries_type28(buf, arg1); break;
        case 0x2B: p = obj2b_write_msg(buf, arg1); break;
        case 0x4B: p = (s16 *)obj_adjust_entries_type4b((u8 *)buf, arg1); break;
        case 0x5A: case 0x74: case 0x7A: case 0x8D: p = obj_adjust_entries_tilt(buf, arg1); break;
        case 0x7B: p = obj7b_joint_swing_entries(buf, arg1); break;
        case 0x8A: p = (s16 *)obj_adjust_entries_type8a((u8 *)buf, arg1); break;
        case 0x98: p = obj_adjust_entries_type98(buf, arg1); break;
        }
    }
    j0 = model_get_face_joint(((u8 *)obj)[4], 0);
    *obj_adjust_entries_face(p, (u8 *)obj, j0, model_get_face_joint(((u8 *)obj)[4], 1)) = 0x1000;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/obj_adjust_list_build.s")
#endif

#ifdef NON_MATCHING
/* was func_150344AC */
s16 *obj_adjust_entries_player(s16 *arg0, s32 arg1) {
    s16 *var_a2;
    s32 temp_f10;
    s32 var_v1;
    struct126 *temp_v0_2;
    struct126 *temp_v1;
    struct127 *temp_v0;
    u16 temp_a1;

    var_a2 = arg0;
    temp_v0 = &D_800CC2D0[arg1];
    temp_v1 = temp_v0->unk31C;
    if ((temp_v1 != NULL) && !(temp_v0->unk2F8 & 0x80)) {
        temp_a1 = temp_v0->unk84.uh;
        temp_f10 = (s32) (temp_v0->unk54 * 182.04445f);
        if ((temp_a1 != 0x42) && (temp_a1 != 0x14) && (temp_a1 != 0x76)) {
            var_v1 = 4;
            if (temp_v1->unk78 == 0xA) {
                var_v1 = 0;
            }
            (*(s16 *)((u8 *)var_a2 + 0)) = var_v1 + 6;
            (*(s16 *)((u8 *)var_a2 + 2)) = (s16) temp_f10;
        } else {
            (*(s16 *)((u8 *)var_a2 + 0)) = 0xA;
            (*(s16 *)((u8 *)var_a2 + 2)) = (s16) temp_f10;
            var_a2 = (s16 *)((u8 *)var_a2 + (4));
            (*(s16 *)((u8 *)var_a2 + 0)) = 4;
            (*(s16 *)((u8 *)var_a2 + 2)) = (s16) -(s16) temp_f10;
        }
        var_a2 = (s16 *)((u8 *)var_a2 + (4));
    }
    if (temp_v0->unk1D1 != 0) {
        *var_a2 = 6;
        var_a2 = (s16 *)((u8 *)var_a2 + (4));
        (*(s16 *)((u8 *)var_a2 + -2)) = (s16) (temp_v0->unk1D1 * 0xC8);
    }
    temp_v0_2 = D_800CC2D0[D_800C3E78].unk31C;
    if ((temp_v0_2 != NULL) && (temp_v0_2->unk12 != 0)) {
        *var_a2 = 8;
        var_a2 = (s16 *)((u8 *)var_a2 + (4));
        (*(s16 *)((u8 *)var_a2 + -2)) = (s16) -D_800CC2D0[D_800C3E78].unk31C->unk12;
    }
    return var_a2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/obj_adjust_entries_player.s")
#endif
/* was func_15034630 */
s16 *obj_adjust_entries_type98(s16 *arg0, s32 arg1)
{
  struct127 *temp_v0;
  temp_v0 = &D_800CC2D0[arg1];
  if (temp_v0->unk1D1 != 0)
  {
    *arg0 = 6;
    arg0 += 2;
    arg0[-1] = (s16) (temp_v0->unk1D1 * 0xC8);
  }
  return arg0;
}

/* was func_150346A0 */
s16 *obj_adjust_entries_tilt(s16 *arg0, s32 arg1)
{
  struct127 *temp_v0;
  temp_v0 = &D_800CC2D0[arg1];
  if (temp_v0->unk1D1 != 0)
  {
    *arg0 = 6;
    arg0 += 2;
    arg0[-1] = (s16) (temp_v0->unk1D1 * 0xC8);
  }
  return arg0;
}

#ifdef NON_MATCHING
extern s32 D_800CC9D4;

/* was func_15034710 */
u8 *obj_adjust_entries_type8a(u8 *arg0, s32 arg1) {
    s32 temp_f16;
    s32 temp_t1;

    (*(s16 *)((u8 *)arg0 + 0)) = 0;
    (*(s16 *)((u8 *)arg0 + 4)) = 0x18;
    temp_f16 = (s32) ((f32) *(s32 *)((u8 *)&D_800CC9D4 + (arg1 * 0x32C)) * 18.204445f);
    temp_t1 = (s16) temp_f16 >> 4;
    (*(s16 *)((u8 *)arg0 + 2)) = (s16) temp_t1;
    (*(s16 *)((u8 *)arg0 + 6)) = (s16) ((s16) temp_f16 - temp_t1);
    return arg0 + 8;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/obj_adjust_entries_type8a.s")
#endif
extern f32 D_800980CC;
/* was func_15034790 */
s16 *obj_adjust_entries_type28(s16 *arg0, s32 arg1) {
    struct127 *p;
    s32 v;
    f32 k;

    k = D_800980CC;
    {
        s32 blk_t; // fakematch: block boundary keeps the k load first

        arg0[0] = 0x12;
        p = &D_800CC2D0[arg1];
        v = *(s16 *)((u8 *)p + 0x2E6);
        arg0[1] = v * k;
        arg0[2] = 0xE;
        p += 0; // fakematch: register roles of p and v
        v = -*(s16 *)((u8 *)p + 0x2E4);
        arg0[3] = v * k;
    }
    return arg0 + 4;
}

void tail_update_conker();

/* was func_1503482C */
void obj_update_tail_for_conker(s32 arg0) {
    switch (D_800CC2D4[arg0 * 0x32C]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 0x80:
    case 0xB0:
        tail_update_conker(arg0);   /* P76: a0 still holds arg0 at the jal */
        break;
    }
}

s32 obj_lower_joints_by_face(struct127 *, s32, s32);
void obj_joint_look_at_camera(s32, s32, s32, s32);
void obj7b_update_pulse_scale(struct127 *);

/* was func_150348D4 */
void obj_postprocess_joints(s32 arg0) {

    if (D_800CC2D0[arg0].unk1D4 != NULL) {
        if ((D_800CC2D0[arg0].interaction_state == 1) || (D_800CC2D0[arg0].unk5 == 7)) {
            obj_update_tail_for_conker(arg0);
        }
        if (D_800CC2D0[arg0].interaction_state == 0x22) {
            obj_update_tail_for_conker(arg0);
        }
        switch (D_800CC2D0[arg0].id) {                          /* irregular */
        case 0x4:
            if (D_800BE616 == 0) {
                obj_joint_look_at_camera(0, arg0, 9, 0);
                obj_joint_look_at_camera(0, arg0, 4, 0);
                return;
            }
            break;
        case 0x70:
            obj_lower_joints_by_face(&D_800CC2D0[arg0], 0xA, 0xB);
            return;
        case 0x7B:
            obj7b_update_pulse_scale(&D_800CC2D0[arg0]);
            return;
        case 0x60:
            obj_pin_root_height(&D_800CC2D0[arg0]);
            break;
        }
    }
}

typedef struct { f32 m[4][4]; } Mtx44;
typedef struct {
    u8 pad0[4];
    u8 unk4;
    u8 pad5[0x97];
    s32 unk9C;
    u8 padA0[0x134];
    Mtx44 *unk1D4;
} S34A18;
s32 model_joint_mtx_count(u8);
/* was func_15034A18 */
void obj_hide_masked_joints(S34A18 *arg0) {
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    Mtx44 *m;
    if (arg0->unk1D4 != NULL && arg0->unk9C != 0) {
        n = model_joint_mtx_count(arg0->unk4) - 1;
        m = arg0->unk1D4;
        i = 31; if (n < 31) i = n;
        for (; i >= 0; i--) {
            if (arg0->unk9C & (1 << i)) {
                Mtx44 *e = &m[i];
                for (j = 0; j < 3; j++) {
                    for (k = 0; k < 3; k++) {
                        e->m[j][k] = 0.0f;
                    }
                }
            }
        }
    }
}

/* was func_15034AD8 */
void obj_hide_masked_joints_all(void) {
    struct127 *var_s0;
    var_s0 = D_800CC2D0;
    if (D_800BEAC0 == 0) {
        do {
            if ((var_s0->interaction_state != 0) && (var_s0->unk9C != 0)) {
                obj_hide_masked_joints(var_s0);
            }
            var_s0++;
        } while (var_s0 != (struct127 *)&D_800D121C);
    }
}
