#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
u8 *func_15140410(u8 *arg0, u8 *arg1, u8 *arg2, s16 arg3);
Gfx *func_1513F4E4(Gfx *arg0, u8 arg1, u8 *arg2);
extern u8 D_800A4EA8[];
#endif

// copies the colours of 4 vertices
typedef struct {
    s16 c[4];
    u16 flag;
} struct_eu_vtxcol;

void func_1513FFF4(Vtx *arg0, u8 arg1, u8 arg2);
void func_151400D0(Vtx *arg0, struct_eu_vtxcol *arg1);
s32 func_1515D9B0(void);
s32 func_1515D9F0(s32);


#ifdef NON_MATCHING
extern s32 (*D_8008A010[])(u8 *);
extern s32 (*D_8008A048[])(u8 *);
/* Per-frame update of a sprite effect (struct210): +0x10 bit 0 active; +0x18 flags; +0x1C life (s16, counts down
 * by D_800BE9E4 when flags & 1); +0x80 / +0x81 update / end handler index (D_8008A010 / D_8008A048, 0 = none);
 * +0x3A fade start, +0x3C fade rate: alpha +0x28 (flags & 0x8000) or +0x2D (flags & 0x10000) follows life * rate;
 * +0x20 frame position (16.16) advanced by speed +0x24, wrapped at the frame count of texture +0x1E
 * (D_80090F10 entry byte 4): flags 2 / 8 end at the top / bottom, 0x40 / 0x80 clamp, 4 ping-pong, else wrap.
 * When the effect ends, the end handler may veto the removal (func_1516972C). */
void func_1513C060(u8 *p) {
    s8 done;
    s32 flags;
    s32 life;
    s32 a;
    s32 speed;
    s32 pos;
    s32 top;

    if (!(*(s32 *)(p + 0x10) & 1)) {
        return;
    }
    done = 0;
    if (*(s32 *)(p + 0x18) & 1) {
        *(s16 *)(p + 0x1C) -= D_800BE9E4;
        if (*(s16 *)(p + 0x1C) < 0) {
            done = 1;
        }
    }
    if ((p[0x80] != 0) && (D_8008A010[p[0x80]](p) == 0)) {
        done = 1;
    }
    flags = *(s32 *)(p + 0x18);
    if ((flags & 0x8000) && !done) {
        life = *(s16 *)(p + 0x1C);
        if (life < *(s16 *)(p + 0x3A)) {
            a = life * *(s16 *)(p + 0x3C);
            if (a < p[0x28]) {
                p[0x28] = a;
            }
        }
    }
    flags = *(s32 *)(p + 0x18);
    if ((flags & 0x10000) && !done) {
        life = *(s16 *)(p + 0x1C);
        if (life < *(s16 *)(p + 0x3A)) {
            a = life * *(s16 *)(p + 0x3C);
            if (a < p[0x28]) {
                p[0x2D] = a;
            }
        }
    }
    if (!done && ((speed = *(s32 *)(p + 0x24)) != 0)) {
        pos = *(s32 *)(p + 0x20) + speed * D_800BE9E4;
        *(s32 *)(p + 0x20) = pos;
        top = (D_80090F14[p[0x1E]][0] << 16) - 1;
        if (top < pos) {
            flags = *(s32 *)(p + 0x18);
            if (flags & 2) {
                done = 1;
            } else if (flags & 0x40) {
                *(s32 *)(p + 0x24) = 0;
                *(s32 *)(p + 0x20) = top;
            } else if (flags & 4) {
                *(s32 *)(p + 0x20) = top - pos % top;
                *(s32 *)(p + 0x24) = -speed;
            } else {
                do {
                    pos -= top;
                    *(s32 *)(p + 0x20) = pos;
                } while (top < pos);
            }
        } else if (pos < 0) {
            flags = *(s32 *)(p + 0x18);
            if (flags & 8) {
                done = 1;
            } else if (flags & 0x80) {
                *(s32 *)(p + 0x24) = 0;
                *(s32 *)(p + 0x20) = 0;
            } else if (flags & 4) {
                *(s32 *)(p + 0x20) = -pos % top;
                *(s32 *)(p + 0x24) = -speed;
            } else {
                do {
                    pos += top;
                    *(s32 *)(p + 0x20) = pos;
                } while (pos < 0);
            }
        }
    }
    if (done) {
        if ((p[0x81] == 0) || (D_8008A048[p[0x81]](p) != 0)) {
            func_1516972C((struct102 *)p);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513C060.s")
#endif

struct210 *func_1513C350(struct210 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, struct167 *arg7, s32 arg8, u8 arg9, s32 argA) {
    struct210 *temp_v0;
    u8 phi_v0;
    s32 i;

    if (arg1 == 0) {
        arg1 = (s32)&D_800A4AA0;
    }
    if (arg0->unk0 & 0x40000) {
        phi_v0 = 0x4A;
    } else {
        phi_v0 = 0x1B;
    }
    temp_v0 = func_15167A68(phi_v0, argA, arg8 + 0xB0, 1, arg9, 1);
    if (temp_v0 == 0) {
        return NULL;
    }
    memcpy(&temp_v0->unk18.i.unk0, arg0, 0x28); // memcpy
    func_1513FFF4((Vtx *)&temp_v0->unk40, temp_v0->unk1E, arg4);
    func_151400D0((Vtx *)&temp_v0->unk40, (struct_eu_vtxcol *)arg1);
    temp_v0->unk80 = arg2;
    temp_v0->unk81 = arg3;
    temp_v0->unk84 = arg5;
    temp_v0->unk10 = 1;
    temp_v0->unk14 = 0;
    temp_v0->unkA0 = arg6;
    for (i = 0; i < 4; i++) {
        temp_v0->unk8C[i] = 0;
    }

    temp_v0->unk9C = 0;
    if (arg5) {
        for (i = 0; i <= D_80082FA0; i++) {
            temp_v0->unk8C[i] = func_1515D9F0(arg5);
        }
        temp_v0->unk9C = func_1515D9B0();
    }
    if (arg7) {
        *(struct167 *)temp_v0->unkA4 = *arg7;
    }
    return temp_v0;
}

struct210 *func_1513C4EC(s32 arg0, s32 arg1, u8 arg2, u8 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF) {
    s32 temp_v0;
    struct17 tmp;

    tmp.unk0 = arg4;
    tmp.unk4 = arg5;
    tmp.unk8 = arg6;
    temp_v0 = func_1513C350(arg0, arg1, arg2, arg3, argA, argB, argC, &tmp, argD, argE, argF);
    if (temp_v0 == 0) {
        return 0;
    }
    func_1513E13C(temp_v0, arg4, arg5, arg6, arg7, arg8, arg9);
    return temp_v0;
}

struct210 *func_1513C5B0(s32 arg0, s32 arg1, u8 arg2, u8 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD) {
    s32 tmp = func_1513C350(arg0, arg1, arg2, arg3, argA, 0, 0, 0, argB, argC, argD);
    if (tmp == 0) {
        return 0;
    }
    func_1513E13C(tmp, arg4, arg5, arg6, arg7, arg8, arg9);
    return tmp;
}

struct210 *func_1513C650(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF) {
    s32 temp_v0;
    struct17 tmp;

    tmp.unk0 = arg4;
    tmp.unk4 = arg5;
    tmp.unk8 = arg6;

    temp_v0 = func_1513C350(arg0, 0, arg1, arg2, argA, argB, argC, &tmp, argD, argE, argF);
    if (temp_v0 == 0) {
        return 0;
    }

    if (func_1513E2AC(temp_v0, 0, arg3, arg4, arg5, arg6, arg7, arg8, arg9) == 0) {
        func_1516972C(temp_v0);
        return 0;
    }
    return temp_v0;
}

struct210 *func_1513C73C(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD) {
    s32 tmp = func_1513C350(arg0, 0, arg1, arg2, argA, 0, 0, 0, argB, argC, argD);
    if (tmp == 0) {
        return 0;
    }

    if (func_1513E2AC(tmp, 0, arg3, arg4, arg5, arg6, arg7, arg8, arg9) == 0) {
        func_1516972C(tmp);
        return 0;
    }
    return tmp;
}

struct210 *func_1513C804(s32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u8 argA, u8 argB, s32 argC, u8 argD, s32 argE) {
    s32 tmp = func_1513C350(arg0, 0, arg2, arg3, argB, 0, 0, 0, argC, argD, argE);
    if (tmp == 0) {
        return 0;
    }
    if (func_1513E2AC(tmp, 0, arg4, arg5, arg6, arg7, arg8, arg9, argA) == 0) {
        func_1516972C(tmp);
        return 0;
    }
    return tmp;
}

void func_1513C8D4(struct210 *arg0) {
    func_1513C92C(arg0);
    func_15169804(arg0);
}

void func_1513C900(struct210 *arg0) {
    func_1513C92C(arg0);
    func_15169824(arg0);
}

void func_1513C92C(struct210 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (arg0->unk8C[i]) {
            func_100043B4(arg0->unk8C[i], 4);
        }
    }
    if (arg0->unk9C != 0) {
        func_100043B4(arg0->unk9C, 4);
    }
}

void func_1513C9B0(struct210 *arg0) {
    s32 idx;
    if ((arg0->unk18.i.unk0 & 0x1000) != 0) {
        idx = arg0->unk1F;
    } else {
        idx = 0;
    }
    /* P82: the asm leaves arg0 in a0 and every handler takes the struct210 (arity scan row, dropped argument) */
    ((void (*)(struct210 *))D_80089EE8[idx])(arg0);
}

void func_1513C9FC(struct210 *arg0) {
    s32 idx;
    if ((arg0->unk18.i.unk0 & 0x1000) != 0) {
        idx = arg0->unk1F;
    } else {
        idx = 0;
    }
    /* P82: the asm leaves arg0 in a0 and every handler takes the struct210 (arity scan row, dropped argument) */
    ((void (*)(struct210 *))D_80089EF0[idx])(arg0);
}

void func_1513CA48(struct210 *arg0) {
    func_151D5E30(&arg0->unk100);
}

void func_1513CA6C(struct210 *arg0) {
    func_1513CA48(arg0);
    func_1513CAD4(arg0);
    func_15169804(arg0);
}

void func_1513CAA0(struct210 *arg0) {
    func_1513CA48(arg0);
    func_1513CAD4(arg0);
    func_15169824(arg0);
}

void func_1513CAD4(struct210 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (arg0->unkA4[i]) {
            func_100043B4(arg0->unkA4[i], 4);
        }
    }
    if (arg0->unkB4 != 0) {
        func_100043B4(arg0->unkB4, 4);
    }
}

// is this really struct210?
void func_1513CB58(struct210 *arg0) {
    s32 idx;
    if ((arg0->unk58 & 0x400000) != 0) {
        idx = arg0->unk18.b.unk1; //unk19;
    } else {
        idx = 0;
    }
    /* P82: the asm leaves arg0 in a0 and every handler takes the struct210 (arity scan row, dropped argument) */
    ((void (*)(struct210 *))D_80089EF8[idx])(arg0);
}

void func_1513CBA4(struct210 *arg0) {
    s32 idx;
    if ((arg0->unk58 & 0x400000) != 0) {
        idx = arg0->unk18.b.unk1; //unk19;
    } else {
        idx = 0;
    }
    /* P82: the asm leaves arg0 in a0 and every handler takes the struct210 (arity scan row, dropped argument) */
    ((void (*)(struct210 *))D_80089F2C[idx])(arg0);
}

#ifdef NON_MATCHING
Gfx *func_15142B7C(Gfx *gfx, s32 set, s32 clear);
Gfx *func_15142C10(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5);
Gfx *func_15142CF0(s32, s32, s32, s16, s32, s32, s32, u8 *);
s32 func_15142E24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *arg9, s32 argA);
u8 *func_15142FBC(Gfx *, s32, s32, u8 *);
void func_151441A4(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
void func_151442FC(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
s32 func_151462C8(u8 *, u8 *, s32, s32, s32, s32, u8 *, s32, s32);
extern s32 D_800D30BC;

u8 *func_1513CBF0(u8 *arg0, u8 *arg1, s16 arg2) {
    struct {
        s16 u60;
        s16 u62;
        s16 u64;
        s16 u66;
        s16 u68;
        s16 u6A;
        s16 u6C;
        s16 u6E;
        u8 pad70[0x6];
        s16 u76;
        u8 pad78[0x1];
        u8 u79;
        u8 u7A;
        u8 u7B;
    } sp;
    Gfx *temp_a0;
    s32 temp_s1;
    s32 temp_t7;
    s32 temp_v0;
    s32 var_s1_2;
    s32 var_v0;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v1;
    u8 temp_v1;
    u8 var_v0_2;
    u8 var_v0_3;
    u8 *temp_v0_2;
    u8 *temp_v1_2;
    u8 *var_s1;

    var_s1 = arg0;
    if ((*(s32 *)((u8 *)arg1 + 0x10)) & 1) {
        if (((*(s32 *)((u8 *)arg1 + 0x18)) & 0x2000) && !((*(u8 *)((u8 *)arg1 + 0x38)) & (1 << arg2))) {

        } else {
            sp.u7B = 1;
            temp_t7 = (*(s32 *)((u8 *)arg1 + 0x30));
            sp.u79 = (u8) ((u32) (temp_t7 & 0xFFFF0000) >> 0x10);
            sp.u7A = (u8) temp_t7;
            temp_v0 = (*(s32 *)((u8 *)arg1 + 0x18));
            sp.u76 = temp_v0 & 0x30;
            if (temp_v0 & 0x4000) {
                var_v0 = (*(s32 *)((u8 *)arg1 + 0x34));
            } else {
                var_v0 = 0;
            }
            temp_s1 = func_151462C8(var_s1, arg1 + 0x84, 0, 0, 0, (s32) arg2, arg1 + 0xA4, 2, var_v0);
            if ((*(s32 *)((u8 *)arg1 + 0x18)) & 0x100) {
                var_v0_2 = (*(u8 *)((u8 *)arg1 + 0x2E));
            } else {
                var_v0_2 = 3;
            }
            func_151441A4(&sp.u6E, &sp.u6C, &sp.u6A, &sp.u68, (s32) (*(u8 *)((u8 *)arg1 + 0x2A)), (s32) (*(u8 *)((u8 *)arg1 + 0x2B)), (s32) (*(u8 *)((u8 *)arg1 + 0x2C)), (s32) (*(u8 *)((u8 *)arg1 + 0x2D)), 0xFF, 0xFF, 0xFF, (s32) (*(u8 *)((u8 *)arg1 + 0x28)), (s32) (*(u8 *)((u8 *)arg1 + 0x29)), (s32) var_v0_2);
            if ((*(s32 *)((u8 *)arg1 + 0x18)) & 0x200) {
                var_v0_3 = (*(u8 *)((u8 *)arg1 + 0x2F));
            } else {
                var_v0_3 = 4;
            }
            func_151442FC(&sp.u66, &sp.u64, &sp.u62, &sp.u60, (s32) (*(u8 *)((u8 *)arg1 + 0x2A)), (s32) (*(u8 *)((u8 *)arg1 + 0x2B)), (s32) (*(u8 *)((u8 *)arg1 + 0x2C)), (s32) (*(u8 *)((u8 *)arg1 + 0x2D)), 0xFF, 0xFF, 0xFF, (s32) (*(u8 *)((u8 *)arg1 + 0x28)), (s32) (*(u8 *)((u8 *)arg1 + 0x29)), (s32) var_v0_3);
            var_v1 = 0;
            if (sp.u76 & 0x10) {
                var_v1 = 0x200;
            }
            if (sp.u76 & 0x20) {
                var_v1 |= 0x400;
            }
            if ((*(s32 *)((u8 *)arg1 + 0x18)) & 0x400) {
                var_v0_4 = 0x20000;
            } else {
                var_v0_4 = 0;
            }
            temp_v1 = (*(u8 *)((u8 *)arg1 + 0x1E));
            var_s1_2 = func_15142B7C(temp_s1, var_v0_4 | var_v1 | 1, 0x600);
            if (temp_v1 != 0xFF) {
                if ((*(s32 *)((u8 *)arg1 + 0x18)) & 0x20000) {
                    var_v0_5 = 0x3E;
                } else {
                    var_v0_5 = 3;
                }
                var_s1_2 = func_15142E24(var_s1_2, &D_80090F10[temp_v1], (*(s32 *)((u8 *)arg1 + 0x20)), 2, 0, 0, (s32) temp_v1, 0, 0, &sp.u7B, var_v0_5);
            }
            temp_a0 = func_1513F4E4(func_15142CF0(func_15142C10(var_s1_2, sp.u66, sp.u64, sp.u62, (s32) sp.u60, &sp.u7B), 0, 0, sp.u6E, (s32) sp.u6C, (s32) sp.u6A, (s32) sp.u68, &sp.u7B), sp.u79, &sp.u7B);
            if ((*(u8 *)((u8 *)arg1 + 0x1E)) == 0xFF) {
                var_v0_6 = 0;
            } else {
                var_v0_6 = D_800D30BC;
            }
            temp_v1_2 = (sp.u7A * 8) + ((u8 *)&D_800A4EA8);
            temp_v0_2 = func_15142FBC(temp_a0, var_v0_6 | 0x80000 | 0x2CA0, (*(s32 *)((u8 *)temp_v1_2 + 4)) | (*(s32 *)((u8 *)temp_v1_2 + 0)), &sp.u7B);
            (*(u8 **)((u8 *)temp_v0_2 + 4)) = (u8 *) (arg1 + 0x40);
            (*(s32 *)((u8 *)temp_v0_2 + 0)) = 0x01004008;
            (*(s32 *)((u8 *)temp_v0_2 + 8)) = 0x05000204;
            (*(s32 *)((u8 *)temp_v0_2 + 0xC)) = 0;
            (*(s32 *)((u8 *)temp_v0_2 + 0x10)) = 0x05000406;
            var_s1 = temp_v0_2 + 0x18;
            (*(s32 *)((u8 *)temp_v0_2 + 0x14)) = 0;
        }
    }
    return var_s1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513CBF0.s")
#endif
void func_1513CF9C(s32 arg0, s32 arg1, u8 arg2) {
    D_80089F60[0](arg0, arg1, arg2);
}

void func_1513CFD0(s32 arg0, s32 arg1, s32 arg2) {
}

#ifdef NON_MATCHING
/* P143 draft, inserted P146 */
extern s32 (*D_8008A058[])(u8 *);
extern s32 (*D_8008A100[])(u8 *);
extern s32 (*D_8008A1B0[])(u8 *);
// effect3d_update: per-frame update of a 3D sprite effect (sibling of func_1513C060): +0x10 bit 0 active;
// +0x58 flags; +0x1C life (s16, counts down by D_800BE9E4 when flags & 1); +0x70 / +0x71 update handlers
// (D_8008A058 / D_8008A100, 0 = none; returning 0 ends the effect); while alive, flags 0x08000000 / 0x10000000 fade
// alpha +0x5C / +0x2B to life * rate +0x6E below life +0x6C (only ever lowering it, compared against +0x5C);
// +0x20 frame position (16.16) advanced by speed +0x24 and wrapped at the frame count of texture +0x18
// (D_80090F14): flags 0x800 / 0x1000 end at the top / bottom, 0x400 ping-pong, else wrap. When it ends, the end
// handler +0x72 (D_8008A1B0, 2 slots) may veto the removal (nonzero), else func_1516972C frees it.
void func_1513CFE4(u8 *fx) {
    s8 done;
    s32 flags;
    s32 life;
    s32 a;
    s32 speed;
    s32 pos;
    s32 top;

    if (!(*(s32 *)(fx + 0x10) & 1)) {
        return;
    }
    done = 0;
    if (*(s32 *)(fx + 0x58) & 1) {
        *(s16 *)(fx + 0x1C) -= D_800BE9E4;
        if (*(s16 *)(fx + 0x1C) < 0) {
            done = 1;
        }
    }
    if ((fx[0x70] != 0) && (D_8008A058[fx[0x70]](fx) == 0)) {
        done = 1;
    }
    if ((fx[0x71] != 0) && (D_8008A100[fx[0x71]](fx) == 0)) {
        done = 1;
    }
    flags = *(s32 *)(fx + 0x58);
    if ((flags & 0x08000000) && !done) {
        life = *(s16 *)(fx + 0x1C);
        if (life < *(s16 *)(fx + 0x6C)) {
            a = life * *(s16 *)(fx + 0x6E);
            if (a < fx[0x5C]) {
                fx[0x5C] = a;
            }
        }
    }
    flags = *(s32 *)(fx + 0x58);
    if ((flags & 0x10000000) && !done) {
        life = *(s16 *)(fx + 0x1C);
        if (life < *(s16 *)(fx + 0x6C)) {
            a = life * *(s16 *)(fx + 0x6E);
            if (a < fx[0x5C]) {
                fx[0x2B] = a;
            }
        }
    }
    if (!done && ((speed = *(s32 *)(fx + 0x24)) != 0)) {
        pos = *(s32 *)(fx + 0x20) + speed * D_800BE9E4;
        *(s32 *)(fx + 0x20) = pos;
        top = (D_80090F14[fx[0x18]][0] << 16) - 1;
        if (top < pos) {
            flags = *(s32 *)(fx + 0x58);
            if (flags & 0x800) {
                done = 1;
            } else if (flags & 0x400) {
                *(s32 *)(fx + 0x20) = top - pos % top;
                *(s32 *)(fx + 0x24) = -speed;
            } else {
                do {
                    pos -= top;
                    *(s32 *)(fx + 0x20) = pos;
                } while (top < pos);
            }
        } else if (pos < 0) {
            flags = *(s32 *)(fx + 0x58);
            if (flags & 0x1000) {
                done = 1;
            } else if (flags & 0x400) {
                *(s32 *)(fx + 0x20) = -pos % top;
                *(s32 *)(fx + 0x24) = -speed;
            } else {
                do {
                    pos += top;
                    *(s32 *)(fx + 0x20) = pos;
                } while (pos < 0);
            }
        }
    }
    if (done) {
        if ((fx[0x72] == 0) || (D_8008A1B0[fx[0x72]](fx) == 0)) {
            func_1516972C((struct102 *)fx);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513CFE4.s")
#endif

#ifdef NON_MATCHING
void * func_1513D2F0(void * arg0_p, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB) {
    u8 * arg0 = (u8 *) arg0_p;
    Vtx *temp_s0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_v0;
    u8 *temp_v0;
    u8 *var_s0;
    u8 *var_s0_2;

    temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x40));
    if (temp_v0_2 & 0x800000) {
        var_a0 = 0x56;
    } else {
        var_a0 = 0x1C;
        if (temp_v0_2 & 0x02000000) {
            var_a0 = 0x49;
        }
    }
    if (temp_v0_2 & 0x80000000) {
        var_v0 = 2;
    } else {
        var_v0 = 1;
    }
    temp_v0 = func_15167A68(var_a0, argB, arg9 + 0x110, 1, (u8) (s32) argA, (u8) var_v0);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(temp_v0 + 0x18, arg0, 0x58);
    (*(s8 *)((u8 *)temp_v0 + 0x70)) = (s8) (arg2 & 0xFF);
    (*(s8 *)((u8 *)temp_v0 + 0x71)) = (s8) (arg3 & 0xFF);
    (*(u8 *)((u8 *)temp_v0 + 0x72)) = arg4;
    (*(s8 *)((u8 *)temp_v0 + 0x74)) = 0;
    (*(u8 *)((u8 *)temp_v0 + 0x73)) = arg5;
    bzero(temp_v0 + 0x100, 0x10);
    temp_s0 = temp_v0 + 0xC0;
    func_1513FFF4(temp_s0, (*(u8 *)((u8 *)temp_v0 + 0x18)), arg6);
    func_151400D0(temp_s0, (struct_eu_vtxcol *) arg1);
    (*(s32 *)((u8 *)temp_v0 + 0x10)) = 1;
    (*(s32 *)((u8 *)temp_v0 + 0x14)) = 0;
    (*(s32 *)((u8 *)temp_v0 + 0x98)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x95)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x94)) = 0;
    (*(s32 *)((u8 *)temp_v0 + 0x90)) = 0;
    (*(s32 *)((u8 *)temp_v0 + 0x9C)) = arg7;
    (*(f32 *)((u8 *)temp_v0 + 0x78)) = -10000.0f;
    (*(s8 *)((u8 *)temp_v0 + 0xA0)) = 0;
    var_s1 = 0;
    var_s0 = temp_v0;
    (*(s32 *)((u8 *)temp_v0 + 0xB8)) = arg8;
    do {
        var_s1 += 1;
        var_s0 += 4;
        (*(s32 *)((u8 *)var_s0 + 0xA0)) = 0;
    } while (var_s1 < 4);
    (*(s32 *)((u8 *)temp_v0 + 0xB4)) = 0;
    if (arg7 != 0) {
        var_s1_2 = 0;
        var_s0_2 = temp_v0;
        if (D_80082FA0 >= 0) {
            do {
                (*(s32 *)((u8 *)var_s0_2 + 0xA4)) = func_1515D9F0(arg7);
                var_s1_2 += 1;
                var_s0_2 += 4;
            } while (D_80082FA0 >= var_s1_2);
        }
        (*(s32 *)((u8 *)temp_v0 + 0xB4)) = func_1515D9B0();
    }
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513D2F0.s")
#endif
#ifdef NON_MATCHING
// record_spawn: func_1513D2F0 without extra words; returns the new record (the asm leaves func_1513D2F0's v0 in
// v0 and func_15100B80 uses it). P153.
struct210 *func_1513D4B8(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    return func_1513D2F0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 0, 0, arg7, arg8, arg9);
}
#else
void func_1513D4B8(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    func_1513D2F0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 0, 0, arg7, arg8, arg9);
}
#endif

#ifdef NON_MATCHING
// record_spawn_default: func_1513D2F0 with the default parameter block D_800A4AA0 and no extra words; returns the
// new record (the asm leaves func_1513D2F0's v0 in v0; func_15149AC0 copies into it). P128.
// functions.h declares it with this return type under NON_MATCHING (P131 merge).
struct210 *func_1513D524(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8) {
    return func_1513D2F0(arg0, &D_800A4AA0, arg1, arg2, arg3, arg4, arg5, 0, 0, arg6, arg7, arg8);
}
#else
void func_1513D524(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8) {
    func_1513D2F0(arg0, &D_800A4AA0, arg1, arg2, arg3, arg4, arg5, 0, 0, arg6, arg7, arg8);
}
#endif

s32 func_1513D594(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, u8 argD, s32 argE, u8 argF, s32 arg10) {
    struct210 *temp_v0;

    if (arg1 == 0) {
        arg1 = &D_800A4AA0;
    }
    temp_v0 = func_1513D2F0(arg0, arg1, arg2, arg3, arg4, 0xC, arg5, argB, argC, argE + 0x18, argF, arg10);
    if ((temp_v0 != 0) && (func_1513D6FC(&temp_v0->unk110, arg6, arg7, arg8, arg9, argA, argD) == 0)) {
        func_1516972C(temp_v0);
        return 0;
    }
    return temp_v0;
}

#ifdef NON_MATCHING
/* P160: the N64 code leaves func_1513D594's record in v0 and func_151DA08C (game_2062D0) uses it */
struct210 *func_1513D668(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC, u8 argD, s32 argE) {
    return (struct210 *)func_1513D594(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, 0, 0, argB, argC, argD, argE);
}
#else
void func_1513D668(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC, u8 argD, s32 argE) {
    func_1513D594(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, 0, 0, argB, argC, argD, argE);
}
#endif

#ifdef NON_MATCHING
s32 func_1510E908(s32, s32, f32 *, f32 *);
s32 func_15144E80(s32, f32 *, f32 *, s32 *);
s32 func_15145128(f32 *, f32 *, s32 *, s32 *);

s32 func_1513D6FC(struct211 *arg0, s16 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5, u8 arg6) {
    struct {
        s32 u4C;
        s32 u50;
        s32 u54;
        u8 pad58[0x8];
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        u8 pad80[0x4];
        f32 u84;
        f32 u88;
        f32 u8C;
        u8 pad90[0x14];
        f32 uA4;
        u8 padA8[0x4];
        f32 uAC;
        u8 padB0[0x4];
        f32 uB4;
        f32 uB8;
        f32 uBC;
    } sp;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 var_f12;
    f32 var_f12_2;
    f32 var_f14;

    if (arg6 != 0) {
        sp.uB4 = func_151423D8((arg1 - 0x40) & 0xFF);
        temp_f0 = func_151423D8((u8) arg1);
        sp.uAC = arg2 * temp_f0;
        sp.uA4 = arg3 * temp_f0;
        if (func_1510E908(arg4, arg5, &sp.uBC, &sp.uB8) == 0) {
            return 0;
        }
        temp_f18 = sp.uA4 * sp.uB8;
        sp2C = fabsf(sp.uA4);
        temp_f16 = arg3 * sp.uB4;
        sp28 = sqrtf((sp.uA4 * sp.uA4) + (temp_f18 * temp_f18));
        if (temp_f16 != 0.0f) {
            temp_f12 = temp_f16 * sp.uBC;
            temp_f2 = fabsf(temp_f16);
            sp.u8C = temp_f12;
            sp.u88 = temp_f2 / sqrtf((temp_f16 * temp_f16) + (temp_f12 * temp_f12));
        } else {
            sp.u8C = 0.0f;
            sp.u88 = 0.0f;
        }
        if (sp.uA4 != 0.0f) {
            sp.u84 = temp_f18;
            var_f12 = sp2C / sp28;
        } else {
            var_f12 = 0.0f;
            sp.u84 = 0.0f;
        }
        arg0->unk0 = sp.u88 * temp_f16;
        arg0->unk8 = var_f12 * sp.uA4;
        arg0->unk4 = (sp.u88 * sp.u8C) + (var_f12 * sp.u84) + 0.5f;
        temp_f18_2 = -(arg2 * sp.uB4);
        temp_f2_2 = temp_f18_2 * sp.uB8;
        sp28 = fabsf(temp_f18_2);
        sp2C = temp_f2_2;
        sp24 = sqrtf((temp_f18_2 * temp_f18_2) + (temp_f2_2 * temp_f2_2));
        if (sp.uAC != 0.0f) {
            temp_f12_2 = sp.uAC * sp.uBC;
            temp_f2_3 = fabsf(sp.uAC);
            sp.u8C = temp_f12_2;
            var_f14 = temp_f2_3 / sqrtf((sp.uAC * sp.uAC) + (temp_f12_2 * temp_f12_2));
        } else {
            var_f14 = 0.0f;
            sp.u8C = 0.0f;
            sp.u88 = 0.0f;
        }
        if (temp_f18_2 != 0.0f) {
            sp.u84 = sp2C;
            var_f12_2 = sp28 / sp24;
        } else {
            var_f12_2 = 0.0f;
            sp.u84 = 0.0f;
        }
        arg0->unkC = var_f14 * sp.uAC;
        arg0->unk14 = var_f12_2 * temp_f18_2;
        arg0->unk10 = (var_f14 * sp.u8C) + (var_f12_2 * sp.u84) + 0.5f;
        goto block_23;
    }
    sp.u7C = func_151423D8((arg1 - 0x40) & 0xFF);
    sp.u78 = func_151423D8((u8) arg1);
    if (func_15144E80(arg5, &sp.u6C, &sp.u60, &sp.u54) == 0) {
        return 0;
    }
    if (func_15145128(&sp.u6C, &sp.u6C, &sp.u50, &sp.u4C) == 0) {
        return 0;
    }
    if (func_15145128(&sp.u60, &sp.u60, &sp.u50, &sp.u4C) == 0) {
        return 0;
    }
    temp_f0_2 = arg2 * sp.u78;
    temp_f2_4 = arg2 * sp.u7C;
    arg0->unk0 = (temp_f0_2 * sp.u6C) + (temp_f2_4 * sp.u60);
    arg0->unk4 = (temp_f0_2 * sp.u70) + (temp_f2_4 * sp.u64);
    arg0->unk8 = (temp_f0_2 * sp.u74) + (temp_f2_4 * sp.u68);
    temp_f12_3 = -arg3 * sp.u7C;
    temp_f14 = arg3 * sp.u78;
    arg0->unkC = (temp_f12_3 * sp.u6C) + (temp_f14 * sp.u60);
    arg0->unk10 = (temp_f12_3 * sp.u70) + (temp_f14 * sp.u64);
    arg0->unk14 = (temp_f12_3 * sp.u74) + (temp_f14 * sp.u68);
block_23:
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513D6FC.s")
#endif
// s32 func_1513D6FC(struct211 *arg0, s16 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5, u8 arg6) {
//     f32 spBC;
//     f32 spB8;
//     f32 spB4;
//     s32 spB0;
//     f32 spAC;
//     s32 spA8;
//     f32 spA4;
//     s32 spA0;
//     s32 sp9C;
//     s32 sp98;
//     s32 sp94;
//     s32 sp90;
//     f32 sp8C;
//     f32 sp88;
//     f32 sp84;
//     s32 sp80;
//     f32 sp7C;
//     f32 sp78;
//     f32 sp74;
//     f32 sp70;
//     f32 sp6C;
//     f32 sp68;
//     f32 sp64;
//     f32 sp60;
//     s32 sp5C;
//     s32 sp58;
//     s32 sp54; // ?
//     s32 sp50; // ?
//     s32 sp4C; // ?
//     s32 sp48; // ?
//     s32 sp44; // ?
//     s32 sp40; // ?
//     s32 sp3C; // ?
//     s32 sp38; // ?
//     s32 sp34; // ?
//     s32 sp30; // ?
//     f32 sp2C;
//     f32 sp28;
//     f32 sp24;
//
//     f32 temp_f0;
//     f32 temp_f16;
//     f32 temp_f18;
//     f32 phi_f12;
//     f32 phi_f14;
//     f32 phi_f12_2;
//
//     if (arg6 != 0) {
//         spB4 = func_151423D8(arg1 - 64);
//         temp_f0 = func_151423D8(arg1);
//         spAC = arg2 * temp_f0;
//         spA4 = arg3 * temp_f0;
//         if (func_1510E388(arg4, arg5, &spBC, &spB8) == 0) {
//             return 0;
//         }
//         temp_f18 = spA4 * spB8;
//         sp2C = fabsf(spA4);
//         temp_f16 = arg3 * spB4;
//         sp28 = sqrtf((spA4 * spA4) + (temp_f18 * temp_f18));
//         if (temp_f16 != 0.0f) {
//             sp8C = temp_f16 * spBC;
//             sp88 = fabsf(temp_f16) / sqrtf((temp_f16 * temp_f16) + (sp8C * sp8C));
//         } else {
//             sp8C = 0.0f;
//             sp88 = 0.0f;
//         }
//         if (spA4 != 0.0f) {
//             sp84 = temp_f18;
//             phi_f12 = sp2C / sp28;
//         } else {
//             sp84 = 0.0f;
//             phi_f12 = 0.0f;
//         }
//         arg0->unk0 = sp88 * temp_f16;
//         arg0->unk8 = phi_f12 * spA4;
//         arg0->unk4 = (sp88 * sp8C) + (phi_f12 * sp84) + 0.5f;
//         temp_f18 = -(arg2 * spB4);
//         temp_f16 = temp_f18 * spB8;
//         sp28 = fabsf(temp_f18);
//         sp2C = temp_f16;
//         sp24 = sqrtf((temp_f18 * temp_f18) + (temp_f16 * temp_f16));
//         if (spAC != 0.0f) {
//             temp_f0 = spAC * spBC;
//             sp8C = temp_f0;
//             phi_f14 = fabsf(spAC) / sqrtf((spAC * spAC) + (temp_f0 * temp_f0));
//         } else {
//             sp8C = 0.0f;
//             sp88 = 0.0f;
//             phi_f14 = 0.0f;
//         }
//         if (temp_f18 != 0.0f) {
//             sp84 = sp2C;
//             phi_f12_2 = sp28 / sp24;
//         } else {
//             sp84 = 0.0f;
//             phi_f12_2 = 0.0f;
//         }
//         arg0->unkC = phi_f14 * spAC;
//         arg0->unk14 = phi_f12_2 * temp_f18;
//         arg0->unk10 = (phi_f14 * sp8C) + (phi_f12_2 * sp84) + 0.5f;
//     } else {
//         sp7C = func_151423D8(arg1 - 64);
//         sp78 = func_151423D8(arg1);
//         if (func_15144E80(arg5, &sp6C, &sp60, &sp54) == 0) {
//             return 0;
//         }
//         if (func_15145128(&sp6C, &sp6C, &sp50, &sp4C) == 0) {
//             return 0;
//         }
//         if (func_15145128(&sp60, &sp60, &sp50, &sp4C) == 0) {
//             return 0;
//         }
//         temp_f0 = arg2 * sp78;
//         temp_f18 = arg2 * sp7C;
//         arg0->unk0 = (temp_f0 * sp6C) + (temp_f18 * sp60);
//         arg0->unk4 = (temp_f0 * sp70) + (temp_f18 * sp64);
//         arg0->unk8 = (temp_f0 * sp74) + (temp_f18 * sp68);
//         temp_f0 = -arg3 * sp7C;
//         temp_f18 = arg3 * sp78;
//         arg0->unkC = (temp_f0 * sp6C) + (temp_f18 * sp60);
//         arg0->unk10 = (temp_f0 * sp70) + (temp_f18 * sp64);
//         arg0->unk14 = (temp_f0 * sp74) + (temp_f18 * sp68);
//     }
//     return 1;
// }

#ifdef NON_MATCHING
Gfx *func_15142B7C(Gfx *gfx, s32 set, s32 clear);
Gfx *func_15142C10(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5);
Gfx *func_15142CF0(s32, s32, s32, s16, s32, s32, s32, u8 *);
s32 func_15142E24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *arg9, s32 argA);
u8 *func_15142FBC(Gfx *, s32, s32, u8 *);
void func_151441A4(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
void func_151442FC(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern s32 D_8008A1BC;
extern s32 D_800D30BC;

u8 *func_1513DB00(u8 *arg0, u8 *arg1, s16 arg2) {
    struct {
        s16 u7A;
        s16 u7C;
        s16 u7E;
        s16 u80;
        s16 u82;
        s16 u84;
        s16 u86;
        s16 u88;
        u8 pad8A[0x1];
        u8 u8B;
    } sp;
    u8 sp79;
    u8 sp78;
    s16 sp76;
    s32 sp6C;
    u8 *sp54;
    Gfx *temp_a0;
    s32 var_a3;
    s16 temp_a2;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    s32 *temp_v1_4;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 temp_v1_5;
    s32 var_t0;
    s32 var_v0;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    u16 temp_t9;
    u8 temp_t0;
    u8 var_v0_2;
    u8 var_v0_3;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v1_6;
    u8 *var_a0;

    temp_a2 = arg2;
    if ((*(s32 *)((u8 *)arg1 + 0x10)) & 1) {
        sp.u8B = 1;
        temp_v1 = (*(s32 *)((u8 *)arg1 + 0x58));
        if ((temp_v1 & 8) && !((*(u8 *)((u8 *)arg1 + 0x64)) & (1 << temp_a2))) {
            temp_v0 = arg1 + (temp_a2 * 4);
            temp_v1_2 = (*(s32 **)((u8 *)temp_v0 + 0x100));
            if (temp_v1_2 != NULL) {
                sp54 = temp_v0;
                func_100043B4(temp_v1_2, 2U);
                (*(s32 **)((u8 *)temp_v0 + 0x100)) = NULL;
            }
        } else {
            temp_t9 = (*(u16 *)((u8 *)arg1 + 0x1A));
            sp78 = (u8) ((s32) (temp_t9 & 0xFF00) >> 8);
            sp76 = temp_v1 & 0xC000;
            sp79 = (u8) temp_t9;
            if ((temp_v1 & 0x01000000) && (temp_v0_2 = (*(u8 **)((u8 *)arg1 + 0x60)), (temp_v0_2 != NULL)) && !((*(s16 *)((u8 *)temp_v0_2 + 2)) & (1 << temp_a2))) {
                temp_v0_3 = arg1 + (temp_a2 * 4);
                temp_v1_3 = (*(s32 **)((u8 *)temp_v0_3 + 0x100));
                if (temp_v1_3 != NULL) {
                    sp54 = temp_v0_3;
                    func_100043B4(temp_v1_3, 2U);
                    (*(s32 **)((u8 *)temp_v0_3 + 0x100)) = NULL;
                }
            } else {
                arg2 = temp_a2;
                temp_v0_4 = ((s32 (*)()) *(s32 *)((u8 *)&D_8008A1BC + ((*(u8 *)((u8 *)arg1 + 0x73)) * 4)))(arg1, temp_a2, temp_a2);
                sp6C = temp_v0_4;
                if (temp_v0_4 == 0) {
                    temp_v0_5 = arg1 + (arg2 * 4);
                    temp_v1_4 = (*(s32 **)((u8 *)temp_v0_5 + 0x100));
                    if (temp_v1_4 != NULL) {
                        sp54 = temp_v0_5;
                        func_100043B4(temp_v1_4, 2U);
                        (*(s32 **)((u8 *)temp_v0_5 + 0x100)) = NULL;
                    }
                } else {
                    if ((*(s32 *)((u8 *)arg1 + 0x58)) & 0x04000000) {
                        var_v0 = (*(s32 *)((u8 *)arg1 + 0x68));
                    } else {
                        var_v0 = 0;
                    }
                    arg0 = (u8 *) func_151462C8(arg0, arg1 + 0x9C, 0, 0, 0, (s32) arg2, arg1 + 0x34, 2, var_v0);
                    if ((*(s32 *)((u8 *)arg1 + 0x58)) & 0x40000) {
                        var_v0_2 = (*(u8 *)((u8 *)arg1 + 0x5E));
                    } else {
                        var_v0_2 = 4;
                    }
                    func_151441A4(&sp.u88, &sp.u86, &sp.u84, &sp.u82, (s32) (*(u8 *)((u8 *)arg1 + 0x28)), (s32) (*(u8 *)((u8 *)arg1 + 0x29)), (s32) (*(u8 *)((u8 *)arg1 + 0x2A)), (s32) (*(u8 *)((u8 *)arg1 + 0x2B)), 0xFF, 0xFF, 0xFF, (s32) (*(u8 *)((u8 *)arg1 + 0x5C)), (s32) (*(u8 *)((u8 *)arg1 + 0x5D)), (s32) var_v0_2);
                    if ((*(s32 *)((u8 *)arg1 + 0x58)) & 0x80000) {
                        var_v0_3 = (*(u8 *)((u8 *)arg1 + 0x5F));
                    } else {
                        var_v0_3 = 5;
                    }
                    func_151442FC(&sp.u80, &sp.u7E, &sp.u7C, &sp.u7A, (s32) (*(u8 *)((u8 *)arg1 + 0x28)), (s32) (*(u8 *)((u8 *)arg1 + 0x29)), (s32) (*(u8 *)((u8 *)arg1 + 0x2A)), (s32) (*(u8 *)((u8 *)arg1 + 0x2B)), 0xFF, 0xFF, 0xFF, (s32) (*(u8 *)((u8 *)arg1 + 0x5C)), (s32) (*(u8 *)((u8 *)arg1 + 0x5D)), (s32) var_v0_3);
                    var_v0_4 = 0;
                    if (sp76 & 0x4000) {
                        var_v0_4 = 0x200;
                    }
                    if (sp76 & 0x8000) {
                        var_v0_4 |= 0x400;
                    }
                    if ((*(s32 *)((u8 *)arg1 + 0x58)) & 0x100000) {
                        var_v0_4 |= 0x20000;
                    }
                    temp_t0 = (*(u8 *)((u8 *)arg1 + 0x18));
                    var_a0 = func_15142B7C(arg0, var_v0_4 | 1, 0x600);
                    if (temp_t0 != 0xFF) {
                        temp_v1_5 = (*(s32 *)((u8 *)arg1 + 0x58));
                        if (temp_v1_5 & 0x200000) {
                            var_a3 = 0;
                        } else {
                            var_a3 = 2;
                        }
                        if (temp_v1_5 & 0x40000000) {
                            var_v0_5 = 0x3E;
                        } else {
                            var_v0_5 = 3;
                        }
                        arg0 = func_15142E24(var_a0, &D_80090F10[temp_t0], (*(s32 *)((u8 *)arg1 + 0x20)), var_a3, 0, 0, (s32) temp_t0, 0, 0, &sp.u8B, var_v0_5);
                        var_a0 = arg0;
                    }
                    temp_a0 = func_1513F4E4(func_15142CF0(func_15142C10(var_a0, sp.u80, sp.u7E, sp.u7C, (s32) sp.u7A, &sp.u8B), 0xF2, 0, sp.u88, (s32) sp.u86, (s32) sp.u84, (s32) sp.u82, &sp.u8B), sp78, &sp.u8B);
                    if ((*(s32 *)((u8 *)arg1 + 0x58)) & 0x20000000) {
                        var_t0 = 0x100000;
                    } else {
                        var_t0 = 0;
                    }
                    if ((*(u8 *)((u8 *)arg1 + 0x18)) == 0xFF) {
                        var_v0_6 = 0;
                    } else {
                        var_v0_6 = D_800D30BC;
                    }
                    temp_v1_6 = (sp79 * 8) + ((u8 *)&D_800A4EA8);
                    temp_v0_6 = func_15142FBC(temp_a0, var_v0_6 | (var_t0 | 0x80000) | 0x2CA0, (*(s32 *)((u8 *)temp_v1_6 + 4)) | (*(s32 *)((u8 *)temp_v1_6 + 0)), &sp.u8B);
                    (*(s32 *)((u8 *)temp_v0_6 + 0)) = 0x01004008;
                    (*(s32 *)((u8 *)temp_v0_6 + 4)) = sp6C;
                    arg0 = temp_v0_6 + 0x10;
                    (*(s32 *)((u8 *)temp_v0_6 + 0xC)) = 0x406;
                    (*(s32 *)((u8 *)temp_v0_6 + 8)) = 0x06000204;
                }
            }
        }
    }
    return arg0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513DB00.s")
#endif
// jump table
extern s32 (*D_8008A304[])(u8 *, s32, u8);

void func_1513DF9C(u8 *arg0, s32 arg1, u8 arg2) {
    s32 idx;

    if (!(*(s32 *)(arg0 + 0x58) & 0x400000)) {
        idx = 0;
    } else {
        switch (arg0[0x19]) {
        case 12: idx = 10; break;
        case 11: idx = 9; break;
        case 0:
        case 2: idx = 0; break;
        case 1: idx = 1; break;
        case 5: idx = 2; break;
        case 6: idx = 3; break;
        case 3: idx = 4; break;
        case 7: idx = 5; break;
        case 8: idx = 6; break;
        case 9: idx = 7; break;
        case 4: idx = 8; break;
        default: idx = 0; break;
        }
    }
    D_8008A304[idx](arg0, arg1, arg2);
}

void func_1513E070(s32 arg0, s32 arg1, s32 arg2) {
}

void func_1513E084(struct210 *arg0, struct212 *arg1, u8 arg2) {
    struct212 *temp_v0 = &arg0->unk110;
    if (arg2 == 0x1A) {
        if ((temp_v0->unk0 == arg1->unk0) || (temp_v0->unk4.b.unk0 == arg1->unk4.b.unk0)) {
            func_1516972C(arg0);
        }
    } else {
        temp_v0 = &arg0->unk110;
        if (arg2 == 0x2D) {
            if (temp_v0->unk0 == arg1->unk0) {
                temp_v0->unk0 = arg1->unk4.i.unk0;
                temp_v0->unk4.b.unk0 = arg1->unk9;
            } else if (temp_v0->unk0 == arg1->unk4.i.unk0) {
                temp_v0->unk0 = arg1->unk0;
                temp_v0->unk4.b.unk0 = arg1->unk8;
            }
        }
    }
}

void func_1513E134(void) {
}

// positions a 4-vertex quad of half-size (arg4, arg5) at (arg1, arg2, arg3), rotated by angle arg6
#ifdef NON_MATCHING
void func_1513E13C(struct210 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6) {
    f32 sp48;
    f32 sp30;
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f10_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f8;
    f32 temp_f8_2;
    s32 temp_f10;

    sp48 = func_151423D8((arg6 - 0x40) & 0xFF);
    temp_f0 = func_151423D8(arg6);
    temp_f14 = arg4 * temp_f0;
    temp_f12 = arg5 * sp48;
    temp_f18 = arg1 + temp_f14;
    arg0->unk40 = (s16) (s32) (temp_f18 - temp_f12);
    temp_f10 = (s32) arg2;
    arg0->unk42 = (s16) temp_f10;
    temp_f16 = arg5 * temp_f0;
    temp_f2 = arg4 * sp48;
    temp_f8 = arg3 + temp_f16;
    sp1C = temp_f8;
    arg0->unk44 = (s16) (s32) (temp_f8 + temp_f2);
    temp_f8_2 = arg1 - temp_f14;
    sp30 = temp_f8_2;
    arg0->unk52 = (s16) temp_f10;
    arg0->unk50 = (s16) (s32) (temp_f8_2 - temp_f12);
    arg0->unk54 = (s16) (s32) (sp1C - temp_f2);
    arg0->unk62 = (s16) temp_f10;
    arg0->unk60 = (s16) (s32) (sp30 + temp_f12);
    temp_f10_2 = arg3 - temp_f16;
    sp30 = temp_f10_2;
    arg0->unk72 = (s16) temp_f10;
    arg0->unk70 = (s16) (s32) (temp_f18 + temp_f12);
    arg0->unk64 = (s16) (s32) (temp_f10_2 - temp_f2);
    arg0->unk74 = (s16) (s32) (sp30 + temp_f2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E13C.s")
#endif
// NON-MATCHING: arg0 lives in a1 and stack layout differs (frame 0x50)
// void func_1513E13C(struct210 *arg0_, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6) {
//     Vtx *arg0 = (Vtx *)&arg0_->unk40;
//     f32 s = func_151423D8(arg6 - 0x40);
//     f32 c = func_151423D8(arg6);
//     s32 y;
//
//     arg0[0].v.ob[0] = (arg1 + arg4 * c) - arg5 * s;
//     arg0[0].v.ob[1] = y = arg2;
//     arg0[0].v.ob[2] = (arg3 + arg5 * c) + arg4 * s;
//     arg0[1].v.ob[1] = y;
//     arg0[1].v.ob[0] = (arg1 - arg4 * c) - arg5 * s;
//     arg0[1].v.ob[2] = (arg3 + arg5 * c) - arg4 * s;
//     arg0[2].v.ob[1] = y;
//     arg0[2].v.ob[0] = (arg1 - arg4 * c) + arg5 * s;
//     arg0[3].v.ob[1] = y;
//     arg0[3].v.ob[0] = (arg1 + arg4 * c) + arg5 * s;
//     arg0[2].v.ob[2] = (arg3 - arg5 * c) - arg4 * s;
//     arg0[3].v.ob[2] = (arg3 - arg5 * c) + arg4 * s;
// }

void func_1513E2A4(void) {
}

#ifdef NON_MATCHING
s32 func_1510E908(s32, s32, f32 *, f32 *);
s32 func_15144E80(s32, f32 *, f32 *, s32 *);
s32 func_15145128(f32 *, f32 *, s32 *, s32 *);
/* Corners of a sprite quad (4 Vtx at vtx + 0x40): centre (x, y, z), half sizes w / h, rotated by angle in the
 * screen plane. With a camera (arg2) the quad uses the camera's right / up axes (func_15144E80, normalised by
 * func_15145128); without one it is built in x / z and tilted by the view slopes of func_1510E908(arg1).
 * Returns 0 when the axes are not available. */
s32 func_1513E2AC(s32 vtx, s32 arg1, s32 arg2, f32 x, f32 y, f32 z, f32 w, f32 h, u8 angle) {
    s16 *v = (s16 *)(vtx + 0x40);
    f32 c = func_151423D8((u8)(angle - 0x40));
    f32 s = func_151423D8(angle);
    f32 right[3];
    f32 up[3];
    f32 rx, ry, rz;
    f32 ux, uy, uz;
    f32 ws, wc, hc, hs;
    f32 slopeX, slopeZ;
    f32 pt[4][2];
    f32 a, b, ta, tb, fa, fb;
    s16 i;

    if (arg2 != 0) {
        if (func_15144E80(arg2, right, up, NULL) == 0) {
            return 0;
        }
        func_15145128(right, right, NULL, NULL);
        func_15145128(up, up, NULL, NULL);
        ws = w * s;
        wc = w * c;
        rx = ws * right[0] + wc * up[0];
        ry = ws * right[1] + wc * up[1];
        rz = ws * right[2] + wc * up[2];
        hc = -h * c;
        hs = h * s;
        ux = hc * right[0] + hs * up[0];
        uy = hc * right[1] + hs * up[1];
        uz = hc * right[2] + hs * up[2];
        v[0] = (s32)((x - rx) + ux);
        v[1] = (s32)((y - ry) + uy);
        v[2] = (s32)((z - rz) + uz);
        v[8] = (s32)((x + rx) + ux);
        v[9] = (s32)((y + ry) + uy);
        v[10] = (s32)((z + rz) + uz);
        v[16] = (s32)((x + rx) - ux);
        v[17] = (s32)((y + ry) - uy);
        v[18] = (s32)((z + rz) - uz);
        v[24] = (s32)((x - rx) - ux);
        v[25] = (s32)((y - ry) - uy);
        v[26] = (s32)((z - rz) - uz);
        return 1;
    }
    if (func_1510E908(arg1, arg2, &slopeX, &slopeZ) == 0) {
        return 0;
    }
    ws = w * s;
    hc = h * c;
    hs = h * s;
    wc = w * c;
    pt[0][0] = ws - hc;
    pt[0][1] = hs + wc;
    pt[1][0] = -ws - hc;
    pt[1][1] = hs - wc;
    pt[2][0] = -ws + hc;
    pt[2][1] = -hs - wc;
    pt[3][0] = ws + hc;
    pt[3][1] = -hs + wc;
    for (i = 0; i < 4; i++) {
        b = pt[i][0];
        a = pt[i][1];
        ta = a * slopeZ;
        if (b == 0.0f) {
            tb = 0.0f;
            fb = 0.0f;
        } else {
            tb = b * slopeX;
            fb = fabsf(b) / sqrtf(b * b + tb * tb);
        }
        if (a == 0.0f) {
            ta = 0.0f;
            fa = 0.0f;
        } else {
            fa = fabsf(a) / sqrtf(a * a + ta * ta);
        }
        v[0] = (s32)(b * fb + x);
        v[1] = (s32)(((fb * tb + y) + fa * ta) + 0.5f);
        v[2] = (s32)(pt[i][1] * fa + z);
        v += 8;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E2AC.s")
#endif

typedef struct {
    u8  pad0[0x8];
    f32 unk8[3];
    f32 unk14[3];
    f32 unk20[3];
    f32 unk2C;
} struct_eu_1513E6E8_vel;

typedef struct {
    u8  pad0[0x34];
    f32 unk34[3];
    f32 unk40[3];
    f32 unk4C[3];
    s32 unk58;
    u8  pad5C;
    u8  unk5D;
    u8  pad5E[0xB2];
    struct_eu_1513E6E8_vel unk110;
} struct_eu_1513E6E8;

s32 func_1513E6E8(struct_eu_1513E6E8 *arg0) {
    struct_eu_1513E6E8_vel *vel = &arg0->unk110;

    if (arg0->unk58 & 0x20) {
        vel->unk8[1] += vel->unk2C * D_800BE9A4;
    }
    if (arg0->unk58 & 0x40) {
        arg0->unk34[0] += vel->unk8[0] * D_800BE9A4;
        arg0->unk34[1] += vel->unk8[1] * D_800BE9A4;
        arg0->unk34[2] += vel->unk8[2] * D_800BE9A4;
    }
    if (arg0->unk58 & 0x80) {
        arg0->unk40[0] += vel->unk14[0] * D_800BE9A4;
        arg0->unk40[1] += vel->unk14[1] * D_800BE9A4;
        arg0->unk40[2] += vel->unk14[2] * D_800BE9A4;
    }
    if (arg0->unk58 & 0x100) {
        arg0->unk4C[0] += vel->unk20[0] * D_800BE9A4;
        arg0->unk4C[1] += vel->unk20[1] * D_800BE9A4;
        arg0->unk4C[2] += vel->unk20[2] * D_800BE9A4;
    }
    arg0->unk5D = 0xFF;
    return 1;
}

#ifdef NON_MATCHING
/* P143 */
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
// sprite_quad_build_scaled: builds the 4 corner vertices (+-half width +0x2C, +-half height +0x30, z 0) of a
// sprite effect's quad for display list slot `slot`: rotation from the angles +0x40/+0x44/+0x48, matrix rows scaled
// by +0x4C/+0x50/+0x54, translated to +0x34/+0x38/+0x3C. func_151D6310 hands out the slot's vertex buffer (pointer
// table at +0x100); when it is new, both halves (0x40 bytes each) are first filled from the template at +0xC0.
// Returns the written vertices, or NULL when no buffer is available. (Draw-table D_8008A1BC entry.)
u8 *func_1513E83C(u8 *fx, s16 slot) {
    f32 corner[4][3];
    f32 mtx[4][4];
    u8 *vtx;
    u8 *start;
    u8 fresh;
    s16 i;

    func_151D6310((s32 *)(fx + 0x100), slot, 0x40, (s32 *)&vtx, &fresh);
    start = vtx;
    if (vtx == NULL) {
        return NULL;
    }
    if (fresh) {
        memcpy(*(u8 **)(fx + 0x100 + slot * 4), fx + 0xC0, 0x40);
        memcpy(*(u8 **)(fx + 0x100 + slot * 4) + 0x40, fx + 0xC0, 0x40);
    }
    corner[0][0] = *(f32 *)(fx + 0x2C);
    corner[0][1] = *(f32 *)(fx + 0x30);
    corner[1][0] = -*(f32 *)(fx + 0x2C);
    corner[1][1] = *(f32 *)(fx + 0x30);
    corner[2][0] = -*(f32 *)(fx + 0x2C);
    corner[2][1] = -*(f32 *)(fx + 0x30);
    corner[3][0] = *(f32 *)(fx + 0x2C);
    corner[3][1] = -*(f32 *)(fx + 0x30);
    func_150A8050(mtx, *(f32 *)(fx + 0x40), *(f32 *)(fx + 0x44), *(f32 *)(fx + 0x48));
    mtx[3][0] = *(f32 *)(fx + 0x34);
    mtx[3][1] = *(f32 *)(fx + 0x38);
    mtx[3][2] = *(f32 *)(fx + 0x3C);
    mtx[0][0] *= *(f32 *)(fx + 0x4C);
    mtx[0][1] *= *(f32 *)(fx + 0x4C);
    mtx[0][2] *= *(f32 *)(fx + 0x4C);
    mtx[1][0] *= *(f32 *)(fx + 0x50);
    mtx[1][1] *= *(f32 *)(fx + 0x50);
    mtx[1][2] *= *(f32 *)(fx + 0x50);
    mtx[2][0] *= *(f32 *)(fx + 0x54);
    mtx[2][1] *= *(f32 *)(fx + 0x54);
    mtx[2][2] *= *(f32 *)(fx + 0x54);
    for (i = 0; i < 4; i++) {
        func_150A7E40(mtx, corner[i][0], corner[i][1], 0.0f, &corner[i][0], &corner[i][1], &corner[i][2]);
        *(s16 *)(vtx + 0) = (s32)corner[i][0];
        *(s16 *)(vtx + 2) = (s32)corner[i][1];
        *(s16 *)(vtx + 4) = (s32)corner[i][2];
        *(s16 *)(vtx + 6) = 0;
        vtx += 0x10;
    }
    return start;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E83C.s")
#endif
// ???
#ifdef NON_MATCHING
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
extern s32 D_800DD608;
extern s32 D_800DD618;

u8 *func_1513EAD8(u8 *arg0, u8 arg1, s16 arg2) {
    struct {
        u8 u37;
        u8 pad38[0x10];
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s16 u50;
        s16 u52;
        s16 u54;
        s16 u56;
        s16 u58;
        s16 u5A;
        s16 u5C;
        s16 u5E;
        u8 * u60;
        u8 * u64;
    } sp;
    u8 *sp30;
    s32 sp2C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    s32 temp_a1;
    s32 temp_f10;
    s32 temp_f4;
    s32 temp_f4_2;
    s32 temp_f6;
    s32 temp_f6_2;
    s32 temp_f8;
    s32 temp_t0;
    u8 *temp_v0;

    func_151D6310(arg0 + 0x100, arg2, 0x40, &sp.u64, &sp.u37);
    sp.u60 = sp.u64;
    if (sp.u64 != NULL) {
        if (sp.u37 != 0) {
            temp_v0 = arg0 + (arg2 * 4);
            temp_a1 = arg0 + 0xC0;
            sp2C = temp_a1;
            sp30 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_t0 = arg2 * 4;
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
        temp_f12 = (*(f32 *)((u8 *)arg0 + 0x30));
        (*(s16 *)((u8 *)sp.u64 + 6)) = 0;
        temp_f14 = *(&D_800DD608 + temp_t0) * temp_f0;
        (*(s16 *)((u8 *)sp.u64 + 0x16)) = 0;
        temp_f16 = *(&D_800DD618 + temp_t0) * temp_f0;
        (*(s16 *)((u8 *)sp.u64 + 0x26)) = 0;
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x50)) * temp_f12;
        (*(s16 *)((u8 *)sp.u64 + 0x36)) = 0;
        temp_f6 = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f16);
        sp.u48 = (s16) temp_f6;
        sp.u5A = (s16) temp_f6;
        temp_f4 = (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - temp_f2);
        sp.u4A = (s16) temp_f4;
        sp.u50 = (s16) temp_f4;
        temp_f10 = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f14);
        sp.u4C = (s16) temp_f10;
        sp.u5E = (s16) temp_f10;
        temp_f8 = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f16);
        sp.u4E = (s16) temp_f8;
        sp.u54 = (s16) temp_f8;
        temp_f6_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (temp_f12 - temp_f2));
        sp.u56 = (s16) temp_f6_2;
        sp.u5C = (s16) temp_f6_2;
        temp_f4_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f14);
        sp.u52 = (s16) temp_f4_2;
        sp.u58 = (s16) temp_f4_2;
        if (arg1 != 0) {
            (*(s16 *)((u8 *)sp.u64 + 0)) = sp.u4E;
            (*(s16 *)((u8 *)sp.u64 + 2)) = sp.u50;
            (*(s16 *)((u8 *)sp.u64 + 4)) = sp.u52;
            (*(s16 *)((u8 *)sp.u64 + 0x10)) = sp.u54;
            (*(s16 *)((u8 *)sp.u64 + 0x12)) = sp.u56;
            (*(s16 *)((u8 *)sp.u64 + 0x14)) = sp.u58;
            (*(s16 *)((u8 *)sp.u64 + 0x20)) = sp.u5A;
            (*(s16 *)((u8 *)sp.u64 + 0x22)) = sp.u5C;
            (*(s16 *)((u8 *)sp.u64 + 0x24)) = sp.u5E;
            (*(s16 *)((u8 *)sp.u64 + 0x30)) = sp.u48;
            (*(s16 *)((u8 *)sp.u64 + 0x32)) = sp.u4A;
            (*(s16 *)((u8 *)sp.u64 + 0x34)) = sp.u4C;
        } else {
            (*(s16 *)((u8 *)sp.u64 + 0)) = sp.u48;
            (*(s16 *)((u8 *)sp.u64 + 2)) = sp.u4A;
            (*(s16 *)((u8 *)sp.u64 + 4)) = sp.u4C;
            (*(s16 *)((u8 *)sp.u64 + 0x10)) = sp.u4E;
            (*(s16 *)((u8 *)sp.u64 + 0x12)) = sp.u50;
            (*(s16 *)((u8 *)sp.u64 + 0x14)) = sp.u52;
            (*(s16 *)((u8 *)sp.u64 + 0x20)) = sp.u54;
            (*(s16 *)((u8 *)sp.u64 + 0x22)) = sp.u56;
            (*(s16 *)((u8 *)sp.u64 + 0x24)) = sp.u58;
            (*(s16 *)((u8 *)sp.u64 + 0x30)) = sp.u5A;
            (*(s16 *)((u8 *)sp.u64 + 0x32)) = sp.u5C;
            (*(s16 *)((u8 *)sp.u64 + 0x34)) = sp.u5E;
        }
        return sp.u60;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513EAD8.s")
#endif
void func_1513EDB4(s32 arg0, s16 arg1) {
    func_1513EAD8(arg0, 0, arg1);
}

s32 func_1513EDE4(s32 arg0, s16 arg1) {
    return func_1513EAD8(arg0, 1, arg1);
}

#ifdef NON_MATCHING
/* P143 */
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
// sprite_quad_build: builds the 4 corner vertices (+-half width +0x2C, +-half height +0x30, z 0) of a sprite
// effect's quad for display list slot `slot`, rotated by the angles +0x40/+0x44/+0x48 and translated to
// +0x34/+0x38/+0x3C (no scale; func_1513E83C is the scaled variant). New vertex buffers from func_151D6310 are first
// filled (both 0x40-byte halves) from the template at +0xC0. Returns the vertices, or NULL when there is no buffer.
// (Draw-table D_8008A1BC entry.)
u8 *func_1513EE14(u8 *fx, s16 slot) {
    f32 mtx[4][4];
    f32 in[4][2];
    f32 out[4][3];
    u8 *vtx;
    u8 *start;
    u8 fresh;
    s32 i;

    func_151D6310((s32 *)(fx + 0x100), slot, 0x40, (s32 *)&vtx, &fresh);
    start = vtx;
    if (vtx == NULL) {
        return NULL;
    }
    if (fresh) {
        memcpy(*(u8 **)(fx + 0x100 + slot * 4), fx + 0xC0, 0x40);
        memcpy(*(u8 **)(fx + 0x100 + slot * 4) + 0x40, fx + 0xC0, 0x40);
    }
    func_150A8050(mtx, *(f32 *)(fx + 0x40), *(f32 *)(fx + 0x44), *(f32 *)(fx + 0x48));
    mtx[3][0] = *(f32 *)(fx + 0x34);
    mtx[3][1] = *(f32 *)(fx + 0x38);
    mtx[3][2] = *(f32 *)(fx + 0x3C);
    in[0][0] = *(f32 *)(fx + 0x2C);
    in[0][1] = *(f32 *)(fx + 0x30);
    in[1][0] = -*(f32 *)(fx + 0x2C);
    in[1][1] = *(f32 *)(fx + 0x30);
    in[2][0] = -*(f32 *)(fx + 0x2C);
    in[2][1] = -*(f32 *)(fx + 0x30);
    in[3][0] = *(f32 *)(fx + 0x2C);
    in[3][1] = -*(f32 *)(fx + 0x30);
    for (i = 0; i < 4; i++) {
        func_150A7E40(mtx, in[i][0], in[i][1], 0.0f, &out[i][0], &out[i][1], &out[i][2]);
    }
    for (i = 0; i < 4; i++) {
        *(s16 *)(vtx + 0) = (s32)out[i][0];
        *(s16 *)(vtx + 2) = (s32)out[i][1];
        *(s16 *)(vtx + 4) = (s32)out[i][2];
        *(s16 *)(vtx + 6) = 0;
        vtx += 0x10;
    }
    return start;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513EE14.s")
#endif

#ifdef NON_MATCHING
extern s32 D_800DD608;
extern s32 D_800DD618;

u8 *func_1513F114(u8 *arg0, s16 arg1) {
    struct {
        u8 u4B;
        f32 u4C;
        u8 pad50[0x24];
        f32 u74;
        f32 u78;
        f32 u7C;
        u8 pad80[0x4];
        f32 u84;
        u8 * u88;
        u8 * u8C;
    } sp;
    u8 *sp44;
    s32 sp40;                                       /* compiler-managed */
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 var_f12;
    f32 var_f14;
    f32 var_f2;
    s32 temp_a1;
    s32 temp_t0;
    u8 *temp_v0;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u8C, &sp.u4B);
    sp.u88 = sp.u8C;
    if (sp.u8C != NULL) {
        if (sp.u4B != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp40 = temp_a1;
            sp44 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_t0 = arg1 * 4;
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_f18 = *(&D_800DD608 + temp_t0);
        temp_f20 = *(&D_800DD618 + temp_t0);
        temp_f16 = -((*(f32 *)((u8 *)arg0 + 0x50)) * temp_f0);
        sp.u78 = temp_f0 + temp_f16;
        var_f14 = -1.0f;
        var_f2 = ((((*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x34))) * temp_f20) - (temp_f18 * ((*(f32 *)((u8 *)arg0 + 0x48)) - (*(f32 *)((u8 *)arg0 + 0x3C))))) * D_800BEDC8;
        if (var_f2 < 0.0f) {
            var_f14 = 1.0f;
            var_f2 = -var_f2;
        }
        var_f12 = sqrtf(var_f2) * (*(f32 *)((u8 *)arg0 + 0x4C));
        if (var_f12 > 1.5707964f) {
            var_f12 = 1.5707964f;
        }
        temp_f12 = var_f12 * var_f14;
        sp.u7C = temp_f16;
        sp.u84 = temp_f18;
        sp.u4C = temp_f12;
        sp.u74 = sinf(temp_f12);
        temp_f0_2 = cosf(temp_f12);
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x2C));
        temp_f14 = temp_f2 * temp_f0_2;
        temp_f16_2 = temp_f2 * sp.u74;
        temp_f8 = sp.u7C * sp.u74;
        temp_f12_2 = temp_f14 - temp_f8;
        sp3C = temp_f8;
        (*(s16 *)((u8 *)sp.u8C + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + (temp_f12_2 * temp_f20));
        temp_f6 = sp.u7C * temp_f0_2;
        sp38 = temp_f6;
        (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f6 + temp_f16_2);
        (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (temp_f12_2 * temp_f18));
        (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
        temp_f2_2 = -(temp_f14 + sp3C);
        (*(s16 *)((u8 *)sp.u8C + 0x10)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + (temp_f2_2 * temp_f20));
        (*(s16 *)((u8 *)sp.u8C + 0x12)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) + sp38) - temp_f16_2);
        (*(s16 *)((u8 *)sp.u8C + 0x14)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (temp_f2_2 * temp_f18));
        (*(s16 *)((u8 *)sp.u8C + 0x16)) = 0;
        temp_f12_3 = sp.u78 * sp.u74;
        temp_f8_2 = -(temp_f14 + temp_f12_3);
        sp34 = temp_f8_2;
        (*(s16 *)((u8 *)sp.u8C + 0x20)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + (temp_f8_2 * temp_f20));
        temp_f4 = sp.u78 * temp_f0_2;
        temp_f0_3 = temp_f14 - temp_f12_3;
        sp40 = temp_f4;
        (*(s16 *)((u8 *)sp.u8C + 0x22)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f4) - temp_f16_2);
        (*(s16 *)((u8 *)sp.u8C + 0x24)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (temp_f8_2 * temp_f18));
        (*(s16 *)((u8 *)sp.u8C + 0x26)) = 0;
        (*(s16 *)((u8 *)sp.u8C + 0x30)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + (temp_f0_3 * temp_f20));
        (*(s16 *)((u8 *)sp.u8C + 0x32)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + sp40 + temp_f16_2);
        (*(s16 *)((u8 *)sp.u8C + 0x34)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (temp_f0_3 * temp_f18));
        (*(s16 *)((u8 *)sp.u8C + 0x36)) = 0;
        return sp.u88;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513F114.s")
#endif
void func_1513F4B0(struct210 *arg0, s16 arg1) {
    func_15140410(arg0, &arg0->unk110, &arg0->unk11C, arg1);
}

// emits gDPSetCombineLERP for combine mode arg1 (table D_800A4F88), preceded by a pipe sync if *arg2 == 1
Gfx *func_1513F4E4(Gfx *arg0, u8 arg1, u8 *arg2) {
    s32 mode = func_15143044(arg1, 0);

    if (mode != D_800DD5EE) {
        if (*arg2 == 1) {
            gDPPipeSync(arg0++);
            *arg2 = 0;
        }
#define CC(i) D_800A4F88[arg1][i]
        // fakematch: w0 and w1 on one line (statement scheduling)
        { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = _SHIFTL(G_SETCOMBINE, 24, 8) | _SHIFTL(GCCc0w0(CC(0), CC(2), CC(4), CC(6)) | GCCc1w0(CC(8), CC(10)), 0, 24); _g->words.w1 = (unsigned int)(GCCc0w1(CC(1), CC(3), CC(5), CC(7)) | GCCc1w1(CC(9), CC(12), CC(14), CC(11), CC(13), CC(15))); }
#undef CC
        D_800DD5EE = mode;
    }
    return arg0;
}

void func_1513F680(struct171 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    arg0->unk70 = arg1;
    arg0->unk71 = arg2;
    arg0->unk72 = arg3;
    arg0->unk73 = arg4;
}

void func_1513F6C0(struct210 *arg0, u8 arg1, u8 arg2) {
    arg0->unk80 = arg1;
    arg0->unk81 = arg2;
}

s32 func_1513F6E8(struct210 *arg0) {
    f32 temp_f0 = ((f32 *)arg0)[0x128 / 4];
    arg0->unk2C += temp_f0 * D_800BE9A4;
    arg0->unk30 += temp_f0 * D_800BE9A4;
    return 1;
}

#ifdef NON_MATCHING
s32 func_1513F728(u8 *arg0) {
    struct {
        f32 u20;
        f32 u24;
        f32 u28;
        u8 pad2C[0x4];
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f16;
    f32 var_f18;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_v0;
    s32 var_v0_2;
    u8 *temp_v1;

    temp_v1 = arg0 + 0x110;
    (*(f32 *)((u8 *)(&sp.u20) + 0)) = (*(f32 *)((u8 *)temp_v1 + 0));
    (*(f32 *)((u8 *)(&sp.u20) + 4)) = (f32) (*(f32 *)((u8 *)temp_v1 + 4));
    (*(f32 *)((u8 *)(&sp.u20) + 8)) = (f32) (*(f32 *)((u8 *)temp_v1 + 8));
    var_v0 = D_800BE9E4;
    if (var_v0 != 0) {
        temp_a2 = -(var_v0 & 3);
        temp_a1 = temp_a2 + var_v0;
        if (temp_a2 != 0) {
            temp_f0 = (*(f32 *)((u8 *)temp_v1 + 0x10));
            var_v0 -= 1;
            var_f18 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0;
            if (temp_a1 != var_v0) {
                do {
                    (*(f32 *)((u8 *)temp_v1 + 0)) = var_f18;
                    var_v0 -= 1;
                    var_f18 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0;
                    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0);
                    (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0);
                } while (temp_a1 != var_v0);
            }
            (*(f32 *)((u8 *)temp_v1 + 0)) = var_f18;
            (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0);
            (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0);
            if (var_v0 != 0) {
                goto block_5;
            }
        } else {
block_5:
            temp_f0_2 = (*(f32 *)((u8 *)temp_v1 + 0x10));
            var_v0_2 = var_v0 - 4;
            var_f16 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2;
            if (var_v0_2 != 0) {
                do {
                    (*(f32 *)((u8 *)temp_v1 + 0)) = var_f16;
                    var_v0_2 -= 4;
                    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
                    var_f16 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2;
                    (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
                } while (var_v0_2 != 0);
            }
            (*(f32 *)((u8 *)temp_v1 + 0)) = var_f16;
            (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
        }
    }
    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) + ((*(f32 *)((u8 *)temp_v1 + 0xC)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((sp.u20 + (0.5f * (((*(f32 *)((u8 *)temp_v1 + 0)) - sp.u20) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((sp.u24 + (0.5f * (((*(f32 *)((u8 *)temp_v1 + 4)) - sp.u24) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((sp.u28 + (0.5f * (((*(f32 *)((u8 *)temp_v1 + 8)) - sp.u28) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40)) + ((*(f32 *)((u8 *)temp_v1 + 0x14)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) + ((*(f32 *)((u8 *)temp_v1 + 0x18)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x48)) + ((*(f32 *)((u8 *)temp_v1 + 0x1C)) * D_800BE9A4));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513F728.s")
#endif
u8 *func_1513FAB4(u8 *fx, u8 flip, f32 *scale, s16 slot);

void func_1513FA2C(s32 arg0, s16 arg1) {
    f32 sp18[2];

    sp18[0] = 1.0f;
    sp18[1] = 1.0f;
    func_1513FAB4((u8 *) arg0, 0, sp18, arg1);
}

void func_1513FA70(s32 arg0, s16 arg1) {
    f32 sp18[2];

    sp18[0] = 1.0f;
    sp18[1] = 1.0f;
    func_1513FAB4((u8 *) arg0, 1, sp18, arg1);
}

#ifdef NON_MATCHING
/* P170 */

// beam_quad_build: builds the 4 vertices of a camera-facing beam quad for display list slot `slot`: from the start
// point +0x34/+0x38/+0x3C towards +0x40/+0x44/+0x48, the length scaled by +0x30 x scale[1], the half width
// +0x2C x scale[0] along cross(direction, middle - camera) (func_150ADD90; the camera point from func_15144B34).
// `flip` picks the vertex order (start+, start-, end-, end+ or start-, end-, end+, start+). New vertex buffers from
// func_151D6310 are first filled (both 0x40-byte halves) from the template at +0xC0. Returns the vertices, or NULL
// when there is no buffer. Called by func_1513FA2C (order 0) / func_1513FA70 (order 1).
u8 *func_1513FAB4(u8 *fx, u8 flip, f32 *scale, s16 slot) {
    f32 dir[3];
    f32 end[3];
    f32 toCam[3];
    f32 side[3];
    f32 *cam;
    f32 halfWidth;
    f32 len;
    f32 lenSq;
    f32 s;
    u8 *vtx;
    u8 *start;
    u8 fresh;

    func_151D6310((s32 *) (fx + 0x100), slot, 0x40, (s32 *) &vtx, &fresh);
    start = vtx;
    if (vtx == NULL) {
        return NULL;
    }
    if (fresh) {
        memcpy(*(u8 **) (fx + 0x100 + slot * 4), fx + 0xC0, 0x40);
        memcpy(*(u8 **) (fx + 0x100 + slot * 4) + 0x40, fx + 0xC0, 0x40);
    }
    cam = func_15144B34(slot);
    halfWidth = *(f32 *) (fx + 0x2C) * scale[0];
    len = *(f32 *) (fx + 0x30) * scale[1];
    dir[0] = *(f32 *) (fx + 0x40) - *(f32 *) (fx + 0x34);
    dir[1] = *(f32 *) (fx + 0x44) - *(f32 *) (fx + 0x38);
    dir[2] = *(f32 *) (fx + 0x48) - *(f32 *) (fx + 0x3C);
    dir[0] *= len;
    dir[1] *= len;
    dir[2] *= len;
    end[0] = *(f32 *) (fx + 0x34) + dir[0];
    end[1] = *(f32 *) (fx + 0x38) + dir[1];
    end[2] = *(f32 *) (fx + 0x3C) + dir[2];
    toCam[0] = *(f32 *) (fx + 0x34) + dir[0] * 0.5f - cam[0];
    toCam[1] = *(f32 *) (fx + 0x38) + dir[1] * 0.5f - cam[1];
    toCam[2] = *(f32 *) (fx + 0x3C) + dir[2] * 0.5f - cam[2];
    func_150ADD90((u8 *) dir, (u8 *) toCam, (u8 *) side);
    lenSq = side[0] * side[0] + side[1] * side[1] + side[2] * side[2];
    if (lenSq == 0.0f) {
        side[0] = side[1] = side[2] = 0.0f;
    } else {
        s = halfWidth / sqrtf(lenSq);
        side[0] *= s;
        side[1] *= s;
        side[2] *= s;
    }
    if (flip) {
        *(s16 *) (vtx + 0) = (s32) (*(f32 *) (fx + 0x34) + side[0]);
        *(s16 *) (vtx + 2) = (s32) (*(f32 *) (fx + 0x38) + side[1]);
        *(s16 *) (vtx + 4) = (s32) (*(f32 *) (fx + 0x3C) + side[2]);
        *(s16 *) (vtx + 6) = 0;
        vtx += 0x10;
        *(s16 *) (vtx + 0) = (s32) (*(f32 *) (fx + 0x34) - side[0]);
        *(s16 *) (vtx + 2) = (s32) (*(f32 *) (fx + 0x38) - side[1]);
        *(s16 *) (vtx + 4) = (s32) (*(f32 *) (fx + 0x3C) - side[2]);
        *(s16 *) (vtx + 6) = 0;
        vtx += 0x10;
        *(s16 *) (vtx + 6) = 0;
        *(s16 *) (vtx + 0) = (s32) (end[0] - side[0]);
        *(s16 *) (vtx + 2) = (s32) (end[1] - side[1]);
        *(s16 *) (vtx + 4) = (s32) (end[2] - side[2]);
        vtx += 0x10;
        *(s16 *) (vtx + 6) = 0;
        *(s16 *) (vtx + 0) = (s32) (end[0] + side[0]);
        *(s16 *) (vtx + 2) = (s32) (end[1] + side[1]);
        *(s16 *) (vtx + 4) = (s32) (end[2] + side[2]);
    } else {
        *(s16 *) (vtx + 0) = (s32) (*(f32 *) (fx + 0x34) - side[0]);
        *(s16 *) (vtx + 2) = (s32) (*(f32 *) (fx + 0x38) - side[1]);
        *(s16 *) (vtx + 4) = (s32) (*(f32 *) (fx + 0x3C) - side[2]);
        *(s16 *) (vtx + 6) = 0;
        vtx += 0x10;
        *(s16 *) (vtx + 0) = (s32) (end[0] - side[0]);
        *(s16 *) (vtx + 2) = (s32) (end[1] - side[1]);
        *(s16 *) (vtx + 4) = (s32) (end[2] - side[2]);
        *(s16 *) (vtx + 6) = 0;
        vtx += 0x10;
        *(s16 *) (vtx + 0) = (s32) (end[0] + side[0]);
        *(s16 *) (vtx + 2) = (s32) (end[1] + side[1]);
        *(s16 *) (vtx + 4) = (s32) (end[2] + side[2]);
        *(s16 *) (vtx + 6) = 0;
        vtx += 0x10;
        *(s16 *) (vtx + 0) = (s32) (*(f32 *) (fx + 0x34) + side[0]);
        *(s16 *) (vtx + 2) = (s32) (*(f32 *) (fx + 0x38) + side[1]);
        *(s16 *) (vtx + 4) = (s32) (*(f32 *) (fx + 0x3C) + side[2]);
        *(s16 *) (vtx + 6) = 0;
    }
    return start;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513FAB4.s")
#endif

// sets the texture coordinates of a 4-vertex quad, flipping s/t according to arg2 bits 0/1
void func_1513FFF4(Vtx *arg0, u8 arg1, u8 arg2) {
    struct_eu_80090F10 *entry;
    u16 w;
    u16 h;

    if (arg1 != 0xFF) {
        entry = &D_80090F10[arg1];
        w = entry->unk6 - 1;
        h = entry->unk8 - 1;
        arg0[0].v.tc[0] = arg0[3].v.tc[0] = (arg2 & 1) ? w << 6 : 0;
        arg0[1].v.tc[0] = arg0[2].v.tc[0] = (arg2 & 1) ? 0 : w << 6;
        arg0[0].v.tc[1] = arg0[1].v.tc[1] = (arg2 & 2) ? h << 6 : 0;
        arg0[2].v.tc[1] = arg0[3].v.tc[1] = (arg2 & 2) ? 0 : h << 6;
    }
}


void func_151400D0(Vtx *arg0, struct_eu_vtxcol *arg1) {
    s32 i;

    for (i = 0; i < 4; i++, arg0++, arg1++) {
        arg0->v.flag = arg1->flag;
        arg0->v.cn[0] = arg1->c[0];
        arg0->v.cn[1] = arg1->c[1];
        arg0->v.cn[2] = arg1->c[2];
        arg0->v.cn[3] = arg1->c[3];
        arg0->v.flag = 0;
    }
}

#ifdef NON_MATCHING
/* P143 */
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
// sprite_quad_build_flat: same result as func_1513EE14 (corner quad +-0x2C / +-0x30 rotated by +0x40/+0x44/+0x48,
// translated to +0x34/+0x38/+0x3C, no scale), written as a loop over corners kept in place. New vertex buffers from
// func_151D6310 are first filled (both 0x40-byte halves) from the template at +0xC0. Returns the vertices, or NULL
// when there is no buffer. (Draw-table D_8008A1BC entry.)
u8 *func_15140190(u8 *fx, s16 slot) {
    f32 corner[4][3];
    f32 mtx[4][4];
    u8 *vtx;
    u8 *start;
    u8 fresh;
    u8 i;

    func_151D6310((s32 *)(fx + 0x100), slot, 0x40, (s32 *)&vtx, &fresh);
    start = vtx;
    if (vtx == NULL) {
        return NULL;
    }
    if (fresh) {
        memcpy(*(u8 **)(fx + 0x100 + slot * 4), fx + 0xC0, 0x40);
        memcpy(*(u8 **)(fx + 0x100 + slot * 4) + 0x40, fx + 0xC0, 0x40);
    }
    corner[0][0] = *(f32 *)(fx + 0x2C);
    corner[0][1] = *(f32 *)(fx + 0x30);
    corner[0][2] = 0.0f;
    corner[1][0] = -*(f32 *)(fx + 0x2C);
    corner[1][1] = *(f32 *)(fx + 0x30);
    corner[1][2] = 0.0f;
    corner[2][0] = -*(f32 *)(fx + 0x2C);
    corner[2][1] = -*(f32 *)(fx + 0x30);
    corner[2][2] = 0.0f;
    corner[3][0] = *(f32 *)(fx + 0x2C);
    corner[3][1] = -*(f32 *)(fx + 0x30);
    corner[3][2] = 0.0f;
    func_150A8050(mtx, *(f32 *)(fx + 0x40), *(f32 *)(fx + 0x44), *(f32 *)(fx + 0x48));
    mtx[3][0] = *(f32 *)(fx + 0x34);
    mtx[3][1] = *(f32 *)(fx + 0x38);
    mtx[3][2] = *(f32 *)(fx + 0x3C);
    for (i = 0; i < 4; i++) {
        func_150A7E40(mtx, corner[i][0], corner[i][1], 0.0f, &corner[i][0], &corner[i][1], &corner[i][2]);
        *(s16 *)(vtx + 0) = (s32)corner[i][0];
        *(s16 *)(vtx + 2) = (s32)corner[i][1];
        *(s16 *)(vtx + 4) = (s32)corner[i][2];
        *(s16 *)(vtx + 6) = 0;
        vtx += 0x10;
    }
    return start;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_15140190.s")
#endif

void func_151403A8(s32 arg0, u8 arg1) {
    func_15169260(&D_800A5168, 4, arg0, arg1);
}

void func_151403DC(s32 arg0, u8 arg1) {
    func_15169260(&D_800A5178, 3, arg0, arg1);
}

#ifdef NON_MATCHING
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);

u8 *func_15140410(u8 *arg0, u8 *arg1, u8 *arg2, s16 arg3) {
    struct {
        u8 u47;
        u8 pad48[0x18];
        u8 * u60;
        u8 * u64;
    } sp;
    u8 *sp40;
    s32 sp3C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f2;
    s32 temp_a1;
    u8 *temp_v0;

    func_151D6310(arg0 + 0x100, arg3, 0x40, &sp.u64, &sp.u47);
    sp.u60 = sp.u64;
    if (sp.u64 != NULL) {
        if (sp.u47 != 0) {
            temp_v0 = arg0 + (arg3 * 4);
            temp_a1 = arg0 + 0xC0;
            sp3C = temp_a1;
            sp40 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
        temp_f12 = (*(f32 *)((u8 *)arg1 + 0)) * temp_f0;
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_f14 = (*(f32 *)((u8 *)arg1 + 4)) * temp_f0;
        temp_f16 = (*(f32 *)((u8 *)arg1 + 8)) * temp_f0;
        temp_f18 = (*(f32 *)((u8 *)arg2 + 0)) * temp_f2;
        temp_f20 = (*(f32 *)((u8 *)arg2 + 4)) * temp_f2;
        temp_f22 = (*(f32 *)((u8 *)arg2 + 8)) * temp_f2;
        (*(s16 *)((u8 *)sp.u64 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12 + temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f14 + temp_f20);
        (*(s16 *)((u8 *)sp.u64 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f16 + temp_f22);
        (*(s16 *)((u8 *)sp.u64 + 6)) = 0;
        (*(s16 *)((u8 *)sp.u64 + 0x10)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12) + temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 0x12)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) - temp_f14) + temp_f20);
        (*(s16 *)((u8 *)sp.u64 + 0x14)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f16) + temp_f22);
        (*(s16 *)((u8 *)sp.u64 + 0x16)) = 0;
        (*(s16 *)((u8 *)sp.u64 + 0x20)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12) - temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 0x22)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) - temp_f14) - temp_f20);
        (*(s16 *)((u8 *)sp.u64 + 0x24)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f16) - temp_f22);
        (*(s16 *)((u8 *)sp.u64 + 0x26)) = 0;
        (*(s16 *)((u8 *)sp.u64 + 0x30)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12) - temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 0x32)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f14) - temp_f20);
        (*(s16 *)((u8 *)sp.u64 + 0x34)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f16) - temp_f22);
        (*(s16 *)((u8 *)sp.u64 + 0x36)) = 0;
        return sp.u60;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_15140410.s")
#endif
#ifdef NON_MATCHING
#define L6AC_PREV(n) (*(u8 **)((n) + 4))
#define L6AC_NEXT(n) (*(u8 **)((n) + 8))
#define L6AC_KEY(n) (((n)[0x18] << 8) + (*(s32 *)((n) + 0x20) >> 16))

/* Insertion sort of scene-node list D_800DD280[group][idx] by key (+0x18 << 8) + (+0x20 >> 16), ascending, stable;
 * a node moves behind the last earlier node whose key is not greater. A stack node stands in for the list head
 * (key 0, no prev); as in the asm the head's prev is set before the NULL test and the first node's prev is cleared
 * at the end, so an empty list writes word 4. `skip` != 0: nothing. Returns `ret` (a0) unchanged. */
s32 func_151406AC(s32 ret, s32 idx, s32 group, s16 skip) {
    s32 dummy[9];
    u8 *d = (u8 *)dummy;
    u8 **slot;
    u8 *head;
    u8 *node;
    u8 *prev;
    u8 *next;
    u8 *at;
    s32 key;

    if (skip != 0) {
        return ret;
    }
    slot = (u8 **)((u8 *)D_800DD280 + group * 0x1A0 + idx * 4);   /* D_800DD280[2][104] list heads */
    head = *slot;
    d[0x18] = 0;
    dummy[8] = 0;
    L6AC_PREV(d) = NULL;
    L6AC_NEXT(d) = head;
    L6AC_PREV(head) = d;
    if (head != NULL) {
        for (node = L6AC_NEXT(head); node != NULL; node = next) {
            key = L6AC_KEY(node);
            prev = L6AC_PREV(node);
            next = L6AC_NEXT(node);
            for (at = prev; at != NULL; at = L6AC_PREV(at)) {
                if (!(key < L6AC_KEY(at))) {
                    break;
                }
            }
            if (at == NULL || at == prev) {
                continue;
            }
            L6AC_NEXT(prev) = next;
            if (L6AC_NEXT(node) != NULL) {
                L6AC_PREV(L6AC_NEXT(node)) = L6AC_PREV(node);
            }
            L6AC_NEXT(node) = L6AC_NEXT(at);
            if (L6AC_NEXT(node) != NULL) {
                L6AC_PREV(L6AC_NEXT(node)) = node;
            }
            L6AC_PREV(node) = at;
            L6AC_NEXT(at) = node;
        }
    }
    *slot = L6AC_NEXT(d);
    L6AC_PREV(L6AC_NEXT(d)) = NULL;
    return ret;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_151406AC.s")
#endif