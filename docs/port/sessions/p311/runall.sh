#!/bin/bash
# P311: run FUNC's current NM block against every setup of SETUPFILE (run1.sh), one verdict line per setup.
# usage: runall.sh FUNC SETUPFILE [setup ...]   (after wt.sh env)
F=$1; SF=$2; shift 2
D=$(dirname "$0")
names=("$@"); [ ${#names[@]} -eq 0 ] && names=($(grep -v '^#' "$SF" | awk '{print $1}'))
for n in "${names[@]}"; do printf '%-10s ' "$n"; NL=1 "$D/run1.sh" "$F" "$SF" "$n" | cut -c1-200; done
