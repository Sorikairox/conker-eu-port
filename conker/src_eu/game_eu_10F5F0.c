#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 g_door_light_level[4]; /* was D_80088D30 */
extern f32 g_door_light_target[4]; /* was D_80088D40 */
extern f32 g_door_light_vel[4]; /* was D_80088D50 */
extern s32 g_door_light_query_events[4]; /* was D_80088D60 */
extern s32 g_door_light_set_events[4]; /* was D_80088D70 */
s32 event_dispatch(s32, s32, s32, s32);
void math_spring_approach(f32 *, f32, f32 *, f32, f32, f32);

// door_lights_update: for each of the 4 lights, flag 0x9000 of event 0x4039 + i (event_dispatch) picks the target
// level (192 on, 255 off); the level eases toward it (math_spring_approach: speed 4, rate 6, frame step obj+0x7B4) and is
// sent as byte parameter 0x12 of sound / effect 0x30E4 + i (event_dispatch_alt). obj+0x84 gets 0x10, plus 0x80021010
// while any light is on (else those bits are cleared); bit 31 is set unless event 0x403D has flag 0x2000.
/* was func_150E1DE0 */
void map_door_lights_update(u8 *obj) {
    s32 any = 0;
    s32 i;

    *(u32 *) (obj + 0x84) |= 0x10;
    for (i = 0; i < 4; i++) {
        if (event_dispatch(1, g_door_light_query_events[i], 6, 0x9000) != 0) {
            g_door_light_target[i] = 192.0f;
            *(u32 *) (obj + 0x84) |= 0x80021010;
            any = 1;
        } else {
            g_door_light_target[i] = 255.0f;
        }
        math_spring_approach(&g_door_light_level[i], g_door_light_target[i], &g_door_light_vel[i], 4.0f, 6.0f, *(f32 *) (obj + 0x7B4));
        event_dispatch_alt(1, g_door_light_set_events[i], 0x12, (u8) (u32) g_door_light_level[i]);
    }
    if (!any) {
        *(u32 *) (obj + 0x84) &= 0x7FFDEFFF;
    }
    if (event_dispatch(1, 0x403D, 6, 0x2000) != 0) {
        *(u32 *) (obj + 0x84) &= 0x7FFFFFFF;
    } else {
        *(u32 *) (obj + 0x84) |= 0x80000000;
    }
}
