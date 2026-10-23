s32 func_1510D66C(s32, s32 *, s32, s32);
extern s32 D_800B1268[]; /* per texture key: the texture address its G_SETTIMG loads */

// dl_find_texture_vertices: P181: scans display list `dl` for the (skip+1)-th G_SETTIMG (0xFD) of texture
// D_800B1268[key], then walks to the vertex load (G_VTX, 1) of the triangles drawn with it and follows the
// triangle commands (G_TRI1 5, G_TRI2 6, 0x1X four-triangle packs) until the next texture or G_ENDDL. *out gets
// the lowest vertex address used (the loaded block start, moved up to the smallest vertex index of the first
// triangle seen after walking back to the load); the result is the number of vertices from *out to the highest
// index used of the last load. 0 when the texture is not found. The G_VTX scan back steps one command before the
// load (the asm re-reads that command as part of the triangle phase). `vbase` is an uninitialised stack slot in
// the asm (only read when a texture or G_ENDDL ends the list before any vertex load); 0 here.
s32 func_1510C4E0(Gfx *dl, s32 key, Vtx **out, s32 skip) {
    s32 idx[12];
    s32 tmp;
    s32 state;
    s32 max;
    s32 nest;
    s32 first;
    s32 found;
    s32 n;
    s32 k;
    s32 lo;
    u32 w0;
    u32 w1;
    u32 vbase;
    s32 c;

    func_1510D66C(key, &tmp, 3, 0);
    *out = NULL;
    state = 0;
    max = 0;
    nest = 0;
    first = 0;
    vbase = 0;
    for (;;) {
        c = (s8)(dl->words.w0 >> 24);
        if (state == 0) {
            /* find the texture */
            if (c == -0x21) {
                return 0;
            }
            if (c == -3 && dl->words.w1 == (u32)D_800B1268[key]) {
                if (skip-- < 1) {
                    state++;
                }
            }
            dl++;
        } else if (state == 1) {
            /* find its vertex load: forward to a G_VTX, or back from the first triangle */
            found = 0;
            if (c != 5 && c != 6 && (c >> 4) != 1) {
                for (;;) {
                    if (c == 1) {
                        found = 1;
                        break;
                    }
                    dl++;
                    c = (s8)(dl->words.w0 >> 24);
                    if (c == 5 || c == 6 || (c >> 4) == 1) {
                        break;
                    }
                }
            }
            state++;
            if (!found) {
                first = 1;
                while (c != 1) {
                    if (c == -3) {
                        nest--;
                    }
                    dl--;
                    c = (s8)(dl->words.w0 >> 24);
                }
            }
            dl--;
        } else {
            /* follow the triangles */
            if (c == -0x21) {
                break;
            }
            if (c == -3) {
                if (++nest > 0) {
                    break;
                }
            } else if (c == 1) {
                vbase = dl->words.w1;
                max = 0;
                if (*out == NULL || vbase < (u32)*out) {
                    *out = (Vtx *)vbase;
                }
            } else if (c == 5 || c == 6 || (c >> 4) == 1) {
                w0 = dl->words.w0;
                w1 = dl->words.w1;
                if (c == 5) {
                    idx[0] = (w0 >> 16) & 0xFF;
                    idx[1] = (w0 >> 8) & 0xFF;
                    idx[2] = w0 & 0xFF;
                    n = 3;
                    for (k = 0; k < n; k++) {
                        idx[k] >>= 1;
                    }
                } else if (c == 6) {
                    idx[0] = (w0 >> 16) & 0xFF;
                    idx[1] = (w0 >> 8) & 0xFF;
                    idx[2] = w0 & 0xFF;
                    idx[3] = (w1 >> 16) & 0xFF;
                    idx[4] = (w1 >> 8) & 0xFF;
                    idx[5] = w1 & 0xFF;
                    n = 6;
                    for (k = 0; k < n; k++) {
                        idx[k] >>= 1;
                    }
                } else {
                    idx[0] = (w1 >> 25) & 0x1F;
                    idx[1] = (w1 >> 20) & 0x1F;
                    idx[2] = (w1 >> 15) & 0x1F;
                    idx[3] = (w1 >> 10) & 0x1F;
                    idx[4] = (w1 >> 5) & 0x1F;
                    idx[5] = w1 & 0x1F;
                    idx[6] = (w0 >> 10) & 0x1F;
                    idx[7] = (w0 >> 5) & 0x1F;
                    idx[8] = w0 & 0x1F;
                    idx[9] = (w0 >> 23) & 0x1F;
                    idx[10] = (w0 >> 18) & 0x1F;
                    idx[11] = ((w1 >> 30) & 3) + (((w0 >> 15) & 7) << 2);
                    n = 12;
                }
                for (k = 0; k < n; k++) {
                    if (max < idx[k]) {
                        max = idx[k];
                    }
                }
                if (nest == 0 && first) {
                    lo = idx[0];
                    for (k = 1; k < n; k++) {
                        if (idx[k] < lo) {
                            lo = idx[k];
                        }
                    }
                    first = 0;
                    *out = (Vtx *)((u8 *)*out + ((lo & 0xFF) << 4));
                }
            }
            dl++;
        }
    }
    return (s32)(vbase + (max + 1) * 16 - (u32)*out) >> 4;
}
