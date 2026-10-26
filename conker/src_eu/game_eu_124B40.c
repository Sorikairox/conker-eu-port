#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150F7330(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0((s32)&tmp, 0x3E);
}

#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void *memcpy(void *, const void *, s32);

/* func_151307F0's particle template (the GlowTmplC034 layout of game_2062D0) */
typedef struct {
    s32 u0;           /* 0x00 */
    s32 u4;           /* 0x04 */
    u16 flags;        /* 0x08 */
    s16 life;         /* 0x0A */
    s32 uC;           /* 0x0C */
    s32 u10;          /* 0x10 */
    u8 colour[8];     /* 0x14 */
    u8 u1C;           /* 0x1C */
    u8 sprite;        /* 0x1D */
    s16 u1E;          /* 0x1E */
    s16 u20;          /* 0x20 */
    s16 u22;          /* 0x22 */
    f32 u24;          /* 0x24 */
    f32 size[2];      /* 0x28 */
    f32 pos[3];       /* 0x30 */
    f32 u3C[3];       /* 0x3C */
    f32 vel[3];       /* 0x48 */
    f32 u54;          /* 0x54 */
    s32 mode;         /* 0x58 */
    s32 u5C;          /* 0x5C */
    u8 u60[7];        /* 0x60 */
    u8 pad67;
    s16 u68;          /* 0x68 */
    u8 pad6A[2];
    f32 u6C;          /* 0x6C */
} Tmpl7364;

/* the 0x78-byte record copied to the new object's +0x28 (only these fields are set) */
typedef struct {
    struct127 *owner; /* 0x00 */
    u8 u4;            /* 0x04: owner +0x3B */
    s32 fx[2];        /* 0x08: the two particles */
    u8 pad10[0x64];
    u8 u74;           /* 0x74 */
    u8 pad75[3];
} Rec7364;
#endif

#ifdef NON_MATCHING
// object_twin_glow_spawn: creates a type-0x43 object (func_15149130) for obj and copies a record {obj, obj +0x3B,
// 0, 0, ..., +0x74 = 0} to its +0x28, then spawns two func_151307F0 glow particles (flags 0x4417, life 300, size
// 1511, sprite 100, mode 0x64C000, the second one red instead of blue in colour[4..7]) and stores them at the
// record's fx[0] / fx[1]. Returns the new object (NULL when the alloc fails).
void *func_150F7364(struct127 *obj) {
    Rec7364 rec;
    Tmpl7364 t;
    struct260 *o;
    Rec7364 *r;
    f32 *still = (f32 *) D_800A5860; /* zero vector */
    u8 i;

    rec.owner = obj;
    rec.u4 = ((u8 *) obj)[0x3B];
    for (i = 0; i < 2; i++) {
        rec.fx[i] = 0;
    }
    rec.u74 = 0;
    o = func_15149130(0x12C, -1, 0x43, -1, 0, 0x37, (struct37 *) 0x78, 0xFF, 1);
    if (o == NULL) {
        return NULL;
    }
    r = (Rec7364 *) ((u8 *) o + 0x28);
    memcpy(r, &rec, sizeof(Rec7364));
    t.u0 = 0x200004;
    t.u4 = 0;
    t.flags = 0x4417;
    t.life = 0x12C;
    t.uC = 0;
    t.u10 = 0;
    t.colour[0] = 0xFF;
    t.colour[1] = 0xFF;
    t.colour[2] = 0xFF;
    t.colour[3] = 0xFF;
    t.u1C = 0xFF;
    t.size[1] = 1511.0f; /* D_800A1F80 */
    t.size[0] = 1511.0f;
    t.pos[0] = still[0];
    t.pos[1] = still[1];
    t.pos[2] = still[2];
    t.u3C[0] = still[0];
    t.u3C[1] = still[1];
    t.u3C[2] = still[2];
    t.vel[0] = still[0];
    t.vel[1] = still[1];
    t.vel[2] = still[2];
    t.u1E = 1;
    t.u20 = 0xFF;
    t.u22 = 1;
    t.mode = 0x64C000;
    t.u60[0] = 8;
    t.u60[1] = 6;
    t.u60[2] = 0xFF;
    t.u60[3] = 0xFF;
    t.u60[4] = 3;
    t.u60[5] = 0;
    t.u5C = 0;
    t.u60[6] = 0xFF;
    t.u68 = 10;
    t.sprite = 0x64;
    t.colour[4] = 0;
    t.colour[5] = 0;
    t.colour[6] = 0xFF;
    t.colour[7] = 0xFF;
    t.u54 = 0.0f;
    t.u24 = 1.0f;
    t.u6C = 20.0f;
    r->fx[0] = func_151307F0((s32) &t, 1, 0, 0, ((u8 *) o)[0xC], ((u8 *) o)[1]);
    t.colour[4] = 0xFF;
    t.colour[5] = 0;
    t.colour[6] = 0;
    t.colour[7] = 0xFF;
    r->fx[1] = func_151307F0((s32) &t, 1, 0, 0, ((u8 *) o)[0xC], ((u8 *) o)[1]);
    return o;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_124B40/func_150F7364.s")
#endif

#ifdef NON_MATCHING
extern f32 D_800A1F84;
extern f32 D_800A1F88;
void func_1502ED88(u8 *, s32, s32, s32, s32, s32, s32);
s32 func_1506196C(s32, s32);
s32 func_15081A90(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
extern s32 D_800D9E70;

void func_150F75EC(u8 *arg0) {
    struct {
        s32 u60;
        u8 pad64[0x8];
        f32 u6C;
        f32 u70;
        f32 u74;
    } sp;
    s8 var_t1;
    struct127 *temp_s2;
    u8 *temp_s1;
    u8 *temp_t5;
    u8 *temp_t8;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *var_t2;

    temp_s2 = (*(struct127 **)((u8 *)arg0 + 0x28));
    temp_s1 = arg0 + 0x28;
    if ((temp_s2->interaction_state == 0) || ((*(u8 *)((u8 *)temp_s1 + 4)) != temp_s2->unique_id)) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    if (D_800C35EA == 1) {
        temp_v0 = (*(u8 **)((u8 *)temp_s1 + 8));
        if ((temp_v0 != NULL) && ((*(u8 **)((u8 *)temp_s1 + 0xC)) != NULL)) {
            (*(s8 *)((u8 *)temp_v0 + 0x74)) = 3;
            (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0xC))) + 0x74)) = 3;
        }
    } else {
        sp.u6C = temp_s2->x_position;
        sp.u70 = temp_s2->y_position + 46.0f;
        sp.u74 = temp_s2->z_position;
        func_15145740(temp_s2, (s32) &D_800D9E70, 0, 0, 0.0f);
        (*(f32 *)((u8 *)(&D_800D9E70) + 0)) = (f32) ((*(f32 *)((u8 *)(&D_800D9E70) + 0)) * D_800A1F84);
        (*(f32 *)((u8 *)(&D_800D9E70) + 4)) = (f32) ((*(f32 *)((u8 *)(&D_800D9E70) + 4)) * D_800A1F84);
        (*(f32 *)((u8 *)(&D_800D9E70) + 8)) = (f32) ((*(f32 *)((u8 *)(&D_800D9E70) + 8)) * D_800A1F84);
        func_15081A90(temp_s2, sp.u6C, sp.u70, sp.u74, (*(f32 *)((u8 *)(&D_800D9E70) + 0)), (*(f32 *)((u8 *)(&D_800D9E70) + 4)), (*(f32 *)((u8 *)(&D_800D9E70) + 8)), temp_s1 + 0x10, D_800A1F88, 0, 0, 1, -1, 0, 0);
        (*(u8 *)((u8 *)temp_s1 + 0x74)) = (u8) ((*(u8 *)((u8 *)temp_s1 + 0x74)) | 1);
        if (((*(u8 **)((u8 *)temp_s1 + 8)) != NULL) && (temp_v0_2 = (*(u8 **)((u8 *)temp_s1 + 0xC)), (temp_v0_2 != NULL))) {
            if ((*(u8 *)((u8 *)temp_s1 + 0x69)) == 0) {
                (*(s8 *)((u8 *)temp_v0_2 + 0x74)) = 3;
                var_t2 = (*(u8 **)((u8 *)temp_s1 + 8));
                var_t1 = (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0xC))) + 0x74));
                goto block_16;
            }
            (*(s32 *)((u8 *)(&sp.u60) + 0)) = (s32) (*(s32 *)((u8 *)temp_s1 + 0x18));
            (*(s32 *)((u8 *)(&sp.u60) + 4)) = (s32) (*(s32 *)((u8 *)temp_s1 + 0x1C));
            (*(s32 *)((u8 *)(&sp.u60) + 8)) = (s32) (*(s32 *)((u8 *)temp_s1 + 0x20));
            temp_t5 = (*(u8 **)((u8 *)temp_s1 + 0xC));
            (*(s32 *)((u8 *)temp_t5 + 0x40)) = (s32) (*(s32 *)((u8 *)(&sp.u60) + 0));
            (*(s32 *)((u8 *)temp_t5 + 0x44)) = (s32) (*(s32 *)((u8 *)(&sp.u60) + 4));
            (*(s32 *)((u8 *)temp_t5 + 0x48)) = (s32) (*(s32 *)((u8 *)(&sp.u60) + 8));
            temp_t8 = (*(u8 **)((u8 *)temp_s1 + 8));
            (*(s32 *)((u8 *)temp_t8 + 0x40)) = (s32) (*(s32 *)((u8 *)(&sp.u60) + 0));
            (*(s32 *)((u8 *)temp_t8 + 0x44)) = (s32) (*(s32 *)((u8 *)(&sp.u60) + 4));
            (*(s32 *)((u8 *)temp_t8 + 0x48)) = (s32) (*(s32 *)((u8 *)(&sp.u60) + 8));
            if ((*(u8 *)((u8 *)temp_s1 + 0x69)) == 1) {
                (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 8))) + 0x74)) = -1;
                (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0xC))) + 0x74)) = 3;
                return;
            }
            if (func_1506196C((*(s32 *)((u8 *)temp_s1 + 0x10)), 0) < 0xFF) {
                (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 8))) + 0x74)) = -1;
                (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0xC))) + 0x74)) = 3;
                return;
            }
            func_1502ED88((*(s32 *)((u8 *)temp_s1 + 0x10)), 0xFF, 0, 0, 0x7F, 0, 0x10);
            var_t1 = -1;
            (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 8))) + 0x74)) = 3;
            var_t2 = (*(u8 **)((u8 *)temp_s1 + 0xC));
block_16:
            (*(s8 *)((u8 *)var_t2 + 0x74)) = var_t1;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_124B40/func_150F75EC.s")
#endif
#ifdef NON_MATCHING
// linked_obj_event_3e: event handler of an object whose link record sits at +0x28 ({ s32 id, u8 key }): event 0x3E removes the
// object (node_destroy) when the event's record matches by id or by key; any other event goes to the common
// handler func_15149514.
void func_150F7890(struct102 *obj, u8 *ev, u8 type) {
    u8 *link = (u8 *) obj + 0x28;

    if (type == 0x3E) {
        if (*(s32 *) link == *(s32 *) ev || link[4] == ev[4]) {
            node_destroy(obj);
        }
    } else {
        func_15149514((s32) ev, type, (s32) link, (s32) (link + 4), (s32) obj);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_124B40/func_150F7890.s")
#endif

s32 func_1514EDF0(s32, s32);
void func_150F791C(s32 arg0) {
    s32 *p;
    s32 i;
    struct102 *a;
    p = (s32 *)((u8 *)arg0 + 0x28);
    i = 0;
    do {
        a = (struct102 *)p[i + 2];
        if (a != NULL) {
            node_destroy(a);
        }
        i += 1;
        i = i & 0xFF;
    } while (i < 2);
    func_1514EDF0(arg0, *p);
}

void func_150F798C(void *arg0) {
    func_150F791C(arg0);
    func_1514933C(arg0);
}

void func_150F79B8(void *arg0) {
    func_150F791C(arg0);
    func_15149368(arg0);
}
