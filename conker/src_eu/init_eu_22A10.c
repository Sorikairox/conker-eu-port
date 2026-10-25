#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P279: readable C for libultra's hand-asm bzero (also replaced on PC by port/ultra/pc_libc.c vbe.bzero). */
// bzero: clears n bytes at p (nothing for n <= 0). From 12 bytes on: the bytes up to the next word boundary, then
// whole words, then the tail bytes, like the asm (swl / 32-byte sw blocks / sw / sb).
void bzero(void *p, int n) {
    u8 *b = p;

    if (n >= 12) {
        while ((u32) b & 3) {
            *b++ = 0;
            n--;
        }
        while (n >= 4) {
            *(u32 *) b = 0;
            b += 4;
            n -= 4;
        }
    }
    while (n > 0) {
        *b++ = 0;
        n--;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_22A10/bzero.s")
#endif
