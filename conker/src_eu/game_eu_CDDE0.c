#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct { u32 active:1; u32 flag:1; u32 kind:4; u32 pad:26; u32 count; u32 timer; } SlotEnt; /* was D_800D3434 */ /* was D_800D3430 */ // 12 bytes, g_event_timers_count = &g_event_timers[0].count
extern SlotEnt g_event_timers[]; /* was D_800D3430 */


// slots_reset: clears the 10 slots of g_event_timers (inactive, count and timer 0); level start (level_state_init).
/* was func_150A00F0 */
void event_timers_reset(void) {
    SlotEnt *v;

    for (v = g_event_timers; v != g_event_timers + 10; v++) {
        v->active = 0;
        v->count = 0;
        v->timer = 0;
    }
}

extern u16 g_event_timer_periods[]; /* timer period per kind; was D_800888B0 */
extern u16 g_event_timer_mods[]; /* count modulus per kind (0: none); was D_800888BC */

/* Per frame: every active, running slot (of the 10) adds g_frame_ticks to its timer; each time the timer reaches the
 * period of its kind it wraps and the count goes up (modulo the kind's modulus when that is set). */
/* was func_150A067C */
void event_timers_update(void) {
    SlotEnt *v;
    u32 period;

    for (v = g_event_timers; v != g_event_timers + 10; v++) {
        if (v->active && v->flag == 1) {
            v->timer += g_frame_ticks;
            period = g_event_timer_periods[v->kind];
            if (v->timer >= period) {
                v->timer -= period;
                v->count++;
                if (g_event_timer_mods[v->kind] != 0) {
                    v->count %= g_event_timer_mods[v->kind];
                }
            }
        }
    }
}

/* was func_150A0744 */
s32 event_timer_start(s32 arg0, u8 *arg1)
{
    SlotEnt *v = &g_event_timers[arg0];

    if (v->active) {
        return 0;
    }
    v->active = 1;
    v->flag = 0;
    v->kind = *(s32 *)(arg1 + 4);
    v->count = 0;
    return 1;
}

/* was func_150A07B0 */
s32 event_action_timer(s32 arg0, s32 arg1, u8 *arg2)
{
    switch (arg1) {
    case 0:
        g_event_timers[arg0].flag = 1;
        return 1;
    case 1:
        g_event_timers[arg0].flag = 0;
        return 1;
    case 2:
        g_event_timers[arg0].count = *(s32 *)(arg2 + 8);
        return 1;
    }
    return 0;
}

/* was func_150A0854 */
s32 event_query_timer(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 3) {
        return g_event_timers_count[arg0].unk0;
    }
    return 0;
}
