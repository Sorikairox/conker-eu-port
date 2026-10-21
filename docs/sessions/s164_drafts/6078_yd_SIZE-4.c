s32 func_15146078(f32 *v, f32 *a, f32 *b) {
    u8 count;
    u8 nz;
    u8 z;
    f32 x;
    s32 i;
    s32 j;
    f32 sp34;
    f32 sp30;

    x = v[0];
    if (x == 0.0f && v[1] == 0.0f && v[2] == 0.0f) {
        return 0;
    }
    count = 0;
    if (x == 0.0f) {
        count++;
        z = 0;
    } else {
        nz = 0;
    }
    if (v[1] == 0.0f) {
        count++;
        z = 1;
    } else {
        nz = 1;
    }
    if (v[2] == 0.0f) {
        count++;
        z = 2;
    } else {
        nz = 2;
    }
    if (count == 2) {
        switch (nz) {
        case 0:
            a[0] = 0.0f;
            a[2] = 0.0f;
            a[1] = 1.0f;
            b[0] = 0.0f;
            b[1] = 0.0f;
            b[2] = 1.0f;
            return 1;
        case 1:
            a[1] = 0.0f;
            a[2] = 0.0f;
            a[0] = 1.0f;
            b[0] = 0.0f;
            b[1] = 0.0f;
            b[2] = 1.0f;
            return 1;
        case 2:
            a[1] = 0.0f;
            a[2] = 0.0f;
            a[0] = 1.0f;
            b[0] = 0.0f;
            b[2] = 0.0f;
            b[1] = 1.0f;
            return 1;
        }
    } else {
        i = 1;
        j = 2;
        if (count == 1 && z == 2) {
            i = 2;
            j = 1;
        }
        a[0] = 1.0f;
        a[i] = 1.0f;
        a[j] = -v[0] - v[i] / v[j];
        func_151450B4((struct17 *)a, (struct17 *)v, (struct17 *)b);
        func_151450B4((struct17 *)b, (struct17 *)v, (struct17 *)a);
        func_15145128((struct17 *)a, (struct17 *)a, &sp34, &sp30);
        func_15145128((struct17 *)b, (struct17 *)b, &sp34, &sp30);
    }
    return 1;
}
