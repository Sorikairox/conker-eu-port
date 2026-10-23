f32 sinf(f32);
f32 cosf(f32);
extern u8 *D_800DA280[]; /* texture scroller records, D_800D9E64 of them */
extern Vtx *D_800B1220[2]; /* the two vertex buffers the scrollers patch */

// tex_scroll_update: per frame, for every enabled texture scroller record r (r[0xC] == 0): advances its angle
// (u16 +0xE += speed +0x10 * D_800BE9E4), turns it into an offset (radius +0x12 * sin / cos of angle * 2pi / 65536)
// and writes base texture coordinates + offset into the Vtx tc of r[8] vertices of buffer 0 (from vertex r[0xA],
// base pairs at +0) and r[9] vertices of buffer 1 (from vertex r[0xB], base pairs at +4). A record without the
// buffer-0 list uses the offset of the previous record (the asm keeps it in registers; it starts as two
// uninitialised stack halfwords, 0 here). The asm returns nothing; s32 matches the caller's prototype.
s32 func_1510CE28(void) {
    u8 *r;
    Vtx *v;
    s16 *base;
    s32 i;
    s32 j;
    s16 dx;
    s16 dy;
    f32 a;
    f32 s;
    f32 c;
    f32 radius;
    u32 angle;

    dx = 0;
    dy = 0;
    for (i = 0; i < D_800D9E64; i++) {
        r = D_800DA280[i];
        if (r[0xC] != 0) {
            continue;
        }
        if (*(s16 **) r != NULL) {
            *(u16 *) (r + 0xE) += *(u16 *) (r + 0x10) * D_800BE9E4;
            angle = *(u16 *) (r + 0xE);
            v = D_800B1220[0] + r[0xA];
            a = angle * 9.58738e-05f; /* 2pi / 65536 */
            s = sinf(a);
            c = cosf(a);
            radius = (u32) * (u16 *) (r + 0x12);
            dx = radius * s;
            dy = radius * c;
            base = *(s16 **) r;
            for (j = 0; j < r[8]; j++) {
                v[j].v.tc[0] = base[j * 2] + dx;
                v[j].v.tc[1] = base[j * 2 + 1] + dy;
            }
        }
        if (*(s16 **) (r + 4) != NULL) {
            v = D_800B1220[1] + r[0xB];
            base = *(s16 **) (r + 4);
            for (j = 0; j < r[9]; j++) {
                v[j].v.tc[0] = base[j * 2] + dx;
                v[j].v.tc[1] = base[j * 2 + 1] + dy;
            }
        }
    }
    return 0;
}
