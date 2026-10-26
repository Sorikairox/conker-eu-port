#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// expf: Perfect Dark src/lib/mp3/lib_47d20.c func00047d20 (Rare shared code; `sp1c += sp1c` for `*= 2`)
#pragma intrinsic (fabsf)
f32 fabsf(f32);
#define MAXFLOAT 3.40282347e+38f
/* was func_1504A5A0 */
f32 math_expf(f32 arg0)
{
	f32 sp1c;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 sp0c;
	s32 sp08;
	s32 sp04;

	sp0c = fabsf(arg0);

	if (sp0c < 0.00000011920929f) {
		return 1;
	}

	sp04 = (s32) (sp0c / 0.6931471824646f);

	if (sp04 > 1024) {
		if (arg0 >= 0) {
			return MAXFLOAT;
		} else {
			return 0;
		}
	}

	sp10 = sp0c - sp04 * 0.6931471824646f;
	sp08 = 1;
	sp1c = 1;
	sp18 = 1;

	do {
		sp14 = sp1c;
		sp18 *= sp10 / sp08;
		sp1c += sp18;
		sp08++;
	} while (sp1c != sp14);

	while (sp04) {
		sp1c += sp1c;
		sp04--;
	}

	if (arg0 >= 0) {
		return sp1c;
	} else {
		return 1 / sp1c;
	}
}
