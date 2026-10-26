#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void smoke_trail_destroy_puffs(void *);


/* was func_150C0EB0 */
void smoke_trail_on_message(u8 *arg0, s32 arg1, u8 arg2) {
    node_handle_link_message(arg1, arg2, (s32)(arg0 + 0x20), (s32)(arg0 + 0x24), (s32)arg0);
}

/* was func_150C0EF0 */
void smoke_trail_retire(void *arg0) {
    smoke_trail_destroy_puffs(arg0);
    node_retire(arg0);
}

/* was func_150C0F1C */
void smoke_trail_free(void *arg0) {
    smoke_trail_destroy_puffs(arg0);
    node_unlink_free(arg0);
}

/* was func_150C0F48 */
void smoke_trail_destroy_puffs(void *arg0) {
    s16 var_s0;
    s32 temp_s2;
    var_s0 = (*(s16 *)((u8 *)arg0 + 0x44));
    if (var_s0 != -1) {
        do {
            temp_s2 = var_s0 * 8;
            node_destroy(*(void **)((*(u8 **)((u8 *)arg0 + 0x40)) + temp_s2));
            var_s0 = (*(s16 *)((u8 *)(*(u8 **)((u8 *)arg0 + 0x40)) + temp_s2 + 4));
        } while (var_s0 != -1);
    }
}

void * memcpy(void *, const void *, s32);

/* was func_150C0FC0 */
u8 *smoke_trail_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *temp_v0_4;
    u8 *temp_v0_3;
    u8 *temp_v0;
    s32 *temp_v0_2;
    s16 var_v1;
    s16 temp_v0_5;
    s32 sp28;
    u8 *sp2C;

    sp28 = ((*(s16 *)((u8 *)arg0 + 0x14)) * 8) + 0x48;
    if (!((*(u8 *)((u8 *)arg0 + 0x18)) & 2)) {
        temp_v0_2 = (*(s32 **)((u8 *)arg0 + 8));
        if (temp_v0_2 == NULL) {
            return NULL;
        }
        if (*temp_v0_2 == 0) {
            return NULL;
        }
        goto block_5;
    }
block_5:
    temp_v0 = node_alloc(0x25, arg2, sp28, 1, (u8) (s32) arg1, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp2C = temp_v0;
    memcpy(temp_v0 + 0x18, arg0, 0x1C);
    (*(u8 **)((u8 *)temp_v0 + 0x40)) = (u8 *) (temp_v0 + 0x48);
    if ((*(u8 *)((u8 *)arg0 + 0x18)) & 2) {
        temp_v0_3 = (*(u8 **)((u8 *)temp_v0 + 0x18));
        (*(f32 *)((u8 *)temp_v0 + 0x34)) = (f32) (*(f32 *)((u8 *)temp_v0_3 + 0));
        (*(f32 *)((u8 *)temp_v0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v0_3 + 8));
    } else {
        temp_v0_4 = (*(u8 **)((u8 *)temp_v0 + 0x20));
        (*(f32 *)((u8 *)temp_v0 + 0x34)) = (f32) (*(f32 *)((u8 *)temp_v0_4 + 0x14));
        (*(f32 *)((u8 *)temp_v0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v0_4 + 0x1C));
    }
    (*(f32 *)((u8 *)temp_v0 + 0x3C)) = 0.0f;
    (*(s16 *)((u8 *)temp_v0 + 0x44)) = -1;
    (*(s16 *)((u8 *)temp_v0 + 0x46)) = 0;
    var_v1 = 0;
    if (((*(s16 *)((u8 *)arg0 + 0x14)) - 1) > 0) {
        do {
            temp_v0_5 = var_v1 + 1;
            (*(s16 *)((u8 *)(((*(u8 **)((u8 *)temp_v0 + 0x40)) + (var_v1 * 8))) + 4)) = temp_v0_5;
            var_v1 = temp_v0_5;
        } while (temp_v0_5 < ((*(s16 *)((u8 *)arg0 + 0x14)) - 1));
    }
    (*(s16 *)((u8 *)(((*(u8 **)((u8 *)temp_v0 + 0x40)) + ((*(s16 *)((u8 *)arg0 + 0x14)) * 8))) + -4)) = -1;
    (*(s32 *)((u8 *)temp_v0 + 0x10)) = 1;
    (*(s32 *)((u8 *)temp_v0 + 0x14)) = 0;
    return temp_v0;
}
s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

typedef struct {
    /* 0x00 */ u8 *rec; /* the smoke puff (particle_spawn_ex record) */
    /* 0x04 */ s16 next;
    /* 0x06 */ s16 pad6;
} TrailSlot1138;

/* smoke trail (object type 0x25, made by smoke_trail_spawn; +0x18..0x33 come from its template) */
typedef struct {
    /* 0x00 */ u8 u0;
    /* 0x01 */ u8 owner;
    /* 0x02 */ u8 pad2[0xA];
    /* 0x0C */ u8 room;
    /* 0x0D */ u8 padD[0xB];
    /* 0x18 */ f32 *src;       /* followed point (flag 2) */
    /* 0x1C */ s32 u1C;
    /* 0x20 */ u8 *target;     /* followed object */
    /* 0x24 */ u8 targetId;    /* its id byte (+0x3B) at creation */
    /* 0x25 */ u8 pad25[3];
    /* 0x28 */ f32 rate;       /* puffs per frame unit */
    /* 0x2C */ s16 u2C;
    /* 0x2E */ s16 timer;      /* flag 1: frames left */
    /* 0x30 */ u8 flags;
    /* 0x31 */ u8 pad31[3];
    /* 0x34 */ f32 lastX;
    /* 0x38 */ f32 lastZ;
    /* 0x3C */ f32 accum;
    /* 0x40 */ TrailSlot1138 *slots;
    /* 0x44 */ s16 used;       /* used slot list head (-1 = none) */
    /* 0x46 */ s16 free;       /* free slot list head */
} Trail1138;

/* particle_spawn_ex's sprite particle template (the emit_particle_burst_req layout, as SprTmpl5268 in game_eu_101080) */
typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ s32 u4;
    /* 0x08 */ u16 flags;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 uC;
    /* 0x10 */ s32 u10;
    /* 0x14 */ u8 colour[8]; /* 7 bytes, alpha */
    /* 0x1C */ u8 u1C;
    /* 0x1D */ u8 sprite;
    /* 0x1E */ s16 u1E;
    /* 0x20 */ s16 u20;
    /* 0x22 */ s16 u22;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 size[2];
    /* 0x30 */ s32 pos[3]; /* f32, copied as words */
    /* 0x3C */ f32 dir[3];
    /* 0x48 */ f32 vel[3];
    /* 0x54 */ f32 u54;
    /* 0x58 */ s32 mode;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 u60[7];
    /* 0x67 */ u8 pad67;
    /* 0x68 */ s16 u68;
    /* 0x6A */ u8 pad6A[2];
    /* 0x6C */ f32 u6C;
} SprTmpl1138;

// smoke_trail_update: update handler of a smoke trail. It follows its target object (x, +0x180 y, z), or with flag 2
// the point obj->src (65 lower), and dies (node_destroy) when the target is gone (word 0 == 0) or became another
// object (id +0x3B != targetId), or with flag 1 when the timer runs out. The puffs on the used slot list are moved to
// the current position. When the position changed, and (flag 4) the target is in state 0x1D / 0x1E, and its +0x3C
// speed is not below 3, the trail adds rate * D_800BE9A4 to accum and spawns one blue-grey smoke puff (sprite 0x6C,
// size 67..84, alpha 80..200, life 70..91, random flips, drifting 40..73 in a random direction) per whole unit from
// the free slot list; each puff gets the trail pointer at +0xA8 and its slot moves to the used list.
/* was func_150C1138 */
void smoke_trail_update(Trail1138 *obj) {
    s32 pos[3]; /* f32 x, y, z */
    SprTmpl1138 t;
    Trail1138 *self;
    u8 kill = 0;
    s32 emit;
    s16 i;
    s16 slot;
    u32 r;
    f32 cs;
    f32 sn;
    f32 speed;
    s32 flipX;
    u8 *rec;

    if (!(obj->flags & 2)) {
        if (*(s32 *) obj->target == 0) {
            kill = 1;
        }
        if (obj->targetId != obj->target[0x3B]) {
            kill = 1;
        }
        *(f32 *) &pos[0] = *(f32 *) (obj->target + 0x14);
        *(f32 *) &pos[1] = *(f32 *) (obj->target + 0x180);
        *(f32 *) &pos[2] = *(f32 *) (obj->target + 0x1C);
    } else {
        memcpy(pos, obj->src, 12);
        *(f32 *) &pos[1] -= 65.0f;
    }
    if (!kill) {
        emit = 1;
        for (i = obj->used; i != -1; i = obj->slots[i].next) {
            rec = obj->slots[i].rec;
            ((s32 *) (rec + 0x40))[0] = pos[0];
            ((s32 *) (rec + 0x40))[1] = pos[1];
            ((s32 *) (rec + 0x40))[2] = pos[2];
        }
        if (obj->flags & 4) {
            if (*(u16 *) (obj->target + 0x84) != 0x1D && *(u16 *) (obj->target + 0x84) != 0x1E) {
                emit = 0;
            }
        }
        if (*(f32 *) (obj->target + 0x3C) < 3.0f) {
            emit = 0;
        }
        if (!(*(f32 *) &pos[0] == obj->lastX && *(f32 *) &pos[2] == obj->lastZ) && emit) {
            obj->accum = obj->accum + obj->rate * D_800BE9A4;
            if (1.0f < obj->accum) {
                t.u0 = 0x00200005;
                t.u4 = 0x001F0600;
                t.flags = 0x5103;
                t.uC = 0;
                t.u10 = 0;
                t.colour[3] = 0xFF;
                t.u1C = 0xFF;
                t.sprite = 0x6C;
                t.vel[0] = t.vel[1] = t.vel[2] = 0.0f;
                t.u54 = 0.0f;
                t.u1E = 0x1E;
                t.u20 = 8;
                t.mode = 0x0080DE01;
                t.u60[0] = 8;
                t.u60[1] = 6;
                t.u60[2] = 0xFF;
                t.u60[3] = 0;
                t.u60[4] = 0xFF;
                t.u60[5] = 0;
                self = obj;
                while (1.0f < obj->accum && self->free != -1) {
                    slot = obj->free;
                    r = random_int();
                    cs = angle_byte_cos(r - 0x40);
                    sn = angle_byte_cos(r);
                    speed = random_float() * 33.0f + 40.0f;
                    t.colour[4] = 0x52;
                    t.colour[5] = 0x6B;
                    t.colour[6] = 0x97;
                    t.colour[0] = 0x87;
                    t.colour[1] = 0x6B;
                    t.colour[2] = 0x97;
                    t.colour[7] = (u32) random_int() % 121 + 80;
                    t.size[0] = t.size[1] = random_float() * 17.0f + 67.0f;
                    t.pos[0] = pos[0];
                    t.pos[1] = pos[1];
                    t.pos[2] = pos[2];
                    t.dir[0] = speed * cs;
                    t.dir[2] = speed * sn;
                    t.dir[1] = 0.0f;
                    t.mode &= ~0xC0;
                    flipX = (random_int() & 1) ? 0x80 : 0;
                    t.mode |= ((random_int() & 1) ? 0x40 : 0) | flipX;
                    t.life = t.u22 = (u32) random_int() % 22 + 70;
                    t.u24 = 1.0352269f; /* D_800A0590 */
                    obj->slots[slot].rec = (u8 *) particle_spawn_ex((s32) &t, 1, 0, 4, obj->room, obj->owner);
                    rec = obj->slots[slot].rec;
                    if (rec != NULL) {
                        memcpy(rec + 0xA8, &self, 4);
                        obj->free = obj->slots[slot].next;
                        obj->slots[slot].next = obj->used;
                        obj->used = slot;
                    }
                    obj->accum -= 1.0f;
                }
                while (1.0f < obj->accum) {
                    obj->accum -= 1.0f;
                }
            }
        }
        obj->lastX = *(f32 *) &pos[0];
        obj->lastZ = *(f32 *) &pos[2];
    }
    if (obj->flags & 1) {
        obj->timer -= D_800BE9E4;
        if (obj->timer < 0) {
            kill = 1;
        }
    }
    if (kill) {
        node_destroy((struct102 *) obj);
    }
}

/*
 * pool_slot_release: particle death handler 0 (D_80089BA0, called by particle_sprite_update before the free). The owner
 * at +0xA8 keeps 8-byte slots at +0x40 (object pointer, s16 next) in a used list (head +0x44) and a free list
 * (head +0x46); the slot holding this particle is unlinked from the used list and pushed on the free list.
 */
/* was func_150C1698 */
void pool_slot_release(u8 *arg0) {
    u8 *pool = *(u8 **)(arg0 + 0xA8);
    s16 head = *(s16 *)(pool + 0x44);
    s16 prev = -1;
    s16 cur = head;
    s32 found = FALSE;
    u8 *slots;
    u8 *e;

    if (cur != -1) {
        slots = *(u8 **)(pool + 0x40);
        do {
            e = slots + cur * 8;
            if (*(u8 **)e == arg0) {
                found = TRUE;
            } else {
                prev = cur;
                cur = *(s16 *)(e + 4);
            }
        } while (cur != -1 && !found);
    }
    if (found) {
        e = *(u8 **)(pool + 0x40) + cur * 8;
        if (cur == head) {
            *(s16 *)(pool + 0x44) = *(s16 *)(e + 4);
        } else {
            *(s16 *)(*(u8 **)(pool + 0x40) + prev * 8 + 4) = *(s16 *)(e + 4);
            e = *(u8 **)(pool + 0x40) + cur * 8;
        }
        *(s16 *)(e + 4) = *(s16 *)(pool + 0x46);
        *(s16 *)(pool + 0x46) = cur;
    }
}
