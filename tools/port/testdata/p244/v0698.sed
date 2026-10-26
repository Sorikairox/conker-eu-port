# P244 CANDSED for projectile_fire: the asm returns a callee's / B(obj, 4)'s leftover v0 (random trials, setups fl77 / fl28),
# no caller reads it (v0use: objfx_gun_fire overwrites; game_981E0's C calls ignore it); the C returns 0 (s32 kept for
# 981E0's K&R declaration). Tested as void so difftest does not compare v0. Line count unchanged.
s/^s32 projectile_fire(/void projectile_fire(/
s/return 0;/return;/
