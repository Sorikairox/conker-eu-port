#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 *func_1502B6BC(s32, s32, s32, s32, s32, s32);
s32 func_1510D3E0(s32, s32, s32, s32, s32 *);
void func_15168E54(s32, s32 *);
extern u8 D_800DFC00[];
extern s32 D_800DFDE8[];
extern s32 *D_800E0578[];
/* func_1518C900 (P57): reference-counted load of asset (9, arg0) (pair func_1518CF74 releases it). First use:
 * func_1502B6BC(0, 0, 0, 2, 9, arg0) (0 = not found: return 0), relocate the display list *p with
 * func_1510D3E0(*p, 0, 1, 0x3E, &D_800DFDE8[arg0]), func_15168E54(*p, p), keep p in D_800E0578[arg0].
 * The count D_800DFC00[arg0] saturates at 0xFF. Returns the display list *p (a G_DL target in func_150900F0). */
s32 func_1518C900(s32 arg0) {
    s32 *p;

    if (D_800DFC00[arg0] == 0) {
        p = func_1502B6BC(0, 0, 0, 2, 9, arg0);
        if (p == NULL) {
            return 0;
        }
        func_1510D3E0(*p, 0, 1, 0x3E, &D_800DFDE8[arg0]);
        func_15168E54(*p, p);
        D_800E0578[arg0] = p;
    } else {
        p = D_800E0578[arg0];
    }
    if (D_800DFC00[arg0] != 0xFF) {
        D_800DFC00[arg0]++;
    }
    return *p;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BA680/func_1518C900.s")
#endif

extern u8 D_800DFC00[];
extern s32 D_800DFDE8[];
extern s32 *D_800E0578[];
void func_1518CF74(s32 arg0) {
    if (arg0 != 0x1E4 && D_800DFC00[arg0] != 0) {
        if (--D_800DFC00[arg0] == 0) {
            func_1510DBB0(D_800DFDE8[arg0]);
            func_100043B4(D_800E0578[arg0], 4);
        }
    }
}
