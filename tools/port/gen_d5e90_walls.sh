#!/bin/sh
# P56: regenerate the register-level C of the hand-asm wall engine and ray cast (src_eu/nm_asm/D5E90_*.inc).
# Run from the worktree root. D5E90.c includes walls.inc; touch it so make rebuilds.
set -e
cd conker
python3 ../tools/port/asm2c_hand.py asm/D5E90.s walls 150AA950 150AB278 150AB6D0 150ACEA0 e150AB6D0 e150AC8C4 \
    > src_eu/nm_asm/D5E90_walls.inc
# P291: the ray cast (D5E90_ray.inc) is readable C in D5E90.c now. Note: walls.inc holds hand-edited readable
# entries since P285 / P288 (do not regenerate it over them).
touch src_eu/nm_asm/D5E90.c
