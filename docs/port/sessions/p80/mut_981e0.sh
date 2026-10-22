#!/bin/bash
# P80: func_1507488C / func_1506EF5C mutants on s981e0.txt
D=/Users/sorikairo/conker-wt/port/docs/port/sessions/p80
MTAG=_x $D/mutfast.sh func_1507488C port_work/p80/488c.c $D/s981e0.txt 's/add ^= 1;/add = 1;/' 's/((w >> 8) \& 0xFF)) {/((w >> 8) \& 0x7F)) {/' 's/0x2E4/0x2E8/' 's/w >> 24;/w >> 23;/' 's/add = w \& 1;/add = w \& 2;/' 's/if (add) {/if (!add) {/'
MTAG=_y $D/mutfast.sh func_1506EF5C port_work/p80/ef5c.c $D/s981e0.txt 's/= 0xFFFF;/= 0xFFFE;/' 's/0x276) = 5;/0x276) = 4;/' 's/i) = w;/i) = w >> 1;/' 's/\& 0xFF) \* 2;/\& 0xFF) * 4;/' 's/= w >> 8;/= w >> 9;/' 's/0x284 + i/0x286 + i/'
