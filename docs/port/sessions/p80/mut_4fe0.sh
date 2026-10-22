#!/bin/bash
# P80: func_15004FE0 mutants on s4fe0.txt
D=/Users/sorikairo/conker-wt/port/docs/port/sessions/p80
MTAG=_v $D/mutfast.sh func_15004FE0 port_work/p80/4fe0.c $D/s4fe0.txt 's/ \/ 0x18;/ \/ 0x14;/' 's/count \* 0x14, 1, 1, 0/count * 0x14, 1, 0, 0/' 's/D_800C6A74 = count;/D_800C6A74 = count + 1;/' \
 's/0x6) = 0;/0x6) = 1;/' 's/0x8) = r \* r;/0x8) = r;/' 's/src\[i \* 6 + 3\] + src\[i \* 6 + 0\]/src[i * 6 + 3] + src[i * 6 + 1]/' 's/0x10) = src\[i \* 6 + 0\] - src\[i \* 6 + 3\]/0x10) = src[i * 6 + 3] - src[i * 6 + 0]/' \
 's/0x12) = src\[i \* 6 + 5\]/0x12) = src[i * 6 + 4]/' 's/0xC) = src\[i \* 6 + 4\]/0xC) = src[i * 6 + 5]/' 's/return i;/return count;/' 's/0xC, arg0, 3)/0xC, arg0, 2)/' 's/if (src != NULL) {/if (src == NULL) {/'
