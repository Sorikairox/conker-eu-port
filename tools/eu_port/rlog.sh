#!/bin/bash
# usage: rlog.sh func start attempts end y|n perm y|n "note"   -> appends a row to repair_log.tsv
printf '%s\t%s\t%s\t%s\t%s\t%s\t%s\n' "$@" >> ${CONKER_ROOT:-$HOME/conker}/tools/eu_port/repair_log.tsv
