#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F9060.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F911C.s")

#ifdef NON_MATCHING
/*
 * mp3util_get_bits: P190 readable C for the hand-written func_151F9150.s. Returns the next `numbits` bits of buffer
 * at bit *offset (MSB first; the asm reads the big-endian word at byte *offset >> 3 unaligned with lwl / lwr) and
 * advances *offset. The right shift is (32 - numbits) mod 32 (srlv), so numbits 0 returns the whole shifted word.
 */
s32 func_151F9150(u8 *buffer, s32 *offset, s32 numbits) {
    u32 pos = *offset;
    u8 *p = buffer + (pos >> 3);
    u32 word = ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | p[3];

    word <<= pos & 7;
    *offset = pos + numbits;
    return word >> ((32 - numbits) & 0x1F);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F9150.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F9184.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F933C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F94E0.s")
