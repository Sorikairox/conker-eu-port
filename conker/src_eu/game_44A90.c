#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150175E0 */
void render_set_detail_level(void) {
    if ((D_800BE616 == 0) && ((D_800D2E4C->unk18 & 1) == 0)) {
        D_800D2457 = D_800D2456 = 3;
    } else {
        D_800D2457 = D_800D2456 = 6;
    }
}

extern s32 D_8009E084;
extern Mtx D_800D27F0;
extern s32 D_800D2848;
extern s32 D_800D2858;
extern s32 D_800D2864;
extern u16 D_800D2874;
extern s32 D_800D2880;
extern s8 D_800D288D;
extern s8 D_800D289D;
extern s32 D_800D28E0;
extern s32 D_800D28E8;
extern s32 D_800D29A8;

/* was func_15017640 */
void camera_view_state_init(void) {
    f32 *var_v0;
    u8 *temp_v0;

    D_800D2458 = 0;
    D_800D29A8 = 0;
    (*(f32 *)((u8 *)(&D_800D2858) + 0)) = 0.0f;
    (*(f32 *)((u8 *)(&D_800D2858) + 4)) = 0.0f;
    (*(f32 *)((u8 *)(&D_800D2858) + 8)) = 0.0f;
    (*(f32 *)((u8 *)(&D_800D2848) + 0)) = (f32) (*(s16 *)((u8 *)(&D_8009E084) + 0));
    (*(f32 *)((u8 *)(&D_800D2848) + 4)) = (f32) (*(s16 *)((u8 *)(&D_8009E084) + 2));
    var_v0 = D_800D2410;
    (*(f32 *)((u8 *)(&D_800D2848) + 8)) = (f32) (*(s16 *)((u8 *)(&D_8009E084) + 4));
    D_800D2864 = 0;
    D_800D245C = NULL;
    do {
        var_v0 = (f32 *)((u8 *)var_v0 + (4));
        (*(f32 *)((u8 *)var_v0 + -4)) = 1.0f;
    } while ((u32) var_v0 < (u32) &D_800D2848);
    D_800D288D = 0;
    D_800D289D = 0;
    temp_v0 = ((s32 *)((u8 *)&D_800D2880 + (2 * 0x10)));
    (*(s8 *)((u8 *)temp_v0 + 0x1D)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x2D)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x3D)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0xD)) = 0;
    D_800D28E0 = 0;
    bzero(&D_800D28E8, 0xC0);
    guPerspective(&D_800D27F0, &D_800D2874, 50.0f, 60.6f, 53.0f, 20000.0f, 1.0f);
}
// void camera_view_state_init(void) {
//     s32 i;
//     D_800D2458 = 0;
//     D_800D2588 = 0;
//
//     D_800D2438[0] = 0.0f;
//     D_800D2438[1] = 0.0f;
//     D_800D2438[2] = 0.0f;
//
//     D_800D2428[0] = D_8009DCB4[0];
//     D_800D2428[1] = D_8009DCB4[1];
//     D_800D2428[2] = D_8009DCB4[2];
//
//     D_800D2444 = 0;
//     D_800D245C = 0;
//
//     for (i = 0; i < 6; i++) {
//         D_800D2410[i] = 1.0f;
//     }
//
//     D_800D246D = 0;
//     D_800D247D = 0;
//
//     D_800D2460[1][13] = 0;
//     D_800D2460[2][13] = 0;
//     D_800D2460[3][13] = 0;
//     D_800D2460[0][13] = 0;
//
//     D_800D24C0 = 0;
//     bzero(&D_800D24C8, 0xC0);
//     guPerspective(&D_800D23D0, &D_800D2454, 50.0f, 60.599998474121094f, 53.0f, D_800968B0, 1.0f);
// }
