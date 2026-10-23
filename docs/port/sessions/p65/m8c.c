extern s32 D_800C48A8[];    /* per model: its display-list table (one list used here) */
extern u16 D_800C5D38[];    /* per model: triangle count */
extern u16 D_800C6318[];    /* per model: vertex-range count */

/* D_800C5C08[model] entries: a run of vertices loaded by G_VTX and the matrix group (G_MTX) they belong to */
typedef struct ModelVtxRange {
    u32 start;  /* model base D_800D19A0[model] + vertex offset */
    s32 count;
    s32 group;  /* (G_MTX address & 0xFFFFFF) >> 6 */
} ModelVtxRange;

#define DL_OP(dl, k) (((u8 *) (dl))[(k) * 8])

/*
 * P65: per-model collision / skinning tables from the model's display list (D_800C48A8[id][0], Gfx words):
 * D_800C5C08[id] = the vertex ranges (one per G_VTX, merged with the previous range when contiguous and in the
 * same G_MTX group), sorted by start address, D_800C6318[id] = their count; D_800C6070[id] = the triangles
 * (D_800C5D38[id] of them) as 3 vertex byte offsets (into the model's vertex block, from base + 0x38) each, from
 * G_TRI1 (0x05), G_TRI2 (0x06) and the packed 4-triangle commands 0x10..0x1F (5-bit indices). Already built: 0.
 * Allocation failure: 1. Vertex buffer indices are assumed < 32, as in the game's lists (the asm's buffer is 32 words).
 */
s32 func_150028BC(s32 id) {
    s32 vtxOfs[32];
    s32 idx[3];
    ModelVtxRange *ranges;
    ModelVtxRange *last;
    ModelVtxRange tmp;
    u32 *dl;
    u32 *cmd;
    u32 base;
    u32 start;
    s32 w0, w1;
    s32 j, k, v, t, n, dst, ofs;
    s32 nVtxCmds = 0;
    s32 nRanges;
    s32 nTris;
    s32 group = 0;
    u8 op;

    if (D_800C5C08[id] != 0) {
        return 0;
    }

    /* count the G_VTX commands: at most one range each */
    for (j = 0; j < 1; j++) {
        dl = ((u32 **) D_800C48A8[id])[j];
        for (k = 0; DL_OP(dl, k) != 0xDF; k++) {
            if (DL_OP(dl, k) == 0x01) {
                nVtxCmds++;
            }
        }
    }
    D_800C5C08[id] = allocate_memory(nVtxCmds * sizeof(ModelVtxRange), 1, 0, 2);
    if (D_800C5C08[id] == 0) {
        return 1;
    }
    D_800C6070[id] = allocate_memory(D_800C5D38[id] * 12, 1, 0, 2);
    if (D_800C6070[id] == 0) {
        func_10004074(D_800C5C08[id]);
        D_800C5C08[id] = 0;
        return 1;
    }

    base = ((s32 *) &D_800D19A0)[id];
    nRanges = 0;
    nTris = 0;
    for (j = 0; j < 1; j++) {
        dl = ((u32 **) D_800C48A8[id])[j];
        for (k = 0; DL_OP(dl, k) != 0xDF; k++) {
            cmd = &dl[k * 2];
            op = DL_OP(dl, k);
            w0 = cmd[0];
            w1 = cmd[1];
            if (op == 0x01) {
                /* G_VTX: n vertices from segment offset w1 into buffer slots end - n .. end - 1 */
                n = (w0 >> 12) & 0xFF;
                dst = ((w0 >> 1) & 0x7F) - n;
                ofs = (w1 & 0xFFFFFF) - 0x38;
                for (v = 0; v < n; v++) {
                    vtxOfs[dst + v] = v * 16 + ofs;
                }
                start = base + (((u32) (w1 - 0x38) & 0xFFFFFF) >> 4) * 16;
                ranges = (ModelVtxRange *) D_800C5C08[id];
                last = &ranges[nRanges - 1];
                if (nRanges != 0 && start == last->count * 16 + last->start && group == last->group) {
                    last->count += n;
                } else {
                    ranges[nRanges].start = start;
                    nRanges++;
                    ranges[nRanges - 1].group = group;
                    ranges[nRanges - 1].count = n;
                }
            } else if (op == 0xDA) {
                /* G_MTX: following vertices belong to this matrix */
                group = (w1 & 0xFFFFFF) >> 6;
            } else if (op == 0x05) {
                /* G_TRI1: buffer indices * 2 in bytes 1..3 */
                for (v = 0; v < 3; v++) {
                    ((s32 *) D_800C6070[id])[nTris * 3 + v] = vtxOfs[((u8 *) cmd)[1 + v] >> 1];
                }
                nTris++;
            } else if (op == 0x06) {
                /* G_TRI2: bytes 1..3 and 5..7 */
                for (t = 0; t < 8; t += 4) {
                    for (v = 0; v < 3; v++) {
                        ((s32 *) D_800C6070[id])[nTris * 3 + v] = vtxOfs[((u8 *) cmd)[t + 1 + v] >> 1];
                    }
                    nTris++;
                }
            } else if ((op >> 4) == 1) {
                /* 0x10..0x1F: four triangles with 5-bit buffer indices packed in w1 and w0 */
                for (t = 0; t < 4; t++) {
                    if (t == 0) {
                        idx[0] = (w1 >> 25) & 0x1F;
                        idx[1] = (w1 >> 20) & 0x1F;
                        idx[2] = (w1 >> 15) & 0x1F;
                    } else if (t == 1) {
                        idx[0] = (w1 >> 10) & 0x1F;
                        idx[1] = (w1 >> 5) & 0x1F;
                        idx[2] = w1 & 0x1F;
                    } else if (t == 2) {
                        idx[0] = (w0 >> 10) & 0x1F;
                        idx[1] = (w0 >> 5) & 0x1F;
                        idx[2] = w0 & 0x1F;
                    } else {
                        idx[0] = (w0 >> 23) & 0x1F;
                        idx[1] = (w0 >> 18) & 0x1F;
                        idx[2] = ((w1 >> 30) & 3) | ((w0 >> 13) & 0x1C);
                    }
                    for (v = 0; v < 3; v++) {
                        ((s32 *) D_800C6070[id])[nTris * 3 + v] = vtxOfs[idx[v]];
                    }
                    nTris++;
                }
            }
        }
    }

    /* gnome sort of the ranges by start address */
    D_800C6318[id] = nRanges;
    k = 1;
    while (k < D_800C6318[id]) {
        ranges = (ModelVtxRange *) D_800C5C08[id];
        if (ranges[k].start > ranges[k - 1].start) {
            tmp = ranges[k];
            ranges[k] = ranges[k - 1];
            ((ModelVtxRange *) D_800C5C08[id])[k - 1] = tmp;
            if (k >= 2) {
                k--;
            }
        } else {
            k++;
        }
    }
    return 0;
}
