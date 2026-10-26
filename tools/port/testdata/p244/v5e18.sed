# P244 CANDSED for player_item_action: item_effect_spawn never reads a1 (asm: no $a1 read; C comment "arg1 unused"); the C passes 0,
# the asm leaves a stale a1 -> test with a 1-argument prototype so difftest compares a0 only. Line count unchanged.
s/^u8 \*item_effect_spawn(u8 kind, s32 arg1);/u8 *item_effect_spawn(u8 kind);/
s/item_effect_spawn(\([05]\), 0);/item_effect_spawn(\1);/
