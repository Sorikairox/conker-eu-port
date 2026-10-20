#!/bin/bash
# fixchain.sh <listfile> <outdir>   (s62) run the whole draft-repair chain over fresh m2c drafts and keep the best variant.
# Needs drafts in tools/decomp-permuter/repair/fresh/<f>.c (TYPED=1 gensome.sh <list>). <outdir> must be under conker/ (container mount),
# e.g. conker/build_port/s62/fc. Variants (each screened with screen.py, 8 jobs):
#   v0 = m2cfix (declfix + ARGFIX=1)          v1 = v0 + spdecl + fnptrfix
#   v2 = v1 + vecfix + spinline               v3 = v1 + spstruct      v4 = v2 + spstruct     v5 = v1 + spinline (no vecfix)
# then CERR leftovers of the best get extfix (missing externs) + redeclfix. Result: <outdir>/best/<f>.c, <outdir>/best.txt
# ("score result func variant"), bucket table on stdout.
R=${CONKER_ROOT:-$HOME/conker}; T=$R/tools/eu_port; export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
L=$(realpath $1); O=$R/$2; [ "${2#/}" != "$2" ] && O=$2; D=${CONKERDEV:-conkerdev}
rm -rf $O; mkdir -p $O/best; cd $R
rel=${O#$R/conker/}
scr(){ cp $T/m2c/screen.py $R/conker/build/screen.py; docker exec -w /conker/conker $D python3 build/screen.py $rel/$1 8 >/dev/null 2>&1; }
each(){ # each <cmd-with-IN-OUT> <srcdir> <dstdir>: per-file filter
  mkdir -p $3; for f in $(ls $2 | sed 's/\.c$//'); do eval "${1//IN/$2/$f.c}" >/dev/null 2>&1 || cp $2/$f.c $3/$f.c; [ -f $3/$f.c ] || cp $2/$f.c $3/$f.c; done; }
# v0
python3 $T/m2cfix.py $L $O/v0 >/dev/null 2>&1; [ -d $O/v0 ] || { echo "m2cfix failed"; exit 1; }
# m2cfix wrote screen.txt+ranked.txt in v0 already
mkdir -p $O/s1; for f in $(ls $O/v0 | grep '\.c$' | sed 's/\.c$//'); do
  python3 $T/spdecl.py $O/v0/$f.c $O/s1/$f.c 2>/dev/null || cp $O/v0/$f.c $O/s1/$f.c
  python3 $T/fnptrfix.py $O/s1/$f.c $O/s1/$f.c.t 2>/dev/null && mv $O/s1/$f.c.t $O/s1/$f.c; rm -f $O/s1/$f.c.t; done
cp -r $O/s1 $O/v1
python3 $T/vecfix.py $O/v1 $O/s2a >/dev/null 2>&1; python3 $T/spinline.py $O/s2a $O/v2 >/dev/null 2>&1
python3 $T/spinline.py $O/v1 $O/v5 >/dev/null 2>&1
mkdir -p $O/v3 $O/v4
for f in $(ls $O/v1 | sed 's/\.c$//'); do
  python3 $T/spstruct.py $O/v1/$f.c $O/v3/$f.c >/dev/null 2>&1 || cp $O/v1/$f.c $O/v3/$f.c
  [ -f $O/v2/$f.c ] && { python3 $T/spstruct.py $O/v2/$f.c $O/v4/$f.c >/dev/null 2>&1 || cp $O/v2/$f.c $O/v4/$f.c; }; done
for v in v1 v2 v3 v4 v5; do [ -d $O/$v ] && scr $v; done
for v in v0 v1 v2 v3 v4 v5; do [ -f $O/$v/screen.txt ] && sed "s|\$| $v|" $O/v*/screen.txt >/dev/null; done
for v in v0 v1 v2 v3 v4 v5; do [ -f $O/$v/screen.txt ] && awk -v v=$v '{print $1,$2,v}' $O/$v/screen.txt; done | awk '
 function sc(r){ if(r=="OK")return 0; if(r~/^DIFF/)return substr(r,5)+0; if(r~/^SIZE/){n=substr(r,6)+0; if(n<0)n=-n; return 3.5+n/100} return 1000 }
 {s=sc($1); if(!($2 in b)||s<b[$2]){b[$2]=s;r[$2]=$1;v[$2]=$3}}
 END{for(f in b)print b[f],r[f],f,v[f]}' | sort -n > $O/best.txt
while read s r f v; do cp $O/$v/$f.c $O/best/$f.c; done < $O/best.txt
echo "before(v0):"; awk '{print $1}' $O/v0/screen.txt | sed 's/[0-9]*$//;s/SIZE[+-]/SIZE/' | sort | uniq -c | tr '\n' ' '; echo
# CERR leftovers: extfix + redeclfix (sequential, repair_try)
for f in $(awk '$2~/CERR/{print $3}' $O/best.txt); do
  cp $O/best/$f.c $O/cx_$f.c
  for i in 1 2 3 4 5 6; do
    r=$($T/repair_try.sh $f $O/cx_$f.c 2>&1); n=$(echo "$r" | grep -o "'[A-Za-z_0-9]*' undefined" | head -1 | tr -d "' " | sed 's/undefined//')
    [ -z "$n" ] && break
    l=$(grep -rhE "^extern [^(]*\b$n\b(\[[^]]*\])?;" $R/include $R/conker/src_eu 2>/dev/null | head -1)
    [ -z "$l" ] && break
    { echo "$l"; cat $O/cx_$f.c; } > $O/cx_$f.t; mv $O/cx_$f.t $O/cx_$f.c
  done
  python3 $T/redeclfix.py $f $O/cx_$f.c $O/cy_$f.c >/dev/null 2>&1 || cp $O/cx_$f.c $O/cy_$f.c
  res=$($T/repair_try.sh $f $O/cy_$f.c 2>&1 | head -1 | awk '{print $2}')
  echo "$f ${res:-CERR}" >> $O/cerr_after.txt
  case "$res" in CERR*|"") ;; *) cp $O/cy_$f.c $O/best/$f.c;; esac
done
awk 'NR==FNR{a[$1]=$2;next} ($3 in a)&&a[$3]!~/^CERR/{$2=a[$3];$1=($2=="OK"?0:($2~/^DIFF/?substr($2,5)+0:3.5+1))} {print}' $O/cerr_after.txt $O/best.txt | sort -n > $O/best2.txt; mv $O/best2.txt $O/best.txt
echo "after (best per function):"; awk '{r=$2; sub(/[0-9]+$/,"",r); if(r~/^DIFF/){}; print r}' $O/best.txt | sort | uniq -c | tr '\n' ' '; echo
awk '$2=="OK"||$2~/^DIFF/{print $2,$3,$4}' $O/best.txt | sort -k1.5n | head -30
