extern char D_800A242C[]; /* joint names, 12 bytes each (D_800A2420 is declared s32 above) */
extern char D_800A2438[];
extern char D_800A2444[];
extern char D_800A2450[2][6][12]; /* two sets of 6 point joint names */
/* func_1514654C (model, s32, 0, names, outs, n): implicitly declared by the matched func_150FF604 above */
s32 func_150ADA20(void);

// model_points_find: looks up 10 joints of `model` by name in one func_1514654C call: D_800A2420 -> a,
// D_800A2438 -> ref, D_800A2444 -> out, D_800A242C -> b, and one of the two D_800A2450 sets (random) -> the 6
// vectors of `points`. On success `out` is made relative to `ref` and the result is 1, else 0.
s32 func_150FFC60(f32 *points, f32 *a, f32 *ref, f32 *out, f32 *b, u8 *model, s32 arg6) {
    struct {
        void *outs[10];   /* sp+0x34 */
        char *names[10];  /* sp+0x5C */
    } q;
    s32 set;
    s32 i;

    set = func_150ADA20() & 1;
    q.names[0] = (char *) &D_800A2420;
    q.names[1] = D_800A2438;
    q.names[2] = D_800A2444;
    q.names[3] = D_800A242C;
    for (i = 0; i < 6; i++) {
        q.names[4 + i] = D_800A2450[set][i];
        q.outs[4 + i] = points + i * 3;
    }
    q.outs[0] = a;
    q.outs[1] = ref;
    q.outs[2] = out;
    q.outs[3] = b;
    if (func_1514654C(model, arg6, 0, q.names, q.outs, 10) != 0) {
        out[0] -= ref[0];
        out[1] -= ref[1];
        out[2] -= ref[2];
        return 1;
    }
    return 0;
}
