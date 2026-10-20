#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* guRandom (libultra gu/random.c, -O3); xseed is D_80091D20 (owned .data) */
int func_151EFDD0(void) {
    static unsigned int xseed = 174823885;
    unsigned int x;

    x = (xseed << 2) + 2;

    x *= (x + 1);
    x = x >> 2;

    xseed = x;

    return (x);
}
