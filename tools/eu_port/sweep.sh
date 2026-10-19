#!/bin/bash
_top=$(git rev-parse --show-toplevel 2>/dev/null); if [ -n "$_top" ] && [ "$_top" != "${CONKER_ROOT:-$HOME/conker}" ]; then echo "refusing: cwd repo $_top != CONKER_ROOT ${CONKER_ROOT:-$HOME/conker} (run: eval \"\$(tools/eu_port/wt.sh env <name>)\")" >&2; exit 3; fi
# Near-miss sweep: fresh m2c drafts for every GLOBAL_ASM function up to MAX instructions, screened,
# then decomp-permuter on the close ones. Host side, repo root; uses the container conkerdev.
#
# usage: tools/eu_port/sweep.sh gen   [max=200]        drafts + screen + candidate list
#        tools/eu_port/sweep.sh perm  <list> [secs=300] [streams=3] [jobs=3]
#        tools/eu_port/sweep.sh collect | apply         list / apply every confirmed match.c
#
# Work dir S=tools/decomp-permuter/sweep (gitignored, survives verify_all.sh):
#   gen:  conker/build/k/{v0..v7,n0..n7} (gen2.py with JT=1 + narrow.py), screened; OK drafts merged to
#         $S/ok/ (copy to conker/build/... and run apply.py); best variant per function -> $S/drafts/<f>.c;
#         $S/best.txt (best result per function), $S/cand.txt ("func draft" lines, SIZE+-1 and DIFF1-5,
#         closest first).
#   perm: splits the list round-robin into <streams> lists, runs permute.sh -l on each in parallel
#         (-j<jobs>), one summary line per function in $S/perm_<listname>.txt.
#   collect: "func path/match.c" for every nm/<func>/match.c (screened OK by try).
#   apply: apply.py on every match.c whose function is still GLOBAL_ASM (ACCEPT/REJECT lines), then
#          needsyms.py --apply on the accepted ones (auto symbols the new C names).
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
R=${CONKER_ROOT:-$HOME/conker}; S=$R/tools/decomp-permuter/sweep; M=$R/tools/eu_port/m2c; K=$R/conker/build/k
mkdir -p $S
case $1 in
gen)
  max=${2:-200}
  rm -rf $K $M/ctx; mkdir -p $K
  (cd $M && python3 list.py > all.txt)
  JT=1 $M/venv/bin/python3 $M/gen2.py $K 1 $max > $S/gen.log 2>&1
  for v in 0 1 2 3 4 5 6 7; do python3 $M/narrow.py $K/v$v $K/n$v >/dev/null 2>&1; done
  cp $M/screen.py $R/conker/build/screen.py
  for v in $K/v* $K/n*; do
    docker exec -w /conker/conker ${CONKERDEV:-conkerdev} python3 build/screen.py build/k/$(basename $v) 8 >/dev/null 2>&1
  done
  rm -rf $S/ok $S/drafts; mkdir -p $S/drafts
  (cd $R/conker && python3 $M/merge.py $S/ok $K/v* $K/n* >/dev/null 2>&1)
  # best per function: OK=0, DIFFn=n, SIZE+-1 = 3 (ranked between DIFF2 and DIFF3), else skip
  for v in $K/v* $K/n*; do sed "s|\$| $v|" $v/screen.txt; done | awk '
    {r=$1; f=$2; if(r=="OK")s=0; else if(r~/^DIFF/)s=substr(r,5)+0; else if(r=="SIZE+1"||r=="SIZE-1")s=3.5; else s=1000;
     if(!(f in b)||s<b[f]){b[f]=s;br[f]=r;bd[f]=$4}}
    END{for(f in b)print b[f],br[f],f,bd[f]}' | sort -n > $S/best.txt
  awk '$1>0 && $1<=5' $S/best.txt | while read -r s r f d; do cp $d/$f.c $S/drafts/$f.c; echo "$f $S/drafts/$f.c"; done > $S/cand.txt
  echo "functions $(wc -l < $S/best.txt)  OK $(awk '$1==0' $S/best.txt | wc -l)  candidates $(wc -l < $S/cand.txt)"
  awk '$1>0&&$1<=5{print $2}' $S/best.txt | sort | uniq -c | tr '\n' ' '; echo
  ;;
perm)
  list=$2; secs=${3:-300}; n=${4:-3}; jobs=${5:-3}; name=$(basename $list .txt)
  rm -f $S/${name}_s*.lst
  awk -v n=$n -v p=$S/${name}_s '{print > (p (NR-1)%n ".lst")}' $list
  for i in $(seq 0 $((n-1))); do
    [ -f $S/${name}_s$i.lst ] && $R/tools/eu_port/permute.sh -l $S/${name}_s$i.lst $secs $jobs > $S/perm_${name}_$i.txt 2>&1 &
  done
  wait
  cat $S/perm_${name}_*.txt > $S/perm_$name.txt
  echo "$(wc -l < $S/perm_$name.txt) run, $(grep -c 'try=OK' $S/perm_$name.txt) OK"
  ;;
collect)
  for m in $R/tools/decomp-permuter/nm/*/match.c; do [ -f "$m" ] && echo "$(basename $(dirname $m)) $m"; done
  ;;
apply)
  # every match.c of a function that is still GLOBAL_ASM -> conker/build/permok -> apply.py
  A=$R/conker/build/permok; rm -rf $A; mkdir -p $A
  for m in $R/tools/decomp-permuter/nm/*/match.c; do
    [ -f "$m" ] || continue; f=$(basename $(dirname $m))
    src=$(grep -rl --include="*.c" "GLOBAL_ASM(\"[^\"]*/$f\.s\")" $R/conker/src_eu 2>/dev/null | head -1)
    [ -n "$src" ] || continue
    grep -v '^// PERMUTER CHANGED' $m > $A/$f.c; echo "OK $f ${src#$R/conker/}" >> $A/screen.txt
  done
  [ -f $A/screen.txt ] || { echo "nothing to apply"; exit 0; }
  docker exec -w /conker/conker ${CONKERDEV:-conkerdev} python3 ../tools/eu_port/m2c/apply.py build/permok 2>&1 | grep -E 'ACCEPT|REJECT' | tee $A/result.txt
  python3 $R/tools/eu_port/needsyms.py --apply $(awk '$1=="ACCEPT"{print $2}' $A/result.txt)
  ;;
*) sed -n '2,19p' $0 ;;
esac
