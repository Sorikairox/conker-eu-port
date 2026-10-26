#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "stdlib.h"

// libc xlitob.c; this file is built -O2
typedef struct {
    union {
        long long ll;
        long double ld;
    } v;
    unsigned char *s;
    int n0;
    int nz0;
    int n1;
    int nz1;
    int n2;
    int nz2;
    int prec;
    int width;
    size_t nchar;
    unsigned int flags;
    char qual;
} _Pft;

#define BUFF_LEN 0x18
#define FLAGS_MINUS 4
#define FLAGS_ZERO 16

extern unsigned char g_os_litob_ldigs[]; /* was D_8002C080 */ // ldigs "0123456789abcdef"
extern unsigned char g_os_litob_udigs[]; /* was D_8002C094 */ // udigs "0123456789ABCDEF"

void _Litob(_Pft *args, unsigned char type) {
    unsigned char buff[BUFF_LEN];
    const unsigned char *digs;
    s32 base;
    s32 i;
    unsigned long long ull;

    digs = (type == 'X') ? g_os_litob_udigs : g_os_litob_ldigs;
    base = (type == 'o') ? 8 : ((type != 'x' && type != 'X') ? 10 : 16);
    i = BUFF_LEN;
    ull = args->v.ll;
    if ((type == 'd' || type == 'i') && args->v.ll < 0) {
        ull = -ull;
    }
    if (ull != 0 || args->prec != 0) {
        buff[--i] = digs[ull % base];
    }
    args->v.ll = ull / base;
    while (args->v.ll > 0 && i > 0) {
        lldiv_t qr = lldiv(args->v.ll, base);

        args->v.ll = qr.quot;
        buff[--i] = digs[qr.rem];
    }
    args->n1 = BUFF_LEN - i;
    memcpy(args->s, buff + i, args->n1);
    if (args->n1 < args->prec) {
        args->nz0 = args->prec - args->n1;
    }
    if (args->prec < 0 && (args->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO) {
        if ((i = args->width - args->n0 - args->nz0 - args->n1) > 0) {
            args->nz0 += i;
        }
    }
}
