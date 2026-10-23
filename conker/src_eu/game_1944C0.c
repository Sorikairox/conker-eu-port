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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168118.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516865C.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169260.s")
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
