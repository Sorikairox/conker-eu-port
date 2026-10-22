#!/bin/bash
# usage: p68_dbg.sh FUNC cand setups name [extra difftest args]
cd /Users/sorikairo/conker-wt/portb && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
F=$1; C=$2; S=$3; N=$4; shift 4
l=$(grep "^$N " $S); IFS='!' read -r n a p r rf ow ww wb <<< "$l"
DIFFTEST_TMP=build/difftest_p68_dbg DIFFTEST_EXACT='*' DIFFTEST_ARG="$(echo $a)" DIFFTEST_POKE="$(echo $p)" DIFFTEST_RET="$(echo $r)" DIFFTEST_RETF="$(echo $rf)" DIFFTEST_OUTA="$(echo $ow)" DIFFTEST_OUTW="$(echo $ww)" DIFFTEST_OUTB="$(echo $wb)" tools/port/difftest.sh $F $C "$@"
