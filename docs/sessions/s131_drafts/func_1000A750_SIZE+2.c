s32 func_1000A750(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC) {
    s32 i;
    s32 d;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 best;
    s32 lastD;
    s32 bestIdx;
    s32 prevD;
    s32 nextD;
    u8 n;
    s32 flag;
    PathPt *p;
    s16 x;
    s16 y;
    s16 z;
    f32 dir[3];
    f32 rel[3];
    f32 lenSq;
    f32 t;

    n = D_800D2528[arg0];
    flag = 0;
    lastD = 0x7FFFFFFF;
    bestIdx = -2;
    best = lastD;
    if (n == 0) {
        return 0;
    }
    p = (PathPt *)D_800D2104[arg0];
    for (i = 0; i < n; i++) {
        dx = arg5 - p->x;
        dy = arg6 - p->y;
        dz = arg7 - p->z;
        d = dx * dx + dy * dy + dz * dz;
        if (d < best) {
            bestIdx = i;
            prevD = lastD;
            best = d;
        } else if (i == bestIdx + 1) {
            nextD = d;
        }
        lastD = d;
        p++;
    }
    x = ((PathPt *)D_800D2104[arg0])[bestIdx].x;
    y = ((PathPt *)D_800D2104[arg0])[bestIdx].y;
    z = ((PathPt *)D_800D2104[arg0])[bestIdx].z;
    if (n >= 2 && best > 28000) {
        if (bestIdx >= n - 1 || prevD < nextD) {
            bestIdx--;
        }
        dir[0] = ((PathPt *)D_800D2104[arg0])[bestIdx + 1].x - ((PathPt *)D_800D2104[arg0])[bestIdx].x;
        dir[1] = ((PathPt *)D_800D2104[arg0])[bestIdx + 1].y - ((PathPt *)D_800D2104[arg0])[bestIdx].y;
        dir[2] = ((PathPt *)D_800D2104[arg0])[bestIdx + 1].z - ((PathPt *)D_800D2104[arg0])[bestIdx].z;
        rel[0] = arg5 - ((PathPt *)D_800D2104[arg0])[bestIdx].x;
        rel[1] = arg6 - ((PathPt *)D_800D2104[arg0])[bestIdx].y;
        rel[2] = arg7 - ((PathPt *)D_800D2104[arg0])[bestIdx].z;
        t = func_150ADDE0(dir, rel);
        if (t < 0.0f) {
            flag = 1;
        } else {
            lenSq = func_150AD930(dir);
            lenSq = lenSq * lenSq;
            if (lenSq < t) {
                flag = 1;
            }
        }
        if (flag) {
            func_150ADDE0(dir, rel);
            if (prevD < nextD) {
                bestIdx++;
            } else {
                bestIdx--;
            }
            dir[0] = ((PathPt *)D_800D2104[arg0])[bestIdx + 1].x - ((PathPt *)D_800D2104[arg0])[bestIdx].x;
            dir[1] = ((PathPt *)D_800D2104[arg0])[bestIdx + 1].y - ((PathPt *)D_800D2104[arg0])[bestIdx].y;
            dir[2] = ((PathPt *)D_800D2104[arg0])[bestIdx + 1].z - ((PathPt *)D_800D2104[arg0])[bestIdx].z;
            rel[0] = arg5 - ((PathPt *)D_800D2104[arg0])[bestIdx].x;
            rel[1] = arg6 - ((PathPt *)D_800D2104[arg0])[bestIdx].y;
            rel[2] = arg7 - ((PathPt *)D_800D2104[arg0])[bestIdx].z;
            t = func_150ADDE0(dir, rel);
            lenSq = func_150AD930(dir);
            lenSq = lenSq * lenSq;
        }
        if (lenSq != 0.0f) {
            if (t < lenSq) {
                func_15049148((struct17 *)dir, t / lenSq, (struct17 *)dir);
            }
            x = dir[0] + ((PathPt *)D_800D2104[arg0])[bestIdx].x;
            y = dir[1] + ((PathPt *)D_800D2104[arg0])[bestIdx].y;
            z = dir[2] + ((PathPt *)D_800D2104[arg0])[bestIdx].z;
        }
    }
    return func_1000A420(x - arg1, y - arg2, z - arg3, arg4, x - arg5, y - arg6, z - arg7, arg8, arg9, argA, argB, argC);
}
