#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// libultra gu/ortho.c (game copy, -O3: functions are emitted in reverse source order)

void game_gu_mtx_ident_f(float mf[4][4]); // guMtxIdentF
void guMtxF2L2(float mf[4][4], Mtx *m);
void game_gu_ortho_f(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale);

// guOrtho
/* was func_151F0114 */
void game_gu_ortho(Mtx *m, float l, float r, float b, float t, float n, float f, float scale)
{
	float	mf[4][4];
	game_gu_ortho_f(mf, l, r, b, t, n, f, scale);
	guMtxF2L2(mf, m);
}

// guOrthoF
/* was func_151EFFC0 */
void game_gu_ortho_f(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale)
{
	int	i, j;
	game_gu_mtx_ident_f(mf);
	mf[0][0] = 2/(r-l);
	mf[1][1] = 2/(t-b);
	mf[2][2] = -2/(f-n);
	mf[3][0] = -(r+l)/(r-l);
	mf[3][1] = -(t+b)/(t-b);
	mf[3][2] = -(f+n)/(f-n);
	mf[3][3] = 1;
	for (i=0; i<4; i++)
	    for (j=0; j<4; j++)
		mf[i][j] *= scale;
}
