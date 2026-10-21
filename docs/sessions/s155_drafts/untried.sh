#!/bin/bash
# s155: s149_targets rows still GLOBAL_ASM and not named in any s14x/s15x session doc or drafts dir
cd ~/conker
grep -v '^#' docs/sessions/s149_targets.txt | while read f n file c; do
  grep -q "GLOBAL_ASM(.*/$f.s" conker/src_eu/$file 2>/dev/null || continue
  grep -rqs "$f" docs/sessions/s14[0-9]*.md docs/sessions/s15[0-9]*.md docs/sessions/s14[0-9]_drafts docs/sessions/s15[0-9]_drafts HANDOFF.md && continue
  echo "$f $n $file $c"
done
