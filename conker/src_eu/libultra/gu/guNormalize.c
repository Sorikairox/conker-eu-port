// needs OPT_FLAGS := -O2 for this file (verified)
// not including gu.h: it makes sqrtf an intrinsic, but here it is a real call
extern float sqrtf(float value);

void guNormalize(float *x, float *y, float *z) {
    float m;

    m = 1 / sqrtf((*x) * (*x) + (*y) * (*y) + (*z) * (*z));
    *x *= m;
    *y *= m;
    *z *= m;
}
