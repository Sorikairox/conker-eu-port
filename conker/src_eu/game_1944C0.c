#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15168F84(s32 arg0, s32 *arg1, s32 *arg2);
#endif
typedef struct { u8 pad0[0xC]; void (*fn0C)(struct_eu_node *); u8 pad10[0xC]; void (*fn)(struct_eu_node *, s32, u8); u8 pad20[0x14]; } Tbl9070;
extern Tbl9070 D_8008B848[];


#ifdef NON_MATCHING
/* P95: per-frame update hooks: calls the +0x18 function of each of the 101 D_8008B848 entries that has one
 * (no arguments are set up: a0 is the caller's, unused by the hooks as far as known). */
void func_15167010(void) {
    Tbl9070 *p;

    for (p = D_8008B848; p < (Tbl9070 *) ((u8 *) D_8008B848 + 0x1484); p++) {
        if (*(void (**)(void)) ((u8 *) p + 0x18) != NULL) {
            (*(void (**)(void)) ((u8 *) p + 0x18))();
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167010.s")
#endif
// NON-MATCHING: EU table has 101 entries (D_8008B4A8 = 0x8008B848 in EU); register/loop shape differs
// void func_15167010(void) {
//     void (*func)(void);
//     struct115 *p;
//     s32 i;
//
//     p = D_8008B4A8;
//     for (i = 0; i < 101; i++, p++) {
//         func = (void (*)(void))p->unk18;
//         if (func != NULL) {
//             func();
//         }
//     }
// }

void func_1516706C(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_8008CF04[i] != NULL) {
            D_8008CF04[i]();
        }
    }
}
void func_151670C0(void) {
    s32 i;
    s32 j;
    struct_eu_node *node;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 101; j++) {
            if (D_8008B4A8[j].unk0 != NULL) {
                node = D_800DD280[i][j];
                D_800DD5C0++;
                while (node != NULL) {
                    D_800DD5C8[D_800DD5C0] = node->next;
                    D_8008B4A8[j].unk0((struct102 *)node);
                    node = D_800DD5C8[D_800DD5C0];
                }
                D_800DD5C0--;
            }
        }
    }
}
void func_151671E8(void) {
    s32 i;
    s32 j;
    struct_eu_node *node;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 101; j++) {
            if (((void (**)(struct_eu_node *))&D_8008B4A8[j])[1] != NULL) {
                node = D_800DD280[i][j];
                D_800DD5C0++;
                while (node != NULL) {
                    D_800DD5C8[D_800DD5C0] = node->next;
                    ((void (**)(struct_eu_node *))&D_8008B4A8[j])[1](node);
                    node = D_800DD5C8[D_800DD5C0];
                }
                D_800DD5C0--;
            }
        }
    }
}
extern f32 D_800DD600[2];
extern f32 D_800DD608[4];
extern f32 D_800DD618[4];
void func_15167310(void) {
    s32 i;
    f32 a;
    s32 j;
    struct_eu_node *node;
    s32 k;

    for (k = 0; k < D_80082FA0 + 1; k++) {
        a = *(f32 *)((u8 *)D_800DBFF0 + k * 0x9A0 + 0x3A0);
        D_800DD608[k] = sinf(a);
        D_800DD618[k] = cosf(a);
    }
    a = D_800DBFF0->unk3A0;
    D_800DD600[0] = sinf(a);
    D_800DD600[1] = cosf(a);
dummy: ; // fakematch: label splits the block (permuter)
    for (j = 0; j < 0x68; j++) {
        for (i = 0; i < 2; i++) {
            if (D_800DD280[i][j] != NULL && D_8008B848[j].fn0C != NULL) {
                node = D_800DD280[i][j];
                D_800DD5C0++;
                while (node != NULL) {
                    D_800DD5C8[D_800DD5C0] = node->next;
                    D_8008B848[j].fn0C(node);
                    node = D_800DD5C8[D_800DD5C0];
                }
                D_800DD5C0--;
            }
        }
    }
}
#ifdef NON_MATCHING
/* The fields of a D_8008B848 render layer (0x34 bytes) that func_151674F8 uses. */
typedef struct {
    u8 pad0[0x8];
    Gfx *(*draw)(Gfx *, struct_eu_node *, s16); /* per node */
    void (*fn0C)(struct_eu_node *);
    Gfx *dlPre;
    Gfx *(*pre)(Gfx *, s32, s32, s16);
    u8 pad18[0x8];
    Gfx *(*post)(Gfx *, s32, s16);
    Gfx *dlPost;
    u8 pad28[0x8];
    s8 type; /* 0: dropped whole on DL overflow, 1: per-node overflow check */
    u8 pad31[0x3];
} RenderLayer;
extern struct_eu_node *D_800DD5C8[];
extern s8 D_800DD5C0;
extern struct_eu_node *D_800DD280[][104];
extern u8 D_800D31CB;
extern s32 D_800DD5E0;
extern s32 D_800DD5E4;
extern s32 D_800DD5E8;
extern s16 D_800DD5EC;
extern s16 D_800DD5EE;
extern s16 D_800DD5F0;
extern s16 D_800DD5F2;
extern s16 D_800DD5F4;
extern s16 D_800DD5F6;
extern s16 D_800DD5F8;
extern s16 D_800DD5FA;
extern s16 D_800DD5FC;
extern s16 D_800DD5FE;
extern s16 D_800DD628;
extern s32 D_800DD62C;
extern s32 D_800DD630;
extern s16 D_800DD634;
extern s16 D_800DD636;
extern s32 D_800DD638;
extern s32 D_800DD63C;
extern s32 D_800DD640;
extern s32 D_800DD644;
extern s32 D_800DD648;
extern s32 D_800DD64C;
extern s32 D_800DD650;
extern s32 D_800DD654;
extern s32 D_800DD658;
extern Gfx *D_800BEDE8[];
extern s32 D_800BEFC4;
extern u8 D_80089810[];

#define DL_FULL(g) (D_800BEFC4 < (g) - D_800BEDE8[D_800BE9C0])

/* Draw the render layers of `group` (func_15168F84 gives the index range) from node list `list`:
 * per layer the pre DL / callback, every node's draw callback, then the post DL / callback.
 * The node walk keeps its cursor in D_800DD5C8[depth] so a callback can unlink nodes. When the DL buffer
 * runs out, a type 1 layer drops the node that overflowed and a type 0 layer is dropped whole; the
 * layer's start is then returned with a G_SETGEOMETRYMODE(1) at the cut instead of the rest. */
void *func_151674F8(void *arg0, s32 group, s16 arg2, s32 list) {
    Gfx *gdl = arg0;
    RenderLayer *layer;
    struct_eu_node **head;
    struct_eu_node *node;
    Gfx *before;
    Gfx *start0;
    Gfx *start1;
    s32 first;
    s32 last;
    s32 i;
    s32 dropped;
    Gfx *(*draw)(Gfx *, struct_eu_node *, s16);

    gSPMatrix(gdl++, D_80089810, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    func_15168F84(group, &first, &last);
    layer = &((RenderLayer *)D_8008B848)[first];
    for (i = first; i < last; i++, layer++) {
        if (layer->draw == NULL) {
            continue;
        }
        head = &D_800DD280[list][i];
        if (*head == NULL) {
            continue;
        }
        D_8003C8E0 = (i & 0xFFFFFF) | 0x07000000;
        dropped = 0;
        if (layer->type == 0) {
            start0 = gdl;
        }
        if (layer->type == 1) {
            start1 = gdl;
        }
        D_800D31CB = 0;
        D_800DD658 = 0;
        D_800DD650 = 0;
        D_800DD654 = 2;
        D_800DD5E0 = -1;
        D_800DD5E4 = -1;
        D_800DD5E8 = -1;
        D_800DD5EC = 0;
        D_800DD5EE = 0;
        D_800DD5F6 = -1;
        D_800DD5F4 = D_800DD5F6;
        D_800DD5F2 = D_800DD5F4;
        D_800DD5F0 = D_800DD5F2;
        D_800DD5FE = -1;
        D_800DD5FC = D_800DD5FE;
        D_800DD5FA = D_800DD5FC;
        D_800DD5F8 = D_800DD5FA;
        D_800DD628 = 0;
        D_800DD62C = 0;
        D_800DD630 = 0;
        D_800DD634 = -1;
        D_800DD636 = -1;
        D_800DD638 = -1;
        D_800DD63C = -1;
        D_800DD640 = -1;
        D_800DD644 = 0;
        D_800DD648 = 0;
        D_800DD64C = 0;
        if (layer->dlPre != NULL) {
            gdl->words.w0 = 0xDE000000; /* G_DL */
            gdl->words.w1 = (u32)layer->dlPre;
            gdl++;
        }
        if (layer->pre != NULL) {
            gdl = layer->pre(gdl, i, list, arg2);
        }
        gSPClearGeometryMode(gdl++, G_LIGHTING);

        node = *head;
        D_800DD5C0++;
        if (layer->type == 1) {
            while (node != NULL) {
                draw = layer->draw;
                D_800DD5C8[D_800DD5C0] = node->next;
                before = gdl;
                gdl = draw(gdl, node, arg2);
                if (DL_FULL(gdl)) {
                    dropped = 1;
                    gdl = before;
                }
                node = D_800DD5C8[D_800DD5C0];
            }
        } else {
            while (node != NULL) {
                draw = layer->draw;
                D_800DD5C8[D_800DD5C0] = node->next;
                gdl = draw(gdl, node, arg2);
                node = D_800DD5C8[D_800DD5C0];
            }
        }
        D_800DD5C0--;

        if (layer->dlPost != NULL) {
            gdl->words.w0 = 0xDE000000; /* G_DL */
            gdl->words.w1 = (u32)layer->dlPost;
            gdl++;
        }
        if (layer->post != NULL) {
            gdl = layer->post(gdl, i, arg2);
        }
        if (dropped && DL_FULL(gdl)) {
            gSPSetGeometryMode(gdl, 1);
            return start1;
        }
        if (layer->type == 0 && DL_FULL(gdl)) {
            gSPSetGeometryMode(gdl, 1);
            return start0;
        }
        D_8003C8E0 = 0;
    }
    gSPSetGeometryMode(gdl++, 1);
    return gdl;
}
#undef DL_FULL
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151674F8.s")
#endif
void *func_15167A68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5) {
    struct_eu_node *node = (struct_eu_node *)func_10003C6C(arg2, 1, arg3, 0, arg5);

    if (node != NULL) {
        node->unk1 = arg1;
        func_15168A4C(node, arg0);
        ((u8 *)node)[0xC] = arg4;
    }
    return node;
}
void func_15167AD8(void *arg0, u8 arg1, s32 arg2) {
    u8 *temp_v0 = func_15167A68(3, arg2, 0x28, 0, arg1, 1);

    if (temp_v0 != NULL) {
        bcopy(arg0, temp_v0 + 0x10, 0x18);
        temp_v0[0x23] = 0xFF;
    }
}
typedef struct {
    u8  pad0[0x10];
    u8 *unk10;
    s16 unk14;
    s16 unk16;
    u8  pad18[0xA];
    s8  unk22;
    u8  unk23;
    u8  unk24;
} struct_eu_15167B44;

void func_15167B44(struct_eu_15167B44 *arg0) {
    u8 idx = arg0->unk24;
    s32 step;
    s32 neg;

    if (idx != 0) {
        D_8008CDC0[idx]();
    }
    step = arg0->unk22;
    if (step > 0) {
        if (step < arg0->unk23) {
            arg0->unk23 -= step;
        } else {
            arg0->unk14 = arg0->unk10[4] << 8;
        }
    } else {
        neg = -step; // fakematch: hoisted out of the step < 0 block (permuter)
        if (step < 0) {
            s16 cur = arg0->unk14;

            if (cur / 256 >= arg0->unk10[4] - 1) {
                if (neg < arg0->unk23) {
                    arg0->unk23 -= neg;
                    arg0->unk14 = cur - arg0->unk16;
                }
            }
        }
    }
    arg0->unk14 += arg0->unk16;
    if (arg0->unk14 / 256 >= arg0->unk10[4]) {
        func_1516972C((struct102 *)arg0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167C58.s")
void *func_15167D84(void *arg0, s32 arg1, s32 arg2, s8 arg3, u8 arg4, s32 arg5) {
    u8 *temp_v0;
    s32 type;

    if (arg1 == 0) {
        type = 5;
    } else {
        type = 0x42;
    }
    temp_v0 = func_15167A68(type, arg5, arg2 + 0x50, 0, arg4, 1);
    if (temp_v0 == NULL) {
        return temp_v0;
    }
    bcopy(arg0, temp_v0 + 0x10, 0x38);
    temp_v0[0x48] = arg3;
    return temp_v0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167E0C.s")
#ifdef NON_MATCHING
/* P186 */
Gfx *func_15142E24(Gfx *gfx, s32 tex, s32 frame, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *flag, s32 argA);
Gfx *func_15142B7C(Gfx *gfx, s32 set, s32 clear);
Gfx *func_1513F4E4(Gfx *gfx, u8 combine, u8 *flag);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
Gfx *func_15142CF0(Gfx *gfx, s32 m, s32 l, s32 r, s32 g, s32 b, s32 a, u8 *flag);
Gfx *func_15142C10(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *flag);
Gfx *func_15095B70(Gfx *gfx, u8 *quad);
extern s32 D_800D30BC;
extern s32 D_800A4EA8[]; /* render mode pairs (2 words each) */
extern u8 D_80090BAC[];
extern u8 D_800908EC[];

/* billboard_sprite_draw: P186: draws the camera-facing sprite of object record obj for player view `player`.
 * Texture obj +0x10 (word 0 = the image, or above 0x10000000 a frame table indexed by frame obj +0x1C >> 8;
 * byte +0xA = kind), position s16 obj +0x20 / +0x22 / +0x24, size s16 obj +0x34 (width) / +0x36 (height).
 * A negative width is a size scaled by how much the sprite faces the camera: |camera yaw (view +0x380) +
 * obj[0x1B] * 1.40625| folded into 0..90 degrees, times -width / 90, at least 1024. A negative height is
 * |view +0x388| * (max(width, 0) + height) / 90 - height. Render mode: flag 0x100 in u16 obj +0x44 takes the
 * combiner byte / D_800A4EA8 entry from obj +0x14 (bit 0x200: +0x100000), otherwise by texture kind (5 with
 * flag 0x10: combiner 13 / entry 18, 5: combiner 15 / entry 17 / +0x100000, other: combiner 13 / entry 3).
 * Primitive colour obj +0x3C..0x3F, environment colour obj +0x40..0x42 (flag 1) or by texture (D_80090BAC
 * (128, 128, 255), D_800908EC white, else black). Returns the display list end. */
s32 func_15168118(s32 gdl, u8 *obj, s16 player) {
    struct {
        s16 x, y, z;
        s16 w, h;
    } quad;
    u8 flag;
    Gfx *gfx = (Gfx *) gdl;
    u8 *tex = *(u8 **) (obj + 0x10);
    u8 *view = (u8 *) D_800DBFF0 + player * 0x9A0;
    u16 flags;
    s32 img;
    s32 w, h;
    s32 *mode;
    f32 ang;
    u8 r, g, b;

    flag = 1;
    img = *(s32 *) tex;
    if ((u32) img >= 0x10000000) {
        img = ((s32 *) img)[*(s16 *) (obj + 0x1C) >> 8];
    }
    gfx = func_15142E24(gfx, (s32) tex, *(s16 *) (obj + 0x1C) << 8, 2, 0x100, 0x100, img, 5, (s32) &quad, &flag, 3);

    quad.x = *(s16 *) (obj + 0x20);
    quad.y = *(s16 *) (obj + 0x22);
    quad.z = *(s16 *) (obj + 0x24);

    w = *(s16 *) (obj + 0x34);
    if (w < 0) {
        ang = fabsf(*(f32 *) (view + 0x380) + (f32) obj[0x1B] * 1.40625f);
        while (ang >= 360.0f) {
            ang -= 360.0f;
        }
        if (ang >= 180.0f) {
            ang -= 180.0f;
        }
        if (ang >= 90.0f) {
            ang = 180.0f - ang;
        }
        w = (s32) ((f32) w * ang * (-1.0f / 90.0f));
        if (w < 0x400) {
            w = 0x400;
        }
    }
    quad.w = w;

    h = *(s16 *) (obj + 0x36);
    if (h < 0) {
        w = *(s16 *) (obj + 0x34);
        if (w < 0) {
            w = 0;
        }
        h = (s32) (fabsf(*(f32 *) (view + 0x388)) * (f32) (w + h) * (1.0f / 90.0f) - (f32) h);
    }
    quad.h = h;

    flags = *(u16 *) (obj + 0x44);
    if (flags & 0x100) {
        u8 combine = obj[0x15];
        u8 entry = obj[0x17];

        gfx = func_15142B7C(gfx, 5, 0);
        gfx = func_1513F4E4(gfx, combine, &flag);
        mode = &D_800A4EA8[entry * 2];
        gfx = func_15142FBC(gfx, ((flags & 0x200) ? 0x100000 : 0) | D_800D30BC | 0x2CA0,
                            (mode[1] | mode[0]) | 4, &flag);
    } else if (tex[0xA] != 5) {
        gfx = func_1513F4E4(gfx, 13, &flag);
        gfx = func_15142FBC(gfx, D_800D30BC | 0x2CA0, (D_800A4EA8[3 * 2 + 1] | D_800A4EA8[3 * 2]) | 4, &flag);
    } else if (flags & 0x10) {
        /* (the asm also holds an unreachable kind 3 branch here: combiner 14 / entry 3) */
        gfx = func_1513F4E4(gfx, 13, &flag);
        gfx = func_15142FBC(gfx, D_800D30BC | 0x2CA0, (D_800A4EA8[18 * 2 + 1] | D_800A4EA8[18 * 2]) | 4, &flag);
    } else {
        gfx = func_1513F4E4(gfx, 15, &flag);
        gfx = func_15142FBC(gfx, D_800D30BC | 0x100000 | 0x2CA0, (D_800A4EA8[17 * 2 + 1] | D_800A4EA8[17 * 2]) | 4,
                            &flag);
    }

    gfx = func_15142CF0(gfx, 1, 0, obj[0x3C], obj[0x3D], obj[0x3E], obj[0x3F], &flag);
    if (flags & 1) {
        r = obj[0x40];
        g = obj[0x41];
        b = obj[0x42];
    } else if (*(u8 **) (obj + 0x10) == D_80090BAC) {
        r = 128;
        g = 128;
        b = 255;
    } else if (*(u8 **) (obj + 0x10) == D_800908EC) {
        r = 255;
        g = 255;
        b = 255;
    } else {
        r = g = b = 0;
    }
    gfx = func_15142C10(gfx, r, g, b, 0, &flag);
    return (s32) func_15095B70(gfx, (u8 *) &quad);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168118.s")
#endif
#ifdef NON_MATCHING
/* P125 */
extern u8 *D_8008CDEC[];

/* sprite_quad_init: fills the two 4-vertex quads at the start of a sprite spawn record (8 Vtx, 0x80 bytes) with
 * colour (r, g, b, a) and flag 0, and their texture coordinates from the texture D_8008CDEC[rec[0xA0]] (u16 width
 * +6, height +8; S10.5 coordinates (size + 256) << 5, the other edge 256 << 5). Record flags u16 +0x98: 0x80 flips
 * t, 0x100 flips s. Also clears the s16 at +0x88, +0x9C and +0x9E. The colour parameters are bytes. Returns the
 * last t value (what the asm leaves in v0; the callers, declared s32, ignore it). */
s32 func_1516865C(u8 *rec, s32 r, s32 g, s32 b, s32 a) {
    Vtx *v = (Vtx *) rec;
    u8 *tex;
    u16 flags;
    s16 s0, s1, t0, t1;
    s32 i;

    tex = D_8008CDEC[rec[0xA0]];
    s0 = 0x2000;
    t0 = 0x2000;
    s1 = (*(u16 *) (tex + 6) + 0x100) << 5;
    t1 = (*(u16 *) (tex + 8) + 0x100) << 5;
    for (i = 0; i < 8; i++) {
        v[i].v.flag = 0;
        v[i].v.cn[0] = r;
        v[i].v.cn[1] = g;
        v[i].v.cn[2] = b;
        v[i].v.cn[3] = a;
    }
    flags = *(u16 *) (rec + 0x98);
    if (flags & 0x80) {
        t1 = 0x2000;
        t0 = (*(u16 *) (D_8008CDEC[rec[0xA0]] + 8) + 0x100) << 5;
    }
    if (flags & 0x100) {
        s1 = 0x2000;
        s0 = (*(u16 *) (D_8008CDEC[rec[0xA0]] + 6) + 0x100) << 5;
    }
    v[6].v.tc[0] = s0;
    v[7].v.tc[1] = t0;
    v[7].v.tc[0] = s1;
    v[1].v.tc[0] = v[5].v.tc[0] = v[2].v.tc[0] = v[6].v.tc[0];
    v[5].v.tc[1] = t1;
    *(s16 *) (rec + 0x88) = 0;
    v[2].v.tc[1] = v[6].v.tc[1] = v[3].v.tc[1] = v[7].v.tc[1];
    *(s16 *) (rec + 0x9C) = 0;
    *(s16 *) (rec + 0x9E) = 0;
    v[0].v.tc[0] = v[4].v.tc[0] = v[3].v.tc[0] = v[7].v.tc[0];
    v[0].v.tc[1] = v[4].v.tc[1] = v[1].v.tc[1] = v[5].v.tc[1];
    return t0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516865C.s")
#endif
void *func_15168800(void *arg0, u8 arg1, s32 arg2) {
    u8 *temp_v0 = func_15167A68(0xE, arg2, 0xB8, 1, arg1, 1);

    if (temp_v0 == NULL) {
        return NULL;
    }
    bcopy(arg0, temp_v0 + 0x10, 0xA8);
    return temp_v0;
}
extern u8 *D_8008CDEC[];
extern void (*D_8008CD68[])(u8 *);

void func_15168870(u8 *arg0) {
    s16 speed = *(s16 *)(arg0 + 0x9A);
    s32 len;
    s8 w;
    s32 t;

    if (speed != 0) {
        t = D_8008CDEC[arg0[0xB0]][4];
        len = (t << 8) - 1;
        *(s16 *)(arg0 + 0x98) += speed * D_800BE9E4;
        if (*(s16 *)(arg0 + 0x98) > len) {
            if (*(u16 *)(arg0 + 0xA8) & 0x40) {
                *(s16 *)(arg0 + 0x98) = len - *(s16 *)(arg0 + 0x98) % len;
                *(s16 *)(arg0 + 0x9A) = -speed;
            } else if (*(u16 *)(arg0 + 0xA8) & 4) {
                *(s16 *)(arg0 + 0x98) = -1;
            } else {
                do {
                    *(s16 *)(arg0 + 0x98) -= len;
                } while (*(s16 *)(arg0 + 0x98) > len);
            }
        } else if (*(s16 *)(arg0 + 0x98) < 0) {
            if (*(u16 *)(arg0 + 0xA8) & 0x40) {
                *(s16 *)(arg0 + 0x98) = -*(s16 *)(arg0 + 0x98) % len;
                *(s16 *)(arg0 + 0x9A) = -speed;
            } else if (*(u16 *)(arg0 + 0xA8) & 4) {
                *(s16 *)(arg0 + 0x98) = -1;
            } else {
                do {
                    *(s16 *)(arg0 + 0x98) += len;
                } while (*(s16 *)(arg0 + 0x98) < 0);
            }
        }
    }
    w = arg0[0xB2];
    if (w != -1 && D_8008CD68[w] != NULL) {
        D_8008CD68[w](arg0);
    }
    if (*(s16 *)(arg0 + 0x98) == -1) {
        func_1516972C((struct102 *)arg0);
    }
}
void func_15168A2C(s32 arg0) {
    func_15168B10(arg0, 0);
}
void func_15168A4C(struct_eu_node *arg0, s32 arg1) {
    s32 group = arg0->unk1;
    struct_eu_node **head = &D_800DD280[group][arg1];

    arg0->next = *head;
    if (arg0->next != NULL) {
        arg0->next->prev = arg0;
    }
    arg0->unk0 = arg1;
    arg0->prev = NULL;
    *head = arg0;
}
void func_15168A9C(struct_eu_node *arg0) {
    s32 group = arg0->unk1;
    s32 idx = arg0->unk0;
    struct_eu_node **head = &D_800DD280[group][idx];

    if (arg0 == *head) {
        *head = arg0->next;
    }
    if (arg0->next != NULL) {
        arg0->next->prev = arg0->prev;
    }
    if (arg0->prev != NULL) {
        arg0->prev->next = arg0->next;
    }
}

void func_15168B10(s32 arg0, s32 arg1) {
    func_15168A9C(arg0);
    func_15168A4C(arg0, arg1);
}

#ifdef NON_MATCHING
void func_15168B44(u8 *arg0) {
    s32 temp_t2;
    s32 temp_t6;
    s32 temp_t9;
    s32 temp_v1;
    u8 temp_a2;

    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x14));
    temp_t6 = temp_v1 & 0xFFFF;
    if (temp_t6 != 0) {
        temp_t9 = temp_v1 & 0xFFFF0000;
        (*(s32 *)((u8 *)arg0 + 0x14)) = temp_t9;
        (*(s16 *)((u8 *)arg0 + 0x38)) = 0x1E;
        (*(s32 *)((u8 *)arg0 + 0x14)) = (s32) (temp_t9 | ((temp_t6 - 1) & 0xFFFF));
        return;
    }
    temp_a2 = (*(u8 *)((u8 *)arg0 + 0x3F));
    temp_t2 = (temp_v1 >> 0x10) & 0xFFFF;
    if (temp_t2 < (s32) temp_a2) {
        (*(u8 *)((u8 *)arg0 + 0x3F)) = (u8) (temp_a2 - temp_t2);
        (*(s16 *)((u8 *)arg0 + 0x38)) = 0x1E;
        return;
    }
    (*(s16 *)((u8 *)arg0 + 0x38)) = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168B44.s")
#endif
void func_15168BAC(u8 *arg0) {
    u8 idx = arg0[0xE4];
    if (idx != 0) {
        D_8008CDC0[idx]();
    }
}
void func_15168BE4(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *temp_v0;

    if (((s32 *)arg0)[0x40 / 4] != 0) {
        temp_v0 = func_15167A68(0x10, arg2, 0xF0, 1, arg1, 1);
        if (temp_v0 != NULL) {
            bcopy(arg0, temp_v0 + 0x90, 0x60);
        }
    }
}
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
extern s16 D_800DD5F0;
extern s16 D_800DD5F2;
extern s16 D_800DD5F4;
extern s16 D_800DD5F6;

Gfx *func_15168C4C(Gfx *gfx, u8 *arg1, s32 arg2) {
    s32 pad; // fakematch: frame
    s32 mode;
    u8 flag;
    s32 pad2; // fakematch: frame

    func_15043D90(&((Mtx *)(arg1 + 0x10))[D_800BE9C0], *(f32 *)(arg1 + 0x9C), *(f32 *)(arg1 + 0xA0), *(f32 *)(arg1 + 0xA4), *(f32 *)(arg1 + 0xC0), *(f32 *)(arg1 + 0xC4), *(f32 *)(arg1 + 0xC8), *(f32 *)(arg1 + 0x90), *(f32 *)(arg1 + 0x94), *(f32 *)(arg1 + 0x98));
    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, arg1[0xE5]);
    D_800DD5F6 = arg1[0xE5];
    D_800DD5F0 = D_800DD5F2 = D_800DD5F4 = 0;
    gDPSetEnvColor(gfx++, 0, 0, 0, 0);
    gDPSetTileSize(gfx++, 0, 2, arg1[0xE6], 0x7E, 0xFE);
    switch (arg1[0xEC]) {
    case 1:
        mode = 0x552230;
        break;
    case 2:
        mode = 0x504A50;
        break;
    }
    flag = 0;
    gfx = func_15142FBC(gfx, 0x8ACA0, mode, &flag);
    if (arg1[0xED] == 1) {
        gDPSetCombineLERP(gfx++, TEXEL0, 0, SHADE, 0, PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, PRIMITIVE, 0, SHADE, 0);
    }
    gSPMatrix(gfx++, &((Mtx *)(arg1 + 0x10))[D_800BE9C0], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, *(Gfx **)(arg1 + 0xD0));
    return gfx;
}
void func_15168E34(s32 *arg0, s32 arg1) {
    s32 temp_v0 = *arg0;
    if (!(temp_v0 & 0x0F000000)) {
        *arg0 = temp_v0 + arg1;
    }
}
#ifdef NON_MATCHING
void func_15168E54(s8 *arg0, s32 arg1) {
    s32 var_s0;
    s8 *var_v1;
    s8 var_v0;

    var_s0 = 0;
    var_v1 = arg0;
    if (*arg0 != -0x21) {
        var_v0 = *arg0;
        do {
            if ((var_v0 == 1) || ((var_v0 == -0x24) && ((*(u8 *)((u8 *)var_v1 + 3)) == 0xE))) {
                func_15168E34(var_v1 + 4, arg1);
            }
            var_s0 += 1;
            var_v1 = (var_s0 * 8) + arg0;
            var_v0 = *var_v1;
        } while (var_v0 != -0x21);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168E54.s")
#endif
// NON-MATCHING: first cmd load is CSE'd in mine
// void func_15168E54(struct_eu_gfxcmd *arg0, s32 arg1) {
//     s32 i = 0;
//     struct_eu_gfxcmd *gfx = arg0;
//     s32 cmd = gfx->cmd;
//
//     while (cmd != -0x21) {
//         cmd = gfx->cmd;
//         if (cmd == 1 || (cmd == -0x24 && gfx->b3 == 0xE)) {
//             func_15168E34(&gfx->w1, arg1);
//         }
//         i++;
//         gfx = &arg0[i];
//         cmd = gfx->cmd;
//     }
// }

void func_15168F08(struct_eu_gfxcmd *arg0, s32 arg1) {
    s32 i = 0;
    struct_eu_gfxcmd *gfx = arg0;

    while (gfx->cmd != -0x21) {
        i++;
        if (gfx->cmd == 1 || (gfx->cmd == -0x24 && gfx->b3 == 0xE)) {
            gfx->w1 &= 0xFFFFFF;
            gfx->w1 += arg1;
        }
        gfx = &arg0[i];
        goto next; // fakematch: label at the end of the loop body
    next:;
    }
}

void func_15168F84(s32 arg0, s32 *arg1, s32 *arg2) {
    if (arg0 == 0) {
        *arg1 = 1;
        *arg2 = 0x41;
    } else if (arg0 == 1) {
        *arg1 = 0x42;
        *arg2 = 0x4F;
    } else if (arg0 == 2) {
        *arg1 = 0x50;
        *arg2 = 0x58;
    } else if (arg0 == 3) {
        *arg1 = 0x59;
        *arg2 = 0x5C;
    } else if (arg0 == 5) {
        *arg1 = 0x61;
        *arg2 = 0x63;
    } else if (arg0 == 6) {
        *arg1 = 0x64;
        *arg2 = 0x65;
    } else {
        *arg1 = 0x5D;
        *arg2 = 0x60;
    }
}
void func_15169040(s32 arg0, u8 arg1) {
    func_15169070(0, 0x68, arg0, arg1);
}
void func_1516968C(struct102 *arg0, u8 *arg1, u8 arg2);
void func_15143D18(s32 *, s32 *, s32, s32);
void func_15169070(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 j;
    s32 i;

    func_15143D18(&arg0, &arg1, 2, 0x68);
    for (j = arg0; j < arg1; j++) {
        struct_eu_node *node;

        for (i = 0; i < 2; i++) {
            if (D_8008B848[j].fn != NULL) {
                node = D_800DD280[i][j];
                D_800DD5C0++;
                while (node != NULL) {
                    D_800DD5C8[D_800DD5C0] = node->next;
                    func_1516968C((struct102 *)node, (u8 *)arg2, arg3);
                    D_8008B848[j].fn(node, arg2, arg3);
                    node = D_800DD5C8[D_800DD5C0];
                }
                D_800DD5C0--;
            } else {
                node = D_800DD280[i][j];
                D_800DD5C0++;
                while (node != NULL) {
                    D_800DD5C8[D_800DD5C0] = node->next;
                    func_1516968C((struct102 *)node, (u8 *)arg2, arg3);
                    node = D_800DD5C8[D_800DD5C0];
                }
                D_800DD5C0--;
            }
        }
    }
}
#ifdef NON_MATCHING
/* P136 */
/*
 * node_lists_update_types: for each of the n type ids in types[] (arg0), walks that type's node lists in both rows of
 * D_800DD280 and calls func_1516968C(node, arg2, arg3) on every node, then the type's D_8008B848 handler (+0x1C)
 * when it has one. The next node is kept in D_800DD5C8[++D_800DD5C0] (as func_15169070) so a call may unlink or
 * free the current node or the saved next one.
 */
void func_15169260(void *arg0, s32 n, s32 arg2, u8 arg3) {
    s32 *types = arg0;
    struct_eu_node *node;
    s32 k;
    s32 i;

    for (k = 0; k < n; k++, types++) {
        for (i = 0; i < 2; i++) {
            if (D_8008B848[*types].fn != NULL) {
                node = D_800DD280[i][*types];
                D_800DD5C0++;
                while (node != NULL) {
                    D_800DD5C8[D_800DD5C0] = node->next;
                    func_1516968C((struct102 *) node, (u8 *) arg2, arg3);
                    D_8008B848[*types].fn(node, arg2, arg3);
                    node = D_800DD5C8[D_800DD5C0];
                }
                D_800DD5C0--;
            } else {
                node = D_800DD280[i][*types];
                D_800DD5C0++;
                while (node != NULL) {
                    D_800DD5C8[D_800DD5C0] = node->next;
                    func_1516968C((struct102 *) node, (u8 *) arg2, arg3);
                    node = D_800DD5C8[D_800DD5C0];
                }
                D_800DD5C0--;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169260.s")
#endif
void func_1516968C(struct102 *arg0, u8 *arg1, u8 arg2);
void func_1516944C(s32 j, s32 arg1, u8 arg2) {
    s32 i;
    struct_eu_node *node;

    if (j >= 0x68) {
        j = 0x67;
    }
    for (i = 0; i < 2; i++) {
        if (D_8008B848[j].fn != NULL) {
            node = D_800DD280[i][j];
            D_800DD5C0++;
            while (node != NULL) {
                D_800DD5C8[D_800DD5C0] = node->next;
                func_1516968C((struct102 *)node, (u8 *)arg1, arg2);
                D_8008B848[j].fn(node, arg1, arg2);
                node = D_800DD5C8[D_800DD5C0];
            }
            D_800DD5C0--;
        } else {
            node = D_800DD280[i][j];
            D_800DD5C0++;
            while (node != NULL) {
                D_800DD5C8[D_800DD5C0] = node->next;
                func_1516968C((struct102 *)node, (u8 *)arg1, arg2);
                node = D_800DD5C8[D_800DD5C0];
            }
            D_800DD5C0--;
        }
    }
}
void func_151695F0(u8 *arg0, u8 arg1) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_15169040(&tmp, arg1);
}
void func_1516962C(s32 arg0, u8 *arg1, u8 arg2) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg1;
    tmp.unk4 = arg1[0x3B];
    func_1516944C(arg0, &tmp, arg2);
}
s32 func_15169668(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800D31CB = 1;
    return arg0;
}
void func_1516968C(struct102 *arg0, u8 *arg1, u8 arg2) {
    if ((arg2 == 15 || arg2 == 16) && *arg1 == ((u8 *)arg0)[0xC]) {
        func_1516972C(arg0);
    }
}
void func_151696DC(struct_eu_node *arg0) {
    s8 i;

    for (i = 0; i < D_800DD5C0; i++) {
        if (arg0 == D_800DD5C8[i]) {
            D_800DD5C8[i] = arg0->next;
        }
    }
}

void func_1516972C(struct102 *arg0) {
    void (*func)(struct102 *arg0);
    func_151696DC(arg0);

    if (arg0->unk0 >= 2) {
        func = D_8008B4D0[arg0->unk0].unk0;
        if (func != NULL) {
            func(arg0);
            return;
        }
        func_15169804(arg0);
    }
}

void func_1516979C(struct102 *arg0) {
    void (*func)(struct102 *arg0);

    func_151696DC(arg0);
    func = D_8008B4D4[arg0->unk0].unk0;
    if (func != NULL) {
        func(arg0);
        return;
    }
    func_15169824(arg0);
}

void func_15169804(struct102 *arg0) {
    func_15168B10(arg0, 1);
}

void func_15169824(struct102 *arg0) {
    func_15168A9C(arg0);
    func_10004074(arg0);
}

s32 func_15169850(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_v1;

    if (arg1 == 0) {
        if ((*(s32 *)(arg0 + 0) == *(s32 *)arg2) || (*(u8 *)(arg0 + 4) == *(u8 *)arg3)) {
            func_1516972C((struct102 *)arg4);
        }
    } else if (arg1 == 0x2D) {
        temp_v1 = *(s32 *)(arg0 + 0);
        if (temp_v1 == *(s32 *)arg2) {
            *(s32 *)arg2 = *(s32 *)(arg0 + 4);
            *(u8 *)arg3 = *(u8 *)(arg0 + 9);
            return;
        }
        if (*(s32 *)(arg0 + 4) == *(s32 *)arg2) {
            *(s32 *)arg2 = temp_v1;
            *(u8 *)arg3 = *(u8 *)(arg0 + 8);
        }
    }
}
// NON-MATCHING: regalloc (v0/v1 swapped)
// void func_15169850(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4) {
//     s32 *a = (s32 *)arg0;
//     s32 *b = (s32 *)arg2;
//     u8 *c = (u8 *)arg3;
//
//     if (arg1 == 0) {
//         if (a[0] == *b || ((u8 *)a)[4] == *c) {
//             func_1516972C((struct102 *)arg4);
//         }
//     } else if (arg1 == 0x2D) {
//         if (a[0] == *b) {
//             *b = a[1];
//             *c = ((u8 *)a)[9];
//         } else if (*b == a[1]) {
//             *b = a[0];
//             *c = ((u8 *)a)[8];
//         }
//     }
// }
