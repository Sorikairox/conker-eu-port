#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CD540/func_1509FD30.s")

#ifdef NON_MATCHING
/* Game-state query handler: entry 4 of func_1509BE40's handler table D_80088838, called as handler(id, cmd, args)
 * like func_1509A024 (args[2] = first extra argument, D_800D3C60 = number of words). Commands 0x1A..0x2D read
 * flags and counters of the game state; 0x22 picks a weighted random index. */
struct249 *func_1509B704(s16 arg0);
s32 func_151E6710(s32);
f32 func_150ADA68(void);
s32 func_1517F51C(s32 player);
extern s32 D_800D3C60;
extern s8 D_800E0FE1;
extern u16 D_8009015C;
extern u16 D_800BED50[4];
extern OSContPad D_800BED38[4];
extern u8 D_800D3260;

s32 func_150A02EC(s32 id, s32 cmd, s32 *args) {
    struct249 *rec;
    s32 mask;
    s32 count;
    s32 total;
    s32 target;
    s32 i;

    switch (cmd) {
    case 0x1A: /* bit `id` of the flag bytes at D_800D2E4C */
        return ((u8 *)D_800D2E4C)[id >> 3] & (1 << (id & 7));
    case 0x1B:
        return *(u16 *)((u8 *)func_1509B704(id) + 2);
    case 0x1C:
        return D_800BE9F0;
    case 0x1D: /* players whose D_80087270 entry is not 10, minus the D_800D18A0 bits */
        mask = 0;
        for (i = 0; i < D_8008FD8C; i++) {
            if (D_80087270[i] != 10) {
                mask |= 1 << i;
            }
        }
        return mask & ~D_800D18A0;
    case 0x1E:
        return func_151E6710(args[2]);
    case 0x1F:
        return D_800BE9F8;
    case 0x20:
        return (s8)D_800BE3DF;
    case 0x21:
        return D_800BE800;
    case 0x22: /* random index i < args[2] weighted by args[3 + i] */
        count = args[2];
        total = 0;
        for (i = 0; i < count; i++) {
            total += args[3 + i];
        }
        target = func_150ADA68() * total;
        count = args[2];
        total = 0;
        for (i = 0; i < count; i++) {
            total += args[3 + i];
            if (total >= target && args[3 + i] != 0) {
                return i;
            }
        }
        return count - 1;
    case 0x23:
        return D_80090130;
    case 0x24:
        return D_800E0FE1;
    case 0x25:
        return D_8009015C & 0x10;
    case 0x26:
        return D_8008FD8C;
    case 0x27: /* buttons newly pressed on controller args[2] */
        return D_800BED50[args[2]];
    case 0x28: /* buttons of controller args[2] */
        return D_800BED38[args[2]].button;
    case 0x29:
        return D_800E0B94 == 2;
    case 0x2A:
        return args[2] & D_800E9D00;
    case 0x2B:
        rec = func_1509B704(id);
        if (rec != NULL) {
            return !(*(u16 *)rec & 0x2000);
        }
        return 0;
    case 0x2C: /* the player argument is optional (player 0) */
        return func_1517F51C(D_800D3C60 == 3 ? args[2] : 0);
    case 0x2D:
        return D_800D3260;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CD540/func_150A02EC.s")
#endif
