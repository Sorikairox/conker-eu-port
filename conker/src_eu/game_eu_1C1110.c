#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
extern f32 D_800A8590;
s32 sprite_vtx_quads_init(s32 *, s32, s32, s32, s32);

void func_15193900(u8 *arg0) {
    struct {
        s32 u28;
        u8 pad2C[0x82];
        s16 uAE;
        u8 padB0[0x4];
        s16 uB4;
        s16 uB6;
        s16 uB8;
        s16 uBA;
        s16 uBC;
        s16 uBE;
        s16 uC0;
        u8 padC2[0x6];
        s8 uC8;
        u8 padC9[0x1];
        s8 uCA;
        u8 uCB;
        s8 uCC;
    } sp;
    s16 temp_v1;
    u8 *temp_v0;

    bzero(&sp.u28, 0xA8);
    temp_v1 = (*(s16 *)((u8 *)arg0 + 0x2E));
    temp_v0 = arg0 + 0x28;
    if ((f32) temp_v1 != D_800A8590) {
    s32 pad;
        sp.uBE = temp_v1;
    } else {
        sp.uBE = (s16) (s32) ((f32) (*(s16 *)((u8 *)temp_v0 + 2)) - 200.0f);
        (*(u8 *)((u8 *)temp_v0 + 8)) = 0U;
    }
    sp.uB4 = (*(s16 *)((u8 *)temp_v0 + 0));
    sp.uB6 = (*(s16 *)((u8 *)temp_v0 + 2));
    sp.uBA = 0;
    sp.uBC = 0;
    sp.uCA = 0xF;
    sp.uC8 = 0x45;
    sp.uAE = 0xA;
    sp.uB8 = (*(s16 *)((u8 *)temp_v0 + 4));
    sp.uC0 = 0x4880;
    sp.uCC = 0x80;
    sp.uCB = (*(u8 *)((u8 *)temp_v0 + 8));
    sprite_vtx_quads_init(&sp.u28, 0xFF, 0xFF, 0xFF, 0x80);
    node_spawn_vtx_sprite(&sp.u28, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
    (*(s16 *)((u8 *)arg0 + 0xE)) = (s16) ((random_int() & 0x7F) + 0x64);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1110/func_15193900.s")
#endif
void func_15193A24(u8 *arg0) {
    s16 temp_v0;
    f32 sp38[3];

    if ((*(s16 *)((u8 *)arg0 + 0xA4)) < (*(s16 *)((u8 *)arg0 + 0x96))) {
        temp_v0 = (*(s16 *)((u8 *)arg0 + 0xAA));
        (*(s16 *)((u8 *)arg0 + 0xA4)) = (s16) ((s32) ((temp_v0 >> 2) * 0x18) / 3);
        (*(s16 *)((u8 *)arg0 + 0xA2)) = (s16) ((s32) ((temp_v0 >> 2) * 6) / 3);
        (*(s16 *)((u8 *)arg0 + 0xAA)) = (s16) (temp_v0 + D_800BE9E4);
        return;
    }
    (*(s16 *)((u8 *)arg0 + 0x94)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x94)) + 1);
    if ((*(s16 *)((u8 *)arg0 + 0x94)) >= 0x15) {
        (*(s16 *)((u8 *)arg0 + 0x94)) = 0x14;
    }
    (*(s16 *)((u8 *)arg0 + 0x9E)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x9E)) - ((s32) ((*(s16 *)((u8 *)arg0 + 0x94)) * D_800BE9E4) >> 1));
    if ((*(s16 *)((u8 *)arg0 + 0x9E)) < (*(s16 *)((u8 *)arg0 + 0xA6))) {
        if ((*(s8 *)((u8 *)arg0 + 0xB3)) == 1) {
            sp38[0] = (f32) (*(s16 *)((u8 *)arg0 + 0x9C));
            sp38[1] = (f32) (*(s16 *)((u8 *)arg0 + 0xA6));
            sp38[2] = (f32) (*(s16 *)((u8 *)arg0 + 0xA0));
            impact_dust_particle_spawn(5U, 30.0f, 0xFF, 0, sp38, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        }
        (*(s16 *)((u8 *)arg0 + 0x98)) = -1;
    }
}
