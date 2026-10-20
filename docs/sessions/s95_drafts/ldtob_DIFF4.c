#include "libc/stdlib.h"
extern const f64 D_8002C270[];
s16 func_100019F0(s16 *arg0, struct05 *arg1);
void func_10001AA8(_Pft *px, u8 code, u8 *p, s16 nsig, s16 xexp);
void *memcpy(void *, const void *, size_t);

#define args ((_Pft *)arg0)
void func_10001550(void *arg0, u8 type)
{
	u8 buff[0x20];
	u8 *p = buff;
	f64 ldval = args->v.ld;
	f32 zero = 0.0f;
	f64 zero64 = zero;
	f32 one32;
	short err;
	short nsig;
	short exp;

	if (args->prec < 0) {
		args->prec = 6;
	} else if (args->prec == 0 && (type == 'g' || type == 'G')) {
		args->prec = 1;
	}

	err = func_100019F0(&exp, (struct05 *)args);

	if (err > 0) {
		memcpy(args->s, err == 2 ? "NaN" : "Inf", args->n1 = 3);
		return;
	}

	if (err == 0) {
		nsig = 0;
		exp = 0;
	} else {
		int i;
		int n;

		if (ldval < zero64) {
			ldval = -ldval;
		}

		exp = exp * 30103L / 100000L - 4;

		if (exp < 0) {
			n = (3 - exp) & ~3;
			exp = -n;

			for (i = 0; n > 0; n >>= 1, i++) {
				if ((n & 1) != 0) {
					ldval *= D_8002C270[i];
				}
			}
		} else if (exp > 0) {
			f64 factor;
			one32 = 1.0f;
			factor = one32;
			exp &= ~3;

			for (n = exp, i = 0; n > 0; n >>= 1, i++) {
				if (n & 1) {
					factor *= D_8002C270[i];
				}
			}

			ldval /= factor;
		}

		{
			int gen = ((type == 'f') ? exp + 10 : 6) + args->prec;

			if (gen > 0x13) {
				gen = 0x13;
			}

			*p++ = '0';

			while (gen > 0 && zero64 < ldval) {
				int j;
				int lo = ldval;

				if ((gen -= 8) > 0) {
					ldval = (ldval - lo) * 1.0e8;
				}

				p += 8;

				for (j = 8; lo > 0 && --j >= 0;) {
					ldiv_t qr = ldiv(lo, 10);
					*--p = qr.rem + '0';
					lo = qr.quot;
				}

				while (--j >= 0) {
					p--;
					*p = '0';
				}

				p += 8;
			}

			gen = p - &buff[1];

			for (p = &buff[1], exp += 7; *p == '0'; p++) {
				--gen;
				--exp;
			}

			nsig = ((type == 'f') ? exp + 1 : ((type == 'e' || type == 'E') ? 1 : 0)) + args->prec;

			if (gen < nsig) {
				nsig = gen;
			}

			if (nsig > 0) {
				u8 drop;
				int n;

				if (nsig < gen && p[nsig] > '4') {
					drop = '9';
				} else {
					drop = '0';
				}

				for (n = nsig; p[--n] == drop;) {
					nsig--;
				}

				if (drop == '9') {
					p[n]++;
				}

				if (n < 0) {
					--p, ++nsig, ++exp;
				}
			}
		}
	}

	func_10001AA8(args, type, p, nsig, exp);
}

#undef args
