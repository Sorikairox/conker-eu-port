#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15080628(void);
#endif
// hoisted forward declaration(s) for func_1501E7A8
s32 func_1507EE9C(struct127 *);


#ifdef NON_MATCHING
/* End of frame (P13, hand C): closes the display list (rolled back to the per-buffer reserve D_800BE9D8 when it
 * overflowed, cut at 0x190 commands before the end otherwise), fills the gfx OSScTask D_800BEEF8[idx] (0x60
 * bytes), sends it to the scheduler's gfx queue and, when arg1 != 0, flips the DL buffer index D_800BE9C0.
 * Names are the asm's (several are US names remapped by undefined_syms.eu.txt). */
extern s32 *D_800BEEF4;           /* the task being filled */
extern u8 D_800BEEF8[];           /* OSScTask[2], 0x60 each */
extern u8 D_10029400[];           /* rspboot */
extern u8 D_100294D0[];
extern u8 D_800BEFC0;
extern u8 D_800BEA37;
extern u8 D_8003A948[];           /* yield buffer */
extern OSMesgQueue D_800BEE30;    /* main-loop queue */
extern u8 D_800BEE88[];           /* done messages, 0x20 each */
extern OSMesgQueue D_8003B548;    /* scheduler gfx queue */
extern s16 D_800BEEC8;
extern s32 D_800BEFD0;            /* ucode text / data pairs */
extern s32 D_800C1480;
extern u8 *D_800BEFBC;
extern u8 *D_800BEEF0;
void func_1501A39C(void);
void func_1501CC1C(void);

void func_eu_1501C860(s32 arg0, s32 arg1) {
    s32 *task;
    s32 cap;
    s32 n;
    s32 base;
    s32 *g;

    task = (s32 *)(D_800BEEF8 + D_800BE9C0 * 0x60);
    D_800BEEF4 = task;
    task[0] = 0;
    cap = ((s32)D_800BEDE8[1] - (s32)D_800BEDE8[0]) >> 3;
    base = (s32)D_800BEDE8[D_800BE9C0];
    n = (D_800BE9D0 - base) >> 3;
    if (n < 0 || cap < n) {
        func_1501A39C();
        D_800BE9D0 = D_800BE9D8[D_800BE9C0];
        g = (s32 *)D_800BE9D0; D_800BE9D0 += 8; g[1] = 0; g[0] = 0xE9000000;
        g = (s32 *)D_800BE9D0; D_800BE9D0 += 8; g[1] = 0; g[0] = 0xDF000000;
        base = (s32)D_800BEDE8[D_800BE9C0];
        n = (D_800BE9D0 - base) >> 3;
    }
    if (n < 0 || cap - 0x190 < n) {
        D_800BE9D0 = base + (cap - 0x190) * 8;
        g = (s32 *)D_800BE9D0; D_800BE9D0 += 8; g[1] = 0; g[0] = 0xE9000000;
        g = (s32 *)D_800BE9D0; D_800BE9D0 += 8; g[1] = 0; g[0] = 0xDF000000;
        base = (s32)D_800BEDE8[D_800BE9C0];
    }
    D_800BEEF4[0x48 / 4] = base;
    D_800BEEF4[0x4C / 4] = ((D_800BE9D0 - (s32)D_800BEDE8[D_800BE9C0]) >> 3) << 3;
    func_1501CC1C();
    D_800BEEF4[0x18 / 4] = 1;                                  /* M_GFXTASK */
    D_800BEEF4[0x1C / 4] = 4;                                  /* OS_TASK_LOADABLE */
    D_800BEEF4[0x20 / 4] = (s32)D_10029400;
    D_800BEEF4[0x24 / 4] = D_100294D0 - D_10029400;
    if (D_800BEFC0 != 0) {
        D_800BEEF4[0x28 / 4] = (s32)&D_800C1480;
        D_800BEEF4[0x30 / 4] = (s32)D_800BEFBC;
    } else {
        D_800BEEF4[0x28 / 4] = (s32)&D_800BEFD0;
        D_800BEEF4[0x30 / 4] = (s32)D_800BEEF0;
    }
    D_800BEEF4[0x34 / 4] = 0x800;
    D_800BEEF4[0x38 / 4] = (s32)&D_800CC230;
    D_800BEEF4[0x3C / 4] = 0x400;
    D_800BEEF4[0x40 / 4] = D_80038090;
    D_800BEEF4[0x44 / 4] = D_80038094;
    D_800BEEF4[0x50 / 4] = (s32)D_8003A948;
    D_800BEEF4[0x54 / 4] = 0xC00;
    D_800BEEF4[0x0C / 4] = 0x23;
    if (arg1 != 0) {
        D_800BEEF4[0x0C / 4] |= 0x40;
    }
    if (D_800BEA37 != 0) {
        D_800BEEF4[0x0C / 4] |= (D_80082FA0 + 1) << 16;
        D_800BEA37 = 0;
    }
    D_800BEEF4[0x58 / 4] = (s32)&D_800BEE30;
    D_800BEEF4[0x5C / 4] = (s32)(D_800BEE88 + D_800BE9C0 * 0x20);
    D_800BEEF4[0x10 / 4] = D_8002AAE8[D_800BE9C0];
    osWritebackDCacheAll();
    osSendMesg(&D_8003B548, (OSMesg)D_800BEEF4, OS_MESG_BLOCK);
    if (arg1 != 0) {
        D_800BE9C0 ^= 1;
    }
    D_800BEEC8++;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_eu_1501C860.s")
#endif
#ifdef NON_MATCHING
extern s32 D_2D810;
extern s8 D_80084400;
extern s8 D_80084404;
extern s32 D_80084408;
extern u8 *D_800BEEF0;
extern s32 D_800BEFB8;
extern u8 *D_800BEFBC;
extern s32 D_800BEFD0;
extern s32 D_800C1480;

void func_1501CC1C(void) {
    s32 sp2C;
    s32 sp28;
    u8 *sp20;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_t1;
    u8 var_t0;
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_t1 = 4;
    var_t0 = D_800B0DF0->pad2A[1];
    if ((s32) var_t0 >= 2) {
        var_t0 -= 2;
        var_t1 = 0;
    }
    if (D_800BEFB8 == 1) {
        var_t0 += 2;
    }
    temp_v0 = ((s32 *)((u8 *)&D_80084408 + (var_t0 * 0x10)));
    if ((var_t0 != D_80084400) || (var_t1 != D_80084404)) {
        temp_v1 = (*(s32 *)((u8 *)temp_v0 + 0));
        sp20 = temp_v0;
        sp2C = (s32) var_t0;
        sp28 = var_t1;
        func_10004514((s32) (((s32 *)((u8 *)&D_2D810 + temp_v1))), &D_800C1480, (*(s32 *)((u8 *)temp_v0 + 4)) - temp_v1, 1);
        temp_v1_2 = (*(s32 *)((u8 *)temp_v0 + 8));
        temp_a1 = ((s32 *)((u8 *)&D_800C1480 + ((*(s32 *)((u8 *)temp_v0 + 4)) - (*(s32 *)((u8 *)temp_v0 + 0)))));
        D_800BEFBC = temp_a1;
        func_10004514((s32) (((s32 *)((u8 *)&D_2D810 + temp_v1_2))), temp_a1, (*(s32 *)((u8 *)temp_v0 + 0xC)) - temp_v1_2, 1);
        D_80084400 = (s8) var_t0;
        temp_v0_2 = ((s32 *)((u8 *)&D_80084408 + ((var_t0 + var_t1) * 0x10)));
        D_80084404 = (s8) var_t1;
        temp_v1_3 = (*(s32 *)((u8 *)temp_v0_2 + 0));
        sp20 = temp_v0_2;
        func_10004514((s32) (((s32 *)((u8 *)&D_2D810 + temp_v1_3))), &D_800BEFD0, (*(s32 *)((u8 *)temp_v0_2 + 4)) - temp_v1_3, 1);
        temp_a1_2 = ((s32 *)((u8 *)&D_800BEFD0 + ((*(s32 *)((u8 *)temp_v0_2 + 4)) - (*(s32 *)((u8 *)temp_v0_2 + 0)))));
        D_800BEEF0 = temp_a1_2;
        temp_v1_4 = (*(s32 *)((u8 *)temp_v0_2 + 8));
        func_10004514((s32) (((s32 *)((u8 *)&D_2D810 + temp_v1_4))), temp_a1_2, (*(s32 *)((u8 *)temp_v0_2 + 0xC)) - temp_v1_4, 1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CC1C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CDA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CE34.s")

s32 func_1501D064(s32 arg0) {
    s32 sum = 0;
    s32 i;

    for (i = 0; i < D_800C3A5A[arg0]; i++) {
        sum += D_800C39F8[arg0][i];
    }
    return sum;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501D044.s")

s32 func_1502B6BC(s32 *, s32, s32 *, s32, s32, s32, s32);
extern s32 D_800C3A88;

s32 func_1501D240(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp34;
    s32 sp30;
    s32 temp_v0;

    temp_v0 = func_1502B6BC(&sp30, 0, &sp34, 3, 6, arg0, arg1);
    if (temp_v0 != 0) {
        (&D_800C3A88)[arg2] = temp_v0;
    } else {
        (&D_800C3A88)[arg2] = 0;
    }
    return temp_v0;
}

void func_1501D2C4(s32 arg0, s32 arg1) {
    if (D_800C3670 == 0) {
        D_800C3A60[arg0] |= 1ULL << arg1;
    }
}

s32 func_1501D330(s32 arg0, s32 arg1) {
    u64 bit;
    if (D_800C3670 != 0) {
        return 1;
    }
    if ((D_800C3A60[arg0] & (1ULL << arg1)) != 0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501D348.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501DB18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501DE84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501DF70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E0C8.s")

s32 func_1000E17C(void);
void func_1501DF70(void);
s32 func_1501E0C8(s32, u8 *);
s32 func_151F2CDC(void);
extern s8 D_80090124;
extern s32 D_800C39D0;
extern u8 D_800C40A9;
extern s32 D_eu_800C3A60;

void func_1501E220(s32 arg0) {
    if (D_800C3C88 == 0) {
        if (((&D_800C35EA)[arg0] == 1) && (func_1501E0C8(arg0, &D_800C3C88) != 0)) {
            D_80090124 = 0;
            if (((*(&D_eu_800C3A60 + arg0) - *(&D_800C39D0 + arg0)) >= 0x4C)) {
                D_800C3C88 = 1;
                D_800C40A9 = 0x19;
                func_1517F3B0(0, 0, 0, 0x19, 1, 0);
                func_1000E17C();
                if ((func_151F2CDC() == 1) || (func_151F2CDC() == 2)) {
                    func_151F2D6C(0, 0x2B02);
                }
            }
        }
    } else if (D_800C3C88 == 1) {
        if (D_800BEA08 < (s32) D_800C40A9) {
            D_800C40A9 -= D_800BEA08;
            return;
        }
        D_800C40A9 = 0;
        D_800C3C88 = 2;
        func_1501DF70();
        D_800C3C88 = 0;
    }
}

#ifdef NON_MATCHING
void func_1501E46C(s32);
s32 func_1501E888(s32, s32);
s32 func_1501ECA4(s32);
s32 func_15020F6C(s32);
void func_1502457C(s32, s32);
extern u8 D_800C40AC;

void func_1501E364(s32 arg0) {
    s32 var_s1;
    u8 *temp_s0;

    var_s1 = arg0;
loop_1:
    temp_s0 = &(&D_800C35EA)[var_s1];
    if ((*temp_s0 == 1) && ((&D_800C39D0)[var_s1] >= (&D_eu_800C3A60)[var_s1])) {
        if (D_800C40AC == 0) {
            func_1501E888(0, var_s1);
            if (*temp_s0 == 1) {
                var_s1 = 0;
                func_1501E46C(0);
                func_1502457C(1, 0);
                func_1501ECA4(0);
                func_1502457C(0, 0);
                func_15020F6C(0);
                goto loop_1;
            }
        } else {
            D_800C40AC = 2;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E364.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800C39D8[];
extern u8 D_800C39E0[];
extern u16 D_800C40AE;
extern u8 D_eu_800C3E78;

/* Per-player counter step (P15, hand C from the asm): remembers the previous value D_800C39D8[i] of
 * D_800C39D0[i], and for an active player (D_800C35EA[i] == 1) advances it by D_800BEA08 (player 0
 * only when D_800BEAC0 == 0), clamped to D_eu_800C3A60[i]. */
void func_1501E46C(s32 i) {
    s32 *cur = &(&D_800C39D0)[i];
    s32 lim;

    if (D_eu_800C3E78 != 0) {
        D_eu_800C3E78--;
    }
    D_800C39D8[i] = *cur;
    if ((&D_800C35EA)[i] != 1) {
        return;
    }
    func_1501E220(i);
    if (i != 0 || D_800BEAC0 == 0) {
        *cur += D_800BEA08;
    }
    if (D_800C39E0[i] == 0 && D_800C40AE == D_800C39D8[i] && D_800C40AE != *cur) {
        D_800C39D8[i] = -1;
    }
    if (func_151F2CDC() == 1) {
        func_15080628();
    }
    lim = (&D_eu_800C3A60)[i];
    if (*cur >= lim) {
        *cur = lim;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E46C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E5AC.s")

extern u8 *D_800C3A10[];

void func_1501E7A8(s32 arg0)
{
  s32 var_s0;
  s32 n;
  struct127 *e;
  u8 *cnt;
  u8 **tbl;
  u8 *p;
  cnt = &D_800C3A5A[arg0];
  n = *cnt;
  if (n > 0)
  {
    tbl = &D_800C3A10[arg0];
    var_s0 = 0;
    do
    {
      p = (*tbl) + var_s0;
      if ((*((u16 *) p)) == 2)
      {
        e = func_15083E90(p[2]);
        if (e == 0)
        {
          s32 blk_t; // fakematch: block-local decl (shape D)
          n = *cnt;
        }
        else
        {
          if ((*((u8 *) (((u8 *) e) + 0x6C))) >= 0xA)
          {
            *((u8 *) (((u8 *) e) + 0x6C)) = 0;
            *((s8 *) (((u8 *) e) + 0x6A)) = 0;
          }
          if ((*((u8 *) (((u8 *) e) + 0x6D))) >= 0xA)
          {
            *((u8 *) (((u8 *) e) + 0x6D)) = 0;
            *((s8 *) (((u8 *) e) + 0x6B)) = 0;
          }
          func_1507EE9C(e);
          n = *cnt;
        }
      }
      if (0) // fakematch: permuter empty if
      {
      }
    }
    while ((var_s0 += 8) < (n * 8));
  }
  tbl++; // fakematch: permuter tbl++/tbl--
  tbl--;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E888.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501EA84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501ECA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501F7D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501FD34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501FF10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020090.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020430.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020920.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020F6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15021834.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15021E60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150220CC.s")

void func_15022238(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    D_800C39B4 = arg3;
    D_800C39AC[0] = arg0;
    D_800C39AC[1] = arg1;
    D_800C39AC[2] = arg2;
    D_800C3663 = 1;
}

void func_15022290(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    D_800C39C0 = arg3;
    D_800C39B8[0] = arg0;
    D_800C39B8[1] = arg1;
    D_800C39B8[2] = arg2;
}

void func_150222DC(s32 arg0) {
    D_800C3930[arg0] = 0;
}

void func_150222F0(s32 arg0) {
    D_800C396A[arg0] = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022304.s")

extern u16 *D_800C39E8[];
extern u8 *D_800C3A10[];
void func_15022388(s32 arg0, s32 arg1) {
    struct127 *obj;
    u8 *e;
    if (D_800C39E8[arg1][arg0] != 0) {
        e = D_800C3A10[arg1] + arg0 * 8;
        if (*(u16 *)e == 2) {
            obj = func_15083E90(e[2]);
            if (obj != NULL) {
                *((u8 *)obj + 0x6C) = 0;
                *((u8 *)obj + 0x6D) = 0;
                *((u8 *)obj + 0x6A) = 0;
                *((u8 *)obj + 0x6B) = 0;
                *(s16 *)((u8 *)obj + 0x282) = 0;
                *(s16 *)((u8 *)obj + 0x27A) = 0;
                *(s16 *)((u8 *)obj + 0x27C) = 0;
                *(s16 *)((u8 *)obj + 0x27E) = 0;
                *(s16 *)((u8 *)obj + 0x280) = 0;
                func_1507E7E4(obj, 0, 3, 0xFFFF, 0xA);
                *((u8 *)obj + 0x71) = 0;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022440.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150225D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150226E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022764.s")

s32 func_15022764(s32, s32);

void func_150227FC(s32 arg0) {
    s32 var_s0;
    u8 *temp_s1;

    temp_s1 = &D_800C3A5A[arg0];
    var_s0 = 0;
    if ((s32) *temp_s1 > 0) {
        do {
            func_15022764(var_s0, arg0);
            var_s0 += 1;
        } while (var_s0 < (s32) *temp_s1);
    }
}

u8 *func_151149AC(u8);
extern u8 D_800C3970[];
void func_15022864(s32 arg0)
{
  s32 i;
  u8 *cnt;
  u8 *p;
  cnt = &D_800C396A[arg0];
 do { i = 0; if ((*cnt) > 0) { p = D_800C3970 + (arg0 * 0x1E); do { func_151149AC(*p)[0x6E] = 1; i += 1; p += 1; } while (i < (*cnt)); } } while (0);
}

void func_15022388(s32, s32);
s32 func_15022440(s32, s32);

void func_150228F0(s32 arg0) {
    s32 var_s0;
    u8 *temp_s2;

    if ((&D_800C35EA)[arg0] == 1) {
        D_800C3638 = 0;
        temp_s2 = &D_800C3A5A[arg0];
        var_s0 = 0;
        if ((s32) *temp_s2 > 0) {
            do {
                func_15022440(var_s0, arg0);
                func_15022388(var_s0, arg0);
                var_s0 += 1;
            } while (var_s0 < (s32) *temp_s2);
        }
        D_800C3638 = 1;
    }
}

extern u8 D_800C3938[][0x19];

void func_1502298C(s32 arg0)
{
  s32 i;
  u8 *new_var; // fakematch: permuter temp
  s32 n;
  u8 *cnt = &D_800C3930[arg0];
  u8 *p;
  struct127 *e;
 i = 0; n = *cnt; if (n > 0) { p = D_800C3938[arg0]; do {
      e = &D_800CC2D0[*p];
      if (e->interaction_state)
      {
        new_var = &(*cnt);
        func_15060F28(e, 0);
        n = *new_var;
      }
      i++;
      p++;
    }
    while (i < n);
  }
}

void func_15022A40(s32 *arg0) {
    s32 v = arg0[0];

    if ((v == 27) || (v == 4)) {
        if (D_800863B4[v] != NULL) {
            D_800863B4[v]();
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022A8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022BB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022C4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502330C.s")

void func_15023464(void) {
    bzero(D_800C3CA0, 0xA8);
}

void func_1502348C(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if ((s16)D_800C3CA0[i].unk0 != 0) {
            func_1516D850(*(s32 *)((u8 *)&D_800C3CA0[i] + 0x34));
            *(s32 *)((u8 *)&D_800C3CA0[i] + 0x34) = 0;
            D_800C3CA0[i].unk0 = 0;
        }
    }
}

void func_150234E8(s16 *arg0, s32 arg1) {
    if (arg1 != 0) {
        func_1516D850(*(s32 *)((u8 *)arg0 + 0x34));
        *(s32 *)((u8 *)arg0 + 0x34) = 0;
    } else if (*(u8 *)((u8 *)arg0 + 0xC) != 0) {
        func_1516D898(*(s32 *)((u8 *)arg0 + 0x34));
    } else {
        *(s32 *)((u8 *)arg0 + 0x34) = 0;
    }
    *(s16 *)((u8 *)arg0) = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502354C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15023684.s")

#ifdef NON_MATCHING
s32 func_15021834(s32 *, s32, s32);
s32 func_15022A8C(s32 *);
s32 func_1504A730();
s32 func_15061B4C();
s32 func_1507EB1C(s32 *);
void func_150802A8(s32 *);
extern u8 D_800C3A78;

void func_1502378C(void) {
    struct127 *var_s0;
    u8 var_s1;

    var_s0 = D_800CC2D0;
    var_s1 = 0;
    if (D_800C3A78 != 0) {
        func_1504A730();
        return;
    }
    do {
        if (var_s0->interaction_state != 0) {
            D_800C3E78 = var_s1;
            func_15022A40(&var_s0->interaction_state);
            func_1507EB1C(&var_s0->interaction_state);
            if (func_15022A8C(&var_s0->interaction_state) != 0) {
                func_15021834(&var_s0->interaction_state, 0, -1);
                func_150627D4(var_s0);
                func_150802A8(&var_s0->interaction_state);
                var_s0->unk2FF = 1;
            }
        }
        var_s1 += 1;
        var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
    } while (var_s1 != 0x19);
    func_15061B4C();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502378C.s")
#endif