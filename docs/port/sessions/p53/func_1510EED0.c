/*
 * P53: floor / ceiling lookup under (x, z) = (arg7, arg9) over the 4 collision areas (D_800894C0[area] == 1):
 * 0 / 1 level tree (func_150A3F50), 2 world objects (func_150A6A48 + func_150A49D0 + func_150A48C0), 3 records
 * (func_150A5480). Each area leaves its candidate floors in D_800D3720 (16 bytes: +0 height in 24.8, +4 triangle
 * (3 vertex offsets), +8 vertex base (0 = level), +0xC object / record index); func_1510EBF0(i) says whether
 * candidate i is not a floor (a ceiling).
 * Outputs: arg0 = floor triangle, arg1 / arg2 = s16[9] vertices of the floor / object ceiling, arg3 = floor y,
 * arg4 = ceiling y (area 2 objects), arg5 = floor flags, arg6 = floor area; record argC (+0x19E triangle,
 * +0x1A0 object, +0x274 standing-on record, +0x17C ceiling). argA = the y the actor came from, argD / argE the
 * object search y range, argF != 0: no fallback floor when nothing is in [y - ..., y + step].
 */
s32 func_150A3F50(s32, s32);
s32 func_150A48C0(s32, s32, s32, s32 *);
s32 func_150A5480(s32, s32);
s32 func_150A6A48(s32, s32, s32 *, s32, s32, s32, s32, s32);
s32 func_150A49D0(s32 count, s32 *idList, s32 force);
s32 func_1510EBF0(s32 arg0);
extern s32 D_800D3720;
extern s32 D_800D3C00;
extern s32 D_800D3C50;
extern s32 D_800DC26C;
extern f32 D_800DC284;
extern f32 D_800DC288;
extern u16 D_800DC290;
extern f32 D_800DC298;
extern f32 D_800DC29C;
extern s32 D_800DC3C4;
extern u8 D_800894C0[];
#define EED0_E(i) ((u8 *)&D_800D3720 + (i) * 0x10)
#define EED0_H(i) ((f32)*(s32 *)EED0_E(i) * (1.0f / 256.0f))
#define EED0_OBJ(i) ((u8 *)D_800DBEF4 + (i) * 0xA0)

/* per-triangle floor flags of world object o (D_800DBEF4 record: +0x44 table or +0x40 default, +0x58 first tri) */
#define EED0_OBJFLAGS(o, tri)                                                                                         \
    ((*(s32 *)((o) + 0x44) != 0) ? *(s32 *)(*(s32 *)((o) + 0x44) + (tri) * 4 - *(u16 *)((o) + 0x58) * 4)             \
                                 : *(s32 *)((o) + 0x40))

s32 func_1510EED0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9,
                  f32 argA, u16 argB, s32 argC, f32 argD, f32 argE, s32 argF) {
    s32 total;   /* sp124 */
    s32 tri;     /* sp114 */
    s32 base;    /* sp10C */
    s32 bestArea; /* sp12C */
    s32 best;    /* sp140 */
    s32 first;   /* sp138 */
    s32 noFloor; /* spC8 */
    s32 fbFound; /* spCC */
    s32 fbArea;  /* spD0 */
    s32 fbIdx;   /* spD4 */
    s32 onRec;   /* spF4 */
    s32 flagsBuf; /* spF0 */
    s32 objList; /* spB8 */
    s32 objs;    /* spBC */
    f32 step;    /* spC0 */
    s32 ceilFlags; /* s4 */
    s32 hit;     /* s2 */
    s32 area;    /* s3 */
    s32 found;   /* fp */
    s32 n;       /* s5 */
    s32 i, k, cnt, x, z, ti, t0;
    f32 ceil, floorY, h, lo, cmax;
    u8 *e;
    u8 *o;
    s32 *vofs;
    s16 *src;

    total = 0;
    tri = 0;
    ceilFlags = 0;
    hit = 0;
    if (arg0 != 0) {
        *(s32 *)arg0 = 0;
    }
    step = (argC != 0) ? D_800DBE64 : 50.0f;
    D_800DC298 = arg7;
    D_800DC29C = arg8;
    fbFound = 0;
    *(f32 *)&D_800DC2A0 = arg9;
    *(f32 *)arg3 = -10000.0f;
    if (arg5 == 0) {
        flagsBuf = 0;
        arg5 = (s32)&flagsBuf;
    }
    ceil = 20000.0f;
    D_800DC284 = -10000.0f;
    onRec = 0;
    D_800DC290 = 0;
    if (argC != 0) {
        *(s16 *)(argC + 0x19E) = 0;
    }
    first = 1;
    noFloor = 1;
    if (arg4 != 0) {
        *(f32 *)arg4 = -10000.0f;
    }
    floorY = -10000.0f; /* set before use: first == 1 until an area runs */
    best = -1;
    bestArea = 0;
    fbArea = 0;
    fbIdx = 0;
    base = 0;
    for (area = 0; area != 4; area++) {
        if (D_800894C0[area] != 1) continue;
        if (area == 3 && argC != 0 && (*(s32 *)(argC + 0xF8) & 0x200)) continue;
        x = (s32)arg7;
        z = (s32)arg9;
        i = 0;
        found = 0;
        func_1510F800(area);
        if (area == 2) {
            objs = func_150A6A48((s16)x, (s16)z, &objList, argB, x, z, (s32)argD, (s32)argE);
            func_150A49D0(objs, &D_800D3C00, 0);
            if (arg4 != 0) {
                t0 = 0;
                func_150A49D0(objList, &D_800D3C50, 0);
                cnt = func_150A48C0(x, z, objList, &D_800D3C50);
                if (cnt != 0) {
                    cmax = -10000.0f;
                    for (k = 0; k < cnt; k++) {
                        h = EED0_H(k);
                        if (cmax < h && h < ceil) {
                            t0 = k;
                            cmax = h;
                        }
                    }
                    *(f32 *)arg4 = cmax;
                }
                if (*(f32 *)arg4 != -10000.0f && arg2 != 0) {
                    e = EED0_E(t0);
                    vofs = *(s32 **)(e + 4);
                    cnt = *(s32 *)(e + 8);
                    for (k = 0; k < 3; k++) {
                        src = (s16 *)(vofs[k] + cnt);
                        ((s16 *)arg2)[k * 3 + 0] = src[0];
                        ((s16 *)arg2)[k * 3 + 1] = src[1];
                        ((s16 *)arg2)[k * 3 + 2] = src[2];
                    }
                }
            }
            n = func_150A48C0(x, z, objs, &D_800D3C00);
        } else if (area == 3) {
            n = func_150A5480(x, z);
        } else {
            n = func_150A3F50(x, z);
        }
        total += n;
        if (first) {
            floorY = -10000.0f;
            best = -1;
            bestArea = area;
            first = 0;
        }
        for (i = 0; i < n; i++) {
            h = EED0_H(i);
            if (argF == 0 && noFloor && *(f32 *)arg3 == -10000.0f && func_1510EBF0(i) != 0) {
                fbFound = 1;
                fbIdx = i;
                fbArea = area;
            }
            if (D_800DC284 < h) {
                D_800DC284 = h;
            }
            if (arg8 < argA) {
                if (h < argA + step && floorY < h) hit = 1;
            } else if (h < arg8 + step) {
                if (h < argA) {
                    if (floorY < h) hit = 1;
                } else if (floorY < argA) {
                    hit = 1;
                } else if (h < floorY) {
                    hit = 1;
                }
            }
            if (hit) {
                hit = 0;
                if (func_1510EBF0(i) != 0) {
                    bestArea = area;
                    found = 1;
                    floorY = h;
                    best = i;
                }
            }
        }
        if (found || fbFound) {
            if (!found && fbFound) {
                best = fbIdx;
                bestArea = fbArea;
            }
            fbFound = 0;
            if (arg6 != 0) {
                *(s16 *)arg6 = bestArea;
            }
            if (best != -1) {
                e = EED0_E(best);
                noFloor = 0;
                *(f32 *)arg3 = EED0_H(best);
                if (*(f32 *)arg3 < -10000.0f) {
                    *(f32 *)arg3 = -10000.0f;
                }
                tri = *(s32 *)(e + 4);
                if (area != 3) {
                    if (argC != 0 && *(s32 *)(e + 8) == 0) {
                        *(s16 *)(argC + 0x19E) = (tri - D_800DC26C) / 12;
                    }
                } else if (argC != 0) {
                    *(s16 *)(argC + 0x19E) = (tri - D_800C6070[*((u8 *)&D_800CC2D0[*(s32 *)(e + 0xC)] + 4)]) / 12;
                }
                if (*(s32 *)(e + 8) == 0 && arg0 != 0) {
                    *(s32 *)arg0 = *(s32 *)(e + 4);
                }
                base = *(s32 *)(e + 8);
            } else {
                *(f32 *)arg3 = -10000.0f;
                base = 0;
                if (arg0 != 0) {
                    *(s32 *)arg0 = D_800DC26C;
                }
                tri = D_800DC26C;
            }
            ti = (tri - D_800DC26C) / 12;
            if (area == 0 && arg5 != 0) {
                *(s32 *)arg5 = (D_800DBE5C != 0) ? ((s32 *)D_800DBE5C)[ti] : 0;
            } else if (area == 2 && arg5 != 0) {
                D_800DC290 = *(s32 *)(EED0_E(best) + 0xC) + 1;
                *(s32 *)arg5 = EED0_OBJFLAGS(EED0_OBJ(D_800DC290) - 0xA0, ti);
            } else if (arg5 != 0) {
                *(s32 *)arg5 = 0;
            }
            if (area == 3) {
                onRec = *(s32 *)(EED0_E(best) + 0xC) + 1;
            }
        }
        if (n >= 2) {
            lo = (*(f32 *)arg3 < arg8) ? arg8 : *(f32 *)arg3;
            for (i = 0; i < n; i++) {
                h = EED0_H(i);
                if (lo < h && h < ceil && func_1510EBF0(i) == 0) {
                    ceil = h;
                    ti = (*(s32 *)(EED0_E(i) + 4) - D_800DC26C) / 12;
                    if (area == 0) {
                        ceilFlags = (D_800DBE5C != 0) ? ((s32 *)D_800DBE5C)[ti] : 0;
                    } else {
                        ceilFlags = 0;
                        if (area == 2) {
                            ceilFlags = EED0_OBJFLAGS(EED0_OBJ(*(s32 *)(EED0_E(i) + 0xC)), ti);
                        }
                    }
                }
            }
        }
    }
    if (arg4 != 0) {
        if (ceil != 10000.0f && (ceilFlags & 0x1F) == 8) {
            *(f32 *)arg4 = 10000.0f;
        }
        if (*(f32 *)arg4 == -10000.0f && (*(s32 *)arg5 & 0x1F) == 8) {
            *(f32 *)arg4 = *(f32 *)arg3;
        }
    }
    if (tri != 0 && arg1 != 0) {
        vofs = (s32 *)tri;
        for (k = 0; k < 3; k++) {
            src = (s16 *)(vofs[k] + base);
            ((s16 *)arg1)[k * 3 + 0] = src[0];
            ((s16 *)arg1)[k * 3 + 1] = src[1];
            ((s16 *)arg1)[k * 3 + 2] = src[2];
        }
        if (arg0 != 0) {
            *(s32 *)arg0 = 0;
        }
    }
    if (argC != 0) {
        *(u16 *)(argC + 0x1A0) = D_800DC290;
        if (D_800DC290 != 0 && arg8 - *(f32 *)arg3 < 10.0f) {
            o = EED0_OBJ(D_800DC290) - 0xA0;
            o[0x4F] |= 0x84;
            ((s32 *)D_800DC3C4)[D_800DC290 - 1] |= 1 << ((struct127 *)argC - D_800CC2D0);
        }
        if (onRec != 0 && arg8 - *(f32 *)arg3 < 10.0f) {
            *(u8 *)(argC + 0x274) = onRec;
        } else {
            *(u8 *)(argC + 0x274) = 0;
        }
    }
    if (total == 0) {
        *(f32 *)arg3 = -10000.0f;
        if (arg5 != 0) {
            *(s32 *)arg5 = 0;
        }
    }
    if (argC != 0) {
        *(f32 *)(argC + 0x17C) = ceil;
    }
    D_800DC288 = ceil;
    return argC;
}
