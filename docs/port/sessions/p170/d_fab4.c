void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
f32 *func_15144B34(s32 arg0);
void func_150ADD90(u8 *, u8 *, u8 *);

// beam_quad_build: builds the 4 vertices of a camera-facing beam quad for display list slot `slot`: from the start
// point +0x34/+0x38/+0x3C towards +0x40/+0x44/+0x48, the length scaled by +0x30 x scale[1], the half width
// +0x2C x scale[0] along cross(direction, middle - camera) (func_150ADD90; the camera point from func_15144B34).
// `flip` picks the vertex order (start+, start-, end-, end+ or start-, end-, end+, start+). New vertex buffers from
// func_151D6310 are first filled (both 0x40-byte halves) from the template at +0xC0. Returns the vertices, or NULL
// when there is no buffer. Called by func_1513FA2C (order 0) / func_1513FA70 (order 1).
u8 *func_1513FAB4(u8 *fx, u8 flip, f32 *scale, s16 slot) {
    f32 dir[3];
    f32 end[3];
    f32 toCam[3];
    f32 side[3];
    f32 *cam;
    f32 halfWidth;
    f32 len;
    f32 lenSq;
    f32 s;
    u8 *vtx;
    u8 *start;
    u8 fresh;

    func_151D6310((s32 *) (fx + 0x100), slot, 0x40, (s32 *) &vtx, &fresh);
    start = vtx;
    if (vtx == NULL) {
        return NULL;
    }
    if (fresh) {
        memcpy(*(u8 **) (fx + 0x100 + slot * 4), fx + 0xC0, 0x40);
        memcpy(*(u8 **) (fx + 0x100 + slot * 4) + 0x40, fx + 0xC0, 0x40);
    }
    cam = func_15144B34(slot);
    halfWidth = *(f32 *) (fx + 0x2C) * scale[0];
    len = *(f32 *) (fx + 0x30) * scale[1];
    dir[0] = *(f32 *) (fx + 0x40) - *(f32 *) (fx + 0x34);
    dir[1] = *(f32 *) (fx + 0x44) - *(f32 *) (fx + 0x38);
    dir[2] = *(f32 *) (fx + 0x48) - *(f32 *) (fx + 0x3C);
    dir[0] *= len;
    dir[1] *= len;
    dir[2] *= len;
    end[0] = *(f32 *) (fx + 0x34) + dir[0];
    end[1] = *(f32 *) (fx + 0x38) + dir[1];
    end[2] = *(f32 *) (fx + 0x3C) + dir[2];
    toCam[0] = *(f32 *) (fx + 0x34) + dir[0] * 0.5f - cam[0];
    toCam[1] = *(f32 *) (fx + 0x38) + dir[1] * 0.5f - cam[1];
    toCam[2] = *(f32 *) (fx + 0x3C) + dir[2] * 0.5f - cam[2];
    func_150ADD90((u8 *) dir, (u8 *) toCam, (u8 *) side);
    lenSq = side[0] * side[0] + side[1] * side[1] + side[2] * side[2];
    if (lenSq == 0.0f) {
        side[0] = side[1] = side[2] = 0.0f;
    } else {
        s = halfWidth / sqrtf(lenSq);
        side[0] *= s;
        side[1] *= s;
        side[2] *= s;
    }
    if (flip) {
        *(s16 *) (vtx + 0) = (s32) (*(f32 *) (fx + 0x34) + side[0]);
        *(s16 *) (vtx + 2) = (s32) (*(f32 *) (fx + 0x38) + side[1]);
        *(s16 *) (vtx + 4) = (s32) (*(f32 *) (fx + 0x3C) + side[2]);
        *(s16 *) (vtx + 6) = 0;
        vtx += 0x10;
        *(s16 *) (vtx + 0) = (s32) (*(f32 *) (fx + 0x34) - side[0]);
        *(s16 *) (vtx + 2) = (s32) (*(f32 *) (fx + 0x38) - side[1]);
        *(s16 *) (vtx + 4) = (s32) (*(f32 *) (fx + 0x3C) - side[2]);
        *(s16 *) (vtx + 6) = 0;
        vtx += 0x10;
        *(s16 *) (vtx + 6) = 0;
        *(s16 *) (vtx + 0) = (s32) (end[0] - side[0]);
        *(s16 *) (vtx + 2) = (s32) (end[1] - side[1]);
        *(s16 *) (vtx + 4) = (s32) (end[2] - side[2]);
        vtx += 0x10;
        *(s16 *) (vtx + 6) = 0;
        *(s16 *) (vtx + 0) = (s32) (end[0] + side[0]);
        *(s16 *) (vtx + 2) = (s32) (end[1] + side[1]);
        *(s16 *) (vtx + 4) = (s32) (end[2] + side[2]);
    } else {
        *(s16 *) (vtx + 0) = (s32) (*(f32 *) (fx + 0x34) - side[0]);
        *(s16 *) (vtx + 2) = (s32) (*(f32 *) (fx + 0x38) - side[1]);
        *(s16 *) (vtx + 4) = (s32) (*(f32 *) (fx + 0x3C) - side[2]);
        *(s16 *) (vtx + 6) = 0;
        vtx += 0x10;
        *(s16 *) (vtx + 0) = (s32) (end[0] - side[0]);
        *(s16 *) (vtx + 2) = (s32) (end[1] - side[1]);
        *(s16 *) (vtx + 4) = (s32) (end[2] - side[2]);
        *(s16 *) (vtx + 6) = 0;
        vtx += 0x10;
        *(s16 *) (vtx + 0) = (s32) (end[0] + side[0]);
        *(s16 *) (vtx + 2) = (s32) (end[1] + side[1]);
        *(s16 *) (vtx + 4) = (s32) (end[2] + side[2]);
        *(s16 *) (vtx + 6) = 0;
        vtx += 0x10;
        *(s16 *) (vtx + 0) = (s32) (*(f32 *) (fx + 0x34) + side[0]);
        *(s16 *) (vtx + 2) = (s32) (*(f32 *) (fx + 0x38) + side[1]);
        *(s16 *) (vtx + 4) = (s32) (*(f32 *) (fx + 0x3C) + side[2]);
        *(s16 *) (vtx + 6) = 0;
    }
    return start;
}
