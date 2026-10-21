#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_1503F8A8(u8 *, s32, s32, s32, f32, s32);

s32 func_15030448(struct127 *, s32);

s32 func_15030600(u8 *, s32, s32);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150302C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030448.s")

void func_150305E0(s32 arg0, s32 arg1) {
    func_15030600(arg0, arg1, 0xFF);
}

#ifdef NON_MATCHING
s32 func_15030600(u8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_s1;
    s32 var_a0;
    s32 var_s0;
    s32 var_s5;

    var_s0 = arg2;
    if ((*(u8 *)((u8 *)arg0 + 0x3B)) == 0) {
        return 0;
    }
    var_a0 = D_800C3EE0;
    var_s5 = 0;
    if (var_a0 != 0) {
loop_3:
        temp_s1 = (*(s32 *)((u8 *)var_a0 + 0x54));
        if (((*(u8 *)((u8 *)arg0 + 0x3B)) == (*(u8 *)((u8 *)var_a0 + 0))) && (arg1 == (*(u8 *)((u8 *)var_a0 + 6)))) {
            if ((var_s0 != 0xFF) && (var_s0 != 0)) {
                var_s0 -= 1;
                var_a0 = temp_s1;
                goto block_10;
            }
            var_s5 = 1;
            func_15030448((struct127 *) var_a0, 0);
            if (var_s0 != 0) {
                goto block_9;
            }
        } else {
block_9:
            var_a0 = temp_s1;
block_10:
            if (var_a0 != 0) {
                goto loop_3;
            }
        }
    }
    return var_s5;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030600.s")
#endif
s32 func_150306D4(u8 *arg0) {
    s32 temp_s0;
    s32 var_a0;
    s32 var_s1;

    if ((*(u8 *)((u8 *)arg0 + 0x3B)) == 0) {
        return 0;
    }
    var_a0 = D_800C3EE0;
    var_s1 = 0;
    if (var_a0 != 0) {
        do {
            temp_s0 = (*(s32 *)((u8 *)var_a0 + 0x54));
            if ((*(u8 *)((u8 *)arg0 + 0x3B)) == (*(u8 *)var_a0)) {
                var_s1 = 1;
                func_15030448((u8 *) var_a0, 0);
            }
            var_a0 = temp_s0;
        } while (temp_s0 != 0);
    }
    return var_s1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030758.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030DE4.s")

#ifdef NON_MATCHING
f32 *allocate_memory(s32, s32, s32, s32);

void func_15031044(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 *temp_v0;

    temp_v0 = allocate_memory(0x18, 1, 0, 2);
    (*(f32 **)((u8 *)arg0 + 0x44)) = temp_v0;
    if (temp_v0 != NULL) {
        *temp_v0 = arg1;
        (*(f32 *)((u8 *)((*(f32 **)((u8 *)arg0 + 0x44))) + 4)) = arg2;
        (*(f32 *)((u8 *)((*(f32 **)((u8 *)arg0 + 0x44))) + 8)) = arg3;
        (*(f32 *)((u8 *)((*(f32 **)((u8 *)arg0 + 0x44))) + 0xC)) = arg4;
        (*(f32 *)((u8 *)((*(f32 **)((u8 *)arg0 + 0x44))) + 0x10)) = arg5;
        (*(f32 *)((u8 *)((*(f32 **)((u8 *)arg0 + 0x44))) + 0x14)) = arg6;
        if ((*(f32 **)((u8 *)arg0 + 0x34)) == NULL) {
            (*(f32 **)((u8 *)arg0 + 0x34)) = allocate_memory(0x80, 1, 2, 2);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031044.s")
#endif
#ifdef NON_MATCHING
s32 func_150314B4(s32, u8 *, struct127 *, s32, s32);

s32 func_150310F8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s2;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s6;
    struct127 *temp_v0;

    var_s6 = arg0;
    var_s0 = D_800C3EE0;
    if (var_s0 != 0) {
        do {
            temp_s2 = (*(s32 *)((u8 *)var_s0 + 0x54));
            if ((*(u8 *)((u8 *)var_s0 + 3)) == 0) {

            } else {
                temp_v0 = func_15083E90((*(u8 *)((u8 *)var_s0 + 0)));
                if ((temp_v0 == NULL) || (temp_v0->unk1D4 == NULL) || (temp_v1 = 1 << arg1, (temp_v1 == (temp_v0->unk74 & temp_v1)))) {

                } else if (arg2 == 2) {
                    if (temp_v0->unk5 != 7) {

                    } else {
                        goto block_19;
                    }
                } else {
                    temp_v0_2 = func_1506196C(temp_v0, arg1);
                    if (arg2 == 1) {
                        if (!((*(u8 *)((u8 *)var_s0 + 4)) & 2) && (temp_v0_2 == 0xFF) && (temp_v0->unk5 != 1)) {

                        } else {
                            goto block_19;
                        }
                    } else if (((*(u8 *)((u8 *)var_s0 + 4)) & 2) || (temp_v0_2 < 0xFF) || (temp_v0->unk5 == 1)) {

                    } else {
block_19:
                        var_s6 = func_150314B4(var_s6, (u8 *) var_s0, temp_v0, arg1, 0);
                    }
                }
            }
            var_s0 = temp_s2;
        } while (var_s0 != 0);
    }
    return var_s6;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150310F8.s")
#endif
#ifdef NON_MATCHING
#ifndef NON_MATCHING
s32 func_150314B4(s32, u8 *, u8 *, s32, s32);
#endif

s32 func_15031284(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
    s32 temp_s1;
    s32 var_s0;
    s32 var_s3;

    var_s3 = arg0;
    if ((arg1 == NULL) || ((*(s32 *)((u8 *)arg1 + 0x1D4)) == 0) || ((*(u8 *)((u8 *)arg1 + 0x3B)) == 0)) {

    } else {
        var_s0 = D_800C3EE0;
        if (var_s0 != 0) {
            do {
                temp_s1 = (*(s32 *)((u8 *)var_s0 + 0x54));
                if (((*(u8 *)((u8 *)arg1 + 0x3B)) != (*(u8 *)((u8 *)var_s0 + 0))) || ((*(u8 *)((u8 *)var_s0 + 3)) == 0)) {

                } else {
                    var_s3 = func_150314B4(var_s3, (u8 *) var_s0, arg1, arg2, arg3);
                }
                var_s0 = temp_s1;
            } while (var_s0 != 0);
        }
    }
    return var_s3;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031284.s")
#endif
#ifdef NON_MATCHING
u8 *func_15031C4C(u8 *, u16, s32);

s32 func_15031360(u8 *arg0, u8 *arg1, s32 *arg2, s32 *arg3) {
    s32 temp_t9;
    s32 temp_v0_2;
    s32 var_t3;
    u16 temp_v0_3;
    u8 *temp_v0;
    u8 *temp_v0_4;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x48));
    if (temp_v0 != NULL) {
        if ((*(u8 *)((u8 *)temp_v0 + 0x3F6)) == 0) {
            return 0;
        }
        *arg2 = (*(s32 *)((u8 *)((temp_v0 + (D_800BE9C0 * 4))) + 0x3E8));
        *arg3 = (*(s32 *)((u8 *)(((*(u8 **)((u8 *)arg0 + 0x48)) + (D_800BE9C0 * 4))) + 0x3E0));
        goto block_14;
    }
    temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x34));
    if (temp_v0_2 != 0) {
        *arg2 = temp_v0_2 + (D_800BE9C0 << 6);
        var_t3 = (*(s32 *)((u8 *)arg1 + 0x1D4)) + ((*(u8 *)((u8 *)arg0 + 2)) << 6);
        goto block_13;
    }
    temp_v0_3 = (*(u16 *)((u8 *)arg0 + 0x1E));
    if (temp_v0_3 != 0) {
        temp_v0_4 = func_15031C4C(arg1, temp_v0_3, 0);
        if (temp_v0_4 == NULL) {
            return 0;
        }
        if (func_15031360(temp_v0_4, arg1, arg2, arg3) == 0) {
            return 0;
        }
        *arg2 += (*(u16 *)((u8 *)arg0 + 0x20)) << 6;
        goto block_14;
    }
    temp_t9 = (*(s32 *)((u8 *)arg1 + 0x1D4));
    *arg2 = temp_t9;
    var_t3 = temp_t9 + ((*(u8 *)((u8 *)arg0 + 2)) << 6);
    *arg2 = var_t3;
block_13:
    *arg3 = var_t3;
block_14:
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031360.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150314B4.s")

void func_15031C1C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_v0 = func_15031C4C(arg0, arg1, arg3);
    if (temp_v0 != NULL) {
        temp_v0[3] = arg2;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031C4C.s")

u8 *func_15031CBC(s32 arg0, u8 *arg1) {
    u8 *n;
    u8 *next;

    if (arg1 != NULL) {
        n = (u8 *)D_800C3EE0;
        if (n != NULL) {
            do {
                next = *(u8 **)(n + 0x54);
                if (arg1[0x3B] == n[0] && arg0 == n[6]) {
                    return n;
                }
                n = next;
            } while (n != NULL);
        }
    }
    n = (u8 *)D_800C3EE0;
    if (n != NULL) {
        do {
            next = *(u8 **)(n + 0x54);
            if (arg0 == n[6]) {
                return n;
            }
            n = next;
        } while (n != NULL);
    }
    return NULL;
}

#ifdef NON_MATCHING
s32 func_150D3870(u8 *, s32, s32);
void func_150D5950(u8 *, u8, s32);
void func_15100734(u8 *);
s32 func_15163BE8(u8 *, s32, s32);
s32 func_151BDDD8(u8 *, s32, s32);
void func_151D7A60(u8 *, u8, s8, u8, s32);
extern s32 D_800905D8;
extern s32 D_800905DC;

void func_15031D40(u8 *arg0, u8 *arg1) {
    u8 temp_v0;
    u8 *temp_v0_2;

    temp_v0 = (*(u8 *)((u8 *)arg0 + 1));
    switch ((s32) temp_v0) {                        /* switch 2; irregular */
    default:                                        /* switch 2 */
        if ((u32) (temp_v0 - 0x82) < 0xFU) {
            switch (temp_v0) {                      /* switch 1 */
            case 0x37:                              /* switch 2 */
            case 0x91:                              /* switch 1 */
                func_15100734(arg1);
                return;
            case 0x5A:                              /* switch 2 */
            case 0xB4:                              /* switch 1 */
                temp_v0_2 = (*(u8 **)((u8 *)arg1 + 0x31C));
                if (temp_v0_2 != NULL) {
                    (*(u16 *)((u8 *)temp_v0_2 + 0x1A6)) = (u16) ((*(u16 *)((u8 *)temp_v0_2 + 0x1A6)) + 0xAA);
                    return;
                }
                break;
            case 0x90:                              /* switch 1 */
                (*(s32 *)((u8 *)arg1 + 0x9C)) = (s32) ((*(s32 *)((u8 *)arg1 + 0x9C)) | 0x70);
                return;
            case 0x8F:                              /* switch 1 */
                (*(s32 *)((u8 *)arg1 + 0x9C)) = (s32) ((*(s32 *)((u8 *)arg1 + 0x9C)) | 0xE00);
                return;
            case 0x49:                              /* switch 2 */
            case 0xA3:                              /* switch 1 */
                func_15163BE8(arg1, 0xFF, 1);
                return;
            case 0x5D:                              /* switch 2 */
            case 0xB7:                              /* switch 1 */
                func_150D3870(arg1, 0xFF, 1);
                func_150D5950(arg1, 0xFF, 1);
                return;
            case 0x3D:                              /* switch 2 */
            case 0x97:                              /* switch 1 */
                func_151BDDD8(arg1, 0xFF, 1);
                return;
            case 0x5E:                              /* switch 2 */
            case 0x85:                              /* switch 1 */
            case 0xB8:                              /* switch 1 */
                (*(s32 *)((u8 *)arg1 + 0x9C)) = (s32) ((*(s32 *)((u8 *)arg1 + 0x9C)) | 0x6000);
                return;
            case 0x8D:                              /* switch 1 */
                if (func_150859AC(0, 6) < 0x64) {
                    (*(s16 *)((u8 *)arg0 + 0x18)) = (s16) D_800905D8;
                    return;
                }
                (*(s16 *)((u8 *)arg0 + 0x18)) = (s16) D_800905DC;
                return;
            case 0x82:                              /* switch 1 */
                func_151D7A60(arg1, 6, -1, 0xFF, 1);
                break;
            }
        } else {
            return;
        }
        break;
    case 0x1D:                                      /* switch 2 */
        func_151D7A60(arg1, 0, 2, 0xFF, 1);
        return;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031D40.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031F04.s")

s32 func_1503211C(u8 *arg0, s32 arg1) {
    s32 var_v0 = *(s32 *)(arg0 + 0x38);

    if (*(s32 *)(arg0 + 0x38) >= 3) {
        var_v0 = 5 - var_v0;
    }
    *(s16 *)(arg0 + 0x18) = D_8009066C[var_v0];
    (*(s32 *)(arg0 + 0x38))++;
    if (*(s32 *)(arg0 + 0x38) >= 6) {
        *(s32 *)(arg0 + 0x38) = 0;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_1503216C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150322B8.s")

s32 func_150334A8(u8 *arg0, u8 *arg1) {
    u8 *v;
    u8 *s;
    f32 f;
    s32 t;
    v = *(u8 **)(arg1 + 0x2D0);
    s = *(u8 **)(arg0 + 0x48);
    if (s == NULL) {
        return 0;
    }
    t = *(s32 *)(arg1 + 0x2E4) & 0xFF;
    if (t != 0xFF) {
        func_1503F8A8(s, 0, t, 0x3F800000, 0.0f, 1);
    }
    if (v != NULL) {
        *(f32 *)(*(u8 **)(arg0 + 0x48) + 8) = *(f32 *)(v + 8);
        s = *(u8 **)(arg0 + 0x48);
        f = *(f32 *)(s + 0x18);
        if (f <= *(f32 *)(s + 8)) {
            *(f32 *)(s + 8) = f - 1.0f;
        }
    }
    return 0;
}


s32 func_1503356C(u8 *arg0, s32 arg1) {
    u8 *var_s0;

    var_s0 = *(u8 **)(arg0 + 0x48);
    if (var_s0 == NULL) {
        return 0;
    }
    if ((*(u16 *)(var_s0 + 4) & 0x8000) != 0x8000) {
        func_1503F8A8(var_s0, 0, 0, 0x3F800000, 0.0f, 1);
        var_s0 = *(u8 **)(arg0 + 0x48);
    }
    if ((*(f32 *)(var_s0 + 0x18) - 1.0f) <= *(f32 *)(var_s0 + 8)) {
        return 1;
    }
    return 0;
}

s32 func_15033618(u8 *arg0, u8 *arg1)
{
  s32 temp_a1;
  if (D_800C35EA == 1)
  {
    return 0;
  }
  if (((*((u8 *) (((u8 *) arg1) + 0xAD))) == 0) && ((*((f32 *) (((u8 *) arg1) + 0x118))) < (*((f32 *) (((u8 *) arg1) + 0x180)))))
  {
    ;
    if (D_800BE9E4 < (*((s32 *) (((u8 *) arg0) + 0x38))))
    {
      *((s32 *) (((u8 *) arg0) + 0x38)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x38))) - D_800BE9E4);
      return 0;
    }
    return 1;
  }
  *((s32 *) (((u8 *) arg0) + 0x38)) = 0x19;
  return 0;
}

s32 func_15033698(u8 *arg0, u8 *arg1) {
    f32 temp_f0;
    f32 new_var;
    u8 *temp_v0;
    new_var = -10000.0f; // fakematch: constant in a variable swaps the c.eq.s operands
    if (D_800C35EA == 1) {
        return 0;
    }
    if (arg1[0xAD] != 0) {
        temp_v0 = *(u8 **)(arg1 + 0x31C);
        if (temp_v0 != NULL) {
            temp_v0[0x11A] = 0;
        }
        return 1;
    }
    temp_f0 = *(f32 *)(arg1 + 0x118);
    if (temp_f0 != (0, new_var) && *(f32 *)(arg1 + 0x18) < temp_f0 + 300.0f) {
        arg0[3] = 0;
    } else {
        arg0[3] = 0xFF;
    }
    return 0;
}

s32 func_15033730(u8 *arg0, u8 *arg1)
{
  switch (arg0[1]) {
  case 0x27:
  case 0x35:
    if (arg1[5] == 5) {
      arg0[2] = 0;
      *(s16 *)(arg0 + 0x22) += D_800BE9E4 * 0xAAA;
    }
    break;
  case 0x29:
    if (arg1[5] == 5) {
      arg0[2] = 0;
    }
    break;
  }
  return 0;
}

#ifdef NON_MATCHING
s32 func_150337A8(u8 *arg0, u8 *arg1) {
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a1;
    s32 var_t1;
    s32 var_t3;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a2;

    var_v0 = 0;
    var_v1 = 0;
    var_a1 = 0;
    if ((*(u8 *)((u8 *)arg0 + 1)) == 0x37) {
        var_v1 = 4;
        var_a1 = -0x64;
        var_v0 = *(*(s32 **)((u8 *)arg0 + 0x24));
    }
    if (var_v0 != 0) {
        var_a0 = 0;
        if (var_v1 != 0) {
            do {
                var_v1 -= 1;
                if (*(s32 *)((var_a0 * 8) + var_v0) != -0xE) {
                    do {
                        var_a0 += 1;
                    } while (*(s32 *)((var_a0 * 8) + var_v0) != -0xE);
                }
                if (var_v1 != 0) {
                    var_a0 += 1;
                }
            } while (var_v1 != 0);
        }
        temp_a2 = var_v0 + (var_a0 * 8);
        temp_v1 = (*(s32 *)((u8 *)temp_a2 + 0));
        temp_a3 = (*(s32 *)((u8 *)temp_a2 + 4));
        temp_t2 = ((temp_v1 >> 0xC) & 0xFFF) + var_a1;
        temp_t0 = ((temp_a3 >> 0xC) & 0xFFF) + 2;
        temp_t4 = temp_v1 & 0xFFF;
        var_t1 = temp_t2;
        var_t3 = temp_t4;
        if (temp_t2 >= temp_t0) {
            var_t1 = temp_t2 - temp_t0;
        }
        if (var_t1 < 0) {
            var_t1 += temp_t0;
        }
        temp_v0 = (temp_a3 & 0xFFF) + 2;
        if (temp_t4 >= temp_v0) {
            var_t3 = temp_t4 - temp_v0;
        }
        if (var_t3 < 0) {
            var_t3 += temp_v0;
        }
        (*(s32 *)((u8 *)temp_a2 + 0)) = (s32) (((var_t1 & 0xFFF) << 0xC) | 0xF2000000 | (var_t3 & 0xFFF));
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150337A8.s")
#endif
void func_15031044(s32, f32, f32, f32, f32, f32, f32);
void func_1503E5F8(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void func_150A7A48(f32 a[4][4], f32 b[4][4], f32 c[4][4]);
s32 func_150335C8(u8 *arg0, struct127 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 ret;
    f32 m1[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    f32 m4[4][4];
    f32 x;
    f32 y;
    f32 z;
    f32 u0;
    f32 u1;
    f32 u2;
    f32 r0;
    f32 r1;
    f32 r2;

    if (arg1->unk1D4 == NULL) {
        return 0;
    }
    ret = func_15083568(arg1, arg2, 1.0f, 0);
    if (ret != 0) {
        *(s8 *)(ret + 2) = arg3;
        *(f32 *)(ret + 0x40) = *(f32 *)(arg0 + 0x14C);
        if (arg4 != 0) {
            *(u8 *)(ret + 0x16) &= ~4;
        } else {
            *(u8 *)(ret + 0x16) |= 4;
        }
        guMtxL2F(m1, (Mtx *)((u8 *)arg1->unk1D4 + (arg3 << 6)));
        func_15048B10((s32)m1, (s32)m2);
        func_150A9B0C(m3, *(f32 *)(arg0 + 0xB8), *(f32 *)(arg0 + 0x40), *(f32 *)(arg0 + 0xC4), *(f32 *)(arg0 + 0x14C), *(f32 *)(arg0 + 0x150), *(f32 *)(arg0 + 0x14C));
        m3[3][0] = *(f32 *)(arg0 + 0x14);
        m3[3][1] = *(f32 *)(arg0 + 0x18);
        m3[3][2] = *(f32 *)(arg0 + 0x1C);
        m3[0][3] = 0.0f;
        m3[1][3] = 0.0f;
        m3[2][3] = 0.0f;
        m3[3][3] = 1.0f;
        func_150A7A48(m3, m2, m4);
        func_1503E5F8((f32 *)m4, &x, &y, &z, &r0, &r1, &r2, &u0, &u1, &u2);
        if (arg5 != 0) {
            z = 0.0f;
            y = 0.0f;
            x = 0.0f;
        }
        func_15031044(ret, x, y, z, r0, r1, r2);
        return ret;
    }
    return 0;
}

s32 func_15033A7C(u8 *arg0, u8 *arg1) {
    u16 temp_v0;

    temp_v0 = (*(u16 *)((u8 *)arg1 + 0x84));
    if (((*(u8 *)((u8 *)arg0 + 1)) == 0x11) && ((temp_v0 == 0x3E) || (temp_v0 == 0x3D) || (temp_v0 == 0x41) || (temp_v0 == 0xD9) || (temp_v0 == 0x138) || (temp_v0 == 0x139))) {
        return 0;
    }
    return 1;
}

s32 func_15033AD4(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x38) += D_800BE9E4;
    if (*(s32 *)(arg0 + 0x38) >= 16) {
        *(s32 *)(arg0 + 0x38) = 0;
        *(s32 *)(arg0 + 0x3C) ^= 1;
    }
    *(s16 *)(arg0 + 0x18) = D_800906AC[*(s32 *)(arg0 + 0x3C)];
    return 0;
}

#ifdef NON_MATCHING
void func_151027E8(u8 *);
s32 func_15102C3C(u8 *, s32, s32, s32, s32, s32);

s32 func_15033B28(u8 *arg0, u8 *arg1) {
    s32 var_a2;
    s32 var_v1;
    u16 temp_v0_2;
    u8 temp_v0;
    u8 *temp_v0_3;
    u8 *temp_v0_4;

    var_v1 = 0;
    temp_v0 = (*(u8 *)((u8 *)arg0 + 6));
    if (temp_v0 == 0x16) {
        var_a2 = 4;
        if ((*(u16 *)((u8 *)arg1 + 0x84)) == 0x165) {
            goto block_10;
        }
    } else if (temp_v0 == 0x89) {
        var_a2 = 6;
        temp_v0_2 = (*(u16 *)((u8 *)arg1 + 0x84));
        if (((temp_v0_2 == 0x221) || (temp_v0_2 == 0x223) || (temp_v0_2 == 0x31B)) && ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg1 + 0x31C))) + 0x198)) == 2)) {
            goto block_10;
        }
    } else {
        var_a2 = 5;
        if ((*(u16 *)((u8 *)arg1 + 0x84)) == 0x157) {
block_10:
            var_v1 = 1;
        }
    }
    if ((*(s32 *)((u8 *)arg0 + 0x38)) == 0) {
        if ((var_v1 != 0) && ((temp_v0_3 = (*(u8 **)((u8 *)arg1 + 0x31C)), ((*(u8 *)((u8 *)temp_v0_3 + 0x197)) != 0)) || (var_a2 == 6)) && (((*(u16 *)((u8 *)temp_v0_3 + 0x8A)) & 0x2000) == 0x2000) && ((*(u16 *)((u8 *)temp_v0_3 + 0x19E)) == 0)) {
            (*(s32 *)((u8 *)arg0 + 0x38)) = 1;
            func_15102C3C(arg1, -1, var_a2, 1, 0xFF, 1);
        }
    } else if ((var_v1 == 0) || (temp_v0_4 = (*(u8 **)((u8 *)arg1 + 0x31C)), (((*(u16 *)((u8 *)temp_v0_4 + 0x8A)) & 0x2000) == 0)) || (((*(u8 *)((u8 *)temp_v0_4 + 0x197)) == 0) && (var_a2 != 6))) {
        (*(s32 *)((u8 *)arg0 + 0x38)) = 0;
        func_151027E8(arg1);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15033B28.s")
#endif
extern s32 func_15033ECC;
s32 func_1000FD38(s32 *, u8 *, u8 *);
s32 func_150337A8(u8 *, u8 *);
extern u8 D_800BEE2C;
s32 func_15033CB8(u8 *arg0, u8 *arg1) {
    func_150337A8(arg0, arg1);
    if (D_800C35EA != 1) {
        if (D_800BEE2C != 0) {
            if (*(s32 *)(arg0 + 0x3C) != 0) {
                func_1000FD38(&func_15033ECC, arg0, arg1);
            }
            *(s32 *)(arg0 + 0x3C) = 0;
        } else if (*(s32 *)(arg0 + 0x3C) == 0) {
            *(s32 *)(arg0 + 0x3C) = func_1000FA64(0x448U, (s16) (s32) (*(f32 *)(arg1 + 0x14)), (s16) (s32) (*(f32 *)(arg1 + 0x18)), (s16) (s32) (*(f32 *)(arg1 + 0x1C)), 0x7D00, 0x3E8U, 0x1F4, (s32) &func_15033ECC, arg0, (s32) arg1, 0, 0) | 0x80000000;
        }
    }
    return 0;
}

extern s32 func_15033ECC;

s32 func_15033DC8(u8 *arg0, u8 *arg1) {
    s32 temp_v0;

    if (D_800BE616 != 0) {
        func_1508B20C((*(f32 *)((u8 *)arg1 + 0x14)), (*(f32 *)((u8 *)arg1 + 0x18)), (*(f32 *)((u8 *)arg1 + 0x1C)), 900.0f);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x38)) == 0) {
        temp_v0 = (*(s32 *)((u8 *)arg0 + 0x3C));
        if (temp_v0 < 0x19) {
            (*(s32 *)((u8 *)arg0 + 0x3C)) = (s32) (temp_v0 + D_800BE9E4);
        } else {
            (*(s32 *)((u8 *)arg0 + 0x3C)) = func_1000FA64(0x513U, (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x18)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x1C)), 0x7D00, 0x3E8U, 0x1F4, (s32) &func_15033ECC, arg0, (s32) arg1, 0, 0);
            (*(s32 *)((u8 *)arg0 + 0x38)) = 0x513;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15033ECC.s")

s32 func_150340F0(s32 arg0, u8 *arg1) {
    if (arg1[5] == 3) {
        return 1;
    }
    return 0;
}

s32 func_15034118(u8 *arg0, s32 *arg1) {
    s32 n;
    u8 *p;
    u8 *next;
    n = 0;
    if (D_800C3EE0 == 0) {
        return 0;
    }
    p = (u8 *)D_800C3EE0;
    if (p != NULL) {
        do {
            next = *(u8 **)(p + 0x54);
            if (arg0[0x3B] == p[0]) {
                arg1[n] = (s32)p;
                n += 1;
            }
            p = next;
        } while (next != NULL);
    }
    return n;
}

u8 *func_15034174(u8 *arg0) {
    u8 *var_v1;
    u8 *next;
    for (var_v1 = (u8 *)D_800C3EE0; var_v1 != NULL; var_v1 = next) {
        next = *(u8 **)(var_v1 + 0x54);
        if (arg0[0x3B] == var_v1[0]) {
            return var_v1;
        }
    }
    return NULL;
}

void func_150341B4(s32 arg0, s32 arg1) {
    u8 *var_v0;
    u8 *next;
    for (var_v0 = (u8 *)D_800C3EE0; var_v0 != NULL; var_v0 = next) {
        next = *(u8 **)(var_v0 + 0x54);
        if (arg0 == var_v0[0]) {
            var_v0[0] = arg1;
        } else if (arg1 == var_v0[0]) {
            var_v0[0] = arg0;
        }
    }
}

s32 func_150341FC(s32 arg0, u8 *arg1) {
    u8 *temp_v1;

    if (D_800C35EA == 1) {
        return 0;
    }
    temp_v1 = (*(u8 **)((u8 *)arg1 + 0x31C));
    if ((temp_v1 != NULL) && ((*(u8 *)((u8 *)temp_v1 + 0x78)) != 9) && ((*(u8 *)((u8 *)temp_v1 + 0x11A)) != 3)) {
        (*(u8 *)((u8 *)temp_v1 + 0x11A)) = 0U;
        return 1;
    }
    return 0;
}

s32 func_15034260(s32 arg0, u8 *arg1) {
    u8 temp_v0;
    u8 *temp_v1;

    if (D_800C35EA == 1) {
        return 0;
    }
    temp_v1 = (*(u8 **)((u8 *)arg1 + 0x31C));
    if (temp_v1 != NULL) {
        temp_v0 = (*(u8 *)((u8 *)temp_v1 + 0x78));
        if ((temp_v0 != 0xC) && (temp_v0 != 0x16) && ((*(u8 *)((u8 *)temp_v1 + 0x11A)) != 3)) {
            (*(u8 *)((u8 *)temp_v1 + 0x11A)) = 0U;
            return 1;
        }
    }
    return 0;
}
