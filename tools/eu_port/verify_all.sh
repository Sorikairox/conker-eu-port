#!/bin/bash
# Full from-scratch verification of the EU build, with compact output.
#   clean re-split -> code build -> check_files.py -> full ROM -> progress
# Exit status 0 only if everything matches.
# Usage (repo root, on the host): tools/eu_port/verify_all.sh [--quick]
#   --quick: skip the clean re-split (reuse the current asm/ and build/)
set -uo pipefail
cd "$(dirname "$0")/../.."
DOCKER=${DOCKER:-docker}
command -v "$DOCKER" >/dev/null || DOCKER=/Applications/Docker.app/Contents/Resources/bin/docker
QUICK=${1:-}

# P245: named so a running one is identifiable in `docker ps` (was an anonymous name such as youthful_bhaskara)
CTNAME="verify-$(basename "$(pwd)")-$$"
"$DOCKER" run --rm --name "$CTNAME" --platform linux/amd64 -v "$(pwd)":/conker conker bash -c '
set -uo pipefail
fail=0
make VERSION=eu extract >/dev/null 2>&1 || { echo "FAIL root extract"; exit 1; }
cd conker
if [ "'"$QUICK"'" != "--quick" ]; then
  rm -rf asm build; find . -maxdepth 1 -name "*_auto.txt" -delete
  make VERSION=eu extract >/tmp/split.log 2>&1 || { echo "FAIL split"; tail -5 /tmp/split.log; exit 1; }
fi
rm -f build/conker.eu.ok
if make VERSION=eu -j8 >/tmp/build.log 2>&1 && grep -q "conker.eu.bin: OK" /tmp/build.log; then
  echo "code build: OK"
else
  echo "code build: FAIL"; grep -E "rror|FAILED" /tmp/build.log | sort -u | head -10; fail=1
fi
# known false SIZE reports for the last file of each code segment
bad=$(python3 ../tools/eu_port/check_files.py | grep -v "^OK" | grep -vE "init_eu_289A0|game_eu_227BF0|debugger_eu_259B40|bad of")
if [ -z "$bad" ]; then echo "check_files: OK"; else echo "check_files: FAIL"; echo "$bad" | head -20; fail=1; fi
if [ $fail -eq 0 ]; then
  make VERSION=eu replace >/dev/null 2>&1 && cd .. && rm -f build/conker.eu.* &&
  if make VERSION=eu -j8 2>&1 | grep -q "conker.eu.z64: OK"; then echo "full ROM: OK"; else echo "full ROM: FAIL"; fail=1; fi
  cd conker
fi
rm -f progress*.csv; make VERSION=eu progress >/dev/null 2>&1 && python3 ../tools/eu_port/progress.py
exit $fail
'
