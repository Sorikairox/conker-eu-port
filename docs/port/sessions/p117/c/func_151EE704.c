// menu_sprites_load: mode 3's first frame. Allocates the 0x1A8-byte menu sprite block D_800E10AC (0x40 header bytes,
// then 30 entries of 12 bytes at D_800904E8: display list, asset, +8 filled by func_1510D3E0), loads the menu
// sprite assets 0x1C5..0x1E2 (func_1502B6BC(NULL, 1, NULL, 2, 9, id)) and patches each display list up to its
// G_ENDDL (0xDF): G_VTX (1) addresses are relocated into the asset and the first two vertices get colour 0,0,0,0xFF,
// G_SETCOMBINE (0xFC) becomes 0xFC127E05 / 0xFFFFF3F8, G_SETOTHERMODE_H (0xEF) gets bit 0x100000 and w1 0x0F0A4000.
// Then clears D_800E10B0..B4 and the block's bytes 0 and 0x20. On allocation failure D_800904E8 stays NULL.
void func_151EE704(void) {
    u8 *block;
    s32 *asset;
    u32 *dl;
    u8 *vtx;
    s32 id;
    s32 off;
    u32 cmd;

    D_800904E8 = NULL;
    block = allocate_memory(0x1A8, 1, 0, 0);
    D_800E10AC = block;
    if (block == NULL) {
        return;
    }
    D_800904E8 = block + 0x40;
    for (id = 0x1C5, off = 0; id != 0x1E3; id++, off += 0xC) {
        asset = (s32 *) func_1502B6BC(NULL, 1, NULL, 2, 9, id);
        *(s32 **) (D_800904E8 + off + 4) = asset;
        *(s32 *) (D_800904E8 + off) = *asset;
        func_1510D3E0(*(s32 *) (D_800904E8 + off), 0, 1, 0x3E, (s32 *) (D_800904E8 + off + 8));
        dl = *(u32 **) (D_800904E8 + off);
        do {
            cmd = (dl[0] >> 24) & 0xFF;
            if (cmd == 1) {
                dl[1] += (u32) asset;
                vtx = (u8 *) (dl[1] | 0x80000000);
                vtx[0xC] = 0;
                vtx[0xD] = 0;
                vtx[0xE] = 0;
                vtx[0xF] = 0xFF;
                vtx += 0x10;
                vtx[0xC] = 0;
                vtx[0xD] = 0;
                vtx[0xE] = 0;
                vtx[0xF] = 0xFF;
            }
            if (cmd == 0xFC) {
                dl[0] = 0xFC127E05;
                dl[1] = 0xFFFFF3F8;
            }
            if (cmd == 0xEF) {
                dl[1] = 0x0F0A4000;
                dl[0] |= 0x100000;
            }
            dl += 2;
        } while (cmd != 0xDF);
    }
    D_800E10B0 = 0;
    D_800E10B1 = 0;
    D_800E10B2 = 0;
    D_800E10B3 = 0;
    D_800E10AC[0] = 0;
    D_800E10AC[0x20] = 0;
    D_800E10B4 = 0;
}
