#!/bin/bash
# P132: candidate file for difftest from the source's NM block that defines FUNC. usage: cand.sh FUNC file.c out.c
python3 - "$@" <<'PY'
import sys, re
f, src, out = sys.argv[1], open(sys.argv[2]).read(), sys.argv[3]
m = re.search(r'^[A-Za-z_][^\n;#/]*\b%s\s*\([^;{]*?\)\s*\{' % f, src, re.M)
s = src.rfind('#ifdef NON_MATCHING', 0, m.start()); e = src.find('\n#else', m.end())
open(out, 'w').write(src[s:e] + '\n#endif\n')
PY
