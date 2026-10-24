u8 *allocate_memory(s32, s32, s32, s32);
s32 func_1510C4E0(Gfx *dl, s32 key, Vtx **out, s32 skip);
extern s32 D_800B0E00[];  /* level display lists */
extern s32 D_800B1214;    /* = D_800B0E00[1] */
extern u8 *D_800DA280[];  /* texture scroller records, D_800D9E64 of them */
extern Vtx *D_800B1220[2]; /* the two vertex buffers the scrollers patch */

// tex_scroll_create: P181: creates the (only) texture scroller record (20 bytes, see func_1510CE28): disabled flag
// +0xC = `off`, angle +0xE = 0, speed +0x10, radius +0x12. For texture key `key` in level display list 0 and key
// D_80091B68 in list 1 (func_1510C4E0) it stores the vertex count (+8 / +9), the first vertex index in vertex
// buffer 0 / 1 (+0xA / +0xB) and a copy of their base texture coordinates (s16 pairs, +0 / +4). NULL when a record
// exists already or the allocation fails (the coordinate arrays are not checked).
u8 *func_1510CA2C(s32 key, s32 off, s32 speed, s32 radius) {
    u8 *r;
    s16 *base;
    Vtx *v;
    s32 n;
    s32 i;

    if (D_800D9E64 != 0) {
        return NULL;
    }
    r = allocate_memory(20, 1, 0, 0);
    if (r == NULL) {
        return NULL;
    }
    D_800DA280[D_800D9E64++] = r;
    *(s16 **)(r + 0) = NULL;
    *(s16 **)(r + 4) = NULL;
    *(u16 *)(r + 0xE) = 0;
    r[0xC] = off;
    *(u16 *)(r + 0x10) = speed;
    *(u16 *)(r + 0x12) = radius;
    n = func_1510C4E0((Gfx *)D_800B0E00[0], key, &v, 0);
    if (n != 0) {
        r[8] = n;
        r[0xA] = ((u8 *)v - (u8 *)D_800B1220[0]) >> 4;
        base = (s16 *)allocate_memory(n * 4, 1, 0, 0);
        *(s16 **)(r + 0) = base;
        for (i = 0; i < n; i++) {
            base[i * 2] = v[i].v.tc[0];
            base[i * 2 + 1] = v[i].v.tc[1];
        }
    }
    n = func_1510C4E0((Gfx *)D_800B1214, D_80091B68, &v, 0);
    if (n != 0) {
        r[9] = n;
        r[0xB] = ((u8 *)v - (u8 *)D_800B1220[1]) >> 4;
        base = (s16 *)allocate_memory(n * 4, 1, 0, 0);
        *(s16 **)(r + 4) = base;
        for (i = 0; i < n; i++) {
            base[i * 2] = v[i].v.tc[0];
            base[i * 2 + 1] = v[i].v.tc[1];
        }
    }
    return r;
}
