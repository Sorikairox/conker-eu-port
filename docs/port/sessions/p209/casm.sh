#!/bin/bash
# P207: compact asm listing (vaddr op args) of FUNC.s. usage: casm.sh path.s
grep -E '/\*|^[[:space:]]*\.L|glabel' "$1" | sed -E 's#^[[:space:]]*/\* [0-9A-F]+ ([0-9A-F]+) [0-9A-F]{8} \*/[[:space:]]+#\1 #; s/[[:space:]]+/ /g; s/^ //'
