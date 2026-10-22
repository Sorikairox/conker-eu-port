#!/bin/bash
# Harness self-test: matched functions must be EQUIV with --self; mutated copies must be DIFFER.
# usage: tools/port/difftest/selftest.sh   (after eval "$(tools/eu_port/wt.sh env <name>)")
. "$(dirname "${BASH_SOURCE[0]}")/../portguard.sh"  # wrong-checkout guard (P7)
R=${CONKER_ROOT:-$HOME/conker}; T=$R/conker/build/difftest_self; mkdir -p $T
ext() { python3 - "$R/conker/$1" "$2" <<'PY'
import sys,re
src=open(sys.argv[1]).read(); f=sys.argv[2]
m=re.search(r'^[A-Za-z_][^\n;#/]*\b%s\s*\([^;{]*?\)\s*\{'%f,src,re.M); i=m.end()-1; d=0
while True:
    d+= {'{':1,'}':-1}.get(src[i],0); i+=1
    if d==0: break
print(src[m.start():i])
PY
}
pass=0; fail=0
C=$R/tools/port/difftest/cases
chkc() { # expect func case-file [sed-expr]: a draft kept in tools/port/difftest/cases
  local exp=$1 f=$2 cf=$C/$2.c ex=$3 out
  if [ -n "$ex" ]; then sed -e "$ex" $cf > $T/$f.mut.c; cmp -s $cf $T/$f.mut.c && { echo "BADMUT $f $ex"; fail=$((fail+1)); return; }; cf=$T/$f.mut.c; fi
  out=$($R/tools/port/difftest.sh $f $cf --trials ${TRIALS:-32})
  case "$out" in $exp*) pass=$((pass+1)); echo "ok   [$exp] case ${ex:-as is}  $out";; *) fail=$((fail+1)); echo "FAIL [want $exp] case ${ex:-as is}  $out";; esac
}
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
# P5: MIPS III sd/ld in the reference (emulated by a code hook)
chkc EQUIV  func_150A7D00
chkc DIFFER func_150A7D00 's/mtx\[15\] = 1;/mtx[15] = 2;/'
chkc DIFFER func_150A7D00 's/i < 16;/i < 15;/'
# P5: branch right after a stubbed call whose delay slot is an FPU store (was UC_ERR_EXCEPTION at 0)
chkc EQUIV  func_151DAE28
chkc DIFFER func_151DAE28 's/arg1, 0x40, \&sp4C/arg1, 0x41, \&sp4C/'
# P5: daddiu (64-bit add feeding an sd)
chkc EQUIV  func_150ADACC
chkc DIFFER func_150ADACC 's/(s64)arg0 + 1/(s64)arg0 + 2/'
# P18: FPRs move through memory (Unicorn 2.0.1 ignores FPR reg_read/reg_write): float args, f0 return
chk EQUIV  func_15048A70 src_eu/game_75E60.c
chk DIFFER func_15048A70 src_eu/game_75E60.c 's/return arg1 - arg0;/return arg0 - arg1;/'
chk DIFFER func_15048A70 src_eu/game_75E60.c 's/arg0 -= 360.0f;/arg0 -= 361.0f;/'
# P18: a candidate's own float literal (TU .rodata) after a null-pointer access (was read as 0: TU_BASE aliased page 0)
chkc EQUIV  func_151B97C4
chkc DIFFER func_151B97C4 's/0.0234f/0.0235f/g'
chkc DIFFER func_151B97C4 's/sinf(temp_f0)/sinf(temp_f2)/'
# P73: func_1501B300's NON_MATCHING block also holds func_1501B640: the candidate went into the dropped #else side
# and src_eu's body was tested instead (every mutant EQUIV). The mutant must be DIFFER.
chk EQUIV  func_1501B300 src_eu/game_eu_48B10.c
chk DIFFER func_1501B300 src_eu/game_eu_48B10.c 's/out\[1\] = negSinPitch \* 127.0f;/out[1] = x * 127.0f;/'
echo "selftest: $pass ok, $fail failed"; [ $fail = 0 ]
