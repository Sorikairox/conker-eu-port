#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 ground_glow_b_spawn();
/* was func_150C6BF0 */
void ground_glow_b_keep_alive(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x6C) != 0) {
        u8 *p = *(u8 **)(arg0 + 0x6C);
        p += 0xB0;
        p[4] = 1;
    } else {
    *(s32 *)(arg0 + 0x6C) = ground_glow_b_spawn(arg0);
    }
}

typedef struct {
    u8 pad0[4];
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 pad1A;
    f32 unk1C;
} struct_C630;
/* was func_150C6C3C */
s8 ground_glow_b_flicker_update(u8 *arg0) {
    s8 ret;
    struct_C630 *p;
    ret = 1;
    p = (struct_C630 *)(arg0 + 0xB0);
    if (p->unk4 == 0) {
        ret = 0;
    }
    p->unk4 = 0;
    p->unk14 -= D_800BE9E4;
    if (p->unk14 < 0) {
        p->unk14 = ((u32)random_int() % (u32)(p->unk18 + 1)) + p->unk16;
        p->unk10 = (random_float() * p->unkC) + p->unk8;
    }
    *(s32 *)(arg0 + 0x24) += (s32)((p->unk10 - (f32)*(s32 *)(arg0 + 0x24)) * p->unk1C);
    return ret;
}

s32 sprite_fx_set_handlers(u8 *, s32, s32);
/* was func_150C6D2C */
s32 ground_glow_b_detach(u8 *arg0)
{
  u8 *p;
  p = *((u8 **) (arg0 + 0xB0));
  p += 0x59;  // fakematch: keeps the dead addiu (p += K+1; p--;)
  p--;  // fakematch: pairs with p += K+1
  *((s32 *) (p + 0x14)) = 0;
  *((s32 *) (arg0 + 0xB0)) = 0;
  *((s32 *) (arg0 + 0x18)) = (*((s32 *) (arg0 + 0x18))) | 2;
  sprite_fx_set_handlers(arg0, 0, 0);
  return 0;
}

s32 ground_trail_b_spawn(s32, u8 *, s32);

/* was func_150C6D70 */
void ground_trail_b_keep_alive(u8 *arg0)
{
  u8 *new_var4;
  u8 *new_var;
  s32 *new_var3;
  u8 *new_var2;
  s32 temp_a2;
  do
  {
    new_var2 = arg0;
    temp_a2 = *((s32 *) (((u8 *) new_var2) + 0x18));
    new_var = ((u8 *) new_var2) + 0x70;
    if (((*((s32 *) new_var)) != 0) ^ 0)
    {
      temp_a2++;
      temp_a2--;
      new_var3 = (s32 *) new_var;
      new_var4 = (u8 *) ((*new_var3) + 0x58);
      new_var2 = new_var4 + 4;
      *((s8 *) new_var2) = 1;
      goto dummy_label_302949;
      dummy_label_302949:
      ;

      ;
      ;
      return;
    }
  }
  while (0);
  *((s32 *) new_var) = ground_trail_b_spawn(temp_a2, new_var2, *((s32 *) (((u8 *) new_var2) + 0x18)));
}

s32 collision_floor_dynamic_b_full(f32 *, s32, f32, u8 *);
s32 emitter_trail_spawn(s32 *, s32, s32, s32);
s32 memcpy(s32, u8 **, s32);

/* was func_150C6DC4 */
s32 ground_trail_b_spawn(s32 arg0, u8 *arg1, s32 arg2) {
    struct {
        f32 u24;
        f32 u28;
        f32 u2C;
        u8 pad30[0x4];
        u8 * u34;
        s8 u38;
        u8 pad39[0x3];
        f32 u3C;
        s32 u40;
        s32 u44;
        u8 u48;
        u8 pad49[0x3];
        s32 u4C;
        s8 u50;
        u8 pad51[0x3];
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        s8 u6A;
        s8 u6B;
        s8 u6C;
        s8 u6D;
    } sp;
    s32 temp_v0;

    sp.u38 = 1;
    sp.u34 = arg1;
    sp.u24 = (*(f32 *)((u8 *)arg0 + 0x14));
    sp.u28 = (*(f32 *)((u8 *)arg0 + 0x18)) + 5000.0f;
    sp.u2C = (*(f32 *)((u8 *)arg0 + 0x1C));
    if (collision_floor_dynamic_b_full(&sp.u24, 0, (*(f32 *)((u8 *)arg0 + 0x18)) - 100.0f, arg1 + 0x34) != 0) {
        sp.u3C = (*(f32 *)((u8 *)arg1 + 0x34));
    } else {
        sp.u3C = (*(f32 *)((u8 *)arg0 + 0x18)) + 5000.0f;
    }
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = arg0;
    sp.u50 = 0;
    sp.u54 = 0.0f;
    sp.u58 = 0.0f;
    sp.u5C = 0.0f;
    sp.u68 = 0x12C;
    sp.u6A = 0xA;
    sp.u6B = 5;
    sp.u6C = 2;
    sp.u6D = 3;
    sp.u48 = (*(u8 *)((u8 *)arg0 + 0x3B));
    sp.u60 = 80.0f;
    sp.u64 = 0.60497f;
    temp_v0 = emitter_trail_spawn(&sp.u40, 0xC, 0xFF, 0);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x58, &sp.u34, 0xC);
    }
    return temp_v0;
}
s32 particle_spawn_default(void *, s32, s32);
/* was func_150C6F08 */
void ground_trail_b_particle_spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        u8 u48;
        u8 u49;
        u8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        u8 u4E;
        u8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0xC];
    } sp;
    s32 obj;
    struct {
        f32 scale;
        s8 u20;
        s8 u21;
        s8 u22;
        s8 u23;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        s8 u34;
        s8 u35;
        s8 u36;
        s8 u37;
        f32 u38;
        f32 u3C;
        f32 u40;
    } b;

    sp.u51 = 0x2F;
    sp.u3C = 0xC01;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u4E = 0;
    sp.u4D = 0;
    sp.u4C = 0;
    sp.u4B = 0;
    sp.u4A = 0;
    sp.u49 = 0;
    sp.u48 = 0;
    sp.u44 = 0;
    sp.u40 = 0;
    sp.u50 = 0xFF;
    sp.u56 = 0;
    sp.u58 = 0.0f;
    sp.u8C = 0x3207;
    sp.u94 = 5;
    sp.u95 = 5;
    sp.u96 = 4;
    sp.u97 = -1;
    sp.u64 = arg0;
    sp.u68 = arg1;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    sp.u52 = 0x1E;
    sp.u54 = 8;
    sp.u6C = arg2;
    b.u40 = *(f32 *)(arg6 + 0x60);
    b.u2C = 4.0f;
    b.u30 = 0.25f;
    b.u20 = 0;
    b.u21 = 0;
    b.u34 = 0;
    b.u35 = 0;
    sp.u7C = -arg3 * 0.2f;
    sp.u80 = 0.0f;
    sp.u84 = -arg5 * 0.2f;
    if (random_int() & 1) {
        sp.u8C |= 0x40;
    }
    if (random_int() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u3E = (random_int() % 51U) + 0x6A;
    sp.u4F = (random_int() % 101U) + 0x64;
    b.scale = sp.u5C = sp.u60 = (random_float() * 62.0f) + 41.0f;
    b.u22 = (random_int() % 5U) + 4;
    b.u23 = (random_int() % 5U) + 4;
    b.u24 = ((random_float() * 0.25f) + 0.15f) * b.scale;
    b.u28 = ((random_float() * 0.25f) + 0.15f) * b.scale;
    b.u36 = (random_int() % 5U) + 4;
    b.u37 = (random_int() % 5U) + 4;
    b.u38 = ((random_float() * 0.1f) + 0.08f) * b.scale;
    b.u3C = ((random_float() * 0.1f) + 0.08f) * b.scale;
    sp.u88 = ((random_float() * 60.0f) + 21.0f) * 0.001f;
    obj = particle_spawn_default(&sp, 2, 0x28);
    if (obj != 0) {
        memcpy(obj + 0xA8, &b, 0x28);
    }
}

/* was func_150C721C */
s32 ground_trail_b_alive_check(u8 *arg0) {
    s32 ret = 1;
    if (arg0[0x5C] == 0) {
        ret = 0;
    }
    arg0[0x5C] = 0;
    return ret;
}

s32 object_list_move_1(u8 *);
s32 object_list_free(u8 *);

/* D_80089E40 table entries 6 / 16 (s32 (*)(obj), see emitter_trail_update): clear the data's word +0x70, then return
 * object_list_move_1 / object_list_free's result (the asm tail value). */
/* was func_150C7240 */
s32 ground_trail_b_retire(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 0x18) = 0;
    return object_list_move_1(arg0);
}

/* was func_150C7268 */
s32 ground_trail_b_free(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 0x18) = 0;
    return object_list_free(arg0);
}

s32 collision_floor_dynamic_b_full(f32 *, s32, f32, u8 *);
u8 impact_current_kind(void);
extern s32 D_80088B80;
extern s32 D_800AB7F4;

/* was func_150C7290 */
s32 ground_glow_b_spawn(u8 *arg0) {
    struct {
        u8 * u64;
        s8 u68;
        u8 pad69[0x3];
        f32 u6C;
        f32 u70;
        f32 u74;
        s16 u78;
        s16 u7A;
        s16 u7C;
        u8 pad7E[0x2];
        f32 u80;
        s32 u84;
        s16 u88;
        s8 u8A;
        u8 pad8B[0x1];
        s32 u8C;
        s32 u90;
        s8 u94;
        s8 u95;
        u8 u96;
        u8 u97;
        u8 u98;
        s8 u99;
        s8 u9A;
        s8 u9B;
        s32 u9C;
        u8 padA0[0xC];
        f32 uAC;
        f32 uB0;
        f32 uB4;
        s32 uB8;
        u8 padBC[0xC];
        f32 uC8;
        f32 uCC;
        f32 uD0;
        struct210 * uD4;
    } sp;
    f32 sp60;
    u8 sp5F;
    s32 sp54;
    s32 sp50;
    f32 temp_f10;
    struct210 *temp_v0_3;
    u8 *temp_v0;
    u8 *temp_v0_2;

    sp.uD4 = NULL;
    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x18));
    if ((*(u8 **)((u8 *)temp_v0 + 0x1D4)) != NULL) {
        (*(s32 *)((u8 *)(&sp.uB8) + 0)) = (s32) (*(s32 *)((u8 *)(&D_80088B80) + 0));
        (*(s32 *)((u8 *)(&sp.uB8) + 4)) = (s32) (*(s32 *)((u8 *)(&D_80088B80) + 4));
        (*(s32 *)((u8 *)(&sp.uB8) + 8)) = (s32) (*(s32 *)((u8 *)(&D_80088B80) + 8));
        mtx_transform_point_or_origin(&sp.uB8, &sp.uC8, (*(u8 **)((u8 *)temp_v0 + 0x1D4)));
    } else {
        sp.uC8 = (*(f32 *)((u8 *)temp_v0 + 0x14));
        sp.uCC = (*(f32 *)((u8 *)temp_v0 + 0x18));
        sp.uD0 = (*(f32 *)((u8 *)temp_v0 + 0x1C));
    }
    sp.uB0 = sp.uCC + 200.0f;
    sp.uAC = sp.uC8;
    sp.uB4 = sp.uD0;
    if (collision_floor_dynamic_b_full(&sp.uAC, 0, sp.uCC - 200.0f, arg0 + 0x34) != 0) {
        sp5F = impact_current_kind();
        sp.uB0 = (*(f32 *)((u8 *)arg0 + 0x34));
        temp_f10 = random_float() * 100.0f;
        sp.u68 = 1;
        sp60 = temp_f10 + 200.0f;
        sp.u7A = 0xA;
        sp.u7C = 0xA;
        temp_v0_2 = (u8 *) &D_800AB7F4 + sp5F * 3;
        sp.u8A = 0x38;
        sp.u88 = 0x12C;
        sp.u90 = (s32) ((32768.0f * 0.5f) + 26214.4f);
        sp.u84 = 0x20300;
        sp.u94 = 0x96;
        sp.u64 = arg0;
        sp.u78 = 0;
        sp.u8C = 0;
        sp.u95 = 0xFF;
        sp.u99 = 0xFF;
        sp.u9C = 0x440001;
        sp.u9A = 0;
        sp.u9B = 6;
        sp.u6C = 26214.4f;
        sp.u70 = 32768.0f;
        sp.u80 = 0.231f;
        sp.u74 = 0.0f;
        sp.u96 = (*(u8 *)((u8 *)temp_v0_2 + 0));
        sp.u97 = (*(u8 *)((u8 *)temp_v0_2 + 1));
        sp.u98 = (*(u8 *)((u8 *)temp_v0_2 + 2));
        sp50 = random_int();
        sp54 = random_int();
        temp_v0_3 = sprite_fx_spawn_cam((s32) &sp.u84, 9U, 3U, (s32) (arg0 + 0x38), sp.uAC, sp.uB0, sp.uB4, sp60, sp60, (u8) (sp50 & 0xFF), (u8) (((random_int() & 1) * 2) + (sp54 & 1)), 0x20, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        sp.uD4 = temp_v0_3;
        if (temp_v0_3 != NULL) {
            memcpy(&temp_v0_3->unkA4[3], &sp.u64, 0x20);
        }
    }
    return (s32) sp.uD4;
}