#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 *func_1513445C(u8 *arg0, u16 arg1, u8 arg2, s32 arg3);
#endif
// hoisted forward declaration(s) for func_151341C8, func_15134290
s32 func_15134108(u8 *, f32, f32, f32, f32, s32);


extern s32 (*D_80089C50[])(u8 *);
extern s32 (*D_80089CB4[])(u8 *);
extern void (*D_80089D1C[])(u8 *);
extern s32 (*D_80089D28[])(u8 *);
s32 func_1514672C(u8 *);

void func_15132740(u8 *arg0) {
    s32 pad;
    u8 done = 0;
    s16 t;

    *(s32 *)(arg0 + 0x60) &= ~0x200000;
    if ((*(s32 *)(arg0 + 0x60) & 0x10) && (arg0[0x148] & 0x18)) {
        if (!D_80089D28[arg0[0x77]](arg0)) {
            done = 1;
        }
    } else if (arg0[0x71] != 0) {
        if (!D_80089C50[arg0[0x71]](arg0)) {
            done = 1;
        }
    }
    if (arg0[0x72] != 0 && !done) {
        if (!D_80089CB4[arg0[0x72]](arg0)) {
            done = 1;
        }
    }
    if ((*(s32 *)(arg0 + 0x60) & 0x80) && !done) {
        *(s16 *)(arg0 + 0x64) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x64) < 0) {
            done = 1;
        }
    }
    if ((*(s32 *)(arg0 + 0x60) & 0x2000) && !done) {
        t = *(s16 *)(arg0 + 0x64);
        if (t < *(s16 *)(arg0 + 0x82)) {
            if ((t * *(s16 *)(arg0 + 0x84)) < arg0[0x70]) {
                if (!(t * *(s16 *)(arg0 + 0x84))) { // fakematch: empty if fixes the multu operand order
                }
                arg0[0x70] = (t * *(s16 *)(arg0 + 0x84));
            }
        }
    }
    if (!done && !(*(s32 *)(arg0 + 0x60) & 0x80000)) {
        done = !func_1514672C(arg0 + 0x38);
    }
    if (done) {
        if (arg0[0x76] != 0) {
            D_80089D1C[arg0[0x76]](arg0);
        }
        node_destroy((struct102 *)arg0);
    }
}

void func_1513291C(u8 *arg0) {
    u8 var_v0 = (*(s32 *)(arg0 + 0x60) & 0x100) ? arg0[0x68] : 0;

    D_80089D50[var_v0](arg0);
}

void func_15132968(u8 *arg0) {
    u8 var_v0 = (*(s32 *)(arg0 + 0x60) & 0x100) ? arg0[0x68] : 0;

    D_80089D74[var_v0](arg0);
}

void func_15132B38(u8 *arg0);
s32 texture_id_list_release(s32, s32 *, u16 *);
extern s32 D_800DCA70[];
typedef struct Node29B4 {
    s32 *data;
    struct Node29B4 *next;
    struct Node29B4 *prev;
    u8 pad0C[2];
    u8 flag;
} Node29B4;
typedef struct {
    u8 pad0[0x66];
    u16 idx;
    u8 pad68[0x24];
    Node29B4 *node;
} Obj29B4;
void func_151329B4(Obj29B4 *arg0) {
    D_800DC63C--;
    ((s16 *)D_800DC468)[arg0->idx]--;
    if (((s16 *)D_800DC468)[arg0->idx] == 0) {
        if (arg0->node->flag != 0) {
            D_800DC468[arg0->idx] = 1;
        } else {
            texture_id_list_release(D_800DCA70[arg0->idx], &D_800DC63C, D_800DC468);
            if (arg0->node->prev == NULL) {
                D_800DC460 = (s32)arg0->node->next;
                if (D_800DC460 != 0) {
                    ((Node29B4 *)D_800DC460)->prev = NULL;
                } else {
                    D_800DC464 = 0;
                }
            } else {
                arg0->node->prev->next = arg0->node->next;
                if (arg0->node->next != NULL) {
                    arg0->node->next->prev = arg0->node->prev;
                } else {
                    D_800DC464 = (s32)arg0->node->prev;
                }
            }
            func_100043B4(arg0->node->data, 4);
            func_100043B4((s32 *)arg0->node, 4);
        }
    }
    func_15132B38((u8 *)arg0);
}

void func_15132AE0(struct102 * arg0) {
    func_151329B4(arg0);
    node_retire(arg0);
}

void func_15132B0C(struct102 * arg0) {
    func_151329B4(arg0);
    node_unlink_free(arg0);
}

void func_15132B38(u8 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (((s32 *)(arg0 + 0x154))[i]) {
            func_100043B4(((s32 *)(arg0 + 0x154))[i], 4);
        }
    }
    if (*(s32 *)(arg0 + 0x164) != 0) {
        func_100043B4(*(s32 *)(arg0 + 0x164), 4);
    }
}

#ifdef NON_MATCHING
/* one shared model per particle model id (D_800DC468 counts the users, D_800DC460 / D_800DC464 = list head / tail) */
typedef struct ParticleModelRef {
    s32 *model;                      /* loaded model file (asset_load_with_subfiles) */
    struct ParticleModelRef *next;
    struct ParticleModelRef *prev;
    u16 modelId;
    u8 keep;                         /* 1: not freed when the last user dies (func_151329B4) */
} ParticleModelRef;
/* D_800DC460 / D_800DC464: list head / tail (ParticleModelRef *), D_800DC468: s16 users per model id,
   D_800DC63C: live particles */

void func_10004074(void *);
u8 *func_1515D9F0(s32);
void *func_1515D9B0(void);
s32 func_15133C18(s32 modelId, ParticleModelRef *ref, void *particle);

// particle_spawn: creates a particle object from a 0x7C-byte request (model id at +0x56, flags at +0x50); loads
// the request's model on first use (shared, reference counted per model id), copies the request to +0x10, sets
// the spin / scale state, the optional 9-word bounds (else "no bounds": y min -10000), and allocates nTrails
// trail buffers (one per player). Returns the particle or 0 (more than 300 alive, out of memory, model missing).
u8 *func_15132BBC(u8 *req, s32 nTrails, s32 arg2, s32 *bounds, s32 extraSize, u8 arg5, s32 owner) {
    u8 *p;
    ParticleModelRef *ref;
    s16 *users;
    s32 kind;
    s32 heap;
    s32 n;
    s32 i;
    u16 id;
    f32 x, y, z;

    if (D_800DC63C > 300) {
        return 0;
    }
    kind = (*(s32 *)(req + 0x50) & 0x4000) ? 0x48 : 0x19;
    heap = (*(s32 *)(req + 0x50) & 0x400000) ? 2 : 1;
    p = node_alloc(kind, owner, extraSize + 0x170, 1, arg5, heap);
    if (p == NULL) {
        return 0;
    }
    id = *(u16 *)(req + 0x56);
    users = &((s16 *)D_800DC468)[id];
    if (*users == 0) {
        ref = (ParticleModelRef *)allocate_memory(0x10, 1, 2, (*(s32 *)(req + 0x50) & 0x400000) ? 2 : 1);
        if (ref == NULL) {
            node_list_unlink((struct_eu_node *)p);
            func_10004074(p);
            return 0;
        }
        if (!func_15133C18(*(u16 *)(req + 0x56), ref, p)) {
            node_list_unlink((struct_eu_node *)p);
            func_10004074(p);
            func_10004074(ref);
            return 0;
        }
        /* push at the head of the model list */
        ref->next = (ParticleModelRef *)D_800DC460;
        if (D_800DC460 != 0) {
            ((ParticleModelRef *)D_800DC460)->prev = ref;
        } else {
            D_800DC464 = (s32)ref;
        }
        D_800DC460 = (s32)ref;
        ref->prev = NULL;
        ref->modelId = *(u16 *)(req + 0x56);
        if ((*(s32 *)(req + 0x50) & 0x100000) && D_800BE9F0 != 0x3B && D_800BE9F0 != 6 && D_800BE9F0 != 0x13 &&
            D_800BE616 == 0 && D_800BE9F0 != 2) {
            ref->keep = 1;
        } else {
            ref->keep = 0;
        }
        users = &((s16 *)D_800DC468)[*(u16 *)(req + 0x56)];
    } else {
        /* find the loaded model (at most 100 entries) */
        ref = (ParticleModelRef *)D_800DC460;
        n = 100;
        while (ref->modelId != id) {
            n--;
            ref = ref->next;
            if (n <= 0) {
                break;
            }
        }
        if (n <= 0) {
            node_list_unlink((struct_eu_node *)p);
            func_10004074(p);
            return 0;
        }
    }
    (*users)++;
    *(ParticleModelRef **)(p + 0x8C) = ref;
    memcpy(p + 0x10, req, 0x7C);
    p[0x149] = 0;
    *(f32 *)(p + 0x134) = 0.0f;
    *(f32 *)(p + 0x138) = 0.0f;
    *(f32 *)(p + 0x13C) = 0.0f;
    x = *(f32 *)(req + 0x34);
    y = *(f32 *)(req + 0x38);
    z = *(f32 *)(req + 0x3C);
    p[0x148] = 0;
    *(f32 *)(p + 0x144) = 1.0f;
    *(f32 *)(p + 0x140) = sqrtf(x * x + y * y + z * z);
    if (bounds != NULL) {
        for (i = 0; i < 9; i++) {
            ((s32 *)(p + 0x110))[i] = bounds[i];
        }
    } else {
        *(s32 *)(p + 0x130) = 0;
        p[0x12D] = 0;
        p[0x12C] = 0;
        *(s32 *)(p + 0x128) = 0;
        *(f32 *)(p + 0x110) = -10000.0f; /* D_800A3C48 */
    }
    D_800DC63C++;
    p[0x150] = 0;
    *(s32 *)(p + 0x14C) = nTrails;
    *(s32 *)(p + 0x168) = arg2;
    for (i = 0; i < 4; i++) {
        ((s32 *)(p + 0x154))[i] = 0;
    }
    *(s32 *)(p + 0x164) = 0;
    if (nTrails != 0) {
        for (i = 0; i <= D_80082FA0; i++) {
            ((u8 **)(p + 0x154))[i] = func_1515D9F0(nTrails);
        }
        *(void **)(p + 0x164) = func_1515D9B0();
    }
    *(s32 *)(p + 0x60) &= ~0x200000;
    return p;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15132BBC.s")
#endif

#ifdef NON_MATCHING
/* the asm passes func_15132BBC's v0 through, and func_150BCBBC tests it */
s32 func_15132FBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    return (s32)func_15132BBC((u8 *)arg0, arg1, arg2, NULL, arg3, arg4, arg5);
}
#else
void func_15132FBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_15132BBC(arg0, arg1, arg2, 0, arg3, arg4, arg5);
}
#endif

u8 func_151464B8(s16 *arg0);
typedef struct {
    u8 pad0[0x60];
    u32 flags;
    u8 pad64[8];
    s16 *unk6C;
    u8 pad70[8];
    u8 unk78;
    u8 pad79[0x17];
    Mtx mtx[2];
} Unk15132FF8;
/* P241: every entry (func_15133A80, func_150BA1F4, func_15133CD0, func_150C7C3C, func_151B98C0, func_15134004) takes
 * the object as its second argument: the asm leaves it in a1 at the jalr (`move a1, a0` on entry). The table was
 * declared with one parameter, so the port passed nothing there (wasm: signature mismatch). */
extern s32 (*D_80089D2C[])(Mtx *, Unk15132FF8 *);

void func_15132FF8(Unk15132FF8 *arg0) {
    s32 r;

    arg0->flags &= ~0x200000;
    if (arg0->flags & 0x20000) {
        return;
    }
    if ((arg0->flags & 0x400) && arg0->unk6C != NULL && func_151464B8(arg0->unk6C) != 0) {
        return;
    }
    if (arg0->flags & 0x80000) {
        arg0->flags |= 0x200000;
        return;
    }
    r = D_80089D2C[arg0->unk78](&arg0->mtx[D_800BE9C0], arg0);
    if (r == -1) {
        node_destroy((struct102 *)arg0);
        return;
    }
    if (r == 0) {
        arg0->flags &= ~0x40000;
    } else {
        arg0->flags |= 0x240000;
    }
}

#ifdef NON_MATCHING
Gfx *func_15142B7C(Gfx *gfx, s32 set, s32 clear);
Gfx *func_15142C10(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5);
u8 *func_151462C8(u8 *, u8 *, u8, s32, s32, s32, u8 *, s32, s32);
extern s32 D_80083AD0;
extern s32 D_80083C50;
extern s32 D_80089D44;

u8 *func_151330F0(u8 *arg0, u8 *arg1, s16 arg2) {
    struct {
        s8 u6B;
    } sp;
    s32 temp_a0;
    s32 temp_s1_2;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a3;
    s32 var_t0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s8 temp_v0;
    u8 *temp_s1;
    u8 *var_s1;
    u8 *var_s1_2;

    temp_v1 = (*(s32 *)((u8 *)arg1 + 0x60));
    if (!(temp_v1 & 0x200000)) {
        return arg0;
    }
    if (temp_v1 & 0x20000) {
        return arg0;
    }
    if (!(temp_v1 & 0x40000)) {
        return arg0;
    }
    sp.u6B = 1;
    if ((s32) (*(u8 *)((u8 *)arg1 + 0x70)) < 0xFF) {
        (*(s32 *)((u8 *)arg0 + 0)) = 0xDB060020;
        (*(s32 **)((u8 *)arg0 + 4)) = &D_80083AD0;
        var_s1 = arg0 + 8;
    } else {
        (*(s32 *)((u8 *)arg0 + 0)) = 0xDB060020;
        (*(s32 **)((u8 *)arg0 + 4)) = &D_80083C50;
        var_s1 = arg0 + 8;
    }
    if ((*(s32 *)((u8 *)arg1 + 0x60)) & 0x10000) {
        temp_v0 = (*(s8 *)((u8 *)arg1 + 0x79));
        if (temp_v0 != -1) {
            var_s1 = (*(s32 (**)())((u8 *)&D_80089D44 + (temp_v0 * 4)))(var_s1, arg1, arg2);
        }
    }
    temp_v1_2 = (*(s32 *)((u8 *)arg1 + 0x60));
    temp_s1_2 = func_15142C10(var_s1, 0, 0, 0, (s32) (*(u8 *)((u8 *)arg1 + 0x70)), &sp.u6B);
    temp_a0 = temp_v1_2 & 0x800;
    temp_v0_2 = temp_v1_2 & 0x1000;
    if (temp_a0 != 0) {
        var_t0 = 0x20000;
    } else {
        var_t0 = 0;
    }
    var_v1 = 0;
    if (temp_v0_2 != 0) {
        var_v1 = 0x400000;
    }
    if (temp_a0 != 0) {
        var_a3 = 0;
    } else {
        var_a3 = 0x20000;
    }
    if (temp_v0_2 != 0) {
        var_v0 = 0;
    } else {
        var_v0 = 0x400000;
    }
    temp_v1_3 = (*(s32 *)((u8 *)arg1 + 0x60));
    var_s1_2 = func_15142B7C(temp_s1_2, var_v1 | var_t0 | 5 | 0x200000, var_v0 | var_a3 | 0x600 | 0x10000 | 0x40000 | 0x80000);
    if (temp_v1_3 & 0x800) {
        if (temp_v1_3 & 0x1000) {
            var_v0_2 = 1;
        } else {
            var_v0_2 = 0;
        }
        var_s1_2 = func_151462C8(var_s1_2, arg1 + 0x14C, (*(u8 *)((u8 *)arg1 + 0x7A)), (*(s32 *)((u8 *)arg1 + 0x7C)), (s32) (*(u8 *)((u8 *)arg1 + 0x80)), (s32) arg2, arg1 + 0x38, var_v0_2, (*(s32 *)((u8 *)arg1 + 0x128)));
    }
    (*(s32 *)((u8 *)var_s1_2 + 0)) = 0xDA380003;
    temp_s1 = var_s1_2 + 8;
    (*(u8 **)((u8 *)var_s1_2 + 4)) = (u8 *) (arg1 + (D_800BE9C0 << 6) + 0x90);
    (*(s32 *)((u8 *)temp_s1 + 0)) = 0xDE000000;
    (*(s32 *)((u8 *)temp_s1 + 4)) = (s32) **(*(s32 ***)((u8 *)arg1 + 0x8C));
    return temp_s1 + 8;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_151330F0.s")
#endif
#ifdef NON_MATCHING
typedef struct {
    s16 v[9];
} Surf334C; /* floor / wall surface record (+0x114 of a particle) */
/* func_15044670 wall-probe request (0x1A0 bytes on the stack; only the fields set here are named) */
typedef struct {
    /* 0x000 */ s32 kind;
    /* 0x004 */ u8 pad4[0x10];
    /* 0x014 */ f32 pos[3];
    /* 0x020 */ u8 pad20[8];
    /* 0x028 */ f32 u28;
    /* 0x02C */ u8 pad2C[0xB8];
    /* 0x0E4 */ s16 uE4;
    /* 0x0E6 */ s16 uE6;
    /* 0x0E8 */ u8 padE8[0x10];
    /* 0x0F8 */ s32 uF8;
    /* 0x0FC */ u8 padFC[0x50];
    /* 0x14C */ f32 u14C;
    /* 0x150 */ f32 u150;
    /* 0x154 */ u8 pad154[0x2C];
    /* 0x180 */ f32 floor;
    /* 0x184 */ u8 pad184[4];
    /* 0x188 */ s32 u188;
    /* 0x18C */ Surf334C surf;
    /* 0x19E */ u8 pad19E[2];
} WallProbe334C;
s32 func_15046F70(f32 *, s32, f32, u8 *);
s32 func_15044670(f32, f32, s32, u8 *, s32, s32);
extern s32 (*D_80089CD4[])(u8 *, f32, f32, f32, f32, u8 *); /* landing handlers by +0x73 */
/* floor-hit handlers by +0x74 and wall-hit handlers by +0x75 (entry 0 unused) */
extern s32 (*D_80089D10[])(u8 *, f32, f32, f32, f32);
extern s32 (*D_80089D14[])(u8 *, WallProbe334C *, f32, f32, f32);

// particle_collide_update: integrates the particle's motion by D_800BE9A4 (+0x60 flags: 8 = gravity +0x5C on the y
// velocity, 0x20 = position +0x38 += velocity +0x44, 0x40 = rotation +0x20 += spin +0x50) and, when any of the
// collision bits 7 is set, checks the move from the old position: a floor probe (func_15046F70 from the old height
// down to the new one less the +0x10 offset; floor height +0x110, info +0x114). On a floor of type (+0x12D) 1, or 2
// with +0x12C bit 0: flag 1 of +0x148, the speed (+0x140) / its inverse (+0x144, flag 8) when +0x60 bit 0x10 and
// faster than 1, the landing handler D_80089CD4[+0x73] and, with bit 0x10, the position saved at +0x134; type 3:
// flag 2 and the D_80089D10[+0x74] handler. With bit 4 a wall probe (func_15044670, request kind 4 from the old to
// the new position): flag 4, speed and yaw (+0x14A, func_150484A0 of the probe's hit point, 256 steps) with 0x10,
// the D_80089D14[+0x75] handler and the saved position. A handler returning 0 ends the particle: returns 0, else 1.
s32 func_1513334C(u8 *p) {
    WallProbe334C req;
    f32 probe[3];
    f32 old[3];
    f32 len;
    u8 type;

    if (*(s32 *) (p + 0x60) & 7) {
        memcpy((u8 *) old, p + 0x38, 12);
    }
    if (*(s32 *) (p + 0x60) & 8) {
        *(f32 *) (p + 0x48) += *(f32 *) (p + 0x5C) * D_800BE9A4;
    }
    if (*(s32 *) (p + 0x60) & 0x20) {
        *(f32 *) (p + 0x38) += *(f32 *) (p + 0x44) * D_800BE9A4;
        *(f32 *) (p + 0x3C) += *(f32 *) (p + 0x48) * D_800BE9A4;
        *(f32 *) (p + 0x40) += *(f32 *) (p + 0x4C) * D_800BE9A4;
    }
    if (*(s32 *) (p + 0x60) & 0x40) {
        *(f32 *) (p + 0x20) += *(f32 *) (p + 0x50) * D_800BE9A4;
        *(f32 *) (p + 0x24) += *(f32 *) (p + 0x54) * D_800BE9A4;
        *(f32 *) (p + 0x28) += *(f32 *) (p + 0x58) * D_800BE9A4;
    }
    if (!(*(s32 *) (p + 0x60) & 7)) {
        return 1;
    }

    probe[0] = *(f32 *) (p + 0x38);
    probe[1] = old[1];
    probe[2] = *(f32 *) (p + 0x40);
    if (func_15046F70(probe, 0, *(f32 *) (p + 0x3C) - *(f32 *) (p + 0x10), p + 0x110) != 0) {
        type = p[0x12D];
        if (type == 1 || (type == 2 && (p[0x12C] & 1))) {
            p[0x148] |= 1;
            if (*(s32 *) (p + 0x60) & 0x10) {
                len = sqrtf(*(f32 *) (p + 0x44) * *(f32 *) (p + 0x44) + *(f32 *) (p + 0x48) * *(f32 *) (p + 0x48)
                            + *(f32 *) (p + 0x4C) * *(f32 *) (p + 0x4C));
                if (1.0f < len) {
                    p[0x148] |= 8;
                    *(f32 *) (p + 0x140) = len;
                    *(f32 *) (p + 0x144) = 1.0f / len;
                }
            }
            if (p[0x73] != 0
                && !D_80089CD4[p[0x73]](p, old[0], old[1], old[2], *(f32 *) (p + 0x110), p + 0x114)) {
                return 0;
            }
            if (*(s32 *) (p + 0x60) & 0x10) {
                memcpy(p + 0x134, p + 0x38, 12);
            }
        }
        if (p[0x12D] == 3) {
            p[0x148] |= 2;
            if (p[0x74] != 0 && !D_80089D10[p[0x74]](p, old[0], old[1], old[2], *(f32 *) (p + 0x110))) {
                return 0;
            }
        }
    }

    if (!(*(s32 *) (p + 0x60) & 4)) {
        return 1;
    }
    req.kind = 4;
    req.pos[0] = *(f32 *) (p + 0x38);
    req.pos[1] = *(f32 *) (p + 0x3C);
    req.pos[2] = *(f32 *) (p + 0x40);
    req.u188 = 0;
    req.surf = *(Surf334C *) (p + 0x114);
    req.u28 = 1.0f;
    req.u14C = 1.0f;
    req.u150 = 1.0f;
    req.uE4 = (s32) *(f32 *) (p + 0x10);
    req.uE6 = (s32) *(f32 *) (p + 0x10);
    if (p[0x12C] & 2) {
        req.floor = *(f32 *) (p + 0x110);
    } else {
        req.floor = -10000.0f;
    }
    req.uF8 = 0;
    if (func_15044670(old[0], old[1], *(s32 *) &old[2], (u8 *) &req, 0, 0) == 0) {
        return 1;
    }
    p[0x148] |= 4;
    if (*(s32 *) (p + 0x60) & 0x10) {
        len = sqrtf(*(f32 *) (p + 0x44) * *(f32 *) (p + 0x44) + *(f32 *) (p + 0x48) * *(f32 *) (p + 0x48)
                    + *(f32 *) (p + 0x4C) * *(f32 *) (p + 0x4C));
        if (1.0f < len) {
            p[0x148] |= 0x10;
            *(f32 *) (p + 0x140) = len;
            *(f32 *) (p + 0x144) = 1.0f / len;
            p[0x14A] = (s32) (func_150484A0(req.pos[0] - *(f32 *) (p + 0x38), req.pos[2] - *(f32 *) (p + 0x40)) * 40.743664f);
        }
    }
    if (p[0x75] != 0 && !D_80089D14[p[0x75]](p, &req, old[0], old[1], old[2])) {
        return 0;
    }
    if (*(s32 *) (p + 0x60) & 0x10) {
        memcpy(p + 0x134, p + 0x38, 12);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_1513334C.s")
#endif

s32 func_1513384C(u8 *arg0)
{
  f32 cs;
  *((f32 *) (arg0 + 0x2C)) = 1.0f;
  *((f32 *) (arg0 + 0x30)) = 1.0f;
  *((f32 *) (arg0 + 0x34)) = 1.0f;
  if ((*((s32 *) (arg0 + 0x60))) & 0x40)
  {
    *((f32 *) (arg0 + 0x20)) += (*((f32 *) (arg0 + 0x50))) * D_800BE9A4;
    *((f32 *) (arg0 + 0x24)) += (*((f32 *) (arg0 + 0x54))) * D_800BE9A4;
    *((f32 *) (arg0 + 0x28)) += (*((f32 *) (arg0 + 0x58))) * D_800BE9A4;
  }
  arg0[0x149] += ((s32) (576.0f * (*((f32 *) (arg0 + 0x144))))) * D_800BE9E4;
  if (arg0[0x149] < 0x80)
  {
    f32 s;
    s = angle_byte_cos(arg0[0x149] - 0x40);
    s = ((1.0f - (*((f32 *) (arg0 + 0x144)))) * (1.0f - (*((f32 *) (arg0 + 0x14))))) * s;
    if (arg0[0x148] & 8)
    {
      *((f32 *) (arg0 + 0x2C)) *= 1.0f + s;
      *((f32 *) (arg0 + 0x30)) *= 1.0f - s;
      *((f32 *) (arg0 + 0x34)) *= s + 1.0f;
      *((f32 *) (arg0 + 0x3C)) = (*((f32 *) (arg0 + 0x138))) - ((*((f32 *) (arg0 + 0x10))) * (0, s)); // fakematch: comma puts s in fs
    }
    if (arg0[0x148] & 0x10)
    {
      f32 sn;
      f32 d;
      sn = angle_byte_cos(((s8) arg0[0x14A]) - 0x40);
      cs = angle_byte_cos((u8) arg0[0x14A]);
      *((f32 *) (arg0 + 0x2C)) *= 1.0f - s;
      *((f32 *) (arg0 + 0x30)) *= 1.0f + s;
      *((f32 *) (arg0 + 0x34)) *= 1.0f - s;
      d = (*((f32 *) (arg0 + 0x10))) * (0, s); // fakematch: comma puts s in fs
      *((f32 *) (arg0 + 0x38)) = (*((f32 *) (arg0 + 0x134))) - (d * cs);
      *((f32 *) (arg0 + 0x40)) = (*((f32 *) (arg0 + 0x13C))) + (d * sn);
    }
  }
  else
  {
    memcpy(arg0 + 0x38, arg0 + 0x134, 0xC);
    arg0[0x149] = 0;
    arg0[0x148] &= ~0x18;
  }
  return 1;
}

#ifdef NON_MATCHING
s32 mtx_rot_scale_trans_l(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32); /* P95: f32 (float bits were passed as an int) */
#else
s32 mtx_rot_scale_trans_l(s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);
#endif
s32 func_15133A80(s32 arg0, u8 *arg1) {
#ifdef NON_MATCHING
    mtx_rot_scale_trans_l(arg0, *(f32 *)(arg1 + 0x18), *(f32 *)(arg1 + 0x1C), *(f32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x24), *(f32 *)(arg1 + 0x28), *(f32 *)(arg1 + 0x2C), *(f32 *)(arg1 + 0x30), *(f32 *)(arg1 + 0x34), *(f32 *)(arg1 + 0x38), *(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x40)); /* P95: f32 (float bits were passed as an int) */
#else
    mtx_rot_scale_trans_l(arg0, *(s32 *)(arg1 + 0x18), *(s32 *)(arg1 + 0x1C), *(s32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x24), *(f32 *)(arg1 + 0x28), *(f32 *)(arg1 + 0x2C), *(f32 *)(arg1 + 0x30), *(f32 *)(arg1 + 0x34), *(f32 *)(arg1 + 0x38), *(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x40));
#endif
    return 1;
}

void func_151B9C10(void *);
extern void (*D_80089D98[])(u8 *, u8 *, u8);
void func_15133AF8(u8 *arg0, u8 *arg1, u8 arg2)
{
  s32 idx;
  s32 sel = arg2;
  s32 t;
  s32 k; // fakematch: unused local fixes the arg2-copy spill slot
  if ((arg2 == 0x1B) && (*(u16 *)(arg0 + 0x66) == 0x22))
  {
    func_151B9C10(arg0);
  }
  if (sel == 0x2D)
  {
    if (*(s32 *)arg1 == *(s32 *)(arg0 + 0x7C)) { *(s32 *)(arg0 + 0x7C) = *(s32 *)(arg1 + 4); arg0[0x80] = arg1[9]; }
    else if (*(s32 *)(arg1 + 4) == *(s32 *)(arg0 + 0x7C)) {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
      *(s32 *)(arg0 + 0x7C) = *(s32 *)arg1; arg0[0x80] = arg1[8]; }
  }
  else if (sel == 0)
  {
    t = *(s32 *)arg1;
    if ((t == *(s32 *)(arg0 + 0x7C)) || (arg0[0x80] == arg1[4])) { *(s32 *)(arg0 + 0x7C) = 0; arg0[0x80] = 0; }
  }
  if (*(s32 *)(arg0 + 0x60) & 0x100) { idx = arg0[0x68]; } else { idx = 0; }
  if (D_80089D98[idx] != NULL) { D_80089D98[idx](arg0, arg1, arg2); }
}

#ifdef NON_MATCHING
extern s32 D_800A3C60[];             /* model file per particle model id (ROM table) */
s32 asset_load_with_subfiles(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, ...);
s32 texture_resolve_dl_ids(Gfx *dl, s32 skipResolved, s32 addRef, s32 age, s16 **outList);
void gfx_dl_relocate(s8 *arg0, s32 arg1);

// particle_model_load: loads the model file of particle model id modelId into ref->model, resolves its display
// list (D_800DCA70[modelId]) and registers it; returns 0 when the file is missing. The particle is unused.
s32 func_15133C18(s32 modelId, ParticleModelRef *ref, void *particle) {
    s32 found;
    s32 size;

    ref->model = (s32 *)asset_load_with_subfiles(&found, 0, &size, 2, 9, D_800A3C60[modelId]);
    if (ref->model == NULL) {
        return 0;
    }
    texture_resolve_dl_ids((Gfx *)*ref->model, 0, 1, 0x3E, (s16 **)&D_800DCA70[modelId] /* resolved segment list per model id */);
    gfx_dl_relocate((s8 *)*ref->model, (s32)ref->model);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15133C18.s")
#endif

#ifdef NON_MATCHING
s32 mtx_rot_scale2_trans_l(s32, f32, f32, f32, f32, f32, f32, f32, f32); /* P95: f32 (float bits were passed as an int) */
#else
s32 mtx_rot_scale2_trans_l(s32, s32, s32, s32, f32, f32, f32, f32, f32);
#endif
s32 func_15133CD0(s32 arg0, u8 *arg1) {
#ifdef NON_MATCHING
    mtx_rot_scale2_trans_l(arg0, *(f32 *)(arg1 + 0x18), *(f32 *)(arg1 + 0x1C), *(f32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x24), *(f32 *)(arg1 + 0x28), *(f32 *)(arg1 + 0x38), *(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x40)); /* P95: f32 (float bits were passed as an int) */
#else
    mtx_rot_scale2_trans_l(arg0, *(s32 *)(arg1 + 0x18), *(s32 *)(arg1 + 0x1C), *(s32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x24), *(f32 *)(arg1 + 0x28), *(f32 *)(arg1 + 0x38), *(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x40));
#endif
    return 1;
}

s32 func_15133D30(u8 *arg0) {
    *(f32 *)(arg0 + 0x38) += *(f32 *)(arg0 + 0x44) * D_800BE9A4;
    *(f32 *)(arg0 + 0x3C) += (*(f32 *)(arg0 + 0x48) * D_800BE9A4) + (*(f32 *)(arg0 + 0x5C) * D_800BE9A4 * D_800BE9A4 * 0.5f);
    *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x5C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}

#ifdef NON_MATCHING
s32 func_15046F70(f32 *, s32, f32, u8 *);
/* landing handlers by +0x73 (entry 0 is NULL); they take (particle, old x, old y, old z, floor height, floor info),
   several are declared with s32 / fewer parameters (o32 passes them alike; the port's icall layer converts) */
extern s32 (*D_80089CD4[])(u8 *, f32, f32, f32, f32, u8 *);

// particle_fall_update: moves the particle (func_15133D30). When it has gravity (+0x60 bit 0), a landing kind (+0x73)
// and moved down, it probes the floor from the old height (+0x10 offset) down to the new one (func_15046F70, floor
// height at +0x110, info from +0x114); on a hit, unless its owner object (+0x130) is in state 0x40 (+0x4F & 0x60),
// the kind's landing handler decides the result. Returns 1 (keep the particle) or the handler's verdict (as s8).
s32 func_15133E04(u8 *p) {
    s8 keep;
    f32 old[3];
    f32 probe[3];
    u8 *owner;
    s32 skip;

    keep = 1;
    old[0] = *(f32 *) (p + 0x38);
    old[1] = *(f32 *) (p + 0x3C);
    old[2] = *(f32 *) (p + 0x40);
    func_15133D30(p);
    if ((*(s32 *) (p + 0x60) & 1) && p[0x73] != 0 && *(f32 *) (p + 0x3C) < old[1]) {
        probe[0] = *(f32 *) (p + 0x38);
        probe[1] = *(f32 *) (p + 0x10) + old[1];
        probe[2] = *(f32 *) (p + 0x40);
        if (func_15046F70(probe, 0, *(f32 *) (p + 0x3C) - *(f32 *) (p + 0x10), p + 0x110) != 0) {
            owner = *(u8 **) (p + 0x130);
            skip = FALSE;
            if (owner != NULL && (owner[0x4F] & 0x60) == 0x40) {
                skip = TRUE;
            }
            if (!skip) {
                keep = D_80089CD4[p[0x73]](p, old[0], old[1], old[2], *(f32 *) (p + 0x110), p + 0x114);
            }
        }
    }
    return keep;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15133E04.s")
#endif

/* P317: D_80089CD4's dispatcher type (wasm call_indirect); args 1..3 / 5 are unused, the code is unchanged */
s32 func_15133F44(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, u8 *arg5) {
    f32 temp_f0;
    *(f32 *)(arg0 + 0x3C) = *(f32 *)(arg0 + 0x10) + arg4;
    temp_f0 = *(f32 *)(arg0 + 0x14);
    *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x44) * temp_f0;
    *(f32 *)(arg0 + 0x48) = *(f32 *)(arg0 + 0x48) * -temp_f0;
    *(f32 *)(arg0 + 0x4C) = *(f32 *)(arg0 + 0x4C) * temp_f0;
    *(f32 *)(arg0 + 0x50) = *(f32 *)(arg0 + 0x50) * temp_f0;
    *(f32 *)(arg0 + 0x54) = *(f32 *)(arg0 + 0x54) * temp_f0;
    *(f32 *)(arg0 + 0x58) = *(f32 *)(arg0 + 0x58) * temp_f0;
    return 1;
}

/* P317: D_80089CD4's dispatcher type (wasm call_indirect); args 1..3 / 5 are unused, the code is unchanged */
s32 func_15133FC0(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, u8 *arg5) {
    *(f32 *)(arg0 + 0x3C) = *(f32 *)(arg0 + 0x10) + arg4;
    *(f32 *)(arg0 + 0x44) = 0.0f;
    *(f32 *)(arg0 + 0x48) = 0.0f;
    *(f32 *)(arg0 + 0x4C) = 0.0f;
    *(f32 *)(arg0 + 0x50) = 0.0f;
    *(f32 *)(arg0 + 0x54) = 0.0f;
    *(f32 *)(arg0 + 0x58) = 0.0f;
    return 1;
}

#ifdef NON_MATCHING
/* P241: readable C for func_15134004 (game_eu_15FF50, 65 insns). */
// attached_bone_matrix: entry 5 of D_80089D2C (dispatcher func_15132FF8: -1 ends the object, 0 hides it, 1 shows
// it): copies bone obj[0x170] of the target object (+0x7C) into mtx. -1 when the target is gone (NULL, word +0 is 0,
// byte +4 is 0xFF or its id +0x3B no longer matches obj +0x80); 0 when the target has no bone matrices (+0x1D4) or
// its +0x74 low nibble is 0xF. The bone list holds Mtx (D_800C42B0 set: copied as is) or float matrices (made affine:
// column 3 = 0, 0, 0, 1, then guMtxF2L).
s32 func_15134004(Mtx *mtx, u8 *obj) {
    u8 *target = *(u8 **) (obj + 0x7C);
    u8 *bones;
    f32 mf[4][4];

    if (target == NULL || *(s32 *) target == 0 || target[4] == 0xFF || obj[0x80] != target[0x3B]) {
        return -1;
    }
    bones = *(u8 **) (target + 0x1D4);
    if (bones == NULL) {
        return 0;
    }
    if ((target[0x74] & 0xF) == 0xF) {
        return 0;
    }
    if (D_800C42B0 != 0) {
        memcpy(mtx, bones + obj[0x170] * 0x40, 0x40);
        return 1;
    }
    memcpy(mf, bones + obj[0x170] * 0x40, 0x40);
    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][3] = 1.0f;
    guMtxF2L(mf, mtx);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15134004.s")
#endif

s32 func_15134108(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5)
{
  f32 temp_f18;
  f32 temp_f6;
  *((f32 *) (((u8 *) arg0) + 0x3C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x10))) + arg4);
  temp_f18 = *((f32 *) (((u8 *) arg0) + 0x14));
  *((f32 *) (((u8 *) arg0) + 0x48)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x48))) * (-temp_f18));
  *((f32 *) (((u8 *) arg0) + 0x44)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x44))) * temp_f18);
  *((f32 *) (((u8 *) arg0) + 0x4C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x4C))) * temp_f18);
  *((f32 *) (((u8 *) arg0) + 0x50)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x50))) * temp_f18);
  *((f32 *) (((u8 *) arg0) + 0x54)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x54))) * temp_f18);
  *((f32 *) (((u8 *) arg0) + 0x58)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x58))) * temp_f18);
  if (fabsf(*((f32 *) (((u8 *) arg0) + 0x48))) < 4.0f)
  {
    *((f32 *) (((u8 *) arg0) + 0x44)) = 0.0f;
    *((s32 *) (((u8 *) arg0) + 0x60)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x60))) & (~0x69));
    *((f32 *) (((u8 *) arg0) + 0x48)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x4C)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x50)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x54)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x58)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x5C)) = 0.0f;
  }
  return 1;
}

s32 func_151341C8(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    func_15134108(arg0, arg1, arg2, arg3, arg4, arg5);
    if (random_int() & 1) {
        func_10010F88((random_int() % 9U) + 0x2DE, 0x2EE0U, 0, 0U, 0, (s16) (s32) arg1, (s16) (s32) arg2, (s16) (s32) arg3, 0x1F4, 0x3E8);
    }
    return 1;
}

s32 func_15134290(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    func_15134108(arg0, arg1, arg2, arg3, arg4, arg5);
    if (random_int() & 1) {
        func_10010F88((random_int() % 10U) + 0x1B8, 0x5DC0U, 0, 0U, 0, (s16) (s32) arg1, (s16) (s32) arg2, (s16) (s32) arg3, 0x1F4, 0x3E8);
    }
    return 1;
}

void func_15134358(struct102 *arg0, s32 *arg1, u8 arg2) {
    s32 id;
    if (arg2 == 0) {
        id = arg1[0];
        if (id == *(s32 *)((u8 *)arg0 + 0x7C) || ((u8 *)arg1)[4] == *((u8 *)arg0 + 0x80)) {
            node_destroy(arg0);
        }
    }
}

void func_151343AC(s32 arg0, u8 arg1) {
    struct_eu_s32x2 sp18 = D_800A3C40;
    node_broadcast_types(&sp18, 2, arg0, arg1);
}

void func_151343F4(s32 arg0, u8 *arg1, s32 arg2) {
    func_1513445C(arg0, *(u16 *)(arg1 + 0x170), arg1[0x172], *(s32 *)(arg1 + 0x174));
}

void func_15134428(s32 arg0, u8 *arg1, s32 arg2) {
    func_1513445C(arg0, *(u16 *)(arg1 + 0x174), arg1[0x176], *(s32 *)(arg1 + 0x178));
}

#ifdef NON_MATCHING
s32 texture_cache_lookup(s32, s32 *, s32, s32);

s32 *func_1513445C(u8 *arg0, u16 arg1, u8 arg2, s32 arg3) {
    struct {
        s32 u30;
        u8 pad34[0x6];
        u8 u3A;
        u8 u3B;
    } sp;
    s32 *temp_v1;
    s32 *var_s0;
    s32 temp_t2;
    s32 temp_v0_2;
    s32 var_a0;
    struct_eu_80090F10 *temp_v0;

    temp_v0 = &D_80090F10[arg1];
    sp.u3B = temp_v0->padA[0];
    sp.u3A = temp_v0->padA[1];
    temp_v0_2 = texture_cache_lookup(*(*(s32 **)((u8 *)temp_v0 + 0)), &sp.u30, arg3, 0);
    (*(s32 *)((u8 *)arg0 + 4)) = temp_v0_2;
    temp_t2 = arg2 * 4;
    (*(s32 *)((u8 *)arg0 + 0)) = (s32) ((temp_t2 & 0xFFFF) | 0xDB060000);
    var_s0 = arg0 + 8;
    temp_v1 = var_s0;
    if (sp.u3B == 2) {
        (*(s32 *)((u8 *)temp_v1 + 0)) = ((temp_t2 + 4) & 0xFFFF) | 0xDB060000;
        var_s0 = (s32 *)((u8 *)var_s0 + (8));
        if (sp.u3A == 1) {
            var_a0 = 0x200;
        } else {
            var_a0 = 0x20;
        }
        (*(s32 *)((u8 *)temp_v1 + 4)) = (s32) ((temp_v0_2 + sp.u30) - var_a0);
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_1513445C.s")
#endif
s32 func_15134548(s32 arg0, u8 *arg1, s32 arg2) {
    u8 *p = arg1 + 0x170;
    u8 *q = p;
    u8 *e;
    s32 i;

    for (i = 0; i < *q; i = (i + 1) & 0xFF) {
        e = (u8 *)((s32)p + (i << 3));
        arg0 = (s32)func_1513445C((u8 *)arg0, *(u16 *)(e + 4), *(u8 *)(e + 6), *(s32 *)(e + 8));
    }
    return arg0;
}
