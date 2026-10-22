#!/bin/bash
# P54: mutants of the floor collectors (game_eu_D1760.c / game_eu_D3880.c) through p53/mutant.sh + nmasm_floorsets.py
cd "$(dirname "$0")/../../../.."; M=docs/port/sessions/p53/mutant.sh
{
$M src_eu/game_eu_D1760.c 's/if (n != 0x27) n++;/if (n != 0x28) n++;/' 'nmasm_floorsets.py 300 5'
$M src_eu/game_eu_D1760.c 's/if (x < b\[0\] - 2 ||/if (x < b[0] - 1 ||/' 'nmasm_floorsets.py 300 5'
$M src_eu/game_eu_D1760.c 's/if ((d2 ^ d1) >= 0) return n;/if ((d2 ^ d1) > 0) return n;/' 'nmasm_floorsets.py 300 5'
$M src_eu/game_eu_D1760.c 's/            i += c;/            i = c;/' 'nmasm_floorsets.py 300 5 --only 3f50'
$M src_eu/game_eu_D1760.c 's/if (cz < bz) {/if (cz <= bz) {/' 'nmasm_floorsets.py 300 5'
$M src_eu/game_eu_D1760.c 's/        if (idx == skip) continue;/        if (0) continue;/' 'nmasm_floorsets.py 300 5 --only 5480'
$M src_eu/game_eu_D3880.c 's/if (i == n - 1) goto next;/if (i == n) goto next;/' 'nmasm_floorsets.py 300 5 --only 6a48'
$M src_eu/game_eu_D3880.c 's/if ((obj\[0x4F\] \& 0x40) != 0x40) {/if ((obj[0x4F] \& 0x60) != 0x40) {/' 'nmasm_floorsets.py 300 5 --only 6a48'
} > port_work/p54/floormut.log 2>&1
