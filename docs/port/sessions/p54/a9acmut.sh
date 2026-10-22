#!/bin/bash
# P54: mutants of the func_1505A9AC draft (sed on a copy) against the setup that reaches the mutated line.
cd "$(dirname "$0")/../../../.."; D=docs/port/sessions/p54/func_1505A9AC.c; M=port_work/p54/mut_a9ac.c
mut() { sed "$1" $D > $M; cmp -s $D $M && { echo "not applied: $1"; return; }
        echo "[$1] $2: $(docs/port/sessions/p54/a9acknobs.sh $M "$2" | cut -c1-120 | tr '\n' ' ')"; }
mut 's/arg0->y_velocity \*= 0.85f;/arg0->y_velocity *= 0.8f;/' b
mut 's/arg0->unk228 = 0xA;/arg0->unk228 = 0xB;/' "g l m"
mut 's/arg0->stunned = 8;/arg0->stunned = 9;/' "h m"
mut 's/func_15060B70(0x1B8, arg0);/func_15060B70(0x1B9, arg0);/' "j o"
mut 's/var_t0_3 = 0xD8;/var_t0_3 = 0xD9;/' q
mut 's/arg0->xz_velocity \*= 0.7f;/arg0->xz_velocity *= 0.75f;/' r
mut 's/func_1505E650(arg0, 0x4BU,/func_1505E650(arg0, 0x4CU,/' n
mut 's/if (arg0->unk65 != 0) {/if (arg0->unk65 == 0x55) {/' c
