#!/bin/bash
# usage: fwdproto.sh <src_eu file> '<prototype;>' : insert a forward prototype after the last #include of the file
# (needed when the file calls the function implicitly before its definition, so a C draft is a CERR 'redeclaration')
f=$1; p=$2; n=$(grep -n '^#include' "$f" | tail -1 | cut -d: -f1)
grep -qF "$p" "$f" || perl -pi -e "\$_ .= qq{\n$p\n} if \$. == $n" "$f"
