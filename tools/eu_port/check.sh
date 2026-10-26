#!/bin/bash
# P327: pre-commit checks for port-web, two levels (replaces docs/port/sessions/p322/check.sh + pNNN/all.sh).
#   tools/eu_port/check.sh --fast   verify_all (default ROM byte-identical) + NM link + protocheck + implicit_scan
#                                   + incremental web build. For changes that only touch `#ifdef PORT` code, port/
#                                   or the page (port/web): those cannot change the IDO/NM code the skipped checks
#                                   look at.
#   tools/eu_port/check.sh --full   the above + romabs_check + arity_scan + difftest selftest + a full census
#                                   (port/web/run.sh census: every TU, 0 FAIL) + the web build. Required for any
#                                   change outside #ifdef PORT / port/ (NM C, headers, harness, merges), and run once
#                                   by every session before its final commit and deploy.
#   tools/eu_port/check.sh --port   P328: the checks that do not need the byte-matching build (conker/build, conker/asm,
#                                   *_auto.txt, IDO NM link): implicit_scan + romabs_check + difftest selftest (reference
#                                   code from the ROM, port/symbols) + full census + web build. Skips verify_all, the NM
#                                   link, protocheck and arity_scan (they read the matching build). Cleanup part 2 makes
#                                   this the default and removes the old modes.
# Sequential on purpose (verify_all regenerates asm/, the NM build and the scans read it). Logs: port_work/check/.
# Prints one line per step (rc, seconds, key line) and a final GREEN / RED line; exit status 0 only when green.
MODE=${1:---fast}
case $MODE in --fast|--full|--port) ;; *) sed -n '2,16p' "$0"; exit 2;; esac
cd ~/conker-wt/web || exit 2
eval "$(tools/eu_port/wt.sh env web)" || exit 2
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH DIFFTEST_SLOTS=1
D=port_work/check; mkdir -p $D
red=0; T0=$(date +%s)
step() {  # step NAME OKTEST CMD...   OKTEST is a shell test run after CMD with $rc and $log set
  local name=$1 ok=$2; shift 2
  local log=$D/$name.log s=$(date +%s)
  "$@" > $log 2>&1; rc=$?
  if eval "$ok"; then st=ok; else st=RED; red=1; fi
  printf '%-10s %-3s rc %-3s %4ss  %s\n' "$name" "$st" "$rc" "$(( $(date +%s) - s ))" "$(eval "$KEY" | cut -c1-150)"
}
if [ $MODE != --port ]; then
KEY='tail -1 $log'; step verify_all '[ $rc = 0 ]' tools/eu_port/verify_all.sh
KEY='tail -1 $log'; step nm '[ $rc = 0 ]' docker exec -w /conker $CONKERDEV make -C conker VERSION=eu NON_MATCHING=1 -j4
KEY='tail -1 $log'; step protocheck '[ $rc = 0 ]' python3 tools/eu_port/protocheck.py
fi
KEY='tail -1 $log'; step implicit '[ $rc = 0 ] && grep -q " 0 NM+float" $log' python3 tools/port/implicit_scan.py
if [ $MODE != --fast ]; then
  KEY='tail -1 $log'; step romabs '[ $rc = 0 ] && grep -q " 0 FAIL" $log' python3 port/tools/romabs_check.py
  [ $MODE = --full ] && { KEY='grep -c . $log'; step arity '[ $rc = 0 ]' python3 tools/port/arity_scan.py; }
  KEY='tail -1 $log'; step selftest '[ $rc = 0 ] && grep -q " 0 failed" $log' tools/port/difftest/selftest.sh
  KEY='echo "$(grep -m1 "^TUs" $log), $(grep -c "FAIL$" port/build/census/files.tsv) FAIL (srcfix copies build: $(grep -m1 "^srcfix" $log | cut -d: -f2 | cut -c1-40)...)"'
  step census '[ $rc = 0 ] && ! grep -q "FAIL$" port/build/census/files.tsv' port/web/run.sh census
fi
KEY='echo "$(grep -h "census --incremental\|^vbe_build:" $log | tr "\n" " ") $(grep -h "link warnings" $log)"'
step build '[ $rc = 0 ]' port/web/run.sh build
[ $red = 0 ] && echo "GREEN ($MODE, $(( $(date +%s) - T0 ))s)" || echo "RED ($MODE, $(( $(date +%s) - T0 ))s): see $D/<step>.log"
exit $red
