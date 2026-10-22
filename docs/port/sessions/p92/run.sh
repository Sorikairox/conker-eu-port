#!/bin/bash
# P92: setups then mutants, sequentially, for "FUNC:key" pairs (draft p92/FUNC.c, setups p92/key.txt, mutants p92/key_mut.txt).
cd "$(dirname "$0")/../../../.."
for fk in "$@"; do
  F=${fk%%:*}; k=${fk##*:}; D=docs/port/sessions/p92/$F.c; S=docs/port/sessions/p92/$k.txt
  TR=${TR:-4} KTMP=build/difftest_p92k_$F docs/port/sessions/p73/knobs.sh $F $D $S > port_work/p92/${k}_knobs.log 2>&1
  echo "$F setups: $(wc -l < port_work/p92/${k}_knobs.log), non-EQUIV $(grep -vc EQUIV port_work/p92/${k}_knobs.log)"
  [ -n "$NOMUT" ] && continue
  TR=${TR:-4} docs/port/sessions/p82/mut.sh $F $D $S docs/port/sessions/p92/${k}_mut.txt > port_work/p92/${k}_mut.log 2>&1
  echo "$F mutants: $(grep -c KILLED port_work/p92/${k}_mut.log) killed of $(wc -l < port_work/p92/${k}_mut.log)"
done
