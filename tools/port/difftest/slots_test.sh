#!/bin/bash
# P235: test of the difftest.sh job limiter (2 slots per container). Uses its own slot dir, so real jobs are not affected.
# usage: tools/port/difftest/slots_test.sh   (after eval "$(tools/eu_port/wt.sh env <name>)")
#  1. both slots held by a live in-container process -> a third job waits (gives up after DIFFTEST_SLOT_MAXWAIT)
#  2. a slot held by a process that exits after 8 s -> a third job waits, then runs once that slot frees
#  3. a slot with a dead PID is stale -> cleaned, the job runs at once; its slot is released afterwards
. "$(dirname "${BASH_SOURCE[0]}")/../portguard.sh"
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
R=${CONKER_ROOT:-$HOME/conker}; C=${CONKERDEV:-conkerdev}; SD=/tmp/difftest_slots_test
export DIFFTEST_SLOTDIR=$SD DIFFTEST_TIMEOUT=60
pass=0; fail=0
ck() { if [ "$1" = 1 ]; then echo "ok   $2"; pass=$((pass+1)); else echo "FAIL $2"; fail=$((fail+1)); fi; }
job() { $R/tools/port/difftest.sh sfx_cooldown_clear --self --trials 4 2>&1; }   # a small matched function (selftest case)
dx() { docker exec $C bash -c "$1"; }
dx "rm -rf $SD; mkdir -p $SD/slot1 $SD/slot2; echo 1 > $SD/slot1/pid; echo 1 > $SD/slot2/pid"   # PID 1 is always alive

# 1. both slots busy: waits, gives up after 6 s
t0=$(date +%s); out=$(DIFFTEST_SLOT_MAXWAIT=6 job); dt=$(( $(date +%s) - t0 ))
echo "$out" | grep -q "slots busy" && echo "$out" | grep -q "^ERROR difftest.sh: no job slot" && [ $dt -ge 6 ]; ck $([ $? = 0 ] && echo 1 || echo 0) "third job waits while 2 slots are busy (${dt}s)"

# 2. slot2 held by a process that exits after 8 s (docker exec -d, no shell &): the job waits, then runs
dx "rm -rf $SD/slot2"; docker exec -d $C bash -c "mkdir $SD/slot2; echo \$\$ > $SD/slot2/pid; exec sleep 8"
sleep 1; t0=$(date +%s); out=$(job); dt=$(( $(date +%s) - t0 ))
echo "$out" | grep -q "slots busy" && echo "$out" | grep -q "^EQUIV" && [ $dt -ge 5 ]; ck $([ $? = 0 ] && echo 1 || echo 0) "third job waits, then runs when a slot frees (${dt}s)"

# 3. stale slot (dead PID) is cleaned; the job runs at once and releases its slot
dx "rm -rf $SD/slot2; mkdir $SD/slot2; echo 999999 > $SD/slot2/pid"
t0=$(date +%s); out=$(job); dt=$(( $(date +%s) - t0 ))
echo "$out" | grep -q "^EQUIV" && ! echo "$out" | grep -q "slots busy"; ck $([ $? = 0 ] && echo 1 || echo 0) "stale slot cleaned, job runs at once (${dt}s)"
left=$(dx "ls $SD"); [ "$left" = "slot1" ]; ck $([ $? = 0 ] && echo 1 || echo 0) "slot released after the job (left: $(echo $left))"

# 4. DIFFTEST_SLOTS=0 turns the limiter off
out=$(DIFFTEST_SLOTS=0 DIFFTEST_SLOT_MAXWAIT=2 job); echo "$out" | grep -q "^EQUIV"; ck $([ $? = 0 ] && echo 1 || echo 0) "DIFFTEST_SLOTS=0 bypasses the limiter"
dx "rm -rf $SD"
echo "slots_test: $pass ok, $fail fail"; [ $fail = 0 ]
