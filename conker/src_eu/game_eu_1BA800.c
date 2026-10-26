#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 node_spawn_sprite(s32 *, s32, s32, s32, s32, s32);
extern s32 D_8008CDEC;

void func_1518CFF0(u8 *arg0, s32 arg1) {
    struct {
        s32 u30;
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s16 u40;
        s16 u42;
        s16 u44;
        s16 u46;
        s16 u48;
        s16 u4A;
        u8 u4C;
        u8 u4D;
        u8 u4E;
        s8 u4F;
        s16 u50;
        s16 u52;
        s16 u54;
        s16 u56;
        s16 u58;
        s8 u5A;
        u8 u5B;
        s8 u5C;
        s8 u5D;
        s8 u5E;
        u8 u5F;
        s8 u60;
        s8 u61;
        s8 u62;
        u8 pad63[0x1];
        s16 u64;
    } sp;
    s32 temp_t0;
    u8 temp_v1;

    temp_v1 = (*(u8 *)((u8 *)arg0 + 0x2E));
    sp.u5C = (s8) ((s32) ((*(u8 *)((u8 *)arg0 + 0x28)) * temp_v1) >> 8);
    sp.u5D = (s8) ((s32) ((*(u8 *)((u8 *)arg0 + 0x29)) * temp_v1) >> 8);
    sp.u5E = (s8) ((s32) ((*(u8 *)((u8 *)arg0 + 0x2A)) * temp_v1) >> 8);
    sp.u60 = (s8) ((s32) ((*(u8 *)((u8 *)arg0 + 0x2B)) * temp_v1) >> 8);
    sp.u61 = (s8) ((s32) ((*(u8 *)((u8 *)arg0 + 0x2C)) * temp_v1) >> 8);
    sp.u62 = (s8) ((s32) ((*(u8 *)((u8 *)arg0 + 0x2D)) * temp_v1) >> 8);
    sp.u58 = (*(s16 *)((u8 *)arg0 + 0x26));
    sp.u5F = (*(u8 *)((u8 *)arg0 + 0x2F));
    sp.u3C = 0;
    sp.u3E = 0x100;
    sp.u30 = D_8008CDEC;
    sp.u5A = (*(s8 *)((u8 *)arg0 + 0x30));
    if ((arg1 & 0xFF) == 1) {
        sp.u40 = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0));
        sp.u42 = (s16) (s32) (*(f32 *)((u8 *)arg0 + 4));
        sp.u44 = (s16) (s32) (*(f32 *)((u8 *)arg0 + 8));
        sp.u4C = (u8) (s32) ((*(f32 *)((u8 *)arg0 + 0)) * 256.0f);
        sp.u4E = (u8) (s32) ((*(f32 *)((u8 *)arg0 + 4)) * 256.0f);
        sp.u4D = (u8) (s32) ((*(f32 *)((u8 *)arg0 + 8)) * 256.0f);
    } else {
        sp.u40 = (*(s16 *)((u8 *)arg0 + 0xC));
        sp.u42 = (*(s16 *)((u8 *)arg0 + 0xE));
        sp.u44 = (*(s16 *)((u8 *)arg0 + 0x10));
        sp.u4C = (*(u8 *)((u8 *)arg0 + 0x12));
        sp.u4E = (*(u8 *)((u8 *)arg0 + 0x14));
        sp.u4D = (*(u8 *)((u8 *)arg0 + 0x13));
    }
    sp.u46 = (*(s16 *)((u8 *)arg0 + 0x1E));
    sp.u48 = (*(s16 *)((u8 *)arg0 + 0x20));
    sp.u50 = (*(s16 *)((u8 *)arg0 + 0x22));
    sp.u4F = 9;
    sp.u64 = 1;
    sp.u52 = (*(s16 *)((u8 *)arg0 + 0x24));
    sp.u54 = (*(s16 *)((u8 *)arg0 + 0x16));
    sp.u56 = (*(s16 *)((u8 *)arg0 + 0x18));
    temp_t0 = (*(s16 *)((u8 *)arg0 + 0x1A)) << 0x10;
    sp.u34 = temp_t0;
    sp.u34 = temp_t0 + (*(s16 *)((u8 *)arg0 + 0x1C));
    sp.u4A = 0;
    sp.u38 = 0;
    sp.u5B = (*(u8 *)((u8 *)arg0 + 0x31));
    node_spawn_sprite(&sp.u30, 0, 0, -1, 0xFF, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BA800/func_1518CFF0.s")
#endif
extern void (*D_8008D970[])();

void func_1518D218(u8 *arg0) {
    s32 *new_var; // fakematch: permuter temporaries pin the lw register
    u16 new_var2; // fakematch: permuter temporary
    s32 idx;

    *(s16 *)(arg0 + 0x34) += (u32)(*(s32 *)(arg0 + 0x14) & 0xFFFF0000) >> 16;
    new_var = (s32 *)(arg0 + 0x14);
    new_var2 = *new_var;
    *(s16 *)(arg0 + 0x36) += new_var2;
    if (*(s16 *)(arg0 + 0x38) == 0) {
        idx = arg0[0x3B] & 0xF;
        if (idx != 0) {
            D_8008D970[idx]();
        }
    }
}
