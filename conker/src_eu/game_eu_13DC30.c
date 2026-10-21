#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_15115244();


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110420.s")

void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_1511084C(f32 (*arg0)[4], f32 arg1, f32 arg2, f32 arg3) {
    f32 sp28[4][4];
    func_150A8050(arg0, 0.0f, arg2, 0.0f);
    func_150A8050(sp28, arg1, 0.0f, 0.0f);
    func_150A7A48(arg0, sp28, arg0);
    func_150A8050(sp28, 0.0f, 0.0f, arg3);
    func_150A7A48(arg0, sp28, arg0);
}

void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_1511084C(f32 (*)[4], f32, f32, f32);
void func_151108E0(s32 arg0, f32 (*arg1)[4], f32 arg2, f32 arg3, f32 arg4) {
    func_1511084C(arg1, arg2, arg3, arg4);
    func_150A7A48(arg1, (f32 (*)[4])((u8 *)D_800BE628 + arg0 * 0x180 + 0xBC), arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110948.s")

Gfx *func_15110AC4(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 r, u8 g, u8 b) {
    gDPPipeSync(gdl++);
    gDPSetOtherMode(gdl++, 0x302C0F, 4);
    gdl = func_1501A680(gdl);
    gDPSetFillColor(gdl++, (GPACK_RGBA5551(r, g, b, 1) << 16) | GPACK_RGBA5551(r, g, b, 1));
    return func_1501A6CC(gdl, arg1, arg2, arg3, arg4);
}

extern u8 D_800DC2D8[];
Gfx *func_15110B80(Gfx *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if ((D_800BE9F0 == 0x1B) || (D_800BE9F0 == 0x1E) || ((D_800BE9F0 == 0x31) && (*(u8 *)((u8 *)D_800DBFF0->unk3D4 + 0x78) == 3))) {
        arg0 = func_15110AC4(arg0, 2, 0, D_800BE620 - 2, D_800BE624, D_800DC2D8[0], D_800DC2D8[1], D_800DC2D8[2]);
    }
    return arg0;
}

#ifdef NON_MATCHING
extern u8 D_800BEEE2;

u8 *func_15110C28(u8 *arg0) {
    s32 temp_t5;
    s32 temp_t7;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *var_a0;

    var_a0 = arg0;
    if (D_80082FA4 == 0) {
        temp_a0 = var_a0 + 8;
        (*(s32 *)((u8 *)var_a0 + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)var_a0 + 4)) = 0;
        (*(s32 *)((u8 *)temp_a0 + 4)) = 4;
        (*(s32 *)((u8 *)temp_a0 + 0)) = 0xEF302C0F;
        temp_a0_2 = temp_a0 + 8;
        (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xFCFFFFFF;
        (*(s32 *)((u8 *)temp_a0_2 + 4)) = 0xFFFE793C;
        temp_a0_3 = temp_a0_2 + 8;
        (*(s32 *)((u8 *)temp_a0_3 + 0)) = (s32) (((D_800BE620 - 1) & 0xFFF) | 0xFF100000);
        temp_a0_4 = temp_a0_3 + 8;
        (*(s32 *)((u8 *)temp_a0_3 + 4)) = (s32) D_800BEDE4;
        (*(s32 *)((u8 *)temp_a0_4 + 0)) = 0xF7000000;
        (*(s32 *)((u8 *)temp_a0_4 + 4)) = 0xFFFCFFFC;
        temp_v0 = func_1501A490((s32) (temp_a0_4 + 8), 0xFF, 0, 0, 0, 0);
        (*(s32 *)((u8 *)temp_v0 + 4)) = 0x8000;
        (*(s32 *)((u8 *)temp_v0 + 0)) = (s32) ((((D_800BE620 - 2) & 0x3FF) << 0xE) | 0xF6000000 | ((D_800BE624 & 0x3FF) * 4));
        (*(s32 *)((u8 *)temp_v0 + 8)) = 0xE7000000;
        (*(s32 *)((u8 *)temp_v0 + 0xC)) = 0;
        temp_v0_2 = func_1501A680(temp_v0 + 0x10);
        var_a0 = temp_v0_2;
        if (D_80082FA0 != 0) {
            (*(s32 *)((u8 *)temp_v0_2 + 0)) = 0xE7000000;
            (*(s32 *)((u8 *)temp_v0_2 + 4)) = 0;
            temp_v0_3 = func_1501A490((s32) (var_a0 + 8), 0xFF, 0, 0, 0, 0);
            (*(s32 *)((u8 *)temp_v0_3 + 0)) = 0xF7000000;
            (*(s32 *)((u8 *)temp_v0_3 + 4)) = 0x10001;
            temp_t5 = (s32) D_800BE624 >> 1;
            var_a0 = func_1501A6CC(temp_v0_3 + 8, 0, temp_t5 - 6, D_800BE620, temp_t5 + 6);
            if (D_80082FA0 != 1) {
                temp_t7 = (s32) D_800BE620 >> 1;
                var_a0 = func_1501A6CC(var_a0, temp_t7 - 1, 0, temp_t7 + 1, D_800BE624);
            }
            if (D_800BEEE2 != 0) {
                var_a0 = func_1501A6CC(var_a0, 0, 0, D_800BE620, D_800BE624);
            }
        }
    }
    return var_a0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110C28.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110E44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_1511127C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15111CAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15111DD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15112074.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15112AA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113000.s")

#ifdef NON_MATCHING
void func_15113700(void) {
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 temp_a1;

    var_v0 = 0;
    var_v1 = 0;
    if (D_800DC320 > 0) {
        do {
            temp_a0 = &D_800DBEF4->pad[var_v1];
            (*(u8 *)((u8 *)temp_a0 + 0x6F)) = (u8) ((*(u8 *)((u8 *)temp_a0 + 0x6F)) & ~0x40);
            temp_a0_2 = &D_800DBEF4->pad[var_v1];
            temp_a1 = (*(u8 *)((u8 *)temp_a0_2 + 0x6F));
            if (((temp_a1 & 0xF) || (((*(u8 *)((u8 *)temp_a0_2 + 0x70)) & 4) == 4)) && ((*(s32 *)((u8 *)temp_a0_2 + 0x38)) != 0)) {
                (*(u8 *)((u8 *)temp_a0_2 + 0x6F)) = (u8) (temp_a1 | 0x40);
            }
            var_v0 += 1;
            var_v1 += 0xA0;
        } while (var_v0 < D_800DC320);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113700.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113798.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113B44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113D54.s")

extern u8 D_800C3A7C;
s32 func_15022BB0(s32, s32);
void *func_1510DEF0(s32, struct131 *, s32, s32, s32);

void func_15114208(void) {
    s32 i;
    s32 j;
    s32 found;
    s32 ok;
    struct131 *e;

    for (i = 0; i < D_800DC320; i++) {
        e = &D_800DBEF4[i];
        found = 0;
        for (j = 0; j < D_80082FA0; j++) {
            do {
            } while (0); // fakematch: changes the s-register allocation
            if (func_150859AC(j, 0) && ((u8 *)e)[0x8B + j] == 0) {
                found = 1;
                break;
            }
        }
        if ((e->pad70[0] & 8) || ((u8 *)e)[0x4C] == 0 || (((u8 *)e)[0x4F] & 0x10) == 0x10 || found ||
            (D_800C3A7C == 0 && D_800C35EA == 1 && !func_15022BB0(i, 0)) || !(((u8 *)e)[0x4F] & 1)) {
            ok = 0;
        } else {
            ok = 1;
        }
        if (ok) {
            if (*(void **)((u8 *)e + 0x94) == NULL) {
                *(void **)((u8 *)e + 0x94) = func_1510DEF0(1, e, 0, 1, 0);
            }
        } else if (*(struct102 **)((u8 *)e + 0x94) != NULL) {
            func_1516972C(*(struct102 **)((u8 *)e + 0x94));
            *(struct102 **)((u8 *)e + 0x94) = NULL;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151143D4.s")

extern s32 *D_800DC3C4;

s32 func_151145D0(struct131 *arg0, s32 arg1) {
    if (*((u8 *)arg0 + 0x4F) & 0x80) {
        if (arg1 == -1) {
            return 1;
        }
        if (D_800DC3C4[arg0 - D_800DBEF4] & (1 << arg1)) {
            return 1;
        }
    }
    return 0;
}

s32 func_15114644(u8 *arg0) {
    s32 i;
    s32 v;
    s32 m; // fakematch: mask temp fixes the and operand order
    i = 0;
    if (arg0[0x4F] & 0x80) {
        v = D_800DC3C4[(arg0 - (u8 *)D_800DBEF4) / 160];
loop:
        m = 1 << i;
        if ((v & m) != 0) return i;
        m = 1 << (i + 1);
        if ((v & m) != 0) return i + 1;
        m = 1 << (i + 2);
        if ((v & m) != 0) return i + 2;
        m = 1 << (i + 3);
        if ((v & m) != 0) return i + 3;
        i += 4;
        if (i != 0x20) goto loop;
    }
    return 0;
}

#ifdef NON_MATCHING
void func_15114CBC(struct127 *, s32);
extern s32 *D_800DC3C4;
typedef void (*fn15114708)(u8 *, struct127 *, u8 *, void *);

void func_15114708(void) {
    s32 i;
    s32 j;
    s32 *mask;
    u8 *e;
    u8 *base;
    fn15114708 fn;
    struct127 *obj;
    u8 f;

    for (i = 0; i < D_800DC320; i++) {
        if (D_800DC3C4[i] == 0) {
            continue;
        }
        for (j = 0; j < 0x19 && D_800DC3C4[i] != 0; j++) {
            mask = &D_800DC3C4[i];
            if (!(*mask & (1 << j))) {
                continue;
            }
            *mask ^= 1 << j;
            base = (u8 *)D_800DBEF4;
            e = base + i * 0xA0;
            fn = *(fn15114708 *)(e + 0x78);
            obj = (struct127 *)((u8 *)D_800CC2D0 + j * 0x32C);
            if (fn != NULL && (e[0x92] != 0 || ((u8 *)obj)[0x127] != 0xFF)) {
                (*fn)(e, obj, base, (void *)fn);
                e = (u8 *)D_800DBEF4 + i * 0xA0;
            }
            f = e[0x4F];
            if ((f & 4) == 4 && !(f & 8)) {
                func_15114CBC(obj, i);
            }
        }
        e = (u8 *)D_800DBEF4 + i * 0xA0;
        e[0x4F] &= 0x73;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15114708.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151148C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15114CBC.s")

void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_15114E28(f32 (*arg0)[4], u8 *arg1) {
    f32 sp18[4][4];
    func_150A8050(arg0, 0.0f, *(f32 *)(arg1 + 4), 0.0f);
    func_150A8050(sp18, *(f32 *)arg1, 0.0f, *(f32 *)(arg1 + 8));
    func_150A7A48(sp18, arg0, arg0);
}

void func_15114E8C(f32 (*arg0)[4], u8 *arg1) {
    f32 sp20[4][4];

    func_15114E28(arg0, arg1);
    (*(f32 *)((u8 *)arg0 + 0x30)) = *(s16 *)(arg1 + 0x10);
    (*(f32 *)((u8 *)arg0 + 0x34)) = *(f32 *)(arg1 + 0x18) + *(s16 *)(arg1 + 0x12);
    (*(f32 *)((u8 *)arg0 + 0x38)) = *(s16 *)(arg1 + 0x14);
    func_150A7CB0(sp20, *(s32 *)(arg1 + 0x2C), *(s32 *)(arg1 + 0x30), *(s32 *)(arg1 + 0x34));
    func_150A7A48(sp20, arg0, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151149AC.s")

#ifdef NON_MATCHING
/* Per-frame release of the per-entry blocks D_800DC328[i] (P15, hand C from the asm). Entries are the
 * 0xA0-byte D_800DBEF4 records. A disabled entry (flag 0x70 & 1) drops its block pointer unless it is
 * kept (0x6F & 0x80). Otherwise a live block is freed at once, or, for kept / type-3 entries (0x4E),
 * after its D_800DC32C[i] frame countdown reaches 0. */
void func_10004074(s32);
void func_15114F9C(void) {
    s32 i;

    for (i = 0; i < D_800DC320; i++) {
        u8 *e = (u8 *)D_800DBEF4 + i * 0xA0;

        if ((e[0x70] & 1) == 1) {
            if (!(e[0x6F] & 0x80)) {
                D_800DC328[i] = 0;
            }
        } else if (D_800DC328[i] != 0) {
            if (e[0x4E] != 3 && !(e[0x6F] & 0x80)) {
                func_10004074(D_800DC328[i]);
                D_800DC328[i] = 0;
            } else if (D_800DC32C[i] != 0) {
                D_800DC32C[i]--;
            } else {
                func_10004074(D_800DC328[i]);
                D_800DC328[i] = 0;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15114F9C.s")
#endif
extern s32 D_800DC3C8;

void func_15115114(u32 arg0) {
    struct131 *p;
    u32 j;

    j = arg0 * 0xA0; // fakematch: j doubles as the row offset
    if (arg0 < D_800DC320) {
        p = (struct131 *)((u8 *)D_800DBEF4 + j);
        if (*(struct102 **)((u8 *)p + 0x94) != NULL) {
            func_1516972C(*(struct102 **)((u8 *)p + 0x94));
            *(struct102 **)((u8 *)D_800DBEF4 + arg0 * 0xA0 + 0x94) = NULL;
            p = (struct131 *)((u8 *)D_800DBEF4 + arg0 * 0xA0);
        }
        p->pad70[0] |= 8;
        D_800DBEF4[arg0].pad5A[0x14] = 1;
    }
    arg0 = D_800DC320 - 1;
    j = D_800DC320 - D_800DC3C8;
    if (D_800DC320 != 0) {
        p = (struct131 *)((u8 *)D_800DBEF4 + arg0 * 0xA0);
        if (p->pad70[0] & 8) {
            do {
                if (arg0 >= j && D_800DC3C8 != 0) {
                    D_800DC3C8--;
                } else {
                    j--;
                }
                D_800DC320--;
                arg0--;
                p--;
            } while (D_800DC320 != 0 && (p->pad70[0] & 8));
        }
    }
}

s32 func_15115244(u8 *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x18));
    if ((temp_v1 != NULL) && ((*arg2 != 0) || ((*(s32 *)((u8 *)arg0 + 0x1C)) == 0))) {
        (*(s32 *)((u8 *)arg0 + 0x1C)) = 1;
        (*(s16 *)((u8 *)arg0 + 2)) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x10));
        (*(s16 *)((u8 *)arg0 + 4)) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x12));
        (*(s16 *)((u8 *)arg0 + 6)) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x14));
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151152A4.s")

void func_15115484(s32 arg0, s32 arg1, s32 arg2) {
    func_1001001C(func_15115244, arg0, 0, arg1, arg2);
}

s32 func_150ADC50();
extern s32 D_800DC3CC;
extern s32 D_800DC3D0;
extern s32 D_800DC3D4;

void func_151154C4(s32 arg0, s32 arg1, s32 arg2)
{
    s32 i;
    s32 j;
    if (D_800BE9F0 == 0x12 || D_800BE9F0 == 0x36 || D_800BE9F0 == 0x13) {
        for (i = 0; i < 2; i++) {
            u32 *base = (u32 *)D_800DC208[i];
            for (j = 0; j < D_800DBE18[i]; j++) {
                if ((base[j * 3 + 0] & 0xF0000000) != 0x80000000 || (base[j * 3 + 1] & 0xF0000000) != 0x80000000 || (base[j * 3 + 2] & 0xF0000000) != 0x80000000 || (base[j * 3 + 0] & 3) || (base[j * 3 + 1] & 3) || (base[j * 3 + 2] & 3)) {
                    D_8003C8E0 = 0x0C00005A;
                    func_150ADC50();
                }
            }
        }
        D_800DC3CC = arg0;
        D_800DC3D0 = arg1;
        D_800DC3D4 = arg2;
    }
}
