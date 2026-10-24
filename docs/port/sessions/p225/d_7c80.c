#ifdef NON_MATCHING
s32 func_15081A90(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);

/* The 0x50-byte arc spec func_15106260 copies into the arc object (+0x10). */
typedef struct {
    /* 0x00 */ s16 life;        /* 300 when the caller passes -1 */
    /* 0x02 */ u8 u02;          /* 0 when the caller passes -1, else 1 */
    /* 0x04 */ f32 start[3];
    /* 0x10 */ f32 c1[3];       /* control points (func_15108060: 1/3 and 2/3 of the way) */
    /* 0x1C */ f32 c2[3];
    /* 0x28 */ f32 end[3];
    /* 0x34 */ u8 u34;
    /* 0x38 */ s32 segments;
    /* 0x3C */ f32 jitter;
    /* 0x40 */ f32 width;
    /* 0x44 */ s16 lifeBase;
    /* 0x46 */ s16 lifeRange;
    /* 0x48 */ u8 rgba[4];
    /* 0x4C */ u8 u4C;          /* 2 */
} ArcSpec;

/* The 0xC-byte record the arc's data area (+0x60) gets: the object it hangs on and the attachment angles. */
typedef struct {
    u8 *obj;
    u8 id;                      /* obj[0x3B] */
    s16 angle0;
    s16 angle1;
} ArcLink;

// object_arc_to_surface_spawn: casts a ray (func_15081A90) from the object's attachment point at angles
// (angle0, angle1) (func_15107FA0) outwards from the object's centre and, when it hits something, spawns a lightning arc
// (func_15106260, 0xC extra bytes for an ArcLink back to the object) from the point to the hit, with control points at
// 1/3 and 2/3 (func_15108060). life -1 = 300 and spec +0x02 = 0. Returns the arc, 0 when the object has no +0x1D4, the
// ray hits nothing or no arc could be spawned.
s32 func_15107C80(u8 *obj, s16 angle0, s16 angle1, s16 life, s32 segments, f32 jitter, f32 width, s32 lifeBase,
                  s32 lifeRange, s8 *rgba, s32 layer, s32 arg11) {
    u8 hit[0x64];
    f32 origin[3];
    ArcSpec spec;
    ArcLink link;
    u8 *arc;

    if (*(s32 *)(obj + 0x1D4) == 0) {
        return 0;
    }
    link.obj = obj;
    link.id = obj[0x3B];
    link.angle0 = angle0;
    link.angle1 = angle1;
    spec.life = (life == -1) ? 300 : life;
    spec.u02 = (life == -1) ? 0 : 1;
    spec.u34 = 0;
    spec.segments = segments;
    spec.jitter = jitter;
    spec.width = width;
    spec.lifeBase = lifeBase;
    spec.lifeRange = lifeRange;
    spec.rgba[0] = rgba[0];
    spec.rgba[1] = rgba[1];
    spec.rgba[2] = rgba[2];
    spec.rgba[3] = rgba[3];
    spec.u4C = 2;
    func_15107FA0(obj, angle0, angle1, (u8 *)spec.start, (u8 *)origin);
    func_15081A90((struct127 *)obj, spec.start[0], spec.start[1], spec.start[2], spec.start[0] - origin[0],
                  spec.start[1] - origin[1], spec.start[2] - origin[2], hit, 0.0f, 0, 1, 1, -1, 0, 0);
    if (hit[0x59] == 0) {
        return 0;
    }
    spec.end[0] = *(f32 *)(hit + 0x08);
    spec.end[1] = *(f32 *)(hit + 0x0C);
    spec.end[2] = *(f32 *)(hit + 0x10);
    func_15108060(spec.start, spec.end, spec.c1, spec.c2);
    arc = func_15106260(&spec.life, 0xC, layer, arg11);
    if (arc != NULL) {
        memcpy(*(u8 **)(arc + 0x60), &link, 0xC);
    }
    return (s32)arc;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15107C80.s")
#endif
