#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include <stdarg.h>

// libultra libc/sprintf.c (game copy, -O2 without -g3); proutSprintf comes first in this version

void *memcpy(void *, const void *, unsigned int);
int init_printf_xprintf(void *(*prout)(void *, const char *, unsigned int), char *s, const char *fmt, va_list ap); // _Printf

// proutSprintf
/* was func_151F0730 */
void *game_prout_sprintf(void *s, const char *buf, unsigned int n) {
    return (char *)memcpy(s, buf, n) + n;
}

// sprintf
/* was func_151F0754 */
int game_sprintf(char *s, const char *fmt, ...) {
    int ans;
    va_list ap;
    va_start(ap, fmt);
    ans = init_printf_xprintf(game_prout_sprintf, s, fmt, ap);
    if (ans >= 0) {
        s[ans] = 0;
    }
    return ans;
}
