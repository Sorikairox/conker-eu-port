#!/bin/bash
# usage: gen40.sh [max=40]   fresh m2c drafts (JT=1) of all asm functions <= max insns -> conker/build/k40, screened;
# ranked list "score result func dir" -> tools/decomp-permuter/repair/fresh.txt (score 0=OK, n=DIFFn, 3.5=SIZE+-1)
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
R=${CONKER_ROOT:-$HOME/conker}; M=$R/tools/eu_port/m2c; K=$R/conker/build/k40; max=${1:-40}
rm -rf $K $M/ctx; mkdir -p $K; (cd $M && python3 list.py > all.txt)
JT=1 $M/venv/bin/python3 $M/gen2.py $K 1 $max > $K/gen.log 2>&1
for v in 0 1 2 3 4 5 6 7; do python3 $M/narrow.py $K/v$v $K/n$v >/dev/null 2>&1; done
cp $M/screen.py $R/conker/build/screen.py
for v in $K/v* $K/n*; do docker exec -w /conker/conker ${CONKERDEV:-conkerdev} python3 build/screen.py build/k40/$(basename $v) 8 >/dev/null 2>&1; done
mkdir -p $R/tools/decomp-permuter/repair
for v in $K/v* $K/n*; do sed "s|\$| $v|" $v/screen.txt; done | awk '
 {r=$1; f=$2; if(r=="OK")s=0; else if(r~/^DIFF/)s=substr(r,5)+0; else if(r=="SIZE+1"||r=="SIZE-1")s=3.5; else s=1000;
  if(!(f in b)||s<b[f]){b[f]=s;br[f]=r;bd[f]=$4}}
 END{for(f in b)print b[f],br[f],f,bd[f]}' | sort -n > $R/tools/decomp-permuter/repair/fresh.txt
echo "done $(wc -l < $R/tools/decomp-permuter/repair/fresh.txt) OK $(awk '$1==0' $R/tools/decomp-permuter/repair/fresh.txt | wc -l)"
