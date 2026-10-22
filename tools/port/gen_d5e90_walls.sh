#!/bin/sh
# P56: regenerate the register-level C of the hand-asm wall engine and ray cast (src_eu/nm_asm/D5E90_*.inc).
# Run from the worktree root. D5E90.c includes both; touch it so make rebuilds.
set -e
cd conker
python3 ../tools/port/asm2c_hand.py asm/D5E90.s walls 150AA950 150AB278 150AB6D0 150ACEA0 e150AB6D0 e150AC8C4 \
    > src_eu/nm_asm/D5E90_walls.inc
python3 ../tools/port/asm2c_hand.py asm/D5E90.s ray 150ACEA0 150ADC44 e150ACEA0 > src_eu/nm_asm/D5E90_ray.inc
touch src_eu/nm_asm/D5E90.c
