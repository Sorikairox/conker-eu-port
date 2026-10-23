#include <stdio.h>
#include <string.h>
typedef long s32; typedef unsigned long u32; typedef unsigned short u16; typedef short s16; typedef unsigned char u8;
typedef signed char s8; typedef float f32;
typedef struct struct249 { u16 unk0; u16 h[15]; } struct249;
typedef struct struct127 { int x; } struct127;
typedef s32 (*EvNative)(s32 *args, s32 mode, s32 *operand);
typedef s32 (*EvHandlerB)(s32 id, s32 arg, s32 *args);
enum { EV_FRAME, EV_VAR, EV_DATA, EV_IMM, EV_LABEL, EV_RESULT, EV_NATIVE };
#define EV_ABORTED -1
u8 D_800876F8[64] = {1,4,4,4,4,4,3,3,3,4,4,4,4,4,3,2,3,3,4,4,4,4,4,4,2,2,2,2,1,4,4,0};
EvNative D_80088A44[16]; EvHandlerB D_80088874[16];
s32 D_800D3C60, D_800D3C64, D_800D3C68, *D_800D3C6C, D_800D3858, D_800D3C80[0x800];
s32 D_800D3268, D_800D3378, D_800D3420, D_800D3424, D_800D2120, D_800D2124, D_80082FA0, D_800E9D00;
u8 D_800877B0[4], D_800D2E43, D_800D2E44, D_800D3289, D_800D2E60[64], D_800DDE38, D_800BE3DF, D_800BE800;
u16 *D_800BE9F4; char D_8009F870[] = "%d"; struct127 D_800CC2D0[26];
u8 bitmap[64]; void *D_800D2E4C = bitmap;
struct249 fake_ev; int calls_b704;
struct249 *func_1509B704(s16 id) { calls_b704++; return &fake_ev; }
struct249 *func_1509B5AC(s32 id, s32 a) { return 0; }
void func_1501C710(s32 a, s32 b, s32 c, s32 d, s32 e) {} void func_151733EC(struct127 *a, s32 b, s32 c) {}
void func_1517F3B0(s32 a, s32 b, s32 c, s32 d, s8 e, s32 f) {} void func_151E5B94(s32 a) {}
void func_151E89C0(void) {} void func_151E5528(void) {} void func_15042E3C(s32 a, ...) {}
#undef bzero
#define bzero my_bzero
void my_bzero(void *p, int n) { memset(p, 0, n); } u32 osGetCount(void) { return 0; }
#define NULL 0
s32 func_150AE60C(s32 *args); void func_150AE760(void); s32 func_1509FD30(s32 id, s32 action, s32 *args);
