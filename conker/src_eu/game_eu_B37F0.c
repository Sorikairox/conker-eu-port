#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15088CA0(u8 *);

extern s8 D_800D27B9;

extern s32 D_800D27B4;

extern s8 D_800D27B8;


u8 *func_1502B5C8(s32, s32, s32, s32);
s32 func_15086058();
extern s16 D_80087634;

void func_15085FE0(s32 arg0) {
    u8 *temp_v0;

    temp_v0 = func_1502B5C8(0, 2, 0x19, arg0);
    if (temp_v0 == NULL) {
        D_80087630 = 0;
        D_80087634 = 0;
        D_800D2778 = NULL;
    } else {
        D_80087630 = (*(s16 *)temp_v0);
        D_80087634 = (*(s16 *)((u8 *)temp_v0 + 2));
        D_800D2778 = temp_v0 + 4;
    }
    func_15086058();
}

#ifdef NON_MATCHING
extern u8 D_800D2780; /* number of used height bands in D_800D2770 */
// point_bands_build: groups the D_800D2778 points by band (byte +6, 6 bands) and keeps each band's height range
// (+2). The used bands go in D_800D2770 (count D_800D2780) and the split heights between consecutive used bands in
// D_800D2788 (midpoint of band i's top and band i+1's bottom; a last 100000 entry ends func_15086218's search).
// Returns 1 when two consecutive bands overlap. Level start (func_15085FE0).
s32 func_15086058(void) {
    f32 top[6];
    f32 bottom[6];
    s32 overlap = 0;
    s32 i;
    struct_eu_800D2778 *p;
    f32 y;
    u8 a;
    u8 b;

    for (i = 0; i < 6; i++) {
        bottom[i] = 10000.0f;
        top[i] = -10000.0f;
    }
    for (i = 0, p = D_800D2778; i < D_80087630; i++, p++) {
        y = p->unk2;
        if (y < bottom[p->pad6]) {
            bottom[p->pad6] = y;
        }
        if (top[p->pad6] < y) {
            top[p->pad6] = y;
        }
    }
    D_800D2780 = 0;
    for (i = 0; i < 6; i++) {
        if (bottom[i] <= top[i]) {
            D_800D2770[D_800D2780++] = i;
        }
    }
    for (i = 0; i < D_800D2780 - 1; i++) {
        a = D_800D2770[i];
        b = D_800D2770[i + 1];
        D_800D2788[i] = (bottom[b] + top[a]) * 0.5f;
        if (bottom[b] < top[a]) {
            overlap = 1;
        }
    }
    D_800D2788[i] = 100000.0f;
    return overlap;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15086058.s")
#endif

s32 func_15086218(f32 arg0) {
    s32 i = 0;

    while (D_800D2788[i] <= arg0) {
        i++;
    }
    return D_800D2770[i];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15086268.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15086508.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150867D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15087040.s")

s32 func_150870E0(s32 arg0) {
    s32 temp_v1 = D_800D2778[arg0].unk4;

    return func_150A3674(3, 0xB, D_800D2778[arg0].unk0, D_800D2778[arg0].unk2, temp_v1);
}

s32 func_1508712C(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    if ((arg0 < 0) || (arg0 >= D_80087630)) {
        return 0;
    }
    *arg1 = (f32) D_800D2778[arg0].unk0;
    *arg2 = (f32) D_800D2778[arg0].unk2;
    *arg3 = (f32) D_800D2778[arg0].unk4;
    return 1;
}

s32 func_150871B8(s32 arg0) {
    s32 i;

    for (i = 0; i < D_80087630; i++) {
        if (arg0 == D_800D2778[i].unk7) {
            return i;
        }
    }
    return 0xFF;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15087204.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15087540.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150877C0.s")

#ifdef NON_MATCHING
extern s8 D_800D27C9;
void func_15089664(u8 *rec, u8 *player);
void func_15089B68(u8 *rec, u8 *player, s32 release);

// rail_cameras_update: clears D_800D27C9 and runs the rail camera of each of the D_800D27B8 player records
// (D_80087640, 0x84 bytes) whose player (D_800CC2D0 + rec[0x31]) has a camera (+0x318): records in state 2 or more
// (rec[0x30]) follow the rail (func_15089664), the others with rec[0x48] == 0 run the spline camera
// (func_15089B68), and the rest release the spline camera once while rec[0x49] is set.
void func_15088130(void) {
    u8 *rec;
    u8 *player;
    s32 i;

    D_800D27C9 = 0;
    if (D_80087640 == NULL) {
        return;
    }
    for (i = 0; i < D_800D27B8; i++) {
        rec = (u8 *) D_80087640 + i * 0x84;
        player = (u8 *) &D_800CC2D0[(s8) rec[0x31]];
        if (*(s32 *) (player + 0x318) == 0) {
            continue;
        }
        if ((s8) rec[0x30] >= 2) {
            func_15089664(rec, player);
        } else if (rec[0x48] == 0) {
            func_15089B68(rec, player, 0);
        } else if ((s8) rec[0x49] != 0) {
            func_15089B68(rec, player, 1);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088130.s")
#endif

s32 func_15088D24(u8, u8, s32);
void func_1508823C(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_v1;
    s32 temp_v0;
    if (D_80087640 != NULL) {
        temp_v1 = &D_80087640[arg0];
        if (arg1 != (s8) temp_v1->pad28[7]) {
            if (arg1 != 0) {
                temp_v0 = func_15088D24(temp_v1->pad28[3], temp_v1->pad28[4], 1);
                temp_v1->pad28[5] = temp_v0;
                temp_v1->pad28[6] = func_15088D24(temp_v1->pad28[4], temp_v0, 1);
            }
            temp_v1->pad28[7] = (u8) arg1;
        }
    }
}

#ifdef NON_MATCHING
// obj_yaw_clamp_to_track: keeps the object's yaw (+0x76) within 0x2400 of a quarter turn (+0x4000) past player
// `player`'s track direction (record D_80087640 + player * 0x84, vector +0x10 / +0xC, func_1505A630). Nothing without
// player records. Returns func_1505A630's raw result (the asm leaves v0 unset without records; the one caller
// ignores it).
s32 func_150882C4(u8 player, struct127 *obj) {
    struct_eu_80087640 *rec;
    s32 r;
    u16 dir;
    u16 diff;

    if (D_80087640 == NULL) {
        return 0;
    }
    rec = &D_80087640[player];
    r = func_1505A630(*(f32 *) ((u8 *) rec + 0x10), *(f32 *) ((u8 *) rec + 0xC), 0);
    dir = r + 0x4000;
    diff = dir - *(u16 *) ((u8 *) obj + 0x76);
    if (diff & 0x8000) {
        if (diff < 0xDBFF) {
            *(u16 *) ((u8 *) obj + 0x76) = dir + 0x2400;
        }
    } else if (diff > 0x2400) {
        *(u16 *) ((u8 *) obj + 0x76) = dir - 0x2400;
    }
    return r;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150882C4.s")
#endif

#ifdef NON_MATCHING
extern s8 D_800D27C8;

// player_face_track_side: turns the object (+0x76 yaw) a quarter turn (+0x3600 / +0x4A00) from the direction of
// player `player`'s track vector (+0x10 / +0xC, func_1505A630), the side picked by the track position +0 against 0.5
// (mirrored when D_800D27C8 is set). Returns that direction (0 without player records); the one caller ignores it.
s32 func_15088360(s32 player, struct127 *obj) {
    struct_eu_80087640 *rec;
    u16 dir;

    if (D_80087640 == NULL) {
        return 0;
    }
    rec = &D_80087640[player];
    dir = func_1505A630(*(f32 *)((u8 *)rec + 0x10), *(f32 *)((u8 *)rec + 0xC), 0);
    if (D_800D27C8 == 0) {
        if (rec->unk0 < 0.5f) {
            *(u16 *)((u8 *)obj + 0x76) = dir + 0x4A00;
        } else {
            *(u16 *)((u8 *)obj + 0x76) = dir + 0x3600;
        }
    } else {
        if (0.5f <= rec->unk0) {
            *(u16 *)((u8 *)obj + 0x76) = dir + 0x4A00;
        } else {
            *(u16 *)((u8 *)obj + 0x76) = dir + 0x3600;
        }
    }
    return dir;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088360.s")
#endif

void func_15088434(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_v1;

    if (D_80087640 != NULL) {
        temp_v1 = &D_80087640[arg0];
        temp_v1->unk31 = arg1;
    }
}

void func_1508845C(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_v1;

    if (D_80087640 != NULL) {
        temp_v1 = &D_80087640[arg0];
        temp_v1->unk4 = arg1 * (1.0f / 256);
    }
}

struct216 *func_1507BB28(s32, s32);

s32 func_1508849C(struct_eu_80087640 *arg0, struct127 *arg1, s32 arg2) {
    struct126 *temp_v0;

    temp_v0 = arg1->unk31C;
    if (temp_v0->unk120 != 0) {
        return 1;
    }
    if (D_800D18A0 & (1 << (arg1 - D_800CC2D0))) {
        return 1;
    }
    temp_v0->unk84 = 1;
    arg1->interaction_state = 0xC;
    arg1->unk232 = arg2;
    D_800D154C = arg1;
    D_800C3E78 = *(s8 *)&arg0->unk31;
    arg1->unk218 = func_1507BB28(0, arg2);
    arg1->unk21C = 0;
    arg1->immune = 0xFF;
    arg0->pad28[8] = 2;
    return 0;
}

s32 func_1508849C(struct_eu_80087640 *, struct127 *, s32); // 3 params: the asm never reads a3 (s87)
extern s8 D_800D27BA;

s32 func_15088568(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_a0;
    struct127 *temp_a1;
    s8 temp_v1;
    s32 var_a2;
    struct_eu_80087640 *sp1C;

    var_a2 = 0;
    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    temp_v1 = (s8) temp_a0->pad28[8];
    temp_a1 = &D_800CC2D0[(s8) temp_a0->unk31];
    if (temp_v1 == 0) {
        sp1C = temp_a0;
        var_a2 = func_1508849C(temp_a0, temp_a1, arg1);
    } else if (temp_v1 == 1) {
        temp_a0->pad28[8] = 2;
        temp_a1->immune = 0xFF;
    }
    temp_a0->pad28[2] = (u8) D_800D27BA;
    D_800D27BA += 1;
    return var_a2;
}

s32 func_1508863C(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk0 * 256.0f;
}

s32 func_15088688(s32 arg0) {
    struct_eu_80087640 *temp_a0;
    s16 temp_a2;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    temp_a2 = temp_a0->unk24;
    return (temp_a2 * 16) + (s32)(temp_a0->unk8 * 16.0f);
}

s32 func_150886E0(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk14 * 0.8f;
}

s32 func_1508872C(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk27;
}

#ifdef NON_MATCHING
// player_place_gap: finds the other player whose place (+0x29) is `player`'s place + `delta` and returns the absolute
// track-progress gap to it (lap +0x24 * 16 + segment +8 * 16) << 8 | its index; 16 when there is none.
s32 func_15088760(s32 player, s32 delta) {
    struct_eu_80087640 *me;
    struct_eu_80087640 *other;
    s32 place;
    s32 gap;
    s32 i;

    if (D_80087640 == NULL) {
        return 16;
    }
    me = &D_80087640[player];
    place = *(s8 *)((u8 *)me + 0x29) + delta;
    for (i = 0, other = D_80087640; i < D_800D27B8; i++, other++) {
        if (place == *(s8 *)((u8 *)other + 0x29) && i != player) {
            gap = me->unk24 * 16 + (s32)(me->unk8 * 16.0f) - other->unk24 * 16 - (s32)(other->unk8 * 16.0f);
            if (gap < 0) {
                gap = -gap;
            }
            return (gap << 8) | i;
        }
    }
    return 16;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088760.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_1508882C.s")

// K&R: func_15088BFC calls this without the argument.
s32 func_150889D8(arg0)
    struct127 *arg0;
{
    s32 idx;
    s32 i;
    s32 n;
    struct_eu_80087640 *p;

    idx = arg0 - D_800CC2D0;
    if (D_80087640 == NULL) {
        return -1;
    }
    if (idx == 0) {
        return 0;
    }
    i = 1;
    n = D_800D27B8 + D_800D27B9;
    p = D_80087640 + 1;
    if (n >= 2) {
        for (;;) {
            if (idx == (s8)p->unk31) {
                return i;
            }
            i++;
            p++;
            if (i < n) { // fakematch: continue/break form keeps the loop rolled and the bnel shape
                continue;
            }
            break;
        }
    }
    return -1;
}

void func_15088A68(s32 arg0, s32 arg1)
{
  s32 a;
  s32 b;
  if (D_80087640 != 0) {
    a = (s8)D_80087640[arg1].unk31;
    b = (s8)D_80087640[arg1].pad28[8];
    bcopy(&D_80087640[arg0], &D_80087640[arg1], 0x84);
    D_80087640[arg1].unk31 = a;
    D_80087640[arg1].pad28[8] = b;
  }
}

#ifdef NON_MATCHING
// cpu_player_slot_claim: takes the first free computer-player slot (bit i of D_800D27B4, i < D_800D27B9), resets
// its record D_80087640[D_800D27B8 + i] (func_15088CA0), marks it used (+0x30 = 1) for the object record objp
// (+0x31 = its D_800CC2D0 index) and returns the record index; -1 when none is free or there are no records.
// arg1 is unused (the caller passes the object twice).
s32 func_15088B08(s32 objp, s32 arg1) {
    s32 bit = 1;
    s32 n = D_800D27B9;
    s32 i;

    if (D_80087640 == NULL) {
        return -1;
    }
    for (i = 0; i < n; i++, bit <<= 1) {
        if (!(D_800D27B4 & bit)) {
            D_800D27B4 |= bit;
            i += D_800D27B8;
            func_15088CA0((u8 *)&D_80087640[i]);
            *((u8 *)&D_80087640[i] + 0x30) = 1;
            D_80087640[i].unk31 = ((u8 *)objp - (u8 *)D_800CC2D0) / 0x32C;
            return i;
        }
    }
    return -1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088B08.s")
#endif

s32 func_150889D8();

#ifdef NON_MATCHING
/* The asm never sets a0 before calling func_150889D8: the object pointer is this function's own a0,
 * passed through (UNVERIFIED: check the asm callers pass a struct127 *). */
void func_15088BFC(struct127 *arg0) {
#else
void func_15088BFC(void) {
#endif
    s32 temp_v0;

    if (D_80087640 != NULL) {
#ifdef NON_MATCHING
        temp_v0 = func_150889D8(arg0);
#else
        temp_v0 = func_150889D8();
#endif
        D_80087640[temp_v0].unk31 = 0;
        D_800D27B4 &= ~(1 << (temp_v0 - D_800D27B8));
    }
}

s32 func_15088C74(void) {
    if (D_80087640 == NULL) {
        return 0;
    }
    return D_80087640->unk46 == 0xFF;
}

void func_15088CA0(u8 *arg0) {
    (*(s8 *)((u8 *)arg0 + 0x2B)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2C)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x28)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x1C)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x20)) = -1;
    (*(s8 *)((u8 *)arg0 + 0x2F)) = 0;
    (*(f32 *)((u8 *)arg0 + 8)) = 0.0f;
    (*(f32 *)arg0) = 0.5f;
    (*(f32 *)((u8 *)arg0 + 4)) = 0.5f;
    (*(s16 *)((u8 *)arg0 + 0x24)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x26)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x27)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x31)) = 0;
    (*(f32 *)((u8 *)arg0 + 0xC)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x14)) = 0.0f;
    (*(s8 *)((u8 *)arg0 + 0x33)) = 2;
    (*(s8 *)((u8 *)arg0 + 0x30)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2A)) = 0x7F;
    (*(s8 *)((u8 *)arg0 + 0x49)) = 0;
    (*(f32 *)((u8 *)arg0 + 0x10)) = 1.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088D24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088E84.s")

f32 func_15144BC8(f32);
f32 func_15049AD0(s32 *, s32, f32);
f32 func_15049B94(s32 *, s32, f32, s32 *);
s32 func_15088E84(struct_eu_80087640 *, f32); // 2 params: the asm never reads a2 (s87)
s32 func_150893AC(struct_eu_80087640 *, s32 *, s32 *, s32 *);

void func_150891D4(u8 *arg0)
{
  u8 *new_var;
  u8 *new_var2;
  s32 sp98[2];
  s32 sp88[4];
  s32 sp78[4];
  s32 sp68[4];
  f32 temp_f0;
  s16 temp_v0_2;
  s32 temp_v0;
  s32 var_v0;
  struct_eu_80087640 *temp_s4;
  struct_eu_800D2778 *temp_a1;
  u8 *var_v1;
  u8 temp_a0;
  u8 var_s0;
  temp_v0 = func_150889D8(arg0);
  if (temp_v0 >= 0)
  {
    temp_s4 = &D_80087640[temp_v0];
    temp_s4->unk0 = 0.5f;
    temp_s4->unk4 = 0.5f;
    temp_s4->unk8 = 0.5f;
    do
    {
      var_s0 = 0;
      var_v0 = 0;
      var_v1 = (u8 *) &D_800D2778[temp_s4->pad28[4]];
      do
      {
        temp_a0 = var_v1[9];
        var_v0 += 1;
        if (temp_a0 != 0xFF)
        {
          temp_a1 = &D_800D2778[temp_a0];
          if (temp_a1->pad8[6] == 4)
          {
            var_s0 = temp_a1->pad8[7];
          }
        }
        var_v1 += 1;
      }
      while (var_v0 != 5);
      if (var_s0)
      {
        func_15088E84(temp_s4, 1.0f);
      }
    }
    while (var_s0 != 0);
    temp_s4->unk8 = 0.0f;
    func_150893AC(temp_s4, sp88, sp78, sp68);
    *((f32 *) (((u8 *) arg0) + 0x14)) = func_15049B94(sp88, 0, temp_s4->unk8, &sp98[1]);
    new_var2 = ((u8 *) arg0) + 0x18; // fakematch: permuter temp
    *((f32 *) new_var2) = func_15049AD0(sp78, 0, temp_s4->unk8);
    *((f32 *) (((u8 *) arg0) + 0x1C)) = func_15049B94(sp68, 0, temp_s4->unk8, sp98);
    temp_f0 = func_15144BC8(((f32) (func_1505A630(*((f32 *) (((u8 *) temp_s4) + 0x10)), *((f32 *) (((u8 *) temp_s4) + 0xC)), 0) + 0x8000)) * 0.005493164f);
    new_var = (u8 *) arg0; // fakematch: permuter temp
    *((f32 *) (new_var + 0x40)) = temp_f0;
    temp_v0_2 = (s32) (temp_f0 * 182.04445f);
    temp_v0_2 = temp_v0_2 - 0x4000;
    *((s16 *) (((u8 *) arg0) + 0x7A)) = temp_v0_2;
    *((s16 *) (((u8 *) arg0) + 0x78)) = temp_v0_2;
    *((s16 *) (((u8 *) arg0) + 0x76)) = temp_v0_2;
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150893AC.s")

#ifdef NON_MATCHING
// rail_node_next: the rail node after `node` coming from `prev` (D_800D2778, D_80087630 nodes of 16 bytes: s16 x / y / z,
// links +9..+0xD (0xFF = none), type +0xE, band +0xF). Takes the links in order, skipping 0xFF and `prev`; a link of
// type `type` (any type when `type` is 0xFF) and band `band` is returned at once, otherwise the last link of the right
// type. 0xFF when `node` is out of range or no link fits.
u8 func_150894F8(u8 node, u8 type, u8 prev, u8 band) {
    u8 *p;
    u8 *q;
    u8 last = 0xFF;
    u8 link;
    s32 k;

    if (node >= D_80087630) {
        return 0xFF;
    }
    p = (u8 *) &D_800D2778[node];
    for (k = 0; k < 5; k++) {
        link = p[9 + k];
        if (link == 0xFF || link == prev) {
            continue;
        }
        q = (u8 *) &D_800D2778[link];
        if (q[0xE] == type || type == 0xFF) {
            last = link;
            if (q[0xF] == band) {
                return link;
            }
        }
    }
    return last;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150894F8.s")
#endif

#ifdef NON_MATCHING
extern u16 D_8009015C;
void func_1512DAD0(u8 *, s32, void *);
u8 func_150894F8(u8 node, u8 type, u8 prev, u8 band);

// rail_camera_follow: rail camera of one player record (D_80087640 + i * 0x84, player = D_800CC2D0 + rec[0x31],
// camera = player + 0x318) on the rail nodes of D_800D2778 (band 1 when D_8009015C bit 6 is set, else 0). State 2
// (rec[0x30]) sets it up: the first type-5 band-2 node starts the segment rec[0x4A] -> rec[0x4B] (rec[0x4B] = its
// band-3 link, or its non-band-3 link when D_800D27C8 is set), then the whole rail loop is walked from there and the
// segment whose end node is nearest the player (x / z) is kept; camera mode 5, state 3. Every call: the segment moves
// on when the player is nearer its end node than its start; the camera (mode 7, parameters at rec + 0x4C) looks at the
// player from that node's direction, at most 1000 units back. Camera +0x19C..+0x1A8 = 30.
void func_15089664(u8 *rec, u8 *player) {
    u8 *cam = *(u8 **) (player + 0x318);
    u8 band;
    u8 *node;
    u8 *a;
    u8 *b;
    u8 link;
    u8 start;
    u8 cur;
    u8 prev;
    u8 next;
    s32 i;
    s32 k;
    f32 best;
    f32 d;
    f32 dB;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;

    if (cam == NULL) {
        return;
    }
    band = (D_8009015C & 0x40) ? 1 : 0;
    if ((s8) rec[0x30] == 2) {
        for (i = 0; i < D_80087630; i++) {
            node = (u8 *) &D_800D2778[i];
            if (node[0xE] != 5 || node[0xF] != 2) {
                continue;
            }
            rec[0x4A] = i;
            rec[0x4B] = i;
            for (k = 0; k < 5; k++) {
                link = node[9 + k];
                if (link == 0xFF) {
                    continue;
                }
                if (D_800D27C8 == 0) {
                    if (((u8 *) &D_800D2778[link])[0xF] == 3) {
                        rec[0x4B] = link;
                    }
                } else if (((u8 *) &D_800D2778[link])[0xF] != 3) {
                    rec[0x4B] = link;
                }
            }
            break;
        }
        start = rec[0x4B];
        cur = start;
        prev = rec[0x4A];
        best = 1.0e9f;
        do {
            node = (u8 *) &D_800D2778[cur];
            next = func_150894F8(cur, 0xFF, prev, band);
            dx = *(f32 *) (player + 0x14) - *(s16 *) node;
            dz = *(f32 *) (player + 0x1C) - *(s16 *) (node + 4);
            prev = cur;
            cur = next;
            d = dx * dx + dz * dz;
            if (d < best) {
                best = d;
                rec[0x4A] = prev;
                rec[0x4B] = next;
            }
        } while (cur != start);
        func_1512DAD0(*(u8 **) (player + 0x318), 5, NULL);
        rec[0x30] = 3;
    }

    b = (u8 *) &D_800D2778[rec[0x4B]];
    dx = *(f32 *) (player + 0x14) - *(s16 *) b;
    dz = *(f32 *) (player + 0x1C) - *(s16 *) (b + 4);
    dB = dx * dx + dz * dz;
    a = (u8 *) &D_800D2778[rec[0x4A]];
    node = a;
    dx = *(f32 *) (player + 0x14) - *(s16 *) a;
    dz = *(f32 *) (player + 0x1C) - *(s16 *) (a + 4);
    d = dx * dx + dz * dz;
    if (dB < d) {
        prev = rec[0x4A];
        rec[0x4A] = rec[0x4B];
        rec[0x4B] = func_150894F8(rec[0x4A], 0xFF, prev, band);
        node = b;
        dx = *(f32 *) (player + 0x14) - *(s16 *) b;
        dz = *(f32 *) (player + 0x1C) - *(s16 *) (b + 4);
        d = dB;
    }
    dy = *(f32 *) (player + 0x18) - *(s16 *) (node + 2);
    dist = sqrtf(dy * dy + d);
    dx /= dist;
    dy /= dist;
    dz /= dist;
    if (1000.0f < dist) {
        dist = 1000.0f;
    }
    *(s32 *) (rec + 0x4C) = 0;
    *(f32 *) (rec + 0x6C) = *(f32 *) (player + 0x14);
    *(f32 *) (rec + 0x70) = *(f32 *) (player + 0x18);
    *(f32 *) (rec + 0x74) = *(f32 *) (player + 0x1C);
    *(f32 *) (rec + 0x60) = *(f32 *) (player + 0x14) - dx * dist;
    *(f32 *) (rec + 0x64) = *(f32 *) (player + 0x18) - dy * dist;
    *(f32 *) (rec + 0x68) = *(f32 *) (player + 0x1C) - dz * dist;
    *(s32 *) (rec + 0x50) = 0;
    *(f32 *) (rec + 0x7C) = 30.0f;
    *(f32 *) (rec + 0x80) = 30.0f;
    *(f32 *) (rec + 0x78) = 0.0f;
    func_1512DAD0(*(u8 **) (player + 0x318), 7, rec + 0x4C);
    *(f32 *) (cam + 0x19C) = 30.0f;
    *(f32 *) (cam + 0x1A4) = 30.0f;
    *(f32 *) (cam + 0x1A0) = 30.0f;
    *(f32 *) (cam + 0x1A8) = 30.0f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15089664.s")
#endif

#ifdef NON_MATCHING
void func_1512DAD0(u8 *, s32, void *);
u8 func_150894F8(u8 node, u8 type, u8 prev, u8 band);

// rail_camera_spline: spline camera of one player record (D_80087640 + i * 0x84, camera = player + 0x318).
// `release` != 0: camera mode 10 (rec + 0x4C params: +0x58 = 999, +0x5C = 120), then mode 6 with the camera's +0x23D,
// rec[0x49] = 0. Else, on the first call (rec[0x49] == 0): the first type-6 node of band D_800D27C8 + 1 and the next
// three type-6 nodes after it fill rec[0x44..0x47], the player position is kept at rec + 0x38, t (rec + 0x34) = 0,
// camera mode 5, rec[0x49] = 1. Each call t += 0.017 * D_800BE9E4; past 1 the four nodes shift on by one (t stays at
// 1 at the rail end). The eye points are the nodes rec[0x44 + k] (from rec + 0x38 behind the player's yaw +0x40 for
// the first missing one, then extrapolated), the targets their type-4 links; func_15049AD0 interpolates both at t
// into rec + 0x60 / + 0x6C and camera mode 7 takes rec + 0x4C.
void func_15089B68(u8 *rec, u8 *player, s32 release) {
    u8 *cam = *(u8 **) (player + 0x318);
    f32 pt[6][4]; // eye x / y / z, target x / y / z for the four nodes
    f32 t;
    f32 ang;
    u8 want;
    u8 old;
    u8 node;
    s32 had;
    s32 i;
    s32 k;
    s32 j;

    if (cam == NULL) {
        return;
    }
    if (release) {
        *(s32 *) (rec + 0x5C) = 120;
        *(f32 *) (rec + 0x58) = 999.0f;
        func_1512DAD0(*(u8 **) (player + 0x318), 10, rec + 0x4C);
        func_1512DAD0(*(u8 **) (player + 0x318), 6, (void *) (s32) cam[0x23D]);
        rec[0x49] = 0;
        return;
    }
    if ((s8) rec[0x49] == 0) {
        want = D_800D27C8 + 1;
        for (i = 0; i < D_80087630; i++) {
            if (((u8 *) &D_800D2778[i])[0xE] == 6 && ((u8 *) &D_800D2778[i])[0xF] == want) {
                rec[0x44] = i;
                break;
            }
        }
        rec[0x45] = func_150894F8(rec[0x44], 6, 0xFF, 0);
        rec[0x46] = func_150894F8(rec[0x45], 6, rec[0x44], 0);
        rec[0x47] = func_150894F8(rec[0x46], 6, rec[0x45], 0);
        *(f32 *) (rec + 0x38) = *(f32 *) (player + 0x14);
        *(f32 *) (rec + 0x3C) = *(f32 *) (player + 0x18);
        *(f32 *) (rec + 0x34) = 0.0f;
        *(f32 *) (rec + 0x40) = *(f32 *) (player + 0x1C);
        func_1512DAD0(*(u8 **) (player + 0x318), 5, (void *) (s32) cam[0x23D]);
        rec[0x49] = 1;
    }
    *(f32 *) (rec + 0x34) += 0.017f * (f32) D_800BE9E4;
    t = *(f32 *) (rec + 0x34);
    if (1.0f <= t) {
        node = rec[0x46];
        if (node == 0xFF) {
            *(f32 *) (rec + 0x34) = 1.0f;
        } else {
            old = rec[0x45];
            rec[0x45] = node;
            *(f32 *) (rec + 0x34) = t - 1.0f;
            rec[0x46] = rec[0x47];
            rec[0x44] = old;
            rec[0x47] = func_150894F8(rec[0x46], 6, node, 0);
        }
    }

    had = 0;
    for (k = 0; k < 4; k++) {
        if (rec[0x44 + k] != 0xFF) {
            had = 1;
            func_1508712C(rec[0x44 + k], &pt[0][k], &pt[1][k], &pt[2][k]);
            func_1508712C(func_150894F8(rec[0x44 + k], 4, 0xFF, 0), &pt[3][k], &pt[4][k], &pt[5][k]);
        } else if (had == 1) {
            had = 0;
            ang = *(f32 *) (player + 0x40) * 0.01745;
            pt[0][k] = *(f32 *) (rec + 0x38) - sinf(ang) * 500.0f;
            pt[1][k] = *(f32 *) (rec + 0x3C) + 180.0f;
            pt[2][k] = *(f32 *) (rec + 0x40) - cosf(ang) * 500.0f;
            pt[3][k] = *(f32 *) (rec + 0x38);
            pt[4][k] = *(f32 *) (rec + 0x3C) + 120.0f;
            pt[5][k] = *(f32 *) (rec + 0x40);
        } else if (k >= 2) {
            // the asm also extrapolates at k = 0 / 1 (rec[0x44] == 0xFF) from stack garbage; left 0 here
            for (j = 0; j < 6; j++) {
                pt[j][k] = (pt[j][k - 1] - pt[j][k - 2]) + pt[j][k - 1];
            }
        } else {
            for (j = 0; j < 6; j++) {
                pt[j][k] = 0.0f;
            }
        }
    }
    t = *(f32 *) (rec + 0x34);
    *(f32 *) (rec + 0x60) = func_15049AD0((s32 *) pt[0], 0, t);
    *(f32 *) (rec + 0x64) = func_15049AD0((s32 *) pt[1], 0, t);
    *(f32 *) (rec + 0x68) = func_15049AD0((s32 *) pt[2], 0, t);
    *(f32 *) (rec + 0x6C) = func_15049AD0((s32 *) pt[3], 0, t);
    *(f32 *) (rec + 0x70) = func_15049AD0((s32 *) pt[4], 0, t);
    *(f32 *) (rec + 0x74) = func_15049AD0((s32 *) pt[5], 0, t);
    *(s32 *) (rec + 0x4C) = 0;
    *(s32 *) (rec + 0x50) = 0;
    *(f32 *) (rec + 0x7C) = 30.0f;
    *(f32 *) (rec + 0x80) = 30.0f;
    *(f32 *) (rec + 0x78) = 0.0f;
    func_1512DAD0(*(u8 **) (player + 0x318), 7, rec + 0x4C);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15089B68.s")
#endif
