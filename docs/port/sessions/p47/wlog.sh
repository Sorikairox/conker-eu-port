#!/bin/bash
# usage: wlog.sh FUNC cand.c TRIAL LO-HI [ntrials] -- write logs of the last ref run and the cand run of TRIAL
cd "$(dirname "$0")/../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
DIFFTEST_EXACT="*" DIFFTEST_WLOG=$4 DIFFTEST_WLOG_T=$3 tools/port/difftest.sh $1 $2 --trials ${5:-$(($3+1))} --seed ${SEED:-1} 2>&1 | grep '^WLOG' | awk '/WLOG R --- run/{r=""} /^WLOG R/{r=r $0 "\n"; next} /^WLOG C/{c=c $0 "\n"} END{printf "%s%s", r, c}'
