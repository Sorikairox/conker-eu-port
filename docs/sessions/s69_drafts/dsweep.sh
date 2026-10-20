#!/bin/bash
# shape-D sweep: base draft + blkvar variants per function; prints best
cd ~/conker-wt/a; eval "$(tools/eu_port/wt.sh env a)"
W=conker/build_port/s69/sw; mkdir -p $W
while read f rest; do
  d=""
  for c in tools/decomp-permuter/repair/fresh/$f.c tools/decomp-permuter/repair/$f.c ~/conker/tools/decomp-permuter/repair/$f.c; do [ -s $c ] && { d=$c; break; }; done
  [ -z "$d" ] && { echo "$f NODRAFT"; continue; }
  cp $d $W/$f.c; sed -i '' -E 's/dummy_label_[0-9]+: *;?//' $W/$f.c
  vs=$(python3 tools/eu_port/blkvar.py $W/$f.c $W/$f | head -12)
  r=$(tools/eu_port/m2c/tryall $f $W/$f.c $vs 2>&1)
  base=$(echo "$r" | head -1 | cut -d' ' -f1)
  best=$(echo "$r" | grep -v "^ " | awk '{k=$1; n=k; sub(/^[A-Z]+[+-]?/,"",n); if(k=="OK")n=-1; if(n=="")n=999; print n, $0}' | sort -n | head -1 | cut -d' ' -f2-)
  echo "$f base=$base best=$best"
done
