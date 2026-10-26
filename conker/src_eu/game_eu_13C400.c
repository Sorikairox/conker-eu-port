#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void collision_select_area(s32 arg0);
extern u8 *D_800DC278;
s32 zone_tree_leaf_index(u8 *arg0);
#endif


#ifdef NON_MATCHING
void func_150ADD90(u8 *, u8 *, u8 *);
extern s32 D_800D3720;

/* was func_1510EBF0 */
s32 collision_candidate_is_floor(s32 arg0) {
    struct {
        s32 u20;
        s32 u24;
        u8 pad28[0x4];
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
    } sp;
    s32 temp_t1;
    s32 var_v0;
    u8 *temp_a3;
    u8 *temp_t0;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v1;

    temp_v0 = ((s32 *)((u8 *)&D_800D3720 + (arg0 * 0x10)));
    temp_t0 = (*(u8 **)((u8 *)temp_v0 + 4));
    temp_t1 = (*(s32 *)((u8 *)temp_v0 + 8));
    var_v0 = 0;
    if (temp_t0 != NULL) {
        temp_v0_2 = (*(s32 *)((u8 *)temp_t0 + 0)) + temp_t1;
        temp_v1 = (*(s32 *)((u8 *)temp_t0 + 4)) + temp_t1;
        temp_a3 = (*(s32 *)((u8 *)temp_t0 + 8)) + temp_t1;
        sp.u38 = (f32) ((*(s16 *)((u8 *)temp_v1 + 0)) - (*(s16 *)((u8 *)temp_v0_2 + 0)));
        sp.u3C = (f32) ((*(s16 *)((u8 *)temp_v1 + 2)) - (*(s16 *)((u8 *)temp_v0_2 + 2)));
        sp.u40 = (f32) ((*(s16 *)((u8 *)temp_v1 + 4)) - (*(s16 *)((u8 *)temp_v0_2 + 4)));
        sp.u2C = (f32) ((*(s16 *)((u8 *)temp_a3 + 0)) - (*(s16 *)((u8 *)temp_v0_2 + 0)));
        sp.u30 = (f32) ((*(s16 *)((u8 *)temp_a3 + 2)) - (*(s16 *)((u8 *)temp_v0_2 + 2)));
        sp.u34 = (f32) ((*(s16 *)((u8 *)temp_a3 + 4)) - (*(s16 *)((u8 *)temp_v0_2 + 4)));
        func_150ADD90(&sp.u38, &sp.u2C, &sp.u20);
        if (sp.u24 < 0.0f) {
            return 0;
        }
        var_v0 = 1;
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/collision_candidate_is_floor.s")
#endif
s32 collision_find_floor_ceiling(s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32, s32);
/* was func_1510ED24 */
void collision_find_floor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD) {
    collision_find_floor_ceiling(arg0, arg1, 0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, argC, argD, 0);
}

s32 collision_find_floor_ceiling(s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32, s32);
/* was func_1510EDAC */
void collision_find_floor_default_range(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB) {
    collision_find_floor_ceiling(arg0, arg1, 0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, -10000.0f, 20000.0f, 0);
}

s32 collision_find_floor_ceiling(s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32, s32);
/* was func_1510EE3C */
void collision_find_floor_no_fallback(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, s32 argC, s32 argD, s32 argE) {
    collision_find_floor_ceiling(arg0, arg1, 0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, -10000.0f, 20000.0f, argE);
}

#ifdef NON_MATCHING
/*
 * P53: floor / ceiling lookup under (x, z) = (arg7, arg9) over the 4 collision areas (D_800894C0[area] == 1):
 * 0 / 1 level tree (func_150A3F50), 2 world objects (func_150A6A48 + func_150A49D0 + func_150A48C0), 3 records
 * (func_150A5480). Each area leaves its candidate floors in D_800D3720 (16 bytes: +0 height in 24.8, +4 triangle
 * (3 vertex offsets), +8 vertex base (0 = level), +0xC object / record index); collision_candidate_is_floor(i) says whether
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
s32 collision_candidate_is_floor(s32 arg0);
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

/* was func_1510EED0 */
s32 collision_find_floor_ceiling(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9,
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
        collision_select_area(area);
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
            if (argF == 0 && noFloor && *(f32 *)arg3 == -10000.0f && collision_candidate_is_floor(i) != 0) {
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
                if (collision_candidate_is_floor(i) != 0) {
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
                if (lo < h && h < ceil && collision_candidate_is_floor(i) == 0) {
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/collision_find_floor_ceiling.s")
#endif

#ifdef NON_MATCHING
s32 func_150A48C0(s32, s32, s32, s32 *);
s32 func_150A49D0(s32, s32 *, s32);
s32 func_150A69A8(s32, s32, s32 *, s32);
extern s32 D_800D3720;
extern s32 D_800D3C50;

/* was func_1510FBC8 */
f32 collision_object_floor_height(f32 arg0, f32 arg1, f32 arg2) {
    struct {
        s32 u28;
    } sp;
    s32 sp20;
    s32 sp1C;
    f32 var_f2;
    s32 temp_f10;
    s32 temp_f6;

    collision_select_area(2);
    temp_f6 = (s32) arg0;
    temp_f10 = (s32) arg2;
    sp20 = temp_f6;
    sp1C = temp_f10;
    func_150A69A8((s16) temp_f6, (s16) temp_f10, &sp.u28, (s32) arg1);
    func_150A49D0(sp.u28, &D_800D3C50, 0);
    if (func_150A48C0(sp20, sp1C, sp.u28, &D_800D3C50) != 0) {
        var_f2 = (f32) D_800D3720 * 0.00390625f;
    } else {
        var_f2 = -10000.0f;
    }
    return var_f2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/collision_object_floor_height.s")
#endif
#ifdef NON_MATCHING
/* was func_1510FCA0 */
s32 zone_tree_collect_near(s32 arg0, s32 arg1, s32 arg2, u8 **arg3) {
    s16 temp_a1_3;
    s16 var_a2_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;
    u8 **var_s2;
    u8 *var_v0;

    var_s2 = arg3;
    var_v0 = D_800DC278;
    var_v1 = 0;
    if (var_v0 != NULL) {
        do {
            temp_a1 = (*(s16 *)((u8 *)var_v0 + 8)) - arg0;
            var_a2 = temp_a1;
            if (temp_a1 < 0) {
                var_a2 = -temp_a1;
            }
            temp_a1_2 = arg2 + (*(u16 *)((u8 *)var_v0 + 6));
            if (var_a2 < temp_a1_2) {
                temp_a2 = (*(s16 *)((u8 *)var_v0 + 0xA)) - arg1;
                var_a3 = temp_a2;
                if (temp_a2 < 0) {
                    var_a3 = -temp_a2;
                }
                if (var_a3 < temp_a1_2) {
                    temp_a1_3 = (*(s16 *)((u8 *)var_v0 + 0xC));
                    if (temp_a1_3 != 0) {
                        var_a2_2 = temp_a1_3;
                    } else {
                        *var_s2 = var_v0;
                        var_s2 = (u8 * *)((u8 *)var_s2 + (4));
                        var_v1 += 1;
                        goto block_10;
                    }
                } else {
                    goto block_10;
                }
            } else {
block_10:
                var_a2_2 = (*(s16 *)((u8 *)var_v0 + 4));
            }
            if (var_a2_2 != 0) {
                var_v0 = &var_v0[var_a2_2];
            } else {
                var_v0 = NULL;
            }
        } while (var_v0 != NULL);
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/zone_tree_collect_near.s")
#endif
/* was func_1510F800 */
void collision_select_area(s32 arg0) {
    func_150A4ED4(arg0);
}

s32 floor_triangle_slope(s32, s32, f32 *, f32 *);
/* was func_1510FDA0 */
void floor_slope_direction(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3, s32 arg4, f32 *arg5, f32 *arg6)
{
  f32 sp24;
  f32 sp20;
  f32 temp_f2;
  floor_triangle_slope(arg0, arg1, &sp24, &sp20);
  temp_f2 = sqrtf((sp24 * sp24) + (sp20 * sp20));
  *arg5 = sp24;
  *arg6 = sp20;
  temp_f2 = temp_f2 * 0.02f;
  if (temp_f2 == 0.0f) {
    *arg2 = 1.0f;
    *arg3 = 0.0f;
    return;
  }
  *arg2 = sp24 / temp_f2;
  *arg3 = sp20 / temp_f2;
}

/* was func_1510FE4C */
s32 floor_flags_surface_type(s32 arg0) {
    return arg0 & 0x1F;
}

#ifdef NON_MATCHING
s32 func_150A3F50(s32, s32);
extern s32 D_800D3720;

/* was func_1510FE58 */
s32 collision_level_nearest_height(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f14;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f2;
    s32 temp_t8;
    s32 temp_v0;
    s32 var_a0;
    s32 var_v1;
    u8 *var_v0;

    collision_select_area(0);
    temp_v0 = func_150A3F50(arg0, arg2);
    if (temp_v0 == 0) {
        return -0x2710;
    }
    var_a0 = 0;
    temp_t8 = (temp_v0 - 1) & 3;
    temp_f14 = (f32) arg1;
    var_v1 = 1;
    var_f2 = temp_f14 - ((f32) D_800D3720 * 0.00390625f);
    if (temp_v0 >= 2) {
        if (temp_t8 != 0) {
            do {
                if (((var_f2 >= 0.0f) && (var_f0 = temp_f14 - ((f32) *(s32 *)((u8 *)&D_800D3720 + (var_v1 * 0x10)) * 0.00390625f), (var_f0 < var_f2)) && (var_f0 >= 0.0f)) || ((var_f2 < 0.0f) && (var_f0 = temp_f14 - ((f32) *(s32 *)((u8 *)&D_800D3720 + (var_v1 * 0x10)) * 0.00390625f), (var_f2 < var_f0)))) {
                    var_f2 = var_f0;
                    var_a0 = var_v1;
                }
                var_v1 += 1;
            } while ((temp_t8 + 1) != var_v1);
            if (var_v1 != temp_v0) {
                goto block_13;
            }
        } else {
block_13:
            var_v0 = ((s32 *)((u8 *)&D_800D3720 + (var_v1 * 0x10)));
            do {
                if (((var_f2 >= 0.0f) && (var_f0_2 = temp_f14 - ((f32) (*(s32 *)((u8 *)var_v0 + 0)) * 0.00390625f), (var_f0_2 < var_f2)) && (var_f0_2 >= 0.0f)) || ((var_f2 < 0.0f) && (var_f0_2 = temp_f14 - ((f32) (*(s32 *)((u8 *)var_v0 + 0)) * 0.00390625f), (var_f2 < var_f0_2)))) {
                    var_f2 = var_f0_2;
                    var_a0 = var_v1;
                }
                temp_f0 = temp_f14 - ((f32) (*(s32 *)((u8 *)var_v0 + 0x10)) * 0.00390625f);
                if (((var_f2 >= 0.0f) && (temp_f0 < var_f2) && (temp_f0 >= 0.0f)) || ((var_f2 < 0.0f) && (var_f2 < temp_f0))) {
                    var_f2 = temp_f0;
                    var_a0 = var_v1 + 1;
                }
                temp_f0_2 = temp_f14 - ((f32) (*(s32 *)((u8 *)var_v0 + 0x20)) * 0.00390625f);
                if (((var_f2 >= 0.0f) && (temp_f0_2 < var_f2) && (temp_f0_2 >= 0.0f)) || ((var_f2 < 0.0f) && (var_f2 < temp_f0_2))) {
                    var_f2 = temp_f0_2;
                    var_a0 = var_v1 + 2;
                }
                temp_f0_3 = temp_f14 - ((f32) (*(s32 *)((u8 *)var_v0 + 0x30)) * 0.00390625f);
                if (((var_f2 >= 0.0f) && (temp_f0_3 < var_f2) && (temp_f0_3 >= 0.0f)) || ((var_f2 < 0.0f) && (var_f2 < temp_f0_3))) {
                    var_f2 = temp_f0_3;
                    var_a0 = var_v1 + 3;
                }
                var_v1 += 4;
                var_v0 += 0x40;
            } while (var_v1 != temp_v0);
        }
    }
    if (arg3 != NULL) {
        *arg3 = (*(s32 *)((u8 *)((((s32 *)((u8 *)&D_800D3720 + (var_a0 * 0x10))))) + 4));
    }
    return (s32) ((f32) *(s32 *)((u8 *)&D_800D3720 + (var_a0 * 0x10)) * 0.00390625f);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/collision_level_nearest_height.s")
#endif
#ifdef NON_MATCHING
void func_150A6C40(s32);
void camera_zone_flag_update(s32);
extern s32 D_800DC1F0;
extern s32 D_800DC1F4;
extern s32 D_800DC1F8;
extern f32 D_800DC1FC;
extern f32 D_800DC200;
extern s32 D_800DC260;

/* was func_151101B4 */
void player_zone_update(s32 arg0) {
    s16 *temp_v1;
    s32 temp_f10;
    s32 temp_f6;
    s32 temp_v0_2;
    s32 temp_v0_3;
    struct108 *temp_v0;

    D_800DC1F0 = arg0;
    temp_v0 = &D_800DBFF0[arg0];
    temp_f6 = (s32) temp_v0->unk2F8;
    temp_f10 = (s32) temp_v0->unk300;
    D_800DC1FC = (f32) temp_f6;
    D_800DC200 = (f32) temp_f10;
    temp_v0_2 = zone_tree_find_leaf(temp_f6, temp_f10);
    D_800DC1F8 = temp_v0_2;
    temp_v0_3 = zone_tree_leaf_index((u8 *) temp_v0_2);
    D_800DC1F4 = temp_v0_3;
    temp_v1 = ((s32 *)((u8 *)&D_800DC260 + (arg0 * 2)));
    if (temp_v0_3 != *temp_v1) {
        *temp_v1 = (s16) temp_v0_3;
        func_150A6C40(arg0);
    }
    if (D_800BE9F0 == 0x3C) {
        camera_zone_flag_update(arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/player_zone_update.s")
#endif
#ifdef NON_MATCHING
/* was func_1510FD20 */
s32 zone_tree_find_leaf(s32 arg0, s32 arg1) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_a1;
    s32 temp_a1_3;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_t0;
    s32 var_t0_2;
    u16 temp_a1_2;
    u16 temp_a1_4;
    u8 *var_v1;

    var_v1 = D_800DC278;
    if (var_v1 != NULL) {
loop_1:
        temp_v0 = (*(s16 *)((u8 *)var_v1 + 0xC));
        if (temp_v0 != 0) {
            temp_a1 = arg0 - (*(s16 *)((u8 *)var_v1 + 8));
            var_a2 = temp_a1;
            if (temp_a1 < 0) {
                var_a2 = -temp_a1;
            }
            temp_a1_2 = (*(u16 *)((u8 *)var_v1 + 6));
            if ((s32) temp_a1_2 >= var_a2) {
                temp_a2 = arg1 - (*(s16 *)((u8 *)var_v1 + 0xA));
                var_t0 = temp_a2;
                if (temp_a2 < 0) {
                    var_t0 = -temp_a2;
                }
                if ((s32) temp_a1_2 >= var_t0) {
                    var_v1 = &var_v1[temp_v0];
                } else {
                    goto block_9;
                }
            } else {
block_9:
                temp_v0_2 = (*(s16 *)((u8 *)var_v1 + 4));
                if (temp_v0_2 != 0) {
                    var_v1 = &var_v1[temp_v0_2];
                } else {
                    goto block_21;
                }
            }
            goto block_22;
        }
        temp_a1_3 = arg0 - (*(s16 *)((u8 *)var_v1 + 8));
        var_a2_2 = temp_a1_3;
        if (temp_a1_3 < 0) {
            var_a2_2 = -temp_a1_3;
        }
        temp_a1_4 = (*(u16 *)((u8 *)var_v1 + 6));
        if ((s32) temp_a1_4 >= var_a2_2) {
            temp_a2_2 = arg1 - (*(s16 *)((u8 *)var_v1 + 0xA));
            var_t0_2 = temp_a2_2;
            if (temp_a2_2 < 0) {
                var_t0_2 = -temp_a2_2;
            }
            if ((s32) temp_a1_4 >= var_t0_2) {
                return (s32) var_v1;
            }
            goto block_19;
        }
block_19:
        temp_v0_3 = (*(s16 *)((u8 *)var_v1 + 4));
        if (temp_v0_3 != 0) {
            var_v1 = &var_v1[temp_v0_3];
        } else {
block_21:
            var_v1 = NULL;
        }
block_22:
        if (var_v1 == NULL) {
    s32 pad;
            /* Duplicate return node #23. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/zone_tree_find_leaf.s")
#endif
extern u8 *D_800DC278;
/* was func_151103B0 */
s32 zone_tree_leaf_index(u8 *arg0) {
    s32 count = 0;
    u8 *p = D_800DC278;

    while (p != NULL) {
        if (p == arg0) {
            return count;
        }
        if (*(s16 *)(p + 0xC) != 0) {
            p += *(s16 *)(p + 0xC);
        } else if (*(s16 *)(p + 4) != 0) {
            p += *(s16 *)(p + 4);
            count++;
        } else {
            p = NULL;
        }
    }
    return 0;
}
