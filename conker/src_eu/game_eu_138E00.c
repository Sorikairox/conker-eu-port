#include <ultra64.h>
#include "functions.h"
#include "variables.h"


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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BA9C.s")

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BC10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BD34.s")

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510BF50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510C4E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510CA2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_138E00/func_1510CE28.s")
