#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800AB930[];
#endif


#ifdef NON_MATCHING
extern s32 D_800AB934;

/* was func_151DD390 */
void bounce_dust_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u2C;
        s32 u30;
        s32 u34;
        u8 pad38[0x8];
        s16 u40;
        s16 u42;
        s16 u44;
        s16 u46;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        s16 u58;
        s16 u5A;
        f32 u5C;
        f32 u60;
        f32 u64;
    } sp;

    sp.u2C = 0xC;
    sp.u30 = 5;
    (*(s32 *)((u8 *)(&sp.u34) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u34) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u34) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u40 = 0;
    sp.u42 = 0xFF;
    sp.u44 = -0x40;
    sp.u46 = 0x31;
    sp.u58 = 0x19;
    sp.u5A = 0x14;
    sp.u5C = 0.2f;
    sp.u60 = 0.2f;
    sp.u48 = 3.0f;
    sp.u4C = 9.0f;
    sp.u50 = -0.693f;
    sp.u54 = 0.30400002f;
    sp.u64 = 25.714f;
    emit_textured_burst(&sp.u2C, ((u8 *)&D_800AB930), &D_800AB934, 1, 26.0f, 0U, (u8) (s32) arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20ABA0/bounce_dust_spawn.s")
#endif