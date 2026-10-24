#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_1516D970(void) {
    s32 i;
    s32 v;

    for (i = 0; i < 4; i++) {
        if ((&D_800DD2A0)[i] < 0xFF) {
            v = (&D_800DD2A0)[i] + D_800BE9A0;
            if (v >= 0x100) {
                v = 0xFF;
            }
            (&D_800DD2A0)[i] = v;
        }
    }
}

s32 func_15044BC0(s32, s32, s32, s32, s32, s32, s32, u8 *, u8 *);

void func_1516DA58(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15, u8 arg16, s16 arg17, s16 arg18, u8 arg19, s16 arg1A, s32 arg1B, s32 arg1C, u8 arg1D, s32 arg1E) {
    u8 *temp_v0;
    s32 var_a0;
    u8 *sp34;

    if (arg1B != 0) {
        var_a0 = 0x67;
    } else {
        var_a0 = 0x12;
    }
    temp_v0 = func_15167A68(var_a0, arg1E, 0x34, 0, (u8) (s32) arg1D, 1U);
    if (temp_v0 != NULL) {
        (*(s16 *)((u8 *)temp_v0 + 0xE)) = arg0;
        (*(s16 *)((u8 *)temp_v0 + 0x10)) = arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x12)) = arg2;
        (*(u8 *)((u8 *)temp_v0 + 0x1A)) = arg3;
        (*(u8 *)((u8 *)temp_v0 + 0x1B)) = arg4;
        (*(u8 *)((u8 *)temp_v0 + 0x1C)) = arg5;
        (*(u8 *)((u8 *)temp_v0 + 0x1D)) = arg6;
        (*(u8 *)((u8 *)temp_v0 + 0x1E)) = arg7;
        (*(u8 *)((u8 *)temp_v0 + 0x1F)) = arg8;
        (*(u8 *)((u8 *)temp_v0 + 0x20)) = arg9;
        (*(u8 *)((u8 *)temp_v0 + 0x21)) = argA;
        (*(u8 *)((u8 *)temp_v0 + 0x22)) = argB;
        (*(u8 *)((u8 *)temp_v0 + 0x23)) = argC;
        (*(s16 *)((u8 *)temp_v0 + 0x14)) = arg17;
        (*(s16 *)((u8 *)temp_v0 + 0x16)) = arg18;
        (*(u8 *)((u8 *)temp_v0 + 0x24)) = arg19;
        (*(s16 *)((u8 *)temp_v0 + 0x18)) = arg1A;
        (*(s8 *)((u8 *)temp_v0 + 0x25)) = 0;
        (*(u8 *)((u8 *)temp_v0 + 0x26)) = argD;
        (*(u8 *)((u8 *)temp_v0 + 0x27)) = argE;
        (*(u8 *)((u8 *)temp_v0 + 0x28)) = argF;
        (*(u8 *)((u8 *)temp_v0 + 0x29)) = arg10;
        (*(u8 *)((u8 *)temp_v0 + 0x2A)) = arg11;
        (*(u8 *)((u8 *)temp_v0 + 0x2B)) = arg12;
        (*(u8 *)((u8 *)temp_v0 + 0x2C)) = arg13;
        (*(u8 *)((u8 *)temp_v0 + 0x2D)) = arg14;
        (*(u8 *)((u8 *)temp_v0 + 0x2E)) = arg15;
        (*(u8 *)((u8 *)temp_v0 + 0x2F)) = arg16;
        if (arg1C != 0) {
            sp34 = temp_v0;
            (*(s32 *)((u8 *)temp_v0 + 0x30)) = func_15044BC0(-1, 0, arg1C, 0x14, 0x14, 0x14, 0, temp_v0 + 0xE, temp_v0 + 0x14);
            return;
        }
        (*(s32 *)((u8 *)temp_v0 + 0x30)) = 0;
    }
}

extern s32 (*D_8008CF40[])(u8 *);

void func_1516DBE8(u8 *arg0) {
    s32 v;

    v = arg0[0x24];
    if (v != 0) {
        v -= D_800BE9E4;
        if (v < 0) {
            v = 0;
        }
        arg0[0x24] = v;
    }
    if (D_8008CF40[arg0[0x23]](arg0) == 1) {
        if (*(u8 **)(arg0 + 0x30) != NULL) {
            *(s16 *)(*(u8 **)(arg0 + 0x30) + 4) = 0;
        }
        func_1516972C((struct102 *)arg0);
    } else {
        s32 t;
        v = *(s16 *)(arg0 + 0x10) << 8;
        v += arg0[0x25];
        t = v;
        t += *(s16 *)(arg0 + 0x18) * D_800BE9E4;
        *(s16 *)(arg0 + 0x10) = t >> 8;
        arg0[0x25] = t & 0xFF;
    }
}

#ifdef NON_MATCHING
s32 func_15142E24(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
u8 *func_15095B70(u8 *, u8 *);
extern u8 *D_8008CDEC[];
extern s16 D_800DD5EC; /* last sprite other-mode (1 / 2 / 3), shared with func_150A6D40 */
extern s32 D_800D30BC; /* TLUT bit of the last loaded texture */
extern u8 D_800D31C8;
extern u8 D_800D31C9;
extern u8 D_800D31CA;
// tinted_sprite_draw: draw handler of the particle type whose tick is func_1516DBE8 (D_8008BBF8 / D_8008CD3C, same
// slot as func_150A6D40). Loads the texture D_8008CDEC[+0x1A] frame +0x1B (func_15142E24), picks the combine mode
// (2 for a texture of format 5 at +0xA, else 1; set only when it differs from D_800DD5EC, after a pipe sync), sets the
// other mode 0x2C00 | TLUT | (0x100000 for mode 2), the colour D_800D31C8..CA from +0x1C..+0x1E and the env colour
// +0x20..+0x22 (only when it differs from D_800DD5F8..FC; alpha 0), and draws the quad (+0xE..+0x16, alpha +0x1F)
// with func_15095B70. Returns the advanced display list.
// The asm leaves its other-mode word (sp+0x5C) uninitialised when the combine mode is unchanged (a stale stack
// word); the C uses the word that belongs to the mode, i.e. what the previous draw of this mode set.
u8 *func_1516DCA8(u8 *gfx, u8 *obj, s32 arg2) {
    struct {
        s16 x, y, z;
        s16 sizeX, sizeZ;
        u8 alpha;
        u8 pad[2];
        u8 flag;
    } quad; /* sp84 */
    s32 *tex;
    s32 synced; /* the s32 at sp78; func_15142E24 / func_15142FBC see it as a byte */
    s32 mode;
    s32 other;
    s32 r;
    s32 g;
    s32 b;

    synced = 0;
    D_800D31CB = 0;
    tex = (s32 *) D_8008CDEC[obj[0x1A]];
    gfx = (u8 *) func_15142E24((s32) gfx, (s32) tex, obj[0x1B] << 8, 2, 0x100, 0x100, 0, 6, (s32) &quad,
                               (u8 *) &synced, 3);
    if (((u8 *) tex)[0xA] == 5) {
        mode = 2;
    } else {
        mode = 1;
    }
    other = (mode == 1) ? 0 : 0x100000;
    if (mode != D_800DD5EC) {
        if (synced == 0) {
            ((s32 *) gfx)[0] = 0xE7000000; /* gDPPipeSync */
            ((s32 *) gfx)[1] = 0;
            gfx += 8;
            synced = 1;
        }
        D_800DD5EC = mode;
        if (mode == 1) {
            ((s32 *) gfx)[0] = 0xFC30B261; /* gDPSetCombine */
            ((s32 *) gfx)[1] = 0x5566FF7F;
        } else {
            ((s32 *) gfx)[0] = 0xFC30B5FF;
            ((s32 *) gfx)[1] = 0x5FFEFE38;
        }
        gfx += 8;
    }
    gfx = (u8 *) func_15142FBC((Gfx *) gfx, other | D_800D30BC | 0x2C00, 0x5049DC, (u8 *) &synced);

    quad.x = *(s16 *) (obj + 0xE);
    quad.y = *(s16 *) (obj + 0x10);
    quad.z = *(s16 *) (obj + 0x12);
    quad.sizeX = *(s16 *) (obj + 0x14);
    quad.sizeZ = *(s16 *) (obj + 0x16);
    quad.flag = 0;
    quad.alpha = obj[0x1F];
    D_800D31C8 = obj[0x1C];
    D_800D31C9 = obj[0x1D];
    D_800D31CA = obj[0x1E];
    r = obj[0x20];
    g = obj[0x21];
    b = obj[0x22];
    if (r != D_800DD5F8 || g != D_800DD5FA || b != D_800DD5FC) {
        D_800DD5F8 = r;
        D_800DD5FA = g;
        D_800DD5FC = b;
        if (synced == 0) {
            ((s32 *) gfx)[0] = 0xE7000000; /* gDPPipeSync */
            ((s32 *) gfx)[1] = 0;
            gfx += 8;
        }
        ((s32 *) gfx)[0] = 0xFB000000; /* gDPSetEnvColor(r, g, b, 0) */
        ((s32 *) gfx)[1] = (r << 24) | (g << 16) | (b << 8);
        gfx += 8;
    }
    return func_15095B70(gfx, (u8 *) &quad);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516DCA8.s")
#endif

void func_1516DF0C(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15, u8 arg16, u8 arg17, u8 arg18, u8 arg19, u8 arg1A, s16 arg1B, s16 arg1C, s16 arg1D, s16 arg1E, u16 arg1F, u8 arg20, u8 arg21, u8 arg22, u8 arg23, s16 arg24, u16 arg25, u16 arg26, u8 arg27, u8 arg28, u8 arg29, u8 arg2A, u8 arg2B, s32 arg2C, u8 arg2D, u8 arg2E, u8 arg2F, s32 arg30) {
    s32 var_a0;
    u8 *temp_v0;

    if (arg2C != 0) {
        var_a0 = 0x66;
    } else {
        var_a0 = 0x11;
    }
    temp_v0 = func_15167A68(var_a0, arg30, 0x4C, 0, arg2F, 1);
    if (temp_v0 != NULL) {
        *(s16 *)(temp_v0 + 0xE) = arg0;
        *(s16 *)(temp_v0 + 0x10) = arg1;
        *(s16 *)(temp_v0 + 0x12) = arg2;
        *(s16 *)(temp_v0 + 0x14) = arg1B;
        *(s16 *)(temp_v0 + 0x16) = arg1C;
        *(s16 *)(temp_v0 + 0x18) = arg1D;
        *(s16 *)(temp_v0 + 0x1A) = arg1E;
        *(u8 *)(temp_v0 + 0x24) = arg3;
        *(u8 *)(temp_v0 + 0x25) = arg4;
        *(u8 *)(temp_v0 + 0x26) = arg5;
        *(u8 *)(temp_v0 + 0x27) = arg6;
        *(u8 *)(temp_v0 + 0x28) = arg7;
        *(u8 *)(temp_v0 + 0x2A) = arg9;
        *(u8 *)(temp_v0 + 0x2B) = argA;
        *(u8 *)(temp_v0 + 0x2C) = argB;
        *(u8 *)(temp_v0 + 0x29) = arg8;
        *(u8 *)(temp_v0 + 0x2D) = argC;
        *(u8 *)(temp_v0 + 0x2E) = argD;
        *(u8 *)(temp_v0 + 0x2F) = argE;
        *(u8 *)(temp_v0 + 0x30) = argF;
        *(u8 *)(temp_v0 + 0x31) = arg10;
        *(u8 *)(temp_v0 + 0x32) = arg11;
        *(u8 *)(temp_v0 + 0x33) = arg12;
        *(u8 *)(temp_v0 + 0x34) = arg13;
        *(u8 *)(temp_v0 + 0x35) = arg14;
        *(u8 *)(temp_v0 + 0x36) = arg15;
        *(u8 *)(temp_v0 + 0x37) = arg16;
        *(u8 *)(temp_v0 + 0x38) = arg17;
        *(u8 *)(temp_v0 + 0x39) = arg18;
        *(u8 *)(temp_v0 + 0x3A) = arg19;
        *(u8 *)(temp_v0 + 0x3B) = arg1A;
        *(u16 *)(temp_v0 + 0x20) = arg1F;
        *(s8 *)(temp_v0 + 0x3C) = arg1F;
        *(u8 *)(temp_v0 + 0x3D) = arg20;
        *(u8 *)(temp_v0 + 0x3E) = arg21;
        *(u8 *)(temp_v0 + 0x3F) = arg22;
        *(u8 *)(temp_v0 + 0x40) = arg23;
        *(s16 *)(temp_v0 + 0x1C) = arg24;
        *(u16 *)(temp_v0 + 0x1E) = arg25;
        *(u16 *)(temp_v0 + 0x22) = arg26;
        *(u8 *)(temp_v0 + 0x41) = arg27;
        *(s8 *)(temp_v0 + 0x42) = 0;
        *(u8 *)(temp_v0 + 0x43) = arg28;
        if ((arg2C != 0) && (arg29 >= 4)) {
            arg29 = 3;
        }
        *(u8 *)(temp_v0 + 0x44) = arg29;
        *(u8 *)(temp_v0 + 0x45) = arg2A;
        *(u8 *)(temp_v0 + 0x46) = arg2B;
        *(u8 *)(temp_v0 + 0x47) = arg2D;
        *(u8 *)(temp_v0 + 0x48) = arg2E;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516E100.s")

void func_1516ECE8(u32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    if (arg1) { // fakematch: permuter, forces arg1 home/reload order
    }
    func_1516DF0C(arg0 >> 0x10, arg0 & 0xFFFF, 0, arg2, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0, 8, 8, 1, 0, 0, 0, 0, 0x155, 0x155, 0x155, 0x155, arg1, 0x1E, 0, 0xFF, 0x28, 0x168, 0x18, 0x21, 4, 0, 1, 0, 0, 0, 0, 0, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516EE3C.s")

s32 func_1516F21C(u8 *arg0) {
    s32 v;
    s32 t;
    s32 hl;
    s32 m;

    v = arg0[0x1F];
    if (arg0[0x24] != 0) {
        if (v != 0xFF) {
            v += D_800BE9E4 << 7;
            if (v >= 0x100) {
                v = 0xFF;
            }
            arg0[0x1F] = v;
        }
    } else if (v != 0) {
        v -= D_800BE9E4 * arg0[0x26];
        if (v < 0) {
            v = 0;
        }
        arg0[0x1F] = v;
    }
    if ((arg0[0x24] == 0) && (v == 0)) {
        return 1;
    }
    hl = arg0[0x2D] | (arg0[0x2C] << 8);
    m = hl * v;
    t = m >> 7;
    *(s16 *)(arg0 + 0x16) = t;
    *(s16 *)(arg0 + 0x14) = t;
    return 0;
}

void func_1516F2D8(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 t;

    t = D_800CC2D4[arg0 * 0x32C];
    if (t == 0x3A) {
        func_1516DF0C(5, 0, 0, 4, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0x124, 0x124, 0, 0, arg1, 0, 0, arg0, 0xC, 0, 0, 0x81, 2, 0, 1, 0, 0, 0, 5, 0, arg2, arg3);
    }
}

void func_1516EED4(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    if ((arg0 < 4) && ((&D_800DD2A0)[arg0 ^ 0] >= arg1)) { // fakematch: ^ 0 (permuter), keeps one arg0 reload
        (&D_800DD2A0)[arg0 ^ 0] = 0;
        func_1516DF0C(0, 0, 0, 4, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x200, 0x200, 0, 0, 0x1E, 0, 0, arg0, 0x14, 0, 0, 0x81, 8, 0, 1, 0, 0, 0, 0xC, 0, arg2, arg3);
    }
}

#ifdef NON_MATCHING
void func_1516FDD4(u8 *arg0);
void func_1516FEBC(s32 arg0, s32 arg1);

// sprite_fade_grow_kind_tick: particle tick (handler at 0x8008CF48, sibling of func_1516FF34) with per-kind
// parameters (+0x2C = kind 0..10, tables copied from D_8008CF64 / CF70 / CF7C / CF88). While +0x24 (fading in) is
// set, alpha +0x1F rises by 16 per frame (D_800BE9E4) up to the kind's maximum; otherwise it falls by the kind's
// rate per frame down to 0. Returns 1 (done) once fading out reached 0. Else moves the particle
// (func_1516FDD4), grows the size +0x14 / +0x16 by the kind's step per frame (kind 3 also sets +0x18 = 100),
// scales its velocity by the kind's factor / 256 (func_1516FEBC) and returns 0.
s32 func_1516F594(u8 *arg0) {
    static const u8 scale[11] = { 0xFA, 0xFA, 0xEB, 0xEB, 0xFA, 0xFA, 0xDC, 0xD2, 0xD2, 0xDC, 0xD2 };
    static const u8 grow[11] = { 0x10, 0x07, 0x07, 0x07, 0x14, 0x08, 0x28, 0x28, 0x28, 0x14, 0x14 };
    static const u8 maxAlpha[11] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xBE, 0xAA, 0x78, 0xC8, 0x3C, 0x78, 0xC8 };
    static const u8 fadeRate[11] = { 0x08, 0x02, 0x0A, 0x01, 0x08, 0x0A, 0xFF, 0x0A, 0x02, 0xFF, 0x0A };
    s32 kind = arg0[0x2C];
    s32 v = arg0[0x1F];
    s32 size;

    if (arg0[0x24] != 0) {
        if (v != maxAlpha[kind]) {
            v += D_800BE9E4 << 4;
            if (v > maxAlpha[kind]) {
                v = maxAlpha[kind];
            }
            arg0[0x1F] = v;
        }
    } else if (v != 0) {
        v -= D_800BE9E4 * fadeRate[kind];
        if (v < 0) {
            v = 0;
        }
        arg0[0x1F] = v;
    }
    if (arg0[0x24] == 0 && v == 0) {
        return 1;
    }
    func_1516FDD4(arg0);
    size = *(s16 *) (arg0 + 0x14) + D_800BE9E4 * grow[kind];
    *(s16 *) (arg0 + 0x16) = size;
    *(s16 *) (arg0 + 0x14) = size;
    if (kind == 3) {
        *(s16 *) (arg0 + 0x18) = 100;
    }
    func_1516FEBC((s32) arg0, scale[kind]);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516F594.s")
#endif

void func_1516DF0C(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15, u8 arg16, u8 arg17, u8 arg18, u8 arg19, u8 arg1A, s16 arg1B, s16 arg1C, s16 arg1D, s16 arg1E, u16 arg1F, u8 arg20, u8 arg21, u8 arg22, u8 arg23, s16 arg24, u16 arg25, u16 arg26, u8 arg27, u8 arg28, u8 arg29, u8 arg2A, u8 arg2B, s32 arg2C, u8 arg2D, u8 arg2E, u8 arg2F, s32 arg30);

void func_1516F730(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    func_1516DF0C(2, 0, 0, 0x2D, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0x50, 0x50, 0, 0, arg1, 0xA, 0xA, arg0, 0x3C, 0, 0, 0x81, 4, 0, 1, 0, 0, 0, 4, 2, (s32) arg2, arg3);
}

void func_1516F868(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_1516DF0C(3, 0, 0, 0x2B, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0x50, 0x50, 0, 0, arg1, 4, 4, arg0, 0x10, 0, 0, 0x81, 4, 0, 1, 0, 0, 0, 1, 0, arg4, arg5);
    func_1516DF0C(3, 0, 0, 0x2B, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0x50, 0x50, 0, 0, 7, 4, 4, arg0, arg2, 0, 0, 0x81, 5, 0, 1, 0, 0, 0, 1, arg3, arg4, arg5);
}

#ifdef NON_MATCHING

// spray_pair_spawn: spawns two particle sprays at (x, y, z) through func_1516DF0C (same parameters except the second
// one's +0x13 byte (rate11 instead of rate10) and +0x27 = 6), then plays sound 7 there with `span` as the sound's user
// value. Speeds speedA / speedB go through a 20.12 fixed-point round trip ((v << 12) / 4096) as in the asm.
void func_1516FAB8(s32 x, s32 y, s32 z, s32 span, s32 dx, s32 spread, s32 dz, s32 speedA, s32 speedB, s32 size,
                   s32 rate10, s32 rate11, s32 unused12, s32 unused13, s32 unused14, s32 flag, s32 owner) {
    s16 a = (s16)((speedA << 12) / 4096);
    s16 b = (s16)((speedB << 12) / 4096);

    func_1516DF0C(x, y, z, 0xD, 0, 0x67, 0x17, 0xD, 0, 0, 0x12, 0, 2, dx, 0, dz, 0, 0, 0, rate10, 0, 0, 0, 0, 0, 0, 0,
                  a, a, b, b, span, size, 0x14, 0xFF, 0x10, spread, 0xC8, 1, 0, 0, 1, 0, 0, 0, 0, 0, flag, owner);
    func_1516DF0C(x, y, z, 0xD, 0, 0x67, 0x17, 0xD, 0, 0, 0x12, 0, 2, dx, 0, dz, 0, 0, 0, rate11, 0, 0, 0, 0, 0, 0, 0,
                  a, a, b, b, span, size, 0x14, 0xFF, 0x10, spread, 0xC8, 1, 6, 0, 1, 0, 0, 0, 0, 0, flag, owner);
    func_1000FA64(7, x, y, z, 0x36B0, 0x3E8, 0x64, (s32)&func_1000EBC4, (void *)span, 0, 0, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FAB8.s")
#endif

#ifdef NON_MATCHING
void func_1516FDD4(u8 *arg0) {
    s32 temp_t1;
    s32 temp_t3;

    temp_t3 = ((*(s16 *)((u8 *)arg0 + 0xE)) << 8) + (*(u8 *)((u8 *)arg0 + 0x2A)) + ((((*(s8 *)((u8 *)arg0 + 0x26)) << 8) + (*(u8 *)((u8 *)arg0 + 0x27))) * D_800BE9E4);
    (*(s16 *)((u8 *)arg0 + 0xE)) = (s16) (temp_t3 >> 8);
    (*(u8 *)((u8 *)arg0 + 0x2A)) = (u8) temp_t3;
    temp_t1 = ((*(s16 *)((u8 *)arg0 + 0x12)) << 8) + (*(u8 *)((u8 *)arg0 + 0x2B)) + ((((*(s8 *)((u8 *)arg0 + 0x28)) << 8) + (*(u8 *)((u8 *)arg0 + 0x29))) * D_800BE9E4);
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (temp_t1 >> 8);
    (*(u8 *)((u8 *)arg0 + 0x2B)) = (u8) temp_t1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FDD4.s")
#endif
void func_1516FE5C(s32 arg0, s32 arg1) {
    s32 v;

    v = ((s8 *)arg0)[0x26];
    v <<= 8;
    v += ((u8 *)arg0)[0x27];
    v *= (u32)arg1;
    v >>= 8;
    ((u8 *)arg0)[0x26] = v >> 8;
    ((u8 *)arg0)[0x27] = v & 0xFFFFu; // fakematch: the mask moves the low byte temp from t8 to t0
}

void func_1516FE8C(s32 arg0, s32 arg1) {
    s32 v;

    v = ((s8 *)arg0)[0x28];
    v <<= 8;
    v += ((u8 *)arg0)[0x29];
    v *= (u32)arg1;
    v >>= 8;
    ((u8 *)arg0)[0x28] = v >> 8;
    ((u8 *)arg0)[0x29] = v & 0xFFFFu; // fakematch: the mask moves the low byte temp from t8 to t0
}

void func_1516FE5C(s32, s32);
void func_1516FE8C(s32, s32);

void func_1516FEBC(s32 arg0, s32 arg1) {
    func_1516FE5C(arg0, arg1);
    func_1516FE8C(arg0, arg1);
}

void func_1516FEF4(s32 arg0, s32 arg1) {
    s32 v;
    func_1516FEBC(arg0, arg1);
    v = *(s16 *)((u8 *)arg0 + 0x18);
    v = v * arg1;
    *(s16 *)((u8 *)arg0 + 0x18) = v >> 8;
}

#ifdef NON_MATCHING
// sprite_fade_scale_tick: particle tick (same scheme as func_151702C0): while +0x24 (fading in) is set, alpha +0x1F
// rises by 16 per frame (D_800BE9E4) up to 255; otherwise it falls by 8 per frame down to 0 and the size
// (+0x14 / +0x16) follows it (2 * alpha). Returns 1 (done) once fading out reached 0; else moves the particle
// (func_1516FDD4), scales its velocity by 0xF0 / 256 (func_1516FEF4) and returns 0.
s32 func_1516FF34(u8 *arg0) {
    s32 v;
    s32 t;

    v = arg0[0x1F];
    if (arg0[0x24] != 0) {
        if (v != 0xFF) {
            v += D_800BE9E4 * 0x10;
            if (v >= 0x100) {
                v = 0xFF;
            }
            arg0[0x1F] = v;
        }
    } else {
        if (v != 0) {
            v -= D_800BE9E4 * 8;
            if (v < 0) {
                v = 0;
            }
            arg0[0x1F] = v;
        }
        t = (v << 9) >> 8;
        *(s16 *)(arg0 + 0x16) = t;
        *(s16 *)(arg0 + 0x14) = t;
    }
    if ((arg0[0x24] == 0) && (v == 0)) {
        return 1;
    }
    func_1516FDD4(arg0);
    func_1516FEF4((s32) arg0, 0xF0);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FF34.s")
#endif

void func_1516FFF8(s16 arg0, s16 arg1, s16 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_1516DF0C(arg0, arg1, arg2, 0x1B, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0xFF, 0xFF, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x400, 0x400, 0, 0, 2, 0, 0, 0xFF, 0xF, 0, 0, 9, 0, 0xFF, 0xA, 0x5A, 5, arg3, 0, 0, (s32) arg4, arg5);
}

#ifdef NON_MATCHING
// sprite_fade_drift_tint_tick: particle tick (handler at 0x8008CF50, same scheme as func_1516FF34): while +0x24
// (fading in) is set, alpha +0x1F rises by 16 per frame (D_800BE9E4) up to 255; otherwise it falls by
// D_800BE9E4 << +0x2F down to 0. Returns 1 (done) once fading out reached 0. Else the size +0x14 / +0x16 grows by
// the signed rates +0x2D / +0x2E per frame; when the width reaches 0 or below both are cleared and it returns 1.
// Else the tint step +0x2C advances by D_800BE9E4 (up to 0x7F) and the colour +0x1C..+0x1E blends from
// +0x26..+0x28 towards +0x29..+0x2B by 2 * step / 256; returns 0.
s32 func_1517013C(u8 *arg0) {
    s32 v = arg0[0x1F];
    s32 t;

    if (arg0[0x24] != 0) {
        if (v != 0xFF) {
            v += D_800BE9E4 << 4;
            if (v >= 0x100) {
                v = 0xFF;
            }
            arg0[0x1F] = v;
        }
    } else if (v != 0) {
        v -= D_800BE9E4 << arg0[0x2F];
        if (v < 0) {
            v = 0;
        }
        arg0[0x1F] = v;
    }
    if (arg0[0x24] == 0 && v == 0) {
        return 1;
    }
    *(s16 *) (arg0 + 0x14) += (s8) arg0[0x2D] * D_800BE9E4;
    *(s16 *) (arg0 + 0x16) += (s8) arg0[0x2E] * D_800BE9E4;
    if (*(s16 *) (arg0 + 0x14) <= 0) {
        *(s16 *) (arg0 + 0x16) = 0;
        *(s16 *) (arg0 + 0x14) = *(s16 *) (arg0 + 0x16);
        return 1;
    }
    v = arg0[0x2C] + D_800BE9E4;
    if (v >= 0x80) {
        v = 0x7F;
    }
    arg0[0x2C] = v;
    t = v * 2;
    arg0[0x1C] = (((arg0[0x29] - arg0[0x26]) * t) >> 8) + arg0[0x26];
    arg0[0x1D] = (((arg0[0x2A] - arg0[0x27]) * t) >> 8) + arg0[0x27];
    arg0[0x1E] = (((arg0[0x2B] - arg0[0x28]) * t) >> 8) + arg0[0x28];
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1517013C.s")
#endif

void func_1516FDD4(u8 *arg0);

s32 func_151702C0(u8 *arg0) {
    s32 v;
    s32 t;

    v = arg0[0x1F];
    if (arg0[0x24] != 0) {
        if (v != 0xFF) {
            v += D_800BE9E4 * 0x10;
            if (v >= 0x100) {
                v = 0xFF;
            }
            arg0[0x1F] = v;
        }
    } else {
        if (v != 0) {
            v -= D_800BE9E4 * 8;
            if (v < 0) {
                v = 0;
            }
            arg0[0x1F] = v;
        }
        t = (v << 9) >> 8;
        *(s16 *)(arg0 + 0x16) = t;
        *(s16 *)(arg0 + 0x14) = t;
    }
    if ((arg0[0x24] == 0) && (v == 0)) {
        return 1;
    }
    func_1516FDD4(arg0);
    *(s16 *)(arg0 + 0x18) += ((s8 *)arg0)[0x2C];
    return 0;
}

#ifdef NON_MATCHING
void func_1516FE1C(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    struct {
        s32 uFC;
    } sp;
    f32 *temp_fp;
    s16 var_fp;
    s16 var_s7;
    s32 var_a0;
    s32 var_a1;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    struct127 *temp_t0;

    var_a0 = arg0;
    temp_t0 = &D_800CC2D0[var_a0];
    var_s1 = 0;
    var_s0 = 0;
    if (temp_t0->interaction_state == 1) {
        var_s7 = 4;
        var_fp = 0;
        var_s2 = 0x19;
        var_a1 = 1;
    } else {
        temp_fp = &temp_t0->x_position;
        var_s7 = (s16) ((s32) temp_fp >> 0x10);
        var_fp = (s16) temp_fp;
        var_a0 = 0xFF;
        var_a1 = 0x21;
        var_s2 = sp.uFC;
    }
    do {
        if (var_s0 == 1) {
            var_s2 = 0x1B;
            var_s1 = 8;
        }
        func_1516DF0C(var_s7, var_fp, 0, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, (u8) var_s1, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0xAA, 0xAA, 0xAA, 0xAA, (u16) (arg1 & 0xFFFF), 0x1EU, 0U, (u8) (var_a0 & 0xFF), 0x1EU, 0x168, 0x18U, (u16) (var_a1 & 0xFFFF), 4U, 0U, 1U, 0U, 0U, 0, (u8) var_s2, 0U, (u8) (s32) arg2, arg3);
        var_s0 += 1;
    } while (var_s0 != 2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FE1C.s")
#endif
f32 func_150489B0();
s32 func_151705A4(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 mask;
    s32 pad; // fakematch: frame slot 0x28
    f32 s;
    f32 c;
    s32 v;
    f32 t;

    mask = (arg0 & 0x40) ? 0x3F : 0x7F;
    v = func_150ADA20() & mask;
    *arg2 = func_150489B0(v & 0xFF);
    c = func_15048A40(v);
    v = func_150ADA20() & 0xFF;
    s = func_150489B0(v & 0xFF);
    t = func_15048A40(v);
    *arg1 = c * t;
    *arg3 = c * s;
}

#ifdef NON_MATCHING
s32 func_150ADA20(void);
extern f32 D_8008CFA0[3]; /* spread per variant: 571, 130, 130 */
extern u8 D_8008CFAC[9];  /* colour per variant (3 bytes) */

// quad_edge_sparks_spawn: walks the 4 edges of `quad` (4 points of 3 floats) and spawns `countA` (edges 0 / 2) or
// `countB` (edges 1 / 3) sparks evenly along each edge (func_1516DA58 type 0xD, variant `variant`'s colour): the
// spark's push is the edge midpoint relative to (x, z) (doubled, as hi / lo bytes), its speed 731 * size + rand
// modulo 836 * size, life 15..46, spread 143 * size + rand modulo D_8008CFA0[variant] * size. The caller's D_8008CF94 copy is unused.
void func_15170648(f32 *quad, f32 x, f32 z, s32 kind, f32 size, s32 variant, s32 countA, s32 countB, s32 alpha,
                   s32 owner) {
    f32 *p;
    f32 *q;
    u8 *col;
    s32 edge;
    s32 next;
    s32 n;
    s32 i;
    s32 range;
    s32 vx, vz;
    s32 speedBase, speedRange, spreadBase;
    s32 life;
    s32 speed;
    f32 mx, mz;
    f32 step;
    f32 t;
    f32 px, py, pz;

    range = (s32)(D_8008CFA0[variant] * size);
    p = quad;
    for (edge = 0; edge < 4; edge++, p += 3) {
        next = (edge == 3) ? 0 : edge + 1;
        n = (edge == 0 || edge == 2) ? countA : countB;
        q = &quad[next * 3];
        col = &D_8008CFAC[variant * 3];
        mx = (q[0] + p[0]) * 0.5f - x;
        mz = (q[2] + p[2]) * 0.5f - z;
        vx = (s32)(mx + mx);
        vz = (s32)(mz + mz);
        if (n <= 0) {
            continue;
        }
        speedBase = (s32)(731.0f * size);
        speedRange = (s32)(836.0f * size);
        spreadBase = (s32)(143.0f * size);
        step = 1.0f / (f32)(n - 1);
        for (i = 0; i < n; i++) {
            t = (f32)i * step;
            px = (q[0] - p[0]) * t + p[0];
            py = (q[1] - p[1]) * t + p[1];
            pz = (q[2] - p[2]) * t + p[2];
            life = (func_150ADA20() & 0x1F) + 15;
            speed = (u32)func_150ADA20() % (u32)speedRange + speedBase;
            func_1516DA58((s16)(s32)px, (s16)(s32)py, (s16)(s32)pz, 0xD, 0, col[0], col[1], col[2], 0, 0, 0, 0, 2,
                          (vx >> 8) & 0xFF, vx & 0xFF, (vz >> 8) & 0xFF, vz & 0xFF, 0, 0, kind, 0, 0, 0, speed, speed,
                          life, (u32)func_150ADA20() % (u32)range + spreadBase, 0, 0, alpha, owner);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_15170648.s")
#endif

#ifdef NON_MATCHING
extern u16 D_800CC76A;
s32 func_151EFDD0(void);
f32 func_150489B0(s32 angle); // defined (u8); the file's unprototyped declaration rules out u8 here
// spark_particle_spawn: one spark at (x, y, z) thrown in direction `angle` (the camera angle D_800CC76A when `flare`
// is 0) with a random pitch (rand % 50, both signs), horizontal speed from sin / cos of the angle, fixed fall -0x32;
// flare != 0: long-lived flare particle (func_1516DA58), else short spark (func_1516DF0C). alpha and arg6 pass through.
// Called by ambient_emitters_update (func_1517C11C) for torch / fire sparks and flare-ups.
void func_15170A70(s32 x, s32 y, s32 z, s32 angle, s32 flare, s32 alpha, s32 arg6) {
    s32 pitch;
    f32 dirX;
    f32 dirZ;
    f32 tilt;
    f32 dx;
    f32 dz;
    f32 dy;
    s32 vx;
    s32 vz;
    s32 vy;

    if (flare == 0) {
        angle = D_800CC76A;
    }
    pitch = func_151EFDD0() % 50;
    dirX = func_150489B0(angle & 0xFF);
    dirZ = -func_15048A40(angle & 0xFF);
    tilt = func_150489B0(pitch & 0xFF);
    dx = dirX * tilt;
    dz = dirZ * tilt;
    dy = 0.0f;
    dx = dx + dx;
    dz = dz + dz;
    dy = dy + dy;
    vx = dx * 256.0f;
    vz = dz * 256.0f;
    vy = dy * 256.0f;
    if (flare != 0) {
        func_1516DA58(x, y, z, 0x2A, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 6, vx >> 8, vx & 0xFF, vz >> 8, vz & 0xFF,
                      0, 0, 0, 0, 0, 1, 0x200, 0x166, 0xFF, vy - 0x32, 0, 0, alpha & 0xFF, arg6);
    } else {
        func_1516DF0C(x, y, z, 0x2A, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 6, vx >> 8, vx & 0xFF, vz >> 8, vz & 0xFF,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x200, 0x166, 0, 0, 0x14, 0, 0, 0xFF, 0xFF, vy - 0x32, 0xC8, 9,
                      1, 0, 1, 0x32, 0x14, 0, 0, 0, alpha & 0xFF, arg6);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_15170A70.s")
#endif

#ifdef NON_MATCHING
s32 func_151EFDD0(void);
// sprite_flicker_drift_tick: particle tick (handler at 0x8008CF58 of D_8008CF40, same scheme as func_1516FF34).
// While +0x24 (life) is set, the alpha +0x1F rises by 64 per frame (D_800BE9E4) up to 254; a particle whose alpha is
// still 0 first gets a life of 200..224 (func_150ADA20). Otherwise the alpha falls by 16 per frame down to 0, and
// the particle is done (returns 1) once it reached 0. Else it moves (func_1516FDD4) and its velocity +0x26 / +0x28
// is scaled by a random (230 + -31..31) / 256 when +0x2F is set, or by (220 + -31..31) / 256 when the 8.8
// velocity +0x26 is above sqrt(1000); +0x18 is cleared and it returns 0.
s32 func_15170D50(u8 *arg0) {
    s32 alpha = arg0[0x1F];
    s32 vel;

    if (arg0[0x24] != 0) {
        if (alpha == 0) {
            arg0[0x24] = (u32) func_150ADA20() % 25 + 200;
        }
        if (alpha != 0xFE) {
            alpha += D_800BE9E4 << 6;
            if (alpha >= 0xFF) {
                alpha = 0xFE;
            }
            arg0[0x1F] = alpha;
        }
    } else if (alpha != 0) {
        alpha -= D_800BE9E4 << 4;
        if (alpha < 0) {
            alpha = 0;
        }
        arg0[0x1F] = alpha;
    }
    if (arg0[0x24] == 0 && alpha == 0) {
        return 1;
    }
    func_1516FDD4(arg0);
    if (arg0[0x2F] != 0) {
        func_1516FE5C((s32) arg0, func_151EFDD0() % 32 + 0xE6);
        func_1516FE8C((s32) arg0, func_151EFDD0() % 32 + 0xE6);
    } else {
        vel = (*(s8 *) (arg0 + 0x26) << 8) + arg0[0x27];
        // the asm squares the +0x26 velocity twice (not +0x28); u32 keeps its wrap-around at vel = -0x8000
        if ((s32) ((u32) vel * vel + (u32) vel * vel) > 2000) {
            func_1516FE5C((s32) arg0, func_151EFDD0() % 32 + 0xDC);
            func_1516FE8C((s32) arg0, func_151EFDD0() % 32 + 0xDC);
        }
    }
    *(s16 *) (arg0 + 0x18) = 0;
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_15170D50.s")
#endif

s32 func_151705A4(s32, f32 *, f32 *, f32 *);
void func_15170F24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, u8 arg5, s32 arg6) {
    s32 q0; // fakematch: unused locals pad the frame to 0xF8
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 a;
    s32 b;
    s32 p0, p1; // fakematch: unused locals pad the frame

    for (i = 0; i < arg3; i++) {
        func_151705A4(0x40, &x, &y, &z);
        x *= arg4;
        y *= 2.0f * arg4;
        z *= arg4;
        a = x;
        b = z;
        func_1516DA58(arg0, arg1, arg2, 0x2F, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 0, 7, a >> 8, a & 0xFF, b >> 8, b & 0xFF, 0, 0, 0, 0, 0, 0, 0x200, 0x200, 0x28, y, 0, 0, arg5, arg6);
    }
}
