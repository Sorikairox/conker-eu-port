struct_eu_node *func_151AEB40(s32);
void func_151AE86C(f32 *, u8 *, s32, f32);
// path_try_attach: attaches obj to path node `id` (func_151AEB40; the original hangs when there is none) unless the
// path is busy (+0x52), obj cannot ride (+0x1CA == 0) or is busy (+0x104). The rider record (+0x31C) gets its
// progress along the path at +0xA0 (func_151AE86C from obj's height); when the path point at that progress
// (points +0x38, 24 bytes each, count +0x42, spacing +0x3C, 140 units kept free at the end) is within 100 units
// of obj, the record takes the path (+0x98 id, +0x9C path), obj state +0x8A = 0x12 and the path's rider +0x44 = obj.
void func_151AE694(u8 *obj, u8 id) {
    u8 *path;
    u8 *rec;
    f32 *point;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 spare;
    s32 index;

    path = (u8 *)func_151AEB40(id);
    if (path == NULL) {
        for (;;) {
        }
    }
    if (*(s16 *)(path + 0x52) != 0 || obj[0x1CA] == 0 || obj[0x104] != 0) {
        return;
    }
    func_151AE86C((f32 *)(*(u8 **)(obj + 0x31C) + 0xA0), path, *(s32 *)(obj + 0x14), *(f32 *)(obj + 0x18));
    spare = 140.0f / *(f32 *)(path + 0x3C);
    rec = *(u8 **)(obj + 0x31C);
    index = (f32)(path[0x42] - spare - 1) * *(f32 *)(rec + 0xA0);
    point = (f32 *)(*(u8 **)(path + 0x38) + index * 24);
    dx = point[0] - *(f32 *)(obj + 0x14);
    dy = point[1] - *(f32 *)(obj + 0x18);
    dz = point[2] - *(f32 *)(obj + 0x1C);
    if (dz * dz + (dx * dx + dy * dy) > 10000.0f) {
        return;
    }
    (*(u8 **)(obj + 0x31C))[0x98] = id;
    obj[0x8A] = 0x12;
    *(u8 **)(*(u8 **)(obj + 0x31C) + 0x9C) = path;
    *(u8 **)(path + 0x44) = obj;
}
