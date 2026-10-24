#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#ifdef NON_MATCHING
void func_15042D94(s32, s32, u8, s32, ...);

s32 func_150D06B0(u8 *arg0) {
    u8 *sp20;
    s32 temp_t0;
    s32 var_s0;
    s8 *temp_v0;
    s8 temp_v1;
    u8 var_a3;
    u8 *temp_v0_2;

    var_a3 = 0xFF;
    var_s0 = 0;
    temp_v0 = (*(s8 **)((u8 *)arg0 + 0x48));
    if ((*(u8 *)((u8 *)arg0 + 0x30)) & 1) {
        *temp_v0 = 8;
    }
    temp_v1 = *temp_v0;
    if (temp_v1 > 0) {
        temp_t0 = (temp_v1 * 0x1F) & 0xFF;
        var_s0 = temp_t0;
        var_a3 = (0xFF - temp_t0) & 0xFF;
        *temp_v0 = temp_v1 - D_800BE9E4;
    }
    if (var_a3 != 0) {
        func_1504332C(0xCEU, 0xC4U, 0x61U, var_a3);
        func_15042D94(0x92, 0xBE, 0x81, (*(s32 *)((u8 *)((arg0 + 0x28 + ((*(u8 *)((u8 *)arg0 + 0x3D)) * 4))) + 0x18)));
    }
    if (var_s0 != 0) {
        temp_v0_2 = arg0 + 0x28;
        sp20 = temp_v0_2;
        func_1504332C(0xCEU, 0xC4U, 0x61U, var_s0 & 0xFF);
        func_15042D94(0x92, 0xBE, 0x81, (*(s32 *)((u8 *)((temp_v0_2 + (((*(u8 *)((u8 *)temp_v0_2 + 0x15)) ^ 1) * 4))) + 0x18)));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FDEC0/func_150D06B0.s")
#endif
u8 *func_150D0420(u8, s32, s16, s32, s32, s32, u8, s32);
s32 memcpy(s32, void *, s32);
void func_150D07C4(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {    s32 sfpad;

    struct { f32 x; s16 y; } sp2C;
    u8 *temp_v0;
    sp2C.y = 0;
    sp2C.x = 0.0f;
    temp_v0 = func_150D0420(arg0, arg1, arg2, 8, 1, 0, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((*(s32 *)((u8 *)temp_v0 + 0x48)), &sp2C, 8);
    }
}

#ifdef NON_MATCHING
typedef struct {
    f32 t;  /* fraction of the next character */
    s16 n;  /* characters shown */
} TypeState_150D083C;
// console_text_type: P253. Handler (s32 (u8 *), function table at ELF file offset 0x248C44, between func_150D06B0 and
// func_150D0A44) of a text box (+0x28 text block: +0x14 length, +0x15 index of the current string in the pointer
// list at +0x18; +0x48 typing state). Types the string out: flag 1 of +0x30 restarts it; while not complete, the
// fraction advances by 0.437 * D_800BE9A4 and each whole step shows one more character (at most the length). Draws
// "C:> " + the shown characters + " " + 0xBB (cursor) in colour (0, 255, 0, 150) at (15, 190). Returns 1.
s32 func_150D083C(u8 *p) {
    char prompt[] = "C:> ";
    u8 buf[0x50];
    u8 *txt = p + 0x28;
    TypeState_150D083C *st = *(TypeState_150D083C **) (p + 0x48);

    if (p[0x30] & 1) {
        st->n = 0;
        st->t = 0.0f;
    }
    if (st->t < (f32) txt[0x14]) {
        st->t += 0.437f * D_800BE9A4;
        while (st->t > 1.0f) {
            st->n++;
            if (st->n > txt[0x14]) {
                st->n = txt[0x14];
            }
            st->t -= 1.0f;
        }
    }
    /* memcpy / func_15042D94 take the buffer as s32 in this file's declarations */
    memcpy((s32) buf, prompt, 4);
    memcpy((s32) (buf + 4), *(u8 **) (txt + 0x18 + txt[0x15] * 4), st->n);
    buf[st->n + 4] = ' ';
    buf[st->n + 5] = 0xBB;
    buf[st->n + 6] = 0;
    func_1504332C(0, 0xFF, 0, 0x96);
    func_15042D94(0xF, 0xBE, 0x80, (s32) buf);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FDEC0/func_150D083C.s")
#endif

u8 *func_150D0420(u8, s32, s16, s32, s32, s32, u8, s32);
void func_150D09D4(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    s8 sp30[8];
    u8 *temp_v0;
    sp30[0] = 0;
    temp_v0 = func_150D0420(arg0, arg1, arg2, 8, 2, 0, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy(*(void **)(temp_v0 + 0x48), sp30, 1);
    }
}

#ifdef NON_MATCHING
void func_15042D94(s32, s32, u8, s32, ...);

s32 func_150D0A44(u8 *arg0) {
    u8 *sp20;
    s32 temp_t0;
    s32 var_s0;
    s8 *temp_v0;
    s8 temp_v1;
    u8 var_a3;
    u8 *temp_v0_2;

    var_a3 = 0xFF;
    var_s0 = 0;
    temp_v0 = (*(s8 **)((u8 *)arg0 + 0x48));
    if ((*(u8 *)((u8 *)arg0 + 0x30)) & 1) {
        *temp_v0 = 0x14;
    }
    temp_v1 = *temp_v0;
    if (temp_v1 > 0) {
        temp_t0 = (temp_v1 * 0xC) & 0xFF;
        var_s0 = temp_t0;
        var_a3 = (0xFF - temp_t0) & 0xFF;
        *temp_v0 = temp_v1 - D_800BE9E4;
    }
    if (var_a3 != 0) {
        func_1504332C(0xFFU, 0xFFU, 0xFFU, var_a3);
        func_15042D94(0x14, 0x14, 0x80, (*(s32 *)((u8 *)((arg0 + 0x28 + ((*(u8 *)((u8 *)arg0 + 0x3D)) * 4))) + 0x18)));
    }
    if (var_s0 != 0) {
        temp_v0_2 = arg0 + 0x28;
        sp20 = temp_v0_2;
        func_1504332C(0xFFU, 0xFFU, 0xFFU, var_s0 & 0xFF);
        func_15042D94(0x14, 0x14, 0x80, (*(s32 *)((u8 *)((temp_v0_2 + (((*(u8 *)((u8 *)temp_v0_2 + 0x15)) ^ 1) * 4))) + 0x18)));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FDEC0/func_150D0A44.s")
#endif