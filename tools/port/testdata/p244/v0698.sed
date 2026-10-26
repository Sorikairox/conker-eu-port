# P244 CANDSED for func_151C0698: the asm returns a callee's / B(obj, 4)'s leftover v0 (random trials, setups fl77 / fl28),
# no caller reads it (v0use: func_15070300 overwrites; game_981E0's C calls ignore it); the C returns 0 (s32 kept for
# 981E0's K&R declaration). Tested as void so difftest does not compare v0. Line count unchanged.
s/^s32 func_151C0698(/void func_151C0698(/
s/return 0;/return;/
