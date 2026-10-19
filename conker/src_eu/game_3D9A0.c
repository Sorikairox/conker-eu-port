#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// ???
#pragma GLOBAL_ASM("asm/nonmatchings/game_3D9A0/func_150104F0.s")

void func_15010538(struct127 *arg0) {
    struct175 tmp;
    struct37 *temp_v0;

    func_15161E24(arg0, 2, 2, 300, 30, 100, 200, 255, 255, 1);
// FAKEMATCH but works...
dummy_label_927029:
    tmp.unk0 = arg0;
    tmp.unk4 = arg0->unique_id;
    tmp.unk6 = 0;
    tmp.unk8 = 0;
    tmp.unkA = 0;

    temp_v0 = func_15149130(300, -1, 80, -1, 0, 61, 12, 255, 1);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 12); // memcpy
    }
}

extern u8 D_800D9D40;
extern u8 D_800D9D41;
extern u8 D_800D9D48;
extern u8 D_800D9D49;
extern u8 D_800D9D4A[];
extern u8 D_800D9D58;
extern u8 D_800D9D59;
extern u8 D_800D9D5A[];
void func_15010600(void)
{
  s32 i;
  D_800D9D41 = 0;
  D_800D9D40 = 0;
  D_800D9D48 = 0;
  D_800D9D58 = 0;
  D_800D9D49 = 0;
  for (i = 0; i < 12; i++)
  {
    D_800D9D59 = 0; // fakematch: store inside the loop schedules after the pointer setup
    D_800D9D4A[i] = 0;
    D_800D9D5A[i] = 0;
  }

}
// NON-MATCHING: addresses are wrong :(
// void func_15010600(void) {
//     s32 i;
//
//     for (i = 0; i < 11; i++) {
//         D_800D9930[i] = D_800D9920[i] = 0;
//     }
// }
