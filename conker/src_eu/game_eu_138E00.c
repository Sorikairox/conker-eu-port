#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_1501B22C(s32);
#endif


#ifdef NON_MATCHING
extern f32 D_800D3A90;
extern f32 D_800D9F3C;
extern f32 D_800D9F40;
extern Mtx D_800D9F48;
extern s16 D_800DD722;
extern s16 D_800DD724;
extern f32 D_800A2FF0;
void func_151F0114(void *, float, float, float, float, float, float, float);

/* screen size from D_800DD722/4, then an orthographic projection (guOrtho) over the current camera extent */
void func_1510B5F0(s32 arg0) {
    f32 w;
    f32 h;

    D_800D9F40 = (f32)D_800DD722;
    D_800D9F3C = (f32)D_800DD724;
    D_800D3A90 = 100.0f - D_800D9F3C;
    h = ((f32 *)((u8 *)D_800BE628 + 0x10))[0];
    w = ((f32 *)((u8 *)D_800BE628 + 0xC))[0];
    func_151F0114(&D_800D9F48, -w, w, -h, h, 1.0f, D_800A2FF0, 1.0f);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510B5F0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510B6A8.s")

s32 func_1510B6A8(s32, f32, f32, f32, f32);
struct V3 { f32 x, y, z; };
extern struct V3 D_800D9EE0[];
extern u8 D_800D9F10;
void func_1510B8AC(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    func_1510B6A8(arg0, arg1, arg2, arg3, 0.0f);
    D_800D9EE0[arg0].x = arg3;
    D_800D9EE0[arg0].y = arg1;
    D_800D9EE0[arg0].z = arg2;
    D_800D9F10 = 1;
}

void func_1510B930(void)
{
    s32 i;
    for (i = 0; i <= D_80082FA0; i++) {
        if (D_800D9EE0[i].x != -1.0f) {
            func_1510B6A8(i, D_800D9EE0[i].y, D_800D9EE0[i].z, D_800D9EE0[i].x, 0.0f);
            D_800D9EE0[i].x = -1.0f;
        }
    }
    D_800D9F10 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510B9D8.s")

#ifdef NON_MATCHING
// Apply the pending per-player requests queued in D_800D9F18 (x == -1.0f: none) through func_1510BB78,
// with the player's camera record (D_800BE628, 0x180 bytes each).
struct PendingF2 { f32 x, y; };
extern struct PendingF2 D_800D9F18[];
extern u8 D_800D9F38;
void func_1510BB78(s32 arg0, u16 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);

void func_1510BA9C(void) {
    s32 i;
    u8 *cam;

    for (i = 0; i <= D_80082FA0; i++) {
        if (D_800D9F18[i].x != -1.0f) {
            cam = (u8 *)D_800BE628 + i * 0x180;
            func_1510BB78(i, (u16 *)(cam + 0xB8), *(f32 *)(cam + 0x78), *(f32 *)(cam + 0x74), D_800D9F18[i].x,
                          D_800D9F18[i].y, *(f32 *)(cam + 0x84));
            D_800D9F18[i].x = -1.0f;
        }
    }
    D_800D9F38 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BA9C.s")
#endif
#ifdef NON_MATCHING
void func_1510BB78(s32 arg0, u16 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    s32 sp2C;
    s32 temp_v0;
    s32 temp_v1;

    temp_v1 = arg0 * 0x180;
    sp2C = temp_v1;
    guPerspectiveF(D_800BE628 + temp_v1 + 0xBC, arg1, arg2, arg3, arg4, arg5, arg6);
    temp_v0 = D_800BE628 + temp_v1;
    guMtxF2L(temp_v0 + 0xBC, temp_v0 + (D_800BE9C0 << 6) + 0x100);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BB78.s")
#endif
#ifdef NON_MATCHING
extern f32 D_800DA030[][4][4];   /* per player: view matrix (float) */
extern f32 D_800DA130[][4][4];   /* per player: product */
extern u8 *D_800DC6D0[];         /* per DL buffer: fixed-point view matrices, 0x40 per player */

/* Per-player matrix refresh (P15, hand C from the asm): converts this frame's fixed-point projection
 * (player record + 0x100 in D_800BE628, 0x180 per player, 0x40 per DL buffer) and view matrix to float,
 * multiplies them into D_800DA130[i] and runs the per-player update func_1501B22C(i). */
void func_1510BC10(void) {
    f32 proj[4][4];
    s16 i;

    for (i = 0; i <= D_80082FA0; i++) {
        guMtxL2F(proj, (Mtx *)(D_800BE628 + i * 0x180 + D_800BE9C0 * 0x40 + 0x100));
        guMtxL2F(D_800DA030[i], (Mtx *)(D_800DC6D0[D_800BE9C0] + i * 0x40));
        func_150A7A48(D_800DA030[i], proj, D_800DA130[i]);
        func_1501B22C(i);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BC10.s")
#endif
#ifdef NON_MATCHING
u8 *func_1510BD34(u8 *arg0, s32 arg1) {
    u8 *temp_a0;
    u8 *temp_a0_10;
    u8 *temp_a0_11;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_a0_8;
    u8 *temp_a0_9;

    (*(s32 *)((u8 *)arg0 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    temp_a0_2 = arg0 + 8;
    (*(s32 *)((u8 *)temp_a0_2 + 4)) = 1;
    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xF9000000;
    temp_a0_3 = temp_a0_2 + 8;
    (*(s32 *)((u8 *)temp_a0_3 + 0)) = 0xDA380003;
    (*(u8 **)((u8 *)temp_a0_3 + 4)) = D_80089810;
    temp_a0_4 = temp_a0_3 + 8;
    (*(s32 *)((u8 *)temp_a0_4 + 0)) = 0xDB0E0000;
    temp_a0_5 = temp_a0_4 + 8;
    (*(s32 *)((u8 *)temp_a0_4 + 4)) = (s32) (*(u16 *)((u8 *)((D_800BE628 + (arg1 * 0x180))) + 0xB8));
    (*(s32 *)((u8 *)temp_a0_5 + 4)) = 3;
    (*(s32 *)((u8 *)temp_a0_5 + 0)) = 0xDB040004;
    temp_a0_6 = temp_a0_5 + 8;
    (*(s32 *)((u8 *)temp_a0_6 + 0)) = 0xDB04000C;
    (*(s32 *)((u8 *)temp_a0_6 + 4)) = 3;
    temp_a0_7 = temp_a0_6 + 8;
    (*(s32 *)((u8 *)temp_a0_7 + 0)) = 0xDB040014;
    (*(s32 *)((u8 *)temp_a0_7 + 4)) = 0xFFFD;
    temp_a0_8 = temp_a0_7 + 8;
    (*(s32 *)((u8 *)temp_a0_8 + 0)) = 0xDB04001C;
    (*(s32 *)((u8 *)temp_a0_8 + 4)) = 0xFFFD;
    temp_a0_9 = temp_a0_8 + 8;
    (*(s32 *)((u8 *)temp_a0_9 + 0)) = 0xD9EFFFFF;
    (*(s32 *)((u8 *)temp_a0_9 + 4)) = 0;
    temp_a0_10 = temp_a0_9 + 8;
    (*(s32 *)((u8 *)temp_a0_10 + 0)) = 0xDA380007;
    (*(s32 *)((u8 *)temp_a0_10 + 4)) = (s32) (D_800BE628 + (arg1 * 0x180) + (D_800BE9C0 << 6) + 0x100);
    temp_a0_11 = temp_a0_10 + 8;
    (*(s32 *)((u8 *)temp_a0_11 + 0)) = 0xDA380005;
    temp_a0 = temp_a0_11 + 8;
    (*(s32 *)((u8 *)temp_a0_11 + 4)) = (s32) (*(s32 *)((u8 *)&D_800DC6D0 + (D_800BE9C0 * 4)) + (arg1 << 6));
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xEF082C3F;
    (*(s32 *)((u8 *)temp_a0 + 4)) = 0x552230;
    return temp_a0 + 8;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BD34.s")
#endif
#ifdef NON_MATCHING
extern f32 D_800D3A00;

void func_1510BED8(s32 arg0) {
    u8 *temp_v0;

    temp_v0 = D_800BE628 + (arg0 * 0x180);
    D_800D3A00 = ((((*(f32 *)((u8 *)temp_v0 + 0x74)) / (*(f32 *)((u8 *)temp_v0 + 0x6C))) - 1.0f) * -1.0f) + (*(f32 *)((u8 *)temp_v0 + 0x64));
    *(((f32 *)((u8 *)&D_800D3A00 + 4))) = ((((*(f32 *)((u8 *)temp_v0 + 0x78)) / (*(f32 *)((u8 *)temp_v0 + 0x70))) - 1.0f) * -1.0f) + (*(f32 *)((u8 *)temp_v0 + 0x68));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BED8.s")
#endif
#ifdef NON_MATCHING
Gfx *func_150A55A0(s32, Gfx *, u8 *, s32, s32, s32);
Gfx *func_150A5858(s32, Gfx *, u8 *, s32, s32, s32);
Gfx *func_150C8B00(Gfx *);
Gfx *func_150CFAF8(Gfx *);
Gfx *func_150D7B6C(Gfx *);
Gfx *func_150E0150(Gfx *);
Gfx *func_151009E4(Gfx *);
void func_1510D090(s16);
Gfx *func_1510D338(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3);
Gfx *func_1512EB60(Gfx *, struct108 *);
Gfx *func_1515DE84(Gfx *, s16, s32, s32, s32, s32, s32, s32, u8 *, u8 *, s32, s32, s32, u8 *);
Gfx *func_1515EAB4(Gfx *, s32, u8, s32, u8 *);
Gfx *func_15173948(Gfx *, s32);
Gfx *func_1517485C(Gfx *, s16);
extern s32 D_800B1214;          /* optional display lists */
extern s32 D_800B1218;
extern u8 D_800BEECA;
extern u8 D_800BEFC0;
extern u8 D_800C3A86;
extern u8 D_800D9FB0[];         /* viewports: [buffer][2] x 16 bytes */
extern u8 D_800D9FF0[];         /* per player: [buffer] x 8 bytes */
extern s32 D_800DA230[];        /* per player */
extern u8 D_800DA240;
extern u8 D_800DA241;
extern u8 D_800DA248;

/* Build the display list of player `player`'s view. */
Gfx *func_1510BF50(Gfx *gdl, s16 player) {
    struct108 *p = &D_800DBFF0[player];
    s32 skipWorld;
    s32 mask;
    u8 *vpPtr;
    s32 *dataPtr;

    D_800BEFC0 = 1;
    skipWorld = FALSE;
    if ((D_800C35EA == 1) && (D_800C3A86 != 0)) {
        skipWorld = TRUE;
    }
    mask = 1 << player;
    if (D_800D18A0 & mask) {
        skipWorld = TRUE;
    }

    gdl = (Gfx *)func_1510BD34((u8 *)gdl, player);
    gdl[0].words.w0 = 0xDC08000A;
    gdl[0].words.w1 = (u32)(D_800D9FB0 + (D_800BE9C0 << 5));
    gdl[1].words.w0 = 0xDC08060A;
    gdl[1].words.w1 = (u32)(D_800D9FB0 + (D_800BE9C0 << 5) + 0x10);
    gdl += 2;
    func_1510D090(player);
    gdl = func_15173948(func_1510D338(gdl, 0xFF, 0xFF, player), 1);
    gdl->words.w0 = 0xDA380003;
    gdl->words.w1 = (u32)D_80089810;
    gdl++;

    if (!skipWorld) {
        switch (D_800BE9F0) {
        case 0x14:
            gdl = func_150C8B00(gdl);
            break;
        case 0x1A:
            gdl = func_151009E4(gdl);
            break;
        case 0x13:
            gdl = func_150E0150(gdl);
            break;
        case 0x35:
            gdl = func_150CFAF8(gdl);
            break;
        case 0x33:
            gdl = func_150D7B6C(gdl);
            break;
        }
    }

    func_1510F800(0);
    if (D_800DCD7C == 0) {
        gdl->words.w0 = 0xDC280C0A;
        gdl->words.w1 = (u32)(D_800D9FF0 + player * 0x10 + D_800BE9C0 * 8);
        gdl++;
    }

    p = (struct108 *)((u8 *)D_800DBFF0 + player * 0x9A0);
    dataPtr = &D_800DA230[player];
    vpPtr = D_800D9FF0 + player * 0x10;
    gdl = func_1515DE84(gdl, player, (s32)p->unk2F8, (s32)p->unk2FC, (s32)p->unk300, 0, *dataPtr, D_800DA240,
                        vpPtr + D_800BE9C0 * 8, &D_800DA241, 1, 0, 0x25, &D_800DA248);

    if (!skipWorld) {
        if (D_800BE9F0 != 5) {
            if (D_800BEECA != 0) {
                gDPPipeSync(gdl++);
                if (D_800DBE62 != 0) {
                    if ((D_800BE9F0 != 0x14) && (D_800BE9F0 != 0x33) && (D_800BE9F0 != 0x32)) {
                        gdl = func_150A5858(D_800B0E00[0], gdl, (u8 *)D_800DA030[player], 0, 0, mask);
                    } else {
                        gdl->words.w0 = 0xDE000000;
                        gdl->words.w1 = D_800B0E00[0];
                        gdl++;
                    }
                    if (D_800B1214 != 0) {
                        gDPPipeSync(gdl++);
                        gdl = func_15173948(func_1510D338(gdl, 0xFF, 0xFF, player), 1);
                        if (D_800BE9F0 == 0x35) {
                            gdl = func_150CFAF8(gdl);
                        }
                        gdl->words.w0 = 0xDE000000;
                        gdl->words.w1 = D_800B1214;
                        gdl++;
                    }
                    D_800BEFC0 = 0;
                    p = &D_800DBFF0[player];
                    if ((p->pad880[0x38] != 0) && (p->unk84 & 8)) {
                        gdl = func_1512EB60(gdl, p);
                        gDPPipeSync(gdl++);
                    }
                } else {
                    gdl->words.w0 = 0xDE000000;
                    gdl->words.w1 = D_800B0E00[0];
                    gdl++;
                }
            } else {
                gdl->words.w0 = 0xDE000000;
                gdl->words.w1 = D_800B0E00[0];
                gdl++;
            }
        }
        gdl = func_1515EAB4(gdl, *dataPtr, D_800DA240, D_800DA241, vpPtr + D_800BE9C0 * 8);
        if (D_800B1218 != 0) {
            gDPPipeSync(gdl++);
            gdl = func_1510D338(gdl, 0xFF, 0xFF, player);
            gdl->words.w0 = 0xDE000000;
            gdl->words.w1 = D_800B1218;
            gdl++;
        }
    }
    gdl = func_1517485C(gdl, player);
    gDPPipeSync(gdl++);
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BF50.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510C4E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510CA2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510CE28.s")
