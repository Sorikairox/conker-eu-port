#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 * func_151149AC(u8);
s32 func_15117D18();
void func_150CF5B0(u8 *arg0) {
    u8 *p;
    if ((arg0[0x73] & 3) != 2) {
        if ((arg0[0x4F] & 4) && ((u8 *)D_800CCA0C)[0x57] != 0) {
            p = func_151149AC(0xFE);
            p[0x73] &= 0xFFFC;
            p[0x73] |= 2;
            p = func_151149AC(0xFD);
            p[0x73] &= 0xFFFC;
            p[0x73] |= 2;
        }
    } else {
        func_15117D18(arg0);
    }
}
