#include <ultra64.h>

#include "functions.h"
#include "variables.h"

// MP3-style stream decoder state (game_221290). Needs OPT_FLAGS := -g.
typedef struct struct_eu_221290 {
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 (*unk4)(s32, u8 *, s32, s32);
    /* 0x0008 */ s32 unk8;
    /* 0x000C */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001C */ u8 unk1C[0x2000];
    /* 0x201C */ s32 unk201C;
    /* 0x2020 */ s32 unk2020;
    /* 0x2024 */ u8 pad2024[0x2070 - 0x2024];
    /* 0x2070 */ u8 unk2070[6][0x488];
    /* 0x3BA0 */ s32 unk3BA0;
    /* 0x3BA4 */ s32 unk3BA4;
    /* 0x3BA8 */ u8 pad3BA8[0x3BB4 - 0x3BA8];
    /* 0x3BB4 */ s32 unk3BB4;
    /* 0x3BB8 */ u8 pad3BB8[0x3BC8 - 0x3BB8];
    /* 0x3BC8 */ s32 unk3BC8;
    /* 0x3BCC */ u8 pad3BCC[0x3C98 - 0x3BCC];
    /* 0x3C98 */ s32 unk3C98[2];
    /* 0x3CA0 */ s32 unk3CA0[2];
    /* 0x3CA8 */ s32 unk3CA8[2];
    /* 0x3CB0 */ u8 pad3CB0[0x3F88 - 0x3CB0];
    /* 0x3F88 */ s32 unk3F88;
    /* 0x3F8C */ s32 unk3F8C;
    /* 0x3F90 */ u8 pad3F90[0x4664 - 0x3F90];
    /* 0x4664 */ f32 unk4664[576];
    /* 0x4F64 */ f32 unk4F64[576];
    /* 0x5864 */ u8 pad5864[0x6A64 - 0x5864];
    /* 0x6A64 */ u8 unk6A64[0x900];
    /* 0x7364 */ u8 pad7364[0x8474 - 0x7364];
    /* 0x8474 */ s32 unk8474;
    /* 0x8478 */ s32 (*unk8478)(struct struct_eu_221290 *);
} struct_eu_221290;

extern struct_eu_221290 D_800E1CB0;
extern s16 D_800AEF8C[][3][576];
extern s32 D_800E0E04;
extern void (*D_800E1230)(s32, u8 *, s32);
s32 func_151F8088(struct_eu_221290 *arg0, s32 arg1);




#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F3DE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F42E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F4F38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F578C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F63C4.s")
s32 func_151F6970(struct_eu_221290 *arg0, s32 ch) {
    s16 *table;
    f32 *dst;
    f32 *src;
    s32 i;

    table = D_800AEF8C[arg0->unk3BA4][arg0->unk3BB4];
    dst = arg0->unk4F64;
    src = arg0->unk4664;
    i = 0;
    if ((arg0->unk3C98[ch] != 0) && (arg0->unk3CA0[ch] == 2)) {
        if (arg0->unk3CA8[ch] != 0) {
            while (i++ < 36) {
                *dst++ = *src++;
            }
        }
        while (i < 576) {
            dst[table[i++]] = *src++;
        }
    } else {
        while (i++ < 576) {
            *dst++ = *src++;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F6B28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F6FD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F78B4.s")
s32 func_151F7F60(struct_eu_221290 *arg0) {
    s32 sp1C;
    s32 sp18;

    sp1C = 0x1000;
    if ((arg0->unk201C + arg0->unk3F88) >= 0x1FFC) {
        bcopy(arg0->unk1C + sp1C, arg0->unk1C, sp1C);
        arg0->unk201C -= sp1C;
        arg0->unk2020 -= sp1C * 8;
    }
    sp18 = arg0->unk4(arg0->unk0, arg0->unk1C + arg0->unk201C, arg0->unk3F88, -1);
    if (sp18 < arg0->unk3F88) {
        bzero(arg0->unk1C + sp18, arg0->unk3F88 - sp18);
    }
    arg0->unk18 += arg0->unk3F88;
    arg0->unk201C += arg0->unk3F88;
    return arg0->unk201C - arg0->unk3F88;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F8088.s")
struct_eu_221290 *func_151F85C4(s32 arg0, s32 (*arg1)(s32, u8 *, s32, s32), s32 arg2) {
    struct_eu_221290 *sp1C;

    sp1C = &D_800E1CB0;
    if (sp1C == NULL) {
        return NULL;
    }
    sp1C->unkC = -1;
    sp1C->unk10 = -1;
    sp1C->unk14 = -1;
    sp1C->unk0 = arg0;
    sp1C->unk4 = arg1;
    sp1C->unk8 = arg2;
    sp1C->unk201C = 0;
    sp1C->unk2020 = 0;
    sp1C->unk3BA0 = 0;
    if (func_151F8088(sp1C, 0) == 0) {
        return NULL;
    }
    sp1C->unk8474 = 0;
    bzero(sp1C->unk6A64, 0x900);
    return sp1C;
}
s32 func_151F86B0(struct_eu_221290 *arg0, u8 **arg1, s32 *arg2) {
    struct_eu_221290 *sp12C;
    s32 sp128;
    u8 sp28[0x100];
    s32 sp24;

    sp12C = arg0;
    sp12C->unk3BA0++;
    if (sp12C->unk3BA0 >= 6) {
        sp12C->unk3BA0 = 0;
    }
    if (func_151F8088(sp12C, sp12C->unk8474) == 0) {
        D_800E0E04 = 3;
        return 0;
    }
    sp12C->unk8474 = -1;
    sp128 = sp12C->unk8478(sp12C);
    if (sp128 == 0) {
    } else {
        *arg1 = sp12C->unk2070[sp12C->unk3BA0];
        *arg2 = sp12C->unk3F8C;
        if (sp12C->unk3BC8 != 0) {
            sp24 = 0;
            do {
                if (sp12C->unk4(sp12C->unk0, &sp28[sp24], 1, -1) == 0) {
                    break;
                }
            } while (sp28[sp24++]);
            if (D_800E1230 != NULL) {
                D_800E1230(0, sp28, strlen(sp28) + 1);
            }
        }
    }
    return sp128;
}
