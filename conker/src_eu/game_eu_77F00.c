#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// powf: Perfect Dark src/lib/mp3/lib_45ed0.c func00045ed0; float compares use 0.0f, loop tests int 0 (s90)
f32 func_1504A620(f32);
f32 func_1504A5A0(f32);

f32 func_1504A6F0(f32 arg0, f32 arg1)
{
	f32 sp30;
	register s32 s0;

	if (arg0 != 0.0f && arg1 == 0.0f) {
		return 1.0f;
	}

	if (arg0 == 0.0f) {
		return 0.0f;
	}

	if ((arg0 == 0.0f && arg1 == 0.0f) || (arg0 < 0.0f && (s32)arg1 != arg1)) {
		return 0.0f;
	}

	if ((s32)arg1 != arg1) {
		arg0 = func_1504A5A0(func_1504A620(arg0) * arg1);
	} else if (arg1 > 0.0f) {
		arg1--;
		sp30 = arg0;

		for (s0 = (arg1-- != 0); s0; s0 = (arg1-- != 0)) {
			arg0 *= sp30;
		}
	} else {
		sp30 = 1.0f;

		for (s0 = (arg1++ != 0); s0; s0 = (arg1++ != 0)) {
			sp30 /= arg0;
		}

		arg0 = sp30;
	}

	return arg0;
}
