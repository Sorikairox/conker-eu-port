#!/bin/bash
# P92: inserts the verified drafts (NM blocks) and the #undef block after func_15124C38.
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"
D=docs/port/sessions/p92
python3 tools/port/insert_nm.py "$@"
python3 - <<'PY'
p='conker/src_eu/game_14FF90.c'; s=open(p).read()
old='#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15124C38.s")\n#endif\n'
if old in s and 'P92: end of func_15124C38' not in s:
    s=s.replace(old, old+'#ifdef NON_MATCHING\n/* P92: end of func_15124C38 */\n#undef CAM_W\n#undef CAM_F\n#undef PL\n#undef HOLD\n#endif\n')
    open(p,'w').write(s); print('undef block added')
PY
