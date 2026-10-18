#!/bin/bash
# usage: sh.sh <func>   -> asm (one line) + fresh draft
f=$1; F=~/conker/tools/decomp-permuter/repair/fresh
grep -h -A80 "glabel $f\$" ~/conker/conker/asm/nonmatchings/*/$f.s | sed 's|.*\*/ *||;s/  */ /g' | tr '\n' ';' ; echo; echo ----; cat $F/$f.c
