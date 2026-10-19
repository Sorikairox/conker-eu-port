#!/bin/bash
# usage: fi_ab.sh <listfile> <tag>   (s54) A/B-measure typed m2c context: drafts for the functions in <listfile> WITHOUT (old header + ctx/) and WITH
# (current header + ctx_typed/ + struct127 * param hints from fieldinfer) typed context, same pipeline (gensome.sh -> m2cfix.py with ARGFIX=1).
# Needs OLDHDR (default conker/build_port/s54/structs.h.orig) = struct127 header BEFORE fieldinfer --patch-header. Leaves the current header in place.
# Output: conker/build_port/s54/<tag>/{base,typed}/ranked.txt + a bucket table.
R=${CONKER_ROOT:-$HOME/conker}; T=$R/tools/eu_port; H=$R/conker/include/structs.h; OLD=${OLDHDR:-$R/conker/build_port/s54/structs.h.orig}
L=$1; TAG=$2; O=$R/conker/build_port/s54/$TAG; mkdir -p $O; cp $H $O/structs.h.new
trap 'cp $O/structs.h.new $H' EXIT
for mode in ${MODES:-base typed}; do
  if [ $mode = base ]; then cp $OLD $H; unset TYPED; else cp $O/structs.h.new $H; export TYPED=1; fi
  rm -rf $O/$mode; mkdir -p $O/$mode
  $T/gensome.sh $(cat $L) > $O/$mode/gensome.out 2>&1
  mkdir -p $O/$mode/fresh; for f in $(cat $L); do cp $R/tools/decomp-permuter/repair/fresh/$f.c $O/$mode/fresh/ 2>/dev/null; done
  ARGFIX=1 python3 $T/m2cfix.py $L $R/conker/build/dfx_${TAG}_$mode > $O/$mode/m2cfix.out 2>&1
  cp $R/conker/build/dfx_${TAG}_$mode/ranked.txt $O/$mode/ranked.txt 2>/dev/null
done
unset TYPED
python3 - $O <<'PY'
import sys,re,collections
O=sys.argv[1]; res={}
def bucket(r):
    if r=='OK': return '0 OK'
    m=re.match(r'DIFF(\d+)',r)
    if m:
        n=int(m.group(1)); return '1 DIFF<=3' if n<=3 else '2 DIFF4-8' if n<=8 else '3 DIFF9-15' if n<=15 else '4 DIFF16+'
    m=re.match(r'SIZE([+-])(\d+)',r)
    if m: return '5 SIZE+-1..3' if int(m.group(2))<=3 else '6 SIZE+-4+'
    return '7 CERR/other'
for mode in ('base','typed'):
    d={}
    for l in open(O+'/%s/ranked.txt'%mode):
        t=l.split()
        if len(t)>=3: d[t[2]]=t[1]
    res[mode]=d
fs=sorted(set(res['base'])|set(res['typed']))
c={m:collections.Counter(bucket(res[m].get(f,'CERR')) for f in fs) for m in res}
print('%-14s %6s %6s'%('bucket','base','typed'))
for b in sorted(set(c['base'])|set(c['typed'])): print('%-14s %6d %6d'%(b,c['base'][b],c['typed'][b]))
print('n=%d'%len(fs))
imp=[(f,res['base'].get(f,'CERR'),res['typed'].get(f,'CERR')) for f in fs if bucket(res['typed'].get(f,'CERR'))<bucket(res['base'].get(f,'CERR'))]
open(O+'/improved.txt','w').write(''.join('%s %s -> %s\n'%x for x in imp))
print('improved',len(imp),'worse',sum(1 for f in fs if bucket(res['typed'].get(f,'CERR'))>bucket(res['base'].get(f,'CERR'))))
PY
