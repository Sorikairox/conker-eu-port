#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* mtx_set_identity: writes the fixed-point identity into the Mtx m (64 bytes: the 16 integer halves, then the 16
 * fraction halves, row-major as s16); only the diagonal integer halves (0, 5, 10, 15) are 1. Used for the matrix of
 * disabled world records (func_15113798) and by func_1513B968 (game_168A90.c). */
void func_150A7B80(Mtx *m) {
    s16 *h = (s16 *) m;
    s32 i;

    for (i = 0; i < 32; i++) {
        h[i] = 0;
    }
    h[0] = 1;
    h[5] = 1;
    h[10] = 1;
    h[15] = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5030/func_150A7B80.s")
#endif

// struct WORD {
//     s64 unk0;
// };
//
// struct SHORTS {
//     s16 unk0;
//     s16 unk2;
//     s16 unk4;
//     s16 unk6;
// };
//
// typedef struct {
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u0;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u1;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u2;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u3;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u4;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u5;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u6;
//     union {
//         struct SHORTS s;
//         struct WORD w;
//     } u7;
// } baz;
//
// typedef struct {
//     s16 unk0;
//     // s16 unk2;
//     // s16 unk4;
//     // s16 unk8;
//     s16 unkA;
//     // s16 unkC;
//     // s16 unkE;
//     // s16 unk10;
//     // s16 unk12;
//     s16 unk14;
//     // s16 unk18;
//     // s16 unk1A;
//     // s16 unk1C;
//     s16 unk1E;
//     // s16 unk20;
//     // s16 unk22;
//     // s16 unk24;
//     // s16 unk28;
//     // s16 unk2A;
//     // s16 unk2C;
//     // s16 unk2E;
//     // s16 unk30;
//     // s16 unk32;
//     // s16 unk34;
//     // s16 unk38;
//     // s16 unk3A;
//     // s16 unk3C;
//     // s16 unk3E;
// } foobar;
//
// void func_150A7B80(baz *arg0)
// {
//     arg0->u0.w.unk0 = 0;
//     arg0->u1.w.unk0 = 0;
//     arg0->u2.w.unk0 = 0;
//     arg0->u3.w.unk0 = 0;
//     arg0->u4.w.unk0 = 0;
//     arg0->u5.w.unk0 = 0;
//     arg0->u6.w.unk0 = 0;
//     arg0->u7.w.unk0 = 0;
//     arg0->u0.s.unk0 = 1;
//     arg0->u1.s.unk2 = 1;
//     arg0->u2.s.unk4 = 1;
//     arg0->u3.s.unk6 = 1;
//
// }
