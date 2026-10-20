# Slot: main checkout (parallel session)

You work in the **main checkout** ~/conker (branch `eu`), default container `conkerdev`
(CONKER_ROOT/CONKERDEV may stay unset). Another agent works in parallel in ~/conker-wt/a:
never touch ~/conker-wt/a, the `conkerdev-a` container, or branch `eu-wt-a`.

- Read tools/eu_port/AGENT_BRIEF.md and follow it exactly. Then HANDOFF.md, and
  docs/IDO_SHAPES.md before matching.
- Keep job outputs under conker/build_port/ (not the shared Claude scratchpad).
- **Never pkill/pgrep by name on the host** (e.g. `pkill -f permuter.py`), since that
  kills the other agent's jobs. Kill only PIDs you started, or your own /work/<id> jobs on
  the Mac mini.
- **Slice:** game files whose name ends in a hex offset **below 0x130000**
  (src_eu/game*_XXXXX.c, src_eu/game/done/game_XXXXX.c). Don't touch init, libultra,
  debugger, or game files at 0x130000 and above.
- Shared headers: only add lines or change single prototypes, then run check_files.py on
  everything.
- Budget: 2 work commits or about 40 functions tried, plus the hand-off commit. No
  background processes of yours may be left running.
- Hand-off: update HANDOFF's current state and next steps compactly, and add
  docs/sessions/sNN.md.
- **Hard context cap:** count your tool calls. After about 150, stop new work regardless of the
  function budget and do the hand-off. Keep tool outputs short (head/grep, no big asm dumps).
