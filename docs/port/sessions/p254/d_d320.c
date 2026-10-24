#ifdef NON_MATCHING
// path_trail_spawn_effects: spawns effect `kind` (func_1505D1C4) at even spacing along the path of `arg0` (needs a
// count +0x2C >= 2): walks back from the head point +0x2E to the current point +0x2D (ring of +0x25 points of 0x28
// bytes at +0x94, +0x1C = segment length), starting from the position at +0x10; whenever the walked length reaches
// the next mark (0, then every owner +0x14C * step), one effect is spawned on that segment, interpolated back towards
// the previous point, for the owner's object (**(arg0 + 0x98): its D_800CC2D0 index and u16 +0x76).
void func_1519D320(s32 arg0, f32 step, s32 kind) {
    u8 *self = (u8 *) arg0;
    u8 *owner = *(u8 **) (self + 0x98);
    u8 *points = *(u8 **) (self + 0x94);
    f32 *prev = (f32 *) (self + 0x10);
    f32 *pt;
    u8 *obj;
    f32 spacing;
    f32 walked;
    f32 mark;
    f32 len;
    f32 t;
    s32 i;

    if (*(s8 *) (self + 0x2C) < 2) {
        return;
    }
    walked = 0.0f;
    mark = 0.0f;
    spacing = *(f32 *) (owner + 0x14C) * step;
    i = *(s8 *) (self + 0x2E);
    do {
        i--;
        if (i < 0) {
            i = self[0x25] - 1;
        }
        pt = (f32 *) (points + i * 0x28);
        len = pt[7];
        walked += len;
        if (mark <= walked) {
            obj = *(u8 **) owner;
            t = (walked - mark) / len;
            func_1505D1C4(pt[0] + (prev[0] - pt[0]) * t, pt[1] + (prev[1] - pt[1]) * t, pt[2] + (prev[2] - pt[2]) * t,
                          kind, (s32) (obj - (u8 *) D_800CC2D0) / 0x32C, *(u16 *) (obj + 0x76), 0, 0);
            mark += spacing;
        }
        prev = pt;
    } while (i != *(s8 *) (self + 0x2D));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519D320.s")
#endif
