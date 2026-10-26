#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 event_dispatch(s32, s32, ...);
#else
s32 event_dispatch(s32, s32, s32, s32);
#endif
/* was func_150F9FA0 */
void camera_hook_event_4025(u8 *arg0)
{
  if (event_dispatch(1, 0x4025, 6, 0x2000) != 0) {
    *(s32 *)(arg0 + 0x84) |= 0x80;
    *(s32 *)(arg0 + 0x84) &= ~8;
    *(f32 *)(arg0 + 0x190) = 85.0f;
  } else {
    *(s32 *)(arg0 + 0x84) &= ~0x80;
    *(s32 *)(arg0 + 0x84) |= 8;
    *(f32 *)(arg0 + 0x190) = 0.0f;
  }
}
