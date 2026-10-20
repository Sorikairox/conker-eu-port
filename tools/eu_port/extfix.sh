#!/bin/bash
# extfix.sh f : loop adding missing extern D_* decls found in include/ or src_eu
cd ~/conker-wt/a && eval "$(tools/eu_port/wt.sh env a)"
f=$1; D=${EF_DIR:-conker/build_port/s59}; cp $D/d/$f.c $D/e/$f.c
for i in 1 2 3 4 5 6 7 8; do
  r=$(tools/eu_port/repair_try.sh $f $D/e/$f.c 2>&1)
  n=$(echo "$r" | grep -o "'[A-Za-z_0-9]*' undefined" | head -1 | tr -d "' " | sed 's/undefined//')
  [ -z "$n" ] && break
  l=$(grep -rhE "^extern [^(]*\b$n\b(\[[^]]*\])?;" include conker/src_eu 2>/dev/null | head -1)
  [ -z "$l" ] && l=$(grep -rhE "^extern [^(]*\b$n\b(\[[^]]*\])?;" conker/build_port/drafts 2>/dev/null | head -1)
  [ -z "$l" ] && { echo "$f NODECL $n"; break; }
  { echo "$l"; cat $D/e/$f.c; } > $D/e/$f.tmp; mv $D/e/$f.tmp $D/e/$f.c
done
echo "$r" | head -2 | cut -c1-200
