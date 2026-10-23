s32 func_15143E08(struct127 *arg0);
f32 func_151423D8(u8);
// path_ride_place: P153: places the rider obj (arg0 + 0x1C) on its path (record +0x31C, path +0x9C): the rider's
// progress (+0xA0) picks a segment of the path points (+0x38, 24 bytes each, count +0x42, 140 units kept free at
// the end as in func_151AE694); the record's +0xAE gets the segment index, and obj's position becomes the point
// between that segment's two ends, moved sideways by arg0 +0x28 along obj's yaw (func_15143E08) - 0x80.
void func_151AE958(u8 *arg0) {
    u8 *obj;
    u8 *path;
    u8 *rec;
    f32 *p;
    f32 oldX;
    f32 oldY;
    f32 oldZ;
    f32 side;
    f32 sinYaw;
    f32 cosYaw;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    s32 spare;
    s32 index;
    u8 yaw;

    obj = *(u8 **) (arg0 + 0x1C);
    path = *(u8 **) (*(u8 **) (obj + 0x31C) + 0x9C);
    yaw = func_15143E08((struct127 *) obj) - 0x80;
    sinYaw = func_151423D8((yaw - 0x40) & 0xFF);
    cosYaw = func_151423D8(yaw);
    rec = *(u8 **) (obj + 0x31C);
    oldY = *(f32 *) (obj + 0x18);
    oldX = *(f32 *) (obj + 0x14);
    side = *(f32 *) (arg0 + 0x28);
    oldZ = *(f32 *) (obj + 0x1C);
    spare = 140.0f / *(f32 *) (path + 0x3C);
    index = (f32) (path[0x42] - spare - 1) * *(f32 *) (rec + 0xA0);
    rec[0xAE] = index;
    t = (f32) (path[0x42] - spare - 1) * *(f32 *) (rec + 0xA0) - (f32) index;
    p = (f32 *) (*(u8 **) (path + 0x38) + index * 24);
    x = (p[6] - p[0]) * t + p[0] + side * sinYaw;
    y = (p[7] - p[1]) * t + p[1];
    z = (p[8] - p[2]) * t + p[2] + side * cosYaw;
    *(f32 *) (obj + 0x14) = (x - oldX) + oldX;
    *(f32 *) (obj + 0x18) = (y - oldY) + oldY;
    *(f32 *) (obj + 0x1C) = (z - oldZ) + oldZ;
}
