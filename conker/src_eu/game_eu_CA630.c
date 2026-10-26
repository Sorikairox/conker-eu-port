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

#ifdef NON_MATCHING
void func_1509D274(s32 listp, void (*cb)(s32), s32 arg2);
#else
s32 func_1509D274(s32, void (*)(s32), s32);
#endif
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

#ifdef NON_MATCHING
// event_list_unlock: for each id of the 0xFFFF-terminated u16 list: calls cb(id) (func_1509D0C4 recurses into the
// event's own list), sets its state byte D_800D2E70[id] to 3 and its save bit in D_800D2E4C. arg2 is unused; the
// asm returns no value.
void func_1509D274(s32 listp, void (*cb)(s32), s32 arg2) {
    u16 *list = (u16 *)listp;

    while (*list != 0xFFFF) {
        cb(*list);
        ((u8 *)&D_800D2E70)[*list] = 3;
        ((u8 *)D_800D2E4C)[*list >> 3] |= 1 << (*list & 7);
        list++;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D274.s")
#endif

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

#ifdef NON_MATCHING
extern u8 D_8009F4A0;            /* the one-entry effect table of command 0x18 */
extern s8 D_800D9D40;
void light_ctrl_broadcast(u8, u8, s32);
void func_1000E7A0(u32, s32);
s32 func_15046F70(void *, u16, f32, void *);
struct260 *func_150B58B0(u8 *, s16, u8, s32);
void func_150BD550(u8, s32);
void func_150BF47C(s32);
void func_150D5F7C(struct127 *, s32, s32);
void func_150DF240(f32 *, u8, s32);
void func_150E0880(void);
struct260 *func_150E15E0(u8, u8, s32);
s32 func_150E3788(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_150E3850(s32, s32, s32, s32, s32, f32);
s32 func_150E3994(s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_150E8728(s32, u8, s32);
void func_150E8EB0(void);
void func_150ED180(s32, u8, s32);
void *func_150F7364(struct127 *);
void func_150FAFC0(u8, s32);
void func_150FB2A8(void);
void func_150FB2F8(void);
void func_150FCFB0(void);
void func_150FD554(struct127 *, u8, s32);
void func_151086A0(struct127 *, u8, s32);
s32 object_hit_effects(u8 *, u8, u8, u8, u8, u8, u8, s32);
void func_15155D6C(s32, s32, f32);
struct225 *light_create_obj_pulse(u8, u8, s32);
void func_1517946C(s32);
s32 func_1518FA8C(s32, u8, s16, s8, s8, s8, u8, s32, u8, s32);
void func_151C0434(u8 *, f32 *, f32 *, u8, u8, s32);
void func_151C0648(u8 *, s32, u8, s32, s32);
void func_151CD90C(s32);
void func_151D2C70(s16);
/* event_effect_command: handler 14 of the event VM's native table D_800887C0 (id = the command word without its
 * nibble, args = the operands, args[1] mostly an object id resolved with func_1505EEF4 & 0xFFF). Starts effects /
 * spawns: 0 func_150B58B0, 1 func_150BF47C (returns 1), 2 sets D_800D9D40, 3 func_1517946C, 4 / 5 / 6 spawn through
 * func_150E3788 / func_150E3850 (at an object) / func_150E3994 (at the player) and return the handle as
 * (h << 6) | 0xE004, 7 func_150DF240 at a point (args[1] == 999) or func_150E8728, 0x10 / 0x16 light_ctrl_broadcast
 * pairs, 0x18 func_1518FA8C on character args[1], 0x21 func_151C0648 50 above an object, 0x22 func_151C0434 at the
 * ground below (args[1], args[2]) found by func_15046F70, 0x24 func_1514F18C (0x1B), others single calls. Returns 0
 * unless noted. */
s32 func_1509D590(s32 id, s32 *args, s32 *operand) {
    struct {
        u8 pad[0x14];
        s32 u14;
        s8 u18;
        s8 u19;
        s32 u1C;
    } hit;
    f32 pos[3];
    f32 dir[3];
    f32 ground;
    u8 tbl[1];
    struct127 *obj;
    s32 ret = 0;

    switch ((u32) id) {
    case 0x00:
        func_150B58B0((u8 *) func_1505EEF4(args[1] & 0xFFF), (s16) args[2], 0xFF, 1);
        break;
    case 0x01:
        func_150BF47C(args[1]);
        return 1;
    case 0x02:
        D_800D9D40 = 1;
        break;
    case 0x03:
        func_1517946C(args[1]);
        break;
    case 0x04:
        ret = func_150E3788(args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
        if (ret != 0) {
            ret = (ret << 6) | 0xE004;
        }
        break;
    case 0x05:
        obj = func_1505EEF4(args[4] & 0xFFF);
        if (obj != NULL) {
            ret = func_150E3850(args[1], args[2], args[3], (s32) obj, args[5], (f32) args[7]);
            if (ret != 0) {
                ret = (ret << 6) | 0xE004;
            }
        }
        break;
    case 0x06:
        ret = func_150E3994(args[1], args[2], args[3], args[4], args[5], args[6], (s32) D_800CC2D0, args[7],
                            (f32) args[8]);
        if (ret != 0) {
            ret = (ret << 6) | 0xE004;
        }
        break;
    case 0x07:
        if (args[1] == 999) {
            pos[0] = (f32) args[2];
            pos[1] = (f32) args[3];
            pos[2] = (f32) args[4];
            func_150DF240(pos, 0xFF, 1);
        } else {
            func_150E8728(args[1] & 0xFF, 0xFF, 1);
        }
        break;
    case 0x0F:
        func_150E8EB0();
        break;
    case 0x10:
        func_1000E7A0(0x10, 0);
        light_ctrl_broadcast(0x16, 0x1F, 0);
        break;
    case 0x12:
        func_151CD90C(args[1]);
        break;
    case 0x13:
        func_151D2C70((s16) args[1]);
        break;
    case 0x14:
        func_150E15E0((u8) args[1], 0xFF, 1);
        break;
    case 0x16:
        light_ctrl_broadcast(0x23, 0x27, 0);
        light_ctrl_broadcast(0x24, 0x27, 0);
        break;
    case 0x17:
        light_create_obj_pulse((u8) args[1], 0xFF, 1);
        break;
    case 0x18:
        tbl[0] = D_8009F4A0;
        func_1518FA8C((s32) func_15083E90((u8) args[1]), tbl[args[2]], (s16) args[3], -1, -1, -1, 0, 0, 0xFF, 1);
        break;
    case 0x1B:
        func_150FCFB0();
        break;
    case 0x20:
        func_150D5F7C(func_1505EEF4(args[1] & 0xFFF), 0xFF, 1);
        break;
    case 0x21:
        obj = func_1505EEF4(args[1] & 0xFFF);
        if (obj != NULL) {
            pos[0] = obj->x_position;
            pos[1] = obj->y_position + 50.0f;
            pos[2] = obj->z_position;
            func_151C0648((u8 *) pos, (s32) obj, 1, 0xFF, 1);
        }
        break;
    case 0x22:
        ground = -10000.0f;
        hit.u14 = 0;
        hit.u18 = 0;
        hit.u19 = 0;
        hit.u1C = 0;
        pos[0] = (f32) args[1];
        pos[1] = 20000.0f;
        pos[2] = (f32) args[2];
        if (func_15046F70(pos, 0, -10000.0f, &ground) != 0) {
            pos[1] = ground;
            dir[0] = 0.0f;
            dir[1] = -1.0f;
            dir[2] = 0.0f;
            func_151C0434((u8 *) &hit, pos, dir, 1, 0xFF, 1);
        }
        break;
    case 0x23:
        object_hit_effects((u8 *) func_1505EEF4(args[1] & 0xFFF), 1, 1, 1, 1, 0, 0xFF, 1);
        break;
    case 0x24:
        obj = func_1505EEF4(args[1] & 0xFFF);
        if (obj != NULL) {
            func_1514F18C(func_150F7364(obj), obj, 0x1B);
        }
        break;
    case 0x25:
        func_15155D6C(args[1] & 0xFFF, 0x78, (f32) args[2]);
        break;
    case 0x2A:
        obj = func_1505EEF4(args[1] & 0xFFF);
        if (obj != NULL) {
            func_150FD554(obj, 0xFF, 1);
        }
        break;
    case 0x2B:
        func_150E0880();
        break;
    case 0x2C:
        func_150FB2F8();
        break;
    case 0x2E:
        obj = func_1505EEF4(args[1] & 0xFFF);
        if (obj != NULL) {
            func_150ED180((s32) obj, 0xFF, 1);
        }
        break;
    case 0x2F:
        obj = func_1505EEF4(args[1] & 0xFFF);
        if (obj != NULL) {
            func_151086A0(obj, 0xFF, 1);
        }
        break;
    case 0x30:
        func_150FAFC0(0xFF, 1);
        break;
    case 0x31:
        func_150FB2A8();
        break;
    case 0x33:
        func_150BD550(0xFF, 1);
        break;
    }
    return ret;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D590.s")
#endif

#ifdef NON_MATCHING
void func_150B42B0(void);
void func_150C572C(void);
void func_150C619C(s32);
void func_150E3B5C(s32);
s32 func_150EBE44(s32);
void func_150F7330(u8 *);
void func_150F9CA0(u8);
void light_ctrl_broadcast(u8, u8, s32);
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
        light_ctrl_broadcast(0x29, 0x18, 0);
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
        light_ctrl_broadcast(0x26, 0x18, 0);
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
        light_ctrl_broadcast(0x20, 0x18, 0);
        return;
    case 22:
        light_ctrl_broadcast(0x23, 0x28, 0);
        light_ctrl_broadcast(0x24, 0x28, 0);
        break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509DB90.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800A0D30;

// P176: s32 like the D_80088874 handler table. The asm sets v0 only on the case 0x1C / 5 out-of-range path (1);
// elsewhere v0 is a callee's result (undefined): 0 here.
s32 func_1509DD0C(s32 arg0, s32 arg1, u8 *arg2) {
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
            return 0;
        }
    default:
        return 0;
    case 0x32:
        if (arg1 == 2) {
            fx_lists_broadcast_a(0, 0x53U);
            return 0;
        }
        if (arg1 == 3) {
            fx_lists_broadcast_a(0, 0x54U);
            return 0;
        }
        break;
    case 0x2D:
        level_set_lights_mode((arg1 == 6) & 0xFF);
        return 0;
    case 0x28:
        if (arg1 == 2) {
            func_1515F170(4, 1);
            func_1515F170(5, 0);
            return 0;
        }
        if (arg1 == 3) {
            func_1515F170(4, 0);
            func_1515F170(5, 1);
            return 0;
        }
        break;
    case 0x1F:
        if (arg1 == 5) {
            sp.u38 = (s8) (*(s32 *)((u8 *)arg2 + 8));
            fx_lists_broadcast_a((s32) &sp.u38, 0x36U);
        }
        /* fallthrough */
    case 0x1E:
        if (arg1 == 2) {
            sp.u34 = (s8) (*(s32 *)((u8 *)arg2 + 8));
            func_151494E0((s32) &sp.u34, 0x34U);
            return 0;
        }
        break;
    case 0x1D:
        if (arg1 == 5) {
            sp.u2C = (f32) (*(s32 *)((u8 *)arg2 + 0xC));
            sp.u30 = (s8) (*(s32 *)((u8 *)arg2 + 8));
            sp.u31 = (s8) (*(s32 *)((u8 *)arg2 + 0x10));
            sp.u32 = (s8) (*(s32 *)((u8 *)arg2 + 0x14));
            sp.u33 = (s8) (*(s32 *)((u8 *)arg2 + 0x18));
            node_broadcast_type(0x35, (s32) &sp.u2C, 0x33U);
            return 0;
        }
        break;
    case 0x1C:
        if (arg1 == 5) {
            temp_v0 = (*(s32 *)((u8 *)arg2 + 8));
            if ((temp_v0 < 0) || (temp_v0 >= 3)) {
                return 1;
            }
            func_151494E0((s32) ((u8 *) &D_800A0D30 + temp_v0 * 0x10), 0x32U);
            return 0;
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
        light_ctrl_broadcast(var_a0, var_a1, 0);
        return 0;
    case 0x11:
        func_150DF1A8((*(u8 *)((u8 *)arg2 + 0xB)), (arg1 == 3) & 0xFF);
        break;
    }
    return 0;
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
                var_v0_2 = D_800DD280[var_t0][*(s32 *)((u8 *)&D_800A6440 + var_a1 * 4)];
                var_a1 += 1;
                /* P176 (browser P174): test +0x48 of every node, then move to next (the m2c body advanced first:
                 * it skipped each list's first node and read NULL + 0x48 at the end) */
                for (; var_v0_2 != NULL; var_v0_2 = temp_v1) {
                    temp_v1 = var_v0_2->next;
                    if ((*(u8 *)((u8 *)var_v0_2 + 0x48)) == 2) {
                        return 0;
                    }
                }
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