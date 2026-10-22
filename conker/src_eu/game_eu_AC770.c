#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1508039C(u8 *arg0);
#endif


void func_1507EF60(u8 *arg0, s32 *arg1, u8 arg2) {
    if ((*arg1 + 1) < 40) {
        arg0[*arg1] = arg2;
        (*arg1)++;
    }
}

extern u8 *D_80086FC4[];
extern u8 D_8009BFC0[];
void func_1507EF98(s32 arg0, s32 *arg1, s32 arg2) {
    u8 *src;
    s32 len;
    s32 v;
    src = D_80086FC4[arg2];
    len = D_8009BFC0[arg2];
    v = *arg1;
    if (v + len < 0x28) {
        bcopy(src, v + arg0, len);
        *arg1 += len;
    }
}

#ifdef NON_MATCHING
s32 func_1507F018(u8 *arg0, s32 arg1, u8 *arg2, s32 *arg3, u8 *arg4) {
    struct {
        s32 u2C;
    } sp;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_t1;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_t9;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_t0;
    s32 var_t0_2;
    s32 var_t0_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_v1_2;
    u8 *var_t1;
    u8 *var_t2;
    u8 *var_t4;
    u8 *var_t5;
    u8 temp_t2;
    u8 temp_t2_2;
    u8 *var_v0_3;

    var_v1 = 0;
    *arg3 = 0;
    var_v0 = 0;
    if (arg1 > 0) {
        do {
            temp_t1 = *arg3;
            var_a0 = 0;
            var_t0 = 0;
            var_t2 = arg2;
            if (temp_t1 > 0) {
loop_4:
                var_t0 += 1;
                if (*var_t2 == *(arg0 + var_v0)) {
                    var_a0 = 1;
                } else {
                    var_t2 += 1;
                    if (var_t0 < temp_t1) {
                        goto loop_4;
                    }
                }
            }
            if (var_a0 == 0) {
                temp_t2 = *(arg0 + var_v0);
                var_t0_2 = 0;
                var_t5 = arg4;
loop_9:
                var_t0_2 += 1;
                if (*var_t5 == temp_t2) {
                    var_a0 = 1;
                } else {
                    var_t5 += 1;
                    if (var_t0_2 != 5) {
                        goto loop_9;
                    }
                }
                if (var_a0 == 0) {
                    *(arg2 + temp_t1) = temp_t2;
                    *arg3 += 1;
                }
            }
            var_v0 += 1;
        } while (var_v0 != arg1);
    }
    var_a0_2 = 0;
    var_v0_2 = 0;
    if (*arg3 == 0) {
        var_t1 = arg4;
        do {
            temp_t2_2 = *var_t1;
            var_v0_2 += 1;
            if (temp_t2_2 != 0) {
                var_t0_3 = 0;
                if (arg1 > 0) {
                    var_t4 = arg0;
loop_20:
                    var_t0_3 += 1;
                    if (temp_t2_2 == *var_t4) {
                        *(&sp.u2C + var_a0_2) = temp_t2_2;
                        var_a0_2 += 1;
                    } else {
                        var_t4 += 1;
                        if (var_t0_3 != arg1) {
                            goto loop_20;
                        }
                    }
                }
            }
            var_t1 += 1;
        } while (var_v0_2 < 5);
        if (var_a0_2 == 0) {
            *arg2 = 0;
            *arg3 = 1;
        } else {
            var_v1_2 = var_a0_2 >> 1;
            if (var_v1_2 == 0) {
                var_v1_2 = 1;
            }
            if (var_v1_2 != 0) {
                temp_a1 = -(var_v1_2 & 3);
                var_v0_3 = var_a0_2 + &sp.u2C;
                if (temp_a1 != 0) {
                    temp_a0 = temp_a1 + var_v1_2;
                    do {
                        var_v1_2 -= 1;
                        *(arg2 + *arg3) = (*(u8 *)((u8 *)var_v0_3 + -1));
                        var_v0_3 -= 1;
                        *arg3 += 1;
                    } while (temp_a0 != var_v1_2);
                    if (var_v1_2 != 0) {
                        goto loop_33;
                    }
                } else {
                    do {
loop_33:
                        var_v1_2 -= 4;
                        *(arg2 + *arg3) = (*(u8 *)((u8 *)var_v0_3 + -1));
                        var_v0_3 -= 4;
                        temp_t8 = *arg3 + 1;
                        *arg3 = temp_t8;
                        *(arg2 + temp_t8) = (*(u8 *)((u8 *)var_v0_3 + 2));
                        temp_t9 = *arg3 + 1;
                        *arg3 = temp_t9;
                        *(arg2 + temp_t9) = (*(u8 *)((u8 *)var_v0_3 + 1));
                        temp_t7 = *arg3 + 1;
                        *arg3 = temp_t7;
                        *(arg2 + temp_t7) = (*(u8 *)((u8 *)var_v0_3 + 0));
                        *arg3 += 1;
                    } while (var_v1_2 != 0);
                }
            }
            var_v1 = 1;
        }
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F018.s")
#endif
void func_1507F238(u8 arg0, u8 *arg1) {
    func_1507F298(arg0, arg1);
    if (arg0 == 0x11) {
        func_1507F298(0x12, arg1);
    } else if (arg0 == 0x12) {
        func_1507F298(0x11, arg1);
    }
}

void func_1507F298(u8 arg0, u8 *arg1) {
    s32 i;

    for (i = 4; i > 0; i--) {
        arg1[i] = arg1[i - 1];
    }
    arg1[0] = arg0;
}

void func_1507F2D4(void)
{
  u8 *p;
  s32 type;
  p = (u8 *)D_800D154C->unk31C;
  type = p[0x64];
  p += 0x58;
  if (type == 0) {
    p[0xC] = 1;
    p[0xD] = 0;
  } else if (type == 1) {
    func_150ADA20();
    if (p[0xD] >= 3) {
      p[0xC] = 2;
      p[0xD] = 0;
    }
  } else {
    if (p[0xD] >= (func_150ADA20() & 3) + 8) {
      p[0xC] = 1;
      p[0xD] = 0;
    }
  }
}

void func_1507F380(s32 arg0, u8 *arg1) {
    s32 i;

    for (i = 4; i >= 0; i--) {
        if (arg0 == arg1[i]) {
            arg1[i] = 0;
            return;
        }
    }
}

#ifdef NON_MATCHING
s32 func_1507F8A0(s32);
s32 func_150803E0(struct127 *);
u8 func_1515999C(u8 *, s16, s16, s16, s16, s16);
u8 *func_15031C4C(u8 *, s32, s32);
extern u8 *D_80086F40[];

/* P64: the idle-chooser state of a player controller, ctl +0x58 (func_1507F2D4 / F640 / F834 / F3B0). */
typedef struct {
    /* 0x0 */ u8  active;     /* ctl +0x58 */
    /* 0x1 */ u8  delay;      /* ctl +0x59 */
    /* 0x2 */ u16 timer;      /* ctl +0x5A: frames idle */
    /* 0x4 */ u8  set;        /* ctl +0x5C: idle set (D_80086F40 index, 0 = none) */
    /* 0x5 */ u8  entry;      /* ctl +0x5D: position inside the set */
    /* 0x6 */ u8  pad6;
    /* 0x7 */ u8  recent[5];  /* ctl +0x5F: last chosen sets, newest first */
    /* 0xC */ u8  mode;       /* ctl +0x64: 0 / 1 / 2 (func_1507F2D4) */
    /* 0xD */ u8  count;      /* ctl +0x65: sets played in this mode */
} IdleState;

/* P64: picks the next idle set. Collects candidate set ids into list[40] (func_1507EF60 adds one id,
 * func_1507EF98 appends the D_80086FC4 group n): a forced set (rec +0x13A / +0x139), the D_800D18C0 & 2
 * request (3), the "bored" set 0xB / 0xC (ctl +0x66 with no character idle, 0xC after 100 frames, which also
 * resets the mode and calls func_1508039C), 0 when hurt (health < 2), held (func_1515999C) or the timer is
 * still below func_1507F8A0(mode). Otherwise func_1507F2D4 updates the mode and a group is chosen: by state /
 * character / level (D_800BE9F0) / D_800D18C0 & 1, else by the mode (0, 1, plus 3 in mode 2 after 4 sets
 * when func_150803E0). func_1507F018 filters the list against the recent sets; a random survivor becomes
 * ctl +0x5C (entry 0) and is pushed onto recent[] (func_1507F238; func_1507F380 first drops it when
 * func_1507F018 says it was already there). */
void func_1507F3B0(void) {
    struct127 *rec = D_800D154C;
    IdleState *st = (IdleState *)((u8 *)rec->unk31C + 0x58);
    struct126 *ctl;
    u8 list[40];
    u8 picked[40];
    s32 n = 0;
    s32 npicked;
    s32 group;
    s32 seen;
    s32 i;

    if (rec->unk13A != 0) {
        if (rec->pad139 <= 0x20) {
            func_1507EF60(list, &n, rec->pad139);
        }
        goto choose;
    }
    if (D_800D18C0 & 2) {
        func_1507EF60(list, &n, 3);
        D_800D18C0 = 0;
        goto choose;
    }
    ctl = rec->unk31C;
    if ((s16)ctl->unk66 != 0 && ctl->unk78 == 0) {
        s32 id = 0xB;
        if (st->timer > 100) {
            ctl->unk66 = 0;
            id = 0xC;
            st->timer = 0;
            st->mode = 0;
            func_1508039C((u8 *)D_800D154C);
        }
        func_1507EF60(list, &n, id);
        goto choose;
    }
    if (rec->health < 2
        || func_1515999C((u8 *)&D_800CC2D0[D_800C3E78], 0, 0, -1, -1, -1) != 0
        || st->timer < func_1507F8A0(st->mode)) {
        func_1507EF60(list, &n, 0);
        goto choose;
    }

    func_1507F2D4();
    rec = D_800D154C;
    group = -1;
    if (rec->unk2F8 & 0x200) {
        group = 2;
    } else if (rec->unk31C->unk78 == 9) {
        group = 5;
    } else if (rec->unk31C->unk78 == 0x23) {
        group = 9;
    } else if (rec->unk31C->unk78 == 0x16) {
        group = 0xA;
    } else if (func_15031C4C((u8 *)rec, 0x17, 0) != NULL) {
        group = 6;
    } else if (D_800BE9F0 == 0x31) {
        group = (D_800D18C0 & 4) ? 8 : 7;
    } else if (D_800D154C->id == 0x96) {
        group = 2;
    } else {
        switch (D_800BE9F0) {
            case 0x0E: case 0x10: case 0x1B: case 0x1C: case 0x1E: case 0x23:
            case 0x26: case 0x28: case 0x2F: case 0x36: case 0x3A:
                group = 2;
                break;
            default:
                if (D_800D18C0 != 0) {
                    if (D_800D18C0 & 1) {
                        group = 4;
                    }
                    D_800D18C0 = 0;
                }
                break;
        }
    }
    if (group != -1) {
        func_1507EF98((s32)list, &n, group);
    } else if (st->mode == 1) {
        func_1507EF98((s32)list, &n, 0);
    } else {
        func_1507EF98((s32)list, &n, 1);
        if (st->mode == 2 && st->count >= 4 && func_150803E0(D_800D154C) != 0) {
            func_1507EF98((s32)list, &n, 3);
        }
    }

choose:
    seen = func_1507F018(list, n, picked, &npicked, st->recent);
    i = 0;
    if (npicked >= 2) {
        i = (u32)func_150ADA20() % (u32)npicked;
    }
    st->entry = 0;
    st->count++;
    st->set = picked[i];
    if (st->mode != 0) {
        st->timer = 0;
    }
    if (seen != 0) {
        func_1507F380(st->set, st->recent);
    }
    func_1507F238(st->set, st->recent);
}


/* P64: advances the current idle set (ctl +0x5C) to its next entry. Returns 1 when a new set must be chosen
 * (no set, or the set's list ends with 0: then set and entry are cleared), else 0. */
s32 func_1507F834(void) {
    IdleState *st = (IdleState *)((u8 *)D_800D154C->unk31C + 0x58);

    if (st->set == 0) {
        return 1;
    }
    st->entry++;
    if (D_80086F40[st->set][st->entry] == 0) {
        st->set = 0;
        st->entry = 0;
        return 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F3B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F834.s")
#endif

s32 func_1507F8A0(s32 arg0) {
    s32 pad;
    s32 var_v1;
    u32 var_a0;

    if (arg0 == 0) {
        var_v1 = 0x96;
        var_a0 = 0x32;
        goto block_7;
    }
    if (D_800BE9F0 == 0x31) {
        return 0;
    }
    var_v1 = 0;
    if (arg0 == 1) {
        var_v1 = 0x32;
        var_a0 = 0x32;
    } else {
        var_a0 = 0x1E;
    }
block_7:
    return (func_150ADA20() % var_a0) + var_v1;
}

extern u8 D_800B89C4[];

void func_1507F92C(struct127 *arg0) {
    s32 v;

    if (arg0->unk13C >= 0x64) {
        switch (D_800B89C4[arg0->unk13C * 0x32C]) {
        case 0x57:
            v = 0x115;
            break;
        case 0x8C:
            v = 0x1A5;
            break;
        case 0xA8:
        case 0xA9:
            v = 0x1AF;
            break;
        case 0x89:
        case 0xBA:
            v = 0x1FA;
            break;
        default:
            v = 0xD8;
            break;
        }
        func_1505E650(arg0, v, 1.0f, 4.0f, 0.0f, 0.0f, 0);
    } else {
        func_1505E650(arg0, 0xF, 1.0f, 3.0f, 0.0f, 0.0f, 0);
    }
}

#ifdef NON_MATCHING
s32 func_1507CD64(struct127 *, s32);
void func_1507F3B0(void);
s32 func_1507F834(void);
extern u8 *D_80086F40[];
extern u8 D_8009BC80[][8];

/* P60: idle animation of the current player record D_800D154C (D_800C3E78 = its index, players only; not when
 * D_800C35EA == 1 or the record's +5 is 4). Marks the controller's idle state (ctl +0x58 = 1); while the idle
 * delay ctl +0x59 runs it counts down. Out of health: func_1507CD64(rec, 0). Else the run / jump locks and the
 * turn are reset and an idle animation is chosen: ctl +0x17 (random 0x4F / 0x4D), a per-character idle
 * (ctl +0x78, below), carried items / states (ctl +0x1B2, +0x4E, +0x8, +0x1A, +0x32), held by another record
 * (func_1507F92C), the cutscene idle 0xF (D_800BE616), else the idle sets D_80086F40 / D_8009BC80 (u16 anim,
 * speed / 100, blend / 10, delay) chosen by ctl +0x5C / +0x5D after func_1507F834 / func_1507F3B0. */
void func_1507F640(void) {
    struct127 *rec;
    struct126 *ctl;
    u8 *e;
    s32 anim;
    s32 ch;
    f32 speed = 1.0f;
    f32 blend = 4.0f;

    if (D_800C35EA == 1) {
        return;
    }
    rec = D_800D154C;
    if (rec->unk5 == 4 || D_800C3E78 >= D_8008FD8C) {
        return;
    }
    ctl = rec->unk31C;
    ctl->unk58 = 1;
    if ((D_800D154C->unk2F8 & 0x20) || D_800D154C->unk31C->unk120 != 0) {
        return;
    }
    if (ctl->unk59 > 0) {
        ctl->unk59--;
        ctl->unk5A = 0;
        return;
    }
    rec = D_800D154C;
    if (rec->health == 0) {
        func_1507CD64(rec, 0);
        return;
    }
    if (rec->disable_run >= 0xFA) {
        D_800D154C->disable_run = 0;
    }
    if (D_800D154C->disable_jump == 0xFF) {
        D_800D154C->disable_jump = 0;
    }
    D_800D154C->unk83 = 0;
    D_800D154C->unkAA = 0;
    D_800D154C->unk76 = D_800D154C->unk7A;
    D_800D154C->unk100 &= ~1;
    D_800D154C->unk2F8 &= ~7;

    rec = D_800D154C;
    ctl = rec->unk31C;
    if (ctl->pad17[0] != 0) {
        anim = (func_150ADA20() & 3) ? 0x4D : 0x4F;
        func_1505E650(D_800D154C, anim, 1.0f, 4.0f, 0.0f, 0.0f, 0);
        return;
    }
    ch = ctl->unk78;
    switch (ch) {
        case 0x02: case 0x13: anim = 0x3E; break;
        case 0x38: anim = 0x1DF; break;
        case 0x39: anim = 0x1EA; break;
        case 0x37: anim = 0x1F3; break;
        case 0x3B: anim = 0x221; break;
        case 0x26: anim = 0x177; break;
        case 0x3A: anim = 0x1FA; break;
        case 0x25: anim = 0xD8; break;
        case 0x2D: case 0x2E: anim = 0x1AF; break;
        case 0x15: anim = 0xE2; break;
        case 0x0C: anim = 0xBD; break;
        case 0x14: case 0x3F: anim = 0xF9; break;
        case 0x22: anim = 0x15A; break;
        case 0x21: anim = 0x122; break;
        case 0x19: case 0x40: anim = 0x10F; break;
        case 0x12: anim = 0x10A; break;
        case 0x18: case 0x41: anim = 0xC5; break;
        case 0x24: anim = 0x153; break;
        default: anim = -1; break;
    }
    if (ctl->unk1B2 != 0 && ch == 0x16) {
        anim = 0x2C5;
    }
    if (ctl->unk4E == 2) {
        anim = 5;
    }
    if (ctl->unk8 != 0) {
        blend = 8.0f;
        speed = 1.5f;
        anim = 0xAB;
    }
    if (ctl->pad17[3] != 0) {
        anim = 0x63;
        blend = 8.0f;
    }
    if (ctl->unk32 & 2) {
        anim = 0x6B;
        blend = 8.0f;
    } else if (ctl->unk32 & 1) {
        anim = 0xAF;
        blend = 8.0f;
    }
    if (anim != -1) {
        func_1505E650(rec, anim, speed, blend, 0.0f, 0.0f, 0);
        return;
    }
    if (rec->unk13C >= 100) {
        func_1507F92C(rec);
        return;
    }
    if (D_800BE616 != 0 && ch != 0x23 && ch != 0x16 && ch != 9) {
        func_1505E650(rec, 0xF, 1.0f, 3.0f, 0.0f, 0.0f, 0);
        return;
    }

    if (func_1507F834() != 0) {
        rec = D_800D154C;
        if (rec->unk31C->unk198 != 0 && ctl->unk5C == 0) {
            switch (rec->unk31C->unk78) {
                case 0x03: anim = 0x2C; break;
                case 0x09: anim = 0x7F; break;
                case 0x16: anim = 0xBD; break;
                case 0x23: anim = 0x165; break;
                default:
                    func_1507F92C(rec);
                    return;
            }
            func_1505E650(rec, anim, 1.0f, 4.0f, 0.0f, 0.0f, 0);
            return;
        }
        func_1507F3B0();
    }

    e = D_8009BC80[D_80086F40[ctl->unk5C][ctl->unk5D]];
    if (D_80086F40[ctl->unk5C][ctl->unk5D] == 0) {
        rec = D_800D154C;
        switch (rec->unk31C->unk78) {
            case 0x09: anim = 0x3A; break;
            case 0x23: anim = 0x42; break;
            case 0x16: anim = 0x44; break;
            default:
                if (rec->health == 1) {
                    anim = 0xE;
                } else if (rec->unk31C->pad17[3] != 0) {
                    anim = 0x25;
                }
                break;
        }
        if (anim != -1) {
            e = D_8009BC80[anim];
        }
    }
    func_1505E650(D_800D154C, *(u16 *) e, e[2] * 0.01f, e[3] * 0.1f, 0.0f, 0.0f, 0);
    ctl->unk58 = 1;
    ctl->unk59 = e[4];
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F640.s")
#endif

#ifdef NON_MATCHING
void func_1000D96C(s32, s32, s32);
void func_1000DE1C(s32, s32);
void func_1000E7A0(u32, s32);
void func_1000E8C4(s32);
void func_100109D0(struct127 *arg0);
extern u8 *D_80086F40[];
extern u8 D_8009BC80[][8];
extern s32 D_80041C50[];
extern u8 D_80041D40;
extern s32 D_800D1CE4;

/* Per-frame surface effects of the record's current floor material (ctl = rec->unk31C + 0x58: +4 material set,
 * +5 index, +6 the flags applied last frame). Flags (D_8009BC80[mat][6]): 0x10 scales the model's +0x08 by the
 * D_80041C50 level, and on change 1 = record flag unk2F8 bit 0, 2 = func_1000E7A0 / func_1000E8C4, 4 = ambient
 * loop 0x15 / 0x16 (D_800D1CE4) start / stop, 8 cleared = func_100109D0. */
void func_1508000C(struct127 *rec) {
    u8 *ctl = (u8 *)rec->unk31C + 0x58;
    u8 set = ctl[4];
    u8 flags = 0;
    u8 old;
    u8 changed, gained, lost;
    f32 k;

    if (set != 0) {
        flags = D_8009BC80[D_80086F40[set][ctl[5]]][6];
    }
    if (flags & 0x10) {
        k = ((f32)D_80041C50[D_80041D40 * 16] - 5462.0f) * 1.2f;
        if (k < 0.0f) {
            k = 0.0f;
        }
        rec->unk2D0->unk8 = ((rec->unk2D0->unk18 - 1.0f) * (32768.0f - k)) / 32768.0f;
    }
    old = ctl[6];
    if (flags == old) {
        return;
    }
    changed = flags ^ old;
    gained = changed & flags;
    lost = changed & old;
    if (gained & 1) {
        rec->unk2F8 |= 1;
    } else if (lost & 1) {
        rec->unk2F8 &= ~1;
    }
    if (gained & 2) {
        func_1000E7A0(1, 0);
    } else if (lost & 2) {
        func_1000E8C4(1);
    }
    if (gained & 4) {
        if (D_800D1CE4 == 0) {
            D_800D1CE4 = 0x15;
        } else if (D_800D1CE4++ == 0x17) { /* 0x15 -> 0x16 -> 0x17 -> 0x15 */
            D_800D1CE4 = 0x15;
        }
        func_1000D96C(D_800D1CE4, 0, 0);
    } else if (lost & 4) {
        func_1000DE1C(D_800D1CE4, 0);
    }
    if (lost & 8) {
        func_100109D0(rec);
    }
    ctl[6] = flags;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1508000C.s")
#endif
#ifdef NON_MATCHING
void func_1508000C(struct127 *);

void func_150802A8(struct127 *arg0) {
    s16 temp_v0_2;
    struct126 *temp_a1;
    struct126 *temp_a1_3;
    u16 temp_a1_2;
    u8 *temp_v0;
    u8 temp_v1;

    temp_a1 = arg0->unk31C;
    if ((temp_a1 != NULL) && (arg0->unk127 != 0xFF)) {
        temp_v1 = arg0->unk13A;
        temp_v0 = &temp_a1->unk58;
        if (temp_v1 != 0) {
            arg0->unk13A = temp_v1 - 1;
        }
        if (((*(u8 *)((u8 *)temp_v0 + 0)) == 1) && (D_800C35EA != 1)) {
            temp_a1_2 = (*(u16 *)((u8 *)temp_v0 + 2));
            if ((s32) temp_a1_2 < (0xFFFF - D_800BE9E4)) {
                (*(u16 *)((u8 *)temp_v0 + 2)) = (u16) (temp_a1_2 + D_800BE9E4);
            }
        } else {
            (*(u16 *)((u8 *)temp_v0 + 2)) = 0U;
            (*(s8 *)((u8 *)temp_v0 + 4)) = 0;
            (*(s8 *)((u8 *)temp_v0 + 5)) = 0;
            (*(s8 *)((u8 *)temp_v0 + 0xC)) = 0;
            (*(s8 *)((u8 *)temp_v0 + 0xD)) = 0;
        }
        temp_a1_3 = arg0->unk31C;
        temp_v0_2 = (s16) temp_a1_3->unk66;
        if (temp_v0_2 != 0) {
            if (D_800BE9E4 < temp_v0_2) {
                temp_a1_3->unk66 = temp_v0_2 - D_800BE9E4;
            } else {
                func_1508039C((u8 *) arg0);
                arg0->unk31C->unk66 = 0;
            }
        }
        func_1508000C(arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_150802A8.s")
#endif
void func_1508039C(u8 *arg0)
{
  u8 *sp20[2];
  s32 sp1C;
  sp1C = 1;
  sp20[0] = arg0;
 if (0) { }
  if (sp1C)
  {
    sp1C = (s32) sp20;
    ((u8 *) sp20)[4] = arg0[0x3B];
    func_151920FC(sp1C, 0xD);
  }
  func_151494E0(0xFFFFFFFFFFFFFFFF & sp1C, 0xD);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_150803E0.s")
