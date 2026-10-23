#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
typedef struct Node8D80 { u8 u0; u8 u1; u8 u2; u8 u3; u8 u4; s16 u6; void *u8_; struct Node8D80 *uC; struct127 *u10; s32 u14; } Node8D80;
void *allocate_memory(s32, s32, s32, s32);
void func_10004074(u8 *);
s32 func_1502DE10(u8);
void func_15188FC8();

// object_trail_start: starts (or extends) the trail effect of obj (scene event 5 / 0x2D): an existing node of the
// D_800DF7C8 list for obj gets the longer duration and the new style; else a 0x18-byte node (type 3, 0x14) with a
// zeroed buffer of 0x180 bytes per trail point of the object's kind (func_1502DE10(kind), 0 = no trail) is appended.
void func_15188D80(struct127 *obj, s32 frames, s32 style) {
    Node8D80 *n;
    void *buf;
    s32 count;

    for (n = *(Node8D80 **) D_800DF7C8; n != NULL; n = n->uC) {
        if (obj == n->u10) {
            if (n->u6 < frames) {
                n->u6 = frames;
            }
            n->u4 = style;
            return;
        }
    }
    n = allocate_memory(0x18, 1, 0, 0);
    if (n == NULL) {
        return;
    }
    count = func_1502DE10(((u8 *) obj)[4]);
    if (count == 0) {
        func_10004074((u8 *) n);
        return;
    }
    buf = allocate_memory(count * 0x180, 1, 1, 1);
    if (buf == NULL) {
        func_10004074((u8 *) n);
        return;
    }
    n->u0 = 0;
    n->u1 = 3;
    n->u2 = 0;
    n->u3 = 0x14;
    n->u4 = style;
    n->u8_ = buf;
    n->u10 = obj;
    n->u14 = 0;
    n->u6 = frames;
    bzero(buf, count * 0x180);
    func_15188FC8(n, D_800DF7C8);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_15188D80.s")
#endif

typedef struct Node8EBC { u8 u0; u8 u1; u8 u2; u8 u3; u8 u4; s16 u6; void *u8_; struct Node8EBC *uC; s32 u10; } Node8EBC;
extern Node8EBC *D_800DFBFC;
void *allocate_memory(s32, s32, s32, s32);
#ifdef NON_MATCHING // the definition is void; one signature for wasm
void func_10004074(u8 *);
#else
s32 func_10004074(u8 *);
#endif
void func_15188FC8();
void func_15188EBC(s32 arg0, s32 arg1, s32 arg2) {
    Node8EBC *n;
    void *buf;

    for (n = D_800DFBFC; n != NULL; n = n->uC) {
        if (arg0 == n->u10) {
            if (n->u6 < arg1) {
                n->u6 = arg1;
            }
            n->u4 = arg2;
            return;
        }
    }
    n = allocate_memory(0x14, 1, 0, 0);
    if (n == NULL) {
        return;
    }
    buf = allocate_memory(0x180, 1, 1, 0);
    if (buf == NULL) {
        func_10004074((u8 *)n);
        return;
    }
    n->u0 = 1;
    n->u1 = 3;
    n->u2 = 0;
    n->u3 = 0x14;
    n->u4 = arg2;
    n->u6 = arg1;
    n->u8_ = buf;
    n->u10 = arg0;
    bzero(buf, 0x180);
    func_15188FC8(n, &D_800DFBFC);
}

typedef struct struct_15188FC8 {
    u8 pad0[0xC];
    struct struct_15188FC8 *unkC;
} struct_15188FC8;

void func_15188FC8(struct_15188FC8 *arg0, struct_15188FC8 **arg1) {
    struct_15188FC8 *var_v1;

    arg0->unkC = NULL;
    if (*arg1 != NULL) {
        for (var_v1 = *arg1; var_v1->unkC != NULL; var_v1 = var_v1->unkC) {
        }
        var_v1->unkC = arg0;
    } else {
        *arg1 = arg0;
    }
}

void func_1518900C(s32 arg0) {
    struct_eu_1B6590 *var_v0 = (struct_eu_1B6590 *)D_800DF7C8[0];
    while (var_v0 != NULL) {
        if (arg0 == var_v0->unk10) {
            var_v0->unk6 = 0;
        }
        var_v0 = var_v0->unkC;
    }
}

#ifdef NON_MATCHING // the definition is void; one signature for wasm
void func_10004074(u8 *);
#else
s32 func_10004074(u8 *);
#endif

void func_15189040(s32 arg0) {
    s32 temp_s0;
    s32 var_s1;
    u8 *var_s2;

    var_s1 = *D_800DF7C8;
    var_s2 = NULL;
    if (var_s1 != 0) {
        do {
            temp_s0 = (*(s32 *)((u8 *)var_s1 + 0xC));
            if (arg0 == (*(s32 *)((u8 *)var_s1 + 0x10))) {
                if (var_s2 == NULL) {
                    *D_800DF7C8 = temp_s0;
                } else {
                    (*(s32 *)((u8 *)var_s2 + 0xC)) = temp_s0;
                }
                func_100043B4((*(s32 **)((u8 *)var_s1 + 8)), 2U);
                func_10004074((u8 *) var_s1);
            } else {
                var_s2 = (u8 *) var_s1;
            }
            var_s1 = temp_s0;
        } while (temp_s0 != 0);
    }
}

extern void (*D_8008D920[])(struct_eu_1B6590 *);
extern void (*D_8008D928[])(struct_eu_1B6590 *);
#ifdef NON_MATCHING // the definition is void; one signature for wasm
void func_10004074(u8 *);
#else
s32 func_10004074(u8 *);
#endif
void func_151890E4(s32 arg0) {
    struct_eu_1B6590 **head;
    struct_eu_1B6590 *n;
    struct_eu_1B6590 *next;
    struct_eu_1B6590 *prev;
    s32 v;

    head = (struct_eu_1B6590 **)&D_800DF7C8[arg0];
    prev = NULL;
    for (n = *head; n != NULL; n = next) {
        next = n->unkC;
        if (n->unk6 != 0) {
            n->unk6 -= D_800BE9E4;
        }
        if (n->unk6 < 0) {
            n->unk6 = 0;
        }
        D_8008D920[n->pad0[0]](n);
        v = n->pad0[3];
        if (n->unk6 != 0) {
            if (v != 0xFF) {
                v += D_800BE9E4 * 16;
                if (v >= 0x100) {
                    v = 0xFF;
                }
                n->pad0[3] = v;
            }
            prev = n;
        } else if (v != 0) {
            v -= D_800BE9E4 * 8;
            if (v < 0) {
                v = 0;
            }
            if (v == 0) {
                if (prev == NULL) {
                    *head = next;
                } else {
                    prev->unkC = next;
                }
                D_8008D928[n->pad0[0]](n);
                func_10004074((u8 *)n);
            } else {
                n->pad0[3] = v;
                prev = n;
            }
        }
    }
}

extern Gfx *(*D_8008D930[])(Gfx *, struct_eu_1B6590 *, s16);
Gfx *func_15189270(Gfx *gfx, s32 arg1, s16 arg2) {
    struct_eu_1B6590 *n;

    n = (struct_eu_1B6590 *)D_800DF7C8[arg1];
    if (n == NULL) {
        return gfx;
    }
    gSPMatrix(gfx++, D_80089810, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPGeometryMode(gfx++, 0, 0x200004);
    gSPGeometryMode(gfx++, 0x110000, 0);
    gDPPipeSync(gfx++);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetConvert(gfx++, 0, 0, 0, 0, 0, 0xFF);
    while (n != NULL) {
        gfx = D_8008D930[n->pad0[0]](gfx, n, arg2);
        n = n->unkC;
    }
    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_151893B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_151894F4.s")

#ifdef NON_MATCHING
s32 func_1502DE10(u8);

void func_15189688(s32 arg0) {
    f32 temp_f0;
    f32 temp_f14_2;
    f32 temp_f14_3;
    f32 temp_f16_2;
    f32 temp_f16_3;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f18_3;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f26_3;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f28_3;
    f32 var_f30;
    s16 var_t5;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_f14;
    s32 temp_f16;
    s32 temp_t1;
    s32 temp_v0;
    s32 var_a1;
    s32 var_a3;
    s32 var_s0;
    s32 var_t0;
    u8 temp_s1;
    u8 temp_t4;
    u8 *temp_a1_2;
    u8 *temp_v1;
    u8 *var_a0;
    u8 *var_v1;

    var_s0 = D_800DF7C8[arg0];
    if (var_s0 != 0) {
        do {
            if ((*(u8 *)((u8 *)var_s0 + 4)) != 0) {
                temp_s1 = (*(u8 *)((u8 *)var_s0 + 1));
                temp_v0 = func_1502DE10((*(u8 *)((u8 *)((*(u8 **)((u8 *)var_s0 + 0x10))) + 4)));
                temp_t4 = (*(u8 *)((u8 *)var_s0 + 4));
                temp_a2 = temp_v0;
                var_f30 = (f32) temp_t4;
                temp_t1 = D_800BE9C0 * temp_v0 * temp_s1;
                if ((s32) temp_t4 < 0) {
                    var_f30 += 4294967296.0f;
                }
                var_a3 = (*(u8 *)((u8 *)var_s0 + 2)) - 1;
                if (var_a3 >= 0) {
                    var_t0 = (var_a3 * temp_v0) + temp_t1;
loop_7:
                    temp_a1 = (*(s32 *)((u8 *)var_s0 + 8));
                    var_v1 = temp_a1 + (var_t0 << 6);
                    if ((var_a3 + 1) == (*(u8 *)((u8 *)var_s0 + 2))) {
                        temp_a1_2 = (*(u8 **)((u8 *)((*(u8 **)((u8 *)var_s0 + 0x10))) + 0x1D4));
                        if (temp_a1_2 == NULL) {
                            (*(u8 *)((u8 *)var_s0 + 2)) = 0U;
                        } else {
                            var_a0 = temp_a1_2;
                            goto block_12;
                        }
                    } else {
                        var_a0 = temp_a1 + ((((var_a3 + 1) * temp_v0) + temp_t1) << 6);
block_12:
                        temp_f22 = ((f32) ((*(s16 *)((u8 *)var_v1 + 0x38)) + ((*(s16 *)((u8 *)var_v1 + 0x18)) << 0x10)) * 0.000015258789f) - ((f32) ((*(s16 *)((u8 *)var_a0 + 0x38)) + ((*(s16 *)((u8 *)var_a0 + 0x18)) << 0x10)) * 0.000015258789f);
                        temp_f26 = ((f32) ((*(s16 *)((u8 *)var_v1 + 0x3A)) + ((*(s16 *)((u8 *)var_v1 + 0x1A)) << 0x10)) * 0.000015258789f) - ((f32) ((*(s16 *)((u8 *)var_a0 + 0x3A)) + ((*(s16 *)((u8 *)var_a0 + 0x1A)) << 0x10)) * 0.000015258789f);
                        temp_f28 = ((f32) ((*(s16 *)((u8 *)var_v1 + 0x3C)) + ((*(s16 *)((u8 *)var_v1 + 0x1C)) << 0x10)) * 0.000015258789f) - ((f32) ((*(s16 *)((u8 *)var_a0 + 0x3C)) + ((*(s16 *)((u8 *)var_a0 + 0x1C)) << 0x10)) * 0.000015258789f);
                        temp_f0 = sqrtf((temp_f22 * temp_f22) + (temp_f26 * temp_f26) + (temp_f28 * temp_f28));
                        if ((var_f30 < temp_f0) && (temp_f0 != 0.0f)) {
                            temp_f22_2 = var_f30 / temp_f0;
                            if (temp_v0 > 0) {
                                var_a1 = 1;
                                var_t5 = (*(s16 *)((u8 *)var_v1 + 0x18));
                                if (temp_a2 != 1) {
                                    do {
                                        temp_f28_2 = (f32) ((*(s16 *)((u8 *)var_v1 + 0x38)) + (var_t5 << 0x10)) * 0.000015258789f;
                                        temp_f26_2 = (f32) ((*(s16 *)((u8 *)var_v1 + 0x3A)) + ((*(s16 *)((u8 *)var_v1 + 0x1A)) << 0x10)) * 0.000015258789f;
                                        temp_f16 = (*(s16 *)((u8 *)var_a0 + 0x3A)) + ((*(s16 *)((u8 *)var_a0 + 0x1A)) << 0x10);
                                        temp_f20 = (f32) ((*(s16 *)((u8 *)var_v1 + 0x3C)) + ((*(s16 *)((u8 *)var_v1 + 0x1C)) << 0x10)) * 0.000015258789f;
                                        temp_f14 = (*(s16 *)((u8 *)var_a0 + 0x3C)) + ((*(s16 *)((u8 *)var_a0 + 0x1C)) << 0x10);
                                        var_a1 += 1;
                                        (*(s16 *)((u8 *)var_v1 + 0x38)) = 0;
                                        temp_f18 = (f32) ((*(s16 *)((u8 *)var_a0 + 0x38)) + ((*(s16 *)((u8 *)var_a0 + 0x18)) << 0x10));
                                        (*(s16 *)((u8 *)var_v1 + 0x3A)) = 0;
                                        (*(s16 *)((u8 *)var_v1 + 0x3C)) = 0;
                                        var_v1 += 0x40;
                                        var_a0 += 0x40;
                                        temp_f18_2 = temp_f18 * 0.000015258789f;
                                        temp_f16_2 = (f32) temp_f16 * 0.000015258789f;
                                        temp_f14_2 = (f32) temp_f14 * 0.000015258789f;
                                        (*(s16 *)((u8 *)var_v1 + -0x26)) = (s16) (s32) (((temp_f26_2 - temp_f16_2) * temp_f22_2) + temp_f16_2);
                                        var_t5 = (*(s16 *)((u8 *)var_v1 + 0x18));
                                        (*(s16 *)((u8 *)var_v1 + -0x28)) = (s16) (s32) (((temp_f28_2 - temp_f18_2) * temp_f22_2) + temp_f18_2);
                                        (*(s16 *)((u8 *)var_v1 + -0x24)) = (s16) (s32) (((temp_f20 - temp_f14_2) * temp_f22_2) + temp_f14_2);
                                    } while (var_a1 != temp_a2);
                                }
                                temp_f28_3 = (f32) ((*(s16 *)((u8 *)var_v1 + 0x38)) + (var_t5 << 0x10)) * 0.000015258789f;
                                temp_f26_3 = (f32) ((*(s16 *)((u8 *)var_v1 + 0x3A)) + ((*(s16 *)((u8 *)var_v1 + 0x1A)) << 0x10)) * 0.000015258789f;
                                (*(s16 *)((u8 *)var_v1 + 0x38)) = 0;
                                temp_f20_2 = (f32) ((*(s16 *)((u8 *)var_v1 + 0x3C)) + ((*(s16 *)((u8 *)var_v1 + 0x1C)) << 0x10));
                                (*(s16 *)((u8 *)var_v1 + 0x3A)) = 0;
                                (*(s16 *)((u8 *)var_v1 + 0x3C)) = 0;
                                temp_v1 = var_v1 + 0x40;
                                temp_f18_3 = (f32) ((*(s16 *)((u8 *)var_a0 + 0x38)) + ((*(s16 *)((u8 *)var_a0 + 0x18)) << 0x10)) * 0.000015258789f;
                                temp_f16_3 = (f32) ((*(s16 *)((u8 *)var_a0 + 0x3A)) + ((*(s16 *)((u8 *)var_a0 + 0x1A)) << 0x10)) * 0.000015258789f;
                                temp_f14_3 = (f32) ((*(s16 *)((u8 *)var_a0 + 0x3C)) + ((*(s16 *)((u8 *)var_a0 + 0x1C)) << 0x10)) * 0.000015258789f;
                                (*(s16 *)((u8 *)temp_v1 + -0x28)) = (s16) (s32) (((temp_f28_3 - temp_f18_3) * temp_f22_2) + temp_f18_3);
                                (*(s16 *)((u8 *)temp_v1 + -0x26)) = (s16) (s32) (((temp_f26_3 - temp_f16_3) * temp_f22_2) + temp_f16_3);
                                (*(s16 *)((u8 *)temp_v1 + -0x24)) = (s16) (s32) ((((temp_f20_2 * 0.000015258789f) - temp_f14_3) * temp_f22_2) + temp_f14_3);
                            }
                        }
                        var_a3 -= 1;
                        var_t0 += -temp_v0;
                        if (var_a3 >= 0) {
                            goto loop_7;
                        }
                    }
                }
            }
            var_s0 = (*(s32 *)((u8 *)var_s0 + 0xC));
        } while (var_s0 != 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_15189688.s")
#endif
void func_15189B14(u8 *arg0) {
    func_100043B4((*(s32 **)((u8 *)arg0 + 8)), 2U);
}

void func_15189B3C(u8 *arg0) {
    func_100043B4((*(s32 **)((u8 *)arg0 + 8)), 2U);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_15189B64.s")

#ifdef NON_MATCHING
s32 func_15113D54(s32, u8 *, s32, s16, s32, s32);

s32 func_15189D14(s32 arg0, u8 *arg1, s16 arg2) {
    s32 sp44;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s4;
    u8 temp_a0;
    u8 temp_a3;

    var_s4 = arg0;
    temp_a3 = (*(u8 *)((u8 *)arg1 + 2));
    if (temp_a3 == 0) {
        return var_s4;
    }
    temp_a0 = (*(u8 *)((u8 *)arg1 + 3));
    var_s1 = temp_a0 * 0x60;
    var_s0 = 0;
    sp44 = (s32) (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg1 + 0x10))) + 0x8A));
    var_s2 = D_800BE9C0 * (*(u8 *)((u8 *)arg1 + 1));
    if ((s32) temp_a3 > 0) {
        do {
            (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg1 + 0x10))) + 0x8A)) = (u8) (var_s1 >> 8);
            temp_v0 = func_15113D54(var_s4, (*(u8 **)((u8 *)arg1 + 0x10)), (*(s32 *)((u8 *)arg1 + 8)) + (var_s2 << 6), arg2, 0, 0);
            var_s0 += 1;
            var_s1 += temp_a0 << 5;
            var_s2 += 1;
            var_s4 = temp_v0;
        } while (var_s0 != temp_a3);
    }
    (*(s8 *)((u8 *)((*(u8 **)((u8 *)arg1 + 0x10))) + 0x8A)) = (s8) sp44;
    return var_s4;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_15189D14.s")
#endif
void func_151898C0(s32 arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = *D_800DF7C8;
    if (var_v0 != 0) {
loop_1:
        if (arg0 == (*(s32 *)((u8 *)var_v0 + 0x10))) {
            (*(s32 *)((u8 *)var_v0 + 0x14)) = arg1;
            return;
        }
        var_v0 = (*(s32 *)((u8 *)var_v0 + 0xC));
        if (var_v0 == 0) {

        } else {
            goto loop_1;
        }
    }
}
