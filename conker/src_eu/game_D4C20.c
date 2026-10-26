#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* P279: readable C for the hand asm (6 insns, sb / bnel loop). */
// fill_bytes: memset: stores val into dst[0 .. n-1]. Like the asm the first byte is written before n is tested, so
// n must be >= 1 (n = 0 would run on for 2^32 bytes).
/* was func_150A7770 */
void fill_bytes(u8 *dst, u8 val, s32 n) {
    do {
        *dst++ = val;
    } while (--n != 0);
}
