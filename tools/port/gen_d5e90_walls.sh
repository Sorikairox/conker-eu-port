#!/bin/sh
# P56 generated the register-level C of the hand-asm wall engine (D5E90_walls.inc) and ray cast (D5E90_ray.inc)
# with tools/port/asm2c_hand.py. Retired in P294: the whole engine is readable C in src_eu/nm_asm/D5E90.c (ray cast
# P291, engine P294) and both .inc files are deleted. Do not regenerate them.
echo "gen_d5e90_walls.sh: retired (P294), D5E90.c is readable C" >&2
exit 1
