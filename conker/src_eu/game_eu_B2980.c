#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern s8 D_800E1013;
extern f32 D_8009DD30;
extern f32 D_8009DD34;
f32 sinf(f32);
f32 cosf(f32);
void camera_set_initial_eye(u8 *arg0, u8 *arg1, f32 *arg2);
void obj_contact_pass(u8 *arg0, s32 arg1);
f32 anim_events_run(struct127 *arg0, f32 arg1, s32 arg2);
s32 obj_collision_cylinder(struct127 *, u16 *, u16 *, u16 *);
void node_broadcast_all(s32 arg0, u8 arg1);
#endif

typedef struct {
    /* 0x000 */ u8 pad0[0x11B];
    /* 0x11B */ u8 unk11B;
} struct_eu_B2980_b;

typedef struct {
    /* 0x000 */ u8 pad0[0x31C];
    /* 0x31C */ struct_eu_B2980_b *unk31C;
} struct_eu_B2980;


#ifdef NON_MATCHING
extern s32 D_800875E0;
extern u8 D_8009DD24;

/* was func_15085170 */
u8 obj_type_model_group(u8 *arg0) {
    s32 var_a0;
    s32 var_v0;
    u8 *temp_a3;
    u8 *var_a1;
    u8 *var_t0;
    u8 temp_a2;
    u8 temp_v1;

    temp_v1 = (*(u8 *)((u8 *)arg0 + 4));
    var_a1 = &D_8009DD24;
    var_v0 = 0;
loop_1:
    temp_a2 = *var_a1;
    var_a0 = 0;
    if ((s32) temp_a2 > 0) {
        temp_a3 = *(s32 *)((u8 *)&D_800875E0 + (var_v0 * 4));
        var_t0 = temp_a3;
loop_3:
        var_a0 += 1;
        if (temp_v1 == *var_t0) {
            return *temp_a3;
        }
        var_t0 += 1;
        if (var_a0 >= (s32) temp_a2) {
            goto block_6;
        }
        goto loop_3;
    }
block_6:
    var_v0 += 1;
    var_a1 += 1;
    if (var_v0 == 7) {
        return temp_v1;
    }
    goto loop_1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/obj_type_model_group.s")
#endif
#ifdef NON_MATCHING
/* Level start point lookup. Entries of D_800D212C are 0x18 bytes: s16 x/y/z +0, u8 +6 / +7 (angle), f32 x3 +8,
 * u8 +0x14, s8 +0x15, s8 +0x16 (alias index). arg0 = player (0xFF: none), arg1 = start index (-1: the player's
 * saved one at rec+0x31C->+0x11B). Multiplayer (D_800BE616 && D_800D18A8) picks the start farthest from the
 * others. Returns 1 when there is no start table, else 0. arg9 is unused. */
/* was func_150851E0 */
s32 level_start_point_get(s32 arg0, s32 arg1, s32 arg2, s16 *arg3, f32 *arg4, u8 *arg5, u8 *arg6, s32 *arg7, s32 *arg8,
                  s32 arg9, s32 *arg10) {
    s32 save = 1;
    s32 idx;
    s32 v1;
    s8 c;
    u8 *tab;
    u8 *e;

    if (D_800BE9F0 == 0x2B) {
        save = 0;
        D_800D18A8 = 0;
    }
    if (D_800BE616 != 0 && *(s8 *)(D_80090174 + 0x42) == 0 && D_800E1013 != 0) {
        save = 0;
    }
    if (arg0 != 0xFF) {
        if (arg1 == -1) {
            arg1 = (*(u8 **)((u8 *)&D_800CCA0C + arg0 * 0x32C))[0x11B];
        }
        if (save) {
            (*(u8 **)((u8 *)&D_800CCA0C + arg0 * 0x32C))[0x11B] = 0;
        }
    }
    idx = arg1 & 0xFFF;
    if (!(idx < D_800D2128) || idx < 0) {
        idx = 0;
    }
    tab = (u8 *)D_800D212C;
    if (tab == NULL) {
        return 1;
    }
    if (D_800BE616 != 0 && D_800D18A8 != 0) {
        u8 *rec = (u8 *)D_800CC2D0 + arg0 * 0x32C;
        u8 team = rec[0x128];
        u8 *ctl = *(u8 **)(rec + 0x31C);
        s32 mask = team ? D_800D2124 : D_800D2120;
        u8 list[0x20];
        s32 n = 0;
        s32 i;
        s32 best = 0;
        f32 bestd = 0.0f;
        s8 cur;

        for (i = 0; i < D_800D2128; i++) {
            if (mask & (1 << i)) {
                list[n++] = i;
            }
        }
        cur = *(s8 *)(ctl + 0x1B0);
        for (i = 0; i < n; i++) {
            u8 s = list[i];
            f32 d;
            f32 r;
            u8 *o;
            u8 *end;

            if (cur == s) {
                continue;
            }
            d = D_8009DD30;
            end = (u8 *)D_800CC2D0 + D_8008FD8C * 0x32C;
            for (o = (u8 *)D_800CC2D0; o < end; o += 0x32C) {
                f32 dx, dz, q;
                if (team == o[0x128]) {
                    continue;
                }
                e = (u8 *)D_800D212C + s * 0x18;
                dx = *(f32 *)(o + 0x14) - (f32)*(s16 *)(e + 0);
                dz = *(f32 *)(o + 0x1C) - (f32)*(s16 *)(e + 4);
                q = dx * dx + dz * dz;
                if (q < d) {
                    d = q;
                }
            }
            r = random_float() * 500.0f;
            d = d + r * r;
            if (bestd < d) {
                best = i;
                bestd = d;
            }
        }
        if (*(s8 *)(D_80090174 + 0x42) != 0 || D_800E1013 == 0) {
            idx = list[best];
        }
        ctl = *(u8 **)(rec + 0x31C);
        ctl[0x1B0] = idx;
        arg2 = 0;
        tab = (u8 *)D_800D212C;
    }
    v1 = idx;
    if (arg2 != 0 && (c = *(s8 *)(tab + idx * 0x18 + 0x16)) != 0) {
        if (c == -1 || !(c < D_800D2128)) {
            v1 = idx;
        } else {
            v1 = c;
        }
        if (arg10 != NULL) {
            c = *(s8 *)(tab + v1 * 0x18 + 0x15);
            if (c >= 0) {
                *arg10 = 0;
            } else if (c == -1) {
                *arg10 = 0;
            } else {
                *arg10 = 1;
            }
        }
    } else if (arg2 != 0 && *(s8 *)(tab + idx * 0x18 + 0x16) == 0) {
        D_800DDE38 = 2;
    }
    e = (u8 *)D_800D212C + v1 * 0x18;
    arg4[0] = *(f32 *)(e + 8);
    arg4[1] = *(f32 *)(e + 0xC);
    arg4[2] = *(f32 *)(e + 0x10);
    arg3[0] = *(s16 *)(e + 0);
    arg3[1] = *(s16 *)(e + 2);
    arg3[2] = *(s16 *)(e + 4);
    *arg5 = e[6];
    *arg6 = e[7];
    *arg7 = e[0x14];
    *arg8 = *(s8 *)(e + 0x15);
    if (D_800BE616 != 0 && D_800D18A8 == 0) {
        f32 ang = ((f32)*arg6 * D_8009DD34) * 0.0078125f;
        f32 r = random_float() * 80.0f - 40.0f;
        arg3[0] = (s16)(s32)((f32)arg3[0] + sinf(ang) * r);
        arg3[2] = (s16)(s32)((f32)arg3[2] + cosf(ang) * r);
    }
    if (arg0 != 0xFF && save) {
        (*(u8 **)((u8 *)&D_800CCA0C + arg0 * 0x32C))[0x11B] = idx;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/level_start_point_get.s")
#endif
/* was func_15085880 */
void player_start_index_set(struct_eu_B2980 *arg0, s32 arg1) {
    arg0->unk31C->unk11B = arg1;
}

/* was func_15085890 */
u8 player_start_index_get(struct_eu_B2980 *arg0) {
    return arg0->unk31C->unk11B;
}

#ifdef NON_MATCHING
/* Place object record arg0 (D_800CC2D0[i]) at level start arg1: level_start_point_get gives the start point, angle and
 * flags; anim_events_run runs with D_800D154C / D_800C3E78 temporarily set to this record; then position
 * (+0x14 / +0x2C / +0x180 / +0x1CC), yaw (+0x76..+0x7A, +0x40, +0xB8) and the camera controller's start eye
 * (camera_set_initial_eye). */
/* was func_150858A0 */
void obj_place_at_start(void *arg0, s32 arg1, s32 arg2) {
    u8 *rec = arg0;
    s16 pos[3];
    f32 eye[3];
    u8 b6B;
    u8 ang;
    s32 o60;
    s32 o64;
    struct {
        u8 *rec;
        u8 b;
    } msg;
    s32 idx;
    struct127 *save;
    u8 saveb;
    s32 v;
    u8 *ctl;

    level_start_point_get(rec[0x127], arg1, D_800D18A8, pos, eye, &b6B, &ang, &o60, &o64, arg2, NULL);
    idx = (s32)(rec - (u8 *)D_800CC2D0) / 0x32C;
    save = D_800D154C;
    saveb = D_800C3E78;
    D_800D154C = (struct127 *)rec;
    D_800C3E78 = idx;
    anim_events_run((struct127 *)rec, 800.0f, 1);
    D_800D154C = save;
    D_800C3E78 = saveb;
    *(f32 *)(rec + 0x14) = (f32)pos[0];
    *(f32 *)(rec + 0x18) = (f32)pos[1];
    *(f32 *)(rec + 0x2C) = *(f32 *)(rec + 0x14);
    *(f32 *)(rec + 0x30) = *(f32 *)(rec + 0x18);
    *(f32 *)(rec + 0x1C) = (f32)pos[2];
    *(f32 *)(rec + 0x34) = *(f32 *)(rec + 0x1C);
    v = ang << 8;
    *(s16 *)(rec + 0x7A) = v;
    *(s16 *)(rec + 0x78) = v;
    *(s16 *)(rec + 0x76) = v;
    *(f32 *)(rec + 0x40) = (f32)(s16)(v + 0x4000) * 0.0054931640625f;
    *(f32 *)(rec + 0xB8) = (f32)((b6B * 360) >> 8);
    while (180.0f < *(f32 *)(rec + 0xB8)) {
        *(f32 *)(rec + 0xB8) = *(f32 *)(rec + 0xB8) - 360.0f;
    }
    ctl = *(u8 **)(rec + 0x31C);
    *(f32 *)(rec + 0x28) = 0.0f;
    *(f32 *)(rec + 0x180) = *(f32 *)(rec + 0x18);
    if (ctl != NULL) {
        obj_collision_cylinder((struct127 *)rec, (u16 *)(ctl + 0x114), (u16 *)(ctl + 0x116), (u16 *)(ctl + 0x118));
    }
    *(f32 *)(rec + 0x1CC) = *(f32 *)(rec + 0x18);
    *(u16 *)(rec + 0x2F8) &= 0xFFEF;
    *(u16 *)(rec + 0x22C) |= 0x200;
    *(f32 *)(rec + 0x164) = 0.0f;
    *(f32 *)(rec + 0x168) = 0.0f;
    *(f32 *)(rec + 0x16C) = 0.0f;
    *(f32 *)(rec + 0x170) = 0.0f;
    if (rec[0x127] == 0xFF) {
        rec[0x83] = 0;
    } else {
        (*(u8 **)(rec + 0x31C))[0x23] = o64;
        if (D_800BE616 != 0 && D_800D18A8 != 0) {
            obj_contact_pass(rec, idx);
        }
        ctl = *(u8 **)(rec + 0x31C);
        if (ctl[0x78] == 0 && ctl[0x19B] != 4 && ctl[0x19B] != 7) {
            rec[0x83] = 0;
        }
    }
    if (*(u8 **)(rec + 0x318) != NULL) {
        camera_set_initial_eye(*(u8 **)(rec + 0x318), rec, eye);
    }
    msg.rec = rec;
    msg.b = rec[0x3B];
    node_broadcast_all((s32)&msg, 4);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/obj_place_at_start.s")
#endif
#ifdef NON_MATCHING
extern u16 D_8009015C;
extern s32 D_800D255C;
extern s32 D_800D2560;
extern s32 D_800D2564;
extern s32 D_800D2565;
extern s32 D_800D2566;
extern s32 D_800D2568;
extern s8 D_800E1050;

/* was func_15085710 */
void player_stat_modify(s16 arg0, s16 arg1, s32 arg2) {
    s32 o;
    u8 *e;
    s8 b;
    s32 w;

    if (arg0 >= 0xFF || (u32)(s32)arg1 >= 12) {
        return;
    }
    o = arg0 * 0x1C;
    e = (u8 *)&D_800D2138 + o + 4;
    switch (arg1) {
        case 0: *(s32 *)((u8 *)&D_800D255C + o) = arg2; return;
        case 1: *(s32 *)((u8 *)&D_800D2560 + o) = arg2; return;
        case 2:
            if (D_8009015C & 1) {
                arg2 = 6;
            }
            *((u8 *)&D_800D2564 + o) = arg2;
            return;
        case 3:
            *(s8 *)(e + 8) = *(s8 *)(e + 8) + arg2;
            b = *(s8 *)(e + 8);
            *(s8 *)(e + 8) = (b >= 0x65) ? 0x64 : b;
            return;
        case 4:
            if (!(D_8009015C & 1)) {
                *(s8 *)(e + 8) = *(s8 *)(e + 8) - arg2;
            }
            return;
        case 5: *((u8 *)&D_800D2565 + o) = arg2; return;
        case 6:
            *(s8 *)(e + 9) = *(s8 *)(e + 9) + arg2;
            b = *(s8 *)(e + 9);
            *(s8 *)(e + 9) = (b >= 0x64) ? 0x63 : b;
            return;
        case 7:
            *(s8 *)(e + 9) = *(s8 *)(e + 9) - arg2;
            b = *(s8 *)(e + 9);
            *(s8 *)(e + 9) = (b < 0) ? 0 : b;
            return;
        case 8: *((u8 *)&D_800D2566 + o) = arg2; return;
        case 9: *(s32 *)((u8 *)&D_800D2568 + o) = arg2; return;
        case 10:
            if (D_800BE616 != 0 && D_800E1050 != 0) {
                return;
            }
            *(s32 *)(e + 0xC) += arg2;
            return;
        case 11:
            w = *(s32 *)(e + 0xC) - arg2;
            *(s32 *)(e + 0xC) = w;
            *(s32 *)(e + 0xC) = (w < 0) ? 0 : w;
            return;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/player_stat_modify.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800D255C;          /* per-player records, 0x1C bytes each (fields at +0, +4, +8, +9, +0xA, +0xC) */
extern s32 D_800D2560;
extern s32 D_800D2564;
extern s32 D_800D2565;
extern s32 D_800D2566;
extern s32 D_800D2568;

/* Query field `field` of player `player`'s record (0: the bit in D_800D2340). Players >= 0xFF give 0. */
/* was func_150859AC */
s32 player_stat_get(s16 player, s32 field) {
    s32 off = player * 0x1C;

    if (player >= 0xFF) {
        return 0;
    }
    switch ((s16)field) {
    case 0:
        return (u16)D_800D2340 & (1 << player);
    case 1:
        return *(s32 *)((u8 *)&D_800D255C + off);
    case 2:
        return *(s32 *)((u8 *)&D_800D2560 + off);
    case 3:
        return *(s8 *)((u8 *)&D_800D2564 + off);
    case 4:
        return *(s8 *)((u8 *)&D_800D2565 + off);
    case 5:
        return *(u8 *)((u8 *)&D_800D2566 + off);
    case 6:
        return *(s32 *)((u8 *)&D_800D2568 + off);
    }
    return 0; /* the asm returns whatever v0 held */
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/player_stat_get.s")
#endif
/* was func_15085ABC */
void player_stats_store_health(s16 arg0)
{
  long var_s0;
  var_s0 = 0;
  if (D_800D18A8 == 0)
  {
    do
    {
      if ((1 << var_s0) & arg0)
      {
        player_stat_modify(var_s0, 5, (s32) D_800CC2D0[var_s0].health);
      }
      var_s0 += 1;
    }
    while (var_s0 != 4);
  }
}
