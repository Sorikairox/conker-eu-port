#!/bin/bash
# P329: the hold-L regression (new game route, muted, det=2, one headless Chrome): Start at the title, then L held
# from retrace 5600 skips the opening. Expected: the opening ends at retrace 5789, level 0x29 follows, no traps.
#   tools/port/scripts/holdl.sh [NAME] [SECS]      (logs: port_work/p326/NAME/chrome.log)
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1   # P353: the worktree this script lives in
N=${1:-holdl}; T=${2:-200}
tools/port/scripts/newgame_summary.sh "$N" "$T" '3386:1000:0:0,3401:0:0:0,4458:1000:0:0,4473:0:0:0,5600:20:0:0,5800:0:0:0'
L=port_work/p326/$N/chrome.log
if grep -q "^\[p88\] scene frame 5789:" $L && ! grep -q "Aborted\|RuntimeError" $L; then echo "HOLD-L OK"; else echo "HOLD-L CHANGED (see $L)"; exit 1; fi
