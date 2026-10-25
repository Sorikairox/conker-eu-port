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
/* func_151307F0 sprite template (same layout as game_eu_1F3040's SprTmpl64F4) */
typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ s32 u4;
    /* 0x08 */ u16 flags;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 uC;
    /* 0x10 */ s32 u10;
    /* 0x14 */ u8 colour[8];
    /* 0x1C */ u8 u1C;
    /* 0x1D */ u8 sprite;
    /* 0x1E */ s16 u1E;
    /* 0x20 */ s16 u20;
    /* 0x22 */ s16 u22;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 size[2];
    /* 0x30 */ f32 pos[3];
    /* 0x3C */ f32 u3C[3];
    /* 0x48 */ f32 vel[3];
    /* 0x54 */ f32 u54;
    /* 0x58 */ s32 mode;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 u60[7];
    /* 0x67 */ u8 pad67;
    /* 0x68 */ s16 u68;
    /* 0x6A */ u8 pad6A[2];
    /* 0x6C */ f32 u6C;
} SprTmpl7364;

/* the 0x78-byte record copied to the new object's +0x28 */
typedef struct {
    /* 0x00 */ struct127 *owner;
    /* 0x04 */ u8 room;
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ s32 sprite[2]; /* the two func_151307F0 particles */
    /* 0x10 */ u8 pad10[0x64];
    /* 0x74 */ u8 u74;
    /* 0x75 */ u8 pad75[3];
} Rec7364;

s32 func_151307F0(s32 *, s32, s32, s32, s32, s32);
void *memcpy(void *, const void *, size_t);

// owner_glow_pair_spawn: creates a func_15149130 object (type 0x12C, 0x43) whose 0x78-byte record (+0x28) holds the
// owner, its byte +0x3B and two glow sprites (sprite 0x64, 300 frames, size 1511) made with func_151307F0 at the
// origin: the first tinted 00 00 FF FF, the second FF 00 00 FF (template colour bytes 4..7). Returns the object
// (NULL when it could not be created).
void *func_150F7364(struct127 *owner) {
    Rec7364 rec;
    SprTmpl7364 t;
    struct260 *obj;
    u8 *o;
    Rec7364 *r;
    u8 i;

    rec.owner = owner;
    rec.room = ((u8 *) owner)[0x3B];
    for (i = 0; i < 2; i++) {
        rec.sprite[i] = 0;
    }
    rec.u74 = 0;
    obj = func_15149130(0x12C, -1, 0x43, -1, 0, 0x37, (struct37 *) sizeof(Rec7364), 0xFF, 1);
    if (obj == NULL) {
        return NULL;
    }
    o = (u8 *) obj;
    r = (Rec7364 *) (o + 0x28);
    memcpy(r, &rec, sizeof(Rec7364));
    t.flags = 0x4417;
    t.u0 = 0x200004;
    t.u4 = 0;
    t.life = 300;
    t.uC = 0;
    t.u10 = 0;
    t.colour[0] = 0xFF;
    t.colour[1] = 0xFF;
    t.colour[2] = 0xFF;
    t.colour[3] = 0xFF;
    t.u1C = 0xFF;
    t.size[1] = 1511.0f;
    t.size[0] = 1511.0f;
    t.pos[0] = ((f32 *) D_800A5860)[0];
    t.pos[1] = ((f32 *) D_800A5860)[1];
    t.pos[2] = ((f32 *) D_800A5860)[2];
    t.u3C[0] = ((f32 *) D_800A5860)[0];
    t.u3C[1] = ((f32 *) D_800A5860)[1];
    t.u3C[2] = ((f32 *) D_800A5860)[2];
    t.vel[0] = ((f32 *) D_800A5860)[0];
    t.vel[1] = ((f32 *) D_800A5860)[1];
    t.vel[2] = ((f32 *) D_800A5860)[2];
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
    r->sprite[0] = func_151307F0((s32 *) &t, 1, 0, 0, o[0xC], o[1]);
    t.colour[4] = 0xFF;
    t.colour[5] = 0;
    t.colour[6] = 0;
    t.colour[7] = 0xFF;
    r->sprite[1] = func_151307F0((s32 *) &t, 1, 0, 0, o[0xC], o[1]);
    return obj;
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
// object (func_1516972C) when the event's record matches by id or by key; any other event goes to the common
// handler func_15149514.
void func_150F7890(struct102 *obj, u8 *ev, u8 type) {
    u8 *link = (u8 *) obj + 0x28;

    if (type == 0x3E) {
        if (*(s32 *) link == *(s32 *) ev || link[4] == ev[4]) {
            func_1516972C(obj);
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
            func_1516972C(a);
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
