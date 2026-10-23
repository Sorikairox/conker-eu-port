#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_151AD010
s32 func_151AD0E8(u8 *, u8 *);


#ifdef NON_MATCHING
/* P155 */
u8 func_151D8E20(void);
void func_1514CBE8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9,
                   s32 argA, u8 argB);
void func_151DBE80(s32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, s32 arg5, u8 arg6, u8 arg7, u8 arg8, s32 arg9);
typedef struct {
    f32 size;         /* 0x0 */
    s16 count;        /* 0x4 */
    u16 countRange;   /* 0x6 */
} DebrisDefAC3F0;
typedef struct {
    f32 u0;           /* 0x0 */
    s16 u4;           /* 0x4 */
    f32 u8;           /* 0x8 */
} FlashDefAC3F0;
extern s8 D_800A9400[][5];          /* per kind: chunk def, dust def, flash def (-1 = none) */
extern DebrisDefAC3F0 D_800A9420[]; /* chunks (type 0xB) */
extern DebrisDefAC3F0 D_800A9538[]; /* dust (type 0xC) */
extern FlashDefAC3F0 D_800A963C[];  /* flash */

// debris_burst_spawn: P153: the debris of a broken object of `kind` at pos (src = the owner): per D_800A9400[kind]
// a chunk burst (func_1514CBE8 type 0xB, def D_800A9420) and a dust burst (type 0xC, D_800A9538) with count
// +4 + random [0, +6], each with the owner block {src, arg4, light} (light = func_151D8E20()), and when src +0x1C
// bit 0 is set a flash (func_151DBE80, D_800A963C, 150) at pos, src + 4.
void func_151AC3F0(f32 *pos, u8 *src, s32 kind, u8 arg3, s32 arg4) {
    struct {
        u8 *src;
        s32 arg;
        u8 light;
    } chunkOwner, dustOwner;
    s8 *def;
    DebrisDefAC3F0 *d;
    FlashDefAC3F0 *fl;
    u8 light;

    light = func_151D8E20();
    if (src == NULL) {
        return;
    }
    def = D_800A9400[kind];
    if (def[0] != -1) {
        chunkOwner.src = src;
        chunkOwner.light = light;
        chunkOwner.arg = arg4;
        d = &D_800A9420[def[0]];
        func_1514CBE8(pos[0], pos[1], pos[2], d->size, 0, 0xFF, (u32) func_150ADA20() % (u32) (d->countRange + 1) + d->count,
                      0xB, kind, 0.0f, (s32) &chunkOwner, arg3);
    }
    if (def[2] != -1) {
        dustOwner.src = src;
        dustOwner.arg = arg4;
        dustOwner.light = light;
        d = &D_800A9538[def[2]];
        func_1514CBE8(pos[0], pos[1], pos[2], d->size, 0, 0xFF, (u32) func_150ADA20() % (u32) (d->countRange + 1) + d->count,
                      0xC, kind, 0.0f, (s32) &dustOwner, arg3);
    }
    if (def[4] != -1 && (src[0x1C] & 1)) {
        fl = &D_800A963C[def[4]];
        func_151DBE80(light, fl->u0, fl->u8, fl->u4, (u8 *) pos, (s32) (src + 4), 0x96, 0, arg3, arg4);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AC3F0.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AC628.s")

s32 func_151AC97C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 var_v1 = *(s16 *)(arg0 + 0x1C) * 8;

    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < temp_v0[0x1B]) {
        temp_v0[0x1B] = var_v1;
    }
    return 1;
}

typedef struct { f32 x, y, z; s32 a, b; } Node14;
u8 func_151D8E20(void);
void func_151DAB58(u8, f32, u8, f32 *, u8, u8, s32);
s32 func_151AC9B8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    u8 *tbl;
    u8 *obj;
    f32 pos[3];
    u8 id;

    tbl = *(u8 **)(arg0 + 0x94);
    obj = *(u8 **)(arg0 + 0x98);
    pos[0] = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].x;
    pos[1] = arg4;
    pos[2] = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].z;
    id = func_151D8E20();
    if (func_150ADA20() & 1) {
        func_151D9B8C(id, *(f32 *)(obj + 0) * 6.0f, *(u8 *)(obj + 0x1B), arg5, (struct17 *)pos, func_150ADA20() % 41U + 0x50, 1, 1, 0, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
    } else {
        func_151DAB58(id, *(f32 *)(obj + 0) * 1.5f, *(u8 *)(obj + 0x1B), pos, 1, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
    }
    *(s8 *)(obj + 0x20) = 4;
    return 1;
}

s32 func_151ACB00(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    u8 *sp44;
    f32 (*tab)[5];
    f32 sp34[3];
    sp44 = *(u8 **)(arg0 + 0x98);
    tab = *(f32 (**)[5])(arg0 + 0x94);
    sp34[0] = tab[*(s8 *)(arg0 + 0x2D)][0];
    sp34[1] = arg4;
    sp34[2] = tab[*(s8 *)(arg0 + 0x2D)][2];
    func_151DBCBC(func_151D8E20(), *(f32 *)(sp44 + 0) * 7.0f, *(u8 *)(sp44 + 0x1B), arg5, sp34, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
    *(s8 *)(sp44 + 0x20) = 4;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151ACBCC.s")

s32 func_151D6310(s32, s16, s32, u8 **, u8 *);
extern f32 D_800DD608[];
extern f32 D_800DD618[];

u8 *func_151ACDC0(u8 *arg0, s16 arg1) {
    u8 *sp4C;
    u8 *sp48;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f14;
    u8 sp37;

    func_151D6310((s32)(arg0 + 0x100), arg1, 0x40, &sp4C, &sp37);
    sp48 = sp4C;
    if (sp4C != NULL) {
        if (sp37 != 0) {
            memcpy(((u8 **)(arg0 + 0x100))[arg1], arg0 + 0xC0, 0x40);
            memcpy(((u8 **)(arg0 + 0x100))[arg1] + 0x40, arg0 + 0xC0, 0x40);
        }
    } else {
        return NULL;
    }
    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x4C)) * (*(f32 *)((u8 *)arg0 + 0x2C));
    temp_f14 = (*(f32 *)((u8 *)arg0 + 0x50)) * (*(f32 *)((u8 *)arg0 + 0x30));
    temp_f2 = D_800DD608[arg1] * temp_f0;
    temp_f12 = D_800DD618[arg1] * temp_f0;
    *(s16 *)(sp4C + 6) = 0;
    *(s16 *)(sp4C + 0x16) = 0;
    *(s16 *)(sp4C + 0x26) = 0;
    *(s16 *)(sp4C + 0x36) = 0;
    *(s16 *)(sp4C + 0) = *(s16 *)(sp4C + 0x30) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12);
    *(s16 *)(sp4C + 2) = *(s16 *)(sp4C + 0x12) = (s32) (*(f32 *)((u8 *)arg0 + 0x38));
    *(s16 *)(sp4C + 4) = *(s16 *)(sp4C + 0x34) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f2);
    *(s16 *)(sp4C + 0x10) = *(s16 *)(sp4C + 0x20) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12);
    *(s16 *)(sp4C + 0x22) = *(s16 *)(sp4C + 0x32) = (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f14);
    *(s16 *)(sp4C + 0x14) = *(s16 *)(sp4C + 0x24) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f2);
    return sp48;
}

s32 func_151ACF9C(f32 *arg0) {
    f32 temp_f0 = arg0[0x4C / 4] * D_800BE9A4;

    arg0[0x2C / 4] += temp_f0;
    arg0[0x30 / 4] += temp_f0;
    return 1;
}

s32 func_151ACFD0(u8 *arg0) {
    s32 var_v0 = 0xFF;
    s16 temp_v1 = *(s16 *)(arg0 + 0x1C);

    if (temp_v1 < 0x10) {
        var_v0 = (s16)(temp_v1 * 16);
    }
    if (var_v0 < arg0[0x5C]) {
        arg0[0x5C] = var_v0;
    }
    return 1;
}

u8 *func_151AD010(u8 *arg0, f32 arg1, s32 arg2) {
    u8 *temp_v0;

    if (arg0 == NULL) {
        return NULL;
    }
    temp_v0 = func_15167A68(0x30, 0, arg2 + 0x30, 1, 0xFFU, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    if (func_151AD0E8(arg0, temp_v0 + 0x18) == 0) {
        func_1516979C((struct102 *)temp_v0);
        return NULL;
    }
    *(u8 **)(temp_v0 + 0x1C) = arg0;
    temp_v0[0x20] = arg0[0x3B];
    *(s32 *)(temp_v0 + 0x24) = (struct127 *)arg0 - D_800CC2D0;
    *(f32 *)(temp_v0 + 0x28) = arg1;
    *(s32 *)(temp_v0 + 0x10) = 1;
    *(s32 *)(temp_v0 + 0x14) = 0;
    return temp_v0;
}

s32 func_151AD0E8(u8 *arg0, u8 *arg1) {
    s32 ret = 0;

    if (arg0[0x3B] == 1) {
        *arg1 = 1;
        ret = 1;
    }
    return ret;
}

#ifdef NON_MATCHING
void func_151AE958(u8 *arg0);
#else
s32 func_151AE958();
#endif

void func_151AD110(u8 *arg0) {
    s32 temp = *(s32 *)(*(u8 **)(*(u8 **)(arg0 + 0x1C) + 0x31C) + 0x9C);
    if (temp != 0) {
        func_151AE958(arg0);
    }
    if (arg0) {} // keeps arg0 live past the call (home-slot store); likely a stripped debug macro
}

void func_151AD144(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x1C), (s32)(arg0 + 0x20), (s32)arg0);
}

#ifdef NON_MATCHING
/* P183 */
void *allocate_memory(s32, s32, s32, s32);

// light_column_create: P183: creates the light-column effect (func_15167A68 kind 0x4E in level 0x2C, else 0x2F;
// layer arg1 + 0x58) from the 0x24-byte zone record arg0 (copied to +0x10: point +0x14..+0x1C, bottom y +0x24,
// +0x2C scale -> +0x34 = 1 / scale). +0x38 = 20 points (0x18 bytes) up the column from y = bottom to the top
// (+0x18) in 19 steps at the point's x / z, +0x3C = step height, +0x48 = 2 x 20 quads of 4 Vtx (texture 0x37 in
// level 0xB, else 0x36: s = 0 / w/4 / w/2 / 3w/4 (+0x100, << 5), t = (0x100 + i * (h - 1)) << 5 (<< 4 for 0x37),
// flag 0, colour (0x58, 0x4B, 0x2C) in level 0x39 else white, alpha 0xFF). Returns the effect (0 without one).
s32 func_151ACBD4(s8 *arg0, s32 arg1) {
    u8 *e;
    f32 *pt;
    Vtx *v;
    s32 x, top, bottom, z, dy;
    s32 i, k;
    s32 shift;
    s32 tw, th;
    s32 t;
    s32 s1, s2, s3;
    u8 r, g, b;
    struct_eu_80090F10 *tex;

    e = func_15167A68((D_800BE9F0 == 0x2C) ? 0x4E : 0x2F, 0, arg1 + 0x58, 1, 0xFF, 1);
    if (e == NULL) {
        return 0;
    }
    memcpy(e + 0x10, arg0, 0x24);
    *(s32 *) (e + 0x44) = 0;
    *(s16 *) (e + 0x52) = 0;
    *(f32 *) (e + 0x34) = 1.0f / *(f32 *) (e + 0x2C);
    *(f32 **) (e + 0x38) = allocate_memory(0x1E0, 1, 0, 0);
    x = *(f32 *) (e + 0x14);
    top = *(f32 *) (e + 0x18);
    z = *(f32 *) (e + 0x1C);
    bottom = *(f32 *) (e + 0x24);
    e[0x42] = 20;
    dy = top - bottom;
    for (i = 0; i < 20; i++) {
        pt = *(f32 **) (e + 0x38) + i * 6;
        pt[0] = x;
        pt[1] = (dy * i) / 19 + bottom;
        pt[2] = z;
        pt[3] = 0.0f;
        pt[4] = 0.0f;
        pt[5] = 0.0f;
    }
    *(f32 *) (e + 0x3C) = (f32) (top - bottom) / 19.0f;
    *(Vtx **) (e + 0x48) = allocate_memory(0xA00, 1, 2, 0);

    if (D_800BE9F0 == 0xB) {
        *(u16 *) (e + 0x40) = 0x37;
        shift = 4;
    } else {
        *(u16 *) (e + 0x40) = 0x36;
        shift = 5;
    }
    if (D_800BE9F0 == 0x39) {
        r = 0x58;
        g = 0x4B;
        b = 0x2C;
    } else {
        r = 0xFF;
        g = 0xFF;
        b = 0xFF;
    }
    tex = &D_80090F10[*(u16 *) (e + 0x40)];
    tw = tex->unk6 >> 2;
    th = tex->unk8 - 1;
    s1 = (tw + 0x100) << 5;
    s2 = (tw * 2 + 0x100) << 5;
    s3 = (tw * 3 + 0x100) << 5;
    for (k = 0; k < 2; k++) {
        v = *(Vtx **) (e + 0x48) + k * 80;
        t = 0x100;
        for (i = 0; i < 20; i++, v += 4) {
            s32 tt = t << shift;

            t += th;
            v[0].v.flag = 0;
            v[0].v.tc[0] = 0x2000;
            v[0].v.tc[1] = tt;
            v[0].v.cn[0] = r;
            v[0].v.cn[1] = g;
            v[0].v.cn[2] = b;
            v[0].v.cn[3] = 0xFF;
            v[1].v.flag = 0;
            v[1].v.tc[0] = s1;
            v[1].v.tc[1] = tt;
            v[1].v.cn[0] = r;
            v[1].v.cn[1] = g;
            v[1].v.cn[2] = b;
            v[1].v.cn[3] = 0xFF;
            v[2].v.flag = 0;
            v[2].v.tc[0] = s2;
            v[2].v.tc[1] = tt;
            v[2].v.cn[0] = r;
            v[2].v.cn[1] = g;
            v[2].v.cn[2] = b;
            v[2].v.cn[3] = 0xFF;
            v[3].v.flag = 0;
            v[3].v.tc[0] = s3;
            v[3].v.tc[1] = tt;
            v[3].v.cn[0] = r;
            v[3].v.cn[1] = g;
            v[3].v.cn[2] = b;
            v[3].v.cn[3] = 0xFF;
        }
    }
    *(f32 *) (e + 0x4C) = 0.0f;
    return (s32) e;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151ACBD4.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AD724.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151ADEDC.s")

void func_151AE814(u8 *);
void func_151AE694(u8 *, u8);
void func_151AE61C(u8 *arg0, u8 *arg1) {
    u8 sp1F;
    u8 a;
    u8 sp1E;
    if (func_151AD0E8(arg0, &sp1F) != 0) {
        a = arg1[0x1B];
        if ((*(u8 **)(arg0 + 0x31C))[0x98] == 0) {
            func_151AE694(arg0, a);
        } else if (a != (*(u8 **)(arg0 + 0x31C))[0x98]) {
            sp1E = a;
            func_151AE814(arg0);
            func_151AE694(arg0, sp1E);
        }
    }
}

#ifdef NON_MATCHING
/* P150 */
struct_eu_node *func_151AEB40(s32);
void func_151AE86C(f32 *, u8 *, s32, f32);
// path_try_attach: attaches obj to path node `id` (func_151AEB40; the original hangs when there is none, the port returns) unless the
// path is busy (+0x52), obj cannot ride (+0x1CA == 0) or is busy (+0x104). The rider record (+0x31C) gets its
// progress along the path at +0xA0 (func_151AE86C from obj's height); when the path point at that progress
// (points +0x38, 24 bytes each, count +0x42, spacing +0x3C, 140 units kept free at the end) is within 100 units
// of obj, the record takes the path (+0x98 id, +0x9C path), obj state +0x8A = 0x12 and the path's rider +0x44 = obj.
void func_151AE694(u8 *obj, u8 id) {
    u8 *path;
    u8 *rec;
    f32 *point;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 spare;
    s32 index;

    path = (u8 *)func_151AEB40(id);
    if (path == NULL) {
        // Deliberate port divergence (coordinator decision, P155): the N64 code spins here forever (the console
        // hangs) when no path object with this id is spawned. In the port that would freeze the browser tab, so
        // the attach is simply skipped. The NM build has no port log hook to report it; the normal path is
        // unchanged.
        return;
    }
    if (*(s16 *)(path + 0x52) != 0 || obj[0x1CA] == 0 || obj[0x104] != 0) {
        return;
    }
    func_151AE86C((f32 *)(*(u8 **)(obj + 0x31C) + 0xA0), path, *(s32 *)(obj + 0x14), *(f32 *)(obj + 0x18));
    spare = 140.0f / *(f32 *)(path + 0x3C);
    rec = *(u8 **)(obj + 0x31C);
    index = (f32)(path[0x42] - spare - 1) * *(f32 *)(rec + 0xA0);
    point = (f32 *)(*(u8 **)(path + 0x38) + index * 24);
    dx = point[0] - *(f32 *)(obj + 0x14);
    dy = point[1] - *(f32 *)(obj + 0x18);
    dz = point[2] - *(f32 *)(obj + 0x1C);
    if (dz * dz + (dx * dx + dy * dy) > 10000.0f) {
        return;
    }
    (*(u8 **)(obj + 0x31C))[0x98] = id;
    obj[0x8A] = 0x12;
    *(u8 **)(*(u8 **)(obj + 0x31C) + 0x9C) = path;
    *(u8 **)(path + 0x44) = obj;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AE694.s")
#endif

void func_151AE814(u8 *arg0) {
    u8 *temp_v0;
    f32 f;

    temp_v0 = (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x9C));
    f = (*(f32 *)((u8 *)arg0 + 0x3C)) * 0.89f;
    (*(f32 *)((u8 *)temp_v0 + 0x4C)) = f;
    (*(u8 *)((u8 *)temp_v0 + 0x50)) = (*(u16 *)((u8 *)arg0 + 0x76)) >> 8;
    (*(u8 *)((u8 *)temp_v0 + 0x51)) = (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0xAE));
    (*(s16 *)((u8 *)temp_v0 + 0x52)) = 0x14;
    (*(s32 *)((u8 *)temp_v0 + 0x44)) = 0;
    (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x98)) = 0;
    (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x9C)) = NULL;
}

#ifdef NON_MATCHING
void func_151AE86C(f32 *arg0, u8 *arg1, s32 arg2, f32 arg3) {
    f32 temp_f0;
    f32 temp_f2;
    f32 var_f0;
    s32 temp_a2;
    s32 var_v1;
    u8 temp_v0;
    u8 *temp_a0;
    u8 *var_a0;

    temp_v0 = (*(u8 *)((u8 *)arg1 + 0x42));
    var_v1 = 0;
    temp_a2 = temp_v0 - 1;
    if (temp_a2 > 0) {
        var_a0 = (*(u8 **)((u8 *)arg1 + 0x38));
loop_2:
        if (!(arg3 <= (*(f32 *)((u8 *)var_a0 + 4)))) {
            var_v1 += 1;
            var_a0 += 0x18;
            if (var_v1 != temp_a2) {
                goto loop_2;
            }
        }
    }
    if (var_v1 >= (temp_v0 - 2)) {
        *arg0 = 1.0f;
        return;
    }
    if (var_v1 == 0) {
        *arg0 = 0.0f;
        return;
    }
    temp_a0 = (*(u8 **)((u8 *)arg1 + 0x38)) + (var_v1 * 0x18);
    temp_f2 = (*(f32 *)((u8 *)temp_a0 + -0x14));
    temp_f0 = (*(f32 *)((u8 *)temp_a0 + 4)) - temp_f2;
    if (temp_f0 != 0.0f) {
        var_f0 = (arg3 - temp_f2) / temp_f0;
    } else {
        var_f0 = 0.0f;
    }
    *arg0 = ((f32) (var_v1 - 1) / (f32) (temp_v0 - 3)) + (var_f0 / (f32) temp_a2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AE86C.s")
#endif
#ifdef NON_MATCHING
/* P153 */
s32 func_15143E08(struct127 *arg0);
f32 func_151423D8(u8);
// path_ride_place: P153: places the rider obj (arg0 + 0x1C) on its path (record +0x31C, path +0x9C): the rider's
// progress (+0xA0) picks a segment of the path points (+0x38, 24 bytes each, count +0x42, 140 units kept free at
// the end as in func_151AE694); the record's +0xAE gets the segment index, and obj's position becomes the point
// between that segment's two ends, moved sideways by arg0 +0x28 along obj's yaw (func_15143E08) - 0x80.
void func_151AE958(u8 *arg0) {
    u8 *obj;
    u8 *path;
    u8 *rec;
    f32 *p;
    f32 oldX;
    f32 oldY;
    f32 oldZ;
    f32 side;
    f32 sinYaw;
    f32 cosYaw;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    s32 spare;
    s32 index;
    u8 yaw;

    obj = *(u8 **) (arg0 + 0x1C);
    path = *(u8 **) (*(u8 **) (obj + 0x31C) + 0x9C);
    yaw = func_15143E08((struct127 *) obj) - 0x80;
    sinYaw = func_151423D8((yaw - 0x40) & 0xFF);
    cosYaw = func_151423D8(yaw);
    rec = *(u8 **) (obj + 0x31C);
    oldY = *(f32 *) (obj + 0x18);
    oldX = *(f32 *) (obj + 0x14);
    side = *(f32 *) (arg0 + 0x28);
    oldZ = *(f32 *) (obj + 0x1C);
    spare = 140.0f / *(f32 *) (path + 0x3C);
    index = (f32) (path[0x42] - spare - 1) * *(f32 *) (rec + 0xA0);
    rec[0xAE] = index;
    t = (f32) (path[0x42] - spare - 1) * *(f32 *) (rec + 0xA0) - (f32) index;
    p = (f32 *) (*(u8 **) (path + 0x38) + index * 24);
    x = (p[6] - p[0]) * t + p[0] + side * sinYaw;
    y = (p[7] - p[1]) * t + p[1];
    z = (p[8] - p[2]) * t + p[2] + side * cosYaw;
    *(f32 *) (obj + 0x14) = (x - oldX) + oldX;
    *(f32 *) (obj + 0x18) = (y - oldY) + oldY;
    *(f32 *) (obj + 0x1C) = (z - oldZ) + oldZ;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AE958.s")
#endif

#ifdef NON_MATCHING
extern s32 D_800A9650;

struct_eu_node *func_151AEB40(s32 arg0) {
    s32 temp_t4;
    s32 temp_t5;
    s32 var_v0;
    s32 var_v1;
    struct_eu_node *temp_a2;
    struct_eu_node *var_a0;

    var_v0 = 0;
loop_1:
    var_v1 = 0;
loop_2:
    var_a0 = D_800DD280[var_v1][*(s32 *)((u8 *)&D_800A9650 + (var_v0 * 4))];
    temp_t4 = (var_v1 + 1) & 0xFF;
    if (var_a0 != NULL) {
loop_3:
        temp_a2 = var_a0->next;
        if ((arg0 & 0xFF) == (*(u8 *)((u8 *)var_a0 + 0x10))) {
            return var_a0;
        }
        var_a0 = temp_a2;
        if (temp_a2 == NULL) {
            goto block_6;
        }
        goto loop_3;
    }
block_6:
    var_v1 = temp_t4;
    if (temp_t4 >= 2) {
        temp_t5 = (var_v0 + 1) & 0xFF;
        var_v0 = temp_t5;
        if (temp_t5 >= 2) {
            return NULL;
        }
        goto loop_1;
    }
    goto loop_2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AEB40.s")
#endif
void func_151AEBF0(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 a;
  if (arg2 == 0) {
    a = arg1[0];
    if (a == *(s32 *)(arg0 + 0x44)) {
      s32 *p = (s32 *)(arg0 + 0x44); // a declaration in the arm = basic-block boundary (unfilled jr ra delay slot, s69)
      *p = 0;
    }
    return;
  }
  if (arg2 == 0x2D) {
    a = arg1[0];
    if (a == *(s32 *)(arg0 + 0x44)) { *(s32 *)(arg0 + 0x44) = arg1[1]; return; }
    if (arg1[1] == *(s32 *)(arg0 + 0x44)) { *(s32 *)(arg0 + 0x44) = a; }
  }
}
