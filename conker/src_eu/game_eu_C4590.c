#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15096970(void) {
    bzero(D_800D31E0, 0x6C);
    D_800D2DB4 = 0;
}

s32 func_15096DB0(s32 arg0)
{
  s32 i;
  for (i = 0; i < arg0; i++) {
    if (*((u8 *)D_800D31E0 + i * 0x24) != 0) {
      return 1;
    }
  }
  return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C4590/func_15096E78.s")

s32 func_15096E78(s32);

void func_15097118(void) {
    s32 var_s0;
    u8 *var_s1;

    var_s0 = 0;
    if (D_800C35EA != 1) {
        var_s1 = D_800D31E0;
loop_2:
        if (*var_s1 != 0) {
            if (func_15096E78(var_s0) == 0) {
                goto block_6;
            }
            return;
        }
block_6:
        var_s0 += 1;
        var_s1 += 0x24;
        if (var_s0 == 3) {

        } else {
            goto loop_2;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C4590/func_15097188.s")

#ifdef NON_MATCHING
f32 func_150ADDE0(f32 *, struct17 *);
extern s32 D_800DC450;

s32 func_150979AC(s32 arg0, s32 arg1, u8 *arg2) {
    struct {
        struct127 * u28;
        f32 u2C;
        struct17 u30;
        f32 u3C;
        f32 u40;
        f32 u44;
        u8 pad48[0x4];
        struct108 * u4C;
    } sp;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f2;
    struct108 *temp_a3;
    struct127 *temp_v0;
    u8 *temp_v1;

    temp_a3 = &D_800DBFF0[arg0];
    if (D_80082FA0 < arg0) {
        goto block_13;
    }
    switch (arg1) {
    case 31:
        return (s32) (temp_a3->unk390 * 65536.0f);
    case 30:
        return (s32) (temp_a3->unk37C * 65536.0f);
    case 29:
        return (s32) *(D_800D31E0 + ((*(s32 *)((u8 *)arg2 + 8)) * 0x24));
    case 32:
        temp_v1 = (((*(s32 *)((u8 *)arg2 + 8)) & 0xFFF) * 0x18) + D_800DC450;
        temp_f2 = temp_a3->unk2F8 - (f32) (*(s16 *)((u8 *)temp_v1 + 0));
        temp_f12 = temp_a3->unk300 - (f32) (*(s16 *)((u8 *)temp_v1 + 4));
        return (s32) sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
    case 33:
        sp.u4C = temp_a3;
        temp_v0 = func_1505EEF4((*(s32 *)((u8 *)arg2 + 8)) & 0xFFF, temp_a3);
        sp.u28 = temp_v0;
        if (temp_v0 == NULL) {
            return -1;
        }
        sp.u4C = temp_a3;
        temp_f12_2 = temp_a3->unk39C + 1.5707964f;
        sp.u2C = temp_f12_2;
        sp.u3C = sinf(temp_f12_2);
        sp.u40 = 0.0f;
        sp.u44 = cosf(temp_f12_2);
        func_15048F90((struct17 *) &temp_a3->unk2F8, (struct17 *) &sp.u28->x_position, &sp.u30);
        sp.u30.unk4 = 0.0f;
        if (func_150ADDE0(&sp.u3C, &sp.u30) >= 0.0f) {
            return -1;
        }
        return 1;
    default:
block_13:
        return 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C4590/func_150979AC.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800D3250[];
/* Pushes player `id` back along the direction between its two position vectors (+0x2A4 and +0x2F8): d =
 * normalised direction (func_15048F90 / func_1504917C); both vectors move by d * (-2.5, -2.0, -2.5) times the
 * per-player factor D_800D3250[id]. Only while D_800D2DB4 is set. Returns the record (v0 holds it on both paths;
 * the caller in game_14FF90 declares s32 and ignores it). */
s32 func_15097BA8(s32 id) {
    struct108 *r = &D_800DBFF0[id];
    struct17 *a;
    struct17 *b;
    struct17 d;

    if (D_800D2DB4 != 0) {
        a = (struct17 *) &r->unk2A4;
        b = (struct17 *) &r->unk2F8;
        func_15048F90(a, b, &d);
        func_1504917C(&d, &d);
        a->unk0 += d.unk0 * -2.5f * (f32) D_800D3250[id];
        a->unk4 += d.unk4 * -2.0f * (f32) D_800D3250[id];
        a->unk8 += d.unk8 * -2.5f * (f32) D_800D3250[id];
        b->unk0 += d.unk0 * -2.5f * (f32) D_800D3250[id];
        b->unk4 += d.unk4 * -2.0f * (f32) D_800D3250[id];
        b->unk8 += d.unk8 * -2.5f * (f32) D_800D3250[id];
    }
    return (s32) r;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C4590/func_15097BA8.s")
#endif
