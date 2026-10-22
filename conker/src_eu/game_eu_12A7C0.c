#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A5860[];
extern u8 D_800A22BC[];
#endif


s32 func_150FD140(s32);
s32 func_1516547C(s32, s32, s32, s32, s32);
extern s32 func_1000EC24;

void func_150FCFB0(void) {
    s32 var_s0;
    struct { s8 u44; s8 u45; s16 u46; s8 u48; s8 u49; s8 u4A; } sp;

    func_150FD140(0);
    func_150FD140(1);
    func_150FD140(2);
    func_1000FA64(0x2B8U, -0x7F6, 0x618, -0xA47, 0x6D60, 0x2328U, 0x1B58, (s32) &func_1000EC24, (u8 *)0x2D, 0, 0, 0);
    func_1000FA64(0x2B7U, -0x13F, -0x111, -0xD5B, 0x6D60, 0x2328U, 0x1B58, (s32) &func_1000EC24, NULL, 0, 0, 0);
    func_1000FA64(0x2B6U, 0x5EF, 0x3B3, -0xA49, 0x6D60, 0x2328U, 0x1B58, (s32) &func_1000EC24, (u8 *)0x5A, 0, 0, 0);
    var_s0 = 0;
    if ((D_80082FA0 + 1) > 0) {
        do {
            func_1516547C(4, var_s0 & 0xFF, 0, 0xFF, 1);
            var_s0 += 1;
        } while (D_80082FA0 >= var_s0);
    }
    sp.u44 = 1;
    sp.u46 = 0x64;
    sp.u49 = 0xF;
    sp.u48 = 8;
    sp.u4A = -1;
    func_151D8E18((structEU_151D8E18 *) &sp, 0, 0xFFU, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FD140.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FD49C.s")

void func_150FD530(s32 arg0) {
    func_15103828();
}

#ifdef NON_MATCHING
s32 func_15046F70(u8 *, u16, f32, u8 *);
void func_1504715C(void *, u8 *);
s32 func_1505D024(struct127 *, s32, u16, s32);
s32 func_1516284C(s8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 memcpy(u8 *, struct127 **, s32);

void func_150FD554(struct127 *arg0, u8 arg1, s32 arg2) {
    struct {
        s8 u60;
        s8 u61;
        s16 u62;
        s16 u64;
        u8 pad66[0x2];
        s32 u68;
        s32 u6C;
        s8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        s32 u88;
        u8 pad8C[0x8];
        f32 u94;
        f32 u98;
        f32 u9C;
        s32 uA0;
        s8 uA4;
        s8 uA5;
        s8 uA6;
        s8 uA7;
        s32 uA8;
        s8 uAC;
        u8 padAD[0x3];
        s32 uB0;
        s16 uB4;
        s16 uB6;
        s32 uB8;
        s32 uBC;
        s32 uC0;
        s8 uC4;
        s8 uC5;
        s16 uC6;
        s8 uC8;
        u8 padC9[0xB];
        struct127 * uD4;
        u8 uD8;
        u8 padD9[0x3];
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        s32 uF8;
        s32 uFC;
        f32 u100;
        struct_eu_bytes24 u104;
        u16 u128;
        u8 pad12A[0x2];
        s8 u12C;
        s8 u12D;
        u8 pad12E[0x2];
        s8 u130;
        s8 u131;
        s16 u132;
        s16 u134;
        u8 pad136[0x2];
        s32 u138;
        s32 u13C;
        s8 u140;
        s8 u141;
        s8 u142;
        s8 u143;
        f32 u144;
        f32 u148;
        s32 u14C;
        u8 pad150[0x8];
        s32 u158;
        u8 pad15C[0x8];
        f32 u164;
        f32 u168;
        f32 u16C;
        s32 u170;
        s8 u174;
        s8 u175;
        s8 u176;
        s8 u177;
        s32 u178;
        s8 u17C;
        u8 pad17D[0x3];
        s32 u180;
        s16 u184;
        s16 u186;
        f32 u188;
        f32 u18C;
        f32 u190;
        u8 pad194[0x3];
        u8 u197;
        f32 u198;
        f32 u19C;
        f32 u1A0;
        f32 u1A4;
        s32 u1A8;
    } sp;
    f32 temp_f0;
    f32 temp_f16;
    s8 var_v0;
    u8 *temp_t1;
    u8 *temp_t4;
    u8 *temp_s0;
    u8 *temp_v0;

    if ((s32) arg0->unk7 >= 0xFF) {
        sp.u198 = arg0->x_position;
        sp.u188 = sp.u198;
        sp.u18C = arg0->y_position + 100.0f;
        sp.u1A0 = arg0->z_position;
        sp.u190 = sp.u1A0;
        func_1504715C(&sp.u1A4, arg0);
        if (func_15046F70(&sp.u188, 0, 0xC61C4000, &sp.u1A4) != 0) {
            sp.u197 = 1;
            sp.u19C = sp.u1A4;
        } else {
            sp.u197 = 0;
            sp.u19C = arg0->y_position;
        }
        func_1505D024(arg0, 0x39, arg0->unk7A, -1);
        sp.uD4 = arg0;
        sp.uDC = 60.0f;
        sp.uD8 = arg0->unique_id;
        sp.uE0 = 50.0f;
        temp_f0 = func_150ADA68();
        sp.u12C = 0;
        sp.uE8 = -2048.0f;
        sp.uEC = -2048.0f;
        sp.uE4 = temp_f0 * 6.2831855f;
        sp.uF0 = func_150ADA68() * 6.2831855f;
        temp_f16 = func_150ADA68() * 6.2831855f;
        sp.uF8 = 0;
        sp.uFC = 0;
        sp.u100 = 0.0f;
        sp.uF4 = temp_f16;
        sp.u104 = *(struct_eu_bytes24 *)(&sp.u1A4);
        sp.u128 = func_1000FA64(0x69EU, (s16) (s32) sp.u198, (s16) (s32) sp.u19C, (s16) (s32) sp.u1A0, 0x7D00, 0xBB8U, 0x1F4, 0, NULL, 0, 0, 0);
        if (sp.u197 != 0) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        sp.u12D = var_v0;
        sp.u130 = 0x59;
        sp.u131 = 0xB;
        sp.u132 = 0x5B1A;
        sp.u134 = 0x12C;
        sp.u138 = 0;
        sp.u13C = 0;
        sp.u140 = 0xFF;
        sp.u141 = 0;
        sp.u142 = 0;
        sp.u143 = 0xFF;
        sp.u174 = 0xFF;
        sp.u144 = 0.0f;
        sp.u148 = 1500.0f;
        temp_t1 = ((u8 *)&D_800A5860);
        (*(f32 *)((u8 *)(&sp.u14C) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u198) + 0));
        (*(s32 *)((u8 *)(&sp.u14C) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u198) + 4));
        (*(s32 *)((u8 *)(&sp.u14C) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u198) + 8));
        (*(s32 *)((u8 *)(&sp.u158) + 0)) = (s32) (*(s32 *)((u8 *)temp_t1 + 0));
        (*(s32 *)((u8 *)(&sp.u158) + 4)) = (s32) (*(s32 *)((u8 *)temp_t1 + 4));
        (*(s32 *)((u8 *)(&sp.u158) + 8)) = (s32) (*(s32 *)((u8 *)temp_t1 + 8));
        sp.u168 = 0.0f;
        sp.u170 = 0x24EC0008;
        sp.u175 = 0xFF;
        sp.u176 = 0;
        sp.u177 = 6;
        sp.u178 = 0;
        sp.u17C = 0xFF;
        sp.u180 = 0;
        sp.u184 = 1;
        sp.u186 = 0xFF;
        sp.u164 = 1.0f;
        sp.u16C = 1.0f;
        temp_v0 = func_1513D2F0(&sp.u130, (s32) ((u8 *)&D_800A22BC), 0U, 0x2BU, 0U, 0x24U, 0U, 0, 0, 0x5C, (u8) (s32) arg1, arg2);
        temp_s0 = temp_v0 + 0x110;
        if (temp_v0 != NULL) {
            memcpy(temp_s0, &sp.uD4, 0x5C);
            sp.uC6 = 0x12C;
            sp.uC8 = 6;
            sp.uC4 = 2;
            sp.uC5 = 2;
            sp.uB8 = (s32) sp.u198;
            sp.uBC = (s32) sp.u19C;
            sp.uC0 = (s32) sp.u1A0;
            (*(s32 *)((u8 *)temp_s0 + 0x24)) = func_1516284C(&sp.uC4, &sp.uB8, 0xFF, 0, 0, 0xFF, 0, 0, 0x17, (s32) arg1, arg2);
            if (sp.u197 != 0) {
                temp_t4 = ((u8 *)&D_800A4AA0);
                sp.u60 = 3;
                sp.u61 = 0;
                sp.u62 = 0x3103;
                sp.u64 = 0x12C;
                sp.u68 = 0;
                sp.u6C = 0;
                sp.u70 = 0xFF;
                sp.u71 = 0;
                sp.u72 = 0;
                sp.u73 = 0xFF;
                sp.uA4 = 0xFF;
                sp.u74 = 1.0f;
                sp.u78 = 1.0f;
                sp.u80 = sp.u19C + 5.0f;
                sp.u7C = sp.u198;
                sp.u84 = sp.u1A0;
                (*(s32 *)((u8 *)(&sp.u88) + 0)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0));
                (*(s32 *)((u8 *)(&sp.u88) + 4)) = (s32) (*(s32 *)((u8 *)temp_t4 + 4));
                (*(s32 *)((u8 *)(&sp.u88) + 8)) = (s32) (*(s32 *)((u8 *)temp_t4 + 8));
                sp.u94 = 1.0f;
                sp.u98 = 1.0f;
                sp.u9C = 1.0f;
                sp.uA0 = 0x04EC0008;
                sp.uA5 = 0xFF;
                sp.uA6 = 0;
                sp.uA7 = 6;
                sp.uA8 = 0;
                sp.uAC = 0xFF;
                sp.uB0 = 0;
                sp.uB4 = 1;
                sp.uB6 = 0xFF;
                (*(s32 *)((u8 *)temp_s0 + 0x28)) = func_1513D594((s32) &sp.u60, (s32) ((u8 *)&D_800A4AA0), 0U, 0U, 0U, 0U, 0, 50.0f, 50.0f, 0, (s32) &sp.u1A8, 0, 0, 0U, 0, (u8) (s32) arg1, arg2);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FD554.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FDA94.s")

void func_150FE08C(u8 *arg0, u8 *arg1, u8 arg2)
{
  s32 new_var2; // fakematch: permuter temp
  u8 new_var; // fakematch: permuter temp
  u8 *v = arg0 + 0x110;
  if (arg2 == 0x2D)
  {
    if ((*((s32 *) arg1)) == (*((s32 *) v)))
    {
      *((s32 *) v) = *((s32 *) (arg1 + 4));
      v[4] = arg1[9];
      return;
    }
    if ((*((s32 *) (arg1 + 4))) == (*((s32 *) v)))
    {
      *((s32 *) v) = *((s32 *) arg1);
      v[4] = arg1[8];
      dummy_label_617528: // fakematch: permuter artifact (unused label)
      ;

      ;
      ;
    }
  }
  else
    if (arg2 == 0)
  {
    new_var2 = *((s32 *) arg1);
    if ((new_var2 == (*((s32 *) v))) || ((new_var = v[4] ^ 0) == arg1[4])) // fakematch: ^ 0
    {
      *((s32 *) v) = 0;
    }
  }
}

u8 *func_150FE120(u8 *arg0, s16 arg1) {
    u8 *v = (u8 *)func_1513EDE4((s32)arg0, arg1);
    if (v != NULL) {
        *(s16 *)(v + 0x8) = *(f32 *)(arg0 + 0x124);
        *(s16 *)(v + 0x18) = *(f32 *)(arg0 + 0x128);
        *(s16 *)(v + 0x28) = *(f32 *)(arg0 + 0x128);
        *(s16 *)(v + 0x38) = *(f32 *)(arg0 + 0x124);
    }
    return v;
}

void func_150FE1AC(u8 *arg0)
{
  u8 *v = arg0 + 0x110; // fakematch: v defined first so IDO keeps it as a separate pointer (not folded)
  
  if (*(s32 *)(arg0 + 0x134) != 0) { func_1516972C(*(struct102 **)(arg0 + 0x134)); }
  if (*(struct102 **)(v + 0x28)) { func_1516972C(*(struct102 **)(v + 0x28)); } // fakematch: pointer-typed test gives one load (s32 test double-loads like line above)
  if (*(u16 *)(v + 0x54) != 0) { func_100111C8(*(u16 *)(v + 0x54)); }
  if (*(u16 *)(v + 0x56) != 0) func_100111C8(*(u16 *)(v + 0x56));
}

void func_150FE22C(void *arg0) {
    func_150FE1AC(arg0);
    func_1513CA6C(arg0);
}

void func_150FE258(void *arg0) {
    func_150FE1AC(arg0);
    func_1513CAA0(arg0);
}
