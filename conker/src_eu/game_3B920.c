#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_15004FE0(s32);
void func_1500AC14(void);
s32 func_1500BEC0();
void func_1500E5C0(void);
void func_15012370(void);
s32 func_15012760();
void func_15012FE0(void);
void func_151645C4(u8);
void func_15173850(s32);
void func_15179420(void);
void func_15187820(s32);
void func_15195D9C(void);
void func_151EFE00(u32);
extern s32 D_80083120;
extern s8 D_80088F00;
extern s8 D_800DD834;
extern s8 D_800DD835;
extern s8 D_800DD836;
extern s32 D_800E0D64;
extern s32 D_eu_800BE900;

void func_1500E470(s32 arg0) {
    u8 temp_v0;

    D_800DD5C0 = -1;
    bzero(D_800DD5C8, 0x18);
    D_800DD834 = 0xFF;
    D_800DD835 = 0;
    D_800DD836 = 0;
    D_800E0930 = NULL;
    D_800E0D64 = 0;
    D_800E0940 = NULL;
    D_8008D0A0 = 0;
    D_80088F00 = 0;
    D_eu_800BE900 = 0;
    D_800E0A10 = func_15012720();
    func_15012370();
    func_151EFE00(0x40);
    func_15173850(arg0);
    func_15004FE0(arg0);
    func_15012760();
    func_15195D9C();
    func_15008BE0();
    func_15008B90();
    func_1500E5C0();
    temp_v0 = D_800B0DF0->unkA;
    if (temp_v0 != 0) {
        (*(s32 (**)())((u8 *)&D_80083120 + (temp_v0 * 4)))();
    }
    func_1500ABA0(arg0);
    func_1500BEC0();
    func_1500AC14();
    func_15187820(arg0);
    func_15179420();
    func_15012FE0();
    func_151645C4(((D_800D2E4C->unk4 & 0x80) == 0) & 0xFF);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_3B920/func_1500E470.s")
#endif
// NON-MATCHING: damn nops, is this -g ?
// void func_1500E470(s32 arg0) {
//     u8 tmp;
//     D_800DD190 = -1;
//     bzero(&D_800DD198, 24);
//     D_800DD404 = 0xFF;
//     D_800DD405 = 0;
//     D_800DD406 = 0;
//     D_800E0930 = 0;
//     D_800E0934 = 0;
//     D_800E0940 = 0;
//     D_8008CD00 = 0;
//     D_80088B60 = 0;
//     D_800BE4E0 = 0;
//     // is this handwritten?
//     D_800E0A10 = func_15012720();
//     func_15012370();
//
//     func_151EF640(64);
//     func_151732E0(arg0);
//     func_15004FE0(arg0);
//     func_150127B0();
//
//     func_1519582C();
//     func_15008BE0();
//     func_15008B90();
//     func_1500E5C0();
//
//     if (0) {};
//     if (D_800B0DF0->unkA) {
//         D_80082D90[D_800B0DF0->unkA]();
//     }
//     func_1500ABA0(arg0);
//     func_1500BEC0();
//     func_1500AC14();
//     func_151872B0(arg0);
//     func_15178EB0();
//     func_15012FE0();
//
//     if (0) {};
//     tmp = (D_800D2E4C->unk4 & 128) == 0;
//     func_151645C4(tmp);
// }
