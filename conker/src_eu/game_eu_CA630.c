#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A6440[];
#endif


s32 func_1509CE20(s32 arg0) {
    return D_800877D0[arg0].unk0;
}

u16 func_1509CE40(s32 arg0) {
    return D_800877D0[arg0].unk8;
}

s32 func_1509CE60(s32 arg0) {
    return *(u16 *)((u8 *)&D_800877D0[arg0] + 0xA) & 0xFFF;
}

s32 func_1509CE88(s32 arg0) {
    return D_800877D0[arg0].unk4;
}

s32 func_1509CEA8(s32 arg0)
{
  s32 var_v1;
  struct_eu_800877D0 *var_v0;
  var_v1 = 0;
 var_v0 = D_800877D0; loop_1: if ((var_v0->unk0 != 0) && (arg0 == ((var_v0->unk4 & 0x1FFFFFFF) + 1))) { return var_v1;
  }

  if (((*((s32 *) (((u8 *) var_v0) + 0x14))) != 0) && (arg0 == (((*((s32 *) (((u8 *) var_v0) + 0x18))) & 0x1FFFFFFF) + 1)))
  {
    return var_v1 + 1;
  }
  if (((*((s32 *) (((u8 *) var_v0) + 0x28))) != 0) && (arg0 == (((*((s32 *) (((u8 *) var_v0) + 0x2C))) & 0x1FFFFFFF) + 1)))
  {
    return var_v1 + 2;
  }
  if (((*((s32 *) (((u8 *) var_v0) + 0x3C))) != 0) && (arg0 == (((*((s32 *) (((u8 *) var_v0) + 0x40))) & 0x1FFFFFFF) + 1)))
  {
    return var_v1 + 3;
  }
  var_v1 += 4;
  var_v0 += 4;
  if (var_v1 == 0xCC)
  {
    return 0xCC;
  }
  goto loop_1;
}

s32 func_1509CF78(void) {
    s32 n = 0;
    s32 i;
    for (i = 0; i < 204; i++) {
        if (D_800877D0[i].unk0 != 0) {
            n++;
        }
    }
    return n;
}

#ifdef NON_MATCHING
/* event_prereqs_met: D_800877D0[id] +0xC is a 0xFFFF-terminated list of event ids. The event may start when every
 * prerequisite has its save bit set (bit field at D_800D2E4C) and its own prerequisites hold. Empty list: 1. */
s32 func_1509CBD4(s32 id) {
    u16 *p = *(u16 **) ((u8 *) D_800877D0 + id * 0x14 + 0xC);
    u16 e;
    s32 ok;

    e = *p;
    while (e != 0xFFFF) {
        ok = func_1509CBD4(e);
        e = *p;
        if (!(((u8 *) D_800D2E4C)[e >> 3] & (1 << (e & 7))) || ok == 0) {
            return 0;
        }
        p++;
        e = *p;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509CBD4.s")
#endif

void func_1509D0C4(s32 arg0);

void func_1509D0A4(s32 arg0) {
    func_1509D0C4(arg0);
}

s32 func_1509D274(s32, void (*)(s32), s32);
extern s32 D_800877DC;

void func_1509D0C4(s32 arg0) {
    func_1509D274(*(s32 *)((u8 *)&D_800877DC + (arg0 * 0x14)), func_1509D0C4, arg0);
}

extern u16 *D_800877E0[][5];

s32 func_1509D104(s32 arg0) {
    s32 cnt;
    u16 *p;
    s32 *new_var2; // fakematch: permuter temp
    u16 *new_var; // fakematch: permuter temp
    u8 *q; // fakematch: permuter temp (dead)

    p = D_800877E0[arg0][0];
    cnt = 0;
    if (*p != 0xFFFF) {
        do {
            ((u8 *)D_800D2E4C)[*p >> 3] |= 1 << (*p & 7);
            new_var = p;
            q = *new_var + (u8 *)(new_var2 = &D_800D2E70);
            if (*((u8 *)&D_800D2E70 + *new_var) != 3) {
                *((u8 *)new_var2 + *new_var) = 3;
                func_1509D0C4(*new_var);
                cnt++;
            }
            p++;
        } while (*p != 0xFFFF);
    }
    return cnt;
}

#ifdef NON_MATCHING
// save_unlocks_propagate: unlocks arg0's list (func_1509D104), then keeps expanding every entry of the state bytes
// D_800D2E70 (0xCC of them) that is in state 3 until a whole pass unlocks nothing new. The asm returns no value.
void func_1509D1EC(s32 arg0) {
    s32 added;
    s32 i;

    func_1509D104(arg0);
    do {
        added = 0;
        for (i = 0; i < 0xCC; i++) {
            if (((u8 *) &D_800D2E70)[i] == 3) {
                added += func_1509D104(i);
            }
        }
    } while (added != 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D1EC.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D274.s")

#ifdef NON_MATCHING
/* P132: the save-route table func_1502B6BC loads (asset 3, 8-byte records): record 0's info word gets the record
 * count - 1; record i >= 1 points at its own block, a list of (offset, flags) pairs ended by flag 0x80000000. */
typedef struct SaveRouteRec {
    u32 *data;
    u32 info;
} SaveRouteRec;
s32 func_1502B6BC(s32 *, s32, s32 *, s32, ...);

// save_route_table_load: loads the save-route table into D_800D33D0 (arg0 selects it), stores the number of routes
// (records - 1) in record 0 and *count, and relocates each route block: every pair's first word gets the block
// address added (up to the pair flagged 0x80000000; the flags are cleared), and the block's word 3 becomes
// (word 3 & 0x0FFFFFFF) >> 1. Returns 0 (and *count = 0) when nothing was loaded, else 1.
s32 func_1509D338(s32 arg0, s32 *count) {
    u32 n;
    u32 i;
    u32 *p;
    s32 last;
    SaveRouteRec *tbl;

    n = 0;
    D_800D33D0 = func_1502B6BC(NULL, 0, (s32 *) &n, 3, 8, 0, arg0);
    tbl = (SaveRouteRec *) D_800D33D0;
    if (tbl == NULL) {
        *count = 0;
        return 0;
    }
    tbl[0].info = n - 1;
    *count = n - 1;
    for (i = 1; i < n; i++) {
        p = tbl[i].data;
        last = 0;
        do {
            p[0] += (u32) tbl[i].data;
            if (p[1] & 0x80000000) {
                last = 1;
            }
            p[1] &= 0x0FFFFFFF;
            p += 2;
        } while (!last);
        p = tbl[i].data;
        p[3] = (p[3] & 0x0FFFFFFF) >> 1;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D338.s")
#endif

#ifdef NON_MATCHING // the definition is void (asm: v0 is not a result); one signature for wasm
void func_10004074(s32);
#else
s32 func_10004074(s32);
#endif
void func_1509D464(void) {
    s32 r;
    if (D_800D33D0 != 0) {
        r = D_800D33D0;
        func_10004074(r);
        D_800D33D0 = 0;
    }
}

#ifdef NON_MATCHING
// save_route_check: route arg1 of the table D_800D33D0 (record arg1 + 1, relocated by func_1509D338): writes the
// first id of its requirement list through outA and the id its word 0 points at through outB (0xBF / 0 when there
// is no table or no route; NULL out-pointers are skipped) and returns 1 when every id of the list (word 2, count
// word 3, s16 each) has its bit set in D_800D2E4C, else 0. arg0 is unused.
s32 func_1509D49C(s8 arg0, u8 arg1, s32 *outA, s32 *outB) {
    SaveRouteRec *rec;
    u32 *route;
    s16 *ids;
    u32 i;
    u32 n;
    s32 id;

    rec = &((SaveRouteRec *) D_800D33D0)[arg1];
    if (D_800D33D0 == 0 || rec[1].data == NULL) {
        if (outA != NULL) {
            *outA = 0xBF;
        }
        if (outB != NULL) {
            *outB = 0;
        }
        return 0;
    }
    if (outA != NULL) {
        *outA = *(s16 *) rec[1].data[2];
    }
    if (outB != NULL) {
        *outB = *(s16 *) rec[1].data[0];
    }
    route = rec[1].data;
    n = route[3];
    if (n == 0) {
        return 1;
    }
    ids = (s16 *) route[2];
    for (i = 0; i < n; i++) {
        id = ids[i];
        if (!(((u8 *) D_800D2E4C)[id >> 3] & (1 << (id & 7)))) {
            return 0;
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D49C.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D590.s")

#ifdef NON_MATCHING
void func_150B42B0(void);
void func_150C572C(void);
void func_150C619C(s32);
void func_150E3B5C(s32);
s32 func_150EBE44(s32);
void func_150F7330(u8 *);
void func_150F9CA0(u8);
void func_151616D0(u8, u8, s32);
void func_151CD944(s32);
void func_151D2CC8(s16);
extern s8 D_800D9D40;

void func_1509DB90(s32 arg0, u8 *arg1) {
    struct127 *temp_v0;
    struct127 *temp_v0_2;

    switch (arg0) {
    case 41:
        func_150EBE44(arg0);
        return;
    case 39:
        func_150F9CA0((*(u8 *)((u8 *)arg1 + 7)));
        return;
    case 38:
        func_151616D0(0x29, 0x18, 0);
        return;
    case 36:
        temp_v0 = func_1505EEF4((*(s32 *)((u8 *)arg1 + 4)) & 0xFFF);
        if (temp_v0 != NULL) {
            func_150F7330(temp_v0);
            return;
        }
    default:
        return;
    case 26:
        func_151616D0(0x26, 0x18, 0);
        return;
    case 18:
        func_151CD944((*(s32 *)((u8 *)arg1 + 4)));
        return;
    case 2:
        D_800D9D40 = 0;
        return;
    case 4:
    case 5:
    case 6:
        func_150E3B5C(arg0 >> 6);
        return;
    case 8:
        func_150B42B0();
        return;
    case 9:
        temp_v0_2 = func_1505EEF4((*(s32 *)((u8 *)arg1 + 4)) & 0xFFF);
        if (temp_v0_2 == NULL) {
            return;
        }
        func_150C619C(temp_v0_2);
        return;
    case 10:
        func_150C572C();
        return;
    case 19:
        func_151D2CC8((*(s16 *)((u8 *)arg1 + 6)));
        return;
    case 21:
        func_151616D0(0x20, 0x18, 0);
        return;
    case 22:
        func_151616D0(0x23, 0x28, 0);
        func_151616D0(0x24, 0x28, 0);
        break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509DB90.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800A0D30;

void func_1509DD0C(s32 arg0, s32 arg1, u8 *arg2) {
    struct {
        f32 u2C;
        s8 u30;
        s8 u31;
        s8 u32;
        s8 u33;
        s8 u34;
        u8 pad35[0x3];
        s8 u38;
    } sp;
    s32 var_a0;
    s32 var_a1;
    s32 temp_v0;
    s32 temp_v0_2;

    switch (arg0) {
    case 0x34:
        if (arg1 == 3) {
            func_15197A7C(func_1505EEF4((*(s32 *)((u8 *)arg2 + 4)) & 0xFFF));
            return;
        }
    default:
        return;
    case 0x32:
        if (arg1 == 2) {
            func_151403A8(0, 0x53U);
            return;
        }
        if (arg1 == 3) {
            func_151403A8(0, 0x54U);
            return;
        }
        break;
    case 0x2D:
        func_151645C4((arg1 == 6) & 0xFF);
        return;
    case 0x28:
        if (arg1 == 2) {
            func_1515F170(4, 1);
            func_1515F170(5, 0);
            return;
        }
        if (arg1 == 3) {
            func_1515F170(4, 0);
            func_1515F170(5, 1);
            return;
        }
        break;
    case 0x1F:
        if (arg1 == 5) {
            sp.u38 = (s8) (*(s32 *)((u8 *)arg2 + 8));
            func_151403A8((s32) &sp.u38, 0x36U);
        }
        /* fallthrough */
    case 0x1E:
        if (arg1 == 2) {
            sp.u34 = (s8) (*(s32 *)((u8 *)arg2 + 8));
            func_151494E0((s32) &sp.u34, 0x34U);
            return;
        }
        break;
    case 0x1D:
        if (arg1 == 5) {
            sp.u2C = (f32) (*(s32 *)((u8 *)arg2 + 0xC));
            sp.u30 = (s8) (*(s32 *)((u8 *)arg2 + 8));
            sp.u31 = (s8) (*(s32 *)((u8 *)arg2 + 0x10));
            sp.u32 = (s8) (*(s32 *)((u8 *)arg2 + 0x14));
            sp.u33 = (s8) (*(s32 *)((u8 *)arg2 + 0x18));
            func_1516944C(0x35, (s32) &sp.u2C, 0x33U);
            return;
        }
        break;
    case 0x1C:
        if (arg1 == 5) {
            temp_v0 = (*(s32 *)((u8 *)arg2 + 8));
            if ((temp_v0 < 0) || (temp_v0 >= 3)) {
                return;
            }
            func_151494E0((s32) ((temp_v0 * 0x10) + &D_800A0D30), 0x32U);
            return;
        }
        break;
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
        temp_v0_2 = arg0 & 0x3F;
        if (temp_v0_2 == 0xB) {
            var_a0 = 1;
        } else if (temp_v0_2 == 0xC) {
            var_a0 = 2;
        } else if (temp_v0_2 == 0xD) {
            var_a0 = 3;
        } else {
            var_a0 = 0;
            if (temp_v0_2 == 0xE) {
                var_a0 = 4;
            }
        }
        if (arg1 == 2) {
            var_a1 = 0x17;
        } else {
            var_a1 = 0x17;
            if (arg1 == 3) {
                var_a1 = 0x18;
            }
        }
        func_151616D0(var_a0, var_a1, 0);
        return;
    case 0x11:
        func_150DF1A8((*(u8 *)((u8 *)arg2 + 0xB)), (arg1 == 3) & 0xFF);
        break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509DD0C.s")
#endif
#ifdef NON_MATCHING
void func_150E3C3C(s32, s32 *, s32 *, s32 *);

s32 func_1509DFCC(s32 arg0, s32 arg1, s32 arg2) {
    struct {
        s32 u34;
        s32 u38;
        s32 u3C;
    } sp;
    s32 temp_a0;
    s32 temp_t8;
    s32 var_t0;
    s32 var_v0;
    s8 var_a1;
    struct_eu_node *temp_v1;
    struct_eu_node *var_v0_2;

    var_v0 = 4;
    sp.u3C = 0;
    sp.u38 = 0;
    sp.u34 = 0;
    if ((arg0 != 4) && (arg0 != 5) && (arg0 != 6)) {
        if (arg0 == 0x19) {
            var_t0 = 0;
            if (arg1 == 4) {
loop_6:
                var_a1 = 0;
loop_7:
                var_v0_2 = D_800DD280[var_t0][*(((u8 *)&D_800A6440) + (var_a1 * 4))];
                var_a1 += 1;
                if (var_v0_2 != NULL) {
loop_8:
                    temp_v1 = var_v0_2->next;
                    var_v0_2 = temp_v1;
                    if ((*(u8 *)((u8 *)var_v0_2 + 0x48)) == 2) {
                        return 0;
                    }
                    if (temp_v1 == NULL) {
                        goto block_11;
                    }
                    goto loop_8;
                }
block_11:
                if (var_a1 >= 3) {
                    temp_t8 = (var_t0 + 1) & 0xFF;
                    var_t0 = temp_t8;
                    if (temp_t8 >= 2) {
                        return 1;
                    }
                    goto loop_6;
                }
                goto loop_7;
            }
        }
        /* Duplicate return node #20. Try simplifying control flow for better match */
        return var_v0;
    }
    if ((arg1 == 0) || (arg1 == 1)) {
        temp_a0 = arg0 >> 6;
        if (temp_a0 != 0) {
            func_150E3C3C(temp_a0, &sp.u3C, &sp.u38, &sp.u34);
            if (arg1 == 0) {
                sp.u38 = (sp.u3C << 0x10) | (sp.u34 & 0xFFFF);
            }
            var_v0 = sp.u38;
        }
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509DFCC.s")
#endif