#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150158C0(void) {
    D_800CC16C = 0;
}

#ifdef NON_MATCHING
void func_10004074(s32);
void func_150159E8(u8 *, s32, s16);
extern u32 D_80083310[][2];

/* load ROM range #idx (D_80083310[idx] = {start, end}) into a temporary buffer and hand each record
   (big-endian size at +4, at least 16 bytes) to func_150159E8 */
void func_150158D0(s16 idx) {
    u8 *buf = (u8 *)func_10003C6C(0x2800, 1, 2, 1, 0);
    u32 *range = D_80083310[idx];
    u8 *rec;
    s32 i;

    func_10004514(range[0], buf, range[1] - range[0], 1);
    rec = buf;
    i = 0;
    while ((u32)(rec + 0xF) < (u32)(buf + range[1] - range[0])) {
        func_150159E8(rec, i, idx);
        rec += (rec[4] << 24) + (rec[5] << 16) + (rec[6] << 8) + rec[7];
        i++;
    }
    func_10004074((s32)buf);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_430D0/func_150158D0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_430D0/func_150159E8.s")
