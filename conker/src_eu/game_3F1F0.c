#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15011D40 */
void level_hook_call_15103800(void) {
    sfx_cooldown_clear();
}

// doesnt look like fun
// marker_effect_spawn: P256: spawns a type 0x12C effect (effect_node_create, 0x4C-byte state copied to +0x28) for `obj`
// and its slot byte (low byte of the word at obj +0x1C): the state holds obj, the slot, slot >= 4, a life of
// 300 + rand % 121, eight handles world_record_find(g_marker_effect_record_ids[i * 8 + slot]) and the position of the slot's map marker
// (map_marker_find over g_level_zone_count with a key of type 3 / 0x15 / slot, flags 0x11A0: its s16 x, y, z at +0 / +4 / +6),
// or (0, 0, 10) without one. Always returns 1.
s32 world_record_find(u8);
u8 *map_marker_find(s32, s32, u16, u8 *);
void *memcpy(void *, const void *, unsigned int);
extern u8 g_marker_effect_record_ids[]; /* was D_800A1FD0 */
/* was func_15011D60 */
s32 marker_effect_spawn(u8 *obj) {
    struct {
        u8 pad0[0x15];
        u8 type;        /* +0x15 */
        u8 pad16;
        u8 sub;         /* +0x17 */
        s32 slot;       /* +0x18 */
        u8 pad1C[0x18];
    } key;
    struct {
        u8 *obj;        /* +0x00 */
        u8 slot;        /* +0x04 */
        u8 high;        /* +0x05 slot >= 4 */
        s16 life;       /* +0x06 */
        u8 b8;          /* +0x08 */
        s32 handle[8];  /* +0x0C */
        f32 f2C[4];     /* +0x2C */
        s16 h3C;        /* +0x3C */
        f32 pos[3];     /* +0x40 */
    } state;
    s16 *marker;
    u8 *e;
    u8 i;

    bzero(&state, sizeof(state));
    state.b8 = 0;
    state.life = random_int() % 121U + 300;
    state.obj = obj;
    state.slot = *(s32 *)(obj + 0x1C);
    state.high = (state.slot < 4) ? 0 : 1;
    for (i = 0; i < 8; i++) {
        state.handle[i] = world_record_find(g_marker_effect_record_ids[i * 8 + state.slot]);
    }
    state.h3C = 0;
    state.f2C[0] = 0.0f;
    state.f2C[1] = 0.0f;
    state.f2C[2] = 0.0f;
    state.f2C[3] = 0.0f;
    key.type = 3;
    key.sub = 0x15;
    key.slot = state.slot;
    marker = (s16 *) map_marker_find(0, g_level_zone_count, 0x11A0, (u8 *) &key);
    if (marker != NULL) {
        state.pos[0] = marker[0];
        state.pos[1] = marker[2];
        state.pos[2] = marker[3];
    } else {
        state.pos[2] = 10.0f;
    }
    e = (u8 *) effect_node_create(300, -1, -1, -1, 0, 0x38, (struct37 *) sizeof(state), 0xFF, 1);
    if (e != NULL) {
        memcpy(e + 0x28, &state, sizeof(state));
    }
    return 1;
}
