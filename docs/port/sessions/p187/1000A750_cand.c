f32 func_150ADDE0(f32 *a, f32 *b);
f32 func_150AD930(f32 *);
void func_15049148(struct17 *v, f32 len, struct17 *out);
typedef struct { s16 x, y, z, pad; } PathSoundPoint; /* D_800D2104[path] points */
// path_sound_pan_volume: func_1000A420 (pan / volume / distance) for a sound that runs along path `path`
// (D_800D2104 points, D_800D2528 counts) instead of sitting at one spot: the sound position is the path point
// nearest to (x, y, z); when that is 168 units or more away (squared >= 0x6D61) and the path has two or more points,
// the position slides along the neighbouring segment (the one towards the nearer neighbour, stepping once to the
// other side when the projection falls outside it) to the foot of the perpendicular. (ex, ey, ez) is the listener,
// yaw / near / far / out-pointers go to func_1000A420. Returns its result (0 for an empty path).
// Only caller func_10011624 (init_EB00, sound emitters on paths).
s32 func_1000A750(s32 path, s32 ex, s32 ey, s32 ez, f32 yaw, s32 x, s32 y, s32 z, s32 near, s32 far, s32 *outPan, u32 *outVol, u32 *outDist) {
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
    pts = (PathSoundPoint *) D_800D2104[path];
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
        t = func_150ADDE0(dir, rel);
        if (t < 0.0f) {
            outside = 1;
        } else {
            len = func_150AD930(dir);
            len2 = len * len;
            if (len2 < t) {
                outside = 1;
            }
        }
        if (outside) {
            func_150ADDE0(dir, rel); /* result unused */
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
            t = func_150ADDE0(dir, rel);
            len = func_150AD930(dir);
            len2 = len * len;
        }
        if (len2 != 0.0f) {
            if (t < len2) {
                func_15049148((struct17 *) dir, t / len2, (struct17 *) dir);
            }
            px = pts[seg].x + dir[0];
            py = pts[seg].y + dir[1];
            pz = pts[seg].z + dir[2];
        }
    }
    return func_1000A420(px - ex, py - ey, pz - ez, yaw, px - x, py - y, pz - z, near, far, outPan, (s32 *) outVol,
                         (s32 *) outDist);
}
