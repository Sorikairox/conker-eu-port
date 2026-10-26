#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* g_level_model_colour_groups[mesh]: per-mesh vertex colour groups */
typedef struct {
    /* 0x0 */ u8 *rgb;   /* target colour, 3 bytes per listed vertex */
    /* 0x4 */ u16 *vtx;  /* vertex indices */
    /* 0x8 */ s32 count;
} VtxColourGroup;
extern u8 *g_level_model_colour_counts;               /* group count per mesh; was D_800B1244 */
extern VtxColourGroup **g_level_model_colour_groups; /* was D_800B1240 */
extern u8 *g_level_part_vtx;               /* mesh vertex buffer (16-byte vertices); was D_800B1220 */
extern u8 *D_800BE930;               /* base vertex colours, 3 bytes per vertex */

// vertex_colours_blend: blends the vertex colours of mesh's colour groups (all with group 0xFF, else only that one)
// from their base colour towards the group's target colour by t / 256, writing the vertex rgb (+0xC..+0xE). Base
// colour: per group / vertex table D_800BE940[mesh][g] when g_level_header +0x21 bit 2 is set, else D_800BE930 by
// vertex index (offset by D_800BE944[slot] vertices for mode != 0). Mode 0 writes the g_level_part_vtx vertices, other
// modes the vertex buffer of g_world_objs[slot] (+0x20 + g_dl_buf_index * 4). Without bit 2, mode 0 needs bit 0 and mode 1
// bit 1 of +0x21.
/* was func_15173F20 */
void vtx_colour_groups_blend(s32 mesh, s32 mode, s32 t, s32 group, s32 slot) {
    VtxColourGroup *grp;
    u8 *vtxBuf;
    u8 *from;
    u8 *to;
    u8 *v;
    u8 flags;
    s32 first;
    s32 end;
    s32 g;
    s32 j;
    s32 n;

    if (g_level_model_colour_counts[mesh] == 0) {
        return;
    }
    flags = ((u8 *) g_level_header)[0x21];
    if (!(flags & 4)) {
        if (mode == 0) {
            if (!(flags & 1)) {
                return;
            }
        } else if (mode == 1) {
            if (!(flags & 2)) {
                return;
            }
        }
    }
    if (group == 0xFF) {
        first = 0;
        end = g_level_model_colour_counts[mesh];
    } else {
        if (group >= g_level_model_colour_counts[mesh]) {
            return;
        }
        first = group;
        end = group + 1;
    }
    if (mode == 0) {
        vtxBuf = g_level_part_vtx;
    } else {
        vtxBuf = *(u8 **) ((u8 *) g_world_objs + slot * 0xA0 + 0x20 + g_dl_buf_index * 4);
    }
    grp = &g_level_model_colour_groups[mesh][first];
    for (g = first; g < end; g++, grp++) {
        to = grp->rgb;
        for (j = 0; j < grp->count; j++, to += 3) {
            n = grp->vtx[j];
            if (((u8 *) g_level_header)[0x21] & 4) {
                from = (*(u8 ****) D_800BE940)[mesh][g] + j * 3;
            } else if (mode == 0) {
                from = D_800BE930 + n * 3;
            } else {
                from = D_800BE930 + (*(u16 **) D_800BE944)[slot] * 3 + n * 3;
            }
            v = vtxBuf + n * 16;
            v[0xC] = (((to[0] - from[0]) * t) >> 8) + from[0];
            v[0xD] = (((to[1] - from[1]) * t) >> 8) + from[1];
            v[0xE] = (((to[2] - from[2]) * t) >> 8) + from[2];
        }
    }
}

/* was func_151741D0 */
void vtx_colour_world_blend(s32 arg0, s32 arg1) {
    vtx_colour_groups_blend(0, 0, arg0, arg1, 0);
}

s32 world_record_find(u8);
/* was func_15174200 */
void vtx_colour_record_blend(s32 arg0, s32 arg1, s32 arg2) {
    u8 *p = (u8 *)world_record_find(arg2);
    u32 v; // fakematch: named temp fixes the order of the argument setup

    if (p != NULL) {
        v = *(u16 *)(p + 0x54) & 0xFFFF7FFF;
        vtx_colour_groups_blend(v, 1, arg0, arg1, (p - (u8 *)g_world_objs) / 0xA0);
    }
}
