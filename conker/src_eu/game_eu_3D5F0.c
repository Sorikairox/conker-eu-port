#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *allocate_memory(s32, s32, s32, s32);
s32 wobblers_set_intensity(s32);
extern u8 *D_eu_800BE900;

typedef struct { s8 a; s8 p1; s8 b; s8 p3; s16 c; s16 d; s16 e; } S0A;
/* was func_1500FDE0 */
void level_slots10_init(void) {
    s32 i;

    D_eu_800BE900 = allocate_memory(0x64, 1, 0, 0);
    bzero(D_eu_800BE900, 0x64);
    for (i = 0; i < 10; i++) {
        ((S0A *)D_eu_800BE900)[i].a = i / 5;
        ((S0A *)D_eu_800BE900)[i].b = -1;
        ((S0A *)D_eu_800BE900)[i].c = random_int() % 5U;
    }
    wobblers_set_intensity(0x64);
    for (i = 0; i < 10; i++) {
        ((S0A *)D_eu_800BE900)[i].d = ((S0A *)D_eu_800BE900)[i].e;
    }
}

/* was func_1500FF4C */
void level_tex_scroll_create(void) {
    tex_scroll_create(D_80091B68, 0, 0xAD, 0x75);
}

#ifdef NON_MATCHING
s32 memcpy(u8 *, f32 *, s32);
extern s32 D_8009068C;
extern s32 D_800B1214;

/* was func_1500FF7C */
void level_tex_scroll_fx_setup(void) {
    struct {
        f32 u38;
        f32 u3C;
        u8 pad40[0x4];
        f32 u44;
    } sp;
    struct260 *temp_v0;
    u8 *temp_v0_2;

    level_dl_add_texture_scroll(*D_800B0E00, D_8009068C, 1, -1, 0, 0, 0, -4);
    level_dl_add_texture_scroll(D_800B1214, D_8009068C, 1, -1, 0, 1, 0, -4);
    level_slots10_init();
    level_tex_scroll_create();
    sp.u44 = 0.0f;
    temp_v0 = effect_node_create_nodraw(0x12C, -1, 0x12, 0U, 0xEU, 4, 0xFFU, 0);
    if (temp_v0 != NULL) {
        memcpy(((struct260 *)((u8 *)temp_v0 + 0x28)), &sp.u44, 4);
    }
    sp.u38 = 0.0f;
    sp.u3C = 0.0f;
    temp_v0_2 = effect_node_create(0x12C, -1, 0x17, -1, 0U, 0x14U, (struct37 *)8, 0xFFU, 1);
    D_80088C10 = temp_v0_2;
    if (temp_v0_2 != NULL) {
        memcpy(temp_v0_2 + 0x28, &sp.u38, 8);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_3D5F0/level_tex_scroll_fx_setup.s")
#endif