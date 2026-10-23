#!/bin/bash
# P70: base runs + mutants of func_15039CC8 (tail combos), func_1503216C, func_1503A968, func_1502FED8.
cd /Users/sorikairo/conker-wt/port
M=docs/port/sessions/p70/mut.sh; S=docs/port/sessions/p70; K=docs/port/sessions/p62/knobs.sh
TR=4 bash $K func_15039CC8 port_work/p70/9cc8.c $S/s9cc8.txt | awk '{print "9cc8 base", $2}' | sort | uniq -c
bash $M func_15039CC8 port_work/p70/9cc8.c $S/s9cc8.txt 's/< 5.0f/<= 5.0f/' 's/obj->in_water \&\& //' 's/} else if (obj->health == 0)/} else if (0)/'
bash $M func_1503216C port_work/p70/216c.c $S/s216c.txt 's/!= -14/!= -13/' 's/left = 4;/left = 3;/' 's/25.0f \* t + 2.0f/25.0f * t + 3.0f/' 's/y <= 120.0f/y < 120.0f/' 's/t = 1.0f;/t = 0.5f;/' 's/& 0xFFF)/\& 0x7FF)/'
bash $M func_1503A968 port_work/p70/a968.c $S/sa968.txt 's/0.015625f/0.03125f/' 's/sx.f = 1.0f \/ f;/sx.f = f;/' 's/m\[3\]\[1\] = pos\[1\];/m[3][1] = pos[0];/' 's/D_800C441A++;/D_800C441A += 2;/' 's/obj->id != 0x22/obj->id != 0x21/'
bash $M func_1502FED8 port_work/p70/fed8.c $S/sfed8.txt 's/entry = req - 1;/entry = req;/' 's/if (anim < (u16) D_800C5A90\[model\])/if (anim <= (u16) D_800C5A90[model])/' 's/D_800C3638 = 1;/D_800C3638 = 2;/' 's/OBJ_U8(obj, 0x1C9) = 0;/OBJ_U8(obj, 0x1C9) = 1;/' 's/if (entry == OBJ_U8(obj, 0x1C8)) {/if (0) {/'
