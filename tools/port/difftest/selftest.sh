#!/bin/bash
# Harness self-test: matched functions must be EQUIV with --self; mutated copies must be DIFFER.
# usage: tools/port/difftest/selftest.sh   (after eval "$(tools/eu_port/wt.sh env <name>)")
. "$(dirname "${BASH_SOURCE[0]}")/../portguard.sh"  # wrong-checkout guard (P7)
R=${CONKER_ROOT:-$HOME/conker}; T=$R/conker/build/difftest_self; mkdir -p $T
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
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
# P260 preflight: name the environment causes that turned cases red before (P233 unpinned Unicorn: faults at pc 0 next
# to FPU code; P260 stale bind-mount view after a Docker restart: re-used mutant paths compiled truncated -> CERR).
pf=$(docker exec -w /conker/conker ${CONKERDEV:-conkerdev} python3 -c "import sys; sys.path.insert(0, '../port_work/pyuc201'); import unicorn; print(unicorn.__version__)" 2>&1 | tail -1)
case "$pf" in 2.0.1*) echo "preflight: unicorn $pf (pinned port_work/pyuc201)";; *) echo "FAIL preflight: unicorn '$pf', want the pinned 2.0.1 in port_work/pyuc201 (orchestrator.md: pip3 install --target /conker/port_work/pyuc201 unicorn==2.0.1.post1)"; fail=$((fail+1));; esac
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
# P246: DIFFTEST_WLOG=1 (no LO-HI range) raised IndexError in every trial (WLOG[1] of a 1-tuple), so no trial ran; it
# now means the whole range and the result is unchanged (WLOG_T=99: no trial logs, so the result line stays first; the
# old IndexError came before the trial check, so this still catches it).
chkce EQUIV  func_1502AB94 "$AB94 DIFFTEST_WLOG=1 DIFFTEST_WLOG_T=99"
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
# P134: a callee declared only in a header (cosf in gu.h) takes its arity / float slots from there: a0 (written at the
# call site, &D_800CC298) is not an argument of cosf(float). DIFFTEST_HDRSLOT_OLD=1 = pre-P134 (false DIFFER on a0).
chkce EQUIV  func_150F1F80 "DIFFTEST_TRIALS_UNUSED=1"
# P234: the included-header prototypes (gu.h `cosf`) now come first, so HDRSLOT_OLD alone has no effect: the P134
# false DIFFER needs DIFFTEST_INCHDR_OLD=1 too
chkce DIFFER func_150F1F80 "DIFFTEST_HDRSLOT_OLD=1 DIFFTEST_INCHDR_OLD=1"
chkce EQUIV  func_150F1F80 "DIFFTEST_HDRSLOT_OLD=1"
chkce DIFFER func_150F1F80 "DIFFTEST_TRIALS_UNUSED=1" 's/0.35000002f/0.35f/'
# P176: a stub on the last word of a page (func_151CFFFC at 0x151CFFFC): its delay slot runs as a separate Unicorn
# block that was taken for a second call (both sides faulted at 0 -> UNSURE). Type-0x25 object with +0x2EC set.
D754="DIFFTEST_ARG=0=80480000 DIFFTEST_POKE=80480004=25000000,80480014=42C80000,80480018=C1200000,8048001C=43480000,804800B8=3F800000,80480040=40000000,804800C4=40400000,80480124=00000003,800BEA34=00000000,800BEE10=00000000,800C3A08=00000000,804802EC=00000001 DIFFTEST_RET=15114F2C=80484000,1507551C=80486000"
chkce EQUIV  func_1507D754 "$D754"
chkce DIFFER func_1507D754 "$D754" 's/func_151CFFFC(obj, 0xFF, 1);/func_151CFFFC(obj, 0xFE, 1);/'
chkce UNSURE func_1507D754 "$D754 DIFFTEST_PAGESTUB_OLD=1"
# P198: words a stub writes (DIFFTEST_OUTW '@ADDR') are part of the compared memory: func_15063254 saves +0xB8 / +0xC4
# of its object, func_15060F28 (jal 150612D4) clobbers them, the function restores them. Before P198 the final compare
# used the function's own store log only, so dropping a restore compared equal. DIFFTEST_STUBW_OLD=1 = old behaviour.
S63254="DIFFTEST_EXACT=* DIFFTEST_ARG=0=800CC6F0,1=3,2=7,3=3FC00000 DIFFTEST_POKE=800CC704=41280000,800CC708=C1A20000,800CC70C=43960000,800CC7A8=3F400000,800CC730=3FA00000,800CC7B4=C0900000,800CC764=5555BEEF,800CC82C=11111102,800CC834=80410000,800CCA08=80420000,800CCA0C=CAFE0000 DIFFTEST_OUTW=150612D4=@800CC7A8:DEADBEEF/@800CC7B4:DEADBEEF/@800CCA08:DEADBEEF"
chkce EQUIV  func_15063254 "$S63254"
chkce DIFFER func_15063254 "$S63254" 's/    \*(f32 \*) (o + 0xC4) = fC4;/    ;/'
chkce EQUIV  func_15063254 "$S63254 DIFFTEST_STUBW_OLD=1" 's/    \*(f32 \*) (o + 0xC4) = fC4;/    ;/'
# P200: DIFFTEST_ARG on a leading float parameter (f12 / f14) set only a0 / a1, so f(f32 x, f32 y, ...) ran on random
# x / y: func_15087204's wall setups never met the wall and dropping `ex = -ex` survived. DIFFTEST_ARGF_OLD=1 = old.
# (old mode: 4 trials, the random x / y of trial 5 happen to cross the wall)
S87204="DIFFTEST_EXACT=* DIFFTEST_ARG=0=42700000,1=40A00000,2=41A00000,3=C2200000,4=42200000 DIFFTEST_POKE=800D2778=80470000,80087630=00020000,80470000=00000007,80470004=00000200,80470008=0001FFFF,8047000C=FFFF0100,80470010=00640007,80470014=00640200,80470018=00FFFFFF,8047001C=FFFF0100 DIFFTEST_RET=15086218=2"
chkce EQUIV  func_15087204 "$S87204"
chkce DIFFER func_15087204 "$S87204" 's/            ex = -ex;//'
TRIALS=4 chkce EQUIV  func_15087204 "$S87204 DIFFTEST_ARGF_OLD=1" 's/            ex = -ex;//'
# P211: an indirect call (jalr) compared only the arg registers the reference wrote since the previous call, and only
# for targets of unknown arity: a candidate setting the pass-through a0 to 0 in an earlier block (`arg0 = 0` in the
# `idx >= 10` branch, a branch before the jalr block) compared equal. Now every arg register / f12-f15 either side wrote
# since entry is compared at a jalr. Table entry 0 poked to an unknown target (0x80450000). DIFFTEST_JALRARG_OLD=1 = old.
S472C="DIFFTEST_ARG=0=80490000 DIFFTEST_POKE=8049003C=000F0000,80089E4C=80450000"
chkce EQUIV  func_1513472C "$S472C"
chkce DIFFER func_1513472C "$S472C" 's|idx = 0; /\* hi \*/|idx = 0; arg0 = 0;|'
chkce EQUIV  func_1513472C "$S472C DIFFTEST_JALRARG_OLD=1" 's|idx = 0; /\* hi \*/|idx = 0; arg0 = 0;|'
# P211: DIFFTEST_STKFILL=WORD fills the harness stack (zeros before): func_151C384C builds an emitter request on its
# stack; dropping `req.angle[1] = 0.0f` compared equal because the unwritten slot read 0 anyway. With the fill the
# request bytes (ARGMEM on func_151530A8) differ. No fill = old behaviour.
S384C="DIFFTEST_EXACT=* DIFFTEST_ROMDATA=1 DIFFTEST_ARGMEM=151530A8=0:89,151530A8=0+5C:15,151530A8=0+6C:8,151307F0=0:92,151307F0=0+60:6,15160830=0:5,15160830=1:12 DIFFTEST_ARG=0=80450000,1=7,2=1 DIFFTEST_POKE=80450000=44610000,80450004=C2C80000,80450008=3F800000 DIFFTEST_RET=150ADF00=0;0;0;0;0 DIFFTEST_RETF=150ADF48=00000000"
TRIALS=4 chkce EQUIV  func_151C384C "$S384C DIFFTEST_STKFILL=5A5A5A5A"
TRIALS=4 chkce DIFFER func_151C384C "$S384C DIFFTEST_STKFILL=5A5A5A5A" 's/    req.angle\[1\] = 0.0f;//'
TRIALS=4 chkce EQUIV  func_151C384C "$S384C" 's/    req.angle\[1\] = 0.0f;//'
# P214: arguments of direct calls. (1) `return func_X(...)` was parsed as a declaration of func_X (type `return`):
# game_A28B0's `return func_1505A630(temp_v0[0] - ...)` gave func_1505A630 an empty FP-argument set, so f12 / f14 were
# never compared (port-b P210 func_150768DC x-swap survived); DIFFTEST_DECLKW_OLD=1 = old. (2) a callee of unknown
# prototype (DIFFTEST_NOPROTO forces it): every f12-f15 / a0-a3 either side wrote since the previous call is
# compared, not only FPRs both sides set right before the jal (the case writes f12 before a branch); JALARG_OLD=1 = old.
S68DC="DIFFTEST_EXACT=* DIFFTEST_POKE=800CC6F0=00000000,800CCA1C=00000000,800CCD48=00000000,800CD074=00000001,800CD078=10000000,800CD088=00000000,800CD08C=40A00000,800CD090=00000000,800CD0E8=00000000,800CD11C=33000000,800CD33C=00000000,800CD3A0=00000000,800CD6CC=00000001,800CD6D0=11000000,800CD6E0=42480000,800CD6E4=40A00000,800CD6E8=40A00000,800CD7C4=00000020,800CD894=00000500,800CD8E4=80470000,800CD8EC=00005500,800CD8FC=00004400,800CD9F8=00000000,800CDD24=00000000,800CE050=00000000,800CE37C=00000000,800CE6A8=00000000,800CE9D4=00000000,800CED00=00000000,800CF02C=00000000,800CF358=00000000,800CF684=00000000,800CF9B0=00000000,800CFCDC=00000000,800D0008=00000000,800D0334=00000000,800D0660=00000000,800D098C=00000000,800D0CB8=00000000,800D0FE4=00000000,800D1310=00000000,800D196C=800CD074,800D1CB0=20001527,800D20F0=80450000,80450014=00000040 DIFFTEST_RET=1507BEE8=80470010,1505A9B0=00001000 DIFFTEST_RETF=1505AAAC=42000000"
M68DC='s/dx = o->x_position - D_800D154C->x_position;/dx = D_800D154C->x_position - o->x_position;/'
TRIALS=4 chkce EQUIV  func_150768DC "$S68DC"
TRIALS=4 chkce DIFFER func_150768DC "$S68DC" "$M68DC"
TRIALS=4 chkce EQUIV  func_150768DC "$S68DC DIFFTEST_DECLKW_OLD=1" "$M68DC"
TRIALS=4 chkce EQUIV  func_150768DC "$S68DC DIFFTEST_NOPROTO=func_1505A630"
TRIALS=4 chkce DIFFER func_150768DC "$S68DC DIFFTEST_NOPROTO=func_1505A630" "$M68DC"
TRIALS=4 chkce EQUIV  func_150768DC "$S68DC DIFFTEST_NOPROTO=func_1505A630 DIFFTEST_JALARG_OLD=1" "$M68DC"
# P215: (1) P214 lost the `cnt = max(cnt, ...indw...)` line of the P211 jalr compare (indw computed, never used): the
# func_1513472C `arg0 = 0` case above gave EQUIV (82 / 83 at the end of P214). (2) at a jalr the target register is not
# an argument: func_1506B04C does `lw a2, D_800864B0(a2); jalr a2` (a2 = the handler address in the reference, `arg`
# in the candidate) and keeps a scratch copy of `arg` in a3 (`or a3, a2, zero`; it passes it in a1). The target
# register is skipped (DIFFTEST_JALRTGT_OLD=1 = old); DIFFTEST_JALRSKIP=3 drops the scratch a3 (all 15 handlers take 2 args).
SB04C="DIFFTEST_ROMDATA=1 DIFFTEST_ARG=0=80450000,1=A,2=80460010 DIFFTEST_POKE=8045002C=3F800000"
TRIALS=4 chkce EQUIV  func_1506B04C "$SB04C DIFFTEST_JALRSKIP=3"
TRIALS=4 chkce DIFFER func_1506B04C "$SB04C DIFFTEST_JALRSKIP=3" 's/handler(obj, arg);/handler(obj, obj);/'
TRIALS=4 chkce DIFFER func_1506B04C "$SB04C DIFFTEST_JALRSKIP=3" 's/handler(obj, arg);/handler(arg, arg);/'
TRIALS=4 chkce DIFFER func_1506B04C "$SB04C DIFFTEST_JALRSKIP=3 DIFFTEST_JALRTGT_OLD=1"
TRIALS=4 chkce DIFFER func_1506B04C "$SB04C"
# P215: (3) a TU-literal argument (candidate "%d" at TU_BASE vs the reference's rodata_inject D_8009DDF0) compared
# "different" when the reference never touched that page (unmapped: mem_read failed). Now the page's initial content
# is read (DIFFTEST_TUPEEK_OLD=1 = old). func_1508AB7C draws the counters with func_15042D94(x, y, 1, "%d", n / 50).
SAB7C="DIFFTEST_ROMDATA=1 DIFFTEST_TUCMP_LEN=4 DIFFTEST_EXACT=* DIFFTEST_POKE=800D27D0=80450000,80450010=3,800BEE04=2,800CCA0C=80460000,800CCD38=80460000,800CD064=80460000,80460198=00000000,804601AC=00000000,800E1000=00000000,80450E64=0,80450E68=1,80450E6C=2,804516BC=00B90000,800CC91C=0,800CCC48=0,800CCF74=0,80450014=00000000,80450018=00000000,8045035C=00000000,80450360=00000000,80450364=00000000,8045031C=00000000,80450320=00000000,80450324=00000000,800E0FE8=02000000,800BEA48=80470000,80470024=41200000,8047002C=42000000,80470030=43000000,800CC818=0,80083330=1,80451574=00000123,80451578=00000123,8045157C=00000123 DIFFTEST_RET=15085E1C=0 DIFFTEST_RETF=150ADF48=3F400000"
TRIALS=4 chkce EQUIV  func_1508AB7C "$SAB7C"
TRIALS=4 chkce DIFFER func_1508AB7C "$SAB7C" 's/(s32) "%d"/(s32) "%x"/'
TRIALS=4 chkce DIFFER func_1508AB7C "$SAB7C DIFFTEST_TUPEEK_OLD=1"
# P221: a jalr to an unaligned / unstubbable target ends the trial as a common fault (inconclusive) on both sides
# (DIFFTEST_BADJALR_OLD=1 = old: stub_at refused it silently and both sides ran into garbage, then into their own code:
# func_151416E8 trial 24 handler 0x1167216A from a random D_8008A3CC). Different / one-sided bad targets still DIFFER.
TRIALS=32 chkce EQUIV  func_151416E8 ""
TRIALS=32 chkce DIFFER func_151416E8 "DIFFTEST_BADJALR_OLD=1"
TRIALS=32 chkce DIFFER func_151416E8 "" 's/D_8008A3CC\[rec\[0x168\]\](rec/D_8008A3CC[rec[0x167]](rec/'
TRIALS=32 chkce DIFFER func_151416E8 "" 's/(rec, msg, c);/(rec, msg, code);/'
# P234: a callee declared only in a header the TU includes (func_150ADA20 / func_150ADA68 in functions.h) has a known
# prototype: IDO's scratch f12 left right before `jal func_150ADA20` is not an argument (P232 func_15109DC8 first run
# was a false DIFFER; the case is the P232 block without its local declarations). DIFFTEST_INCHDR_OLD=1 = old.
S9DC8="DIFFTEST_EXACT=* DIFFTEST_ROMDATA=1 DIFFTEST_STKFILL=A5A5A5A5 DIFFTEST_ARGMEM=151308E4=0:92,151308E4=0+60:6,151530A8=0:89,151530A8=0+5C:15,151530A8=0+6C:8 DIFFTEST_RET=150ADF00=0;0;0 DIFFTEST_RETF=150ADF48=3F000000;3E800000"
TRIALS=4 chkce EQUIV  func_15109DC8 "$S9DC8"
TRIALS=4 chkce DIFFER func_15109DC8 "$S9DC8 DIFFTEST_INCHDR_OLD=1"
TRIALS=4 chkce DIFFER func_15109DC8 "$S9DC8" 's/t.life = (func_150ADA20() \& 0xF) + 10;/t.life = (func_150ADA20() \& 0xF) + 11;/'
TRIALS=4 chkce DIFFER func_15109DC8 "$S9DC8" 's/scale = (func_150ADA68() \* D_800A2A04/scale = (func_150ADA68() * D_800A2A08/'
# P238: DIFFTEST_OUTP writes through a pointer read from an argument array (func_15145EA4's dst[i] points). Without
# it the transformed start / end points stay stack fill (start == dir) and a swapped subtraction is EQUIV (the hole).
S60E30="DIFFTEST_EXACT=* DIFFTEST_ROMDATA=1 DIFFTEST_STKFILL=A5A5A5A5 DIFFTEST_ARGMEM=15146414=0:8,15145698=0:12 DIFFTEST_ARG=0=80450000 DIFFTEST_POKE=80450014=80460000,80450018=80470000,8045001C=07030000,80450038=42C80000,8045003C=03000000,80470000=00000001,80470014=42F73333,80470038=00000007,80470074=03000000,804701D4=80480000 DIFFTEST_RET=15145698=1 DIFFTEST_OUTA=15081A90=7:80490000;3F000000;C29B6666;4284CCCD;44BB8666;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;10000"
P60E30="DIFFTEST_OUTP=15146414=1.0:41200000;41A00000;41F00000/1.1:42200000;C1200000;42480000"
M60E30='s/        dir\[0\] = dir\[0\] - start\[0\];/        dir[0] = start[0] - dir[0];/'
TRIALS=4 chkce EQUIV  func_15160E30 "$S60E30 $P60E30"
TRIALS=4 chkce DIFFER func_15160E30 "$S60E30 $P60E30" "$M60E30"
TRIALS=4 chkce EQUIV  func_15160E30 "$S60E30" "$M60E30"
# P225: (1) nm_resolve passes #if blocks nested inside an NM block through (DIFFTEST_NMNEST_OLD=1 = old: the nested #else /
# #endif closed the NM block -> CERR, P222 1BAF40). The case has `#ifdef PORT` (dropped: no PORT in difftest)
# / `#else` (kept) inside its NM block. (2) DIFFTEST_STKFILL with a non-hex value is an ERROR line (was a traceback with
# no result line, P222).
TRIALS=8 chkce EQUIV  func_15103828 ""
TRIALS=8 chkce CERR   func_15103828 "DIFFTEST_NMNEST_OLD=1"
TRIALS=8 chkce DIFFER func_15103828 "" 's/D_800D9AB0\[i\] -= D_800BE9E4;/D_800D9AB0[i] -= D_800BE9E4 + 2;/'
TRIALS=8 chkce EQUIV  func_15103828 "" 's/D_800BE9E4 + 1;/D_800BE9E4 + 3;/'
TRIALS=8 chkce ERROR  func_15103828 "DIFFTEST_STKFILL=WORD"
TRIALS=8 chkce EQUIV  func_15103828 "DIFFTEST_STKFILL=A5A5A5A5"
# P229: a DIFFTEST_ARG item with a non-decimal index (`A=7`) is an ERROR line (was a traceback, empty result, P225);
# a valid decimal index with a hex value still runs.
TRIALS=8 chkce ERROR  func_15103828 "DIFFTEST_ARG=A=7"
TRIALS=8 chkce EQUIV  func_15103828 "DIFFTEST_ARG=0=7"
# P243: a matched-C reference is its own ELF symbol size, not len(candidate): a longer candidate that jals the next
# function (func_150305E0 -> func_15030600) used to make the reference span the callee, leave `jal func_15030600`
# unstubbed and run into the real callee (hang until DIFFTEST_TIMEOUT). Now the candidate moves to CAND_ALT and the
# callee is a stub on both sides. DIFFTEST_REFSZ_OLD=1 = old (hangs; not a case here). D_800C3EE0 is EU 800C4300.
TRIALS=8 chkce EQUIV  func_150305E0 "DIFFTEST_TIMEOUT=120"
TRIALS=8 chkce DIFFER func_150305E0 "DIFFTEST_TIMEOUT=120 DIFFTEST_POKE=800C4300=5A5A1234" '1,/0xFF/s/0xFF/0xFE/'
TRIALS=8 chkce EQUIV  func_150305E0 "DIFFTEST_TIMEOUT=120" '1,/0xFF/s/0xFF/0xFE/'
# P243 (port-b P242): 0x15031C4C carries two symbols (func_15031C4C, and func_1503195C in undefined_syms.eu.txt); calls
# are named func_1503195C. Since P234 its functions.h declaration is found through the TU's includes; without that
# (DIFFTEST_INCHDR_OLD=1, or an alias no header declares) the callee had no prototype. Now every name at the address
# is tried (first declared one wins; DIFFTEST_ALIASPROTO_OLD=1 = old). Case: the candidate leaves a scratch value in a3
# (not an argument of the 3-argument callee): with the prototype EQUIV, without it a false DIFFER on a3.
TRIALS=8 chkce EQUIV  func_15031C1C ""
TRIALS=8 chkce DIFFER func_15031C1C "" 's/func_15031C4C(arg0, arg1, arg3)/func_15031C4C(arg0, arg1, arg2)/'
TRIALS=8 chkce EQUIV  func_15031C1C "DIFFTEST_INCHDR_OLD=1" 's/func_15031C4C(arg0, arg1, arg3)/func_15031C4C(arg0, arg1, (arg3 = arg2 ^ arg3) ^ arg2)/'
TRIALS=8 chkce DIFFER func_15031C1C "DIFFTEST_INCHDR_OLD=1 DIFFTEST_ALIASPROTO_OLD=1" 's/func_15031C4C(arg0, arg1, arg3)/func_15031C4C(arg0, arg1, (arg3 = arg2 ^ arg3) ^ arg2)/'
# P250: at a jalr, f12-f15 are no longer compared when the target's prototype (or, without a declaration in the TU, its
# C definitions in src_eu) starts with an integer / pointer parameter: a leftover f14 scratch gave a false DIFFER in
# func_150C5A68 (handler func_150C6088 is s32 (u8 *); P246 / P247 needed DIFFTEST_JALRARG_OLD=1). DIFFTEST_JALRFPR_OLD=1
# shows the old false DIFFER; a wrong a0 at the jalr still DIFFERs. Also: a stub knob address given twice is an error.
S5A68="DIFFTEST_ROMDATA=1 DIFFTEST_STKFILL=A5A5A5A5 DIFFTEST_ARG=0=80410000 DIFFTEST_POKE=80410010=00000001,80410018=41200000,8041001C=40A00000,80410020=C1200000,80410024=3F800000,80410028=40000000,8041002C=40400000,80410030=00000000,804100C0=12345678 DIFFTEST_RET=150C6088=1 DIFFTEST_RETF=151443D4=42C80000"
chkce EQUIV  func_150C5A68 "$S5A68"
chkce DIFFER func_150C5A68 "$S5A68 DIFFTEST_JALRFPR_OLD=1"
chkce DIFFER func_150C5A68 "$S5A68" 's/D_80088B00\[\*(s8 \*) (o + 0x30)\](o) == 0/D_80088B00[*(s8 *) (o + 0x30)](o + 4) == 0/'
TRIALS=1 chkce KNOBERROR func_150C5A68 "$S5A68 DIFFTEST_OUTW=150C6088=0:1,150C6088=1:2"
# P256: DIFFTEST_ARGMEM "N*OFF:LEN" compares LEN bytes at the pointer stored at aN + OFF (func_15104A80's key holds a
# stack copy of a 9-byte part list; the pointer itself differs between the builds, so only the deref sees a swapped list).
S4A80="DIFFTEST_ROMDATA=1 DIFFTEST_STKFILL=A5A5A5A5 DIFFTEST_ARG=0=804100A0 DIFFTEST_POKE=800DC324=80410000,800DC3C4=80420000,80420004=0000000C,80410110=0000F800,800CCD48=00000000,800CD074=00000001 DIFFTEST_ARGMEM=15149A50=0:4,15149A50=0+8:4,15149A50=0*4:9"
chkce EQUIV  func_15104A80 "$S4A80"
chkce DIFFER func_15104A80 "$S4A80" 's/parts = D_800A275C;/parts = D_800A2768;/'
# P259: knob keys that are no jal / j target of the reference are flagged statically ("[knob not a jal target of the
# reference ...]"), also when no trial reaches the call (P256 keyed ARGMEM on func_151494E0's US address 151494E0; its
# EU jal target is 15149A50, and the compare silently did nothing). chkcn: want yes|no, func, env, substring.
chkcn() {
  local want=$1 f=$2 ev=$3 pat=$4 cf=$C/$2.c out has=no
  out=$(set -f; env $ev $R/tools/port/difftest.sh $f $cf --trials ${TRIALS:-8})
  case "$out" in *"$pat"*) has=yes;; esac
  if [ $has = $want ]; then pass=$((pass+1)); echo "ok   [$want: $pat] env case  $(echo "$out" | cut -c1-200)"
  else fail=$((fail+1)); echo "FAIL [want $want: $pat] env case  $out"; fi
}
chkcn yes func_15104A80 "$S4A80 DIFFTEST_ARGMEM=151494E0=0:4" "not a jal target of the reference (EU address? jalr-only callee?): ARGMEM 151494E0"
chkcn yes func_15104A80 "$S4A80 DIFFTEST_RET=151494E0=1" "RET 151494E0"
chkcn no  func_15104A80 "$S4A80" "not a jal target"
chkcn no  func_15104A80 "$S4A80 DIFFTEST_JALKEY_OLD=1 DIFFTEST_ARGMEM=151494E0=0:4" "not a jal target"
# P281: DIFFTEST_STOPCALL=ADDR=N ends a trial at the N-th call of a stub (endless thread loops: func_100052A0 spins in
# `while (1) {}` after osWritebackDCacheAll 100252A0). Without it every trial times out (UNSURE). A candidate that never
# makes the stop call times out alone (DIFFER). DIFFTEST_RETV1 sets the low word of osGetTime (100252D0): the busy wait
# bound 0x22ADD7 shows only with exact low words (EQUIV without them).
S52A0="DIFFTEST_STOPCALL=100252A0=1 DIFFTEST_RET=100252D0=0 DIFFTEST_POKE=8002C068=1,8002AE14=0"
V52A0="DIFFTEST_RETV1=100252D0=0;22ADD6;7270E0;0;7270E0"
chkce UNSURE func_100052A0 "DIFFTEST_RET=100252D0=0"
chkce EQUIV  func_100052A0 "$S52A0"
chkce DIFFER func_100052A0 "$S52A0" 's/__osSpSetPc(0);/__osSpSetPc(4);/'
chkce DIFFER func_100052A0 "$S52A0" 's/    osWritebackDCacheAll();//'
chkce EQUIV  func_100052A0 "$S52A0 $V52A0"
chkce DIFFER func_100052A0 "$S52A0 $V52A0" 's/D_8003BFC0 + 0x22ADD7/D_8003BFC0 + 0x22ADD6/'
chkce EQUIV  func_100052A0 "$S52A0" 's/D_8003BFC0 + 0x22ADD7/D_8003BFC0 + 0x22ADD6/'
# P281: a struct returned by value (ldiv_t ldiv(long, long)) takes a hidden a0, so its divisor is a2: the arity now
# counts it (DIFFTEST_SRET_OLD=1 = old: the divisor was never compared), and ldiv's stub computes the real quotient /
# remainder (DIFFTEST_LDIV_OLD=1 = old random). func_10001550 = libc _Ldtob on 1234.5678 with %e.
S1550="DIFFTEST_ARG=0=80480000,1=65 DIFFTEST_POKE=80480000=40934A45,80480004=6D5CFAAD,80480008=80490000,80480024=6 DIFFTEST_RET=10001A80=FFFFFFFF DIFFTEST_OUTB=10001A80=0:00;0B"
chkce EQUIV  func_10001550 "$S1550"
chkce DIFFER func_10001550 "$S1550" 's/qr = ldiv(lo, 10);/qr = ldiv(lo, 16);/'
chkce EQUIV  func_10001550 "$S1550 DIFFTEST_SRET_OLD=1 DIFFTEST_LDIV_OLD=1" 's/qr = ldiv(lo, 10);/qr = ldiv(lo, 16);/'
# P288: a stub's OUTW / OUTA into a page the function never touched (func_10001194's func_10004514 reads into
# D_80082EB0) faulted in stub_write (mem_write without ensure()) -> UNSURE; stub_write now maps the pages first
# (DIFFTEST_STUBMAP_OLD=1 = old). The xor-key mutant is only seen through the OUTW-read offset table.
S1194="DIFFTEST_ROMDATA=1 DIFFTEST_ARG=0=0 DIFFTEST_POKE=8000030C=0 DIFFTEST_RET=10003E90=80480000,10003EBC=80400000;80420000 DIFFTEST_OUTW=10004764=1:00001234;0;8039CCCB"
chkce EQUIV  func_10001194 "$S1194"
chkce UNSURE func_10001194 "$S1194 DIFFTEST_STUBMAP_OLD=1"
chkce DIFFER func_10001194 "$S1194" 's/(D_8003585C\[i\] ^ 0x8039CCCA)/(D_8003585C[i] ^ 0x8039CCCB)/'
# P292: a stub output (DIFFTEST_OUTW / OUTA) into a heap page the function had not touched yet faulted with
# UC_ERR_WRITE_UNMAPPED at the stub, so every trial was inconclusive (func_1518D290: the ring / world buffers that
# DIFFTEST_RET hands out are filled by stubs first). same fix as P288 above (one ensure() loop, one
# DIFFTEST_STUBMAP_OLD switch since the P308 merge).
# (The old-behaviour case uses 1 trial: with more, the fault-learning re-runs map the page and later trials pass.)
SD290="DIFFTEST_EXACT=* DIFFTEST_ROMDATA=1 DIFFTEST_STKFILL=A5A5A5A5 DIFFTEST_ARG=0=80480000,1=7,2=1234 DIFFTEST_RET=10003EBC=80460000;80470000 DIFFTEST_OUTW=15143CAC=2:42C80000;C2480000/3:41200000;C1A00000 DIFFTEST_OUTA=15146324=2:43480000;C2C80000;44160000;41200000;C1200000;42F00000;3F800000;40000000;40400000;C0800000;C0A00000;C0C00000 DIFFTEST_ARGMEM=151307F0=0:102"
TRIALS=4 chkce EQUIV  func_1518D290 "$SD290"
TRIALS=1 chkce UNSURE func_1518D290 "$SD290 DIFFTEST_STUBMAP_OLD=1"
TRIALS=1 chkce DIFFER func_1518D290 "$SD290" 's/(func_150ADA68() \* 202.0f/(func_150ADA68() * 200.0f/'
# P260: a candidate path the container already read, rewritten on the host with a different size (what every
# chkce sed mutant does with $T/FUNC.mut.c). After the P256 Docker restart the container kept the old size, so the
# selftest's 5 re-used mutant paths compiled truncated (CERR). difftest.sh now refreshes the parent dir and compares
# md5s (ERROR "stale container view" if it still differs). The rewritten file must be the DIFFER mutant, not CERR.
F28=$T/func_15103828.mut.c
sed -e 's/D_800BE9E4 + 1;/D_800BE9E4 + 3;/' $C/func_15103828.c > $F28; docker exec ${CONKERDEV:-conkerdev} cat ${F28/#$R//conker} > /dev/null
TRIALS=8 chkce DIFFER func_15103828 "" 's/D_800D9AB0\[i\] -= D_800BE9E4;/D_800D9AB0[i] -= D_800BE9E4 + 2;/'
# P280: DIFFTEST_ARGMEM "N:LEN@K" compares only at the K-th call to ADDR. func_1501175C memcpys a 0x10 link record,
# then a 0x5C tail: LEN 92 on every call compares stack bytes past the link record (layout-dependent, DIFFER as is);
# with @0 / @1 the case is EQUIV and a one-ulp change of a tail constant DIFFERs.
S175C="DIFFTEST_ROMDATA=1 DIFFTEST_STKFILL=A5A5A5A5 DIFFTEST_ARG=0=80460000,1=00000012,2=00000001 DIFFTEST_POKE=8046003B=07000000,8046014C=41200000,80460150=42C80000 DIFFTEST_RET=151496A0=80470000,1513D860=80480000,150ADF00=00000003,15160830=80490000"
chkce DIFFER func_1501175C "$S175C DIFFTEST_ARGMEM=10023360=1:92"
chkce EQUIV  func_1501175C "$S175C DIFFTEST_ARGMEM=10023360=1:16@0,10023360=1:92@1"
chkce DIFFER func_1501175C "$S175C DIFFTEST_ARGMEM=10023360=1:16@0,10023360=1:92@1" 's/0.396174014f/0.396175f/'
chkce EQUIV  func_1501175C "$S175C DIFFTEST_ARGMEM=10023360=1:16@0" 's/0.396174014f/0.396175f/'
# P317: DIFFTEST_MEMCPY=1 makes the memcpy stub copy for real. func_1501175C's 0x5C tail record is memcpy'd to the
# heap: with the stub copying nothing, a tail-constant change was invisible without an ARGMEM compare (EQUIV above);
# with the real copy the destination writes are compared and it DIFFERs, while the unmutated function stays EQUIV.
chkce EQUIV  func_1501175C "$S175C DIFFTEST_ARGMEM=10023360=1:16@0 DIFFTEST_MEMCPY=1"
chkce DIFFER func_1501175C "$S175C DIFFTEST_ARGMEM=10023360=1:16@0 DIFFTEST_MEMCPY=1" 's/0.396174014f/0.396175f/'
echo "selftest: $pass ok, $fail failed"; [ $fail = 0 ]
