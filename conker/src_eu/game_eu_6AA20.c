#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1503D728(s32 *arg0, s32 arg1);
#endif


#ifdef NON_MATCHING
s32 func_1502B6BC(s32 *, s32, s32 *, s32, ...);
void func_1503D658(s8 *arg0, s32 arg1);
s32 func_1503DF2C(s32 arg0);
void func_1503DC74(s32 arg0);
s32 func_1503DAF4(s32 arg0);
s32 func_150028BC(s32 arg0);
s32 func_1503DA64(s32 arg0, s32 arg1);
s32 func_1503D950(s32 arg0, s32 arg1);
void func_1503E00C(s32 arg0);
void func_10004074(s32);
s32 func_1510D3E0(Gfx *, s32, s32, s32, s16 **);
extern s32 D_800C48A8[];
extern s32 D_800C4D10[];
extern s32 D_800C5000[];
extern s32 D_800C5468[];
extern u16 D_800C4730[];
extern u16 D_800C5BC0[];
extern u16 D_800C4B98[];
extern s32 D_800C4440;
extern s32 D_800C5758;
extern s32 D_800C5A48;
extern s32 D_800C6360[187];
extern s32 D_800C5C08[187];
extern s32 D_800C6070[187];
/* P51: model load of id arg0 (< 0xBB, not 0xFF; nothing to do when D_800D19A0[id] is set). Model asset (1, id)
 * through func_1502B6BC (7 relocated {offset, size} pairs): D_800D19A0[id] = base + 0x38, D_800C4440 (+0),
 * D_800C48A8 (+8, display lists), D_800C4D10 (+0x28), D_800C5000 (+0x10, skeleton), D_800C5758 (+0x18),
 * D_800C5468 (+0x20), the counts D_800C4730 (+4 / 4), D_800C5BC0, D_800C4B98 (+0xC / 4), D_800C5A48 (+0x1C / 12),
 * D_800C52F0 (+0x14 / 16, joints). The display lists of +8 and +0x28 are relocated (func_1503D728 / func_1503D658).
 * Then (arg3) func_1503DF2C and func_1510D3E0 per display list, func_1503DC74 / func_1503DAF4, (arg2 +0x18 & 0x4000
 * or arg4 & 1) func_150028BC, func_1503DA64, func_1503D950 (animation bank); any error frees everything again.
 * Returns 0, 1 (no asset) or the error bits. */
s32 func_1503D210(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 id = arg0;
    s32 sz;
    u8 *m;
    s32 base;
    s32 err = 0;
    s32 i;
    u32 n;

    if (id == 0xFF) {
        return 0;
    }
    if (id >= 0xBB) {
        return 0;
    }
    if (((s32 *)&D_800D19A0)[id] != 0) {
        return 0;
    }
    m = (u8 *)func_1502B6BC(&sz, 7, NULL, 2, 1, id);
    if (m == NULL) {
        return 1;
    }
    ((s32 *)&D_800D19A0)[id] = (s32)(m + 0x38);
    ((s32 *)&D_800C4440)[id] = *(s32 *)(m + 0);
    D_800C48A8[id] = *(s32 *)(m + 8);
    D_800C4D10[id] = *(s32 *)(m + 0x28);
    D_800C5000[id] = *(s32 *)(m + 0x10);
    ((s32 *)&D_800C5758)[id] = *(s32 *)(m + 0x18);
    D_800C5468[id] = *(s32 *)(m + 0x20);
    D_800C4730[id] = *(u32 *)(m + 4) >> 2;
    base = ((s32 *)&D_800C4440)[id];
    if (base == 0) {
        base = D_800C48A8[id];
    }
    D_800C5BC0[id] = (u32)(base - (s32)m - 0x38) >> 4;
    D_800C4B98[id] = *(u32 *)(m + 0xC) >> 2;
    for (i = 0; i < D_800C4B98[id]; i++) {
        func_1503D728((s32 *)D_800C48A8[id] + i, (s32)m);
        func_1503D658(((s8 **)D_800C48A8[id])[i], (s32)m);
    }
    n = *(u32 *)(m + 0x2C) >> 2;
    for (i = 0; (u32)i < n; i++) {
        func_1503D728((s32 *)D_800C4D10[id] + i, (s32)m);
        func_1503D658(((s8 **)D_800C4D10[id])[i], (s32)m);
    }
    ((u16 *)&D_800C5A48)[id] = *(u32 *)(m + 0x1C) / 12;
    D_800C52F0[id] = *(u32 *)(m + 0x14) >> 4;
    if (arg3 != 0) {
        err = func_1503DF2C(id);
        if (err == 0) {
            for (i = 0; i < D_800C4B98[id]; i++) {
                func_1510D3E0(((Gfx **)D_800C48A8[id])[i], 0, 0, 0x3E, NULL);
            }
        }
    }
    if (err == 0) {
        func_1503DC74(id);
        err |= func_1503DAF4(id);
    }
    if (err == 0) {
        if ((arg2 != 0 && (*(s32 *)(arg2 + 0x18) & 0x4000)) || (arg4 & 1)) {
            if (func_150028BC(id) != 0) {
                err |= 8;
            }
        }
    }
    if (err == 0) {
        err |= func_1503DA64(id, 0);
        if (err == 0) {
            err |= func_1503D950(id, 0);
        }
    }
    if (err != 0) {
        if (D_800C6360[id] != 0) {
            func_10004074(D_800C6360[id]);
        }
        func_1503E00C(id);
        if (D_800C5C08[id] != 0) {
            func_10004074(D_800C5C08[id]);
            D_800C5C08[id] = 0;
        }
        if (D_800C6070[id] != 0) {
            func_10004074(D_800C6070[id]);
            D_800C6070[id] = 0;
        }
        if (((s32 *)&D_800D19A0)[id] != 0) {
            func_10004074(((s32 *)&D_800D19A0)[id] - 0x38);
            ((s32 *)&D_800D19A0)[id] = 0;
        }
    }
    return err;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D210.s")
#endif

#ifdef NON_MATCHING
void func_1503D658(s8 *arg0, s32 arg1) {
    s32 var_s0;
    s8 *var_v0;
    s8 var_v1;

    if (arg0 != NULL) {
        var_s0 = 0;
        var_v0 = arg0;
        if (*arg0 != -0x21) {
            var_v1 = *arg0;
            do {
                if (var_v1 != -0x24) {
                    if (var_v1 == 1) {
                        func_1503D728(var_v0 + 4, arg1);
                    }
                } else if ((*(u8 *)((u8 *)var_v0 + 3)) == 0xE) {
                    func_1503D728(var_v0 + 4, arg1);
                }
                var_s0 += 1;
                var_v0 = (var_s0 * 8) + arg0;
                var_v1 = *var_v0;
            } while (var_v1 != -0x21);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D658.s")
#endif
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

#ifdef NON_MATCHING
s32 allocate_memory(s32, s32, s32, s32);
extern s32 D_800C4440;

s32 func_1503DAF4(s32 arg0) {
    s32 sp34;
    s32 sp2C;
    s32 *sp18;
    s16 temp_t6;
    s16 temp_t9;
    s32 *temp_t1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v0;
    s32 var_a0;
    s32 var_t0;
    s32 var_t2;
    s32 var_v1;
    u8 *var_v0;
    u8 *var_v0_2;
    u8 *var_v1_2;
    u8 *var_v1_3;

    var_v1 = -1;
    if (arg0 == 0x24) {
        var_t0 = 0x5E;
        var_v1 = 0;
    } else {
        var_t0 = 0;
    }
    if (var_t0 == 0) {
        goto block_18;
    }
    temp_t1 = &D_800C6360[arg0];
    if (*temp_t1 != 0) {
        goto block_18;
    }
    var_t2 = (&D_800D19A0)[arg0];
    if (var_v1 != -1) {
        var_t2 += *(s32 *)(*(s32 *)((u8 *)&D_800C4440 + (arg0 * 4)) + (var_v1 * 4)) * 0x10;
    }
    sp34 = var_t0;
    sp18 = temp_t1;
    sp2C = var_t2;
    temp_v0 = allocate_memory(var_t0 * 4, 1, 0, 2);
    *temp_t1 = temp_v0;
    if (temp_v0 == 0) {
        return 1;
    }
    temp_a3 = *temp_t1;
    var_a0 = 0;
    if (var_t0 > 0) {
        temp_a2 = var_t0 & 3;
        if (temp_a2 != 0) {
            var_v1_2 = var_t2 + (0 * 0x10);
            var_v0 = temp_a3 + (0 * 4);
            do {
                var_a0 += 1;
                var_v0 += 4;
                (*(s16 *)((u8 *)var_v0 + -4)) = (s16) (*(s16 *)((u8 *)var_v1_2 + 8));
                temp_t9 = (*(s16 *)((u8 *)var_v1_2 + 0xA));
                var_v1_2 += 0x10;
                (*(s16 *)((u8 *)var_v0 + -2)) = temp_t9;
            } while (temp_a2 != var_a0);
            if (var_a0 != var_t0) {
                goto block_16;
            }
        } else {
block_16:
            var_v1_3 = var_t2 + (var_a0 * 0x10);
            var_v0_2 = temp_a3 + (var_a0 * 4);
            do {
                var_a0 += 4;
                var_v0_2 += 0x10;
                (*(s16 *)((u8 *)var_v0_2 + -0x10)) = (s16) (*(s16 *)((u8 *)var_v1_3 + 8));
                temp_t6 = (*(s16 *)((u8 *)var_v1_3 + 0xA));
                var_v1_3 += 0x40;
                (*(s16 *)((u8 *)var_v0_2 + -0xE)) = temp_t6;
                (*(s16 *)((u8 *)var_v0_2 + -0xC)) = (s16) (*(s16 *)((u8 *)var_v1_3 + -0x28));
                (*(s16 *)((u8 *)var_v0_2 + -0xA)) = (s16) (*(s16 *)((u8 *)var_v1_3 + -0x26));
                (*(s16 *)((u8 *)var_v0_2 + -8)) = (s16) (*(s16 *)((u8 *)var_v1_3 + -0x18));
                (*(s16 *)((u8 *)var_v0_2 + -6)) = (s16) (*(s16 *)((u8 *)var_v1_3 + -0x16));
                (*(s16 *)((u8 *)var_v0_2 + -4)) = (s16) (*(s16 *)((u8 *)var_v1_3 + -8));
                (*(s16 *)((u8 *)var_v0_2 + -2)) = (s16) (*(s16 *)((u8 *)var_v1_3 + -6));
            } while (var_a0 != var_t0);
        }
    }
block_18:
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DAF4.s")
#endif
#ifdef NON_MATCHING
extern u16 D_800C5D38[];
extern s32 D_800C48A8[];
/* P51: triangle count of model arg0's first display list (D_800C48A8[arg0][0]; the asm's loop over the list
 * stops after one): G_TRI1 1, G_TRI2 2, opcodes 0x10-0x1F 4, up to G_ENDDL; into D_800C5D38[arg0]. */
void func_1503DC74(s32 arg0) {
    u32 **lst = (u32 **)D_800C48A8[arg0];
    u32 *c;
    s32 n = 0;
    s32 k = 0;
    s32 op;

    do {
        c = *lst++;
        k += 4;
        op = (s8)(c[0] >> 24);
        while (op != -0x21) {
            if (op == 5) {
                n += 1;
            } else if (op == 6) {
                n += 2;
            } else if ((op >> 4) == 1) {
                n += 4;
            }
            c += 2;
            op = (s8)(c[0] >> 24);
        }
    } while (k != 4);
    D_800C5D38[arg0] = n;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DC74.s")
#endif

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
#ifdef NON_MATCHING
s32 func_1510DD2C(s32, s32, u16);
extern s32 D_800C5758;
extern s32 D_800C5A48;

void func_1503E00C(s32 arg0) {
    s32 temp_a1;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s1;
    u16 *temp_s3;
    u8 *temp_v0;

    temp_s3 = ((s32 *)((u8 *)&D_800C5A48 + (arg0 * 2)));
    var_s0 = 0;
    if ((s32) *temp_s3 > 0) {
        var_s1 = 0;
        do {
            temp_v0 = *(((s32 *)((u8 *)&D_800C5758 + (arg0 * 4)))) + var_s1;
            temp_v1 = (*(s32 *)((u8 *)temp_v0 + 0));
            if (temp_v1 != 0x80000000) {
                temp_a1 = (*(s32 *)((u8 *)temp_v0 + 4));
                if (temp_v1 != temp_a1) {
                    func_1510DD2C(temp_a1, temp_a1, *temp_s3);
                }
            }
            var_s0 += 1;
            var_s1 += 0xC;
        } while (var_s0 < (s32) *temp_s3);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503E00C.s")
#endif