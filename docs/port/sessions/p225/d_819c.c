#ifdef NON_MATCHING
/* The 0x18-byte record the arc's data area (+0x60) gets: the object, a point and a kind byte. */
typedef struct {
    u8 *obj;
    u8 id;                      /* obj[0x3B] */
    f32 pos[3];                 /* 0x08 */
    u8 kind;                    /* 0x14 */
} ArcPointLink;

// object_arc_from_point_spawn: like func_15107C80 but from the object's point `pos` / `kind` (func_151084D4) in the
// direction of angles (angle0, angle1) (func_15143794, unit length): the ray (func_15081A90, length 300) ends the
// arc at the hit, or 300 units out when it hits nothing. Spec +0x34 = 1, +0x4C = 3, 0x18 extra bytes for an
// ArcPointLink. Returns the arc, 0 when the object has no +0x1D4 or no arc could be spawned.
s32 func_1510819C(u8 *obj, u8 kind, f32 *pos, s16 angle0, s16 angle1, s16 life, s32 segments, f32 jitter,
                  f32 width, s32 lifeBase, s32 lifeRange, s8 *rgba, s32 layer, s32 arg13) {
    u8 hit[0x64];
    f32 dir[3];
    ArcSpec spec;
    ArcPointLink link;
    u8 *arc;

    if (*(s32 *)(obj + 0x1D4) == 0) {
        return 0;
    }
    link.obj = obj;
    link.id = obj[0x3B];
    link.pos[0] = pos[0];
    link.pos[1] = pos[1];
    link.pos[2] = pos[2];
    link.kind = kind;
    spec.life = (life == -1) ? 300 : life;
    spec.u02 = (life == -1) ? 0 : 1;
    spec.u34 = 1;
    spec.segments = segments;
    spec.jitter = jitter;
    spec.width = width;
    spec.lifeBase = lifeBase;
    spec.lifeRange = lifeRange;
    spec.rgba[0] = rgba[0];
    spec.rgba[1] = rgba[1];
    spec.rgba[2] = rgba[2];
    spec.rgba[3] = rgba[3];
    spec.u4C = 3;
    func_151084D4(obj, kind, pos, spec.start);
    func_15143794(angle0, angle1, 1.0f, (u8 *)dir);
    func_15081A90((struct127 *)obj, spec.start[0], spec.start[1], spec.start[2], dir[0], dir[1], dir[2], hit,
                  300.0f, 0, 1, 1, -1, 0, 0);
    if (hit[0x59] == 0) {
        spec.end[0] = spec.start[0] + dir[0] * 300.0f;
        spec.end[1] = spec.start[1] + dir[1] * 300.0f;
        spec.end[2] = spec.start[2] + dir[2] * 300.0f;
    } else {
        spec.end[0] = *(f32 *)(hit + 0x08);
        spec.end[1] = *(f32 *)(hit + 0x0C);
        spec.end[2] = *(f32 *)(hit + 0x10);
    }
    func_15108060(spec.start, spec.end, spec.c1, spec.c2);
    arc = func_15106260(&spec.life, 0x18, layer, arg13);
    if (arc != NULL) {
        memcpy(*(u8 **)(arc + 0x60), &link, 0x18);
    }
    return (s32)arc;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_1510819C.s")
#endif
