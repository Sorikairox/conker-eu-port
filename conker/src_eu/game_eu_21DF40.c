#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include <stdarg.h>

// libultra libc/sprintf.c (game copy, -O2 without -g3); proutSprintf comes first in this version

void *memcpy(void *, const void *, unsigned int);
int func_100020D0(void *(*prout)(void *, const char *, unsigned int), char *s, const char *fmt, va_list ap); // _Printf

// proutSprintf
void *func_151F0730(void *s, const char *buf, unsigned int n) {
    return (char *)memcpy(s, buf, n) + n;
}

// sprintf
int func_151F0754(char *s, const char *fmt, ...) {
    int ans;
    va_list ap;
    va_start(ap, fmt);
    ans = func_100020D0(func_151F0730, s, fmt, ap);
    if (ans >= 0) {
        s[ans] = 0;
    }
    return ans;
}
