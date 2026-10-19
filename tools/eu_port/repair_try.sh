#!/bin/bash
# usage: repair_try.sh <func> <draft.c>  -> one line "<func> OK|DIFFn|SIZE+-n|CERR..." 
# Screens the draft (m2c/try), saves it as tools/decomp-permuter/repair/<func>.c (latest) and the word
# diff as <func>.diff (used by repair_ctx.sh). An OK draft is also kept in conker/build/hand (apply.py build/hand).
R=${CONKER_ROOT:-$HOME/conker}/tools/decomp-permuter/repair; mkdir -p $R
f=$1; d=$2
[ "$(realpath $d)" != "$(realpath $R/$f.c 2>/dev/null)" ] && cp "$d" $R/$f.c
out=$(TRYDIR=rt_$f V=1 ${CONKER_ROOT:-$HOME/conker}/tools/eu_port/m2c/try $f $R/$f.c)
res=$(echo "$out" | head -1)
echo "$out" | tail -n +2 > $R/$f.diff
echo "$f $res"
case "$res" in OK*) ${CONKER_ROOT:-$HOME/conker}/tools/eu_port/m2c/keep $f $R/$f.c >/dev/null;; CERR*) head -5 ${CONKER_ROOT:-$HOME/conker}/conker/build/rt_$f/errs/$f.txt 2>/dev/null;; esac
