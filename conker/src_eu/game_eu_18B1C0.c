#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1515F4E4(s16 *arg0);
#endif
// hoisted forward declaration(s) for func_1515D5F8
s32 func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, u8);

void func_1515F61C(f32, s32);

f32 func_1515F578(s16 *, s32);

s32 func_1505D024();


void *func_1515D9B0(void) {
    void *sp1C = allocate_memory(0x10, 1, 2, 0);
    bzero(sp1C, 0x10);
    return sp1C;
}

u8 *func_1515D9F0(s32 arg0) {
    u8 *p;
    s32 n;
    s32 *q = &arg0; // fakematch: address-taken arg
    n = *q * 0x60;
    p = allocate_memory(n, 1, 2, 0);
    bzero(p, n);
    return p;
}

#ifdef NON_MATCHING
void func_1515D4D4(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 temp_t6;

    temp_t6 = arg3 & 0xFF;
    if (temp_t6 >= (s32) D_800DD157) {
        (*(s8 *)((u8 *)(&D_800DCD20) + 0)) = (s8) arg0;
        (*(s8 *)((u8 *)(&D_800DCD20) + 1)) = (s8) arg1;
        (*(s8 *)((u8 *)(&D_800DCD20) + 2)) = (s8) arg2;
        D_800DCD7C = 1;
        D_800DD157 = (u8) temp_t6;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515D4D4.s")
#endif
struct lnode_1515DA90 { struct lnode_1515DA90 *next; };
struct lnode_1515DA90 *func_1515DA90(void) {
    struct lnode_1515DA90 *p;
    struct lnode_1515DA90 *cur;

    p = allocate_memory(0x34, 1, 2, 2);
    if (p != NULL) {
        bzero(p, 0x34);
        if (D_800DCD78 != 0) {
            cur = (struct lnode_1515DA90 *)D_800DCD78;
            while (cur->next != NULL) {
                cur = cur->next;
            }
            cur->next = p;
        } else {
            D_800DCD78 = (s32)p;
        }
        p->next = NULL;
    }
    return p;
}


void func_1515DB1C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9) {
    func_1515D5F8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}

s32 func_1515D5F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9) {
    u8 *temp_v0;


    temp_v0 = (u8 *)func_1515DA90();
    if (temp_v0 != NULL) {
        (*(s8 *)((u8 *)temp_v0 + 4)) = 0;
        (*(s8 *)((u8 *)temp_v0 + 5)) = (s8) arg4;
        (*(s8 *)((u8 *)temp_v0 + 6)) = (s8) arg5;
        (*(s8 *)((u8 *)temp_v0 + 7)) = (s8) arg6;
        (*(s8 *)((u8 *)temp_v0 + 8)) = (s8) arg7;
        (*(s8 *)((u8 *)temp_v0 + 9)) = (s8) arg8;
        (*(u8 *)((u8 *)temp_v0 + 0xB)) = arg9;
        (*(s8 *)((u8 *)temp_v0 + 0xA)) = 0;
        (*(s16 *)((u8 *)temp_v0 + 0xE)) = (s16) arg0;
        (*(s16 *)((u8 *)temp_v0 + 0x10)) = (s16) arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x12)) = (s16) arg2;
        (*(s8 *)((u8 *)temp_v0 + 0x2F)) = (s8) arg3;
        (*(s8 *)((u8 *)temp_v0 + 0x2C)) = 0x7F;
        (*(s8 *)((u8 *)temp_v0 + 0x2D)) = 0;
        (*(s8 *)((u8 *)temp_v0 + 0x2E)) = 0;
    }
    return (s32) temp_v0;
}

void func_1515DC0C(void) {
    u8 *var_v0 = (u8 *)D_800DCD78;
    while (var_v0 != NULL) {
        var_v0[0xC] = 0;
        var_v0[0x30] = 0;
        var_v0 = *(u8 **)var_v0;
    }
}

void func_1515DC38(void) {
}

#ifdef NON_MATCHING
extern s32 D_800DD140;

/* Per-player view setup: no lights, lighting on, then func_1515F4E4 turns the player's current viewport
 * (D_800BE628 + player * 0x180 + 0x100 + frame * 0x40) into the s15.16 values D_800DD140[0..3], which are
 * loaded with the custom G_MOVEWORD index 0x10: integer halves at offsets 0x00..0x0C, fractions at 0x10..0x1C,
 * then 0x20..0x2C. */
Gfx *func_1515DC40(Gfx *gdl, s32 player) {
    s32 *m = &D_800DD140;

    gdl->words.w0 = 0xDB020000; /* G_MOVEWORD G_MW_NUMLIGHT: 0 */
    gdl->words.w1 = 0;
    gdl++;
    gSPSetGeometryMode(gdl++, G_LIGHTING);
    func_1515F4E4((s16 *)(D_800BE628 + player * 0x180 + D_800BE9C0 * 0x40 + 0x100));

    gdl->words.w0 = 0xDB100000;
    gdl->words.w1 = ((m[0] >> 16) << 16) | ((m[1] >> 16) & 0xFFFF);
    gdl++;
    gdl->words.w0 = 0xDB100008;
    gdl->words.w1 = ((m[0] >> 16) << 16) | ((m[1] >> 16) & 0xFFFF);
    gdl++;
    gdl->words.w0 = 0xDB100004;
    gdl->words.w1 = (m[2] >> 16) << 16;
    gdl++;
    gdl->words.w0 = 0xDB10000C;
    gdl->words.w1 = (m[2] >> 16) << 16;
    gdl++;
    gdl->words.w0 = 0xDB100010;
    gdl->words.w1 = (m[0] << 16) | (m[1] & 0xFFFF);
    gdl++;
    gdl->words.w0 = 0xDB100018;
    gdl->words.w1 = (m[0] << 16) | (m[1] & 0xFFFF);
    gdl++;
    gdl->words.w0 = 0xDB100014;
    gdl->words.w1 = m[2] << 16;
    gdl++;
    gdl->words.w0 = 0xDB10001C;
    gdl->words.w1 = m[2] << 16;
    gdl++;
    gdl->words.w0 = 0xDB100020;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xDB100024;
    gdl->words.w1 = m[3] << 16;
    gdl++;
    gdl->words.w0 = 0xDB100028;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xDB10002C;
    gdl->words.w1 = m[3] << 16;
    gdl++;
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515DC40.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515DE84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515E7E8.s")

u8 *func_1515F0F4(s32, s32, s32, s32, u8 **);

void func_1515E9AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4, u8 *arg5, u8 *arg6, u8 *arg7) {
    u8 *p;

    p = func_1515F0F4(arg0, arg1, arg2, 0, (u8 **)D_800DCD84);
    if (p != NULL) {
        arg4[0] = (*(u32 *)(p + 0x18)) & 0xFF;
        arg4[1] = (*(u32 *)(p + 0x18) >> 8) & 0xFF;
        arg4[2] = (*(u32 *)(p + 0x18) >> 16) & 0xFF;
        arg5[0] = (*(u32 *)(p + 0x1C)) & 0xFF;
        arg5[1] = (*(u32 *)(p + 0x1C) >> 8) & 0xFF;
        arg5[2] = (*(u32 *)(p + 0x1C) >> 16) & 0xFF;
        *arg6 = (*(u32 *)(p + 0x1C) >> 24) & 0xFF;
        *arg7 = (*(u32 *)(p + 0x18) >> 24) & 0xFF;
    } else {
        arg4[0] = ((u8 *)D_800DCD24)[0];
        arg4[1] = ((u8 *)D_800DCD24)[1];
        arg4[2] = ((u8 *)D_800DCD24)[2];
        arg5[0] = D_800DCD28[0];
        arg5[1] = D_800DCD28[1];
        arg5[2] = D_800DCD28[2];
        *arg6 = D_800DCD3C;
        *arg7 = D_800DCD3D;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515EAB4.s")

#ifdef NON_MATCHING
s32 func_1515E7E8(s32, s32, s32, s32, u8 *, s32, s32);
extern u8 D_800DA241;
extern u8 *D_800DA248;

void func_1515EDF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5, s32 arg6, s32 arg7) {
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f6;
    f32 var_f10;
    f32 var_f10_2;
    f32 var_f10_3;
    f32 var_f16;
    f32 var_f4;
    f32 var_f6;
    f32 var_f6_2;
    f32 var_f8;
    s32 temp_a1;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    u8 temp_t0;
    u8 temp_t5;
    u8 temp_t6;
    u8 temp_t7;
    u8 temp_t8;
    u8 temp_t8_2;
    u8 temp_t9;
    u8 **var_a0;
    u8 *temp_v0;

    func_1515E7E8(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    temp_t8 = (*(u8 *)((u8 *)arg5 + 0));
    var_f6 = (f32) temp_t8;
    if ((s32) temp_t8 < 0) {
        var_f6 += 4294967296.0f;
    }
    sp50 = var_f6;
    temp_t9 = (*(u8 *)((u8 *)arg5 + 1));
    var_f4 = (f32) temp_t9;
    if ((s32) temp_t9 < 0) {
        var_f4 += 4294967296.0f;
    }
    sp54 = var_f4;
    temp_t0 = (*(u8 *)((u8 *)arg5 + 2));
    var_f10 = (f32) temp_t0;
    if ((s32) temp_t0 < 0) {
        var_f10 += 4294967296.0f;
    }
    sp58 = var_f10;
    var_v1 = 0;
    temp_a1 = (D_800DA241 & 0x7F) - 1;
    if (temp_a1 > 0) {
        var_a0 = &D_800DA248;
        do {
            temp_v0 = *var_a0;
            var_v1 += 1;
            if (temp_v0 != NULL) {
                sp5C = (f32) (*(s16 *)((u8 *)temp_v0 + 0xE));
                sp60 = (f32) (*(s16 *)((u8 *)temp_v0 + 0x10));
                temp_f6 = (f32) (*(s16 *)((u8 *)temp_v0 + 0x12));
                sp64 = temp_f6;
                temp_t5 = (*(u8 *)((u8 *)temp_v0 + 0x2F));
                var_f10_2 = (f32) temp_t5;
                if ((s32) temp_t5 < 0) {
                    var_f10_2 += 4294967296.0f;
                }
                temp_f2 = temp_f6 - (f32) arg3;
                temp_f12 = sp5C - (f32) arg1;
                temp_f14 = sp60 - (f32) arg2;
                var_f16 = (var_f10_2 * 2048.0f) / ((temp_f2 * temp_f2) + ((temp_f12 * temp_f12) + (temp_f14 * temp_f14)));
                if (var_f16 > 1.0f) {
                    var_f16 = 1.0f;
                }
                temp_t6 = (*(u8 *)((u8 *)temp_v0 + 5));
                var_f10_3 = (f32) temp_t6;
                if ((s32) temp_t6 < 0) {
                    var_f10_3 += 4294967296.0f;
                }
                sp50 += var_f16 * var_f10_3;
                temp_t7 = (*(u8 *)((u8 *)temp_v0 + 6));
                var_f8 = (f32) temp_t7;
                if ((s32) temp_t7 < 0) {
                    var_f8 += 4294967296.0f;
                }
                sp54 += var_f16 * var_f8;
                temp_t8_2 = (*(u8 *)((u8 *)temp_v0 + 7));
                var_f6_2 = (f32) temp_t8_2;
                if ((s32) temp_t8_2 < 0) {
                    var_f6_2 += 4294967296.0f;
                }
                sp58 += var_f16 * var_f6_2;
            }
            var_a0 = (u8 * *)((u8 *)var_a0 + (4));
        } while (var_v1 != temp_a1);
    }
    var_v0 = (s32) sp50;
    if (var_v0 >= 0x100) {
        var_v0 = 0xFF;
    }
    (*(u8 *)((u8 *)arg5 + 0)) = (u8) var_v0;
    var_v0_2 = (s32) sp54;
    if (var_v0_2 >= 0x100) {
        var_v0_2 = 0xFF;
    }
    (*(u8 *)((u8 *)arg5 + 1)) = (u8) var_v0_2;
    var_v0_3 = (s32) sp58;
    if (var_v0_3 >= 0x100) {
        var_v0_3 = 0xFF;
    }
    (*(u8 *)((u8 *)arg5 + 2)) = (u8) var_v0_3;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515EDF8.s")
#endif
u8 *func_1515F0F4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 **arg4) {
    struct127 sp;
    s32 pad[2]; // 8 bytes below the struct (frame 0x360)
    u8 *p;

    sp.x_position = sp.old_x_position = arg0;
    sp.unk180 = sp.y_position = sp.old_y_position = arg1;
    sp.z_position = sp.old_z_position = arg2;
    for (; arg4 != NULL; arg4 = (u8 **)arg4[0]) {
        p = arg4[1];
        if (p[0x14] != 0) {
            continue;
        }
        if (arg3 != 0 && !((*(u32 *)(p + 0x18) >> 24) & arg3)) {
            continue;
        }
        if ((p[0x15] >> 2) != 0x18 && (*(u32 *)(p + 0x18) >> 31) != 0) {
            continue;
        }
        if (func_150A2280(&sp, p, 0) != 0) {
            continue;
        }
        return arg4[1];
    }
    return NULL;
}

#ifdef NON_MATCHING
extern s32 D_800DA030;

void func_1515F1E8(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    struct {
        s32 u48;
        s32 u4C;
        s32 u50;
        s32 u54;
        s32 u58;
        s32 u5C;
        u8 pad60[0x10];
        f32 u70;
        f32 u74;
        f32 u78;
    } sp;
    s32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 temp_f0;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f4;
    f32 temp_f8;
    f32 var_f12;
    f32 var_f14;
    f32 var_f2;
    s16 temp_t6;
    s16 var_t9;
    s32 *var_a2;
    s32 *var_v1;
    s32 temp_f8_2;
    s32 temp_v0;
    s32 temp_v1;
    u8 temp_t0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *var_a0;
    u8 *var_a1;
    u8 *var_v0;

    temp_t6 = (*(s16 *)((u8 *)arg0 + 0xE));
    sp.u48 = (s32) temp_t6;
    if (temp_t6 != -0x8000) {
        sp.u4C = (s32) (*(s16 *)((u8 *)arg0 + 0x10));
        var_t9 = (*(s16 *)((u8 *)arg0 + 0x12));
    } else {
        temp_v0 = ((*(s16 *)((u8 *)arg0 + 0x12)) & 0xFFFF) | ((*(s16 *)((u8 *)arg0 + 0x10)) << 0x10);
        sp.u48 = (s32) (*(f32 *)((u8 *)temp_v0 + 0));
        sp.u4C = (s32) (*(f32 *)((u8 *)temp_v0 + 4));
        var_t9 = (s16) (s32) (*(f32 *)((u8 *)temp_v0 + 8));
    }
    sp.u50 = (s32) var_t9;
    if (arg6 & 2) {
        temp_f18 = (f32) (sp.u48 - arg3);
        temp_f4 = (f32) (sp.u4C - arg4);
        sp3C = temp_f4;
        temp_f8 = (f32) (sp.u50 - arg5);
        sp38 = temp_f8;
        temp_f0 = sqrtf((temp_f18 * temp_f18) + (temp_f4 * temp_f4) + (temp_f8 * temp_f8));
        if (temp_f0 != 0.0f) {
            temp_f16 = 127.0f / temp_f0;
            var_f2 = temp_f18 * temp_f16;
            var_f12 = temp_f4 * temp_f16;
            var_f14 = temp_f8 * temp_f16;
        } else {
            var_f14 = 0.0f;
            var_f2 = 127.0f;
            var_f12 = 0.0f;
        }
        sp.u54 = (s32) var_f2;
        sp.u58 = (s32) var_f12;
        sp.u5C = (s32) var_f14;
    } else {
        sp.u54 = 0;
        sp.u58 = 0;
        sp.u5C = 0x7F;
    }
    temp_v1 = 1 << arg1;
    if ((*(u8 *)((u8 *)arg0 + 0x30)) & temp_v1) {
        temp_v0_2 = arg0 + (arg1 * 6);
        sp.u48 = (s32) (*(s16 *)((u8 *)temp_v0_2 + 0x14));
        sp.u4C = (s32) (*(s16 *)((u8 *)temp_v0_2 + 0x16));
        sp.u50 = (s32) (*(s16 *)((u8 *)temp_v0_2 + 0x18));
    } else {
        sp40 = temp_v1;
        func_150A7E40(((s32 *)((u8 *)&D_800DA030 + (arg1 << 6))), (f32) sp.u48, (f32) sp.u4C, (f32) sp.u50, &sp.u70, &sp.u74, &sp.u78);
        temp_f8_2 = (s32) sp.u70;
        temp_v0_3 = arg0 + (arg1 * 6);
        sp.u48 = temp_f8_2;
        sp.u4C = (s32) sp.u74;
        sp.u50 = (s32) sp.u78;
        (*(s16 *)((u8 *)temp_v0_3 + 0x14)) = (s16) temp_f8_2;
        (*(s16 *)((u8 *)temp_v0_3 + 0x16)) = (s16) sp.u4C;
        (*(s16 *)((u8 *)temp_v0_3 + 0x18)) = (s16) sp.u50;
        (*(u8 *)((u8 *)arg0 + 0x30)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x30)) | sp40);
    }
    var_a1 = arg2;
    var_a0 = arg0;
    var_a2 = &sp.u54;
    var_v1 = &sp.u48;
    var_v0 = var_a1;
    do {
        var_v1 = (s32 *)((u8 *)var_v1 + (4));
        var_v0 += 1;
        (*(u8 *)((u8 *)var_v0 + -1)) = (u8) (*(u8 *)((u8 *)var_a0 + 5));
        temp_t0 = (*(u8 *)((u8 *)var_a0 + 5));
        var_a0 += 1;
        var_a2 = (s32 *)((u8 *)var_a2 + (4));
        (*(u8 *)((u8 *)var_v0 + 3)) = temp_t0;
        var_a1 += 2;
        (*(s8 *)((u8 *)var_v0 + 7)) = (s8) (*(s32 *)((u8 *)var_a2 + -4));
        (*(s16 *)((u8 *)var_a1 + 0x1E)) = (s16) (*(s32 *)((u8 *)var_v1 + -4));
        (*(s16 *)((u8 *)var_a1 + 0x26)) = (s16) (*(s32 *)((u8 *)var_v1 + -4));
    } while (var_v1 != &sp.u54);
    (*(u8 *)((u8 *)arg2 + 0xC)) = (u8) (*(u8 *)((u8 *)arg0 + 0x2F));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515F1E8.s")
#endif
void func_1515F5B0(f32, s32);

void func_1515F4E4(s16 *arg0) {
    func_1515F5B0(1.0f / func_1515F578(arg0, 0), 0);
    func_1515F5B0(1.0f / func_1515F578(arg0, 5), 1);
    func_1515F5B0(1.0f / func_1515F578(arg0, 0xA), 2);
    func_1515F61C(-func_1515F578(arg0, 0xE), 3);
}

f32 func_1515F578(s16 *arg0, s32 arg1) {
    s32 v = arg0[arg1];
    v = (u16)arg0[arg1 + 0x10] | (v << 16);
    return v * (1.0f / 65536.0f);
}

extern s32 D_800DD140;
void func_1515F5B0(f32 arg0, s32 arg1) {
    if (arg0 >= 32767.0f) {
        arg0 = 32767.0f;
    } else if (arg0 < -32768.0f) {
        arg0 = -32768.0f;
    }
    arg0 *= 65536.0f;
    *(s32 *)((u8 *)&D_800DD140 + (arg1 * 4)) = (s32) arg0;
}

extern s32 D_800DD140;
void func_1515F61C(f32 arg0, s32 arg1) {
    if (arg0 >= 32767.0f) {
        arg0 = 32767.0f;
    } else if (arg0 < -32768.0f) {
        arg0 = -32768.0f;
    }
    *(s32 *)((u8 *)&D_800DD140 + (arg1 * 4)) = (s32) arg0;
}

void func_1515F10C(s32 **arg0) {
    s32 **prev = NULL;
    s32 **cur = (s32 **)D_800DCD78;

    while (cur != arg0) {
        prev = cur;
        cur = (s32 **)*cur;
    }
    if (prev != NULL) {
        *prev = *cur;
    } else {
        D_800DCD78 = (s32)*cur;
    }
    func_10004074(cur);
}

void func_1515F170(s32 arg0, u8 arg1) {
    u8 *var_v0 = (u8 *)D_800DCD78;
    while (var_v0 != NULL) {
        if (arg0 == var_v0[0xB]) {
            var_v0[9] = arg1;
        }
        var_v0 = *(u8 **)var_v0;
    }
}

u8 *func_1515F1B0(struct_eu_15144598 *arg0) {
    s32 var_v1;
    s32 temp_v0;
    s32 sp2C;

    temp_v0 = func_10003C6C(0x10, 1, 2, 0, 1);
    var_v1 = temp_v0;
    if (temp_v0 == 0) {
        return NULL;
    }
    (*(struct_eu_15144598 **)temp_v0) = arg0;
    if (arg0 != NULL) {
        sp2C = var_v1;
        (*(f32 *)((u8 *)var_v1 + 4)) = func_1514462C(arg0);
    } else {
        (*(f32 *)((u8 *)temp_v0 + 4)) = 0.0f;
    }
    if (arg0 != NULL) {
        sp2C = var_v1;
        (*(f32 *)((u8 *)var_v1 + 8)) = func_15144598(arg0);
    } else {
        (*(f32 *)((u8 *)var_v1 + 8)) = 0.0f;
    }
    (*(s32 *)((u8 *)var_v1 + 0xC)) = 0;
    return (u8 *) var_v1;
}

void func_1515F25C(s32 *arg0, s32 *arg1) {
    arg1[3] = *arg0;
    *arg0 = (s32)arg1;
}

void func_1515F7E0(void *arg0, u8 *arg1) {
    s32 idx = *(s32 *)(arg1 + 0x18);
    if ((idx >= 0) && (idx < 12)) {
        void (*fp)(void *, void *) = D_8008B430[idx];
        if (fp != NULL) {
            fp(arg0, arg1);
        }
    }
}

void func_1515F828(u8 *arg0, s32 arg1) {
    func_1505D024(arg0, 0x6001D, *(u16 *)(arg0 + 0x7A), -1);
}

extern void (*D_8008B460[])(u8 *, u8 *);
void func_1515F858(u8 *arg0, u8 *arg1) {
    s32 v;

    if (arg0[0x3B] == 1) {
        v = *(s32 *)(arg1 + 0x1C);
        if ((v >= 0) && (v < 3)) {
            D_8008B460[v](arg0, arg1);
        }
    }
}

void func_1515F8A8(s32 arg0, s32 arg1) {
    u8 var_t0;
    u8 var_t1;
    u8 var_v1;

    var_v1 = (*(u8 *)((u8 *)(&D_800DCD20) + 0));
    var_t0 = (*(u8 *)((u8 *)(&D_800DCD20) + 1));
    var_t1 = (*(u8 *)((u8 *)(&D_800DCD20) + 2));
    if (D_800DCD94 != 97.0f) {
        D_800DCD94 += (97.0f - D_800DCD94) * 0.5f;
        var_v1 = D_800DCD94;
    }
    if (D_800DCD98 != 96.0f) {
        D_800DCD98 += (96.0f - D_800DCD98) * 0.5f;
        var_t0 = D_800DCD98;
    }
    if (D_800DCD9C != 98.0f) {
        D_800DCD9C += (98.0f - D_800DCD9C) * 0.5f;
        var_t1 = D_800DCD9C;
    }
    func_1515D4D4(var_v1, var_t0, var_t1, 0);
}

void func_1515FB34(s32 arg0, s32 arg1) {
    u8 var_t0;
    u8 var_t1;
    u8 var_v1;

    var_v1 = (*(u8 *)((u8 *)(&D_800DCD20) + 0));
    var_t0 = (*(u8 *)((u8 *)(&D_800DCD20) + 1));
    var_t1 = (*(u8 *)((u8 *)(&D_800DCD20) + 2));
    if (D_800DCD94 != 229.0f) {
        D_800DCD94 += (229.0f - D_800DCD94) * 0.5f;
        var_v1 = D_800DCD94;
    }
    if (D_800DCD98 != 253.0f) {
        D_800DCD98 += (253.0f - D_800DCD98) * 0.5f;
        var_t0 = D_800DCD98;
    }
    if (D_800DCD9C != 160.0f) {
        D_800DCD9C += (160.0f - D_800DCD9C) * 0.5f;
        var_t1 = D_800DCD9C;
    }
    func_1515D4D4(var_v1, var_t0, var_t1, 0);
}
