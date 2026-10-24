# P244 CANDSED for func_15065E18: func_150DC2F0 never reads a1 (asm: no $a1 read; C comment "arg1 unused"); the C passes 0,
# the asm leaves a stale a1 -> test with a 1-argument prototype so difftest compares a0 only. Line count unchanged.
s/^u8 \*func_150DC2F0(u8 kind, s32 arg1);/u8 *func_150DC2F0(u8 kind);/
s/func_150DC2F0(\([05]\), 0);/func_150DC2F0(\1);/
