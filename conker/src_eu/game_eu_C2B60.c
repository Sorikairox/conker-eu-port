#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 func_15095F18(s32, f32, f32, f32, s32, s32 *);
#endif

Gfx *func_15095350(Gfx *arg0) {
    gSPDisplayList(arg0++, D_80087770);
    D_800D30C0 = 0;
    return arg0;
}

void func_15095470(s32, s32, s32);
s32 func_150954E4(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800D30B0;

#ifdef NON_MATCHING
/* NON_MATCHING: the matching void wrappers return the callee's v0 (the new display-list pointer), which callers use. */
s32 func_15095380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    func_15095470(arg1, arg2, arg3);
    return func_150954E4(arg0, &D_800D30B0, arg4, arg5, 0, arg6, arg7, 0x100, 0x100, arg8);
}
#else
void func_15095380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    func_15095470(arg1, arg2, arg3);
    func_150954E4(arg0, &D_800D30B0, arg4, arg5, 0, arg6, arg7, 0x100, 0x100, arg8);
}
#endif

void func_15095470(s32, s32, s32);
s32 func_150954E4(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800D30B0;

#ifdef NON_MATCHING
/* NON_MATCHING: the matching void wrappers return the callee's v0 (the new display-list pointer), which callers use. */
s32 func_150953F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    func_15095470(arg1, arg2, arg3);
    return func_150954E4(arg0, &D_800D30B0, arg4, arg5, 0, arg6, arg7, arg8, arg9, argA);
}
#else
void func_150953F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    func_15095470(arg1, arg2, arg3);
    func_150954E4(arg0, &D_800D30B0, arg4, arg5, 0, arg6, arg7, arg8, arg9, argA);
}
#endif

void func_15095470(s32 arg0, s32 arg1, s32 arg2) {
    u32 temp_v0;
    if (arg2 != 0) {
        (*(s32 **)((u8 *)arg2 + 0x10)) = &D_800D30B0;
    }
    temp_v0 = (*(u32 *)((u8 *)arg0 + 0));
    if (temp_v0 < 0x10000000U) {
        (*(s32 *)((u8 *)(&D_800D30B0) + 0)) = (s32) temp_v0;
    } else {
        (*(s32 *)((u8 *)(&D_800D30B0) + 0)) = *(s32 *)((u8 *)((s32)temp_v0 + ((arg1 >> 8) * 4)));
    }
    (*(u16 *)((u8 *)(&D_800D30B0) + 4)) = (u16) (*(u16 *)((u8 *)arg0 + 6));
    (*(u16 *)((u8 *)(&D_800D30B0) + 6)) = (u16) (*(u16 *)((u8 *)arg0 + 8));
    (*(u8 *)((u8 *)(&D_800D30B0) + 8)) = (u8) (*(u8 *)((u8 *)arg0 + 0xA));
    (*(u8 *)((u8 *)(&D_800D30B0) + 9)) = (u8) (*(u8 *)((u8 *)arg0 + 0xB));
    (*(u8 *)((u8 *)(&D_800D30B0) + 0xA)) = (u8) (*(u8 *)((u8 *)arg0 + 4));
}

#ifdef NON_MATCHING
/* Texture loader behind func_15095380 / func_150953F8 (the sky quad, sprites, ...): appends the display-list
 * commands that load the texture `tex` into TMEM at `tmem` and set up render tile `tile`, and returns the new
 * display-list end. `tex` is the descriptor func_15095470 fills (D_800D30B0): +0 address, or an asset id below
 * 0x10000000 that the texture cache resolves (func_1510D66C with `age`), +4 width, +6 height, +8 format (G_IM_FMT_*;
 * 5 = RGBA texels followed by an I4 plane that goes to tile + 1), +9 texel size (G_IM_SIZ_*), +0xA animated flag
 * (`frame` selects one of several equal textures stored after each other; 0 when not animated). The address used
 * is kept in D_800D30C0. Clamp / mirror `cm` applies to s and t; the tile rectangle starts at (uls, ult) with the
 * s fraction `sfrac` (10.2). For CI textures the palette after the texels is loaded too (D_800D30BC = 0x8000,
 * the CI flag for the caller's render mode; 0 otherwise). Note the I4 tile's ult is not shifted by 2 (as the
 * original). */
s32 func_1510D66C(s32 id, s32 *outSize, s32 age, s32 addRef);
extern s32 D_800D30BC;

static const u8 s954E4_incr[4] = { G_IM_SIZ_4b_INCR, G_IM_SIZ_8b_INCR, G_IM_SIZ_16b_INCR, G_IM_SIZ_32b_INCR };
static const u8 s954E4_shift[4] = { G_IM_SIZ_4b_SHIFT, G_IM_SIZ_8b_SHIFT, G_IM_SIZ_16b_SHIFT, G_IM_SIZ_32b_SHIFT };
static const u8 s954E4_lineBytes[4] = { 1, 1, 2, 2 };   /* D_8009E288: line = (bytes * lineW + 7) / 8 */
static const u8 s954E4_loadSiz[4] = { G_IM_SIZ_4b_LOAD_BLOCK, G_IM_SIZ_8b_LOAD_BLOCK, G_IM_SIZ_16b_LOAD_BLOCK,
                                      G_IM_SIZ_32b_LOAD_BLOCK };

s32 func_150954E4(s32 gfxAddr, s32 *tex, s32 tmem, s32 tile, s32 frame, s32 sfrac, s32 cm, s32 uls, s32 ult,
                  s32 age) {
    Gfx *gfx = (Gfx *)gfxAddr;
    u8 *t = (u8 *)tex;
    s32 width, height, fmt, siz, imgFmt;
    s32 texels, words, lineW, masks, maskt, n, line, lrs, lrt, ulsFixed;
    s32 addr;
    s32 palBits, palCount;

    if (t[0xA] == 0) {
        frame = 0;
    }
    width = *(u16 *)(t + 4);
    height = *(u16 *)(t + 6);
    siz = t[9];
    texels = width * height;
    words = s954E4_incr[siz] + texels;
    if (t[8] == 5) {
        words += texels / 4;   /* the I4 plane */
    }
    words >>= s954E4_shift[siz];

    addr = *(s32 *)t;
    D_800D30C0 = addr;
    if ((u32)addr < 0x10000000) {
        D_800D30C0 = func_1510D66C(addr, NULL, age, 0);
        addr = D_800D30C0;
    }
    if (addr != (s32)0x80000000) {
        D_800D30C0 = addr + words * 2 * frame;
    }

    lineW = (siz == G_IM_SIZ_4b) ? width >> 1 : width;
    for (masks = 1, n = 2; n < width; n <<= 1) {
        masks++;
    }
    for (maskt = 1, n = 2; n < height; n <<= 1) {
        maskt++;
    }
    fmt = t[8];
    imgFmt = (fmt == 5) ? G_IM_FMT_RGBA : fmt;

    gDPPipeSync(gfx++);
    gDPSetTextureImage(gfx++, imgFmt, s954E4_loadSiz[t[9]], 1, D_800D30C0);
    gDPSetTile(gfx++, imgFmt, s954E4_loadSiz[t[9]], 0, tmem, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
    gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, words - 1, 0);
    siz = t[9];
    line = (s954E4_lineBytes[siz] * lineW + 7) >> 3;
    gDPSetTile(gfx++, imgFmt, siz, line, tmem, tile, 0, cm, maskt, 0, cm, masks, 0);
    ulsFixed = uls * 4 + sfrac;
    lrs = (*(u16 *)(t + 4) + uls - 1) * 4 + sfrac;
    lrt = (*(u16 *)(t + 6) + ult - 1) * 4;
    gDPSetTileSize(gfx++, tile, ulsFixed, ult * 4, lrs, lrt);
    if (t[8] == 5) {
        line = (s954E4_lineBytes[G_IM_SIZ_4b] * (lineW >> 1) + 7) >> 3;
        gDPSetTile(gfx++, G_IM_FMT_I, G_IM_SIZ_4b, line, tmem + lineW * *(u16 *)(t + 6) / 4, tile + 1, 0, cm, maskt,
                   0, cm, masks, 0);
        lrs = (*(u16 *)(t + 4) + uls - 1) * 4 + sfrac;
        lrt = (*(u16 *)(t + 6) + ult - 1) * 4;
        gDPSetTileSize(gfx++, tile + 1, ulsFixed, ult, lrs, lrt);
    }
    if (t[8] == G_IM_FMT_CI) {
        if (t[9] == G_IM_SIZ_4b) {
            palBits = 4;
            palCount = 15;
        } else {
            palBits = 8;
            palCount = 255;
        }
        gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1,
                           D_800D30C0 + *(u16 *)(t + 4) * *(u16 *)(t + 6) * palBits / 8);
        gDPLoadSync(gfx++);
        gDPLoadTLUTCmd(gfx++, 6, palCount);
        D_800D30BC = 0x8000;
    } else {
        D_800D30BC = 0;
    }
    return (s32)gfx;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_150954E4.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095A4C.s")

#ifdef NON_MATCHING
s32 func_15095A4C(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32);

u8 *func_15095B70(u8 *arg0, u8 *arg1) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
    } sp;
    u8 *temp_a0;
    u8 *temp_t0;

    if (func_15095A4C((f32) (*(s16 *)((u8 *)arg1 + 0)), (f32) (*(s16 *)((u8 *)arg1 + 2)), (f32) (*(s16 *)((u8 *)arg1 + 4)), &sp.u44, &sp.u40, &sp.u3C, &sp.u38, 4000.0f) == 0) {
        return arg0;
    }
    (*(s32 *)((u8 *)arg0 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    temp_a0 = arg0 + 8;
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xEE000000;
    temp_t0 = D_800BE628 + (D_80082FA4 * 0x180) + (D_800BE9C0 * 0x10);
    (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) ((s32) (((f32) (*(s16 *)((u8 *)temp_t0 + 0x4C)) + ((sp.u3C / sp.u38) * (f32) (*(s16 *)((u8 *)temp_t0 + 0x44)))) * 32.0f) << 0x10);
    return func_15095EA0((s32) (temp_a0 + 8), (s32) arg1, sp.u44, sp.u40, sp.u38, 1, 0, 0, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095B70.s")
#endif
#ifdef NON_MATCHING
s32 func_15095A4C(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32);

u8 *func_15095CC0(u8 *arg0, u8 *arg1, s32 *arg2) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
    } sp;
    u8 *temp_s0;
    u8 *var_s0;

    var_s0 = arg0;
    if (func_15095A4C((f32) (*(s16 *)((u8 *)arg1 + 0)), (f32) (*(s16 *)((u8 *)arg1 + 2)), (f32) (*(s16 *)((u8 *)arg1 + 4)), &sp.u44, &sp.u40, &sp.u3C, &sp.u38, 4000.0f) == 0) {
        *arg2 = 0;
        return var_s0;
    }
    func_15095F18((s32) arg1, sp.u44, sp.u40, sp.u38, 1, arg2);
    if (*arg2 != 0) {
        temp_s0 = var_s0 + 8;
        (*(s32 *)((u8 *)var_s0 + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)var_s0 + 4)) = 0;
        (*(s32 *)((u8 *)temp_s0 + 0)) = 0xEE000000;
        var_s0 = temp_s0 + 8;
        (*(s32 *)((u8 *)temp_s0 + 4)) = (s32) ((u32) (((sp.u3C / sp.u38) * 16352.0f) + 16352.0f) << 0x10);
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095CC0.s")
#endif
#ifdef NON_MATCHING
/* NON_MATCHING: the matching void wrappers return the callee's v0 (the new display-list pointer), which callers use. */
s32 func_15095EA0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
s32 func_15095E58(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    return func_15095EA0(arg0, arg1, arg2, arg3, 4096.0f, 0, 0, 0, 0);
}
#else
void func_15095E58(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    func_15095EA0(arg0, arg1, arg2, arg3, 4096.0f, 0, 0, 0, 0);
}
#endif

s32 func_15095F18(s32, f32, f32, f32, s32, s32 *);
s32 func_15096144(s32, s32, s32, s32, s32);
s32 func_15095EA0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 sp24;
    func_15095F18(arg1, arg2, arg3, arg4, arg5, &sp24);
    if (sp24 != 0) {
        arg0 = func_15096144(arg0, arg1, arg6, arg7, arg8);
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095F18.s")

#ifdef NON_MATCHING
/* NON_MATCHING: the matching void wrappers return the callee's v0 (the new display-list pointer), which callers use. */
s32 func_1509611C(s32 arg0, s32 arg1) {
    return func_15096144(arg0, arg1, 0, 0, 0);
}
#else
void func_1509611C(s32 arg0, s32 arg1) {
    func_15096144(arg0, arg1, 0, 0, 0);
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15096144.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_150966AC.s")

Gfx *func_15096D44(Gfx *arg0) {
    gSPDisplayList(arg0++, D_800877A8);
    D_800D31CB = 0;
    return arg0;
}
