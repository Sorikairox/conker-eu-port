#include <ultra64.h>

#include "functions.h"
#include "variables.h"

typedef struct { s16 x, y, z, w; } PathPt;
f32 vec3f_dot(f32 *a, f32 *b);
s32 sound_calc_pan_volume(s32, s32, s32, f32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *); /* P151: arg 3 is the f32 heading */


void music_song_set_volume(s32, s32);
s32 approx_dist2_int(s32 x0, s32 z0, s32 x1, s32 z1);
s32 approx_dist3_int(s32 arg0, s32 arg1, s32 arg2);

// sound_pan_volume: stereo pan and volume of a sound source (P151). (dx, dy, dz) is the source relative to the
// listener, `yaw` the listener's heading in degrees, (ox, oy, oz) the offset used for the distance (planar
// approx_dist2_int when bit 0x8000 of `near` is set, else 3-D approx_dist3_int). Volume = 0x7FFF - ((far - dist) << 15) /
// (far - near), clamped to 0..0x7FFF and 0 when <= 400. With `outPan` the pan is 0x40 +/- the source's angle
// (acos of dx over the planar distance, mirrored for dz > 0, turned by the heading) folded into -95..95, with flag
// 0x80 unless it is in the front +/-32 band (then doubled); sources within 31 units pan centre (0x40). The
// distance goes to *outDist when given and is returned.
/* was func_1000A420 */
s32 sound_calc_pan_volume(s32 dx, s32 dy, s32 dz, f32 yaw, s32 ox, s32 oy, s32 oz, s32 near, s32 far, s32 *outPan,
                  s32 *outVol, s32 *outDist) {
    s32 behind = 0x80;
    s32 dist;
    s32 vol;
    s32 span;
    f32 len, c;
    s16 ang;
    s8 rel;

    if (near & 0x8000) {
        near &= 0x7FFF;
        dist = approx_dist2_int(ox, oz, 0, 0);
    } else {
        dist = approx_dist3_int(ox, oy, oz);
    }
    span = far - near;
    vol = 0x7FFF - ((far - dist) << 15) / span;
    if (vol > 400) {
        if (outPan != NULL) {
            if (approx_dist2_int(dx, dz, 0, 0) >= 31) {
                len = sqrtf((f32)(dx * dx + dz * dz));
                c = len;
                if (0.01f < len) {
                    c = (f32)dx / len;
                }
                ang = (s16)(s32)(math_asin_scaled(c) * 40.74366543152521); /* 128 / pi */
                if (dz > 0) {
                    ang = (ang < 0) ? (s16)(-128 - ang) : (s16)(128 - ang);
                }
                rel = (s8)(s32)((f32)ang + yaw * 0.7111111f); /* 128 / 180 */
                if (rel >= 96 || rel < -96) {
                    ang = 0;
                } else if (rel >= 32) {
                    ang = 95 - rel;
                } else if (rel < -32) {
                    ang = -95 - rel;
                } else {
                    behind = 0;
                    ang = rel * 2;
                }
                *outPan = (ang + 0x40) | behind;
            } else {
                *outPan = 0x40;
            }
        }
        if (0x7FFF - ((far - dist) << 15) / span < 0) {
            vol = 0;
        }
        if (vol >= 0x8000) {
            vol = 0x7FFF;
        }
        *outVol = vol;
    } else {
        *outVol = 0;
    }
    if (outDist != NULL) {
        *outDist = dist;
    }
    return dist;
}
// NON-MATCHING: mostly just regalloc
// s32 func_150AD960(s32, s32, s32, s32);
// s32 approx_dist3_int(s32, s32, s32);
// s32 sound_calc_pan_volume(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 *arg9, s32 *argA, s32 *argB) {
//     f64 dbl;
//     s32 temp_v1;
//     f32 phi_f12;
//     s32 sp24;
//     s16 tmp0;
//     s8 temp_t5;
//     s32 ret;
//
//     sp24 = 128;
//     if ((arg7 & 0x8000) != 0) {
//         // if arg7 is negative, take abs
//         arg7 = arg7 & 0x7FFF;
//         ret = func_150AD960(arg4, arg6, 0, 0);
//     } else {
//         ret = approx_dist3_int(arg4, arg5, arg6);
//     }
//     temp_v1 = 0x7FFF - ((arg8 - ret) << 15) / (arg8 - arg7);
//     if (temp_v1 >= 401) {
//         if (arg9 != 0) {
//             if (func_150AD960(arg0, arg2, 0, 0) >= 31) {
//                 phi_f12 = sqrtf((f32) ((arg0 * arg0) + (arg2 * arg2)));
//                 if (D_8002C200 < phi_f12) { // rodata, 0.009999999776482582
//                     phi_f12 = arg0 / phi_f12;
//                 }
//                 dbl = (math_asin_scaled(phi_f12) * D_8002C208);
//                 tmp0 = dbl;
//                 if (arg2 > 0) {
//                     if (tmp0 < 0) {
//                         tmp0 = -128 - tmp0;
//                     } else {
//                         tmp0 = 128 - tmp0;
//                     }
//                 }
//                 temp_t5 = tmp0 + (arg3 * D_8002C210);
//                 if ((temp_t5 >= 96) || ((temp_t5 < (-96)))) {
//                     tmp0 = 0;
//                 } else if ( temp_t5 >= 32) {
//                     tmp0 = 95 - temp_t5;
//                 } else if (temp_t5 < -32) {
//                     tmp0 = -95 - temp_t5;
//                 } else {
//                     sp24 = 0;
//                     tmp0 = temp_t5 * 2;
//                 }
//                 *arg9 = (tmp0 + 64) | sp24;
//             } else {
//                 *arg9 = 64;
//             }
//         }
//         if ((0x7FFF - ((s32) ((arg8 - ret) << 15) / (arg8 - arg7))) < 0) {
//             temp_v1 = 0;
//         }
//         if (temp_v1 >= 0x8000) {
//             temp_v1 = 0x7FFF;
//         }
//         *argA = temp_v1;
//     } else {
//         *argA = 0;
//     }
//     if (argB != 0) {
//         *argB = ret;
//     }
//     return ret;
// }


f32 vec3f_dot(f32 *a, f32 *b);
f32 vec3f_magnitude(f32 *);
void vec3_scale(struct17 *v, f32 len, struct17 *out);
typedef struct { s16 x, y, z, pad; } PathSoundPoint; /* g_path_points[path] points; was D_800D2104 */
// path_sound_pan_volume: sound_calc_pan_volume (pan / volume / distance) for a sound that runs along path `path`
// (g_path_points points, D_800D2528 counts) instead of sitting at one spot: the sound position is the path point
// nearest to (x, y, z); when that is 168 units or more away (squared >= 0x6D61) and the path has two or more points,
// the position slides along the neighbouring segment (the one towards the nearer neighbour, stepping once to the
// other side when the projection falls outside it) to the foot of the perpendicular. (ex, ey, ez) is the listener,
// yaw / near / far / out-pointers go to sound_calc_pan_volume. Returns its result (0 for an empty path).
// Only caller sfx_emitters_update (init_EB00, sound emitters on paths).
/* was func_1000A750 */
s32 sound_path_calc_pan_volume(s32 path, s32 ex, s32 ey, s32 ez, f32 yaw, s32 x, s32 y, s32 z, s32 near, s32 far, s32 *outPan, u32 *outVol, u32 *outDist) {
    PathSoundPoint *pts;
    s32 count;
    s32 i;
    s32 dx, dy, dz;
    s32 d;
    s32 best;
    s32 lastD;
    s32 prevD;
    s32 nextD;
    s32 nearest;
    s32 seg;
    s32 outside;
    f32 dir[3];
    f32 rel[3];
    f32 t;
    f32 len;
    f32 len2;
    s16 px, py, pz;

    count = D_800D2528[path];
    if (count == 0) {
        return 0;
    }
    pts = (PathSoundPoint *) g_path_points[path];
    best = 0x7FFFFFFF;
    lastD = 0x7FFFFFFF;
    nearest = -2;
    prevD = 0x7FFFFFFF;
    nextD = 0x7FFFFFFF; /* uninitialised in the original when the nearest point is the last one */
    for (i = 0; i < count; i++) {
        dx = x - pts[i].x;
        dy = y - pts[i].y;
        dz = z - pts[i].z;
        d = (u32) dx * dx + (u32) dy * dy + (u32) dz * dz;
        if (d < best) {
            nearest = i;
            prevD = lastD;
            best = d;
        } else if (i == nearest + 1) {
            nextD = d;
        }
        lastD = d;
    }
    px = pts[nearest].x;
    py = pts[nearest].y;
    pz = pts[nearest].z;
    if (count >= 2 && best >= 0x6D61) {
        if (nearest >= count - 1 || prevD < nextD) {
            seg = nearest - 1;
        } else {
            seg = nearest;
        }
        outside = 0;
        dir[0] = pts[seg + 1].x - pts[seg].x;
        dir[1] = pts[seg + 1].y - pts[seg].y;
        dir[2] = pts[seg + 1].z - pts[seg].z;
        rel[0] = x - pts[seg].x;
        rel[1] = y - pts[seg].y;
        rel[2] = z - pts[seg].z;
        t = vec3f_dot(dir, rel);
        if (t < 0.0f) {
            outside = 1;
        } else {
            len = vec3f_magnitude(dir);
            len2 = len * len;
            if (len2 < t) {
                outside = 1;
            }
        }
        if (outside) {
            vec3f_dot(dir, rel); /* result unused */
            if (prevD < nextD) {
                seg++;
            } else {
                seg--;
            }
            dir[0] = pts[seg + 1].x - pts[seg].x;
            dir[1] = pts[seg + 1].y - pts[seg].y;
            dir[2] = pts[seg + 1].z - pts[seg].z;
            rel[0] = x - pts[seg].x;
            rel[1] = y - pts[seg].y;
            rel[2] = z - pts[seg].z;
            t = vec3f_dot(dir, rel);
            len = vec3f_magnitude(dir);
            len2 = len * len;
        }
        if (len2 != 0.0f) {
            if (t < len2) {
                vec3_scale((struct17 *) dir, t / len2, (struct17 *) dir);
            }
            px = pts[seg].x + dir[0];
            py = pts[seg].y + dir[1];
            pz = pts[seg].z + dir[2];
        }
    }
    return sound_calc_pan_volume(px - ex, py - ey, pz - ez, yaw, px - x, py - y, pz - z, near, far, outPan, (s32 *) outVol,
                         (s32 *) outDist);
}
extern f32 D_8002C574;
extern f64 D_8002C578;

/* was func_1000B060 */
s32 sound_calc_pan_from_xz(f32 arg0, f32 arg1, s32 arg2) {
    s16 a;
    s16 flag;
    f32 d;
    s32 t;

    d = sqrtf(arg0 * arg0 + arg1 * arg1);
    if (d > D_8002C574) {
        d = arg0 / d;
    }
    flag = 0x80;
    t = math_asin_scaled(d) * D_8002C578;
    a = t;
    if (arg1 > 0.0f) {
        if ((s16)t < 0) {
            a = -0x80 - (s16)t;
        } else {
            a = 0x80 - (s16)t;
        }
    }
    a += arg2;
    a = (s8)a;
    if (a >= 0x60 || a < -0x60) {
        a = 0;
    } else if (a >= 0x20) {
        a = 0x5F - a;
    } else if (a < -0x20) {
        a = -0x5F - a;
    } else {
        flag = 0;
        a = a + a;
    }
    return (a + 0x40) | flag;
}
// NON-MATCHING: fair amount to fix up
// s32 sound_calc_pan_from_xz(f32 arg0, f32 arg1, s32 arg2) {
//     s16 phi_a1;
//     f32 sp18;
//     s16 temp_t8;
//     f64 temp_f6;
//     s8 temp_t9;
//     s16 phi_v1_2;
//
//     sp18 = sqrtf((arg0 * arg0) + (arg1 * arg1));
//     if (D_8002C214 < sp18) {
//         sp18 = arg0 / sp18;
//     }
//     phi_a1 = 128;
//     temp_f6 = math_asin_scaled(sp18) * D_8002C218;
//     phi_v1_2 = temp_f6;
//     if (0.0f < arg1) {
//         temp_t8 = temp_f6;
//         if ((s32) temp_t8 < 0) {
//             phi_v1_2 = (s16) (-128 - temp_t8);
//         } else {
//             phi_v1_2 = (s16) (128 - temp_t8);
//         }
//     }
//     temp_t9 = phi_v1_2 + arg2;
//     if (( temp_t9 >= 96) || ( temp_t9 < -96)) {
//         phi_v1_2 = 0;
//         phi_a1 = 128;
//     } else if ((s32) temp_t9 >= 32) {
//         phi_v1_2 = (s16) (0x5F - temp_t9);
//         phi_a1 = 128;
//     } else if ((s32) temp_t9 < -32) {
//         phi_v1_2 = (s16) (-0x5F - temp_t9);
//         phi_a1 = 128;
//     } else {
//         phi_v1_2 = (s16) (temp_t9 * 2);
//         phi_a1 = 0;
//     }
//     return (phi_v1_2 + 64) | phi_a1;
// }
