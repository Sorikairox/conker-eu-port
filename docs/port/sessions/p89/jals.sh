#!/bin/bash
# P86: list decoded EU jal targets of an asm function: jals.sh <path-to-.s>  -> "name EUtarget" (unique)
python3 - "$1" <<'PY'
import re, sys
seen = set()
for l in open(sys.argv[1]):
    m = re.search(r'/\* \w+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/\s+jal\s+(\S+)', l)
    if m:
        pc, w = int(m.group(1), 16), int(m.group(2), 16)
        t = (pc & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
        k = '%s %08X' % (m.group(3), t)
        if k not in seen: seen.add(k); print(k)
PY
