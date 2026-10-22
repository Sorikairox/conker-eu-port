#include <ultra64.h>

#include "functions.h"
#include "variables.h"

#include "macros.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 func_15002248(s32 x0, s32 x1, s32 z0, s32 z1, s32 *xmin, s32 *zmax, u16 *in, u16 **out);
s32 func_15049260(struct_eu_bytes24 arg0);
void func_15002008(s32 x0, s32 x1, s32 z0, s32 z1, u16 *list);
extern s32 D_800DC26C;   /* triangle table: 3 vertex pointers (s16 x, y, z) per entry */
extern s32 D_800DC274;   /* grid table: s16 x, z per entry */
#endif

void func_15001970(void) {
    s32 pad;
    s32 tmp;

    D_800B0DE4 = 0;
    D_800DBE63 = 0;
    *D_800DBE18 = 0;
    *D_800DBE1C = 0;
    D_800DBE20 = 0;
    tmp = D_80091C04[D_800BE9F0];
    D_800DBE24 = 0;
    D_800B0DC0 = allocate_memory(tmp, 1, 0, 0);
    D_800B0DC8 = tmp + D_800B0DC0;
    D_800B0DC4 = D_800B0DC0;
}

#ifdef NON_MATCHING
extern s32 D_80091EA0[];   /* node pool size per level (rodata) */
extern s32 D_800B11EC;     /* node pool base */
extern s16 D_800DC260;
extern s16 D_800DC262;
extern s16 D_800DC264;
extern s16 D_800DC266;
void func_10023BC0(void);  /* __osPiGetAccess */
void func_10023C04(void);  /* __osPiRelAccess */

/* Node pool for the level quadtrees (func_15001B10 hands out 14-byte nodes, func_15002008 appends the leaf lists).
 * The size per level doubles unless the cart word at ROM 0xD24 is 0x98CCE31A. */
void func_15001A08(void) {
    s32 size;
    s32 word;

    size = D_80091EA0[D_800BE9F0];
    func_10023BC0();
    while (IO_READ(PI_STATUS_REG) & 3) {
    }
    word = IO_READ(D_80000308 | 0xB0000D24);
    func_10023C04();
    if (word != 0x98CCE31A) {
        size <<= 1;
    }
    D_800B11EC = allocate_memory(size, 1, 0, 0);   /* implicit int declaration (func_15001970) */
    D_800B0DE0 = (u8 *) D_800B11EC;
    D_800B0DCC = 0;
    D_800B0DD0 = 0;
    D_800DC260 = 0;
    D_800DC262 = 0;
    D_800DC264 = 0;
    D_800DC266 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2F180/func_15001A08.s")
#endif
// NON-MATCHING: JUSTREG (US draft)
// void func_15001A08(void) {
//     s32 sp24;
//     s32 tmp;
//     s32 sp1C;
//
//     tmp = D_800BE9F0;
//     sp24 = D_80091AF0[tmp];
//
//     __osPiGetAccess();
//
//     while ((IO_READ(PI_STATUS_REG) & 3)) {};
//
//     tmp = D_80000308 | 0xB0000D24 | 0xA0000000;
//     sp1C = *(s32*)tmp;
//
//     __osPiRelAccess();
//
//     if (sp1C != 0x98CCE31A) {
//         sp24 <<= 1;
//     }
//
//     D_800B0DDC = allocate_memory(sp24, 1, 0, 0);
//     D_800B0DE0 = D_800B0DDC;
//     D_800B0DCC = 0;
//     D_800B0DD0 = 0;
//     D_800DBE30 = 0;
//     D_800DBE32 = 0;
//     D_800DBE34 = 0;
//     D_800DBE36 = 0;
// }

u16* func_15001B10(void) {
    u16 *temp_v0;

    D_800B0DE0 = ALIGN4(D_800B0DE0);
    D_800B0DCC += 1;

    temp_v0 = (u16*)D_800B0DE0;
    temp_v0[6] = 0;
    temp_v0[2] = 0;

    D_800B0DE0 += 14;
    return temp_v0;
}

void func_15001B5C(u8 arg0) {
    *D_800B0DE0++ = arg0;
}

void func_15001B8C(u16 arg0) {
   D_800B0DE0[0] = (arg0 >> 8);
   D_800B0DE0[1] = arg0 & 0xFF;
   D_800B0DE0 += 2;
}

void func_15001BC8(s32 arg0, s16 *arg1, s16 *arg2) {
    u16 *tmp;
    s16 *sp20;
    s32 i;

    func_1510F800(arg0);
    D_800B0DD8 = 10;
    D_800B0DD4 = 512;
    sp20 = allocate_memory((D_800DBE4C + 1) << 1, 1, 0, 0);

    *sp20 = D_800DBE4C;
    for (i = 0; i < D_800DBE4C; i++) {
        sp20[i + 1] = i;
    }

    tmp = func_15001DE0(0, 0, 32768, 32768, 0, sp20);
    D_800DBE08[arg0] = tmp;
    func_15002560(tmp, 0);
    func_10004074(sp20);

    // regalloc fix:
    if (1) { }

    if (arg1 != 0) {
        *arg1 = D_800B0DCC;
    }
    if (arg2 != 0) {
        *arg2 = D_800B0DD0;
    }
}

void func_15001CEC(s32 arg0) {
    u16 *temp_v0;
    s16 *sp20;
    s32 i;

    func_1510F800(arg0);
    temp_v0 = func_15001B10();

    D_800DBE08[arg0] = temp_v0;

    *((s16*)temp_v0 + 0) = 32768;
    temp_v0[1] = 32767;
    temp_v0[2] = 0;
    temp_v0[3] = -32768;
    temp_v0[4] = 0;
    temp_v0[5] = 0;
    temp_v0[6] = 0;

    sp20 = allocate_memory((D_800DBE4C + 1) << 1, 1, 0, 0);

    *sp20 = D_800DBE4C;
    for (i = 0; i < D_800DBE4C; i++) {
        sp20[i + 1] = i;
    }

    func_15002008(-0x8000, 0x8000, -0x8000, 0x8000, sp20);
    func_10004074(sp20);
}

u16 *func_15001DE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u16 *temp_v0;
    u16 *temp_v0_2;
    u16 *temp_v0_3;
    u16 *temp_v0_4;

    s32 sp7C;
    s32 sp78;

    s32 tmp0;
    s32 tmp1;

    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;

    tmp0 = D_800B0DD8;
    tmp1 = D_800B0DD4;

    sp54 = arg0 - arg2;
    sp50 = arg0 + arg2;
    sp4C = arg1 - arg3;
    sp48 = arg1 + arg3;

    if ((func_15002248(sp54, sp50, sp4C, sp48, &sp7C, &sp78, arg5, &sp58) < tmp0) || (arg2 < tmp1)) {
        temp_v0 = func_15001B10();
        D_800B0DD0 = (D_800B0DD0 + 1);
        temp_v0[0] = sp7C;
        temp_v0[1] = sp78;
        temp_v0[3] = arg2;
        temp_v0[4] = arg0;
        temp_v0[5] = arg1;
        temp_v0[2] = 0;
        temp_v0[6] = 0;
        func_15002008(sp54, sp50, sp4C, sp48, sp58);
    } else {
        temp_v0 = func_15001B10();
        temp_v0[0] = sp7C;
        temp_v0[1] = sp78;
        temp_v0[3] = arg2;
        temp_v0[4] = arg0;
        temp_v0[5] = arg1;
        temp_v0[2] = 0;

        temp_v0_2 = func_15001DE0(arg0 - (arg2 >> 1), arg1 - (arg3 >> 1), arg2 >> 1, arg3 >> 1, 0, sp58);
        temp_v0[6] = (s32)temp_v0_2 - (s32)temp_v0;
        temp_v0_3 = func_15001DE0(arg0 - (arg2 >> 1), (arg3 >> 1) + arg1, arg2 >> 1, arg3 >> 1, 0, sp58);
        temp_v0_2[2] = (s32)temp_v0_3 - (s32)temp_v0_2;
        temp_v0_4 = func_15001DE0((arg2 >> 1) + arg0, arg1 - (arg3 >> 1), arg2 >> 1, arg3 >> 1, 0, sp58);
        temp_v0_3[2] = (s32)temp_v0_4 - (s32)temp_v0_3;
        temp_v0_4[2] = (s32)func_15001DE0((arg2 >> 1) + arg0, (arg3 >> 1) + arg1, arg2 >> 1, arg3 >> 1, 0, sp58) - (s32)temp_v0_4;
    }
    func_10004074(sp58);
    return temp_v0;
}

// 3 loops
#ifdef NON_MATCHING
/* Leaf list of a quadtree node, appended to the node pool after the node: the entries of the u16 index list
 * `list` (list[0] = count) whose triangle (relative to the box centre, (x0 + x1) / 2 and (z0 + z1) / 2) passes
 * the box test func_15049260 (0 = inside). The first kept index is written as a big-endian halfword | 0x8000;
 * the next ones as one byte (index - previous) when that is below 0x80, else again as a halfword | 0x8000.
 * A 0 byte ends the list. Vertex pointers up to 0x80000000 count as (0, 0, 0). */
void func_15002008(s32 x0, s32 x1, s32 z0, s32 z1, u16 *list) {
    s32 n;
    s32 prev;
    s32 k;
    s32 d;
    u16 *src;
    u16 *end;
    union {
        struct_eu_bytes24 s;
        f32 v[9];
    } tri;

    func_150492CC((f32) (x1 - x0), 32000.0f, (f32) (z1 - z0));
    prev = -1;
    n = list[0];
    if (n > 0) {
        src = &list[1];
        end = &list[n + 1];
        do {
            u16 idx = *src;
            u32 *verts = (u32 *) (D_800DC26C + idx * 12);

            for (k = 0; k < 3; k++) {
                s16 *p = (s16 *) verts[k];
                if ((u32) p < 0x80000001) {
                    tri.v[k * 3 + 0] = 0.0f;
                    tri.v[k * 3 + 1] = 0.0f;
                    tri.v[k * 3 + 2] = 0.0f;
                } else {
                    tri.v[k * 3 + 0] = (f32) (p[0] - (x0 + x1) / 2);
                    tri.v[k * 3 + 1] = (f32) p[1];
                    tri.v[k * 3 + 2] = (f32) (p[2] - (z0 + z1) / 2);
                }
            }
            if (func_15049260(tri.s) == 0) {
                if (prev == -1) {
                    func_15001B8C(idx | 0x8000);
                } else {
                    d = idx - prev;
                    if (d < 0x80) {
                        func_15001B5C(d & 0xFF);
                    } else {
                        func_15001B8C(idx | 0x8000);
                    }
                }
                prev = idx;
            }
            src++;
        } while (src != end);
    }
    func_15001B5C(0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2F180/func_15002008.s")
#endif
#ifdef NON_MATCHING

/* Quadtree build helper of func_15001DE0: keeps the entries of the u16 index list `in` (in[0] = count)
 * whose triangle (relative to the box centre) passes the box test func_15049260 (0 = inside), writes
 * them to a new list *out (in[0] layout; the caller frees it) and returns their count. *xmin / *zmax get
 * the grid-snapped x minimum / z maximum of the kept entries (grid step 2 << D_80082FA0). */
s32 func_15002248(s32 x0, s32 x1, s32 z0, s32 z1, s32 *xmin, s32 *zmax, u16 *in, u16 **out) {
    s32 step = 1 << (D_80082FA0 + 1);
    s32 lo = step - 1;
    s32 mask = -step;
    s32 n;
    s32 cnt;
    s32 found;
    s32 i;
    s32 k;
    u16 *list;
    u16 *src;
    union {
        struct_eu_bytes24 s;
        f32 v[9];
    } tri;

    func_150492CC((f32) (x1 - x0), 32000.0f, (f32) (z1 - z0));
    n = in[0] + 1;
    cnt = 0;
    list = (u16 *) allocate_memory(n * 2, 1, 0, 0);
    *out = list;
    *xmin = 0;
    *zmax = 0;
    found = 0;
    src = &in[1];
    for (i = 1; i < n; i++, src++) {
        u16 idx = *src;
        u32 *verts = (u32 *) (D_800DC26C + idx * 12);
        s16 *g;
        s32 a;
        s32 b;

        for (k = 0; k < 3; k++) {
            s16 *p = (s16 *) verts[k];
            if ((u32) p < 0x80000001) {
                tri.v[k * 3 + 0] = 0.0f;
                tri.v[k * 3 + 1] = 0.0f;
                tri.v[k * 3 + 2] = 0.0f;
            } else {
                tri.v[k * 3 + 0] = (f32) (p[0] - ((x0 + x1) >> 1));
                tri.v[k * 3 + 1] = (f32) p[1];
                tri.v[k * 3 + 2] = (f32) (p[2] - ((z0 + z1) >> 1));
            }
        }
        if (func_15049260(tri.s) != 0) {
            continue;
        }
        list[++cnt] = idx;
        g = (s16 *) (D_800DC274 + idx * 4);
        a = (g[0] - lo) & mask;
        b = ((g[1] + lo) & mask) + lo;
        if (!found) {
            found = 1;
            *xmin = a;
            *zmax = b;
        } else {
            if (a < *xmin) {
                *xmin = a;
            }
            if (*zmax < b) {
                *zmax = b;
            }
        }
    }
    list[0] = cnt;
    return cnt;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2F180/func_15002248.s")
#endif
void func_15002560(struct_eu_qnode *arg0, struct_eu_qnode *arg1) {
    struct_eu_qnode *s1;
    struct_eu_qnode *s0;
    s32 off;

    for (;;) {
        if (arg0 == NULL) {
            return;
        }
        if (arg0->unk4 == 0) {
            if (arg1 != NULL) {
                off = (u8 *)arg1 - (u8 *)arg0;
            } else {
                off = 0;
            }
            arg0->unk4 = off;
        }
        if (arg0->unkC == 0) {
            return;
        }
        s1 = (struct_eu_qnode *)((u8 *)arg0 + arg0->unkC);
        while (s1->unk4 != 0) {
            s0 = (struct_eu_qnode *)((u8 *)s1 + s1->unk4);
            func_15002560(s1, s0);
            s1 = s0;
        }
        arg0 = s1;
    }
}

void func_150025FC(void) {
    s32 tmp0;
    s32 tmp1;
    s32 tmp2;
    s32 tmp3;

    tmp0 = D_800DBE2A;
    tmp1 = D_800DBE2C;

    D_800DBE28 = (((tmp0 + 7) / 8) + 0xF) & 0xFFF0;
    tmp2 = func_1502B5C8(0, 2, 5, D_800BE9F0 << 1);
    tmp3 = func_1502B5C8(0, 2, 5, (D_800BE9F0 << 1) + 1);
    if (tmp2 == 0) {
        D_800BE5D0 = 0;
    } else {
        func_150183D0(D_800DBE28, tmp1, tmp2, tmp3);
        func_10004074(tmp3);
    }
}

void func_150026C4(s32 arg0) {
    D_800DBE38 = 0;
    func_1510F800(arg0);
}

void func_150026E8(s32 arg0) {
    D_800DBE18[arg0] = D_800DBE38;
    D_800DBE4C = D_800DBE38;
    D_800B0DE4 += D_800DBE38;
}

void func_15002724(s32 arg0) {
    D_800DBE38 += func_150027F8(arg0);
}

void func_15002754(void) {
    D_800B0DC0 = (D_800B0DC0 + 3) & ~3;
    D_800DC208[D_800DC280] = D_800B0DC0;
    D_800B0DC0 += D_800DBE38 * 12;
    D_800DC218[D_800DC280] = D_800B0DC0;
    D_800B0DC0 += D_800DBE38 * 8;
    D_800DC228[D_800DC280] = D_800B0DC0;
    D_800B0DC0 += D_800DBE38 * 4;
    func_1510F800(D_800DC280);
    D_800DBE38 = 0;
}


s32 func_150027F8(Gfx *arg0) {
    s32 i;
    s32 count;
    s32 cmd;

    if (arg0 == NULL) {
        return 0;
    }
    i = 0;
    count = 0;
    while ((cmd = ((s8 *)&arg0[i])[0]) != -0x21) {
        i++;
        if ((cmd >> 4) == 1) {
            count += 4;
        } else if (cmd == 6) {
            count += 2;
        } else if (cmd == 5) {
            count += 1;
        }
    }
    return count;
}

s32 func_15002878(void) {
    s32 i;
    s32 tmp;
    s32 highest;

    highest = *D_800DBE18;

    for (i = 0; i < 3; i++) {
        tmp = D_800DBE1C[i];
        if (highest < tmp) {
            highest = tmp;
        }
    }

    return highest;
}

// 12 loops!
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2F180/func_150028BC.s")

void func_15002F40(s32 arg0) {
    if (arg0 == 50 || arg0 == 51) {
        D_800DBE64 = 150.0f;
        return;
    }
    if (D_800BE616) {
        D_800DBE64 = 85.0f;
        return;
    }
    D_800DBE64 = 50.0f;
}

s32 func_15002FA0(s32 arg0) {
    return arg0 ^ 0xF0F0F0F0;
}

void func_15002FB4(s32 arg0) {
    struct00 *sp3C; // TBD
    s32 sp38;
    s32 sp34;
    struct104 *temp_v0;
    s32 sp2C;

    sp3C = func_1502B6BC(&sp34, 0, &sp38, 2, 21, arg0);
    if ((sp38 != 0) && ((sp3C->unk4 << 8) != 0)) {
        D_800B0DF0 = sp3C->unk0;
        if (sp34 == 0) {
            D_8003C8E0 = 0xC000037;
            func_150AD770();
        }
        if (D_800B0DF0 == 0) {
            D_8003C8E0 = 0xC000037;
            func_150AD770();
        }
    }
    func_151EF040(func_15002FA0(0x40F0FAAC), &sp2C);
    sp2C = func_15002FA0(sp2C);
    if (sp2C != 0xE7B00F09) {
        temp_v0 = D_800B0DF0;
        temp_v0->unk12 >>= 1;
    }

    temp_v0 = D_800B0DF0;
    if (temp_v0->unk12 != 0) {
        D_800D2F3C = temp_v0->unk12;
        D_800D2F40 = sp3C->unk8;
    } else {
        D_800D2F3C = 0U;
        D_800D2F40 = 0;
    }

    if ((D_8008FD90 >= 2) && (temp_v0->unk8 == 4)) {
        temp_v0->unk8 = 2U;
    }
}

void func_1500310C(void) {
}
