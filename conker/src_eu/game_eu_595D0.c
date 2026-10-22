#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 func_1506196C(struct127 *, s32);
void func_1502E228(s32 arg0, s32 arg1);
void func_1502C8F8(s32 arg0);
void func_1502FED8(struct127 *arg0);
void func_1502E7B4(s32 arg0);
void func_1503A37C(struct127 *arg0);
void func_150348D4(s32 arg0);
void func_1503AB20(struct127 *arg0);
void func_1503E238(s32 arg0);
void func_1502F1E4(s32 arg0);
void func_1502F554(s32 arg0);
void func_1502EDEC(struct127 *arg0);
void func_150A4FE4(struct127 *arg0);
void func_1517B270(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_800C6A8F[];
#endif

typedef struct {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ u8 unkA4;
    /* 0xA5 */ u8 unkA5;
    /* 0xA6 */ u8 unkA6;
    /* 0xA7 */ u8 unkA7;
} struct_eu_595D0;


#ifdef NON_MATCHING
u8 * func_1502C6F8(u8 *, s32, s16);
u8 * func_1502CC64(u8 *, s32, s16, s32, s32);
u8 * func_15036BB4(u8 *, s32, s16);
extern s32 D_800844F0;
extern s32 D_80084520;

Gfx *func_1502BDC0(Gfx *gdl, s32 arg1, s16 arg2) {
    u8 *arg0 = (u8 *) gdl;
    s32 var_s1;
    struct127 *var_s0;
    u8 temp_v0;
    u8 *temp_v0_2;
    u8 *var_s2;
    u8 *var_v0;
    u8 *var_v0_2;

    (*(s32 *)((u8 *)arg0 + 0)) = 0xDE000000;
    (*(s32 **)((u8 *)arg0 + 4)) = &D_800844F0;
    var_s2 = arg0 + 8;
    var_s0 = D_800CC2D0;
    var_s1 = 0;
    do {
        D_8003C8E0 = (var_s1 & 0xFFFFFF) | 0x01000000;
        if (var_s0->interaction_state != 0) {
            temp_v0 = var_s0->unk5;
            if ((temp_v0 != 3) && (temp_v0 != 5)) {
                if (temp_v0 == 2) {
                    if (arg1 != 2) {

                    } else {
                        goto block_8;
                    }
                } else if (var_s0->id != 0xFF) {
block_8:
                    if (arg1 == 6) {
                        if (temp_v0 != 7) {

                        } else {
                            goto block_27;
                        }
                    } else if (arg1 == 0) {
                        if (!(((u32) var_s0->unk184 >> 9) & 1)) {

                        } else {
                            goto block_27;
                        }
                    } else if (arg1 == 1) {
                        if ((temp_v0 != 7) && (temp_v0 != 1)) {
                            if ((temp_v0 == 0) && (func_1506196C(var_s0, arg2) < 0xFF)) {

                            } else {
                                goto block_27;
                            }
                        }
                    } else if ((arg1 != 2) || (temp_v0 == 2) || ((temp_v0 != 7) && ((temp_v0 == 0) || (temp_v0 == 1)) && ((temp_v0 != 0) || (func_1506196C(var_s0, arg2) != 0xFF)))) {
block_27:
                        if (var_s0->unk5 == 2) {
                            var_v0 = func_1502C6F8(var_s2, var_s1, arg2);
                            goto block_31;
                        }
                        temp_v0_2 = func_1502CC64(var_s2, var_s1, arg2, arg1, 0);
                        var_s2 = temp_v0_2;
                        if (var_s1 == 0) {
                            var_v0 = func_15036BB4(temp_v0_2, var_s1, arg2);
block_31:
                            var_s2 = var_v0;
                        }
                    }
                }
            }
        }
        var_s1 += 1;
        var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
    } while (var_s1 != 0x19);
    D_8003C8E0 = 0x01FFFFFF;
    if (arg1 == 1) {
        var_v0_2 = func_150310F8(var_s2, arg2, 0);
        goto block_39;
    }
    if (arg1 == 2) {
        var_v0_2 = func_150310F8(var_s2, arg2, 1);
        goto block_39;
    }
    if (arg1 == 6) {
    s32 pad;
        var_v0_2 = func_150310F8(var_s2, arg2, 2);
block_39:
        var_s2 = var_v0_2;
    }
    (*(s32 *)((u8 *)var_s2 + 0)) = 0xDE000000;
    (*(s32 **)((u8 *)var_s2 + 4)) = &D_80084520;
    D_8003C8E0 = 0;
    return (Gfx *) (var_s2 + 8);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502BDC0.s")
#endif
#ifdef NON_MATCHING
/* P41: per-object update of object arg1 (record arg0): clears +0x1D4 (the shadow / model pointer), type +5 == 5 →
 * func_1502E228(arg1, 1) only; type +4 == 0xFF or +5 == 3: nothing; +5 == 2: func_1502C8F8. Otherwise the model setup
 * (func_1502E7B4, func_1502E228(arg1, 0) which sets +0x1D4, func_1503A37C), +0x1FC = 2 without a model, and the
 * per-frame callees (D_800C6A8F[arg1 * 16], +0x0, +0xA4, +0xF8 & 0x4000, +0x260). */
void func_1502C074(struct127 *arg0, s32 arg1) {
    u8 *obj = (u8 *)arg0;
    s32 t = obj[5];

    *(s32 *)(obj + 0x1D4) = 0;
    if (t == 5) {
        func_1502E228(arg1, 1);
        return;
    }
    if (obj[4] == 0xFF || t == 3) {
        return;
    }
    if (t == 2) {
        func_1502C8F8(arg1);
        return;
    }
    if (obj[0x1C9] != 0) {
        func_1502FED8(arg0);
    }
    func_1502E7B4(arg1);
    func_1502E228(arg1, 0);
    func_1503A37C(arg0);
    if (*(s32 *)(obj + 0x1D4) == 0) {
        obj[0x1FC] = 2;
    } else {
        func_150348D4(arg1);
        func_1503AB20(arg0);
    }
    if (D_800C6A8F[arg1 * 16] != 0) {
        func_1503E238(arg1);
    }
    if (*(s32 *)obj == 0) {
        return;
    }
    func_1502F1E4(arg1);
    func_1502F554(arg1);
    if (obj[0xA4] != 0) {
        func_1502EDEC(arg0);
    }
    if (*(s32 *)(obj + 0xF8) & 0x4000) {
        func_150A4FE4(arg0);
    }
    if (*(s32 *)(obj + 0x260) != 0) {
        func_1517B270(obj[0x134], obj[0x135], arg1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C074.s")
#endif
#ifdef NON_MATCHING
void func_1503FC54(void);
void func_1502C074(struct127 *arg0, s32 arg1);
void func_1502F6B8(void);
void func_1502FC38(u8 *arg0);
void func_15030758(void);
void func_1507C608(s32 arg0);
extern s32 D_800C4294;
extern u8 D_800C4290;
/* P48: per-frame object update loop. D_800C4294 = mask of the +0x274 values (bit v - 1) of the 25 records.
 * Records with no parent (+0x65 == 0) are updated (func_1502C074) in index order; the others afterwards, sorted
 * by the depth of their +0x65 parent chain (1-based record index), so a parent is updated before its children. */
void func_1502C1D4(void) {
    u8 depth[25];
    u8 order[0x30];
    u8 *rec;
    s32 i, j, d, n, maxd;

    func_1503FC54();
    D_800C42B0 = 0;
    D_800C4294 = 0;
    maxd = 0;
    for (i = 0; i < 25; i++) {
        u8 v = ((u8 *)&D_800CC2D0[i])[0x274];
        if (v != 0) {
            D_800C4294 |= 1 << ((v + 0x1F) & 0x1F);
        }
    }
    bzero(depth, 25);
    for (i = 0; i < 25; i++) {
        rec = (u8 *)&D_800CC2D0[i];
        if (*(s32 *)rec == 0) {
            continue;
        }
        if (rec[0x65] == 0) {
            func_1502C074((struct127 *)rec, i);
            continue;
        }
        depth[i] = 0;
        do {
            depth[i]++;
            rec = (u8 *)&D_800CC2D0[rec[0x65] - 1];
        } while (rec[0x65] != 0);
        if (maxd < depth[i]) {
            maxd = depth[i];
        }
    }
    if (maxd != 0) {
        n = 0;
        for (d = 1; d <= maxd; d++) {
            for (j = 0; j < 25; j++) {
                if (depth[j] == d) {
                    order[n++] = j;
                }
            }
        }
        for (i = 0; i < n; i++) {
            func_1502C074(&D_800CC2D0[order[i]], order[i]);
        }
    }
    func_1502F6B8();
    for (i = 0; i < 25; i++) {
        if (*(s32 *)&D_800CC2D0[i] != 0) {
            func_1502FC38((u8 *)&D_800CC2D0[i]);
        }
    }
    func_15030758();
    if (D_800BEAC0 == 0) {
        func_1507C608(0);
    }
    D_800C4290 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C1D4.s")
#endif

#ifdef NON_MATCHING
s32 func_15022A8C(struct127 *);
s32 func_1506196C(struct127 *, s32);
struct102 *func_1510DEF0(s32, struct127 *, s32, s32, s32);
extern u8 D_800C3A7A;

void func_1502C494(void) {
    s32 var_a2;
    s32 var_s0;
    s32 var_s2;
    s32 var_v0;
    struct127 *var_s1;
    u8 *temp_a0;

    var_s1 = D_800CC2D0;
    do {
        if (var_s1->interaction_state != 0) {
            var_s2 = 0;
            if ((var_s1->unk5 != 3) && (var_s1->id != 0xFF) && (var_s1->unk123 == 0) && ((var_s1->unk66 & 0x10) != 0x10) && (var_s1->unk160 != 0) && (var_s1->unk65 == 0) && ((D_800C3638 == 0) || (D_800C3A7A != 0) || (func_15022A8C(var_s1) != 0)) && ((var_s1->unk88 == 0) || (var_s1->unkCC >= -0x96))) {
                var_s0 = 0;
                if (D_80082FA0 >= 0) {
                    do {
                        if (func_1506196C(var_s1, var_s0) != 0) {
                            var_s2 = 1;
                        }
                        var_s0 += 1;
                    } while (D_80082FA0 >= var_s0);
                }
            }
            if (var_s2 != 0) {
                if (var_s1->unk2D4 == NULL) {
                    var_a2 = 0;
                    var_v0 = 0;
                    if (var_s1->id == 0x4D) {
                        var_a2 = 2;
                        var_v0 = 1;
                    }
                    var_s1->unk2D4 = func_1510DEF0(0, var_s1, var_a2, 0, var_v0);
                }
            } else {
                temp_a0 = var_s1->unk2D4;
                if (temp_a0 != NULL) {
                    func_1516972C((struct102 *) temp_a0);
                    var_s1->unk2D4 = NULL;
                }
            }
        }
        var_s1 = (struct127 *)((u8 *)var_s1 + (0x32C));
    } while ((s32)var_s1 != (s32)&D_800D121C);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C494.s")
#endif
void func_1502C380(void) {
    D_800C42AC = D_800C42A8 = (&D_800C3E80)[D_800BE9C0];
    D_800C429A = 0;
}

s32 func_1502C6AC(s32 arg0) {
    s32 temp_v1 = (&D_800CC826)[arg0 * 0x32C];

    if (temp_v1 >= 0x46) {
        temp_v1 = 0xB;
    }
    return temp_v1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C6F8.s")

extern u8 *D_8008CDEC[];

void func_1502C8F8(s32 arg0) {
    s32 lim;
    s16 a;
    s16 b;

    if (D_800BEAC0 == 0) {
        a = *(s16 *)((u8 *)&D_800CC2D0[arg0] + 0x60);
        b = *(s16 *)((u8 *)&D_800CC2D0[arg0] + 0x62);
        if (D_800CC2D0[arg0].unk7 != 0) {
            lim = D_8008CDEC[func_1502C6AC(arg0)][4] << 8;
            a = a + b;
            if (a >= lim) {
                a = a - lim;
            } else if (a < 0) {
                a = a + lim;
            }
            *(s16 *)((u8 *)&D_800CC2D0[arg0] + 0x60) = a;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C9D8.s")

#ifdef NON_MATCHING
s32 func_15022A8C(struct127 *);
void func_1502C9D8(s32, s16, s32);
void func_1502D920(u8 *, s32 *, s32);
u8 func_15084E34(struct127 *, s32 *);
Gfx *func_1502CFEC(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 *color, s32 arg6, s32 arg7);
void func_1502D83C(s32 arg0, u8 *arg1);
extern u8 D_800C3A7A;
extern s32 D_800BEFC4;
extern s32 D_800DFBF0;
extern u8 D_800DFBF4;

/* P43: one object of the frame DL (object arg1, part arg2, mode arg3). Skipped (returns gdl) when the object is
 * culled, part bit arg2 of +0x74 is set, func_1506196C(obj, part) == 0 or +0x1D4 == NULL. Colour block col[6]
 * (sp40): func_1502D83C fills it, func_1502D920 adjusts it when D_800B0DF0->+0x3E != 0 (else col[3] = 0xFF);
 * col[5] = +0x1C8 (func_1502C9D8 path) or from func_15084E34 (modes 3 / 4 / 5). Alpha = func_1506196C, 0xFF when the
 * object's camera record is in mode 0x100 and the part is not +0x127; mode 4 scales it by D_800DFBF4 and draws
 * D_800DFBF0 instead of +0x1D4. The DL from func_1502CFEC is dropped (gdl returned) when it overflows
 * D_800BEFC4 commands of the frame buffer D_800BEDE8[D_800BE9C0]. */
u8 *func_1502CC64(u8 *gdl, s32 arg1, s16 arg2, s32 arg3, s32 arg4) {
    s32 col[6];   /* sp40 */
    s32 model;    /* sp38 */
    u8 *rec;
    u8 *cam;
    s32 alpha;
    u8 *r;

    if (D_800C3638 != 0 && D_800C3A7A == 0 && func_15022A8C(&D_800CC2D0[arg1]) == 0) {
        return gdl;
    }
    rec = (u8 *)&D_800CC2D0[arg1];
    if ((rec[0x74] & (1 << arg2)) == (1 << arg2)) {
        return gdl;
    }
    if (func_1506196C((struct127 *)rec, arg2) == 0) {
        return gdl;
    }
    if (*(s32 *)(rec + 0x1D4) == 0) {
        return gdl;
    }
    if (arg3 != 4 && arg3 != 5 && arg3 != 3) {
        func_1502C9D8(arg1, arg2, arg3);
        col[5] = rec[0x1C8];
    } else {
        func_15084E34((struct127 *)rec, &col[5]);
    }
    func_1502D83C(arg1, (u8 *)col);
    if (*(s16 *)((u8 *)D_800B0DF0 + 0x3E) != 0) {
        func_1502D920(rec, col, arg2);
    } else {
        col[3] = 0xFF;
    }
    alpha = func_1506196C((struct127 *)rec, arg2);
    if (alpha < 0xFF) {
        cam = *(u8 **)(rec + 0x318);
        if (cam != NULL && *(s32 *)(cam + 0x2C) == 0x100 && arg2 != rec[0x127]) {
            alpha = 0xFF;
        }
    }
    if (arg3 == 4) {
        model = D_800DFBF0;
        alpha = (s32)(D_800DFBF4 * (u32)alpha) >> 8;
    } else {
        model = *(s32 *)(rec + 0x1D4);
    }
    r = (u8 *)func_1502CFEC((Gfx *)gdl, arg1, arg2, model, alpha, col, arg3, arg4);
    if (D_800BEFC4 < (s32)((u32)r - (u32)D_800BEDE8[D_800BE9C0]) >> 3) {
        return gdl;
    }
    return r;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502CC64.s")
#endif

s32 func_1502EF24(u8 *, s32 *, s32 *, s32 *, s32 *);

void func_1502CF24(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *argA, s32 *argB, s32 *argC, s32 *argD) {
    s32 temp_a2;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_a2 = arg1 * 3;
    temp_v0 = temp_a2 + D_800D9F88;
    *arg4 = (s32) (*(u8 *)((u8 *)temp_v0 + 0));
    temp_v1 = temp_a2 + D_800D9F98;
    *arg5 = (s32) (*(u8 *)((u8 *)temp_v0 + 1));
    *arg6 = (s32) (*(u8 *)((u8 *)temp_v0 + 2));
    *arg7 = (s32) (*(u8 *)((u8 *)temp_v1 + 0));
    *arg8 = (s32) (*(u8 *)((u8 *)temp_v1 + 1));
    *arg9 = (s32) (*(u8 *)((u8 *)temp_v1 + 2));
    *argA = 0;
    *argB = 0;
    *argC = 0;
    *argD = (*(s32 *)((u8 *)arg3 + 0xC));
    if ((*(u8 *)((u8 *)arg0 + 0xA4)) != 0) {
        func_1502EF24(arg0, argA, argB, argC, argD);
    }
}

#ifdef NON_MATCHING
u8 *func_1502FCEC(u8 *arg0, s32 arg1);
void func_15030060(u8 *arg0);
u8 *func_1502F30C(u8 *, s32);
s32 func_1503DD8C(struct127 *, s32, s32, s32);
u8 func_15084E34(struct127 *, s32 *);
Gfx *func_1515DE84(Gfx *, s32, s32, s32, s32, s32, s32, s32, u8 *, u8 *, s32, u8 *, s32, u8 *);
s32 func_15031284(s32 arg0, u8 *arg1, s32 arg2, s32 arg3);
void func_151F0648(Mtx *arg0);
extern u8 D_80083350[];
extern u8 D_800834D0[];
extern u8 D_80083650[];
extern s32 D_800844F0;
extern s32 D_80084520;
extern Mtx D_800C42B8;
extern u16 D_800C4B98[];
extern u8 **D_800C48A8[];
extern u8 **D_800C4D10[];
extern u8 D_800DA248[];
extern u8 D_800DD714[];

/* func_1502CFEC (P57): the model display list of object arg1, part arg2. arg3 = model (segment 6 base, from
 * +0x1D4 or D_800DFBF0), arg4 = alpha, color = colour block (func_1502CF24 unpacks it), arg6 = mode (0 normal,
 * 3 / 4 / 5 special; 3 draws the D_800C4D10 DLs without matrix), arg7: wrap in D_800844F0 / D_80084520.
 * model = obj+4 (or func_15084E34 in modes 3-5), variant +0x1C8; returns gdl unchanged when func_1503DD8C fails or
 * the variant has no vertex block (+0x28C + variant * 8 + frame * 4). Emits: segment 6 = arg3, segment 1 =
 * that block - 0x38, the combiner DL (segment 8), geometry mode, lights (func_1515DE84) when lit, then per DL k
 * of D_800C4B98[model] not hidden by +0x94 bit k: prim / env / blend colours (+0x98 bit k: fixed white ones),
 * G_MTX D_800C42B8 (physical address) + G_DL D_800C48A8[model][k]. Then func_15030060, +0x2FE = 1, func_15031284. */
Gfx *func_1502CFEC(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 *color, s32 arg6, s32 arg7) {
    u32 *g = (u32 *)gdl;
    u8 *o = (u8 *)&D_800CC2D0[arg1];
    s32 model;    /* sp140 */
    s32 var;      /* sp144 */
    s32 fog;      /* sp130 */
    s32 c0, c1, c2, c3, c4, c5, c6, c7, c8, c9;
    s32 lit, mode, k, n, fl, a;
    u16 *cnt;

    model = o[4];
    if (arg6 == 3 || arg6 == 4 || arg6 == 5) {
        model = func_15084E34((struct127 *)o, &var);
    } else {
        var = o[0x1C8];
    }
    if (func_1503DD8C((struct127 *)o, model, var, (arg6 == 3) ? 0 : 1) != 0) {
        return (Gfx *)g;
    }
    if (*(s32 *)(o + var * 8 + D_800BE9C0 * 4 + 0x28C) == 0) {
        return (Gfx *)g;
    }
    if (arg7 != 0) {
        g[1] = (u32)&D_800844F0;
        g[0] = 0xDE000000;
    } else {
        g[0] = 0xE7000000;
        g[1] = 0;
    }
    g += 2;
    g = (u32 *)func_1502FCEC(func_1502F30C((u8 *)g, arg1), arg1);
    g[0] = 0xDB06000C;
    g[1] = arg3;
    g[2] = 0xDB060004;
    g[3] = *(s32 *)(o + var * 8 + D_800BE9C0 * 4 + 0x28C) - 0x38;
    g += 4;
    func_1502CF24(o, arg2, arg4, (u8 *)color, &c0, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9);
    g[0] = 0xDB060020;
    if (arg6 == 5) g[1] = (u32)D_80083650;
    else if (arg6 == 3) g[1] = (u32)D_80083650;
    else if (arg4 < 0xFF) g[1] = (u32)D_80083350;
    else g[1] = (u32)D_800834D0;
    g += 2;
    g[0] = 0xD9FFF9FF;
    g[1] = 0;
    g += 2;
    g[1] = (arg6 == 0) ? 0x200 : 0x400;
    g[0] = 0xD9FFFFFF;
    g += 2;
    lit = 1;
    fog = *(s16 *)((u8 *)D_800B0DF0 + 0x3E);
    fl = o[0x66] & 0xC;
    if (fl == 0xC) {
        g[0] = 0xD9FFFFFF;
        g[1] = 0x20000;
        g[2] = 0xD9BFFFFF;
        g[3] = 0;
        g += 4;
    } else if (fl == 8 && D_800DCD7C != 0) {
        g[1] = 0x420000;
        g[0] = 0xD9FFFFFF;
        g += 2;
    } else {
        g[0] = 0xD9BDFFFF;
        g[1] = 0;
        g += 2;
        lit = 0;
    }
    if (arg6 == 3) {
        g[0] = 0xD9BDFFFF;
        g[1] = 0;
        g += 2;
        lit = 0;
    }
    if (lit) {
        s32 v = 2;
        if (o[0x2FE] == 0) v = 0xA;
        if (D_800D9D20 != 0) v |= 8;
        g = (u32 *)func_1515DE84((Gfx *)g, arg2, (s32)*(f32 *)(o + 0x14), (s32)*(f32 *)(o + 0x18),
                                 (s32)*(f32 *)(o + 0x1C), *(s32 *)(o + 0x184), *(s32 *)(o + arg2 * 4 + 0x304),
                                 o[0x301], *(u8 **)(o + 0x314) + D_800BE9C0 * 8, o + 0x302, 2, o + 0x1DD, v,
                                 D_800DA248);
    }
    cnt = &D_800C4B98[model];
    n = *cnt;
    mode = -1;
    for (k = 0; k < n; k++) {
        if (*(u32 *)(o + 0x94) & (1 << k)) continue;
        if (!(*(u32 *)(o + 0x98) & (1 << k))) {
            if (mode != 0) {
                g[0] = 0xE7000000;
                g[1] = 0;
                g += 2;
                a = arg4 & 0xFF;
                mode = 0;
                g[0] = 0xF8000000;
                if (fog == 0) {
                    g[1] = (c6 << 24) | ((c7 & 0xFF) << 16) | ((c8 & 0xFF) << 8) | (c9 & 0xFF);
                } else {
                    g[1] = (D_800DD714[0] << 24) | (D_800DD714[1] << 16) | (D_800DD714[2] << 8) | (c9 & 0xFF);
                }
                g += 2;
                g[0] = 0xFA00F200;
                g[1] = (c0 << 24) | ((c1 & 0xFF) << 16) | ((c2 & 0xFF) << 8);
                g += 2;
                g[0] = 0xFB000000;
                g[1] = (c3 << 24) | ((c4 & 0xFF) << 16) | ((c5 & 0xFF) << 8) | a;
                g += 2;
            }
        } else if (mode != 1) {
            g[0] = 0xE7000000;
            g[1] = 0;
            g[2] = 0xF8000000;
            g[3] = 0xFF;
            g[4] = 0xFA00F200;
            g[5] = 0;
            g[6] = 0xFB000000;
            g[7] = 0xFF;
            g += 8;
            mode = 1;
        }
        if (arg6 == 3) {
            if (D_800C4D10[model] != NULL) {
                g[0] = 0xDE000000;
                g[1] = (u32)D_800C4D10[model][k];
                g += 2;
            }
        } else {
            func_151F0648(&D_800C42B8);
            g[0] = 0xDA380003;
            g[1] = (u32)&D_800C42B8 & 0x1FFFFFFF; /* the asm stores D_C42B8 (physical) */
            g[2] = 0xDE000000;
            g[3] = (u32)D_800C48A8[model][k];
            g += 4;
        }
        n = *cnt;
    }
    func_15030060(o);
    o[0x2FE] = 1;
    if (arg6 == 0) {
        g = (u32 *)func_15031284((s32)g, o, arg2, 1);
    }
    if (arg7 != 0) {
        g[0] = 0xDE000000;
        g[1] = (u32)&D_80084520;
        g += 2;
    }
    if (arg6 == 0) {
        g[1] = 0x400;
        g[0] = 0xD9FFFDFF;
        g += 2;
    }
    return (Gfx *)g;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502CFEC.s")
#endif

#ifdef NON_MATCHING
void func_1502D83C(s32 arg0, u8 *arg1) {
    s32 temp_t1;
    struct127 *temp_v0;

    temp_v0 = &D_800CC2D0[arg0];
    if ((temp_v0->unk66 & 0xC) == 4) {
        (*(s32 *)((u8 *)arg1 + 0)) = (s32) ((s32) (temp_v0->unk1DD + temp_v0->unk1E0) / 2);
        (*(s32 *)((u8 *)arg1 + 4)) = (s32) ((s32) (temp_v0->unk1DE + temp_v0->unk1E1) / 2);
        temp_t1 = (s32) (temp_v0->unk1DF + temp_v0->unk1E2) / 2;
        (*(s32 *)((u8 *)arg1 + 8)) = temp_t1;
        (*(s32 *)((u8 *)arg1 + 0)) = (s32) (0xFF - (*(s32 *)((u8 *)arg1 + 0)));
        (*(s32 *)((u8 *)arg1 + 4)) = (s32) (0xFF - (*(s32 *)((u8 *)arg1 + 4)));
        (*(s32 *)((u8 *)arg1 + 8)) = (s32) (0xFF - temp_t1);
        return;
    }
    (*(s32 *)((u8 *)arg1 + 8)) = 0xFF;
    (*(s32 *)((u8 *)arg1 + 4)) = 0xFF;
    (*(s32 *)((u8 *)arg1 + 0)) = 0xFF;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502D83C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502D920.s")

#ifdef NON_MATCHING
void func_1505DFDC(struct127 *arg0);
/* P51: per-frame key-frame copy for the skeleton evaluator func_150A86B0. For the animation state a (arg0, or
 * object arg1's +0x2D0 after func_1505DFDC when its animation +0x84 is 0xFFFF) and each active slot k (2 with a
 * blend weight +0x3C > 0; slot k's header byte +0x45 = bytes per key frame, +0x48 = key-frame step - 1, at
 * +0x40 + k * 0x1D0): the key frame of frame time +8 + 4k (frame count +0x18 + 4k) and the next one are DMA'd from
 * the stream (ROM +0x28 + 4k, word-aligned down) to the next 16-byte boundary of arg2. +0x30 + 4k = the key frame,
 * +0x38 + k = byte offset of the next one from it (at the last frame: frame 0 of the stream, copied separately).
 * +0x38 + k = 0 for a static animation (no key bytes); a slot with no stream is left alone. NM: void (the asm's v0
 * is left over; no caller uses it). */
void func_1502DB14(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *obj = (u8 *)arg1;
    u8 *a = arg0;
    u8 *h;
    u8 *s;
    u32 dst = arg2;
    u32 src;
    u32 mis;
    u32 n;
    s32 slots = 1;
    s32 k, kb, key, d, wrap;
    f32 t, cnt, f2;

    if (obj != NULL) {
        if (*(u16 *)(obj + 0x84) == 0xFFFF) {
            func_1505DFDC((struct127 *)obj);
        }
        a = *(u8 **)(obj + 0x2D0);
    }
    if (a == NULL) {
        return;
    }
    if (*(s16 *)(a + 0x3C) > 0) {
        slots = 2;
    }
    for (k = 0; k < slots; k++) {
        h = a + k * 0x1D0;
        s = a + k * 4;
        kb = h[0x45];
        if (kb == 0) {
            a[0x38 + k] = 0;
            continue;
        }
        if (*(u32 *)(s + 0x28) == 0) {
            continue;
        }
        t = *(f32 *)(s + 8);
        cnt = *(f32 *)(s + 0x18);
        dst = (dst + 15) & ~15;
        key = (s32)t;
        if (cnt <= (f32)key) {
            key = (s32)(cnt - 1.0f);
        }
        d = h[0x48] + 1;
        if (d >= 2) {
            f2 = cnt - 1.0f;
            if (f2 <= (f32)key) {
                key = (s32)((f2 + (f32)(d - 1)) / (f32)d);
            } else {
                key = key / d;
            }
        }
        src = *(u32 *)(s + 0x28) + (u32)kb * key;
        mis = src & 3;
        src -= mis;
        wrap = 0;
        if (cnt <= t + 1.0f) {
            wrap = 1;
            n = kb;
        } else {
            a[0x38 + k] = kb;
            n = kb * 2;
        }
        n += mis;
        *(u32 *)(s + 0x30) = mis + dst;
        if (n < 0xC8) {
            func_1000480C(src, (void *)dst, n);
        } else {
            func_10004514(src, (void *)dst, (n + 15) & ~15, 1);
        }
        dst += n;
        if (wrap) {
            /* the stream's frame 0 after the last key frame */
            src = *(u32 *)(s + 0x28);
            dst = (dst + 15) & ~15;
            mis = src & 1;
            n = mis + kb;
            src -= mis;
            if (n < 0xC8) {
                func_1000480C(src, (void *)dst, n);
            } else {
                func_10004514(src, (void *)dst, (n + 15) & ~15, 1);
            }
            a[0x38 + k] = (dst + mis) - *(u32 *)(s + 0x30);
            dst += n;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502DB14.s")
#endif

#ifdef NON_MATCHING
/* P48: joint-matrix count of model id: D_800C52F0[id], minus 4 for the ids of the asm's jump table
 * (jtbl_800971A8: 0x3B and 0x75 .. 0xB4 entries pointing at the "- 4" case). */
s32 func_1502DE10(s32 id) {
    switch (id) {
        case 0x3B:
        case 0x75: case 0x82: case 0x88: case 0x90: case 0x96: case 0x98: case 0x9C:
        case 0x9D: case 0x9F: case 0xA0: case 0xB1: case 0xB2: case 0xB4:
            return D_800C52F0[id] - 4;
        default:
            return D_800C52F0[id];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502DE10.s")
#endif

#ifdef NON_MATCHING
s32 func_1503D210(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_15083D54(struct127 *, u16, s32, f32);
s32 func_1502DE10(s32);
void func_15030060(u8 *arg0);
void func_150342D0(u8 *arg0, s32 arg1);
void func_1502DB14(u8 *, s32, s32);
void func_150A86B0(s32 *arena, f32 (*mtx)[4], s32 anim, s32 skel, s32 n, u8 *arg5, u8 *remap, s32 h);
extern u8 D_800C441A;
extern u8 *D_800845BC[];
extern s32 D_800C5000[];
extern s32 D_800888F8;
extern s32 D_800888F4;
extern s32 D_8008891C;
/* P48: model instance of object arg1 (record +0x1D4) from its root matrix m. Loads the model of id +4 when
 * D_800D19A0[id] is empty (func_1503D210), makes sure the object has an animation state +0x2D0 (func_15083D54),
 * then reserves func_1502DE10(id) joint matrices (0x40 bytes each) in the D_800C42A8 arena (none written and
 * +0x1D4 = 0 when the D_800C3E7C-matrix arena would overflow), sets +0x1D4 to the first one and fills them with the
 * hand-asm skeleton evaluator func_150A86B0 (D5E90.s). +0x29 of the model header selects a joint remap table
 * (D_800845BC, pairs ending in 0xFF). The evaluator's outputs D_800888F4 / D_800888F8 give the animation
 * position +0x1F8 / +0x1F4 (and +0x2D0 +0x10 with +0x246 & 0x40); +0x7C = D_8008891C. */
void func_1502DE74(f32 (*m)[4], s32 arg1) {
    u8 remap[0x44];
    u8 dbuf[0x324];
    u8 sbuf[0x54];
    u8 *obj = (u8 *)&D_800CC2D0[arg1];
    s32 id = obj[4];
    s32 *slot = &((s32 *)&D_800D19A0)[id];
    u8 *map = NULL;
    u16 *cnt;
    s32 n, f1, f2, h;
    u8 *p;
    u8 fl;
    f32 t, old;

    if (*slot == 0) {
        if (func_1503D210(id, 0, *(s32 *)(obj + 0x144), 1, obj[0xAC]) != 0) {
            *(s32 *)(obj + 0x1D4) = 0;
            return;
        }
        if (*slot == 0) {
            *(s32 *)(obj + 0x1D4) = 0;
            return;
        }
    }
    if (*(s32 *)(obj + 0x2D0) == 0) {
        if (func_15083D54((struct127 *)obj, 0, 0, 1.0f) != 0) {
            return;
        }
    }
    cnt = &D_800C52F0[id];
    if (*cnt >= 2 && *(s32 *)(obj + 0x2D0) == 0) {
        return;
    }
    n = func_1502DE10(id);
    if ((u32)(D_800C3E7C << 6) < (u32)(D_800C42A8 + (n << 6) - D_800C42AC)) {
        *(s32 *)(obj + 0x1D4) = 0;
        return;
    }
    func_15030060(obj);
    *(s32 *)(obj + 0x1D4) = D_800C42A8;
    if (((u8 *)D_800D1C90[id])[0x29] != 0) {
        D_800C441A = 0;
        bzero(remap, *cnt);
        p = D_800845BC[((u8 *)D_800D1C90[id])[0x29]];
        while (p[0] != 0xFF) {
            remap[p[0]] = p[1];
            p += 2;
        }
        map = remap;
    }
    func_150342D0(sbuf, arg1);
    func_1502DB14(NULL, (s32)obj, (s32)dbuf);
    if (D_800C35EA != 1) {
        h = (s16)(s32)(*(f32 *)(obj + 0x150) * (f32)*(s16 *)(obj + 0xCC));
    } else {
        h = 0;
    }
    func_150A86B0(&D_800C42A8, m, *(s32 *)(obj + 0x2D0), D_800C5000[id], n, sbuf, map, h);
    *(s16 *)(obj + 0x7C) = D_8008891C;
    f1 = D_800888F8;
    if (f1 != 0) {
        t = (f32)D_800888F4 / 32768.0f;
        fl = obj[0x1FC];
        if (fl & 4) {
            *(f32 *)(obj + 0x1F8) -= (f32)f1 * 0.03125f;
            fl = obj[0x1FC];
        }
        old = *(f32 *)(obj + 0x1F8);
        *(f32 *)(obj + 0x1F8) = t;
        *(f32 *)(obj + 0x1F4) = t - old;
        if (fl & 2) {
            obj[0x1FC] = fl & 0xFC;
            *(f32 *)(obj + 0x1F4) = *(f32 *)(obj + 0x3C);
        } else {
            obj[0x1FC] = fl | 1;
        }
        if (obj[0x246] & 0x40) {
            u8 *an = *(u8 **)(obj + 0x2D0);
            *(f32 *)(an + 0x10) = (*(f32 *)(obj + 0x3C) / ((*(f32 *)(obj + 0x14C) * ((f32)f1 * 0.03125f)) / *(f32 *)(an + 0x18))) * 0.5f;
        }
    }
    D_800C429A += n;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502DE74.s")
#endif

#ifdef NON_MATCHING
void func_1502DE74(f32 (*mtx)[4], s32 arg1);
extern s32 D_800C4294;
/* P48: object arg0's model matrix. Skipped (nothing written) when the object is hidden for every player (+0x74 low
 * nibble 0xF, or every func_1506196C alpha 0), unless it is forced (+0x66 & 0x20, a player-controlled object
 * (+0x31C +0x197), bit arg0 of D_800C4294, or id 0x8A whose func_15072208 target is player-controlled).
 * A child (+0x65 = parent index + 1, without +0x101 & 0x10) takes the parent's joint +0x5C matrix (+0x1D4 + 0x40 *
 * joint) with rows 0 / 2 scaled by +0x14C and row 1 by +0x150 (+0x101 & 4: rows normalised first); otherwise
 * func_150A9B0C builds it from the angles (+0xB8, +0x40, +0xC4) and scales, at the position (with +0x101 & 0x10:
 * the parent's joint position), raised by +0xCC when +0x2D0 +0x28 is 0.
 * arg1 != 0: the matrix is copied to the D_800C42A8 arena and +0x1D4 points at it; else func_1502DE74(m, arg0). */
void func_1502E228(s32 arg0, s32 arg1) {
    f32 m[4][4];
    u8 *obj = (u8 *)&D_800CC2D0[arg0];
    u8 *src;
    u8 *ref;
    s32 force = 1;
    s32 i, j, a, best;
    f32 s;

    if (*(f32 *)(obj + 0x14C) == 0.0f) {
        *(f32 *)(obj + 0x14C) = 0.1f;
        *(f32 *)(obj + 0x154) = 0.1f;
    }
    if (*(f32 *)(obj + 0x150) == 0.0f) {
        *(f32 *)(obj + 0x150) = 0.1f;
        *(f32 *)(obj + 0x158) = 0.1f;
    }
    if ((obj[0x66] & 0x20) == 0x20) {
        force = 0;
    }
    if (*(u8 **)(obj + 0x31C) != NULL && (*(u8 **)(obj + 0x31C))[0x197] != 0) {
        force = 0;
    }
    if ((1 << (arg0 & 0x1F)) & D_800C4294) {
        force = 0;
    }
    if (obj[4] == 0x8A) {
        u8 *t = (u8 *)func_15072208((struct127 *)obj, 0);
        if (t != NULL && *(u8 **)(t + 0x31C) != NULL && (*(u8 **)(t + 0x31C))[0x197] != 0) {
            force = 0;
        }
    }
    if (force != 0) {
        if ((obj[0x74] & 0xF) == 0xF) {
            return;
        }
        best = 0;
        for (i = 0; i <= D_80082FA4; i++) {
            a = func_1506196C((struct127 *)obj, i);
            if (best < a) {
                best = a;
            }
        }
        if (best == 0) {
            return;
        }
    }
    D_800C3E78 = arg0;
    if (obj[0x65] != 0 && !(obj[0x101] & 0x10)) {
        src = *(u8 **)((u8 *)&D_800CC2D0[obj[0x65] - 1] + 0x1D4);
        if (src == NULL) {
            return;
        }
        src += *(s32 *)(obj + 0x5C) << 6;
        for (i = 0; i < 3; i++) {
            f32 *row = (f32 *)(src + i * 0x10);
            s = (i == 1) ? *(f32 *)(obj + 0x150) : *(f32 *)(obj + 0x14C);
            if (obj[0x101] & 4) {
                s = s / sqrtf(row[2] * row[2] + (row[0] * row[0] + row[1] * row[1]));
            }
            for (j = 0; j < 3; j++) {
                m[i][j] = row[j] * s;
            }
            m[i][3] = 0.0f;
            m[3][i] = ((f32 *)src)[12 + i];
        }
        m[3][3] = 1.0f;
    } else {
        func_150A9B0C(m, *(f32 *)(obj + 0xB8), *(f32 *)(obj + 0x40), *(f32 *)(obj + 0xC4),
                      *(f32 *)(obj + 0x14C), *(f32 *)(obj + 0x150), *(f32 *)(obj + 0x14C));
        if (obj[0x101] & 0x10) {
            /* the parent (index +0x65 - 1; the asm does not check +0x65 != 0 here) */
            ref = (u8 *)&D_800CC2D0[obj[0x65]] - 0x32C;
            src = *(u8 **)(ref + 0x1D4);
            if (src == NULL) {
                m[3][0] = 0.0f;
                m[3][1] = 0.0f;
                m[3][2] = 0.0f;
            } else {
                src += *(s32 *)(obj + 0x5C) << 6;
                m[3][0] = ((f32 *)src)[12];
                m[3][1] = ((f32 *)src)[13];
                m[3][2] = ((f32 *)src)[14];
            }
        } else {
            ref = obj;
            m[3][0] = *(f32 *)(obj + 0x14);
            m[3][1] = *(f32 *)(obj + 0x18) + *(f32 *)(obj + 0x150) * *(f32 *)(obj + 0xC8);
            m[3][2] = *(f32 *)(obj + 0x1C);
        }
        if (*(u8 **)(ref + 0x2D0) != NULL && *(s32 *)(*(u8 **)(ref + 0x2D0) + 0x28) == 0) {
            m[3][1] += (f32)*(s16 *)(ref + 0xCC);
        }
    }
    if (arg1 != 0) {
        *(s32 *)(obj + 0x1D4) = D_800C42A8;
        bcopy(m, (void *)D_800C42A8, 0x40);
        D_800C42A8 += 0x40;
        D_800C429A++;
        return;
    }
    func_1502DE74(m, arg0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502E228.s")
#endif

void func_1502E764(void) {
    if ((u16)D_800C429A != 0) {
        func_150A9E64((&D_800C3E80)[D_800BE9C0], (u16)D_800C429A);
    }
    D_800C42B0 = 1;
}

#ifdef NON_MATCHING
void func_1502ECEC(s32 arg0, s32 arg1);
s32 func_15022A8C(struct127 *);
s32 func_1503FBF4(struct127 *, s32, s32);
s32 func_1506196C(struct127 *, s32);
s32 func_150A6840(s32, s32 *, f32, f32, f32, f32, f32, f32);
extern u8 D_800C3A7A;
extern u8 D_800C3A84;
extern s32 D_800DA030;

/* P48: visibility mask +0x74 of object arg0 (bit i set = hidden for player i). Type 7: low nibble cleared. Otherwise
 * all four bits are set, and when the object is not culled and in an active view group (+0x127 bit of D_800D2340):
 * a child (+0x65 = parent index + 1) copies its parent's mask; else each player's view test func_150A6840
 * (radius from the model header D_800D1C90[id] +0xE / +0x10 and the scales) and the fade distance (+0x10, or
 * 100000 for player-controlled cameras) choose func_1506160C events 8 / 9 / 10 and clear the player's bit.
 * The m2c draft stepped D_800DA030 by 0x100 and D_800DBFF0 by sizeof(struct108) * 0x9A0: both are byte offsets. */
void func_1502E7B4(s32 arg0) {
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    s32 sp5C;
    s32 sp54;
    u8 *var_s5;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    s32 temp_v0_6;
    s32 var_fp;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s6;
    s32 var_s7;
    s32 var_v1;
    struct108 *temp_v0_7;
    struct124 **temp_v1;
    struct124 *temp_v0_4;
    struct127 *temp_s1;
    u16 temp_v0_5;
    u8 temp_s0;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_8;

    var_s7 = 1;
    temp_s1 = &D_800CC2D0[arg0];
    temp_s0 = temp_s1->id;
    if (temp_s1->unk5 == 7) {
        temp_s1->unk74 &= 0xFFF0;
        return;
    }
    temp_v0 = temp_s1->unk74;
    temp_s1->unk74 = temp_v0 | 0xF;
    sp54 = (s32) temp_v0;
    if (((D_800C3638 == 0) || (D_800C3A7A != 0) || (func_15022A8C(temp_s1) != 0)) && ((temp_v0_2 = temp_s1->unk127, (temp_v0_2 == 0xFF)) || ((u16) D_800D2340 & (1 << (temp_v0_2 & 0x1F)))) && ((temp_s1->unk101 & 1) != 1) && (temp_s1->unk7 != 0)) {
        temp_v0_3 = temp_s1->unk65;
        if (temp_v0_3 != 0) {
            temp_s1->unk74 = ((u8 *)&D_800CC2D0[temp_v0_3 - 1])[0x74] /* the parent's mask */;
            return;
        }
        temp_v1 = &D_800D1C90[temp_s0];
        temp_v0_4 = *temp_v1;
        temp_f0 = (f32) (u16) temp_v0_4->unkE;
        temp_f12 = temp_s1->xz_scale;
        temp_f2 = temp_s1->y_scale;
        temp_f14 = temp_f0 * temp_f12;
        sp78 = temp_f0 * temp_f2;
        sp74 = (f32) ((*(s16 *)((u8 *)temp_v0_4 + 0x10)) + temp_s1->unkCC) * temp_f2;
        temp_s1->unk270 = temp_f14;
        sp5C = (s32) (*(u16 *)((u8 *)temp_s1 + 0x10));
        if ((D_800C35EA == 1) && (D_800C3A84 == 0)) {
            sp5C = 0;
        }
        var_fp = 0;
        if (temp_s1->unk101 & 0x80) {
            sp70 = 0.0f;
        } else {
            temp_v0_5 = (*(u16 *)((u8 *)(*temp_v1) + 0x3E));
            if (temp_v0_5 == 0) {
                sp70 = (f32) temp_s1->unkE4;
            } else if (temp_v0_5 == 1) {
                sp70 = 0.0f;
            } else {
                sp70 = (f32) temp_v0_5 * temp_f12;
            }
        }
        var_s2 = 0;
        if (D_80082FA0 >= 0) {
            var_s5 = (u8 *)&D_800DA030;
            var_s4 = 0;
            var_s6 = 0;
            sp7C = temp_f14;
            do {
                var_s3 = 0;
                if ((*(u8 *)((u8 *)((*(u8 **)((u8 *)D_800DBFF0 + var_s6 + 0x3D4))) + 0x197)) != 0) {
                    var_s0 = 0x186A0;
                } else {
                    var_s0 = sp5C;
                }
                temp_v0_6 = func_150A6840(var_s4 + D_800BE628, (s32 *)var_s5, temp_s1->x_position, temp_s1->y_position + sp74, temp_s1->z_position, sp7C, sp78, 20000.0f);
                var_v1 = temp_v0_6;
                if (temp_v0_6 == 0) {
                    goto block_37;
                }
                if (temp_v0_6 < 0) {
                    var_v1 = -temp_v0_6;
                }
                if (var_fp < var_v1) {
                    var_fp = var_v1;
                }
                if (((temp_s1->unk66 & 0x80) != 0x80) && ((f32) var_v1 <= sp70) && (D_800C35EA != 1)) {
block_37:
                    var_s3 = 1;
                }
                if (var_s3 == 0) {
                    if ((var_s0 != 0) && (var_s2 != arg0)) {
                        if (var_s0 < var_v1) {
                            var_s0_2 = 8;
                        } else {
                            var_s0_2 = 9;
                        }
                        func_1506160C(temp_s1, var_s0_2 & 0xFF, 0U, 0U, (u8) var_s2);
                    } else {
                        temp_s1->unkE.ub[1] |= (1 << (var_s2 & 0x1F)) << 4;
                        var_s0_2 = -1;
                        func_1506160C(temp_s1, 9U, 0U, 0U, (u8) var_s2);
                    }
                    if ((temp_s1->unkF8 & 0x800000) && (var_s0_2 != 8) && (D_800C35EA != 1) && (func_1503FBF4(temp_s1, var_s2, sp54) != 0)) {
                        var_s3 = 1;
                    }
                } else {
                    var_s0_2 = 0xA;
                }
                if (var_s0_2 != -1) {
                    func_1506160C(temp_s1, var_s0_2 & 0xFF, 1U, 0U, (u8) var_s2);
                }
                if (var_s3 == 0) {
                    temp_s1->unk74 &= ~var_s7;
                }
                if (func_1506196C(temp_s1, var_s2) == 0) {
                    temp_s1->unk74 |= var_s7;
                }
                var_s7 *= 2;
                var_s2 += 1;
                var_s4 += 0x180;
                var_s5 += 0x40;
                var_s6 += 0x9A0;
            } while (D_80082FA0 >= var_s2);
        }
        func_1502ECEC((s32) temp_s1, var_fp);
        temp_v0_7 = temp_s1->camera;
        if ((temp_v0_7 != NULL) && ((temp_v0_7->unk2C == 0x10000) || (temp_s1->unk31C->unk197 != 0))) {
            temp_s1->unk74 |= 1 << arg0;
        }
        if (D_800C35EA != 1) {
            temp_v0_8 = temp_s1->unk2FC;
            if (temp_v0_8 != 0) {
                temp_s1->unk74 |= temp_v0_8;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502E7B4.s")
#endif

void func_1502ECEC(s32 arg0, s32 arg1) {
}

void func_1502ECFC(struct_eu_595D0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    arg0->unkA4 = 4;
    arg0->unkA5 = 0;
    arg0->unkA6 = arg5;
    arg0->unkA0 = (arg4 << 24) | (arg1 << 16) | (arg2 << 8) | arg3;
    arg0->unkA7 = 0xFF;
}

void func_1502ED40(struct_eu_595D0 *arg0) {
    arg0->unkA4 = 5;
}

void func_1502ED50(struct_eu_595D0 *arg0, s32 arg1) {
    arg0->unkA4 = 2;
    arg0->unkA5 = 0xFF;
    arg0->unkA6 = arg1;
}

void func_1502ED6C(struct_eu_595D0 *arg0, s32 arg1) {
    arg0->unkA4 = 3;
    arg0->unkA5 = 0xFF;
    arg0->unkA6 = arg1;
}

void func_1502ED88(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u8 temp_v0;

    temp_v0 = (*(u8 *)((u8 *)arg0 + 0xA4));
    if ((temp_v0 != 6) && (temp_v0 != 7)) {
        if (arg5 != 0) {
            (*(u8 *)((u8 *)arg0 + 0xA5)) = 0xFF;
        } else {
            (*(s8 *)((u8 *)arg0 + 0xA5)) = 0;
        }
        (*(s32 *)((u8 *)arg0 + 0xA0)) = (s32) ((arg4 << 0x18) | (arg1 << 0x10) | (arg2 << 8) | arg3);
        (*(s8 *)((u8 *)arg0 + 0xA6)) = (s8) arg6;
    }
    (*(u8 *)((u8 *)arg0 + 0xA4)) = 6U;
}

#ifdef NON_MATCHING
void func_1502EDEC(struct127 *arg0) {
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_t1;
    u8 temp_t6;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;

    temp_t6 = arg0->unkA4;
    switch (temp_t6) {
    case 2:
    case 3:
        temp_v1 = arg0->unkA5;
        temp_lo = arg0->unkA6 * D_800BE9E4;
        if (temp_lo < (s32) temp_v1) {
            arg0->unkA5 = temp_v1 - temp_lo;
            return;
        }
        arg0->unkA5 = 0;
        return;
    case 5:
        temp_v1_2 = arg0->unkA7;
        temp_t1 = D_800BE9E4 * 0xA;
        if (temp_t1 < (s32) temp_v1_2) {
            arg0->unkA7 = temp_v1_2 - temp_t1;
        } else {
            arg0->unkA4 = 0;
        }
        /* fallthrough */
    case 4:
        arg0->unkA5 += arg0->unkA6 * D_800BE9E4;
        return;
    case 6:
        temp_v1_3 = arg0->unkA5;
        temp_lo_2 = arg0->unkA6 * D_800BE9E4;
        if ((s32) temp_v1_3 < (0xFF - temp_lo_2)) {
            arg0->unkA5 = temp_v1_3 + temp_lo_2;
        } else {
            arg0->unkA5 = 0xFF;
        }
        arg0->unkA4 = 7;
        return;
    case 7:
        temp_v1_4 = arg0->unkA5;
        temp_lo_3 = arg0->unkA6 * D_800BE9E4;
        if (temp_lo_3 < (s32) temp_v1_4) {
            arg0->unkA5 = temp_v1_4 - temp_lo_3;
            return;
        }
        arg0->unkA4 = 0;
    default:
        return;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502EDEC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502EF24.s")

#ifdef NON_MATCHING
/* func_1502F17C (P57): object arg0's mode byte +0x6A + arg1 folded to 0..2 (values 2 / 3 map to 0 / 1). */
s32 func_1502F17C(s32 arg0, s32 arg1) {
    s32 v = ((u8 *)&D_800CC2D0[arg0])[0x6A + arg1];
    if (v >= 2) {
        if (v < 4) v -= 2;
        else v = 2;
    }
    return v;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F17C.s")
#endif

#ifdef NON_MATCHING
s32 func_1502F17C(s32, s32);
void func_1507E7A0(struct127 *);

void func_1502F1E4(s32 arg0) {
    s32 temp_v1;
    s32 var_s1;
    struct127 *var_s0;
    u8 temp_v0;
    u8 temp_v0_2;

    var_s0 = &D_800CC2D0[arg0];
    var_s1 = 0;
    do {
        if ((s32) (*(u8 *)((u8 *)var_s0 + 0x6C)) < 0xA) {
            temp_v1 = func_1502F17C(arg0, var_s1) & 0xFF;
            if (temp_v1 == 0) {
                temp_v0 = (*(u8 *)((u8 *)var_s0 + 0x6C));
                if ((s32) temp_v0 > 0) {
                    (*(u8 *)((u8 *)var_s0 + 0x6C)) = (u8) (temp_v0 - 1);
                }
            } else if (temp_v1 == 1) {
                temp_v0_2 = (*(u8 *)((u8 *)var_s0 + 0x6C));
                if ((s32) temp_v0_2 < 2) {
                    (*(u8 *)((u8 *)var_s0 + 0x6C)) = (u8) (temp_v0_2 + 1);
                }
            } else {
                (*(u8 *)((u8 *)var_s0 + 0x6C)) = 1U;
            }
        }
        var_s1 += 1;
        var_s0 = (struct127 *)((u8 *)var_s0 + (1));
    } while (var_s1 != 2);
    func_1507E7A0(&D_800CC2D0[arg0]);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F1E4.s")
#endif
#ifdef NON_MATCHING
u8 *func_1507ECE8(u8 *, s32);
extern s32 D_800C5758;
/* func_1502F30C (P57): segments 6 +0x18 / +0x1C / +0x28 / +0x2C of object arg1's model: vertex blocks
 * D_800C5758[type][k * 12] for k = the two selector bytes +0x6C / +0x6D (>= 10: k = byte - 10; else the model
 * header table (D_800D1C90[type])[i * 3 + byte + 8], overridden by func_1507ECE8(obj, +0x6F)'s
 * pair when that matches the table's +0xA entry or the byte is 0) and the bytes +0x68 / +0x69. */
u8 *func_1502F30C(u8 *gdl, s32 arg1) {
    u8 *o = (u8 *)&D_800CC2D0[arg1];
    s32 type = o[4];
    u8 *ov = NULL;
    u8 sel[2];
    s32 pr[2];
    s32 i;
    s32 v;
    u8 *p;

    for (i = 0; i < 2; i++) {
        v = o[0x6C + i];
        if (v >= 10) {
            sel[i] = v - 10;
            continue;
        }
        sel[i] = ((u8 *)D_800D1C90[type])[i * 3 + v + 8];
        if (o[0x6F] != 0 && ov == NULL) {
            ov = func_1507ECE8(o, o[0x6F]);
        }
        if (ov == NULL) continue;
        pr[0] = ov[0];
        pr[1] = ov[1];
        v = pr[i];
        if (v == ((u8 *)D_800D1C90[type])[i * 3 + 0xA] || o[0x6C + i] == 0) {
            sel[i] = v;
        }
    }
    p = ((u8 **)&D_800C5758)[o[4]];
    if (p != NULL) {
        u32 *g = (u32 *)gdl;
        g[0] = 0xDB060018;
        g[1] = *(u32 *)(p + sel[0] * 12);
        g[2] = 0xDB06001C;
        g[3] = *(u32 *)(p + sel[1] * 12);
        g[4] = 0xDB060028;
        g[5] = *(u32 *)(p + o[0x68] * 12);
        g[6] = 0xDB06002C;
        g[7] = *(u32 *)(p + o[0x69] * 12);
        gdl += 0x20;
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F30C.s")
#endif

#ifdef NON_MATCHING
/* func_1502F554 (P57): object arg0 attached to parent obj+0x65 (1-based): copy the parent's position
 * (its joint obj+0x5C translation when the parent has a skeleton +0x1D4), +0x180, z offset -4; unless
 * +0x101 & 0x20 the parent's +0x3C / +0x40 / angles; unless & 0x40 the bytes +7..+0xA, +0xF, +0xB.. */
void func_1502F554(s32 arg0) {
    u8 *o = (u8 *)&D_800CC2D0[arg0];
    u8 *p;
    u8 *m;
    s32 i;
    u8 fl;

    if (o[0x65] == 0) return;
    if ((o[0x101] & 2) == 2) return;
    p = (u8 *)&D_800CC2D0[o[0x65]] - 0x32C;
    m = *(u8 **)(p + 0x1D4);
    if (m == NULL) {
        *(f32 *)(o + 0x14) = *(f32 *)(p + 0x14);
        *(f32 *)(o + 0x18) = *(f32 *)(p + 0x18);
        *(f32 *)(o + 0x1C) = *(f32 *)(p + 0x1C);
    } else {
        m += *(s32 *)(o + 0x5C) << 6;
        *(f32 *)(o + 0x14) = *(f32 *)(m + 0x30);
        *(f32 *)(o + 0x18) = *(f32 *)(m + 0x34);
        *(f32 *)(o + 0x1C) = *(f32 *)(m + 0x38);
    }
    fl = o[0x101];
    *(f32 *)(o + 0x180) = *(f32 *)(p + 0x180);
    *(f32 *)(o + 0x20) = -4.0f;
    if (!(fl & 0x20)) {
        *(u16 *)(o + 0x76) = *(u16 *)(p + 0x76);
        fl = o[0x101];
        *(f32 *)(o + 0x3C) = *(f32 *)(p + 0x3C);
        *(f32 *)(o + 0x40) = *(f32 *)(p + 0x40);
        *(u16 *)(o + 0x76) = *(u16 *)(p + 0x76);
        *(u16 *)(o + 0x7A) = *(u16 *)(p + 0x7A);
        *(u16 *)(o + 0x78) = *(u16 *)(p + 0x78);
    }
    if (fl & 0x40) return;
    o[7] = p[7];
    o[8] = p[8];
    o[9] = p[9];
    o[0xA] = p[0xA];
    o[0xF] = p[0xF];
    for (i = 0; i <= D_80082FA0; i++) {
        o[0xB + i] = p[0xB + i];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F554.s")
#endif

#ifdef NON_MATCHING
void func_1502F780(struct127 *arg0, f32 *x, f32 *y, f32 *z, s32 arg4);
/* P48: objects attached to another one (+0x274 = its index + 1): y = +0x180, then func_1502F780 moves the position
 * (+0x14 / +0x18 / +0x1C) with the carrier (+0x19E passed along); y never goes below +0x180, which keeps the max. */
void func_1502F6B8(void) {
    u8 *obj;

    for (obj = (u8 *)D_800CC2D0; obj != (u8 *)&D_800CC2D0[25]; obj += 0x32C) {
        if (*(s32 *)obj == 0 || obj[0x274] == 0) {
            continue;
        }
        *(f32 *)(obj + 0x18) = *(f32 *)(obj + 0x180);
        func_1502F780(&D_800CC2D0[obj[0x274] - 1], (f32 *)(obj + 0x14), (f32 *)(obj + 0x18), (f32 *)(obj + 0x1C),
                      *(u16 *)(obj + 0x19E));
        if (*(f32 *)(obj + 0x18) < *(f32 *)(obj + 0x180)) {
            *(f32 *)(obj + 0x18) = *(f32 *)(obj + 0x180);
        } else {
            *(f32 *)(obj + 0x180) = *(f32 *)(obj + 0x18);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F6B8.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F780.s")

u8 *allocate_memory(s32, s32, s32, s32);
void func_1502FC38(u8 *arg0) {
    s32 temp_v1;
    u8 *temp_v0;
    if ((*(s32 *)(arg0 + 0xF8) & 0x4000) && *(s32 *)(arg0 + 0x264) != 0 && *(s32 *)(arg0 + 0x1D4) != 0) {
        temp_v1 = arg0[4];
        if (*(s32 *)(arg0 + 0x1D8) == 0) {
            temp_v0 = allocate_memory(D_800C52F0[temp_v1] << 6, 1, 1, 2);
            *(u8 **)(arg0 + 0x1D8) = temp_v0;
            if (temp_v0 == NULL) {
                return;
            }
        }
        bcopy(*(u8 **)(arg0 + 0x1D4), *(u8 **)(arg0 + 0x1D8), D_800C52F0[temp_v1] << 6);
    }
}

#ifdef NON_MATCHING
void * func_150C3160(void *, void *);
extern s32 D_800C5758;

u8 *func_1502FCEC(u8 *arg0, s32 arg1) {
    s32 *temp_t4;
    s32 var_a0;
    s32 var_v1;
    struct127 *temp_a2;
    struct127 *var_a1;
    u8 temp_v0;
    u8 *temp_v0_2;
    u8 *var_s0;

    var_s0 = arg0;
    temp_a2 = &D_800CC2D0[arg1];
    temp_v0 = temp_a2->id;
    if ((temp_v0 == 0x89) || (temp_v0 == 0xBA)) {
        return func_150C3160(var_s0, temp_a2);
    }
    if (temp_v0 == 0) {
        var_v1 = 0xE;
    } else {
        var_v1 = 7;
        if (temp_v0 == 0x96) {

        } else {
            var_v1 = 4;
            if (temp_v0 == 0x28) {

            } else if ((temp_v0 == 1) || (temp_v0 == 2) || (temp_v0 == 3) || (var_v1 = 0, (temp_v0 == 4))) {
                var_v1 = 5;
            }
        }
    }
    temp_t4 = ((s32 *)((u8 *)&D_800C5758 + (temp_v0 * 4)));
    var_a0 = 0;
    if (*temp_t4 != 0) {
        var_a1 = &D_800CC2D0[arg1];
        do {
            temp_v0_2 = *temp_t4 + (var_v1 * 0xC);
            (*(s32 *)((u8 *)var_s0 + 0)) = (s32) ((((var_a1->unk27A + 2) & 0xFFFF & 0xFFF) << 0xC) | 0xF2000000 | ((var_a1->unk27E + 2) & 0xFFFF & 0xFFF));
            (*(s32 *)((u8 *)var_s0 + 4)) = (s32) ((((5 - var_a0) & 7) << 0x18) | (((((*(u16 *)((u8 *)temp_v0_2 + 8)) * 4) - 2) & 0xFFFF & 0xFFF) << 0xC) | ((((*(u16 *)((u8 *)temp_v0_2 + 0xA)) * 4) - 2) & 0xFFFF & 0xFFF));
            var_s0 += 8;
            var_a0 += 1;
            var_a1 = (struct127 *)((u8 *)var_a1 + (2));
        } while (var_a0 != 2);
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502FCEC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502FED8.s")

void func_15030060(u8 *arg0)
{
  u8 idx = arg0[4];
  u8 *p;
  u8 *s;
  u8 a2;
  s32 v;
  if ((D_80038080 == 0) && (D_800BE9F0 == 0x1D))
  {
    ((u8 *) D_800D2040)[idx] = 2;
    return;
  }
  p = &((u8 *) D_800D2040)[idx];
  if ((*p) != 0xFF)
  {
    s = *((u8 **) (arg0 + 0x144));
    if (s != 0)
    {
      ;
      if (s[0x2E] != 0xFF)
      {
        if (s[0x2E] != 0)
        {
          ;
          if ((*p) < (s[0x2E] * 30))
          {
            *p = s[0x2E] * 30;
          }
        }
        else
        {
          goto set3;
        }
      }
    }
    else
    {
      set3:
      *p = 3;

    }
    if (arg0)
    {
    }
  }
}
