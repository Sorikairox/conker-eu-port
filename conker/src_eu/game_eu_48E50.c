#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern u16 g_model_vtx_counts[];  /* vertex count of each model slot; was D_800C5BC0 */
extern u8 *g_obj_colour_key_sets[];  /* per colour group 1..5: RGB key colours (3 bytes each); was D_800843D0 */
extern u8 g_obj_colour_key_counts[];   /* per colour group 1..5: number of key colours (asm rodata_inject block; ROM); was D_80096CD0 */
// model_vertex_colours_blend: recolours the object's current vertex buffer (obj+0x28C, slot obj+0x1C8, buffer
// g_dl_buf_index). Each vertex's group ((u16 +6 >> 8) & 0x7F, 1..5; 0 = keep) picks a key colour ramp; the group's
// value t in 0..1 (vals[group - 1] when perGroup, else vals[0]) is linearly interpolated between the two key
// colours around it and written to the vertex colour (+0xC..+0xE). Groups 6 and up are skipped.
/* was func_eu_1501B640 */
void obj_vertex_colours_blend(struct127 *obj, f32 *vals, s32 perGroup) {
    u8 *o = (u8 *) obj;
    u8 *vtx;
    u8 *c0;
    u8 *c1;
    s32 i;
    s32 group;
    s32 prev;
    s32 k;
    f32 x;
    f32 seg;
    f32 t;
    u8 idx;
    u8 r;
    u8 g;
    u8 b;

    vtx = *(u8 **) (o + 0x28C + o[0x1C8] * 8 + g_dl_buf_index * 4);
    if (vtx == NULL) {
        return;
    }
    prev = -1;
    for (i = 0; i < g_model_vtx_counts[o[4]]; i++, vtx += 0x10) {
        group = (*(u16 *) (vtx + 6) & 0x7F00) >> 8;
        if (group == 0) {
            continue;
        }
        if (group != prev) {
            if (group >= 6) {
                continue;
            }
            prev = group;
            k = group - 1;
            x = perGroup ? vals[k] : vals[0];
            seg = 1.0f / (f32) (g_obj_colour_key_counts[k] - 1);
            idx = (u32) (x / seg);
            c0 = g_obj_colour_key_sets[k] + idx * 3;
            c1 = c0 + 3;
            t = (x - (f32) idx * seg) / seg;
            r = (u32) ((c1[0] - c0[0]) * t + c0[0]);
            g = (u32) ((c1[1] - c0[1]) * t + c0[1]);
            b = (u32) ((c1[2] - c0[2]) * t + c0[2]);
        }
        vtx[0xC] = r;
        vtx[0xD] = g;
        vtx[0xE] = b;
    }
}
