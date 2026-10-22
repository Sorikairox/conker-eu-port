#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_15034B50.s")

extern s16 D_800C4310;

void func_150351A4(u8 *arg0, s32 arg1, s32 arg2)
{
  f32 temp_f0;
  s32 temp_v1;
  u8 *temp_a2;
  s32 new_var;
  if (D_800C4310 != 0)
  {
    u8 *temp_v0;
    temp_v1 = (new_var = /* fakematch: permuter chain */ *((s32 *) (((u8 *) arg0) + 0x1D4)));
    temp_a2 = (arg1 << 6) + temp_v1;
    temp_v0 = (arg2 << 6) + new_var;
    temp_v1 = D_800C4310;
    temp_f0 = ((f32) temp_v1) * 0.00076296274f;
    temp_f0 *= *((f32 *) (((u8 *) arg0) + 0x14C));
    *((f32 *) (((u8 *) temp_a2) + 0x34)) = (f32) ((*((f32 *) (((u8 *) temp_a2) + 0x34))) - temp_f0);
    if (((0, arg2)) != (-1)) // fakematch: permuter comma
    {
      *((f32 *) (((u8 *) ((arg2 << 6) + new_var)) + 0x34)) = (f32) ((*((f32 *) (((u8 *) temp_v0) + 0x34))) - temp_f0);
    }
  }
}

void func_15035210(void) {
    D_800C4320 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_15035220.s")

struct_eu_size0C *func_150359B8(void) {
    if (D_800C4320 == 15) {
        return NULL;
    }
    D_800C4320++;
    return &D_800C4328[D_800C4320 - 1];
}

#ifdef NON_MATCHING
s32 func_150A6840(s32, s32 *, s32, f32, f32, f32, f32, f32);
extern s32 D_800DA030;
extern f32 D_80098120;

s32 func_15035A04(s32 arg0, u8 *arg1, u8 *arg2, f32 arg3) {
    s32 sp28 = D_800BE628;
    struct124 *e = D_800D1C90[arg1[4]];
    f32 w = (f32)(u16)e->unkE;
    f32 h = (f32)*(s16 *)((u8 *)e + 0x10) * *(f32 *)(arg1 + 0x150);
    f32 y;

    if (arg0 == 1 || arg0 == 0) {
        y = arg3 - ((*(f32 *)(arg1 + 0x18) + h) - arg3);
    } else {
        y = *(f32 *)(arg1 + 0x18) + h;
    }
    return func_150A6840(sp28, &D_800DA030, *(s32 *)(arg2 + 0x30), y, *(f32 *)(arg2 + 0x38),
                         w * *(f32 *)(arg1 + 0x14C), w * *(f32 *)(arg1 + 0x150), D_80098120) == 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_15035A04.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_15035AF8.s")

#ifdef NON_MATCHING
extern s32 D_80083350;
extern s32 D_800834D0;

u8 *func_1503605C(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 *temp_s4;
    s32 *var_a0_2;
    s32 temp_t6;
    s32 var_v0;
    struct_eu_size0C *var_a2;
    struct_eu_size0C *var_s3;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *var_a0;

    var_a0 = arg0;
    if (D_800C4320 == 0) {

    } else {
        (*(s32 *)((u8 *)var_a0 + 4)) = 0x200;
        var_a0_2 = var_a0 + 8;
        (*(s32 *)((u8 *)var_a0 + 0)) = 0xD9FFFFFF;
        var_a2 = D_800C4328;
        if ((s32) D_800C4320 > 0) {
            do {
                if (var_a2->unk0[0xB] != 1) {
                    var_s3 = &D_800C4328[D_800C4320];
                } else if ((*(u8 *)((u8 *)arg1 + 0)) != var_a2->unk0[9]) {
                    var_s3 = &D_800C4328[D_800C4320];
                } else if ((*(u8 *)((u8 *)arg1 + 6)) != var_a2->unk0[0xA]) {
                    var_s3 = &D_800C4328[D_800C4320];
                } else {
                    temp_a0 = ((s32 *)((u8 *)var_a0_2 + 8));
                    temp_t6 = (s32) (var_a2->unk0[4] * (*(u8 *)((u8 *)arg1 + 3))) >> 8;
                    (*(s32 *)((u8 *)var_a0_2 + 0)) = 0xE7000000;
                    (*(s32 *)((u8 *)var_a0_2 + 4)) = 0;
                    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xDB06000C;
                    temp_a0_2 = temp_a0 + 8;
                    (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) (*(s32 *)((u8 *)var_a2 + 0));
                    (*(s32 *)((u8 *)temp_a0_2 + 4)) = (s32) ((arg2 << 0x18) | ((arg3 & 0xFF) << 0x10) | ((arg4 & 0xFF) << 8) | (temp_t6 & 0xFF));
                    temp_a0_3 = temp_a0_2 + 8;
                    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xFB000000;
                    var_v0 = 0;
                    if (temp_t6 < 0xFF) {
                        (*(s32 *)((u8 *)temp_a0_3 + 0)) = 0xDB060020;
                        (*(s32 **)((u8 *)temp_a0_3 + 4)) = &D_80083350;
                        var_a0_2 = temp_a0_3 + 8;
                    } else {
                        (*(s32 *)((u8 *)temp_a0_3 + 0)) = 0xDB060020;
                        (*(s32 **)((u8 *)temp_a0_3 + 4)) = &D_800834D0;
                        var_a0_2 = temp_a0_3 + 8;
                    }
                    if ((s32) (*(u8 *)((u8 *)arg1 + 0x14)) > 0) {
                        do {
                            temp_s4 = var_a0_2;
                            if (!((*(u8 *)((u8 *)arg1 + 0x13)) & (1 << var_v0))) {
                                (*(s32 *)((u8 *)temp_s4 + 0)) = 0xDE000000;
                                var_a0_2 = (s32 *)((u8 *)var_a0_2 + (8));
                                (*(s32 *)((u8 *)temp_s4 + 4)) = (s32) *(s32 *)((*(s32 *)((u8 *)arg1 + 0x24)) + (var_v0 * 4));
                            }
                            var_v0 += 1;
                        } while (var_v0 < (s32) (*(u8 *)((u8 *)arg1 + 0x14)));
                    }
                    var_s3 = &D_800C4328[D_800C4320];
                }
                var_a2 = (struct_eu_size0C *)((u8 *)var_a2 + (0xC));
            } while ((u32) var_a2 < (u32) var_s3);
        }
        (*(s32 *)((u8 *)var_a0_2 + 0)) = 0xD9FFFDFF;
        (*(s32 *)((u8 *)var_a0_2 + 4)) = 0;
        var_a0 = ((s32 *)((u8 *)var_a0_2 + 8));
    }
    return var_a0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_1503605C.s")
#endif
#ifdef NON_MATCHING
Gfx *func_1502CFEC(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 *color, s32 arg6, s32 arg7);

/* Draw the D_800C4320 entries of D_800C4328 that have no unkB flag through func_1502CFEC, after a
 * geometry-mode / othermode setup. */
Gfx *func_150362D8(Gfx *gdl, s32 arg1) {
    struct_eu_size0C *e;
    s32 color[4];

    if (D_800C4320 == 0) {
        return gdl;
    }
    gdl->words.w0 = 0xD9FFFFFF;
    gdl->words.w1 = 0x200004;
    gdl++;
    gdl->words.w0 = 0xD9EEFFFF;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xE2001E01;
    gdl->words.w1 = 0;
    gdl++;
    for (e = D_800C4328; e < &D_800C4328[D_800C4320]; e++) {
        if (e->unk0[0xB] != 0) {
            continue;
        }
        color[0] = e->unk0[5];
        color[1] = e->unk0[6];
        color[2] = e->unk0[7];
        color[3] = 0xFF;
        gdl = func_1502CFEC(gdl, e->unk0[8], arg1, *(s32 *)e->unk0, e->unk0[4], color, 0, 1);
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_150362D8.s")
#endif
#ifdef NON_MATCHING
s32 func_15035AF8(s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 func_1507C7C0(struct127 *, s16 *, s32 *, s32 *);

void func_15036438(void) {
    struct {
        s32 u8E;
        s16 u92;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    s32 var_s1;
    struct127 *var_s0;
    u8 temp_v0;

    var_s0 = D_800CC2D0;
    var_s1 = 0;
    if (!(D_800DBFF0->unk5F0 & 1)) {
        do {
            if ((var_s0->interaction_state != 0) && ((temp_v0 = var_s0->unk5, (temp_v0 == 0)) || (temp_v0 == 1))) {
                temp_f0 = var_s0->unk118;
                if ((temp_f0 != -10000.0f) && (temp_f0 < var_s0->y_position) && (var_s0->unk180 < temp_f0) && (var_s0->unk28 > 5.0f)) {
                    func_1507C7C0(var_s0, &sp.u92, &(*(s32 *)((u8 *)&sp + 0x2)), &sp.u8E);
                    temp_f0_2 = var_s0->unk118;
                    if ((f32) sp.u92 < (temp_f0_2 - var_s0->unk180)) {
                        func_15035AF8(1, var_s1, var_s0->x_position, temp_f0_2, var_s0->z_position, 0.0f, 0.0f, 100.0f, 150.0f, 127.0f);
                    }
                }
            }
            var_s1 += 1;
            var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
        } while (var_s1 != 0x19);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_15036438.s")
#endif