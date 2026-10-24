#!/bin/bash
# P211: func_151C384C with ROMDATA + ARGMEM on its three requests (bytes the asm leaves unwritten skipped)
export DIFFTEST_ROMDATA=1 DIFFTEST_ARGMEM=151530A8=0:89,151530A8=0+5C:15,151530A8=0+6C:8,151307F0=0:92,151307F0=0+60:6,15160830=0:5,15160830=1:12
exec "$(dirname "$0")/full.sh" 151C384C
