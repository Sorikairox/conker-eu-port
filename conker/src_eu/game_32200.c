#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15004D50 */
void vertex_anchor_alloc_players(void) { 
    s32 i; //s0
    struct222** s1;

    g_vertex_anchor_blocks = (struct222*) &g_vertex_anchor_template;
    for( i = 1;  i <= g_last_player_index; i++){
        (&g_vertex_anchor_blocks)[i] = (struct222 *) allocate_memory(0x50, 1, 2, 0); //allocate_memory
        bcopy(g_vertex_anchor_blocks, (&g_vertex_anchor_blocks)[i], 0x50); //bcopy
    }
}
