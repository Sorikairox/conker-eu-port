#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15049F30 */
void quat_align_hemisphere(f32 q1[4], f32 q2[4])
{
	f32 dot = q1[0] * q2[0] + q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3];

	if (dot < 0.0f) {
		q2[0] = -q2[0];
		q2[1] = -q2[1];
		q2[2] = -q2[2];
		q2[3] = -q2[3];
	}
}

typedef struct { s32 v[3]; } Idx3;
extern Idx3 g_quat_next_idx; /* was D_80086390 */
#pragma function sqrtf
/* was func_15049FA8 */
void quat_from_mtx(f32 mtx[4][4], f32 arg1[4])
{
	f32 var1;
	f32 var2;
	f32 trace = mtx[0][0] + mtx[1][1] + mtx[2][2] + 1.0f;

	if (trace > 0.01f) {
		var1 = sqrtf(trace);
		var2 = 0.5f / var1;

		arg1[0] = var1 * 0.5f;
		arg1[1] = (mtx[1][2] - mtx[2][1]) * var2;
		arg1[2] = (mtx[2][0] - mtx[0][2]) * var2;
		arg1[3] = (mtx[0][1] - mtx[1][0]) * var2;
		dummy: ; // fakematch: block boundary
	} else {
		s32 i;
		s32 j;
		Idx3 indices = g_quat_next_idx; // fakematch: .data initializer {1, 2, 0} of the PD source, copied from the asm-owned symbol
		s32 k;

		i = 0;

		if (mtx[0][0] < mtx[1][1]) {
			i = 1;
		}

		if (mtx[i][i] < mtx[2][2]) {
			i = 2;
		}

		j = indices.v[i];
		k = indices.v[j];

		var1 = sqrtf(mtx[i][i] - mtx[j][j] - mtx[k][k] + 1.0f);
		var2 = 0.5f / var1;

		arg1[i + 1] = var1 * 0.5f;
		arg1[    0] = (mtx[j][k] - mtx[k][j]) * var2;
		arg1[j + 1] = (mtx[i][j] + mtx[j][i]) * var2;
		arg1[k + 1] = (mtx[i][k] + mtx[k][i]) * var2;
	}
}

f32 math_acosf_lut(f32);
#define EPSILON 0.00001001f
/* was func_1504A1CC */
void quat_slerp(f32 q1[4], f32 q2[4], f32 t, f32 result[4])
{
	f32 dot = q1[0] * q2[0] + q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3];

	if (dot < -1.0f + EPSILON) {
		result[0] = (1.0f - t) * q1[0] - q2[0] * t;
		result[1] = (1.0f - t) * q1[1] - q2[1] * t;
		result[2] = (1.0f - t) * q1[2] - q2[2] * t;
		result[3] = (1.0f - t) * q1[3] - q2[3] * t;
	} else if (dot <= 1.0f - EPSILON) {
		f32 theta;
		f32 theta_q1;
		f32 theta_q2;
		f32 sine;
		f32 coeff_q1;
		f32 coeff_q2;
		theta = math_acosf_lut(dot);
		theta_q1 = (1.0f - t) * theta;
		theta_q2 = t * theta;
		sine = sinf(theta);
		coeff_q1 = sinf(theta_q1) / sine;
		coeff_q2 = sinf(theta_q2) / sine;
		result[0] = coeff_q1 * q1[0] + q2[0] * coeff_q2;
		result[1] = coeff_q1 * q1[1] + q2[1] * coeff_q2;
		result[2] = coeff_q1 * q1[2] + q2[2] * coeff_q2;
		result[3] = coeff_q1 * q1[3] + q2[3] * coeff_q2;
	} else {
		result[0] = (1.0f - t) * q1[0] + q2[0] * t;
		result[1] = (1.0f - t) * q1[1] + q2[1] * t;
		result[2] = (1.0f - t) * q1[2] + q2[2] * t;
		result[3] = (1.0f - t) * q1[3] + q2[3] * t;
	}
}

/* was func_1504A430 */
void quat_to_mtx(f32 quat[4], f32 mtx[4][4])
{
	f32 mult = 2.0f / (quat[0] * quat[0] + quat[1] * quat[1] + quat[2] * quat[2] + quat[3] * quat[3]);
	f32 a = quat[1] * mult;
	f32 b = quat[2] * mult;
	f32 c = quat[3] * mult;

	f32 sp34 = quat[0] * a;
	f32 sp30 = quat[0] * b;
	f32 sp2c = quat[0] * c;
	f32 sp28 = quat[1] * a;
	f32 sp24 = quat[1] * b;
	f32 sp20 = quat[1] * c;
	f32 sp1c = quat[2] * b;
	f32 sp18 = quat[2] * c;
	f32 sp14 = quat[3] * c;

	mtx[0][0] = 1.0f - (sp1c + sp14);
	mtx[0][1] = sp24 + sp2c;
	mtx[0][2] = sp20 - sp30;

	mtx[1][0] = sp24 - sp2c;
	mtx[1][1] = 1.0f - (sp28 + sp14);
	mtx[1][2] = sp18 + sp34;

	mtx[2][0] = sp20 + sp30;
	mtx[2][1] = sp18 - sp34;
	mtx[2][2] = 1.0f - (sp28 + sp1c);


	mtx[0][3] = 0.0f;
	mtx[1][3] = 0.0f;
	mtx[2][3] = 0.0f;
	mtx[3][3] = 1.0f;
}
