#!/bin/bash
# usage: gensome.sh <func>...   regenerate m2c drafts (JT=1) for just these functions (gen40.sh wipes build/k40; a resplit wipes it too),
# narrow + screen, copy the best draft per function into repair/fresh/ and print "result func".
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
R=~/conker; M=$R/tools/eu_port/m2c; K=$R/conker/build/ks; F=$R/tools/decomp-permuter/repair/fresh
rm -rf $K; mkdir -p $K $F; for f in "$@"; do echo $f; done > $K/only.txt
ONLY=$K/only.txt JT=1 $M/venv/bin/python3 $M/gen2.py $K 1 400 > $K/gen.log 2>&1
for v in 0 1 2 3 4 5 6 7; do [ -d $K/v$v ] && python3 $M/narrow.py $K/v$v $K/n$v >/dev/null 2>&1; done
cp $M/screen.py $R/conker/build/screen.py
for v in $K/v* $K/n*; do [ -d $v ] && docker exec -w /conker/conker conkerdev python3 build/screen.py build/ks/$(basename $v) 8 >/dev/null 2>&1; done
for v in $K/v* $K/n*; do [ -f $v/screen.txt ] && sed "s|\$| $v|" $v/screen.txt; done | awk '
 {r=$1; f=$2; if(r=="OK")s=0; else if(r~/^DIFF/)s=substr(r,5)+0; else if(r=="SIZE+1"||r=="SIZE-1")s=3.5; else s=1000;
  if(!(f in b)||s<b[f]){b[f]=s;br[f]=r;bd[f]=$4}}
 END{for(f in b)print br[f],f,bd[f]}' | while read r f d; do cp $d/$f.c /Users/sorikairo/conker/tools/decomp-permuter/repair/fresh/$f.c 2>/dev/null; echo "$r $f"; done
