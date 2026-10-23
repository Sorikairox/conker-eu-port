extern s32 D_800D3AB0;
extern s32 D_800DC26C;
extern s32 D_800DF514;  /* number of world object ids for func_150A6324 */
extern s32 D_800DF518;
extern s32 D_800DF51C;
extern s32 D_800DF520;
extern s32 D_800DF524;
extern s16 D_800D3C00[]; /* visible world object ids */
void func_1510F800(s32);
s32 func_150A49D0(s32 count, s32 *idList, s32 force);
s32 func_150A6324(u16 *, s32, f32 *, s32);

// shadow_object_vertices: adds the world objects' triangles under a shadow (box x / z +- r) after the count level
// shadow vertices at buf. Takes the D_800DC320 world objects (0xA0-byte records at D_800DBEF4) that are shown
// (+0x6E == 0, no 0x60 flag at +0x4F) and whose x / z (s16 +0x10 / +0x14) +- their size (max of u16 +0x50, +0x52)
// meet the box, refreshes their triangles (func_150A49D0) and projects them (func_150A6324).
// Returns count plus the number of vertices added.
u32 func_15187954(s32 x, s32 z, s32 r, s32 buf, u8 *light, s32 end, s32 count) {
    u8 *obj;
    s32 size;
    s32 i, n;

    if (D_800DC320 == 0) {
        return count;
    }
    func_1510F800(2);
    buf += count * 20;
    D_800DF518 = x - r;
    D_800DF51C = x + r;
    D_800DF520 = z - r;
    D_800DF524 = z + r;
    n = 0;
    obj = (u8 *) D_800DBEF4;
    for (i = 0; i < D_800DC320; i++, obj += 0xA0) {
        if (obj[0x6E] != 0 || (obj[0x4F] & 0x60)) {
            continue;
        }
        size = *(u16 *) (obj + 0x52);
        if (size < *(u16 *) (obj + 0x50)) {
            size = *(u16 *) (obj + 0x50);
        }
        if (D_800DF51C < *(s16 *) (obj + 0x10) - size || *(s16 *) (obj + 0x10) + size < D_800DF518 ||
            D_800DF524 < *(s16 *) (obj + 0x14) - size || *(s16 *) (obj + 0x14) + size < D_800DF520) {
            continue;
        }
        D_800D3C00[n++] = i;
    }
    if (n != 0) {
        func_150A49D0(n, (s32 *) D_800D3C00, 0);
        D_800D3AB0 = D_800DC26C;
        D_800DF514 = n;
        count += (func_150A6324((u16 *) D_800D3C00, buf, (f32 *) light, end) - buf) / 20;
    }
    return count;
}
