#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510B5F0.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510B930.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510B9D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BA9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BB78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BC10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BD34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BED8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BF50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510C4E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510CA2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510CE28.s")
