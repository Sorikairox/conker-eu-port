#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D210.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D658.s")

void func_1503D728(s32 *arg0, s32 arg1) {
    s32 temp_v0 = *arg0;
    if ((temp_v0 != 0) && !(temp_v0 & 0x0F000000)) {
        *arg0 = temp_v0 + arg1;
    }
}

void func_1503D74C(s32 *arg0, s32 arg1) {
    while (*arg0 != 0) {
        *arg0 += arg1;
        arg0 += 2;
    }
}

void func_1503D774(u8 *arg0, s32 arg1)
{
  u8 *start = arg0;
  while (*(u16 *)arg0 != 0x3E7) {
    if (*(s32 *)(arg0 + 4) != 0) {
      func_1503D728(arg0 + 4, start);
    }
    arg0 += 8;
  }
  D_800C5A90[arg1] = (arg0 - start) >> 3;
}

#ifdef NON_MATCHING
extern s32 D_800847A0;
extern u8 D_80098C38;

void func_1503D800(s32 arg0) {
    s16 *temp_t3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    u8 *temp_a3;
    u8 *var_a1;
    u8 *var_t0;
    u8 *var_v1_2;
    u8 temp_a0;

    var_a1 = &D_80098C38;
    var_v0 = 0;
loop_1:
    temp_a0 = *var_a1;
    var_v1 = 0;
    if ((s32) temp_a0 > 0) {
        temp_a3 = *(s32 *)((u8 *)&D_800847A0 + (var_v0 * 4));
        var_t0 = temp_a3;
loop_3:
        var_v1 += 1;
        if (arg0 == *var_t0) {
            var_v0_2 = 0;
            if ((s32) temp_a0 > 0) {
                var_v1_2 = temp_a3;
                do {
                    var_v0_2 += 1;
                    D_800D1588[*var_v1_2] = D_800D1588[arg0];
                    temp_t3 = &D_800C5A90[*var_v1_2];
                    var_v1_2 += 1;
                    *temp_t3 = (s16) (u16) D_800C5A90[arg0];
                } while (var_v0_2 < (s32) temp_a0);
            }
        } else {
            var_t0 += 1;
            if (var_v1 >= (s32) temp_a0) {
                goto block_9;
            }
            goto loop_3;
        }
    } else {
block_9:
        var_v0 += 1;
        var_a1 += 1;
        if (var_v0 == 5) {
            return;
        }
        goto loop_1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D800.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800847A0;
extern u8 D_80098C38;

s32 func_1503D8E0(s32 arg0) {
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a3;
    u8 *var_a1;
    u8 *var_t0;
    u8 temp_a0;

    var_a1 = &D_80098C38;
    var_v0 = 0;
loop_1:
    temp_a0 = *var_a1;
    var_v1 = 0;
    if ((s32) temp_a0 > 0) {
        temp_a3 = *(s32 *)((u8 *)&D_800847A0 + (var_v0 * 4));
        var_t0 = temp_a3;
loop_3:
        var_v1 += 1;
        if (arg0 == *var_t0) {
            return (s32) *temp_a3;
        }
        var_t0 += 1;
        if (var_v1 >= (s32) temp_a0) {
            goto block_6;
        }
        goto loop_3;
    }
block_6:
    var_v0 += 1;
    var_a1 += 1;
    if (var_v0 == 5) {
        return arg0;
    }
    goto loop_1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D8E0.s")
#endif
s32 func_1503D8E0(s32);
void func_1503D800(s32);
s32 func_1502B350(u8 *, s32, s32 *);
s32 func_1502B5C8(s32 *, s32, ...);
void func_1503D74C(s32 *arg0, s32 arg1);
void func_1503D774(u8 *arg0, s32 arg1);

s32 func_1503D950(s32 arg0, s32 arg1) {
    s32 sp34;
    s32 *p;

    if (*(s32 **)&D_800D1588[arg0] != NULL) {
        return 0;
    }
    p = (s32 *)func_1502B5C8(&sp34, 2, 0xF, func_1503D8E0(arg0));
    if (p == NULL) {
        *(s32 **)&D_800D1588[arg0] = NULL;
        D_800C5A90[arg0] = 0;
        func_1503D800(arg0);
        return 4;
    }
    *(s32 **)&D_800D1588[arg0] = p;
    if ((*(s32 **)&D_800D1588[arg0])[0] != 0) {
        (*(s32 **)&D_800D1588[arg0])[0] += (s32)*(s32 **)&D_800D1588[arg0];
        func_1503D74C((s32 *)(*(s32 **)&D_800D1588[arg0])[0], (s32)*(s32 **)&D_800D1588[arg0] + 0x10);
    }
    if ((*(s32 **)&D_800D1588[arg0])[1] != 0) {
        (*(s32 **)&D_800D1588[arg0])[1] += (s32)*(s32 **)&D_800D1588[arg0];
    }
    if ((*(s32 **)&D_800D1588[arg0])[2] != 0) {
        (*(s32 **)&D_800D1588[arg0])[2] += (s32)*(s32 **)&D_800D1588[arg0];
    }
    *(s32 **)&D_800D1588[arg0] = (s32 *)((u8 *)*(s32 **)&D_800D1588[arg0] + 0x10);
    func_1503D774((u8 *)*(s32 **)&D_800D1588[arg0], arg0);
    func_1503D800(arg0);
    return 0;
}

s32 func_1502B6BC(s32 *, s32, s32 *, s32, ...);

s32 func_1503DA64(s32 arg0, s32 arg1) {
    s32 sp2C;
    s32 *v;

    if (D_800D1C90[arg0] != NULL) {
        return 0;
    }
    v = (s32 *)func_1502B6BC(&sp2C, 2, NULL, 2, 0x11, arg0);
    if (v == NULL) {
        D_800D1C90[arg0] = NULL;
        return 2;
    }
    do { // fakematch: do-while(0) keeps the result in v0 (permuter)
        D_800D1C90[arg0] = (struct124 *)v;
        D_800D1C90[arg0] = (struct124 *)*v;
    } while (0);
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DAF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DC74.s")

u8 func_1503DD2C(s32 arg0, s32 arg1) {
    u8 *p = ((u8 **)&D_800D19A0)[arg0];
    u8 *q = p - 0x38; // fakematch: computed before the NULL test (delay-slot addiu)
    u8 *r;
    u8 v;

    if (p == NULL) {
        return 0xFF;
    }
    if (*(u32 *)(q + 0x34) < arg1 + 1) {
        return 0xFF;
    }
    r = *(u8 **)(q + 0x30);
    if (r != NULL) {
        v = r[arg1];
    } else {
        v = 0xFF;
    }
    return v;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DD8C.s")

#ifdef NON_MATCHING
s32 func_1510D66C(s32, s32, s32, s32);
extern s32 D_800C5758;
extern s32 D_800C5A48;

s32 func_1503DF2C(s32 arg0) {
    s32 *temp_s0;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    u16 *temp_s6;
    u8 **temp_s2;
    u8 *var_s0;

    temp_s6 = ((u16 *)((u8 *)&D_800C5A48 + (arg0 * 2)));
    var_s4 = 0;
    var_s3 = 0;
    if ((s32) *temp_s6 > 0) {
        temp_s2 = ((u8 **)((u8 *)&D_800C5758 + (arg0 * 4)));
        var_s0 = *temp_s2;
        var_s1 = 0;
        do {
            *(s32 *)(*temp_s2 + var_s1) = func_1510D66C((*(s32 *)((u8 *)var_s0 + 4)), 0, 0x3E, 1);
            temp_s0 = (s32 *)(*temp_s2 + var_s1);
            if (*temp_s0 == 0x80000000) {
                var_s4 |= 0x10;
            }
            var_s3 += 1;
            var_s1 += 0xC;
            var_s0 = ((u8 *)((u8 *)temp_s0 + 0xC));
        } while (var_s3 < (s32) *temp_s6);
    }
    return var_s4;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DF2C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503E00C.s")
