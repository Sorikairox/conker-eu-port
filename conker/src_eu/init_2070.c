#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#include <stdarg.h>

s32 init_printf_xprintf(void *prout, char *arg, const char *fmt, va_list args);


/* was func_10002070 */
s32 init_printf_null_out(s32 arg0, s32 arg1, s32 arg2) {
    return 1;
}

/* was func_10002088 */
void init_debug_printf_stub(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    D_80035500 = 0;
    init_printf_xprintf(init_printf_null_out, 0, fmt, args);
}

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
    unsigned char qual;
} _Pft;

void _Litob(_Pft *args, unsigned char type);
int strlen(const char *);


// libultra libc xprintf.c (old version: (c = *s++) > 0 scan, as GoldenEye)
#define FLAGS_SPACE 1
#define FLAGS_ZERO 16
#define FLAGS_MINUS 4
#define FLAGS_HASH 8
#define FLAGS_PLUS 2
#define ISDIGIT(x) ((x >= '0' && x <= '9'))
#define ATOI(dst, src) \
	for (dst = 0; ISDIGIT(*src); ++src) { \
		if (dst < 999) \
			dst = dst * 10 + *src - '0'; \
	}
#define MAX_PAD (sizeof(D_8002AE30) - 1)
#define PAD(s, n) \
	if (0 < (n)) { \
		int i, j = (n); \
		for (; 0 < j; j -= i) { \
			i = MAX_PAD < (unsigned int)j ? (int)MAX_PAD : j; \
			PUT(s, i); \
		} \
	}
#define PUT(s, n) \
	if (0 < (n)) { \
		if ((arg = (*(void *(*)(void *, const char *, u32))prout)(arg, s, n)) != NULL) \
			x.nchar += (n); \
		else \
			return x.nchar; \
	}
extern char D_8002AE30[33]; // spaces
void init_printf_put_arg(_Pft *px, va_list *pap, unsigned char code, unsigned char *ac);
char *strchr(const char *, s32);

/* was func_100020D0 */
s32 init_printf_xprintf(void *prout, char *arg, const char *fmt, va_list args)
{
#define char unsigned char
	_Pft x;
	const char *s;
	char c;
	const char *t;
	static const char fchar[] = " +-#0";
	static const unsigned int fbit[] = {FLAGS_SPACE, FLAGS_PLUS, FLAGS_MINUS, FLAGS_HASH, FLAGS_ZERO, 0};
	char ac[32];
	x.nchar = 0;

	for (;;) {
		s = fmt;

		for (c = *s; (c = *s++) > 0;) {
			if (c == '%') {
				s--;
				break;
			}
		}

		PUT(fmt, s - fmt);

		if (c == 0) {
			return x.nchar;
		}

		fmt = ++s;

		for (x.flags = 0; (t = strchr(fchar, *s)) != NULL; s++) {
			x.flags |= fbit[t - fchar];
		}

		if (*s == '*') {
			x.width = va_arg(args, int);

			if (x.width < 0) {
				x.width = -x.width;
				x.flags |= FLAGS_MINUS;
			}

			s++;
		} else {
			ATOI(x.width, s);
		}

		if (*s != '.') {
			x.prec = -1;
		} else if (*++s == '*') {
			x.prec = va_arg(args, int);
			++s;
		} else {
			ATOI(x.prec, s);
		}

		x.qual = strchr("hlL", *s) ? *s++ : '\0';

		if (x.qual == 'l' && *s == 'l') {
			x.qual = 'L';
			++s;
		}

		init_printf_put_arg(&x, &args, *s, ac);

		x.width -= x.n0 + x.nz0 + x.n1 + x.nz1 + x.n2 + x.nz2;

		if (!(x.flags & FLAGS_MINUS)) {
			PAD(D_8002AE30, x.width);
		}

		PUT(ac, x.n0);
		PAD((char *)&D_8002AE54, x.nz0);
		PUT(x.s, x.n1);
		PAD((char *)&D_8002AE54, x.nz1);
		PUT(x.s + x.n1, x.n2);
		PAD((char *)&D_8002AE54, x.nz2);

		if (x.flags & FLAGS_MINUS) {
			PAD(D_8002AE30, x.width);
		}

		fmt = s + 1;
	dummy: ; // fakematch: label splits the loop tail so the back-branch delay copies the loop-head load
	}

	return 0;
}
#undef char

#define char unsigned char

/* was func_10002718 */
void init_printf_put_arg(_Pft *x, va_list *args, char type, char *buff)
{
	x->n0 = x->nz0 = x->n1 = x->nz1 = x->n2 = x->nz2 = 0;

	switch (type) {
	case 'c':
		buff[x->n0++] = va_arg(*args, int);
		break;
	case 'd':
	case 'i':
		if (x->qual == 'l') {
			x->v.ll = va_arg(*args, int);
		} else if (x->qual == 'L') {
			x->v.ll = va_arg(*args, s64);
		} else {
			x->v.ll = va_arg(*args, int);
		}

		if (x->qual == 'h') {
			x->v.ll = (s16)x->v.ll;
		}

		if (x->v.ll < 0) {
			buff[x->n0++] = '-';
		} else if (x->flags & FLAGS_PLUS) {
			buff[x->n0++] = '+';
		} else if (x->flags & FLAGS_SPACE) {
			buff[x->n0++] = ' ';
		}

		x->s = (char *)&buff[x->n0];

		_Litob(x, type);
		break;
	case 'x':
	case 'X':
	case 'u':
	case 'o':
		if (x->qual == 'l') {
			x->v.ll = va_arg(*args, int);
		} else if (x->qual == 'L') {
			x->v.ll = va_arg(*args, s64);
		} else {
			x->v.ll = va_arg(*args, int);
		}

		if (x->qual == 'h') {
			x->v.ll = (u16)x->v.ll;
		} else if (x->qual == 0) {
			x->v.ll = (unsigned int)x->v.ll;
		}

		if (x->flags & FLAGS_HASH) {
			buff[x->n0++] = '0';

			if (type == 'x' || type == 'X') {
				buff[x->n0++] = type;
			}
		}

		x->s = (char *)&buff[x->n0];
		_Litob(x, type);
		break;
	case 'e':
	case 'f':
	case 'g':
	case 'E':
	case 'G':
		x->v.ld = x->qual == 'L' ? va_arg(*args, f64) : va_arg(*args, f64);

		if (*(u16 *)&x->v.ld & 0x8000) {
			buff[x->n0++] = '-';
		} else if (x->flags & FLAGS_PLUS) {
			buff[x->n0++] = '+';
		} else if (x->flags & FLAGS_SPACE) {
			buff[x->n0++] = ' ';
		}

		x->s = (char *)&buff[x->n0];
		init_printf_ldtob(x, type);
		break;
	case 'n':
		if (x->qual == 'h') {
			*(va_arg(*args, u16 *)) = x->nchar;
		} else if (x->qual == 'l') {
			*va_arg(*args, unsigned int *) = x->nchar;
		} else if (x->qual == 'L') {
			*va_arg(*args, u64 *) = x->nchar;
		} else {
			*va_arg(*args, unsigned int *) = x->nchar;
		}
		break;
	case 'p':
		x->v.ll = (long)va_arg(*args, void *);
		x->s = (char *)&buff[x->n0];
		_Litob(x, 'x');
		break;
	case 's':
		x->s = va_arg(*args, char *);
		x->n1 = strlen(x->s);

		if (x->prec >= 0 && x->n1 > x->prec) {
			x->n1 = x->prec;
		}
		break;
	case '%':
		buff[x->n0++] = '%';
		break;
	default:
		buff[x->n0++] = type;
		break;
	}
}

#undef char
