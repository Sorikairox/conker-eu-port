#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 D_8002AE18;
extern u64 D_8002C060;
extern OSMesgQueue D_8003B578;
extern OSTimer D_800BEB00;
void func_1501BB20(void) {
    if (D_8002AE18 != 0) {
        osSetTimer(&D_800BEB00, (25ULL * D_8002C060) / 1000000ULL, 0, &D_8003B578, (void *)6);
        D_8002AE18 = 0;
    }
}

#ifdef NON_MATCHING
extern u8 D_8002AE18;
extern OSMesg D_800BEDB0;
extern u8 D_800BEB60;
extern u8 D_800E0FC5;
extern u16 D_800BEB20[4];
extern u16 D_800BEB28[4];
extern u16 D_800BEB30[4];
extern u16 D_800BEB38[4];
extern OSContPad D_800BED38[4];
extern u16 D_800BED50[4];
void func_151DDE70(void);
void func_1501C55C(void);

/* Stick dead zone: |v| < 8 -> 0, otherwise move v 7 towards 0. */
#define DEADZONE(v) ((((v) < 0) ? -(v) : (v)) >= 8 ? (v) - (((v) < 0) ? -1 : 1) * 7 : 0)

/* Per-frame controller read: fetch the 4 pads, map them to players, compute the edge masks
 * and apply the stick dead zone. Returns the player input block. */
struct14 *func_1501BBB8(void) {
    OSContPad pads[4];
    OSContPad *player = (OSContPad *)D_800BE748;
    s32 i;
    s32 nplayers;
    s32 replay;
    u8 idx;

    for (i = 0; i < 4; i++) {
        D_800BEB38[i] = player[i].button;
    }
    osRecvMesg(&D_800BE900, &D_800BEDB0, OS_MESG_BLOCK);
    osContGetReadData(pads);
    func_1501C55C();
    D_8002AE18 = 1;
    D_800BEB60 = 0;
    for (i = 0; i < 4; i++) {
        if (pads[i].errno != 0) {
            pads[i].button = 0;
            pads[i].stick_x = 0;
            pads[i].stick_y = 0;
        } else {
            D_800BEB60 |= 1 << i;
        }
    }

    nplayers = 4;
    if (D_800BE9F0 != 0x1D) {
        nplayers = D_80090130;
    }
    for (i = 0; i < 4; i++) {
        idx = D_800843F0[i];
        if (idx < 4 && i < nplayers) {
            player[i].stick_x = pads[idx].stick_x;
            player[i].stick_y = pads[idx].stick_y;
            player[i].button = pads[idx].button | D_800BE720[idx];
            D_800BE720[idx] = 0;
        } else {
            player[i].button = 0;
            player[i].stick_x = 0;
            player[i].stick_y = 0;
        }
    }

    for (i = 0; i < 4; i++) {
        D_800BED50[i] = ~D_800BEB28[i] & player[i].button;
        D_800BED38[i].button = player[i].button;
        D_800BEB28[i] = player[i].button;
        D_800BED38[i].stick_x = DEADZONE(player[i].stick_x);
        D_800BED38[i].stick_y = DEADZONE(player[i].stick_y);
    }

    if (D_800E0B94 == 2 || D_800E0FC5 == 2) {
        replay = 1;
        func_151DDE70();
    } else {
        replay = 0;
    }

    for (i = 0; i < 4; i++) {
        D_800BEB30[i] = ~D_800BEB20[i] & player[i].button;
        D_800BEB20[i] = player[i].button;
        if (replay == 0) {
            player[i].stick_x = DEADZONE(player[i].stick_x);
            player[i].stick_y = DEADZONE(player[i].stick_y);
        }
    }
    return &D_800BE730;
}
#undef DEADZONE
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501BBB8.s")
#endif
extern f32 D_80096D10;
void func_1501C0D0(u8, f32, f32);
void func_1501BFF0(u8 arg0, u8 arg1)
{
  f32 t;
  f32 a;
  f32 b;
  if (arg1 >= 9) {
    arg1 = 8;
  }
  if (arg1 == 8) {
    a = 20.0f;
    b = 0.0f;
  } else if (arg1 == 0) {
    a = 0.0f;
    b = 99.0f;
  } else {
    t = ((f32)(u32)arg1 - 1) * D_80096D10 * 5.0f;
    a = t + 2.0f;
    b = 7.0f - t;
  }
  func_1501C0D0(arg0, a, b);
}

extern u8 D_800BED64[];
extern f32 D_800BED70[];
extern f32 D_800BED80[];
extern f32 D_800BED90[];
extern f32 D_800BEDA0[];
void func_1501C0D0(u8 arg0, f32 arg1, f32 arg2) {
    s32 idx;
    idx = D_800843F0[arg0];
    if (idx < 4 && D_800BED64[idx] != 0) {
        D_800BED5C[idx] = 1;
        D_800BED70[idx] = 0.0f;
        D_800BED80[idx] = arg1;
        D_800BED90[idx] = arg2;
        D_800BEDA0[idx] = arg1 + arg2;
    }
}

void func_1501C15C(u8 arg0) {
    s32 temp_v0 = D_800843F0[arg0];

    if (temp_v0 < 4) {
        D_800BED5C[temp_v0] = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501C1B0.s")

void func_1501C51C(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        func_1501C15C(i);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501C55C.s")
