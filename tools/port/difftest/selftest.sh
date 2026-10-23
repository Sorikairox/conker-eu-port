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
# P71: a call statement with a comma inside a macro argument (`func_100043B4((s32 *) ATT_W(rec, 0x28), 4);`) is not
# a 3-argument prototype: the declared 2-argument func_100043B4 must not compare the scratch a2 (was a false DIFFER)
chkc EQUIV  func_15030448
chkc DIFFER func_15030448 's/ATT_W(rec, 0x2C), 4);/ATT_W(rec, 0x2C), 5);/'
# P80: a converted function whose #else holds a note line before the pragma (game_981E0.c "// TBD ..."): the candidate
# used to be dropped (the old NM C was tested, every mutant survived); now spliced, and a dropped candidate is an ERROR
chkc EQUIV  func_1506EF5C
chkc DIFFER func_1506EF5C 's/= 0xFFFF;/= 0xFFFE;/'
# P89: a stub-returned pointer in the harness stack range (0x80660000, below every frame) is not a frame address: a
# +0x14 -> +0x10 mutant on it must DIFFER (P86: same_val normalised every 0x806xxxxx value to 'STK', the mutant survived).
# DIFFTEST_STK_OLD=1 restores the old rule; the case then shows the hole (EQUIV).
AB94="DIFFTEST_EXACT=* DIFFTEST_ARG=0=4002,1=2,2=1234,3=77,4=0 DIFFTEST_POKE=800C3A08=01000509,800C3A10=80520000,800C3A14=80520400,800C3A18=80520800,800C3A1C=80520C00,800C3D78=80530000,800C3D7C=80532000,800C3D80=80534000,800C3D84=80536000,800C40A8=00000000,80520010=00021211,80520014=22334455 DIFFTEST_RET=150842F8=80660000,15114F2C=80470000,15024910=0,150268BC=0,15029EA8=0"
chkce() { # expect func "ENV=.. ..." [sed-expr]
  local exp=$1 f=$2 ev=$3 ex=$4 cf=$C/$2.c out
  if [ -n "$ex" ]; then sed -e "$ex" $cf > $T/$f.mut.c; cmp -s $cf $T/$f.mut.c && { echo "BADMUT $f $ex"; fail=$((fail+1)); return; }; cf=$T/$f.mut.c; fi
  out=$(set -f; env $ev $R/tools/port/difftest.sh $f $cf --trials ${TRIALS:-8})
  case "$out" in $exp*) pass=$((pass+1)); echo "ok   [$exp] env case ${ex:-as is}  $out";; *) fail=$((fail+1)); echo "FAIL [want $exp] env case ${ex:-as is}  $out";; esac
}
chkce EQUIV  func_1502AB94 "$AB94"
chkce DIFFER func_1502AB94 "$AB94" 's/data = (u8 \*) obj + 0x14;/data = (u8 *) obj + 0x10;/'
chkce EQUIV  func_1502AB94 "$AB94 DIFFTEST_STK_OLD=1" 's/data = (u8 \*) obj + 0x14;/data = (u8 *) obj + 0x10;/'
# P90: stack arguments past sp+0x3C (args 16+) were never captured: func_150268BC's func_1516DF0C call has 49 arguments;
# a player -> track mutant of argument 44 (sp+0xB0) must DIFFER; DIFFTEST_STKW_OLD=1 (old 12-word window) shows the hole.
DF0C="DIFFTEST_EXACT=* DIFFTEST_ARG=0=80480000,1=2,2=99,3=10,4=1,5=804A0000,6=804C0000,7=804B0000,8=37 DIFFTEST_POKE=800C395C=80490000,800C3A04=804D2000,800C3D08=804D1000,800C3E00=804D0000,80480000=05070011,80480004=00030150,80490088=40B00000,8049008C=40D00000,80490090=C0F00000,80490094=41000000,80490098=41100000,804900A0=41300000,804900A4=41400000,804900A8=41500000,804900C0=41600000,804A0004=58123456,804A0014=42C90000,804A0018=43488000,804A001C=C3964000,804B0000=41280000,804B0004=41A20000,804B0008=C1F60000,804D1000=00050006,804D1004=00070000 DIFFTEST_RET=15023C60=40,150ADF00=12345,151905AC=0"
chkce EQUIV  func_150268BC "$DF0C"
chkce DIFFER func_150268BC "$DF0C" 's/0, 0, player, 0, 0, flag, 0);/0, 0, track, 0, 0, flag, 0);/'
chkce EQUIV  func_150268BC "$DF0C DIFFTEST_STKW_OLD=1" 's/0, 0, player, 0, 0, flag, 0);/0, 0, track, 0, 0, flag, 0);/'
# P93: knob notes. P90 poked D_800C3958 at its US address 0x800C395C (EU 0x800C3D78): the 0x33 record pokes never reached
# the code and the rec + 0x18 -> 0x1C mutant survived. difftest now appends [POKE unread: ...] for poke words the
# reference never reads (trials 0-1) and [knob callee never called: ...] for RET/RETF/OUT*/ARGMEM keys never called.
S33="DIFFTEST_EXACT=* DIFFTEST_ARG=0=80480000,1=2,2=99,3=10,4=1,5=804A0000,6=804C0000,7=804B0000,8=37 DIFFTEST_POKE=800C395C=80490000,800C3A04=804D2000,800C3D08=804D1000,800C3E00=804D0000,80480000=05070033,80480004=00030150,80490088=40B00000,8049008C=40D00000,80490090=C0F00000,80490094=41000000,80490098=41100000,804900A0=41300000,804900A4=41400000,804900A8=41500000,804900C0=41600000,804A0004=58123456,804A0014=42C90000,804A0018=43488000,804A001C=C3964000,804B0000=41280000,804B0004=41A20000,804B0008=C1F60000,804D1000=00050006,804D1004=00070000 DIFFTEST_RET=15023C60=40,150ADF00=12345,151905AC=0 DIFFTEST_RETF=150ADF48=3EC00000,15048D30=3F000000,15048CA0=BF400000"
M33='s/O_F32(r, 0x18) \* 0.1f + 1.0f, scale/O_F32(r, 0x1C) * 0.1f + 1.0f, scale/'
chkce "EQUIV*POKE unread: 800C395C"  func_150268BC "$S33"   # (the mutant below survives P90's TR=4 with the US address)
chkce DIFFER func_150268BC "${S33/800C395C=/800C3D7C=}" "$M33"
# P93: a callee declared only in include/functions.h had an unknown arity: stack args 16+ (sp+0x40..) were never compared
# (func_150FD554 -> func_1513D594, 17 args). Prototypes with > 16 args are now taken from functions.h.
FD554="DIFFTEST_EXACT=* DIFFTEST_ARG=0=80450000 DIFFTEST_POKE=80450004=000000FF DIFFTEST_RET=15046F70=1,1513D860=80460000"
chkce EQUIV  func_150FD554 "$FD554"
chkce DIFFER func_150FD554 "$FD554" 's/0U, 0, (u8) (s32) arg1, arg2);/0U, 0, (u8) (s32) arg1, arg2 + 1);/'
chkce "EQUIV*knob callee never called: RET 1513D2F0" func_150FD554 "${FD554/1513D860=/1513D2F0=}"
# P95: stack argument words 12+ (arguments 16+) were never set: func_15035220 (19 args) read leftovers for alpha (16) /
# fixed (17) / tofixed (18) and DIFFTEST_ARG 16..18 were ignored, so every alpha mutant survived. Now set when needed.
S5220="DIFFTEST_EXACT=* DIFFTEST_ARG=0=80450000,1=804B0000,2=1,3=80460000,4=80470000,5=2,6=42C80000,7=42480000,8=43480000,9=40E00000,10=3F000000,11=42F00000,12=43160000,13=43520000,14=41A00000,15=43960000,16=43480000,17=0,18=0 DIFFTEST_POKE=8045009C=00000001,804501D4=80455550,80460000=3F800000,80460004=3E800000,80460008=00000000,8046000C=40400000,80460010=3F800000,80460014=3E800000,80460018=00000000,8046001C=40400000,80460020=3F800000,80460024=3E800000,80460028=00000000,8046002C=40400000,80460030=41200000,80460034=42700000,80460038=C1F00000,8046003C=40000000,80460040=3F800000,80460044=3E800000,80460048=00000000,8046004C=40400000,80460050=3F800000,80460054=3E800000,80460058=00000000,8046005C=40400000,80460060=3F800000,80460064=3E800000,80460068=00000000,8046006C=40400000,80460070=41300000,80460074=42700000,80460078=C1F00000,8046007C=40000000 DIFFTEST_RET=150ADE40=64"
chkce EQUIV  func_15035220 "$S5220"
chkce DIFFER func_15035220 "$S5220" 's/(dist - g) \/ (h - g)/(dist - g) \/ (h - g + 1.0f)/'
# P100: DIFFTEST_OUTA/OUTB/OUTW target '@ADDR' (absolute address): func_1517C11C marks the voices it hears in globals;
# without the knob every "flag ignored" mutant of func_1517E3CC survived.
S7E3CC="DIFFTEST_EXACT=* DIFFTEST_POKE=800DE150=1,800DC420=80480000,800DD8A8=0,800DDEC8=1000,800DDECC=01000000,800DD910=1,800DDED8=1001,800DDEDC=01000000,800DD978=1,800DDEE8=1002,800DDEEC=01000000,800DD9E0=0,800DDEF8=1003,800DDEFC=01000000,800DDA48=1,800DDF08=1004,800DDF0C=01000000,800DDAB0=1,800DDF18=1005,800DDF1C=01000000,800DDB18=0,800DDF28=1006,800DDF2C=01000000,800DDB80=1,800DDF38=1007,800DDF3C=01000000,800DDBE8=1,800DDF48=1008,800DDF4C=01000000,800DDC50=0,800DDF58=1009,800DDF5C=01000000,800DDCB8=1,800DDF68=100A,800DDF6C=01000000,800DDD20=1,800DDF78=100B,800DDF7C=01000000,800DDD88=0,800DDF88=100C,800DDF8C=01000000,800DDDF0=1,800DDF98=100D,800DDF9C=01000000,800DDE58=1,800DDFA8=100E,800DDFAC=01000000"
chkce EQUIV  func_1517E3CC "$S7E3CC DIFFTEST_OUTB=1517C11C=@800DDECC:01/@800DDEFC:01/@800DDF5C:01/@800DDFAC:01"
chkce DIFFER func_1517E3CC "$S7E3CC DIFFTEST_OUTB=1517C11C=@800DDECC:01/@800DDEFC:01/@800DDF5C:01/@800DDFAC:01" 's/ \&\& voices\[i \* 0x10 + 0xC\] == 0) {/) {/'
chkce EQUIV  func_1517E3CC "$S7E3CC" 's/ \&\& voices\[i \* 0x10 + 0xC\] == 0) {/) {/'
# P100: DIFFTEST_ARGMEM "N+OFF:LEN" (bytes from aN + OFF): func_151DA6F8's spawn block has 2 uninitialised pad bytes
# at +0x16, so the owner word at +0x18 is compared from an offset.
SDA6F8="DIFFTEST_EXACT=* DIFFTEST_ARG=0=80460000,1=80460010,2=3F400000,3=5,4=C8,5=40A00000,6=1234,7=0,8=3F800000,9=40000000,10=0,11=2,12=77,13=FFF0,14=12,15=80490000,16=1,17=9  DIFFTEST_POKE=80460000=1,80460004=2,80460008=3,80460010=41200000,80460014=C1200000,80460018=3F000000,80470098=80480000  DIFFTEST_RET=15148310=80470000"
chkce EQUIV  func_151DA6F8 "$SDA6F8 DIFFTEST_ARGMEM=15148310=0+18:4"
chkce DIFFER func_151DA6F8 "$SDA6F8 DIFFTEST_ARGMEM=15148310=0+18:4" 's/sb.owner = owner;/sb.owner = argC;/'
# P100: a callee declared only in a header (sinf: include/libc/math.h): the call statement `sinf(temp->unk8)` was
# read as an int-parameter prototype, so f12 was never compared (port-b P96: a `rad = ang` mutant survived).
chk DIFFER func_15141564 src_eu/game_16DC80.c 's/sinf(temp->unk8)/sinf(temp->unk4)/'
# P112: an indirect call whose argument register is set in an earlier block (event native 6: lw a1 before the branch
# to the shared jalr tail) - a1 was not compared, the P106 args[1] -> args[0] mutant survived. Now every arg register
# the reference wrote since the previous call counts for a jalr of an unknown function.
AE60C="DIFFTEST_ROMDATA=1 DIFFTEST_EXACT=* DIFFTEST_REFLEN=104 DIFFTEST_SIGNORE=7 DIFFTEST_ARG=0=80490000,1=6,2=80491000 DIFFTEST_POKE=80490000=1001,80490004=1234"
chkce EQUIV  func_150AE60C "$AE60C"
chkce DIFFER func_150AE60C "$AE60C" 's/args\[1\], args)/args[0], args)/'
# P132: func_151DE100 time limit (game_pause_update). DE: D_80082FA0 (.game_data 80083330) = 1, D_800BE616 = 1,
# D_800E1013 = 3, D_80090118 = 3000, D_800BEA08 = 0x20, D_800BEAC0 / AC1 = 0, D_8009029C = 0.
DE="DIFFTEST_EXACT=* DIFFTEST_POKE=80083330=1,800BEA34=100,800E1010=3,800BEEE0=0,80090118=BB8,8009029C=0,800BEE28=20"
chkce EQUIV  func_151DE100 "$DE"
# varargs stack args behind IDO's division trap checks (secs / 60, secs % 60 stored before the `bnez; break 7`
# guard): the call-site scan goes through the guards since P132; DIFFTEST_TRAPSCAN_OLD=1 (old scan) misses it.
chkce DIFFER func_151DE100 "$DE" 's/secs = D_80090118 \/ 50;/secs = D_80090118 \/ 60;/'
chkce EQUIV  func_151DE100 "$DE DIFFTEST_TRAPSCAN_OLD=1" 's/secs = D_80090118 \/ 50;/secs = D_80090118 \/ 60;/'
# a POKE wins over the ROM .data image (ROM D_80082FA0 = 0): with DIFFTEST_ROMDATA=1 every trial loads the image;
# y = 100 needs D_80082FA0 > 0, so the mutant dies only if the poke holds. DIFFTEST_POKE_OLD=1 = pre-P132 order.
chkce DIFFER func_151DE100 "$DE DIFFTEST_ROMDATA=1" 's/y = 100;/y = 101;/'
chkce EQUIV  func_151DE100 "$DE DIFFTEST_ROMDATA=1 DIFFTEST_POKE_OLD=1" 's/y = 100;/y = 101;/'
# [POKE unread] comes from decoded loads since P132 (Unicorn's read hook missed `lbu D_800BE616` at 800BEA36)
out=$(set -f; env $DE $R/tools/port/difftest.sh func_151DE100 $C/func_151DE100.c --trials 4)
case "$out" in *POKE\ unread*) fail=$((fail+1)); echo "FAIL [want no POKE unread] $out";; EQUIV*) pass=$((pass+1)); echo "ok   [no POKE unread] $out";; *) fail=$((fail+1)); echo "FAIL $out";; esac
echo "selftest: $pass ok, $fail failed"; [ $fail = 0 ]
