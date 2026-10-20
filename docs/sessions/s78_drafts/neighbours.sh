#!/bin/zsh
# per file in slice touched since bcbf973: matched/unmatched counts and asm neighbour sizes
cd ~/conker
for f in $(git log --name-only --format= bcbf973..HEAD -- conker/src_eu | sort -u); do
  b=$(basename $f .c); hex=${b##*_}
  [[ $f == *init* || $f == *libultra* || $f == *debug* ]] && continue
  (( 16#$hex >= 16#130000 )) && continue
  [[ -f $f ]] || continue
  n=$(grep -c GLOBAL_ASM $f)
  (( n == 0 )) && continue
  m=$(grep -cE '^[a-zA-Z].*\) *\{ *$|^\{' $f)
  sizes=""
  for a in $(grep GLOBAL_ASM $f | sed -E 's/.*"(.*)".*/\1/'); do
    fn=$(basename $a .s); s=$(find conker/asm -name "$fn.s" | head -1)
    [[ -n $s ]] && sizes="$sizes $fn:$(grep -c '^\s*/\*' $s)"
  done
  echo "$b C~$m asm=$n |$sizes"
done
