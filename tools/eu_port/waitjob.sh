#!/bin/bash
# Block (in the foreground) until background jobs finish, at most MAX seconds per call
# (default 540, under the 600 s Bash tool limit). Call it again if it reports "still running".
# Use instead of ending your turn or sleep-polling.
#   waitjob.sh pid PID...        wait for these PIDs (yours) to exit
#   waitjob.sh file FILE PATTERN  wait until FILE contains PATTERN (e.g. a "done" marker)
MAX=${MAX:-540}; end=$(( $(date +%s) + MAX ))
mode=$1; shift
while [ $(date +%s) -lt $end ]; do
  case $mode in
    pid) alive=0; for p in "$@"; do kill -0 $p 2>/dev/null && alive=1; done
         [ $alive = 0 ] && { echo "done"; exit 0; } ;;
    file) grep -q -- "$2" "$1" 2>/dev/null && { echo "done"; exit 0; } ;;
    *) echo "usage: waitjob.sh pid PID... | file FILE PATTERN"; exit 2 ;;
  esac
  sleep 5
done
echo "still running (call waitjob.sh again)"; exit 1
