#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_150039E0.s")

// FIXME: matches but something isnt right
void func_15004574(void) {
    if (D_800DBF88 != 0xFF) {
        D_800DBF8C = D_800DBEF4[D_800DBF88].unk1C;
        D_800DBF90 = D_800DBEF4[D_800DBF88].unk28;
    }
}

void func_150045BC(void) {
}

#ifdef NON_MATCHING
void func_15004A4C(void);
void func_15114E8C(f32 (*arg0)[4], u8 *arg1);
void func_150A7E40(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ);
void func_1510F800(s32 arg0);
s32 func_150A49D0(s32 count, s32 *idList, s32 force);
void func_1510ED24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD);
void func_15115630();
void func_151165D8();
void func_15116690();
extern f32 D_800DC338[4][4];
extern f32 D_800DC378[4][4];
extern Mtx **D_800895F0[2];       /* per DL buffer: -> the world-object matrix array (0x40 each) */
extern u16 D_800D3C00;

/* Level start for the D_800DC320 world objects (0xA0-byte records at D_800DBEF4): reset, identity camera matrices,
 * then per object: kind 3 for no/known callbacks, its matrix (func_15114E8C) into both DL buffers' D_800895F0
 * arrays unless static (+0x70 bit 0); static objects get their vertices (+0x28, 0x10 stride) transformed once into
 * +0x20 and copied to +0x24; func_150A49D0 for flagged ones. Second pass: func_1510ED24 per visible object
 * (bounds from +0x10/+0x12/+0x14, range -10000..20000) into +0x80/+0x84. arg0 (the level) is unused. */
void func_150045C4(s32 arg0) {
    f32 mf[4][4];     /* sp+0x98 */
    f32 ox, oy, oz;   /* sp+0x84, 0x80, 0x7C */
    s32 out0;         /* sp+0x88 */
    f32 out1;         /* sp+0x8C */
    s32 out2;         /* sp+0x90 */
    u8 *r;
    s16 *v;
    s16 *w;
    s32 i, j;
    s32 b;
    void *cb;

    func_15004A4C();
    guMtxIdentF(D_800DC338);
    guMtxIdentF(D_800DC378);
    for (i = 0; i < D_800DC320; i++) {
        r = (u8 *)D_800DBEF4 + i * 0xA0;
        cb = *(void **)(r + 0x38);
        if (cb == NULL || cb == (void *)func_151165D8 || cb == (void *)func_15116690) {
            r[0x4E] = 3;
        }
        if (!(r[0x70] & 1)) {
            func_15114E8C(mf, r);
            guMtxF2L(mf, *D_800895F0[D_800BE9C0] + i);
            b = D_800BE9C0;
            bcopy(*D_800895F0[b] + i, *D_800895F0[b == 0] + i, 0x40);
        }
        if (*(void **)(r + 0x38) == (void *)func_15115630) {
            *(void **)(r + 0x38) = NULL;
        }
        if ((r[0x70] & 1) == 1) {
            func_15114E8C(mf, r);
            for (j = 0; j < *(u16 *)(r + 0x16); j++) {
                v = (s16 *)(*(u8 **)(r + 0x28) + j * 0x10);
                func_150A7E40(mf, v[0], v[1], v[2], &ox, &oy, &oz);
                w = (s16 *)(*(u8 **)(r + 0x20) + j * 0x10);
                w[0] = (s32)ox;
                w = (s16 *)(*(u8 **)(r + 0x20) + j * 0x10);
                w[1] = (s32)oy;
                w = (s16 *)(*(u8 **)(r + 0x20) + j * 0x10);
                w[2] = (s32)oz;
            }
            bcopy(*(void **)(r + 0x20), *(void **)(r + 0x24), *(u16 *)(r + 0x16) << 4);
        }
        func_1510F800(2);
        if ((r[0x6F] & 0x80) == 0x80 && (r[0x4F] & 0x60) != 0x20) {
            D_800D3C00 = i;
            func_150A49D0(1, (s32 *)&D_800D3C00, 1);
        }
    }
    for (i = 0; i < D_800DC320; i++) {
        r = (u8 *)D_800DBEF4 + i * 0xA0;
        if (r[0x6E] == 1) {
            continue;
        }
        if ((r[0x6F] & 0x20) != 0x20) {
            continue;
        }
        func_1510ED24((s32)&out0, 0, (s32)&out1, 0, (s32)&out2, 0, *(s16 *)(r + 0x10), *(s16 *)(r + 0x12),
                      *(s16 *)(r + 0x14), *(s16 *)(r + 0x12), i + 1, 0, -10000.0f, 20000.0f);
        *(s32 *)(r + 0x80) = out0;
        *(f32 *)(r + 0x84) = out1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_150045C4.s")
#endif
void func_150049A4(Gfx *arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; ((struct_eu_cmd8 *)&arg0[i])->cmd != -0x21; i++) {
        switch (((struct_eu_cmd8 *)&arg0[i])->cmd) {
            case 0xDE:
                ((struct_eu_cmd8 *)&arg0[i])->unk4 += arg1;
                break;
            case 1:
                ((struct_eu_cmd8 *)&arg0[i])->unk4 += arg1;
                break;
            case -0x24:
                if (((struct_eu_cmd8 *)&arg0[i])->unk3 == 0xE) {
                    ((struct_eu_cmd8 *)&arg0[i])->unk4 += arg2;
                }
                break;
        }
    }
}
void func_15004A4C(void) {
    s32 i;

    for (i = 0; i < D_800DC320; i++) {
        D_800DC328[i] = 0;
        D_800DC32C[i] = 0;
    }
}

#ifdef NON_MATCHING
extern u16 D_800BE6C0;
extern u16 D_800BE6C2;
extern u16 D_800BE6C4;

void func_15004AAC(u8 *arg0, s32 arg1) {
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f18;
    f32 temp_f2;
    s32 temp_f10;
    s32 temp_f4;
    s32 temp_f8;
    s32 var_a2;
    s32 var_v0;
    u16 temp_a1;
    u16 temp_v1;
    u8 *var_a3;

    temp_a1 = (*(u16 *)((u8 *)arg0 + 0x16));
    var_v0 = 0;
    var_a2 = 0;
    if ((s32) temp_a1 > 0) {
        var_a3 = (*(u8 **)((u8 *)arg0 + 0x28));
        do {
            var_a2 += 0x10;
            temp_f2 = (f32) (*(s16 *)((u8 *)var_a3 + 4)) * (*(f32 *)((u8 *)arg0 + 0x34));
            temp_f14 = (f32) (*(s16 *)((u8 *)var_a3 + 0)) * (*(f32 *)((u8 *)arg0 + 0x2C));
            temp_f18 = (f32) (*(s16 *)((u8 *)var_a3 + 2)) * (*(f32 *)((u8 *)arg0 + 0x30));
            temp_f10 = (s32) ((temp_f2 * temp_f2) + ((temp_f14 * temp_f14) + (temp_f18 * temp_f18)));
            if (var_v0 < temp_f10) {
                var_v0 = temp_f10;
            }
            var_a3 += 0x10;
        } while (var_a2 < (temp_a1 * 0x10));
    }
    if (var_v0 != 0) {
        temp_v1 = (*(u16 *)((u8 *)arg0 + 0x50));
        temp_f0 = sqrtf((f32) var_v0);
        if (temp_v1 == 0) {
            temp_f4 = (s32) temp_f0;
            (*(u16 *)((u8 *)arg0 + 0x50)) = (u16) temp_f4;
            (*(u16 *)((u8 *)arg0 + 0x52)) = (u16) temp_f4;
            D_800BE6C2 += 1;
            return;
        }
        temp_f8 = (s32) temp_f0;
        if (((s32) temp_v1 < temp_f8) || ((s32) (*(u16 *)((u8 *)arg0 + 0x52)) < temp_f8)) {
            D_800BE6C0 += 1;
            return;
        }
        D_800BE6C4 += 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_15004AAC.s")
#endif
s32 func_15004BF0(s32 arg0) {
    s32 i;
    s32 id;
    s32 first;

    if (arg0 == 0) {
        id = 1;
        for (i = D_800DBF00; i < D_800DC320; i++) {
            if (id == D_800DBEF4[i].pad70[2]) {
                id++;
                i = D_800DBF00 - 1;
            }
            if (id >= 0x100) {
                id = 0xFF;
                break;
            }
        }
    } else {
        first = 0xFF - D_800DBF00;
        id = first;
        for (i = 0; i < D_800DC320; i++) {
            if (id == D_800DBEF4[i].pad70[2]) {
                id--;
                i = -1;
            }
            if (id <= 0) {
                id = first;
                break;
            }
        }
    }
    return id;
}
void func_15004CE0(Gfx *arg0, s32 arg1) {
    s32 i;
    struct_eu_cmd8 *p;

    for (i = 0; ((struct_eu_cmd8 *)&arg0[i])->cmd != -0x21; i++) {
        p = (struct_eu_cmd8 *)&arg0[i];
        if (p->cmd == -0x24 && p->unk3 == 0xE && p->unk4 < 0x80000000) {
            p->unk4 += arg1;
        }
    }
}
