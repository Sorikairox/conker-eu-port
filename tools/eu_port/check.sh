#!/bin/bash
# P327/P329: pre-commit check for port-web (the byte-matching build is gone since P329; it lives on branch
# exact-byte-decomp-wip). One mode:
#   tools/eu_port/check.sh   implicit_scan (0 NM+float) + romabs_check + difftest selftest (reference code from the ROM,
#                            port/symbols) + full census (every TU, 0 FAIL) + incremental web build.
# (--port, the P328 name of this mode, is still accepted.)
#   tools/eu_port/check.sh --layout   the same + the layout-independence check (P353, tools/port/scripts/layout_cmp.sh
#                            check: two builds with n64_rdram moved, title menu route, ~4 min more; one headless Chrome)
# Sequential on purpose (the selftest and the census both load the container). Logs: port_work/check/.
# Prints one line per step (rc, seconds, key line) and a final GREEN / RED line; exit status 0 only when green.
LAYOUT=; case ${1:---port} in --port) ;; --layout) LAYOUT=1;; *) sed -n '2,8p' "$0"; exit 2;; esac
ROOT=$(git -C "$(dirname "$0")" rev-parse --show-toplevel) && cd "$ROOT" || exit 2   # P353: the worktree this script lives in
eval "$(tools/eu_port/wt.sh env "$(basename "$ROOT")")" || exit 2
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
KEY='tail -1 $log'; step implicit '[ $rc = 0 ] && grep -q " 0 NM+float" $log' python3 tools/port/implicit_scan.py
KEY='tail -1 $log'; step romabs '[ $rc = 0 ] && grep -q " 0 FAIL" $log' python3 port/tools/romabs_check.py
KEY='tail -1 $log'; step selftest '[ $rc = 0 ] && grep -q " 0 failed" $log' tools/port/difftest/selftest.sh
KEY='echo "$(grep -m1 "^TUs" $log), $(grep -c "FAIL$" port/build/census/files.tsv) FAIL (srcfix copies build: $(grep -m1 "^srcfix" $log | cut -d: -f2 | cut -c1-40)...)"'
step census '[ $rc = 0 ] && ! grep -q "FAIL$" port/build/census/files.tsv' port/web/run.sh census
KEY='echo "$(grep -h "census --incremental\|^vbe_build:" $log | tr "\n" " ") $(grep -h "link warnings" $log)"'
step build '[ $rc = 0 ]' port/web/run.sh build
if [ -n "$LAYOUT" ] && [ $red = 0 ]; then
  KEY='grep -h "^short\|LAYOUT" $log | tr "\n" " " | cut -c1-200'
  step layout '[ $rc = 0 ]' tools/port/scripts/layout_cmp.sh check
fi
[ $red = 0 ] && echo "GREEN ($(( $(date +%s) - T0 ))s)" || echo "RED ($(( $(date +%s) - T0 ))s): see $D/<step>.log"
exit $red
