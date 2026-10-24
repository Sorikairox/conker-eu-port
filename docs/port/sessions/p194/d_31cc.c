f32 func_151834C8(s32 arg0, s32 arg1);
/* wave types (D_8008D3F0, 0x18 bytes): +0x10 the mesh's yaw, +0x12 the D_800DBEF4 record holding its vertex count */
extern s16 D_8008D400[][12];
// wave_mesh_update: P194. World mesh record (D_800DBEF4, 0xA0 bytes) handler of the wave meshes (water surfaces /
// bridges simulated by func_15182D40): wave index w = +0x3C, type D_800DE284[w], 40 height nodes (12 bytes, height
// at +8) at D_800DE290[w]. For each of the vertex-count (u16 +0x16 of the type's record D_800DBEF4[D_8008D402]) source
// vertices (+0x28, 16-byte Vtx), the node position func_151834C8(z, w) gives the interpolated height h of nodes
// floor / floor + 1 (capped at 39); the vertex (x, y + (s32) h / 16, z) is turned by the type's yaw (func_150A8050
// (0, -yaw, 0), func_150A7E40) and stored, plus the record position (+0x10 / +0x12 / +0x14), into this frame's vertex
// buffer (+0x20[D_800BE9C0]). The count is re-read every vertex.
void func_151831CC(u8 *rec) {
    s32 w = *(s32 *) (rec + 0x3C);
    u8 *type = &D_800DE284[w];
    s16 *dst = *(s16 **) (rec + 0x20 + D_800BE9C0 * 4);
    f32 mf[4][4];
    f32 outX, outY, outZ;
    s16 *src;
    u8 *nodes;
    f32 pos, frac;
    s32 n, n1;
    s32 dy;
    s32 i;

    func_150A8050(mf, 0.0f, (f32) -D_8008D400[*type][0], 0.0f);
    for (i = 0; i < *(u16 *) ((u8 *) D_800DBEF4 + D_8008D400[*type][1] * 0xA0 + 0x16); i++, dst += 8) {
        src = (s16 *) (*(u8 **) (rec + 0x28) + i * 0x10);
        pos = func_151834C8(src[2], w);
        n = (s32) pos;
        n1 = n + 1;
        if (n1 >= 40) {
            n1 = 39;
        }
        frac = pos - (f32) n;
        nodes = ((u8 **) &D_800DE290)[w];
        dy = (s32) (*(f32 *) (nodes + n1 * 12 + 8) * frac + *(f32 *) (nodes + n * 12 + 8) * (1.0f - frac));
        src = (s16 *) (*(u8 **) (rec + 0x28) + i * 0x10);
        func_150A7E40(mf, (f32) src[0], (f32) (src[1] + (dy >> 4)), (f32) src[2], &outX, &outY, &outZ);
        dst[0] = (s32) ((f32) *(s16 *) (rec + 0x10) + outX);
        dst[1] = (s32) ((f32) *(s16 *) (rec + 0x12) + outY);
        dst[2] = (s32) ((f32) *(s16 *) (rec + 0x14) + outZ);
    }
}
