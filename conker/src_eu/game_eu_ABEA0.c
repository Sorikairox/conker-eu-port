#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1507E690(u8 *);
void func_1507EE9C();
s32 func_1507EA98(u8 *);
s32 func_1507ECE8(s32 arg0, s32 arg1);
u32 func_1507ED48(s32 arg0);
s32 *func_1507EDD8(s32 arg0, s32 *arg1);
void func_1507E7E4(struct127 *obj, u8 anim, u8 prio, u16 time, s32 arg4);
#endif


#ifdef NON_MATCHING
/* P48: eye blink of object obj (+0x6A / +0x6B eyelid states, +0x6E countdown in frames of D_800BE9E4). Id 0x2B
 * and D_800C35EA == 1: nothing. A player-controlled object whose controller +0x120 is set keeps both eyes at 1.
 * When the countdown runs out (and +0x6C != 1) both states toggle; reopened eyes wait 10 + random % 140. */
void func_1507E690(u8 *obj) {
    if (obj[4] == 0x2B || D_800C35EA == 1) {
        return;
    }
    if (obj[0x127] != 0xFF && (*(u8 **)(obj + 0x31C))[0x120] != 0) {
        obj[0x6A] = 1;
        obj[0x6B] = 1;
        return;
    }
    if (obj[0x6A] >= 3) {
        obj[0x6A] = 0;
    }
    if (obj[0x6B] >= 3) {
        obj[0x6B] = 0;
    }
    if (obj[0x6E] >= D_800BE9E4) {
        obj[0x6E] -= D_800BE9E4;
        return;
    }
    obj[0x6E] = 0;
    if (obj[0x6C] == 1) {
        return;
    }
    obj[0x6A] ^= 1;
    obj[0x6B] ^= 1;
    if (obj[0x6A] == 0) {
        obj[0x6E] = (u32)func_150ADA20() % 140 + 10;
    } else {
        obj[0x6E] = 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507E690.s")
#endif

#ifdef NON_MATCHING
/* func_1507E7A0 (P57): for model types 0xF / 0x46 / 0x4C, the DL hide mask +0x94 from the selector bytes +0x6C / +0x6D:
 * bits 1..6 set, then one of 8 / 0x10 / 4 (first selector 0 / 1 / other) and 0x20 / 0x40 / 2 (second) cleared.
 * Selector: >= 10: (v - 10) == 5 -> 0, == 1 -> 1, else 2; below 2: v + 1; else v. */
void func_1507E7A0(struct127 *arg0) {
    u8 *o = (u8 *)arg0;
    s32 s[2];
    s32 i;
    s32 v;
    s32 type = o[4];

    if (type != 0xF && type != 0x46 && type != 0x4C) return;
    for (i = 0; i < 2; i++) {
        v = o[0x6C + i];
        s[i] = v;
        if (v >= 10) {
            v -= 10;
            if (v == 5) s[i] = 0;
            else if (v == 1) s[i] = 1;
            else s[i] = 2;
        } else if (v < 2) {
            s[i] = v + 1;
        }
    }
    *(u32 *)(o + 0x94) |= 0x7E;
    if (s[0] == 0) *(u32 *)(o + 0x94) &= ~8;
    else if (s[0] == 1) *(u32 *)(o + 0x94) &= ~0x10;
    else *(u32 *)(o + 0x94) &= ~4;
    if (s[1] == 0) *(u32 *)(o + 0x94) &= ~0x20;
    else if (s[1] == 1) *(u32 *)(o + 0x94) &= ~0x40;
    else *(u32 *)(o + 0x94) &= ~2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507E7A0.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507E8E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507E9A8.s")

s32 func_15084E08();

s32 func_1507EA98(u8 *arg0)
{
  s32 temp_v0;
  u8 new_var;
  if ((*((u8 *) (((u8 *) arg0) + 0x1CA))) == 0)
  {
    goto dummy_label_268708;
    dummy_label_268708:
    ;

    ;
    goto block_9;
  }
  if ((*((u8 *) (((u8 *) arg0) + 0x70))) == (*((u8 *) (((u8 *) arg0) + 0x6F))))
  {
    return 1;
  }
  temp_v0 = func_15084E08();
  new_var = *((u8 *) (((u8 *) arg0) + 0x6F));
  if (temp_v0 == 0)
  {
    if (new_var == 0x15)
    {
      return 1;
    }
    goto block_9;
  }
  if (temp_v0 == 0x52)
  {
    return 1;
  }
  block_9:
  return 0;

}

#ifdef NON_MATCHING
// P45: per-record animation / interaction timer step (after the state handler). +0x72 counts down by D_800BE9E4
// (0xFFFE = frozen: return; 0xFFFF = forever); when func_1507EA98 says so, func_1507E690; once +0x72 is 0 and
// +0x70 != +0x6F, func_1507EE9C. Records of type +5 == 2 are skipped.
void func_1507EB1C(u8 *arg0) {
    s32 t;
    u16 v;

    if (arg0[5] == 2) {
        return;
    }
    v = *(u16 *)(arg0 + 0x72);
    if (v != 0) {
        if (v == 0xFFFE) {
            return;
        }
        if (v != 0xFFFF) {
            t = D_800BE9E4;
            if (t < (s32)v) {
                *(u16 *)(arg0 + 0x72) = v - t;
            } else {
                *(u16 *)(arg0 + 0x72) = 0;
            }
        }
    }
    if (func_1507EA98(arg0) != 0) {
        func_1507E690(arg0);
    }
    if (*(u16 *)(arg0 + 0x72) == 0 && arg0[0x70] != arg0[0x6F]) {
        func_1507EE9C(arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507EB1C.s")
#endif
#ifdef NON_MATCHING
void func_150305E0(s32 arg0, s32 arg1);
void func_1507E9A8(struct127 *, s32);

/* P67: start animation `anim` (obj +0x6F) with priority `prio` (+0x71) for `time` frames (+0x72, 0xFFFF = until
 * replaced). Priority 3 always wins; otherwise a running timed animation of equal or higher priority is kept unless
 * it is the default one (+0x70) or `anim` itself. Animations past the object's table (func_1507ED48) are ignored.
 * The first frame's sound of the new animation is played (func_150305E0). `void` under NM: callers ignore the
 * result and the asm leaves v0 undefined on the early returns. */
void func_1507E7E4(struct127 *obj, u8 anim, u8 prio, u16 time, s32 arg4) {
    u8 *entry;
    u8 *sounds;

    if (obj->unk6F == anim && obj->unk71 == prio && obj->unk72 == time) {
        return;
    }
    if (prio != 3 && obj->unk70 != obj->unk6F && anim != obj->unk6F && obj->unk72 != 0 && obj->unk71 >= prio) {
        return;
    }
    if (!((s32)anim < (s32)func_1507ED48((s32)obj))) {
        return;
    }
    entry = (u8 *)func_1507ECE8((s32)obj, obj->unk6F);
    if (entry[4] != 0) {
        sounds = (u8 *)func_1507EDD8((s32)obj, NULL);
        if (sounds != NULL) {
            func_150305E0((s32)obj, sounds[entry[4] - 1]);
        }
    }
    obj->unk6F = anim;
    obj->unk72 = time;
    obj->unk71 = prio;
    func_1507E9A8(obj, arg4);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ABEA0/func_1507E7E4.s")
#endif
s32 func_1507ECE8(s32 arg0, s32 arg1) {
    s32 *p;
    s32 v;
    p = (s32 *)D_800D1C90[func_15084E08(arg0)];
    if (p != NULL) {
        p -= 2;
        v = *p;
        if (v != 0) {
            return (arg1 * 10) + v;
        }
    }
    return 0;
}

u32 func_1507ED48(s32 arg0)
{
  s32 *p;
  u32 r;
  s32 idx;
  idx = *((u8 *) (arg0 + 4));
  if (idx != 0x96)
  {
    idx = func_15084E08(arg0);
    arg0 = idx;
  }
  else
  {
    arg0 = idx;
  }
  if (arg0 == 0xFF)
  {
    return 0;
  }
  p = (s32 *) D_800D1C90[arg0];
  r = 0;
  if (p != 0)
  {
    p -= 2; return (u32)p[1] / 10U;
  }
  return r;
}

void func_1507EDC8(s32 arg0, s32 arg1) {
}

s32 *func_1507EDD8(s32 arg0, s32 *arg1) {
    if (func_15084E08(arg0) == 0) {
        if (arg1 != NULL) {
            *arg1 = 5;
        }
        return &D_8009DCE0;
    }
    if (arg1 != NULL) {
        *arg1 = 0;
    }
    return NULL;
}

extern f32 D_8009BC70;
void func_1507EE24(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    if (arg1 != 0) {
        temp_v0 = func_1507EDD8(arg0, 0);
        if (temp_v0 != 0) {
            func_15083568((struct127 *) arg0, (s32) (*(u8 *)(arg1 + temp_v0 - 1)), (f32) arg2 * D_8009BC70, 0);
        }
    }
}

void func_1507E7E4(struct127 *, u8, u8, u16, s32);
void func_1507EE9C(arg0)
u8 *arg0;
{
    func_1507E7E4(arg0, arg0[0x70], 3, 0xFFFF, 0xA);
    arg0[0x71] = 0;
    *(s16 *)(arg0 + 0x72) = 0;
    if (arg0[0x6C] >= 0xA) {
        arg0[0x6C] = 0;
        arg0[0x6A] = 0;
    }
    if (arg0[0x6D] >= 0xA) {
        arg0[0x6D] = 0;
        arg0[0x6B] = 0;
    }
}

void func_1507EF0C(struct127 *arg0) {
    func_1507EB4C(arg0, 0);
}

void func_1507EB4C(struct127 *arg0, s32 arg1) {
    if (arg1 != arg0->unk70) {
        arg0->unk70 = arg1;
        func_1507EE9C(arg0, arg1);
    }
}
