// path_face_nearest_segment: turns obj toward its path `path` (D_800D2104[path], D_800D2528[path] points of s16
// {x, y, z, speed}; at least 3): finds the point nearest to obj's x / z (squared distance, first minimum wins);
// unless that is the first or the last point, steps back one point when obj is 0x6D61 or more away from it and the
// previous point is nearer than the next one; then faces along the segment to the next point
// (func_150593C4(obj, angle, speed, min(speed * 0.0025, 1)); speed 0 = 8); above speed 20 the angle | 1 also goes
// to obj's linked object (+0x31C, +0x68).
void func_150611E8(struct127 *obj, s32 path) {
    s32 count;
    s16 *pts;
    s16 *seg;
    s16 x;
    s16 z;
    s32 dx;
    s32 dz;
    s32 d;
    s32 best;
    s32 nearest;
    s32 i;
    u16 speed;
    f32 fspeed;
    f32 turn;
    u16 angle;

    count = D_800D2528[path];
    if (count < 3) {
        return;
    }
    x = obj->x_position;
    z = obj->z_position;
    best = 0x7FFFFFFF;
    nearest = 0;
    pts = (s16 *) D_800D2104[path];
    for (i = 0; i < count; i++) {
        dx = x - pts[i * 4 + 0];
        dz = z - pts[i * 4 + 2];
        d = (s32) ((u32) dx * dx + (u32) dz * dz); // wraps like multu
        if (d < best) {
            nearest = i;
            best = d;
        }
    }
    if (nearest == 0 || nearest + 1 == count) {
        return;
    }
    if (best >= 0x6D61) {
        s32 dNext;
        s32 dPrev;

        dx = x - pts[(nearest + 1) * 4 + 0];
        dz = z - pts[(nearest + 1) * 4 + 2];
        dNext = (s32) ((u32) dx * dx + (u32) dz * dz);
        dx = x - pts[(nearest - 1) * 4 + 0];
        dz = z - pts[(nearest - 1) * 4 + 2];
        dPrev = (s32) ((u32) dx * dx + (u32) dz * dz);
        if (dPrev < dNext) {
            nearest--;
        }
    }
    seg = &pts[nearest * 4];
    speed = seg[7];
    if (speed == 0) {
        fspeed = 8.0f;
    } else {
        fspeed = speed;
    }
    turn = fspeed * 0.0025f;
    if (1.0f < turn) {
        turn = 1.0f;
    }
    angle = func_1505A630(seg[4] - seg[0], seg[2] - seg[6], 0);
    if (obj->unk31C != NULL && 20.0f < fspeed) {
        *(u16 *) ((u8 *) obj->unk31C + 0x68) = angle | 1;
    }
    func_150593C4(obj, angle, fspeed, turn);
}
