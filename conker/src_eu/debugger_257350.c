#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#include <stdarg.h>
#include "libc/stdlib.h"

s32 func_16001B8C(u8 *arg0, u8 *arg1, u32 arg2); // proutSprintf
s32 func_16001BB4(void *prout, char *buf, const char *fmt, va_list args); // _Printf

// libultra xstdio.h
typedef struct {
    union {
        long long ll;
        double ld;
    } v;
    char *s;
    s32 n0;
    s32 nz0;
    s32 n1;
    s32 nz1;
    s32 n2;
    s32 nz2;
    s32 prec;
    s32 width;
    u32 nchar;
    u32 flags;
    unsigned char qual;
} _Pft;

#define FLAGS_ZERO 16
#define FLAGS_MINUS 4
#define FLAGS_HASH 8

extern u8 D_16004878[]; // "0"

extern u8 D_16003CB8[]; // "0123456789abcdef"
extern u8 D_16003CCC[]; // "0123456789ABCDEF"


// whats wrong with bcopy?
u8* func_16001AD0(u8 *arg0, u8 *arg1, u32 arg2) {
    u8 *tmp0 = arg0;
    u8 *tmp1 = arg1;

    while (arg2 > 0) {
        *tmp0++ = *tmp1++;
        arg2 -= 1;
    }

    return arg0;
}

// strlen
s32 func_16001B00(u8 *arg0) {
    u8 *p = arg0;
    s32 len = 0;
    while (*p != 0) {
        len++;
        p++;
    }
    return len;
}

// sprintf
s32 func_16001B34(char *buf, const char *fmt, ...) {
    s32 ret;
    va_list args;

    va_start(args, fmt);
    ret = func_16001BB4(func_16001B8C, buf, fmt, args);
    if (ret >= 0) {
        buf[ret] = 0;
    }
    return ret;
}

s32 func_16001B8C(u8 *arg0, u8 *arg1, u32 arg2) {
    return func_16001AD0(arg0, arg1, arg2) + arg2;
}

// libultra libc xprintf.c _Printf (old version: (c = *s++) > 0 scan, as GoldenEye)
#define FLAGS_SPACE 1
#define FLAGS_PLUS 2
#define ISDIGIT(x) ((x >= '0' && x <= '9'))
#define ATOI(dst, src) \
	for (dst = 0; ISDIGIT(*src); ++src) { \
		if (dst < 999) \
			dst = dst * 10 + *src - '0'; \
	}
#define MAX_PAD (sizeof(D_16003C70) - 1)
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
extern char D_16003C70[33]; // spaces
extern char D_16003C94[33]; // zeroes
extern const char D_16004800[]; // "hlL"
extern const char D_16004804[6]; // fchar
extern const u32 D_1600480C[6]; // fbit
void func_160021FC(_Pft *px, va_list *pap, unsigned char code, unsigned char *ac);
char *strchr(const char *, s32);

s32 func_16001BB4(void *prout, char *arg, const char *fmt, va_list args)
{
#define char unsigned char
	_Pft x;
	const char *s;
	char c;
	const char *t;
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

		for (x.flags = 0; (t = strchr(D_16004804, *s)) != NULL; s++) {
			x.flags |= D_1600480C[t - D_16004804];
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

		x.qual = strchr(D_16004800, *s) ? *s++ : '\0';

		if (x.qual == 'l' && *s == 'l') {
			x.qual = 'L';
			++s;
		}

		func_160021FC(&x, &args, *s, ac);

		x.width -= x.n0 + x.nz0 + x.n1 + x.nz1 + x.n2 + x.nz2;

		if (!(x.flags & FLAGS_MINUS)) {
			PAD(D_16003C70, x.width);
		}

		PUT(ac, x.n0);
		PAD(D_16003C94, x.nz0);
		PUT(x.s, x.n1);
		PAD(D_16003C94, x.nz1);
		PUT(x.s + x.n1, x.n2);
		PAD(D_16003C94, x.nz2);

		if (x.flags & FLAGS_MINUS) {
			PAD(D_16003C70, x.width);
		}

		fmt = s + 1;
	dummy: ; // fakematch: label splits the loop tail so the back-branch delay copies the loop-head load
	}

	return 0;
}
#undef char
// uses jump table
void func_160033A8(_Pft *args, u8 type);
void func_1600288C(_Pft *px, u8 code);
#define char unsigned char

// rodata_inject: late_align8 0x25ADA0
void func_160021FC(_Pft *x, va_list *args, char type, char *buff)
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

		func_160033A8(x, type);
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
		func_160033A8(x, type);
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
		func_1600288C(x, type);
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
		func_160033A8(x, 'x');
		break;
	case 's':
		x->s = va_arg(*args, char *);
		x->n1 = func_16001B00(x->s);

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
// contains delay slot
#pragma GLOBAL_ASM("asm/nonmatchings/debugger_257350/func_1600288C.s")
// _Ldunscale
s16 func_16002D2C(s16 *pex, f64 *px) {
    u16 *ps = (u16 *)px;
    s16 xchar = (ps[0] & 0x7FF0) >> 4;

    if (xchar == 0x7FF) {
        *pex = 0;
        return (ps[0] & 0xF || ps[1] || ps[2] || ps[3]) ? 2 : 1;
    } else if (xchar > 0) {
        ps[0] = (ps[0] & 0x800F) | 0x3FF0;
        *pex = xchar - 0x3FE;
        return -1;
    } else if (xchar < 0) {
        return 2;
    } else {
        *pex = 0;
        return 0;
    }
}
// _Genld
void func_16002DE4(_Pft *px, u8 code, u8 *p, s16 nsig, s16 xexp) {
    const u8 point = '.';

    if (nsig <= 0) {
        p = D_16004878;
        nsig = 1;
    }
    if (code == 'f' || ((code == 'g' || code == 'G') && (-4 <= xexp) && (xexp < px->prec))) {
        xexp++;
        if (code != 'f') {
            if (((px->flags & FLAGS_HASH) == 0) && (nsig < px->prec)) {
                px->prec = nsig;
            }
            if ((px->prec -= xexp) < 0) {
                px->prec = 0;
            }
        }
        if (xexp <= 0) {
            px->s[px->n1++] = '0';
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1++] = point;
            }
            if (px->prec < -xexp) {
                xexp = -px->prec;
            }
            px->nz1 = -xexp;
            px->prec += xexp;
            if (px->prec < nsig) {
                nsig = px->prec;
            }
            func_16001AD0(&px->s[px->n1], p, px->n2 = nsig);
            px->nz2 = px->prec - nsig;
        } else if (nsig < xexp) {
            func_16001AD0(&px->s[px->n1], p, nsig);
            px->n1 += nsig;
            px->nz1 = xexp - nsig;
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1] = point;
                ++px->n2;
            }
            px->nz2 = px->prec;
        } else {
            func_16001AD0(&px->s[px->n1], p, xexp);
            px->n1 += xexp;
            nsig -= xexp;
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1++] = point;
            }
            if (px->prec < nsig) {
                nsig = px->prec;
            }
            func_16001AD0(&px->s[px->n1], p + xexp, nsig);
            px->n1 += nsig;
            px->nz1 = px->prec - nsig;
        }
    } else {
        if (code == 'g' || code == 'G') {
            if (nsig < px->prec) {
                px->prec = nsig;
            }
            if (--px->prec < 0) {
                px->prec = 0;
            }
            code = (code == 'g') ? 'e' : 'E';
        }
        px->s[px->n1++] = *p++;
        if (0 < px->prec || px->flags & FLAGS_HASH) {
            px->s[px->n1++] = point;
        }
        if (0 < px->prec) {
            if (px->prec < --nsig) {
                nsig = px->prec;
            }
            func_16001AD0(&px->s[px->n1], p, nsig);
            px->n1 += nsig;
            px->nz1 = px->prec - nsig;
        }
        p = (u8 *)&px->s[px->n1];
        *p++ = code;
        if (0 <= xexp) {
            *p++ = '+';
        } else {
            *p++ = '-';
            xexp = -xexp;
        }
        if (100 <= xexp) {
            if (1000 <= xexp) {
                *p++ = (xexp / 1000) + '0', xexp %= 1000;
            }
            *p++ = (xexp / 100) + '0', xexp %= 100;
        }
        *p++ = (xexp / 10) + '0', xexp %= 10;
        *p++ = xexp + '0';
        px->n2 = (u32)p - ((u32)px->s + px->n1);
    }
    if ((px->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO) {
        s32 n = px->n0 + px->n1 + px->nz1 + px->n2 + px->nz2;

        if (n < px->width) {
            px->nz0 = px->width - n;
        }
    }
}
// _Litob
void func_160033A8(_Pft *args, u8 type) {
    char buff[0x18];
    const u8 *digs;
    s32 base;
    s32 i;
    unsigned long long ullval;

    digs = (type == 'X') ? D_16003CCC : D_16003CB8;
    base = (type == 'o') ? 8 : ((type != 'x' && type != 'X') ? 10 : 16);
    i = 0x18;
    ullval = args->v.ll;
    if ((type == 'd' || type == 'i') && args->v.ll < 0) {
        ullval = -ullval;
    }
    if (ullval != 0 || args->prec != 0) {
        buff[--i] = digs[ullval % base];
    }
    args->v.ll = ullval / base;
    while (args->v.ll > 0 && i > 0) {
        lldiv_t qr = lldiv(args->v.ll, base);
        args->v.ll = qr.quot;
        buff[--i] = digs[qr.rem];
    }
    args->n1 = 0x18 - i;
    func_16001AD0(args->s, buff + i, args->n1);
    if (args->n1 < args->prec) {
        args->nz0 = args->prec - args->n1;
    }
    if (args->prec < 0 && (args->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO) {
        i = args->width - args->n0 - args->nz0 - args->n1;
        if (i > 0) {
            args->nz0 += i;
        }
    }
}
