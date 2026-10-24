// mesh_effect_spawn: spawns an animated mesh effect record (P195). The 0x3C-byte spawn block p (copied to rec + 0x10) names
// a model by its +0x30 / +0x34 words (func_1502B6BC, kind 2 lookup); the model header starts with its display list
// pointer, followed at +0x28 by the vertex block (size = dl - header - 0x28). The record (kind 0x54 when arg1 != 0,
// else 0x38; func_15167A68 with group arg4 and priority arg3) gets D_80082FA0 + 1 double-buffered vertex copies at
// +0xF8 (+0x58[i] / +0x68[i] point at the two halves), +0x4C = header, +0x50 = the copies' size, +0x54 = the display
// list, which is registered with func_1510D3E0 (age 0x3E). arg2 extra bytes follow the copies. Returns NULL when the
// pool is full. Callers: func_15010A60 (ambient fires), func_15108850, func_1513BAE8, game_eu_1E7CC0.
s32 func_1502B6BC(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, ...);
s32 func_1510D3E0(Gfx *dl, s32 skipResolved, s32 addRef, s32 age, s16 **outList);
void *func_15167A68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5);
void *memcpy(void *, const void *, s32);

struct102 *func_1513B5E0(void *p, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 found;
    s32 count;
    u8 *hdr;
    u8 *rec;
    u8 *dst;
    s32 size;
    s32 total;
    s32 i;

    hdr = (u8 *) func_1502B6BC(&found, 0, &count, 2, *(s32 *) ((u8 *) p + 0x30), *(s32 *) ((u8 *) p + 0x34));
    size = *(s32 *) hdr - (s32) hdr - 0x28;
    total = size * 2 * (D_80082FA0 + 1);
    rec = func_15167A68(arg1 ? 0x54 : 0x38, arg4, arg2 + total + 0xF8, 2, arg3, 1);
    if (rec == NULL) {
        return NULL;
    }
    memcpy(rec + 0x10, p, 0x3C);
    *(u8 **) (rec + 0x4C) = hdr;
    dst = rec + 0xF8;
    for (i = 0; i <= D_80082FA0; i++) {
        ((u8 **) (rec + 0x58))[i] = dst;
        ((u8 **) (rec + 0x68))[i] = dst + size;
        memcpy(dst, hdr + 0x28, size);
        memcpy(((u8 **) (rec + 0x68))[i], hdr + 0x28, size);
        dst += size * 2;
    }
    *(s32 *) (rec + 0x54) = *(s32 *) hdr;
    *(s32 *) (rec + 0x50) = total;
    func_1510D3E0(*(Gfx **) hdr, 0, 1, 0x3E, NULL);
    return (struct102 *) rec;
}
