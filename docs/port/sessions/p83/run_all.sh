#!/bin/bash
# P83: setups then mutants, sequentially, for "FUNC key" pairs. usage: run_all.sh FUNC:key ...
# Env RETX: DIFFTEST_RET for the random phase of mut.sh (e.g. func_15128030 needs 15048A10=1, P83.md).
cd "$(dirname "$0")/../../../.."
for fk in "$@"; do
  F=${fk%%:*}; k=${fk##*:}; D=docs/port/sessions/p83/$F.c; S=docs/port/sessions/p83/$k.txt
  TR=4 KTMP=build/difftest_p83k_$F docs/port/sessions/p73/knobs.sh $F $D $S > port_work/p83/${k}_knobs.log 2>&1
  echo "$F setups: $(wc -l < port_work/p83/${k}_knobs.log), non-EQUIV $(grep -vc EQUIV port_work/p83/${k}_knobs.log)"
  TR=4 docs/port/sessions/p82/mut.sh $F $D $S docs/port/sessions/p83/${k}_mut.txt > port_work/p83/${k}_mut.log 2>&1
  echo "$F mutants: $(grep -c KILLED port_work/p83/${k}_mut.log) killed of $(wc -l < port_work/p83/${k}_mut.log)"
done
