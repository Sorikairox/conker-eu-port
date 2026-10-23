#!/bin/bash
# asmhead.sh FUNC [N]: first N (default 30) instructions of FUNC from the EU disassembly (compact)
awk -v f="<$1>:" -v n="${2:-30}" '$2==f{p=1;next} p&&/^[0-9a-f]+ </{exit} p&&NF{sub(/^ */,"");print; if(++c>=n)exit}' /Users/sorikairo/conker-wt/port/port_work/p93/eu.dis | sed 's/\t/ /g'
