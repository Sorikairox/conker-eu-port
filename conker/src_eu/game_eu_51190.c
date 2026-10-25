#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15024438(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
/* one 8-byte entry of a player's D_800C3A10 table: what track arg1 refers to (scene chunk table, func_1501D348) */
typedef struct {
    u16 kind;   /* 1: camera track, 2: object func_15083E90(id), 3: world record func_151149AC(id), else none */
    u8  id;
    u8  pad3[5];
} struct_1502AB94_ref;

extern struct_1502AB94_ref *D_800C3A10[];   /* per player */
#endif


void func_15023980(void) {
}

#ifdef NON_MATCHING
extern s32 D_800C39D0;
extern s32 D_eu_800C3A60;
extern u8 D_800C40A9;

/* the 0x10-byte record a scene positional sound (handler C types 6 / 0xA) passes to func_1000FA64 */
typedef struct {
    u8 player;
    u8 track;
    u8 untilEnd;  /* stop when the scene time reaches its end */
    u8 pad3;
    u16 left;     /* frames left (0xFFFF = endless) */
    u16 total;    /* frames at the start */
    u16 fadeIn;   /* fade-in length (frames) */
    u16 fadeOut;  /* fade-out length: the last fadeOut frames */
    u16 volume;
    u8 epoch;     /* D_800C3A08[player] when started */
    u8 padF;
} SceneSfx;

// scene_sfx_update: positional sound callback (SfxEnt +0x14, game init_EB00): follows the track's position (D_800C3958 record:
// x, y + 0x38, z) while the player's scene epoch is unchanged, counts the frames left down, sets *vol from the
// record's volume with the fade-in / fade-out ramps and the cutscene volume D_800C40A9 / 25 while skipping
// (D_800C3C88). Stops (vol 0, *stop = 0, record freed, returns 1) at the end, on a stop request (flag 0x80) or when
// the scene ended; else returns 0.
s32 func_15023988(u8 *e, s32 *a1, u32 *vol, s32 *a3, s32 *a4, s32 *a5, u16 *stop) {
    SceneSfx *r;
    u8 *base;
    u16 left;

    r = *(SceneSfx **) (e + 0x18);
    if ((r->untilEnd != 0 && (&D_800C39D0)[r->player] >= (&D_eu_800C3A60)[r->player]) || (*(s32 *) (e + 0x10) & 0x80)) {
        goto stop;
    }
    if (r->epoch == (&D_800C3A08)[r->player] && (&D_800C3958)[r->player] != NULL) {
        *(s16 *) (e + 2) = *(f32 *) ((u8 *) (&D_800C3958)[r->player] + r->track * 0x44 + 0);
        base = (u8 *) (&D_800C3958)[r->player] + r->track * 0x44;
        *(s16 *) (e + 4) = *(f32 *) (base + 0x38) + *(f32 *) (base + 4);
        *(s16 *) (e + 6) = *(f32 *) ((u8 *) (&D_800C3958)[r->player] + r->track * 0x44 + 8);
    }
    left = r->left;
    if (left != 0xFFFF) {
        if (D_800BE9E4 < left) {
            r->left = left - D_800BE9E4;
        } else {
            goto stop;
        }
    }
    *vol = r->volume;
    if (r->left < r->fadeOut) {
        if (r->left != 0) {
            *vol = (u32) (r->volume * r->left) / r->fadeOut;
        }
    } else if (r->fadeIn != 0 && r->total - r->fadeIn < r->left) {
        *vol = (u32) (*vol * (r->total - r->left)) / r->fadeIn;
    }
    if (r->left == 0xFFFF || D_800C3C88 == 0) {
        return 0;
    }
    *vol = (u32) (*vol * D_800C40A9) / 25;
    if (D_800BE9E4 < D_800C40A9) {
        return 0;
    }
stop:
    *vol = 0;
    *stop = 0;
    func_10004074(r);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15023988.s")
#endif

#ifdef NON_MATCHING
extern s32 D_800C3AA8;
extern s32 D_eu_800C3A60;

s32 func_15023C60(u32 arg0, s32 arg1, s32 arg2, u8 **arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    s16 var_v1;
    s32 var_a1;
    u16 temp_t0;
    u8 var_v0;
    u8 *temp_v0;
    u8 *var_a0;

    temp_v0 = *(((s32 *)((u8 *)&D_800C3AA8 + ((argA * 0x78) + (arg2 * 4)))));
    if (temp_v0 != NULL) {
        var_a0 = temp_v0 + 0x20;
        temp_t0 = D_800C39F8[argA][arg2];
        var_a1 = var_a0 - temp_v0;
        var_v1 = (*(s16 *)((u8 *)temp_v0 + 2));
        if ((u32) (var_a1 >> 3) < temp_t0) {
loop_3:
            var_v0 = (*(u8 *)((u8 *)var_a0 + 1));
            if ((var_v0 == 0) && ((*(s8 *)((u8 *)var_a0 + 0)) == 0)) {
                var_v1 = (*(s16 *)((u8 *)var_a0 + 2));
                goto block_37;
            }
            if ((arg0 < (u32) var_a0) && (arg1 == (*(s8 *)((u8 *)var_a0 + 0))) && ((arg4 == 0) || ((arg4 == 1) && (arg5 == (*(s16 *)((u8 *)var_a0 + 2))))) && ((arg6 == 0) || ((arg6 == 1) && (arg7 == (*(s8 *)((u8 *)var_a0 + 4))))) && ((arg8 == 0) || ((arg8 == 1) && (arg9 == (*(s8 *)((u8 *)var_a0 + 5)))))) {
                *arg3 = var_a0;
                return (s32) (var_v1 * 0x32) / 60;
            }
            if (var_v0 == 0) {
loop_19:
                if ((*(s8 *)((u8 *)var_a0 + 0)) == 0) {
                    var_v1 = (*(s16 *)((u8 *)var_a0 + 2));
                    goto block_36;
                }
                var_a1 += 8;
                var_a0 += 8;
                if ((u32) (var_a1 >> 3) >= temp_t0) {
                    var_v0 = (*(u8 *)((u8 *)var_a0 + 1));
                    goto block_36;
                }
                if ((arg0 < (u32) var_a0) && (arg1 == (*(s8 *)((u8 *)var_a0 + 0))) && ((arg4 == 0) || ((arg4 == 1) && (arg5 == (*(s16 *)((u8 *)var_a0 + 2))))) && ((arg6 == 0) || ((arg6 == 1) && (arg7 == (*(s8 *)((u8 *)var_a0 + 4))))) && ((arg8 == 0) || ((arg8 == 1) && (arg9 == (*(s8 *)((u8 *)var_a0 + 5)))))) {
                    *arg3 = var_a0;
                    return (s32) (var_v1 * 0x32) / 60;
                }
                var_v0 = (*(u8 *)((u8 *)var_a0 + 1));
                if (var_v0 != 0) {
                    goto block_36;
                }
                goto loop_19;
            }
block_36:
            var_v1 += var_v0;
block_37:
            var_a1 += 8;
            var_a0 += 8;
            if ((u32) (var_a1 >> 3) >= temp_t0) {
                goto block_38;
            }
            goto loop_3;
        }
    }
block_38:
    *arg3 = NULL;
    return *(s32 *)((u8 *)&D_eu_800C3A60 + (argA * 4));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15023C60.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800C3AA8;
extern s32 D_eu_800C3A60;
extern s32 D_800C39D0;
extern s32 D_800C3A68;

/* an 8-byte scene event: s8 type, u8 delta time (0: same time as the previous event), s16 id (type 0 with delta 0:
 * absolute time), s8 b4, s8 b5, s16 w6 */
#define EV_MATCH(ev) ((s8) (ev)[0] == type && (useId == 0 || (useId == 1 && id == *(s16 *) ((ev) + 2))) && \
                      (useB4 == 0 || (useB4 == 1 && b4 == (s8) (ev)[4])))

// scene_event_find_around: on the player's track list (D_800C3AA8[player][track], D_800C39F8 entries after the
// 0x20-byte header) finds the last matching event at or before `now` (*prev, *prevTime) and the first one after it
// (*next, *nextTime, default the scene end D_eu_800C3A60[player]); type / optional id / optional b4 must match. Times
// are track ticks (60 per second) converted to and from frames (50). Inside a run of same-time events the split
// point is the scene limit (D_800C39D0[player] while the scene runs, else D_800C3A68), as in the asm.
void func_15023EC4(u8 **prev, u8 **next, s32 *prevTime, s32 *nextTime, s32 track, s32 type, s32 useId, s32 id,
                   s32 useB4, s32 b4, s32 now, s32 player) {
    u8 *list;
    u8 *ev;
    s32 t;
    s32 limit;
    s32 time;
    u32 n;
    u8 d;

    if (prev != NULL) {
        *prev = NULL;
    }
    *next = NULL;
    if (prevTime != NULL) {
        *prevTime = 0;
    }
    t = now * 60 / 50;
    *nextTime = (&D_eu_800C3A60)[player];
    if ((&D_800C39D0)[player] < (&D_eu_800C3A60)[player]) {
        limit = (&D_800C39D0)[player] * 60 / 50;
    } else {
        limit = D_800C3A68;
    }
    list = ((u8 **) &D_800C3AA8)[player * 30 + track];
    if (list == NULL) {
        return;
    }
    n = D_800C39F8[player][track];
    time = *(s16 *) (list + 2);
    for (ev = list + 0x20; (u32) ((ev - list) >> 3) < n; ev += 8) {
        d = ev[1];
        if (d == 0 && (s8) ev[0] == 0) {
            time = *(s16 *) (ev + 2);
            continue;
        }
        if (time <= t && EV_MATCH(ev)) {
            if (prev != NULL) {
                *prev = ev;
            }
            if (prevTime != NULL) {
                *prevTime = time * 50 / 60;
            }
        }
        if (t < time && EV_MATCH(ev)) {
            *next = ev;
            *nextTime = time * 50 / 60;
            return;
        }
        d = ev[1];
        while (d == 0) {
            if ((s8) ev[0] == 0) {
                time = *(s16 *) (ev + 2);
                break;
            }
            ev += 8;
            if ((u32) ((ev - list) >> 3) >= n) {
                d = ev[1];
                break;
            }
            if (time <= limit) {
                if (EV_MATCH(ev)) {
                    if (prev != NULL) {
                        *prev = ev;
                    }
                    if (prevTime != NULL) {
                        *prevTime = time * 50 / 60;
                    }
                }
            } else if (EV_MATCH(ev)) {
                *next = ev;
                *nextTime = time * 50 / 60;
                return;
            }
            d = ev[1];
        }
        time += d;
    }
}
#undef EV_MATCH
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15023EC4.s")
#endif

s32 func_1502AB94(s32, u8, u16, s32, s32);

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u16 unkA;
} struct_150243AC; // size 0xC

extern struct_150243AC *D_800C4170;

void func_150243AC(s32 arg0, s32 arg1) {
    s32 i;
    struct_150243AC *temp_v0;

    for (i = 0; i < arg0; i++) {
        temp_v0 = (struct_150243AC *)((u8 *)D_800C4170 + i * 0xC);
        func_1502AB94(temp_v0->unk0, temp_v0->unk8, temp_v0->unkA, temp_v0->unk4 >> 8, arg1);
    }
}

#ifdef NON_MATCHING
extern u16 D_800C40BA;

void func_15024438(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 *var_v0_2;
    s32 temp_a0;
    s32 temp_at;
    s32 temp_s0;
    s32 var_a0;
    s32 var_a2;
    u8 *temp_v0;
    u8 *var_v0;
    u8 *var_v1;

    temp_s0 = *arg1;
    var_a2 = temp_s0;
    if (temp_s0 >= (s32) D_800C40BA) {
        func_150243AC(temp_s0, arg6);
        *arg1 = 0;
        return;
    }
    var_a0 = 0;
    if (temp_s0 > 0) {
        var_v0 = arg0;
loop_4:
        if ((*(s32 *)((u8 *)var_v0 + 4)) >= arg5) {
            var_a2 = var_a0;
        } else {
            var_a0 += 1;
            var_v0 += 0xC;
            if (var_a0 < temp_s0) {
                goto loop_4;
            }
        }
    }
    temp_a0 = temp_s0 - 1;
    if (temp_a0 >= var_a2) {
        var_v0_2 = arg0 + (temp_a0 * 0xC);
        var_v1 = ((s32 *)((u8 *)var_v0_2 + 0xC));
        do {
            temp_at = *var_v0_2;
            var_v1 -= 0xC;
            var_v0_2 = (s32 *)((u8 *)var_v0_2 - (0xC));
            (*(s32 *)((u8 *)var_v1 + 0xC)) = temp_at;
            (*(s32 *)((u8 *)var_v1 + 0x10)) = (s32) (*(s32 *)((u8 *)var_v0_2 + 0x10));
            (*(s32 *)((u8 *)var_v1 + 0x14)) = (s32) (*(s32 *)((u8 *)var_v0_2 + 0x14));
        } while ((u32) var_v1 >= (u32) ((var_a2 * 0xC) + arg0 + 0xC));
    }
    temp_v0 = arg0 + (var_a2 * 0xC);
    (*(s32 *)((u8 *)temp_v0 + 0)) = arg2;
    (*(s8 *)((u8 *)temp_v0 + 8)) = (s8) arg3;
    (*(s32 *)((u8 *)temp_v0 + 4)) = arg5;
    (*(s16 *)((u8 *)temp_v0 + 0xA)) = (s16) arg4;
    *arg1 += 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15024438.s")
#endif
#ifdef NON_MATCHING
void func_15024438(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern s32 D_800C39D0;
extern s32 D_800C39D8;
extern s32 D_800C39E0;
extern s32 D_800C3A68;
extern s32 D_800C3AA8;
extern u8 D_800C40AC;
extern u16 D_800C40BA;
extern s32 D_eu_800C3A60;

void func_1502457C(s32 arg0, s32 arg1) {
    struct {
        s32 u80;
    } sp;
    s32 sp7C;
    s32 sp78;
    u8 *sp74;
    s16 var_s1;
    s32 temp_a0;
    s32 temp_v1;
    s32 var_s7;
    s32 var_v0;
    s32 var_v1;
    u16 **temp_s4;
    u16 var_a0;
    u8 *temp_t2;
    u8 temp_v0;
    u8 var_a3;
    u8 var_v0_2;
    u8 **var_s6;
    u8 *temp_a1;
    u8 *var_s0;

    if ((D_800C40AC != 2) && ((&D_800C35EA)[arg1] == 1) && (D_800C40BA != 0)) {
        D_800C3638 = 0;
        sp.u80 = 0;
        temp_t2 = &D_800C3A5A[arg1];
        sp74 = temp_t2;
        var_a3 = *temp_t2;
        var_s7 = 0;
        if ((s32) var_a3 > 0) {
            var_s6 = (u8 **) ((u8 *) &D_800C3AA8 + arg1 * 0x78); /* P117: byte offset (was x4 on an s32 *) */
            do {
                temp_a1 = *var_s6;
                if (temp_a1 != NULL) {
                    temp_a0 = (&D_800C39D8)[arg1]; /* P117: was + arg1 * 4 words */
                    temp_v1 = (&D_800C39D0)[arg1];
                    var_s0 = temp_a1 + 0x20;
                    if (temp_a0 != temp_v1) {
                        temp_s4 = &D_800C39F8[arg1];
                        var_s1 = (*(s16 *)((u8 *)temp_a1 + 2));
                        sp78 = (s32) (temp_a0 * 0x3C) / 50;
                        if (temp_v1 >= (&D_eu_800C3A60)[arg1]) {
                            sp7C = D_800C3A68;
                        } else {
                            sp7C = (s32) (temp_v1 * 0x3C) / 50;
                        }
                        var_a0 = (*temp_s4)[var_s7];
                        var_v1 = var_s0 - temp_a1;
                        var_v0 = var_v1 >> 3;
                        if ((u32) var_v0 < var_a0) {
loop_11:
                            if (((*(u8 *)((u8 *)var_s0 + 1)) == 0) && ((*(s8 *)((u8 *)var_s0 + 0)) == 0)) {
                                var_s1 = (*(s16 *)((u8 *)var_s0 + 2));
                                goto block_35;
                            }
                            if ((sp7C >= var_s1) && (sp78 < var_s1) && ((u32) var_v0 < var_a0)) {
loop_17:
                                if (((arg0 == 0) && ((*(s8 *)((u8 *)var_s0 + 0)) != 0x11)) || ((arg0 == 1) && ((*(s8 *)((u8 *)var_s0 + 0)) == 0x11))) {
                                    func_15024438(D_800C4170, &sp.u80, var_s0, var_s7, var_v0, (s32) ((var_s1 << 8) * 0x32) / 60, arg1);
                                }
                                temp_v0 = (*(u8 *)((u8 *)var_s0 + 1));
                                if ((temp_v0 == 0) && ((temp_v0 != 0) || ((*(s8 *)((u8 *)var_s0 + 0)) != 0))) {
                                    var_s0 += 8;
                                    var_v0 = (s32) (var_s0 - *var_s6) >> 3;
                                    if ((u32) var_v0 < (u16) (*temp_s4)[var_s7]) {
                                        goto loop_17;
                                    }
                                }
                            }
                            if (sp7C < var_s1) {
                                var_a3 = *sp74;
                            } else {
                                var_v0_2 = (*(u8 *)((u8 *)var_s0 + 1));
                                var_a0 = (*temp_s4)[var_s7];
                                var_v1 = var_s0 - *var_s6;
                                if (var_v0_2 == 0) {
loop_29:
                                    if ((*(s8 *)((u8 *)var_s0 + 0)) == 0) {
                                        var_s1 = (*(s16 *)((u8 *)var_s0 + 2));
                                    } else {
                                        var_v1 += 8;
                                        var_s0 += 8;
                                        if ((u32) (var_v1 >> 3) >= var_a0) {
                                            var_v0_2 = (*(u8 *)((u8 *)var_s0 + 1));
                                        } else {
                                            var_v0_2 = (*(u8 *)((u8 *)var_s0 + 1));
                                            if (var_v0_2 == 0) {
                                                goto loop_29;
                                            }
                                        }
                                    }
                                }
                                var_s1 += var_v0_2;
block_35:
                                var_v1 += 8;
                                var_v0 = var_v1 >> 3;
                                var_s0 += 8;
                                if ((u32) var_v0 >= var_a0) {
                                    var_a3 = *sp74;
                                } else {
                                    goto loop_11;
                                }
                            }
                        }
                    }
                }
                var_s7 += 1;
                var_s6 += 1; /* P117: one track pointer (was 4) */
            } while (var_s7 < (s32) var_a3);
        }
        func_150243AC(sp.u80, arg1);
        D_800C3638 = 1;
        if (arg0 == 0) {
            ((u8 *) &D_800C39E0)[arg1] = 1; /* P117: sb (was a word at 4 * arg1) */
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_1502457C.s")
#endif
#ifdef NON_MATCHING
/* --- P114: scene event handler A (func_15024910); hand-written from the asm (map: docs/port/sessions/p114/scene_vm_map.md) --- */
s16 *func_1502354C(s32 track, s32 start);
void func_150234E8(s16 *arg0, s32 arg1);
void func_1516D850(u8 *arg0);
u8 *func_1516D8E8(u8 *arg0);
u8 *func_1516D934(u8 *arg0);
s32 func_1516AD20(s32, s32, s32, void (*)(s32, s32, s32), s32 *, s32);
s32 func_15023C60(u32 arg0, s32 arg1, s32 arg2, u8 **arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);
void func_1507EB4C(struct127 *arg0, s32 arg1);
void func_1507E7E4(struct127 *obj, u8 anim, u8 prio, u16 time, s32 arg4);
s32 func_15083568(struct127 *arg0, s32 arg1, f32 arg2, s32 arg3);
s32 func_150836CC(struct127 *obj, s32 n);
u8 *func_15031C4C(u8 *arg0, s32 arg1, s32 arg2);
s32 func_15053430(struct127 *obj);
void func_15060F28(struct127 *arg0, s32 arg1);
void func_1501C710(s32 arg0, u16 *arg1, s32 arg2, s32 arg3, s32 arg4);
u8 *func_151149AC(u8 id);
void func_151494E0(s32, u8);
void func_1515F170(s32 arg0, u8 arg1);
void func_151645C4(u8 arg0);
void func_151616D0(u8 arg0, u8 arg1, s32 arg2);
void func_151CD90C(s32 arg0);
void func_150B696C(u8 arg0);
void func_151C9CBC(s32 arg0, s32 arg1);
void func_151CA398(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_151CA484(u8 *arg0);
void func_150E0880(void);
void func_150FB2A8(void);
void func_150F58C0(s32 arg0);
void func_150FAFC0(u8 arg0, s32 arg1);
void func_15169040(s32 arg0, u8 arg1);
void func_151CD944(s32 arg0);
void func_15190A88(u8 *arg0);
void func_1518F9CC(s32 arg0, u8 arg1);
void func_151937F4(u8 *arg0, s32 arg1, s32 arg2);
void func_151920FC(s32 arg0, u8 arg1);
s32 *func_151905AC(u8 *arg0, s32 *arg1);
s32 func_1518FA8C(s32 arg0, u8 arg1, s16 arg2, s8 arg3, s8 arg4, s8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9);
u8 *func_1518D1C0(u8 *obj, s16 kind, s16 span, s32, s32 flag, s32, char *name);
s32 func_1519D5A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_151482D4(s32 arg0, u8 arg1);
void func_150C6174(s32 arg0);
void func_150C619C(s32 arg0);
void func_1510B9D8(s32 player, f32 width, f32 height);
s32 func_15083FB0(u8 arg0);
void func_150B7700(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void *func_151A5580(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7);
void func_10011FB0(s32 arg0);
void func_150C851C(s32 arg0);
f32 func_15052F9C(struct127 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
void func_1517F9F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_1517FC90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_150F59A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_1510AEB0(s32 arg0, s32 arg1, s32 arg2);
void func_151DECB4(void);
void func_151E5B94(s32 arg0);
void func_1505959C(struct127 *arg0, s32 arg1);
void func_15073F1C(void);
void func_15093818(s32 arg0);

extern s8 D_800E1024;              /* cutscene colour-light events (7 / 0xE / 0xF / 0x10 / 0x12) enabled */
extern u8 D_800BEECB;              /* which of them is active: 0 / 4 / 2 / 3 / 1 */
extern u8 D_800844A8[3][3];        /* light colours (.data) */
extern u8 D_800844B4[2][3];        /* sub 0x41 colours (.data) */
extern s16 D_800844BC[4][2];       /* sub 0x05 kinds (.data; [i][1] is used) */
extern u8 D_800844CC[3][3];        /* sub 0x37 colours (.data) */
extern s32 *D_800C3A00[4];
extern u8 D_800C3A18;
extern s32 D_800905C4[];
extern u8 D_800C3A78[], D_800C3A7A[], D_800C3A7C[], D_800C3A7E[], D_800C3A80[], D_800C3A82[], D_800C3A84[];
extern u8 D_800C3A86;
extern f32 D_800C3A70, D_800C3A74, D_800C3A94, D_800C3A98;
extern s32 D_800C3A9C;
extern f32 D_800D9F3C, D_800D9F40;
extern s32 D_800BEE08;
extern u8 D_800C40AB, D_800C40AD, D_800C3AA0, D_800DC2DC, D_800C40BD, D_800BEE2C;
extern u8 D_800C39E2, D_800C39E3, D_800C3682, D_800C3683;
extern s16 D_800C40BE;
extern s32 D_800D2870;
extern u8 *D_800DE274, *D_800DE278, *D_800DE27C;
extern char D_80096DE0[];          /* "Cutscene 1" */

typedef struct { u8 b[9]; } SceneBytes9;
typedef struct { u8 b[6]; } SceneBytes6;
typedef struct { s16 h[8]; } SceneHalves8;
/* one 8-byte scene event (as in func_150268BC) */
typedef struct {
    s8  type;
    u8  delta;
    s16 id;
    s8  b4;
    s8  b5;
    s16 w6;
} SceneEventA;

#define SA_REC(p, t) ((u8 *) (&D_800C3958)[p] + (t) * 0x44)   /* the track's struct233 record (0x44 bytes) */
#define SA_U8(p, o) (*(u8 *) ((u8 *) (p) + (o)))
#define SA_S8(p, o) (*(s8 *) ((u8 *) (p) + (o)))
#define SA_S16(p, o) (*(s16 *) ((u8 *) (p) + (o)))
#define SA_S32(p, o) (*(s32 *) ((u8 *) (p) + (o)))
#define SA_F32(p, o) (*(f32 *) ((u8 *) (p) + (o)))
#define SA_PTR(p, o) (*(u8 **) ((u8 *) (p) + (o)))
#define SA_OBJ_INDEX(o) (((u8 *) (o) - (u8 *) D_800CC2D0) / 0x32C)

// scene_event_run_a: first handler of a scene event (func_1502AB94 tries this one, then func_150268BC, then
// func_15029EA8). ev is the 8-byte event, track / player its track, now the track time, obj / wrec the track's object
// or world record (ref kind 2 / 3), flag the player's D_800C3A08 byte. Handles the cutscene light types (7, 0xE, 0xF,
// 0x10, 0x12 while D_800E1024), object types 0xC (animation), 0xD (setup lists), 4, 9, 1, track switch 3, and the
// type 5 sub-types below (0x67: leave the logo scene for the title menu via func_151DECB4). Returns 1 when handled.
s32 func_15024910(s32 arg0, u8 track, u16 value, s32 now, s32 player, struct127 *obj, u8 *wrec, u8 *data, s32 flag) {
    SceneEventA *ev = (SceneEventA *) arg0;
    u8 *o = (u8 *) obj;
    u8 *rec;
    u8 *next;
    s32 span;
    s32 type = ev->type;

    if (D_800E1024 != 0 && (type == 7 || type == 0xE || type == 0xF || type == 0x10 || type == 0x12)) {
        u8 colours[3][3];
        s16 *light;
        u8 *text;
        s32 k;

        *(SceneBytes9 *) colours = *(SceneBytes9 *) D_800844A8;
        if ((type == 7 && D_800BEECB != 0) || (type == 0xE && D_800BEECB != 4) || (type == 0xF && D_800BEECB != 2) ||
            (type == 0x10 && D_800BEECB != 3) || (type == 0x12 && D_800BEECB != 1)) {
            return 1;
        }
        light = func_1502354C(track, ev->b4 == 0);
        if (light == NULL) {
            return 1;
        }
        if (ev->b4 == 0) {
            if (SA_U8(light, 0xC) != 0) {
                func_1516D850(SA_PTR(light, 0x34));
            }
            text = (u8 *) D_800C3A00[player][ev->id];
            if (*text == 0xBE) {
                SA_S32(light, 4) = 0x8013;
                text++;
            } else if (*text == 0xBF) {
                SA_S32(light, 4) = 0x8019;
                text++;
            } else {
                SA_S32(light, 4) = 0x8011;
            }
            SA_PTR(light, 8) = text;
            SA_S16(light, 0x2A) = 100;
            SA_U8(light, 0xC) = 1;
            SA_S16(light, 0x28) = 0;
            rec = SA_REC(player, track);
            SA_PTR(light, 0x1C) = rec + 0xC;
            SA_U8(light, 0x2F) = 1;
            SA_PTR(light, 0x20) = rec + 0x10;
            SA_PTR(light, 0x24) = rec + 0x14;
            SA_U8(light, 0x2C) = colours[ev->b5][0];
            SA_U8(light, 0x2D) = colours[ev->b5][1];
            SA_U8(light, 0x2E) = colours[ev->b5][2];
            if (ev->b5 == 2) {
                SA_S32(light, 4) |= 0x40000;
            }
            SA_S32(light, 0x34) = func_1516AD20(0, 0, 0, NULL, (s32 *) ((u8 *) light + 4), flag);
        } else if (ev->b4 == 1) {
            func_150234E8(light, ev->b5);
        } else {
            if (ev->b5 == 0) {
                SA_PTR(light, 0x34) = func_1516D8E8(SA_PTR(light, 0x34));
            } else {
                SA_PTR(light, 0x34) = func_1516D934(SA_PTR(light, 0x34));
            }
            if (ev->w6 != 0) {
                k = ev->w6 - 1;
                SA_U8(light, 0x2C) = colours[k][0];
                SA_U8(light, 0x2D) = colours[k][1];
                SA_U8(light, 0x2E) = colours[k][2];
                if (k == 2) {
                    SA_S32(light, 4) |= 0x40000;
                } else {
                    SA_S32(light, 4) &= ~0x40000;
                }
            }
        }
        return 1;
    }

    switch (type) {
    case 0xC: /* object animation */
        if (ev->id != 0) {
            if (ev->w6 != 0) {
                func_1507EB4C(obj, ev->id);
            } else {
                if (ev->b5 != 0) {
                    span = 0xFFFF;
                } else {
                    span = func_15023C60(arg0, type, track, &next, 0, 0, 0, 0, 0, 0, player) - now;
                }
                func_1507E7E4(obj, ev->id, 3, span, ev->b4);
            }
        }
        return 1;
    case 0xD: /* object setup list id + 1: run / undo / set a parameter */
        if (obj != NULL) {
            if (ev->b4 == 0) {
                func_15083568(obj, ev->id + 1, 1.0f, 0);
            } else if (ev->b4 == 1) {
                func_150836CC(obj, ev->id + 1);
            } else {
                u8 *att = func_15031C4C(o, ev->id + 1, 0);

                if (att != NULL) {
                    if (ev->b4 == 2) {
                        SA_S16(att, 0x18) = D_800905C4[ev->b5];
                    } else if (ev->b4 == 3) {
                        SA_S16(att, 0x1A) = D_800905C4[ev->b5];
                    }
                }
            }
        }
        return 1;
    case 4: /* object +0x134 / +0x135: id and half the span (1 .. 255) */
        if (obj != NULL) {
            span = (func_15023C60(arg0, type, track, &next, 0, 0, 0, 0, 0, 0, player) - now) / 2;
            if (span >= 0x100) {
                span = 0xFF;
            } else if (span == 0) {
                span = 1;
            }
            if (ev->b4 == 0) {
                SA_U8(o, 0x135) = span;
                SA_U8(o, 0x134) = ev->id;
            }
        }
        return 1;
    case 3: /* switch the camera track: only to a track of ref kind 1 */
        if (ev->id < D_800C3A5A[player] && D_800C3A10[player][ev->id].kind == 1 && ev->id != D_800C3A18) {
            D_800C3A18 = ev->id;
            D_800DBFF4[0] = 4;
            SA_S32(D_800DBFF0, 0x5F0) |= 4;
        }
        return 1;
    case 9:
        if (obj != NULL) {
            SA_U8(o + ev->b4, 0x6C) = ev->id + 10;
        }
        return 1;
    case 1:
        if (obj != NULL) {
            SA_U8(o, 0x1C9) = ev->id != 0 ? ev->id : 0xFF;
        }
        return 1;
    case 5:
        break;
    default:
        return 0;
    }

    switch (ev->id) {
    case 0x3B:
        D_800DDE18 = ev->b4 == 0 ? (s32) (SA_REC(player, track) + 0x28) : 0;
        break;
    case 0x08:
        D_800C3A7A[player] = ev->b4 == 0;
        break;
    case 0x09:
        D_800C3A7C[player] = ev->b4 == 0;
        break;
    case 0x0D:
        D_800C3A78[player] = ev->b4 == 0;
        break;
    case 0x12:
        D_800C3A7E[player] = ev->b4 == 0;
        break;
    case 0x13:
        D_800C3A80[player] = ev->b4;
        break;
    case 0x15:
        D_800C3A82[player] = ev->b4 == 0;
        break;
    case 0x14:
        if (obj != NULL) {
            if (ev->b4 == 0) {
                func_15053430(obj);
            } else {
                func_15060F28(obj, 0);
            }
        }
        break;
    case 0x41: {
        u8 colours[2][3];

        *(SceneBytes6 *) colours = *(SceneBytes6 *) D_800844B4;
        if (obj != NULL) {
            if (ev->b4 == 0) {
                SA_U8(o, 0xA5) = colours[ev->b5][0];
                SA_U8(o, 0xA6) = colours[ev->b5][1];
                SA_U8(o, 0xA4) = 1;
                SA_U8(o, 0xA7) = colours[ev->b5][2];
                SA_PTR(o, 0xA0) = SA_REC(player, track) + 0x30;
            } else {
                SA_U8(o, 0xA4) = 0;
                SA_PTR(o, 0xA0) = NULL;
            }
        }
        break;
    }
    case 0x44: /* level change */
        if (ev->b5 != 0) {
            func_1501C710(2, (u16 *) (s32) ev->b4, ev->w6, 0, 0);
        } else {
            func_1501C710(1, (u16 *) (s32) ev->b4, 0, 0, 0);
        }
        break;
    case 0x17:
        if (obj != NULL) {
            SA_U8(o, 0x1FF) = ev->b4 == 0;
            if (SA_U8(o, 0x1FF) != 0) {
                SA_U8(o, 0x1FF) += ev->b5;
            }
            if (ev->b4 == 0) {
                SA_U8(o, 0x201) = ev->w6;
            }
        }
        break;
    case 0x16:
        if (obj != NULL) {
            SA_U8(o, 0x206) = ev->b4 == 0;
            if (SA_U8(o, 0x206) != 0) {
                SA_U8(o, 0x206) += ev->b5;
            }
            if (ev->b4 == 0) {
                SA_U8(o, 0x208) = ev->w6;
            }
        }
        break;
    case 0x18:
    case 0x66:
    case 0x6B:
        break;
    case 0x1D:
        if (D_800C3A10[player][track].kind == 3 && wrec != NULL) {
            SA_U8(wrec, 0x6E) = ev->b4 == 0 ? 1 : 0;
        }
        break;
    case 0x1E:
        D_800C39E2 = ev->b4 + 1;
        D_800C39E3 = D_800BE9F0;
        break;
    case 0x03: {
        u8 *r = func_151149AC(ev->w6);

        if (r != NULL) {
            SA_U8(r, 0x73) &= ~3;
            if (ev->b5 == 0) {
                SA_U8(r, 0x73) |= 2;
            } else {
                SA_U8(r, 0x73) |= 1;
            }
        }
        break;
    }
    case 0x6C:
        switch ((u8) ev->b4) {
        case 0: {
            f32 pos[3];

            rec = SA_REC(player, track);
            pos[0] = SA_F32(rec, 0);
            pos[1] = SA_F32(rec, 4);
            pos[2] = SA_F32(rec, 8);
            func_151BEE00(pos, SA_F32(rec, 0x10), 1, 0, 2, 0xFF, 1);
            break;
        }
        case 1: {
            f32 pos[3];

            rec = SA_REC(player, track);
            pos[0] = SA_F32(rec, 0);
            pos[1] = SA_F32(rec, 4);
            pos[2] = SA_F32(rec, 8);
            func_151A9940(5, 1, NULL, (s32) pos, -10000.0f, 100.0f, -1, flag, 1);
            break;
        }
        case 2:
            func_151494E0(0, ev->b5 != 0 ? 0x2B : 0x2C);
            break;
        case 3:
            if (ev->b5 != 0) {
                func_1515F170(1, 0);
                func_1515F170(2, 1);
            } else {
                func_1515F170(1, 1);
                func_1515F170(2, 0);
            }
            break;
        case 4:
            func_151645C4(ev->b5);
            break;
        case 5:
            func_151616D0(0x28, 0x17, 0);
            break;
        case 6:
            func_151CD90C(ev->b5);
            break;
        case 7:
            func_1515F170(3, ev->b5 != 0 ? 0 : 1);
            break;
        case 8:
            func_150B696C(ev->b5);
            break;
        case 9: {
            static const s32 sLights[4] = { 0x12, 0x13, 0x14, 0x15 };   /* D_80096DD0 */
            u8 i;

            for (i = 0; i < 4; i++) {
                func_151C9CBC(2, (s32) (D_800D34B8 + sLights[i] * 0x34));
            }
            break;
        }
        case 10:
            func_151CA398((u8 *) D_800DBFF0, 0, (s8) track, (u8) flag, 1);
            break;
        case 11:
            func_151CA484((u8 *) D_800DBFF0);
            break;
        case 12:
            func_150E0880();
            break;
        case 13:
            func_150FB2A8();
            break;
        case 14:
            func_150F58C0(9);
            break;
        case 15:
            func_150FAFC0(0xFF, 1);
            break;
        case 16:
            func_15169040(0, 0x4E);
            break;
        case 17:
            func_15169040(0, 0x4F);
            break;
        case 18:
            func_151CD944(ev->b5);
            break;
        case 19:
            func_1515F170(0xB, 0);
            break;
        case 20:
            if (obj != NULL) {
                func_15190A88(o);
                func_1518F9CC(0, 0x49);
            }
            break;
        case 21:
            func_151494E0(0, ev->b5 != 0 ? 0x55 : 0x56);
            break;
        case 22:
            if (obj != NULL) {
                func_151937F4(o, 0xFF, 1);
            }
            break;
        case 23:
            if (obj != NULL) {
                struct { u8 *obj; u8 kind; } ref;

                ref.obj = o;
                ref.kind = SA_U8(o, 0x3B);
                func_151920FC((s32) &ref, 0x50);
            }
            break;
        }
        break;
    case 0x6E: {
        s32 n;
        u8 *list = (u8 *) func_151905AC(o, &n);

        if (list != NULL && ev->w6 < n) {
            func_1518FA8C((s32) obj, list[ev->w6], -1, -1, -1, -1, 0, 0, 0xFF, 1);
        }
        break;
    }
    case 0x05: {
        s16 kinds[4][2];
        s32 k;
        s32 f;

        *(SceneHalves8 *) kinds = *(SceneHalves8 *) D_800844BC;
        if (ev->b4 == 0) {
            k = ev->b5 >= 4 ? 3 : ev->b5;
            span = func_15023C60(arg0, ev->type, track, &next, 1, ev->id, 0, 0, 1, ev->b5, player) - now;
            if (ev->w6 != 0) {
                span = 999;
                f = 0xFF;
            } else {
                f = (u8) flag;
            }
            func_1518D1C0(o, kinds[k][1], span, 0, f, 0, D_80096DE0);
        }
        break;
    }
    case 0x36:
        if (ev->b4 == 0) {
            func_1519D5A0((s32) obj, 0, 300, 0, flag, 0);
        } else if (ev->b4 == 1) {
            struct { u8 *obj; u8 kind; } ref;

            ref.obj = o;
            ref.kind = SA_U8(o, 0x3B);
            func_151482D4((s32) &ref, 7);
        }
        break;
    case 0x30:
        if (obj != NULL) {
            s32 anim;

            switch (ev->b4) {
            case 1:
                anim = 4;
                break;
            case 2:
                anim = 7;
                break;
            case 3:
                anim = 10;
                break;
            default:
                anim = 12;
                break;
            }
            func_1514D3B0((s32) obj, 0xD, anim, 0);
        }
        break;
    case 0x46:
        if (ev->b4 != 0) {
            func_150C6174((s32) obj);
        } else {
            func_150C619C((s32) obj);
        }
        break;
    case 0x25:
        D_800C3A70 = ev->b4 != 0 ? (f32) ev->b4 : D_800D9F40;
        func_1510B9D8(0, D_800C3A70, D_800C3A74);
        break;
    case 0x58:
        D_800C3A74 = ev->w6 != 0 ? (f32) (ev->w6 * 10) : D_800D9F3C;
        func_1510B9D8(0, D_800C3A70, D_800C3A74);
        break;
    case 0x3C:
        if (obj != NULL) {
            s32 bits = (ev->b4 << 16) | ev->w6;   /* w6 sign-extended, as the asm (lh) */

            if (ev->b5 == 0) {
                SA_S32(o, 0x94) = bits;
            } else if (ev->b5 == 1) {
                SA_S32(o, 0x94) |= bits;
            } else {
                SA_S32(o, 0x94) &= ~(bits | 1);
            }
        }
        break;
    case 0x3D: /* target: the object with setup id w6 & 0xFF */
        if (obj != NULL) {
            if (ev->b4 == 0) {
                s32 target = func_15083FB0(ev->w6);

                if (target != -1) {
                    SA_U8(o, 0x65) = target + 1;
                    SA_U8(o, 0x101) |= 4;
                    SA_S32(o, 0x5C) = ev->b5;
                }
            } else {
                SA_U8(o, 0x65) = 0;
            }
        }
        break;
    case 0x42:
        switch (ev->b4) {
        case 0:
            D_800D9CB0 = 1;
            break;
        case 1:
            D_800D9CB0 = 4;
            break;
        case 3:
            D_800D9CB0 = 2;
            break;
        case 4:
            D_800D9CB0 = 5;
            break;
        case 5:
            D_800D9CB0 = 6;
            break;
        case 6:
            D_800D9CB0 = 7;
            break;
        case 7:
            D_800D9CB0 = 8;
            break;
        case 8:
            D_800D9CB0 = 9;
            break;
        case 9:
            D_800D9CB0 = 10;
            break;
        }
        break;
    case 0x43:
        if (ev->b4 == 0) {
            rec = SA_REC(player, track);
            func_150B7700((s32) SA_F32(rec, 0x24), (s32) SA_F32(rec, 0x28),
                          func_15023C60(arg0, type, track, &next, 1, ev->id, 0, 0, 0, 0, player) - now, flag);
        }
        break;
    case 0x45:
        if (ev->b4 == 0) {
            func_151A5580(0, func_15023C60(arg0, type, track, &next, 1, ev->id, 0, 0, 0, 0, player) - now, 0xFF, 0, 0,
                          D_800BEE08, 0, 0);
        }
        break;
    case 0x49:
        if (obj != NULL && ev->b4 < 3) {
            SA_S32(o + ev->b4 * 4, 0x2E4) = ev->w6;
        }
        break;
    case 0x4B:
        if (obj != NULL) {
            SA_S32(o, 0x9C) = (u16) ev->w6 | ((u8) ev->b5 << 16) | (ev->b4 << 24);
        }
        break;
    case 0x4A:
        func_10011FB0(ev->b4 == 0 ? ev->b5 : 0);
        break;
    case 0x54:
        D_800C3A84[player] = ~ev->b4;
        break;
    case 0x55:
        func_150C851C(ev->b4);
        break;
    case 0x59:
        D_800C40AB = 1;
        break;
    case 0x5A:
        D_800C3E78 = SA_OBJ_INDEX(obj);
        switch (SA_U8(o, 4)) {
        case 0x53:
            SA_U8(o, 0x124) = 0;
            func_15052F9C(obj, 156.0f, 1, 4, 0, 10, 0xFF, 0, 1, 0);
            break;
        case 0x28:
            SA_U8(o, 0x124) = 0;
            func_15052F9C(obj, 180.0f, 5, 0x44, 1, 1, 0xFF, 0, 1, 0);
            break;
        case 0x21:
            SA_U8(o, 0x124) = 0;
            func_15052F9C(obj, 156.0f, 0x19, 4, 0, 15, 0xFF, 0, 1, 0);
            break;
        }
        break;
    case 0x71: /* release the player object (slot 0) */
        SA_S16(D_800CC2D0, 0xCC) = 0;
        SA_U8(SA_PTR(D_800CC2D0, 0x31C), 0x4E) = 0;
        SA_U8(D_800CC2D0, 0x65) = 0;
        SA_U8(SA_PTR(D_800CC2D0, 0x31C), 0x27) = 0;
        SA_S32(D_800CC2D0, 0xF8) &= ~0x01000000;
        if (obj != NULL) {
            SA_U8(o, 0x13C) = 0;
        }
        break;
    case 0x37: {
        u8 colours[3][3];
        s32 v;

        *(SceneBytes9 *) colours = *(SceneBytes9 *) D_800844CC;
        span = func_15023C60(arg0, ev->type, track, &next, 1, ev->id, 0, 0, 0, 0, player) - now;
        if (ev->b4 == 0) {
            v = ev->w6 != 0 ? ev->w6 : 0x7F;
            func_1517F9F8(colours[ev->b5][0], colours[ev->b5][1], colours[ev->b5][2], (s16) v, span, 0);
        } else {
            D_800DE240[0] = 0;
        }
        break;
    }
    case 0x38:
        span = func_15023C60(arg0, type, track, &next, 1, ev->id, 0, 0, 0, 0, player) - now;
        if (ev->b4 == 0) {
            func_1517FC90(ev->b5, span, ev->w6 != 0 ? ev->w6 : 4, 0x7F, 1);
        } else {
            D_800DDE08 = 0;
        }
        break;
    case 0x5C: /* camera fade in / hold / out: span to the event's b4 = 1 / 2 / 3 companions */
        if (ev->b4 == 0) {
            s32 end = func_15023C60(arg0, type, track, &next, 1, ev->id, 1, 1, 1, ev->b5, player);
            s32 in = func_15023C60(arg0, ev->type, track, &next, 1, ev->id, 1, 2, 1, ev->b5, player) - now;
            s32 out;

            if (next == NULL) {
                in = 0;
            }
            out = end - func_15023C60(arg0, ev->type, track, &next, 1, ev->id, 1, 3, 1, ev->b5, player);
            if (next == NULL) {
                out = 0;
            }
            if (D_800BE9F0 == 0x18) {
                func_150F59A0(in, end - now - out - in, out, ev->b5);
            } else if (D_800BE9F0 == 0x21) {
                func_1510AEB0(in, end - now - out - in, out);
            }
        }
        break;
    case 0x62:
        SA_U8(D_800B0DF0, 8) = 0;
        break;
    case 0x7C:
        D_800C3681 = ev->b4 == 0;
        break;
    case 0x84:
        D_800C3682 = ev->b4 == 0;
        break;
    case 0x85:
        D_800C3683 = ev->b4 == 0;
        break;
    case 0x63:
        D_80041FDC = ev->w6;
        break;
    case 0x64:
        if (ev->b4 == 0) {
            D_800DDE40 = 1;
            rec = SA_REC(player, track);
            D_800DE274 = rec + 0x28;
            D_800DE278 = rec + 0x24;
            D_800DE27C = rec + 0x2C;
        } else {
            D_800DDE40 = 0;
        }
        break;
    case 0x67: /* end of the logo scene: go to the title menu */
        func_151DECB4();
        break;
    case 0x73:
        func_151E5B94(0);
        break;
    case 0x69:
        if (obj != NULL) {
            switch (ev->b4) {
            case 0:
                SA_F32(o, 0x24) = 4.0f;
                SA_F32(o, 0x20) = 20.0f;
                break;
            case 1:
                SA_F32(o, 0x24) = 0.0f;
                SA_F32(o, 0x20) = 0.0f;
                break;
            case 2:
                func_150836CC(obj, 0x11);
                SA_U8(o, 0xA9) = 0;
                break;
            case 3:
                D_800C3E78 = SA_OBJ_INDEX(obj);
                SA_U8(D_800CC2D0, 0x13C) = D_800C3E78 + 100;
                SA_F32(D_800CC2D0, 0x3C) = 0.0f;
                SA_S16(SA_PTR(D_800CC2D0, 0x31C), 0x18) = 0;
                func_1505959C(obj, 0);
                SA_S32(o, 0x5C) = 9;
                SA_U8(o, 0x65) = 1;
                SA_U8(o, 0x101) |= 4;
                break;
            case 4:
                SA_U8(SA_PTR(D_800CC2D0, 0x31C), 0x17) = 1;
                break;
            case 5:
                D_800D154C = obj;
                func_15073F1C();
                break;
            case 6:
                SA_U8(SA_PTR(o, 0x31C), 0x4E) = 0;
                break;
            }
        }
        break;
    case 0x6A:
        D_800C3A94 = ev->w6;
        break;
    case 0x7A:
        D_800C3A9C = ev->b5 * 50;
        D_800C3A98 = ev->w6;
        break;
    case 0x6D:
        D_800C3A86 = ev->b4 == 0;
        break;
    case 0x74:
        D_800BEE2C = ev->b5;
        break;
    case 0x6F:
        if (obj != NULL) {
            SA_U8(o + ev->b4, 0x68) = ev->b5;
        }
        break;
    case 0x70:
        D_800C40AC = 1;
        break;
    case 0x72:
        if (obj != NULL) {
            SA_F32(o, 0xC8) = SA_S16(D_800D1C90[SA_U8(o, 4)], 6);
        }
        break;
    case 0x78:
        D_800C40AD = 1;
        break;
    case 0x79:
        if (wrec != NULL) {
            SA_S32(wrec, 0x84) = 0;
            SA_S32(wrec, 0x80) = 0;
            SA_S32(wrec, 0x7C) = 0;
        }
        break;
    case 0x7B:
        if (D_800BE9F0 == 0x1D) {
            D_800C3AA0 = 1;
        }
        break;
    case 0x7D:
        if (obj != NULL && ev->b4 == 0) {
            SA_U8(o, 5) = 1;
        }
        break;
    case 0x7E:
        if (obj != NULL) {
            D_800D18D0 = SA_OBJ_INDEX(obj);
        }
        break;
    case 0x7F:
        D_800DC2DC = 1;
        break;
    case 0x80:
        D_800BE9ED = ev->b4;
        break;
    case 0x81:
        func_15093818(ev->b4 ^ 1);
        D_800D2870 = ev->w6 * 25;
        break;
    case 0x82:
        D_800C40BD = (u8) ev->b4 >= 101 ? 100 : ev->b4;
        break;
    case 0x83:
        D_800C40BE = ev->w6;
        break;
    default:
        return 0;
    }
    return 1;
}
#undef SA_REC
#undef SA_U8
#undef SA_S8
#undef SA_S16
#undef SA_S32
#undef SA_F32
#undef SA_PTR
#undef SA_OBJ_INDEX
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15024910.s")
#endif
#ifdef NON_MATCHING
/* P90: hand-written from the asm (map: docs/port/sessions/p89/func_150268BC_map.md, tests: docs/port/sessions/p90) */
/* --- callees: C definitions elsewhere (signatures copied) --- */
void func_1001263C(s32 arg0, s32 arg1, s32 arg2);
void func_151F2D6C(s32, s32);
void func_151F2BA8(void);
void func_151F2BE8(void);
void func_151F2C4C(void);
void func_1516DF0C(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA,
                   u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15,
                   u8 arg16, u8 arg17, u8 arg18, u8 arg19, u8 arg1A, s16 arg1B, s16 arg1C, s16 arg1D, s16 arg1E, u16 arg1F,
                   u8 arg20, u8 arg21, u8 arg22, u8 arg23, s16 arg24, u16 arg25, u16 arg26, u8 arg27, u8 arg28, u8 arg29,
                   u8 arg2A, u8 arg2B, s32 arg2C, u8 arg2D, u8 arg2E, u8 arg2F, s32 arg30);
void func_151BA1A0(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9,
                   s16 argA, s16 argB, s16 argC, s32 argD, u8 argE, s32 argF);
void func_15167AD8(void *arg0, u8 arg1, s32 arg2);
void func_150E3334(s32 arg0, u8 arg1, s16 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9,
                   s16 argA, s16 argB, u16 argC, u8 argD);
void func_1516ECE8(u32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4);
void func_150BF47C(s32 arg0);
f32 func_15048A40(u8 arg0);
void func_151DCE6C(u8 *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5);
void func_150BA4C0(u8 *arg0, u8 arg1, s32 arg2);
void func_151A3940(u8 *arg0, u8 arg1);
void func_151664F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8);
void func_150B2974(u8 *arg0, s32 arg1, s32 arg2);
void func_15136A50(s32 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5);
s32 func_150CE660(u8 *arg0, s16 arg1, s32 arg2, s32 arg3);
void func_150D0148(f32 arg0);
void func_151494E0(s32, u8);
struct260 *func_1510A454(u8 *arg0, s16 arg1, s8 arg2, s8 arg3, f32 arg4, s32 arg5, u8 arg6, s32 arg7);
struct260 *func_1510A8C4(u8 *arg0, s16 arg1, u8 arg2, s32 arg3);
struct225 *func_151619A0(s32 arg0, s16 arg1, u8 arg2, s32 arg3);
void func_1510957C(s32 arg0, s32 arg1, u8 arg2);
void func_151A9940(u8 arg0, u8 arg1, void *arg2, s32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8);
u8 *func_15190770(u8 **arg0, s32 arg1, u8 arg2, s32 arg3);
void func_150AFC18(s16 arg0, u8 arg1, s32 arg2);
struct260 *func_15149130(s16 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, struct37 *arg6, u8 arg7, s32 arg8);
void func_150F6188(u8 *arg0, s16 arg1, u8 arg2, s32 arg3);
void func_1519F0FC(u8 *arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4);
void func_150F6E10(u8 *arg0, s16 arg1, u8 arg2, u8 arg3);
void func_150D0644(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4);
void func_150D07C4(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4);
void func_150D09D4(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4);
void func_1519F2F4(u8 *arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4);
s32 func_15046F70(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3);
f32 func_150ADA68(void);
s32 func_150ADA20(void);
s32 func_15136698(f32 arg0, f32 arg1, u8 arg2, u8 arg3, s16 arg4, s32 arg5, struct17 *arg6, u8 arg7, u8 arg8, u8 arg9,
                  s32 argA);
void func_150E38C0(u8 *arg0, u8 *arg1, s32 arg2, s16 arg3);
s32 func_151D8E18(structEU_151D8E18 *arg0, s32 arg1, u8 arg2, s32 arg3);
struct260 *func_151B57F0(s16 arg0, u8 arg1, s32 arg2);
struct260 *func_151932B8(u8 *arg0, s16 arg1, u8 arg2, s32 arg3);
s32 *func_151905AC(u8 *arg0, s32 *arg1);
s32 func_1518FA8C(s32 arg0, u8 arg1, s16 arg2, s8 arg3, s8 arg4, s8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9);
s32 func_15134908(struct_eu_EF410 *arg0, s32 arg1, u8 arg2, s32 arg3);
s32 func_150EA560(u8 *arg0, s16 arg1, u8 arg2, u8 arg3);
void func_150EAA80(u8 *arg0, s16 arg1, u8 arg2, u8 arg3);
void func_150C7520(u8 *arg0, s16 arg1, s32 arg2, s32 arg3);
u8 *func_1519EEE0(s16 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);
void func_1516F868(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void func_1516F730(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void func_15136404(struct127 *arg0, f32 arg1, u8 arg2, s32 arg3);
void func_1504715C(void *out, u8 *obj);
void func_150CAE30(u8 *arg0);
void func_1510965C(void);
u8 *func_15031C4C(u8 *arg0, s32 arg1, s32 arg2);
void func_151C5B38(s32 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4);
void func_151C5C54(u8 *arg0, u8 arg1, s32 arg2);
void func_150FB8A4(u8 *arg0, u8 arg1, s32 arg2);
void func_150E0C58(u8 *arg0, u8 arg1, u8 arg2, s32 arg3);
void func_150F9D6C(u8 *arg0, u8 arg1, s32 arg2);
void func_150F9ED0(u8 *arg0, u8 arg1, s32 arg2);
s32 func_151BEE00(f32 *arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6); /* P98: asm reloads a1 with lwc1 */
void func_150BAEF4(u8 *arg0, u8 arg1, s32 arg2);
void func_151D5BF8(u8 *arg0, u8 arg1, s32 arg2);
void func_15143134(void *arg0, void *arg1, void *arg2);
void func_151C384C(void *arg0, u8 arg1, s32 arg2);
void func_151C9CBC(s32 arg0, s32 arg1);
void func_151080F8(u8 *arg0, s16 arg1, s16 arg2, u8 arg3, s32 arg4);
void func_151CC840(s32 arg0);
void func_1519EFE8(f32 *arg0, u16 arg1, f32 arg2, u8 arg3, s32 arg4);
s32 func_15107C80(u8 *, s16, s16, s16, s32, f32, f32, s32, s32, s8 *, s32, s32);
s32 func_15132454(u8 *arg0, f32 arg1, u8 arg2, s32 arg3);
void func_1507DE4C(struct127 *arg0);
void func_15138C80(struct127 *arg0, s32 arg1, s32 arg2);
void func_15193660(u8 *arg0, u8 arg1, s32 arg2);
void func_151A0A10(u8 *arg0, s16 arg1, u8 arg2, s32 arg3);
void func_15154488(struct_eu_15154488 *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4);
void func_151DBAA8(struct17 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4);
void func_151AFA80(u8 *arg0, u8 arg1, u8 arg2, s32 arg3);
void func_150C2290(s32 arg0);
void func_150C2424(u8 arg0);
void func_1518B7D4(s32 arg0, f32 arg1, f32 arg2, s32 arg3, u8 arg4);
void func_1518B818(s32 arg0, f32 arg1, f32 arg2, s32 arg3, u16 arg4, s32 arg5, u8 arg6);
void func_15171B70(u8 *arg0, u8 arg1, s32 arg2);
void func_15172164(struct127 *arg0, u8 arg1);
void func_15171434(s32 arg0, u8 arg1, s32 arg2);
void func_15171734(u8 *arg0);
void func_1518BC20(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4);
void func_1516F2D8(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void func_150C2804(s32 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5);
void *memcpy(void *s1, const void *s2, size_t n);
/* --- callees still in asm: declared from this function's call sites (arity and widths from the asm) --- */
void func_15177F90(u8 kind, u8 *pos, s32, s32 x, s32 y, s32 z, s32, s32 span, s32 flag, s32, s32 w6);
void func_150B0574(f32 *from, f32 *to, u8 flag, s32);
f32 func_150489B0(u8 angle);
void func_1516FAB8(s32 x, s32 y, s32 z, s32 span, s32 dx, s32, s32 dz, s32, s32, s32, s32, s32, s32, s32, s32, s32 flag, s32);
s32 func_150E2030(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, struct127 *, s32, s32,
                  s32, s32, s32, f32, f32, f32, f32, f32, f32);
struct260 *func_15109990(u8 *obj, s16 span, s8, s8, f32, s32, u8 flag, s32);
void func_150F85AC(u8 *rec, s16 span, u8 flag, s32);
void func_150C4620(u8 *obj, s16 span, u8 flag, s32);
void func_150CFB90(s16 span, u8 flag, s32);
struct260 *func_151925C4(u8 *obj, s16 span, u8 flag, s32);
void func_150FB398(s16 span, u8 flag, s32);
s32 func_151B09BC(u8 *obj, s32, s16 span, u8 flag, s32);
u8 *func_1518D1C0(u8 *obj, s16 kind, s16 span, s32, s32 flag, s32, char *name);
void func_151356D4(f32 *offset, f32, f32, f32, s32, s32, s32, s32 span, s32, s32, s32 flag, s32);
void func_150DBA98(u8 *pos, u8 *, u8 *, u8 *, u8 *, s32 span, s32 flag, s32);
s32 func_1514DA28(s16, s16);
s32 func_1514654C(u8 *obj, u8 *att, s32, f32 **, u8 **, s32);
void func_151CFFFC(u8 *obj, u8 flag, s32);
void func_151C62D0(u8 *obj, u8 b5, s32, u8 *att, s32 kind, s32 flag, s32);
void func_150E0DF0(u8 *obj, u8 flag, s32);
s32 func_15136C3C(struct127 *, s32, s32, s32, s32, s32, s32, s32);
void func_150F1C5C(u8 *obj, u8, u8, u8 flag, s32);
void func_15171100(void *pos, s32, s32, s32, s32 flag, s32);
s32 func_151A74B0(void *spray, s32, u8 flag, s32);
void func_150C1F60(u8 flag);
void func_150DB3F0(u8 *obj, s32, u8 flag, s32);
void func_1514948C(u8 n, f32 x, f32 y, f32 z, s32, s32, s32, f32, s32, f32, f32, s32 flag);
void func_150DBF60(u8 *obj, s32, u8 flag);

/* one 8-byte script event (func_1502AB94's table entry) */
typedef struct {
    s8  type;    /* 0x0B sound, 0x11 table byte, 0x05 effect */
    u8  delta;
    s16 id;      /* sound id / table index / effect sub-type */
    s8  b4;      /* mostly 0 = start, else stop / variant */
    s8  b5;
    s16 w6;
} ScriptEvent;

/* particle spray of sub-types 0x4D / 0x4E (func_151A74B0); 0x28 / 0x2C are left unset */
typedef struct {
    s16 count;
    f32 pos[3];
    s16 unk10;
    f32 unk14;
    s16 unk18, unk1A, unk1C, unk1E;
    f32 unk20, unk24, unk28, unk2C;
    f32 unk30, unk34, unk38, unk3C, unk40, unk44, unk48, unk4C, unk50;
    u8  unk54, unk55;
    s16 unk56, unk58;
} ScriptSpray;

extern u8  *D_800C3D80[4][30];      /* per player and track: byte table written by type 0x11 */
extern s16 *D_eu_800C3C88[4][30];   /* per player and track: s16 x, y, z */
extern s32 *D_800C3A00[4];          /* per player: word table indexed by w6 */
extern s32 D_8008CDF0;
extern u8 *D_8008AF88[];
/* func_151C5280's .s rodata (game_eu_1F3040) is dropped in the NM link: local copy of its first muzzle point */
static const f32 D_800AAE70[3] = { -113.828796f, -14.0823936f, 14.5422001f };
extern char D_80096DEC[];          /* "Cutscene 2" */

extern u8 D_800844D8[3][6];         /* sub 0x11 colour sets (.data) */
/* bone offset tables of sub 0x5F (copied to the stack before use, as the N64 code does: their address is passed on) */
typedef struct { f32 v[3][3]; } ScriptOffsets3;
typedef struct { f32 v[4][3]; } ScriptOffsets4;
typedef struct { f32 v[6][3]; } ScriptOffsets6;
typedef struct { f32 v[2][3]; } ScriptOffsets2;
typedef struct { f32 v[8][3]; } ScriptOffsets8;
static const ScriptOffsets3 sOffsets5F10a = { { { 73, 14, 0 }, { 68, -10, 8 }, { 62, 1, -5 } } };            /* D_80096DF8 */
static const ScriptOffsets4 sOffsets5F10b = { { { -55, -6, -1 }, { -47, -1, -10 }, { -53, -14, 6 }, { -57, 10, 6 } } }; /* D_80096E1C */
static const ScriptOffsets6 sOffsets5F10c = { { { -1, 123, 10 }, { -10, 116, -1 }, { -36, 88, 6 },
                                                { 4, 112, 6 },  { -6, 112, -18 }, { -14, 101, 34 } } };   /* D_80096E4C */
static const s32 sBones5F10[3] = { 0x15, 0x20, 3 };                                                         /* D_80096E94 */
static const s32 sLights5F11[4] = { 6, 7, 8, 9 };                                                           /* D_80096EA0 */
static const ScriptOffsets2 sOffsets5F18 = { { { -65, 172, 9 }, { 15, 63, 9 } } };                          /* D_80096EB0 */
static const ScriptOffsets8 sOffsets5F19 = { { { 0, -14, 18 }, { 0, -14, 18 }, { 0, -14, 18 }, { 0, -14, 18 },
                                               { -5, 25, -7 }, { -11, 28, -5 }, { -4, 30, -4 }, { 3, 30, -8 } } }; /* D_80096EC8 */
static const u8 sBones5F19[8] = { 7, 8, 9, 10, 13, 14, 15, 16 };                                            /* D_80096F28 */

#define O_U8(o, off)  (*(u8 *) ((u8 *) (o) + (off)))
#define O_U16(o, off) (*(u16 *) ((u8 *) (o) + (off)))
#define O_S16(o, off) (*(s16 *) ((u8 *) (o) + (off)))
#define O_S32(o, off) (*(s32 *) ((u8 *) (o) + (off)))
#define O_F32(o, off) (*(f32 *) ((u8 *) (o) + (off)))
#define O_PTR(o, off) (*(u8 **) ((u8 *) (o) + (off)))

/* frames until the next event of this type and id on the track: the effect's duration */
#define SPAN(ev, out) (func_15023C60((u32) (ev), (ev)->type, track, (out), 1, (ev)->id, 0, 0, 0, 0, player) - now)
#define REC(player, track) ((u8 *) &(&D_800C3958)[player][track])
#define OBJ_INDEX(obj) ((s32) ((u8 *) (obj) - (u8 *) D_800CC2D0) / 812)

/* Script event interpreter (middle handler of func_1502AB94). `arg0` is one 8-byte ScriptEvent of track `track` of
 * player `player`; `now` = the current frame, `value` = the byte type 0x11 stores, `obj` / `rec` = the object or the
 * player's D_800C3958 record the track drives, `data` = its position (f32 x, y, z), `flag` = passed on to the effects.
 * Type 0x0B plays / fades / stops a sound, type 0x11 sets a per-track byte, type 0x05 starts effect `id` (most only
 * when b4 == 0; "span" = frames until the next event with the same type and id). Returns 1 when handled, else 0. */
s32 func_150268BC(s32 arg0, u8 track, u16 value, s32 now, s32 player, struct127 *obj, u8 *rec, u8 *data, s32 flag) {
    ScriptEvent *ev = (ScriptEvent *) arg0;
    f32 *pos = (f32 *) data;
    u8 *r;
    u8 *next;   /* out slot of func_15023C60 (never read) */
    s32 span;
    s32 vol;
    s32 i;

    if (ev->type == 0x0B) {   /* sound */
        if (ev->b4 == 0) {
            func_1001263C(ev->id, ev->w6 == 0 ? 0x10000 : (ev->w6 << 16) / 255, 0x40);
        } else if (ev->b4 == 1) {
            span = func_15023C60((u32) ev, ev->type, track, &next, 1, ev->id, 1, 2, 0, 0, player) - now;
            vol = ev->w6 == 0 ? 0x10000 : (ev->w6 << 16) / 255;
            func_151F2D6C(vol, (span * 0x5604) / 50);
        } else if (ev->b4 == 3) {
            func_151F2BA8();
        } else if (ev->b4 == 4) {
            func_151F2BE8();
        } else if (ev->b4 == 5) {
            func_151F2C4C();
        }
        return 1;
    }
    if (ev->type == 0x11) {
        D_800C3D80[player][track][ev->id] = ev->b4 != 0 ? (u8) value : 0xFF;
        return 1;
    }
    if (ev->type != 5) {
        return 0;
    }

    switch (ev->id) {
    case 0x11: {   /* coloured burst: colour set b5, size w6 */
        const u8 *c;
        s32 size;
        s32 k;
        u8 grow;

        span = SPAN(ev, &next);
        if (ev->b4 != 0) {
            break;
        }
        if (ev->w6 == 0) {
            size = 0x1000;
        } else if (ev->w6 > 200) {
            size = ev->w6;
        } else {
            size = 200;
        }
        k = ev->b5 < 3 ? ev->b5 : 0;
        c = D_800844D8[k];   /* N64: from a stack copy of the table taken before the span call */
        grow = (size * 40) / 4096;
        /* a0 / a1: the two halves of the `data` pointer, as the N64 code passes them */
        func_1516DF0C((s16) ((s32) data >> 16), (s16) (s32) data, 0, 0x1B, 0, c[0], c[1], c[2], c[3], c[4], c[5], 0, 1,
                      6, 0, 0, 0, 0, 0, (size >> 3) >> 8, (size >> 3) & 0xFF, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, span, grow,
                      grow, 0xFF, 14, 8, 8, 0x25, 0, 0xFF, 8, 0, 0, player, 0, 0, flag, 0);
        break;
    }
    case 0x0A:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            func_151BA1A0(3, 3, 0, 0, 0, 800, 1200, 400, 200, 0x66, 0x1C7, 2, span, (s32) data, flag, 0);
        }
        break;
    case 0x0B:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            func_151BA1A0(0x2F, 1, 0, 0, 0, 2000, 1000, 400, 200, 0x400, 0x400, 6, span, (s32) data, flag, 0);
        }
        break;
    case 0x0C: {
        struct {
            s32 unk0;
            s16 unk4, unk6, x, y, z, unkE, unk10;
            s8 unk12;
            s8 unk13;
            s8 unk14;
        } s;
        s.unk4 = 0;
        s.unk6 = 0x100;
        s.unk0 = D_8008CDF0;
        s.x = pos[0];
        s.y = pos[1] + ev->b4;
        s.unkE = 1500;
        s.unk10 = 1500;
        s.unk12 = -10;
        s.unk14 = 0;
        s.z = pos[2];
        func_15167AD8(&s, (u8) flag, 1);
        break;
    }
    case 0x19:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            func_15177F90(ev->b5 != 0 ? ev->b5 : 12, data, 0xFF, pos[0], pos[1], pos[2], 0, span, flag, 0, ev->w6);
        }
        break;
    case 0x1A: {
        s16 *p = D_eu_800C3C88[player][track];
        f32 from[3], to[3];
        if (ev->b4 == 1) {
            from[0] = p[0];
            from[1] = p[1];
            r = REC(player, track);
            from[2] = p[2];
            to[0] = O_F32(r, 0);
            to[1] = O_F32(r, 0x38) + O_F32(r, 4);
            to[2] = O_F32(r, 8);
            func_150B0574(from, to, (u8) flag, 1);
        } else {
            r = REC(player, track);
            func_150E2030(0, p[0], p[1], p[2], O_F32(r, 0), O_F32(r, 0x38) + O_F32(r, 4), O_F32(r, 8), 40.0f, 0.0f, 8.0f,
                          60.0f, 600, 35, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        }
        break;
    }
    case 0x1C:
        if (obj != NULL && (ev->b4 == 0 || ev->b4 == 1)) {
            func_150E3334((s32) obj, O_U8(obj, 0x3B), ev->b4 == 0 ? 3 : 2, -1, 0.0f, 0.0f, 156.0f, 0.0f, 0.0f, 636.0f, 3,
                          10, 0xF0, 0);
        }
        break;
    case 0x1B:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            switch ((u16) ev->w6) {
            case 0:
                func_1516ECE8((u32) data, span, ev->b5, (u8) flag, 0);
                break;
            case 1:
                func_150BF47C(span);
                break;
            case 2: {   /* two sprays either side of the object, along its yaw */
                f32 x = O_F32(obj, 0x14);
                f32 y = O_F32(obj, 0x18);
                f32 z = O_F32(obj, 0x1C);
                u8 angle = O_U16(obj, 0x7A) >> 8;
                f32 sn = func_15048A40(angle);
                f32 cs = func_150489B0(angle);
                func_1516FAB8(x + 20.0f, y + 475.0f, z, span, 14.0f * sn, 0xB00, 14.0f * cs, 200, 50, 10, 6, 7, 0xBE,
                              0xBE, 0xBE, (u8) flag, 0);
                func_1516FAB8(x - 24.0f, y + 476.0f, z, span, -23.0f * sn, 0x800, -23.0f * cs, 200, 50, 10, 6, 7, 0xBE,
                              0xBE, 0xBE, (u8) flag, 0);
                break;
            }
            case 3:
                func_151DCE6C(data, span, 1, 1, flag, 0);
                break;
            case 4:
                func_151DCE6C(data, span, 0, 0, flag, 0);
                break;
            }
        }
        break;
    case 0x1F:
        if (obj != NULL) {
            func_150BA4C0((u8 *) obj, (u8) flag, 1);
        }
        break;
    case 0x00:
        if (obj != NULL) {
            func_151A3940((u8 *) obj, (u8) flag);
        }
        break;
    case 0x20:
        func_151664F0(-1, pos[0], pos[1], pos[2], 20, 20, 1, flag, 1);
        break;
    case 0x06:
    case 0x3E:
    case 0x3F:
    case 0x2A:
        break;
    case 0x07:
        func_150B2974((u8 *) obj, 9, -1);
        break;
    case 0x21:
        if (ev->b4 == 0) {
            func_15136A50((s32) data, (s32) (data + 4), (s32) (data + 8), SPAN(ev, &next), flag, 0);
        }
        break;
    case 0x60:
        if (ev->b4 == 0) {
            func_150CE660((u8 *) obj, SPAN(ev, &next), (u8) flag, 0);   /* 4th argument 0 (P80) */
        }
        break;
    case 0x65:
        if (ev->b4 == 2) {
            if (ev->b5 == 0x11 || ev->b5 == 0x12 || ev->b5 == 0x15) {
                s8 level = ev->w6;
                func_151494E0((s32) &level, 0x51);
            } else if (ev->b5 == 0x13) {
                func_150D0148(ev->w6 * 0.01f * 300.0f - 150.0f);
            }
        }
        if (ev->b4 != 0) {
            break;
        }
        span = func_15023C60((u32) ev, ev->type, track, &next, 1, ev->id, 1, 1, 1, ev->b5, player) - now;
        switch (ev->b5) {
        case 1:
            func_15109990((u8 *) obj, span, -1, 0, 0.00071f, 0, flag, 1);
            break;
        case 2:
            func_15109990((u8 *) obj, span, -1, 1, 0.006125f, 0, flag, 1);
            break;
        case 3:
            func_1510A454(rec, span, -1, 0, 0.006125f, 0, flag, 1);
            break;
        case 4:
            func_1510A454(rec, span, -1, 1, 0.006125f, 0, flag, 1);
            break;
        case 5:
            func_1510A8C4((u8 *) obj, span, (u8) flag, 1);
            break;
        case 6:
            func_151619A0(track, span, (u8) flag, 1);
            break;
        case 7:
            func_1510957C(track, span, (u8) flag);
            break;
        case 8: {
            f32 p[3];
            r = REC(player, track);
            p[0] = O_F32(r, 0);
            p[1] = O_F32(r, 4);
            p[2] = O_F32(r, 8);
            func_151A9940(5, 1, NULL, (s32) p, -10000.0f, 100.0f, span, (u8) flag, 1);
            break;
        }
        case 9: {
            struct {
                struct127 *obj;
                u8 index;
                s16 span;
                u8 unk8, unk9, kind;
            } s;
            s.obj = obj;
            s.span = span;
            s.unk8 = 1;
            s.unk9 = 0;
            s.index = O_U8(obj, 0x3B);
            switch (O_U8(obj, 4)) {
            case 0x57:
            case 0x71:
                s.kind = 1;
                break;
            case 0x96:
                s.kind = 3;
                break;
            default:
                s.kind = 0;
                break;
            }
            func_15190770((u8 **) &s, 0, (u8) flag, 1);
            break;
        }
        case 10:
            func_150F85AC(REC(player, track), span, (u8) flag, 1);
            break;
        case 11: {
            struct260 *e;
            s16 zero[2];
            func_150AFC18(span, (u8) flag, 1);
            zero[0] = 0;
            zero[1] = 0;
            e = func_15149130(span, -1, 0x4B, -1, 1, 0, (struct37 *) 4, (u8) flag, 1);
            if (e != NULL) {
                memcpy((u8 *) e + 0x28, zero, 4);
            }
            break;
        }
        case 12:
            func_150F6188((u8 *) obj, span, (u8) flag, 1);
            break;
        case 13:
            func_1519F0FC(REC(player, track), (u16) ev->w6 < 0xE9 ? ev->w6 : 0, span, (u8) flag, 1);
            break;
        case 15:
            if (obj != NULL && span > 0) {
                O_S32(obj, 0x2EC) = 1;
                O_F32(obj, 0x2D8) = span * 0.5f;
                O_F32(obj, 0x2DC) = 1.0f / O_F32(obj, 0x2D8);
                func_150C4620((u8 *) obj, span, (u8) flag, 1);
            }
            break;
        case 16:
            if (obj != NULL && span > 0) {
                func_150F6E10((u8 *) obj, span, (u8) flag, 1);
            }
            break;
        case 17:
            func_150D0644(ev->w6 & 0xFF, D_800C3A00[player][ev->w6], span, (u8) flag, 1);
            break;
        case 18:
            func_150D07C4(ev->w6 & 0xFF, D_800C3A00[player][ev->w6], span, (u8) flag, 1);
            break;
        case 19:
            func_150CFB90(span, (u8) flag, 1);
            break;
        case 20:
            func_151925C4((u8 *) obj, span, (u8) flag, 1);
            break;
        case 21:
            func_150D09D4(ev->w6 & 0xFF, D_800C3A00[player][ev->w6], span, (u8) flag, 1);
            break;
        case 22:
            func_1519F2F4(REC(player, track), (u16) ev->w6 < 0xCF ? (u16) ev->w6 : 0, span, (u8) flag, 1);
            break;
        case 23:
            func_150FB398(span, (u8) flag, 1);
            break;
        case 24: {   /* splash on the floor below the record, unless the surface is of kind 3 */
            f32 p[3];
            f32 probe[3];
            struct {
                f32 y;
                u8 pos[0x18];
                u8 flags;
                u8 surface;   /* +0x1D */
                u8 pad[0x6];
            } hit;
            s32 found;
            f32 ra;
            f32 rb;
            r = REC(player, track);
            p[0] = O_F32(r, 0);
            p[1] = O_F32(r, 4) + 100.0f;
            p[2] = O_F32(r, 8);
            probe[0] = p[0];
            probe[1] = p[1] + 100.0f;
            probe[2] = p[2];
            if (func_15046F70((u8 *) probe, 0, p[1] - 1000.0f, (u8 *) &hit) != 0 && hit.surface != 3) {
                found = 1;
                p[1] = hit.y;
            } else {
                found = 0;
            }
            if (found) {
                ra = func_150ADA68();
                rb = func_150ADA68();
                func_15136698(ra * 0.020000001f + 0.09f, rb * 0.00043999997f + 0.00087999995f,
                              (u32) func_150ADA20() % 101 + 0x9B, 0xFF, span, (s32) hit.pos, (struct17 *) p,
                              ev->w6 == 0, 1, flag, 1);
            }
            break;
        }
        case 25: {
            s16 *q = D_eu_800C3C88[player][track];
            f32 from[3];
            s32 to[3];
            r = REC(player, track);
            from[0] = q[0];
            from[1] = q[1];
            from[2] = q[2];
            to[0] = O_F32(r, 0);
            to[1] = O_F32(r, 4);
            to[2] = O_F32(r, 8);
            func_150E38C0((u8 *) from, (u8 *) to, (s32) r, span);
            break;
        }
        case 26: {
            structEU_151D8E18 s;
            s.unk0 = 1;
            s.unk4 = 8;
            s.unk5 = 1;
            s.unk6 = -1;
            s.unk2 = span;
            func_151D8E18(&s, 0, (u8) flag, 1);
            break;
        }
        }
        break;
    case 0x5B:
        if (ev->b4 == 0) {
            func_151B57F0(SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x5D:
        if (ev->b4 == 0) {
            func_151932B8((u8 *) obj, SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x5E:
        if (ev->b5 == 1) {
            func_151B09BC((u8 *) obj, 0, 1000, (u8) flag, 0);
        } else if (ev->b4 == 0) {
            func_151B09BC((u8 *) obj, 0, SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x4C:
        if (ev->b4 == 0) {
            u8 kind = O_U8(obj, 4);
            span = SPAN(ev, &next);
            if (kind == 0x49 || kind == 0x58) {
                s32 n;
                u8 *list = (u8 *) func_151905AC((u8 *) obj, &n);
                if (list != NULL && ev->w6 < n) {
                    func_1518FA8C((s32) obj, list[ev->w6], span, -1, -1, -1, 0, 0, flag, 1);
                }
            } else {
                func_1518D1C0((u8 *) obj, ev->b5, span, 0, flag, 1, D_80096DEC);
            }
        }
        break;
    case 0x53:
        if (ev->b4 == 0) {
            struct_eu_EF410 s;
            span = SPAN(ev, &next);
            s.unk4 = (s32) (data + 4);
            s.unk8 = (s32) (data + 8);
            s.unk0 = (s32) data;
            s.unk14 = span;
            s.unk16 = 1;
            s.unk17 = 2;
            s.unkC = 2.0f;
            s.unk10 = 1.0f;
            func_15134908(&s, 0, (u8) flag, 0);
        }
        break;
    case 0x50:
        if (ev->b4 == 0) {
            func_150EA560((u8 *) obj, SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x51:
        if (ev->b4 == 0) {
            func_150EAA80((u8 *) obj, SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x48:
        if (ev->b4 == 0) {
            f32 offset[2];
            f32 ra, rb, rc;
            u32 rd;
            span = func_15023C60((u32) ev, ev->type, track, &next, 1, ev->id, 0, 0, 1, ev->b5, player) - now;
            offset[0] = func_150ADA68() * 200.0f + -100.0f;
            offset[1] = func_150ADA68() * 300.0f + -150.0f;
            ra = func_150ADA68();
            rb = func_150ADA68();
            rc = func_150ADA68();
            rd = func_150ADA20();
            func_151356D4(offset, ra * 20.0f + 10.0f, (rb * 65.0f + 35.0f) * 0.001f, (rc * 160.0f + 200.0f) * 0.001f,
                          rd % 101 + 100, 0xFF, (u32) func_150ADA20() % 3 + 4, span, 4, 0x40, flag, 1);
        }
        break;
    case 0x0F:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            func_150C7520((u8 *) obj, span, (u8) flag, 1);
        }
        break;
    case 0x32:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            r = REC(player, track);
            func_150DBA98(data, r + 0x10, r + 0x18, r + 0x1C, r + 0x20, span, flag, 0);
        }
        break;
    case 0x34:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            u8 idx = 0;   /* N64: an uninitialised stack byte when b5 < 0 */
            u8 *node;
            if (ev->b5 >= 0) {
                idx = 13;
            }
            for (node = O_PTR(obj, 0x2F4); node != NULL; node = O_PTR(node, 0x14)) {
                if (idx == O_S16(node, 0x1C) || func_1514DA28(O_S16(D_8008AF88[idx], 4), O_S16(node, 0x1C)) != 0) {
                    r = REC(player, track);
                    O_S32(O_PTR(node, 0x10), 0x30) =
                        (s32) func_1519EEE0(span, (s32) O_PTR(node, 0x10), 0, (s32) (r + 0x30), (s32) (r + 0x20), flag, 0);
                }
            }
        }
        break;
    case 0x23:
        if (obj != NULL) {
            span = SPAN(ev, &next);
            if (ev->b4 == 0) {
                func_1516F868(OBJ_INDEX(obj), span, span, 0, flag, 0);
            }
        }
        break;
    case 0x22:
        if (obj != NULL) {
            span = SPAN(ev, &next);
            if (ev->b4 == 0) {
                func_1516F730(OBJ_INDEX(obj), span, (u8) flag, 0);
            }
        }
        break;
    case 0x52:
        if (obj != NULL) {
            func_15136404(obj, 90.0f, (u8) flag, 1);
        }
        break;
    case 0x5F:
        switch ((u8) ev->b4) {
        case 0:   /* drop on the floor below the object */
            if (obj != NULL) {
                struct {
                    f32 y;
                    u8 rest[0x20];
                } hit;
                f32 probe[3];
                f32 p[3];
                func_1504715C(&hit, (u8 *) obj);
                probe[0] = O_F32(obj, 0x14);
                probe[1] = O_F32(obj, 0x18) + 100.0f;
                probe[2] = O_F32(obj, 0x1C);
                if (func_15046F70((u8 *) probe, 0, O_F32(obj, 0x18) - 300.0f, (u8 *) &hit) != 0) {
                    p[0] = probe[0];
                    p[1] = hit.y;
                    p[2] = probe[2];
                    func_150CAE30((u8 *) p);
                }
            }
            break;
        case 1:
            func_1510965C();
            break;
        case 2:
            if (obj != NULL) {
                switch (O_U8(obj, 4)) {
                case 0x4A:
                    func_150E0C58((u8 *) obj, ev->b5, (u8) flag, 1);
                    break;
                case 0x5A:
                case 0x74:
                case 0x75:
                case 0x7A: {
                    u8 *att = func_15031C4C((u8 *) obj, 0x46, 0);
                    if (att != NULL) {
                        u8 buf[16];
                        f32 *src = D_800AAE70;
                        u8 *dst = buf;
                        if (func_1514654C((u8 *) obj, att, 0, &src, &dst, 1) != 0) {
                            func_151C5B38((s32) obj, (s32) buf, 0x46, (u8) flag, 1);
                            func_151C5C54(buf, (u8) flag, 1);
                        }
                    }
                    break;
                }
                case 0x86:
                    func_150FB8A4((u8 *) obj, (u8) flag, 1);
                    break;
                case 0x97:
                    func_150F9D6C((u8 *) obj, (u8) flag, 1);
                    break;
                case 0x98:
                    func_150F9ED0((u8 *) obj, (u8) flag, 1);
                    break;
                }
            }
            break;
        case 3: {
            f32 p[3];
            r = REC(player, track);
            p[0] = O_F32(r, 0);
            p[1] = O_F32(r, 4);
            p[2] = O_F32(r, 8);
            func_151BEE00(p, O_F32(r, 0x10), 1, 0, 2, flag, 1);
            break;
        }
        case 4:
            func_151CFFFC((u8 *) obj, (u8) flag, 1);
            break;
        case 5:
            if (obj != NULL) {
                u8 *att = NULL;
                if (ev->w6 != 0) {
                    att = func_15031C4C((u8 *) obj, ev->b5 != 0 ? 0xA4 : 0xA5, 0);
                }
                func_151C62D0((u8 *) obj, ev->b5, 1, att, ev->b5 != 0 ? 0xA4 : 0xA5, flag, 1);
            }
            break;
        case 6:
            func_150BAEF4((u8 *) obj, 9, -1);
            break;
        case 7:
            func_150E0DF0((u8 *) obj, (u8) flag, 1);
            break;
        case 8: {
            f32 p[3];
            p[0] = pos[0];
            p[1] = pos[1];
            p[2] = pos[2];
            func_151D5BF8((u8 *) p, (u8) flag, 1);
            break;
        }
        case 9:
            func_15136C3C(obj, 1, 1, 1, 1, 0, flag, 1);
            break;
        case 10:   /* random offset from one of three bones */
            if (O_PTR(obj, 0x1D4) != NULL) {
                ScriptOffsets3 a = sOffsets5F10a;
                ScriptOffsets4 b = sOffsets5F10b;
                ScriptOffsets6 c = sOffsets5F10c;
                f32 *entry = a.v[0];   /* N64: uninitialised when b5 is not 0..2 */
                f32 out[3];
                switch (ev->b5) {
                case 0:
                    entry = a.v[(u32) func_150ADA20() % 3];
                    break;
                case 1:
                    entry = b.v[func_150ADA20() & 3];
                    break;
                case 2:
                    entry = c.v[(u32) func_150ADA20() % 6];
                    break;
                }
                func_15143134(entry, out, O_PTR(obj, 0x1D4) + (sBones5F10[ev->b5] << 6));
                func_151C384C(out, (u8) flag, 1);
            }
            break;
        case 11: {
            u8 k = 0;
            do {
                func_151C9CBC(1, (s32) (D_800D34B8 + sLights5F11[k] * 0x34));
                k++;
            } while (k < 4);
            break;
        }
        case 12: {
            s32 ra = func_150ADA20();
            func_151080F8((u8 *) obj, ra & 0xFF, (func_150ADA20() & 0x7F) - 0x40, (u8) flag, 1);
            break;
        }
        case 13:
            func_151CC840((s32) D_800DBFF0);
            break;
        case 14: {
            f32 p[3];
            p[0] = pos[0];
            p[1] = pos[1];
            p[2] = pos[2];
            func_1519EFE8(p, (u16) ev->b5 < 0xE9 ? (u16) ev->b5 : 0, ev->w6 != 0 ? ev->w6 * 0.01f : 1.0f, (u8) flag, 1);
            break;
        }
        case 15: {   /* blue-white sparks */
            s8 colour[4];
            f32 size;
            s32 ra;
            u32 rb;
            colour[0] = 0xAE;
            colour[1] = 0xD2;
            colour[2] = 0xFF;
            colour[3] = (u32) func_150ADA20() % 61 + 150;
            size = func_150ADA68() * 20.0f + 25.0f;
            if (ev->b5 != 0) {
                size *= 0.35f;
            }
            ra = func_150ADA20();
            rb = func_150ADA20();
            func_15107C80((u8 *) obj, ra & 0xFF, rb % 129 - 63, (u32) func_150ADA20() % 21 + 10, 4, 40.0f, size, 0, 2,
                          colour, flag, 1);
            break;
        }
        case 16:
            func_150F1C5C((u8 *) obj, ev->b5, ((u8 *) ev)[7], (u8) flag, 1);
            break;
        case 17: {
            structEU_151D8E18 s;
            s.unk0 = 1;
            s.unk2 = 50;
            s.unk4 = 8;
            s.unk5 = 1;
            s.unk6 = -1;
            func_151D8E18(&s, 0, (u8) flag, 1);
            break;
        }
        case 18:
            if (O_PTR(obj, 0x1D4) != NULL) {
                ScriptOffsets2 t = sOffsets5F18;
                f32 out[3];
                func_15143134(t.v[ev->b5], out, O_PTR(obj, 0x1D4));
                func_15132454((u8 *) out, 0.646f, (u8) flag, 0);
            }
            break;
        case 19:
            if (O_PTR(obj, 0x1D4) != NULL) {
                ScriptOffsets8 t = sOffsets5F19;
                f32 out[3];
                func_15143134(t.v[ev->b5], out, O_PTR(obj, 0x1D4) + (sBones5F19[ev->b5] << 6));
                func_15132454((u8 *) out, 6.9900002f, (u8) flag, 0);
            }
            break;
        case 20: {
            struct {
                u8 unk0[0x10];   /* not set */
                s16 x, y, z;
            } s;
            r = REC(player, track);
            s.x = O_F32(r, 0);
            s.y = O_F32(r, 4) + 50.0f;
            s.z = O_F32(r, 8);
            func_15171100(&s, 1, 1, 2, flag, 0);
            break;
        }
        case 21:
            if (obj != NULL) {
                func_1507DE4C(obj);
                func_15138C80(obj, (u8) flag, 0);
            }
            break;
        case 22:
            if (obj != NULL) {
                func_15193660((u8 *) obj, (u8) flag, 0);
            }
            break;
        }
        break;
    case 0x40:
        func_151A0A10((u8 *) obj, 0x28, (u8) flag, 1);
        break;
    case 0x4D: {
        ScriptSpray s;
        s.count = (u32) func_150ADA20() % 5 + 5;
        s.pos[0] = pos[0];
        s.pos[1] = pos[1];
        s.pos[2] = pos[2];
        s.unk14 = 4.7000003f;
        s.unk24 = 15.5f;
        s.unk20 = 24.800001f;
        s.unk3C = 0.26700002f;
        s.unk10 = 90;
        s.unk18 = -7;
        s.unk1A = 45;
        s.unk1C = -52;
        s.unk1E = 32;
        s.unk54 = 0;
        s.unk55 = 0;
        s.unk56 = 50;
        s.unk58 = 25;
        s.unk40 = 0.24300002f;
        s.unk44 = -2.0410001f;
        s.unk30 = 0.0f;
        s.unk34 = 0.0f;
        s.unk38 = 0.0f;
        s.unk4C = -3.0f;
        s.unk48 = 0.0f;
        s.unk50 = 6.0f;
        func_151A74B0(&s, 1, (u8) flag, 1);
        break;
    }
    case 0x4E: {
        ScriptSpray s;
        s.count = (u32) func_150ADA20() % 6 + 6;
        s.pos[0] = pos[0];
        s.pos[1] = pos[1];
        s.pos[2] = pos[2];
        s.unk14 = 151.5f;
        s.unk24 = 25.2f;
        s.unk20 = 15.1f;
        s.unk3C = 0.388f;
        s.unk10 = 90;
        s.unk1A = 0xFF;
        s.unk18 = 0;
        s.unk1C = -64;
        s.unk1E = 40;
        s.unk54 = 0;
        s.unk55 = 0;
        s.unk56 = 50;
        s.unk58 = 25;
        s.unk40 = 0.24300002f;
        s.unk44 = -1.0200001f;
        s.unk30 = 0.0f;
        s.unk34 = 0.0f;
        s.unk38 = 0.0f;
        s.unk4C = -4.0f;
        s.unk48 = 0.0f;
        s.unk50 = 8.0f;
        func_151A74B0(&s, 1, (u8) flag, 1);
        break;
    }
    case 0x4F: {
        struct_eu_15154488 s;
        s.unk8.unk0 = pos[0];
        s.unk8.unk4 = pos[1];
        s.unk8.unk8 = pos[2];
        s.unk2C = 15;
        s.unk2E = 10;
        s.unk0 = -20;
        s.unk14 = 2.9f;
        s.unk2 = 49;
        s.unk4 = -52;
        s.unk6 = 43;
        s.unk30 = 3;
        s.unk18 = 17.0f;
        s.unk32 = 4;
        s.unk34 = 40;
        s.unk36 = 30;
        s.unk38 = 100;
        s.unk3A = 100;
        s.unk3C = 0;
        s.unk44 = 16;
        s.unk46 = 15;
        s.unk48 = 0;
        s.unk1C = 2.5f;
        s.unk20 = 0.577f;
        s.unk24 = 25.0f;
        s.unk28 = 20.2f;
        s.unk40 = 0.5f;
        func_15154488(&s, &s.unk8, 0, (u8) flag, 1);
        break;
    }
    case 0x24: {
        f32 p[3];
        u8 kind;
        p[0] = pos[0];
        p[1] = pos[1];
        p[2] = pos[2];
        kind = ev->b5;
        if (kind >= 13) {
            kind = 0;
        }
        func_151DBAA8((struct17 *) p, ev->b4 != 0 ? ev->b4 : 10, kind, (u8) flag, 0);
        break;
    }
    case 0x10: {
        u8 kind = ev->b4;
        if (kind >= 27) {
            kind = 0;
        }
        func_151AFA80((u8 *) obj, kind, (u8) flag, 0);
        break;
    }
    case 0x47:
        func_151925C4((u8 *) obj, 50, (u8) flag, 0);
        break;
    case 0x2E:
        func_150C1F60((u8) flag);
        func_150C2290((u8) flag);
        func_150C2424((u8) flag);
        break;
    case 0x31:
        func_150DB3F0((u8 *) obj, 0, (u8) flag, 0);
        break;
    case 0x33: {
        u8 n = ev->b4 >= 16 ? 15 : (u8) ev->b4;
        f32 scale;
        s32 b5;
        r = REC(player, track);
        b5 = 100;
        scale = O_F32(r, 0x1C) * 0.1f;
        if (ev->b5 != 0) {
            b5 = ev->b5;
        }
        func_1514948C(n, pos[0], pos[1], pos[2], O_F32(r, 0x20) * 0.05f, (O_F32(r, 0x10) + 180.0f) * 0.7111111f,
                      O_F32(r, 0xC) * 0.7111111f, O_F32(r, 0x38) * 0.1f + 0.5f, b5, O_F32(r, 0x18) * 0.1f + 1.0f, scale,
                      flag);
        break;
    }
    case 0x35:
        func_150DBF60((u8 *) obj, ev->b4 >= 2 ? 1 : ev->b4, (u8) flag);
        break;
    case 0x26:
        if (obj != NULL) {
            span = SPAN(ev, &next);
            if (ev->b4 == 0) {
                O_U8(obj, 0x276) = 1;
                O_S16(obj, 0x282) = span;
            }
        }
        break;
    case 0x27:
    case 0x02: {
        f32 speed = 1.0f;
        f32 len = 30.0f;
        s32 n = 1;
        if (ev->b4 != 0) {
            n = ev->b4;
        }
        if (ev->b5 != 0) {
            speed = ev->b5 * 0.1f;
        }
        if (ev->w6 >= 0) {
            len = ev->w6;
        }
        if (ev->id == 0x27) {
            func_1518B7D4((s32) data, len, speed, n, flag);
        } else {
            func_1518B818((s32) data, len, speed, n, 30, 100, (u8) flag);
        }
        break;
    }
    case 0x28:
        if (rec != NULL) {
            func_15171B70(rec, (u8) flag, 0);
        } else if (obj != NULL) {
            func_15172164(obj, (u8) flag);
        }
        break;
    case 0x29:
        if (rec != NULL) {
            func_15171434((s32) rec, (u8) flag, 0);
        } else if (obj != NULL) {
            func_15171734((u8 *) obj);
        }
        break;
    case 0x2B:
        func_1518BC20(pos[0], pos[1], pos[2], (u8) flag, 0);
        break;
    case 0x2C:
        SPAN(ev, &next);
        break;
    case 0x2F:
        if (obj != NULL && ev->b4 == 0) {
            func_1516F2D8(OBJ_INDEX(obj), SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x39:
        if (ev->b4 == 0) {
            func_150C2804((s32) data, (s32) (data + 4), (s32) (data + 8), SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x3A: {
        f32 p[3];
        p[0] = pos[0];
        p[1] = pos[1];
        p[2] = pos[2];
        func_151DBAA8((struct17 *) p, ev->b4 != 0 ? ev->b4 : 10, 6, (u8) flag, 0);
        break;
    }
    default:
        return 0;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_150268BC.s")
#endif

#ifdef NON_MATCHING
extern s32 D_800C39D0;
extern u8 D_800844A0[];  /* screen fade colours, 3 bytes (r, g, b) per entry */
extern s8 D_800C40AA;
extern u16 D_800C40AE;
s32 func_15023C60(u32 arg0, s32 arg1, s32 arg2, u8 **arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);
void func_15023EC4(u8 **, u8 **, s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15023988(u8 *, s32 *, u32 *, s32 *, s32 *, s32 *, u16 *);
s32 func_1000E134(s32);
void func_1000D96C(s32, s32, s32);
void func_1000DE1C(s32, s32);
void func_1517946C(s32);
void func_151D6CA0(s32, s32);
void func_15188EBC(s32, s32, s32);
void func_15188D80(struct127 *, s32, s32);
void func_15189040(s32);
void func_15155D6C(s32, s32, f32);
void func_15156500(void);
void func_1503DE70(struct127 *, s32, s32);
void func_150F59A0(s32, s32, s32, s32);
void func_1517F3B0(s32, s32, s32, s32, s8, s32);
void *allocate_memory(s32, s32, s32, s32);

/* the span (frames from now) to the next event of this track matching the type / id (and b4 / b5 when given) */
#define NEXT(out, useB4, b4v, useB5, b5v) \
    (func_15023C60((u32) ev, (s8) ev[0], track, (out), 1, *(s16 *) (ev + 2), (useB4), (b4v), (useB5), (b5v), player) - now)

// scene_event_run_c: third scene event handler (after func_15024910 / func_150268BC): sounds and music, object
// animations and the screen fade. ev = the 8-byte event (s8 type, u8 delta, s16 id, s8 b4, s8 b5, s16 w6), now the
// track time, obj / wrec the track's object / world record, data its position (f32 x, y, z); replay = 1 while the
// scene is fast-forwarded (then most cases only restore end states). Returns 1 when the event was handled.
//   6 / 0xA: positional sound id (volume w6, 0 = 0xFF) on func_1000FA64 with the update callback func_15023988;
//            0xA stops at its b4 1 event and fades in / out to its b4 2 / 3 events, 6 plays to the end (flags
//            0x400, 0x800 for b4 2). 8: music id (b4 0 start, 1 / 4 volume, 2 / 6 fade, 8 / 9 other controls).
//   2: object animation id with blend w6 - 1 frames, speed so that it lasts to the next type-2 event.
//   5 / 1: screen fade to colour D_800844A0[b5] over the span to the b4 1 event (w6 0 = fade in); in replay the
//          b4 != 0 event re-applies the last one. 5 / 4, 0x5C, 0x56, 0x76, 0x2D, 0x57: see the cases.
s32 func_15029EA8(s32 arg0, u8 track, u16 value, s32 now, s32 player, struct127 *obj, u8 *wrec, u8 *data, s32 flag,
                  s32 replay) {
    u8 *ev = (u8 *) arg0;
    s32 type = (s8) ev[0];
    u8 *next;
    u8 *prev;
    s32 prevTime;
    s32 span;
    s32 t;

    if (type == 6 || type == 0xA) {
        s32 vol;
        s32 fadeIn;
        s32 fadeOut;
        s32 flags;
        u8 *r;

        next = NULL;
        flags = 0;
        if ((s8) ev[4] != 0 && (s8) ev[0] != 6) {
            return 1;
        }
        if (*(s16 *) (ev + 6) == 0) {
            vol = 0xFF;
        } else {
            vol = *(s16 *) (ev + 6) & 0xFF;
        }
        span = NEXT(&next, 1, 1, 0, 0);
        if ((s8) ev[0] == 6 || next == NULL) {
            span = 0xFFFF;
        }
        if (replay != 0 && ((s8) ev[0] != 0xA || next != NULL)) {
            return 1;
        }
        fadeOut = 0;
        fadeIn = 0;
        if ((s8) ev[0] == 0xA) {
            t = NEXT(&next, 1, 2, 0, 0) + now;
            if (next != NULL && t - now < span) {
                fadeIn = t - now;
            }
            t = NEXT(&next, 1, 3, 0, 0) + now;
            if (next != NULL && t - now < span) {
                fadeOut = span - (t - now);
            }
        } else if ((s8) ev[4] == 2) {
            flags = 0x800;
        } else {
            flags = 0x400;
        }
        r = allocate_memory(0x10, 1, 0, 0);
        if (r != NULL) {
            r[0] = player;
            r[0xE] = (&D_800C3A08)[player];
            *(u16 *) (r + 4) = span;
            *(u16 *) (r + 6) = span;
            r[1] = track;
            *(u16 *) (r + 8) = fadeIn;
            *(u16 *) (r + 0xC) = (vol * 0x7FFF) >> 8;
            *(u16 *) (r + 0xA) = fadeOut;
            r[2] = (s8) ev[0] == 0xA;
            func_1000FA64(*(u16 *) (ev + 2), *(f32 *) (data + 0), *(f32 *) (data + 4), *(f32 *) (data + 8),
                          *(u16 *) (r + 0xC), 0x7D00, 0x7918, (s32) func_15023988, r, 0, flags, (s8) ev[5] * 50);
        }
        return 1;
    }
    if (type == 8) {
        s32 id = *(s16 *) (ev + 2);
        s32 w6 = *(s16 *) (ev + 6);
        s32 bit = 1 << (((s8) ev[5] + 31) & 0x1F); /* 1 << (b5 - 1), b5 0 -> bit 31 (MIPS sllv) */

        switch ((s8) ev[4]) {
            case 0:
                if (replay != 0 && func_1000E134(id) != 0) {
                    return 1;
                }
                func_1000D96C(id, 0, 0);
                return 1;
            case 1:
                func_1000E588(id, w6 * 100, bit);
                return 1;
            case 2:
                func_1000DF68(id, w6 * 328, 1);
                return 1;
            case 3:
                return 1;
            case 4:
                t = func_15023C60((u32) ev, type, track, &next, 1, id, 1, 5, 1, (s8) ev[5], player) - now;
                if (replay != 0) {
                    func_1000E588(id, w6, bit);
                } else {
                    func_1000E46C(id, w6, bit, t);
                }
                return 1;
            case 6:
                t = func_15023C60((u32) ev, type, track, &next, 1, id, 1, 7, 0, 0, player) - now;
                if (t < 2) {
                    t = 1;
                }
                func_1000DF68(id, w6 * 328, t);
                return 1;
            case 8:
                func_1000E654(id, w6 + 1, 0, -1);
                return 1;
            case 9:
                func_1000DE1C(id, 0);
                return 1;
        }
        return 1;
    }
    if (type == 2) {
        f32 frames;
        f32 blend;
        f32 speed;
        s32 mode;
        s16 anim;

        if (obj == NULL) {
            return 1;
        }
        frames = func_15023C60((u32) ev, type, track, &next, 0, 0, 0, 0, 0, 0, player) - now;
        if ((s8) ev[4] != 0) {
            return 1;
        }
        if (*(u8 **) ((u8 *) obj + 0x2D0) == NULL) {
            return 1;
        }
        blend = 5.0f;
        anim = *(s16 *) (ev + 2);
        if (*(s16 *) (ev + 6) > 0) {
            blend = *(s16 *) (ev + 6) - 1;
        }
        mode = 1;
        if (D_800C40AE >= now) {
            blend = 0.0f;
        }
        if (replay != 0) {
            blend = 0.0f;
        }
        if (next != NULL) {
            mode = (s8) next[4] == 0;
            if ((s8) next[4] == 1 && (s8) next[5] == 1) {
                mode = 1;
            }
        }
        if (anim != *(u16 *) ((u8 *) obj + 0x84)) {
            func_1505E650(obj, anim, 1.0f, blend, 0.0f, 0.0f, mode);
        }
        if (frames > 0.0f) {
            speed = 2.0f * (*(f32 *) (*(u8 **) ((u8 *) obj + 0x2D0) + 0x18) / frames);
        } else {
            speed = 0.0f;
        }
        if ((s8) ev[5] != 0) {
            speed = 0.0f;
        }
        func_1505E650(obj, anim, speed, blend, 0.0f, 0.0f, mode);
        return 1;
    }
    if (type != 5) {
        return 0;
    }
    switch (*(s16 *) (ev + 2)) {
        case 1: {
            u8 *c;

            if ((s8) ev[4] == 0) {
                t = func_15023C60((u32) ev, type, track, &next, 1, 1, 0, 0, 0, 0, player) - now;
                if (replay != 0) {
                    t = 0;
                }
                c = &D_800844A0[(s8) ev[5] * 3];
                func_1517F3B0(c[0], c[1], c[2], t, *(s16 *) (ev + 6) == 0, 0);
                D_800C40AA = *(s16 *) (ev + 6) == 0;
            } else if (replay != 0) {
                func_15023EC4(&prev, &next, NULL, &prevTime, track, type, 1, 1, 1, 0, (&D_800C39D0)[player], player);
                if (prev != NULL) {
                    c = &D_800844A0[(s8) prev[5] * 3];
                    func_1517F3B0(c[0], c[1], c[2], 0, *(s16 *) (prev + 6) == 0, 0);
                    D_800C40AA = *(s16 *) (prev + 6) == 0;
                }
            }
            return 1;
        }
        case 4: {
            s32 set;

            if (obj == NULL) {
                return 1;
            }
            if (replay == 0) {
                set = -1;
                if (((u8 *) obj)[4] == 0x4B) {
                    set = 2;
                }
                if (set == -1) {
                    return 1;
                }
                func_1503DE70(obj, set, (s8) ev[4] != 0 ? (s8) ev[4] - 1 : -1);
            } else {
                func_15060F28(obj, 1);
            }
            return 1;
        }
        case 0x5C: {
            s32 end;
            s32 in;
            s32 out;

            if ((s8) ev[4] != 0 || replay != 0) {
                return 1;
            }
            end = func_15023C60((u32) ev, type, track, &next, 1, 0x5C, 1, 1, 1, (s8) ev[5], player);
            in = NEXT(&next, 1, 2, 1, (s8) ev[5]);
            if (next == NULL) {
                in = 0;
            }
            out = end - (NEXT(&next, 1, 3, 1, (s8) ev[5]) + now);
            if (next == NULL) {
                out = 0;
            }
            func_150F59A0(in, end - now - out - in, out, (s8) ev[5]);
            return 1;
        }
        case 0x56:
            if ((s8) ev[4] == 0) {
                if (replay == 0) {
                    func_1517946C(3);
                }
            } else if (replay != 0) {
                func_1517946C(2);
            } else if ((s8) ev[5] == 0) {
                func_1517946C(0);
            } else {
                func_1517946C(1);
            }
            return 1;
        case 0x76:
            func_151D6CA0(*(s16 *) (ev + 6), (s8) ev[4] == 1 ? 0 : ((s8) ev[5] == 1 ? 2 : 1));
            return 1;
        case 0x2D:
            t = func_15023C60((u32) ev, type, track, &next, 1, 0x2D, 0, 0, 0, 0, player) - now;
            if (wrec != NULL) {
                if ((s8) ev[4] == 0) {
                    func_15188EBC((s32) wrec, t, (s8) ev[5]);
                }
            } else if (obj != NULL) {
                if ((s8) ev[4] == 0) {
                    func_15188D80(obj, t, (s8) ev[5]);
                } else if (replay != 0) {
                    func_15189040((s32) obj);
                }
            }
            return 1;
        case 0x57:
            if ((s8) ev[4] == 0) {
                func_15155D6C(0, func_15023C60((u32) ev, type, track, &next, 1, 0x57, 0, 0, 0, 0, player) - now, 0.0f);
            } else if (replay != 0) {
                D_800C3E78 = 0;
                func_15156500();
            }
            return 1;
    }
    return 1;
}
#undef NEXT
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15029EA8.s")
#endif

#ifdef NON_MATCHING
u8 *func_151149AC(u8);
s32 func_15024910(s32, u8, u16, s32, s32, struct127 *, u8 *, u8 *, s32);
s32 func_150268BC(s32, u8, u16, s32, s32, struct127 *, u8 *, u8 *, s32);
s32 func_15029EA8(s32, u8, u16, s32, s32, struct127 *, u8 *, u8 *, s32, s32);

/* Runs entry arg1 of player `player` through the three handlers in turn; the first non-zero result is returned.
 * The entry may refer to an object (kind 2: its data at +0x14 replaces the player's D_800C3958 record) or to a
 * func_151149AC record (kind 3); a missing reference returns 0. When D_800C3C88 == 2 the middle handler is skipped
 * and the last one gets 1 instead of 0. */
s32 func_1502AB94(s32 arg0, u8 arg1, u16 arg2, s32 arg3, s32 player) {
    struct127 *obj;
    u8 *rec;
    u8 *data;
    s32 flag;
    s32 ret;
    struct_1502AB94_ref *ref;

    obj = NULL;
    rec = NULL;
    data = NULL;
    flag = (&D_800C3A08)[player];
    ref = &D_800C3A10[player][arg1];
    if (ref->kind == 2) {
        obj = func_15083E90(ref->id);
        if (obj == NULL) {
            return 0;
        }
        data = (u8 *) obj + 0x14;
    } else if (ref->kind == 3) {
        rec = func_151149AC(ref->id);
        if (rec == NULL) {
            return 0;
        }
    }
    if (data == NULL) {
        data = (u8 *) ((&D_800C3958)[player] + arg1);
    }
    if (D_800C3C88 != 2) {
        ret = func_15024910(arg0, arg1, arg2, arg3, player, obj, rec, data, flag);
        if (ret != 0) {
            return ret;
        }
        ret = func_150268BC(arg0, arg1, arg2, arg3, player, obj, rec, data, flag);
        if (ret != 0) {
            return ret;
        }
        return func_15029EA8(arg0, arg1, arg2, arg3, player, obj, rec, data, flag, 0);
    }
    ret = func_15024910(arg0, arg1, arg2, arg3, player, obj, rec, data, flag);
    if (ret != 0) {
        return ret;
    }
    return func_15029EA8(arg0, arg1, arg2, arg3, player, obj, rec, data, flag, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_1502AB94.s")
#endif
