#include <ultra64.h>
#include "functions.h"
#include "variables.h"


struct249 *func_1509B704(s16 arg0);
void func_1509C120(void);
void func_1509C3A0(void);


void func_1509B4A0(s32 arg0, s32 arg1) {
    s32 i;

    if(0) {};

    D_8003C8E0 = 0x5000000;
    func_1509C120();
    func_15096970();

    for (i = 0; i < D_800D2F3C; i++) {
        if (func_1509CBD4(D_800D2F40[i])) {
            func_1509B5AC(D_800D2F40[i], arg1);
        }
    }

    func_1509C3A0();
    D_8003C8E0 = 0;
}

u16 *func_1509B570(s32 arg0) {
    struct248 *temp_v0;
    u16 res;

    temp_v0 = func_1509B704(arg0);
    if (temp_v0 != 0) {
        res = temp_v0->unkA;
        return (s32)temp_v0 + (res & 0xFFFF);
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B5AC.s")

struct249 *func_1509B704(s16 arg0) {
    struct249 *tmp;
    s32 mask = 0xFFFF03FF;
    s32 i;

    tmp = D_800D2F48.unk4;
    for (i = 0; i < D_800D2F48.length; i++) {
        if (arg0 == (tmp->unk0 & mask)) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}


void func_1509B764(struct249 *arg0) {
    if (D_800D2F48.length == 1) {
        D_800D2F48.unk4 = NULL;
        D_800D2F48.unk8 = NULL;
    } else {
        if (arg0 == D_800D2F48.unk4) {
            D_800D2F48.unk4 = arg0->next;
            arg0->next->prev = NULL;
        } else {
            arg0->prev->next = arg0->next;
        }
        if (arg0 == D_800D2F48.unk8) {
            D_800D2F48.unk8 = arg0->prev;
            arg0->prev->next = NULL;
        } else {
            arg0->next->prev = arg0->prev;
        }
    }
    func_10004074(arg0);
    D_800D2F48.length--;
}

void func_1509B810(struct249 *arg0) {
    s32 var_a3;
    struct249 *temp_v0;
    struct249 *var_v0;
    s32 key;
    var_v0 = D_800D2F48.unk8;
    key = arg0->unk0 & ~0xFC00;
    if (D_800D2F48.length == 0) {
        D_800D2F48.unk4 = arg0;
        D_800D2F48.unk8 = arg0;
        arg0->next = NULL;
        arg0->prev = NULL;
        D_800D2F48.length += 1;
        return;
    }
    var_a3 = 0;
    if ((s32) D_800D2F48.length > 0) {
        do {
            var_a3 += 1;
            if ((var_v0->unk0 & ~0xFC00) < key) {
                if (var_v0 == D_800D2F48.unk8) {
                    arg0->prev = var_v0;
                    arg0->next = NULL;
                    var_v0->next = arg0;
                    D_800D2F48.unk8 = arg0;
                    D_800D2F48.length += 1;
                    return;
                }
                arg0->prev = var_v0;
                arg0->next = var_v0->next;
                var_v0->next->prev = arg0;
                var_v0->next = arg0;
                D_800D2F48.length += 1;
                return;
            }
            var_v0 = var_v0->prev;
        } while (var_a3 < (s32) D_800D2F48.length);
    }
    temp_v0 = D_800D2F48.unk4;
    D_800D2F48.unk4 = arg0;
    arg0->prev = NULL;
    arg0->next = temp_v0;
    temp_v0->prev = arg0;
    D_800D2F48.length += 1;
}

void func_1509B8FC(s16 arg0) {
    struct248 *temp_v0;
    s16 sp18[2];

    temp_v0 = func_1502B5C8(&sp18, 2, 20, arg0);
    temp_v0->unk0 |= arg0;
    temp_v0->unk2 = D_800BE9F0;
    func_1509B950(temp_v0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B950.s")
// NON-MATCHING: register allocation of pad/pos swapped (v1/t0)
// struct_eu_C8950_blk *func_1509B950(struct_eu_C8950_blk *arg0) {
//     u16 pos;
//     s32 pad;
//     struct_eu_C8950_blk *new;
//
//     pad = 8 - (((s32)arg0 + arg0->unk4) & 7);
//     pos = arg0->unk4 + pad;
//     arg0->unk4 = pos + arg0->unk6;
//     arg0->unkA = pos;
//     arg0->unk4 = arg0->unk4 - (((s32)arg0 + arg0->unk4) & 7) + 8;
//     new = allocate_memory(arg0->unk4, 0xFF, 2, 0);
//     if (new == NULL) {
//         while (1) {
//         }
//     }
//     bcopy(arg0, new, arg0->unk4);
//     bzero((u8 *)new + new->unkA, new->unk6);
//     func_10004074(arg0);
//     return new;
// }

#ifdef NON_MATCHING
s32 func_150ADFD0(struct249 *, s32);
void func_1509B764(struct249 *);
void func_1509C228(void);

void func_1509BA04(s32 arg0) {
    s32 count;
    s32 i;
    s32 id;
    s32 byte;
    s32 bit;
    u16 flags;
    struct249 *e;
    struct249 *next;
    u8 *state = (u8 *)&D_800D2E70;

    e = D_800D2F48.unk4;
    count = D_800D2F48.length;
    if (D_800D3289 != 0) {
        func_1509C228();
        D_800D3289 = 0;
    }
    for (i = 0; i < count; i++) {
        flags = e->unk0;
        id = flags & 0xFFFF03FF;
        byte = id >> 3;
        bit = 1 << (id & 7);
        next = e->next;
        if ((((u8 *)D_800D2E4C)[byte] & bit) && arg0 == 0) {
            func_1509B764(e);
            state[id] = 3;
        } else if (arg0 != 0 || (flags & 0x8000) ||
                   ((flags & 0x1000) && D_800BE9F0 != *(u16 *)((u8 *)e + 2))) {
            D_8003C8E0 = 0x06000001;
            func_150ADFD0(e, 3);
            D_8003C8E0 = 0;
            func_1509B764(e);
            if (((u8 *)D_800D2E4C)[byte] & bit) {
                state[id] = 3;
            } else {
                state[id] = 0;
            }
        }
        e = next;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BA04.s")
#endif
#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, ...);
s32 func_150ADFD0(struct249 *, s32);
extern s16 D_800BEE12;
extern s32 D_800D3268;
extern s32 D_800D3378;

void func_1509BBA0(s32 arg0) {
    s32 temp_v0;
    s32 var_a1;
    s32 var_s5;
    struct249 *var_s0;
    u16 temp_a2;
    u16 temp_t1;
    u16 var_v1;

    var_s0 = D_800D2F48.unk4;
    func_15097118();
    if ((D_800BE616 != 0) || (D_800BE9F0 == 0x32) || (func_1509BE40(0, 0x2000, 0x93) != 0) || (arg0 != 2)) {
        func_1509C228();
        temp_a2 = D_800D2F48.length;
        var_s5 = 0;
        if ((s32) temp_a2 > 0) {
            do {
                temp_v0 = var_s0->unk0 & 0x3FF;
                D_800D3268 = temp_v0;
                var_v1 = var_s0->unk0;
                var_a1 = var_v1 & 0x8000;
                if (var_a1 != 0) {
                    goto block_26;
                }
                if (arg0 == 4) {
                    if (((u8 *)D_800D2E4C)[temp_v0 >> 3] & (1 << (temp_v0 & 7))) {
                        D_8003C8E0 = 0x06000002;
                        func_150ADFD0(var_s0, 4);
                        D_8003C8E0 = 0;
                        ((u8 *)&D_800D2E70)[temp_v0] = 3;
                        var_s0->unk0 |= 0x8000;
                        var_s0 = var_s0->next;
                    } else {
                        goto block_26;
                    }
                } else if (!(((u8 *)D_800D2E4C)[temp_v0 >> 3] & (1 << (temp_v0 & 7)))) {
                    if (var_v1 & 0x4000) {
                        D_8003C8E0 = 0x06000003;
                        func_150ADFD0(var_s0, 1);
                        D_8003C8E0 = 0;
                        temp_t1 = var_s0->unk0 & 0xBFFF;
                        var_v1 = temp_t1 & 0xFFFF;
                        var_a1 = var_v1 & 0x8000;
                        var_s0->unk0 = temp_t1;
                    }
                    if (var_a1 != 0) {
                        var_s0 = var_s0->next;
                    } else {
                        if (!(var_v1 & 0x2000) || (D_800BE9F0 == (*(u16 *)((u8 *)var_s0 + 2)))) {
                            if ((arg0 == 2) || ((arg0 == 1) && !(var_v1 & 0x400))) {
                                D_8003C8E0 = 0x06000004;
                                func_150ADFD0(var_s0, arg0);
                                D_8003C8E0 = 0;
                            }
                            if (arg0 == 2) {
                                ((u8 *)&D_800D2E70)[temp_v0] = 1;
                            }
                        } else {
                            ((u8 *)&D_800D2E70)[temp_v0] = 2;
                        }
                        goto block_26;
                    }
                } else {
                    ((u8 *)&D_800D2E70)[temp_v0] = 3;
block_26:
                    var_s0 = var_s0->next;
                }
                var_s5 += 1;
            } while (var_s5 < (s32) temp_a2);
        }
        if (D_800D3378 != 0) {
    s32 pad;
            D_800D3378 = 0;
            func_1509B4A0((s32) D_800BEE12, 0);
        }
        D_800D3858 = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BBA0.s")
#endif
//
#ifdef NON_MATCHING
#include <stdarg.h>
extern s32 D_800D3380[];
extern s32 D_800D3C60;
extern s32 (*D_80088838[])(s32, s32, s32 *);

/* P43: variadic event dispatch. func_1509BE40(n, id, arg, x1 .. xn): D_800D3380 = {id & 0xFFF, arg, x1 .. xn},
 * D_800D3C60 = n + 2 during the call (restored after), returns D_80088838[(id >> 12 & 0xF) - 1](id & 0xFFF, arg,
 * D_800D3380). Callers pass 3 to 8 words; every caller's NON_MATCHING prototype is now `(s32, s32, ...)`. */
s32 func_1509BE40(s32 n, s32 id, ...) {
    va_list ap;
    s32 saved;
    s32 arg;
    s32 i;
    s32 r;

    va_start(ap, id);
    saved = D_800D3C60;
    arg = va_arg(ap, s32);
    D_800D3380[0] = id & 0xFFF;
    D_800D3380[1] = arg;
    for (i = 0; i < n; i++) {
        D_800D3380[i + 2] = va_arg(ap, s32);
    }
    va_end(ap);
    D_800D3C60 = n + 2;
    r = D_80088838[((id & 0xF000) >> 12) - 1](id & 0xFFF, arg, D_800D3380);
    D_800D3C60 = saved;
    return r;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BE40.s")
#endif

#ifdef NON_MATCHING
extern void (*D_80088874[])(s32, s32, s32 *);

/* Variadic event dispatch like func_1509BE40, on the second handler table: func_1509BFB0(n, id, arg, x1 .. xn) sets
 * D_800D3380 = {id & 0xFFF, arg, x1 .. xn} and D_800D3C60 = n + 2 for the call (restored after), then calls
 * D_80088874[(id >> 12 & 0xF) - 1](id & 0xFFF, arg, D_800D3380). */
void func_1509BFB0(s32 n, s32 id, s32 arg, ...) {
    va_list ap;
    s32 saved;
    s32 i;

    va_start(ap, arg);
    saved = D_800D3C60;
    D_800D3380[0] = id & 0xFFF;
    D_800D3380[1] = arg;
    for (i = 0; i < n; i++) {
        D_800D3380[i + 2] = va_arg(ap, s32);
    }
    va_end(ap);
    D_800D3C60 = n + 2;
    D_80088874[((id & 0xF000) >> 12) - 1](id & 0xFFF, arg, D_800D3380);
    D_800D3C60 = saved;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BFB0.s")
#endif

// need a bigger brain
void func_1509C120(void) {
    s32 n;
    s32 i;
    struct102 *sp38[4];
    struct102 *sp34;
    n = func_150ADA20() & 3;
    sp34 = D_800D2E4C;
    if (sp34 == NULL || (func_150ADA20() & 4)) {
        for (i = 0; i <= n; i++) {
            sp38[i] = (struct102 *)allocate_memory(0x1B, 0xFF, 2, 0);
        }
        for (i = 0; i <= n; i++) {
            if (i != n) {
                func_10004074(sp38[i]);
            }
        }
        D_800D2E4C = sp38[n];
        if (sp34 != NULL) {
            bcopy(sp34, D_800D2E4C, 0x1B);
            func_10004074(sp34);
        }
    }
}

void func_1509C228(void) {
    if ((D_800D2E68 & 8) || (D_800D2E4C->unkF & 1)) {
        func_1509BFB0(2, 0x2000, 0x36, 0, 1);
        return;
    }
    func_1509BFB0(2, 0x2000, 0x36, 1, 1);
}

s32 func_1509C2A4(void) {
    s32 temp_v0 = D_800BE9F0;
    if ((temp_v0 == 3) ||
        (temp_v0 == 5) ||
        (temp_v0 == 9) ||
        (temp_v0 == 13) ||
        (temp_v0 == 15) ||
        (temp_v0 == 17) ||
        (temp_v0 == 21) ||
        (temp_v0 == 22) ||
        (temp_v0 == 24) ||
        (temp_v0 == 26) ||
        (temp_v0 == 29) ||
        (temp_v0 == 31) ||
        (temp_v0 == 32) ||
        (temp_v0 == 33) ||
        (temp_v0 == 34) ||
        (temp_v0 == 36) ||
        (temp_v0 == 37) ||
        (temp_v0 == 42) ||
        (temp_v0 == 43) ||
        (temp_v0 == 45) ||
        (temp_v0 == 48) ||
        (temp_v0 == 51) ||
        (temp_v0 == 52) ||
        (temp_v0 == 56) ||
        (temp_v0 == 62) ||
        (temp_v0 == 63) ||
        (D_800D2E44 != 0)
      ) {
        return 0;
    }
    return 1;
}

void func_1509C3A0(void) {
    if ((D_800D2E43 != 0) && (D_800D2E44 == 0) && (func_1509C2A4() != 0)) {
        D_800BE3DF = (s8) D_800BE9F4;
        if (D_800C35C4 == 0) {
            func_15007718(D_8008FDA8);
        }
        D_800D2E43 = 0;
    }
}


s32 func_1509C414(s32 arg0) {
    return ((D_800D2E4C->unk3 & 1) << 0xA) + arg0 + 0x1400;
}
