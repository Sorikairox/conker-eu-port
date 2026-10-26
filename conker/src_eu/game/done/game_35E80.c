#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150089D0 */
void particle_cooldowns_reset(void) {
    u8 tmp = -1;
    g_particle_cooldown = tmp;
    if (0) {};
    g_particle_cooldown_p1 = tmp;
    g_particle_cooldown_p2 = tmp;
    g_particle_cooldown_p3 = tmp;
}
