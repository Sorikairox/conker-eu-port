#!/bin/bash
# Harness self-test: matched functions must be EQUIV with --self; mutated copies must be DIFFER.
# usage: tools/port/difftest/selftest.sh   (after eval "$(tools/eu_port/wt.sh env <name>)")
R=${CONKER_ROOT:-$HOME/conker}; T=$R/conker/build/difftest_self; mkdir -p $T
ext() { python3 - "$R/conker/$1" "$2" <<'PY'
import sys,re
src=open(sys.argv[1]).read(); f=sys.argv[2]
m=re.search(r'^[^\n;#/]*\b%s\s*\([^;{]*?\)\s*\{'%f,src,re.M); i=m.end()-1; d=0
while True:
    d+= {'{':1,'}':-1}.get(src[i],0); i+=1
    if d==0: break
print(src[m.start():i])
PY
}
pass=0; fail=0
chk() { # expect func file sed-expr
  local exp=$1 f=$2 file=$3 ex=$4 out
  if [ -z "$ex" ]; then out=$($R/tools/port/difftest.sh $f --self --trials ${TRIALS:-32})
  else ext $file $f | sed -e "$ex" > $T/$f.mut.c
       cmp -s <(ext $file $f) $T/$f.mut.c && { echo "BADMUT $f $ex"; fail=$((fail+1)); return; }
       out=$($R/tools/port/difftest.sh $f $T/$f.mut.c --trials ${TRIALS:-32}); fi
  case "$out" in $exp*) pass=$((pass+1)); echo "ok   [$exp] ${ex:-self}  $out";; *) fail=$((fail+1)); echo "FAIL [want $exp] ${ex:-self}  $out";; esac
}
chk EQUIV  func_15103800 src_eu/game_130CB0.c
chk EQUIV  func_15103828 src_eu/game_130CB0.c
chk EQUIV  func_15141564 src_eu/game_16DC80.c
chk EQUIV  func_15141928 src_eu/game_16DC80.c
chk EQUIV  func_15123934 src_eu/game_14FF90.c
chk DIFFER func_15103800 src_eu/game_130CB0.c 's/D_800D9AB0, 8/D_800D9AB0, 6/'
# note: 's/> D_800BE9E4/>= D_800BE9E4/' is a semantically equivalent mutation (x-=x gives 0 too); difftest says EQUIV
chk EQUIV  func_15103828 src_eu/game_130CB0.c 's/D_800D9AB0\[i\] > D_800BE9E4/D_800D9AB0[i] >= D_800BE9E4/'
chk DIFFER func_15103828 src_eu/game_130CB0.c 's/D_800D9AB0\[i\] = 0;/D_800D9AB0[i] = 1;/'
chk DIFFER func_15103828 src_eu/game_130CB0.c 's/i < 4;/i < 3;/'
chk DIFFER func_15141564 src_eu/game_16DC80.c 's/temp->unkC \* D_800BE9A4/temp->unk4 * D_800BE9A4/'
chk DIFFER func_15141564 src_eu/game_16DC80.c 's/return 1;/return 2;/'
chk DIFFER func_15141928 src_eu/game_16DC80.c 's/temp_v0\[0\], temp_v0\[2\]/temp_v0[2], temp_v0[0]/'
chk DIFFER func_15123934 src_eu/game_14FF90.c 's/STK->unk2C\[0\] = arg1;/STK->unk2C[0] = arg2;/'
echo "selftest: $pass ok, $fail failed"; [ $fail = 0 ]
