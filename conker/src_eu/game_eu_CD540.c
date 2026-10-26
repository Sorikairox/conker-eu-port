#include <ultra64.h>
#include "functions.h"
#include "variables.h"


struct249 *event_find(s16 arg0);
struct249 *event_start(s32 id, s32 arg1);
void event_vm_abort(void);
void game_request_transition(s32, s32, s32, s32, s32);
void warp_request_start(struct127 *arg0, s32 arg1, s32 arg2);
void screen_fade_start(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 arg4, s32 arg5);
void mp_match_end(s32 arg0);
void credits_start(void);
void game_mode_set_10(void);
void text_printf(s32 arg0, ...);
extern s32 D_800D3268;          /* id of the event the VM is running */
extern s32 D_800D3378;          /* save bits changed */
extern s32 D_800D3C60;          /* values pushed for the current native call */
extern u8 D_800877B0[];
extern s32 D_800D3420;
extern s32 D_800D3424;
extern char D_8009F870[];       /* "%d" */

// event_action_game_state: game-state actions of the event scripts (native 6, D_80088874 entry 4, ids 0x5xxx).
// id = the event id the action applies to (call id without the nibble), args = the VM stack (args[2].. = values
// pushed below the id and the action). Actions 1 / 3 / 11 abort the running script when they stop the event that
// runs it: `event_vm_abort(); return 0;` must stay at both sites (the VM checks the abort flag after the call).
/* was func_1509FD30 */
s32 event_action_game_state(s32 id, s32 action, s32 *args) {
    u8 *bits;
    struct249 *ev;
    s32 i;

    switch (action) {
        case 1: /* finish the event: set its done bit, then as 3 */
            if (D_800877B0[1] != 0) {
                D_800877B0[1] = 0;
                return 0;
            }
            bits = (u8 *) D_800D2E4C + (id >> 3);
            *bits |= 1 << (id & 7);
            D_800D3378 = 1;
            D_800D2E43 = 1;
            /* fallthrough */
        case 3: /* stop the event (abort when it is the one running) */
            ev = event_find(id);
            if (ev == NULL) {
                return 0;
            }
            ev->unk0 |= 0x8000;
            if (id == D_800D3268) {
                event_vm_abort();
                return 0;
            }
            return 1;
        case 2: /* stop the event and keep only its done bit (as the asm: byte & 7 & bit) */
            ev = event_find(id);
            bits = (u8 *) D_800D2E4C + (id >> 3);
            *bits = (*bits & 7) & (1 << (id & 7));
            D_800D3378 = 1;
            D_800D2E43 = 1;
            if (ev == NULL) {
                return 0;
            }
            ev->unk0 |= 0x8000;
            return 1;
        case 4: /* pause the event */
            ev = event_find(id);
            if (ev == NULL) {
                return 0;
            }
            ev->unk0 |= 0x4000;
            return 1;
        case 5: /* clear the event's variables */
            ev = event_find(id);
            if (ev == NULL) {
                return 0;
            }
            bzero((u8 *) ev + ((u16 *) ev)[5], ((u16 *) ev)[3]);
            return 0;
        case 6: /* start the event */
            event_start(id, 0);
            return 0;
        case 7: /* change level (four values pushed) */
            if (D_800D3C60 == 4) {
                game_request_transition(2, args[2], args[3], 0, 0);
            }
            return 0;
        case 8:
            if (D_800D3C60 == 4) {
                warp_request_start(g_objects, args[2] & 0xFFF, args[3] & 0xFFF);
            }
            return 0;
        case 9: /* set / clear a bit of D_800D2E60 */
            D_800D3289 = 1;
            bits = &D_800D2E60[args[3] >> 3];
            if (args[2] != 0) {
                *bits |= 1 << (args[3] & 7);
            } else {
                *bits = (*bits & 7) & (1 << (args[3] & 7));
            }
            D_800D2E43 = 1;
            return 0;
        case 10:
            mp_match_end(args[2]);
            return 0;
        case 11: /* finish the event, mp_match_end(0) and abort the running script */
            ev = event_find(id);
            bits = (u8 *) D_800D2E4C + (id >> 3);
            *bits |= 1 << (id & 7);
            D_800D3378 = 1;
            D_800D2E43 = 1;
            if (ev == NULL) {
                return 0;
            }
            ev->unk0 |= 0x8000;
            mp_match_end(0);
            event_vm_abort();
            return 0;
        case 12: /* timer start: both stamps, or only the first */
            if (args[2] < 0) {
                D_800D3420 = D_800D3424 = osGetCount();
            } else {
                osGetCount();
                D_800D3420 = osGetCount();
            }
            return 0;
        case 13:
            g_level_entry_zoom_mode = 1;
            return 0;
        case 14:
            D_800E9D00 |= args[2];
            return 0;
        case 15:
            if (args[3] == 0) {
                D_800D2120 &= ~(1 << args[2]);
            } else {
                D_800D2124 &= ~(1 << args[2]);
            }
            return 0;
        case 16:
            if (args[3] == 0) {
                D_800D2120 |= 1 << args[2];
            } else {
                D_800D2124 |= 1 << args[2];
            }
            return 0;
        case 17:
            screen_fade_start(0, 0, 0, 0, 1, 0);
            return 0;
        case 18:
            for (i = 0; i <= D_80082FA0; i++) {
                screen_fade_start(args[2], args[3], args[4], args[5], args[6], i);
            }
            return 0;
        case 19:
            g_save_resume_level = args[2];
            D_800BE800 = args[3];
            *(s32 *) &g_level_load_id = (s8) g_save_resume_level;
            return 0;
        case 20: /* attract idle check (-> mode 8) */
            credits_start();
            return 0;
        case 21: /* -> mode 10 */
            game_mode_set_10();
            return 0;
        case 22: /* debug print */
            text_printf((s32) D_8009F870, args[2]);
            return 0;
        case 23:
            D_800D2E44 = (args[2] != 0) ? 1 : 0;
            return 0;
    }
    return 0;
}

struct249 *event_find(s16 arg0);
f32 random_float(void);
s32 mp_player_team(s32 arg0);
s32 screen_fade_is_opaque(s32 arg0);
extern s32 D_800D3C60;          /* values pushed for the current native call */
extern s8 D_800E0FE1;
extern u16 D_8009015C;
extern u16 D_800BED50[];
extern u16 D_800BED38[][3];
extern u8 D_800D3260;

// event_query_game_state: game-state queries of the event scripts (native 5, D_80088838 entry 4, ids 0x5xxx), the
// result goes to the VM's result register. id = the event id (for the event queries), args = the VM stack
// (args[2].. = values pushed below the id and the query).
/* was func_150A02EC */
s32 event_query_game_state(s32 id, s32 query, s32 *args) {
    s32 mask;
    s32 sum;
    s32 pick;
    s32 i;

    switch (query) {
        case 0x1A: /* the event's done bit */
            return ((u8 *) D_800D2E4C)[id >> 3] & (1 << (id & 7));
        case 0x1B: /* the event's state word (no NULL check in the asm) */
            return ((u16 *) event_find(id))[1];
        case 0x1C:
            return g_level_id;
        case 0x1D: /* bit mask of the D_8008FD8C slots whose D_80087270 byte is not 10, minus the D_800D18A0 bits */
            mask = 0;
            for (i = 0; i < D_8008FD8C; i++) {
                if (D_80087270[i] != 10) {
                    mask |= 1 << i;
                }
            }
            return mask & ~D_800D18A0;
        case 0x1E:
            return mp_player_team(args[2]);
        case 0x1F:
            return D_800BE9F8;
        case 0x20:
            return (s8) g_save_resume_level;
        case 0x21:
            return D_800BE800;
        case 0x22: /* weighted random pick: args[2] weights follow in args[3..] */
            sum = 0;
            for (i = 0; i < args[2]; i++) {
                sum += args[3 + i];
            }
            pick = random_float() * (f32) sum;
            sum = 0;
            for (i = 0; i < args[2]; i++) {
                sum += args[3 + i];
                if (sum >= pick && args[3 + i] != 0) {
                    return i;
                }
            }
            return args[2] - 1;
        case 0x23:
            return D_80090130;
        case 0x24:
            return D_800E0FE1;
        case 0x25:
            return D_8009015C & 0x10;
        case 0x26:
            return D_8008FD8C;
        case 0x27:
            return D_800BED50[args[2]];
        case 0x28:
            return D_800BED38[args[2]][0];
        case 0x29: /* game mode 2 */
            return D_800E0B94 == 2;
        case 0x2A:
            return args[2] & D_800E9D00;
        case 0x2B: /* the event is not paused (0x2000 clear); no event: 0 */
            {
                struct249 *ev = event_find(id);

                if (ev == NULL) {
                    return 0;
                }
                return (ev->unk0 & 0x2000) == 0;
            }
        case 0x2C:
            return screen_fade_is_opaque((D_800D3C60 == 3) ? args[2] : 0);
        case 0x2D:
            return D_800D3260;
    }
    return 0;
}
