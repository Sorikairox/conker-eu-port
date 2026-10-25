#ifdef NON_MATCHING
void func_151D6310(void *, s16, s32, void *, u8 *);
f32 sqrtf(f32);
// beam_quad_build: entry of the D_8008A1E0 draw table (`s16 *(u8 *, s16 slot)`, same family as func_1519CADC).
// Gets 0x40 bytes of vertices for the view slot from the record's buffers at +0x100 (func_151D6310; on a fresh
// buffer the matrix at +0xC0 is copied into both halves of it) and returns them (NULL when none). The beam runs from
// +0x34 towards +0x40, cut at the fraction +0x30; each end becomes a pair of vertices offset by +/- the half width
// +0x2C along (beam x (end - camera)) normalised, the camera of slot being D_800DBFF0 + slot * 0x9A0 (+0x2F8).
s16 *func_15198180(u8 *arg0, s16 arg1) {
    s16 *vtx;
    s16 *ret;
    u8 fresh;
    u8 *buf;
    f32 *a = (f32 *) (arg0 + 0x34);
    f32 *b = (f32 *) (arg0 + 0x40);
    f32 *cam;
    f32 mid[3];
    f32 d[3];
    f32 c[3];
    f32 cr[3];
    f32 off[3];
    f32 len2;
    f32 s;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &vtx, &fresh);
    ret = vtx;
    if (vtx == NULL) {
        return NULL;
    }
    if (fresh) {
        buf = *(u8 **) (arg0 + 0x100 + arg1 * 4);
        memcpy(buf, arg0 + 0xC0, 0x40);
        memcpy(buf + 0x40, arg0 + 0xC0, 0x40);
    }
    mid[0] = a[0] + (b[0] - a[0]) * *(f32 *) (arg0 + 0x30);
    mid[1] = a[1] + (b[1] - a[1]) * *(f32 *) (arg0 + 0x30);
    mid[2] = a[2] + (b[2] - a[2]) * *(f32 *) (arg0 + 0x30);
    cam = (f32 *) ((u8 *) D_800DBFF0 + arg1 * 0x9A0 + 0x2F8);

    /* the start pair */
    d[0] = mid[0] - a[0];
    d[1] = mid[1] - a[1];
    d[2] = mid[2] - a[2];
    c[0] = a[0] - cam[0];
    c[1] = a[1] - cam[1];
    c[2] = a[2] - cam[2];
    cr[0] = d[1] * c[2] - c[1] * d[2];
    cr[1] = d[2] * c[0] - c[2] * d[0];
    cr[2] = d[0] * c[1] - c[0] * d[1];
    len2 = cr[0] * cr[0] + cr[1] * cr[1] + cr[2] * cr[2];
    if (len2 == 0.0f) {
        off[0] = off[1] = off[2] = 0.0f;
    } else {
        s = *(f32 *) (arg0 + 0x2C) / sqrtf(len2);
        off[0] = cr[0] * s;
        off[1] = cr[1] * s;
        off[2] = cr[2] * s;
    }
    vtx[0] = (s32) (a[0] + off[0]);
    vtx[1] = (s32) (a[1] + off[1]);
    vtx[2] = (s32) (a[2] + off[2]);
    vtx[3] = 0;
    vtx += 8;
    vtx[0] = (s32) (a[0] - off[0]);
    vtx[1] = (s32) (a[1] - off[1]);
    vtx[2] = (s32) (a[2] - off[2]);
    vtx[3] = 0;
    vtx += 8;

    /* the cut-end pair: the reversed beam against the camera */
    d[0] = -d[0];
    d[1] = -d[1];
    d[2] = -d[2];
    c[0] = mid[0] - cam[0];
    c[1] = mid[1] - cam[1];
    c[2] = mid[2] - cam[2];
    cr[0] = d[1] * c[2] - c[1] * d[2];
    cr[1] = d[2] * c[0] - c[2] * d[0];
    cr[2] = d[0] * c[1] - c[0] * d[1];
    len2 = cr[0] * cr[0] + cr[1] * cr[1] + cr[2] * cr[2];
    if (len2 == 0.0f) {
        off[0] = off[1] = off[2] = 0.0f;
    } else {
        s = *(f32 *) (arg0 + 0x2C) / sqrtf(len2);
        off[0] = cr[0] * s;
        off[1] = cr[1] * s;
        off[2] = cr[2] * s;
    }
    vtx[0] = (s32) (mid[0] + off[0]);
    vtx[1] = (s32) (mid[1] + off[1]);
    vtx[2] = (s32) (mid[2] + off[2]);
    vtx[3] = 0;
    vtx += 8;
    vtx[0] = (s32) (mid[0] - off[0]);
    vtx[1] = (s32) (mid[1] - off[1]);
    vtx[2] = (s32) (mid[2] - off[2]);
    vtx[3] = 0;
    return ret;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198180.s")
#endif
