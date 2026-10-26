#include <ultra64.h>

#include "functions.h"
#include "variables.h"


extern u32 g_debug_port_addr; /* was D_800383D0 */
extern s16 g_debug_port_value; /* was D_800383D4 */
/* was func_100038E0 */
void debug_port_write_4040(void)
{
  int new_var;
  volatile s16 *p = (volatile s16 *) 0xBC000C02;
  new_var = 0x4040;
 do { g_debug_port_addr = (u32) p; g_debug_port_value = new_var; *p = new_var; } while (0);
}
// NON-MATCHING: wtf is this
// s32 debug_port_write_4040(void) {
//     D_80038070 = 0xBC000C02; // -0.007815362885594368 ?
//     D_80038074 = (u16)0x4040;
//     D_BC000C02 = (u16)0x4040;
//     return 0xBC000C02;
// }

/* was func_1000390C */
s32 init_stub_return_zero(void) {
    return 0;
}
