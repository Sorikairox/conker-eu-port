#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15049C90 */
void math_mtx_affine_inverse(f32 arg0[4][4], f32 arg1[4][4])
{
	f32 f0 = 0.0f;
	f0 += arg0[0][0] * arg0[1][1] * arg0[2][2];
	f0 += arg0[0][1] * arg0[1][2] * arg0[2][0];
	f0 += arg0[0][2] * arg0[1][0] * arg0[2][1];
	f0 -= arg0[0][2] * arg0[1][1] * arg0[2][0];
	f0 -= arg0[0][1] * arg0[1][0] * arg0[2][2];
	f0 -= arg0[0][0] * arg0[1][2] * arg0[2][1];
	f0 = 1.0f / f0;

	arg1[0][0] = (arg0[1][1] * arg0[2][2] - arg0[1][2] * arg0[2][1]) * f0;
	arg1[1][0] = (arg0[1][2] * arg0[2][0] - arg0[1][0] * arg0[2][2]) * f0;
	arg1[2][0] = (arg0[1][0] * arg0[2][1] - arg0[1][1] * arg0[2][0]) * f0;
	arg1[0][1] = (arg0[0][2] * arg0[2][1] - arg0[0][1] * arg0[2][2]) * f0;
	arg1[1][1] = (arg0[0][0] * arg0[2][2] - arg0[0][2] * arg0[2][0]) * f0;
	arg1[2][1] = (arg0[0][1] * arg0[2][0] - arg0[0][0] * arg0[2][1]) * f0;
	arg1[0][2] = (arg0[0][1] * arg0[1][2] - arg0[0][2] * arg0[1][1]) * f0;
	arg1[1][2] = (arg0[0][2] * arg0[1][0] - arg0[0][0] * arg0[1][2]) * f0;
	arg1[2][2] = (arg0[0][0] * arg0[1][1] - arg0[0][1] * arg0[1][0]) * f0;
	arg1[3][0] = -(arg0[3][0] * arg1[0][0] + arg0[3][1] * arg1[1][0] + arg0[3][2] * arg1[2][0]);
	arg1[3][1] = -(arg0[3][0] * arg1[0][1] + arg0[3][1] * arg1[1][1] + arg0[3][2] * arg1[2][1]);
	arg1[3][2] = -(arg0[3][0] * arg1[0][2] + arg0[3][1] * arg1[1][2] + arg0[3][2] * arg1[2][2]);
	arg1[0][3] = 0.0f;
	arg1[1][3] = 0.0f;
	arg1[2][3] = 0.0f;
	arg1[3][3] = 1.0f;
}
