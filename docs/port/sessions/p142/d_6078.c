// plane_axes_from_normal: builds two unit axes spanning the plane with normal n (a: in-plane axis, b = a x n,
// then a = b x n). Returns 0 for a zero normal, else 1. An axis-aligned normal (two zero components) gets fixed
// unit axes; otherwise a = (1, ..) with a[j] chosen so that the in-plane condition holds, then both are normalised.
s32 func_15146078(f32 *n, f32 *a, f32 *b) {
    f32 len;
    f32 scale;
    s32 zeros;
    s32 nonzero;
    s32 zero;
    s32 i;
    s32 j;

    if (n[0] == 0.0f && n[1] == 0.0f && n[2] == 0.0f) {
        return 0;
    }
    // count the zero components; remember the last zero and the last nonzero index
    zeros = 0;
    nonzero = 0;
    zero = 0;
    if (n[0] == 0.0f) {
        zeros++;
        zero = 0;
    } else {
        nonzero = 0;
    }
    if (n[1] == 0.0f) {
        zeros++;
        zero = 1;
    } else {
        nonzero = 1;
    }
    if (n[2] == 0.0f) {
        zeros++;
        zero = 2;
    } else {
        nonzero = 2;
    }
    if (zeros == 2) {
        // normal along one axis: take the other two unit axes
        switch (nonzero) {
            case 0:
                a[0] = 0.0f;
                a[2] = 0.0f;
                a[1] = 1.0f;
                b[0] = 0.0f;
                b[1] = 0.0f;
                b[2] = 1.0f;
                break;
            case 1:
                a[1] = 0.0f;
                a[2] = 0.0f;
                a[0] = 1.0f;
                b[0] = 0.0f;
                b[1] = 0.0f;
                b[2] = 1.0f;
                break;
            case 2:
                a[1] = 0.0f;
                a[2] = 0.0f;
                a[0] = 1.0f;
                b[0] = 0.0f;
                b[2] = 0.0f;
                b[1] = 1.0f;
                break;
        }
        return 1;
    }
    i = 1;
    j = 2;
    if (zeros == 1 && zero == 2) {
        i = 2;
        j = 1;
    }
    a[0] = 1.0f;
    a[i] = 1.0f;
    a[j] = -n[0] - n[i] / n[j];
    func_151450B4((struct17 *) a, (struct17 *) n, (struct17 *) b);
    func_151450B4((struct17 *) b, (struct17 *) n, (struct17 *) a);
    func_15145128((struct17 *) a, (struct17 *) a, &len, &scale);
    func_15145128((struct17 *) b, (struct17 *) b, &len, &scale);
    return 1;
}
