#!/bin/bash
# P319: run a browser test command (p273/run.sh, p261/route.sh, p240/mp.sh ...) and stop it early when the page traps.
#   watch.sh LOG -- CMD ARGS...    LOG = the chrome.log the command writes. Kills only the Chrome / node it started.
L=$1; shift; [ "$1" = -- ] && shift
"$@" & P=$!
until [ -f "$L" ] || ! kill -0 $P 2>/dev/null; do sleep 2; done
while kill -0 $P 2>/dev/null; do
  if grep -q "RuntimeError\|Uncaught" "$L" 2>/dev/null; then
    sleep 3; echo "watch.sh: trap in $L, stopping"
    for n in $(ps -axo pid,ppid,command | awk '/[a]udprobe.js/{print $1}'); do
      # only the node driver whose ancestor is our command
      a=$n; while [ "$a" -gt 1 ]; do [ "$a" = $P ] && break; a=$(ps -o ppid= -p $a | tr -d ' '); done
      [ "$a" = $P ] || continue
      for c in $(ps -axo pid,ppid | awk -v n=$n '$2==n{print $1}'); do kill -9 $c 2>/dev/null; done
      sleep 1; kill $n 2>/dev/null
    done
    break
  fi
  sleep 5
done
wait $P; echo "watch.sh: rc $?"
grep -m3 -A6 "RuntimeError" "$L" | head -14
