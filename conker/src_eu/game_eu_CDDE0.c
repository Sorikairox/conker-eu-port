#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct { u32 active:1; u32 flag:1; u32 kind:4; u32 pad:26; u32 count; u32 timer; } SlotEnt; // 12 bytes, D_800D3434 = &D_800D3430[0].count
extern SlotEnt D_800D3430[];


#ifdef NON_MATCHING
// slots_reset: clears the 10 slots of D_800D3430 (inactive, count and timer 0); level start (level_state_init).
void func_150A00F0(void) {
    SlotEnt *v;

    for (v = D_800D3430; v != D_800D3430 + 10; v++) {
        v->active = 0;
        v->count = 0;
        v->timer = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CDDE0/func_150A00F0.s")
#endif

#ifdef NON_MATCHING
extern u16 D_800888B0[]; /* timer period per kind */
extern u16 D_800888BC[]; /* count modulus per kind (0: none) */

/* Per frame: every active, running slot (of the 10) adds D_800BE9E4 to its timer; each time the timer reaches the
 * period of its kind it wraps and the count goes up (modulo the kind's modulus when that is set). */
void func_150A067C(void) {
    SlotEnt *v;
    u32 period;

    for (v = D_800D3430; v != D_800D3430 + 10; v++) {
        if (v->active && v->flag == 1) {
            v->timer += D_800BE9E4;
            period = D_800888B0[v->kind];
            if (v->timer >= period) {
                v->timer -= period;
                v->count++;
                if (D_800888BC[v->kind] != 0) {
                    v->count %= D_800888BC[v->kind];
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CDDE0/func_150A067C.s")
#endif

s32 func_150A0744(s32 arg0, u8 *arg1)
{
    SlotEnt *v = &D_800D3430[arg0];

    if (v->active) {
        return 0;
    }
    v->active = 1;
    v->flag = 0;
    v->kind = *(s32 *)(arg1 + 4);
    v->count = 0;
    return 1;
}

s32 func_150A07B0(s32 arg0, s32 arg1, u8 *arg2)
{
    switch (arg1) {
    case 0:
        D_800D3430[arg0].flag = 1;
        return 1;
    case 1:
        D_800D3430[arg0].flag = 0;
        return 1;
    case 2:
        D_800D3430[arg0].count = *(s32 *)(arg2 + 8);
        return 1;
    }
    return 0;
}

s32 func_150A0854(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 3) {
        return D_800D3434[arg0].unk0;
    }
    return 0;
}
