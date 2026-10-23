/* mtx_set_identity: writes the fixed-point identity into the Mtx m (64 bytes: the 16 integer halves, then the 16
 * fraction halves, row-major as s16); only the diagonal integer halves (0, 5, 10, 15) are 1. Used for the matrix of
 * disabled world records (func_15113798) and by func_1513B968 (game_168A90.c). */
void func_150A7B80(Mtx *m) {
    s16 *h = (s16 *) m;
    s32 i;

    for (i = 0; i < 32; i++) {
        h[i] = 0;
    }
    h[0] = 1;
    h[5] = 1;
    h[10] = 1;
    h[15] = 1;
}
