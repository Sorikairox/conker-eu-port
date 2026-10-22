#!/bin/bash
# P74 mutant runner that stops at the first DIFFER. usage: mutfast.sh FUNC base.c setups.txt 'sed-expr' ...
# Prints per mutant: KILLED by <setup> or LIVE (all setups EQUIV/UNSURE). Env TR (trials per setup, 4).
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
F=$1; B=$2; S=$3; shift 3; i=0
for e in "$@"; do
  i=$((i+1)); m=port_work/p74/mut_${F}_$i.c
  sed -e "$e" "$B" > $m
  if cmp -s "$B" "$m"; then echo "m$i NOCHANGE: $e"; continue; fi
  res="LIVE"
  while IFS='!' read -r n a p r rf ow ww wb; do
    n=$(echo $n)
    out=$(DIFFTEST_TMP=build/difftest_p74m_$F DIFFTEST_EXACT='*' DIFFTEST_ARG="$(echo $a)" DIFFTEST_POKE="$(echo $p)" \
      DIFFTEST_RET="$(echo $r)" DIFFTEST_RETF="$(echo $rf)" DIFFTEST_OUTA="$(echo $ow)" DIFFTEST_OUTW="$(echo $ww)" DIFFTEST_OUTB="$(echo $wb)" \
      tools/port/difftest.sh $F $m --trials ${TR:-4} --seed 1 2>&1 | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR|CERR)" | cut -c1-120)
    case "$out" in DIFFER*) res="KILLED by $n"; break;; CERR*|ERROR*) res="BROKEN $out"; break;; esac
  done < <(grep -vE '^\s*(#|$)' "$S")
  echo "m$i $res: $e"
done
# P74 runs: port_work/p74/mut_0ad0.log (22 func_15000AD0 mutants on s0ad0_m.txt), mut_6b_a.log (F45C / ED44 / EF90),
# mut_6b_b.log (mut_6b_b.sh: EB1C / E5F8 / E6B4 / E238); E6B4 matrix mutants with
# DIFFTEST_ARGMEM="150A7F28=0:64,150A7F28=1:64,1503E8E8=0:64" (P74.md).
