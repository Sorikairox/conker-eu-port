#!/bin/bash
# P106: mutants of the model-checked natives (run in the container from /conker/conker): each must DIFFER
i=0
while IFS='|' read -r file from to; do
  [ -z "$file" ] && continue; i=$((i+1)); d=/tmp/p106mut$i; rm -rf $d; mkdir -p $d; cp src_eu/game_DAE50.c src_eu/game_eu_DB7E0.c $d/
  grep -qF "$from" $d/$file || { echo "SED ERROR $i: $from"; continue; }
  python3 -c "import sys;p=sys.argv[1];s=open(p).read();open(p,'w').write(s.replace(sys.argv[2],sys.argv[3],1))" $d/$file "$from" "$to"
  r=$(python3 /conker/docs/port/sessions/p106/ada20/check.py $d 2>&1 | grep -c DIFFER)
  echo "mutant $i ($file: $from -> $to): $([ $r -gt 0 ] && echo killed || echo SURVIVED)"
done <<'M'
game_DAE50.c|x = ((t >> 20) & 0xFFF) ^ t;|x = ((t >> 21) & 0xFFF) ^ t;
game_DAE50.c|t ^= (x << 44) >> 32;|t ^= (x << 45) >> 32;
game_DAE50.c|return (s32) x;|return (s32) (x >> 32);
game_eu_DB7E0.c|return (n == 0) ? r : r % n;|return (n == 0) ? 0 : r % n;
game_eu_DB7E0.c|return (n == 0) ? r : r % n;|return (n == 0) ? r : (s32) r % (s32) n;
game_eu_DB7E0.c|(s64) args[0] * args[1]) >> 16);|(s64) args[0] * args[1]) >> 15);
game_eu_DB7E0.c|return (s32) ((u64) ((s64) args[0] * args[1]) >> 16);|return (s32) ((u32) args[0] * (u32) args[1] >> 16);
game_eu_DB7E0.c|return (n < 0) ? 1 : -1;|return 0;
game_eu_DB7E0.c|s64 n = (s64) args[0] << 16;|s64 n = (s64) (args[0] << 16);
game_eu_DB7E0.c|if (t < 0 && next >= 0) {|if (t < 0 && next > 0) {
game_eu_DB7E0.c|if (t >= 2 && next < 2) {|if (t > 2 && next < 2) {
game_eu_DB7E0.c|if (t == 1) {|if (t == 2) {
M
